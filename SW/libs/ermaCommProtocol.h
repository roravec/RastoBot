/* 
 * File:   ermaCommProtocol.h
 * Author: orras
 *
 * Created on January 18, 2023, 1:13 PM
 * 
 * How to receive and decode ECP packets:
 * 1. Just call "void ECP_RecvBufferInit()"
 * 2. Then each received byte should pre send to "void ECP_ReceivedByte(uint8_t data);"
 *  This function checks whether app received correct ECP packet or not.
 *  If app received complete ECP packet it will then add it to queue to process it by some other process.
 * 3. So in the other process (eg. main loop) we have to dequeue decoded ECP Message with function:
 *  ECP_Message *   ECP_MessageDequeue(void);
 Code example:
static void MCU0_TaskCheckForNewReceivedData(void)
{
    ECP_Message * msg;  // pointer to message to process
    while ((msg = ECP_MessageDequeue()) != 0) // check if we have some message to process in queue
    {
        // a new message was received and decoded. Let's process it...
        MCU0_DoMessageAction(msg);      // do requested action
        ECP_MarkMessageAsComplete(msg); // mark message as processed. It will free up space in queue.
    }
}
 * 
 * MCU0_TaskCheckForNewReceivedData is called continously from main loop so we will not miss any message to process.
 * 4. After the message was processed we have to flag it as Complete with function:
 * void ECP_MarkMessageAsComplete(msg);
 * 
 * That's it.
 * 
 * 
 * How to send ECP packets:
 * 1. We need to have Rarray object prepored to store raw message data so let's create it:
 * Rarray rawPacket; // create Rarray object
 * uint8_t rawPacketArr[ECP_MAX_PACKET_LEN]; // we also have to create dummy array to store data. 
 * // It is not necessary but by this way we will use just required memory space 
 * // (this avoids creating of internal array which size is RARRAY_SIZE_MAX and that can me too much for some MCUs).
 * RarrayCreate(&rawPacket, rawPacketArr, ECP_MAX_PACKET_LEN); // call RarrayCreate function to properly setup our Rarray object
 * 2. Prepare yout ECP_Message, fill it with data.
 * ECP_Message message;
 * 3. Now just call Rarray * ECP_Encode(&message, &rawPacket);
 * It will create ECP raw packet and store it in rawPacket.
 * 4. At this point we have to just send rawPacket data with UART or some other peripheral of our choice.
 * rawPacket stores data and data size.
 * 
 */

#ifndef ERMACOMMPROTOCOL_H
#define	ERMACOMMPROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "rarray.h"
#define ECP_MAX_DATA_BYTES  255
#ifdef PIC18F47J13         // PIC18F47J13
    #undef ECP_MAX_DATA_BYTES
    #define ECP_MAX_DATA_BYTES  32
#endif

#define ECP_QUEUE_SIZE      3   // has to be less than 127!!!
    
#define ECP_START_BYTE      0x01
#define ECP_STOP_BYTE       0x04
#define ECP_COMMAND_LEN     4
#define ECP_DLC_LEN         1
#define ECP_CRC_LEN         1
#define ECP_PATTERN_LEN     1+ECP_COMMAND_LEN+ECP_DLC_LEN
#define ECP_MIN_PACKET_LEN  2+ECP_COMMAND_LEN+ECP_DLC_LEN+ECP_CRC_LEN
#define ECP_MAX_PACKET_LEN  2+ECP_COMMAND_LEN+ECP_DLC_LEN+ECP_MAX_DATA_BYTES+ECP_CRC_LEN
    
#define ECP_CRC_START_VALUE 0x55
    
#define ECP_AVOID_CRC_CHECK_ON_RCV    1
    
typedef enum
{
    ECP_COMDATA = 0,    // command + data
    ECP_COMMAND         // just command
} ECP_MessageType;

typedef struct
{
    _Bool       startByteDetected;
    _Bool       stopByteDetected;
    _Bool       patternDetected;
    Rarray      buffer;
    uint8_t     command;
    uint8_t     subCommand;
    uint8_t     crc;
    uint8_t     dlc;
} ECP_Buffer;

typedef struct
{
    uint8_t         command;
    uint8_t         subCommand;
    uint8_t         dlc;
    uint8_t         data[ECP_MAX_DATA_BYTES];
    ECP_MessageType msgType;
} ECP_Message;

ECP_Message *   ECP_CreateMessage(ECP_Message * messOut, uint8_t command, uint8_t subCommand, uint8_t * data, uint8_t dlc);
ECP_Message *   ECP_CreateMessageCommand(ECP_Message * messOut, uint8_t command, uint8_t subCommand);
ECP_Message *   ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen);
ECP_Message *   ECP_DecodeRarray(ECP_Message * messOut, Rarray * ecpRaw); // calls ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen);
Rarray *        ECP_Encode(ECP_Message * message, Rarray * out);
int8_t          ECP_FindECPPacket(Rarray * in, Rarray * out);

void            ECP_RecvBufferInit(void);
void            ECP_ReceivedByte(uint8_t data);
_Bool           ECP_DetectHeadPattern(Rarray * data);
_Bool           ECP_DetectHeadPatternAtIndex(Rarray * data, uint16_t index);
_Bool           ECP_CheckCRCAtIndex(Rarray * data, uint16_t dlc, uint16_t index);
void            ECP_BufferReset(ECP_Buffer * buffer);
ECP_Message *   ECP_MessageDequeue(void);
void            ECP_MarkMessageAsComplete(ECP_Message * msg);

#ifdef	__cplusplus
}
#endif

#endif	/* ERMACOMMPROTOCOL_H */

