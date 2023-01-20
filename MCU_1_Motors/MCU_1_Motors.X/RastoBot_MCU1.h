/* 
 * File:   RastoBot_MCU1.h
 * Author: orras
 *
 * Created on January 19, 2023, 9:42 PM
 */

#ifndef RASTOBOT_MCU1_H
#define	RASTOBOT_MCU1_H

#include "../../SW/libs/RastoBot.h"
#include "StepperDriver.h"
#include "pwm.h"
#include "pic32mm_uart.h"

#define MCU1_CHECK_NEW_MESSAGES_EVERY   1
#define MCU1_MOTOR_CONTROL_EVERY        1

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    STEPPER_LEFT_WHEEL = 0,    
    STEPPER_RIGHT_WHEEL = 1,
    STEPPER_LEVELING = 2
} StepperMotorId;

/* Function prototypes */
void MCU1_Init(void);

// Main loop. Should be called every 10ms
void MCU1_Loop(void);



/* Getters */


/* Setters */
void MCU1_SetMainMotorSpeed(uint8_t);
Stepper * MCU1_GetStepperByHwId(uint8_t id);
void MCU1_SetStepperDirection(Stepper * stepper, StepperDirection dir);
void MCU1_SetStepperSpeed(Stepper * stepper, uint16_t speed);
void MCU1_SetStepperStepMode(Stepper * stepper, StepperStepMode mode);
void MCU1_SetStepperEnable(Stepper * stepper);
void MCU1_SetStepperDisable(Stepper * stepper);



#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU1_H */

