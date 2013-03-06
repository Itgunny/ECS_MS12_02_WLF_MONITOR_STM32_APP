/**
  ******************************************************************************
  * @file    TimeDelay.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TimeDelay.c module
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
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimeDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    { 
        TimingDelay--;
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  	TimingDelay = nTime;

  	while(TimingDelay != 0);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void TimeDelay(__IO uint32_t nTime)
{ 
    TimingDelay = nTime;

    while (TimingDelay != 0);
}

/**
  * @brief  Inserts a usec delay time.
  * @param  nCount: specifies the delay time length, in milliseconds.
  * @retval None
  */
void TimeDelay_usec(uint32_t nCount)
{
    vu32 i, j;

    for (i = 0; i < nCount; i++)
        for (j = 0; j < 5; j++);
}

/**
  * @brief  Inserts a msec delay time.
  * @param  nCount: specifies the delay time length, in milliseconds.
  * @retval None
  */
void TimeDelay_msec(uint32_t nCount)
{
    vu32 i, j;

#if 0
    for (i = 0; i < nCount; i++)
        for (j = 0; j < 5000; j++);
#else
	for (i = 0; i < nCount; i++)
        for (j = 0; j < 17000; j++);
#endif
}

