#include "StepperDriver.h"

void Stepper_Init(StepperMotor stepper, StepperStepMode mode, StepperDirection dir)
{
    Stepper_ChangeDirection(stepper, dir);
    Stepper_ChangeStepMode(stepper, mode);
    Stepper_Enable(stepper);
}
void Stepper_Step(StepperMotor stepper)
{
    MP6500_Step(stepper);
}
void Stepper_ChangeDirection(StepperMotor stepper, StepperDirection dir)
{
    MP6500_SetDirection(stepper, dir);
}
void Stepper_ChangeStepMode(StepperMotor stepper, StepperStepMode mode)
{
    _Bool ms1 = (_Bool)mode;
    _Bool ms2 = (_Bool)(mode>>1);
    MP6500_SetMS(stepper, ms1, ms2);
}
void Stepper_Enable(StepperMotor stepper)
{
    MP6500_SetEnable(stepper, STEPPER_ENABLE);
}
void Stepper_Disable(StepperMotor stepper)
{
    MP6500_SetEnable(stepper, STEPPER_DISABLE);
}