/*
 * UART.h
 *
 * Created: 12/29/2021 12:17:42 AM
 *  Author: khloud khaled
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BitMath.h"
#ifndef UART_H_
#define UART_H_

#define  UDR    *((volatile uint8*)0x2C)
#define  USCRA  *((volatile uint8*)0x2B)
#define RXC    7
#define TXC    6
#define UDRE   5
#define FE     4
#define DOR    3
#define PE     2
#define U2X    1
#define MPCM   0
#define  USCRB  *((volatile uint8*)0x2A)
#define RXCIE    7
#define TXCIE    6
#define UDRIE    5
#define RXEN     4
#define TXEN     3
#define UCSZ2    2
#define RXB8     1
#define TXB8     0
#define  USCRC  *((volatile uint8*)0x40)
#define URSEL    7
#define UMSEL    6
#define UPM1     5
#define UPM0     4
#define USBS     3
#define UCSZ1    2
#define UCSZ0    1
#define UCPOL    0
#define  UBRRL  *((volatile uint8*)0x29)
#define  UBRRH  *((volatile uint8*)0x40)


//prototype
void USART_voidInit(uint32 copy_uint8BaudRate);

void USART_voidSend(uint8 copy_uint8DataSend);

uint8 USART_u8Recieve(void);

void USART_voidSendNumberu32(uint32 copy_uint32DataSend);

uint32 USART_u32RecieveNumberu32(void);

#endif /* UART_H_ */