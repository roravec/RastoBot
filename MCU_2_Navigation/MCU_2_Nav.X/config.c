/* File:   config.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: General use config file
 */ 
#include "config.h"

void Config_Init(void)
{
    InitOscillator();
    InitInterrupts();
    HwInterface_Init();
    InitGPIOs();
}
int __coretimer = 0; // used to calculate core ticks
void Delay_us(unsigned long us)
{
    // Convert microseconds us into how many clock ticks it will take
    us *= FCY / 1000000 / 2; // Core Timer updates every 2 ticks
    _CP0_SET_COUNT(0); // Set Core Timer count to 0
    __coretimer = _CP0_GET_COUNT();

    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}
void Delay_ms(unsigned int ms)
{
    Delay_us(ms * 1000);
}
void Delay_ticks(unsigned int del)
{
    for(unsigned int time = 0; time < del; time++){
        asm("nop");
    }
}
void InitOscillator(void)
{
    /* unlock system for clock configuration */
    PMDUnLock();
    /* Peripheral Module Disable Configuration */
    PMD1 = 0x371;
    PMD2 = 0x17001f;
    PMD3 = 0xffffffff;
    PMD4 = 0xfff01ff;
    //PMD5 = 0xd30e3f39; // can2 with uarts 1,2,3 // documentation page 643, table 33-1
    PMD5 = 0xDFFEFBF8; // CAN2, all uarts, I2C1, SPI3 // documentation page 643, table 33-1, 0 to enable clock to periphery
    //PMD5 = 0xDFFEFBF8; // CAN2, all uarts, I2C1, SPI3 // documentation page 643, table 33-1, 0 to enable clock to periphery
    PMD6 = 0xf0d0000;
    PMD7 = 0x0;
    /* Lock system since done with clock configuration */
    PMDLock();
    
    /* Configure CP0.K0 for optimal performance (cached instruction pre-fetch) */
    __builtin_mtc0(16, 0,(__builtin_mfc0(16, 0) | 0x3));

    /* Configure Wait States and Prefetch */
    CHECONbits.PFMWS = 1;
    CHECONbits.PREFEN = 1;
   
    // REFO1 - UART SPI
    /* Selecting the SYSCLK as input for REFO4CLK*/
    //REFO1CONbits.ROSEL = 7;
    REFO1CON = 0x200;
    /* Selecting the REFO4 prescaler to 3*/
    REFO1CONbits.RODIV = 0;
    REFO1TRIMbits.ROTRIM = 0;
    REFO1CONSET = 0x00008000;
    
    PB2DIVbits.PBDIV = 0;
    
    // REFO4 - CAN
    /* Selecting the SYSCLK as input for REFO4CLK*/
    //REFO4CONbits.ROSEL = 7;
    REFO4CON = 0x200;
    /* Selecting the REFO4 prescaler to 3*/
    REFO4CONbits.RODIV = 0;
    REFO4TRIMbits.ROTRIM = 0;
    REFO4CONSET = 0x00008000;
}

void InitInterrupts(void)
{
    //asm volatile("ei");
    INTCONSET = _INTCON_MVEC_MASK;
    /* Set up priority and subpriority of enabled interrupts */
    IPC10SET = 0x400 | 0x0;  /* I2C1_BUS:  Priority 1 / Subpriority 0 */
    IPC10SET = 0x4000000 | 0x0;  /* I2C1_MASTER:  Priority 1 / Subpriority 0 */
    IPC42SET = 0x4 | 0x0;  /* CAN2:  Priority 1 / Subpriority 0 */
//    IPC42SET = 0x1F;  /* CAN2:  Priority 7 / Subpriority 3 */
    __builtin_enable_interrupts();
}

void InitGPIOs()
{
    LED_0_LAT = 1;
    LED_1_LAT = 1;
    LED_2_LAT = 1;
    LED_3_LAT = 1;
}