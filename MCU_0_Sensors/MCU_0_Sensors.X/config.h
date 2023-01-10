/* 
 * File:   config.h
 * Author: orras
 *
 * Created on January 9, 2023, 2:22 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include "hwinterface.h"

#define FCY         8000000UL // CPU frequency
#define PCLK        8000000UL // peripheral frequency 
#define _XTAL_FREQ  FCY
#define _DI()		__builtin_disable_interrupts()
#define _EI()		__builtin_enable_interrupts()

#define SYS_FREQ    PCLK

/* Function prototypes */
void Config_Init(void);
//void Delay_us(unsigned long us);
//void Delay_ms(unsigned int ms);
//void Delay(unsigned int del);
void InitOscillator(void);
void InitInterrupts(void);
void InitGPIOs(void);
/***********************/


#endif	/* CONFIG_H */

