/*
 * LDR_program.c
 *
 *  Created on: Nov 18, 2021
 *      Author: taqwa
 */

#include"../../LIB/STD_TYPES/STD_TYPES.h"
#include"../../MCAL/DIO/DIO_interface.h"
#include"../../MCAL/ADC/ADC_interface.h"
#include"LDR_interface.h"
#include"LDR_private.h"
#include"LDR_config.h"

void LDR_SENSOR_voidInit(u8 Copy_u8ChannelNumber)
{
	DIO_SetPinDirection(PORTA, Copy_u8ChannelNumber, INPUT);
}


u8 LDR_SNESOR_u8Read(u8 Copy_u8ChannelNumber)
{
	u16 Local_u16ADCValue = 0;
//	f32 Local_f32AnalogVolt= 0;
	u8 Local_u8INT =0;
	Local_u16ADCValue = ADC_u16Read(Copy_u8ChannelNumber);
//	Local_f32AnalogVolt = (Local_u16ADCValue * VCC)/1024.0;
//	f64 RLDR = ((u64)Known_Res*VCC)/(VCC-Local_f32AnalogVolt);
	Local_u8INT=MAP(Local_u16ADCValue,750,1024,100,0);
	return Local_u8INT;
}

static f32 MAP(f32 Copy_f32Value, f32 Copy_f32INStart, f32 Copy_f32INEnd, f32 Copy_f32OutStart, f32 Copy_f3OutEnd)
{
	return ((Copy_f32Value - Copy_f32INStart ) * (Copy_f3OutEnd - Copy_f32OutStart )/(Copy_f32INEnd -Copy_f32INStart ) + Copy_f32OutStart);

}
