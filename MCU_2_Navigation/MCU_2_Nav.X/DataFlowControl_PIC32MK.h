/* 
 * File:   DataFlowControl_PIC32MK.h
 * Author: orras
 *
 * Created on February 4, 2023, 10:45 PM
 */

#ifndef DATAFLOWCONTROL_PIC32MK_H
#define	DATAFLOWCONTROL_PIC32MK_H

#include "DMA_PIC32MK.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    DMA *       dma;
    _Bool       dmaEnabled;
    void        (*CheckConditionsToTurnOnDma)(uint8_t);
    void        (*CheckConditionsToTurnOffDma)(uint8_t*);
} DFC;

void        DFC_ReceivedByte(DFC * dfc, uint8_t);       // call this in UART/SPI interrupt
void        DFC_ReceivedDataBlock(DFC * dfc, uint8_t*); // call this in DMA interrupt after block transfer

#ifdef	__cplusplus
}
#endif

#endif	/* DATAFLOWCONTROL_PIC32MK_H */

