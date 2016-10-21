/**
  ******************************************************************************
  * @file    WL9F_Monitor_APP.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Main Header
  *
  * Project Name       : WL9F Monitor Common
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
#ifndef __WL9F_Monitor_APP_H
#define __WL9F_Monitor_APP_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "stm32f4xx.h"
#include "stm324xg_eval.h"

#include "System_Init.h"
#include "System_Debug.h"
//	++, kutelf, 140801
//	RevD.01.01 
//	DPRAM ���� - FSMS ��� ����. 
#if 0
#include "DPRAM_Control.h"
#endif
//	--, kutelf, 140801
#include "FM31X4.h"
#include "TimeDelay.h"
#include "GPIO_Control.h"
#include "Buzzer.h"
#include "Hardware_Version.h"
#include "KeySwitch.h"
#include "LAMP_Control.h"
#include "LCD_Control.h"

//	++, kutelf, 140801
//	RevD.01.01 
//	Camera Input, LCD Controller ����
//		=> TW2835 + TW8832 -> TW8816
#include "TW8816_Control.h"
#include "TW8816_OSD.h"

//	RevD ���� �������� ��� 
#include "TW2835_Control.h"
#include "TW2835_OSD.h"
#include "TW8832_Control.h"
#include "TW8832_OSD.h"
//	--, kutelf, 140801

#include "UART_Control.h"
#include "CAN_Control.h"
#include "M25PXX.h"
#include "RTC.h"				// ++, --, 160511 bwk

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// ++, sys3215, 141211
#define REVH			2		// ++, --, 160511 bwk
#define REVD_02_01	1

#define REVB			0

// --, sys3215, 141211

//	++, kutelf, 140801
//	RevD.01.01
//	RevD ���� �̷� ����� �߰�..
//	TW2835, TW8816 ȣȯ�ϱ� ���Ͽ� ����. 
//#define BoardVersion_RevA
//#define BoardVersion_RevB
//#define BoardVersion_RevC

// ++ , sys3215 141211
// revision ���� �߰��� ���� ���� 
//#define BoardVersion_RevD
// -- , sys3215 141211

//	--, kutelf, 140801

//#define     STM32_BUZZER      //  STM32 BUZZER

/* Private macro -------------------------------------------------------------*/
/*******************************************************************
*
*	Smart Key
*
*******************************************************************/

#define GET_VMC				0x00
#define GET_CPK				0x01
#define GET_VMC_CPK			0x02

#define TAG_LEVEL_NORMAL						0x00
#define TAG_LEVEL_MASTER_TAG					0x02

#define TAG_CMD_AUTHENTICATON				0x00
#define TAG_CMD_REGISTRATION					0x01
#define TAG_CMD_ELIMINATION					0x02
#define TAG_CMD_COMM_AUTHENTICATION			0x03

#define SMK_RESPONSE_CODE_AUTHENTICATION			0x00
#define SMK_RESPONSE_CODE_REGISTRATION				0x01
#define SMK_RESPONSE_CODE_ELIMINATION				0x02
#define SMK_RESPOSEN_CODE_COMM_AUTHENTICATION		0x03
#define SMK_RESPONSE_CODE_NOT_MATCH					0xFF

#define SMK_RESPONSE_FLAG_SUCCESS				0x00
#define SMK_RESPONSE_FLAG_FAIL					0x01
#define SMK_RESPONSE_FLAG_NO_TAG					0x02
#define SMK_RESPONSE_FLAG_NO_REGISTRATION		0x03
#define SMK_RESPONSE_FLAG_DUPLICATION_REG		0x04

/******************************************************************/


#define RETURN_VMC_OK				0x01
#define RETURN_VMC_NOT_OK			0x00

#define REQUEST_FIRST_AUTHENTICATION			0x00000001
#define REQUEST_SECOND_AUTHENTICATION		0x00000010
#define RESPONSE_AUTHENTICATION				0x00000100
#define RESPONSE_WAIT							0x00001000
#define RESPONSE_SUCCESS						0x00010000
#define RESPONSE_TIME_OUT						0x00100000

#define TIME_OUT_COUNT							5		// ++, --, 161021 bwk 20 -> 5 


#define SMK_SUCCESS				0xA5
#define SMK_FAIL				0xFE


#define SMK_MSG_TAG_FIRST_REG_SUCCESS		0x01
#define SMK_MSG_TAG_SECOND_REG_SUCCESS		0x02

#define SMK_MSG_TAG_NO_REALIZE				0x03
#define SMK_MSG_FAIL						0x04
#define SMK_MSG_TAG_ALREADY_REG				0x05

#define SMK_MSG_TAG_ELIMINATION_SUCCESS		0x06

#define SMK_MSG_TAG_THIRD_REG_SUCCESS		0x07
#define SMK_MSG_TAG_FOURTH_REG_SUCCESS		0x08
#define SMK_MSG_TAG_FIFTH_REG_SUCCESS		0x09
#define SMK_MSG_TAG_AUTHENTICATION			0x0a	// ++, --, 150707 bwk



#define	VersionCMD		0x05
#define	VersionRES		0x85

#define	StartCANCMD		0x09
#define	StartCANRES		0x89

#define	RTCCMD			0x03
#define	RTCRES			0x83

#define	SMKCMD			0x07
#define	SMKRES			0x87

#define	CANUPDATECMD	0x0A
#define	CANUPDATERES	0x8A

#define	OSUPDATECMD	0x0B
#define	OSUPDATERES	0x8B

#define	EEPROMTESTCMD 0x0C
#define	EEPROMTESTRES 0x8C

#define	FLASHTESTCMD	0x0D
#define	FLASHTESTRES	0x8D




#define	VERSION_HIGH			1
#define	VERSION_LOW			3
#define	VERSION_SUB_HIGH		1
#define	VERSION_SUB_LOW		0
#define	VERSION_HIDDEN		0
///////////////////////////////////////////////////
////1.0.1.0 (1.0.0.9���� 250kpbs�� CAN2 ����)
////1.0.1.1 (1.0.0.9���� ����, 500kbps) 2014.10.08
//Power Off�� Illumination Lamp Reset �ȵǴ� ���� ���� 2014.10.02
//Key Off/On ���� �ݺ� �� CAN ���ͷ�Ʈ �״� ���� ���� 2014.10.02
//OS Update CMD �߰�, OS Update CMD ���� �� 3�ʰ� LCD OFF 2014.10.06
//Key Off �� Outro���� Key On�� Ű��ư ���� �ȵǴ� ���� ���� 2014.10.06
//OS Update �� 20�ʰ� Key IG Check ���� (OS Boot Update�� ������ ������ �ȵ�) 	2014.10.06
////1.0.1.2
//KeyButton ���� �Է� ������ 250ms �߰� (Keybutton �Է� �� 250ms ���� Keybutton ������ ������ ���� 2014.10.16
////1.0.1.3 2014.11.21
//Hardware RevD �� ȣȯ�ڵ�� ���� !!!!!!!!!!!!!!!!!!!
//SmartKey ����(MCU ���) ���ø����̼ǿ��� �߿���� �̵� 2014.11.18
//SmartKey Use EEPROM�� ���� �� �ε� �߰� 2014.11.18
////1.0.1.4
// Camera Mode Change�Լ� Interrupt ��ƾ���� Main������ �̵� 2014.12.05
// Source Address �߰� (ACU, 0x19)
////1.0.1.5
// Revision ���� ADC �߰� 2014.12.12
// HardwareVersion ǥ�ø� ���� Revision ���� ADC �� ���ø����̼����� ������ �κ�  �߰�2014.12.12
////1.0.1.6
// Rear Wiper Long Key �ð� ���� (���� 4.5s -> 1.5s) 2014.12.31
// BKCU Source Address �߰� 2015.01.07
// SmartKey Tag ���� 5���� ���� 2014.01.07
////1.0.1.7
// Smart Key Response Flag 1 �� ��� ��� ���� �߰� 2015.01.14
// Power Off ���� Lamp Off �� ���� Off �߰� 2015.01.14
//// 1.0.1.8
// Hardware Test �� CMD �߰� (EEPROM, Serial Flash Test) 2015.01.20

//// 1.0.1.9
// RMCU ��� ���� key value add

//// 1.0.2.0
// can error reset ��� �߰� 
// CAM original view

//// 1.0.2.1 - 150407
// Power off siganl 100ms 

//// 1.0.2.2 - 150519
// CAM original view white line delete 

//// 1.0.2.3 - 150521
// Rear wiper up key event 

//// 1.0.2.4 - 150609
// CAM ��ȯ �� black -> Color ���� 
// CAM ��ȯ �� ȭ�� down -> up ���� 

//// 1.0.2.5 - 150625
// st update ��, system reset ��, jump_iap �߰� 

//// 1.0.2.41 - 150630(Test��)
// FW Hidden Version �߰�
// SmartKey -> Key Data Logging

//// 1.0.2.42 - 150630(�������)
// 1.0.2.5���ٰ� FW Hidden Version �߰�

//// 1.0.2.50 - 150707
// smart key ���� �䱸 �߰�
// CMD ring buffer ���� 

//// 1.0.2.51 - 150710 
// smart key ���� �䱸 ���� ����(���� Ȯ�� �ʿ�)
//  -> �±� ���� �ð� �ƴ϶� �ʱ� ������� �� ����Ʈ �±� ������ �޾ƾ� ��(���)
// -> ���� Ȯ�� �Ϸ� -> ������ SendSMKCountResult
// CMD SMK ��ȣȭ Ǯ�� �ڵ� �߰�(������) 

//// 1.0.2.60 - 150713
// smart key ������� �� ����ƮŰ �±� ���� �޾ƿ�

//// 1.0.2.61 - 150715
// 1. ī�޶� ���󳪿� �� ä�� ���� �� No signal ǥ�� �ʰ� ������� ���� ����
// 2. ī�޶� On->Off ������ �� ��� �ݿ��ȵǴ� ���� ����

//// 1.0.2.62 - 150812
// 1. HW ���� - 1.8V �и� , IAP ���� 
// 2. power off logic ���� 

//// 1.1.0.00 - 151013
// 1. CAN Update �� �ڵ����� �������� �ۺ�

//// 1.1.0.00 - 151231
// 1. Camera OSD ǥ�� ���� �߰�

//// 1.2.0.00 - 160406
// 1. CAN BITTIMING 
// 2. BKCU ������Ʈ ���� CAN RX �κ� ���� 

//// 1.3.0.00 - 160406
// 1. REV.H.01.01 ����
// 2. RTC ����, EEPROM ����
// 3. SMART KEY �� FLASH�� ����
// 4. WATCH DOG �߰�

//// 1.3.1.00 - 161021
// 1. ����ƮŰ retry ���� �߰�
// 2. SMART KEY �� ���� FLASH�� ����(h����)

///////////////////////////////////////////////////

//=================================================================

#pragma pack(1)
typedef struct
{
	u8 TagLevel:2;
	u8 TagCommand:4;
	u8 Reserved0:2;
	u8 Reserved1;
	u16 VMC;
	u32 CPK;
} WL9FM_send_smartkey;
#pragma pack()


#pragma pack(1)
typedef struct
{
	u8 ReturnTagLevel:2;
	u8 ReturnTagCommand:4;
	u8 ReturnReserved0:2;
	
	u8 ReturnReserved1;
	
	u16 ReturnVMC;	
	
	u8 Smk_Response_Code:4;
	u8 Smk_Response_Flag:4;
	
	u8 Registered_Tag_Count:4;
	u8 Reserved0:2;
	u8 TagLevel:2;
	
	u16 TagCRC16;
} WL9FM_receive_smartkey;
#pragma pack()


#pragma pack(1)
typedef struct
{
	u32 rand_cpk;
	u16 rand_vmc;
	u16 Reserved0;
} WL9FM_save_rand_value;
#pragma pack()


#pragma pack(1)
typedef struct
{
	u32 recv_resp_packet;
}WL9FM_flag_data;
#pragma pack()


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


void SendSMKAuthResult(u8 result);
void SendSMKCountResult();
void SendSMKMsgResult(u8 result);
void SetTagLevel(u8 level);
void SetTagCmd(u8 cmd);
void SetVMC(void);
void SetCPK(void);
void Srand();
void GetRandValue(u8 random);
void RequestFirstAuthentication(void);
void RequestSecondAuthentication(void);
void RequestSMKRegistration(void);
void RequestSMKElimination(void);
void RequestSMKMessage(u8 Msg);
void RequestSMKComm(void);
u8 CheckResponseVMC(void);
u8 CheckResponseAuthentication(u8 Auth);
void SmartKeyAuthentication(void);
void CheckResponseMsgComm(void);

void System_CheckPowerIG();
void SaveDataToEEPROM(void);
void SaveSMKUseToEEPROM(u8 Use);
u8 LoadSMKUseToEEPROM(void);
// ++, 160511 bwk
void SaveSMKUseToFlash(u8 Use);
u8 LoadSMKUseToFlash(void);
// --, 160511 bwk

void SaveTestToEEPROM(u8 Use);
u8 LoadTestToEEPROM(void);

/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern u8 stop_send_as_phone_data;

extern u8 tmpBuf[8];

extern u8 as_data_len;
extern u8 tmpbuf_AS[13];
extern u8 check_as_data_len;


extern u8 Uart2_RxMsg_AS_Phone_Data[8];
extern u8 Uart2_RxMsg_Smk_Reg_Eli[8];

extern u8 Uart2_RxMsg_Single_46[8];
extern u8 Uart2_RxMsg_Single_69[8];
extern u8 Uart2_RxMsg_Multi_69[21];
extern u8 Uart2_RxMsg_Single_160[8];
extern u8 Uart2_RxMsg_Multi_161[16];
extern u8 Uart2_RxMsg_Single_162[8];
extern u8 Uart2_RxMsg_Single_163[8];
extern u8 Uart2_RxMsg_Single_174[8];
extern u8 Uart2_RxMsg_Single_251[8];
extern u8 Uart2_RxMsg_Single_252[8];

extern u8 Uart2_RxMsg_Single_253[8];
extern u8 Uart2_RxMsg_Single_239[8];
extern u8 Uart2_RxMsg_Single_247[8];

//61184
extern u8 Uart2_RxMsg_Single_11[8];
extern u8 Uart2_RxMsg_Single_12[8];
extern u8 Uart2_RxMsg_Single_21[8];
extern u8 Uart2_RxMsg_Multi_23[13];
extern u8 Uart2_RxMsg_Single_61[8];
extern u8 Uart2_RxMsg_Single_62[8];
extern u8 Uart2_RxMsg_Single_101[8];
extern u8 Uart2_RxMsg_Single_104[8];
extern u8 Uart2_RxMsg_Single_105[8];
extern u8 Uart2_RxMsg_Single_109[8];
extern u8 Uart2_RxMsg_Single_121[8];
extern u8 Uart2_RxMsg_Single_123[8];
extern u8 Uart2_RxMsg_Single_201[8];
extern u8 Uart2_RxMsg_Single_203[8];
//0xFFxx
extern u8 Uart2_RxMsg_Single_47[8];
extern u8 Uart2_RxMsg_Multi_145[22];
extern u8 Uart2_RxMsg_Single_247[8];


extern u16 CommErrCnt;
extern u32 Flag_SerialRxMsg;
/* Exported functions ------------------------------------------------------- */
//  WL9F_Monitor_APP.c define
extern void Init_RTC(void);
extern void InitE2PROM(void);
extern void ReadE2PROM_ToSend(void);
extern void SendTo_E2PROM(void);

extern void WL9FM_Monitor_APP(void);
extern void WL9FM_1mSecOperationFunc(void);
extern void WL9FM_10mSecOperationFunc(void);
extern void WL9FM_100mSecOperationFunc(void);
extern void WL9FM_500mSecOperationFunc(void);
extern void WL9FM_1SecOperationFunc(void);
extern void WL9FM_System_Init_Start(void);

#if 0
extern void OperateRingBuffer(void);
#endif

extern void RTCSend(void);

//	++, kutelf, 140801
//	RevD.01.01
//	RevD ����� ȣȯ���� ���Ͽ� �Լ� �߰� �� �̸� ����
extern void CameraMode(u8 Mode, u8 OSD);
extern void CheckCamera_Input(u8 Mode);
//	--, kutelf, 140801

extern void Init_Smart_Key_valuable(void);

// ++ , 141118 sys3215
extern void ESL_System(void);
// --, 141118 sys3215

extern void JumpIAP(void);
#endif /* __WL9F_Monitor_APP_H */