/******************************************************************
 ****************** SWC     : ADC_interface.h	*******************
 ****************** DATE    : Nov 18, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/// Initializing the ADC
///
/// Selecting the ADC Reference Voltage value and the Adjustment of the data in the ADC Data register.
/// The Function also configures the pre-scaler value to chose the speed of the ADC.
/// The Function also configure to Enable/Disable The interrupt
/// @param  : void
/// @return : void
/// @note   : The function is pre-build configurations the Configurations can not be changed in the Runtime
/// @warning : The user must chose the right configuration in the _config.h
/// @warning : The Function must be called in the main before using the ADC_read Function
void ADC_VoidInit (void);

/// Reading a specific ADC Channel
/// This Function is used to read the Digital value Converted by the ADC from wanted Channel
/// This function returns the Digital value in u16 bit as the ADC is 10-bit
/// Step value = ((Vref_max - vref_min)/2^n )  ("n is the number of bits")
/// Analog value = Step value * Digital value
/// @param  u8 Copy_u8Channel_Id : Channel number to convert the analog voltage across
/// @return u16 variable : that represents that the digiatal value
/// @warning The Copy_u8Channel_Id is a pin from ADC_0 to ADC_7
/// @warning This Function must be called after ADC_VoidInit
/// @see ADC_VoidInit
u16 ADC_u16Read (u8 Copy_u8Channel_Id);

/// These are the Channel ID number to be used
/// these are the pins of PORTA registers
#define ADC_0					(0b00000)
#define ADC_1					(0b00001)
#define ADC_2					(0b00010)
#define ADC_3					(0b00011)
#define ADC_4					(0b00100)
#define ADC_5					(0b00101)
#define ADC_6					(0b00110)
#define ADC_7					(0b00111)

#endif /* ADC_INTERFACE_H_ */
