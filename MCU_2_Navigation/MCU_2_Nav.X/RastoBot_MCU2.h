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
#include "UART_PIC32MK.h"
#include "DMA_PIC32MK.h"
#include "DataFlowControl_PIC32MK.h"

#define UART_CLOCK              REFO1CLK
#define UART_MCU0_BAUDRATE      19200
#define UART_MCU1_BAUDRATE      115200
#define UART_MCU3_BAUDRATE      115200
#define UART_LIDAR_BAUDRATE     230400UL
#define UART_GPS_BAUDRATE       9600

#ifdef	__cplusplus
extern "C" {
#endif

/* Function prototypes */
void MCU2_Init(void);

// Main loop. Should be called every 10ms
void MCU2_Loop(void);
void MCU2_UARTMCU0_ReceiveData(uint8_t data);
void MCU2_UARTMCU1_ReceiveData(uint8_t data);
void MCU2_UARTMCU3_ReceiveData(uint8_t data);


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU2_H */

