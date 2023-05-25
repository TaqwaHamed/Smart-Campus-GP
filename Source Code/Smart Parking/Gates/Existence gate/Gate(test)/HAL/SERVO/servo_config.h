/*
 * servo_config.h
 *
 *  Created on: Dec 23, 2021
 *      Author: taqwa
 */

#ifndef HAL_SERVO_SERVO_CONFIG_H_
#define HAL_SERVO_SERVO_CONFIG_H_




#define SERVO_PWM_MODE		FAST_PWM_TOP_ICR1

#define SERVO_TIMER1_PWM_PRESCALER	FCLK_DEV_64

#define TIMER1_TOP_VALUE			2500

#define TIMER1_PULSE_TYPE			INVERTED

#define SERVO_TIMER0_CHANNEL		TIMER1_CHANNEL_A



#endif /* HAL_SERVO_SERVO_CONFIG_H_ */