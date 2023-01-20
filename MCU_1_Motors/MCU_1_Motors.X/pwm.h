
/* File:   pwm.h
 * Author: skorra
 * Created on July 27, 2022, 7:59 AM
 * Version: 
 * 
 * Description: 
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "config.h"

#define PWM_CLOCK_FREQ      SYSCLK

#define PWM_STATIC_FREQ     100

typedef enum { BOTH=0, RISING, FALLING, BOTH2, RISING4TH=4, FALLING4TH} PwmEdgeCaptureTrigger;

void PWM_Init(void);
void PWM_Set(float pwmFreq, uint8_t dutyPercent);
void PWM_SetDirect(uint32_t period, uint32_t duty);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

