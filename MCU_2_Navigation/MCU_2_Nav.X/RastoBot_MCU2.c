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

DMA dmaMcu0mcu3;

uint8_t mcu0dataIN[ECP_MAX_PACKET_LEN];
uint8_t mcu1dataIN[ECP_MAX_PACKET_LEN];
uint8_t mcu3dataIN[ECP_MAX_PACKET_LEN];

static uint8_t uartMCU0recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU0ecpRecvBuffer;
static uint8_t uartMCU1recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU1ecpRecvBuffer;
static uint8_t uartMCU3recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer uartMCU3ecpRecvBuffer;

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
            //(uint32_t*)uartMCU3.registers.UxTXREG, 
            (uint32_t*)mcu0dataIN,
            1, 
            //1,
            ECP_MAX_PACKET_LEN, 
            1, UART3_RX_IRQ_ID, 1);
    dmaMcu0mcu3.InterruptTriggerFnc = &MCU2_UARTMCU0_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu0mcu3);
    //dmaMcu0mcu3.registers.DCHxINTbits->CHBCIE = 1; // block complete interrupt
    dmaMcu0mcu3.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
}

void MCU2_Loop(void)
{
    loopCounter++;
    MCU2_DoTasks();
    //UART_SendByte(&uartMCU3, 0x55);
}

void MCU2_UARTMCU0_ReceiveData(uint8_t data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_ReceivedByteCust(data, &uartMCU0ecpRecvBuffer) == ECP_VALID)
    {
        UART_DisableInterrupts(&uartMCU0);
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
void MCU2_UARTMCU0_ReceivedDataBlock(uint8_t * data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_CheckPacketValidity(data, ECP_MAX_PACKET_LEN) == ECP_VALID)
    {
        for (uint8_t i=0; i<ECP_MAX_PACKET_LEN ; i++)
        {
            if (ECP_ReceivedByteCust(data[i], &uartMCU0ecpRecvBuffer) == ECP_VALID)
                break;
        }
    }
    else
    {
        DMA_TurnOffListeningForInterrupt(&dmaMcu0mcu3);
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
    ECP_Encode(msg, &uartMCU3_OUT);
    UART_SendData(&uartMCU3,uartMCU3_OUT.data, uartMCU3_OUT.size);
    
    if (msg->command == ECP_COMMAND_MOTORS_SET)
    {
        switch (msg->subCommand)
        {
            default: break;
        }
    }
}