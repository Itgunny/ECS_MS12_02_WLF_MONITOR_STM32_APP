/**
  ******************************************************************************
  * @file    TW8832_OSD.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TW8832_OSD.c module
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

uc8		FontOsdWinBase[]  = { FONTWIN1_ST, FONTWIN2_ST, FONTWIN3_ST, FONTWIN4_ST };
vuc8 	SpiOsdWinBase[2]  = { SPI_WIN0_ST, SPI_WIN1_ST };
vuc8 	SPI_MODE_OFFSET[] = {30,21,26,38,22,28,37};

#if 0
uc8 decimal_font[10][4] =
{
	{ 0,  1,  2,  3},
	{ 4,  5,  6,  7},
	{ 8,  9, 10, 11},
	{12, 13, 14, 15},
	{16, 17, 18, 19},
	{20, 21, 22, 23},
	{24, 25, 26, 27},
	{28, 29, 30, 31},
	{32, 33, 34, 35},
	{36, 37, 38, 39}
};
u8 RPM_dec0=0, RPM_dec1=0, RPM_dec2=0, RPM_dec3=0;
u8 temp_RPM_dec0=99, temp_RPM_dec1=99, temp_RPM_dec2=99, temp_RPM_dec3=99;

u8 C_dec0=0, C_dec1=0, C_dec2=0, C_dec3=0;
u8 temp_C_dec0=99, temp_C_dec1=99, temp_C_dec2=99, temp_C_dec3=99;

u8 H_dec0=0, H_dec1=0, H_dec2=0, H_dec3=0;
u8 temp_H_dec0=99, temp_H_dec1=99, temp_H_dec2=99, temp_H_dec3=99;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//=============================================================================
//		OSD Window Setup
//=============================================================================
/*	
	SPI OSD DE delay calculation 
	HDE       = REG(0x210[7:0])
	Mixing    = REG(0x400[1:1]){0,3}
	PCLKO     = REG(0x20d[1:0])
	SPI_MODE  = REG(0x480[2:0]){30,21,26,38,22,28,37}
	CLK_DELAY = REG(0x481[4:4])

	result = HDE + Mixing + PCLKO - (SPI_MODE + CLK_DELAY)
*/ 
void SpiOsdWinEnable(u8 winno, u8 en)
{
	u8  index;
	u8  dat;
	u16 temp;

	//
	WriteTW8832( 0xff, 2 );
	temp = ReadTW8832( 0x10 );			//	HDE
	temp  += (ReadTW8832( 0x0d ) & 3);	// 	PCLKO
	WriteTW8832( 0xff, 4 );

	if ( ReadTW8832( 0x00 ) & 2 ) 		// 	Check Mixing		
	{			
		temp += 3;
	}
	temp -= SPI_MODE_OFFSET[ ReadTW8832( 0x80 ) & 7 ];

	if ( ReadTW8832( 0x81 ) & 0x10 ) 
	{
		temp--;
	}
	WriteTW8832( 0x0F, temp );   		// Write SPI OSD DE value
		
	index = SpiOsdWinBase[winno] + SPI_OSDWIN_ENABLE;
	WriteTW8832( 0xff, SPI_OSD_PAGE );
	dat = ReadTW8832(index);

	if( en ) WriteTW8832(index, dat | 0x01);
	else     WriteTW8832(index, dat & 0xfe);
}
	 
void SpiOsdWinBufferMem(u8 winno, u32 start)
{
	u8 index;
	
	index = SpiOsdWinBase[winno] + SPI_OSDWIN_BUFFERSTART;
	//Printf("\nWinno: %bd, SpiOsdWinBase: %bd", winno, SpiOsdWinBase[winno] );
	//Printf("\nOSD buffer set to reg: %02bx, address:%02bx %02bx %02bx", index, (u8)(start>>16), (u8)(start>>8), (u8)(start) );

	WriteTW8832( 0xff, SPI_OSD_PAGE );
	WriteTW8832(index++, (u8)(start>>16));
	WriteTW8832(index++, (u8)(start>>8));
	WriteTW8832(index++, (u8)start);

}

void SpiOsdWinBufferSizeXY (u8 winno, u16 x, u16 y)
{
	u8 index;

	index = SpiOsdWinBase[winno] + SPI_OSDWIN_DISPSIZE;
	//Printf("\nSpiOsdWinBufferSizeXY to reg: %02bx, x:%d y:%d", index, x, y );
	WriteTW8832( 0xff, SPI_OSD_PAGE );
	WriteTW8832(index++, x>>8);
	WriteTW8832(index++, x);
	WriteTW8832(index++, y>>8);
	WriteTW8832(index,   y);
}
		
void SpiOsdWinBufferOffsetXY (u8 winno, u16 x, u16 y)
{
	u8 index;

	index = SpiOsdWinBase[winno] + SPI_OSDWIN_DISPOFFSET;
	//Printf("\nSpiOsdWinBufferOffsetXY to reg: %02bx, x:%d y:%d", index, x, y );
	WriteTW8832( 0xff, SPI_OSD_PAGE );
	WriteTW8832(index++, (u8)(x>>8));
	WriteTW8832(index++, (u8)x);
	WriteTW8832(index++, (u8)(y>>8));
	WriteTW8832(index,   (u8)y);
}
		
void SpiOsdWinScreen(u8 winno, u16 x, u16 y, u16 w, u16 h)
{
	u8 index;

	index = SpiOsdWinBase[winno] + SPI_OSDWIN_SCREEN;
	//Printf("\nSpiOsdWinScreen to reg: %02bx, x:%d y:%d, w:%d h:%d", index, x, y, w, h );
	WriteTW8832( 0xff, SPI_OSD_PAGE );
	WriteTW8832(index++, (u8)(x>>8));
	WriteTW8832(index++, (u8)x);
	WriteTW8832(index++, (u8)(y>>8));
	WriteTW8832(index++, (u8)y);
	WriteTW8832(index++, (u8)(w>>8));
	WriteTW8832(index++, (u8)w);
	WriteTW8832(index++, (u8)(h>>8));
	WriteTW8832(index,   (u8)h);
}

//=============================================================================
//		OSD Window Functions
//=============================================================================

void SpiOsdWaitVBlank(u8 cnt)
{
	u8 i;

 	WriteTW8832( 0xff, SPI_OSD_PAGE );
	for(i=0; i<cnt; i++) {
		WriteTW8832( 0x08, 0x20 );
		while( (ReadTW8832(0x08) & 0x20)==0 );	
	}
}

//=============================================================================
//		Load LUT
//=============================================================================
void SpiOsdLoadLUT( u32	address, u32 DMA_size )
{
	WriteTW8832( 0xff, SPI_OSD_PAGE );

	//--- SPI-OSD config
	WriteTW8832( 0x10, 0xc0 );    			// 	LUT Write Mode, En
	WriteTW8832( 0x11, 0x00 );    			//	LUT addr
	
	//--- SPI-DMA mode
	
	WriteTW8832( 0x83, 0x85 );
	WriteTW8832( 0x84, 0x00 );
	           
	WriteTW8832( 0x8a, 0x0b ); 				// 	SPI Command=R
	WriteTW8832( 0x8b, (u8)(address>>16) ); // 	SPI Addr
	WriteTW8832( 0x8c, (u8)(address>>8) );
	WriteTW8832( 0x8d, (u8)(address) ); 	//	00
	          
	WriteTW8832( 0x86, 0x00 ); 				// 	04 // DMA dest.
	WriteTW8832( 0x87, 0x00 ); 				// 	12

    WriteTW8832( 0x9a, (u8)(DMA_size>>16) );//	DMA size
	WriteTW8832( 0x88, (u8)(DMA_size>>8) );
	WriteTW8832( 0x89, (u8)(DMA_size) );
    
	//WriteTW8832( 0x9a, 0x00 );//	DMA size
	//WriteTW8832( 0x88, 0x04 );
	//WriteTW8832( 0x89, 0x00 );
	
	WriteTW8832( 0x84, 0x01 ); 	//	DMA Start

	//Printf("\r---> LUT Write ");
}

//=============================================================================
//		SpiOsdWinAlpha( u8 winno, u8 alpha )
//=============================================================================
void SpiOsdWinAlpha( u8 winno, u8 alpha )
{
	u8	index;

	index = SpiOsdWinBase[winno];
	WriteTW8832( 0xff, SPI_OSD_PAGE );

	if ( alpha ) {
		WriteTW8832( index, ( ReadTW8832( 0x20 ) & 0xDF ) | 0x10 );	// en Alpha & Global
	}
	else {
		WriteTW8832( index, ( ReadTW8832( 0x20 ) & 0xCF ) );			// dis Alpha & Global
	}
	index = SpiOsdWinBase[winno] + 0x14;
	WriteTW8832( index, alpha );
}

//=============================================================================
//		SpiOsdWinAlpha( u8 winno, u8 alpha )
//=============================================================================
void	SpiOsdPixelAlpha( u8 winno, u8 alpha )
{
	u8	index;

	index = SpiOsdWinBase[winno];
	WriteTW8832( 0xff, SPI_OSD_PAGE );

	if ( alpha ) {
		WriteTW8832( index, ReadTW8832( 0x20 ) | 0x30 );				// en Alpha & Global
	}
	else {
		WriteTW8832( index, ( ReadTW8832( 0x20 ) & 0xCF ) );			// dis Alpha & Global
	}
	index = SpiOsdWinBase[winno] + 0x14;
	WriteTW8832( index, alpha );
}

//=============================================================================
//		Animation
//=============================================================================
void SpiOsdAnimation(u8 winno, u8 mode, u8 FrameH, u8 FrameV, u8 Duration)
{
	u8 index;
	u8 temp;
	
	temp = SpiOsdWinBase[winno];
	index = SpiOsdWinBase[winno] + SPI_OSDWIN_ANIMATION;
	WriteTW8832( 0xff, SPI_OSD_PAGE );
	WriteTW8832(index++, FrameH);
	WriteTW8832(index++, FrameV);
	WriteTW8832(index, Duration);

	//WriteTW8832( SpiOsdWinBase[winno], ( ReadTW8832( SpiOsdWinBase[winno]) & 0x3f ) | (mode <<6) );
	WriteTW8832( temp, ( ReadTW8832( SpiOsdWinBase[winno]) & 0x3f ) | (mode <<6) );

}


//=============================================================================
//		void FontOsdWinEnable(u8 winno, u8 en)
//=============================================================================
/*	
	SPI OSD DE delay calculation 
	HDE    = REG(0x210[7:0])
	Mixing = REG(0x400[1:1])

	result = HDE - ( Mixing +41 )
*/ 
void FontOsdWinEnable(u8 winno, u8 en)
{
	u8 index;
	u8 dat;
	u16 temp;

	index = FontOsdWinBase[winno] + FONTWIN_ENABLE;

	WriteTW8832( 0xff, 2 );
	temp = ReadTW8832( 0x10 );				// HDE
	WriteTW8832( 0xff, 4 );
	if ( ReadTW8832( 0x00 ) & 2 ) 			// Check Mixing
	{			
		temp--;
	}
	temp -= 41;
	
	WriteTW8832( 0xff, FONT_OSD_PAGE );

	WriteTW8832( 0x03, temp );   			// Write FONT OSD DE value

	dat = ReadTW8832(index);
	if( en ) WriteTW8832(index, dat | 0x80);
	else     WriteTW8832(index, dat & 0x7F);
}
	 
//=============================================================================
//		void FontOsdWinAlpha(u8 winno, u8 color, u8 alpha)
//=============================================================================
void FontOsdWinAlpha(u8 winno, u8 color, u8 alpha)
{
	u8	index = FontOsdWinBase[winno] + FONT_ALPHA;

	WriteTW8832( 0xff, FONT_OSD_PAGE );

	WriteTW8832( index, ( color <<4 ) + alpha );	 		// first select color
	WriteTW8832( index, ( color <<4 ) + alpha );			// second write alpha value
}

//=============================================================================
//		void FontOsdWinScreen(u8 winno, u16 x, u16 y, u8 w, u8 h, u8 zoomH, u8 zoomV)
//=============================================================================
void FontOsdWinScreen(u8 winno, u16 x, u16 y, u8 w, u8 h, u8 zoomH, u8 zoomV)
{
	u8 index, temp;

	index = FontOsdWinBase[winno];
	
	WriteTW8832( 0xff, FONT_OSD_PAGE );
	temp = zoomH*4 + zoomV;
	temp += (ReadTW8832( index ) & 0xf0);
	WriteTW8832( index, temp );				// write Zoom value
	
	temp = x >> 8;
	temp <<= 4;
	temp += ( y >> 8 );
	WriteTW8832( index+2,  temp );			// upper bit for position x, y
	WriteTW8832( index+3, x );				// position x
	WriteTW8832( index+4, y );				// position y
	WriteTW8832( index+5, h );
	WriteTW8832( index+6, w );
}
//=============================================================================
//				   void FontDMA( void )
//=============================================================================
void FontDMA( void )
{

	WriteTW8832( 0xff, 0x03 );
	WriteTW8832( 0x00, 0x03 ); //bypass
	WriteTW8832( 0x04, 0x0d ); //Font RAM access
	WriteTW8832( 0x09, 0x00 ); //Font Addr
	
	WriteTW8832( 0xff, 0x04 );
	WriteTW8832( 0x83, 0x05 ); //e4
	
	WriteTW8832( 0x86, 0x00 ); // DMA Page Register
	WriteTW8832( 0x87, 0x00 ); // DMA Index Register
	
	WriteTW8832( 0x8a, 0x0b );
	WriteTW8832( 0x8b, 0x00 ); // Serial Flash Memory Address
	WriteTW8832( 0x8c, 0x00 ); // Serial Flash Memory Address
	WriteTW8832( 0x8d, 0x00 ); // Serial Flash Memory Address
	
	WriteTW8832( 0x9a, 0x00 );
	WriteTW8832( 0x88, 0x10 );
	WriteTW8832( 0x89, 0xe0 );
	
	WriteTW8832( 0x84, 0x01 ); //DMA Start
	TimeDelay_msec(10);
	
	//WriteTW8832( 0xff, 0x03 );
	//WriteTW8832( 0x04, 0x0c ); //Display RAM Access Mode
}
//=============================================================================

//	사용하지 않는 코드 삭제 
#if 0
//=============================================================================
//		void FontDemo( void )
//=============================================================================
void RPM_Display(u16 RPM_Value)
{
    RPM_dec0 = RPM_Value/1000;
    RPM_dec1 = (RPM_Value%1000)/100;
    RPM_dec2 = (RPM_Value%100)/10;
    RPM_dec3 = RPM_Value%10;
    
    if((temp_RPM_dec0 != RPM_dec0) & (RPM_Value > 999)){
    	temp_RPM_dec0 = RPM_dec0 = RPM_Value/1000;                
    	WriteTW8832( 0x06, 0x00 );                 // OSD Display Ram Addr
    	WriteTW8832( 0x07, decimal_font[RPM_dec0][0]); // FontRam Addr
    	WriteTW8832( 0x06, 0x01 );                            
    	WriteTW8832( 0x07, decimal_font[RPM_dec0][1] );
    	WriteTW8832( 0x06, 0x08 );                            
    	WriteTW8832( 0x07, decimal_font[RPM_dec0][2] );
    	WriteTW8832( 0x06, 0x09 );                           
    	WriteTW8832( 0x07, decimal_font[RPM_dec0][3] );
    }
    else if((temp_RPM_dec0 != RPM_dec0) & (RPM_dec0 == 0 ) & (RPM_Value < 999)){
    	temp_RPM_dec0 = RPM_dec0 = RPM_Value/1000;
		WriteTW8832( 0x06, 0x00 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x01 );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x08 );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x09 );                           
	    WriteTW8832( 0x07, 40 );
    }

    if((temp_RPM_dec1 != RPM_dec1) & (RPM_Value > 99)){
    	temp_RPM_dec1 = RPM_dec1 = (RPM_Value%1000)/100;                
	    WriteTW8832( 0x06, 0x02 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[RPM_dec1][0]); // FontRam Addr
	    WriteTW8832( 0x06, 0x03 );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec1][1]); 
	    WriteTW8832( 0x06, 0x0a );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec1][2]); 
	    WriteTW8832( 0x06, 0x0b );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec1][3]); 
    }
    else if((temp_RPM_dec1 != RPM_dec1) & (RPM_dec1 == 0 ) & (RPM_Value < 99)){
    	temp_RPM_dec1 = RPM_dec1 = (RPM_Value%1000)/100;                
		WriteTW8832( 0x06, 0x02 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x03 );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0a );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0b );                           
	    WriteTW8832( 0x07, 40 );
    }
    
    if((temp_RPM_dec2 != RPM_dec2) & (RPM_Value > 9)){
    	temp_RPM_dec2 = RPM_dec2 = (RPM_Value%100)/10;
	    WriteTW8832( 0x06, 0x04 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[RPM_dec2][0]); // FontRam Addr
	    WriteTW8832( 0x06, 0x05 );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec2][1]); 
	    WriteTW8832( 0x06, 0x0c );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec2][2]); 
	    WriteTW8832( 0x06, 0x0d );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec2][3]); 
    }
    else if((temp_RPM_dec2 != RPM_dec2) & (RPM_dec2 == 0 ) & (RPM_Value < 9)){
    	temp_RPM_dec2 = RPM_dec2 = (RPM_Value%100)/10;
		WriteTW8832( 0x06, 0x04 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x05 );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0c );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0d );                           
	    WriteTW8832( 0x07, 40 );
    }

    if(temp_RPM_dec3 != RPM_dec3){
    	temp_RPM_dec3 = RPM_dec3 = RPM_Value%10;
	    WriteTW8832( 0x06, 0x06 );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[RPM_dec3][0]); // FontRam Addr
	    WriteTW8832( 0x06, 0x07 );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec3][1]); 
	    WriteTW8832( 0x06, 0x0e );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec3][2]); 
	    WriteTW8832( 0x06, 0x0f );                            
	    WriteTW8832( 0x07, decimal_font[RPM_dec3][3]); 
    }
                
    //WriteTW8832( 0xff, 0x03 );
    //WriteTW8832( 0x04, 0x0C );// Display RAM Access Mode
    
}


//=============================================================================
//		void FontDemo( void )
//=============================================================================
void Hyd_TEMP_Display(u16 TEMP_Value)
{
    H_dec0 = TEMP_Value/1000;
    H_dec1 = (TEMP_Value%1000)/100;
    H_dec2 = (TEMP_Value%100)/10;
    H_dec3 = TEMP_Value%10;

    if((temp_H_dec0 != H_dec0) & (TEMP_Value > 999)){
    	temp_H_dec0 = H_dec0 = TEMP_Value/1000;  
	    WriteTW8832( 0x06, 0x00 + FONT_WIN1_OSDADDR_OFFSET );     // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[H_dec0][0]);                // FontRam Addr
	    WriteTW8832( 0x06, 0x01 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec0][1] );
	    WriteTW8832( 0x06, 0x09 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec0][2] );
	    WriteTW8832( 0x06, 0x0a + FONT_WIN1_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, decimal_font[H_dec0][3] );
	}
    else if((temp_H_dec0 != H_dec0) & (H_dec0 == 0 ) & (TEMP_Value < 999)){
    	temp_H_dec0 = H_dec0 = TEMP_Value/1000;  
		WriteTW8832( 0x06, 0x00 + FONT_WIN1_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x01 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x09 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0a + FONT_WIN1_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
    }
    
    if((temp_H_dec1 != H_dec1) & (TEMP_Value > 99)){
    	temp_H_dec1 = H_dec1 = TEMP_Value%1000/100;  
	    WriteTW8832( 0x06, 0x02 + FONT_WIN1_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[H_dec1][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x03 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec1][1]); 
	    WriteTW8832( 0x06, 0x0b + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec1][2]); 
	    WriteTW8832( 0x06, 0x0c + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec1][3]); 
	}
    else if((temp_H_dec1 != H_dec1) & (H_dec1 == 0 ) & (TEMP_Value < 99)){
    	temp_H_dec1 = H_dec1 = TEMP_Value%1000/100;  
		WriteTW8832( 0x06, 0x02 + FONT_WIN1_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x03 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0b + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0c + FONT_WIN1_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
    }
    
    if((temp_H_dec2 != H_dec2) & (TEMP_Value > 9)){
    	temp_H_dec2 = H_dec2 = TEMP_Value%100/10;  
	    WriteTW8832( 0x06, 0x04 + FONT_WIN1_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[H_dec2][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x05 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec2][1]); 
	    WriteTW8832( 0x06, 0x0d + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec2][2]); 
	    WriteTW8832( 0x06, 0x0e + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec2][3]); 

	    WriteTW8832( 0x06, 0x06 + FONT_WIN1_OSDADDR_OFFSET );  //Blank                            
	    WriteTW8832( 0x07, 40 ); 
	    WriteTW8832( 0x06, 0x0f + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 41 ); 
    }
    else if((temp_H_dec2 != H_dec2) & (H_dec2 == 0 ) & (TEMP_Value < 9)){
    	temp_H_dec2 = H_dec2 = TEMP_Value%100/10;  
		WriteTW8832( 0x06, 0x04 + FONT_WIN1_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x05 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0d + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0e + FONT_WIN1_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x06 + FONT_WIN1_OSDADDR_OFFSET );  //Blank                            
	    WriteTW8832( 0x07, 40 ); 
	    WriteTW8832( 0x06, 0x0f + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 41 ); 
    }
    
    if(temp_H_dec3 != H_dec3){
    	temp_H_dec3= H_dec3 = TEMP_Value%10;  
	    WriteTW8832( 0x06, 0x07 + FONT_WIN1_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[H_dec3][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x08 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec3][1]); 
	    WriteTW8832( 0x06, 0x10 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec3][2]); 
	    WriteTW8832( 0x06, 0x11 + FONT_WIN1_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[H_dec3][3]); 
    }
    //WriteTW8832( 0x04, 0x0C );// Display RAM Access Mode
}

//=============================================================================
//		void FontDemo( void )
//=============================================================================
void Cool_TEMP_Display(u16 TEMP_Value)
{
    C_dec0 = TEMP_Value/1000;
    C_dec1 = (TEMP_Value%1000)/100;
    C_dec2 = (TEMP_Value%100)/10;
    C_dec3 = TEMP_Value%10;
    
    if((temp_C_dec0 != C_dec0) & (TEMP_Value > 999)){
    	temp_C_dec0 = C_dec0 = TEMP_Value/1000;
	    WriteTW8832( 0x06, 0x00 + FONT_WIN2_OSDADDR_OFFSET );     // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[C_dec0][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x01 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec0][1] );
	    WriteTW8832( 0x06, 0x09 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec0][2] );
	    WriteTW8832( 0x06, 0x0a + FONT_WIN2_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, decimal_font[C_dec0][3] );
	}
    else if((temp_C_dec0 != C_dec0) & (C_dec0 == 0 ) & (TEMP_Value < 999)){
	    temp_C_dec0 = C_dec0 = TEMP_Value/1000;  
	    WriteTW8832( 0x06, 0x00 + FONT_WIN2_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x01 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x09 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0a + FONT_WIN2_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
    }
    
    if((temp_C_dec1 != C_dec1) & (TEMP_Value > 99)){
	    temp_C_dec1 = C_dec1 = TEMP_Value%1000/100;
	    WriteTW8832( 0x06, 0x02 + FONT_WIN2_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[C_dec1][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x03 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec1][1]); 
	    WriteTW8832( 0x06, 0x0b + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec1][2]); 
	    WriteTW8832( 0x06, 0x0c + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec1][3]); 
	}
    else if((temp_C_dec1 != C_dec1) & (C_dec1 == 0 ) & (TEMP_Value < 99)){
	    temp_C_dec1 = C_dec1 = TEMP_Value%1000/100; 
	    WriteTW8832( 0x06, 0x02 + FONT_WIN2_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x03 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0b + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0c + FONT_WIN2_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
    }
    
    if((temp_C_dec2 != C_dec2) & (TEMP_Value > 9)){
	    temp_C_dec2 = C_dec2 = TEMP_Value%100/10;
	    WriteTW8832( 0x06, 0x04 + FONT_WIN2_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[C_dec2][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x05 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec2][1]); 
	    WriteTW8832( 0x06, 0x0d + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec2][2]); 
	    WriteTW8832( 0x06, 0x0e + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec2][3]); 

	    WriteTW8832( 0x06, 0x06 + FONT_WIN2_OSDADDR_OFFSET ); //Blank                            
	    WriteTW8832( 0x07, 40 ); 
	    WriteTW8832( 0x06, 0x0f + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 41 ); 
	}
    else if((temp_C_dec2 != C_dec2) & (C_dec2 == 0 ) & (TEMP_Value < 9)){
	    temp_C_dec2 = C_dec2 = TEMP_Value%100/10; 
	    WriteTW8832( 0x06, 0x04 + FONT_WIN2_OSDADDR_OFFSET );                 // OSD Display Ram Addr
	    WriteTW8832( 0x07, 40); // FontRam Addr
	    WriteTW8832( 0x06, 0x05 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40 );
	    WriteTW8832( 0x06, 0x0d + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);
	    WriteTW8832( 0x06, 0x0e + FONT_WIN2_OSDADDR_OFFSET );                           
	    WriteTW8832( 0x07, 40 );
	    //WriteTW8832( 0x06, 0x06 + FONT_WIN2_OSDADDR_OFFSET ); //Blank                            
	    //WriteTW8832( 0x07, 40 ); 
	    //WriteTW8832( 0x06, 0x0f + FONT_WIN2_OSDADDR_OFFSET );                            
	    //WriteTW8832( 0x07, 40 ); 
    }

    if(temp_C_dec3 != C_dec3){
	    temp_C_dec3 = C_dec3 = TEMP_Value%10;
	    WriteTW8832( 0x06, 0x06 + FONT_WIN2_OSDADDR_OFFSET );   // OSD Display Ram Addr
	    WriteTW8832( 0x07, decimal_font[C_dec3][0]);                        // FontRam Addr
	    WriteTW8832( 0x06, 0x07 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec3][1]); 
	    WriteTW8832( 0x06, 0x0f + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec3][2]); 
	    WriteTW8832( 0x06, 0x10 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, decimal_font[C_dec3][3]);     
		WriteTW8832( 0x06, 0x11 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);   
		WriteTW8832( 0x06, 0x08 + FONT_WIN2_OSDADDR_OFFSET );                            
	    WriteTW8832( 0x07, 40);  
	}

    //WriteTW8832( 0x04, 0x0C );// Display RAM Access Mode
}
#endif

//=============================================================================
//		void FontDisplay( void )
//=============================================================================
void FontDisplay( void )
{
	//u8	i;
	
	//--- Window1 Setting
    FontOsdWinScreen( 0,  88, 16, 8, 2, 0, 0 );
    FontOsdWinScreen( 1, 198, 430, 9, 2, 0, 0 );
    FontOsdWinScreen( 2, 628, 430, 9, 2, 0, 0 );
  
    
	WriteTW8832( 0xff, 0x03 );
	/*
	WriteTW8832( 0x17, 0x00 );
	WriteTW8832( 0x18, 0x00 );
	WriteTW8832( 0x19, 0x00 );
	WriteTW8832( 0x1A, 0x00 );
	WriteTW8832( 0x1B, 0x00 );
	WriteTW8832( 0x1C, 0x00 );
	WriteTW8832( 0x1D, 0x00 );
	WriteTW8832( 0x1E, 0x00 );
	WriteTW8832( 0x1F, 0x00 );
    */
    WriteTW8832( 0x17, 0x00 );
    WriteTW8832( 0x27, 0x00 );
    WriteTW8832( 0x37, 0x00 );
    WriteTW8832( 0x1F, 0x00 );    // OSD Display RAM Start Addr of OSD Window 1
    WriteTW8832( 0x2F, 0x10 );    // OSD Display RAM Start Addr of OSD Window 2
    WriteTW8832( 0x3F, 0x22 );    // OSD Display RAM Start Addr of OSD Window 3
    
	//--- Write Display RAM
	WriteTW8832( 0x0b, 0xff ); // multi-font start

	WriteTW8832( 0x00, 0x03 ); // bypass OSD/Font RAM
	WriteTW8832( 0x04, 0x0c ); // Auto Inc.
	WriteTW8832( 0x08, 0x0f ); // Attr Font & Background Color

	TimeDelay_msec(3);
	WriteTW8832( 0x11, 0x0f ); // Alpha Blending
	TimeDelay_msec(3);
    WriteTW8832( 0x21, 0x0f ); // Alpha Blending
    TimeDelay_msec(3);
    WriteTW8832( 0x31, 0x0f ); // Alpha Blending
	TimeDelay_msec(3);

	WriteTW8832( 0x11, 0x0f ); // Alpha Blending
	TimeDelay_msec(3);
    WriteTW8832( 0x21, 0x0f ); // Alpha Blending
    TimeDelay_msec(3);
    WriteTW8832( 0x31, 0x0f ); // Alpha Blending
	TimeDelay_msec(3);
}


//=============================================================================
//		void FontDemo( void )
//=============================================================================
void FontDemo( void )
{
	FontDMA();
	FontDisplay();
	FontOsdWinEnable( 0, 1 );
    FontOsdWinEnable( 1, 1 );
    FontOsdWinEnable( 2, 1 );
}


/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
