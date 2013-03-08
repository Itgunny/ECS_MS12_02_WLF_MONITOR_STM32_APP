/**
  ******************************************************************************
  * @file    LCD_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   LCD_Control.c module
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

/*
	ChannelPulse = (uint16_t) (((uint32_t) 0 * (TimerPeriod - 1)) / 10);  	//    0% : 0
	ChannelPulse = (uint16_t) (((uint32_t) 2 * (TimerPeriod - 1)) / 10);	//	 20% : 3327  
	ChannelPulse = (uint16_t) (((uint32_t) 3 * (TimerPeriod - 1)) / 10); 	//	 30% : 4991 
	ChannelPulse = (uint16_t) (((uint32_t) 4 * (TimerPeriod - 1)) / 10); 	//	 40% : 6655 
	ChannelPulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);  	//	 50% : 8319
	ChannelPulse = (uint16_t) (((uint32_t) 6 * (TimerPeriod - 1)) / 10);  	//	 60% : 9982
	ChannelPulse = (uint16_t) (((uint32_t) 7 * (TimerPeriod - 1)) / 10);  	//	 70% : 11646
	ChannelPulse = (uint16_t) (((uint32_t) 85 * (TimerPeriod - 1)) / 100);	//	 85% : 14142  
	ChannelPulse = (uint16_t) (((uint32_t) 10 * (TimerPeriod - 1)) / 10);  //	100% : 16638
*/
//	이 값을 설정할 때, 회로적으로 Inverting 된다.
//	100% -> 0%로 동작한다.
const uint16_t LCDBL_PWMLEVEL[MaxBackLightLEVEL] =  
{	
	16638, 	//  0 Step :   0%
    14142, 	//  1 Step :  20%
    11646, 	//  2 Step :  30%
    9982, 	//  3 Step :  40%
    8319, 	//  4 Step :  50%
    6655, 	//  5 Step :  60%
    4991, 	//  6 Step :  70%
    3327, 	//  7 Step :  85%
	0, 		//  8 Step : 100%
}; 

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  LED Enable
  * @param  None
  * @retval None
  */
void LED_POWER_ONOFF(uint8_t BitData)
{
    GPIO_WriteBit(LED_PORT, LED_CTRL, (BitAction) BitData);
}

/**
  * @brief  LCD Power Enable
  * @param  None
  * @retval None
  */
void LCD_POWER_ONOFF(uint8_t BitData)
{
    GPIO_WriteBit(LCDPWR_PORT, LCDPWR_CTRL, (BitAction) BitData);
}

void LCDBL_ONOFF(uint8_t BitData)
{
    GPIO_WriteBit(LCDBL_PORT, LCDBL_CTRL, (BitAction) BitData);

	WL9FM_LCDBL.OnOff = BitData;
}

/**
  * @brief  PWM Level Setting (LEVEL value를 받아서 설정한다.)
  * @param  pwm
  * @retval None
  */
void LCDBL_PWM_LEVEL(uint8_t LEVEL)
{
    //  PWM을 변경한 후에 항상 저장해 놓는다.
    WL9FM_LCDBL.PWM	  = LCDBL_PWMLEVEL[LEVEL];  
    WL9FM_LCDBL.LEVEL = LEVEL;
    LCDBL_PWM_CONTROL(WL9FM_LCDBL.PWM);
}

/**
  * @brief  PWM Value Setting (pwm value를 받아서, Pulse로 설정한다.)
  * @param  pwm
  * @retval None
  */
void LCDBL_PWM_CONTROL(uint16_t PWM_VALUE)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;

   	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;
   	TIM_OCInitStructure.TIM_OutputNState 	= TIM_OutputNState_Enable;
   	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;
   	TIM_OCInitStructure.TIM_OCIdleState 	= TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState 	= TIM_OCIdleState_Reset;

    //	Channel 1 Configuration in PWM mode
    TIM_OCInitStructure.TIM_Pulse = PWM_VALUE;
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);					
    
	// 	TIM8 counter enable
	TIM_Cmd(TIM8, ENABLE);			

	//	TIM8 Main Output Enable
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

void LCDBL_Init(void)
{
    DebugMsg_printf("++ LCD_Control_Init, LCDBL(TIM8 : PWM), ONOFF Initialize START\r\n");

  /* TIM8 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM8 input clock (TIM8CLK) is set to 2 * APB2 clock (PCLK2), since APB2 
    prescaler is different from 1.   
    TIM8CLK = 2 * PCLK2  
    PCLK2 = HCLK / 2 
    => TIM8CLK = 2 * (HCLK / 2) = HCLK = SystemCoreClock
   TIM8CLK = SystemCoreClock, Prescaler = 0, TIM8 counter clock = SystemCoreClock
   SystemCoreClock is set to 168 MHz for STM32F4xx devices
   
   The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIM8_Period = (SystemCoreClock / 17570) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM8_Period - 1) / 100
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  
  	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
  	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	uint16_t TimerPeriod  = 0;
	
	//	PWM Frequency : 500Hz (Mitsubishi 7" LCD)
	TimerPeriod = (SystemCoreClock / 250 ) - 1;
#if 0
	ChannelPulse = (uint16_t) (((uint32_t) 0 * (TimerPeriod - 1)) / 10);  	//    0% : 0
	ChannelPulse = (uint16_t) (((uint32_t) 2 * (TimerPeriod - 1)) / 10);	//	 20% : 3327  
	ChannelPulse = (uint16_t) (((uint32_t) 3 * (TimerPeriod - 1)) / 10); 	//	 30% : 4991 
	ChannelPulse = (uint16_t) (((uint32_t) 4 * (TimerPeriod - 1)) / 10); 	//	 40% : 6655 
	ChannelPulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);  	//	 50% : 8319
	ChannelPulse = (uint16_t) (((uint32_t) 6 * (TimerPeriod - 1)) / 10);  	//	 60% : 9982
	ChannelPulse = (uint16_t) (((uint32_t) 7 * (TimerPeriod - 1)) / 10);  	//	 70% : 11646
	ChannelPulse = (uint16_t) (((uint32_t) 85 * (TimerPeriod - 1)) / 100);	//	 85% : 14142  
	ChannelPulse = (uint16_t) (((uint32_t) 10 * (TimerPeriod - 1)) / 10);  //	100% : 16638
#endif
	
  	TIM_TimeBaseStructure.TIM_Prescaler         = 16;
  	TIM_TimeBaseStructure.TIM_CounterMode 	    = TIM_CounterMode_Up;
  	TIM_TimeBaseStructure.TIM_Period 			= TimerPeriod;
  	TIM_TimeBaseStructure.TIM_ClockDivision     = 0;
  	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

   	TIM_OCInitStructure.TIM_OCMode 			= TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState 	= TIM_OutputState_Enable;
   	TIM_OCInitStructure.TIM_OutputNState 	= TIM_OutputNState_Enable;
   	TIM_OCInitStructure.TIM_OCPolarity 		= TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity 	= TIM_OCNPolarity_High;
   	TIM_OCInitStructure.TIM_OCIdleState 	= TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState 	= TIM_OCIdleState_Reset;

    //	Channel 1 Configuration in PWM mode
    TIM_OCInitStructure.TIM_Pulse = LCDBL_PWMLEVEL[DefaultLCDBLLEVEL];
	
   	TIM_OC1Init(TIM8, &TIM_OCInitStructure);

  	// 	TIM8 counter enable
  	TIM_Cmd(TIM8, ENABLE);

  	// 	TIM8 Main Output Enable
  	TIM_CtrlPWMOutputs(TIM8, ENABLE);		
	
    DebugMsg_printf("-- LCD_Control_Init, LCDBL(TIM8 : PWM), ONOFF Initialize END\r\n");

	TimeDelay_msec(1000); 

	WL9FM_LCDBL.LEVEL = DefaultLCDBLLEVEL;
	WL9FM_LCDBL.PWM   = LCDBL_PWMLEVEL[DefaultLCDBLLEVEL];
}

void LCD_Display_Change(uint8_t BitData)
{
	//	Display Buffer를 변경하는 것이기 때문에
	//	표시하고자 하는 것을 하기 전에, 다른 것을 먼저 High-Z 상태로 만든다. 
	if (BitData == STM32F4_DISPLAY)
	{
	    GPIO_WriteBit(LCD_EXYNOS_PORT, LCD_EXYNOS, Bit_RESET);
	    GPIO_WriteBit(LCD_STM32_PORT , LCD_STM32 , Bit_SET);
	}
	else
	{
	    GPIO_WriteBit(LCD_STM32_PORT , LCD_STM32 , Bit_RESET);
	    GPIO_WriteBit(LCD_EXYNOS_PORT, LCD_EXYNOS, Bit_SET);
	}
}

/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void LCD_CONTROL_Init(void)
{
	LCDBL_ONOFF(LCDBL_ON);	//  PWM을 설정한 후에 -> BackLight On을 한다. 	
	LCDBL_Init();
	LCD_Display_Change(STM32F4_DISPLAY);
//	LCD_Display_Change(EXYNOS_DISPLAY);
		
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
