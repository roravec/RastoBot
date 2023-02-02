/* 
 * File:   DMA_PIC32MK.c
 * Author: orras
 *
 * Created on January 30, 2023, 8:54 PM
 */

#include <proc/p32mk1024mcm064.h>
#include "DMA_PIC32MK.h"

uint8_t buffer[200];

static void DMA_InterruptHandler(DmaChannel module);

DMA * DmaActiveChannels[DMA_NUMBER_OF_CHANNELS]; // reference to active DMA module configurations

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
                )
{
    if (!dmaObj->initialized)
    {
        dmaObj->channel =           channel;
        dmaObj->source =            srcAddr;
        dmaObj->destination =       destAddr;
        dmaObj->sourceSize =        srcSize;
        dmaObj->destSize =          destSize;
        dmaObj->transferBytesPerEvent = transferBytesPerEvent;
        dmaObj->triggerOnInterruptId = triggerOnInterruptId;
        dmaObj->interruptEnabled =  enInterrupt;
        dmaObj->TransferComplete = 0;
        dmaObj->channelPriority = 3;
        dmaObj->initialized = 0;
    }
}

void DMA_Initialize(DMA * dmaObj)
{
    if (!dmaObj->initialized)
    {
        DMA_AssignRegistersByModule(dmaObj);
        DMA_ClearIRQFlags(dmaObj);
        DMACONbits.ON=1; // enable the main DMA controller
        dmaObj->registers.DCHxCONbits->CHPRI = dmaObj->channelPriority;
        dmaObj->registers.DCHxSSIZbits->CHSSIZ = dmaObj->sourceSize;
        dmaObj->registers.DCHxDSIZbits->CHDSIZ = dmaObj->destSize;
        dmaObj->registers.DCHxCSIZbits->CHCSIZ = dmaObj->transferBytesPerEvent;
        dmaObj->registers.DCHxSSAbits->CHSSA = KVA_TO_PA(dmaObj->source);
        dmaObj->registers.DCHxDSAbits->CHDSA = KVA_TO_PA(dmaObj->destination);
        dmaObj->registers.DCHxECONbits->CHSIRQ = dmaObj->triggerOnInterruptId;
        DCH0DSA = KVA_TO_PA(&U1TXREG);
        
//        dmaObj->registers.DCHxDSIZbits->CHDSIZ = 200;
//        DCH0DSA = KVA_TO_PA(buffer);
        
        if (dmaObj->interruptEnabled) DMA_InitInterrupts(dmaObj);
        dmaObj->registers.DCHxCONbits->CHAEN = 1;
        dmaObj->registers.DCHxCONbits->CHBUSY = 1; // channel is active
        dmaObj->registers.DCHxECONbits->SIRQEN = 1; // enable with interrupt
        
        dmaObj->registers.DCHxCONbits->CHEN = 1;    // enable channel
        
//0x00010000; // disable DMA channel 0 interrupts
//IFS1CLR=0x00010000; // clear any existing DMA channel 0 interrupt flag
//DMACONSET=0x00008000; // enable the DMA controller
//DCH0CON=0x3; // channel 0 off, priority 3, no chaining
//DCH1CON=0x62; // channel 1 off, priority 2
//// chain to higher priority
//// (channel 0), enable events detection while disabled
//DCH0ECONbits.CHSIRQ = 63; // IRQ UART2 TX
//// program channel 0 transfer
//DCH0SSA=KVA_TO_PA(&U3RXREG); // transfer source physical address
//DCH0DSA=KVA_TO_PA(buffer); // transfer destination physical address
//DCH0SSIZ=1; // source size is 1 byte
//DCH0DSIZ=200; // dst size at most 200 bytes
//DCH0CSIZ=1; // one byte per UART transfer request
//
//DCH0INTCLR=0x00ff00ff; // DMA0: clear events, disable interrupts
//
//IPC9CLR=0x00001f1f; // clear the DMA channels 0 and 1 priority and
//// sub-priority
//IPC9SET=0x00000b16; // set IPL 5, sub-priority 2 for DMA channel 0
//// set IPL 2, sub-priority 3 for DMA channel 1
//IEC1SET=0x00020000; // enable DMA channel 1 interrupt
//DCH0ECONbits.SIRQEN = 1;
//DCH0CONSET=0x80; // turn channel on
        
        dmaObj->initialized = 1;
    }
}

void DMA_AssignRegistersByModule(DMA * dmaObj)
{
    switch (dmaObj->channel)
    {
        case DMA_CHANNEL_0:
        {
            DmaActiveChannels[0] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH0CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH0ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH0INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH0SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH0DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH0SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH0DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH0SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH0DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH0CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH0CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS0CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH0DATbits;
            break;
        }
        case DMA_CHANNEL_1:
        {
            DmaActiveChannels[1] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH1CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH1ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH1INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH1SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH1DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH1SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH1DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH1SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH1DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH1CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH1CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS1CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH1DATbits;
            break;
        }
        case DMA_CHANNEL_2:
        {
            DmaActiveChannels[2] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH2CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH2ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH2INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH2SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH2DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH2SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH2DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH2SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH2DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH2CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH2CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS2CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH2DATbits;
            break;
        }
        case DMA_CHANNEL_3:
        {
            DmaActiveChannels[3] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH3CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH3ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH3INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH3SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH3DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH3SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH3DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH3SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH3DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH3CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH3CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS3CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH3DATbits;
            break;
        }
        case DMA_CHANNEL_4:
        {
            DmaActiveChannels[4] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH4CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH4ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH4INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH4SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH4DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH4SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH4DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH4SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH4DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH4CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH4CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS4CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH4DATbits;
            break;
        }
        case DMA_CHANNEL_5:
        {
            DmaActiveChannels[5] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH5CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH5ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH5INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH5SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH5DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH5SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH5DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH5SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH5DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH5CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH5CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS5CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH5DATbits;
            break;
        }
        case DMA_CHANNEL_6:
        {
            DmaActiveChannels[6] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH6CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH6ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH6INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH6SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH6DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH6SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH6DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH6SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH6DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH6CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH6CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS6CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH6DATbits;
            break;
        }
        case DMA_CHANNEL_7:
        {
            DmaActiveChannels[7] = dmaObj;
            dmaObj->registers.DCHxCONbits =     (DCHxCONbits_t*)    &DCH7CONbits;
            dmaObj->registers.DCHxECONbits =    (DCHxECONbits_t*)   &DCH7ECONbits;
            dmaObj->registers.DCHxINTbits =     (DCHxINTbits_t*)    &DCH7INTbits;
            dmaObj->registers.DCHxSSAbits =     (DCHxSSAbits_t*)    &DCH7SSAbits;
            dmaObj->registers.DCHxDSAbits =     (DCHxDSAbits_t*)    &DCH7DSAbits;
            dmaObj->registers.DCHxSSIZbits =    (DCHxSSIZbits_t*)   &DCH7SSIZbits;
            dmaObj->registers.DCHxDSIZbits =    (DCHxDSIZbits_t*)   &DCH7DSIZbits;
            dmaObj->registers.DCHxSPTRbits =    (DCHxSPTRbits_t*)   &DCH7SPTRbits;
            dmaObj->registers.DCHxDPTRbits =    (DCHxDPTRbits_t*)   &DCH7DPTRbits;
            dmaObj->registers.DCHxCSIZbits =    (DCHxCSIZbits_t*)   &DCH7CSIZbits;
            dmaObj->registers.DCHxCPTRbits =    (DCHxCPTRbits_t*)   &DCH7CPTRbits;
            dmaObj->registers.DCSxCPTRbits =    (DCSxCPTRbits_t*)   &DCS7CPTRbits;
            dmaObj->registers.DCHxDATbits =     (DCHxDATbits_t*)    &DCH7DATbits;
            break;
        }
        default: break;
    }
}
/************************/
void DMA_InitInterrupts(DMA * dmaObj)
{
    switch (dmaObj->channel)
    {
        case DMA_CHANNEL_0:
        {
            IFS2bits.DMA0IF = 0; // interrupt flag reset
            IPC18bits.DMA0IP = 5; // interrupt priority
            IPC18bits.DMA0IS = 2; // interrupt sub priority
            IEC2bits.DMA0IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_1:
        {
            IFS2bits.DMA1IF = 0; // interrupt flag reset
            IPC18bits.DMA1IP = 5; // interrupt priority
            IPC18bits.DMA1IS = 2; // interrupt sub priority
            IEC2bits.DMA1IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_2:
        {
            IFS2bits.DMA2IF = 0; // interrupt flag reset
            IPC18bits.DMA2IP = 5; // interrupt priority
            IPC18bits.DMA2IS = 2; // interrupt sub priority
            IEC2bits.DMA2IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_3:
        {
            IFS2bits.DMA3IF = 0; // interrupt flag reset
            IPC18bits.DMA3IP = 5; // interrupt priority
            IPC18bits.DMA3IS = 2; // interrupt sub priority
            IEC2bits.DMA3IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_4:
        {
            IFS5bits.DMA4IF = 0; // interrupt flag reset
            IPC45bits.DMA4IP = 5; // interrupt priority
            IPC45bits.DMA4IS = 2; // interrupt sub priority
            IEC5bits.DMA4IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_5:
        {
            IFS5bits.DMA5IF = 0; // interrupt flag reset
            IPC45bits.DMA5IP = 5; // interrupt priority
            IPC45bits.DMA5IS = 2; // interrupt sub priority
            IEC5bits.DMA5IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_6:
        {
            IFS5bits.DMA6IF = 0; // interrupt flag reset
            IPC46bits.DMA6IP = 5; // interrupt priority
            IPC46bits.DMA6IS = 2; // interrupt sub priority
            IEC5bits.DMA6IE = 1; // interrupt
            break;
        }
        case DMA_CHANNEL_7:
        {
            IFS5bits.DMA7IF = 0; // interrupt flag reset
            IPC46bits.DMA7IP = 5; // interrupt priority
            IPC46bits.DMA7IS = 2; // interrupt sub priority
            IEC5bits.DMA7IE = 1; // interrupt
            break;
        }
        default: break;
    }
}
void DMA_DisableInterrupts(DMA * dmaObj)
{
    switch (dmaObj->channel)
    {
        case DMA_CHANNEL_0:
        {
            IEC2bits.DMA0IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_1:
        {
            IEC2bits.DMA1IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_2:
        {
            IEC2bits.DMA2IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_3:
        {
            IEC2bits.DMA3IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_4:
        {
            IEC5bits.DMA4IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_5:
        {
            IEC5bits.DMA5IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_6:
        {
            IEC5bits.DMA6IE = 0; // enable interrupts
            break;
        }
        case DMA_CHANNEL_7:
        {
            IEC5bits.DMA7IE = 0; // enable interrupts
            break;
        }
        default: break;
    }
}

void DMA_Deactivate(DMA * dmaObj)
{
    dmaObj->registers.DCHxCONbits->CHEN = 0; // disable channel
    DMA_DisableInterrupts(dmaObj); // disable interrupts
}

void DMA_ClearIRQFlags(DMA * dmaObj)
{
    switch (dmaObj->channel)
    {
        case DMA_CHANNEL_0:
        {
            IFS2bits.DMA0IF = 0; // interrupt flag reset
            IFS1bits.U1TXIF = 0;
            break;
        }
        case DMA_CHANNEL_1:
        {
            IFS2bits.DMA1IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_2:
        {
            IFS2bits.DMA2IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_3:
        {
            IFS2bits.DMA3IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_4:
        {
            IFS5bits.DMA4IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_5:
        {
            IFS5bits.DMA5IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_6:
        {
            IFS5bits.DMA6IF = 0; // interrupt flag reset
            break;
        }
        case DMA_CHANNEL_7:
        {
            IFS5bits.DMA7IF = 0; // interrupt flag reset
            break;
        }
        default: break;
    }
}

void __attribute__((interrupt(ipl5auto), at_vector(_DMA0_VECTOR), aligned(16))) DMA0_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_0);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA1_VECTOR), aligned(16))) DMA1_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_1);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA2_VECTOR), aligned(16))) DMA2_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_2);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA3_VECTOR), aligned(16))) DMA3_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_3);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA4_VECTOR), aligned(16))) DMA4_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_4);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA5_VECTOR), aligned(16))) DMA5_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_5);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA6_VECTOR), aligned(16))) DMA6_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_6);   }
void __attribute__((interrupt(ipl5auto), at_vector(_DMA7_VECTOR), aligned(16))) DMA7_IRQ_Handler (void)
{   DMA_InterruptHandler(DMA_CHANNEL_7);   }


/* Interrupt handlers */
static void DMA_InterruptHandler(DmaChannel module)
{
    DMA * dmaObj = DmaActiveChannels[module];
    if (dmaObj->TransferComplete != 0)
        dmaObj->TransferComplete();
    DMA_ClearIRQFlags(dmaObj);
}