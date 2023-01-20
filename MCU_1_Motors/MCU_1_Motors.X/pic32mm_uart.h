/* File:   UART.h
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

#ifndef _PIC32MMUART_H    /* Guard against multiple inclusion */
#define _PIC32MMUART_H

#include <xc.h>
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "config.h"
#include "../../SW/libs/rarray.h"

#define PER_FREQ                FCY        // CPU peripheral frequency
#define UARTBAUDRATE                19200//38400       // UART baudrate

extern Rarray uartBuffer;
extern _Bool uartNewDataFlag;

//-----------[ Functions' Prototypes ]--------------

void UART_Init(void);           // first time init
void UART_Deactivate();         // deactivates uart
void UART_Write(unsigned char); // writes individual char
void UART_Write_String(char*);  // writes string of chars
void UART_WriteData(char* buf, int len);    // writes string of chars
void UART_SendBreak(void);      // prepares bus for incoming message
void UART_InitInterrupts(void); // 
void UART_DisableInterrupts();  // 

#endif /* _UART_H */