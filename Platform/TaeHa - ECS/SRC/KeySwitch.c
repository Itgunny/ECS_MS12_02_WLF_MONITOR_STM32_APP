/**
  ******************************************************************************
  * @file    KeySwitch.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   KeySwitch.c module
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

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//  KeySwitch.h -> KeySwitch Input GPIO Port array
GPIO_TypeDef*  KEYSWITCH_PORT[MAXSWITCH]   =   {  
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT,
                                            };

//  KeySwitch.h -> KeySwitch Input GPIO Pin array
const uint16_t KEYSWITCH_PIN[MAXSWITCH]    =   { 
                                                KeySW0, 
                                                KeySW1, 
                                                KeySW2, 
                                                KeySW3,
                                                KeySW4,
                                            };

//  KeySwitch.h -> Press Input KeySwitch Value array
const uint8_t KEYSWITCH_VALUE[MAXSWITCH]   =   {
                                                KEYSWITCH_MENU,    
                                                KEYSWITCH_LEFT,    
                                                KEYSWITCH_ESC_CAM,    
                                                KEYSWITCH_RIGHT,    
                                                KEYSWITCH_ENTER,    
                                            };                                                

uint8_t     KeySwitchScan;
uint8_t     Temp_Value1, Temp_Value2, Temp_Value3, Temp_Cnt;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void KeySwitch_Init(void)
{

}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
