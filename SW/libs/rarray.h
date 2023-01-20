/* 
 * File:   buffer.h
 * Author: orras
 *
 * Created on January 17, 2023, 10:37 PM
 * 
 * Notes:
 *  Max size of array UINT16. Keep that in mind.
 *  Return value -1 means fail or no match.
 * 
 * How to use:
 * 1. Create Rarray instance and call RarrayCreate on it with your internal size limit.
 * 2. Use preferably RarrayPush, RarrayPop, RarrayShift, RarrayUnshift
 */

#ifndef RARRAY_H
#define	RARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RARRAY_SIZE_MAX  1000
    
#ifdef PIC18F47J13
    #undef  RARRAY_SIZE_MAX
    #define RARRAY_SIZE_MAX  50
//#else
//    #define RARRAY_SIZE_MAX  1000
#endif
   
typedef struct
{
    uint16_t    size;
    uint16_t    currentIndex;
    uint8_t     data[RARRAY_SIZE_MAX];
    _Bool       lockActive;
    uint8_t     lockCode;
} Rarray;

Rarray *    RarrayCreate(Rarray * bufOut, uint16_t size);
void        RarrayReset(Rarray * buf);
uint8_t     RarrayGetValueAtIndex(Rarray * buf, uint16_t index);
void        RarraySetValueAtIndex(Rarray * buf, uint16_t index, uint8_t data);
void        RarrayRemoveRange(Rarray * buf, uint16_t startIndex, uint16_t endIndex, Rarray * removedRangeOut);
void        RarrayRemoveRangeLO(Rarray * buf, uint16_t startIndex, uint16_t endIndex, Rarray * removedRangeOut, _Bool supressLock);
void        RarrayCopyRange(Rarray * from, uint16_t startIndex, uint16_t endIndex, Rarray * destination);
void        RarrayCopyRangeLO(Rarray * from, uint16_t startIndex, uint16_t endIndex, Rarray * destination, _Bool supressLock);
void        RarrayPush(Rarray * buf, uint8_t data); // add element to end
uint8_t     RarrayPop(Rarray * buf);                // removes and returns element from end
uint8_t     RarrayShift(Rarray * buf);              // calls RarrayRemoveFirst
void        RarrayUnshift(Rarray * buf, uint8_t data); // calls RarrayAddFront
uint8_t     RarrayRemoveFirst(Rarray * buf);
void        RarrayAddFront(Rarray * buf, uint8_t data);
int32_t     RarrayFindFirst(Rarray * buf, uint8_t data);
int32_t     RarrayFindLast(Rarray * buf, uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* BUFFER_H */

