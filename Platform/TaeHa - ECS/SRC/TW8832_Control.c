/**
  ******************************************************************************
  * @file    TW8832_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TW8832_Control.c module
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
u8 InitCVBSAll[] = 
{
	0x8a,0x00,	//	TW88I2CAddress,0,	
	0xFF,0x00,	//	Page 00
	0x02,0x20,
	0x03,0xFF,
	0x06,0x26,
	0x07,0x02,
	0x08,0x86,	// 	CVBS INPUT
	0x09,0x00,
	0x40,0x32,	//	BT.656 INPUT
	0x41,0x00,
	0x42,0x02,
	0x43,0x10,
	0x44,0xF0,
	0x45,0x82,
	0x46,0xD0,
	0x47,0x00,	//	BT.656 INPUT
	0x48,0x00,
	0x49,0x41,
	0x4A,0x04,
	0xDB,0x05,
	0xDC,0x00,
	0xDD,0x80,
	0xDE,0x00,
	0xDF,0x80,
	0xE0,0xF2,
	0xE1,0x77,
	0xE2,0x04,
	0xE3,0x40,
	0xE4,0x84,
	0xE5,0x00,
	0xE6,0x20,
	0xE7,0x00,
	0xE8,0xF2,
	0xE9,0x06,
	0xEA,0x04,
	0xEB,0x5F,
	0xEC,0x20,
	0xED,0x40,
	0xEE,0x20,
	0xF6,0x81,
	0xF7,0x16,
	0xF8,0x01,
	0xF9,0x2C,
	0xFA,0x00,
	0xFB,0x40,
	0xFC,0x30,
	0xFD,0x21,
	
	0xFF,0x01,	//	Page01
	0x02,0x40,
	0x04,0x00,
	0x05,0x01,
	0x06,0x00,
	0x07,0x02,
	0x08,0x15,
	0x09,0xF0,
	0x0A,0x0F,
	0x0B,0xD0,
	0x0C,0xCC,
	0x10,0x00,
	0x11,0x5C,
	0x12,0x11,
	0x13,0x80,
	0x14,0x80,
	0x15,0x00,
	0x17,0x80,
	0x18,0x44,
	0x1C,0x0F,
	0x1D,0x7F,
	0x1E,0x00,
	0x20,0x50,
	0x21,0x22,
	0x22,0xF0,
	0x23,0xD8,
	0x24,0xBC,
	0x25,0xB8,
	0x26,0x44,
	0x27,0x38,
	0x28,0x00,
	0x29,0x00,
	0x2A,0x78,
	0x2B,0x44,
	0x2C,0x30,
	0x2D,0x14,
	0x2E,0xA5,
	0x2F,0xE0,
	0x30,0x00,
	0x33,0x05,
	0x35,0x00,
	0xC0,0x01,
	0xC1,0xC7,
	0xC2,0x01,
	0xC3,0x03,
	0xC4,0x5A,
	0xC5,0x00,
	0xC6,0x20,
	0xC7,0x04,
	0xC8,0x00,
	0xC9,0x06,
	0xCA,0x06,
	0xCB,0x10,
	0xCC,0x00,
	0xCD,0x54,
	0xD0,0x00,
	0xD1,0xF0,
	0xD2,0xF0,
	0xD3,0xF0,
	0xD4,0x00,
	0xD5,0x00,
	0xD6,0x10,
	0xD7,0x70,
	0xD8,0x00,
	0xD9,0x04,
	0xDA,0x80,
	0xDB,0x80,
	0xDC,0x20,
	
	0xFF,0x02,	//	Page02
	0x01,0x00,
	0x02,0x20,
	0x03,0x00,
	0x04,0x1C,
	0x05,0x00,
	0x06,0x0F,
	0x07,0xBF,
	0x08,0x8F,
	0x09,0x00,
	0x0A,0x01,
	0x0B,0x63,
	0x0C,0xD0,
	0x0D,0x80,
	0x0E,0x00,
	0x0F,0x02,
	0x10,0x84,
	0x11,0x20,
	0x12,0x03,
	0x13,0x00,
	0x14,0x04,
	0x15,0x2C,
	0x16,0xE0,
	0x17,0x01,
	0x18,0x62,
	0x19,0x00,
	0x1A,0x00,
	0x1B,0x00,
	0x40,0x11,
	0x41,0x0A,
	0x42,0x05,
	0x43,0x01,
	0x44,0x64,
	0x45,0xF4,
	0x46,0x00,
	0x47,0x0A,
	0x48,0x36,
	0x49,0x10,
	0x4A,0x00,
	0x4B,0x00,
	0x4C,0x00,
	0x4D,0x84,
	0x4E,0x24,
	0x80,0x20,	//	0x00,	HUE
	0x81,0x80,
	0x82,0x80,
	0x83,0x80,
	0x84,0x80,
	0x85,0x80,
	0x86,0x80,
	0x87,0x80,
	0x88,0x80,
	0x89,0x80,
	0x8A,0x80,
	0x8B,0xDF,
	0x8C,0x00,
	0xB0,0x10,
	0xB1,0x40,
	0xB2,0x40,
	0xB6,0x67,
	0xB7,0x94,
	0xBF,0x0E,	//	Souce Output
	0xE0,0x00,
	0xE4,0x21,
	0xF8,0x00,
	0xF9,0x80,
	
	0xff, 0x04, //	Page 04
	0x80, 0x15,
	0xff, 0xff
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void NOP_TW8832(void)
{
	TimeDelay_usec(1);	
}

void TW8832_PortChange(unsigned char dir)
{
	unsigned short temp;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if (dir)// Output
	{
		temp = TW8832_I2C2_PORT->IDR;			//	GPIO_ReadInputData
		temp = ((~(TW8832_I2C2_SDA)) & temp);
		TW8832_I2C2_PORT->ODR = (temp);			//	GPIO_Write
		
		GPIO_InitStructure.GPIO_Pin   = TW8832_I2C2_SDA;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
		GPIO_Init(TW8832_I2C2_PORT, &GPIO_InitStructure);	
	}
	else	// Input
	{	
		temp = TW8832_I2C2_PORT->IDR;			//	GPIO_ReadInputData
		temp = ((~(TW8832_I2C2_SDA)) & temp);
		TW8832_I2C2_PORT->ODR = (temp);			//	GPIO_Write
		
		GPIO_InitStructure.GPIO_Pin  = TW8832_I2C2_SDA;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_Init(TW8832_I2C2_PORT, &GPIO_InitStructure);	
	}
}

void I2C2_Write(u8 WData)
{
	u8 i, j;

	NOP_TW8832();

	for (i = 0; i < 8; i++)
	{
		j = ( WData & 0x80 ) ? 1 : 0;
		(j) ? GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA) : GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
		NOP_TW8832();
		TW8832_SCL1;
		NOP_TW8832();		
		WData <<= 1;
		TW8832_SCL0;
		NOP_TW8832();
	}

	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL1;
	NOP_TW8832();
	TW8832_SCL0;
}

void I2C2_ByteWrite(u16 in_AddrVal, u8 in_DataVal)
{
	u16 tmp_index;

	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	TW8832_SDAOUT;
	// START
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	TW8832_SCL1;
	NOP_TW8832();
	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL0;
	// END

	I2C2_Write(TW8832_I2C_Addr);
	I2C2_Write((u8)in_AddrVal);
	I2C2_Write(in_DataVal);

	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL1;
	NOP_TW8832();
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);

	for (tmp_index = 0; tmp_index < 15000; tmp_index++);
}
u8 I2C2_Read(void)
{
	u8 i;
	u8 RData;

	NOP_TW8832();
	TW8832_SCL0;
	NOP_TW8832();
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	TW8832_SDAIN;

	for ( i = 0; i < 8; i++ )
	{
		TW8832_SCL1;
		NOP_TW8832();
		NOP_TW8832();
		RData = (RData << 1) | TW8832_SDA_READ;
		TW8832_SCL0;
		NOP_TW8832();
		NOP_TW8832();
	}
	GPIO_ResetBits(TW8832_I2C2_PORT, GPIO_Pin_7);
	TW8832_SDAOUT;
	return (RData );
}

u8 I2C2_ByteRead(u16 in_AddrVal)
{
	u8 RData = 0;
	u16 tmp_index;

	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	TW8832_SDAOUT;
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	TW8832_SCL1;
	NOP_TW8832();
	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL0;

	I2C2_Write(TW8832_I2C_Addr);
	I2C2_Write((u8)in_AddrVal);

	NOP_TW8832();
	NOP_TW8832();

	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL1;
	NOP_TW8832();

	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL0;

	I2C2_Write(0x8b);

	RData = I2C2_Read();

	// NAK
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL1;
	NOP_TW8832();
	TW8832_SCL0;
	NOP_TW8832();

	// STOP
	GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);
	NOP_TW8832();
	TW8832_SCL1;
	NOP_TW8832();
	GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SDA);

	for (tmp_index = 0; tmp_index < 15000; tmp_index++);
	return (RData);
}

void WriteTW8832(u8 in_AddrVal, u8 in_DataVal)
{
	I2C2_ByteWrite(in_AddrVal, in_DataVal);
	TimeDelay_usec(500);
}

u8 ReadTW8832(u8 in_AddrVal)
{
	u8 val;

	val = I2C2_ByteRead(in_AddrVal);

	return(val);
}

//=============================================================================
//		WORD SetYCbCrContrast(WORD val)
//=============================================================================
u16 SetYCbCrContrast(u16 val)
{
	WriteTW8832( 0xff, SCALER_PAGE );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW8832( ContrastY, val );
	val = ReadTW8832( ContrastY );
	val *= 100;
	val += 128;
	val /= 255;

	return (val);
}

//=============================================================================
//		WORD SetYCbCrBright(WORD val)
//=============================================================================
u16 SetYCbCrBright(u16 val)
{
	WriteTW8832( 0xff, SCALER_PAGE );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW8832( BrightnessY, val );
	val = ReadTW8832( BrightnessY );
	val *= 100;
	val += 128;
	val /= 255;

	return (val);
}

//=============================================================================
//		WORD SetYCbCrSaturation(WORD val)
//=============================================================================
u16 SetYCbCrSaturation(u16 val)
{
	WriteTW8832( 0xff, SCALER_PAGE );
	val *= 255;
	val += 50;
	val /= 100;
	WriteTW8832( SaturationY, val );
	WriteTW8832( SaturationY+1, val );
	val = ReadTW8832( SaturationY );
	val *= 100;
	val += 128;
	val /= 255;

	return (val);
}

//=============================================================================
//		BYTE	ChangeCVBS( void )
//=============================================================================
u8	ChangeCVBS( void )
{
#if 0
	if ( InputMain == INPUT_CVBS ) return(0);
	InputMain = INPUT_CVBS;

	//SaveInputEE( InputMain );
	//Freerun( 0 );

	InitCVBSRegister( );

	WriteTW8832( 0xff, DECODER_PAGE );
	WriteTW8832( 0x02, 0x40 );

	// Get Image control register value
	SetYCbCrContrast( GetVideoDatafromEE( 0 ) );
	SetYCbCrBright( GetVideoDatafromEE( 1 ) );
	SetYCbCrSaturation( GetVideoDatafromEE( 2 ) );
	//SetDecoderContrast( GetVideoDatafromEE( 3 ) );
	SetYCbCrHUE( GetVideoDatafromEE( 4 ) );
	SetYCbCrSharp( GetVideoDatafromEE( 5 ) );

	TimeDelay_msec(10);

	return( CheckAndSetDecoderScaler() );
#endif

	return 0;
}

//=============================================================================
//		BYTE	CheckDecoderVDLOSS( BYTE n )
//=============================================================================
u8	CheckDecoderVDLOSS( u8 n )
{
    u8	mode;

	WriteTW8832( 0xff, DECODER_PAGE );		// set Decoder page
	while (n--) 
	{
		mode = ReadTW8832( 0x01 );
		if (( mode & 0x80 ) == 0 ) return ( 0 );
		TimeDelay_msec(1);
	}

	return ( 1 );
}

//=============================================================================
//		BYTE	CheckDecoderSTD( BYTE n )
//=============================================================================
u8	CheckDecoderSTD( u8 n )
{
    u8	mode;

	WriteTW8832( 0xff, DECODER_PAGE );		// set Decoder page
	while (n--) 
	{
		mode = ReadTW8832( 0x1C );
		if (( mode & 0x80 ) == 0 ) return ( mode );
		TimeDelay_msec(1);
	}

	return ( 0x80 );
}

//=============================================================================
//		BYTE	CheckAndSetDecoderScaler( void )
//=============================================================================
u8	CheckAndSetDecoderScaler( void )
{
    u8	mode;
    //u32	vPeriod=0; 
    u32 vDelay=0;

	if ( CheckDecoderVDLOSS(100) ) 
	{
		//Puts("\nCVBS VDLOSS");
		//Freerun( 1 );
		return( 1 );
	}

	if ( CheckDecoderSTD(100) == 0x80 ) return( 2 );

	TimeDelay_msec(10);

	WriteTW8832( 0xff, DECODER_PAGE );	// Set Decoder page
	mode = ReadTW8832( 0x1c );
	
	//DebugMsg_printf( "\nInput mode %02bx", mode );

	mode >>= 4;
	if ( mode == 0 )		 //	NTSC
	{				
		//DebugMsg_printf( "\nInput Mode(NTSC) vScale:%02bx, vBack:%bd", ReadTW8832( 0x06 ), ReadTW8832( 0x15 ) );
	}
	else if ( mode == 1 )	//	PAL
	{			 
		WriteTW8832( 0x07, ( ReadTW8832( 0x07 ) | 0x10 ) );
		WriteTW8832( 0x09, 32 );
		WriteTW8832( 0x0a, 0x18 );					// change H-delay
		//vPeriod = 275;							// NTSC line number
		vDelay += 7; 		// 6 = ( 288-275 ) / 2
		WriteTW8832( 0xff, SCALER_PAGE );
		WriteTW8832( 0x06, 0x12 );					// set V scale
		WriteTW8832( 0x05, 0xA2 );					// set V scale
		WriteTW8832( 0x15, 0x30);					// set output V delay
		//DebugMsg_printf( "\nInput Mode(PAL) vScale:%02bx, vBack:%bd", ReadTW8832( 0x06 ), ReadTW8832( 0x15 ) );
	}
	else {
		//DebugMsg_printf( "\nInput Mode %bd does not support now", mode );
		return(1);
	}
	
	return(0);
}

//=============================================================================
//		WORD SetYCbCrSharp(WORD val)
//=============================================================================
u16 SetYCbCrSharp(u16 val)
{
    u8	i;

	WriteTW8832( 0xff, SCALER_PAGE );

	for (i=0; i<16; i++) 
	{
		if ( val == (Sharpness[i]+1) )
		{
			val = i+1;
			break;
		}
		if ( Sharpness[i] == (val+1) )
		{
			val = i-1;
			break;
		}
	}
	WriteTW8832( SharpnessY, ((ReadTW8832( SharpnessY ) & 0xf0) + val) );
	val = Sharpness[i];

	return (val);
}

//=============================================================================
//		WORD SetYCbCrHUE(WORD val)
//=============================================================================
u16 SetYCbCrHUE(u16 val)
{
	WriteTW8832( 0xff, SCALER_PAGE );
	val *= 63;
	val += 50;
	val /= 100;
	val += 0x20;
	val &= 0x3F;
	WriteTW8832( HueY, val );
	val = ReadTW8832( HueY );
	val += 0x20;
	val &= 0x3F;
	val *= 100;
	val += 32;
	val /= 63;

	return (val);
}

//=============================================================================
//				                                               
//=============================================================================
void I2C2DeviceInitialize(u8 *RegSet)
{
	u8 Addr, val;
       
	RegSet += 2;
	
	// 0xff, 0xff is end of data
	while (( RegSet[0] != 0xFF ) || ( RegSet[1]!= 0xFF )) 
	{			
		Addr = *RegSet;
		val = *(RegSet+1);
		I2C2_ByteWrite(Addr, val);
		RegSet+=2;
	}

	WriteTW8832(0xff, 0x00);	// Set page 0
}


void InitCVBSRegister( void )
{
	I2C2DeviceInitialize( InitCVBSAll );
}


/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void TW8832_Control_Init(void)
{
    DebugMsg_printf("++ TW8832_Control_Init (I2C2 & SPI2), ADC Initialize START\r\n");

	InitCVBSRegister();
	
    DebugMsg_printf("-- TW8832_Control_Init (I2C2 & SPI2), ADC Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
