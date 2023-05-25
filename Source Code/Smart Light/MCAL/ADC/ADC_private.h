/******************************************************************
 ****************** SWC     : ADC_private.h		*******************
 ****************** DATE    : Nov 18, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX_Reg 	*((volatile u8*)0x27)
#define ADCSRA_Reg 	*((volatile u8*)0x26)
#define ADCH_Reg 	*((volatile u8*)0x25)
#define ADCL_Reg 	*((volatile u8*)0x24)


#define   ADC_INTERNAL_VCC    (1<<6) | (0<<7)
#define   ADC_INTERNAL_2_56   (1<<6) | (1<<7)
#define   ADC_EXTERNAL_AREF   (0<<6) | (0<<7)

#define ADC_LEFT_ADJUST_ENABLE 	(1 << 5)
#define ADC_RIGHT_ADJUST_ENABLE (0 << 5)

#define ADC_ENABLE				(1 << 7)
#define ADC_DISABEL				(0 << 7)

#define ADC_ENABLE_INTERRUPT    (1 << 3)
#define ADC_DISABLE_INTERRUPT	(0 << 3)

#define  ADC_pre_2		     	 ( 0b001 )
#define  ADC_pre_4               ( 0b010 )
#define  ADC_pre_8               ( 0b011 )
#define  ADC_pre_16              ( 0b100 )
#define  ADC_pre_32              ( 0b101 )
#define  ADC_pre_64              ( 0b110 )
#define  ADC_pre_128             ( 0b111 )




#endif /* ADC_PRIVATE_H_ */
