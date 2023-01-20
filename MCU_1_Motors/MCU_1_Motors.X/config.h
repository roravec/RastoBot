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

#define SYS_LOCK { SYSKEY = 0x00000000; }
#define SYS_UNLOCK { SYSKEY = 0x00000000; SYSKEY = 0xAA996655; SYSKEY = 0x556699AA; SYSKEY = 1;}

#define FCY         24000000UL // CPU frequency
#define PCLK        24000000UL // peripheral frequency
#define REFCLK      24000000UL   // output to PWM
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

