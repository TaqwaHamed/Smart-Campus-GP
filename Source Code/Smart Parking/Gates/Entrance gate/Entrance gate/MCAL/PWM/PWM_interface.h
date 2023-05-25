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

#define FAST_PWM_TOP_ICR1	0

#define FCLK_DEV_256		1
#define FCLK_DEV_64			2


#define TIMER1_CHANNEL_A	0
#define TIMER1_CHANNEL_B	1


/// This Function is used to control the intensity of Voltage by changing the duty cycle.
///
/// @param 	f32 duty , u8 pulse
/// @return 	void
/// in case non_inverted : Duty cycle=[OCR+1 /(2^n)]
/// in case inverted : Duty cycle=[1-(OCR+1 /(2^n))]
/// This Function gives Output RMS = Amplitude * sqrt(duty Cycle)
/// @note       in case inverted the pulse starts from low.
/// @note 	in case non_inverted the pulse starts from high.

void T0_FastPwm(f32 duty, uint8 pulse);


/// This Function is used to control the intensity of Voltage by changing the duty cycle.
///
/// @param 	f32 duty , u8 pulse
/// @return 	void
/// in case non_inverted : Duty cycle=[OCR/(2^n -1)]
/// in case inverted : Duty cycle=[1- OCR/(2^n -1)]
/// @note       in case inverted the pulse starts from low.
/// @note 	in case non_inverted the pulse starts from high.
void T0_PhaseCorrectPwm(f32 duty,uint8 pulse);


void T1_FastPWM_Configs(uint8 Copy_u8Prescaler ,uint8 copy_u8Mode , uint16 Copy_u16TopValue);

void T1_FastPWM(f32 Copy_u16DutyCycle , uint8 Copyu8_Pulse , uint8 Copy_u8ChannelNumber , uint16 Copy_u16TopValue);

#endif /* PWM_INTERFACE_H_ */
