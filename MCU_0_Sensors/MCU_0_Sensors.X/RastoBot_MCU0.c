#include "RastoBot_MCU0.h"

MCU_0_Sensors sensors;

void MCU0_Init(void)
{
    
}

void MCU0_Loop(void)
{
    MCU0_Read_TiltSensor();
}

_Bool MCU0_Read_TiltSensor(void)
{
    sensors.tiltSensor = TILT_SENSOR_PORT;
    LED_0_LAT = sensors.tiltSensor;
}

void MCU0_DHT11_Start(uint8_t sensorIndex)
{
    
}
void MCU0_DHT11_Read(uint8_t sensorIndex)
{
    
}
            