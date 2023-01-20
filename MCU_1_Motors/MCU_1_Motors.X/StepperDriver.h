/* 
 * File:   StepperDriver.h
 * Author: orras
 *
 * Created on January 19, 2023, 9:47 PM
 */

#ifndef STEPPERDRIVER_H
#define	STEPPERDRIVER_H

#include "MP6500.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define STEPPER_ENABLE 0
#define STEPPER_DISABLE 1

#define STEPPER_NUMBER_OF_STEPPERS  3
typedef enum
{
    STEPPER_LEFT_WHEEL = 0,    
    STEPPER_RIGHT_WHEEL = 1,
    STEPPER_LEVELING = 2
} StepperMotor;

typedef enum
{
    STEPPER_CW = 0,    
    STEPPER_CCW = 1
} StepperDirection;

typedef enum
{
    STEPPER_FULL_STEP = 0,    
    STEPPER_HALF_STEP = 1,
    STEPPER_QUARTER_STEP = 2,
    STEPPER_EIGHTH_STEP = 3
} StepperStepMode;

    void Stepper_Init(StepperMotor, StepperStepMode, StepperDirection);
    void Stepper_Step(StepperMotor);
    void Stepper_ChangeDirection(StepperMotor, StepperDirection);
    void Stepper_ChangeStepMode(StepperMotor, StepperStepMode);
    void Stepper_Enable(StepperMotor);
    void Stepper_Disable(StepperMotor);


#ifdef	__cplusplus
}
#endif

#endif	/* STEPPERDRIVER_H */

