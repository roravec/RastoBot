/* 
 * File:   DMA_Common.h
 * Author: orras
 *
 * Created on January 30, 2023, 9:03 PM
 */

#ifndef DMA_COMMON_H
#define	DMA_COMMON_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define DMA_NUMBER_OF_CHANNELS 8

typedef enum {
    DMA_CHANNEL_0=0, DMA_CHANNEL_1, DMA_CHANNEL_2, DMA_CHANNEL_3, DMA_CHANNEL_4, DMA_CHANNEL_5,DMA_CHANNEL_6,DMA_CHANNEL_7
} DmaChannel;

typedef struct {
  uint32_t CHPRI:2;
  uint32_t CHEDET:1;
  uint32_t :1;
  uint32_t CHAEN:1;
  uint32_t CHCHN:1;
  uint32_t CHAED:1;
  uint32_t CHEN:1;
  uint32_t CHCHNS:1;
  uint32_t :2;
  uint32_t CHPATLEN:1;
  uint32_t :1;
  uint32_t CHPIGNEN:1;
  uint32_t :1;
  uint32_t CHBUSY:1;
  uint32_t :8;
  uint32_t CHPIGN:8;
} DCHxCONbits_t;

typedef struct {
  uint32_t :3;
  uint32_t AIRQEN:1;
  uint32_t SIRQEN:1;
  uint32_t PATEN:1;
  uint32_t CABORT:1;
  uint32_t CFORCE:1;
  uint32_t CHSIRQ:8;
  uint32_t CHAIRQ:8;
} DCHxECONbits_t;

typedef struct {
  uint32_t CHERIF:1;
  uint32_t CHTAIF:1;
  uint32_t CHCCIF:1;
  uint32_t CHBCIF:1;
  uint32_t CHDHIF:1;
  uint32_t CHDDIF:1;
  uint32_t CHSHIF:1;
  uint32_t CHSDIF:1;
  uint32_t :8;
  uint32_t CHERIE:1;
  uint32_t CHTAIE:1;
  uint32_t CHCCIE:1;
  uint32_t CHBCIE:1;
  uint32_t CHDHIE:1;
  uint32_t CHDDIE:1;
  uint32_t CHSHIE:1;
  uint32_t CHSDIE:1;
} DCHxINTbits_t;

typedef struct {
  uint32_t CHSSA:32;
} DCHxSSAbits_t;

typedef struct {
  uint32_t CHDSA:32;
} DCHxDSAbits_t;

typedef struct {
  uint32_t CHSSIZ:16;
} DCHxSSIZbits_t;

typedef struct {
  uint32_t CHDSIZ:16;
} DCHxDSIZbits_t;

typedef struct {
  uint32_t CHSPTR:16;
} DCHxSPTRbits_t;

typedef struct {
  uint32_t CHDPTR:16;
} DCHxDPTRbits_t;

typedef struct {
  uint32_t CHCSIZ:16;
} DCHxCSIZbits_t;

typedef struct {
  uint32_t CHCPTR:16;
} DCHxCPTRbits_t;

typedef struct {
  uint32_t CHCPTR:16;
} DCSxCPTRbits_t;

typedef struct {
  uint32_t CHPDAT:16;
} DCHxDATbits_t;

// PIC32MK references to useful UART registers
typedef struct {
    DCHxCONbits_t   * DCHxCONbits;
    DCHxECONbits_t  * DCHxECONbits;
    DCHxINTbits_t   * DCHxINTbits;
    DCHxSSAbits_t   * DCHxSSAbits;
    DCHxDSAbits_t   * DCHxDSAbits;
    DCHxSSIZbits_t  * DCHxSSIZbits;
    DCHxDSIZbits_t  * DCHxDSIZbits;
    DCHxSPTRbits_t  * DCHxSPTRbits;
    DCHxDPTRbits_t  * DCHxDPTRbits;
    DCHxCSIZbits_t  * DCHxCSIZbits;
    DCHxCPTRbits_t  * DCHxCPTRbits;
    DCSxCPTRbits_t  * DCSxCPTRbits;
    DCHxDATbits_t   * DCHxDATbits;
} DmaRegisters;

typedef struct
{
    DmaChannel      channel;
    DmaRegisters    registers;
    uint8_t         sourceSize;
    uint8_t         destSize;
    _Bool           interruptEnabled;
    _Bool           initialized;
} DMA;


#ifdef	__cplusplus
}
#endif

#endif	/* DMA_COMMON_H */

