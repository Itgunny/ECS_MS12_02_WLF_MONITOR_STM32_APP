/**
  ******************************************************************************
  * @file    WL9F_Display_Variable.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Main Header
  *
  * Project Name       : WL9F Display Common
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
#ifndef __WL9F_Display_Variable_H
#define __WL9F_Display_Variable_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// EEPROM Clear Variables
WL9FM_SaveE2PROM1			*SaveE2PROM1;
WL9FM_SaveE2PROM2			*SaveE2PROM2;
WL9FM_SaveE2PROM3			*SaveE2PROM3;

WL9FM_SaveE2PROMoniInfo		*SaveE2PROMoniInfo;

WL9F_DATA_RTC   	   	    WL9FM_RTC;
WL9F_TIME_DATA 		        WL9FM_TIME;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __WL9F_Display_Variable_H */
