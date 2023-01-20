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
    
#include <stdint.h>
#include "ermaCommProtocol.h"
    
#define ECP_COMMAND_SENSORS_STATUS     101
#define ECP_COMMAND_SENSORS_STATUS_DLC 26
#define ECP_COMMAND_SENSORS_SET        201

typedef struct
{
    int16_t		batteryVoltage;
	int16_t		externalVoltage;
    _Bool       externalInputDetected;
	int8_t		temperatures[4];
    uint8_t		humidities[4];
	int16_t		currentSensors[4];
	_Bool		powerOutputs[5];
	_Bool		buzzer;
	_Bool		tiltSensor;
	uint16_t    rainSensor;
	uint16_t	lightSensor;
	_Bool		chargingEnabled;
    _Bool       fanManualControl;
} MCU_0_Sensors;

ECP_Message *   RastoBot_Encode_Sensors(ECP_Message * out, MCU_0_Sensors * sensors);
MCU_0_Sensors * RastoBot_Decode_Sensors(MCU_0_Sensors * sensorsOut, ECP_Message * in);


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_H */

