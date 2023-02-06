/* 
 * File:   UART_PIC32MK.c
 * Author: skorra
 * Rev: 230130
 * 
 * Created on June 29, 2022, 7:53 AM
 */

#include "UART_PIC32MK.h"

UART * UartActiveModules[UART_NUMBER_OF_MODULES]; // reference to active UART module configurations

UART * UART_Create
    (UART * uartObj, UartModule iModule, uint32_t perFreq, uint32_t baudrate, _Bool rxInt)
{
    uartObj->rxInterrupt = rxInt;
    uartObj->initialized = 0;
    uartObj->DataReceived = 0;
    uartObj->DataSent = 0;
    uartObj->module = iModule;
    uartObj->rxDisable = 0;
    uartObj->txDisable = 0;
    uartObj->baudrate = ( (perFreq / (16*baudrate))-1);
    uartObj->enablePin = 0;
    return uartObj;
}

void UART_Initialize(UART * uartObj)
{
    if (!uartObj->initialized)
    {
        UART_AssignRegistersByModule(uartObj);
        uartObj->registers.UxMODEbits->ON = 0; // disable UART
        uartObj->registers.UxMODEbits->CLKSEL = 0b11; // REFCLK1
        uartObj->registers.UxBRGbits->BRG = uartObj->baudrate; // set baudrate
        uartObj->registers.UxSTAbits->URXEN = !uartObj->rxDisable; // RX enable
        uartObj->registers.UxSTAbits->UTXEN = !uartObj->txDisable; // TX enable
        UART_InitInterrupts(uartObj, uartObj->rxInterrupt, uartObj->txInterrupt); // enable interrupts
        uartObj->registers.UxMODEbits->ON = 1; // enable UART
        uartObj->initialized = 1;
    }
}
// This function shall be used only during initialization!
void UART_AssignRegistersByModule(UART * uartObj)
{
    switch (uartObj->module)
    {
        case UART_MODULE_1:
        {
            UartActiveModules[0] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U1STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U1MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U1BRGbits;
            uartObj->registers.UxRXREG =        &U1RXREG;
            uartObj->registers.UxTXREG =        &U1TXREG;
            break;
        }
        case UART_MODULE_2:
        {
            UartActiveModules[1] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U2STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U2MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U2BRGbits;
            uartObj->registers.UxRXREG =        &U2RXREG;
            uartObj->registers.UxTXREG =        &U2TXREG;
            break;
        }
        case UART_MODULE_3:
        {
            UartActiveModules[2] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U3STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U3MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U3BRGbits;
            uartObj->registers.UxRXREG =        &U3RXREG;
            uartObj->registers.UxTXREG =        &U3TXREG;
            break;
        }
        case UART_MODULE_4:
        {
            UartActiveModules[3] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U4STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U4MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U4BRGbits;
            uartObj->registers.UxRXREG =        &U4RXREG;
            uartObj->registers.UxTXREG =        &U4TXREG;
            break;
        }
        case UART_MODULE_5:
        {
            UartActiveModules[4] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U5STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U5MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U5BRGbits;
            uartObj->registers.UxRXREG =        &U5RXREG;
            uartObj->registers.UxTXREG =        &U5TXREG;
            break;
        }
        case UART_MODULE_6:
        {
            UartActiveModules[5] = uartObj;
            uartObj->registers.UxSTAbits =      (UxSTAbits_t*)&U6STAbits;
            uartObj->registers.UxMODEbits =     (UxMODEbits_t*)&U6MODEbits;
            uartObj->registers.UxBRGbits =      (UxBRGbits_t*)&U6BRGbits;
            uartObj->registers.UxRXREG =        &U6RXREG;
            uartObj->registers.UxTXREG =        &U6TXREG;
            break;
        }
        default: break;
    }
}
/************************/

void UART_InitInterrupts(UART * uartObj,_Bool rxInt, _Bool txInt)
{
    switch (uartObj->module)
    {
        case UART_MODULE_1:
        {
            IFS1bits.U1EIF = 0; // reset flag
            IFS1bits.U1RXIF = 0; // reset RX flag
            IFS1bits.U1TXIF = 0; // reset TX flag
            IPC10bits.U1TXIP = 7; // TX interrupt priority 7
            IPC10bits.U1TXIS = 1; // TX interrupt sub-priority 3
            IPC9bits.U1RXIP = 6; // RX interrupt priority 6
            IPC9bits.U1RXIS = 1; // RX interrupt sub-priority 3
            IEC1bits.U1RXIE = rxInt; // RX interrupt
            IEC1bits.U1TXIE = txInt; // TX interrupt   
            break;
        }
        case UART_MODULE_2:
        {
            IFS1bits.U2EIF = 0; // reset flag
            IFS1bits.U2RXIF = 0; // reset RX flag
            IFS1bits.U2TXIF = 0; // reset TX flag
            IPC14bits.U2TXIP = 7; // TX interrupt priority 7
            IPC14bits.U2TXIS = 2; // TX interrupt sub-priority 3
            IPC14bits.U2RXIP = 6; // TX interrupt priority 6
            IPC14bits.U2RXIS = 2; // TX interrupt sub-priority 3
            IEC1bits.U2RXIE = rxInt; // RX interrupt
            IEC1bits.U2TXIE = txInt; // TX interrupt
            break;
        }
        case UART_MODULE_3:
        {
            IFS1bits.U3EIF = 0; // reset flag
            IFS1bits.U3RXIF = 0; // reset RX flag
            IFS2bits.U3TXIF = 0; // reset TX flag
            IPC16bits.U3TXIP = 7; // TX interrupt priority 7
            IPC16bits.U3TXIS = 3; // TX interrupt sub-priority 3
            IPC15bits.U3RXIP = 6; // TX interrupt priority 6
            IPC15bits.U3RXIS = 3; // TX interrupt sub-priority 3
            IEC1bits.U3RXIE = rxInt; // RX interrupt
            IEC2bits.U3TXIE = txInt; // TX interrupt
            break;
        }
        case UART_MODULE_4:
        {
            IFS2bits.U4EIF = 0; // reset flag
            IFS2bits.U4RXIF = 0; // reset RX flag
            IFS2bits.U4TXIF = 0; // reset TX flag
            IPC16bits.U4TXIP = 6; // TX interrupt priority 7
            IPC16bits.U4TXIS = 1; // TX interrupt sub-priority 3
            IPC16bits.U4RXIP = 7; // TX interrupt priority 6
            IPC16bits.U4RXIS = 1; // TX interrupt sub-priority 3
            IEC2bits.U4RXIE = rxInt; // RX interrupt
            IEC2bits.U4TXIE = txInt; // TX interrupt
            break;
        }
        case UART_MODULE_5:
        {
            IFS2bits.U5EIF = 0; // reset flag
            IFS2bits.U5RXIF = 0; // reset RX flag
            IFS2bits.U5TXIF = 0; // reset TX flag
            IPC17bits.U5TXIP = 6; // TX interrupt priority 7
            IPC17bits.U5TXIS = 2; // TX interrupt sub-priority 3
            IPC17bits.U5RXIP = 7; // TX interrupt priority 6
            IPC17bits.U5RXIS = 2; // TX interrupt sub-priority 3
            IEC2bits.U5RXIE = rxInt; // RX interrupt
            IEC2bits.U5TXIE = txInt; // TX interrupt
            break;
        }
        case UART_MODULE_6:
        {
            IFS5bits.U6EIF = 0; // reset flag
            IFS5bits.U6RXIF = 0; // reset RX flag
            IFS5bits.U6TXIF = 0; // reset TX flag
            IPC41bits.U6TXIP = 6; // TX interrupt priority 7
            IPC41bits.U6TXIS = 3; // TX interrupt sub-priority 3
            IPC41bits.U6RXIP = 7; // TX interrupt priority 6
            IPC41bits.U6RXIS = 3; // TX interrupt sub-priority 3
            IEC5bits.U6RXIE = rxInt; // RX interrupt
            IEC5bits.U6TXIE = txInt; // TX interrupt
            break;
        }
        default: break;
    }
}
void UART_SetTXInterrupt(UART * uartObj, uint8_t value)
{
    switch (uartObj->module)
    {
        case UART_MODULE_1:
        {
            IEC1bits.U1TXIE = value; // TX interrupt 
            break;
        }
        case UART_MODULE_2:
        {
            IEC1bits.U2TXIE = value; // TX interrupt
            break;
        }
        case UART_MODULE_3:
        {
            IEC2bits.U3TXIE = value; // TX interrupt
            break;
        }
        case UART_MODULE_4:
        {
            IEC2bits.U4TXIE = value; // TX interrupt
            break;
        }
        case UART_MODULE_5:
        {
            IEC2bits.U5TXIE = value; // TX interrupt
            break;
        }
        case UART_MODULE_6:
        {
            IEC5bits.U6TXIE = value; // TX interrupt
            break;
        }
        default: break;
    }
}
void UART_DisableInterrupts(UART * uartObj)
{
    switch (uartObj->module)
    {
        case UART_MODULE_1:
        {
            IEC1bits.U1RXIE = 0; // RX interrupt
            IEC1bits.U1TXIE = 0; // TX interrupt 
            break;
        }
        case UART_MODULE_2:
        {
            IEC1bits.U2RXIE = 0; // RX interrupt
            IEC1bits.U2TXIE = 0; // TX interrupt
            break;
        }
        case UART_MODULE_3:
        {
            IEC1bits.U3RXIE = 0; // RX interrupt
            IEC2bits.U3TXIE = 0; // TX interrupt
            break;
        }
        case UART_MODULE_4:
        {
            IEC2bits.U4RXIE = 0; // RX interrupt
            IEC2bits.U4TXIE = 0; // TX interrupt
            break;
        }
        case UART_MODULE_5:
        {
            IEC2bits.U5RXIE = 0; // RX interrupt
            IEC2bits.U5TXIE = 0; // TX interrupt
            break;
        }
        case UART_MODULE_6:
        {
            IEC5bits.U6RXIE = 0; // RX interrupt
            IEC5bits.U6TXIE = 0; // TX interrupt
            break;
        }
        default: break;
    }
}

void UART_Deactivate(UART * uartObj)
{
    uartObj->registers.UxMODEbits->ON = 0; // disable UART
    UART_DisableInterrupts(uartObj); // disable interrupts
    uartObj->initialized = 0;
}
void UART_SendByte(UART * uartObj, uint8_t data)
{
    while(!uartObj->registers.UxSTAbits->TRMT);  // wait for empty TX register
     // fill TX register with data
    *uartObj->registers.UxTXREG = data;
}
void UART_SendData(UART * uartObj, uint8_t* data, uint16_t len)
{
    for(uint16_t i = 0; i<len;i++)
        UART_SendByte(uartObj, data[i]);
}
void UART_SendBreak(UART * uartObj)
{
    uartObj->registers.UxSTAbits->UTXBRK = 1;
    asm("nop");
}

/* Interrupt handlers */
void __attribute__((interrupt(ipl7auto), at_vector(_UART1_RX_VECTOR), aligned(16))) UART1_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_1, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART1_TX_VECTOR), aligned(16))) UART1_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_1, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART1_FAULT_VECTOR), aligned(16))) UART1_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_1, UART_VECTOR_FAULT);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART2_RX_VECTOR), aligned(16))) UART2_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_2, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART2_TX_VECTOR), aligned(16))) UART2_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_2, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART2_FAULT_VECTOR), aligned(16))) UART2_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_2, UART_VECTOR_FAULT);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART3_RX_VECTOR), aligned(16))) UART3_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_3, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART3_TX_VECTOR), aligned(16))) UART3_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_3, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl7auto), at_vector(_UART3_FAULT_VECTOR), aligned(16))) UART3_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_3, UART_VECTOR_FAULT);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART4_RX_VECTOR), aligned(16))) UART4_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_4, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART4_TX_VECTOR), aligned(16))) UART4_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_4, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART4_FAULT_VECTOR), aligned(16))) UART4_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_4, UART_VECTOR_FAULT);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART5_RX_VECTOR), aligned(16))) UART5_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_5, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART5_TX_VECTOR), aligned(16))) UART5_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_5, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART5_FAULT_VECTOR), aligned(16))) UART5_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_5, UART_VECTOR_FAULT);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART6_RX_VECTOR), aligned(16))) UART6_RX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_6, UART_VECTOR_RX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART6_TX_VECTOR), aligned(16))) UART6_TX_Handler (void)
{   UART_InterruptHandler(UART_MODULE_6, UART_VECTOR_TX);   }
void __attribute__((interrupt(ipl6auto), at_vector(_UART6_FAULT_VECTOR), aligned(16))) UART6_Fault_Handler (void)
{   UART_InterruptHandler(UART_MODULE_6, UART_VECTOR_FAULT);   }
/*********************************/

/* Interrupt handlers */
static void UART_InterruptHandler(UartModule module, UartInterruptType iType)
{
    UART * uartObj = UartActiveModules[module];
    switch (iType)
    {
        case UART_VECTOR_RX:
            UART_RX_InterruptHandler(uartObj);
            break;
        case UART_VECTOR_TX:
            UART_TX_InterruptHandler(uartObj);
            break;
        case UART_VECTOR_FAULT:
            UART_MISC_InterruptHandler(uartObj);
            break;
        default: break;
    }
}
void UART_RX_InterruptHandler(UART * uartObj)
{
    if (uartObj->DataReceived != 0)
    {
        uartObj->DataReceived(*(uartObj->registers.UxRXREG), uartObj->module);
    }
    UART_ClearInterruptFlags(uartObj, UART_RX_FLAG);
}
void UART_TX_InterruptHandler(UART * uartObj)
{
    UART_ClearInterruptFlags(uartObj, UART_TX_FLAG);
}
void UART_MISC_InterruptHandler(UART * uartObj)
{
    UART_ClearInterruptFlags(uartObj, UART_FAULT_FLAG);
}
/***************************************/

/* Interrupt handler utility functions */
void UART_ClearInterruptFlags(UART * uartObj, UartIrqFlagToClear ftc)
{
    uint8_t recv;
    if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)   
        recv = *uartObj->registers.UxRXREG;
    switch (uartObj->module)
    {
        case UART_MODULE_1:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    
                IFS1bits.U1EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       
                IFS1bits.U1RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)    
                IFS1bits.U1TXIF = 0; // reset TX flag
            break;
        }
        case UART_MODULE_2:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    IFS1bits.U2EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       IFS1bits.U2RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)       IFS1bits.U2TXIF = 0; // reset TX flag
            break;
        }
        case UART_MODULE_3:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    IFS1bits.U3EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       IFS1bits.U3RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)       IFS2bits.U3TXIF = 0; // reset TX flag
            break;
        }
        case UART_MODULE_4:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    IFS2bits.U4EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       IFS2bits.U4RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)       IFS2bits.U4TXIF = 0; // reset TX flag
            break;
        }
        case UART_MODULE_5:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    IFS2bits.U5EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       IFS2bits.U5RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)       IFS2bits.U5TXIF = 0; // reset TX flag
            break;
        }
        case UART_MODULE_6:
        {
            if (ftc == UART_FAULT_FLAG || ftc == UART_ALL_FLAGS)    IFS5bits.U6EIF = 0; // reset flag
            if (ftc == UART_RX_FLAG || ftc == UART_ALL_FLAGS)       IFS5bits.U6RXIF = 0; // reset RX flag
            if (ftc == UART_TX_FLAG || ftc == UART_ALL_FLAGS)       IFS5bits.U6TXIF = 0; // reset TX flag
            break;
        }
        default: break;
    }
}
