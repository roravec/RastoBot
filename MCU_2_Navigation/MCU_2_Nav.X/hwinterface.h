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
#define UART_MCU1_RX_TRIS   TRISAbits.TRISA7  // UART3
#define UART_MCU1_TX_TRIS   TRISBbits.TRISB14 // UART3
#define UART_MCU3_RX_TRIS   TRISAbits.TRISA11 // UART2
#define UART_MCU3_TX_TRIS   TRISAbits.TRISA4  // UART2
#define UART_MCU0_RX_TRIS   TRISCbits.TRISC15 // UART
#define UART_MCU0_TX_TRIS   TRISBbits.TRISB7  // UART
#define UART_GPS_RX_TRIS    TRISCbits.TRISC1
#define UART_GPS_TX_TRIS    TRISCbits.TRISC0
#define UART_LIDAR_RX_TRIS  TRISBbits.TRISB10  
#define UART_LIDAR_TX_TRIS  TRISBbits.TRISB5
/******************************************/ 

/* I2C ************************************/
#define I2C_SDA_TRIS        TRISEbits.TRISE12
#define I2C_SCL_TRIS        TRISEbits.TRISE13
/******************************************/ 

/* LEDS ***********************************/
#define LED_0_TRIS          TRISCbits.TRISC7
#define LED_0_LAT           LATCbits.LATC7
#define LED_1_TRIS          TRISCbits.TRISC8
#define LED_1_LAT           LATCbits.LATC8
#define LED_2_TRIS          TRISDbits.TRISD5
#define LED_2_LAT           LATDbits.LATD5
#define LED_3_TRIS          TRISDbits.TRISD6
#define LED_3_LAT           LATDbits.LATD6
/******************************************/ 

/* Sensors ********************************/
#define INDUCTION_SENSE_TRIS TRISGbits.TRISG6
#define INDUCTION_SENSE_AN   ANSELGbits.ANSG6
/******************************************/

/* Outputs ********************************/
#define LIDAR_ENABLE_TRIS   TRISDbits.TRISD8
#define LIDAR_ENABLE_LAT    LATDbits.LATD8
/******************************************/ 

void HwInterface_Init(void);

#endif	/* HWINTERFACE_H */

