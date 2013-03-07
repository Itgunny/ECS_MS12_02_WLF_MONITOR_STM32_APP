/**
  ******************************************************************************
  * @file    TW8832_Control.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW8832_Control.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TW8832_Control_H
#define __TW8832_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define		TW8832_I2C_Addr			0x8a

//	TW8832, TW2835 Set/Reset
#define		TW8832_RESET			GPIO_SetBits(CAMERA_nRESET_PORT, CAMERA_nRESET)	    
#define		TW8832_SET				GPIO_ResetBits(CAMERA_nRESET_PORT, CAMERA_nRESET)	

#define 	TW8832_SCL0				GPIO_ResetBits(TW8832_I2C2_PORT, TW8832_I2C2_SCL)
#define 	TW8832_SCL1				GPIO_SetBits(TW8832_I2C2_PORT, TW8832_I2C2_SCL)
#define 	TW8832_SDA_READ			GPIO_ReadInputDataBit(TW8832_I2C2_PORT, TW8832_I2C2_SDA)

#define 	TW8832_SDAIN   			TW8832_PortChange(0)
#define 	TW8832_SDAOUT  			TW8832_PortChange(1) 


#define		ContrastY				0x84
#define		BrightnessY				0x8A
#define		HueY					0x80
#define		SaturationY				0x85
#define		SharpnessY          	0x8B

#define		ContrastR				0x81
#define		BrightnessR				0x87
//#define	Sharpness				0x8B

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uc8 Sharpness[16];
extern u8  InputMain;	

extern u8  InitCVBSAll[];

/* Exported functions ------------------------------------------------------- */
extern void TW8832_Control_Init(void);
extern u16 SetYCbCrContrast(u16 val);
extern u16 SetYCbCrBright(u16 val);
extern u16 SetYCbCrSaturation(u16 val);
extern u8 ChangeCVBS(void);
extern u8 CheckDecoderVDLOSS(u8 n);
extern u8 CheckDecoderSTD(u8 n);
extern u8 CheckAndSetDecoderScaler(void);
extern u16 SetYCbCrSharp(u16 val);
extern u16 SetYCbCrHUE(u16 val);
extern void	InitCVBSRegister(void);
extern void I2C2DeviceInitialize(u8 *RegSet);

extern void TW8832_PortChange(unsigned char dir);
extern void I2C2_ByteWrite(u16 in_AddrVal, u8 in_DataVal);
extern u8	I2C2_ByteRead(u16 in_AddrVal);
extern void	WriteTW8832(u8 in_AddrVal, u8 in_DataVal);
extern u8	ReadTW8832(u8 in_AddrVal);


#endif /* __TW8832_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
