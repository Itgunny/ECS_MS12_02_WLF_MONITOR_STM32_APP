/**
  ******************************************************************************
  * @file    FM31X4.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   FM31X4.c module
  *
  * Project Name       : WL9F Monitor APP
  * Project Enviroment : IAREmbedded Workbench for ARM 6.5x 
  *                      STM32F407ZGT6 Firmware Library
  * Project Workspace  : WL9F_Monitor_APP
  * MCU Type           : STM32F407ZGT6
  *
  * TAEHA MECHATRONICS Co., Ltd (http://www.taeha.co.kr)				
  * ECS Division R&D Center. / Author by Young-Min Han (kutelf@taeha.co.kr)
  * 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h" 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern unsigned char Hardware_Revision;			// ++, --, 160511 bwk
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void NOP(void)
{
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
	__NOP; __NOP; __NOP; __NOP; __NOP; __NOP; __NOP; 
}

void EEPROM_PortChange(unsigned char dir)
{
	unsigned short temp;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if (dir)// Output
	{
		temp = FM31X4_I2C1_PORT->IDR;			//	GPIO_ReadInputData
		temp = ((~(FM31X4_I2C1_SDA)) & temp);
		FM31X4_I2C1_PORT->ODR = (temp);			//	GPIO_Write
		
		GPIO_InitStructure.GPIO_Pin   = FM31X4_I2C1_SDA;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
		GPIO_Init(FM31X4_I2C1_PORT, &GPIO_InitStructure);	
	}
	else	// Input
	{	
		temp = FM31X4_I2C1_PORT->IDR;			//	GPIO_ReadInputData
		temp = ((~(FM31X4_I2C1_SDA)) & temp);
		FM31X4_I2C1_PORT->ODR = (temp);			//	GPIO_Write
		
		GPIO_InitStructure.GPIO_Pin  = FM31X4_I2C1_SDA;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_Init(FM31X4_I2C1_PORT, &GPIO_InitStructure);	
	}
}

void EEPROM_ByteWrite ( unsigned char WData )
{
	unsigned char i,j;
	
	NOP();
	
	for ( i = 0; i < 8; i++ )
	{
		j = ( WData & 0x80 ) ? 1 : 0;
		(j) ? GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA) : GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

		NOP(); 
		SCL1; 
		NOP();
		
		WData <<= 1;

		SCL0;
		NOP();
	}
	
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

	NOP(); 
	SCL1; 
	NOP(); 
	SCL0;
}

unsigned char CheckEepromByteWrite ( void )  /* return 0 -> ok */
{
	unsigned char i, j;
	unsigned char WData = 0xa0;
	
	NOP(); 
	
	for ( i = 0; i < 8; i++ )
	{
		j = ( WData & 0x80 ) ? 1 : 0;
		(j) ? GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA) : GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

		NOP(); 
		SCL1;
		WData <<= 1;
		NOP(); 
		SCL0;
		NOP(); 
	}
	
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SDAIN;
	SCL1;
	NOP(); 
	i = SDA_READ;
	SCL0;
	SDAOUT;
	return (i);
}

unsigned char EEPROM_ByteRead ( void )
{
	unsigned char i;
	unsigned char RData;

	NOP(); 
	SCL0;
	NOP(); 
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAIN;

	for ( i = 0; i < 8; i++ )
	{
		SCL1;
		NOP(); 
		RData = (RData << 1) | SDA_READ;
		SCL0;
		NOP(); 
		NOP(); 
	}
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	return (RData );
}


void EEPROM_Write ( unsigned long Add, unsigned char WData )
{
	// ++, 160511 bwk
	if(Hardware_Revision < REVH)
	{
	// --, 160511 bwk
		GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		SDAOUT;
		/* start */
		GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		SCL1;
		NOP(); 
		GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		NOP(); 
		SCL0;
		/* start end */

		EEPROM_ByteWrite( 0xa0 );
		EEPROM_ByteWrite( (unsigned char)(Add >> 8) );
		EEPROM_ByteWrite( (unsigned char) Add );
		EEPROM_ByteWrite( WData );

		/* stop */
		GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		NOP(); 
		SCL1;
		NOP(); 
		GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	}		// ++, --, 160511 bwk
}


unsigned char EEPROM_Read ( unsigned long Add )
{
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */

	EEPROM_ByteWrite( 0xa0 );
	EEPROM_ByteWrite( (unsigned char)(Add >> 8) );
	EEPROM_ByteWrite( (unsigned char) Add );

	NOP(); 
	NOP(); 

	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 

	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */

	EEPROM_ByteWrite( 0xa1 );
	Add = EEPROM_ByteRead();

	/* nak */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	SCL0;
	NOP(); 
	NOP(); 

	/* stop */
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

	return (Add);
}


void EEPROM_PageWrite ( unsigned long Add, unsigned char *WData, unsigned char No )
{
	unsigned char i;
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */
	EEPROM_ByteWrite( 0xa0 );
	EEPROM_ByteWrite( (unsigned char)(Add >> 8) );
	EEPROM_ByteWrite( (unsigned char) Add );

	for ( i = 0; i < No; i++ )
	{
		EEPROM_ByteWrite( WData[i] );
	}

	/* stop */
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
}


void EEPROM_PageRead ( unsigned long Add, unsigned char *RData, unsigned char NoC )
{
	unsigned i;

	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;

	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */

	EEPROM_ByteWrite( 0xa0 );
	EEPROM_ByteWrite( (unsigned char)(Add >> 8) );
	EEPROM_ByteWrite( (unsigned char) Add );

	NOP(); 
	NOP(); 

	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */

	EEPROM_ByteWrite( 0xa1 );

	for ( i = 0; i < NoC; i++ )
	{
		RData[i] = EEPROM_ByteRead();

		if ( (i+1) == NoC )
		{
			/* nak */
			GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		}
		else
		{
			/* ack */
			GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
		}
		NOP(); 
		SCL1;
		NOP(); 
		NOP(); 
		SCL0;
		NOP(); 
	}

	/* stop */
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
}

unsigned char EEPROM_WritingCheck ( void )
{
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	/* start */
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	/* start end */

return ( CheckEepromByteWrite() );
}


void FM3164_Watchdog_Init(unsigned char watchdog)
{
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	// start
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	// start end

	EEPROM_ByteWrite( 0xD0 );
	EEPROM_ByteWrite( 0x0A );
	EEPROM_ByteWrite( watchdog );

	// stop
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
}

void FM3164_Restart(void)
{

    GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	// start
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	// start end 
	EEPROM_ByteWrite( 0xD0 );
	EEPROM_ByteWrite( 0x09 );
	EEPROM_ByteWrite( 0x0A );
	
	// stop
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

}

void WRITE_FM31xx_RTC_Companion(unsigned char address, unsigned char data)
{
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	// start
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	// start end

	EEPROM_ByteWrite( 0xD0 );
	EEPROM_ByteWrite( address );
	EEPROM_ByteWrite( data );
	
	// stop
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

}

unsigned char READ_FM31xx_RTC_Companion(unsigned char Add)
{
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SDAOUT;
	// start
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	SCL1;
	NOP(); 
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	// start end

	EEPROM_ByteWrite( 0xD0 );
	EEPROM_ByteWrite( (unsigned char) Add );

	NOP(); 
	NOP(); 

	//start
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 

	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL0;
	//start end

	EEPROM_ByteWrite( 0xD1 );
	Add = EEPROM_ByteRead();

	// nak
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	SCL0;
	NOP(); 
	NOP(); 

	// stop
	GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);
	NOP(); 
	SCL1;
	NOP(); 
	GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA);

	return (Add);
}

// ++, 160511 bwk
#if 0
void WRITE_RTC_Year(unsigned char data)
{
    unsigned char temp;
    
    if (data > 99)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_YEAR, temp);
}

unsigned char READ_RTC_Year(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_YEAR);
    
    temp = 0;
    temp += ((data >> 4) & 0x0f) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC_Month(unsigned char data)
{
    unsigned char temp;
    
    if (data > 12)
        return;
    
    if (data < 1)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_MONTH, temp);
}

unsigned char READ_RTC_Month(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_MONTH);
    
    temp = 0;
    temp += ((data >> 4) & 0x01) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC_Date(unsigned char data)
{
    unsigned char temp;
    
    if (data > 31)
        return;
    
    if (data < 1)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_DATE, temp);
}

unsigned char READ_RTC_Date(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_DATE);
    
    temp = 0;
    temp += ((data >> 4) & 0x03) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC_Day(unsigned char data)
{
    unsigned char temp;
    
    if (data > 7)
        return;
    
    if (data < 1)
        return;
    
    temp = data;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_DAY, temp);
}

unsigned char READ_RTC_Day(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_DAY);
    
    temp = data & 0x07;
    
    return temp;
}

void WRITE_RTC_Hour(unsigned char data)
{
    unsigned char temp;
    
    if (data > 23)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_HOUR, temp);
}

unsigned char READ_RTC_Hour(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_HOUR);
    
    temp = 0;
    temp += ((data >> 4) & 0x03) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC_Minute(unsigned char data)
{
    unsigned char temp;
    
    if (data > 59)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_MINUTE, temp);
}

unsigned char READ_RTC_Minute(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_MINUTE);
    
    temp = 0;
    temp += ((data >> 4) & 0x07) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC_Second(unsigned char data)
{
    unsigned char temp;
    
    if (data > 59)
        return;
    
    temp = 0;
    temp += (data / 10) << 4;
    temp += data % 10;
    
    WRITE_FM31xx_RTC_Companion(ADDR_RTC_SECOND, temp);
}

unsigned char READ_RTC_Second(void)
{
    unsigned char data;
    unsigned char temp;
    
    data = READ_FM31xx_RTC_Companion(ADDR_RTC_SECOND);
    
    temp = 0;
    temp += ((data >> 4) & 0x07) * 10;
    temp += data & 0x0f;
    
    return temp;
}

void WRITE_RTC(WL9FM_DATA_RTC RTC_Data)
{    
    WRITE_FM31xx_RTC_Companion(0x00, 0x02);
    
    WRITE_RTC_Year(RTC_Data.Year);
    WRITE_RTC_Month(RTC_Data.Month);
    WRITE_RTC_Date(RTC_Data.Date);
    WRITE_RTC_Day(RTC_Data.Day);
    WRITE_RTC_Hour(RTC_Data.Hour);
    WRITE_RTC_Minute(RTC_Data.Minute);
    WRITE_RTC_Second(RTC_Data.Second);
    
    WRITE_FM31xx_RTC_Companion(0x00, 0x00);
    
    WRITE_FM31xx_RTC_Companion(0x01, 0x00);
}

void READ_RTC(WL9FM_DATA_RTC *RTC_Data)
{    
    WRITE_FM31xx_RTC_Companion(0x00, 0x01);
    
    RTC_Data->Year 	 = READ_RTC_Year();
    RTC_Data->Month  = READ_RTC_Month();
    RTC_Data->Date 	 = READ_RTC_Date();
    RTC_Data->Day 	 = READ_RTC_Day();
    RTC_Data->Hour   = READ_RTC_Hour();
    RTC_Data->Minute = READ_RTC_Minute();
    RTC_Data->Second = READ_RTC_Second();
    
    WRITE_FM31xx_RTC_Companion(0x00, 0x00);
}
#endif
// --, 160511 bwk

void InitEEPROM(void)
{
	uint8_t i;

	for(i = 0; i < 100; i++) EEPROM_Write(i, 0);	
}

void ReadAllData(WL9FM_DATA_EEPROM *ReadData)
{
	uint8_t  i;
	uint8_t  *buf;
	uint16_t size;

	size = sizeof(WL9FM_DATA_EEPROM); 

	buf = (uint8_t *)ReadData;

	for(i = 0; i < size; i++)
	{
		*buf = EEPROM_Read(i);
		buf++;
	}
}

void SaveAllData(WL9FM_DATA_EEPROM SaveData)
{
	uint8_t  i;
	uint8_t  *buf;
	uint16_t size;

	size = sizeof(WL9FM_DATA_EEPROM); 

	buf = (uint8_t *)&SaveData;
	
	for(i = 0; i < size; i++)
	{
		EEPROM_Write(i, *buf++);
		TimeDelay_msec(10);
	}
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/

