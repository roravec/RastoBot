#include "I2C_PIC32MK.h"
#include "hwinterface.h"

I2C * I2CActiveModules[I2C_NUMBER_OF_MODULES]; // reference to active CAN module configurations


I2C * I2C_Create
    (I2C * i2cObj, I2CModule iModule, uint32_t perFreq, uint32_t fsck, _Bool ienInterrupts)
{
    i2cObj->enableInterrupts = ienInterrupts;
    i2cObj->initialized = 0;
    i2cObj->module = iModule;
    i2cObj->rxDisable = 0;
    i2cObj->txDisable = 0;
    i2cObj->baudrate = ( (perFreq / (2*fsck))-1)-((perFreq / Tpgob)/2); // value has to be over 0x0 and less than 0x3
    return i2cObj;
}

void I2C_Initialize(I2C * i2cObj)
{
    if (!i2cObj->initialized)
    {
        I2C_AssignRegistersByModule(i2cObj);
        I2CConfigure(i2cObj,0); // reset CON
        *i2cObj->registers.I2CxCON = 0;
        i2cObj->registers.I2CxCONbits->SIDL = 0;
        i2cObj->registers.I2CxCONbits->DISSLW = 1;
        i2cObj->registers.I2CxCONbits->SMEN = 0;
     
        IEC6bits.I2C4BIE = 0;
        IEC6bits.I2C4MIE = 0;
        IEC6bits.I2C4SIE = 0;
        IFS6bits.I2C4BIF = 0;
        IFS6bits.I2C4MIF = 0;
        IFS6bits.I2C4SIF = 0;
        
        
//    /* Disable the I2C Master interrupt */
//    IEC1CLR = _IEC1_I2C1MIE_MASK;
//
//    /* Disable the I2C Bus collision interrupt */
//    IEC1CLR = _IEC1_I2C1BIE_MASK;
//
//    I2C1CONCLR = _I2C1CON_SIDL_MASK;
//    I2C1CONCLR = _I2C1CON_DISSLW_MASK;
//    I2C1CONCLR = _I2C1CON_SMEN_MASK;
//
//    /* Clear master interrupt flag */
//    IFS1CLR = _IFS1_I2C1MIF_MASK;
//
//    /* Clear fault interrupt flag */
//    IFS1CLR = _IFS6_I2C1BIF_MASK;
        
        

//    /* Disable the I2C Master interrupt */
//    IEC6CLR = _IEC6_I2C4MIE_MASK;
//
//    /* Disable the I2C Bus collision interrupt */
//    IEC6CLR = _IEC6_I2C4BIE_MASK;
//
//    I2C4BRG = 595;
//
//    I2C4CONCLR = _I2C4CON_SIDL_MASK;
//    I2C4CONCLR = _I2C4CON_DISSLW_MASK;
//    I2C4CONCLR = _I2C4CON_SMEN_MASK;
//
//    /* Clear master interrupt flag */
//    IFS6CLR = _IFS6_I2C4MIF_MASK;
//
//    /* Clear fault interrupt flag */
//    IFS6CLR = _IFS6_I2C4BIF_MASK;

    /* Turn on the I2C module */
//    I2C4CONSET = _I2C4CON_ON_MASK;
    
    
        i2cObj->registers.I2CxBRGbits->I2CBRG = i2cObj->baudrate; // set baudrate
        i2cObj->registers.I2CxCONbits->SDAHT = 0; // Minimum of 300 ns hold time on SDA after the falling edge of SCL
        //I2CSetFrequency(i2cObj,PERIPHERAL_FREQ,I2C_CLOCK_FREQ);
        I2CEnable(i2cObj, 1);
        i2cObj->initialized = 1;
    }
}
// This function shall be used only during initialization!
void I2C_AssignRegistersByModule(I2C * i2cObj)
{
    switch (i2cObj->module)
    {
        case I2C_MODULE_1:
        {
            I2CActiveModules[I2C_MODULE_1] = i2cObj;           
            i2cObj->registers.I2CxCONbits =       (I2CxCONbits_t*)&I2C1CONbits;
            i2cObj->registers.I2CxSTATbits =      (I2CxSTATbits_t*)&I2C1STATbits;
            i2cObj->registers.I2CxBRGbits =       (I2CxBRGbits_t*)&I2C1BRGbits;
            i2cObj->registers.I2CxCON =           &I2C1CON;
            i2cObj->registers.I2CxCONSET =        &I2C1CONSET;
            i2cObj->registers.I2CxCONCLR =        &I2C1CONCLR;
            i2cObj->registers.I2CxTRN =           &I2C1TRN;
            i2cObj->registers.I2CxSTAT =          &I2C1STAT;
            i2cObj->registers.I2CxSTATCLR =       &I2C1STATCLR;
            i2cObj->registers.I2CxRCV =           &I2C1RCV;
            break;
        }
        case I2C_MODULE_2:
        {
            I2CActiveModules[I2C_MODULE_2] = i2cObj;           
            i2cObj->registers.I2CxCONbits =       (I2CxCONbits_t*)&I2C2CONbits;
            i2cObj->registers.I2CxSTATbits =      (I2CxSTATbits_t*)&I2C2STATbits;
            i2cObj->registers.I2CxBRGbits =       (I2CxBRGbits_t*)&I2C2BRGbits;
            i2cObj->registers.I2CxCON =           &I2C2CON;
            i2cObj->registers.I2CxCONSET =        &I2C2CONSET;
            i2cObj->registers.I2CxCONCLR =        &I2C2CONCLR;
            i2cObj->registers.I2CxTRN =           &I2C2TRN;
            i2cObj->registers.I2CxSTAT =          &I2C2STAT;
            i2cObj->registers.I2CxSTATCLR =       &I2C2STATCLR;
            i2cObj->registers.I2CxRCV =           &I2C2RCV;
            break;
        }
        case I2C_MODULE_3:
        {
            I2CActiveModules[I2C_MODULE_3] = i2cObj;           
            i2cObj->registers.I2CxCONbits =       (I2CxCONbits_t*)&I2C3CONbits;
            i2cObj->registers.I2CxSTATbits =      (I2CxSTATbits_t*)&I2C3STATbits;
            i2cObj->registers.I2CxBRGbits =       (I2CxBRGbits_t*)&I2C3BRGbits;
            i2cObj->registers.I2CxCON =           &I2C3CON;
            i2cObj->registers.I2CxCONSET =        &I2C3CONSET;
            i2cObj->registers.I2CxCONCLR =        &I2C3CONCLR;
            i2cObj->registers.I2CxTRN =           &I2C3TRN;
            i2cObj->registers.I2CxSTAT =          &I2C3STAT;
            i2cObj->registers.I2CxSTATCLR =       &I2C3STATCLR;
            i2cObj->registers.I2CxRCV =           &I2C3RCV;
            break;
        }
        case I2C_MODULE_4:
        {
            I2CActiveModules[I2C_MODULE_4] = i2cObj;           
            i2cObj->registers.I2CxCONbits =       (I2CxCONbits_t*)&I2C4CONbits;
            i2cObj->registers.I2CxSTATbits =      (I2CxSTATbits_t*)&I2C4STATbits;
            i2cObj->registers.I2CxBRGbits =       (I2CxBRGbits_t*)&I2C4BRGbits;
            i2cObj->registers.I2CxCON =           &I2C4CON;
            i2cObj->registers.I2CxCONSET =        &I2C4CONSET;
            i2cObj->registers.I2CxCONCLR =        &I2C4CONCLR;
            i2cObj->registers.I2CxTRN =           &I2C4TRN;
            i2cObj->registers.I2CxSTAT =          &I2C4STAT;
            i2cObj->registers.I2CxSTATCLR =       &I2C4STATCLR;
            i2cObj->registers.I2CxRCV =           &I2C4RCV;
            break;
        }
        default: break;
    }
}
/************************/

/* This routine can be used by both master or slave receivers. */
void I2CAcknowledgeByte ( I2C * i2cObj, BOOL ack )
{
    I2CWaitForIdle(i2cObj);
    //while(!I2CBusIsIdle(i2cObj));                   // wait for bus idle
    // Assign the ACK/NAK value
	if(ack == 1)    i2cObj->registers.I2CxCONbits->ACKDT = 1;
    else            i2cObj->registers.I2CxCONbits->ACKDT = 0;
    i2cObj->registers.I2CxCONbits->ACKEN = 0; // Send the ACK/NAK
}

/*This routine can be used by both master or slave receivers.*/
BOOL I2CAcknowledgeHasCompleted ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxCONbits->ACKEN);
}

/*Just because this routine returns TRUE does not guarantee that a bus
    arbitration loss cannot occur.  Two or more masters can start a transfer 
    within the minimum start signal hold time.  (Refer to the I2C specification
    for a definition of the minimum start condition hold time.)*/
BOOL I2CBusIsIdle( I2C * i2cObj )
{
    // Check the status of the Start & Stop bits to determine if the bus is idle.
    return ( (i2cObj->registers.I2CxSTATbits->S == 0 && i2cObj->registers.I2CxSTATbits->P == 0 ) ||
             (i2cObj->registers.I2CxSTATbits->S == 0 && i2cObj->registers.I2CxSTATbits->P == 1 )   );
}

void I2CWaitForIdle( I2C * i2cObj )
{
    //Delay_ms(10);
    while (!I2CTransmitterIsReady(i2cObj));          // wait for transmitter	
    while(i2cObj->registers.I2CxSTATbits->TRSTAT); // Bit = 0 ? Master transmit is not in progress
    while(!I2CConReady(i2cObj));
    //if (I2CBusIsIdle(i2cObj)) return;
    //while (!I2CBusIsIdle(i2cObj));
    while(!I2CBusIsIdle(i2cObj) && (*(i2cObj->registers.I2CxCON) & 0x1F)/* && (*i2cObj->registers.I2CxSTAT & 0x04)*/); // Acknowledge sequence not in progress
                                // Receive sequence not in progress
                                // Stop condition not in progress
                                // Repeated Start condition not in progress
                                // Start condition not in progress
}

/* This routine can be used by both master or slave receivers. */
BOOL I2CByteWasAcknowledged ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxSTATbits->ACKSTAT);
}

/*Some status conditions are automatically cleared by hardware and it is not
    necessary for software to clear them.*/
void I2CClearStatus ( I2C * i2cObj, uint32_t status )
{
	*(i2cObj->registers.I2CxSTATCLR) = status;
}

/*Refer to the I2C_CONFIGURATION enumerated data type for details on each 
    configuration flag.  Note that the bitmask resulting from the bit-wise OR
    of these values will result in a value that is not defined in the enum.*/
void I2CConfigure ( I2C * i2cObj, uint32_t flags )
{
	*(i2cObj->registers.I2CxCONSET) = flags;
}

void I2CEnable( I2C * i2cObj, BOOL enable )
{
	i2cObj->registers.I2CxCONbits->ON = enable;
}

/* This routing should be used by both master and slave receivers. */
BYTE I2CGetByte ( I2C * i2cObj )
{
    I2CReceiverEnable(i2cObj, 1);
    while(!I2CReceivedDataIsAvailable(i2cObj));     // wait for data on RX
    uint8_t data = *(i2cObj->registers.I2CxRCV);    
	return data;
}
/* This routing should be used by both master and slave receivers. */
BYTE I2CGetData ( I2C * i2cObj, BOOL ackAfter, BOOL ackStatus)
{
    BYTE data = 0x00;
    data = I2CGetByte(i2cObj);
    if (ackAfter)
    {
        I2CAcknowledgeByte(i2cObj,ackStatus);     
        while(!I2CAcknowledgeHasCompleted(i2cObj));     // wait for ACK complete
    }
	return data;
}

/* Returns:
    The return value is a bitmask generated by a bit-wise OR of the I2C_STATUS
    values that are currently set.*/
uint32_t I2CGetStatus ( I2C * i2cObj )
{
    uint32_t              status = 0;
    //uint32_t              con;

    // Read the status and control registers
    //status  =   *(i2cObj->registers.I2CxSTAT);
    //con =       *(i2cObj->registers.I2CxCON);
    
//    // Condition the "Start" flag so it does not get set until
//    // the "Start" (or "Repeated Start") signal is complete.
//    if( *(i2cObj->registers.I2CxCON) & (_I2CCON_SEN_MASK | _I2CCON_RSEN_MASK) )
//    {
//        status = *(i2cObj->registers.I2CxSTAT) & (~_I2CSTAT_S_MASK);
//    }
//
//    // Condition the "Stop" flag so it does not get set until
//    // the "Stop" signal is complete.
//    if( *(i2cObj->registers.I2CxCON) & _I2CCON_PEN_MASK )
//    {
//        status = *(i2cObj->registers.I2CxSTAT) & (~_I2CSTAT_P_MASK);
//    }
    status = *(i2cObj->registers.I2CxSTAT) & ((_I2CSTAT_P_MASK | _I2CSTAT_S_MASK));

	return(status);
}

/* Returns:
    Boolean identifying if the byte received is data or an address byte
    * TRUE    - If the byte received is an address byte
    * FALSE   - If the byte received is a data byte*/
BOOL I2CReceivedByteIsAnAddress ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxSTATbits->D_A);
}

/*Returns:
    Boolean identifying if data is availble or not
    * TRUE    - If the receiver has data available
    * FALSE   - If the receiver does not have data availble*/
BOOL I2CReceivedDataIsAvailable ( I2C * i2cObj )
{
	return(i2cObj->registers.I2CxSTATbits->RBF);
}

/* Parameters:
    id      - Identifies the desired I2C module
    
    enable  - Determines if the receiver is to be enabled or disabled
              * If TRUE, enables the module to receive data on the I2C
              * If FALSE, disables the module from receiving data on the I2C*/
I2C_RESULT I2CReceiverEnable ( I2C * i2cObj, BOOL enable )
{
    I2CWaitForIdle(i2cObj);
    // Enable the receiver
	i2cObj->registers.I2CxCONbits->RCEN = enable;
    //while (i2cObj->registers.I2CxCONbits->RCEN);           // Wait until RCEN is cleared (automatic)  
	
    // Check for an overflow condition
	if(i2cObj->registers.I2CxSTATbits->I2COV)
    {
		return(I2C_RECEIVE_OVERFLOW); 
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

/*******************************************************************************
  Function:
    I2C_RESULT I2CRepeatStart ( I2C_MODULE id )
  Summary:
    Routine to send a repeated-start condition during an ongoing transfer
  Description:
    This routine supports sending a repeated start condition to change slave 
    targets or transfer direction to support certain I2C transfer formats.
  Precondition:
    The module must have been configured appropriately and enabled and the a 
    transfer must have been previously started.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    None
  Example:
    <code>
    result = I2CRepeatStart (I2C1);
    </code>
  Remarks:
    Only an I2C master that has already started a transfer can send a repeated-
    start condition.
  *****************************************************************************/
I2C_RESULT I2CRepeatStart ( I2C * i2cObj )
{
    I2C_RESULT result;
    // Send the repeated Start
	//*(i2cObj->registers.I2CxCONSET) = _I2CCON_RSEN_MASK;
    I2CWaitForIdle(i2cObj);
    //while(!I2CBusIsIdle(i2cObj));                   // wait for bus idle
    while(!I2CConReady(i2cObj));
    i2cObj->registers.I2CxCONbits->RSEN = 1;
//    I2C_SDA_LAT = 0;
//    I2C_SCL_LAT = 0;
	
    // Check for collisions
	if( *(i2cObj->registers.I2CxSTAT) & (_I2CSTAT_BCL_MASK|_I2CSTAT_IWCOL_MASK) )
    {
		result = (I2C_MASTER_BUS_COLLISION); 
    }
	else
    {
		result = (I2C_SUCCESS);
    }
    while (!I2CRestartConditionStarted(i2cObj));
    return result;
}

/*******************************************************************************
  Function:
    I2C_RESULT I2CSendByte ( I2C_MODULE id, BYTE data )
  Summary:
    Routine to send a byte of data on the I2C bus
  Description:
    This routine allows the caller to send a byte of data on the I2C bus.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started, and the transmitter must be ready to 
    accept a byte of data to send.
  Parameters:
    id      - Identifies the desired I2C module
    
    data    - Data byte to send on the I2C bus
  Returns:
    An I2C operation result indicating if the operation succeeded or if an error occured.
    * I2C_SUCCESS     - The data has been buffered to be sent on the bus
    * I2C_ERROR       - The transmitter was not ready to accept the data
  Example:
    <code>
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte(I2C1, data);
    }
    </code>
  Remarks:
    This routine should be used by both master and slave transmitters.
  *****************************************************************************/

I2C_RESULT I2CSendByte ( I2C * i2cObj, BYTE data )
{
    // Send the byte
    *(i2cObj->registers.I2CxTRN) = data;
    // Check for collisions
	if( *(i2cObj->registers.I2CxSTAT) & (_I2CSTAT_BCL_MASK|_I2CSTAT_IWCOL_MASK) )
    {
		return(I2C_MASTER_BUS_COLLISION); 
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

/*******************************************************************************
  Function:
    UINT32 I2CSetFrequency ( I2C_MODULE id, UINT32 sourceClock, UINT32 i2cClock )
  Summary:
    Routine to set the I2C module's desired SCL clock frequency
  Description:
    This routine allows the caller to set the desired clock frequency for the
    I2C module's SCL line.
  Precondition:
    The source clock's frequency must be operating at the frequency passed in 
    "sourceClock" parameter.
  Parameters:
    id          - Identifies the desired I2C module
    
    sourceClock - Frequency (Hz) of the source clock being provided to the 
                  I2C module
                  
    i2cClock    - Desired frequency of the I2C SCL clock line
  Returns:
    Actual frequency selected
  Example:
    <code>
    actualClock = I2CSetFrequency(I2C1, GetPeripheralClock(), I2C_CLOCK_FREQ);
    if ( abs(actualClock-I2C_CLOCK_FREQ) > I2C_CLOCK_FREQ/10 )
    {
        DBPRINT("I2C1 clock frequency (%d) error exceeds 10%\n", actualClock);
    }
    </code>
  Remarks:
    Actual frequency selected may be slightly different than frequency 
    requested due to truncation error.  Actual frequency observed on the SCL
    line may be lower due to clock stretching.
  *****************************************************************************/

uint32_t I2CSetFrequency ( I2C * i2cObj, uint32_t sourceClock, uint32_t i2cClock )
{
	//i2cObj->registers->I2CxBRGbits->I2CBRG = ( (sourceClock/i2cClock)/2 ) - 2;
	i2cObj->registers.I2CxBRGbits->I2CBRG = ( (sourceClock / (2*i2cClock))-1)-((sourceClock / Tpgob)/2);
    return i2cObj->registers.I2CxBRGbits->I2CBRG;
	//return( ( sourceClock/(i2cObj->registers->I2CxBRGbits->I2CBRG + 2) )/2 );
}


// Private mask definition
#define I2C_ADDRESS_MODE_FLAGS_MASK \
        (I2C_USE_10BIT_ADDRESS|I2C_ENABLE_GENERAL_CALL_ADDRESS|I2C_USE_RESERVED_ADDRESSES)


/*******************************************************************************
  Function:
    void I2CSetSlaveAddress ( I2C_MODULE id, UINT16 address, UINT16 mask, 
                              I2C_ADDRESS_MODE flags )
  Summary:
    Routine to set the value and mode of the slave address(es) in slave mode
  Description:
    This routine sets the slave address and size (7-or-10 bits) to which the 
    module will respond.  It also sets an optional "ignore" mask, allowing the
    module to ignore bits within the address and thus respond to multiple slave
    addresses as well as how reserved addresses are handled.
  Precondition:
  Parameters:
    id      - Identifies the desired I2C module
    
    address - The 7- or 10-bit slave address to which the module will respond.
              (The address should be right-aligned in the 16-bit parameter, 
              without any read/write bit in the 0 position.)
              
    mask    - This parameter identifies bits in the address that are "don't-
              care" bits.  These bits will be ignored when attempting to match
              the address, effectively allowing the module to recognize 
              multiple slave addresses.  (To match an address exactly, this 
              parameter must be zero (0).)
    flags   - This parameter is a bit-wise OR of the values in the 
              I2C_ADDRESS_MODE enumeration.  These enumeration flags can be
              used to select the addressign mode (7- or 10-bit) and define how
              reserved addresses are handled.
  Returns:
    Some modules may not support all addressing modes or the mask feature.  It 
    is safe to pass a zero (0) value for these features if they are not needed.
    If they are not available, the value passed for these features will be 
    ignored.
  Example:
    <code>
    I2CSetSlaveAddress(I2C1, MY_SLAVE_ADDRESS, 0, I2C_USE_10BIT_ADDRESS);
    </code>
  Remarks:
  *****************************************************************************/

/*void I2CSetSlaveAddress ( I2C * i2cObj, uint16_t address, uint16_t mask, I2C_ADDRESS_MODE flags )
{
	*(i2cObj->registers->I2CxADD)       = address;
	*(i2cObj->registers->I2CxMSK)       = mask;
    *(i2cObj->registers->I2CxCONSET)    = I2C_ADDRESS_MODE_FLAGS_MASK &  flags;
    *(i2cObj->registers->I2CxCONCLR)    = I2C_ADDRESS_MODE_FLAGS_MASK & ~flags;
}*/

/*******************************************************************************
  Function:
    void I2CSlaveClockHold ( I2C_MODULE id )
    
  Summary:
    A routine to hold the SCL clock line low
  Description:
    This routine allows an I2C slave or stretch the SCL clock line,
    holding it low to throttle data transfer from a master transmitter.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    None
  Example:
    <code>
    I2CSlaveClockHold(I2C1);
    </code>
  Remarks:
    This routine will cause the SCL line to be forced low, AFTER the currently 
    transferring data byte has been received.
  *****************************************************************************/

void I2CSlaveClockHold ( I2C * i2cObj )
{
	*(i2cObj->registers.I2CxCONCLR) = _I2CCON_SCLREL_MASK;
}

/*******************************************************************************
  Function:
    void I2CSlaveClockRelease ( I2C_MODULE id )
    
  Summary:
    A routine to release a previously-held SCL clock line
  Description:
    This routine allows a slave receiver to release a previously-held SCL clock
    line, allowing it to go high and allowing data transfer to continue.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started.  Also, the SCL clock line should have 
    been previously held (forced low).
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    None
  Example:
    <code>
    I2CSlaveClockRelease(I2C1);
    </code>
  Remarks:
    Calling this routine when the clock has not been held will not cause any 
    problems.
  *****************************************************************************/

void I2CSlaveClockRelease ( I2C * i2cObj )
{
	*(i2cObj->registers.I2CxCONSET) = _I2CCON_SCLREL_MASK;
}

/*******************************************************************************
  Function:
    BOOL I2CSlaveDataReadRequested ( I2C_MODULE id )
  Summary:
    Routine to detect if request from the master was a read or write
  Description:
    This routine identifies if a slave read (transmit) or a slave write 
    (receive) a was requested by the master that addressed the module.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    Boolean identifying if the request was a slave read or write
    * TRUE    - If an external master is requesting data (slave read/transmit)
    * FALSE   - If an external is sending data (slave write/receive)
    
  Example:
    <code>
    if (I2CSlaveDataReadRequested(I2C1))
    {
        if (I2CTransmitterIsReady(I2C1))
        {
            result = I2CSendByte(I2C1, slaveTxData);
        }
    }
    else
    {
        slaveRxData = I2CGetByte(I2C1);
    }
    </code>
  Remarks:
    This routine should be used by both master and slave receivers.
  *****************************************************************************/

BOOL I2CSlaveDataReadRequested (I2C * i2cObj )
{
	return(i2cObj->registers.I2CxSTATbits->R_W);
}

/*******************************************************************************
  Function:
    I2C_RESULT I2CStart( I2C_MODULE id )
  Summary:
    Routine to start a transfer on the I2C bus
    
  Description:
    This routine sends the "start" signal (a falling edge on SDA while SCL is
    high) on the I2C bus, to start a transfer on the I2C bus.
  Precondition:
    The module must have been configured appropriately and enabled and the I2C
    bus must currently be idle.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    None
  Example:
    <code>
    if (I2CBusIdle(I2C1))
    {
        result = I2CStart(I2C1);
    }
    </code>
  Remarks:
    Only an I2C master can start a transfer on the bus.  The bus is considered
    "busy" after a start condition.
  *****************************************************************************/

I2C_RESULT I2CStart( I2C * i2cObj )
{
    //while (!I2CTransmitterIsReady(i2cObj));          // wait for transmitter	
    I2C_RESULT result;
    I2CWaitForIdle(i2cObj);
    while(!I2CConReady(i2cObj));
    i2cObj->registers.I2CxCONbits->SEN = 1;
    // Check for collisions
	if(i2cObj->registers.I2CxSTATbits->BCL)
    {
		result = (I2C_MASTER_BUS_COLLISION); 
    }
	else
    {
		result = (I2C_SUCCESS);
    }
    while (!I2CStartConditionStarted(i2cObj));       // wait for START condition complete
    while (!I2CTransmitterIsReady(i2cObj));          // wait for transmitter	
    return result;
}

/*******************************************************************************
  Function:
    void I2CStop ( I2C_MODULE id )
  Summary:
    Routine to send an I2C Stop condition to terminate a transfer
  Description:
    This routine sends the "stop" signal (a rising edge on SDA while SCL is
    high) on the I2C bus, to end a transfer on the I2C bus.
  Precondition:
    The module must have been configured appropriately, enabled, and a previously
    started transfer must be completed.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    None
  Example:
    <code>
    I2CStop(I2C1);
    </code>
  Remarks:
  *****************************************************************************/

void I2CStop ( I2C * i2cObj )
{
    I2CWaitForIdle(i2cObj);
    I2C_STATUS status;
    // Enable the Stop condition
    //*(i2cObj->registers.I2CxCONSET) = _I2CCON_PEN_MASK;/
    i2cObj->registers.I2CxCONbits->PEN = 1;
    
    do{
        status = I2CGetStatus(i2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(i2cObj));          // wait for transmission ready status
}

/*******************************************************************************
  Function:
    BOOL I2CTransmissionHasCompleted ( I2C_MODULE id )
  Summary:
    Routine to detect if the module has finshed transmitting the most recent 
    byte
  Description:
    This routine determines if the transmitter has finished sending the most
    recently sent byte on the I2C bus.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started, and a data or address byte must have
    been sent.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    Boolean identifying if the transmission has completed
    * TRUE    - If the transmitter has completed sending the data byte
    * FALSE   - If the transmitter is still busy sending the data byte
  Example:
    <code>
    if (I2CTransmissionHasCompleted(I2C1))
    {
        if (I2CByteAcknowledged(I2C1, data))
        {
            // transmission successful
        }
    }
    </code>
  Remarks:
    This routing should be used by both master and slave transmitters.
  *****************************************************************************/

BOOL I2CTransmissionHasCompleted ( I2C * i2cObj)
{
	return(!i2cObj->registers.I2CxSTATbits->TRSTAT);
}

/*******************************************************************************
  Function:
    BOOL I2CTransmitterIsReady ( I2C_MODULE id )
  Summary:
    Routine to detect if the transmitter is ready to accept data to transmit
  Description:
    This routine determines if the transmitter is ready to accept more data to
    be transmitted on the I2C bus.
  Precondition:
    The module must have been configured appropriately and enabled, a transfer
    must have been previously started.
  Parameters:
    id      - Identifies the desired I2C module
  Returns:
    Boolean identifying if the transmitter is ready or not
    * TRUE    - If the transmitter is ready to accept more data
    * FALSE   - If the transmitter is not ready to accept more data
  Example:
    <code>
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte(I2C1, data);
    }
    </code>
  Remarks:
    This routine should be used by both master and slave transmitters.
  *****************************************************************************/
BOOL I2CTransmitterIsReady ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxSTATbits->TBF);
}

/* Returns:
    Boolean identifying if start condition successfully started
    * TRUE    - Started
    * FALSE   - Not started yet */
BOOL I2CStartConditionStarted ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxCONbits->SEN);
}
/* Returns:
    Boolean identifying if restart condition successfully started
    * TRUE    - restarted
    * FALSE   - Not started yet */
BOOL I2CRestartConditionStarted ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxCONbits->RSEN);
}

/* Returns:
    Boolean identifying if start condition successfully started
    * TRUE    - Started
    * FALSE   - Not started yet */
BOOL I2CConReady ( I2C * i2cObj )
{
	return(!i2cObj->registers.I2CxCONbits->SEN & 0x1F);
}

I2C_RESULT I2CSend(I2C * i2cObj, BYTE data, BOOL waitForAck)
{
    I2CWaitForIdle(i2cObj);
    while(!I2CTransmitterIsReady(i2cObj));          // wait for transmitter
    I2C_RESULT result = I2CSendByte(i2cObj, data);
    while(!I2CTransmissionHasCompleted(i2cObj));    // wait for transmission complete
    if (waitForAck) while (!I2CByteWasAcknowledged(i2cObj));
    return result;
}




/* File:   i2c.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: PIC32 I2C communication library
 */ 

// I2C_init() initialises I2C1 at at frequency of [frequency]Hz  
void I2C_Init(I2C * i2cObj, uint32_t sys_frequency, uint32_t frequency)
{
    if (!i2cObj->initialized)
    {
        I2C_AssignRegistersByModule(i2cObj);
        double BRG;
        *i2cObj->registers.I2CxCON = 0; // Turn off I2C2 module
        i2cObj->registers.I2CxCONbits->DISSLW = 1; // Disable slew rate for 100kHz

        BRG = (1 / (2 * (double)frequency)) - 0.000000104;
        BRG *= (sys_frequency / 2) - 2;    

        i2cObj->registers.I2CxBRGbits->I2CBRG = (uint32_t)BRG;     // Set baud rate
        i2cObj->registers.I2CxCONbits->ON = 1;     // Turn on I2C1 module
        i2cObj->initialized = 1;
    }
}
// I2C_wait_for_idle() waits until the I2C peripheral is no longer doing anything  
void I2C_WaitForIdle(I2C * i2cObj)
{ 
    while((*i2cObj->registers.I2CxCON & 0x1F) /*|| (I2C4STAT & 0x04)*/); // Acknowledge sequence not in progress
                                // Receive sequence not in progress
                                // Stop condition not in progress
                                // Repeated Start condition not in progress
                                // Start condition not in progress
    while(I2C4STATbits.TRSTAT); // Bit = 0 ? Master transmit is not in progress
}

// I2C_start() sends a start condition  
void I2C_Start(I2C * i2cObj, uint8_t addr)
{
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->SEN = 1;
    while (i2cObj->registers.I2CxCONbits->SEN == 1);
    if (addr != 0)
        I2C_Write(i2cObj,addr, 0);
}

// I2C_stop() sends a stop condition  
void I2C_Stop(I2C * i2cObj)
{
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->PEN = 1;
}

// I2C_restart() sends a repeated start/restart condition
void I2C_Restart(I2C * i2cObj, uint8_t addr)
{
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->RSEN = 1;
    while (i2cObj->registers.I2CxCONbits->RSEN == 1);
    if (addr != 0)
        I2C_Write(i2cObj,addr, 0);
}

// I2C_ack() sends an ACK condition
void I2C_Ack(I2C * i2cObj)
{
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->ACKDT = 0; // Set hardware to send ACK bit
    i2cObj->registers.I2CxCONbits->ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
    while(i2cObj->registers.I2CxCONbits->ACKEN); // Wait until ACKEN bit is cleared, meaning ACK bit has been sent
}

// I2C_nack() sends a NACK condition
void I2C_Nack(I2C * i2cObj) // Acknowledge Data bit
{
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->ACKDT = 1; // Set hardware to send NACK bit
    i2cObj->registers.I2CxCONbits->ACKEN = 1; // Send NACK bit, will be automatically cleared by hardware when sent  
    while(i2cObj->registers.I2CxCONbits->ACKEN); // Wait until ACKEN bit is cleared, meaning NACK bit has been sent
}

// set wait_ack to 1 to wait for ACK bit or anything else to skip ACK checking 
void I2C_Wait(I2C * i2cObj, _Bool wait_ack)
{
    if (wait_ack) while (i2cObj->registers.I2CxSTATbits->ACKSTAT == 1);
}

// address is I2C slave address, set wait_ack to 1 to wait for ACK bit or anything else to skip ACK checking  
void I2C_Write(I2C * i2cObj, uint8_t addr, _Bool wait_ack)
{
    I2C_WaitForIdle(i2cObj);                  // Wait until I2C bus is idle
    *i2cObj->registers.I2CxTRN = addr;                   // Send slave address with Read/Write bit cleared
    while (i2cObj->registers.I2CxSTATbits->TBF == 1);      // Wait until transmit buffer is empty
    I2C_Wait(i2cObj,wait_ack); // Wait until ACK is received
}

// value is the value of the data we want to send, set ack_nack to 0 to send an ACK or anything else to send a NACK  
void I2C_ReadRef(I2C * i2cObj, uint8_t * value, _Bool ack_nack)
{
    i2cObj->registers.I2CxCONbits->RCEN = 1;               // Receive enable
    while (i2cObj->registers.I2CxCONbits->RCEN);           // Wait until RCEN is cleared (automatic)  
    while (!i2cObj->registers.I2CxSTATbits->RBF);          // Wait until Receive Buffer is Full (RBF flag)  
    *value = *i2cObj->registers.I2CxRCV;                   // Retrieve value from I2C1RCV

    if (!ack_nack)                      // Do we need to send an ACK or a NACK?  
        I2C_Ack(i2cObj);                      // Send ACK  
    else
        I2C_Nack(i2cObj);                     // Send NACK  
}

// set ack_nack to 0 to send an ACK or anything else to send a NACK  
uint8_t I2C_Read(I2C * i2cObj, _Bool ack_nack)
{
    uint8_t data;
    I2C_WaitForIdle(i2cObj);
    i2cObj->registers.I2CxCONbits->RCEN = 1;               // Receive enable
    while (i2cObj->registers.I2CxCONbits->RCEN);           // Wait until RCEN is cleared (automatic)  
    while (!i2cObj->registers.I2CxSTATbits->RBF);           // Wait until Receive Buffer is Full (RBF flag)       
    data = *i2cObj->registers.I2CxRCV;                     // Retrieve value
    I2C_WaitForIdle(i2cObj);
    if (!ack_nack)                      // Do we need to send an ACK or a NACK?  
        I2C_Ack(i2cObj);                      // Send ACK  
    else
        I2C_Nack(i2cObj);   
    return data;
}
