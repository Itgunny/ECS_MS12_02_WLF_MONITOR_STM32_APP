/**
  ******************************************************************************
  * @file    System_Debug.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   System_Debug.c module
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

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#if 0
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	printf("Wrong parameters value: file %s on line %d\r\n", file, line);	

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
#endif

/**
  * @brief  DebugMsg xxxxx.
  * @param  
  * @retval None
  */

void DebugMsg_FunctionStart(char const *fName_p)
{
#ifdef DEBUG_MSG_LEVEL0
    printf("[START]  %s()\n", fName_p);
#endif
}

void DebugMsg_FunctionEnd(char const *fName_p)
{
#ifdef DEBUG_MSG_LEVEL0
    printf("[End]    %s()\n", fName_p);
#endif
}

void DebugMsg_FunctionNotify(char const *fName_p, int lineNum)
{
#ifdef DEBUG_MSG_LEVEL0
    printf("[Notify] %s() %d\n", fName_p, lineNum);
#endif
}

void DebugMsg_FunctionError(char const *fName_p, int lineNum)
{
#ifdef DEBUG_MSG_LEVEL0
    printf("[ERROR] %s() %d\n", fName_p, lineNum);
#endif
}

#ifdef USE_FULL_ASSERT
void DebugMsg_Assert(char const *fName_p, int lineNum)
{
    printf("ASSERT FAILED !!! %s() %d\n", fName_p, lineNum);
}
#endif

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/