/*
 * Interrupt.h
 *
 * Created: 12/30/2021 6:24:16 PM
 *  Author: Yasmeen
 */ 



#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../../LIB/BitMath.h"
#include "../../LIB/STD_TYPES.h"

//Interrupt number
#define EXTI_INT0  0
#define EXTI_INT1  1
#define EXTI_INT2  2

/**
 * @Function 	 :	-EXTI_Init
 * @brief   	 :	-Initializes Interrupt: Enable global Interrupt 
                                                Make required pin as input
						Choose interrupt mode of pin
					        Enable required interrupt
						ISR code required to be executed when interrupt occurs
 * @parameter[in]:  -EXTI_INT: may be(EXTI_INT0, EXTI_INT1, EXTI_INT2)
 * @parameter[in]:  -void (* copy_CB)(void)
                      * @brief        :* copy_CB : pointer to function ISR
                      * @parameter[in]:void
					  * @return value :void
 * @return value :	-None
 */

void EXTI_Init(uint8 EXTI_INT,void (* copy_CB)(void));


#endif /* INTERRUPT_H_ */