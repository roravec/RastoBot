/* 
 * File:   QMC5883L.h
 * Author: orras
 *
 * Created on February 6, 2023, 11:58 PM
 */

#ifndef QMC5883L_H
#define	QMC5883L_H

#include <xc.h>
#include "I2C_PIC32MK.h"
#include "config.h"
#include <stdbool.h>
#include <math.h>

#define QMC5883L_ADDRESS_W              0x1A
#define QMC5883L_ADDRESS_R              0x1B
#define QMC5883L_READ_FROM_ADDRESS      0x00


#define QMC5883L_SMOOTHING             1
#define QMC5883L_SMOOTHING_STEPS       5
#define QMC5883L_ADVANCED_SMOOTHING    1

#ifdef	__cplusplus
extern "C" {
#endif


void    QMC5883L_Init(I2C * i2cObj);
void    QMC5883L_Read();
void    QMC5883L_SetCalibration(int16_t x_min, int16_t x_max, int16_t y_min, int16_t y_max, int16_t z_min, int16_t z_max);
int16_t QMC5883L_GetX();
int16_t QMC5883L_GetY();
int16_t QMC5883L_GetZ();
int16_t QMC5883L_GetAzimuth();
void    QMC5883L_SetMode(uint8_t mode, uint8_t odr, uint8_t rng, uint8_t osr);
void    QMC5883L_ResetChip();



#ifdef	__cplusplus
}
#endif

#endif	/* QMC5883L_H */

