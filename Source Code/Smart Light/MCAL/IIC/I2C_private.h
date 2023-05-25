/***********************************************************************/
/** author  : Ibrahim Saber Mohammed								  **/
/** Date    : 4 May 2021											  **/
/** Version : V00 													  **/
/***********************************************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWDR  		*( (volatile u8 * const) 0x23 )
#define TWAR  		*( (volatile u8 * const) 0x22 )
#define TWSR  		*( (volatile u8 * const) 0x21 )
#define TWBR  		*( (volatile u8 * const) 0x20 )

typedef union{
	u8 Byte;
	struct{
		u8 TWIE  : 1;
		u8 RES   : 1;
		u8 TWEN  : 1;
		u8 TWWC  : 1;
		u8 TWSTO : 1;
		u8 TWSTA : 1;
		u8 TWEA  : 1;
		u8 TWINT : 1;
	}Bit;
}TWCR_REG;

#define TWCR 			((volatile TWCR_REG * const)0x56) 

#define I2C_STANDARD_SPEED 		32
#define I2C_FAST_SPEED   		2
#define MASTER 		1
#define SLAVE 		0

#define GEN_CALL_ENABLE   1
#define GEN_CALL_DISABLE  0
#endif
