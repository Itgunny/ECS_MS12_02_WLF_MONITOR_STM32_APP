/**
  ******************************************************************************
  * @file    TW8832_OSD.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW8832_OSD.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TW8832_OSD_H
#define __TW8832_OSD_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPI_OSD_PAGE				0x04

#define	DECODER_PAGE				0x01
#define	SCALER_PAGE					0x02
#define	FONT_OSD_PAGE				0x03
#define	SPI_OSD_PAGE				0x04

#define	SPI_OSD_ST					0x00
#define	SPI_WIN0_ST					0x20
#define	SPI_WIN1_ST					0x40

#define	SPI_OSDWIN_ENABLE			0x00
#define	SPI_OSDWIN_BUFFERSTART		0x09
#define	SPI_OSDWIN_DISPSIZE			0x0C
#define	SPI_OSDWIN_DISPOFFSET		0x10
#define	SPI_OSDWIN_SCREEN			0x01
#define	SPI_OSDWIN_ANIMATION		0x15

#define	DMA_SIZE					0x8000L

#define	FONTWIN1_ST					0x10
#define	FONTWIN2_ST					0x20
#define	FONTWIN3_ST					0x30
#define	FONTWIN4_ST					0x40

#define	FONTWIN_ENABLE				0x00
#define	FONT_ALPHA					0x01

#define FONT_WIN1_OSDADDR_OFFSET    0x10
#define FONT_WIN2_OSDADDR_OFFSET    0x22
#define FONT_WIN3_OSDADDR_OFFSET    0x10

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void SpiOsdWinEnable	(u8 winno, u8 en);
extern void SpiOsdWinBufferMem (u8 winno, u32 start);
extern void SpiOsdWinBufferSizeXY (u8 winno, u16 x, u16 y);
extern void SpiOsdWinBufferOffsetXY (u8 winno, u16 x, u16 y);
extern void SpiOsdWinScreen (u8 winno, u16 x, u16 y, u16 w, u16 h);
extern void SpiOsdLoadLUT (u32 address, u32 DMA_size );
extern void SpiOsdAnimation (u8 winno, u8 mode, u8 FrameH, u8 FrameV, u8 Duration);
extern void SpiOsdWinAlpha (u8 winno, u8 alpha );
extern void SpiOsdPixelAlpha (u8 winno, u8 alpha );

//=============================================================================
//		OSD Register Definition	  for FONT
//=============================================================================
extern void FontDMA( void );
extern void FontOsdWinEnable (u8 winno, u8 en);
extern void FontOsdWinAlpha (u8 winno, u8 color, u8 alpha);
extern void FontOsdWinScreen (u8 winno, u16 x, u16 y, u8 w, u8 h, u8 zoomH, u8 zoomV);
#if 0
extern void RPM_Display (u16 RPM_Value);
extern void Hyd_TEMP_Display (u16 TEMP_Value);
extern void Cool_TEMP_Display (u16 TEMP_Value);
#endif
extern void FontDisplay (void);
extern void FontDemo (void);

#endif /* __TW8832_OSD_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
