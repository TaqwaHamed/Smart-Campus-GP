/*
 * PIR.c
 *
 * Created: 12/29/2021 
 *  Author: Yasmeen
 */ 

#include "../../LIB/STD_TYPES.h"#include "../../LIB/BitMath.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Memory_Map/ATmega32.h"
#include "PIR.h"



void PIR_Init(uint8 DIO_PORT_ID , uint8 DIO_PIN_ID)
{
	DIO_Set_DDR_PIN ( DIO_PORT_ID , DIO_PIN_ID, INPUT);
}

uint8 PIR_Read(uint8 DIO_PORT_ID , uint8 DIO_PIN_ID)
{
	uint8 Value;
	Value = DIO_Get_PIN( DIO_PORT_ID ,DIO_PIN_ID);
	return Value;
}