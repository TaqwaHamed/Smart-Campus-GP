/*
 * UART_config.h
 *
 * Created: 12/29/2021 12:59:15 AM
 *  Author: compu
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_



/* Options : 0 for Asynchronous Normal mode
			 1 for Synchronous mode
			 2 for Asynchronous Double Speed mode
*/
#define USART_MODE  0

/* Options : 0 for Disable Parity
			 1 for Even Parity
			 2 for Odd  Parity
*/
#define USART_PARITY 0

/* Options : 0 for one stop bit 
			 1 for two stop bit 
*/
#define  USART_STOPBIT  1

/* Options : 0 for 5-bit word size 
			 1 for 6-bit word size
			 2 for 7-bit word size
		     3 for 8-bit word size
			 4 for 9-bit word size
*/
#define  USART_WORDSIZE 3


#endif /* UART_CONFIG_H_ */