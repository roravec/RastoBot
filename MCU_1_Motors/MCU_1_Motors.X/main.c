/*
 * File:   main.c
 * Author: orras
 *
 * Created on January 9, 2023, 1:07 PM
 */


// PIC32MM0064GPL028 Configuration Bit Settings

// 'C' source line config statements

// FDEVOPT
#pragma config SOSCHP = OFF             // Secondary Oscillator High Power Enable bit (SOSC oprerates in normal power mode.)
#pragma config USERID = 0xFFFF          // User ID bits (Enter Hexadecimal value)

// FICD
#pragma config JTAGEN = OFF              // JTAG Enable bit (JTAG is enabled)
#pragma config ICS = PGx1               // ICE/ICD Communication Channel Selection bits (Communicate on PGEC1/PGED1)

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config RETVR = OFF              // Retention Voltage Regulator Enable bit (Retention regulator is disabled)
#pragma config LPBOREN = ON             // Low Power Brown-out Enable bit (Low power BOR is enabled, when main BOR is disabled)

// FWDT
#pragma config SWDTPS = PS1048576       // Sleep Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config FWDTWINSZ = PS25_0       // Watchdog Timer Window Size bits (Watchdog timer window size is 25%)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Watchdog timer is in non-window mode)
#pragma config RWDTPS = PS1048576       // Run Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config RCLKSEL = LPRC           // Run Mode Watchdog Timer Clock Source Selection bits (Clock source is LPRC (same as for sleep mode))
#pragma config FWDTEN = OFF              // Watchdog Timer Enable bit (WDT is enabled)

// FOSCSEL
#pragma config FNOSC = PLL            // Oscillator Selection bits (Primary or FRC oscillator with PLL)
//#pragma config FNOSC = FRCDIV           // Oscillator Selection bits (Primary or FRC oscillator with PLL)
//#pragma config PLLSRC = PRI           // System PLL Input Clock Selection bit (FRC oscillator is selected as PLL reference input on device reset)
#pragma config PLLSRC = FRC             // System PLL Input Clock Selection bit (FRC oscillator is selected as PLL reference input on device reset)
#pragma config SOSCEN = OFF             // Secondary Oscillator Enable bit (Secondary oscillator is enabled)
#pragma config IESO = OFF               // Two Speed Startup Enable bit (Two speed startup is enabled)
#pragma config POSCMOD = OFF             // Primary Oscillator Selection bit (Primary oscillator is disabled)
#pragma config OSCIOFNC = OFF           // System Clock on CLKO Pin Enable bit (OSCO pin operates as a normal I/O)
#pragma config SOSCSEL = ON            // Secondary Oscillator External Clock Enable bit (SOSC pins configured for Crystal mode)
#pragma config FCKSM = CSECME           // Clock Switching and Fail-Safe Clock Monitor Enable bits (Clock switching is enabled; Fail-safe clock monitor is enabled)

// FSEC
#pragma config CP = OFF                 // Code Protection Enable bit (Code protection is disabled)

#include "config.h"
#include "RastoBot_MCU1.h"

void setup()
{
    Config_Init();
    MCU1_Init();
}

void main(void) {
    setup();
    while (1)
    {
        Delay_us(900);
        MCU1_Loop();
    }
    return;
}