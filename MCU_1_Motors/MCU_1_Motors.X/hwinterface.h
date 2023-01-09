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
#define UART_RX_TRIS        TRISBbits.TRISB15
#define UART_TX_TRIS        TRISBbits.TRISB14
/******************************************/ 

/* MAIN MOTOR *****************************/
#define MAIN_MOTOR_TRIS     TRISBbits.TRISB9
#define MAIN_MOTOR_LAT      LATBbits.LATB9
/******************************************/

/* STEPPER DRIVER 0 ***********************/
#define STEPDRV_0_DIR_TRIS      TRISAbits.TRISA0
#define STEPDRV_0_DIR_LAT       LATAbits.LATA0
#define STEPDRV_0_STEP_TRIS     TRISAbits.TRISA1
#define STEPDRV_0_STEP_LAT      LATAbits.LATA1
#define STEPDRV_0_ENABLE_TRIS   TRISBbits.TRISB2
#define STEPDRV_0_ENABLE_LAT    LATBbits.LATB2
#define STEPDRV_0_MS1_TRIS      TRISBbits.TRISB3
#define STEPDRV_0_MS1_LAT       LATBbits.LATB3
#define STEPDRV_0_MS2_TRIS      TRISAbits.TRISA2
#define STEPDRV_0_MS2_LAT       LATAbits.LATA2
/******************************************/

/* STEPPER DRIVER 1 ***********************/
#define STEPDRV_1_DIR_TRIS      TRISAbits.TRISA3
#define STEPDRV_1_DIR_LAT       LATAbits.LATA3
#define STEPDRV_1_STEP_TRIS     TRISBbits.TRISB4
#define STEPDRV_1_STEP_LAT      LATBbits.LATB4
#define STEPDRV_1_ENABLE_TRIS   TRISAbits.TRISA4
#define STEPDRV_1_ENABLE_LAT    LATAbits.LATA4
#define STEPDRV_1_MS1_TRIS      TRISBbits.TRISB5
#define STEPDRV_1_MS1_LAT       LATBbits.LATB5
#define STEPDRV_1_MS2_TRIS      TRISBbits.TRISB6
#define STEPDRV_1_MS2_LAT       LATBbits.LATB6
/******************************************/

/* STEPPER DRIVER 2 ***********************/
#define STEPDRV_2_DIR_TRIS      TRISBbits.TRISB7
#define STEPDRV_2_DIR_LAT       LATBbits.LATB7
#define STEPDRV_2_STEP_TRIS     TRISBbits.TRISB8
#define STEPDRV_2_STEP_LAT      LATBbits.LATB8
#define STEPDRV_2_ENABLE_TRIS   TRISCbits.TRISC9
#define STEPDRV_2_ENABLE_LAT    LATCbits.LATC9
#define STEPDRV_2_MS1_TRIS      TRISBbits.TRISB10
#define STEPDRV_2_MS1_LAT       LATBbits.LATB10
#define STEPDRV_2_MS2_TRIS      TRISBbits.TRISB11
#define STEPDRV_2_MS2_LAT       LATBbits.LATB11
/******************************************/

/* LIMIT SWITCHES *************************/
#define LIMIT_SWITCH_BOTTOM_TRIS    TRISBbits.TRISB12
#define LIMIT_SWITCH_BOTTOM_PORT    PORTBbits.RB12
#define LIMIT_SWITCH_UP_TRIS        TRISBbits.TRISB13
#define LIMIT_SWITCH_UP_PORT        PORTBbits.RB13
/******************************************/

void HwInterface_Init(void);

#endif	/* HWINTERFACE_H */

