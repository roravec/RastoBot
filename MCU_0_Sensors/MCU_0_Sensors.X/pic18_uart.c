/* File:   pic18_uart.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: PIC32 UART communication library
 */ 
#include "pic18_uart.h"

Rarray uartBuffer;
_Bool uartNewDataFlag = 0;
/*
 * Initializes UART on predefined registers
 */
void UART_Init(void)
{
    RarrayCreate(&uartBuffer, RARRAY_SIZE_MAX);
    U1TX_TRIS = 0;
    U1RX_TRIS = 1;
    SPBRGH1 = 0; // SPBRG high byte
    SPBRG1 = UART_CalculateSPBRG(UART_BAUDRATE);
    //serial port enable
    RCSTA1bits.SPEN = 1;
    //9-bit transmission disabled
    TXSTA1bits.TX9 = 0;
    //transmit enable
    TXSTA1bits.TXEN = 1;
    //asynchronous mode
    TXSTA1bits.SYNC = 0;
    //enable receiver
    RCSTA1bits.CREN = 1;
    //disable address detection
    RCSTA1bits.ADDEN = 0;
    //clear framing error flag
    RCSTA1bits.FERR = 0;
    //clear overrun error flag
    RCSTA1bits.OERR = 0;
    //16-bit baud rate generator enabled
    BAUDCON1bits.BRG16 = 0; // use table 21-3 to calculate BRG
    //high baud rate disabled
    TXSTA1bits.BRGH = 0;
    //receiver polarity not inverted
    BAUDCON1bits.RXDTP = 0;
    //transmitter polarity not inverted
    BAUDCON1bits.TXCKP = 0;
    UART_InitInterrupts();
}

uint8_t UART_CalculateSPBRG(uint32_t desiredBaudrate)
{
    float spb1 = PER_FREQ / desiredBaudrate;
    spb1 = spb1 / 64;
    uint8_t spbrg = spb1 - 1;
    return spbrg;
}

// writes byte to UART TX
void UART_Write(uint8_t data)
{   
    while(TXSTA1bits.TRMT == 0){}
        TXREG1 = data;
}

void UART_WriteString(uint8_t* buf)
{
    while(*buf != '\0'){
        UART_Write(*buf);
        buf++;
    }
}

// writes a string of data byte by byte
void UART_WriteData(uint8_t* buf, uint16_t len)
{
    for(int i = 0; i<len;i++)
        UART_Write(buf[i]);
}

/* Break should be send before every transmission of a string.
 * 
 * From documentation:
UTXBRK: Transmit Break bit
1 = Send Break on next transmission. Start bit followed by twelve ?0? bits, followed by Stop bit; cleared by
hardware upon completion.
0 = Break transmission is disabled or completed
 */
void UART_SendBreak(void)
{
    while(TXSTA1bits.TRMT == 0);
    TXSTA1bits.SENDB = 1;
}

void UART_InitInterrupts(void)
{
    RC1IF = 0; // reset interrupt flag
    RC1IE = 1;
    RC1IP = 1; // high priority
}

void UART_DisableInterrupts()
{
    RC1IE = 0;
}
 /* INTERRUPT HANDLERS */
__interrupt() void ISR(void)
{
    uint8_t recvByte;
    if(RC1IE == 1 && RC1IF==1)  //Polling for reception interrupt
    {
        recvByte=RCREG1;//Receiving data
        RC1IF = 0;          // clear flag
        RarrayPush(&uartBuffer, recvByte);
        if (recvByte == 0x04) // end of packet
            uartNewDataFlag = 1;
    }      
}