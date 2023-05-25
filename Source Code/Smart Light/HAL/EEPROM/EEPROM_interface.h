/*
 * EEPROM_interface.h
 *
 *  Created on: Nov 18, 2021
 *      Author: saber
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_

void EEPROM_void_Init(void);

/// Writing a Byte from EEPROM
///
/// @param : u16 Copy_u16LocationAddress :the EEPROM is divided into locations and this is the location to Write Data to
/// @param : u8 Copy_u8Data the Data Wanted to be written in the EEPROM
/// @return: ERROR_STATE Enum to indicate if the Function is correctly finished or an error occurs.
/// @note  : This Function is used after I2C_voidInit.
/// @note  : Writing to EEPROM takes much time than reading so after each Write operation stay for 100m
/// @warning: according to the size of the EEPROM the Address is 2^n-1 starting from 0
ERROR_STATE EEPROM_enumWriteByte(u16 Copy_u16LocationAddress , u8 Copy_u8Data);

/// Reading byte to the EEPROM
///
/// This Function is used to read one byte from specific location address in EEPROM
/// @param u16 Copy_u16LocationAddress  : the EEPROM is divided into locations and this is the location to read Data from
/// @param u8*Copy_u8Data a pointer to unsigned char to save the data read from the EEPROM
/// @note This Function is used after I2C_voidInit.
/// @warning: according to the size of the EEPROM the Address is 2^n-1 starting from 0
ERROR_STATE EEPROM_enumReadByte(u16 Copy_u16LocationAddress , u8*Copy_u8Data);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
