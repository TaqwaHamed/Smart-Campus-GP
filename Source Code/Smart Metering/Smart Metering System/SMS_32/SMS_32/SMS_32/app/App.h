/***********************************************
 * App.h
 *
 * Created: 19/11/2021
 *
 * Author: Ahmed LNiwehy
 **********************************************/


#ifndef APP_H_
#define APP_H_
#include<math.h>

#include "../LIB/STD_TYPES.h"
#include "../MCAL/ADC/ADC.h"

#define ADC_REF					5
#define ADC_MAX					1023.0


#define VOLTAGE_PIN				0
#define CURRENT_PIN				1

#define VOLTAGE_REF				5.0
#define CURRENT_REF				5.0

#define VOLTAGE_SRC				220

#define Erorr_Reading           20  // ADC read without connect Current Sensor
#define ACS_Reference_Point     512 // reference point (511  for positive current and same  for negative)
#define ACS_Offset_voltage		2.5 // voltage which represent 0 current
#define ACS_Sensitivity			185
#define ACS_Max_Value			30

float voltage_read(void);
float current_read(void);


#endif /* APP_H_ */