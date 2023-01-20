/* File:   config.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: General use config file
 */ 
#include "config.h"

uint32_t __coretimer = 0; // used to calculate core ticks
void Delay_us(unsigned long us)
{
    // Convert microseconds us into how many clock ticks it will take
    us *= FCY / 1000000 / 2; // Core Timer updates every 2 ticks
    _CP0_SET_COUNT(0); // Set Core Timer count to 0
    __coretimer = _CP0_GET_COUNT();

    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}
void Delay_ms(uint32_t ms)
{
    Delay_us(ms * 1000);
}
void Delay_ticks(uint32_t del)
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
    SYS_UNLOCK;

    SPLLCONbits.PLLICLK = 1; // 1-FRC; 0-POSC
    SPLLCONbits.PLLMULT = 0b0000101; // 12;  8*12 = 96
    SPLLCONbits.PLLODIV = 0b010; // 96/4 = 16MHz

    REFO1CONbits.DIVSWEN = 1;
    REFO1CONbits.ROSEL = 0b0111; // pll out
    REFO1CONbits.RODIV = 2; // 96/2 = 24MHz
    REFO1TRIM = 0x0;
    REFO1CONbits.ON = 1;
    
    
    // SETUP PERIPRHERALS
    RPINR9bits.U2RXR = 15;  // U2RX
    RPOR3bits.RP14R = 1;    // U2TX
    RPOR2bits.RP9R = 6;     // OCM3, SCCP2 Output Compare
    // **********************************

    OSCCON = OSCCON | 0x00000101;    //NOSC = SPLL, initiate clock switch (OSWEN = 1)
    while (OSCCONbits.OSWEN); // optional wait
    SYS_LOCK;
}

void InitInterrupts(void)
{
    INTCONbits.MVEC = 1;
    asm volatile("ei");
    __builtin_enable_interrupts();
}

void InitGPIOs()
{
    ANSELA = 0; // disable analog function
    ANSELB = 0; // disable analog function
    ANSELC = 0; // disable analog function
}