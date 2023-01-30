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
//#include <string.h>

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* Function prototypes */
    /* Constructors-factories */
    UART * UART_Create
    (UART * uartObj, UartModule iModule, uint32_t perFreq, uint32_t baudrate, _Bool rxInt, _Bool txInt);
    
    void UART_Initialize(UART * uartObj);
    void UART_AssignRegistersByModule(UART * uartObj);
    
    void UART_Deactivate(UART * uartObj);
    
    void UART_SendByte(UART * uartObj, uint8_t data); // sends individual char
    void UART_SendData(UART * uartObj, unsigned char* data, uint16_t len);  // sends string of chars
    void UART_SendBreak(UART * uartObj);      // prepares bus for incoming message
    void UART_InitInterrupts(UART * uartObj, _Bool rxInt, _Bool txInt); // 
    void UART_DisableInterrupts(UART * uartObj);  // 
    
        /* Interrupt handlers */
    static void UART_InterruptHandler(UartModule module, UartInterruptType iType);
    void UART_RX_InterruptHandler(UART * uartObj);
    void UART_TX_InterruptHandler(UART * uartObj);
    void UART_MISC_InterruptHandler(UART * uartObj);
    /***************************************/
    
    /* Interrupt handler utility functions */
    void UART_ClearInterruptFlags(UART * uartObj);     // clears all interrupt flags
    

    /**************************************************************************/
    /* End of C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _UART_PIC32MK_H */