/* 
 * File:   gps_neo.h
 * Author: orras
 *
 * Created on February 15, 2023, 11:33 PM
 */

#ifndef GPS_NEO_H
#define	GPS_NEO_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define GPS_PARSE_DATA              0

// MINIMUM ALLOWED LENGTH IS 2!!! Always count with 0x00 at the end of a string.
#define GPS_MAX_SIZE_SENTENCE       6
#define GPS_MAX_SIZE_TIME           11
#define GPS_MAX_SIZE_DATE           7
#define GPS_MAX_SIZE_SPEED          6
#define GPS_MAX_SIZE_COURSE         6
#define GPS_MAX_SIZE_SATELLITES     3
#define GPS_MAX_SIZE_LAT            12
#define GPS_MAX_SIZE_LON            12
#define GPS_MAX_SIZE_ALT            7
#define GPS_MAX_SIZE_BUFFER         150

#define GPS_POSITION_SENTENCE       0
#define GPS_POSITION_TIME           1
#define GPS_POSITION_DATE           9
#define GPS_POSITION_SPEED          7
#define GPS_POSITION_COURSE         8
#define GPS_POSITION_LAT            3
#define GPS_POSITION_LAT_DIR        4
#define GPS_POSITION_LON            5
#define GPS_POSITION_LON_DIR        6
#define GPS_POSITION_SATTELITES     7
#define GPS_POSITION_ALT            9

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum {NONE=0, GPRMC, GPGGA, OTHER} GPS_SentenceType;

typedef struct
{
    bool startByteDetected;
    bool latDir;
    bool lonDir;
    GPS_SentenceType sentenceType;
    uint8_t sentence[GPS_MAX_SIZE_SENTENCE];
    uint8_t rawTime[GPS_MAX_SIZE_TIME];
    uint8_t rawDate[GPS_MAX_SIZE_DATE];
    uint8_t rawSpeed[GPS_MAX_SIZE_SPEED];
    uint8_t rawCourse[GPS_MAX_SIZE_COURSE];
    uint8_t rawSatellites[GPS_MAX_SIZE_SATELLITES];
    uint8_t rawLatitude[GPS_MAX_SIZE_LAT];
    uint8_t rawLongitude[GPS_MAX_SIZE_LON];
    uint8_t rawAltitude[GPS_MAX_SIZE_ALT];
    uint8_t buffer[GPS_MAX_SIZE_BUFFER];
    uint8_t index;
    bool decodingInProgress;
} GPS_Buffer;

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    float   latitude;
    bool    latDir;
    float   longitude;
    bool    lonDir;
    float   altitude;
    uint8_t satellites;
    float   speed;
    float   course;
    uint8_t rawBuffer[GPS_MAX_SIZE_BUFFER];
    
} GPS_Data;
extern GPS_Data GPS_DATA;

void GPS_Init();
uint8_t GPS_Read(uint8_t data); // call from interrupt
void GPS_DecodeBuffer(GPS_Buffer * buffer);
uint8_t GPS_SetDataFromBuffer(GPS_Data * dataOut, GPS_Buffer * buffer);
uint8_t GPS_CopyRawDataCS
(       uint8_t * out, 
        uint8_t outArrLimit, 
        uint8_t * buffer, 
        uint8_t bufferSize, 
        uint8_t startComma, 
        uint8_t excludeChar
);
uint8_t GPS_GetDoubleDigitFromChars(uint8_t i, uint8_t j);

#ifdef	__cplusplus
}
#endif

#endif	/* GPS_NEO_H */

uint8_t GPSRead();
uint8_t GPSSecond();
uint8_t GPSMinute();
uint8_t GPSHour();
uint8_t GPSDay();
uint8_t GPSMonth();
uint8_t GPSYear();
float Latitude();
float Longitude();
float Latitude();
float Altitude();
uint8_t Satellites();
float Speed();
float Course();