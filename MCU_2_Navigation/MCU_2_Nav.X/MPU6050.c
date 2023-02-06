///* File:   MPU6050.c
// * Author: Rastislav Oravec
// * Created on Jan 26 2022
// * Version: 1.0 (1/31/2022)
// * 
// * Description: My collection of general use functions
// */ 
//#include "MPU6050.h"
//
//// Startup of MPU6050
//void MPU6050_Init(long sys_frequency, double frequency)
//{
//    // Power-Up Delay & I2C_Init
//    Delay_ms(500);
//    I2C_Init(sys_frequency,frequency);
//    
//    // Setting The Sample (Data) Rate
//    I2CStart(MPU6050_W);
//    I2CWrite(SMPLRT_DIV, 0);
//    I2CWrite(0x07, 0);
//    I2CStop();
//
//    // Setting The Clock Source
//    I2CStart(MPU6050_W);
//    I2CWrite(PWR_MGMT_1, 0);
//    I2CWrite(0x01, 0);
//    I2CStop();
//    
//    // Configure The DLPF
//    I2CStart(MPU6050_W);
//    I2CSendByte(CONFIG, 0);
//    I2CSendByte(0x00, 0);
//    I2CStop();
//
//    // Configure The ACCEL (FSR= +-2g)
//    I2C_Start(MPU6050_W);
//    I2C_Write(ACCEL_CONFIG, 0);
//    //I2C_Write(0x01, 0);   // little move can change everything
//    I2C_Write(0x18, 0);     // requires lots of moving to see results
//    I2C_Stop();
//
//    // Configure The GYRO (FSR= +-2000d/s)
//    I2C_Start(MPU6050_W);
//    I2C_Write(GYRO_CONFIG, 0);
//    I2C_Write(0x18, 0);     // little move can change everything
//    //I2C_Write(0x00, 0);   // requires lots of moving to see results
//    I2C_Stop();
//
//    // Enable Data Ready Interrupts
//    I2C_Start(MPU6050_W);
//    I2C_Write(INT_ENABLE, 0);
//    I2C_Write(0x01, 0);
//    I2C_Stop();
//    Delay_ms(1000);
//}
//// Perform a read from MPU
//// Parameters:
//// int16_t *ax - accel X
//// int16_t *ay - accel Y
//// int16_t *az - accel Z
//// int16_t *gx - gyro X
//// int16_t *gy - gyro Y
//// int16_t *gz - gyro Z
//// int16_t *t - temperature
//void MPU6050_Read(int16_t *ax,  int16_t *ay,  int16_t *az,  int16_t *gx,  int16_t *gy,  int16_t *gz,  int16_t *t)
//{
//    int  Ax, Ay, Az, Gx, Gy, Gz, T;
//    // Prepare For Reading, Starting From ACCEL_XOUT_H
//    I2C_Start(MPU6050_W);
//    I2C_Write(ACCEL_XOUT_H,0);
//    I2C_Stop();
//    //I2C_Restart(MPU6050_R);
//    I2C_Start(MPU6050_R);
//    //I2C_Write(ACCEL_XOUT_H,0);
//    Ax = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    Ay = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    Az = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    T  = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    Gx = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    Gy = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(0);
//    Gz = ((int16_t)I2C_Read(0)<<8) | (int16_t)I2C_Read(1);
//    I2C_Stop();
//    // Set input parameters as output values
//    *ax = Ax;
//    *ay = Ay;
//    *az = Az;
//    *gx = Gx;
//    *gy = Gy;
//    *gz = Gz;
//    *t = T;
//}