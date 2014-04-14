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
st_CANDATA_HCEPGN_65428	RX_HCEPGN_65428;
Realy_Control		rx_Realy_Control;
EHCU_Status		rx_EHCU_Status;
Auto_position_Status rx_Auto_position_Status;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 Lamp_name;
u8 Lamp_Value;

unsigned char Ride_Control_flag;
unsigned char AutoRide_Control_flag;

unsigned char Attachment_Unlock_flag;
unsigned char Attachment_Lock_flag;

unsigned char Auto_Grease_Green_flag;
unsigned char Auto_Grease_Red_flag;

unsigned int Led_SIG_TEMP[10];
unsigned int Led_BL_TEMP[10];

unsigned char Illumination_Sig;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//------------------------------------------------------------------------------
// Function Name 	: Work_Light_left_LampSystem
// Description 	: Work_Light_left_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
// rx_Realy_Control.work_lamp_Status 3435
// rx_Realy_Control.rear_work_Status 3446
//------------------------------------------------------------------------------
unsigned char Work_Light_left_LampSystem(void)
{
	unsigned char work_Light_Lamp_flag;

	if(rx_Realy_Control.Work_Lamp_Status < 0x03)
	{
		if(rx_Realy_Control.Work_Lamp_Status == 0) 
			work_Light_Lamp_flag =0;
		else if(rx_Realy_Control.Work_Lamp_Status == 1)
			work_Light_Lamp_flag =1;
		else
			work_Light_Lamp_flag =0;
	}
	else 
		work_Light_Lamp_flag = 0;

	return work_Light_Lamp_flag;
}
//------------------------------------------------------------------------------
// Function Name 	: Work_Light_right_LampSystem
// Description 	: Work_Light_right_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
// rx_Realy_Control.work_lamp_Status 3435
// rx_Realy_Control.rear_work_Status 3446
//------------------------------------------------------------------------------
unsigned char Work_Light_right_LampSystem(void)
{
	unsigned char work_Light_Lamp_flag;

	if((rx_Realy_Control.Work_Lamp_Status < 0x03) && (rx_Realy_Control.Rear_Work_lamp_Status < 0x03)) 
	{
		if((rx_Realy_Control.Work_Lamp_Status == 0) && (rx_Realy_Control.Rear_Work_lamp_Status == 0)) 
			work_Light_Lamp_flag =0;
		else if((rx_Realy_Control.Work_Lamp_Status == 1) && (rx_Realy_Control.Rear_Work_lamp_Status == 1))
			work_Light_Lamp_flag =1;
		else
			work_Light_Lamp_flag =0;
	}
	else 
		work_Light_Lamp_flag = 0;

	return work_Light_Lamp_flag;
}
//------------------------------------------------------------------------------
// Function Name 	: Main_Light_LampSystem
// Description 	: Main_Light_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
// rx_Realy_Control.Head_lamp_Status 3436
// rx_Realy_Control.Illumination_Status 3438
//------------------------------------------------------------------------------
unsigned char Main_Light_left_LampSystem(void)
{
	unsigned char Main_Light_Lamp_flag;

	if((rx_Realy_Control.Head_lamp_Status < 0x03) && (rx_Realy_Control.Illumination_Status < 0x03)) 
	{
		if((rx_Realy_Control.Head_lamp_Status == 0) && (rx_Realy_Control.Illumination_Status == 0)) 
			Main_Light_Lamp_flag =0;
		else if(rx_Realy_Control.Illumination_Status == 1)
			Main_Light_Lamp_flag =1;
		else
			Main_Light_Lamp_flag =0;
	}
	else 
		Main_Light_Lamp_flag = 0;

	return Main_Light_Lamp_flag;
}

//------------------------------------------------------------------------------
// Function Name 	: Main_Light_LampSystem
// Description 	: Main_Light_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
// rx_Realy_Control.Head_lamp_Status 3436
// rx_Realy_Control.Illumination_Status 3438
//------------------------------------------------------------------------------
unsigned char Main_Light_Right_LampSystem(void)
{
	unsigned char Main_Light_Lamp_flag;

	if((rx_Realy_Control.Head_lamp_Status < 0x03) && (rx_Realy_Control.Illumination_Status < 0x03)) 
	{
		if((rx_Realy_Control.Head_lamp_Status == 0) && (rx_Realy_Control.Illumination_Status == 0)) 
			Main_Light_Lamp_flag =0;
		else if(rx_Realy_Control.Illumination_Status == 1)
			Main_Light_Lamp_flag = ((rx_Realy_Control.Head_lamp_Status == 0x01) ? 0x01 : 0x00);
		else
			Main_Light_Lamp_flag =0;
	}
	else 
		Main_Light_Lamp_flag = 0;

	return Main_Light_Lamp_flag;
}


//------------------------------------------------------------------------------
// Function Name 	: Fine_Modulation_LampSystem
// Description 	: Fine_Modulation_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Fine_Modulation_LampSystem(void)
{
	unsigned char Fine_Modulation_Lamp_flag;

	if(rx_EHCU_Status.Fine_Modulation < 0x03) 	
		Fine_Modulation_Lamp_flag = 	((rx_EHCU_Status.Fine_Modulation == 0x01) ? 0x01 : 0x00);
	else 
		Fine_Modulation_Lamp_flag = 0;

	return Fine_Modulation_Lamp_flag;
}

//------------------------------------------------------------------------------
// Function Name 	: Beacon_LampSystem
// Description 	: Beacon_LampSystem  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Beacon_LampSystem(void)
{
	unsigned char Beacon_Lamp_flag;

	if(rx_Realy_Control.beacon < 0x03) 	
		Beacon_Lamp_flag = 	((rx_Realy_Control.beacon == 0x01) ? 0x01 : 0x00);
	else 
		Beacon_Lamp_flag = 0;

	return Beacon_Lamp_flag;
}

//------------------------------------------------------------------------------
// Function Name 	: Mirror_heat_LampSystem
// Description 	: Mirror_heat_Lamp  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Mirror_heat_LampSystem(void)
{
	unsigned char Mirror_heat_flag;

	if(RX_HCEPGN_65428.Mirror_Heater_Status < 0x03) 	
		Mirror_heat_flag = 	((RX_HCEPGN_65428.Mirror_Heater_Status == 0x01) ? 0x01 : 0x00);
	else 
		Mirror_heat_flag = 0;

	return Mirror_heat_flag;
}

//------------------------------------------------------------------------------
// Function Name 	: Mirror_heat_LampSystem
// Description 	: Mirror_heat_Lamp  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Rear_Wiper_LampSystem(void)
{
	unsigned char rear_wiper_flag;

	if(rx_Realy_Control.Rear_Wiper < 0x03) 	
		rear_wiper_flag = 	((rx_Realy_Control.Rear_Wiper == 0x00) ? 0x00 : 0x01);
	else 
		rear_wiper_flag = 0;

	return rear_wiper_flag;
}
//------------------------------------------------------------------------------
// Function Name 	: Ride_Control_LampSystem
// Description 	: Ride_Control_Lamp 동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
void Ride_Control_LampSystem(void)
{
	if(rx_Realy_Control.Ride_Control < 0x03)
	{
		if(rx_Realy_Control.Ride_Control == 0)
		{
			Ride_Control_flag = 0;
			AutoRide_Control_flag = 0;
		}
		else if(rx_Realy_Control.Ride_Control == 1)
		{
			Ride_Control_flag = 1;
			AutoRide_Control_flag = 0;
		}
		else if(rx_Realy_Control.Ride_Control == 2)
		{
			Ride_Control_flag = 0;
			AutoRide_Control_flag = 1;
		}
	}
	else
	{
		Ride_Control_flag = 0;
		AutoRide_Control_flag = 0;
	}
}

//------------------------------------------------------------------------------
// Function Name 	: Quick_Coupler_LampSystem
// Description 	: Quick_Coupler_Lamp 동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
void Quick_Coupler_LampSystem(void)
{
	if(rx_Realy_Control.Quick_Coupler < 0x03)
	{
		if(rx_Realy_Control.Quick_Coupler == 0)
		{
			Attachment_Unlock_flag = 1;
			Attachment_Lock_flag = 0;
		}
		else if(rx_Realy_Control.Quick_Coupler == 1)
		{
			Attachment_Unlock_flag = 0;
			Attachment_Lock_flag = 1;
		}
		else
		{
			Attachment_Unlock_flag = 0;
			Attachment_Lock_flag = 0;
		}
	}
	else
	{
		Attachment_Unlock_flag = 0;
		Attachment_Lock_flag = 0;
	}
}

//------------------------------------------------------------------------------
// Function Name 	: Boom_Detent_LampSystem
// Description 	: Boom_Detent_LampSystem 동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Boom_Detent_LampSystem(void)
{
	unsigned char Boom_Detent_flag;

	if(rx_Auto_position_Status.Boom_Detent_Mode < 0x07) 	
	{
		if(rx_Auto_position_Status.Boom_Detent_Mode > 0 && rx_Auto_position_Status.Boom_Detent_Mode < 4)
			Boom_Detent_flag = 1;
		else
			Boom_Detent_flag = 0;
	}		
	else 
		Boom_Detent_flag = 0;

	return Boom_Detent_flag;
}

//------------------------------------------------------------------------------
// Function Name 	: Bucket_Detent_LampSystem
// Description 	: Bomm_Detent_LampSystem 동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Bucket_Detent_LampSystem(void)
{
	unsigned char Bucket_Detent_flag;

	if(rx_Auto_position_Status.Bucket_Detent_Mode < 0x07) 	
	{
		if(rx_Auto_position_Status.Bucket_Detent_Mode > 0 && rx_Auto_position_Status.Bucket_Detent_Mode < 4)
			Bucket_Detent_flag = 1;
		else
			Bucket_Detent_flag = 0;
	}		
	else 
		Bucket_Detent_flag = 0;

	return Bucket_Detent_flag;
}


//------------------------------------------------------------------------------
// Function Name 	: Auto_Grease_LampSystem
// Description 	: Auto_Grease_Lamp 동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
void Auto_Grease_LampSystem(void)
{

	if(RX_HCEPGN_65428.AutoGrease_Green_LED < 0x03)
	{
		if(RX_HCEPGN_65428.AutoGrease_Green_LED == 0x01)
		{
			Auto_Grease_Green_flag = 1;
		}
		else
		{
			Auto_Grease_Green_flag = 0;
		}
	}

	if(RX_HCEPGN_65428.AutoGrease_Red_LED < 0x03)
	{
		if(RX_HCEPGN_65428.AutoGrease_Red_LED == 0x01)
		{
			Auto_Grease_Red_flag = 1;
		}
		else
		{
			Auto_Grease_Red_flag = 0;
		}
	}


}

//------------------------------------------------------------------------------
// Function Name 	: Illumination_LampSystem
// Description 	: Illumination_LampSystem Lamp  동작에 조건 판단.
// Input 			: None
// Return 		: None
// Period 		: 10ms
//------------------------------------------------------------------------------
unsigned char Illumination_Lamp_System(void)
{
	unsigned char Illumination_falg;

	if(rx_Realy_Control.Illumination_Status < 0x03)
	{
		if(rx_Realy_Control.Illumination_Status == 1)
			Illumination_falg =1;
		else
			Illumination_falg =0;
	}
	else 
		Illumination_falg = 0;

	return Illumination_falg;
}

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

	if(Illumination_Sig)	LAMP_Update_Data |= 0x700000;
	
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
	unsigned int i;
	
	for (i= 9;  i !=0; i--)
	{
		Led_SIG_TEMP[i] 		= Led_SIG_TEMP[i -1];
		Led_BL_TEMP[i] 		= Led_BL_TEMP[i -1];
	}

	Led_SIG_TEMP[0]  = 0;

	Led_SIG_TEMP[0] += (Main_Light_left_LampSystem())?(Main_Light_1_G):(0x00);
	Led_SIG_TEMP[0] += (Main_Light_Right_LampSystem())?(Main_Light_2_B):(0x00);

	Led_SIG_TEMP[0] += (Work_Light_left_LampSystem())?(Work_Light_G1):(0x00);
	Led_SIG_TEMP[0] += (Work_Light_right_LampSystem())?(Work_Light_G2):(0x00);
	
	Auto_Grease_LampSystem();
	Led_SIG_TEMP[0] += (Auto_Grease_Green_flag)?(Auto_Grease_1_G):(0x00);
	Led_SIG_TEMP[0] += (Auto_Grease_Red_flag)?(Auto_Grease_2_R):(0x00);
	
	Quick_Coupler_LampSystem();
	Led_SIG_TEMP[0] += (Attachment_Lock_flag)?(Quick_coupler_1_G):(0x00);
	Led_SIG_TEMP[0] += (Attachment_Unlock_flag)?(Quick_coupler_2_R):(0x00);

	
	Ride_Control_LampSystem();
	Led_SIG_TEMP[0] += (Ride_Control_flag)?(Ride_Control_1_G):(0x00);
	Led_SIG_TEMP[0] += (AutoRide_Control_flag)?(Ride_Control_2_B):(0x00);

	
	Led_SIG_TEMP[0] += (Beacon_LampSystem())?(Beacon_lamp_G):(0x00);

	Led_SIG_TEMP[0] += (Rear_Wiper_LampSystem())?(Rear_Wiper_G):(0x00);
	
	Led_SIG_TEMP[0] += (Mirror_heat_LampSystem())?(Mirror_Heat_1_G):(0x00);
	Led_SIG_TEMP[0] += (Fine_Modulation_LampSystem())?(Fine_Modulation_G):(0x00);


	Led_SIG_TEMP[0] += (Boom_Detent_LampSystem())?(Auto_Position_1_G):(0x00);
	Led_SIG_TEMP[0] += (Bucket_Detent_LampSystem())?(Auto_Position_2_G):(0x00);

	Led_BL_TEMP[0] = Illumination_Lamp_System();

	if((Led_SIG_TEMP[9] == Led_SIG_TEMP[8]) && (Led_SIG_TEMP[8] == Led_SIG_TEMP[1]) && (Led_SIG_TEMP[1] == Led_SIG_TEMP[0])) 
	{
		LAMP_Update_Data = Led_SIG_TEMP[0];
	}
	if((Led_BL_TEMP[9] == Led_BL_TEMP[8]) && (Led_BL_TEMP[8] == Led_BL_TEMP[1]) && (Led_BL_TEMP[1] == Led_BL_TEMP[0]))  
	{		
		Illumination_Sig = Led_BL_TEMP[0];
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
