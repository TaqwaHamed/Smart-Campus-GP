/*
 * main.c
 *
 *  Created on: Nov 18, 2021
 *      Author: Taqwa Hamed
 */

/// Inclusion of the Libraries
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../LIB/BIT_MATH/BIT_MATH.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/IIC/I2C_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/PWM/PWM_interface.h"
#include "../MCAL/UART/UART.h"

#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/RTC_DS1307/RTC_interface.h"
#include "../HAL/LDR/LDR_interface.h"

#include "util/delay.h"

/// Definition of the Addresses in the EEPROM
#define HOUR_SUNRISE     0
#define MINUTE_SUNRISE   1
#define HOUR_SUNSET      2
#define MINUTE_SUNSET    3

#define SUNSET 		0
#define SUNRISE		1

u8 Local_u8EEpromSET_HOURS=0;
u8 Local_u8EEpromSET_MIN=0;
u8 Local_u8EEpromRIS_Hours = 0;
u8 Local_u8EEpromRIS_Min = 0;

// added : modification of EEPROM_voidWriteTime() Function *****************
u8 Local_u8EEpromWRSET_HOURS=6;
u8 Local_u8EEpromWRSET_MIN=15;
u8 Local_u8EEpromWRRIS_Hours = 17;
u8 Local_u8EEpromWRRIS_Min = 20;


void EEPROM_voidWriteTime(u8 Local_u8EEpromWRSET_HOURS,u8 Local_u8EEpromWRSET_MIN,u8 Local_u8EEpromWRRIS_Hours ,u8 Local_u8EEpromWRRIS_Min) // this Will change later*****************
{
	EEPROM_enumWriteByte(HOUR_SUNRISE,Local_u8EEpromWRRIS_Hours);
	_delay_ms(10);
	EEPROM_enumWriteByte(MINUTE_SUNRISE,Local_u8EEpromWRRIS_Min);
	_delay_ms(10);
	EEPROM_enumWriteByte(HOUR_SUNSET,Local_u8EEpromWRSET_HOURS);
	_delay_ms(10);
	EEPROM_enumWriteByte(MINUTE_SUNSET,Local_u8EEpromWRSET_MIN);
	_delay_ms(10);
}

void EEPROM_ReadTime(void)
{
	EEPROM_enumReadByte(HOUR_SUNSET,&Local_u8EEpromSET_HOURS);
	EEPROM_enumReadByte(MINUTE_SUNSET,&Local_u8EEpromSET_MIN);
	EEPROM_enumReadByte(HOUR_SUNRISE,&Local_u8EEpromRIS_Hours);
	EEPROM_enumReadByte(MINUTE_SUNRISE,&Local_u8EEpromRIS_Min);
}
int main(void)
{
	_delay_ms(100);
	ADC_VoidInit();
	LDR_SENSOR_voidInit(ADC_6);
	I2C_voidInit();
	// added : Init UART   *****************
	USART_voidInit(9600);
	
	u8 local_u8SunSetFlag = SUNRISE;
	u8 Local_u8inti=0 ;
	u8 Local_u8Cluod_UpdateTime = 0;
	RTC_Time Time;
	Time.Seconds = 50;
	Time.Minutes = 19;
	Time.Hours = 17;
	Time.HoursMode = Hours_24;
	Time.AM_PM = PM;
	RTC_enumUpdateTime(&Time);

	// Modified : as new deceleration *****************
	EEPROM_voidWriteTime( Local_u8EEpromWRSET_HOURS, Local_u8EEpromWRSET_MIN, Local_u8EEpromWRRIS_Hours , Local_u8EEpromWRRIS_Min); // this function just write initial data to EEPROM
	EEPROM_ReadTime(); // to and read time and save it to the variables to be checked
	
	// added : PIN DIR for Switch		*****************
	DIO_SetPinDirection(PORTC,PIN0,INPUT);

	while(1)
	{
		
		// get status of Switch *****************
		DIO_GetPinValue(PORTC_REG,PIN0,&Local_u8Cluod_UpdateTime);
		// this Will be valuable in the second release *****************
		if (Local_u8Cluod_UpdateTime == 1)
		{
			// Update RTC Time
			Time.Hours = USART_u8Recieve();
			_delay_ms(200);
			Time.Minutes   = USART_u8Recieve();
			_delay_ms(200);
			Time.Seconds = USART_u8Recieve();
			_delay_ms(200);
			
			// call Function
			RTC_enumUpdateTime(&Time);
			
			// get Sunrise and Sunset Values From NodeMCU
			Local_u8EEpromWRSET_HOURS = USART_u8Recieve();
			_delay_ms(200);
			Local_u8EEpromWRSET_MIN   = USART_u8Recieve();
			_delay_ms(200);
			Local_u8EEpromWRRIS_Hours = USART_u8Recieve();
			_delay_ms(200);
			Local_u8EEpromWRRIS_Min   = USART_u8Recieve();
			_delay_ms(10);
			// Update EEPROM
			EEPROM_voidWriteTime( Local_u8EEpromWRSET_HOURS, Local_u8EEpromWRSET_MIN, Local_u8EEpromWRRIS_Hours , Local_u8EEpromWRRIS_Min);
			EEPROM_ReadTime();  // Read New Time after updating
			
		}
		
		
		Local_u8inti=LDR_SNESOR_u8Read(ADC_6); // Reading the Temperature and convert back to analog and return the percentage of Ligh
		RTC_enumReadTime(&Time); // Read the Time form RTC

		if(Time.HoursMode==Hours_24)
		{
			/// Checking the Time is after the sunset time or before the sunrise time to keep controlling the light
			if( ((Time.Hours > Local_u8EEpromSET_HOURS) || ( Time.Hours == Local_u8EEpromSET_HOURS && Time.Minutes >= Local_u8EEpromSET_MIN )) )
			{
				local_u8SunSetFlag = SUNSET; // Raise flag that it's sunset
			}
			else if ( (Time.Hours < Local_u8EEpromRIS_Hours) || ((Time.Hours == Local_u8EEpromRIS_Hours) && (Time.Minutes <= Local_u8EEpromRIS_Min) ))
			{
				local_u8SunSetFlag = SUNSET; // Raise flag that it's sunset
			}
			else
			{
				local_u8SunSetFlag = SUNRISE;
			}
		}

		if(local_u8SunSetFlag == SUNSET) // if the Sunset time flag is raised
		{
			/// according to the light intensity we control the LED array intensity
			if(Local_u8inti>90)
			{
				T0_PhaseCorrectPwm(0,INVERTED); /// LED is Off
			}
			else if(Local_u8inti<90 && Local_u8inti>70)
			{
				T0_PhaseCorrectPwm(30,INVERTED);  /// LED is on by 30% of its full intensity
			}
			else if(Local_u8inti>50 && Local_u8inti<70)
			{
				T0_PhaseCorrectPwm(50,INVERTED);	/// LED is on by 50% of its full intensity
			}
			else if(Local_u8inti<50 && Local_u8inti>30)
			{
				T0_PhaseCorrectPwm(70,INVERTED); /// LED is on by 70% of its full intensity
			}
			else if(Local_u8inti<30 )
			{
				T0_PhaseCorrectPwm(100,INVERTED); /// LED is on by 100% of its full intensity
			}
		}
		else
		{
			T0_PhaseCorrectPwm(0,INVERTED); /// LED is Off
		}

	}
	return 0;
}


