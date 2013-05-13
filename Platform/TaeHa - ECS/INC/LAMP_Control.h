/**
  ******************************************************************************
  * @file    LAMP_Control.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for LAMP_Control.c module
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
#ifndef __LAMP_Control_H
#define __LAMP_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define 	LAMPCMD			0x4d

#define	CMD_Ride_Control_Lamp		0x01
#define	CMD_Quick_Coupler_Lamp	0x02
#define	CMD_Auto_Grease_Lamp		0x03
#define	CMD_Beacon_Lamp			0x04
#define	CMD_Mirror_Heat_Lamp		0x05
#define	CMD_Rear_Wiper_Lamp		0x06
#define	CMD_user					0x07


#define 	C_LAMP_SCLK_HIGH()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_SET)
#define 	C_LAMP_SCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_RESET)

#define 	C_LAMP_SLCLK_HIGH()     GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_SET)
#define 	C_LAMP_SLCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_RESET)

#define 	C_LAMP_SDATA_HIGH()    	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_SET)
#define 	C_LAMP_SDATA_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_RESET)

#define 	C_LAMP_CLR_ENABLE()    	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_SET)
#define 	C_LAMP_CLR_DISABLE() 	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_RESET)


#define	Ride_Control_Manual_Lamp		0x00000040		//key pad L7 Green
#define	Ride_Control_Auto_Lamp			0x00000080		//key pad L8 Blue
#define	Ride_Control_Lamp_Off			0x000000c0

#define 	Quick_Coupler_Lock_Lamp		0x00000100		//key pad L9 Green
#define 	Quick_Coupler_UnLock_Lamp		0x00000200		//key pad L10 Red
#define 	Quick_Coupler_Lamp_Off			0x00000300

#define	Auto_Grease_Manual_Lamp		0x00000400		//key Pad L11	Grean
#define	Auto_Grease_Auto_Lamp			0x00000800		//key Pad L12	Blue
#define	Auto_Grease_Lamp_Off			0x00000c00

#define	Beacon_Lamp					0x00001000		//Key pad L13 
#define	Mirror_Heat_Lamp				0x00002000		//Key pad L14 
#define	Rear_Wiper_Lamp				0x00004000		//key pad L15

#define		BGLED0						0x00100000
#define		BGLED1						0x00200000
#define		BGLED2						0x00400000

#define 	LAMP_ALL_ON 					0x00707fc0
#define 	LAMP_ALL_OFF 					0x00000000




/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint32_t LAMP_Update_Data;
/* Exported functions ------------------------------------------------------- */
extern void Lamp_Update_State(void);
extern void Lamp_Update_System(void);
extern void LAMP_Control_Init(void);

#endif /* __LAMP_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
