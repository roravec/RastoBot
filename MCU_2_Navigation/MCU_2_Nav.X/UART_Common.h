/* File:   UART_Common.h
 * Author: skorra
 * Created on June 29, 2022, 2:34 PM
 * Rev: 220629
 * 
 * Description: 
 */

#ifndef UART_COMMON_H
#define	UART_COMMON_H

#include <xc.h>

#define UART_NUMBER_OF_MODULES 6

typedef enum {
    UART_MODULE_1=0, UART_MODULE_2, UART_MODULE_3, UART_MODULE_4, UART_MODULE_5, UART_MODULE_6
} UartModule;

typedef enum {
    UART_VECTOR_RX=0, UART_VECTOR_TX, UART_VECTOR_FAULT
} UartInterruptType;

typedef union {
  struct {
    uint32_t STSEL:1;
    uint32_t PDSEL:2;
    uint32_t BRGH:1;
    uint32_t RXINV:1;
    uint32_t ABAUD:1;
    uint32_t LPBACK:1;
    uint32_t WAKE:1;
    uint32_t UEN:2;
    uint32_t :1;
    uint32_t RTSMD:1;
    uint32_t IREN:1;
    uint32_t SIDL:1;
    uint32_t :1;
    uint32_t ON:1;
    uint32_t OVFDIS:1;
    uint32_t CLKSEL:2;
    uint32_t :3;
    uint32_t ACTIVE:1;
    uint32_t SLPEN:1;
  };
  struct {
    uint32_t :16;
    uint32_t RUNOVF:1;
  };
  struct {
    uint32_t :1;
    uint32_t PDSEL0:1;
    uint32_t PDSEL1:1;
    uint32_t :5;
    uint32_t UEN0:1;
    uint32_t UEN1:1;
  };
  struct {
    uint32_t :13;
    uint32_t USIDL:1;
    uint32_t :1;
    uint32_t UARTEN:1;
  };
  struct {
    uint32_t w:32;
  };
} UxMODEbits_t;

typedef union {
  struct {
    uint32_t URXDA:1;
    uint32_t OERR:1;
    uint32_t FERR:1;
    uint32_t PERR:1;
    uint32_t RIDLE:1;
    uint32_t ADDEN:1;
    uint32_t URXISEL:2;
    uint32_t TRMT:1;
    uint32_t UTXBF:1;
    uint32_t UTXEN:1;
    uint32_t UTXBRK:1;
    uint32_t URXEN:1;
    uint32_t UTXINV:1;
    uint32_t UTXISEL:2;
    uint32_t ADDR:8;
    uint32_t MASK:8;
  };
  struct {
    uint32_t :6;
    uint32_t URXISEL0:1;
    uint32_t URXISEL1:1;
    uint32_t :6;
    uint32_t UTXISEL0:1;
    uint32_t UTXISEL1:1;
  };
  struct {
    uint32_t :14;
    uint32_t UTXSEL:2;
  };
  struct {
    uint32_t w:32;
  };
} UxSTAbits_t;

typedef struct {
  uint32_t BRG:20;
} UxBRGbits_t;

// PIC32MK references to useful UART registers
    typedef struct {
        UxMODEbits_t        * UxMODEbits;
        UxSTAbits_t         * UxSTAbits;
        UxBRGbits_t         * UxBRGbits;
        volatile uint32_t   * UxTXREG;
        volatile uint32_t   * UxRXREG;
    } UartRegisters;

/* Main UART struct */
    typedef struct {
        uint32_t        baudrate;
        UartModule      module;
        UartRegisters   registers;
        _Bool           rxDisable;
        _Bool           txDisable;
        _Bool           rxInterrupt;
        _Bool           txInterrupt;
        _Bool           initialized;
        _Bool           enablePin;
        void            (*DataReceived)(uint8_t); // event
    } UART;

#endif	/* UART_COMMON_H */