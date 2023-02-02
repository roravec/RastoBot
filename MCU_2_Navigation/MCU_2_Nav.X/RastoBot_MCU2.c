#include "RastoBot_MCU2.h"

UART uartMCU0;  // U3; RX TX
UART uartMCU1;  // U5; RX TX
UART uartMCU3;  // U1; RX TX
UART uartGPS;   // U6; RX only
UART uartLIDAR; // U2; RX only; DMA

DMA dmaMcu0mcu3;

void MCU2_Init(void)
{
    UART_Create(&uartMCU0, UART_MODULE_3, UART_CLOCK, UART_MCU0_BAUDRATE, 1);
    UART_Create(&uartMCU3, UART_MODULE_1, UART_CLOCK, UART_MCU3_BAUDRATE, 1);
    UART_Initialize(&uartMCU0);
    UART_Initialize(&uartMCU3);
    
    DMA_Create(&dmaMcu0mcu3, DMA_CHANNEL_0, 
            //uartMCU0.registers.UxRXREG, 
            //uartMCU3.registers.UxTXREG, 
            &U3RXREG, &U1TXREG,
            1, 1, 1, UART3_RX_IRQ_ID, 0);
    DMA_Initialize(&dmaMcu0mcu3);
}

void MCU2_Loop(void)
{
    int a = 0;
    //UART_SendByte(&uartMCU3, 0x55);
}