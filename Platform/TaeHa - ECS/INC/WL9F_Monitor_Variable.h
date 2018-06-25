/**
  ******************************************************************************
  * @file    WL9F_Monitor_Variable.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Main Header
  *
  * Project Name       : WL9F Monitor Common
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
#ifndef __WL9F_Monitor_Variable_H
#define __WL9F_Monitor_Variable_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// EEPROM Clear Variables
WL9FM_SaveE2PROM1			*SaveE2PROM1;
WL9FM_SaveE2PROM2			*SaveE2PROM2;
WL9FM_SaveE2PROM3			*SaveE2PROM3;

WL9FM_SaveE2PROMoniInfo		*SaveE2PROMoniInfo;

WL9FM_DATA_RTC   	   	    WL9FM_RTC;
WL9FM_TIME_DATA 		    WL9FM_TIME;
WL9FM_BUZZER_DATA   		WL9FM_BUZZER;
WL9FM_LCDBL_DATA   		    WL9FM_LCDBL;

USARTx_DATA  				WL9FM_USART_DATA;
USARTx_INDEX 				WL9FM_USART_INDEX;

USARTx_FILE_RX_DATA			WL9FM_USART_RX_FILE_DATA;
USARTx_FILE_RX_DATA			WL9FM_USART_FILE_DATA;

uint32_t                    	KeySwitch_Value;            //  GPIO Key Value
uint32_t 					LAMP_Update_Data;			//	LAMP Value
uint32_t 					Old_LAMP_Update_Data;			//	LAMP Value

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __WL9F_Monitor_Variable_H */
