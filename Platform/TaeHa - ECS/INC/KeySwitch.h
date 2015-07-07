/**
  ******************************************************************************
  * @file    KeySwitch.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for KeySwitch.c module
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
#ifndef __KeySwitch_H
#define __KeySwitch_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//  System_Init.c 에서 이미 설정하였지만, 다시 지정하기 위해서 아래의 define 선언.!!!
//  System_Init.h 에서 선언한 것과 macro value만 다른 것이다. 
//  KeySwitch
#define KeySCAN0          		GPIO_Pin_0	//	Key Matrix 00
#define KeySCAN1          		GPIO_Pin_1  //	Key Matrix 01
#define KeySCAN2          		GPIO_Pin_2 	//	Key Matrix 02
#define KeyInput0          		GPIO_Pin_10 //	Key Matrix 10
#define KeyInput1          		GPIO_Pin_11 //	Key Matrix 11
#define KeyInput2          		GPIO_Pin_12 //	Key Matrix 12
#define KeyInput3          		GPIO_Pin_13 //	Key Matrix 13
#define KeyInput4         		GPIO_Pin_14 //	Key Matrix 14
#define KeyInput5          		GPIO_Pin_15 //	Key Matrix 15
#define KeySWXX_PORT       		GPIOF

//	첫번째   키를 눌렀을 때는 Key 값 +0x40
//	연속으로 키를 눌렀을 때는 Key 값 +0x70
#define Continuous_Key			0x30		//	연속키 값을 보내기 위해서 0x40 + 0x30을 할 것이다.

#define KEYSWITCH_MENU         	0x41    		//	
#define KEYSWITCH_LEFT          	0x42		//	
#define KEYSWITCH_ENTER         	0x44		//	
#define KEYSWITCH_RIGHT         	0x48		//	
#define KEYSWITCH_ESC	       	0x50		//	
#define KEYSWITCH_CAM	       	0x81		//

#define KEYSWITCH_REAR_WIPER	       	0xc4		//
#define KEYSWITCH_REAR_WIPER_Washer	       	0xe4		//

//	기타 시스템 용도로 사용하는 키는 Key 값 +0x40으로 처리.
#define KEYSWITCH_NONE		    0x20		//	+0x40 : VK_NUMPAD0(0x60) 
#define KEYSWITCH_POWER_OFF     0xF5		//	+0x40 : VK_NUMPAD1(0x61)
											
#define MAXSCAN 	            3           //  Scan Switch 
#define MAXINPUT               	6           //  Input Switch 

#define MAXSWITCH               6           //  Input Switch 

#define KeyCMD  		  	  	0x00   		//	KeyCMD - 통신 Command Data
#define KeyRES  		  	  	0x80   		//	KeyCMD - 통신 Command Data


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

extern uint32_t                  KeySwitch_Value;

/* Exported functions ------------------------------------------------------- */
extern void KeySwitch_Init(void);
extern void KeySwitch_Process(void);
extern void KeyTest_TEST(uint8_t value);

extern void KeySwitch_SendToEXYNOS(uint32_t KeyValue, uint8_t LongKey);
// ++, 150707 bwk
#if 0
extern void SMK_SendToExynos(uint8_t SMK_Auth, uint8_t SMK_Msg, uint8_t SMK_Count);
#else
extern void SMK_SendToExynos(uint8_t SMK_Auth, uint8_t SMK_Msg, uint8_t SMK_Count, uint8_t Response_Code, uint8_t Response_Flag);
#endif
// --, 150707 bwk

// ++, 150204 sys3215
void Make_Key_Status(uint32_t KeyValue);
// --, 150204 sys3215

#endif /* __KeySwitch_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
