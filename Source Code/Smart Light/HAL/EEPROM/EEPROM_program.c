/*
 * EEPROM_program.c
 *
 *  Created on: Nov 18, 2021
 *      Author: saber
 */

#include "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/IIC/I2C_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_void_Init(void)
{
	I2C_voidInit();
}
ERROR_STATE EEPROM_enumWriteByte(u16 Copy_u16LocationAddress , u8 Copy_u8Data)
{
	ERROR_STATE Local_enum_errorState = NOK;
	Local_enum_errorState = I2C_MASTER_enumSendStart();
	if( Local_enum_errorState == OK )
	{
		Local_enum_errorState = I2C_MASTER_enumSendSlaveAddressWithWrite( 0x50|((Copy_u16LocationAddress >> 8)&0x03));
		if( Local_enum_errorState == OK)
		{
			Local_enum_errorState = I2C_MASTER_enumSendByte((u8)Copy_u16LocationAddress);
			if(Local_enum_errorState == OK)
			{
				Local_enum_errorState = I2C_MASTER_enumSendByte(Copy_u8Data);
				if(Local_enum_errorState == OK)
				{
					I2C_MASTER_voidSendSTOP();
					Local_enum_errorState = OK;
				}
			}
		}
	}
	return Local_enum_errorState;
}

ERROR_STATE EEPROM_enumReadByte(u16 Copy_u16LocationAddress , u8*Copy_u8Data)
{
	ERROR_STATE Local_enum_errorState = NOK;
	Local_enum_errorState = I2C_MASTER_enumSendStart();
	if( Local_enum_errorState == OK )
	{
		Local_enum_errorState = I2C_MASTER_enumSendSlaveAddressWithWrite( 0x50|((Copy_u16LocationAddress >> 8)&0x03));
		if( Local_enum_errorState == OK)
		{
			Local_enum_errorState = I2C_MASTER_enumSendByte((u8)Copy_u16LocationAddress);
			if(Local_enum_errorState == OK)
			{
				Local_enum_errorState = I2C_MASTER_enumSendRepeatedStart();
				if(Local_enum_errorState == OK)
				{
					Local_enum_errorState = I2C_MASTER_enumSendSlaveAddressWithRead(0x50|((Copy_u16LocationAddress >> 8)&0x03));
					if( Local_enum_errorState == OK )
					{
						Local_enum_errorState = I2C_MASTER_enumReadByte_With_NACK(Copy_u8Data);
						if(Local_enum_errorState == OK)
						{
							I2C_MASTER_voidSendSTOP();
						}
					}
				}
			}
		}
	}
	return Local_enum_errorState;
}
