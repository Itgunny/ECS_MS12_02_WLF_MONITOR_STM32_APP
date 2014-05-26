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
#include "WL9F_Display_APP.h"	
#include "WL9F_Display_Variable.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Init_RTC(void)
{
    WL9FM_RTC.Year   = 0;
	WL9FM_RTC.Month  = 1;
	WL9FM_RTC.Date   = 1;
	WL9FM_RTC.Day    = 1;
	WL9FM_RTC.Hour   = 12;
	WL9FM_RTC.Minute = 0;
	WL9FM_RTC.Second = 0;

	WRITE_RTC(WL9FM_RTC);
}
void InitE2PROM(void)
{
	u8 i;
	u8 tmpBuf1[8];
	u8 tmpBuf2[8];
	u8 tmpBuf3[8];
	u8 tmpBuf4[21];
	
	SaveE2PROM1 = (WL9FM_SaveE2PROM1*)&tmpBuf1[0];
	SaveE2PROM2 = (WL9FM_SaveE2PROM2*)&tmpBuf2[0];
	SaveE2PROM3 = (WL9FM_SaveE2PROM3*)&tmpBuf3[0];
	SaveE2PROMoniInfo = (WL9FM_SaveE2PROMoniInfo*)&tmpBuf4[0];

	SaveE2PROM1->WorkLoad 				= 0;
	SaveE2PROM1->testWorkLoad 			= 0;
	SaveE2PROM1->Unit 					= 3;	//	섭씨 ( C ) , km/h
	SaveE2PROM1->DispType	 			= 0;
	SaveE2PROM1->InfoViewPriority 		= 0;
	SaveE2PROM1->UnitPressure 			= 0;
	SaveE2PROM1->Reserved0 				= 0;
	SaveE2PROM1->Lang 					= 0;
	SaveE2PROM1->ManualBackLight 		= 7;
	SaveE2PROM1->AutoBackLight 			= 0;
	SaveE2PROM1->TopInfoView 			= 1;	// 	Hyd Temp
	SaveE2PROM1->BottomInfoView 		= 3;	// 	Cool Temp
	SaveE2PROM1->InfoViewCnt 			= 2;
	SaveE2PROM1->HR_Start 				= 0;
	SaveE2PROM1->RearCamReverseMode 	= 0;	// 	Off
	SaveE2PROM1->ActiveCamNum 			= 1;
	SaveE2PROM1->FirstCam 				= 0;
	SaveE2PROM1->SecondCam 				= 1;
	SaveE2PROM1->ThirdCam 				= 2;
	SaveE2PROM1->Reserved1 				= 0;

	SaveE2PROM2->LightMode 				= 0;
	SaveE2PROM2->JobTimeView 			= 0;
	SaveE2PROM2->OdoMeterView 			= 0;
	SaveE2PROM2->JobOdoSelect 			= 0;
	SaveE2PROM2->LightLowTime 			= 8;
	SaveE2PROM2->LightUpperTime 		= 16;
	SaveE2PROM2->AutoLightDay 			= 0;
	SaveE2PROM2->AutoLightNight 		= 0;
	SaveE2PROM2->Reserved1 				= 0;

	SaveE2PROM3->Phone_1  				= 0;
	SaveE2PROM3->Phone_2  				= 8;
	SaveE2PROM3->Phone_3  				= 0;
	SaveE2PROM3->Phone_4  				= 5;
	SaveE2PROM3->Phone_5  				= 5;
	SaveE2PROM3->Phone_6  				= 5;
	SaveE2PROM3->Phone_7  				= 8;
	SaveE2PROM3->Phone_8  				= 2;
	SaveE2PROM3->Phone_9  				= 7;
	SaveE2PROM3->Phone_10 				= 2;
	SaveE2PROM3->Phone_11 				= 0xf;
	SaveE2PROM3->Phone_12 				= 0xf;

#if 1	// Monitor Change History - temp
	SaveE2PROMoniInfo->ManufactureYear  = 0;
	SaveE2PROMoniInfo->ManufactureMonth = 0;
	SaveE2PROMoniInfo->ManufactureDay   = 0;
	SaveE2PROMoniInfo->MoniPorgramVer   = 0;
	SaveE2PROMoniInfo->MoniSerialNo[0]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[1]  = 0;	// 9
	SaveE2PROMoniInfo->MoniSerialNo[2]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[3]  = 0;	// 8
	SaveE2PROMoniInfo->MoniSerialNo[4]  = 0;	// M
	SaveE2PROMoniInfo->MoniSerialNo[5]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[6]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[7]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[8]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[9]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[10] = 0;	// *
	SaveE2PROMoniInfo->MoniModel[0]     = 0;	// N
	SaveE2PROMoniInfo->MoniModel[1]     = 0;	// -
	SaveE2PROMoniInfo->MoniModel[2]     = 0;	// H
	SaveE2PROMoniInfo->MoniModel[3]     = 0;	// -
	SaveE2PROMoniInfo->MoniModel[4]     = 0;	// W
	SaveE2PROMoniInfo->MoniModel[5]     = 0;	// *
#endif

	SerialPutString("\n\rInitialize : 10 %%\n\r");

	EEPROM_Write(0, 0);	// tmp
	EEPROM_Write(0, 0);	// tmp
	EEPROM_Write(0, 0);	// tmp

	for(i = 0 ; i < 8 ; i++)
	{
		EEPROM_Write(i+8, tmpBuf1[i]);
		TimeDelay_msec(5);
		EEPROM_Write(i+16, tmpBuf2[i]);
		TimeDelay_msec(5);
		EEPROM_Write(i+24, tmpBuf3[i]);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 30 %%\n\r");
	
#if 1	// Monitor Change History - temp
	for(i = 0 ; i < 21 ; i++)
	{
		EEPROM_Write(i+50, tmpBuf4[i]);
		TimeDelay_msec(5);
	}
#endif

	for(i = 0 ; i < 79 ; i++)
	{
		EEPROM_Write(i+100, 0xff);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 60 %%\n\r");

	for(i = 0 ; i < 30 ; i++)
	{
		EEPROM_Write(i+200, 0xff);
		TimeDelay_msec(5);
	}

	for(i = 0 ; i < 29 ; i++)
	{
		EEPROM_Write(i+230, 0xff);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 95 %%\n\r");
	Init_RTC();
	SerialPutString("Initialize : 100 %%\n\r\n\r");
}

void ReadE2PROM_ToSend()
{
#if 0
	u8 i;

	adc_value = (ADC1->DR & 0x0000FFFF);
	
	i = EepromRead(0);	
	i = EepromRead(0);
	i = EepromRead(0);
    i = 0;
    
	adc_value = (ADC1->DR & 0x0000FFFF);

	for(i = 0 ; i < 24 ; i++)
		eepRomReadData1[i] = EepromRead(i+8);

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_Save_Data1[i] = eepRomReadData1[i];

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_Save_Data2[i] = eepRomReadData1[i+8];

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_AS_Phone_Data[i] = eepRomReadData1[i+16];

	for(i = 0 ; i < 21 ; i++)
		MoniInfoData[i] = EepromRead(i+50);
	
	for(i = 0 ; i < 79 ; i++)
		McuInfoData1[i] = EepromRead(i+100);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData2[i] = EepromRead(i+200);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData3[i] = EepromRead(i+210);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData4[i] = EepromRead(i+220);

	memset(&tmpMcuInfoData[1] , 0xff, 77);
	memcpy((u8*)&tmpMcuInfoData[0], (u8*)&McuInfoData1[0], 5);
	memcpy((u8*)&tmpMcuInfoData[5], (u8*)&McuInfoData2[0], 4);
	memcpy((u8*)&tmpMcuInfoData[9], (u8*)&McuInfoData3[0], 4);
	memcpy((u8*)&tmpMcuInfoData[13], (u8*)&McuInfoData4[0], 4);


	adc_value = (ADC1->DR & 0x0000FFFF);
	
	eepRomReadData1[12] = (adc_value & 0xff);
	eepRomReadData1[13] = (adc_value & 0xff00) >> 8;
//	DebugMsg_printf("%2x %2x\r\n", eepRomReadData1[13], eepRomReadData1[12]);

#endif
}

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
void WL9F_10mSecOperationFunc(void)
{
	OperateRingBuffer();
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

void WL9F_System_Init_Start(void)
{
	WL9FM_PowerIG(PowerIG_OFF);					//  ->	GPIO_Control.c PowerIG를 OFF로 만들어 놓고, 
	WL9FM_EXYNOS_POWER_ONOFF(EXYNOS_POWER_ON);	//	->	GPIO_Control.c EXYNOS-4412 Power On..
	//WL9FM_EXYNOS_PMIC_ONOFF();

	DPRAM_Init();								//	-> 	DPRAM_Control.c (Dual Port RAM Init)
	Hardware_Version_Init();					//  ->  Hardware_Version.c (Hardware Version ADC Start)
	Buzzer_Init();              				//  ->  Buzzer.c (Buzzer Timer Start)
	FM3164_Watchdog_Init(0x00);					//  ->  FM31X4.c (Integrated Processor Companion ON)
	KeySwitch_Init();           				//  ->  KeySwitch.c

	LED_POWER_ONOFF(LED_ON);					//	->	LCD_Control.c (LED On/Off)
	LCD_POWER_ONOFF(LCDPWR_ON);					//	-> 	LCD_Control.c (LCD 12V Power On/Off)

	WL9FM_CAMERA_nRESET();						//	-> 	TW2835, TW8832 Power On..
	LCDBL_ONOFF(LCDBL_OFF);						// 	->   부팅시 LCD에 하얀 화면 나옴
	LCD_Control_Init();							//	-> 	LCD_Control.c (LCDBL, ON/OFF)
	//TW2835_Control_Init();						//	-> 	TW2835_Control.c (CAMERA -> Decoder)
	//TW8832_Control_Init();						//	-> 	TW8832_Control.c (LCD Interface)

	USART_COMInit(COMPORT2);       				//  ->	UART_Control.c
	USART_COMInit(COMPORT4);       				//      COM2 : CAN Data
						//		COM4 : CMD Data
	CAN_COMInit();
						//	-> 	CAN_Control.c
	//InitE2PROM();
	ReadE2PROM_ToSend();						//	->	EEPROM Data Read

	//WL9FM_PowerIG(PowerIG_ON);				//	->	GPIO_Control.c 초기화가 끝나면, PowerIG를 ON 한다.!!

}

/**
  * @brief  Application Program Start Point.
  * @param  None
  * @retval None
  */
void WL9F_Display_APP(void)
{
	DebugUART_Init();			//	->	Main.c
	DebugMsg_printf("== START -> DebugMsg from Exynos-4412 \r\n");    

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
		if (WL9FM_TIME.Flag_1mSec == 1)     //  1msec
		{
			WL9FM_TIME.Flag_1mSec = 0;

			//  WL9F_1mSecOperationState -> Func 실행..
			//  if (WL9F_1mSecOperationState != 0) WL9F_1mSecOperationFunc[WL9F_1mSecOperationState]();    
			WL9F_1mSecOperationFunc();
		}            
		
		if (WL9FM_TIME.Flag_10mSec == 1)    //  10msec
		{
			WL9FM_TIME.Flag_10mSec = 0;

			//  WL9F_10mSecOperationState -> Func 실행..
			//  if (WL9F_10mSecOperationState != 0) WL9F_10mSecOperationFunc[WL9F_10mSecOperationState]();    
			WL9F_10mSecOperationFunc();
		}
		
		if (WL9FM_TIME.Flag_100mSec == 1)   //  100 msec
		{
			WL9FM_TIME.Flag_100mSec = 0;

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
		
		if (WL9FM_TIME.Flag_1Sec == 1)      //  1000 msec
		{
			WL9FM_TIME.Flag_1Sec = 0;

			//  WL9F_1SecOperationState -> Func 실행..
			//  if (WL9F_1SecOperationState != 0) WL9F_1SecOperationFunc[WL9F_1SecOperationState]();    
			WL9F_1SecOperationFunc();
		}
	}
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
