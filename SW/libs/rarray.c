#include "rarray.h"
/* Statics */
static void        RarrayLock(Rarray * buf);
static void        RarrayUnlock(Rarray * buf);

//Rarray * RarrayCreate(Rarray * bufOut, uint16_t size)
//{
//    bufOut->size = (size<=RARRAY_SIZE_MAX) ? size : RARRAY_SIZE_MAX;
//    bufOut->lockActive = 0;
//    bufOut->lockCode = 0;
//    RarrayReset(bufOut);
//    return bufOut;
//}

Rarray *    RarrayCreate(Rarray * bufOut, uint8_t * data, uint16_t size)
{
    bufOut->size = (size<=RARRAY_SIZE_MAX) ? size : RARRAY_SIZE_MAX;
    bufOut->data = data;
    bufOut->lockActive = 0;
    bufOut->lockCode = 0;
    bufOut->created = 1; // array was successfully
    RarrayReset(bufOut);
    return bufOut;
}

void RarrayReset(Rarray * buf)
{
    RarrayLock(buf);        // lock buffer for reset
    buf->currentIndex = 0;
    memset(buf->data,0x00,buf->size);// clear data
    RarrayUnlock(buf);      // unlock buffer
}

uint8_t RarrayGetValueAtIndex(Rarray * buf, uint16_t index)
{
    uint8_t retVal = 0;
    RarrayLock(buf);        // lock buffer for reading
    if (index < buf->currentIndex)
        retVal = buf->data[index];
    RarrayUnlock(buf);      // unlock buffer
    return retVal;
}
void RarraySetValueAtIndex(Rarray * buf, uint16_t index, uint8_t data)
{
    if (index >= buf->size)
        return;
    RarrayLock(buf);    // lock buffer
    buf->data[index] = data;
    RarrayUnlock(buf);  // unlock buffer
}

/* Start at startIndex, stops before endIndex */
void RarrayRemoveRange(Rarray * buf, uint16_t startIndex, uint16_t endIndex, Rarray * removedRangeOut)
{
    RarrayRemoveRangeLO(buf, startIndex, endIndex, removedRangeOut, 0);
}
void RarrayRemoveRangeLO(Rarray * buf, uint16_t startIndex, uint16_t endIndex, Rarray * removedRangeOut, _Bool supressLock)
{
    if (startIndex >= endIndex || endIndex > buf->currentIndex)             // fail condition
        return;
    uint16_t dif = endIndex - startIndex;   // get difference
    if (removedRangeOut != 0)   // copy range only if it is requested
        RarrayCopyRangeLO(buf, startIndex, endIndex, removedRangeOut,supressLock); // copy range before removal
    if (!supressLock)
        RarrayLock(buf);                        // lock buffer for writing
    for (uint16_t i = startIndex ;i<buf->size-dif; i++)
    {
        buf->data[i] = buf->data[i+dif];    // copy data from endIndex to startIndex
    }
    for (uint16_t i = buf->size-dif ;i<buf->size; i++)
    {
        buf->data[i] = 0x00;                //  rewrite all copied data with 0x00
    }
    buf->currentIndex -= dif;               // correct current index by difference
    if (!supressLock)
        RarrayUnlock(buf);                      // unlock buffer
}
void RarrayCopyRange(Rarray * from, uint16_t startIndex, uint16_t endIndex, Rarray * destination)
{
    RarrayCopyRangeLO(from, startIndex, endIndex, destination, 0);
}
void RarrayCopyRangeLO(Rarray * from, uint16_t startIndex, uint16_t endIndex, Rarray * destination, _Bool supressLock)
{
    if (from == 0 || destination == 0)      // invalid array pointers
        return;
    uint16_t dif = endIndex - startIndex;   // get difference
    if (dif > destination->size) // destination array is smaller than requested range to copy
        return;
    if (!supressLock)
    {
        RarrayLock(from);                       // lock
        RarrayLock(destination);                // lock
    }
    for (uint16_t i = startIndex, j=0;i<from->size-dif; i++, j++)
    {
        destination->data[j] = from->data[i];    // copy data from endIndex to startIndex
    }
    if (!supressLock)
    {
        RarrayUnlock(destination);                      // unlock buffer
        RarrayUnlock(from);                             // unlock buffer
    }
}

// adds value to the end of the array
void RarrayPush(Rarray * buf, uint8_t data)
{
    RarrayLock(buf);        // lock buffer for writing
    if (buf->currentIndex < buf->size)
        buf->data[buf->currentIndex++] = data;
    RarrayUnlock(buf);       // unlock buffer
}
// removes and returns last value of the array
uint8_t RarrayPop(Rarray * buf)
{
    uint8_t retVal = 0;
    RarrayLock(buf);        // lock buffer for writing
    if (buf->currentIndex < buf->size && buf->currentIndex > 0)
        retVal = buf->data[--buf->currentIndex];
    RarrayUnlock(buf);       // unlock buffer
    return retVal;
}
// removes and returns the first element from the array.
uint8_t RarrayShift(Rarray * buf)
{
    return RarrayRemoveFirst(buf);
}
uint8_t RarrayRemoveFirst(Rarray * buf)
{
    uint8_t retVal = 0;
    if (buf->currentIndex == 0)
        return retVal;
    retVal = RarrayGetValueAtIndex(buf, 0);
    RarrayRemoveRange(buf, 0,1,0);
    return retVal;
}
// Using unshift() we can add elements to the front of an array.
void RarrayUnshift(Rarray * buf, uint8_t data)
{
    RarrayAddFront(buf, data);
}
void RarrayAddFront(Rarray * buf, uint8_t data)
{
    if (buf->size <= 1)
        return;     // invalid array
    // skip last index and start from last-1
    RarrayLock(buf);       // lock buffer
    for (uint16_t i=buf->size-1; i>0;i--)
    {
        uint16_t indexFrom = i-1;
        uint16_t indexTo = i;
        buf->data[indexTo] = buf->data[indexFrom];
    }
    if (buf->currentIndex < buf->size)
        buf->currentIndex++;
    buf->data[0] = data;
    RarrayUnlock(buf);       // unlock buffer
}

int32_t    RarrayFindFirst(Rarray * buf, uint8_t data)
{
    int32_t retIndex = -1;
    RarrayLock(buf);       // lock buffer
    for (uint16_t i=0; i<buf->size ;i++)
    {
        if (buf->data[i] == data)
        {
            retIndex = i;
            break;
        }
    }
    RarrayUnlock(buf);       // unlock buffer
    return retIndex;
}
int32_t    RarrayFindLast(Rarray * buf, uint8_t data)
{
    int32_t retIndex = -1;
    RarrayLock(buf);       // lock buffer
    for (uint16_t i=buf->size; i>0 ;i--)
    {
        if (buf->data[i-1] == data)
        {
            retIndex = i;
            break;
        }
    }
    RarrayUnlock(buf);       // unlock buffer
    return retIndex;
}

static void RarrayLock(Rarray * buf)
{
    while (buf->lockActive);    // wait until lock release
    buf->lockActive = 1;        // lock buffer
}
static void RarrayUnlock(Rarray * buf)
{
    buf->lockActive = 0;        // unlock buffer
}