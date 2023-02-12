/* 
 * File:   HMC5883.h
 * Author: orras
 *
 * Created on February 12, 2023, 10:01 PM
 */

#ifndef HMC5883_H
#define	HMC5883_H

#include <xc.h>
#include "I2C_PIC32MK.h"
#include "config.h"
#include <stdbool.h>
#include <math.h>

#define HMC5883_ADDRESS_W              0x3C
#define HMC5883_ADDRESS_R              0x3D
#define HMC5883_READ_FROM_ADDRESS      0x03

#define HMC5883_SMOOTHING             1
#define HMC5883_SMOOTHING_STEPS       5
#define HMC5883_ADVANCED_SMOOTHING    1

#ifdef	__cplusplus
extern "C" {
#endif

void    HMC5883_Init(I2C * i2cObj);
void    HMC5883_Read();
void    HMC5883_SetCalibration(int16_t x_min, int16_t x_max, int16_t y_min, int16_t y_max, int16_t z_min, int16_t z_max);
int16_t HMC5883_GetX();
int16_t HMC5883_GetY();
int16_t HMC5883_GetZ();
int16_t HMC5883_GetAzimuth();
void    HMC5883_SetMode(uint8_t mode, uint8_t odr, uint8_t rng, uint8_t osr);
void    HMC5883_ResetChip();


#ifdef	__cplusplus
}
#endif

#endif	/* HMC5883_H */

