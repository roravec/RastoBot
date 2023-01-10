/* File:   config.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: General use config file
 */ 
#include "config.h"

//uint32_t __coretimer = 0; // used to calculate core ticks
//void Delay_us(unsigned long us)
//{
//    // Convert microseconds us into how many clock ticks it will take
//    us *= FCY / 1000000 / 2; // Core Timer updates every 2 ticks
//    //_CP0_SET_COUNT(0); // Set Core Timer count to 0
//    //__coretimer = _CP0_GET_COUNT();
//
//    //while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
//}
//void Delay_ms(uint32_t ms)
//{
//    Delay_us(ms * 1000);
//}
void Delay_ticks(unsigned int del)
{
    for(uint32_t time = 0; time < del; time++){
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
    
    REFOCONbits.ROON = 0; // disable REFO on RB2
    
    T1CON  = 0x10; // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H  = 0;           // reset Timer1
    TMR1L  = 0;
    
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
    ANCON1 = 0x1F; // disable analog on Tilt sensor, MCU_TEMP_sensors (set 1 to disable)
    
    POWER_OUTPUT_0_LAT = 0;
    POWER_OUTPUT_1_LAT = 0;
    POWER_OUTPUT_2_LAT = 0;
    POWER_OUTPUT_3_LAT = 0;
    LED_0_LAT = 1;
    LED_1_LAT = 1;
    LED_2_LAT = 1;
    EXT_INPUT_ENABLE_LAT = 1;
    
    TEMP_SENSOR_0_TRIS = 0;
    TEMP_SENSOR_0_LAT = 0;
}
