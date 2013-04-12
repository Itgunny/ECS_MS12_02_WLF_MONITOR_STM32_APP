/**
  ******************************************************************************
  * @file    Buzzer.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Buzzer.c module
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

uint8_t Buzzer_SendCnt, Buzzer_SendFlag;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;
    
    DebugMsg_printf("++ BUZZER (TIM4 : 10msec), TIM4_IRQn Initialize START\r\n");

    //  Buzzer GPIO는 System_Init.c 에서 설정
    #if 0

    GPIO_InitTypeDef    GPIO_InitStructure;

	//  BUZZER_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = BUZZER_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
	
    #endif
    
    TIM_TimeBaseStructure.TIM_Period        = 0x1388;   //  (1 / 1MHz) * 10000 -> 10msec
    TIM_TimeBaseStructure.TIM_Prescaler     = 0xA8;     //  168 MHz / 168 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
    //  TIM4 Enable counter
    TIM_Cmd(TIM4, ENABLE);
    
    //  Enable TIM4 Update Interrupt
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    //  Enable the TIM4 Interrupt, BUZZER
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	WL9FM_BUZZER.Status = 0;
	WL9FM_BUZZER.OnTime = 0;
	WL9FM_BUZZER.OnCnt  = 0;
	WL9FM_BUZZER.Current_Status = 0;

	DebugMsg_printf("-- BUZZER (TIM4 : 10msec), TIM4_IRQn Initialize END\r\n");

	//	Buzzer SendtoEXYNOS 변수
	Buzzer_SendCnt = Buzzer_SendFlag = 0;
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_Set(uint16_t OnTime)
{
    WL9FM_BUZZER.Status = 2;
    WL9FM_BUZZER.OnTime = OnTime;        
    WL9FM_BUZZER.OnCnt  = 0;
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_On(void)
{
    GPIO_SetBits(BUZZER_PORT, BUZZER_CTRL); 
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_UnLimitOn(void)
{
    WL9FM_BUZZER.Status = 1;
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_Off(void)
{
    GPIO_ResetBits(BUZZER_PORT, BUZZER_CTRL);  
}

/**
  * @brief  None
  * @param  None
  * @retval None
  */
void Buzzer_UnLimitOff(void)
{
    WL9FM_BUZZER.Status = 0;	
}


/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
