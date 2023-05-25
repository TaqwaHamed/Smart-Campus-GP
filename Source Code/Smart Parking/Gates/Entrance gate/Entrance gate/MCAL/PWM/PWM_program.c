/******************************************************************
 ****************** SWC     : PWM_program.c		*******************
 ****************** DATE    : Nov 19, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/

 #include "../../LIB/STD_TYPES.h"
 #include "../../LIB/BitMath.h"
 
#include "../DIO/DIO.h"
#include "../DIO/DIO_Types.h"
#include "../Memory_Map/ATmega32.h"

#include "PWM_interface.h"
#include "PWM_config.h"
#include "PWM_private.h"



void T0_FastPwm(f32 duty, uint8 pulse)
{
	//OCR0 as output
	DDRB=(1<<3);

	switch(pulse)
	{
	case INVERTED:
		OCR0 = TOP-(TOP* (duty/100))-1;
		TCCR0= (1<<COM00) | (1<<COM01) | (1<<WGM00) | (1<<WGM01) | PWM_prescaller;
		break;

	case NON_INVERTED:
		OCR0 = (duty*TOP)-1;
		TCCR0=  (1<<COM01) | (1<<WGM00) | (1<<WGM01) | PWM_prescaller;
		break;

	default :
		break;

	}

}


void T0_PhaseCorrectPwm(f32 duty, uint8 pulse)
{
	DDRB = (1 << 3);

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


void T1_FastPWM_Configs(uint8 Copy_u8Prescaler ,uint8 copy_u8Mode , uint16 Copy_u16TopValue)
{
	// Pre-scaler selection
	switch(Copy_u8Prescaler)
	{
	case FCLK_DEV_256 :
		TCCR1B |= (4 << 0); // Clock/256
		break;
	case FCLK_DEV_64:
		TCCR1B |= (3 << 0); // Clock/64
		break;
	default :
		TCCR1B &=~(0b111 << 0); // Clock
		break;
	}

	// Mode Selection
	switch(copy_u8Mode)
	{
	case FAST_PWM_TOP_ICR1 :
		TCCR1A |=(2 << 0);  // Fast PWm mode and the Top is ICR1
		TCCR1B |=(3 << 3);
		ICR1 = Copy_u16TopValue; // write the top value to compare with
		break;
	default :
		// Normal Mode
		TCCR1A &=~(3 << 0);  // Clear the first two bits
		TCCR1B &=~(3 << 3);
		break;
	}
}

void T1_FastPWM(f32 Copy_u16DutyCycle , uint8 Copyu8_Pulse , uint8 Copy_u8ChannelNumber , uint16 Copy_u16TopValue)
{
	switch(Copyu8_Pulse)
	{
	case INVERTED:
		switch(Copy_u8ChannelNumber)
		{
		case TIMER1_CHANNEL_A :
			DIO_Set_DDR_PIN(PORTD , PIN5, OUTPUT);
			OCR1A = Copy_u16TopValue - ( (Copy_u16DutyCycle * Copy_u16TopValue)/100 )-1;
			TCCR1A &=~(3 << 6); // Clear the two bits first
			TCCR1A |= (3 << 6); // Select the Channel A as Inverted
			break;
		case TIMER1_CHANNEL_B:
			DIO_Set_DDR_PIN(PORTD , PIN4, OUTPUT);
			OCR1B = Copy_u16TopValue - ( (Copy_u16DutyCycle * Copy_u16TopValue)/100 )-1;
			TCCR1A &=~(3 << 4); // Clear the two bits first
			TCCR1A |= (3 << 4);	// Select the Channel B as Inverted
			break;
		default :
			OCR1A = Copy_u16TopValue - ( (Copy_u16DutyCycle * Copy_u16TopValue)/100 )-1;
			TCCR1A &=~(3 << 6); // Clear the two bits first
			TCCR1A |= (3 << 6); // Default using channel A
			break;
		}
		break;

		case NON_INVERTED:
			switch(Copy_u8ChannelNumber)
			{
			case TIMER1_CHANNEL_A :
				DIO_Set_DDR_PIN(PORTD , PIN5, OUTPUT);
				OCR1A = (Copy_u16DutyCycle * Copy_u16TopValue)/100 -1 ;
				TCCR1A &=~(3 << 6); // Clear the two bits first
				TCCR1A |= (2 << 6); // Select the Channel A as Non Inverted
				break;
			case TIMER1_CHANNEL_B:
				DIO_Set_DDR_PIN(PORTD , PIN4, OUTPUT);
				OCR1B = (Copy_u16DutyCycle * Copy_u16TopValue)/100 -1; // Inverted
				TCCR1A  &=~(3 << 4); // Clear the two bits first
				TCCR1A |= (2 << 4); // Select the Channel B as Non Inverted
				break;
			default :
				OCR1A = (Copy_u16DutyCycle * Copy_u16TopValue)/100 -1;
				TCCR1A &=~(3 << 6); // Clear the two bits first
				TCCR1A |= (2 << 6);
				break;
			}

			break;
	}
}










