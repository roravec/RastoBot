/* 
 * File:   I2C_PIC32MK.h
 * Author: orras
 *
 * Created on February 2, 2023, 9:00 AM
 */

#ifndef I2C_PIC32MK_H
#define	I2C_PIC32MK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "I2C_Common.h"

I2C * I2C_Create(I2C * i2cObj, I2CModule iModule, uint32_t perFreq, uint32_t fsck, _Bool ienInterrupts);
void I2C_Initialize(I2C * i2cObj);
void I2C_AssignRegistersByModule(I2C * i2cObj);

void I2CWaitForIdle( I2C * i2cObj );
BYTE I2CGetData ( I2C * i2cObj, BOOL ackAfter, BOOL ackStatus);
I2C_RESULT I2CSend(I2C * i2cObj, BYTE data, BOOL waitForAck);

void I2C_Init(I2C * i2cObj, uint32_t sys_frequency, uint32_t frequency);
void I2C_WaitForIdle(I2C * i2cObj);
void I2C_Start(I2C * i2cObj, uint8_t addr);
void I2C_Stop(I2C * i2cObj);
void I2C_Restart(I2C * i2cObj, uint8_t addr);
void I2C_Ack(I2C * i2cObj);
void I2C_Nack(I2C * i2cObj); // Acknowledge Data bit;
void I2C_Wait(I2C * i2cObj, _Bool wait_ack);
void I2C_Write(I2C * i2cObj, uint8_t addr, _Bool wait_ack);
void I2C_ReadRef(I2C * i2cObj, uint8_t * value, _Bool ack_nack);
uint8_t I2C_Read(I2C * i2cObj, _Bool ack_nack);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_PIC32MK_H */

