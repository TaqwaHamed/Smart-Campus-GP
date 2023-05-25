/*
 * main.c
 *
 * Created: 2/22/2022 8:06:02 PM
 *  Author: Yasmeen
 */ 

#include "HAL/LCD/LCD.h"
#include "HAL/SERVO/servo_interface.h"
#include "HAL/PIR/PIR.h"
#include "HAL/RFID/mfrc522.h"
#include "MCAL/PWM/PWM_interface.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/UART/UART.h"
#include "LIB/Delay.h"

#define authorized    1
#define Unauthorized  0

int main(void)
{
	uint8 id[4];
	uint8 Value,flag,spot,flag1=0;
	
	//Set PINS Direction
    DIO_Set_DDR_PIN(PORTA_REG , PA1 ,OUTPUT);
	DIO_Set_DDR_PIN(PORTA_REG , PA3 ,OUTPUT);
	DIO_Set_DDR_PIN(PORTA_REG , PA2 ,OUTPUT);
	
	//initilization
	LCD_Init();
	PIR_Init(PORTA_REG , PA0);
	SERVO_voidInit();
	USART_voidInit(9600);
	mfrc522_init();

	while (1)
	{
		Value=PIR_Read(PORTA_REG, PA0);
		//if there is a car
		if(Value==1 && flag1==0 && spot>0)
		{
			LCD_Send_str("Goodbye");
			LCD_GotoXY(0,1);
			LCD_Send_str("Enter ID Please!");
			Delay_ms(600);
			//get ID from RFID card
			id[4] = mfrc522_get_card_serial(&id);
			//send ID to the main MCU 
			for (uint8 i=0;i<=3;i++)
			{
				USART_voidSend(id[i]);
			}
			// Recieve flag from main MCU 
			flag=USART_u8Recieve();
			if (flag==1) //authorized_id
			{
				LCD_CMD(0x01);
				LCD_Send_str("Thank you");
				//Control gate(open&close)
				SERVO_voidMoveAngle(0);
				Delay_ms(1000);
				SERVO_voidMoveAngle(90);
				LCD_GotoXY(0,1);
				LCD_Send_str("Gate is opened");
				DIO_Set_PIN(PORTA_REG , PA1 ,HIGH); //Green led on
				spot--;
				LCD_CMD(0x01);
				LCD_Send_str("garage has space");
				flag1=1;
			}
			else if(flag==0)  // unauthorized_id 
			{
				LCD_CMD(0x01);
				LCD_Send_str("Unauthorized ID");
				DIO_Set_PIN(PORTA_REG , PA2 ,HIGH); //Red led on
				DIO_Set_PIN(PORTA_REG , PA3 ,HIGH); //Alarm is beeping
			}
		}
		else
		{
			
		}
	}
}