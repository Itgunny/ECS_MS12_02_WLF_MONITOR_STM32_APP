/**
  ******************************************************************************
  * @file    TW8816_OSD.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW8816_OSD.c module
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
#ifndef __TW8816_OSD_H
#define __TW8816_OSD_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


extern void SetFontOSDWindow(void);
extern void SetDisplayCH1(void);
extern void SetDisplayCH2(void);
extern void SetDisplayCH3(void);
extern void SetDisplayCH4(void);
extern void SetDisplayCHBlank(void);
extern void SetDisplayNosignal(void);
extern void SetDisplayWarning(void);
extern void SetDisplayNosignalBlank(void);
extern void SetDisplayIcon(void);
extern void SetChangeSpeakerIcon(void);
extern void SetChange2DBirdView(void);
extern void SetChangeFrontView(void);
extern void SetChangeLeftView(void);
extern void SetChangeBackView(void);
extern void SetChangeRightView(void);
extern void SetChange3DBirdView(void);
extern void SetChange3DRearView(void);
extern void SetChange4ChannelView(void);
extern void SetChange3DLeftView(void);
extern void SetChange3DRightView(void);
extern void SetBlankIcon(void);
extern void SetChangeXIcon(void);
extern void SetDisplayGreenGuideLine(void);
extern void SetDisplayRedGuideLine(void);
extern void SetDisplayBlankGreenGuideLine(void);
extern void SetDisplayBlankRedGuideLine(void);
extern void SetGreenLineIcon(void);
extern void SetGreenBlankLineIcon(void);
extern void SetDisplayNosignalBlankAAVM(void);
#endif /* __TW8816_OSD_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
