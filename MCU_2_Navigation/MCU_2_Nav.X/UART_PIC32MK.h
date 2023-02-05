/* 
 * File:   UART_PIC32MK.h
 * Author: skorra
 * Rev: 220630
 *
 * Created on June 8, 2022, 7:53 AM
 */

#ifndef _UART_PIC32MK_H    /* Guard against multiple inclusion */
#define _UART_PIC32MK_H

#include "UART_Common.h"
#include "DMA_PIC32MK.h"

/* Interrupt IDs */
#define UART1_RX_IRQ_ID    39
#define UART1_TX_IRQ_ID    40
#define UART2_RX_IRQ_ID    57
#define UART2_TX_IRQ_ID    58
#define UART3_RX_IRQ_ID    63
#define UART3_TX_IRQ_ID    64
#define UART4_RX_IRQ_ID    66
#define UART4_TX_IRQ_ID    67
#define UART5_RX_IRQ_ID    69
#define UART5_TX_IRQ_ID    70
#define UART6_RX_IRQ_ID    165
#define UART6_TX_IRQ_ID    166

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* Function prototypes */
    /* Constructors-factories */
    UART * UART_Create
    (UART * uartObj, UartModule iModule, uint32_t perFreq, uint32_t baudrate, _Bool rxInt);
    
    void UART_Initialize(UART * uartObj);
    void UART_AssignRegistersByModule(UART * uartObj);
    
    void UART_Deactivate(UART * uartObj);
    
    void UART_SendByte(UART * uartObj, uint8_t data); // sends individual char
    void UART_SendData(UART * uartObj, uint8_t* data, uint16_t len);  // sends string of chars
    void UART_SendBreak(UART * uartObj);      // prepares bus for incoming message
    void UART_InitInterrupts(UART * uartObj, _Bool rxInt, _Bool txInt); // 
    void UART_SetTXInterrupt(UART * uartObj, uint8_t value);
    void UART_DisableInterrupts(UART * uartObj);  // 
    
        /* Interrupt handlers */
    static void UART_InterruptHandler(UartModule module, UartInterruptType iType);
    void UART_RX_InterruptHandler(UART * uartObj);
    void UART_TX_InterruptHandler(UART * uartObj);
    void UART_MISC_InterruptHandler(UART * uartObj);
    /***************************************/
    
    /* Interrupt handler utility functions */
    void UART_ClearInterruptFlags(UART * uartObj, UartIrqFlagToClear ftc);     // clears interrupt flags
    

    /**************************************************************************/
    /* End of C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _UART_PIC32MK_H */

/*
uint8_t dest[10];
UART uart;
UART_Create(&uart, UART_MODULE_1, 120000000UL, 9600, 1,1);
DMA dma;
DMA_Create(&dma, DMA_CHANNEL_0, uart.registers.UxRXREG, dest, 1, 10, 1, 39, 1);
*/