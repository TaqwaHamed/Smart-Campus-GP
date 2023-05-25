/******************************************************************
 ****************** SWC     : PWM_interface.h	*******************
 ****************** DATE    : Nov 19, 2021		*******************
 ****************** Author  : Taqwa Hamed		*******************
 ****************** Version : V00				*******************
 *****************************************************************/

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#define INVERTED       1
#define NON_INVERTED   2

/// This Function is used to control the intensity of Voltage by changing the duty cycle.
///
/// @param 	f32 duty , u8 pulse
/// @return 	void
/// in case non_inverted : Duty cycle=[OCR+1 /(2^n)]
/// in case inverted : Duty cycle=[1-(OCR+1 /(2^n))]
/// This Function gives Output RMS = Amplitude * sqrt(duty Cycle)
/// @note       in case inverted the pulse starts from low.
/// @note 	in case non_inverted the pulse starts from high.

void T0_FastPwm(f32 duty, u8 pulse);


/// This Function is used to control the intensity of Voltage by changing the duty cycle.
///
/// @param 	f32 duty , u8 pulse
/// @return 	void
/// in case non_inverted : Duty cycle=[OCR/(2^n -1)]
/// in case inverted : Duty cycle=[1- OCR/(2^n -1)]
/// @note       in case inverted the pulse starts from low.
/// @note 	in case non_inverted the pulse starts from high.
void T0_PhaseCorrectPwm(f32 duty,u8 pulse);


#endif /* PWM_INTERFACE_H_ */
