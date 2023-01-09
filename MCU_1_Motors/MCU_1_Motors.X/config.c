/* File:   config.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: General use config file
 */ 
#include "config.h"

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

void Config_Init(void)
{
    InitOscillator();
    InitInterrupts();
    HwInterface_Init();
    InitGPIOs();
}

void InitOscillator(void)
{
    SYSKEY = 0x00000000; // force lock
    SYSKEY = 0xAA996655; // unlock
    SYSKEY = 0x556699AA;
    // Fin = 8MHz
    // Fvco = 64MHz // 16 to 96
    // Fpll = 16MHz // 2 to 24
    SPLLCONbits.PLLICLK = 1; // select POSC as input
    SPLLCONbits.PLLMULT = 0b0000100; // 8*8 = 64MHz // max is 96
    SPLLCONbits.PLLODIV = 0b010; // 64/4 = 16MHz
    // ROSEL = SYSCLK
    // DIVSWEN = 1
    // RODIV = 4
    REFO1CONbits.DIVSWEN = 1;
    REFO1CONbits.ROSEL = 0;
    REFO1CONbits.RODIV = 2; // 4MHz PWM input
    REFO1TRIM = 0x0;
    REFO1CONSET = 0x00008000;
    
    /* DIV_4, MUL_8, PLLSRC= FRC */
    //8SPLLCON = 0x2040080;
    
    OSCCON = OSCCON | 0x00000101;    //NOSC = SPLL, initiate clock switch (OSWEN = 1)
    
    //SYSKEY = 0x00000000; // force lock
    SYSKEY = 0x33333333;
    while (OSCCONbits.OSWEN); // optional wait for ?
    
    /* From documentation:
     * PLLODIV<2:0>: System PLL Output Clock Divider bits
        111 = PLL divide-by-256
        110 = PLL divide-by-64
        101 = PLL divide-by-32
        100 = PLL divide-by-16
        011 = PLL divide-by-8
        010 = PLL divide-by-4
        001 = PLL divide-by-2
        000 = PLL divide-by-1 (default setting)
     * 
        PLLMULT<6:0>: System PLL Multiplier bits
        111111-0000111 = Reserved
        0000110 = 24x
        0000101 = 12x
        0000100 = 8x
        0000011 = 6x
        0000010 = 4x
        0000001 = 3x (default setting)
        0000000 = 2x
     */
}

void InitInterrupts(void)
{
    asm volatile("ei");
    __builtin_enable_interrupts();
}

void InitGPIOs()
{
    MAIN_MOTOR_LAT = 1;
    STEPDRV_0_ENABLE_LAT = 1;
    STEPDRV_1_ENABLE_LAT = 1;
    STEPDRV_2_ENABLE_LAT = 1;
}