/*
 * LCD_config.h
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*			LCD_MODE		*/
#define LCD_MODE		EIGHT_BIT

/*			Control Pins	*/
#define RS_PORT		PORTA
#define RS_PIN		PIN5

#define RW_PORT		PORTA
#define RW_PIN		PIN6

#define EN_PORT		PORTA
#define EN_PIN		PIN7

/*			Data Pins		*/
#define D7_PORT		PORTD
#define D7_PIN		PIN7

#define D6_PORT		PORTD
#define D6_PIN		PIN6

#define D5_PORT		PORTD
#define D5_PIN		PIN5

#define D4_PORT		PORTD
#define D4_PIN		PIN4

#define D3_PORT		PORTD
#define D3_PIN		PIN3

#define D2_PORT		PORTD
#define D2_PIN		PIN2

#define D1_PORT		PORTD
#define D1_PIN		PIN1

#define D0_PORT		PORTD
#define D0_PIN		PIN0



#endif /* LCD_CONFIG_H_ */
