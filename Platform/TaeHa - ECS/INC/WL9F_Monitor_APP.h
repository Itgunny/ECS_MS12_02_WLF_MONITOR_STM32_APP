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
#define	VERSION_LOW			4
#define	VERSION_SUB_HIGH		0
#define	VERSION_SUB_LOW		1
#define	VERSION_HIDDEN		0
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
// BKCU Source Address 추가 2015.01.07
// SmartKey Tag 갯수 5개로 증가 2014.01.07
////1.0.1.7
// Smart Key Response Flag 1 인 경우 등록 실패 추가 2015.01.14
// Power Off 로직 Lamp Off 및 부저 Off 추가 2015.01.14
//// 1.0.1.8
// Hardware Test 용 CMD 추가 (EEPROM, Serial Flash Test) 2015.01.20

//// 1.0.1.9
// RMCU 통신 관련 key value add

//// 1.0.2.0
// can error reset 기능 추가 
// CAM original view

//// 1.0.2.1 - 150407
// Power off siganl 100ms 

//// 1.0.2.2 - 150519
// CAM original view white line delete 

//// 1.0.2.3 - 150521
// Rear wiper up key event 

//// 1.0.2.4 - 150609
// CAM 전환 시 black -> Color 수정 
// CAM 전환 시 화면 down -> up 수정 

//// 1.0.2.5 - 150625
// st update 후, system reset 시, jump_iap 추가 

//// 1.0.2.41 - 150630(Test용)
// FW Hidden Version 추가
// SmartKey -> Key Data Logging

//// 1.0.2.42 - 150630(양산적용)
// 1.0.2.5에다가 FW Hidden Version 추가

//// 1.0.2.50 - 150707
// smart key 인증 요구 추가
// CMD ring buffer 구현 

//// 1.0.2.51 - 150710 
// smart key 인증 요구 응답 구현(실차 확인 필요)
//  -> 태그 인증 시가 아니라 초기 통신인증 시 스마트 태그 개수를 받아야 함(경우)
// -> 실차 확인 완료 -> 미적용 SendSMKCountResult
// CMD SMK 암호화 풀린 코드 추가(디버깅용) 

//// 1.0.2.60 - 150713
// smart key 통신인증 시 스마트키 태그 개수 받아옴

//// 1.0.2.61 - 150715
// 1. 카메라 영상나올 때 채널 변경 시 No signal 표시 늦게 사라지는 현상 개선
// 2. 카메라 On->Off 빠르게 줄 경우 반영안되는 현상 개선

//// 1.0.2.62 - 150812
// 1. HW 변경 - 1.8V 분리 , IAP 수정 
// 2. power off logic 변경 

//// 1.1.0.00 - 151013
// 1. CAN Update 시 자동정지 프로토콜 송부

//// 1.1.0.00 - 151231
// 1. Camera OSD 표시 문구 추가

//// 1.2.0.00 - 160406
// 1. CAN BITTIMING 
// 2. BKCU 업데이트 관련 CAN RX 부분 수정 

//// 1.3.0.00 - 160406
// 1. REV.H.01.01 적용
// 2. RTC 변경, EEPROM 삭제
// 3. SMART KEY 값 FLASH에 저장
// 4. WATCH DOG 추가

//// 1.3.1.00 - 161021
// 1. ����ƮŰ retry ���� �߰�
// 2. SMART KEY �� ���� FLASH�� ����(h����)

//// 1.3.2.0 - 170123
// 1. H���� ��� ����Ʈ���� ���� ����

//// 1.3.2.0.1 - 170410
// 1. RTC : �ð� �ʱ�ȭ �� �帣�� �ʴ� ���� ����(ADC Value : 1087 -> 1050)


//// 1.3.2.1 - 170515
// 1. ī�޶� CH4 <-> CH1 ����(���� Diff Camera ��û ��)

//// 1.4.0.00 - 160830
// 1. AAVM 사양 추가 
// 2. SmartKey Rx 무응답 시 200ms 5회 Retry 추가 
// 3. cpk 최초 1회 생성 후 변경하지 않음


//// 1.4.0.10 - 161012
// 1. AAVM 관련 이미지 폰트 변경

//// 1.4.0.20 - 161017
// 1. AAVM 관련 카메라 깜박임 현상 수정
// 2. AAVM 관련 CH4로 고정

//// 1.4.0.30 - 161027
// 1. NO SiGNAL 현상 수정
// 2. SMARKEY 에러 수정 : Serial Flash 관련
// 3. AAVM ICON 깜박임 OSD 추가

//// 1.4.0.01 - 171018
// 1. AAVM 가이드라인 추가
// 2. ADC VALUE 5번 체크
// 3. AAVM 가이드라인 버튼 추가
// 4. RTC 루틴 변경(F 굴삭기와 동일하게 변경)

//// 1.4.0.10 - 171211
// 1. AAVM NOSIGNAL 현상 개선

//// 1.5.0.00 - 171221
// 1. SKCU Source Address 추가
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
//	RevD 보드와 호환성을 위하여 함수 추가 및 이름 변경
extern void CameraMode(u8 Mode, u8 OSD);
extern void CheckCamera_Input(u8 Mode);
//	--, kutelf, 140801

extern void AAVMMode(u8 Mode, u8 OSD);
extern void CheckAAVM_Input(u8 Mode);


extern void Init_Smart_Key_valuable(void);

// ++ , 141118 sys3215
extern void ESL_System(void);
// --, 141118 sys3215

extern void JumpIAP(void);
#endif /* __WL9F_Monitor_APP_H */
