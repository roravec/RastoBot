/* 
 * File:   ermaCommProtocol.h
 * Author: orras
 *
 * Created on January 18, 2023, 1:13 PM
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

