#include "StepperDriver.h"

void Stepper_Init(Stepper* stepper, uint8_t hwId, StepperStepMode mode, StepperDirection dir)
{
    stepper->hwId = hwId;
    Stepper_ChangeDirection(stepper, dir);
    Stepper_ChangeStepMode(stepper, mode);
    Stepper_ChangeSpeed(stepper, 1023);
    Stepper_Enable(stepper);
    stepper->steps = 0;
}
void Stepper_Step(Stepper* stepper)
{
    if ((stepper->steps % (STEPPER_MAX_SPEED - stepper->speed)) == 0)
        MP6500_Step(stepper->hwId);
    stepper->steps++;
}
void Stepper_ChangeSpeed(Stepper* stepper, uint16_t speed)
{
    stepper->speed = speed;
    stepper->steps = 0;
    
}
void Stepper_ChangeDirection(Stepper* stepper, StepperDirection dir)
{
    stepper->direction = dir;
    MP6500_SetDirection(stepper->hwId, dir);
}
void Stepper_ChangeStepMode(Stepper* stepper, StepperStepMode mode)
{
    _Bool ms1 = (_Bool)mode;
    _Bool ms2 = (_Bool)(mode>>1);
    stepper->stepMode = mode;
    MP6500_SetMS(stepper->hwId, ms1, ms2);
}
void Stepper_Enable(Stepper* stepper)
{
    stepper->enabled = 1;
    MP6500_SetEnable(stepper->hwId, STEPPER_ENABLE);
}
void Stepper_Disable(Stepper* stepper)
{
    stepper->enabled = 0;
    MP6500_SetEnable(stepper->hwId, STEPPER_DISABLE);
}