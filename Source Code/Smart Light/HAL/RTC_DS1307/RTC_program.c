/*
 * RTC_program.c
 *
 *  Created on: Nov 19, 2021
 *      Author: saber
 */

#include  "../../LIB/STD_TYPES/STD_TYPES.h"
#include "../../LIB/BIT_MATH/BIT_MATH.h"

#include "../../MCAL/IIC/I2C_interface.h"

#include "RTC_interface.h"
#include "RTC_private.h"
#include "RTC_config.h"

ERROR_STATE RTC_enumUpdateTime(RTC_Time * Copy_struct_ptr_Time)
{
	ERROR_STATE Local_enum_ErrorState = NOK;
	u8 Local_u8Seconds = (((Copy_struct_ptr_Time->Seconds) / 10 ) << 4);
	Local_u8Seconds   |= ((Copy_struct_ptr_Time->Seconds) % 10);
	Local_u8Seconds &=~(1 << 7); // Enable the channel bit
	u8 Local_u8Minutes = (((Copy_struct_ptr_Time->Minutes)/10) << 4);
	Local_u8Minutes |= ((Copy_struct_ptr_Time->Minutes) % 10);
	u8 Local_u8Hours = (((Copy_struct_ptr_Time->Hours)/10) << 4);
	if(Copy_struct_ptr_Time->HoursMode == Hours_24)
	{
		Local_u8Hours |= ((Copy_struct_ptr_Time->HoursMode)|((Copy_struct_ptr_Time->Hours)%10));
	}
	else
	{
		Local_u8Hours |= ((Copy_struct_ptr_Time->HoursMode)|(Copy_struct_ptr_Time->AM_PM)|((Copy_struct_ptr_Time->Hours)%10));

	}

	Local_enum_ErrorState = I2C_MASTER_enumSendStart();
	if (Local_enum_ErrorState == OK)
	{
		Local_enum_ErrorState = I2C_MASTER_enumSendSlaveAddressWithWrite(RTC_SLAVE_ADDRESS);
		if(Local_enum_ErrorState == OK)
		{
			Local_enum_ErrorState = I2C_MASTER_enumSendByte(RTC_BASE_TIME_ADDRESS);
			if( Local_enum_ErrorState == OK )
			{
				Local_enum_ErrorState = I2C_MASTER_enumSendByte(Local_u8Seconds);
				if( Local_enum_ErrorState == OK )
				{
					Local_enum_ErrorState = I2C_MASTER_enumSendByte(Local_u8Minutes);
					if(Local_enum_ErrorState == OK)
					{
						Local_enum_ErrorState = I2C_MASTER_enumSendByte(Local_u8Hours);
						if(Local_enum_ErrorState == OK)
						{
							I2C_MASTER_voidSendSTOP();
						}
					}
				}
			}
		}
	}
	return Local_enum_ErrorState;
}

ERROR_STATE RTC_enumUpdateCalendar(RTC_Date * Copy_struct_ptr_Date)
{
	ERROR_STATE Local_enumErrorState = NOK;
	u8 Local_u8Date = ((Copy_struct_ptr_Date->Date /10 )<<4);
	Local_u8Date |= (Copy_struct_ptr_Date->Date % 10);

	u8 Local_u8_Month = ((Copy_struct_ptr_Date->Month /10) << 4);
	Local_u8_Month |= (Copy_struct_ptr_Date->Month % 10);

	u8 Local_u8_Year = ((Copy_struct_ptr_Date->Year /10) << 4);
	Local_u8_Year |= (Copy_struct_ptr_Date->Year % 10);

	Local_enumErrorState = I2C_MASTER_enumSendStart();
	if(Local_enumErrorState == OK)
	{
		Local_enumErrorState = I2C_MASTER_enumSendSlaveAddressWithWrite(RTC_SLAVE_ADDRESS);
		if(Local_enumErrorState == OK)
		{
			Local_enumErrorState = I2C_MASTER_enumSendByte(RTC_BASE_CALENDER_ADDRESS);
			if( Local_enumErrorState == OK )
			{
				Local_enumErrorState = I2C_MASTER_enumSendByte(Copy_struct_ptr_Date->Day);
				if( Local_enumErrorState == OK )
				{
					Local_enumErrorState = I2C_MASTER_enumSendByte(Local_u8Date);
					if( Local_enumErrorState == OK )
					{
						Local_enumErrorState = I2C_MASTER_enumSendByte(Local_u8_Month);
						if(Local_enumErrorState == OK)
						{
							Local_enumErrorState = I2C_MASTER_enumSendByte(Local_u8_Year);
							if(Local_enumErrorState == OK)
							{
								I2C_MASTER_voidSendSTOP();
							}
						}
					}
				}
			}
		}
	}
	return Local_enumErrorState;
}

ERROR_STATE RTC_enumReadTime(RTC_Time * Copy_struct_ptr_Time)
{
	ERROR_STATE Local_enumErrorState = NOK;
	u8 Local_u8Array[3] = {0};
	Local_enumErrorState = I2C_MASTER_enumSendStart();
	if(Local_enumErrorState == OK)
	{
		Local_enumErrorState = I2C_MASTER_enumSendSlaveAddressWithWrite(RTC_SLAVE_ADDRESS);
		if( Local_enumErrorState== OK )
		{
			Local_enumErrorState = I2C_MASTER_enumSendByte(RTC_BASE_TIME_ADDRESS);
			if( Local_enumErrorState == OK )
			{
				Local_enumErrorState = I2C_MASTER_enumSendRepeatedStart();

				if( Local_enumErrorState == OK )
				{
					Local_enumErrorState = I2C_MASTER_enumSendSlaveAddressWithRead(RTC_SLAVE_ADDRESS);
					if(Local_enumErrorState == OK)
					{
						Local_enumErrorState = I2C_MASTER_enumReadByte_With_ACK(&Local_u8Array[0]);
						if( Local_enumErrorState == OK )
						{
							Local_enumErrorState = I2C_MASTER_enumReadByte_With_ACK(&Local_u8Array[1]);
							if(Local_enumErrorState == OK)
							{
								Local_enumErrorState = I2C_MASTER_enumReadByte_With_NACK(&Local_u8Array[2]);
								if(Local_enumErrorState == OK)
								{
									I2C_MASTER_voidSendSTOP();
								}
							}
						}
					}
				}
			}
		}
	}

	RTC_ProcessTime( Copy_struct_ptr_Time , Local_u8Array );
	return Local_enumErrorState;
}
ERROR_STATE RTC_enumReadCalendar(RTC_Date * Copy_struct_ptr_Date)
{
	ERROR_STATE Local_enumErrorState = NOK;
	//< To be Implemented later
	return Local_enumErrorState;
}

static void RTC_ProcessTime(RTC_Time * Copy_struct_ptr_retTime , u8* Copy_ptr_arr_ReadData)
{
	Copy_struct_ptr_retTime->Seconds =(Copy_ptr_arr_ReadData[0] >> 4)* 10 ;
	Copy_struct_ptr_retTime->Seconds +=(Copy_ptr_arr_ReadData[0] & 0x0F);
	Copy_struct_ptr_retTime->Minutes =(Copy_ptr_arr_ReadData[1] >> 4)*10;
	Copy_struct_ptr_retTime->Minutes +=(Copy_ptr_arr_ReadData[1] & 0x0F);
	Copy_struct_ptr_retTime->HoursMode = Copy_ptr_arr_ReadData[2] & Hours_24;
	if( Copy_struct_ptr_retTime->HoursMode == Hours_12 )
	{
		Copy_struct_ptr_retTime->AM_PM = Copy_ptr_arr_ReadData[2] & AM ;
		Copy_struct_ptr_retTime->Hours = (Copy_ptr_arr_ReadData[2] >> 4 & 0x01) * 10 ;
		Copy_struct_ptr_retTime->Hours += (Copy_ptr_arr_ReadData[2] & 0x0F);
	}
	else
	{
		Copy_struct_ptr_retTime->Hours = (Copy_ptr_arr_ReadData[2] >> 4 & 0x03) * 10 ;
		Copy_struct_ptr_retTime->Hours += (Copy_ptr_arr_ReadData[2] & 0x0F);
	}

}
