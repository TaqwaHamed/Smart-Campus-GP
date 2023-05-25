/******************************************************************
 ****************** SWC     : PWM_program.c		*******************
 ****************** DATE    : Nov 19, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/

#include"../../LIB/STD_TYPES/STD_TYPES.h"
#include"../../LIB/BIT_MATH/BIT_MATH.h"
#include "../DIO/DIO_private.h"

#include"PWM_interface.h"
#include"PWM_config.h"
#include"PWM_private.h"



void T0_FastPwm(f32 duty, u8 pulse)
{
	//OCR0 as output
	DDRB_REG=(1<<3);

	switch(pulse)
	{
	case INVERTED:
		OCR0 = TOP-(TOP* (duty/100))-1;
		TCCR0= (1<<COM00) | (1<<COM01) | (1<<WGM00) | (1<<WGM01) | PWM_prescaller;
		break;

	case NON_INVERTED:
		OCR0 = (TOP-duty*TOP)-1;
		TCCR0=  (1<<COM01) | (1<<WGM00) | (1<<WGM01) | PWM_prescaller;
		break;

	default :
		break;

	}

}


void T0_PhaseCorrectPwm(f32 duty, u8 pulse)
{
	DDRB_REG = (1 << 3);

	switch(pulse)
	{
	case INVERTED :
		OCR0 = ((TOP-1)-(duty*(TOP-1)/100));
		TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | PWM_prescaller;
		break;

	case NON_INVERTED :
		OCR0 = (duty*(TOP-1))/100;
		TCCR0 = (1 << WGM00) | (1 << COM01) | PWM_prescaller;
		break;

	default :
		break;
	}

}
