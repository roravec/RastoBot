/* File:   pic18_uart.h
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: PIC32 UART communication library
 * 
 * How to use:
 * 0. Define right bits to use in Constants section
 * 1. Initialize with void UART_Init(void);
 * 2. Send message: Send break before sending a string of chars void UART_SendBreak(void);
 *      Then you can use one of these functions to send data to UART bus:
 *          void UART_Write(unsigned char);
 *          void UART_Write_String(char*);
 *          void UART_WriteData(char* buf, int len);
 * 2a. If you want to send another string of chars you have to call void UART_SendBreak(void); again
 * 3. When you are done you should deactivate UART with void UART_Deactivate();
 */ 

#ifndef PIC18_UART_H
#define	PIC18_UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "config.h"

#define PER_FREQ                FCY         // CPU peripheral frequency
#define UART_BAUDRATE           19200       // UART baudrate

// Constants for easier work with UART register bits
#define U1TX_TRIS    UART_TX_TRIS
#define U1RX_TRIS    UART_RX_TRIS

//-----------[ Functions' Prototypes ]--------------

void UART_Init(void);           // first time init
uint8_t UART_CalculateSPBRG(uint16_t desiredBaudrate);
void UART_Write(uint8_t); // writes individual char
void UART_Write_String(uint8_t*);  // writes string of chars
void UART_WriteData(uint8_t* buf, uint16_t len);    // writes string of chars
void UART_SendBreak(void);      // prepares bus for incoming message
void UART_InitInterrupts(void); // 
void UART_DisableInterrupts(void);  // 


#ifdef	__cplusplus
}
#endif

#endif	/* PIC18_UART_H */

