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
//	나중에 지울 것. .
#if 0
	unsigned int i;
	
	for (i= 9;  i !=0; i--)
	{
		Led_SIG_TEMP[i]	= Led_SIG_TEMP[i -1];
		Led_BL_TEMP[i] 	= Led_BL_TEMP[i -1];
	}

	Illumination_LampSystem();

	Led_SIG_TEMP[0]  = 0;
	
	Digital_InputSystem();
	Led_SIG_TEMP[0] += (Mirror_Heater_flag)?(L_Mirror_heater_Status):(0x00);
	Led_SIG_TEMP[0] += (Front_rear_flag)?(L_Front_rear_Status):(0x00);
	Led_SIG_TEMP[0] += (Highbeam_flag)?(L_HighBeam_Status):(0x00);

	Led_SIG_TEMP[0] += (Joystick_Steering_Active_LampSystem())?(L_Joystick_Steering_Active_Status):(0x00);
	Led_SIG_TEMP[0] += (Engine_Cooling_Fan_Reverse_LampSystem())?(L_Engine_Cooling_Fan_Reverse_Status):(0x00);
	Led_SIG_TEMP[0] += (Engine_Preheat_LampSystem())?(L_Engine_Preheat_Status):(0x00);
	Led_SIG_TEMP[0] += (Error_LampSystem())?(L_Error_Status):(0x00);
	Led_SIG_TEMP[0] += (Steering_Main_Pump_Pressure_Low_LampSystem())?(L_Steering_Main_Pump_Pressure_Low_Status):(0x00);
	Led_SIG_TEMP[0] += (Battery_Voltage_Low_LampSystem())?(L_Battery_Voltage_Low_Status):(0x00);
	Led_SIG_TEMP[0] += (Hydraulic_Oil_Temperature_High_LampSystem())?(L_Hydraulic_Oil_Temperature_High_Status):(0x00);
	Led_SIG_TEMP[0] += (Emergency_Steering_Active_LampSystem())?(L_Emergency_Steering_Active_Status):(0x00);
	Led_SIG_TEMP[0] += (Transmission_Check_LampSystem())?(L_Transmission_Check_Status):(0x00);
	Led_SIG_TEMP[0] += (Engine_Coolant_Temperature_High_LampSystem())?(L_Engine_Coolant_Temperature_High_Status):(0x00);
	Led_SIG_TEMP[0] += (Transmission_Oil_Temperature_High_LampSystem())?(L_Transmission_Oil_Temperature_High_Status):(0x00);
	Led_SIG_TEMP[0] += (Seat_belt_LampSystem())?(L_Seat_Beat_Status):(0x00);
	Led_SIG_TEMP[0] += (Brake_Oil_Pressure_Low_LampSystem())?(L_Brake_Oil_Pressure_Low_Status):(0x00);
	Led_SIG_TEMP[0] += (Engine_Oil_Pressure_Low_LampSystem())?(L_Engine_Oil_Pressure_Low_Status):(0x00);
	Led_SIG_TEMP[0] += (Parking_LampSystem())?(L_Parking_Status):(0x00);
	Led_SIG_TEMP[0] += (Fuel_Level_Low_LampSystem())?(L_Fuel_Level_Low_Status):(0x00);	
	Led_SIG_TEMP[0] += (Air_Cleaner_Clog_LampSystem())?(L_Air_Cleaner_Clog_Status):(0x00);
	Led_SIG_TEMP[0] += (Clutch_Cutoff_LampSystem())?(L_Clutch_Cutoff_Status):(0x00);
	Led_SIG_TEMP[0] += (Differential_Lock_LampSystem())?(L_Differential_Lock_Status):(0x00);
	Ride_Control_LampSystem();
	Led_SIG_TEMP[0] += (Ride_Control_flag)?(L_Ride_Control_Status):(0x00);
	Led_SIG_TEMP[0] += (AutoRide_Control_flag)?(L_AutoRide_Control_Status):(0x00);
	Maintenance_Alarm_LampSystem();
	Led_SIG_TEMP[0] += (Maintenance_Alarm_flag)?(L_Maintenance_Alarm_Status):(0x00);
	Led_SIG_TEMP[0] += (Warming_Up_LampSystem())?(L_Warming_Up_Status):(0x00);

//09.11.10 -->fuel_warmer add
	Led_SIG_TEMP[0] += (Fuel_Warmer_LampSystem())?(L_Fuel_Warmer_Status):(0x00);

	
		
	Speed_Unit_LampSystem();
	Led_SIG_TEMP[0] += (KM_flag)?(L_KM_Status):(0x00);
	Led_SIG_TEMP[0] += (MPH_flag)?(L_MP_Status):(0x00);

	if((Led_SIG_TEMP[9] == Led_SIG_TEMP[8]) && (Led_SIG_TEMP[8] == Led_SIG_TEMP[1]) && (Led_SIG_TEMP[1] == Led_SIG_TEMP[0])) 
	{
		Symbol_state = Led_SIG_TEMP[0];
	}

	Led_BL_TEMP[0] = Illumination_flag;

	if((Led_BL_TEMP[9] == Led_BL_TEMP[8]) && (Led_BL_TEMP[8] == Led_BL_TEMP[1]) && (Led_BL_TEMP[1] == Led_BL_TEMP[0]))  
	{		
		Illumination_Sig = Led_BL_TEMP[0];
	}

	Lamp_save();
#endif
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

    DebugMsg_printf("-- LAMP Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
