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

#define 	C_LAMP_SCLK_HIGH()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_SET)
#define 	C_LAMP_SCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_RESET)

#define 	C_LAMP_SLCLK_HIGH()     GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_SET)
#define 	C_LAMP_SLCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_RESET)

#define 	C_LAMP_SDATA_HIGH()    	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_SET)
#define 	C_LAMP_SDATA_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_RESET)

#define 	C_LAMP_CLR_ENABLE()    	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_SET)
#define 	C_LAMP_CLR_DISABLE() 	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_RESET)


#define 	LAMP_ALL_ON 			0x7FFFFFFF
#define 	LAMP_ALL_OFF 			0x00000000

#define		BGLED0					0x00100000
#define		BGLED1					0x00200000
#define		BGLED2					0x00400000


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
