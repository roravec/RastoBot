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

/* MCU1 */
#define MCU1_STEPPERS   3

#define ECP_COMMAND_MOTORS_STATUS     111
#define ECP_COMMAND_MOTORS_STATUS_DLC 12
#define ECP_COMMAND_MOTORS_SET        211

#define ECP_COMMAND_MOTORS_SET        211

typedef struct
{
    uint8_t     mainMotorSpeed; // percent
    _Bool       stepperEnabled[MCU1_STEPPERS];
    _Bool       stepperDirection[MCU1_STEPPERS];
    uint8_t     stepperStepMode[MCU1_STEPPERS];
    uint8_t     stepperOperMode[MCU1_STEPPERS];
    uint16_t    stepperSpeed[MCU1_STEPPERS];
    uint32_t    stepperSteps[MCU1_STEPPERS];
    uint32_t    stepperStepsToMake[MCU1_STEPPERS];
    uint32_t    stepperPosition[MCU1_STEPPERS];
    uint16_t    stepperStepsPerRevolution[MCU1_STEPPERS];
    uint16_t    stepperWheelDiameter[MCU1_STEPPERS];
    uint16_t    levelingPosition;
    _Bool       limitSwitchUP;
    _Bool       limitSwitchDOWN;
} MCU_1_MotorsDebug;

typedef struct
{
    uint8_t     mainMotorSpeed; // percent
    _Bool       stepperEnabled[MCU1_STEPPERS];
    _Bool       stepperDirection[MCU1_STEPPERS];
    uint8_t     stepperStepMode[MCU1_STEPPERS];
    uint8_t     stepperOperMode[MCU1_STEPPERS];
    uint16_t    stepperSpeed[MCU1_STEPPERS];
    uint16_t    levelingPosition;
} MCU_1_Motors;

typedef struct
{
    _Bool       stepperEnabled[2];
    _Bool       stepperDirection[2];
    uint8_t     stepperStepMode[2];
    uint8_t     stepperOperMode[2];
    uint16_t    stepperSpeed[2];
    uint32_t    stepperSteps[2];
} MCU_1_WheelsMotorControl;


ECP_Message *   RastoBot_Encode_Sensors(ECP_Message * out, MCU_0_Sensors * sensors);
MCU_0_Sensors * RastoBot_Decode_Sensors(MCU_0_Sensors * sensorsOut, ECP_Message * in);
ECP_Message *   RastoBot_Encode_Motors(ECP_Message * out, MCU_1_Motors * motors);
MCU_1_Motors *  RastoBot_Decode_Motors(MCU_1_Motors * motorsOut, ECP_Message * in);


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_H */