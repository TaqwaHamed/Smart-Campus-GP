/*
 * mfrc522_cmd.h
 *
 * Created: 28/12/2021 
 * Author : Ahmed LNiwehy
 */ 


#ifndef MFRC522_CMD_H
#define MFRC522_CMD_H

//command set
#define Idle_CMD 				0x00
#define Mem_CMD					0x01
#define GenerateRandomId_CMD	0x02
#define CalcCRC_CMD				0x03
#define Transmit_CMD			0x04
#define NoCmdChange_CMD			0x07
#define Receive_CMD				0x08
#define Transceive_CMD			0x0C
#define Reserved_CMD			0x0D
#define MFAuthent_CMD			0x0E
#define SoftReset_CMD			0x0F                // resets the MFRC522

#endif
