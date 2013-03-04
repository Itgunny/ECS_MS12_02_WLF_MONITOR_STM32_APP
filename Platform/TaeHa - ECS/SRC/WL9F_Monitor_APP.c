/**
  ******************************************************************************
  * @file    WL9F_Monitor_APP.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   WL9F_Monitor_APP.c module
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
#include "main.h"
#include "WL9F_Display_Common.h"	
#include "WL9F_Display_Variable.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  1msec OperationFunc
  * @param  None
  * @retval None
  */
void WL9F_1mSecOperationFunc(void)
{

}

/**
  * @brief  10msec OperationFunc
  * @param  None
  * @retval None
  */
  uint8_t Test;
void WL9F_10mSecOperationFunc(void)
{

}

/**
  * @brief  100msec OperationFunc
  * @param  None
  * @retval None
  */
void WL9F_100mSecOperationFunc(void)
{

}

/**
  * @brief  1sec OperationFunc
  * @param  None
  * @retval None
  */
void WL9F_1SecOperationFunc(void)
{

}

/**
  * @brief  Application Program Start Point.
  * @param  None
  * @retval None
  */
void WL9F_Monitor_APP(void)
{
	DebugUART_Init();			//	->	Main.c
	//DebugMsg_printf("** DEBUG_MSG_LEVEL1 Defined..\r\n");

	System_Configuration();		//  ->  System_Init.c
	                            //      RCC, NVIC, GPIO Initialize

	System_Initialize();		//	-> 	System_Init.c
								//		IAP와 동일한 초기화를 한다. -> 상태 변경 없음.
	
//	System 강제 RESET시키기 위하여 goto lable 추가..
SYSTEM_RESET :

	System_Variable_Init();
	WL9F_System_Init_Start();
	
	/* Infinite loop */
	while (1)
	{  
		if (WL9F_TIME_DATA.Flag_1mSec == 1)     //  1msec
		{
			WL9F_TIME_DATA.Flag_1mSec = 0;

			//  WL9F_1mSecOperationState -> Func 실행..
			//  if (WL9F_1mSecOperationState != 0) WL9F_1mSecOperationFunc[WL9F_1mSecOperationState]();    
			WL9F_1mSecOperationFunc();
		}            
		
		if (WL9F_TIME_DATA.Flag_10mSec == 1)    //  10msec
		{
			WL9F_TIME_DATA.Flag_10mSec = 0;

			//  WL9F_10mSecOperationState -> Func 실행..
			//  if (WL9F_10mSecOperationState != 0) WL9F_10mSecOperationFunc[WL9F_10mSecOperationState]();    
			WL9F_10mSecOperationFunc();
		}
		
		if (WL9F_TIME_DATA.Flag_100mSec == 1)   //  100 msec
		{
			WL9F_TIME_DATA.Flag_100mSec = 0;

			//  WL9F_100mSecOperationState -> Func 실행..
			//  if (WL9F_100mSecOperationState != 0) WL9F_100mSecOperationFunc[WL9F_100mSecOperationState]();    
			WL9F_100mSecOperationFunc();

			#if 0
			//	WL9F Monitor RESET Code
			if((SystemReset == 1) || (gRebootCmd == 1))
			{
				goto SYSTEM_RESET;
			}
			#endif
		}
		
		if (WL9F_TIME_DATA.Flag_1Sec == 1)      //  1000 msec
		{
			WL9F_TIME_DATA.Flag_1Sec = 0;

			//  WL9F_1SecOperationState -> Func 실행..
			//  if (WL9F_1SecOperationState != 0) WL9F_1SecOperationFunc[WL9F_1SecOperationState]();    
			WL9F_1SecOperationFunc();
		}
	}
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
