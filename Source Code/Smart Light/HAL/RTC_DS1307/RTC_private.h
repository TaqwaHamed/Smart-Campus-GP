/*
 * RTC_private.h
 *
 *  Created on: Nov 19, 2021
 *      Author: saber
 */

#ifndef HAL_RTC_DS1307_RTC_PRIVATE_H_
#define HAL_RTC_DS1307_RTC_PRIVATE_H_

#define RTC_SLAVE_ADDRESS			0x68
#define RTC_BASE_TIME_ADDRESS		0x00
#define RTC_BASE_CALENDER_ADDRESS	0x03

static void RTC_ProcessTime(RTC_Time * Copy_struct_ptr_retTime , u8* Copy_ptr_arr_ReadData);

#endif /* HAL_RTC_DS1307_RTC_PRIVATE_H_ */
