/* File:   pwm.c
 * Author: skorra
 * Created on July 27, 2022, 7:59 AM
 * Version: 
 * 
 * Description: 
 */

#include "pwm.h"

static uint8_t preScale = 16;
static uint32_t pwmClockFreq = REFCLK;

void PWM_Init()
{
    CCP2CON1 = 0; // default values
    /* PWM outputs */
    CCP2CON1bits.CLKSEL = 0b001;
    CCP2CON1bits.CCSEL = 0; // output
    // Set 1:64 prescale value to get slowest times
    CCP2CON1bits.TMRPS = 0b10;
    CCP2CON1bits.MOD = 0b0101; // Dual Edge PWM mode, buffered
    //PWM_Set(PWM_STATIC_FREQ, 90);
    PWM_SetDirect(30000, 10000);
    
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

void PWM_SetDirect(uint32_t period, uint32_t duty)
{
    //CCP1PR = period; // 62499
    CCP2PR = period; // set pwm frequency
    CCP2RB = duty; // set duty
}