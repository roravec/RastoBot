/* 
 * File:   StepperDriver.h
 * Author: orras
 *
 * Created on January 19, 2023, 9:47 PM
 */

#ifndef STEPPERDRIVER_H
#define	STEPPERDRIVER_H

#include "MP6500.h"

#define	STEPPER_MAX_SPEED   1024

#ifdef	__cplusplus
extern "C" {
#endif
    
#define STEPPER_ENABLE 0
#define STEPPER_DISABLE 1
    
#define STEPPER_STEP_SCHEDULER 0    // make step on all motors simultaneously

typedef enum
{
    STEPPER_CW = 0,    
    STEPPER_CCW = 1
} StepperDirection;

typedef enum
{
    STEPPER_CONTINOUS = 0,    
    STEPPER_STEPS_ON_DEMAND = 1
} StepperOperMode;

typedef enum
{
    STEPPER_FULL_STEP = 0,    
    STEPPER_HALF_STEP = 1,
    STEPPER_QUARTER_STEP = 2,
    STEPPER_EIGHTH_STEP = 3
} StepperStepMode;

typedef struct
{
    uint8_t             hwId;
    StepperDirection    direction;
    StepperStepMode     stepMode:2;
    uint16_t            speed;      // 1024 maximum
    _Bool               enabled;
    uint32_t            steps;
    
    StepperOperMode     opMode:2;
    uint32_t            stepsToMake;
    
    uint32_t            position;
    uint16_t            stepsPerRevolution;
    uint16_t            wheelDiameter;
    uint16_t            speedCalcSteps;
    
    _Bool               stepScheduled;
} Stepper;

void Stepper_Init(Stepper*, uint8_t hwId, StepperStepMode, StepperDirection);
void Stepper_Step(Stepper*);
void Stepper_FinishStep(Stepper*);
void Stepper_MakeSteps(Stepper*, uint32_t);
void Stepper_Stop(Stepper*);
void Stepper_ChangeSpeed(Stepper*, uint16_t);
void Stepper_ChangeDirection(Stepper*, StepperDirection);
void Stepper_ChangeOperMode(Stepper*, StepperOperMode);
void Stepper_ChangeStepMode(Stepper*, StepperStepMode);
void Stepper_Enable(Stepper*);
void Stepper_Disable(Stepper*);


#ifdef	__cplusplus
}
#endif

#endif	/* STEPPERDRIVER_H */

