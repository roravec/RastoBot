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
    //_CP0_SET_COUNT(0); // Set Core Timer count to 0
    //__coretimer = _CP0_GET_COUNT();

    //while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
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

void Config_Init()
{
    InitOscillator();
    InitInterrupts();
    HwInterface_Init();
    InitGPIOs();
}

void InitOscillator(void)
{
    //internal oscillator setup - 8 MHz
    IRCF2 = 1;
    IRCF1 = 1;
    IRCF0 = 1;
    
    /* From documentation:
        111 = PLL output divided by 256
        110 = PLL output divided by 64
        101 = PLL output divided by 32
        100 = PLL output divided by 16
        011 = PLL output divided by 8
        010 = PLL output divided by 4
        001 = PLL output divided by 2
        000 = PLL output divided by 1
     */
}

void InitInterrupts(void)
{
    PEIE = 1;
    GIE = 1;
    RCIF = 0;
    RCIE = 1;
    TXIE = 0;
    TMR0IE = 1;
}

void InitGPIOs()
{
    FAN_0_LAT = 1;
    FAN_1_LAT = 1;
    FAN_2_LAT = 1;
    FAN_3_LAT = 1;
    LED_0_LAT = 1;
    LED_1_LAT = 1;
    LED_2_LAT = 1;
    EXT_INPUT_ENABLE_LAT = 1;
}
