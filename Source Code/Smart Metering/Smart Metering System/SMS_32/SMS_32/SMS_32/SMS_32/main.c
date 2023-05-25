/*
 *SMS_32.c
 *
 * Created: 6/27/2022 11:47:16 PM
 *  Author: Yasmeen
 */ 

#include "HAL/LCD/LCD.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/Interrupt/Interrupt.h"
#include "LIB/Delay.h"
#include "LIB/BitMath.h"
#include "app/Power_Factor.h"
#include "app/app.h"



#define measure_time 3.3

uint8 TOV_Counter = 0; // can't be removed it used in power_Factor.c as extern

int main(void)
{
	f32 pf=1;
	uint32 T=0;
	uint16 volt = 0 , current = 0;
	f32 power=1;
	//input& output ports  initialization
	//ADC PINS
	DIO_Set_DDR_PIN(PORTA_REG,PIN0,INPUT);	//VOLT
	DIO_Set_DDR_PIN(PORTA_REG,PIN1,INPUT);	//CURRENT
	//PF PINS
	DIO_Set_DDR_PIN(PORTA_REG,PIN2,INPUT);
	DIO_Set_DDR_PIN(PORTA_REG,PIN3,INPUT);
	
	// relay
	//DIO_Set_DDR_PIN(PORTD_REG,PIN0,OUTPUT);
	
	ADC_Init();
	LCD_Init();

	
	while (1)
	{
		//ToggleBit(PORTD,PIN0);
		// loop to take reading of PF to make sure we have a stable value of PF
		for (uint8 i=0;i<25;i++)
		{
			TOV_Counter = 0;
			T = ZeroDetection();
		}
		pf = GetPowerFactor(T);
		volt = voltage_read();
		current = current_read();
		power +=(volt*current*pf*measure_time)/(60000); // power in KWH
		
		//display
		//display voltage
		LCD_Send_str("Voltage : ");
		LCD_Send_RealNum(volt);
		LCD_Send_char('V');
		for (uint8 i_delay =0 ; i_delay<10;i_delay++)
		{
			Delay_ms(1200);
		}
		
		//display current
		LCD_GotoXY(0,1);
		LCD_Send_str("Current : ");
		LCD_Send_RealNum(current);
		LCD_Send_char('A');
		for (uint8 i_delay =0 ; i_delay<10;i_delay++)
		{
			Delay_ms(1200);
		}
		LCD_Clear_Screen();
		//display power factor
		LCD_Send_str("PF percentage");
		LCD_GotoXY(0,1);
		LCD_Send_Num(ceil(pf*100));
		LCD_Send_char('%');
		for (uint8 i_delay =0 ; i_delay<10;i_delay++)
		{
			Delay_ms(1200);
		}
		LCD_Clear_Screen();
		
		//display Consumed Power
		LCD_Send_str("Consumed Power");
		LCD_GotoXY(0,1);
		LCD_Send_RealNum(power);
		LCD_Send_str(" KWH");
		for (uint8 i_delay =0 ; i_delay<10;i_delay++)
		{
			Delay_ms(1200);
		}
		for (uint8 i_delay =0 ; i_delay<10;i_delay++)
		{
			Delay_ms(1200);
		}
		LCD_Clear_Screen();
	
	}
	return 0;
}