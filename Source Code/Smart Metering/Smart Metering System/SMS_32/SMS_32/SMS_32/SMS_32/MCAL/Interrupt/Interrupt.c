/*
 * Interrupt.c
 *
 * Created: 12/30/2021 6:24:33 PM
 *  Author: Yasmeen
 */ 

#include "Interrupt.h"
#include "Interrupt_REG.h"
#include "avr/interrupt.h"

/* Global var  */
void (* Global_CBINT0)(void);
void (* Global_CBINT1)(void);
void (* Global_CBINT2)(void);


void EXTI_Init(uint8 EXTI_INT,void (* copy_CB)(void))
{
	SetBit(SREG,GI);
	switch(EXTI_INT)
	{
		case EXTI_INT0:
		    SetBit(GICR,INT0);
		    SetBit(GIFR,INTF0);
		    ClearBit(DDRD,2);
		    Global_CBINT0 =copy_CB;
		break;
		
		case EXTI_INT1:
		    SetBit(GICR,INT1);
		    SetBit(GIFR,INTF1);
		    ClearBit(DDRD,3);
		    Global_CBINT1 =copy_CB;
		break;
		
		case EXTI_INT2:
		    SetBit(GICR,INT2);
		    SetBit(GIFR,INTF2);
		    ClearBit(DDRB,2);
		    Global_CBINT2 =copy_CB;
		break;
	}
}

ISR(INT0_vect)
{
	(* Global_CBINT0)();
}

ISR(INT1_vect)
{
	(* Global_CBINT1)();
}

ISR(INT2_vect)
{
	(* Global_CBINT2)();
}
