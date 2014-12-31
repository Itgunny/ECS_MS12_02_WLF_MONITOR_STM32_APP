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
//	DPRAM 삭제 - FSMS 사용 안함. 
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
//	Camera Input, LCD Controller 변경
//		=> TW2835 + TW8832 -> TW8816
#include "TW8816_Control.h"
#include "TW8816_OSD.h"

//	RevD 이하 버젼에서 사용 
#include "TW2835_Control.h"
#include "TW2835_OSD.h"
#include "TW8832_Control.h"
#include "TW8832_OSD.h"
//	--, kutelf, 140801

#include "UART_Control.h"
#include "CAN_Control.h"
#include "M25PXX.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// ++, sys3215, 141211
#define REVB			0
#define REVD_02_01	1
// --, sys3215, 141211

//	++, kutelf, 140801
//	RevD.01.01
//	RevD 부터 이런 기능을 추가..
//	TW2835, TW8816 호환하기 위하여 수정. 
//#define BoardVersion_RevA
//#define BoardVersion_RevB
//#define BoardVersion_RevC

// ++ , sys3215 141211
// revision 저항 추가로 인한 삭제 
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

#define TIME_OUT_COUNT							20


#define SMK_SUCCESS				0xA5
#define SMK_FAIL				0xFE


#define SMK_MSG_TAG_FIRST_REG_SUCCESS		0x01
#define SMK_MSG_TAG_SECOND_REG_SUCCESS		0x02

#define SMK_MSG_TAG_NO_REALIZE				0x03
#define SMK_MSG_FAIL							0x04
#define SMK_MSG_TAG_ALREADY_REG				0x05

#define SMK_MSG_TAG_ELIMINATION_SUCCESS		0x06


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



#define	VERSION_HIGH		1
#define	VERSION_LOW			0
#define	VERSION_SUB_HIGH	1
#define	VERSION_SUB_LOW		6

///////////////////////////////////////////////////
////1.0.1.0 (1.0.0.9에서 250kpbs로 CAN2 수정)
////1.0.1.1 (1.0.0.9에서 수정, 500kbps) 2014.10.08
//Power Off시 Illumination Lamp Reset 안되는 문제 수정 2014.10.02
//Key Off/On 순간 반복 시 CAN 인터럽트 죽는 현상 수정 2014.10.02
//OS Update CMD 추가, OS Update CMD 수신 시 3초간 LCD OFF 2014.10.06
//Key Off 후 Outro에서 Key On시 키버튼 동작 안되는 문제 수정 2014.10.06
//OS Update 시 20초간 Key IG Check 안함 (OS Boot Update시 전원이 나가면 안됨) 	2014.10.06
////1.0.1.2
//KeyButton 연속 입력 딜레이 250ms 추가 (Keybutton 입력 후 250ms 동안 Keybutton 데이터 나가지 않음 2014.10.16
////1.0.1.3 2014.11.21
//Hardware RevD 와 호환코드로 수정 !!!!!!!!!!!!!!!!!!!
//SmartKey 인증(MCU 통신) 어플리케이션에서 펌웨어로 이동 2014.11.18
//SmartKey Use EEPROM에 저장 및 로딩 추가 2014.11.18
////1.0.1.4
// Camera Mode Change함수 Interrupt 루틴에서 Main문으로 이동 2014.12.05
// Source Address 추가 (ACU, 0x19)
////1.0.1.5
// Revision 저항 ADC 추가 2014.12.12
// HardwareVersion 표시를 위한 Revision 저항 ADC 값 어플리케이션으로 보내는 부분  추가2014.12.12
////1.0.1.6
// Rear Wiper Long Key 시간 단축 (기존 4.5s -> 1.5s) 2014.12.31
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
extern void OperateRingBuffer(void);
extern void RTCSend(void);

//	++, kutelf, 140801
//	RevD.01.01
//	RevD 보드와 호환성을 위하여 함수 추가 및 이름 변경
extern void CameraMode(u8 Mode, u8 OSD);
extern void CheckCamera_Input(u8 Mode);
//	--, kutelf, 140801

extern void Init_Smart_Key_valuable(void);

// ++ , 141118 sys3215
extern void ESL_System(void);
// --, 141118 sys3215

#endif /* __WL9F_Monitor_APP_H */
