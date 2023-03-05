#include "RastoBot_MCU0.h"
/* GLOBALS */
MCU_0_Sensors sensors;
uint16_t buzzerTick = 0;

ECP_Message sensorsMessage;
uint8_t sensorDataArr[ECP_MAX_PACKET_LEN];
Rarray sendPacket;

//Rarray recvPacket;
//ECP_Message recvMessage;

/* STATIC FUNCTIONS ***********************************************************/
static void MCU0_DoTasks(void);
static void MCU0_DoMessageAction(ECP_Message * msg);

/* Fan control */
static void MCU0_FanControl(void);
static void MCU0_FanPowerControl(void);

/* TASKS */
// This function should run all tasks
static void MCU0_TaskBuzzerBuzz(void);
static void MCU0_TaskLogPowerOutputs(void);
static void MCU0_TaskSendSensorsData(void);
static void MCU0_TaskCheckForNewReceivedData(void);
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
    
    RarrayCreate(&sendPacket, sensorDataArr, ECP_MAX_PACKET_LEN);
    
    // reset fans
    for (uint8_t i=0;i<MCU0_FANS_COUNT;i++)
        fansActive[i] = 0;
    UART_Init();
}
uint16_t loopCounter = 0;
static void MCU0_DoTasks(void)
{
    if (loopCounter % MCU0_FAN_CONTROL_EVERY == 0)
        MCU0_FanControl();
    MCU0_TaskBuzzerBuzz();
    if (loopCounter % MCU0_SEND_SENSORS_DATA_EVERY == 0)
        MCU0_TaskSendSensorsData();
    if (loopCounter % MCU0_CHECK_FOR_RECV_DATA_EVERY == 0)
        MCU0_TaskCheckForNewReceivedData();
}

// Main MCU0 loop - should be called every 1ms
uint8_t led1 = 0;
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
    MCU0_SetLED(1, led1);
    if (loopCounter % 10 == 0)
        led1 = ~led1;
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
    if (sensors.fanManualControl)
        return;
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
void MCU0_SetBuzzer(uint16_t ticks)
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
        BUZZER_LAT = 1;
        sensors.buzzer = 1;
        buzzerTick--;
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

static void MCU0_TaskSendSensorsData(void)
{
    MCU0_TaskLogPowerOutputs();
    //RastoBot_Encode_Sensors(&sensorsMessage, &sensors);
    RastoBot_Encode_Sensors_1(&sensorsMessage, &sensors);
    ECP_EncodeExtended(&sensorsMessage, &sendPacket, ECP_DATA_SIZE_MCU0_TO_MCU2);
    UART_WriteData(sendPacket.data, sendPacket.size);
    __delay_ms(100);
    RastoBot_Encode_Sensors_2(&sensorsMessage, &sensors);
    ECP_EncodeExtended(&sensorsMessage, &sendPacket, ECP_DATA_SIZE_MCU0_TO_MCU2);
    UART_WriteData(sendPacket.data, sendPacket.size);
    __delay_ms(100);
    RastoBot_Encode_Sensors_3(&sensorsMessage, &sensors);
    ECP_EncodeExtended(&sensorsMessage, &sendPacket, ECP_DATA_SIZE_MCU0_TO_MCU2);
    UART_WriteData(sendPacket.data, sendPacket.size);
    __delay_ms(100);
    RastoBot_Encode_Sensors_4(&sensorsMessage, &sensors);
    ECP_EncodeExtended(&sensorsMessage, &sendPacket, ECP_DATA_SIZE_MCU0_TO_MCU2);
    UART_WriteData(sendPacket.data, sendPacket.size);
}

static void MCU0_TaskCheckForNewReceivedData(void)
{
    ECP_Message * msg;  // pointer to message to process
    while ((msg = ECP_MessageDequeue()) != 0) // check if we have some message to process in queue
    {
        // a new message has been received and decoded. Let's process it...
        MCU0_DoMessageAction(msg);      // do requested action
        ECP_MarkMessageAsComplete(msg); // mark message as processed. It will free up space in queue.
    }
}

static void MCU0_DoMessageAction(ECP_Message * msg)
{
    if (msg->command == ECP_COMMAND_SENSORS_SET)
    {
        switch (msg->subCommand)
        {
            case 0: sensors.fanManualControl = 0; break;
            case 1: sensors.fanManualControl = 1; break;
            case 10: POWER_OUTPUT_0_LAT = 1; break;
            case 11: POWER_OUTPUT_1_LAT = 1; break;
            case 12: POWER_OUTPUT_2_LAT = 1; break;
            case 13: POWER_OUTPUT_3_LAT = 1; break;
            case 14: MCU0_SetEmergencyLight(1); break;
            case 20: POWER_OUTPUT_0_LAT = 0; break;
            case 21: POWER_OUTPUT_1_LAT = 0; break;
            case 22: POWER_OUTPUT_2_LAT = 0; break;
            case 23: POWER_OUTPUT_3_LAT = 0; break;
            case 24: MCU0_SetEmergencyLight(0); break;
            case 30: MCU0_SetLED(0,1); break;
            case 31: MCU0_SetLED(1,1); break;
            case 32: MCU0_SetLED(2,1); break;
            case 40: MCU0_SetLED(0,0); break;
            case 41: MCU0_SetLED(1,0); break;
            case 42: MCU0_SetLED(2,0); break;
            case 50: MCU0_SetChargingEnable(0); break;
            case 51: MCU0_SetChargingEnable(1); break;
            case 100: MCU0_SetBuzzer(20); break;
            case 101: MCU0_SetBuzzer(40); break;
            case 102: MCU0_SetBuzzer(60); break;
            case 103: MCU0_SetBuzzer(80); break;
            case 104: MCU0_SetBuzzer(100); break;
            case 105: MCU0_SetBuzzer(150); break;
            default: break;
        }
    }
}