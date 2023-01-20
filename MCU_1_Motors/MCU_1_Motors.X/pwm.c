/* File:   pwm.c
 * Author: skorra
 * Created on July 27, 2022, 7:59 AM
 * Version: 
 * 
 * Description: 
 */

#include "pwm.h"

static uint8_t preScale = 64;
static uint32_t pwmClockFreq = PWM_CLOCK_FREQ;

static uint32_t actualFqPeriod = 0;
static uint32_t actualDutyPeriod = 0;

void PWM_Init()
{
    CCP2CON1 = 0; // default values
    CCP2CON2 = 0; // default values
    /* PWM outputs */
    CCP2CON1bits.CLKSEL = 0b000;
    CCP2CON1bits.CCSEL = 0; // output
    CCP2CON1bits.T32=0;
    CCP2CON2bits.OCAEN = 1;
    // Set 1:64 prescale value to get slowest times
    CCP2CON1bits.TMRPS = 0b11;
    CCP2CON1bits.MOD = 0b0101; // Dual Edge PWM mode, buffered
    PWM_Set(PWM_STATIC_FREQ, 20);
    //PWM_SetDirect(62499, 10000);
    
    CCP2CON1bits.ON = 1;
}

void PWM_Set(float pwmFreq, uint8_t dutyPercent)
{
    // make correction
    if (pwmFreq < 501)
        pwmFreq = pwmFreq * 0.99;
    else if (pwmFreq >= 501 && pwmFreq < 800){}
    else
        pwmFreq = pwmFreq * 1.01;
    uint32_t topP = (pwmClockFreq + (preScale * pwmFreq) / 2) ;
    uint32_t bottomP = (preScale * pwmFreq) - 1;
    uint32_t period = topP / bottomP;
    // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
    float dutyCalcF = 0;
    dutyCalcF = ((float)period / (float)100);
    float dutyCalc = (float)dutyCalcF * (float)dutyPercent;
    PWM_SetDirect(period, dutyCalc);
}

void PWM_SetDuty(uint8_t dutyPercent)
{
    float dutyCalcF = 0;
    dutyCalcF = ((float)actualFqPeriod / (float)100);
    float dutyCalc = (float)dutyCalcF * (float)dutyPercent;
    PWM_SetDirect(actualFqPeriod, dutyCalc);
}

void PWM_SetDirect(uint32_t period, uint32_t duty)
{
    actualFqPeriod = period;
    actualDutyPeriod = duty;
    //CCP1PR = period; // 62499
    CCP2PR = period; // set pwm frequency
    CCP2RB = duty; // set duty
}