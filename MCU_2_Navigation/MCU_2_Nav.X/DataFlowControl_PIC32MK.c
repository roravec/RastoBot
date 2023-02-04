#include "DataFlowControl_PIC32MK.h"

void        DFC_ReceivedByte(DFC * dfc, uint8_t data)       // call this in UART/SPI interrupt
{
    if (dfc->CheckConditionsToTurnOnDma!=0)
    {
        
    }
}
void        DFC_ReceivedDataBlock(DFC * dfc, uint8_t* data) // call this in DMA interrupt after block transfer
{
    if (dfc->CheckConditionsToTurnOffDma!=0)
    {
        
    }
}