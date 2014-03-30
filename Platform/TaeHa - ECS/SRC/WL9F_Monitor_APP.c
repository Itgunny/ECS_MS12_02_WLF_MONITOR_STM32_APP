/**
  ******************************************************************************
  * @file    WL9F_Monitor_APP.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   WL9F_Monitor_APP.c module
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
#include "main.h"
#include "WL9F_Monitor_APP.h"	
#include "WL9F_Monitor_Variable.h"
#include "endecoder.h"
/* Private typedef -----------------------------------------------------------*/
#define RX_MSG69		0x01
#define RX_MSG69_M		0x02
#define RX_MSG145		0x04
#define RX_MSG161		0x08
#define RX_MSG162		0x10
#define RX_MSG163		0x20
#define RX_MSG251		0x40
#define RX_MSG252		0x80
#define RX_MSG202		0x100
#define RX_MSG253		0x200
#define RX_MSG203		0x400
#define RX_MSG239		0x800
#define RX_MSG247		0x1000
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
WL9FM_send_smartkey send_smartkey;
WL9FM_receive_smartkey recv_smartkey;
WL9FM_save_rand_value rand_value;
WL9FM_flag_data smk_flag_data;	

/* Private variables ---------------------------------------------------------*/
u8 gAuthentication_Cnt = 0;

u8 AuthResult;
u8 SMK_Msg_Send;
u8 SMK_Tag_Count;
u8 MultiPacketSendOrder = 0;
u8 TotalPacketNum = 0;
u8 DiffMachInfo = 0;
u8 gStartHCE_DT = 0;
u8 MachInfoSendCnt = 0;
u8 MoniInfoSendCnt = 0;

u8 Flag_UartTxStart = 0;
u8  SendTime_E2PROM = 0;

u16 Flag_1Sec_MachInfo = 0;
u16 Flag_1Sec_MoniInfo = 0;
u16 Flag_1Min = 0;

u8 MachInfoTotalPacketNum = 0;
u8 MoniInfoTotalPacketNum = 0;
u8 Flag_200mSec = 0;
u8 SendRTCnt = 0;
u16 adc_value = 0;

u8 SerialMsgRTC[16];
u8 eepRomReadData1[32];
u8 MoniInfoData[21];
u8 McuInfoData2[4];
u8 McuInfoData3[4];
u8 McuInfoData4[4];

u8 SystemReset = 0;
u8 E2PROM_Save = 0;
u8 PwrOffCnt = 0;
u8 gRebootCmd = 0;


u8 send_mcu_data=0;

u8 ST_Update=0;

extern u8 Uart2_RxMsg_Single_252[8];
extern u8 Uart2_RxMsg_Single_253[8];
extern u8 Uart2_RxMsg_Single_239[8];
extern u8 Uart2_RxMsg_Single_247[8];
extern u8 Uart2_RxMsg_Save_Data1[8];
extern u8 Uart2_RxMsg_Save_Data2[8];
extern u8 Uart2_RxMsg_AS_Phone_Data[8];
extern u8 Uart2_RxMsg_Smk_Reg_Eli[8];
extern u8 McuInfoData1[79];
extern u8 tmpMcuInfoData[78];

extern u8 stop_send_as_phone_data;
extern u8 Flag_TxE2pRomData;

extern u8 Buz1, Buz2;

extern u8 Stm32_Update_CMD;
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
#if 1
	u8 i;

	adc_value = (ADC1->DR & 0x0000FFFF);

	i = EEPROM_Read(0);	
	i = EEPROM_Read(0);
	i = EEPROM_Read(0);
	i = 0;
    
	adc_value = (ADC1->DR & 0x0000FFFF);

	for(i = 0 ; i < 24 ; i++)
		eepRomReadData1[i] = EEPROM_Read(i+8);

	for(i = 0 ; i < 8 ; i++)
		Uart2_RxMsg_Save_Data1[i] = eepRomReadData1[i];

	for(i = 0 ; i < 8 ; i++)
		Uart2_RxMsg_Save_Data2[i] = eepRomReadData1[i+8];

	for(i = 0 ; i < 8 ; i++)
		Uart2_RxMsg_AS_Phone_Data[i] = eepRomReadData1[i+16];

	for(i = 0 ; i < 21 ; i++)
		MoniInfoData[i] = EEPROM_Read(i+50);
	
	for(i = 0 ; i < 79 ; i++)
		McuInfoData1[i] = EEPROM_Read(i+100);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData2[i] = EEPROM_Read(i+200);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData3[i] = EEPROM_Read(i+210);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData4[i] = EEPROM_Read(i+220);

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

void Send_Multipacket_69(void)
{
	if(MultiPacketSendOrder == 0)
	{
		if(TotalPacketNum == 0)
		{
			TimeDelay_msec(15);
			SendTP_CM_BAM_MultiPacket_69();
			TotalPacketNum += 1;
		}
		else if(TotalPacketNum == 1)
		{
			// TP.DT
			TimeDelay_msec(15);
			SendFirstMultiPacket_69();
			TotalPacketNum += 1;
		}
		else if(TotalPacketNum == 2)
		{
			// TP.DT
			TimeDelay_msec(15);
			SendSecondMultiPacket_69();

			if(TotalPacketNum == tp_cm_bam_TotPacketNum)
			{
				Flag_SerialRxMsg &= ~(RX_MSG69_M);
				TotalPacketNum = 0;

				///+++
				if((DiffMachInfo == 1) && (gStartHCE_DT == 1))
				{
					if(MachInfoSendCnt <= 60)
						MultiPacketSendOrder = 1;	// Machine Basic Information
					else if(MoniInfoSendCnt <= 60)
						MultiPacketSendOrder = 2;	// Monitor Basic Information
				}
			}
			else
				TotalPacketNum += 1;
		}
		else if(TotalPacketNum == 3)
		{
			TimeDelay_msec(15);
			SendThirdMultiPacket_69();
			TotalPacketNum = 0;

					///+++
			if((DiffMachInfo == 1) && (gStartHCE_DT == 1))
			{
				if(MachInfoSendCnt <= 60)
					MultiPacketSendOrder = 1;	// Machine Basic Information
				else if(MoniInfoSendCnt <= 60)
					MultiPacketSendOrder = 2;	// Monitor Basic Information
			}
		}
	}
}

void Send_Multipacket_161(void)
{
	if(TotalPacketNum == 0)
	{
		TimeDelay_msec(15);
		SendTP_CM_BAM_MultiPacket_161();
		TotalPacketNum += 1;
	}
	else if((TotalPacketNum == 1) || (TotalPacketNum == 2))
	{
		TimeDelay_msec(15);
		SendMultiPacketData_161(TotalPacketNum);
		TotalPacketNum += 1;

		if(TotalPacketNum >= 3)
		{
			Flag_SerialRxMsg &= ~(RX_MSG161);
			TotalPacketNum = 0;
		}
	}
}

void Send_Multipacket_AS_Num(void)
{
	if(check_as_data_len == 0)
		CheckASDataLen();

	if(as_data_len < 8)	// Single Packet
	{
		SetCanID(255, 145, 6);
		CAN_TX_Data(&tmpbuf_AS[0]);
		check_as_data_len = 0;

		if(stop_send_as_phone_data == 1)
		{
			stop_send_as_phone_data = 0;
			Flag_SerialRxMsg &= ~(RX_MSG202);
		}
	}
	else	        	// Multi Packet
	{
		if(TotalPacketNum == 0)
		{
			TimeDelay_msec(15);
			SendTP_CM_BAM_MultiPacket_202_AS();
			TotalPacketNum += 1;
		}
		else if((TotalPacketNum == 1) || (TotalPacketNum == 2))
		{
			TimeDelay_msec(15);
			SendMultiPacketData_202_AS(TotalPacketNum);
			TotalPacketNum += 1;

			if(TotalPacketNum >= 3)
			{
				if(stop_send_as_phone_data == 1)
				{
					stop_send_as_phone_data = 0;
					Flag_SerialRxMsg &= ~(RX_MSG202);
				}
				
				TotalPacketNum = 0;
				check_as_data_len = 0;
			}
		}
	}
}

void Send_Multipacket_Info(void)
{
	if(MultiPacketSendOrder == 1)
	{
		if(MachInfoSendCnt <= 60)
		{
			if(++Flag_1Sec_MachInfo >= 100)
			{
				if(MachInfoTotalPacketNum == 0)
				{
					SendTP_CM_BAM_MultiPacket_MachInfo();
					MachInfoTotalPacketNum++;
				}
				else
					SendMultiPacket_MachInfo();
			}
			else
			{
				if((Flag_SerialRxMsg & RX_MSG69_M) != 0)	// 69 - Multi Packet
					MultiPacketSendOrder = 0;
			}
		}
		else
		{
			if((Flag_SerialRxMsg & RX_MSG69_M) != 0)	// 69 - Multi Packet
				MultiPacketSendOrder = 0;
			else if(MoniInfoSendCnt <= 60)
				MultiPacketSendOrder = 2;
		}
	}
	else if(MultiPacketSendOrder == 2)
	{
		if(MoniInfoSendCnt <= 60)
		{
			if(++Flag_1Sec_MoniInfo >= 100)
			{
				if(MoniInfoTotalPacketNum == 0)
				{
					SendTP_CM_BAM_MultiPacket_MoniInfo();
					MoniInfoTotalPacketNum++;
				}
				else
					SendMultiPacket_MoniInfo();
			}
			else
			{
				if((Flag_SerialRxMsg & RX_MSG69_M) != 0)	// 69 - Multi Packet
					MultiPacketSendOrder = 0;
			}
		}
		else
		{
			if((Flag_SerialRxMsg & RX_MSG69_M) != 0)	// 69 - Multi Packet
				MultiPacketSendOrder = 0;
			else if(MachInfoSendCnt <= 60)
				MultiPacketSendOrder = 1;
		}
	}
}

void read_clock(void)
{
	READ_RTC(&WL9FM_RTC);
	SerialMsgRTC[8] = WL9FM_RTC.Hour;
	SerialMsgRTC[9] = WL9FM_RTC.Minute;
}

void SaveDataToEEPROM(void)
{
	u8 i;
	
	for(i = 0 ; i < 8 ; i++)
	{
		EEPROM_Write(i+8, Uart2_RxMsg_Save_Data1[i]);
		TimeDelay_msec(1);
	}

	for(i = 0 ; i < 8 ; i++)
	{
		EEPROM_Write(i+16, Uart2_RxMsg_Save_Data2[i]);
		TimeDelay_msec(1);
	}

	for(i = 0 ; i < 8 ; i++)
	{
		EEPROM_Write(i+24, Uart2_RxMsg_AS_Phone_Data[i]);
		TimeDelay_msec(1);
	}

	for(i = 0 ; i < 21 ; i++)
	{
		EEPROM_Write(i+50, MoniInfoData[i]);
		TimeDelay_msec(1);
	}
	
	for(i = 0 ; i < 79 ; i++)
	{
		EEPROM_Write(i+100, McuInfoData1[i]);
		TimeDelay_msec(1);
	}


	if(DiffMachInfo == 1)
	{
		memcpy((u8*)&McuInfoData2[0], (u8*)&tmpMcuInfoData[5] , 4);		
		memcpy((u8*)&McuInfoData3[0], (u8*)&tmpMcuInfoData[9] , 4);
		memcpy((u8*)&McuInfoData4[0], (u8*)&tmpMcuInfoData[13] , 4);
	}

	for(i = 0 ; i < 4 ; i++)
	{
		EEPROM_Write(i+200, McuInfoData2[i]);
		TimeDelay_msec(1);
	}

	for(i = 0 ; i < 4 ; i++)
	{
		EEPROM_Write(i+210, McuInfoData3[i]);
		TimeDelay_msec(1);
	}

	for(i = 0 ; i < 4 ; i++)
	{
		EEPROM_Write(i+220, McuInfoData4[i]);
		TimeDelay_msec(1);
	}
}


void System_CheckPowerIG()
{
	// Check POWER IG
	if(!WL9FM_GetPowerIG())
	{
		WL9FM_PowerIG(PowerIG_ON);
		SystemReset = 0;
	}
	else
	{
		if(E2PROM_Save == 0)
		{
			SaveDataToEEPROM();

			PwrOffCnt = 0;

			while(1)
			{
				if(!WL9FM_GetPowerIG())
				{
					//	POWER OFF 일 때, 시리얼과 캔 통신 부분을 죽여놔야지, 정상적으로 RESET 동작을 수행
					USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
					CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);

					WL9FM_PowerIG(PowerIG_ON);	// System Reset
					SystemReset = 1;
					return;
				}
			
				TimeDelay_msec(100);

				PwrOffCnt++;
				if(PwrOffCnt >= 15)	//	100msec 마다 15번 체크 -> 1.5초..
					break;
			}

			Buzzer_Off();

			//	POWER OFF Code를 3msec 마다 2번 SPICA로 보낸다. 
			KeySwitch_SendToEXYNOS(KEYSWITCH_POWER_OFF,0);	
			TimeDelay_msec(3);
			KeySwitch_SendToEXYNOS(KEYSWITCH_POWER_OFF,0);	
			TimeDelay_msec(3);

			//	POWER OFF 일 때, 시리얼과 캔 통신 부분을 죽여놔야지, 정상적으로 RESET 동작을 수행
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);

			//	엔딩화면 딜레이 시간
			//	1200msec 이상 설정하면, LCD가 하얗게 된다. -> POWER Off Time으로 인하여
			TimeDelay_msec(1200);

			LCDBL_PWM_LEVEL(0);                         	//  LCDBL PWM LEVEL0
			LCDBL_ONOFF(LCDBL_OFF);			//  LCDBL Power On!!!
	
	        
			//	엔딩화면이 지난 후에 PowerIG가 다시 들어오면, System을 RESET 시킨다. 
			if(!WL9FM_GetPowerIG())
			{
				WL9FM_PowerIG(PowerIG_ON);
				SystemReset = 1;
				return;
			}
	        
			LCD_POWER_ONOFF(LCDPWR_OFF);                        //  LCD Power Off
			LED_POWER_ONOFF(LED_OFF);                        	//  LED Off
			WL9FM_EXYNOS_POWER_ONOFF(EXYNOS_POWER_OFF);	
			WL9FM_PowerIG(PowerIG_OFF);                    //  24v Main Power Off	        
		}
	}
}

/*******************************************************************************
*
*	Smart Key Test Function
*
*******************************************************************************/
#if 0
void SendSMKAuthResult(u8 result)
{
	RTC_SendToExynos( result, SMK_Tag_Count );
}

void SendSMKMsgResult(u8 result)
{
	RTC_SendToExynos( result, recv_smartkey.Registered_Tag_Count );
}

void SetTagLevel(u8 level)
{
	if((level == TAG_LEVEL_NORMAL) || (level == TAG_LEVEL_MASTER_TAG))
		send_smartkey.TagLevel = level;
	else
		send_smartkey.TagLevel = 3;
}

void SetTagCmd(u8 cmd)
{
	if(cmd <= TAG_CMD_COMM_AUTHENTICATION)
		send_smartkey.TagCommand = cmd;
	else
		send_smartkey.TagCommand = 0xf;
}

void SetVMC(void)
{
	if(rand_value.rand_vmc <= 64255)
		send_smartkey.VMC = rand_value.rand_vmc;
	else
		send_smartkey.VMC = 0xffff;
}

void SetCPK(void)
{
#if 1
	if(rand_value.rand_cpk <= 0xfaffffff)
		send_smartkey.CPK = rand_value.rand_cpk;
	else
		send_smartkey.CPK = 0xffffffff;
#else
	send_smartkey.CPK = 0x11223344;
#endif
}

void Srand()
{
	READ_RTC(&WL9FM_RTC);
	srand((u32)WL9FM_RTC.Second);
}

void GetRandValue(u8 random)
{
	if(random == GET_VMC)	
		rand_value.rand_vmc = (rand() % 64255);
	else if(random == GET_CPK)	
		rand_value.rand_cpk = (rand() % 0xfaffffff);
	else if(random == GET_VMC_CPK)		
	{
		rand_value.rand_vmc = (rand() % 64255);
		rand_value.rand_cpk = (rand() % 0xfaffffff);
	}	
}

void RequestFirstAuthentication(void)
{
	unsigned int temp;
	
	SetTagLevel(TAG_LEVEL_NORMAL);
	SetTagCmd(TAG_CMD_COMM_AUTHENTICATION);
	GetRandValue(GET_VMC_CPK);
	SetVMC();
	SetCPK();

	setCipherParam(0x8085, 0x8087);
	encode((u8*)&send_smartkey.CPK, 4, (u8*)&temp, 4);
	
	send_smartkey.CPK = temp;

	// CPK 암호화 Function 추가 필요
	TimeDelay_msec(10);
	SetCanID(255, 231, 6);
	CAN_TX_Data((u8*)&send_smartkey);
}

void RequestSecondAuthentication(void)
{
	unsigned short upper_cpk, lower_cpk;
	unsigned int temp;

	upper_cpk = (rand_value.rand_cpk & 0xffff0000) >> 16;
	lower_cpk = rand_value.rand_cpk & 0x0000ffff;
	
	SetTagLevel(TAG_LEVEL_NORMAL);
	SetTagCmd(TAG_CMD_AUTHENTICATON);
	GetRandValue(GET_VMC);
	SetVMC();

	setCipherParam(upper_cpk, lower_cpk);
	//setCipherParam(0x1122, 0x3344);
	encode((u8*)&send_smartkey.CPK, 4, (u8*)&temp, 4);

	send_smartkey.CPK = temp;
	
	TimeDelay_msec(10);
	SetCanID(255, 231, 6);
	CAN_TX_Data((u8*)&send_smartkey);

	//smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
}

void RequestSMKRegistration(void)
{
	unsigned short upper_cpk, lower_cpk;
	unsigned int temp;

	upper_cpk = (rand_value.rand_cpk & 0xffff0000) >> 16;
	lower_cpk = rand_value.rand_cpk & 0x0000ffff;
	
	SetTagLevel(TAG_LEVEL_NORMAL);
	SetTagCmd(TAG_CMD_REGISTRATION);
	GetRandValue(GET_VMC);
	SetVMC();

	setCipherParam(upper_cpk, lower_cpk);
	//setCipherParam(0x1122, 0x3344);
	encode((u8*)&send_smartkey.CPK, 4, (u8*)&temp, 4);

	send_smartkey.CPK = temp;

	SetCanID(255, 231, 6);
	CAN_TX_Data((u8*)&send_smartkey);

	//smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
}

void RequestSMKElimination(void)
{
	unsigned short upper_cpk, lower_cpk;
	unsigned int temp;

	upper_cpk = (rand_value.rand_cpk & 0xffff0000) >> 16;
	lower_cpk = rand_value.rand_cpk & 0x0000ffff;
	
	SetTagLevel(TAG_LEVEL_NORMAL);
	SetTagCmd(TAG_CMD_ELIMINATION);
	GetRandValue(GET_VMC);
	SetVMC();

	setCipherParam(upper_cpk, lower_cpk);
	//setCipherParam(0x1122, 0x3344);
	encode((u8*)&send_smartkey.CPK, 4, (u8*)&temp, 4);

	send_smartkey.CPK = temp;

	SetCanID(255, 231, 6);
	CAN_TX_Data((u8*)&send_smartkey);

	//smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
}

void RequestSMKMessage(u8 Msg)
{
	if(Msg == 1)
		RequestSMKRegistration();
	else if(Msg == 2)
		RequestSMKElimination();
}

void RequestSMKComm(void)
{
	SetTagLevel(TAG_LEVEL_NORMAL);
	SetTagCmd(TAG_CMD_COMM_AUTHENTICATION);
	GetRandValue(GET_VMC);
	SetVMC();

	SetCanID(255, 231, 6);
	CAN_TX_Data((u8*)&send_smartkey);

	//smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
}

u8 CheckResponseVMC(void)
{
	if(send_smartkey.VMC == recv_smartkey.ReturnVMC)
		return RETURN_VMC_OK;
	else
		return RETURN_VMC_NOT_OK;
}

u8 CheckResponseAuthentication(u8 Auth)
{
	u8 output_buf[8];
	u16 upper_cpk, lower_cpk;

	upper_cpk = (rand_value.rand_cpk & 0xffff0000) >> 16;
	lower_cpk = rand_value.rand_cpk & 0x0000ffff;
	
	setCipherParam(upper_cpk, lower_cpk);
	//setCipherParam(0x1122, 0x3344);	// 임시
	decode((u8*)&recv_smartkey, 8, (u8*)&output_buf[0], 8);

	memcpy((u8*)&recv_smartkey, (u8*)&output_buf[0], 8);
	
	
	if((send_smartkey.TagLevel == recv_smartkey.ReturnTagLevel) && (send_smartkey.TagCommand == recv_smartkey.ReturnTagCommand) 
		&& (send_smartkey.VMC == recv_smartkey.ReturnVMC))
	{
		if((recv_smartkey.Smk_Response_Code == Auth) && 
			(recv_smartkey.Smk_Response_Flag == SMK_RESPONSE_FLAG_SUCCESS))
		{
			return SMK_RESPONSE_FLAG_SUCCESS;
		}
		else
			return recv_smartkey.Smk_Response_Flag;
	}
	else
		return SMK_RESPONSE_CODE_NOT_MATCH;
}

void CheckResponseMsgComm(void)
{
	u8 output_buf[8];
	u16 upper_cpk, lower_cpk;

	upper_cpk = (rand_value.rand_cpk & 0xffff0000) >> 16;
	lower_cpk = rand_value.rand_cpk & 0x0000ffff;
	
	setCipherParam(upper_cpk, lower_cpk);
	//setCipherParam(0x1122, 0x3344);	// 임시
	decode((u8*)&recv_smartkey, 8, (u8*)&output_buf[0], 8);

	memcpy((u8*)&recv_smartkey, (u8*)&output_buf[0], 8);

	if((send_smartkey.TagLevel == recv_smartkey.ReturnTagLevel) && (send_smartkey.TagCommand == recv_smartkey.ReturnTagCommand) 
		&& (send_smartkey.VMC == recv_smartkey.ReturnVMC))
	{
		if(recv_smartkey.Smk_Response_Code == 1)
		{
			switch(recv_smartkey.Smk_Response_Flag)
			{
				case 2 :
					SendSMKMsgResult(SMK_MSG_TAG_NO_REALIZE);
					break;
				case 3 :
					SendSMKMsgResult(SMK_MSG_FAIL);
					break;
				case 4 :
					SendSMKMsgResult(SMK_MSG_TAG_ALREADY_REG);
					break;
				default :
					if(recv_smartkey.ReturnTagCommand == SMK_RESPONSE_CODE_REGISTRATION)
					{
						if(recv_smartkey.Registered_Tag_Count == 1)
							SendSMKMsgResult(SMK_MSG_TAG_FIRST_REG_SUCCESS);
						else if(recv_smartkey.Registered_Tag_Count == 2)
							SendSMKMsgResult(SMK_MSG_TAG_SECOND_REG_SUCCESS);
						else
							SendSMKMsgResult(SMK_MSG_FAIL);
					}
					else
					{
						if(SMK_Tag_Count != 0)
							SMK_Tag_Count--;

						SendSMKMsgResult(SMK_MSG_FAIL);
					}
					break;
			}
			
		}
		else if(recv_smartkey.Smk_Response_Code == 2)
			SendSMKMsgResult(SMK_MSG_TAG_ELIMINATION_SUCCESS);
                else
                        SendSMKMsgResult(SMK_MSG_FAIL);
	}
	else
		SendSMKMsgResult(SMK_MSG_FAIL);
}

void SmartKeyAuthentication(void)
{
	u8  Auth = 0;
	u8 returnvalue;

	if(AuthResult != 1)
	{
		if((smk_flag_data.recv_resp_packet != RESPONSE_SUCCESS) && (smk_flag_data.recv_resp_packet != RESPONSE_TIME_OUT))
		{
			if(smk_flag_data.recv_resp_packet == REQUEST_FIRST_AUTHENTICATION)
			{
				smk_flag_data.recv_resp_packet |= RESPONSE_WAIT;
				RequestFirstAuthentication();
			}
			else if(smk_flag_data.recv_resp_packet == REQUEST_SECOND_AUTHENTICATION)
			{
				smk_flag_data.recv_resp_packet |= RESPONSE_WAIT;
				RequestSecondAuthentication();
			}
			else if(smk_flag_data.recv_resp_packet & RESPONSE_AUTHENTICATION)
			{
				//smk_flag_data.recv_resp_packet &= (~(RESPONSE_AUTHENTICATION));
				smk_flag_data.recv_resp_packet = (smk_flag_data.recv_resp_packet & (~(RESPONSE_AUTHENTICATION)));

				if(smk_flag_data.recv_resp_packet & REQUEST_FIRST_AUTHENTICATION)
					Auth = SMK_RESPOSEN_CODE_COMM_AUTHENTICATION;
				else if(smk_flag_data.recv_resp_packet & REQUEST_SECOND_AUTHENTICATION)
					Auth = SMK_RESPONSE_CODE_AUTHENTICATION;
					
				returnvalue = CheckResponseAuthentication(Auth);
					
				if(returnvalue == SMK_RESPONSE_FLAG_SUCCESS)	// Success
				{
					if(smk_flag_data.recv_resp_packet & REQUEST_FIRST_AUTHENTICATION)
					{
						gAuthentication_Cnt = 0;
						smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
					}
					else if(smk_flag_data.recv_resp_packet & REQUEST_SECOND_AUTHENTICATION)
					{
						gAuthentication_Cnt = 0;
						AuthResult = 1;
						SMK_Tag_Count = recv_smartkey.Registered_Tag_Count;
						smk_flag_data.recv_resp_packet = RESPONSE_SUCCESS;
						SendSMKAuthResult(SMK_SUCCESS);
					}
				}
				else
				{
					if(++gAuthentication_Cnt >= TIME_OUT_COUNT)
					{
						//AuthResult = 2;
						AuthResult = 1;
						smk_flag_data.recv_resp_packet = RESPONSE_TIME_OUT;
						SendSMKAuthResult(SMK_FAIL);
						return;
					}

					if(smk_flag_data.recv_resp_packet & REQUEST_FIRST_AUTHENTICATION)
						smk_flag_data.recv_resp_packet = REQUEST_FIRST_AUTHENTICATION;
					else if(smk_flag_data.recv_resp_packet & REQUEST_SECOND_AUTHENTICATION)
						smk_flag_data.recv_resp_packet = REQUEST_SECOND_AUTHENTICATION;
				}
			}
		}
	}
	//else if(AuthResult == 1)
	{
		if((Uart2_RxMsg_Smk_Reg_Eli[0] == 1) || (Uart2_RxMsg_Smk_Reg_Eli[0] == 2)) 
		{
			RequestSMKMessage(Uart2_RxMsg_Smk_Reg_Eli[0]);
			SMK_Msg_Send = 1;
			smk_flag_data.recv_resp_packet = 0;
			Uart2_RxMsg_Smk_Reg_Eli[7] = Uart2_RxMsg_Smk_Reg_Eli[0];
			Uart2_RxMsg_Smk_Reg_Eli[0] = 0xff;
		}

		if(SMK_Msg_Send == 1)
		{
			if(smk_flag_data.recv_resp_packet == RESPONSE_AUTHENTICATION)
			{
				SMK_Msg_Send = 0;
				CheckResponseMsgComm();
			}
		}
	}
}
#endif
/**
  * @brief  1msec OperationFunc
  * @param  None
  * @retval None
  */
void WL9FM_1mSecOperationFunc(void)
{
#if 1
	if( Flag_UartTxStart == 1 )
	{
		if (SendTime_E2PROM++ > 3) //	25msec
		{
			SendTime_E2PROM = 0;
			SendTo_E2PROM();
			KeySwitch_SendToEXYNOS(KEYSWITCH_NONE,0);
		}			
	}
#endif
}

/**
  * @brief  10msec OperationFunc
  * @param  None
  * @retval None
  */
void WL9FM_10mSecOperationFunc(void)
{
	Lamp_Update_State();	//	LAMP Update 상태를 체크한다.
	//Lamp_Update_System();  
	
	if(Flag_SerialRxMsg != 0)
	{
		if((Flag_SerialRxMsg & RX_MSG247) != 0)
		{
			Flag_SerialRxMsg &= ~(RX_MSG247);
			SetCanID(255, 247, 6);
			CAN_TX_Data(&Uart2_RxMsg_Single_247[0]);
		}
		
		if((Flag_SerialRxMsg & RX_MSG253) != 0)
		{
			Flag_SerialRxMsg &= ~(RX_MSG253);
			SetCanID(255, 253, 6);
			CAN_TX_Data(&Uart2_RxMsg_Single_253[0]);
		}
		
		if((Flag_SerialRxMsg & RX_MSG203) != 0)	    // 61184 -203 
		{
			Flag_SerialRxMsg &= ~(RX_MSG203);
			SetCanID(239, 228, 6);
			CAN_TX_Data(&Uart2_RxMsg_Single_46[0]);
		}

		if((Flag_SerialRxMsg & RX_MSG69) != 0)	    // 69 - Single Packet
		{
			Flag_SerialRxMsg &= ~(RX_MSG69);
			SetCanID(255, 69, 6);
			CAN_TX_Data(&Uart2_RxMsg_Single_69[0]);
		}
		
		if((Flag_SerialRxMsg & RX_MSG163) != 0)
		{
			Flag_SerialRxMsg &= ~(RX_MSG163);
			SetCanID(255, 163, 6);
			CAN_TX_Data(&Uart2_RxMsg_Single_163[0]);
		}
		
		if((Flag_SerialRxMsg & RX_MSG69_M) != 0)	// 69 - Multi Packet
		{
			Send_Multipacket_69();
		}
		else if((Flag_SerialRxMsg & RX_MSG161) != 0)
		{
			Send_Multipacket_161();
		}
		else if((Flag_SerialRxMsg & RX_MSG202) != 0)
		{
			Send_Multipacket_AS_Num();
		}
		else
		{
			///+++
			if(gStartHCE_DT == 1)
			{
				if(MachInfoSendCnt <= 60)
				{
					if(MultiPacketSendOrder == 0)
						MultiPacketSendOrder = 1;
				}
				else if(MoniInfoSendCnt <= 60)
					MultiPacketSendOrder = 2;
			}
		}
	}
	else
	{
		///+++
		if(gStartHCE_DT == 1)
		{
			if(MachInfoSendCnt <= 60)
			{
				if(MultiPacketSendOrder == 0)
					MultiPacketSendOrder = 1;
			}
			else if(MoniInfoSendCnt <= 60)
				MultiPacketSendOrder = 2;
		}
	}

	if(gStartHCE_DT == 1)
	{
		Send_Multipacket_Info();
	}
}

/**
  * @brief  100msec OperationFunc
  * @param  None
  * @retval None
  */
void WL9FM_100mSecOperationFunc(void)
{
	Lamp_Update_System();	//	체크된 LAMP 상태를 업데이트 한다.

	SetCanID(255, 160, 6);
	
	CAN_TX_Data(&Uart2_RxMsg_Single_160[0]);

	if(((Uart2_RxMsg_Single_160[0] & 0xc0) == 0x00) || ((Uart2_RxMsg_Single_160[0] & 0xc0) == 0x40))		// Speed Up/Down
		Uart2_RxMsg_Single_160[0] |= 0xc0;

    	//  STM32에서 KeySwitch에 따른 BUZZER에 관한 명령을 MCU로 보내기 위해서 추가~
	if( (Uart2_RxMsg_Single_160[0] & 0x10 ) == 0x10 )
	{
		if( WL9FM_BUZZER.Status == 0 )
			Uart2_RxMsg_Single_160[0] = Uart2_RxMsg_Single_160[0] & 0xCF;
	}

	if((Flag_SerialRxMsg & RX_MSG251) != 0)
	{
		Flag_SerialRxMsg &= ~(RX_MSG251);
		SetCanID(255, 251, 6);
		CAN_TX_Data(&Uart2_RxMsg_Single_251[0]);
	}

	if((Flag_SerialRxMsg & RX_MSG239) != 0) // send 61184 to mcu
	{
		SetCanID(239, 71, 6);
		CAN_TX_Data(&Uart2_RxMsg_Single_239[0]);
		if(++send_mcu_data>2)
		{
			send_mcu_data=0;
			Flag_SerialRxMsg &= ~(RX_MSG239);
		}
	}

   	if(++Flag_200mSec >= 2)
   	{
   		Flag_200mSec = 0;
   		SetCanID(255, 162, 6);
   		CAN_TX_Data(&Uart2_RxMsg_Single_162[0]);
   		if(Uart2_RxMsg_Single_162[4] != 0)
   			Uart2_RxMsg_Single_162[4] = 0;
   	}
#if 0
	if(Flag_TxE2pRomData == 1)
		SmartKeyAuthentication();
#endif
	

	if((Flag_SerialRxMsg & RX_MSG252) != 0)
	{
		Flag_SerialRxMsg &= ~(RX_MSG252);

		WL9FM_RTC.Hour = Uart2_RxMsg_Single_252[4];
		WL9FM_RTC.Minute = Uart2_RxMsg_Single_252[5];
		WRITE_RTC(WL9FM_RTC);
	}

	
	if(CommErrCnt > 1000)
   	{
   		if( Flag_TxE2pRomData == 1 )
	   	{
	   		CAN_COMInit();
   			CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);	

			Buz1 = Buz2 = 0;

			if(++SendRTCnt >= 10)
			{
				SendRTCnt = 0;

				RTC_SendToExynos( WL9FM_RTC.Hour, WL9FM_RTC.Minute );
			}
			//Buzzer_SendToEXYNOS(1);
	   	}
	}	
	
	System_CheckPowerIG();

	if(ST_Update)
	{
		STM32_Update(Stm32_Update_CMD);	
		ST_Update=0;
	}
		
	//	WL9A Monitor RESET Code
	if((SystemReset == 1) || (gRebootCmd == 1))
	{
		if(gRebootCmd == 1)
			SaveDataToEEPROM();
				
		//	여기서 WL99F_100mSecOperationFunc() 함수를 빠져나간다.
		//	WL9F_100mSecOperationFunc() 함수가 종료되는 시점에 SYSTEM RESET을 시킨다.
		//	WL9F_Monitor_APP() 함수로 이동!!!
		return;
	}

}




/**
  * @brief  1sec OperationFunc
  * @param  None
  * @retval None
  */
void WL9FM_1SecOperationFunc(void)
{
	if(gStartHCE_DT == 1)
	{
		CompareMachBasicInfo();
    
		if(++Flag_1Min >= 60)
		{
			Flag_1Min = 0;
			RequestMachBasicInfo();

			if((MachInfoSendCnt > 60) && (MoniInfoSendCnt > 60))
				MultiPacketSendOrder = 0;
		}
	}
	read_clock();


	//  ++, kutelf, 131007
	//	카메라 동작 모드 일 경우, 3초 마다 한번씩 각 채널의
	//	상태를 체크하여, Video가 없으면 No Video 띄워준다.
	if (Camera_CheckFlag == 1)
	{
		if (++Camera_CheckCnt == 6) Camera_CheckCnt = 0;
			
		if ((Camera_CheckCnt % 3) == 0)
		{
			cam_mode_check();
		}
	}
	else
	{
		Camera_CheckCnt = 0;
	}
	//  --, kutelf, 131007
}


void WL9FM_System_Init_Start(void)
{
	WL9FM_PowerIG(PowerIG_OFF);					//  ->	GPIO_Control.c PowerIG를 OFF로 만들어 놓고, 
	WL9FM_EXYNOS_POWER_ONOFF(EXYNOS_POWER_ON);	//	->	GPIO_Control.c EXYNOS-4412 Power On..
	
	WL9FM_CAMERA_nRESET();						//	-> 	TW2835, TW8832 Power On..
	TW8832_Control_Init();						//	-> 	TW8832_Control.c (LCD Interface)
	TW2835_Control_Init();	
	
	DPRAM_Init();								//	-> 	DPRAM_Control.c (Dual Port RAM Init)
	Hardware_Version_Init();					//  ->  Hardware_Version.c (Hardware Version ADC Start)
	Buzzer_Init();              				//  ->  Buzzer.c (Buzzer Timer Start)
	FM3164_Watchdog_Init(0x00);					//  ->  FM31X4.c (Integrated Processor Companion ON)
	KeySwitch_Init();           				//  ->  KeySwitch.c
	LAMP_Control_Init();						//	-> 	LAMP_Control.c
												//		LAMP ALL ON
	LED_POWER_ONOFF(LED_ON);					//	->	LCD_Control.c (LED On/Off)
	LCD_POWER_ONOFF(LCDPWR_ON);					//	-> 	LCD_Control.c (LCD 12V Power On/Off)

	LCD_Control_Init();							//	-> 	LCD_Control.c (LCDBL, ON/OFF)

	USART_COMInit(COMPORT2);       				//      COM2 : CAN
	USART_COMInit(COMPORT4);       				//      COM4 : CMDData

												
	CAN_COMInit();								//	-> 	CAN_Control.c
	//InitE2PROM();
	ReadE2PROM_ToSend();						//	->	EEPROM Data Read

	M25P32_Init();

	//WL9FM_PowerIG(PowerIG_ON);				//	->	GPIO_Control.c 초기화가 끝나면, PowerIG를 ON 한다.!!
	LAMP_Update_Data = LAMP_ALL_OFF;			//	-> 	LAMP ALL OFF
	



	
}

/**
  * @brief  Application Program Start Point.
  * @param  None
  * @retval None
  */
void WL9FM_Monitor_APP(void)
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
	WL9FM_System_Init_Start();
	
	/* Infinite loop */
	while (1)
	{  
		if (WL9FM_TIME.Flag_1mSec == 1)     //  1msec
		{
			WL9FM_TIME.Flag_1mSec = 0;

			//  WL9F_1mSecOperationState -> Func 실행..
			//  if (WL9F_1mSecOperationState != 0) WL9F_1mSecOperationFunc[WL9F_1mSecOperationState]();    
			WL9FM_1mSecOperationFunc();
		}            
		
		if (WL9FM_TIME.Flag_10mSec == 1)    //  10msec
		{
			WL9FM_TIME.Flag_10mSec = 0;

			//  WL9F_10mSecOperationState -> Func 실행..
			//  if (WL9F_10mSecOperationState != 0) WL9F_10mSecOperationFunc[WL9F_10mSecOperationState]();    
			WL9FM_10mSecOperationFunc();
		}
		
		if (WL9FM_TIME.Flag_100mSec == 1)   //  100 msec
		{
			WL9FM_TIME.Flag_100mSec = 0;

			//  WL9F_100mSecOperationState -> Func 실행..
			//  if (WL9F_100mSecOperationState != 0) WL9F_100mSecOperationFunc[WL9F_100mSecOperationState]();    
			WL9FM_100mSecOperationFunc();

			#if 1
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
			WL9FM_1SecOperationFunc();
                        
		}
	}
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
