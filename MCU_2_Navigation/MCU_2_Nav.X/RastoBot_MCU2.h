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

#ifdef	__cplusplus
extern "C" {
#endif

/* Function prototypes */
void MCU2_Init(void);

// Main loop. Should be called every 10ms
void MCU2_Loop(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RASTOBOT_MCU2_H */

