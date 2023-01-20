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

#ifdef	__cplusplus
extern "C" {
#endif

/* Function prototypes */
void MCU1_Init(void);

// Main loop. Should be called every 10ms
void MCU1_Loop(void);



/* Getters */


/* Setters */



#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU1_H */

