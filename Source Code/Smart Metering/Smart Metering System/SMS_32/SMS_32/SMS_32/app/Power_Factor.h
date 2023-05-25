/*
 * main.c
 *
 * Created: 11/20/2021 11:37:03 PM
 *  Author: kholoud
 */ 

#ifndef INCFILE1_H_
#define INCFILE1_H_

#include<math.h>


/* LIB include */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BitMath.h"
#include "../LIB/Delay.h"
/* Driver Include */
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/Timers/Timer.h"
#include "../MCAL/Interrupt/Interrupt.h"



 uint32 ZeroDetection();
float GetPowerFactor(uint32 T);
#endif /* INCFILE1_H_ */