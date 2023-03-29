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
#define MCU1_LOG_DATA_TO_STRUCT_EVERY   1
#define MCU1_MOTOR_CONTROL_EVERY        1
#define MCU1_SEND_STATUS_DATA_EVERY     1000

#define MCU1_LEVELING_REFRUN_STEPS      10000UL
#define MCU1_LEVELING_REFRUN_LOOP_TICKS 10500UL        // for ho many tick it will be impossible to control leveling
#define MCU1_LEVELING_TOTAL_STEPS       10000UL
#define MCU1_LEVELING_TOTAL_POSITIONS   20
#define MCU1_LEVELING_STEPS_PER_POS     (MCU1_LEVELING_TOTAL_STEPS / MCU1_LEVELING_TOTAL_POSITIONS)
#define MCU1_LEVELING_TIME_PER_STEP     (MCU1_LEVELING_REFRUN_LOOP_TICKS / 10000UL)

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
Stepper * MCU1_GetStepperByHwId(uint8_t id);

/* Setters */
void MCU1_SetMainMotorSpeed(uint8_t);
void MCU1_SetStepperDirection(uint8_t id, StepperDirection dir);
void MCU1_SetStepperSpeed(uint8_t id, uint16_t speed);
void MCU1_SetStepperMakeSteps(uint8_t stepperHwId, uint32_t steps);
void MCU1_SetStepperStepMode(uint8_t id, StepperStepMode mode);
void MCU1_SetStepperOperMode(uint8_t stepperHwId, StepperOperMode mode);
void MCU1_SetStepperStop(uint8_t stepperHwId);
void MCU1_SetStepperEnable(uint8_t id);
void MCU1_SetStepperDisable(uint8_t id);
_Bool MCU1_LevelingIsWaiting();
void MCU1_LevelingReferenceRun(void);
void MCU1_LevelingGoToPosition(uint8_t position);



#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU1_H */

