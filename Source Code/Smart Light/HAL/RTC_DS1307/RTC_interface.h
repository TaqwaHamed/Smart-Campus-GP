/*
 * RTC_interface.h
 *
 *  Created on: Nov 19, 2021
 *      Author: saber
 */

#ifndef HAL_RTC_DS1307_RTC_INTERFACE_H_
#define HAL_RTC_DS1307_RTC_INTERFACE_H_

#define Hours_12		0x40 //< Hours mode is 12 Hour
#define Hours_24		0x00 //< Hours mode is 24 Hour
#define AM				0x00 //< AM time
#define PM				0x20 //< PM time

/// Structure that contains all the Day parameters (Hour , Minute ,Seconds , AM or PM , 12 Hour mode or 24 Hour)
typedef struct Time{
	u8 Seconds	;
	u8 Minutes	;
	u8 Hours	;
	u8 AM_PM	;
	u8 HoursMode;
}RTC_Time;

//< Enumeration to carry the week days (The week starts from monday)
typedef enum{
	MONDAY = 1,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
}Week_Days;

//< Structure contains all the parameters to update the calendar(Month, Year , Day of the week ,day Date )
typedef struct Date{
	Week_Days Day ;
	u8 Date		;
	u8 Month	;
	u8 Year		;
}RTC_Date;

/// This Function is Used to Update the Time in RTC Module
///
/// This Function is saving the Hour and Minutes and seconds and the Hours Mode inside a register in the RTC
/// RTC Module is Communicating using I2C Bus
/// the addresses of the register is incremented automatically
/// This Function is Transmitting the RTC Module Address and the operation is writing to Send the Address of the register to Save the Time
/// @param 	: RTC_Time * Copy_struct_ptr_Time  Pinter to structure created by the user of the function
/// @return : ERROR_STATE this is enum to indicates if the function performed the functionality correctly or an error has been occurred
/// @warning: This Function is called after initializing the I2C Bus
/// @see : ../../MCAL/IIC/I2C_voidInit
ERROR_STATE RTC_enumUpdateTime(RTC_Time * Copy_struct_ptr_Time);

/// This Function is Used to Update the Calendar in RTC Module
///
/// This Function is saving the Calendar information a register in the RTC
/// RTC Module is Communicating using I2C Bus
/// This Function is Transmitting the RTC Module Address and the operation is writing to Send the Address of the register to Save the Time
/// @param 	: RTC_Date * Copy_struct_ptr_Date  Pinter to structure created by the user of the function
/// @return : ERROR_STATE this is enum to indicates if the function performed the functionality correctly or an error has been occurred
/// @warning: This Function is called after initializing the I2C Bus
/// @see : ../../MCAL/IIC/I2C_voidInit
/// @see : ../../MCAL/IIC/I2C_MASTER_enumSendRepeatedStart
/// @see : ../../MCAL/IIC/I2C_MASTER_enumSendSlaveAddressWithWrite
/// @note : if the Function had not been called then the RTC Will start Counting from pre-saved value
/// @warning: The year is a number from 0 to 99
/// @warning: Month must be a number from 1 to 12
/// @warning: Date is a number indicates the day date of the current month the max value is 31
/// @warning: Day is starting from Monday so the accepted value if from 1 to 7
ERROR_STATE RTC_enumUpdateCalendar(RTC_Date * Copy_struct_ptr_Date);

/// This Function is Used to Update the Time in RTC Module
///
/// This Function is Loading (Time Information )the Hour and Minutes and seconds and the Hours Mode inside a register in the RTC
/// RTC Module is Communicating using I2C Bus.
/// the addresses of the register is incremented automatically.
/// If the register address to load the value has not been sent then the RTC will read from the last register index
/// * So in this Function we send the Address with write operation
/// * Then send register address.
/// * Send repeated start
/// * Then re send the address with read operation
/// * Read the data using I2C Read Byte from Slave
/// This Function is Transmitting the RTC Module Address and the operation is writing to Send the Address of the register to Save the Time
/// @param 	: RTC_Time * Copy_struct_ptr_Time  Pinter to structure created by the user of the function
/// @return : ERROR_STATE this is enum to indicates if the function performed the functionality correctly or an error has been occurred
/// @warning: This Function is called after initializing the I2C Bus
/// @see : ../../MCAL/IIC/I2C_voidInit
/// @see : ../../MCAL/IIC/I2C_MASTER_enumSendRepeatedStart
/// @see : ../../MCAL/IIC/I2C_MASTER_enumSendSlaveAddressWithWrite
ERROR_STATE RTC_enumReadTime(RTC_Time * Copy_struct_ptr_Time);

/// this Function has not been implemented (not Used)
ERROR_STATE RTC_enumReadCalendar(RTC_Date * Copy_struct_ptr_Date);


#endif /* HAL_RTC_DS1307_RTC_INTERFACE_H_ */
