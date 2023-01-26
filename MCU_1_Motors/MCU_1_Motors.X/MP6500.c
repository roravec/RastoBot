#include "MP6500.h"

void MP6500_SetDirection(uint8_t stepper, _Bool value)
{
    switch (stepper)
    {
        case 0: STEPDRV_0_DIR_LAT = value;
                break;
        case 1: STEPDRV_1_DIR_LAT = value; 
                break;
        case 2: STEPDRV_2_DIR_LAT = value; 
                break;
        default: break; 
    }
}
void MP6500_SetEnable(uint8_t stepper, _Bool value)

{
    switch (stepper)
    {
        case 0: STEPDRV_0_ENABLE_LAT = value;
                break;
        case 1: STEPDRV_1_ENABLE_LAT = value; 
                break;
        case 2: STEPDRV_2_ENABLE_LAT = value; 
                break;
        default: break; 
    }
}
void MP6500_SetMS(uint8_t stepper, _Bool ms1, _Bool ms2)
{
    switch (stepper)
    {
        case 0: STEPDRV_0_MS1_LAT = ms1;
                STEPDRV_0_MS2_LAT = ms2;
                break;
        case 1: STEPDRV_1_MS1_LAT = ms1; 
                STEPDRV_1_MS2_LAT = ms2;
                break;
        case 2: STEPDRV_2_MS1_LAT = ms1; 
                STEPDRV_2_MS2_LAT = ms2;
                break;
        default: break; 
    }
}
void MP6500_Step(uint8_t stepper)
{
    switch (stepper)
    {
        case 0: STEPDRV_0_STEP_LAT = 1;
                Delay_us(MP6500_LATCH_HOLD_HIGH);
                STEPDRV_0_STEP_LAT = 0;
                break;
        case 1: STEPDRV_1_STEP_LAT = 1;
                Delay_us(MP6500_LATCH_HOLD_HIGH);
                STEPDRV_1_STEP_LAT = 0;
                break;
        case 2: STEPDRV_2_STEP_LAT = 1;
                Delay_us(MP6500_LATCH_HOLD_HIGH);
                STEPDRV_2_STEP_LAT = 0;
                break;
        default: break; 
    }
}

void MP6500_StepSetLatch(uint8_t stepper, _Bool latch)
{
    switch (stepper)
    {
        case 0: STEPDRV_0_STEP_LAT = latch;
                break;
        case 1: STEPDRV_1_STEP_LAT = latch;
                break;
        case 2: STEPDRV_2_STEP_LAT = latch;
                break;
        default: break; 
    }
}