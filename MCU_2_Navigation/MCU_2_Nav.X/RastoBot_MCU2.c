#include "RastoBot_MCU2.h"

/* GLOBALS */
uint32_t loopCounter = 0;

UART uartMCU0;  // U3; RX TX
UART uartMCU1;  // U5; RX TX
UART uartMCU3;  // U1; RX TX
UART uartGPS;   // U6; RX only
UART uartLIDAR; // U2; RX only; DMA

MCU_0_Sensors   sensorsStatus;
MCU_1_Motors    motorsStatus;

DMA dmaMcu0IN;
DMA dmaMcu1IN;
DMA dmaMcu3IN;
DMA dmaMcu3OUT;

uint8_t mcu0dataIN[ECP_MAX_PACKET_LEN];
uint8_t mcu1dataIN[ECP_MAX_PACKET_LEN];
uint8_t mcu3dataIN[ECP_MAX_PACKET_LEN];

static uint8_t uartMCU0recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU0ecpRecvBuffer;
ECP_Message mcu0MsgOut;

static uint8_t uartMCU1recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU1ecpRecvBuffer;
ECP_Message mcu1MsgOut;

static uint8_t uartMCU3recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU3ecpRecvBuffer;
ECP_Message mcu3MsgOut;

uint8_t uartMCU0_OUTarr[ECP_MAX_PACKET_LEN];
static uint8_t uartMCU1_OUTarr[ECP_MAX_PACKET_LEN];
uint8_t uartMCU3_OUTarr[ECP_MAX_PACKET_LEN];
static Rarray uartMCU0_OUT;
static Rarray uartMCU1_OUT;
static Rarray uartMCU3_OUT;

/* STATIC FUNCTIONS */
static void MCU2_DoTasks(void);
static void MCU2_TaskLogData(void);
static void MCU2_TaskSendStatusData(void);
static void MCU2_TaskCheckForNewReceivedData(void);
static void MCU2_DoMessageAction(ECP_Message * msg);

void MCU2_Init(void)
{
    MCU2_InitUART();
    MCU2_InitDMA();
}


void MCU2_InitUART(void)
{
    ECP_BufferInit(&uartMCU0ecpRecvBuffer, uartMCU0recvBufferArr, ECP_MAX_PACKET_LEN);
    ECP_BufferInit(&uartMCU1ecpRecvBuffer, uartMCU1recvBufferArr, ECP_MAX_PACKET_LEN);
    ECP_BufferInit(&uartMCU3ecpRecvBuffer, uartMCU3recvBufferArr, ECP_MAX_PACKET_LEN);
    
    RarrayCreate(&uartMCU0_OUT, uartMCU0_OUTarr, ECP_MAX_PACKET_LEN);
    RarrayCreate(&uartMCU1_OUT, uartMCU1_OUTarr, ECP_MAX_PACKET_LEN);
    RarrayCreate(&uartMCU3_OUT, uartMCU3_OUTarr, ECP_MAX_PACKET_LEN);
    
    UART_Create(&uartMCU0, UART_MODULE_3, UART_CLOCK, UART_MCU0_BAUDRATE, 1);
    UART_Create(&uartMCU1, UART_MODULE_5, UART_CLOCK, UART_MCU1_BAUDRATE, 1);
    UART_Create(&uartMCU3, UART_MODULE_1, UART_CLOCK, UART_MCU3_BAUDRATE, 1);
    UART_Create(&uartGPS, UART_MODULE_6, UART_CLOCK, UART_MCU3_BAUDRATE, 1);
    UART_Create(&uartLIDAR, UART_MODULE_2, UART_CLOCK, UART_LIDAR_BAUDRATE, 1);
    
    uartMCU0.DataReceived = &MCU2_UART_ECP_ReceiveData;
    uartMCU1.DataReceived = &MCU2_UART_ECP_ReceiveData;
    uartMCU3.DataReceived = &MCU2_UART_ECP_ReceiveData;
    
    UART_Initialize(&uartMCU0);
    UART_Initialize(&uartMCU1);
    UART_Initialize(&uartMCU3);
//    UART_Initialize(&uartGPS);
//    UART_Initialize(&uartLIDAR);
}

void MCU2_InitDMA(void)
{
    /* DMA MCU0 IN *************************************/
    DMA_Create(&dmaMcu0IN, DMA_CHANNEL_0, 
            (uint32_t*)uartMCU0.registers.UxRXREG, 
            (uint32_t*)mcu0dataIN,
            1, 
            ECP_MAX_PACKET_LEN, 
            1, UART3_RX_IRQ_ID, 1);
    dmaMcu0IN.InterruptTriggerFnc = &MCU2_UART_ECP_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu0IN);
    dmaMcu0IN.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
    
    /* DMA MCU1 IN *************************************/
        DMA_Create(&dmaMcu1IN, DMA_CHANNEL_1, 
            (uint32_t*)uartMCU1.registers.UxRXREG, 
            (uint32_t*)mcu1dataIN,
            1, 
            ECP_MAX_PACKET_LEN, 
            1, UART5_RX_IRQ_ID, 1);
    dmaMcu1IN.InterruptTriggerFnc = &MCU2_UART_ECP_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu1IN);
    dmaMcu1IN.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
}

void MCU2_Loop(void)
{
    loopCounter++;
    MCU2_DoTasks();
    //UART_SendByte(&uartMCU3, 0x55);
}

void MCU2_UART_ECP_ReceiveData(uint8_t data, UartModule uartModule)
{
    UART * uart;
    DMA * dma;
    ECP_Buffer * ecpBuff;
    switch (uartModule)
    {
        case UART_MODULE_1: uart = &uartMCU3; dma = &dmaMcu3IN; ecpBuff = &uartMCU3ecpRecvBuffer; break;
        case UART_MODULE_3: uart = &uartMCU0; dma = &dmaMcu0IN; ecpBuff = &uartMCU0ecpRecvBuffer; break;
        case UART_MODULE_5: uart = &uartMCU1; dma = &dmaMcu1IN; ecpBuff = &uartMCU1ecpRecvBuffer; break;
        default: return;
    }
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_ReceivedByteCust(data, ecpBuff) == ECP_VALID)
    {
        UART_DisableInterrupts(uart);
        DMA_TurnOnListeningForInterrupt(dma);
    }
}

// DMA interrupt handler
void MCU2_UART_ECP_ReceivedDataBlock(uint8_t * data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_CheckPacketValidity(data, ECP_MAX_PACKET_LEN) == ECP_VALID)
    {
        ECP_ParseEnqueueRawDataBlock(data, ECP_MAX_PACKET_LEN);
    }
    else
    {
        DMA_TurnOffListeningForInterrupt(&dmaMcu0IN);
    }
}

/***********************************************************************/
/* TASKS - functions which are called only from loop to do basic tasks */
/* WARNING: Do not invoke this functions somewhere else */

static void MCU2_DoTasks(void)
{
    if (loopCounter % MCU2_LOG_DATA_TO_STRUCT_EVERY == 0)
        MCU2_TaskLogData();
    if (loopCounter % MCU2_CHECK_NEW_MESSAGES_EVERY == 0)
        MCU2_TaskCheckForNewReceivedData();
    if (loopCounter % MCU2_SEND_STATUS_DATA_EVERY == 0)
        MCU2_TaskSendStatusData();
}

static void MCU2_TaskLogData(void)
{
    
}

static void MCU2_TaskSendStatusData(void)
{
//    RastoBot_Encode_Motors_1(&sendMessage, &statusData);
//    ECP_Encode(&sendMessage, &sendPacket);
//    UART_WriteData(sendPacket.data, sendPacket.size);
//    RastoBot_Encode_Motors_2(&sendMessage, &statusData);
//    ECP_Encode(&sendMessage, &sendPacket);
//    UART_WriteData(sendPacket.data, sendPacket.size);
    
    RastoBot_Encode_Sensors_1(&mcu3MsgOut, &sensorsStatus);
    ECP_Encode(&mcu3MsgOut, &uartMCU3_OUT);
    UART_SendData(&uartMCU3,uartMCU3_OUT.data, uartMCU3_OUT.size);
}

static ECP_Message * msg;  // pointer to message to process
static void MCU2_TaskCheckForNewReceivedData(void)
{
    while ((msg = ECP_MessageDequeue()) != 0) // check if we have some message to process in queue
    {
        // a new message has been received and decoded. Let's process it...
        MCU2_DoMessageAction(msg);      // do requested action
        ECP_MarkMessageAsComplete(msg); // mark message as processed. It will free up space in queue.
    }
}

/* MESSAGE ACTION*/
static void MCU2_DoMessageAction(ECP_Message * msg)
{  
    if (msg->command == ECP_COMMAND_SENSORS_STATUS)
    {
        RastoBot_Decode_Sensors(&sensorsStatus, msg);
    }
    else if (msg->command == ECP_COMMAND_MOTORS_STATUS)
    {
        RastoBot_Decode_Motors(&motorsStatus, msg);
    }
}