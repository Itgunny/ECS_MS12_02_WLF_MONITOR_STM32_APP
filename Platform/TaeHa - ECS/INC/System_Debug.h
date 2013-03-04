/**
  ******************************************************************************
  * @file    System_Debug.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/28/2013
  * @brief   
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
#ifndef __System_Debug_H
#define __System_Debug_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "WL9F_Display_Common.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEBUG
#define DEBUG_MSG_LEVEL0            //  DebugMsg_printf를 사용하지 않는다.     
//#define DEBUG_MSG_LEVEL1          //  DebugMsg_printf를 printf로 변경.

#define DEBUG_MSG_FUNC_START        (DebugMsg_FunctionStart(__FUNCTION__))
#define DEBUG_MSG_FUNC_END          (DebugMsg_FunctionEnd(__FUNCTION__))

#define DEBUG_MSG_FUNC_NOTIFY       (DebugMsg_FunctionNotify(__FUNCTION__, __LINE__))
#define DEBUG_MSG_FUNC_ERROR        (DebugMsg_FunctionError(__FUNCTION__, __LINE__))

#ifdef DEBUG_MSG_LEVEL1
#define    DebugMsg_printf(...)     printf(__VA_ARGS__)
#define    SerialPutString(...)     printf(__VA_ARGS__)
#else
#define    DebugMsg_printf(...)     ((void)0)
#define    SerialPutString(...)     ((void)0)
#endif 

#ifdef USE_FULL_ASSERT

#define DEBUG_MSG_ASSERT            (DebugMsg_Assert(__FUNCTION__, __LINE__))

#else

#define DEBUG_MSG_ASSERT            ((void)0)

#endif /* USE_FULL_ASSERT */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void DebugMsg_FunctionStart(char const *fName_p);
extern void DebugMsg_FunctionEnd(char const *fName_p);
extern void DebugMsg_FunctionNotify(char const *fName_p, int lineNum);
extern void DebugMsg_FunctionError(char const *fName_p, int lineNum);

#ifdef USE_FULL_ASSERT
extern void DebugMsg_Assert(char const *fName_p, int lineNum);
#endif

#endif /* __System_Debug_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
