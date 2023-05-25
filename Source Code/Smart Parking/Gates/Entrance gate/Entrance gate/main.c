/*
 * main.c
 *
 * Created: 2/22/2022 9:42:58 PM
 *  Author: Kholoud khaled
 */ 
#include "MCAL/DIO/DIO.h"
#include "LIB/Delay.h"
#include "MCAL/UART/UART.h"
#include "HAL/LCD/LCD.h"
#include "HAL/PIR/PIR.h"
#include "HAL/SERVO/servo_interface.h"
#include "HAL/RFID/mfrc522.h"

#define   F_CPU 8000000UL
#include "util/delay.h"

#define  authorized    1
#define  Unauthorized  0
#define  car_number   20

int main(void)
{
	uint8 id[4];
	uint8 flag ,spot=0;
	//initialization 
	PIR_Init(PORTD_REG,PIN1);
	SERVO_voidInit();
	LCD_Init();
	USART_voidInit(9600);
	mfrc522_init();
	//Set Pin Direction 
	DIO_Set_DDR_PIN(PORTC_REG,PIN0,OUTPUT);//for servo
	DIO_Set_DDR_PIN(PORTC_REG,PIN5,OUTPUT);//for Buzzer
	DIO_Set_DDR_PIN(PORTC_REG,PIN6,OUTPUT);//for red led
	DIO_Set_DDR_PIN(PORTC_REG,PIN7,OUTPUT);//for green led
	DIO_Set_DDR_PIN(PORTD_REG,PIN1,INPUT);//for PIR
	
	while(1)
	{
		//gate locked
		SERVO_voidMoveAngle(0);
		// If there is a car want to enter and there is spot inside system start
		if(PIR_Read(PORTA_REG, PA0)==1 && spot <car_number){
			LCD_Send_str ("Welcome at Entrance gate");
			LCD_GotoXY(0,1);
			LCD_Send_str ("Please Enter your ID:");
			//get ID from RFID card
			id[4] = mfrc522_get_card_serial(& id);
			//send ID to the main MCU 
			for (uint8 i=0;i<=3;i++){
				USART_voidSend(id[i]);
			}
			LCD_Clear_Screen();
			// Recieve flag from main MCU  (if ID authorized or not )
			flag=USART_u8Recieve();
			//if ID authorized (ID is allowed to enter the park)
			if (flag==1){
				//open the gate 
				SERVO_voidMoveAngle(90);
				LCD_GotoXY(0,1);
				LCD_Send_str ("Thank you");
				LCD_GotoXY(0,1);
				LCD_Send_str ("the Gate is opened");
				//Green led on
				DIO_Set_PIN(PORTC_REG,PIN7,HIGH);
				spot++;
				Delay_ms (3000); //wait until the car enter 
			}
			//if ID unauthorized (ID is not allowed to enter the park)
			else if (flag==0){
				LCD_GotoXY(0,1);
				LCD_Send_str ("this ID is not allowed to enter the  park");
				DIO_Set_PIN(PORTC_REG,PIN6,HIGH);//red led on
				DIO_Set_PIN(PORTC_REG,PIN5,HIGH);//Alarm is beeping
				
			}
		}
	}
}