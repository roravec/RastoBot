#include "gps_neo.h"

/******************************************************************************/
static float parse_rawDegree(uint8_t *term_) {
  uint8_t i = 0;
  uint16_t i_part = 0;
  uint32_t multiplier = 1;
  uint32_t float_part = 0;

  while(term_[i] != '.' && term_[i] >= '0' && term_[i] <= '9') {
    i_part = i_part * 10 + (term_[i] - '0') ;
    i += 1;
  }

  i += 1;
  while(term_[i] != '\0' && term_[i] >= '0' && term_[i] <= '9'){
    float_part = float_part * 10 + (term_[i] - '0') ;
    multiplier *= 10;
    i++;
  }
  float_part += multiplier * (i_part % 100);
  i_part /= 100;
  return ((float)float_part / (multiplier * 60)) + i_part;
}

static uint8_t GetSatellitesFromStr(uint8_t * satellitesStr) {
  uint8_t sat_n = 0, i = 0;
  while(satellitesStr[i] != '\0' && satellitesStr[i] >= '0' && satellitesStr[i] <= '9'){
    sat_n = sat_n * 10 + satellitesStr[i] - '0';
    i++ ;
  }
  return sat_n;
}

static float str_to_float(uint8_t *str_) {
  uint8_t i = 0;
  uint16_t i_part = 0;
  uint32_t multiplier = 1;
  uint32_t float_part = 0;

  while(str_[i] != '.' && str_[i] >= '0' && str_[i] <= '9') {
    i_part = i_part * 10 + (str_[i] - '0') ;
    i += 1;
  }

  i += 1;
  while(str_[i] != '\0' && str_[i] >= '0' && str_[i] <= '9') {
    float_part = float_part * 10 + (str_[i] - '0') ;
    multiplier *= 10;
    i++;
  }
  return (float)float_part / multiplier + i_part;
}
/******************************************************************************/

GPS_Buffer gpsBuffer;
GPS_Data GPS_DATA;

void GPS_Init()
{
    gpsBuffer.decodingInProgress = 0;
    gpsBuffer.startByteDetected = 0;
    gpsBuffer.index = 0;
    gpsBuffer.sentenceType = NONE;
}

uint8_t GPS_Read(uint8_t data)
{
    if (data == '$') // start byte
    {
        gpsBuffer.startByteDetected = 1;    // string receiving has started
        gpsBuffer.index = 0;
    }
    else if (data == '\r' && gpsBuffer.startByteDetected) // end of string - decode data
    {
        gpsBuffer.startByteDetected = 0;    // reset start byte detected
        gpsBuffer.index = 0;                // reset index
        if (gpsBuffer.decodingInProgress)   // decoding is already ind progress - SKIP
        {}
        else
        {
            GPS_DecodeBuffer(&gpsBuffer);
            GPS_SetDataFromBuffer(&GPS_DATA, &gpsBuffer);
            return 1;
        }
    }
    if (gpsBuffer.startByteDetected && gpsBuffer.index < GPS_MAX_SIZE_BUFFER) // string data receiving, copy data
    {
        gpsBuffer.buffer[gpsBuffer.index++] = data; // copy received data to buffer
    }
    return 0;
}

void GPS_DecodeBuffer(GPS_Buffer * buffer)
{
    gpsBuffer.decodingInProgress = 1; // start of decoding
    GPS_CopyRawDataCS(buffer->sentence, GPS_MAX_SIZE_SENTENCE,buffer->buffer,GPS_MAX_SIZE_BUFFER,0,'$'); // get sentence type
    if      (buffer->sentence[2]=='R' && buffer->sentence[3]=='M' && buffer->sentence[4]=='C') 
        buffer->sentenceType = GPRMC;
    else if (buffer->sentence[2]=='G' && buffer->sentence[3]=='G' && buffer->sentence[4]=='A') 
        buffer->sentenceType = GPGGA;
    else 
        buffer->sentenceType = OTHER;
    
    if (buffer->sentenceType == GPGGA) // decode GPGGA message **************************
    {
        GPS_CopyRawDataCS(buffer->rawSatellites, GPS_MAX_SIZE_SATELLITES,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_SATTELITES,0x00);
        GPS_CopyRawDataCS(buffer->rawAltitude, GPS_MAX_SIZE_ALT,buffer->buffer,
                GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_ALT,0x00);
    }
    else if (buffer->sentenceType == GPRMC) // decode GPRMC message *********************
    {
        uint8_t temp[3];
        GPS_CopyRawDataCS(buffer->rawTime, GPS_MAX_SIZE_TIME,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_TIME,0x00);
        GPS_CopyRawDataCS(buffer->rawDate, GPS_MAX_SIZE_DATE,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_DATE,0x00);
        GPS_CopyRawDataCS(buffer->rawSpeed, GPS_MAX_SIZE_SPEED,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_SPEED,0x00);
        GPS_CopyRawDataCS(buffer->rawCourse, GPS_MAX_SIZE_COURSE,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_COURSE,0x00);
        GPS_CopyRawDataCS(buffer->rawLatitude, GPS_MAX_SIZE_LAT,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_LAT,0x00);
        GPS_CopyRawDataCS(temp, 3,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_LAT_DIR,0x00);
        if (temp[0] == 'N') buffer->latDir = 1; else buffer->latDir = 0;
        GPS_CopyRawDataCS(buffer->rawLongitude, GPS_MAX_SIZE_LON,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_LON,0x00);
        GPS_CopyRawDataCS(temp, 3,
                buffer->buffer,GPS_MAX_SIZE_BUFFER,
                GPS_POSITION_LON_DIR,0x00);
        if (temp[0] == 'E') buffer->lonDir = 1; else buffer->lonDir = 0;
    }
    gpsBuffer.decodingInProgress = 0; // end of decoding
}

uint8_t GPS_SetDataFromBuffer(GPS_Data * dataOut, GPS_Buffer * buffer)
{
    if (GPS_PARSE_DATA)
    {
        dataOut->seconds =  GPS_GetDoubleDigitFromChars(buffer->rawTime[4],buffer->rawTime[5]);
        dataOut->minutes =  GPS_GetDoubleDigitFromChars(buffer->rawTime[2],buffer->rawTime[3]);
        dataOut->hours =    GPS_GetDoubleDigitFromChars(buffer->rawTime[0],buffer->rawTime[1]);
        dataOut->day =      GPS_GetDoubleDigitFromChars(buffer->rawDate[0],buffer->rawDate[1]);
        dataOut->month =    GPS_GetDoubleDigitFromChars(buffer->rawDate[2],buffer->rawDate[3]);
        dataOut->year =     GPS_GetDoubleDigitFromChars(buffer->rawDate[4],buffer->rawDate[5]);
        dataOut->latDir = buffer->latDir;
        dataOut->lonDir = buffer->lonDir;
        int8_t dir = (buffer->latDir > 0 ? 1 : -1);
        dataOut->latitude = parse_rawDegree(buffer->rawLatitude) * dir;
        dir = (buffer->lonDir > 0 ? 1 : -1);
        dataOut->longitude = parse_rawDegree(buffer->rawLongitude) * dir;
        dataOut->altitude = str_to_float(buffer->rawAltitude);
        dataOut->speed =    str_to_float(buffer->rawSpeed) * 1.852;
        dataOut->course =   str_to_float(buffer->rawCourse);
        dataOut->satellites = GetSatellitesFromStr(buffer->rawSatellites);
    }
    memcpy(dataOut->rawBuffer, buffer->buffer, GPS_MAX_SIZE_BUFFER);
}

uint8_t GPS_CopyRawDataCS(uint8_t * out, uint8_t outArrLimit, uint8_t * buffer, uint8_t bufferSize, uint8_t startComma, uint8_t excludeChar)
{
    uint8_t outIndex = 0;
    if (outArrLimit < 2) // invalid out array size
        return 0;
    for (uint8_t i=0,currentComma=0; i<bufferSize ;i++)
    {
        if (buffer[i] == ',') currentComma++;
        if (buffer[i] == excludeChar) continue;
        if (currentComma == startComma && outIndex < outArrLimit-1)
        {
            out[outIndex++] = buffer[i];
            out[outIndex++] = 0x00;
        }
    }
    return outIndex;
}

uint8_t GPS_GetDoubleDigitFromChars(uint8_t i, uint8_t j){
  if(i >= '0' && i <= '9' && j >= '0' && j <= '9')
    return (i - '0') * 10 + (j - '0');
  else
    return 0;
}