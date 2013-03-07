/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  	TimeDelay_Decrement();

    ++WL9FM_TIME.Cnt_1mSec;

	if (WL9FM_TIME.Cnt_1mSec % 1 == 0)                   //  1msec
	{
        WL9FM_TIME.Flag_1mSec = 1;

		if (WL9FM_TIME.Cnt_1mSec % 10 == 0)              //  10msec
		{
			WL9FM_TIME.Flag_10mSec = 1;

			if (WL9FM_TIME.Cnt_1mSec % 100 == 0)         //  100msec
			{
				WL9FM_TIME.Flag_100mSec = 1;

				if (WL9FM_TIME.Cnt_1mSec % 1000 == 0)    //  1000 msec
				{
					WL9FM_TIME.Flag_1Sec = 1;
					WL9FM_TIME.Cnt_1mSec = 0;
				}
			}
		}
	}    
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)  //  10msec Timer / TimeBase UP Counter
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    
    //  BUZZER Status가 "2" 일 경우 BUZZER OnTime 만큼 BUZZER On
    if (WL9FM_BUZZER.Status == 2)
    {
        if (WL9FM_BUZZER.OnCnt++ < WL9FM_BUZZER.OnTime)
        {
            Buzzer_On();
        }
        else
        {
            WL9FM_BUZZER.Status = 0;               
        }
    }        
    //  BUZZER Status가 "1" 일 경우 UnLimit BUZZER On
    else if (WL9FM_BUZZER.Status == 1)
    {
        Buzzer_On();    
    }    
    else
    {
        Buzzer_Off();
        
        WL9FM_BUZZER.Status = 0;               
        WL9FM_BUZZER.OnTime = 0;
        WL9FM_BUZZER.OnCnt  = 0;
    }

	#if 0
    CommErrCnt++;

    if(CommErrCnt >= 1000)
        CommErrCnt = 1001;
	#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
