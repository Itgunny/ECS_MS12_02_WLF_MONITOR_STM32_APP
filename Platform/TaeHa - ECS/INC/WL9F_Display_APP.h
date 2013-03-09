/**
  ******************************************************************************
  * @file    WL9F_Display_APP.h
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
#ifndef __WL9F_Display_APP_H
#define __WL9F_Display_APP_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "stm32f4xx.h"
#include "stm324xg_eval.h"

#include "System_Init.h"
#include "System_Debug.h"
#include "FM31X4.h"
#include "TimeDelay.h"
#include "GPIO_Control.h"
#include "Buzzer.h"
#include "Hardware_Version.h"
#include "KeySwitch.h"
#include "LCD_Control.h"
#include "TW2835_Control.h"
#include "TW2835_OSD.h"
#include "TW8832_Control.h"
#include "TW8832_OSD.h"
#include "UART_Control.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//#define     STM32_BUZZER      //  STM32 BUZZER

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
//  WL9F_Monitor_APP.c define
extern void Init_RTC(void);
extern void InitE2PROM(void);
extern void ReadE2PROM_ToSend(void);

extern void WL9F_Display_APP(void);
extern void WL9F_1mSecOperationFunc(void);
extern void WL9F_10mSecOperationFunc(void);
extern void WL9F_100mSecOperationFunc(void);
extern void WL9F_1SecOperationFunc(void);
extern void WL9F_System_Init_Start(void);

#endif /* __WL9F_Display_APP_H */
