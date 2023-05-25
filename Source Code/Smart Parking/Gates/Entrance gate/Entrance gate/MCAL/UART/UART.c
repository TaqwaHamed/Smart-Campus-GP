/*
 * UART.c
 *
 * Created: 12/29/2021 12:16:39 AM
 *  Author: khloud khaled
 */ 

 /* LIB include */
 #include "../../LIB/STD_TYPES.h"
 #include "../../LIB/BitMath.h"
 
/* Driver Include */
#include "UART.h"
#include "UART_config.h"

#define F_CPU 8000000UL


void USART_voidInit(uint32 copy_uint8BaudRate)
{
	//BaudRate  9600
	uint16 Local_UBRR;
	//adjust mode
		ClearBit(USCRC,URSEL);
		#if    USART_MODE == 0
		SetBit(USCRC,URSEL);
		ClearBit(USCRC,UMSEL);
		Local_UBRR = (F_CPU/((uint64)16*copy_uint8BaudRate))-1;
		#elif  USART_MODE == 2
		ClearBit(USCRC,UMSEL);
		SetBit(USCRA,U2X);
		Local_UBRR = (F_CPU/((uint64)8*copy_uint8BaudRate))-1;
		#else
		SetBit(USCRC,UMSEL);
		Local_UBRR = (F_CPU/((uint64)2*copy_uint8BaudRate))-1;
		#endif
		
		/* Adjust UBRR */
		SetBit(USCRC,URSEL);
		UBRRH = (uint8)(Local_UBRR >> 8);
		UBRRL = (uint8)(Local_UBRR);
		
		/* Adjust Word Size */
		#if   USART_WORDSIZE == 0
		ClearBit(USCRC,UCSZ0);
		ClearBit(USCRC,UCSZ1);
		ClearBit(USCRB,UCSZ2);
		#elif USART_WORDSIZE == 1
		SetBit(USCRC,UCSZ0);
		ClearBit(USCRC,UCSZ1);
		ClearBit(USCRB,UCSZ2);
		#elif USART_WORDSIZE == 2
		ClearBit(USCRC,UCSZ0);
		SetBit(USCRC,UCSZ1);
		ClearBit(USCRB,UCSZ2);
		#elif USART_WORDSIZE == 3
		SetBit(USCRC,UCSZ0);
		SetBit(USCRC,UCSZ1);
		ClearBit(USCRB,UCSZ2);
		#else
		SetBit(USCRC,UCSZ0);
		SetBit(USCRC,UCSZ1);
		SetBit(USCRB,UCSZ2);
		#endif
		
		/* Adjust Parity */
		#if   USART_PARITY  == 0
		ClearBit(USCRC,UPM0);
		ClearBit(USCRC,UPM1);
		#elif USART_PARITY  == 1
		ClearBit(USCRC,UPM0);
		SetBit(USCRC,UPM1);
		#else
		SetBit(USCRC,UPM0);
		SetBit(USCRC,UPM1);
		#endif
		
		/* Adjust Stop bit */
		#if  USART_STOPBIT == 0
		ClearBit(USCRC,USBS);
		#else
		SetBit(USCRC,USBS);
		#endif
		
		/* Enable TX and RX */
		SetBit(USCRB,TXEN);
		SetBit(USCRB,RXEN);
	
}

void USART_voidSend(uint8 copy_uint8DataSend)
{
	//Wait for UDR transmit buffer to be empty
	while(GetBit(USCRA,UDRE)==0);
	//Put data to UDR transmit buffer transmit
	UDR = copy_uint8DataSend ;
}

uint8 USART_u8Recieve(void)
{
	//Wait for UDR receive buffer to be filled with data
	while(GetBit(USCRA,RXC)==0);
	//Receive data from UDR receive buffer
	return UDR;
}

void USART_voidSendNumberu32(uint32 copy_uint32DataSend)
{
	uint8 Data;
	//USART_voidSend ((uint8)num);
	//USART_voidSend ((uint8)(num>>8));
	//USART_voidSend ((uint8)(num>>16));
	uint8 counter;
	for(counter = 0; counter <=3 ; counter ++)
	{
		Data = (uint8)(copy_uint32DataSend >> (8*counter));
		USART_voidSend(Data);
	}
}

uint32 USART_u32RecieveNumberu32(void)
{
		uint32 Data;
		uint8 counter;
		for(counter = 0; counter <=3 ; counter ++)
		{
			Data |=(USART_u8Recieve() << (8* counter));
		}
		return Data;
}