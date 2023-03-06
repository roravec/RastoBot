#include "hwinterface.h"

void HwInterface_Init(void)
{
    UART_MCU1_RX_TRIS = 1;
    UART_MCU1_TX_TRIS = 0;
    UART_MCU3_RX_TRIS = 0;
    UART_MCU3_TX_TRIS = 1;
    UART_MCU0_RX_TRIS = 0;
    UART_MCU0_TX_TRIS = 1;
    UART_GPS_RX_TRIS = 0;
    UART_GPS_TX_TRIS = 1;
    UART_LIDAR_RX_TRIS = 0;
    UART_LIDAR_TX_TRIS = 1;
    
    LED_0_TRIS = 0;
    LED_1_TRIS = 0;
    LED_2_TRIS = 0;
    LED_3_TRIS = 0;
    
    INDUCTION_SENSE_TRIS = 1;
    
    LIDAR_ENABLE_TRIS = 0;
    
    I2C_SDA_TRIS = 0;
    I2C_SCL_TRIS = 0;
//    I2C_SDA_LAT = 1;
//    I2C_SCL_LAT = 1;
}
