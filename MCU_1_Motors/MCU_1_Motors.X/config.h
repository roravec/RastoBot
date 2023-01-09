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
#include <p32xxxx.h>

#define FCY         64000000UL // CPU frequency
#define PCLK        16000000UL // peripheral frequency
#define REFCLK      4000000UL   // output to PWM
#define SYS_FREQ    PCLK

/* Function prototypes */
void Config_Init(void);
void Delay_us(unsigned long us);
void Delay_ms(unsigned int ms);
void Delay(unsigned int del);
void InitOscillator(void);
void InitInterrupts(void);
void InitGPIOs(void);
/***********************/

#endif	/* CONFIG_H */

