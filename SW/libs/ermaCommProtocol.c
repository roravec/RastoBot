#include "ermaCommProtocol.h"
/* Globals */
static uint8_t recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer ecpRecvBuffer;

ECP_Message ecpMessagesQueue[ECP_QUEUE_SIZE];

/* Statics */
static void         ECP_BufferMessageEnqueue(ECP_Buffer * ecpRecvBuffer);
static int8_t       ECP_GetFreeQueueIndex(void);
static void         RarrayLock(Rarray * buf);
static void         RarrayUnlock(Rarray * buf);

ECP_Message * ECP_CreateMessage(ECP_Message * messOut, uint8_t command, uint8_t subCommand, uint8_t * data, uint8_t dlc)
{
    messOut->command = command;
    messOut->subCommand = subCommand;
    for (uint8_t i=0;i<dlc;i++)
        messOut->data[i] = data[i];
    messOut->dlc = dlc;
    messOut->msgType = ECP_COMDATA;
    return messOut;
}

ECP_Message * ECP_CreateMessageCommand(ECP_Message * messOut, uint8_t command, uint8_t subCommand)
{
    messOut->command = command;
    messOut->subCommand = subCommand;
    messOut->dlc = 0;
    messOut->msgType = ECP_COMMAND;
    return messOut;
}

ECP_Message * ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen)
{
    if (ecpRawLen < ECP_MIN_PACKET_LEN) // invalid length
        return 0;
    messOut->command = ecpRaw[1];
    messOut->subCommand = ecpRaw[3];
    messOut->dlc = ecpRaw[5];
    messOut->msgType = messOut->dlc > 0 ? ECP_COMDATA : ECP_COMMAND;
    if (messOut->dlc > 0 && ecpRawLen == ECP_MIN_PACKET_LEN + messOut->dlc)
    {
        for (uint16_t i=0,j=6;i<messOut->dlc;i++)
            messOut->data[i] = ecpRaw[j+i];
    }
    return messOut;
}

ECP_Message * ECP_DecodeRarray(ECP_Message * messOut, Rarray * ecpRaw) // calls ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen);
{
    return ECP_Decode(messOut, ecpRaw->data, ecpRaw->size);
}

Rarray * ECP_Encode(ECP_Message * message, Rarray * out)
{
    out->size = message->dlc + ECP_MIN_PACKET_LEN;
    uint16_t currentIndex = 0;
    out->data[currentIndex++] = ECP_START_BYTE;
    out->data[currentIndex++] = message->command;
    out->data[currentIndex++] = ~out->data[(currentIndex-1)];
    out->data[currentIndex++] = message->subCommand;
    out->data[currentIndex++] = ~out->data[(currentIndex-1)];
    out->data[currentIndex++] = message->dlc;
    for (uint16_t i=0,j=currentIndex;i<message->dlc;i++)
        out->data[currentIndex++] = message->data[i];
    uint8_t crc = ECP_CRC_START_VALUE;
    for (uint16_t i=0; i<currentIndex  ;i++)
        crc ^= out->data[i];
    out->data[currentIndex++] = crc;
    out->data[currentIndex++] = ECP_STOP_BYTE;
    out->size = currentIndex;
    return out;
}

int8_t ECP_FindECPPacket(Rarray * in, Rarray * out)
{
    if (in->size < ECP_MIN_PACKET_LEN) // input array is too short to contain whole ECP packet
        return -1;
    int8_t successCode = -1;
    RarrayLock(in);             // lock array
    for (uint16_t i=0;i<in->size-ECP_MIN_PACKET_LEN;i++)
    {
        if (ECP_DetectHeadPatternAtIndex(in, i))
        {
            // basic pattern confirmed
            // check if we have got all data
            uint8_t dlc = in->data[i+ECP_COMMAND_LEN+ECP_DLC_LEN];  // get DLC from the packet
            if ((i+ECP_MIN_PACKET_LEN+dlc) < in->size &&          // packet size is able to collect all data
                in->data[(i+1+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc+ECP_CRC_LEN)] == ECP_STOP_BYTE) // check last byte of packet
            {
                // calculate and check CRC
                uint8_t crcpacket = in->data[i+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc];// get crc from packet
                uint16_t crcCalcLen = 1+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc;
                uint8_t actualCrc = ECP_CRC_START_VALUE;
                for (uint16_t j=i; j<i+crcCalcLen  ;j++)
                {
                    actualCrc ^= in->data[j];
                }
                if (ECP_AVOID_CRC_CHECK_ON_RCV || crcpacket == actualCrc) // packet is OK, lets isolate it from Rarray
                {
                    uint16_t packetLen = ECP_MIN_PACKET_LEN + dlc;
                    RarrayRemoveRangeLO(in, i, packetLen, out, 1);
                    out->size = packetLen;
                    successCode = 0;
                    break;
                }
            }
        }
    }
    RarrayUnlock(in);           // unlock array
    return successCode;
}


/* Receiving packets **************************************************************/
void ECP_RecvBufferInit(void)
{
    RarrayCreate(&ecpRecvBuffer.buffer, recvBufferArr, ECP_MAX_PACKET_LEN);
    ECP_BufferReset(&ecpRecvBuffer);
}


void ECP_ReceivedByte(uint8_t data)
{
    if (!ecpRecvBuffer.buffer.created) // if array wasn't initialized then exit
        return;
    if (!ecpRecvBuffer.startByteDetected && data == ECP_START_BYTE) // waiting for start byte
        ecpRecvBuffer.startByteDetected = 1; // streaming of ECP packet has started, next check for pattern
    if (ecpRecvBuffer.startByteDetected) // receiving bytes
    {
        RarrayPush(&ecpRecvBuffer.buffer,data);
        if (ecpRecvBuffer.buffer.currentIndex < ECP_PATTERN_LEN)
        {
            // wait for data until ECP_PATTERN_LEN is reached to check head pattern and determine if packet is correct
        }
        else if (ecpRecvBuffer.buffer.currentIndex == ECP_PATTERN_LEN)
        {
            // at this point we should be able to detect basic patter of ECP packet
            // if pattern failed we will stop receiving packet and will wait for another packet
            if (ECP_DetectHeadPattern(&ecpRecvBuffer.buffer))
            {
                ecpRecvBuffer.dlc = data;
                ecpRecvBuffer.patternDetected = 1;
            }
            else // invalid packet - RESET BUFFER
            {
                ECP_BufferReset(&ecpRecvBuffer);
            }
        }
        else if (ecpRecvBuffer.patternDetected) // head pattern already detected, wait for stop byte after data+crc
        {
            if (ecpRecvBuffer.buffer.currentIndex < (ECP_PATTERN_LEN + ecpRecvBuffer.dlc + 2))
            {
                // receiving data now and waiting for STOP BYTE
            }
            else if (ecpRecvBuffer.buffer.currentIndex == (ECP_PATTERN_LEN + ecpRecvBuffer.dlc + 2) && 
                    ecpRecvBuffer.buffer.data[(ecpRecvBuffer.buffer.currentIndex-1)] == ECP_STOP_BYTE)
            {
                ecpRecvBuffer.stopByteDetected = 1;
                // stop byte received, check CRC
                if (ECP_CheckCRCAtIndex(&ecpRecvBuffer.buffer, ecpRecvBuffer.dlc, ecpRecvBuffer.buffer.currentIndex-2))
                {
                    // CRC OK
                    // Packet is valid ECP packet
                    ecpRecvBuffer.command = ecpRecvBuffer.buffer.data[1];
                    ecpRecvBuffer.subCommand = ecpRecvBuffer.buffer.data[3];
                    ECP_BufferMessageEnqueue(&ecpRecvBuffer);
                }
            }
            else 
            {
                ECP_BufferReset(&ecpRecvBuffer);
            }
        }
        else
        {
            ECP_BufferReset(&ecpRecvBuffer);
        }
    }
}

_Bool ECP_DetectHeadPattern(Rarray * data)
{
    return ECP_DetectHeadPatternAtIndex(data, data->currentIndex);
}

_Bool ECP_DetectHeadPatternAtIndex(Rarray * data, uint16_t startIndex)
{
    if (startIndex >= ECP_PATTERN_LEN && data->size >= startIndex)
    {
        uint8_t index = startIndex - (ECP_PATTERN_LEN); // set index at beginning of the packet
        uint8_t negdat0 = ~data->data[index+1];
        uint8_t negdat1 = ~data->data[index+3];
        if (    data->data[index] == ECP_START_BYTE &&
                negdat0 == data->data[(index+2)] &&
                negdat1 == data->data[(index+4)])
        {
            return 1;
        }
    }
    return 0;
}
_Bool ECP_CheckCRCAtIndex(Rarray * data, uint16_t dlc, uint16_t index)
{
    if (index < data->size && index >= dlc+ECP_PATTERN_LEN)
    {
        uint8_t actualCrc = ECP_CRC_START_VALUE;
        uint8_t crcFromPacket = data->data[index];
        for (uint8_t i=index-dlc-ECP_PATTERN_LEN;i<index;i++)
        {
            actualCrc ^= data->data[i];
        }
        if (ECP_AVOID_CRC_CHECK_ON_RCV)
            return 1;
        if (crcFromPacket == actualCrc)
            return 1;
    }
    return 0;
}

void ECP_BufferReset(ECP_Buffer * buffer)
{
    ecpRecvBuffer.patternDetected = 0;
    ecpRecvBuffer.startByteDetected = 0;
    ecpRecvBuffer.stopByteDetected = 0;
    RarrayReset(&buffer->buffer);
}

ECP_Message * ECP_MessageDequeue(void)
{
    for (uint8_t i=0;i<ECP_QUEUE_SIZE;i++)
    {
        if (ecpMessagesQueue[i].command != 0x00)
        {
            return &ecpMessagesQueue[i];
        }
    }
    return 0;
}

void ECP_MarkMessageAsComplete(ECP_Message * msg)
{
    msg->command = 0x00;
}

static void ECP_BufferMessageEnqueue(ECP_Buffer * ecpRecvBuffer)
{
    int8_t index = ECP_GetFreeQueueIndex();
    if (index > -1) // queue is not full
    {
        //ECP_QueueShiftRight(); // shift all current messages to right to free the first index
        ecpMessagesQueue[index].command = ecpRecvBuffer->command;
        ecpMessagesQueue[index].subCommand = ecpRecvBuffer->subCommand;
        ecpMessagesQueue[index].dlc = ecpRecvBuffer->dlc;
        if (ecpMessagesQueue[index].dlc > 0)
        {
            for (uint8_t i=0,j=ECP_PATTERN_LEN; i<ecpMessagesQueue[0].dlc ;i++)
                ecpMessagesQueue[index].data[i] = ecpRecvBuffer->buffer.data[j+i];
            ecpMessagesQueue[index].msgType = ECP_COMDATA;
        }
        else
            ecpMessagesQueue[index].msgType = ECP_COMMAND;
    }
    ECP_BufferReset(ecpRecvBuffer);
}

static int8_t ECP_GetFreeQueueIndex(void)
{
    for (uint8_t i=0;i<ECP_QUEUE_SIZE;i++)
        if (ecpMessagesQueue[i].command == 0x00)
            return i;
    return -1;
}

static void RarrayLock(Rarray * buf)
{
    while (buf->lockActive);    // wait until lock release
    buf->lockActive = 1;        // lock buffer
}
static void RarrayUnlock(Rarray * buf)
{
    buf->lockActive = 0;        // unlock buffer
}