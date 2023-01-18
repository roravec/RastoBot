#include "dht11.h"

void DHT11_Start(uint8_t module)
{
    DHT11_ChangeDirection(module, 0);   // set module as output
    DHT11_SetLatch(module, 0);          // send low pulse of min. 18 ms width
    __delay_ms(20);
    DHT11_SetLatch(module, 1);          // send HIGH pulse of min. 20 ms width
    __delay_us(10);
    DHT11_ChangeDirection(module, 1);   // set module as input
}

_Bool DHT11_CheckResponse(uint8_t module)
{
    TMR1H = 0;  // reset Timer1
    TMR1L = 0;
    TMR1ON = 1; // enable Timer1 module
    while(!DHT11_GetData(module) && TMR1L < 100);  // wait until DHT11_PIN becomes high (checking of 80µs low time response)
 
    if(TMR1L > 99)  // if response time > 99µS  ==> Response error
        return 0;   // return 0 (Device has a problem with response)

    else
    {
        TMR1H = 0;  // reset Timer1
        TMR1L = 0;

        while(DHT11_GetData(module) && TMR1L < 100); // wait until DHT11_PIN becomes low (checking of 80µs high time response)

        if(TMR1L > 99)  // if response time > 99µS  ==> Response error
          return 0; // return 0 (Device has a problem with response)

        else
          return 1; // return 1 (response OK)
    }
}

uint8_t DHT11_GetData(uint8_t module)
{
    switch (module)
    {
        case 0: return DHT11_MODULE_0_PORT; 
        case 1: return DHT11_MODULE_1_PORT; 
        case 2: return DHT11_MODULE_2_PORT; 
        case 3: return DHT11_MODULE_3_PORT; 
        default: return 0; 
    }
}

void DHT11_ChangeDirection(uint8_t module, _Bool direction)
{
    switch (module)
    {
        case 0: DHT11_MODULE_0_TRIS = direction;
                break;
        case 1: DHT11_MODULE_1_TRIS = direction; 
                break;
        case 2: DHT11_MODULE_2_TRIS = direction; 
                break;
        case 3: DHT11_MODULE_3_TRIS = direction; 
                break;
        default: break; 
    }
}

void DHT11_SetLatch(uint8_t module, _Bool latVal)
{
    switch (module)
    {
        case 0: DHT11_MODULE_0_LAT = latVal;
                break;
        case 1: DHT11_MODULE_1_LAT = latVal; 
                break;
        case 2: DHT11_MODULE_2_LAT = latVal; 
                break;
        case 3: DHT11_MODULE_3_LAT = latVal; 
                break;
        default: break; 
    }
}

_Bool DHT11_ReadSensorData(uint8_t module, int8_t * dataOut)
{
    *dataOut = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        TMR1H = 0;             // reset Timer1
        TMR1L = 0;
        while(!DHT11_GetData(module))      // wait until DHT11_PIN becomes high
        {
            if(TMR1L > 100) {    // if low time > 100  ==>  Time out error (Normally it takes 50µs)
                return 1;
            }
        }
        TMR1H = 0;             // reset Timer1
        TMR1L = 0;
        while(DHT11_GetData(module))       // wait until DHT11_PIN becomes low
        {
            if(TMR1L > 100) {    // if high time > 100  ==>  Time out error (Normally it takes 26-28µs for 0 and 70µs for 1)
                return 1;          // return 1 (timeout error)
            }
        }

         if(TMR1L > 50)                  // if high time > 50  ==>  Sensor sent 1
            *dataOut |= (1 << (7 - i));  // set bit (7 - i)
    }
    return 0;                          // return 0 (data read OK)
}

_Bool DHT11_GetSensorData(uint8_t module, DHT11_SensorData * dataOut)
{
    int8_t T_Byte1=0, T_Byte2=0, RH_Byte1=0, RH_Byte2=0, CheckSum=0;
    DHT11_Start(module);
    if (DHT11_CheckResponse(module))
    {
        if(
                DHT11_ReadSensorData(module, &RH_Byte1) || 
                DHT11_ReadSensorData(module, &RH_Byte2) || 
                DHT11_ReadSensorData(module, &T_Byte1) || 
                DHT11_ReadSensorData(module, &T_Byte2) || 
                DHT11_ReadSensorData(module, &CheckSum)
                ) // TIMEOUT IF CONDITION IS MET
        {
            // TIMEOUT
            return 0;
        }
        else // data OK
        {
            if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))// if there is no checksum error
            {
                // DATA OK
                dataOut->humidity = RH_Byte1;
                dataOut->temperature = T_Byte1;
                return 1;
            }
        }
    }
    else // error timeout
    {
        // TIMEOUT
        return 0;
    }
    return 0;
}