/* File:   MPU6050.c
 * Author: Rastislav Oravec
 * Created on Jan 26 2022
 * Version: 1.0 (1/31/2022)
 * 
 * Description: My collection of general use functions
 */ 
#include "MPU6050.h"
//int16_t  Ax, Ay, Az, Gx, Gy, Gz, T;

I2C * pI2cObj = 0;
// Startup of MPU6050
void MPU6050_Init(I2C * i2cObj)
{
    I2C_STATUS status;
    pI2cObj = i2cObj;
    // Setting The Sample (Data) Rate ******************************************/
    while(!I2CBusIsIdle(pI2cObj));                   // wait for bus idle
    while(!I2CConReady(pI2cObj));
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
    //if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, MPU6050_W);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, SMPLRT_DIV) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, SMPLRT_DIV);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, 0x07) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, 0x07);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    // Setting The Clock Source ******************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
//    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, MPU6050_W);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, PWR_MGMT_1) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, PWR_MGMT_1);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    // tu neprejde
    
//    if (I2CSendByte(pI2cObj, 0x01) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, 0x00);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
        // Setting The Clock Source ******************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
//    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, MPU6050_W);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, PWR_MGMT_1) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, PWR_MGMT_2);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, 0x01) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, 0x78);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    // Configure The DLPF ******************************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
//    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, MPU6050_W);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, CONFIG) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, CONFIG);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
//    if (I2CSendByte(pI2cObj, 0x00) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, 0x00);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    // Configure The ACCEL (FSR= +-2g) ******************************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
//    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS) return;
    I2CSendByte(pI2cObj, MPU6050_W);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, ACCEL_CONFIG) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, 0x18) != I2C_SUCCESS);// requires lots of moving to see results
    while (!I2CByteWasAcknowledged(pI2cObj));
    //if (I2CSendByte(pI2cObj, 0x01) != I2C_SUCCESS) return;// little move can change everything
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    // Configure The GYRO (FSR= +-2000d/s) ******************************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, GYRO_CONFIG) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, 0x18) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    // Configure The GYRO (FSR= +-2000d/s) ******************************************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, INT_ENABLE) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, 0x00) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    I2CStop(pI2cObj);
    do{
        status = I2CGetStatus(pI2cObj);
    } while ( !(status & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
}
// Perform a read from MPU
// Parameters:
// int16_t *ax - accel X
// int16_t *ay - accel Y
// int16_t *az - accel Z
// int16_t *gx - gyro X
// int16_t *gy - gyro Y
// int16_t *gz - gyro Z
// int16_t *t - temperature
void MPU6050_Read(int16_t *ax,  int16_t *ay,  int16_t *az,  int16_t *gx,  int16_t *gy,  int16_t *gz,  int16_t *t)
{
    int16_t  Ax, Ay, Az, Gx, Gy, Gz, T;
    I2C_STATUS result;
    /***************************************************************************/
    // // Prepare For Reading, Starting From ACCEL_XOUT_H ******************************/
    I2CStart(pI2cObj);
    while (!I2CStartConditionStarted(pI2cObj));       // wait for START condition complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmitter
    
    if (I2CSendByte(pI2cObj, MPU6050_W) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    if (I2CSendByte(pI2cObj, ACCEL_XOUT_H) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    //if (I2CSendByte(pI2cObj, 0x60) != I2C_SUCCESS);
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    result = I2CRepeatStart(pI2cObj);                // call repeated start
    while (!I2CRestartConditionStarted(pI2cObj));
    
    if (I2CSendByte(pI2cObj, MPU6050_R) != I2C_SUCCESS);
    while (!I2CByteWasAcknowledged(pI2cObj));
    while(!I2CTransmissionHasCompleted(pI2cObj));    // wait for transmission complete
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    
    // Repeated Starts allow a master to change bus direction of addressed slave device 
    // without relinquishing control of the bus
    result = I2CReceiverEnable(pI2cObj, 1);          // wait for receiver
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for I2C ready status
    // Read Ax
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Ax = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Ax = Ax | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Ay
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Ay = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Ay = Ay | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Az
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Az = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Az = Az | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Temperature
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    T = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    T = T | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Gx
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gx = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gx = Gx | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Gy
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gy = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gy = Gy | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    // Read Gz
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gz = (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,1);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    result = I2CReceiverEnable(pI2cObj, 1);          // enable RX
    while(!I2CReceivedDataIsAvailable(pI2cObj));     // wait for data on RX
    Gz = Gz | (int16_t)I2CGetByte(pI2cObj);
    I2CAcknowledgeByte(pI2cObj,0);                   // send ACK
    while(!I2CAcknowledgeHasCompleted(pI2cObj));     // wait for ACK complete
    
    I2CStop(pI2cObj);
    do{
        result = I2CGetStatus(pI2cObj);
    } while ( !(result & I2C_STOP) );  
    while(!I2CTransmitterIsReady(pI2cObj));          // wait for transmission ready status
    /***************************************************************************/
    *ax = Ax;
    *ay = Ay;
    *az = Az;
    *gx = Gx;
    *gy = Gy;
    *gz = Gz;
    *t = T;
}