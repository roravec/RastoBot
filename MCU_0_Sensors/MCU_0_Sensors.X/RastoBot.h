/* 
 * File:   RastoBot.h
 * Author: orras
 *
 * Created on January 9, 2023, 9:14 PM
 * Version: 1
 */

#ifndef RASTOBOT_H
#define	RASTOBOT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>

typedef struct
{
    int32_t		batteryVoltage;
	int32_t		externalVoltage;
    _Bool       externalInputDetected;
	int32_t		temperatures[4];
    int32_t		humidities[4];
	int32_t		currentSensors[4];
	_Bool		powerOutputs[5];
	_Bool		buzzer;
	_Bool		tiltSensor;
	uint32_t    rainSensor;
	uint32_t	lightSensor;
	_Bool		chargingEnabled;
} MCU_0_Sensors;


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_H */

