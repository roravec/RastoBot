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

#define FCY         120000000UL
#define REFO1CLK    120000000UL // UARTs, SPI
#define PBCLK2      60000000UL // I2C1 I2C2
#define PBCLK3      60000000UL // I2C3 I2C4
#define REFO4CLK    120000000UL // CAN
#define _DI()		__builtin_disable_interrupts()
#define _EI()		__builtin_enable_interrupts()

/* Function prototypes */
void Config_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_ticks(uint32_t del);
void InitOscillator(void);
void InitInterrupts(void);
void InitGPIOs();

#endif	/* CONFIG_H */

