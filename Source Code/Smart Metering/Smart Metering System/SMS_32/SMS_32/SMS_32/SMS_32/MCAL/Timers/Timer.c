/*
 * Timer0.c
 *
 * Created: 11/21/2021 12:28:19 AM
 *  Author: kholoud
 */

 /* LIB include */
 #include "../../LIB/STD_TYPES.h"
 #include "../../LIB/BitMath.h"
 
 /* Driver Include */
 #include "Timer.h"

 
uint8 TOV_Count = 0;
 void  TIMR0_voidStart(uint8 copy_uint8Prescaler)
 {
	 /*********************Enable Global Interrupt************/
	 SetBit(SREG , 7);
	 /*****************Adjust TOV Interrupt *******************/
	// #if  TIMR0_TOVINTERRUPT == 0
	// ClearBit(TIMASK, TOIE0); // Disable TOV Interrupt
	// #else
	 SetBit(TIMASK, TOIE0); // Enable TOV Interrupt
	// #endif
	 /*********** Adjust Clock Prescaler******************/
	 TCCR0 &= 0xF8;
	 TCCR0 |= copy_uint8Prescaler;
 }
 
 // SetTMR0Start
 void  TIMR0_voidSetTCNT0(uint8 copy_uint8InitValue)
 {
	 TCNT0 = copy_uint8InitValue;
 }
 
 
uint32   TIMR0_uint32Read(void)
 {
	uint32 Return_Val;
	 Return_Val = (TOV_Count * 256)+ TCNT0;
	 return Return_Val;
 }
 
 void  TIMR0_voidStopTMR0(void)
 {
	 // Make CS bit Zeros
	 TCCR0 &= 0xF8;
 }
 
 // Set TCCR0 =0x00
 void  TIMR0_voidDInit(void)
 {
	 // Put TCCR0 all bits zeros
	 TCCR0 = 0x00;
 }
 
