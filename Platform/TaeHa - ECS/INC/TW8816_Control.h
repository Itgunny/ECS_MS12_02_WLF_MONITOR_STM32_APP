/**
  ******************************************************************************
  * @file    TW8816_Control.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW8816_Control.c module
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
#ifndef __TW8816_Control_H
#define __TW8816_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define		TW8816_I2C_Addr			0x8A

#define 	TW8816_SCL0				GPIO_ResetBits(TW8816_I2C2_PORT, TW8816_I2C2_SCL)
#define 	TW8816_SCL1				GPIO_SetBits(TW8816_I2C2_PORT, TW8816_I2C2_SCL)
#define 	TW8816_SDA_READ			GPIO_ReadInputDataBit(TW8816_I2C2_PORT, TW8816_I2C2_SDA)

#define 	TW8816_SDAIN   			TW8816_PortChange(0)
#define 	TW8816_SDAOUT  			TW8816_PortChange(1) 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern u8  InitCVBSAll_8816[];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void I2C2_Write_8816(u8 WData);
extern u8 I2C2_Read_8816(void);
extern void I2C2_ByteWrite_8816(u16 in_AddrVal, u8 in_DataVal);
extern u8	I2C2_ByteRead_8816(u16 in_AddrVal);
extern void	WriteTW8816(u8 in_AddrVal, u8 in_DataVal);
extern u8	ReadTW8816(u8 in_AddrVal);

extern void	InitCVBSRegister_8816(void);
extern void I2C2DeviceInitialize_8816(u8 *RegSet);


extern void TW8816_Control_Init(void);
extern void TW8816_CameraMode(u8 Mode, u8 OSD);
extern void TW8816_CheckCamera_Input(u8 Mode);

#endif /* __TW8816_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/

