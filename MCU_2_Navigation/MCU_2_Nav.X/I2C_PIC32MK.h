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


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_PIC32MK_H */

