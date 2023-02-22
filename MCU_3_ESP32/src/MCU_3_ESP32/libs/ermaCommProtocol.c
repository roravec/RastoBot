#include "ermaCommProtocol.h"
ECP_Message ecpMessagesQueue[ECP_QUEUE_SIZE];

/* Globals */
static uint8_t recvBufferArr[ECP_MAX_PACKET_LEN];
ECP_Buffer ecpRecvBuffer;

/* Statics */
static void         ECP_BufferMessageEnqueue(ECP_Buffer * ecpRecvBuffer);
static int8_t       ECP_GetFreeQueueIndex(void);
static void         RarrayLock(Rarray * buf);
static void         RarrayUnlock(Rarray * buf);

ECP_Message * ECP_CreateMessage(ECP_Message * messOut, uint8_t command, uint8_t subCommand, uint8_t * data, uint8_t dlc)
{
    messOut->command =      command;
    messOut->subCommand =   subCommand;
    for (uint8_t i=0;i<dlc;i++)
        messOut->data[i] =  data[i];
    messOut->dlc =          dlc;
    messOut->msgType =      ECP_COMDATA;
    return messOut;
}

ECP_Message * ECP_CreateMessageCommand(ECP_Message * messOut, uint8_t command, uint8_t subCommand)
{
    messOut->command =      command;
    messOut->subCommand =   subCommand;
    messOut->dlc =          0;
    messOut->msgType =      ECP_COMMAND;
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
        for (uint8_t i=0,j=6;i<messOut->dlc;i++)
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
    return ECP_EncodeExtended(message, out, 0);
}
Rarray * ECP_EncodeExtended(ECP_Message * message, Rarray * out, uint8_t minDataLen)
{
    uint16_t currentIndex = 0;
    out->data[currentIndex++] = ECP_START_BYTE;
    out->data[currentIndex++] = message->command;
    out->data[currentIndex++] = ~out->data[(currentIndex-1)];
    out->data[currentIndex++] = message->subCommand;
    out->data[currentIndex++] = ~out->data[(currentIndex-1)];
    out->data[currentIndex++] = message->dlc > minDataLen ? message->dlc : minDataLen;
    uint8_t dataIndex = 0;
    for (uint8_t j=currentIndex; dataIndex < message->dlc && dataIndex < ECP_MAX_DATA_BYTES;dataIndex++)
        out->data[currentIndex++] = message->data[dataIndex];
    for (; dataIndex < minDataLen; dataIndex++)
        out->data[currentIndex++] = ECP_EMPTY_DATA;
//    for (;dataIndex < ECP_FIXED_DATA_SIZE;dataIndex++)
//        out->data[currentIndex++] = ECP_EMPTY_DATA;
    uint8_t crc = ECP_CRC_START_VALUE;
    for (uint16_t i=0; i < currentIndex  ;i++)
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
            //uint8_t packetSize = ECP_FIXED_DATA_SIZE>0 ? ECP_GetMinPacketSize() : ECP_GetMinPacketSize()+dlc; // if ECP_FIXED_DATA_SIZE is defined then DLC is already included in ECP_MIN_PACKET_LEN
            uint8_t packetSize = ECP_MIN_PACKET_LEN+dlc; // if ECP_FIXED_DATA_SIZE is defined then DLC is already included in ECP_MIN_PACKET_LEN
            if ((i+packetSize) < in->size &&          // packet size is able to collect all data
                in->data[(i+packetSize-1)] == ECP_STOP_BYTE) // check last byte of packet
            {
                // calculate and check CRC
                uint8_t crcpacket = in->data[i+packetSize-2];// get crc from packet
                uint16_t crcCalcLen = 1+packetSize-2;
                uint8_t actualCrc = ECP_CRC_START_VALUE;
                for (uint16_t j=i; j<i+crcCalcLen  ;j++)
                {
                    actualCrc ^= in->data[j];
                }
                if (ECP_AVOID_CRC_CHECK_ON_RCV || crcpacket == actualCrc) // packet is OK, lets isolate it from Rarray
                {
                    RarrayRemoveRangeLO(in, i, packetSize, out, 1);
                    out->size = packetSize;
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
void ECP_BufferInit(ECP_Buffer * ecpBuffer, uint8_t * ecpBufferArr, uint8_t size)
{
    RarrayCreate(&ecpBuffer->buffer, ecpBufferArr, size);
    ECP_BufferReset(ecpBuffer);
}

void ECP_ReceivedByte(uint8_t data)
{
    ECP_ReceivedByteCust(data, &ecpRecvBuffer);
}

uint8_t * arrRasto;
ECP_PacketValidity ECP_ReceivedByteCust(uint8_t data, ECP_Buffer * ecpBuffer)
{
    arrRasto = ecpBuffer->buffer.data;
    if (!ecpBuffer->buffer.created) // if array wasn't initialized then exit
        return ECP_UNKNOWN;
    if (!ecpBuffer->startByteDetected && data == ECP_START_BYTE) // waiting for start byte
        ecpBuffer->startByteDetected = 1; // streaming of ECP packet has started, next check for pattern
    if (ecpBuffer->startByteDetected) // receiving bytes
    {
        RarrayPush(&ecpBuffer->buffer,data);
        if (ecpBuffer->buffer.currentIndex < ECP_PATTERN_LEN)
        {
            // wait for data until ECP_PATTERN_LEN is reached to check head pattern and determine if packet is correct
        }
        else if (ecpBuffer->buffer.currentIndex == ECP_PATTERN_LEN)
        {
            // at this point we should be able to detect basic pattern of ECP packet
            // if pattern failed we will stop receiving packet and will wait for another packet
            if (ECP_DetectHeadPattern(&ecpBuffer->buffer))
            {
                ecpBuffer->dlc = data;
                ecpBuffer->patternDetected = 1;
            }
            else // invalid packet - RESET BUFFER
            {
                ECP_BufferReset(ecpBuffer);
                return ECP_INVALID_HEADER;
            }
        }
        else if (ecpBuffer->patternDetected) // head pattern already detected, wait for stop byte after data+crc
        {
//            if (ECP_FIXED_DATA_SIZE == 0 && ecpBuffer->buffer.currentIndex < (ECP_GetPatternSize() + ecpBuffer->dlc + 2) 
//             || ECP_FIXED_DATA_SIZE > 0  && ecpBuffer->buffer.currentIndex < (ECP_GetMaxPacketSize())
//                    )
            if (ecpBuffer->buffer.currentIndex < (ECP_PATTERN_LEN + ecpBuffer->dlc + 2))
            {
                // receiving data and waiting for STOP BYTE
            }
            else if (
//                    ((ECP_FIXED_DATA_SIZE == 0 && ecpBuffer->buffer.currentIndex == (ECP_GetPatternSize() + ecpBuffer->dlc + 2)) 
//                  || (ECP_FIXED_DATA_SIZE > 0  && ecpBuffer->buffer.currentIndex == (ECP_GetMaxPacketSize())))
//                  && ecpBuffer->buffer.data[(ecpBuffer->buffer.currentIndex-1)] == ECP_STOP_BYTE)
                    ((ecpBuffer->buffer.currentIndex == (ECP_PATTERN_LEN + ecpBuffer->dlc + 2)) )
                  && ecpBuffer->buffer.data[(ecpBuffer->buffer.currentIndex-1)] == ECP_STOP_BYTE)
            {
                ecpBuffer->stopByteDetected = 1;
                // stop byte received, check CRC
                if (ECP_CheckCRCAtIndex(&ecpBuffer->buffer,
//                        (ECP_FIXED_DATA_SIZE == 0 ? ecpBuffer->dlc : ECP_FIXED_DATA_SIZE), 
                        ecpBuffer->dlc, 
                        ecpBuffer->buffer.currentIndex-2))
                {
                    // CRC OK
                    // Packet is valid ECP packet
                    ecpBuffer->command = ecpBuffer->buffer.data[1];
                    ecpBuffer->subCommand = ecpBuffer->buffer.data[3];
//                    ecpBuffer->size = (ECP_FIXED_DATA_SIZE == 0 ? ECP_GetMinPacketSize()+ecpBuffer->dlc : ECP_GetMaxPacketSize());
                    ecpBuffer->size = ECP_MIN_PACKET_LEN+ecpBuffer->dlc;
                    ECP_BufferMessageEnqueue(ecpBuffer);
                    return ECP_VALID;
                }
                else // wrong CRC
                {
                    return ECP_INVALID_CRC;
                }
            }
            else 
            {
                ECP_BufferReset(ecpBuffer);
                return ECP_INVALID_FOOTER;
            }
        }
        else
        {
            ECP_BufferReset(ecpBuffer);
            return ECP_INVALID_PACKET_SIZE;
        }
    }
    return ECP_UNKNOWN;
}
ECP_PacketValidity ECP_ParseEnqueueRawDataBlock(uint8_t * packet, uint8_t len)
{
    uint8_t data[ECP_MAX_DATA_BYTES];
    if (packet[5] > 0) // if data is more than 0 then get data from raw packet
    {
        for (uint8_t i=0; i < packet[5] && i<ECP_MAX_DATA_BYTES ;i++)
            data[i] = packet[i];
    }
    ECP_EnqueueData(packet[1], packet[3], packet[5], data);
}

ECP_PacketValidity ECP_CheckPacketValidity(uint8_t * packet, uint8_t len)
{
    uint8_t dlc = ECP_GetDLCFromPacket(packet,0);
    if (len < ECP_MIN_PACKET_LEN)                                       return ECP_INVALID_PACKET_SIZE;
    if (dlc != len-(ECP_PATTERN_LEN+ECP_CRC_LEN+1))                     return ECP_INVALID_DATA_SIZE;
    if (!ECP_DetectHeadPatternAtIndexArr(packet, ECP_PATTERN_LEN))      return ECP_INVALID_HEADER;
    if (packet[len-1] != ECP_STOP_BYTE)                                 return ECP_INVALID_FOOTER;
    if (!ECP_CheckCRCAtIndexArr(packet, dlc, ECP_GetCRCIndex(0, dlc)))  return ECP_INVALID_CRC;
    return ECP_VALID;
}

_Bool ECP_DetectHeadPattern(Rarray * data)
{
    return ECP_DetectHeadPatternAtIndex(data, data->currentIndex);
}

_Bool ECP_DetectHeadPatternAtIndex(Rarray * data, uint16_t startIndex)
{
    if (data->size >= startIndex)
    {
        return ECP_DetectHeadPatternAtIndexArr(data->data, startIndex);
    }
    return 0;
}
_Bool ECP_DetectHeadPatternAtIndexArr(uint8_t * data, uint16_t startIndex)
{
    if (startIndex >= ECP_PATTERN_LEN)
    {
        uint8_t index = startIndex - (ECP_PATTERN_LEN); // set index at beginning of the packet
        uint8_t negdat0 = ~data[index+1];
        uint8_t negdat1 = ~data[index+3];
        if (    data[index] == ECP_START_BYTE &&
                negdat0 == data[(index+2)] &&
                negdat1 == data[(index+4)])
        {
            return 1;
        }
    }
    return 0;
}
_Bool ECP_CheckCRCAtIndex(Rarray * data, uint8_t dlc, uint16_t index)
{
    if (index < data->size)
    {
        return ECP_CheckCRCAtIndexArr(data->data, dlc, index);
    }
    return 0;
}
_Bool ECP_CheckCRCAtIndexArr(uint8_t * data, uint8_t dlc, uint16_t index)
{
    if (index >= dlc+ECP_PATTERN_LEN)
    {
        uint8_t actualCrc = ECP_CalculateCRCFromPacket(data, dlc, 0);
        uint8_t crcFromPacket = ECP_GetCRCFromPacket(data, dlc, 0);
        if (ECP_AVOID_CRC_CHECK_ON_RCV)
            return 1;
        if (crcFromPacket == actualCrc)
            return 1;
    }
    return 0;
}

uint8_t ECP_GetCRCIndex(uint8_t packetStartIndex, uint8_t dlc)
{
    return packetStartIndex + dlc + ECP_PATTERN_LEN + ECP_DLC_LEN;
}

uint8_t ECP_GetDLCFromPacket(uint8_t * data, uint8_t packetStartIndex)
{
    return data[ECP_PATTERN_LEN-1 + packetStartIndex];
}
uint8_t ECP_GetCRCFromPacket(uint8_t * data, uint8_t dlc, uint8_t packetStartIndex)
{
    return data[ECP_PATTERN_LEN + packetStartIndex + dlc + ECP_DLC_LEN];
}
uint8_t ECP_CalculateCRCFromPacket(uint8_t * data, uint8_t dlc, uint16_t startIndex)
{
    uint8_t actualCrc = ECP_CRC_START_VALUE;
    for (uint8_t i=startIndex; i<=startIndex+dlc+ECP_PATTERN_LEN ;i++)
    {
        actualCrc ^= data[i];
    }
    return actualCrc;
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
    if (ecpRecvBuffer == 0) return; // invalid pointer
    uint8_t data[ECP_MAX_DATA_BYTES];
    if (ecpRecvBuffer->dlc > 0)
    {
        for (uint8_t i=0,j=ECP_PATTERN_LEN; i < ecpRecvBuffer->dlc ;i++)
            data[i] = ecpRecvBuffer->buffer.data[j+i];
    }
    ECP_EnqueueData(
            ecpRecvBuffer->command,
            ecpRecvBuffer->subCommand,
            ecpRecvBuffer->dlc,
            data);
    ECP_BufferReset(ecpRecvBuffer);
}

void ECP_MessageEnqueue(ECP_Message * ecpMsg)
{
    ECP_EnqueueData(
            ecpMsg->command,
            ecpMsg->subCommand,
            ecpMsg->dlc,
            ecpMsg->data);
}
void ECP_EnqueueData(uint8_t command, uint8_t subComm, uint8_t dlc, uint8_t * data)
{
    int8_t index = ECP_GetFreeQueueIndex();
    if (index > -1) // queue is not full
    {
        //ECP_QueueShiftRight(); // shift all current messages to right to free the first index
        ecpMessagesQueue[index].command = command;
        ecpMessagesQueue[index].subCommand = subComm;
        ecpMessagesQueue[index].dlc = dlc;
        if (ecpMessagesQueue[index].dlc > 0)
        {
            for (uint8_t i=0; i<ecpMessagesQueue[0].dlc ;i++)
                ecpMessagesQueue[index].data[i] = data[i];
            ecpMessagesQueue[index].msgType = ECP_COMDATA;
        }
        else
            ecpMessagesQueue[index].msgType = ECP_COMMAND;
    }
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