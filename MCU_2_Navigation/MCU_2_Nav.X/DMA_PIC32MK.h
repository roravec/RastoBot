/* 
 * File:   DMA_PIC32MK.h
 * Author: orras
 *
 * Created on January 30, 2023, 8:54 PM
 */

#ifndef DMA_PIC32MK_H
#define	DMA_PIC32MK_H

#define VirtToPhys(p) (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L)

#include <sys/kmem.h>
#include "DMA_Common.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    /* Function prototypes */
    /* Constructors-factories */
    DMA * DMA_Create(
            DMA * dmaObj, 
            DmaChannel channel, 
            uint32_t * srcAddr, 
            uint32_t * destAddr,
            uint16_t srcSize, 
            uint16_t destSize, 
            uint8_t transferBytesPerEvent, 
            uint8_t triggerOnInterruptId, 
            _Bool enInterrupt
    );
    void DMA_Initialize(DMA * dmaObj);
    void DMA_EnableChannel(DMA * dmaObj);
    void DMA_DisableChannel(DMA * dmaObj);
    void DMA_TurnOnListeningForInterrupt(DMA * dmaObj);
    void DMA_TurnOffListeningForInterrupt(DMA * dmaObj);
    void DMA_AssignRegistersByModule(DMA * dmaObj);
    void DMA_InitInterrupts(DMA * dmaObj);
    void DMA_DisableInterrupts(DMA * dmaObj);
    void DMA_Deactivate(DMA * dmaObj);
    void DMA_ClearIRQFlags(DMA * dmaObj);

#ifdef	__cplusplus
}
#endif

#endif	/* DMA_PIC32MK_H */

