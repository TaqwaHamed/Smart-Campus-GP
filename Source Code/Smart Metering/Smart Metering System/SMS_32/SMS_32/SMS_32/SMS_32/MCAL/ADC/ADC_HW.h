/***********************************************
* ADC_HW.h
*
* Created: 19/11/2021
*
* Author: Ahmed LNiwehy
**********************************************/


#ifndef ADC_HW_H_
#define ADC_HW_H_

#include "../../LIB/STD_TYPES.h"
#include "../Memory_Map/ATmega32.h"

// ADCSRA
#define ADEN	7
#define ADSC	6
#define ADFR	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

//ADMUX
#define REFS1	7
#define REFS0	6
#define ADLAR	5
/* bit 4 reserved */
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

#endif /* ADC_HW_H_ */