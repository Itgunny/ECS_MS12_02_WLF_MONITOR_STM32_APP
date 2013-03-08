/**
  ******************************************************************************
  * @file    KeySwitch.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for KeySwitch.c module
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
#ifndef __KeySwitch_H
#define __KeySwitch_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//  System_Init.c 에서 이미 설정하였지만, 다시 지정하기 위해서 아래의 define 선언.!!!
//  System_Init.h 에서 선언한 것과 macro value만 다른 것이다. 
//  KeySwitch
#define KeySW0                  GPIO_Pin_6  //  Input   ->  MENU
#define KeySW1                  GPIO_Pin_7  //  Input   ->  LEFT
#define KeySW2                  GPIO_Pin_8  //  Input   ->  ESC
#define KeySW3                  GPIO_Pin_9  //  Input   ->  RIGHT
#define KeySW4                  GPIO_Pin_10 //  Input   ->  ENTER
#define KeySWx_PORT             GPIOF

//	첫번째   키를 눌렀을 때는 Key 값 +0x40
//	연속으로 키를 눌렀을 때는 Key 값 +0x70
#define Continuous_Key			0x30		//	연속키 값을 보내기 위해서 0x40 + 0x30을 할 것이다.

#define KEYSWITCH_MENU          0x10    	//	+0x70 : VK_F17(0x80), +0x40 : VK_P(0x50)
#define KEYSWITCH_LEFT          0x08		//	+0x70 : VK_F9 (0x78), +0x40 : VK_H(0x48)	
#define KEYSWITCH_ESC_CAM       0x04		//	+0x70 : VK_F5 (0x74), +0x40 : VK_D(0x44)
#define KEYSWITCH_RIGHT         0x02		//	+0x70 :	VK_F3 (0x72), +0x40 : VK_B(0x42)
#define KEYSWITCH_ENTER         0x01		//	+0x70 :	VK_F2 (0x71), +0x40 : VK_A(0x41)

//	기타 시스템 용도로 사용하는 키는 Key 값 +0x40으로 처리.
#define KEYSWITCH_NONE		    0x20		//	+0x40 : VK_NUMPAD0(0x60) 
#define KEYSWITCH_POWER_OFF     0x21		//	+0x40 : VK_NUMPAD1(0x61)
											
#define MAXSWITCH               5           //  Input Switch 

#define KeyCMD  		  	  	0x4B   		//	KeyCMD - 통신 Command Data

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
extern void KeySwitch_Init(void);

#endif /* __KeySwitch_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
