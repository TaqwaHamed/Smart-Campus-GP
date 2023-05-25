/*
 * LDR_interface.h
 *
 *  Created on: Nov 18, 2021
 *      Author: taqwa
 */

#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

/// Initializing the LDR
///
/// Selecting the LDR PIN Direction
/// The pin perform the channel number
/// @param  : u8 Copy_u8ChannelNumber
/// @return : void
void LDR_SENSOR_voidInit(u8 Copy_u8ChannelNumber);

/// Reading a specific ADC Channel
///
/// This Function is used to read the LDR Resistance
/// first read the Digital value Converted by the ADC from wanted Channel
/// then convert the digital value to analog.
/// Analog value = Step value * Digital value
/// @param  u8 Copy_u8ChannelNumber
/// @return u8 variable : that represents the light Intensity which calculated from map function.
/// @see static f32  MAP
/// @warning The Copy_u8Channel_Id is a pin from ADC_0 to ADC_7
/// @warning This Function must be called after LDR_SENSOR_voidInit.
/// @see LDR_SENSOR_voidInit
u8 LDR_SNESOR_u8Read(u8 Copy_u8ChannelNumber);

#endif /* LDR_INTERFACE_H_ */
