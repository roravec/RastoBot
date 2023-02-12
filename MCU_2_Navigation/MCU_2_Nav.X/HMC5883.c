#include "HMC5883.h"

static double PI = 3.14159265359;
static I2C * pI2cObj = 0;
static bool _initialized = false;
static bool _calibrationUse = false;
static int16_t _vRaw[3] = {0,0,0};
static int16_t _vHistory[10][3];
static int16_t _vScan = 0;
static int32_t _vTotals[3] = {0,0,0};
static int16_t _vSmooth[3] = {0,0,0};
static int16_t _vCalibration[3][2];
static int16_t _vCalibrated[3];
static uint8_t _bearings[16][3] =  {
    {' ', ' ', 'N'},
    {'N', 'N', 'E'},
    {' ', 'N', 'E'},
    {'E', 'N', 'E'},
    {' ', ' ', 'E'},
    {'E', 'S', 'E'},
    {' ', 'S', 'E'},
    {'S', 'S', 'E'},
    {' ', ' ', 'S'},
    {'S', 'S', 'W'},
    {' ', 'S', 'W'},
    {'W', 'S', 'W'},
    {' ', ' ', 'W'},
    {'W', 'N', 'W'},
    {' ', 'N', 'W'},
    {'N', 'N', 'W'},
};

static void HMC5883_WriteReg(uint8_t regAddr, uint8_t value);
static int8_t HMC5883_Get(uint8_t index);
static void HMC5883_ApplyCalibration();
static void HMC5883_Smoothing();

void HMC5883_Init(I2C * i2cObj)
{
    pI2cObj = i2cObj;
    _initialized = true;
    //HMC5883_WriteReg(0x0B,0x01);   // soft reset period. It is recommended that the register 0BH is written by 0x01
	//HMC5883_SetMode(0x01,0x0C,0x10,0x00);
    //HMC5883_WriteReg(0x0A, 0x41); // disable interrupt pin, enable pointer rollover
    HMC5883_WriteReg(0x00,0x78);
    HMC5883_WriteReg(0x01,0x00); // highest resolution
    HMC5883_WriteReg(0x02,0x00); // continuous measurement
}

/*
 SET CALIBRATION
	Set calibration values for more accurate readings
 */
void HMC5883_SetCalibration(int16_t x_min, int16_t x_max, int16_t y_min, int16_t y_max, int16_t z_min, int16_t z_max)
{
    _calibrationUse = true;
	_vCalibration[0][0] = x_min;
	_vCalibration[0][1] = x_max;
	_vCalibration[1][0] = y_min;
	_vCalibration[1][1] = y_max;
	_vCalibration[2][0] = z_min;
	_vCalibration[2][1] = z_max;
}

void HMC5883_Read()
{
    if (_initialized)
    {
        I2C_Start(pI2cObj,HMC5883_ADDRESS_W);
        I2C_Write(pI2cObj,HMC5883_READ_FROM_ADDRESS,0);
        I2C_Stop(pI2cObj);
        //I2C_Restart(pI2cObj,HMC5883_ADDRESS_R);
        I2C_Start(pI2cObj,HMC5883_ADDRESS_R);
        
        _vRaw[0] = ((int16_t)I2C_Read(pI2cObj,0)<<8) | (int16_t)I2C_Read(pI2cObj,0);
        _vRaw[1] = ((int16_t)I2C_Read(pI2cObj,0)<<8) | (int16_t)I2C_Read(pI2cObj,0);
        _vRaw[2] = ((int16_t)I2C_Read(pI2cObj,0)<<8) | (int16_t)I2C_Read(pI2cObj,1);
//        (int16_t)I2C_Read(pI2cObj,1);
        
        if ( _calibrationUse ) {
			HMC5883_ApplyCalibration();
		}
		
		if ( HMC5883_SMOOTHING ) {
			HMC5883_Smoothing();
		}
    }
}

int16_t HMC5883_GetX()
{
    return HMC5883_Get(0);
}

int16_t HMC5883_GetY()
{
    return HMC5883_Get(1);
}

int16_t HMC5883_GetZ()
{
    return HMC5883_Get(2);
}

int16_t HMC5883_GetAzimuth()
{
    int16_t a = atan2( (double)HMC5883_GetY(), (double)HMC5883_GetX() ) * 180.0 / PI;
	return a < 0 ? 360 + a : a;
}

void    HMC5883_SetMode(uint8_t mode, uint8_t odr, uint8_t rng, uint8_t osr)
{
    HMC5883_WriteReg(0x09,mode|odr|rng|osr);
}

void    HMC5883_ResetChip()
{
    HMC5883_WriteReg(0x0A,0x80);
}

static void HMC5883_WriteReg(uint8_t regAddr, uint8_t value)
{
    if (_initialized)
    {
        I2C_Start(pI2cObj,HMC5883_ADDRESS_W);
        I2C_Write(pI2cObj,regAddr, 0);
        I2C_Write(pI2cObj,value, 0);
        I2C_Stop(pI2cObj);
    }
}

static int8_t HMC5883_Get(uint8_t index)
{
    if ( HMC5883_SMOOTHING ) 
		return _vSmooth[index];
	
	if ( _calibrationUse )
		return _vCalibrated[index];

	return _vRaw[index];
}

/* APPLY CALIBRATION
	This function uses the calibration data provided via @see setCalibration() to calculate more
	accurate readings
 */
static void HMC5883_ApplyCalibration()
{
    int16_t x_offset = (_vCalibration[0][0] + _vCalibration[0][1])/2;
	int16_t y_offset = (_vCalibration[1][0] + _vCalibration[1][1])/2;
	int16_t z_offset = (_vCalibration[2][0] + _vCalibration[2][1])/2;
	int16_t x_avg_delta = (_vCalibration[0][1] - _vCalibration[0][0])/2;
	int16_t y_avg_delta = (_vCalibration[1][1] - _vCalibration[1][0])/2;
	int16_t z_avg_delta = (_vCalibration[2][1] - _vCalibration[2][0])/2;

	int16_t avg_delta = (x_avg_delta + y_avg_delta + z_avg_delta) / 3;

	float x_scale = (float)avg_delta / x_avg_delta;
	float y_scale = (float)avg_delta / y_avg_delta;
	float z_scale = (float)avg_delta / z_avg_delta;

	_vCalibrated[0] = (_vRaw[0] - x_offset) * x_scale;
	_vCalibrated[1] = (_vRaw[1] - y_offset) * y_scale;
	_vCalibrated[2] = (_vRaw[2] - z_offset) * z_scale;
}

/*
 SMOOTH OUTPUT
	This function smooths the output for the XYZ axis. Depending on the options set in
	@see setSmoothing(), we can run multiple methods of smoothing the sensor readings.
	
	First we store (n) samples of sensor readings for each axis and store them in a rolling array.
	As each new sensor reading comes in we replace it with a new reading. Then we average the total
	of all (n) readings.
	
	Advanced Smoothing
	If you turn advanced smoothing on, we will select the min and max values from our array
	of (n) samples. We then subtract both the min and max from the total and average the total of all
	(n - 2) readings.
	
	NOTE: This function does several calculations and can cause your sketch to run slower.
 */
static void HMC5883_Smoothing()
{
    uint8_t max = 0;
	uint8_t min = 0;
	
	if ( _vScan > HMC5883_SMOOTHING_STEPS - 1 ) { _vScan = 0; }
	
	for ( uint8_t i = 0; i < 3; i++ ) {
		if ( _vTotals[i] != 0 ) {
			_vTotals[i] = _vTotals[i] - _vHistory[_vScan][i];
		}
		_vHistory[_vScan][i] = ( _calibrationUse ) ? _vCalibrated[i] : _vRaw[i];
		_vTotals[i] = _vTotals[i] + _vHistory[_vScan][i];
		
		if ( HMC5883_ADVANCED_SMOOTHING ) {
			max = 0;
			for (uint16_t j = 0; j < HMC5883_SMOOTHING_STEPS - 1; j++) {
				max = ( _vHistory[j][i] > _vHistory[max][i] ) ? j : max;
			}
			
			min = 0;
			for (uint16_t k = 0; k < HMC5883_SMOOTHING_STEPS - 1; k++) {
				min = ( _vHistory[k][i] < _vHistory[min][i] ) ? k : min;
			}
					
			_vSmooth[i] = ( _vTotals[i] - (_vHistory[max][i] + _vHistory[min][i]) ) / (HMC5883_SMOOTHING_STEPS - 2);
		} else {
			_vSmooth[i] = _vTotals[i]  / HMC5883_SMOOTHING_STEPS;
		}
	}
	
	_vScan++;
}
