#include "hwinterface.h"

void HwInterface_Init(void)
{
    UART_RX_TRIS = 1;
    UART_TX_TRIS = 0;
    POWER_OUTPUT_0_TRIS = 0;
    POWER_OUTPUT_1_TRIS = 0;
    POWER_OUTPUT_2_TRIS = 0;
    POWER_OUTPUT_3_TRIS = 0;
    POWER_OUTPUT_4_TRIS = 0;
    LED_0_TRIS = 0;
    LED_1_TRIS = 0;
    LED_2_TRIS = 0;
    BUZZER_TRIS = 0;
    TEMP_SENSOR_0_TRIS = 0;
    TEMP_SENSOR_1_TRIS = 0;
    TEMP_SENSOR_2_TRIS = 0;
    TEMP_SENSOR_3_TRIS = 0;
    EXT_INPUT_SENSE_TRIS = 1;
    EXT_INPUT_ENABLE_TRIS = 0;
    BATTERY_STATUS_TRIS = 1;
    CURRENT_SENSOR_0_TRIS = 1;
    CURRENT_SENSOR_1_TRIS = 1;
    CURRENT_SENSOR_2_TRIS = 1;
    CURRENT_SENSOR_3_TRIS = 1;
    RAIN_SENSOR_TRIS = 1;
    LIGHT_SENSOR_TRIS = 1;
    TILT_SENSOR_TRIS = 1;
    
    POWER_OUTPUT_0_LAT = 0;
    POWER_OUTPUT_1_LAT = 0;
    POWER_OUTPUT_2_LAT = 0;
    POWER_OUTPUT_3_LAT = 0;
    POWER_OUTPUT_4_LAT = 0;
    LED_0_LAT = 0;
    LED_1_LAT = 0;
    LED_2_LAT = 0;
    BUZZER_LAT = 0;
    TEMP_SENSOR_0_LAT = 0;
    TEMP_SENSOR_1_LAT = 0;
    TEMP_SENSOR_2_LAT = 0;
    TEMP_SENSOR_3_LAT = 0;
    EXT_INPUT_ENABLE_LAT = 0;
}
