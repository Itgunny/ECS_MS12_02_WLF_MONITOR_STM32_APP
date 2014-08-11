/**
  ******************************************************************************
  * @file    TimeDelay.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TimeDelay.c module
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
#ifndef __TimeDelay_H
#define __TimeDelay_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct 
{	
	unsigned long  Cnt_1mSec;
	unsigned short Flag_1mSec;
	unsigned short Flag_10mSec;
	unsigned short Flag_100mSec;        
	unsigned short Flag_200mSec;        
	unsigned short Flag_300mSec;        
	unsigned short Flag_400mSec;        
	unsigned short Flag_500mSec;        
 	unsigned short Flag_1Sec;
} WL9FM_TIME_DATA;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern WL9FM_TIME_DATA WL9FM_TIME;

/* Exported functions ------------------------------------------------------- */
extern void Delay(__IO uint32_t nTime);
extern void TimeDelay_Decrement(void);
extern void TimeDelay(__IO uint32_t nTime);
extern void TimeDelay_msec(uint32_t nCount);
extern void TimeDelay_usec(uint32_t nCount);


#endif /* __TimeDelay_H */

