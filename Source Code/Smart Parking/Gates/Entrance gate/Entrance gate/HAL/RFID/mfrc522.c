/*
 * mfrc522.c
 *
 * Created: 28/12/2021 
 * Author : Ahmed LNiwehy
 */ 

#include "mfrc522.h"


/*
 * Function Name : mfrc522_init
 * Description : Initialize RC522
 * Input: None
 * Return value: None
 */
void mfrc522_init()
{
	uint8 byte;
	mfrc522_reset();
	
	mfrc522_write(TModeReg, 0x8D);          // TModeReg and TPrescalerReg registers these registers define the timer settings.
    mfrc522_write(TPrescalerReg, 0x3E);		   
    mfrc522_write(TReloadReg_1, 30);        // TReloadReg register(TReloadReg_1 & TReloadReg_2) defines the 16-bit (two 8-bits) timer  reload value.
    mfrc522_write(TReloadReg_2, 0);			   
	mfrc522_write(TxASKReg, 0x40);	        // forces a 100 % ASK modulation independent of the ModGsPReg register setting
	mfrc522_write(ModeReg, 0x3D);           // ModeReg register defines general mode settings for transmitting and receiving.
	
	byte = mfrc522_read(TxControlReg);      // TxControlReg register Controls the logical behavior of the antenna driver pins TX1 and TX2.
	if(!(byte&0x03))
	{
		mfrc522_write(TxControlReg,byte|0x03);
	}
}

/*
 * Function Name : mfrc522_write
 * Description: MFRC522 of a register to write a byte of data
 * The interface is described in the datasheet section 8.1.2.
 * Input Parameters : reg - register address ; data - the value to be written
 * Return value: None
 */
void mfrc522_write(uint8 reg, uint8 data)
{
	ENABLE_CHIP();
	// Address Format :0XXXXXX0
	SPI_Send((reg<<1)&0x7E);        // init to write data & select the address to which we write data
	SPI_Send(data);                 // data that will be written
	DISABLE_CHIP();
}

/*
 * Function Name : mfrc522_read
 * Description : From a certain MFRC522 read a byte of data register
 * Input Parameters : reg - register address
 * Return value : Returns a byte of data read from the
 */
uint8 mfrc522_read(uint8 reg)
{
	uint8 data;	
	ENABLE_CHIP();
	// Address Format : 1XXXXXX0
	SPI_Send(((reg<<1)&0x7E)|0x80);  // init to read data & select the address from which we read data
	data = SPI_SendReceive(0x00);           // receieve that we read
	DISABLE_CHIP();
	return data;
}

/*
 * Function Name : mfrc522_reset
 * Description : Reset RC522
 * Input: None
 * Return value: None
 */
void mfrc522_reset()
{
	/* 
	CommandReg register: Starts and stops command execution.
	*/
	mfrc522_write(CommandReg,SoftReset_CMD);
}

/*
 * Function Name : mfrc522_request
 * Description : Find cards , read the card type number
 * Input parameters : req_Mode - find cards way
 * Tag_Type - Return Card Type
 * 0x4400 = Mifare_UltraLight
 * 0x0400 = Mifare_One (S50)
 * 0x0200 = Mifare_One (S70)
 * 0x0800 = Mifare_Pro (X)
 * 0x4403 = Mifare_DESFire
 * Return value: the successful return MI_OK
 */
uint8	mfrc522_request(uint8 req_mode, uint8 * tag_type)
{
	uint8  status;  
	uint32 backBits;//The received data bits

	mfrc522_write(BitFramingReg, 0x07);//TxLastBists = BitFramingReg[2..0]	???
	
	tag_type[0] = req_mode;
	status = mfrc522_to_card(Transceive_CMD, tag_type, 1, tag_type, &backBits);

	if ((status != CARD_FOUND) || (backBits != 0x10))
	{    
		status = ERROR;
	}
   
	return status;
}

/*
 * Function Name : mfrc522_to_card
 * Description : RC522 and ISO14443 card communication
 * Input Parameters : cmd - MF522 command word,
 * send_data - RC522 sent to the card via the data
 * send_data_len - length of data sent
 * back_data - received the card returns data,
 * back_data_len - return data bit length
 * Return value: the successful return MI_OK
 */
uint8 mfrc522_to_card(uint8 cmd, uint8 *send_data, uint8 send_data_len, uint8 *back_data, uint32 *back_data_len)
{
	uint8 status = ERROR;
    uint8 irqEn = 0x00;
    uint8 waitIRq = 0x00;
    uint8 lastBits;
    uint8 n;
    uint8	tmp;
    uint32 i;

    switch (cmd)
    {
        case MFAuthent_CMD:		//Certification cards close
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case Transceive_CMD:	//Transmit FIFO data
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
    }
   
    //mfrc522_write(ComIEnReg, irqEn|0x80);	//Interrupt request
    n=mfrc522_read(ComIrqReg);
    mfrc522_write(ComIrqReg,n&(~0x80));//clear all interrupt bits
    n=mfrc522_read(FIFOLevelReg);
    mfrc522_write(FIFOLevelReg,n|0x80);//flush FIFO data
    
	mfrc522_write(CommandReg, Idle_CMD);	//NO action; Cancel the current cmd???

	//Writing data to the FIFO
    for (i=0; i<send_data_len; i++)
    {   
		mfrc522_write(FIFODataReg, send_data[i]);    
	}

	//Execute the cmd
	mfrc522_write(CommandReg, cmd);
    if (cmd == Transceive_CMD)
    {    
		n=mfrc522_read(BitFramingReg);
		mfrc522_write(BitFramingReg,n|0x80);      //StartSend=1,transmission of data starts 
	}   
    
	//Waiting to receive data to complete
	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
    do 
    {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = mfrc522_read(ComIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	tmp=mfrc522_read(BitFramingReg);
	mfrc522_write(BitFramingReg,tmp&(~0x80));
	
    if (i != 0)
    {    
        if(!(mfrc522_read(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
        {
            status = CARD_FOUND;
            if (n & irqEn & 0x01)
            {   
				status = CARD_NOT_FOUND;			//??   
			}

            if (cmd == Transceive_CMD)
            {
               	n = mfrc522_read(FIFOLevelReg);
              	lastBits = mfrc522_read(ControlReg) & 0x07;
                if (lastBits)
                {   
					*back_data_len = (n-1)*8 + lastBits;   
				}
                else
                {   
					*back_data_len = n*8;   
				}

                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAX_LEN)
                {   
					n = MAX_LEN;   
				}
				
				//Reading the received data in FIFO
                for (i=0; i<n; i++)
                {   
					back_data[i] = mfrc522_read(FIFODataReg);    
				}
            }
        }
        else
        {   
			status = ERROR;  
		}
        
    }
	
    //SetBitMask(ControlReg,0x80);           //timer stops
    //mfrc522_write(cmdReg, PCD_IDLE); 

    return status;
}

/*
 * Function Name : mfrc522_get_card_serial
 * Description : get card serial ID
 * Input Parameters : serial_out : ID serial
 * Return value: the successful return MI_OK
 */
uint8 mfrc522_get_card_serial(uint8 * serial_out)
{
	uint8 status;
    uint8 i;
	uint8 serNumCheck=0;
    uint32 unLen;
    
	mfrc522_write(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
 
    serial_out[0] = PICC_ANTICOLL;
    serial_out[1] = 0x20;
    status = mfrc522_to_card(Transceive_CMD, serial_out, 2, serial_out, &unLen);

    if (status == CARD_FOUND)
	{
		//Check card serial number
		for (i=0; i<4; i++)
		{   
		 	serNumCheck ^= serial_out[i];
		}
		if (serNumCheck != serial_out[i])
		{   
			status = ERROR;    
		}
    }
    return status;
}
