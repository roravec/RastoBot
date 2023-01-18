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
#define ECP_FIRST_BYTE      0x01
#define ECP_LAST_BYTE       0x04
#define ECP_COMMAND_LEN     4
#define ECP_DLC_LEN         1
#define ECP_CRC_LEN         1
#define ECP_MIN_PACKET_LEN  2+ECP_COMMAND_LEN+ECP_DLC_LEN+ECP_CRC_LEN
    
#define ECP_CRC_START_VALUE 0x55
    
typedef enum
{
    ECP_COMDATA = 0,    // command + data
    ECP_COMMAND         // just command
} ECP_MessageType;

typedef struct
{
    uint16_t        command;
    uint8_t         dlc;
    uint8_t         data[ECP_MAX_DATA_BYTES];
    ECP_MessageType msgType;
} ECP_Message;

ECP_Message * ECP_CreateMessage(ECP_Message * messOut, uint16_t command, uint8_t * data, uint8_t dlc);
ECP_Message * ECP_CreateMessageCommand(ECP_Message * messOut, uint16_t command);
ECP_Message * ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen);
ECP_Message * ECP_DecodeRarray(ECP_Message * messOut, Rarray * ecpRaw); // calls ECP_Decode(ECP_Message * messOut, uint8_t * ecpRaw, uint16_t ecpRawLen);
Rarray * ECP_Encode(ECP_Message * message, Rarray * out);
Rarray * ECP_FindECPPacket(Rarray * in, Rarray * out);

#ifdef	__cplusplus
}
#endif

#endif	/* ERMACOMMPROTOCOL_H */

