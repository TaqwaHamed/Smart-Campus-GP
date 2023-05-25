/***********************************************
 * App.c
 *
 * Created: 19/11/2021
 *
 * Author: Ahmed LNiwehy
 **********************************************/


#include "App.h"


#define ADC_Reading         (ADC_Read(CURRENT_PIN) - Erorr_Reading)
#define Sensor_Reading		( (ACS_Reference_Point - ADC_Reading) / ADC_MAX) * CURRENT_REF
#define Current_Value   abs( (Sensor_Reading - ACS_Offset_voltage) / ACS_Sensitivity )

float voltage_read(void)
{
	ADC_Init();
	return (ADC_Read(VOLTAGE_PIN) * (ADC_REF / ADC_MAX) * (VOLTAGE_SRC / VOLTAGE_REF));
}


float current_read(void)
{
	ADC_Init();
	return ((Current_Value)/1000);
}