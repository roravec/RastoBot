/* File:   pic18_uart.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: PIC32 UART communication library
 */ 
#include "pic32mm_uart.h"

/*
 * Initializes UART on predefined registers
 */
void UART_Init(void)
{
    ECP_RecvBufferInit();
    U2MODEbits.CLKSEL = 0;
    U2MODEbits.BRGH = 0;
    U2BRG = ( (PER_FREQ / (16*UARTBAUDRATE))-1);//Baud rate generator register
    //U2BRG = 13;//Baud rate generator register
    //UBBRG = 129;
    U2STAbits.URXEN = 1;             //Receiver enable bit
    U2STAbits.UTXEN = 1;             //Transmitter enable bit
    U2STAbits.OERR = 0;              //Overrun error flag clear
    U2STAbits.FERR = 0;              //Framing error flag clear
    UART_InitInterrupts();        // setup interrupts
    U2MODEbits.ON = 1;                   //UART module enable
}

/*
 * Deactivates UART
 */
void UART_Deactivate()
{
    U2STAbits.URXEN = 0;     //Receiver enable bit
    U2STAbits.UTXEN = 0;     //Transmitter enable bit
    U2MODEbits.ON = 0;           //UART module disable
}
// writes byte to UART TX
void UART_Write(uint8_t data)
{   
    while(!U2STAbits.TRMT);  // wait for empty TX register
    U2TXREG = data;         // fill TX register with data
}
void UART_WriteString(uint8_t* buf)
{
    while(*buf != '\0'){
        UART_Write(*buf);
        buf++;
    }
}
// writes a string of data byte by byte
void UART_WriteData(uint8_t* buf, uint8_t len)
{
    for(uint8_t i = 0; i<len;i++)
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
    U2STAbits.UTXBRK = 1;
    asm("nop");
}

void UART_InitInterrupts(void){
    IFS1bits.U2RXIF = 0; // clear flag
    IPC10bits.U2RXIP = 2; // priority
    IPC10bits.U2RXIS = 1; // sub priority
    IEC1bits.U2RXIE = 1; // enable RX interrupt
}

void UART_DisableInterrupts()
{
    IFS1bits.U2RXIF = 0; // clear flag
    IEC1bits.U2RXIE = 0; // enable RX interrupt
}
/***** INTERRUPT HANDLERS ***************************************************/
//Interrupt UART2_RX
uint8_t recvByte;
void __ISR(_UART2_RX_VECTOR, IPL2AUTO) IntUart2AHandler(void){
    if(IEC1bits.U2RXIE && IFS1bits.U2RXIF){
        recvByte=U2RXREG;//Receiving data
        IFS1bits.U2RXIF = 0; // reset flag
        ECP_ReceivedByte(recvByte);
    }
}