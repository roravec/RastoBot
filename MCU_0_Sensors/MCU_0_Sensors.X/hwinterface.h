/* 
 * File:   pins.h
 * Author: orras
 *
 * Created on January 9, 2023, 2:21 PM
 */

#ifndef HWINTERFACE_H
#define	HWINTERFACE_H

#include <xc.h>

/* UART ***********************************/
#define UART_RX_TRIS        TRISCbits.TRISC7
#define UART_TX_TRIS        TRISCbits.TRISC6
/******************************************/ 

/* Power outputs **************************/
#define POWER_OUTPUT_0_TRIS TRISDbits.TRISD4
#define POWER_OUTPUT_0_LAT  LATDbits.LATD4
#define POWER_OUTPUT_0_PORT PORTDbits.RD4
#define POWER_OUTPUT_1_TRIS TRISDbits.TRISD5
#define POWER_OUTPUT_1_LAT  LATDbits.LATD5
#define POWER_OUTPUT_1_PORT PORTDbits.RD5
#define POWER_OUTPUT_2_TRIS TRISDbits.TRISD6
#define POWER_OUTPUT_2_LAT  LATDbits.LATD6
#define POWER_OUTPUT_2_PORT PORTDbits.RD6
#define POWER_OUTPUT_3_TRIS TRISDbits.TRISD7
#define POWER_OUTPUT_3_LAT  LATDbits.LATD7
#define POWER_OUTPUT_3_PORT PORTDbits.RD7
#define POWER_OUTPUT_4_TRIS TRISCbits.TRISC0
#define POWER_OUTPUT_4_LAT  LATCbits.LATC0
#define POWER_OUTPUT_4_PORT PORTCbits.RC0
/******************************************/

/* LEDS ***********************************/
#define LED_0_TRIS          TRISDbits.TRISD0
#define LED_0_LAT           LATDbits.LATD0
#define LED_1_TRIS          TRISDbits.TRISD1
#define LED_1_LAT           LATDbits.LATD1
#define LED_2_TRIS          TRISDbits.TRISD2
#define LED_2_LAT           LATDbits.LATD2
/******************************************/

/* OTHER OUTPUTS **************************/
#define BUZZER_TRIS         TRISCbits.TRISC1
#define BUZZER_LAT          LATCbits.LATC1
/******************************************/

/* TEMP SENSORS ***************************/
#define TEMP_SENSOR_0_TRIS  TRISBbits.TRISB2
#define TEMP_SENSOR_0_LAT   LATBbits.LATB2
#define TEMP_SENSOR_0_PORT  PORTBbits.RB2
#define TEMP_SENSOR_1_TRIS  TRISBbits.TRISB3
#define TEMP_SENSOR_1_LAT   LATBbits.LATB3
#define TEMP_SENSOR_1_PORT  PORTBbits.RB3
#define TEMP_SENSOR_2_TRIS  TRISBbits.TRISB1
#define TEMP_SENSOR_2_LAT   LATBbits.LATB1
#define TEMP_SENSOR_2_PORT  PORTBbits.RB1
#define TEMP_SENSOR_3_TRIS  TRISBbits.TRISB0
#define TEMP_SENSOR_3_LAT   LATBbits.LATB0
#define TEMP_SENSOR_3_PORT  PORTBbits.RB0
/******************************************/

/* DCINPUT SENSORS ************************/
#define EXT_INPUT_SENSE_TRIS    TRISBbits.TRISB5
#define EXT_INPUT_SENSE_PORT    PORTBbits.RB5
#define EXT_INPUT_ENABLE_TRIS   TRISDbits.TRISD3
#define EXT_INPUT_ENABLE_LAT    LATDbits.LATD3
#define BATTERY_STATUS_TRIS     TRISAbits.TRISA2
#define BATTERY_STATUS_AN       AN2
#define BATTERY_STATUS_ANCH     0b0010
/******************************************/

/* CURRENT SENSORS ************************/
#define CURRENT_SENSOR_0_TRIS   TRISAbits.TRISA0
#define CURRENT_SENSOR_0_AN     AN0
#define CURRENT_SENSOR_0_ANCH   0b0000
#define CURRENT_SENSOR_1_TRIS   TRISAbits.TRISA1
#define CURRENT_SENSOR_1_AN     AN1
#define CURRENT_SENSOR_1_ANCH   0b0001
#define CURRENT_SENSOR_2_TRIS   TRISEbits.TRISE0
#define CURRENT_SENSOR_2_AN     AN5
#define CURRENT_SENSOR_2_ANCH   0b0101
#define CURRENT_SENSOR_3_TRIS   TRISEbits.TRISE1
#define CURRENT_SENSOR_3_AN     AN6
#define CURRENT_SENSOR_3_ANCH   0b0110
/******************************************/

/* OTHER ANALOG SENSORS *******************/
#define RAIN_SENSOR_TRIS    TRISEbits.TRISE2
#define RAIN_SENSOR_AN      AN7
#define RAIN_SENSOR_ANCH    0b0111
#define LIGHT_SENSOR_TRIS   TRISAbits.TRISA5
#define LIGHT_SENSOR_AN     AN4
#define LIGHT_SENSOR_ANCH   0b0100
/******************************************/

/* OTHER INPUTS ***************************/
#define TILT_SENSOR_TRIS    TRISCbits.TRISC2
#define TILT_SENSOR_PORT    PORTCbits.RC2
/******************************************/

void HwInterface_Init(void);

/*
0000 = Channel 00 (AN0)
0001 = Channel 01 (AN1)
0010 = Channel 02 (AN2)
0011 = Channel 03 (AN3)
0100 = Channel 04 (AN4)
0101 = Channel 05 (AN5)(1)
0110 = Channel 06 (AN6)(1)
0111 = Channel 07 (AN7)(1)
1000 = Channel 08 (AN8)
1001 = Channel 09 (AN9)
1010 = Channel 10 (AN10)
1011 = Channel 11 (AN11)
1100 = Channel 12 (AN12)*/

#endif	/* HWINTERFACE_H */

