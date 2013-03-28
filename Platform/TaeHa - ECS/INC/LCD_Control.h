/**
  ******************************************************************************
  * @file    LCD_Control.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for LCD_Control.c module
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
#ifndef __LCD_Control_H
#define __LCD_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
typedef struct 
{	
	uint8_t  OnOff;
	uint8_t  LEVEL;
	uint16_t PWM;
} WL9FM_LCDBL_DATA;

/* Private define ------------------------------------------------------------*/
#define     LED_ON                  		1           //  LED All On
#define     LED_OFF                 		0           //  LED All Off

#define     LCDPWR_ON                  		1           //  LCD Power On
#define     LCDPWR_OFF                 		0           //  LCD Power Off

#define     LCDBL_ON                  		0           //  LCDBL On
#define     LCDBL_OFF                 		1           //  LCDBL Off

#define 	MaxBackLightLEVEL				9			//	LEVEL은 1 ~ 7 설정. LEVEL0은 BackLight Off
#define 	DefaultLCDBLLEVEL				6			//	Default LCD BackLight LEVEL

#define 	LCDBLCMD    	  				0x4C   		//	LCD BackLight CMD	- 통신 Command Data

#define 	STM32F4_DISPLAY					1			
#define 	EXYNOS_DISPLAY					0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern WL9FM_LCDBL_DATA	WL9FM_LCDBL;

/* Exported functions ------------------------------------------------------- */
extern void LCD_Control_Init(void);
extern void LCD_POWER_ONOFF(uint8_t BitData);
extern void LED_POWER_ONOFF(uint8_t BitData);
extern void LCDBL_Init(void);
extern void LCDBL_ONOFF(uint8_t BitData);
extern void LCDBL_PWM_LEVEL(uint8_t LEVEL);
extern void LCDBL_PWM_CONTROL(uint16_t PWM_VALUE);
extern void LCD_Display_Change(uint8_t BitData);
#endif /* __LCD_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
