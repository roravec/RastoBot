#include "RastoBot_MCU2.h"

UART uartMCU0;  // U3; RX TX
UART uartMCU1;  // U5; RX TX
UART uartMCU3;  // U1; RX TX
UART uartGPS;   // U6; RX only
UART uartLIDAR; // U2; RX only; DMA

MCU_0_Sensors   sensorsStatus;
MCU_1_Motors    motorsStatus;

DMA dmaMcu0mcu3;

uint8_t mcu0dataIN[ECP_MIN_PACKET_LEN];
uint8_t mcu1dataIN[ECP_MIN_PACKET_LEN];
uint8_t mcu3dataIN[ECP_MIN_PACKET_LEN];

static uint8_t uartMCU0recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU0ecpRecvBuffer;
static uint8_t uartMCU1recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU1ecpRecvBuffer;
static uint8_t uartMCU3recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU3ecpRecvBuffer;

void MCU2_Init(void)
{
    ECP_BufferInit(&uartMCU0ecpRecvBuffer, uartMCU0recvBufferArr, ECP_MAX_PACKET_LEN);
    ECP_BufferInit(&uartMCU1ecpRecvBuffer, uartMCU1recvBufferArr, ECP_MAX_PACKET_LEN);
    ECP_BufferInit(&uartMCU3ecpRecvBuffer, uartMCU3recvBufferArr, ECP_MAX_PACKET_LEN);
    
    UART_Create(&uartMCU0, UART_MODULE_3, UART_CLOCK, UART_MCU0_BAUDRATE, 1);
    UART_Create(&uartMCU1, UART_MODULE_5, UART_CLOCK, UART_MCU1_BAUDRATE, 1);
    UART_Create(&uartMCU3, UART_MODULE_1, UART_CLOCK, UART_MCU3_BAUDRATE, 1);
    UART_Create(&uartGPS, UART_MODULE_6, UART_CLOCK, UART_MCU3_BAUDRATE, 1);
    UART_Create(&uartLIDAR, UART_MODULE_2, UART_CLOCK, UART_LIDAR_BAUDRATE, 1);
    
    uartMCU0.DataReceived = &MCU2_UARTMCU0_ReceiveData;
    uartMCU1.DataReceived = &MCU2_UARTMCU1_ReceiveData;
    uartMCU3.DataReceived = &MCU2_UARTMCU3_ReceiveData;
    
    UART_Initialize(&uartMCU0);
    //UART_Initialize(&uartMCU1);
    UART_Initialize(&uartMCU3);
//    UART_Initialize(&uartGPS);
//    UART_Initialize(&uartLIDAR);
    
    DMA_Create(&dmaMcu0mcu3, DMA_CHANNEL_0, 
            (uint32_t*)uartMCU0.registers.UxRXREG, 
            (uint32_t*)uartMCU3.registers.UxTXREG, 
            //mcu0dataIN,
            1, 
            1,
            //ECP_MIN_PACKET_LEN, 
            1, UART3_RX_IRQ_ID, 1);
    DMA_Initialize(&dmaMcu0mcu3);
}

void MCU2_Loop(void)
{
    int a = 0;
    //UART_SendByte(&uartMCU3, 0x55);
}

void MCU2_UARTMCU0_ReceiveData(uint8_t data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_ReceivedByteCust(data, &uartMCU0ecpRecvBuffer) == ECP_VALID)
    {
        DMA_TurnOnListeningForInterrupt(&dmaMcu0mcu3);
    }
}
void MCU2_UARTMCU1_ReceiveData(uint8_t data)
{
    
}
void MCU2_UARTMCU3_ReceiveData(uint8_t data)
{
    
}

// DMA interrupt handler
void MCU2_UARTMCU0_ReceivedDataBlock(uint32_t * data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_ReceivedByteCust(data, &uartMCU0ecpRecvBuffer) == ECP_VALID)
    {
        DMA_TurnOnListeningForInterrupt(&dmaMcu0mcu3);
    }
}