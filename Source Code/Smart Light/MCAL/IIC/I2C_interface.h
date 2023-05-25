/***********************************************************************/
/** author  : Ibrahim Saber Mohammed								  **/
/** Date    : 4 Nov 2021											  **/
/** Version : V00 													  **/
/***********************************************************************/

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

typedef enum{
	STANDARD_SPEED = 32,
	FAST_SPEED = 2
}I2C_SPEED;

typedef enum{
	I2C_GENERAL_CALL_DISABLE ,
	I2C_GENERAL_CALL_ENABLE
}GENERAL_CALL ;

typedef struct{
	I2C_SPEED speed;
	u8 NodeAddress;
	GENERAL_CALL G_CALL ;
}I2C_MASTER_CONFIG;

typedef struct{
	u8 NodeAddress;
	GENERAL_CALL G_CALL ;
}I2C_SLAVE_CONFIG;

/// Initialization Function to configure the I2C Mode (MASTER , SLAVE ) and the Node Address and the Bus speed
/// @param 		void
/// @return 	void
/// @note 		The Configurations is pre-build this can not be changed in the runtime
/// @warning  	make Sure you have Wrote the Write Configurations as the Options commented
void I2C_voidInit(void);
void I2C_MASTER_voidSetConfigure(I2C_MASTER_CONFIG Copy_structConfigurations);

/// This Function is sending the Start condition on the bus
/// @param 		void
/// @return 	Enumeration ErrorState to Indicate if the Function has run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to Know if the Master is now controlling the bus or another master does
ERROR_STATE I2C_MASTER_enumSendStart(void);

/// This Function is sending the Repeated Start on the bus
/// Repeated Start is used so the Master does not leave the bus and call another Slave or change Operation
/// @param 		void
/// @return 	Enumeration ErrorState to Indicate if the Function has run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
ERROR_STATE I2C_MASTER_enumSendRepeatedStart(void);


/// This Function is sending the Stop condition on the bus. Master ends the communication
/// @param 		void
/// @return 	void
/// @warning 	This Function is called by Master Only
void I2C_MASTER_voidSendSTOP(void);

/// This Function is sending the Slave Address for Reading Operation (Master wants Data from the Slave)
/// @param 		u8 Copy_u8SlaveAddress (the Slave Address )
/// @return 	Enumeration ErrorState to Indicate if the Function have run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to go on the rest of code
/// @note 		The Slave address is 7-bit length must not be greater than 127
ERROR_STATE I2C_MASTER_enumSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

/// This Function is sending the Slave Address for Writing Operation (Master Provides Data To the Slave)
///
/// @param 		u8 Copy_u8SlaveAddress (the Slave Address )
/// @return 	Enumeration ErrorState to Indicate if the Function have run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to go on the rest of code
/// @note 		The Slave address is 7-bit length must not be greater than 127

ERROR_STATE I2C_MASTER_enumSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

/// This Function is sending One Byte to the Slave
///
/// @param 		u8 Copy_u8Data (the Byte Wanted to be sent )
/// @return 	Enumeration ErrorState to Indicate if the Function have run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to go on the rest of code

ERROR_STATE I2C_MASTER_enumSendByte(u8 Copy_u8Data);

/// This Function is Reading One Byte to the Slave
///
/// This Function reads only one byte then sending NAK to the slave so that the Master does not need any other data
/// @param 		u8 * Copy_u8Data (a pointer to unsigned character variable to save the data to  )
/// @return 	Enumeration ErrorState to Indicate if the Function have run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to go on the rest of code
/// @note 		If you want to read Multiple Bytes using this Function you need to Send Repeated Start and repeat the Steps again till this step
ERROR_STATE I2C_MASTER_enumReadByte_With_NACK(u8 * Copy_u8Data);

/// This Function is Reading One Byte to the Slave
///
/// This Function reads one byte then sending ACK to the slave so that the Master need another data
/// The Master will receive data until transmitting NACK to the Slave
/// @param 		u8 * Copy_u8Buffer(a pointer to unsigned character variable or array to save the data to  )
/// @return 	Enumeration ErrorState to Indicate if the Function have run successfully (OK = Function is Done , NOK = the Function went wrong)
/// @warning 	This Function is called by Master Only
/// @note 		You need to check the return of the function to go on the rest of code
ERROR_STATE I2C_MASTER_enumReadByte_With_ACK(u8 * Copy_u8Buffer);

void I2C_SLAVE_voidSetConfigure ( I2C_SLAVE_CONFIG Copy_structConfigurations );


ERROR_STATE I2C_SLAVE_Listen_Adress_MASTER_Read(void);
ERROR_STATE I2C_SLAVE_Listen_Adress_MASTER_Write(void);
ERROR_STATE I2C_SLAVE_enumSendByte_NACK(u8 Copy_u8Data);
ERROR_STATE I2C_SLAVE_enumReadByte(u8 * Copy_u8Data);




#endif
