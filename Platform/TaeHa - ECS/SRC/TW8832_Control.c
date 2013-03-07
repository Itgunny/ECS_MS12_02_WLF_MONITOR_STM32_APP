/**
  ******************************************************************************
  * @file    TW8832_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TW8832_Control.c module
  *
  * Project Name       : WL9F Display APP
  * Project Enviroment : IAREmbedded Workbench for ARM 6.5x 
  *                      STM32F407ZGT6 Firmware Library
  * Project Workspace  : WL9F_Display_APP
  * MCU Type           : STM32F407ZGT6
  *
  * TAEHA MECHATRONICS Co., Ltd (http://www.taeha.co.kr)				
  * ECS Division R&D Center. / Author by Young-Min Han (kutelf@taeha.co.kr)
  * 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void NOP_TW8832(void)
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

	for(tmp_index = 0; tmp_index < 15000; tmp_index++);
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

	for(tmp_index = 0; tmp_index < 15000; tmp_index++);
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
	if ( InputMain == INPUT_CVBS ) return(0);
	InputMain = INPUT_CVBS;
	SaveInputEE( InputMain );

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
u8 xx;
u8 yy = 6;
void I2C2DeviceInitialize(u8 *RegSet)
{
	//u8	cnt=0;
	u8 addr, index, val;
       
    xx = 0;
	addr = *RegSet;
	
	RegSet+=2;
	
	// 0xff, 0xff is end of data
	while (( RegSet[0] != 0xFF ) || ( RegSet[1]!= 0xFF )) 
	{			
		index = *RegSet;
		val = *(RegSet+1);
		I2C2_ByteWrite(addr, index, val);
		RegSet+=2;
		xx += 1;
		if(xx == yy)
		{
			xx = yy;
		}
	}

	WriteTW8832(0xff, 0x00);	// set page 0
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
