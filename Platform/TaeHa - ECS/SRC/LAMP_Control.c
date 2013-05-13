/**
  ******************************************************************************
  * @file    LAMP_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   LAMP_Control.c module
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
u8 Lamp_name;
u8 Lamp_Value;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//------------------------------------------------------------------------------
// Function Name	: Lamp_Update_System
// Description 		: Lamp 제어
// Input 			: Symbol_state
// Return 			: None
// Period 			: 초기화시 , 100ms
//------------------------------------------------------------------------------
 void Lamp_Update_System(void)
{
	unsigned long temp;
	unsigned short i;

	// SIG
	temp = 0x400000;

	for ( i = 0 ; i < 23 ; i++)
	{  
		if ( LAMP_Update_Data & temp )
			C_LAMP_SDATA_HIGH();
		else	
			C_LAMP_SDATA_LOW();

		C_LAMP_SCLK_HIGH();		
		TimeDelay_msec(1);
		C_LAMP_SCLK_LOW();

		temp = temp >> 1;
	}

	C_LAMP_SLCLK_HIGH();	
	TimeDelay_msec(1);
	C_LAMP_SLCLK_LOW();		
	TimeDelay_msec(1);
	C_LAMP_SLCLK_HIGH();
}


//	10msec 마다 실행해야된다.
void Lamp_Update_State(void)
{
	switch(Lamp_name)
	{
		case CMD_Ride_Control_Lamp :
			LAMP_Update_Data &=~(Ride_Control_Lamp_Off);
			if(Lamp_Value==1)		LAMP_Update_Data |=Ride_Control_Manual_Lamp;
			else if(Lamp_Value==2)	LAMP_Update_Data |=Ride_Control_Auto_Lamp;
			break;
		case CMD_Quick_Coupler_Lamp :
			LAMP_Update_Data &=~(Quick_Coupler_Lamp_Off);
			if(Lamp_Value==1)		LAMP_Update_Data |=Quick_Coupler_Lock_Lamp;
			else if(Lamp_Value==2)	LAMP_Update_Data |=Quick_Coupler_UnLock_Lamp;
			break;
		case CMD_Auto_Grease_Lamp :
			LAMP_Update_Data &=~(Auto_Grease_Lamp_Off);
			if(Lamp_Value==1)		LAMP_Update_Data |=Auto_Grease_Manual_Lamp;
			else if(Lamp_Value==2)	LAMP_Update_Data |=Auto_Grease_Auto_Lamp;
			break;
		case CMD_Beacon_Lamp :
			if(Lamp_Value==0)		LAMP_Update_Data &=~(Beacon_Lamp);
			else if(Lamp_Value==1)	LAMP_Update_Data |=Beacon_Lamp;
			break;
		case CMD_Mirror_Heat_Lamp :
			if(Lamp_Value==0)		LAMP_Update_Data &=~(Mirror_Heat_Lamp);
			else if(Lamp_Value==1)	LAMP_Update_Data |=Mirror_Heat_Lamp;
			break;
		case CMD_Rear_Wiper_Lamp :
			if(Lamp_Value==0)		LAMP_Update_Data &=~(Rear_Wiper_Lamp);
			else if(Lamp_Value==1)	LAMP_Update_Data |=Rear_Wiper_Lamp;
			break;
	}
}

/**
  * @brief  LAMP Initialize 
  * @param  
  * @retval None
  */
void LAMP_Control_Init(void)
{
	DebugMsg_printf("++ LAMP Initialize START\r\n");

	//  LAMP GPIO는 System_Init.c 에서 설정
#if 0
	GPIO_InitStructure.GPIO_Pin   = LAMP_CLR | LAMP_SLCLK | LAMP_SCLK | LAMP_SDATA;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LAMP_PORT, &GPIO_InitStructure);
#endif

	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_SET);
	TimeDelay_msec(10);
	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_RESET);

	LAMP_Update_Data = LAMP_ALL_ON;

	Lamp_Update_System();

	DebugMsg_printf("-- LAMP Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
