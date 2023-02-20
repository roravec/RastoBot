/* 
 * File:   RastoBot_MCU2.h
 * Author: orras
 *
 * Created on January 26, 2023, 3:34 PM
 */

#ifndef RASTOBOT_MCU2_H
#define	RASTOBOT_MCU2_H

#include "config.h"
#include "../../SW/libs/RastoBot.h"
#include "ADC_PIC32MK.h"
#include "I2C_PIC32MK.h"
#include "UART_PIC32MK.h"
#include "DMA_PIC32MK.h"
#include "MPU6050.h"
#include "QMC5883L.h"
#include "HMC5883.h"
#include "gps_neo.h"

#define UART_CLOCK              REFO1CLK
#define UART_MCU0_BAUDRATE      19200
#define UART_MCU1_BAUDRATE      115200
#define UART_MCU3_BAUDRATE      115200
#define UART_LIDAR_BAUDRATE     230400UL
#define UART_GPS_BAUDRATE       9600

#define GPS_MAX_DATALOAD        200

#define MCU2_LOG_DATA_TO_STRUCT_EVERY   1000
#define MCU2_CHECK_NEW_MESSAGES_EVERY   1
#define MCU2_SEND_STATUS_DATA_EVERY     1000
#define MCU2_READ_GYRO_DATA_EVERY       100
#define MCU2_READ_COMPASS_DATA_EVERY    250
#define MCU2_READ_PERIMETER_WIRE_EVERY  100

#ifdef	__cplusplus
extern "C" {
#endif

/* Function prototypes */
void MCU2_Init(void);
void MCU2_InitUART(void);
void MCU2_InitDMA(void);
void MCU2_InitI2C(void);
void MCU2_InitGyroMPU6050(void);
void MCU2_InitCompass(void);
void MCU2_InitLidar(void);
void MCU2_InitGPS(void);
void MCU2_InitPerimeterWire(void);

// Main loop. Should be called every 10ms
void MCU2_Loop(void);
void MCU2_UART_ECP_ReceiveData(uint8_t data, UartModule uartModule);
void MCU2_UART_ECP_ReceivedDataBlock(uint8_t * data);
void MCU2_UART_ReceiveGPSData(uint8_t data, UartModule uartModule);
void MCU2_DMA_ReceivedGPSData(uint8_t * data);
void MCU2_UART_ReceiveLIDARData(uint8_t data, UartModule uartModule);
void MCU2_DMA_ReceivedLIDARData(uint8_t * data);


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU2_H */

