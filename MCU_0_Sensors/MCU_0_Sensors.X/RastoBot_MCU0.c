#include "RastoBot_MCU0.h"

MCU_0_Sensors sensors;

void MCU0_Init(void)
{
    
}

// call every 1ms
uint32_t loopCounter = 0;
void MCU0_Loop(void)
{
    MCU0_Read_TiltSensor();
    if (loopCounter % MCU0_READ_TEMPERATURE_EVERY == 0)
        MCU0_ReadDHT11();
    
    MCU0_FanControl();
    loopCounter++;
}

_Bool MCU0_Read_TiltSensor(void)
{
    sensors.tiltSensor = TILT_SENSOR_PORT;
    LED_0_LAT = sensors.tiltSensor;
}

void MCU0_ReadDHT11(void)
{
    DHT11_SensorData dht11data;
    for (uint8_t sensor = 0; sensor < MCU0_DHT11_SENSORS_COUNT ; sensor++)
    if (DHT11_GetSensorData(sensor, &dht11data))
    {
        sensors.temperatures[sensor] = dht11data.temperature;
        sensors.humidities[sensor] = dht11data.humidity;
    }
}

void MCU0_FanControl(void)
{
    if (sensors.temperatures[0] > MCU0_FAN0_TEMP_THRESHOLD)   
        POWER_OUTPUT_0_LAT = 1;
    else                                
        POWER_OUTPUT_0_LAT = 0;
}