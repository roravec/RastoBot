#include "ermaCommProtocol.h"
/* Statics */
static void        RarrayLock(Rarray * buf);
static void        RarrayUnlock(Rarray * buf);

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
    out->data[currentIndex++] = ECP_FIRST_BYTE;
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
    out->data[currentIndex++] = ECP_LAST_BYTE;
    out->size = currentIndex;
    return out;
}

int8_t ECP_FindECPPacket(Rarray * in, Rarray * out)
{
    if (in->size > ECP_MIN_PACKET_LEN) // input array is too short to contain whole ECP packet
        return -1;
    int8_t successCode = -1;
    RarrayLock(in);             // lock array
    for (uint16_t i=0;i<in->size-ECP_MIN_PACKET_LEN;i++)
    {
        // look for ECP pattern
        if (    in->data[i] == ECP_FIRST_BYTE &&
                ~in->data[i+1] == in->data[i+2] &&
                ~in->data[i+3] == in->data[i+4])
        {
            // basic pattern confirmed
            // check if we have got all data
            uint8_t dlc = in->data[i+ECP_COMMAND_LEN+ECP_DLC_LEN];  // get DLC from the packet
            if (i+ECP_MIN_PACKET_LEN+dlc < in->size &&          // packet size is able to collect all data
                in->data[i+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc+ECP_CRC_LEN] == ECP_LAST_BYTE) // check last byte of packet
            {
                // calculate and check CRC
                uint8_t crcpacket = in->data[i+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc];// get crc from packet
                uint16_t crcCalcLen = 1+ECP_COMMAND_LEN+ECP_DLC_LEN+dlc;
                uint8_t actualCrc = ECP_CRC_START_VALUE;
                for (uint16_t j=i; j<i+crcCalcLen  ;j++)
                {
                    actualCrc ^= in->data[j];
                }
                if (crcpacket == actualCrc) // packet is OK, lets isolate it from Rarray
                {
                    uint16_t packetLen = ECP_MIN_PACKET_LEN + dlc;
                    RarrayRemoveRangeLO(in, i, packetLen, out, 1);
                    out->size = packetLen;
                    successCode = 0;
                }
            }
        }
    }
    RarrayUnlock(in);           // unlock array
    return successCode;
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