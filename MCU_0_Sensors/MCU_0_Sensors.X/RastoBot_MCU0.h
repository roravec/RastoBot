/* 
 * File:   RastoBot_MCU0.h
 * Author: orras
 *
 * Created on January 9, 2023, 9:44 PM
 */

/*
 * Function types:
 *  read - get data from sensor, update data structure that hold sensor values, return sensor data
 */

#ifndef RASTOBOT_MCU0_H
#define	RASTOBOT_MCU0_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/* Includes */
#include "RastoBot.h"
#include "hwinterface.h"

/* Globals */
    extern MCU_0_Sensors sensors;

/* Function prototypes */
    void MCU0_Init(void);
    void MCU0_Loop(void);
    _Bool MCU0_Read_TiltSensor(void);
    
    /* DHT11 temperature sensor */
    void MCU0_DHT11_Start(uint8_t sensorIndex);
    void DHT11_CheckResponse(uint8_t sensorIndex);
    void MCU0_DHT11_Read(uint8_t sensorIndex);
    

#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU0_H */

