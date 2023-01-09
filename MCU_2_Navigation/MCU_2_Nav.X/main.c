/*
 * File:   main.c
 * Author: orras
 *
 * Created on January 9, 2023, 1:09 PM
 */

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PWMLOCK = OFF            // PWM IOxCON lock (PWM IOxCON register writes accesses are not locked or protected)
#pragma config FUSBIDIO2 = OFF          // USB2 USBID Selection (USBID pin is controlled by the port function)
#pragma config FVBUSIO2 = OFF           // USB2 VBUSON Selection bit (VBUSON pin is controlled by the port function)
#pragma config PGL1WAY = OFF            // Permission Group Lock One Way Configuration bit (Allow multiple reconfigurations)
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO1 = OFF          // USB1 USBID Selection (USBID pin is controlled by the port function)
#pragma config FVBUSIO1 = OFF           // USB2 VBUSON Selection bit (VBUSON pin is controlled by the port function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1        // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC     // INTERNAL System PLL Input Clock Selection (POSC is input to the System PLL)
//#pragma config FPLLICLK = PLL_POSC      // EXTERNAL System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_80        // System PLL Multiplier (PLL Multiply by 80)
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider)
#pragma config BORSEL = HIGH            // Brown-out trip voltage (BOR trip voltage 2.1v (Non-OPAMP deviced operation))
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL Disabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable Secondary Oscillator)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF             // Primary Oscillator Configuration (External clock mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config TRCEN = ON               // Trace Enable (Trace features in the CPU are enabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = ECC_DECC_DISABLE_ECCON_WRITABLE// Dynamic Flash ECC Configuration Bits (ECC and Dynamic ECC are disabled (ECCCON<1:0> bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = PG_ALL          // Debug Mode CPU Access Permission (Allow CPU access to all permission regions)
#pragma config SMCLR = MCLR_NORM        // Soft Master Clear Enable (MCLR pin generates a normal system Reset)
#pragma config SOSCGAIN = G3            // Secondary Oscillator Gain Control bits (Gain is G3)
#pragma config SOSCBOOST = OFF          // Secondary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
#pragma config POSCGAIN = G3            // Primary Oscillator Coarse Gain Control bits (Gain Level 3 (highest))
#pragma config POSCBOOST = OFF          // Primary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
#pragma config POSCFGAIN = G3           // Primary Oscillator Fine Gain Control bits (Gain is G3)
#pragma config POSCAGCDLY = AGCRNG_x_25ms// AGC Gain Search Step Settling Time Control (Settling time = 25ms x AGCRNG)
#pragma config POSCAGCRNG = ONE_X       // AGC Lock Range bit (Range 1x)
#pragma config POSCAGC = Automatic      // Primary Oscillator Gain Control bit (Automatic Gain Control for Oscillator)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot Enable (Normal EJTAG functionality)

// DEVCP
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// SEQ
#pragma config TSEQ = 0xFFFF            // Boot Flash True Sequence Number (Enter Hexadecimal value)
#pragma config CSEQ = 0xFFFF            // Boot Flash Complement Sequence Number (Enter Hexadecimal value)

#include <xc.h>

void main(void) {
    return;
}
