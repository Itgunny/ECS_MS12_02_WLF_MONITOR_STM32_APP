/**
  ******************************************************************************
  * @file    LAMP_Control.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for LAMP_Control.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LAMP_Control_H
#define __LAMP_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define 	LAMPCMD			0x08
#define 	LAMPRES			0x88



#define 	C_LAMP_SCLK_HIGH()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_SET)
#define 	C_LAMP_SCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SCLK, Bit_RESET)

#define 	C_LAMP_SLCLK_HIGH()     GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_SET)
#define 	C_LAMP_SLCLK_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SLCLK, Bit_RESET)

#define 	C_LAMP_SDATA_HIGH()    	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_SET)
#define 	C_LAMP_SDATA_LOW()     	GPIO_WriteBit(LAMP_PORT, LAMP_SDATA, Bit_RESET)

#define 	C_LAMP_CLR_ENABLE()    	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_SET)
#define 	C_LAMP_CLR_DISABLE() 	GPIO_WriteBit(LAMP_PORT, LAMP_CLR, Bit_RESET)

/////////////// Keypad RevA04.01///////////////////////////
/*
#define 	Main_Light_1_G 					0x00000001
#define 	Main_Light_2_B 					0x00000002
#define 	Work_Light_G1 					0x00000004
#define 	Work_Light_G2 					0x00000008

#define 	Auto_Grease_1_G 				0x00000010
#define 	Auto_Grease_2_R 				0x00000020
#define 	Quick_coupler_1_G 				0x00000040
#define 	Quick_coupler_2_R 				0x00000080

#define 	Ride_Control_1_G 				0x00000100
#define 	Ride_Control_2_B 				0x00000200
#define 	Work_load_1_G 					0x00000400
#define 	Work_load_2_B 					0x00000800

#define 	Beacon_lamp_G 					0x00001000
#define 	Rear_Wiper_G 					0x00002000
#define 	Mirror_Heat_1_G 				0x00004000
#define 	Mirror_Heat_2_B 				0x00008000

#define 	Auto_Position_1_G				0x00010000
#define 	Auto_Position_2_G				0x00020000
#define 	Fine_Modulation_G				0x00040000
#define 	Function_G						0x00080000
*/
///////////////////////////////////////////////////////////
/////////////// Keypad RevA06.01///////////////////////////


#define 	Main_Light_1_G 					0x00000001
#define 	Main_Light_2_B 					0x00000002
#define 	Work_Light_G1 					0x00000004
#define 	Work_Light_G2 					0x00000008
	
#define 	Auto_Grease_1_G 				0x00000010
#define 	Auto_Grease_2_R 				0x00000020
#define 	Quick_coupler_1_G 				0x00000040
#define 	Quick_coupler_2_R 				0x00000080
	
#define 	Ride_Control_1_G 				0x00000100
#define 	Ride_Control_2_B 				0x00000200
#define 	Work_load_1_G 					0x00000400
#define 	Work_load_2_B 					0x00000800
	
#define 	Beacon_lamp_G 					0x00001000
#define 	Rear_Wiper_G 					0x00002000
#define 	Mirror_Heat_1_G 				0x00004000
#define 	Auto_Position_1_G				0x00008000

#define 	Auto_Position_2_G				0x00010000
#define 	Fine_Modulation_G				0x00020000
#define 	Function_G					0x00040000

///////////////////////////////////////////////////////////

#define	BGLED0							0x00100000
#define	BGLED1							0x00200000
#define	BGLED2							0x00400000



#define 	LAMP_ALL_ON 					0x00ffffff
#define 	LAMP_ALL_OFF 					0x00000000


#pragma pack(1)
typedef struct
{	
	unsigned char	MainLight1:2;
	unsigned char	MainLight2:2;
	unsigned char	WorkLight1:2;
	unsigned char	WorkLight2:2;

	unsigned char	AutoGrease1:2;
	unsigned char	AutoGrease2:2;
	unsigned char	QuickCoupler1:2;
	unsigned char	QuickCoupler2:2;

	unsigned char	RideControl1:2;
	unsigned char	RideControl2:2;
	unsigned char	WorkLoad1:2;
	unsigned char	WorkLoad2:2;

	unsigned char	BeaconLamp:2;
	unsigned char	RearWiper:2;
	unsigned char	MirrorHeat:2;
	unsigned char	AutoPosition1:2;
	
	unsigned char	AutoPosition2:2;
	unsigned char	FineModulation:2;
	unsigned char	FN:2;
	unsigned char	Illumination:2;


	unsigned char	DM[3];
}CMD_LAMP;

#pragma pack()



#pragma pack(1)
typedef struct
{	
	unsigned char Power_Max_Status:2; 					//HCESPN 802
	unsigned char Deceleration_Status:2; 					//HCESPN 803
	unsigned char Warming_Up_Status:2; 					//HCESPN 804
	unsigned char Engine_Preheat_Status:2;				//HCESPN 323

	unsigned char Fuel_Warmer_Active_Status:2; 			//HCESPN 326
	unsigned char Cooling_Fan_Driving_Status:2;			//HCESPN 180
	unsigned char Cruise_Status:2;							//HCESPN 519
	unsigned char Parking_Status:2; 						//HCESPN 508

	
	unsigned char Clutch_Cutoff_Status:2; 					//HCESPN 545
	unsigned char FNR_Joystick_Active_Status:2;			//HCESPN 546
	unsigned char Ride_Control_Status:2; 					//HCESPN 550
	unsigned char Differential_Lock_Status:2;				//HCESPN 559

	
	unsigned char Joystick_Steering_Active_Status:2; 		//HCESPN 186
	unsigned char Inching_Status:2; 						//HCESPN 549
	unsigned char Ram_Lock_Status:2; 						//HCESPN 520
	unsigned char Working_Brake_Status:2; 				//HCESPN 506

	unsigned char Maintenance_Alarm_Lamp:2;				//HCESPN 1099
	unsigned char Operator_Absence_Status:2;                        //HCESPN 832
	unsigned char Mirror_Heater_Status:2; 					//HCESPN 724
	unsigned char High_Beam_Status:2; 					//HCESPN 725

	
	unsigned char Travel_Alarm_Switch:2; 					//HCESPN 721
	unsigned char Swing_Boom_Switch:2;					//HCESPN 726		
	unsigned char Parking_Working_Travel_Status:2;		//HCESPN 510
	unsigned char Transmission_Torque_Converter:2; 		//HCESPN 556

	
	unsigned char Exhaust_System_High_temp:2; 			//HCESPN 353
	unsigned char DM1:2; 									
	unsigned char DM2:2; 			
	unsigned char DPF_Regeneration_Inhibit:2; 				//HCESPN 354

	
	unsigned char Automatic_Engine_Shutdown:2;				// HCESPN 363
	unsigned char Delayed_Engine_Shutdown:2;				// HCESPN 365
	unsigned char AutoGrease_Green_LED:2;					// HCESPN 3453
	unsigned char AutoGrease_Red_LED:2;						// HCESPN 3454
}st_CANDATA_HCEPGN_65428;

#pragma pack()

#pragma pack(1)
typedef struct 
{	
	unsigned char Reserved1;

	unsigned char Work_Lamp_Status:2; 	// HCESPN 3435
	unsigned char Head_lamp_Status:2;      // HCESPN 3436
	unsigned char DM0:2;
	unsigned char Illumination_Status:2;     // HCESPN 3438
	
	unsigned char Reserved2;

	unsigned char DM1:2; 
	unsigned char beacon:2; 				//HCESPN 3444
	unsigned char DM2:2; 
	unsigned char Rear_Work_lamp_Status:2;   // HCESPN 3446

	unsigned char Ride_Control:2;				//HCESPN 3447
	unsigned char Quick_Coupler:2;                       //HCESPN 3448
	unsigned char Auto_Grease:2; 				//HCESPN 3449
	unsigned char Mirror_Heat:2; 				//HCESPN 3450

	unsigned char Rear_Wiper:2; 				//HCESPN 3451
	unsigned char Rear_Wiper_Washer:2;		//HCESPN 3452	
	unsigned char DM3:4;	//HCESPN 510

	unsigned char Reserved3;
	
	unsigned char Ride_Control_Speed;					//HCESPN 3460
}Realy_Control;
#pragma pack()


#pragma pack(1)
typedef struct 
{	
	unsigned char Reserved1:2;
	unsigned char Fine_Modulation:2; // 2302 
	unsigned char Reserved2:4;
	
	unsigned char Reserved3;

	
	unsigned short Reserved4;
	
	unsigned short Reserved5;
	
	unsigned short Reserved6;
}EHCU_Status;
#pragma pack()

#pragma pack(1)
typedef struct 
{	
	unsigned char MessageType;
	
	unsigned char Boom_Detent_Mode:3;
	unsigned char Bucket_Detent_Mode:3;
	unsigned char Reserved2:2;
	
	unsigned char Reserved3; 
	
	
	unsigned short Reserved4;
	
	unsigned short Reserved5;
	
	unsigned char Reserved6;
	
}Auto_position_Status;

#pragma pack(1)
typedef struct 
{	
	unsigned char	WeighingSystemOperationMode1StatusJ_1901:2;
	unsigned char	WeighingSystemBuzzer_1907:2;
	unsigned char	WeightAccumulationMode:2;
	unsigned char	Reserved0:2;

	unsigned char	CurrentWeighingResult_1919:4;
	unsigned char	SuddenChangeError:2;
	unsigned char	BucketFullInError:2;

	unsigned short	CurrentWeight_1911;

	unsigned int	TodayWeight_1915;

	
}WEIGHING_SYSTEM_STATUS_65450;

#pragma pack()

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint32_t LAMP_Update_Data;
extern uint32_t Old_LAMP_Update_Data;
/* Exported functions ------------------------------------------------------- */
extern void Lamp_Update_State(void);
extern void Lamp_Update_System(void);
extern void LAMP_Control_Init(void);

#endif /* __LAMP_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
