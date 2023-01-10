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

#define MCU0_READ_TEMPERATURE_EVERY     1000 // loop ticks
#define MCU0_DHT11_SENSORS_COUNT        4

#define MCU0_FAN0_TEMP_THRESHOLD        25

#ifdef	__cplusplus
extern "C" {
#endif
    
/* Includes */
#include "RastoBot.h"
#include "hwinterface.h"
#include "dht11.h"

/* Globals */
    extern MCU_0_Sensors sensors;

/* Function prototypes */
    void MCU0_Init(void);
    void MCU0_Loop(void);
    _Bool MCU0_Read_TiltSensor(void);
    void MCU0_ReadDHT11(void);
    void MCU0_FanControl(void);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU0_H */

