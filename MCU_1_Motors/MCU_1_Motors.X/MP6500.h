/* 
 * File:   MP6500.h
 * Author: orras
 *
 * Created on January 19, 2023, 9:47 PM
 */

#ifndef MP6500_H
#define	MP6500_H

#include "hwinterface.h"
#include "config.h"

#define MP6500_LATCH_HOLD_HIGH  2 // [us]

#ifdef	__cplusplus
extern "C" {
#endif

    void MP6500_SetDirection    (uint8_t stepper, _Bool value);
    void MP6500_SetEnable       (uint8_t stepper, _Bool value);
    void MP6500_SetMS           (uint8_t stepper, _Bool ms1, _Bool ms2);
    void MP6500_Step            (uint8_t stepper);
    void MP6500_StepSetLatch    (uint8_t stepper, _Bool latch);
    
#ifdef	__cplusplus
}
#endif

#endif	/* MP6500_H */

