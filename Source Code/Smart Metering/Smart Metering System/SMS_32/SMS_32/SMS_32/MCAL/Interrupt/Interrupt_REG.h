/*
 * Interrupt_REG.h
 *
 * Created: 12/30/2021 6:25:08 PM
 *  Author: Yasmeen
 */ 


#ifndef INTERRUPT_REG_H_
#define INTERRUPT_REG_H_

//Status register
#define SREG *((volatile uint8*)0x5F)
#define GI  7

//General interrupt flag register
#define GIFR *((volatile uint8*)0x5A)
#define INTF1  7
#define INTF0  6
#define INTF2  5

//Microcontroller control and status register
#define MCUCSR *((volatile uint8*)0x54)
#define ISC2  6

//Microcontroller control register
#define MCUCR *((volatile uint8*)0x55)
#define ISC00  0
#define ISC01  1
#define ISC10  2
#define ISC11  3

//General interrupt control register
#define GICR *((volatile uint8*)0x5B)
#define INT1  7
#define INT0  6
#define INT2  5

//DIO
#define DDRB  *((volatile uint8*)0x37)
#define DDRD  *((volatile uint8*)0x31)


#endif /* INTERRUPT_REG_H_ */