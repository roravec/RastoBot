#include "RastoBot_MCU2.h"

/* GLOBALS */
uint32_t loopCounter = 0;
const bool SEND_STATUS_DATA = 1;
const bool SEND_POSITION_DATA = 0;

I2C i2c;

UART uartMCU0;  // U3; RX TX
UART uartMCU1;  // U5; RX TX
UART uartMCU3;  // U1; RX TX
UART uartGPS;   // U6; RX only
UART uartLIDAR; // U2; RX only; DMA

MCU_0_Sensors   sensorsStatus;
MCU_1_Motors    motorsStatus;
MCU_2_GyroData  gyroData;
MCU_2_GPSData   gpsData;
MCU_2_LidarData lidarData;

DMA dmaMcu0IN;
DMA dmaMcu1IN;
DMA dmaMcu3IN;
DMA dmaMcu3OUT;
DMA dmaGPSIn;
DMA dmaLidarIn;

uint8_t mcu0dataIN[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2)];
uint8_t mcu1dataIN[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU1_TO_MCU2)];
uint8_t mcu3dataIN[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU3_TO_MCU2)];
uint8_t gpsDataIN[GPS_MAX_DATALOAD];
uint8_t lidarDataIN[LIDAR_FIX_DATALOAD];
uint8_t lidarDataINprocess[LIDAR_FIX_DATALOAD];
uint8_t lidarByte; // for debug purposes

static uint8_t uartMCU0recvBufferArr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2)];
ECP_Buffer uartMCU0ecpRecvBuffer;
ECP_Message mcu0MsgOut;

static uint8_t uartMCU1recvBufferArr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU1_TO_MCU2)];
ECP_Buffer uartMCU1ecpRecvBuffer;
ECP_Message mcu1MsgOut;

static uint8_t uartMCU3recvBufferArr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU3_TO_MCU2)];
ECP_Buffer uartMCU3ecpRecvBuffer;
ECP_Message mcu3MsgOut;

uint8_t uartMCU0_OUTarr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU0)];
static uint8_t uartMCU1_OUTarr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU1)];
uint8_t uartMCU3_OUTarr[ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU3)];
static Rarray uartMCU0_OUT;
static Rarray uartMCU1_OUT;
static Rarray uartMCU3_OUT;

/* STATIC FUNCTIONS */
static void MCU2_DoTasks(void);
static void MCU2_TaskReadGyro(void);
static void MCU2_TaskReadPerimeterWire(void);
static void MCU2_TaskLogData(void);
static void MCU2_TaskSendStatusData(void);
static void MCU2_TaskSendPositionData(void);
static void MCU2_TaskCheckForNewReceivedData(void);
static void MCU2_DoMessageAction(ECP_Message * msg);

void MCU2_Init(void)
{
    LIDAR_ENABLE_LAT = 1;
    
    ADC_Init();
    MCU2_InitGPS();
    MCU2_InitUART();
    MCU2_InitDMA();
    MCU2_InitI2C();
    MCU2_InitGyroMPU6050();
    MCU2_InitCompass();
    MCU2_InitPerimeterWire();
    MCU2_InitLidar();
}

void MCU2_InitUART(void)
{
    // setup buffers to receive ECP messages
    ECP_BufferInit(&uartMCU0ecpRecvBuffer, uartMCU0recvBufferArr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2));
    ECP_BufferInit(&uartMCU1ecpRecvBuffer, uartMCU1recvBufferArr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU1_TO_MCU2));
    ECP_BufferInit(&uartMCU3ecpRecvBuffer, uartMCU3recvBufferArr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU3_TO_MCU2));
    
    // setup buffer to send ECP messages
    RarrayCreate(&uartMCU0_OUT, uartMCU0_OUTarr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU0));
    RarrayCreate(&uartMCU1_OUT, uartMCU1_OUTarr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU1));
    RarrayCreate(&uartMCU3_OUT, uartMCU3_OUTarr, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU3));
    
    // create and setup UARTs
    UART_Create(&uartMCU0,  UART_MODULE_3, UART_CLOCK,      UART_MCU0_BAUDRATE, 1);
    UART_Create(&uartMCU1,  UART_MODULE_5, UART_CLOCK,      UART_MCU1_BAUDRATE, 1);
    UART_Create(&uartMCU3,  UART_MODULE_1, UART_1_2_CLOCK,  UART_MCU3_BAUDRATE, 1);
    UART_Create(&uartGPS,   UART_MODULE_6, UART_CLOCK,      UART_GPS_BAUDRATE, 1);
    UART_Create(&uartLIDAR, UART_MODULE_2, UART_1_2_CLOCK,  UART_LIDAR_BAUDRATE, 1);
    
    // setup function which that be called on data receive
    uartMCU0.DataReceived =     &MCU2_UART_ECP_ReceiveData;
    uartMCU1.DataReceived =     &MCU2_UART_ECP_ReceiveData;
    uartMCU3.DataReceived =     &MCU2_UART_ECP_ReceiveData;
    uartGPS.DataReceived =      &MCU2_UART_ReceiveGPSData;
    uartLIDAR.DataReceived =    &MCU2_UART_ReceiveLIDARData;
    uartLIDAR.FailureEvent =    &MCU2_UART_LIDARDataFailure;
    
    // initialize and start UARTS
    UART_Initialize(&uartMCU0);
    UART_Initialize(&uartMCU1);
    UART_Initialize(&uartMCU3);
    UART_Initialize(&uartGPS);
    UART_Initialize(&uartLIDAR); 
}

void MCU2_InitDMA(void)
{
    /* DMA MCU0 IN *************************************/
    DMA_Create(&dmaMcu0IN, DMA_CHANNEL_0, 
            (uint32_t*)uartMCU0.registers.UxRXREG, 
            (uint32_t*)mcu0dataIN,
            1, 
            ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2), 
            1, UART3_RX_IRQ_ID, 1);
    dmaMcu0IN.InterruptTriggerFnc = &MCU2_UART_ECP_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu0IN);
    dmaMcu0IN.registers.DCHxINTbits->CHDDIE = 1; // destination is full, interrupt
    
    /* DMA MCU1 IN *************************************/
    DMA_Create(&dmaMcu1IN, DMA_CHANNEL_1, 
            (uint32_t*)uartMCU1.registers.UxRXREG, 
            (uint32_t*)mcu1dataIN,
            1, 
            ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU1_TO_MCU2), 
            1, UART5_RX_IRQ_ID, 1);
    dmaMcu1IN.InterruptTriggerFnc = &MCU2_UART_ECP_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu1IN);
    dmaMcu1IN.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
    
    /* DMA MCU3 IN *************************************/
    DMA_Create(&dmaMcu3IN, DMA_CHANNEL_2, 
            (uint32_t*)uartMCU3.registers.UxRXREG, 
            (uint32_t*)mcu3dataIN,
            1, 
            ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU3_TO_MCU2), 
            1, UART1_RX_IRQ_ID, 1);
    dmaMcu3IN.InterruptTriggerFnc = &MCU2_UART_ECP_ReceivedDataBlock;
    DMA_Initialize(&dmaMcu3IN);
    dmaMcu3IN.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
    
    /* DMA MCU3 OUT *************************************/
    DMA_Create(&dmaMcu3OUT, DMA_CHANNEL_3, 
            (uint32_t*)uartMCU3_OUT.data,
            (uint32_t*)uartMCU3.registers.UxTXREG,
            ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU3), 
            1, 
//            ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU2_TO_MCU3), 
            1,
            UART1_TX_IRQ_ID, 1);
    dmaMcu3OUT.InterruptTriggerFnc = &MCU2_TransferToMCU3Complete;
    DMA_Initialize(&dmaMcu3OUT);
    dmaMcu3OUT.registers.DCHxCONbits->CHAEN = 0;   //  Channel Automatic is turned off
    dmaMcu3OUT.registers.DCHxINTbits->CHSDIE = 1; //  Channel Source Done Interrupt Enable bit
    
    /* DMA GPS IN *************************************/
    DMA_Create(&dmaGPSIn, DMA_CHANNEL_4, 
            (uint32_t*)uartGPS.registers.UxRXREG, 
            (uint32_t*)gpsDataIN,
            1, 
            GPS_MAX_DATALOAD, 
            1, UART6_RX_IRQ_ID, 1);
    dmaGPSIn.InterruptTriggerFnc = &MCU2_DMA_ReceivedGPSData;
    DMA_Initialize(&dmaGPSIn);
    dmaGPSIn.registers.DCHxDATbits->CHPDAT = '\r'; // end byte of string
    dmaGPSIn.registers.DCHxINTbits->CHBCIE = 1; // = A block transfer has been completed (the larger of CHSSIZ/CHDSIZ bytes has been transferred), or a pattern match event occurs 
    
    /* DMA LIDAR IN *************************************/
    DMA_Create(&dmaLidarIn, DMA_CHANNEL_5, 
            (uint32_t*)uartLIDAR.registers.UxRXREG, 
//            (uint32_t*)&lidarByte, 
            (uint32_t*)lidarDataIN,
            1, 
            LIDAR_FIX_DATALOAD, 
            1, UART2_RX_IRQ_ID, 1);
    dmaLidarIn.InterruptTriggerFnc = &MCU2_DMA_ReceivedLIDARData;
    DMA_Initialize(&dmaLidarIn);
    dmaLidarIn.registers.DCHxCONbits->CHAEN = 0;   //  Channel Automatic is turned off
    dmaLidarIn.registers.DCHxINTbits->CHDDIE = 1; // destination is full interrupt
}
void MCU2_InitI2C(void)
{
    I2C_Create(&i2c, I2C_MODULE_4, PBCLK3, 100000, 0);
    I2C_Init(&i2c,PBCLK3,100000);
}
void MCU2_InitGyroMPU6050(void)
{
    MPU6050_Init(&i2c);
}
void MCU2_InitCompass(void)
{
    //QMC5883L_Init(&i2c);
    HMC5883_Init(&i2c);
}
void MCU2_InitLidar(void)
{
    //MCU2_LidarDisable();
    Delay_ms(200);
    MCU2_LidarEnable();
}
void MCU2_InitGPS(void)
{
    GPS_Init();
}
void MCU2_InitPerimeterWire(void)
{
    
}

/* MAIN LOOP ******************************************************************/
void MCU2_Loop(void)
{
    loopCounter++;
    MCU2_DoTasks();
}
/******************************************************************************/
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
        //UART_DisableInterrupts(uart);
        DMA_TurnOnListeningForInterrupt(dma);
    }
}

// DMA interrupt handler
void MCU2_UART_ECP_ReceivedDataBlock(uint8_t * data)
{
    // interrupt receiving. Check for one packet and then start DMA transfer for faster receiving
    if (ECP_CheckPacketValidity(data, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2)) == ECP_VALID)
    {
        ECP_ParseEnqueueRawDataBlock(data, ECP_PACKET_LEN_KNOWN_DLC(ECP_DATA_SIZE_MCU0_TO_MCU2));
    }
    else
    {
        DMA_TurnOffListeningForInterrupt(&dmaMcu0IN);
    }
}

// UART interrupt
void MCU2_UART_ReceiveGPSData(uint8_t data, UartModule uartModule)
{
    UART * uart = &uartGPS;
    DMA * dma = &dmaGPSIn;
    if (data == '$') // start of string
    {
        //UART_DisableInterrupts(uart);
        DMA_TurnOnListeningForInterrupt(dma);
    }
}
// DMA interrupt
void MCU2_DMA_ReceivedGPSData(uint8_t * data)
{
    UART * uart = &uartGPS;
    DMA * dma = &dmaGPSIn;
    // parse data
    for (uint8_t i=0 ; i < GPS_MAX_DATALOAD ; i++)
    {
        GPS_Read(data[i]);
    }
}
// UART interrupt
void MCU2_UART_LIDARDataFailure(UartModule uartModule)
{
    DMA * dma = &dmaLidarIn;
    DMA_Abort(dma);
}
// UART interrupt
static uint8_t uartLidarBytesCounter = 0;
static uint8_t uartLidarData[LIDAR_FIX_DATALOAD];
static bool lidarReceivingStarted = 0;
void MCU2_UART_ReceiveLIDARData(uint8_t data, UartModule uartModule)
{
    UART * uart = &uartLIDAR;
    DMA * dma = &dmaLidarIn;
    UART_SendByte(&uartMCU3, data); // debug.
    if (data == 0xFA && uartLidarBytesCounter==0) // start of data transfer
    {
        uartLidarBytesCounter = 1;
//        lidarReceivingStarted = 1;
        //UART_SendByte(&uartMCU3, 0xFC); // debug.
        //UART_DisableInterrupts(uart); // disable interrupts
        DMA_TurnOnListeningForInterrupt(dma);
    }
//    
//    if (uartLidarBytesCounter < LIDAR_FIX_DATALOAD && lidarReceivingStarted)
//    {
//        uartLidarData[uartLidarBytesCounter] = data;
//    }
//    else
//    {
//        lidarReceivingStarted = 0;
//        // full container
//        MCU2_ReceivedLIDARData(uartLidarData);
//    }
//    uartLidarBytesCounter++;
}
void MCU2_ReceivedLIDARData(uint8_t * data)
{
    //UART_SendByte(&uartMCU3, 0xFB); // debug.
    memcpy(lidarDataINprocess,data,LIDAR_FIX_DATALOAD); // copy data to another part of memory to avoid data overwrite with new data
    uartLidarBytesCounter = 0; // reset RX counter
    Lidar_ParseData(&lidarData, lidarDataINprocess, LIDAR_FIX_DATALOAD); // parse data
    MCU2_SendPositionData();
}
// DMA interrupt
void MCU2_DMA_ReceivedLIDARData(uint8_t * data)
{
    memcpy(lidarDataINprocess,data,LIDAR_FIX_DATALOAD);
    UART * uart = &uartLIDAR;
    DMA * dma = &dmaLidarIn;
    UART_SendByte(&uartMCU3, 0xFB); // debug.
    //memcpy(lidarDataINprocess,data,LIDAR_FIX_DATALOAD); // copy data to another part of memory to avoid data overwrite with new data
    uartLidarBytesCounter = 0;
    UART_EnableInterrupts(uart); // reenable lidar uart interrupts
    Lidar_ParseData(&lidarData, lidarDataINprocess, LIDAR_FIX_DATALOAD);
    //MCU2_SendPositionData();
    //MCU2_SendRawPositionData();
}

static uint8_t dmaTransferToMcu3Status = 0;
void MCU2_DMATransferToMCU3(uint8_t * data, uint8_t size, bool skippable)
{
    if (skippable && dmaTransferToMcu3Status) // if message is skippable and UART is busy we will skip it
        return;
    while (dmaTransferToMcu3Status);        // wait until previous transfer is completed
    dmaTransferToMcu3Status = 1;            // signal that transfer is in progress
    if ((uint8_t*)&uartMCU3_OUT.data != (uint8_t*)data)         // if pointer to data container we can skip memcpy
        memcpy(uartMCU3_OUT.data, data, size);  // copy data from source to DMA container
    DMA_TurnOnListeningForInterrupt(&dmaMcu3OUT);
}

void MCU2_TransferToMCU3Complete(uint8_t * data)
{
    dmaTransferToMcu3Status = 0; // signal that transfer was completed
}

void MCU2_SendPositionData(void)
{
    RastoBot_Encode_Position(&mcu3MsgOut, &lidarData, &gyroData, &gpsData);
    ECP_EncodeExtended(&mcu3MsgOut, &uartMCU3_OUT, ECP_DATA_SIZE_MCU2_TO_MCU3);
    //UART_SendData(&uartMCU3,uartMCU3_OUT.data, uartMCU3_OUT.size);
    MCU2_DMATransferToMCU3(uartMCU3_OUT.data, uartMCU3_OUT.size, 1);
}
void MCU2_SendRawPositionData(void)
{
    MCU2_DMATransferToMCU3(lidarDataINprocess, LIDAR_FIX_DATALOAD, 1);
}

void MCU2_LidarEnable(void)
{
    UART_SendByte(&uartLIDAR, 'b'); // Lidar enable command
}

void MCU2_LidarDisable(void)
{
    UART_SendByte(&uartLIDAR, 'e'); // Lidar disable command
}

void MCU2_EnableLidarRX(void)
{
    
}

void MCU2_DisableLidarRX(void)
{
    
}

/************************************************************************/
/* TASKS - functions which are called only from loop to do basic tasks  */
/* WARNING: Do not invoke this functions somewhere else                 */
/************************************************************************/
static void MCU2_DoTasks(void)
{
    if (loopCounter % MCU2_LOG_DATA_TO_STRUCT_EVERY == 0)
        MCU2_TaskLogData();
    if (loopCounter % MCU2_CHECK_NEW_MESSAGES_EVERY == 0)
        MCU2_TaskCheckForNewReceivedData();
    if (loopCounter % MCU2_SEND_STATUS_DATA_EVERY == 0)
        MCU2_TaskSendStatusData();
    if (loopCounter % MCU2_SEND_POSITION_DATA_EVERY == 0)
        MCU2_TaskSendPositionData();
    if (loopCounter % MCU2_READ_PERIMETER_WIRE_EVERY == 0)
        MCU2_TaskReadPerimeterWire();
    if (loopCounter % MCU2_READ_GYRO_DATA_EVERY == 0)
        MCU2_TaskReadGyro();
}

static void MCU2_TaskReadGyro(void)
{
    MPU6050_Read(&gyroData.accelX, 
            &gyroData.accelY,
            &gyroData.accelZ,
            &gyroData.gyroX,
            &gyroData.gyroY,
            &gyroData.gyroZ,
            &gyroData.temperature);
    
    //QMC5883L_Read();
    HMC5883_Read();
    gyroData.magnetX = HMC5883_GetX();
    gyroData.magnetY = HMC5883_GetY();
    gyroData.magnetZ = HMC5883_GetZ();
    gyroData.azimuth = HMC5883_GetAzimuth();
}

static void MCU2_TaskReadPerimeterWire(void)
{
    gyroData.perimeterWire = (ADC_ReadData_AN19() << 1) >> 21;
}

static void MCU2_TaskLogData(void)
{
    
}

static void MCU2_TaskSendStatusData(void)
{
    if (SEND_STATUS_DATA)
    {
        RastoBot_Encode_SensorsMotors(&mcu3MsgOut, &sensorsStatus,&motorsStatus);
        ECP_EncodeExtended(&mcu3MsgOut, &uartMCU3_OUT, ECP_DATA_SIZE_MCU2_TO_MCU3);
        //UART_SendData(&uartMCU3,uartMCU3_OUT.data, uartMCU3_OUT.size);
        MCU2_DMATransferToMCU3(uartMCU3_OUT.data, uartMCU3_OUT.size, 0);
    }
}
static void MCU2_TaskSendPositionData(void)
{
    if (SEND_POSITION_DATA)
    {
        RastoBot_Encode_Position(&mcu3MsgOut, &lidarData, &gyroData, &gpsData);
        ECP_EncodeExtended(&mcu3MsgOut, &uartMCU3_OUT, ECP_DATA_SIZE_MCU2_TO_MCU3);
        //UART_SendData(&uartMCU3,uartMCU3_OUT.data, uartMCU3_OUT.size);
        MCU2_DMATransferToMCU3(uartMCU3_OUT.data, uartMCU3_OUT.size, 1);
    }
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