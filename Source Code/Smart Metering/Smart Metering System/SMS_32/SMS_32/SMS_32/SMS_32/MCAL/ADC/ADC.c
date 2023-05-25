/***********************************************
* ADC.c
*
* Created: 19/11/2021
*
* Author: Ahmed LNiwehy
**********************************************/

#include "ADC.h"
#define F_CPU 1000000UL
#include "../../LIB/Delay.h"


void ADC_Init()
{
	
	ADMUX |= (1<<REFS0);                                           // INTERNAL REF VOLTAGE 5V
	ADCSRA |= (1<<ADEN) | (1<<ADPS2);                              //ENABLE ADC AND 16 PRESCALE
}

uint16 ADC_Read(uint8 channel)
{
	
	uint16 data = 0;
	ADMUX |= (channel & 0x0F);						  // SELECT ADCx
	ADCSRA |= (1<<ADSC);                               // START CONVERSION
	while((ADCSRA & (1<<ADIF)) == 0);                 // MONITOR END OF CONVERSION INTERRUPT
	ADCSRA |= (1<<ADIF);			                  // CLEAR ADIF BIT
	
	data = ADCL | (ADCH << 8);			          // READ DATA FROM ADC_ADCL & ADC_ADCH REG
	ADMUX &= 0xF0;								// reset Analog Channel Selection Bits to chanage the channel 
	
	return data;
}