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

#define MCU0_READ_TEMPERATURE_EVERY     400 // loop ticks
#define MCU0_READ_ANALOG_PINS_EVERY     350
#define MCU0_READ_TILT_SENSOR_EVERY     1
#define MCU0_FAN_CONTROL_EVERY          10
#define MCU0_SEND_SENSORS_DATA_EVERY    300
#define MCU0_CHECK_FOR_RECV_DATA_EVERY  1

#define MCU0_DHT11_SENSORS_COUNT        4
#define MCU0_FANS_COUNT                 4

#define MCU0_FAN0_TEMP_THRESHOLD        25
#define MCU0_FAN1_TEMP_THRESHOLD        25
#define MCU0_FAN2_TEMP_THRESHOLD        25
#define MCU0_FAN3_TEMP_THRESHOLD        25

#define MCU0_FAN0_THERMOMETERS          0b1111
#define MCU0_FAN1_THERMOMETERS          0b0001
#define MCU0_FAN2_THERMOMETERS          0b0010
#define MCU0_FAN3_THERMOMETERS          0b0100

#define MCU0_FAN_LATCH0_FANINDEX        0       // binds power output latch to fan
#define MCU0_FAN_LATCH1_FANINDEX        1       // binds power output latch to fan
#define MCU0_FAN_LATCH2_FANINDEX        2       // binds power output latch to fan
#define MCU0_FAN_LATCH3_FANINDEX        3       // binds power output latch to fan


#ifdef	__cplusplus
extern "C" {
#endif
    
/* Includes */
#include "../../SW/libs/RastoBot.h"
#include "hwinterface.h"
#include "dht11.h"
#include "pic18_uart.h"

/* Globals */
    extern MCU_0_Sensors sensors;

/* Function prototypes */
    void MCU0_Init(void);
    
    // Main loop. Should be called every 1ms
    void MCU0_Loop(void);
    
    /* Sensors */
    void MCU0_ReadTiltSensor(void);
    void MCU0_ReadDHT11(void);
    void MCU0_ReadAnalogPins(void);
    uint16_t MCU0_AnalogReadValue(uint8_t channel);
    
    /* Getters */
    _Bool MCU0_GetExternalInputDetected(void);
    
    /* Setters */
    void MCU0_SetBuzzer(uint16_t ticks);
    void MCU0_SetChargingEnable(_Bool pinStatus);
    void MCU0_SetEmergencyLight(_Bool pinStatus);
    void MCU0_SetLED(uint8_t led, _Bool status);
    
#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU0_H */

