/*
 * servo_program.c
 *
 *  Created on: Dec 23, 2021
 *      Author: taqwa
 */



 #include "../../LIB/STD_TYPES.h"
 #include "../../LIB/BitMath.h"
#include "../../MCAL/PWM/PWM_interface.h"
#include "servo_interface.h"
#include "servo_private.h"
#include "servo_config.h"




void SERVO_voidInit(void)
{

	T1_FastPWM_Configs (SERVO_TIMER1_PWM_PRESCALER,  SERVO_PWM_MODE , TIMER1_TOP_VALUE );


}

void SERVO_voidMoveAngle(uint8 Copy_u8Degree)
{

	uint8 Local_u8DutyCycle = 0;
		switch(Copy_u8Degree)
		{
		case 0 	 : Local_u8DutyCycle = 3; break;
		case 90  : Local_u8DutyCycle = 7.5; break;
		case 180 : Local_u8DutyCycle = 12; break;
		}
		T1_FastPWM( Local_u8DutyCycle, TIMER1_PULSE_TYPE, SERVO_TIMER0_CHANNEL, TIMER1_TOP_VALUE);
	}