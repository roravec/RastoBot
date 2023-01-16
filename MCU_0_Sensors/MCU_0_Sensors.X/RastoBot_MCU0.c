#include "RastoBot_MCU0.h"
/* GLOBALS */
MCU_0_Sensors sensors;
uint32_t buzzerTick = 0;

/* STATIC FUNCTIONS ***********************************************************/
static void MCU0_DoTasks(void);

/* Fan control */
static void MCU0_FanControl(void);
static void MCU0_FanPowerControl(void);

/* TASKS */
// This function should run all tasks
static void MCU0_TaskBuzzerBuzz(void);
static void MCU0_TaskLogPowerOutputs(void);
/******************************************************************************/


/*  Bind fans for every DHT11
 * 
 For example lets bind fans 0, 2 and 3 for thermometer index 1:
 thermometerFanBind[1] = 0b1011;
 * 
 * 0b1011 = ON,OFF,ON,ON = 0-ON, 1-OFF, 2-ON, 3-ON
 */
uint8_t fanThermometerBind[MCU0_FANS_COUNT] = 
{ 
    MCU0_FAN0_THERMOMETERS, 
    MCU0_FAN1_THERMOMETERS, 
    MCU0_FAN2_THERMOMETERS, 
    MCU0_FAN3_THERMOMETERS
};
uint8_t fansActive[MCU0_FANS_COUNT];

/******************************************************************************/

/* Init function */
void MCU0_Init(void)
{
    ADCON1bits.ACQT = 0b111; // A/D Acquisition Time Select bits
    ADCON1bits.ADCS = 0b110;
    ADCON1bits.ADFM = 1;
    ADCON0bits.ADON = 1;
    
    // reset fans
    for (uint8_t i=0;i<MCU0_FANS_COUNT;i++)
        fansActive[i] = 0;
}

static void MCU0_DoTasks(void)
{
    MCU0_FanControl();
    MCU0_TaskBuzzerBuzz();
}

// Main MCU0 loop - should be called every 1ms
uint32_t loopCounter = 0;
void MCU0_Loop(void)
{
    if (loopCounter % MCU0_READ_ANALOG_PINS_EVERY == 0)
        MCU0_ReadAnalogPins();
    if (loopCounter % MCU0_READ_TILT_SENSOR_EVERY == 0)
        MCU0_ReadTiltSensor();
    if (loopCounter % MCU0_READ_TEMPERATURE_EVERY == 0)
        MCU0_ReadDHT11();
    
    MCU0_DoTasks();
    loopCounter++;
}

/* SENSORS ********************************************************************/
void MCU0_ReadTiltSensor(void)
{
    sensors.tiltSensor = TILT_SENSOR_PORT;
    LED_0_LAT = sensors.tiltSensor;
}

void MCU0_ReadDHT11(void)
{
    DHT11_SensorData dht11data;
    for (uint8_t sensor = 0; sensor < MCU0_DHT11_SENSORS_COUNT ; sensor++)
    {
        if (DHT11_GetSensorData(sensor, &dht11data))
        {
            sensors.temperatures[sensor] =  dht11data.temperature;
            sensors.humidities[sensor] =    dht11data.humidity;
        }
    }
}

// Reads all analog pins
void MCU0_ReadAnalogPins(void)
{
    sensors.currentSensors[0] = MCU0_AnalogReadValue(CURRENT_SENSOR_0_ANCH);
    sensors.currentSensors[1] = MCU0_AnalogReadValue(CURRENT_SENSOR_1_ANCH);
    sensors.currentSensors[2] = MCU0_AnalogReadValue(CURRENT_SENSOR_2_ANCH);
    sensors.currentSensors[3] = MCU0_AnalogReadValue(CURRENT_SENSOR_3_ANCH);
    sensors.rainSensor =        MCU0_AnalogReadValue(RAIN_SENSOR_ANCH);
    sensors.rainSensor =        MCU0_AnalogReadValue(LIGHT_SENSOR_ANCH);
    sensors.batteryVoltage =    MCU0_AnalogReadValue(BATTERY_STATUS_ANCH);
}

uint16_t MCU0_AnalogReadValue(uint8_t channel)
{
    uint16_t readValue = 0;
    ADCON0bits.CHS = channel;
    //ADCON1bits.ADCAL = 1; // start calibration
    ADCON0bits.GO_DONE= 1; //Start the ADC conversion
    while(ADCON0bits.GO_DONE == 1); //Do nothing until the conversion has finished
    readValue = ADRESH;
    readValue = readValue << 8;
    readValue = readValue | ADRESL;
    ADCON1bits.ADCAL = 0; // stop calibration until next reading
    return readValue;
}

/* FANS ***********************************************************************/
static void MCU0_FanControl(void)
{
    uint8_t fansActivePoints[MCU0_FANS_COUNT];
    // reset fans
    for (uint8_t i=0;i<MCU0_FANS_COUNT;i++)
        fansActivePoints[i] = 0;
    
    for (uint8_t fan = 0; fan < MCU0_FANS_COUNT ; fan++)
    {
        for (uint8_t sensor = 0; sensor < MCU0_DHT11_SENSORS_COUNT ; sensor++)
        {
            _Bool thermometerActive = (_Bool)(fanThermometerBind[fan] >> (MCU0_DHT11_SENSORS_COUNT-sensor-1));
            if (thermometerActive && sensors.temperatures[sensor] > MCU0_FAN0_TEMP_THRESHOLD)
            {
                // turn on the fan
                fansActivePoints[fan]++;
            }
        }
        // If current fan collected enough points to be turned on then turn it on
        if (fansActivePoints[fan] > 0)
        {
            fansActive[fan] = 1;
        }
        else
        {
            fansActive[fan] = 0;
        }
    }
    MCU0_FanPowerControl(); // call power control to actually turn on/off fans by fansActive array
}
// Either turns off or turns on fans by setup in "fansActive" array
static void MCU0_FanPowerControl(void)
{
    POWER_OUTPUT_0_LAT = fansActive[MCU0_FAN_LATCH0_FANINDEX];
    POWER_OUTPUT_1_LAT = fansActive[MCU0_FAN_LATCH1_FANINDEX];
    POWER_OUTPUT_2_LAT = fansActive[MCU0_FAN_LATCH2_FANINDEX];
    POWER_OUTPUT_3_LAT = fansActive[MCU0_FAN_LATCH3_FANINDEX];
}

_Bool MCU0_GetExternalInputDetected(void)
{
    sensors.externalInputDetected = EXT_INPUT_SENSE_PORT;
    return EXT_INPUT_SENSE_PORT;
}

// Tun on buzzer for TICKS cycles of loop
void MCU0_SetBuzzer(uint32_t ticks)
{
    buzzerTick = ticks;
}

void MCU0_SetChargingEnable(_Bool pinStatus)
{
    sensors.chargingEnabled = pinStatus;
    EXT_INPUT_ENABLE_LAT = pinStatus;
}

void MCU0_SetEmergencyLight(_Bool pinStatus)
{
    POWER_OUTPUT_4_LAT = pinStatus;
}

void MCU0_SetLED(uint8_t led, _Bool status)
{
    switch (led)
    {
        case 0: LED_0_LAT = status;
            break;
        case 1: LED_1_LAT = status;
            break;
        case 2: LED_2_LAT = status;
            break;
        default: break;
    }
}


/* TASKS - functions which are called only from loop to do basic tasks */
/* WARNING: Do not invoke this functions somewhere else */

// Task to control buzzer active
static void MCU0_TaskBuzzerBuzz(void)
{
    if (buzzerTick > 0)
    {
        buzzerTick--;
        BUZZER_LAT = 1;
        sensors.buzzer = 1;
    }
    else
    {
        BUZZER_LAT = 0;
        sensors.buzzer = 0;
    }
}

// read actual status on power outputs and write them to sensors structure
static void MCU0_TaskLogPowerOutputs(void)
{
    sensors.powerOutputs[0] = POWER_OUTPUT_0_PORT;
    sensors.powerOutputs[1] = POWER_OUTPUT_1_PORT;
    sensors.powerOutputs[2] = POWER_OUTPUT_2_PORT;
    sensors.powerOutputs[3] = POWER_OUTPUT_3_PORT;
    sensors.powerOutputs[4] = POWER_OUTPUT_4_PORT;
}