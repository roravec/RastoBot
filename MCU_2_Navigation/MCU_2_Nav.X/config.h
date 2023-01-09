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

/* PIC32MK specific*/
#define IOUnLock()  {SYSKEY=0x0; SYSKEY=0xAA996655; SYSKEY=0x556699AA; CFGCONbits.IOLOCK=0;} 
#define IOLock()    {CFGCONbits.IOLOCK=1; SYSKEY=0x0;}
#define PMDUnLock() {SYSKEY=0x0; SYSKEY=0xAA996655; SYSKEY=0x556699AA; CFGCONbits.PMDLOCK=0;} 
#define PMDLock()   {CFGCONbits.PMDLOCK=1; SYSKEY=0x0;} 

#define FCY         80000000UL
//#define PCLK        40000000UL
#define REFO1CLK    80000000UL  // UARTs
#define REFO2CLK    80000000UL  // I2C
#define REFO4CLK    80000000UL  // CAN
#define _DI()		__builtin_disable_interrupts()
#define _EI()		__builtin_enable_interrupts()

/* Function prototypes */
void Config_Init(void);
void Delay_us(unsigned long us);
void Delay_ms(unsigned int ms);
void Delay_ticks(unsigned int del);
void InitOscillator(void);
void InitInterrupts(void);
void InitGPIOs();

#endif	/* CONFIG_H */

