/* 
 * File:   ADC_PIC32MK.h
 * Author: orras
 *
 * Created on February 13, 2023, 9:25 PM
 */

#ifndef ADC_PIC32MK_H
#define	ADC_PIC32MK_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Init(void);
uint32_t ADC_ReadData_AN19(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_PIC32MK_H */

