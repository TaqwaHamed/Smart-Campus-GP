/*
 * Timer0.h
 *
 * Created: 11/20/2021 11:41:27 PM
 *  Author: kholoud 
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

	#define TIMR0_CLKMC    0x01
	#define TIMR0_CLK_8    0x02
	#define TIMR0_CLK_64   0x03
	#define TIMR0_CLK_256  0x04
	#define TIMR0_CLK_1024 0x05
	#define TIMR0_FE 0x06
	#define TIMR0_RE 0x07

	// Timer0 counter Register
	#define TCNT0    *((volatile uint8*)0x52)
	
	// Timer0 control Register
	#define TCCR0    *((volatile uint8*)0x53)
		#define CS00  0
		#define CS01  1

	// Interrupt Control
	#define TIMASK   *((volatile uint8*)0x59)
		#define TOIE0 0
		
	// Interrupt Flags
	#define TIFR     *((volatile uint8*)0x58)
		#define TOV0  0
		
	// Global Interrupt Register
	#define SREG     *((volatile uint8*)0x5F)
	
	
	//prototype
	void TIMR0_voidStart(uint8 copy_uint8Prescaler);
	void TIMR0_voidSetTCNT0(uint8 copy_uint8InitValue);
	uint32 TIMR0_uint32Read(void);
	void TIMR0_voidStopTIMR0(void);
	//set TCCR0 =0x00
	void TIMR0_voidDInit(void);


#endif /* TIMER0_H_ */