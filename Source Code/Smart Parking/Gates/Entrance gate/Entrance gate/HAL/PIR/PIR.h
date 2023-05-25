/*
 * PIR.h
 *
 * Created: 12/29/2021 
 *  Author: Yasmeen
 */ 


#ifndef HAL_PIR_PIR_H_
#define HAL_PIR_PIR_H_

#include "../../LIB/STD_TYPES.h"#include "../../LIB/BitMath.h"
#include "../../MCAL/DIO/DIO.h"

/**
 * @Function 	 :  -PIR_Init
 * @brief   	 :  -Initializes PIR: Selecting the PIR PIN Direction
 * @parameter[in]:  -DIO_PORT_ID: PORT may be (PORTA_REG, PORTB_REG, PORTC_REG , PORTD_REG) or any equivalent macro from DIO_Types.h file
 * @parameter[in]:  -DIO_PIN_ID : PIN Which we want to Read may be between (0:7) or any equivalent macro from DIO_Types.h file
 * @return value :  -None
 */
void PIR_Init(uint8 DIO_PORT_ID , uint8 DIO_PIN_ID);


/**
 * @Function 	 :  -PIR_Read
 * @brief   	 :  -Read the value at the given pin (Out may be HIGH 1 OR LOW 0)
 * @parameter[in]:  -DIO_PORT_ID   : PORT may be (PORTA_REG, PORTB_REG, PORTC_REG , PORTD_REG) or any equivalent macro from DIO_Types.h file
 * @parameter[in]:  -DIO_PIN_ID    : PIN Which we want to Read may be between (0:7) or any equivalent macro from DIO_Types.h file
 * @return value :  -uint8 variable: Value of the pin (1 or 0)
 */
uint8 PIR_Read(uint8 DIO_PORT_ID , uint8 DIO_PIN_ID);



#endif /* HAL_PIR_PIR_H_ */