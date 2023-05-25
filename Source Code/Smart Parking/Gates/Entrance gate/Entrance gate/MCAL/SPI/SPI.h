/*
 * SPI.h
 *
 *  Created on: Dec 17, 2021
 *      Author: Ahmed Nasser
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

/******************************************************************************
 *									INCLUDES				                  *
 ******************************************************************************/
#include "../Memory_Map/ATmega32.h"
#include "SPI_HW.h"


/******************************************************************************
 *									Macros					                  *
 ******************************************************************************/

/*********************************** ENABLE ************************************/

#define SPI_ON									1
#define SPI_OFF									0

/*********************************** MODE ************************************/

#define MASTER									1
#define SLAVE									0

/*********************************** SPI_PRESCALAR ************************************/

#define  SPI_PRESCALAR_4						0x00
#define  SPI_PRESCALAR_16						0x01
#define  SPI_PRESCALAR_64						0x02
#define  SPI_PRESCALAR_128						0x03

/*********************************** SPI_DOUBLE_SPEED ************************************/

#define  SPI_DOUBLE_SPEED_MODE_OFF				0
#define  SPI_DOUBLE_SPEED_MODE_ON	 			1

/*********************************** SPI_DATA_ORDER ************************************/

#define  SPI_MSB_FISRT							0
#define  SPI_LSB_FISRT	 						1

/*********************************** ENABLE_SPI_INTRRUPT ************************************/

#define SPI_INT_ON								1
#define SPI_INT_OFF								0

/*********************************** SPI_OPERATING_LEVEL ************************************/

#define SPI_IDLE_HIGH							1
#define SPI_IDLE_LOW							0

/*********************************** SPI_SAMPLING_EDGE ************************************/

#define SPI_RISING 								1
#define SPI_FALLING 							0




/******************************************************************************
 *									APIS				                      *
 ******************************************************************************/

/**======================================================================
 * @Function 	 :	-SPI_Init
 * @brief   	 :	-Initializes MCU according to SPI_Config.h
 * @parameter[in]:  -None
 * @return value :	-None
 * Note 		 :	-
 */
void SPI_Init(void);

/**======================================================================
 * @Function 	 :	-SPI_SendReceive
 * @brief   	 :	-Transmitting and receiving data between Master to Slave
 * @parameter[in]:  -unsigned char data
 * @return value :	-unsigned char "Content of SPDR which contains data(input) "
 * Note 		 :	-
 */
unsigned char SPI_SendReceive(unsigned char data);

/**======================================================================
 * @Function 	 :	-SPI_Send
 * @brief   	 :	-Transmitting data 
 * @parameter[in]:  -unsigned char data
 * @return value :	-void
 * Note 		 :	-
 */
void SPI_Send(unsigned char data);

/**======================================================================
 * @Function 	 :	-SPI_Receive
 * @brief   	 :	-Receiving data from Master to Slave
 * @parameter[in]:  -void
 * @return value :	-unsigned char "Content of SPDR which contains data(input) "
 * Note 		 :	-
 */
unsigned char SPI_Receive(void);

/**======================================================================
 * @Function 	 :	-SPI_Checks_for_collision
 * @brief   	 :	-check if collision occur (written on the SPDR while transmitting)
 * @parameter[in]:  -void
 * @return value :	-unsigned char "status of WCOL pin in SPSR register "
 * Note 		 :	-
 */
unsigned char SPI_Checks_for_collision(void);

#endif /* MCAL_SPI_SPI_H_ */