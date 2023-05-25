/******************************************************************
 ****************** SWC     : ADC_program.c		*******************
 ****************** DATE    : Nov 18, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/


#include"../../LIB/STD_TYPES/STD_TYPES.h"
#include"ADC_interface.h"
#include"ADC_private.h"
#include"ADC_config.h"

void ADC_VoidInit (void)
{

	ADMUX_Reg =  ADC_REFERNECE_VOLTAGE | ADLAR;
	ADCSRA_Reg = ADC_STATE | ADC_INTERRUPT | ADC_prescaller;

}


u16 ADC_u16Read (u8 Copy_u8Channel_Id)
{
	u16 ADC_u8Result=0;
	ADMUX_Reg &=~(0b11111);
	//select channel
	ADMUX_Reg |= Copy_u8Channel_Id;
	//start conversion
	ADCSRA_Reg |= (1 << 6);
	// wait the flag to be set
	while( ( (ADCSRA_Reg >> 4)& 1) == 0 );
#if ADLAR == ADC_LEFT_ADJUST_DISABEL
	ADC_u8Result = ADCL_Reg | (ADCH_Reg <<8 );

#elif ADLAR == ADC_LEFT_ADJUST_ENABLE
	ADC_u8Result = (ADCH_Reg << 2);
#endif

	// clear flag
	ADCSRA_Reg |= (1 << 4);

	return ADC_u8Result;
}
