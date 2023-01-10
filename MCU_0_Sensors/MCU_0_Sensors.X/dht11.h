/* 
 * File:   dht11.h
 * Author: orras
 *
 * Created on January 10, 2023, 9:44 PM
 * https://simple-circuit.com/mplab-xc8-dht11-sensor-pic-mcu/
 */

#ifndef DHT11_H
#define	DHT11_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "config.h"
    
#define DHT11_MODULE_0_TRIS     TEMP_SENSOR_0_TRIS
#define DHT11_MODULE_0_LAT      TEMP_SENSOR_0_LAT
#define DHT11_MODULE_0_PORT     TEMP_SENSOR_0_PORT
#define DHT11_MODULE_1_TRIS     TEMP_SENSOR_1_TRIS
#define DHT11_MODULE_1_LAT      TEMP_SENSOR_1_LAT
#define DHT11_MODULE_1_PORT     TEMP_SENSOR_1_PORT
#define DHT11_MODULE_2_TRIS     TEMP_SENSOR_2_TRIS
#define DHT11_MODULE_2_LAT      TEMP_SENSOR_2_LAT
#define DHT11_MODULE_2_PORT     TEMP_SENSOR_2_PORT
#define DHT11_MODULE_3_TRIS     TEMP_SENSOR_3_TRIS
#define DHT11_MODULE_3_LAT      TEMP_SENSOR_3_LAT
#define DHT11_MODULE_3_PORT     TEMP_SENSOR_3_PORT
    
typedef struct
{
    int8_t temperature;
    int8_t humidity;
} DHT11_SensorData;
    
    void        DHT11_Start         (uint8_t module);
    _Bool       DHT11_CheckResponse (uint8_t module);
    uint8_t     DHT11_GetData       (uint8_t module);
    void        DHT11_ChangeDirection(uint8_t module, _Bool direction);
    void        DHT11_SetLatch      (uint8_t module, _Bool latVal);
    _Bool       DHT11_ReadSensorData(uint8_t module, uint8_t * dataOut);
    _Bool        DHT11_GetSensorData (uint8_t module, DHT11_SensorData * dataOut);

#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_H */

