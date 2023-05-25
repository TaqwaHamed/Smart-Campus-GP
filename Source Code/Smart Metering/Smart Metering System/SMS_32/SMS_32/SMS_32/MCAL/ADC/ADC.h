 /***********************************************
 * ADC.h
 *
 * Created: 19/11/2021
 *
 * Author: Ahmed LNiwehy
 **********************************************/

#ifndef ADC_H_
#define ADC_H_

#include "ADC_HW.h"

void ADC_Init();
uint16 ADC_Read(uint8 channel);


#endif /* ADC_H_ */