/*
 * main.c
 *
 * Created: 11/20/2021 11:37:03 PM
 *  Author: kholoud
 */ 

#include "Power_Factor.h"
 
uint32 T=0;

 extern uint8 TOV_Counter;

 uint32 ZeroDetection()
 {
	 while(1){
		 if ((DIO_Get_PIN(PORTC_REG,PIN5))==0)   
		 {
			 TCNT0 =0 ;
			 TIMR0_voidStart(1);
			TCCR0 = 0x01;
			break;
		 }
		else
		{
			continue;
		}
	 }
	 while(1){
		if ((DIO_Get_PIN(PORTC_REG,PIN4))==0)
		{
			//TIMR0_voidStopTIMR0();
			TCCR0 = 0x00;
			//T=TIMR0_uint32Read();
			T=TCNT0;
			break;
			
		}
		else
		{
			continue;
		}
	 
	 }
	 return T;
 }

float GetPowerFactor(uint32 T)
{
	float PF;
	// To complete number of counts
	//(T+1); //Value from the timer
	// all counts
	T = (TOV_Counter * 255) +(T+1);
	//To convert into seconds
	PF=(float)T/1000000;
	//To convert into radians
	PF=PF*60*360*(3.14/180);
	//power factor
	// -0.093 average of the error after testing
	PF = cos((PF - 0.093));
	return fabs(PF);
}
ISR(INT0_vect){
	TOV_Counter++;
}