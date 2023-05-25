/******************************************************************
 ****************** SWC     : ADC_config.h		*******************
 ****************** DATE    : Nov 18, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
  	ADC_INTERNAL_VCC
	ADC_INTERNAL_2_56
	ADC_EXTERNAL_AREF
 */
#define ADC_REFERNECE_VOLTAGE 		ADC_INTERNAL_VCC

/*	ADC_LEFT_ADJUST_ENABLE
	ADC_LEFT_ADJUST_DISABEL
*/

#define ADLAR				ADC_LEFT_ADJUST_ENABLE

/*
  ADC_ENABLE
  ADC_DISABEL
 */
#define ADC_STATE			ADC_ENABLE

/*
   ADC_ENABLE_INTERRUPT
   ADC_DISABLE_INTERRUPT
 */

#define ADC_INTERRUPT		ADC_DISABLE_INTERRUPT

/*
ADC_pre_2						( 0b001 )
ADC_pre_4                       ( 0b010 )
ADC_pre_8                       ( 0b011 )
ADC_pre_16                      ( 0b100 )
ADC_pre_32                      ( 0b101 )
ADC_pre_64                      ( 0b110 )
ADC_pre_128                     ( 0b111 )

 */
#define ADC_prescaller						ADC_pre_128

#endif /* ADC_CONFIG_H_ */
