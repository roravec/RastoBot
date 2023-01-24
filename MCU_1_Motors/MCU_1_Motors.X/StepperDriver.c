#include "StepperDriver.h"

void Stepper_Init(Stepper* stepper, uint8_t hwId, StepperStepMode mode, StepperDirection dir)
{
    stepper->hwId = hwId;
    Stepper_ChangeDirection(stepper, dir);
    Stepper_ChangeStepMode(stepper, mode);
    Stepper_ChangeSpeed(stepper, STEPPER_MAX_SPEED);
    Stepper_Disable(stepper);
    stepper->steps = 0;
    stepper->speedCalcSteps = 0;
    stepper->stepsToMake = 0;
}
void Stepper_Step(Stepper* stepper)
{
    if (stepper->speed == 0) // skip
        return;
    if (stepper->opMode == STEPPER_STEPS_ON_DEMAND && stepper->stepsToMake == 0)
        return;
    uint16_t skip = STEPPER_MAX_SPEED / stepper->speed;
    uint16_t skipAt = stepper->speedCalcSteps % skip;
    if (skipAt == 0) // make step
    {
        stepper->steps++;
        stepper->speedCalcSteps++;
        if (stepper->opMode == STEPPER_STEPS_ON_DEMAND)
            stepper->stepsToMake--;
        MP6500_Step(stepper->hwId);
    }
    else
    {
        stepper->speedCalcSteps++;
    }
}
void Stepper_MakeSteps(Stepper* stepper, uint32_t steps)
{
    if (stepper->opMode == STEPPER_CONTINOUS)
        Stepper_ChangeOperMode(stepper, STEPPER_STEPS_ON_DEMAND);
    stepper->stepsToMake += steps;
}
void Stepper_Stop(Stepper* stepper)
{
    Stepper_ChangeOperMode(stepper, STEPPER_STEPS_ON_DEMAND);
    stepper->stepsToMake = 0;
}
void Stepper_ChangeSpeed(Stepper* stepper, uint16_t speed)
{
    stepper->speed = speed;
    stepper->speedCalcSteps = 0;
}
void Stepper_ChangeDirection(Stepper* stepper, StepperDirection dir)
{
    stepper->direction = dir;
    MP6500_SetDirection(stepper->hwId, dir);
}
void Stepper_ChangeOperMode(Stepper* stepper, StepperOperMode mode)
{
    stepper->stepsToMake = 0;
    stepper->opMode = mode;
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