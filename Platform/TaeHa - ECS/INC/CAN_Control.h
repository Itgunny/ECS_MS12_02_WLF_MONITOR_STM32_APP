/**
  ******************************************************************************
  * @file    CAN_Control.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for CAN_Control.c module
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
#ifndef __CAN_Control_H
#define __CAN_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_CAN_TX_DATA_SINGLE      255
#define MAX_CAN_TX_DATA_MULTI       4

#define CANCMD	0x50


#pragma pack(1)
struct st_CAN_Message1
{	
	unsigned char Priority;
	unsigned char PDU_Format;
	unsigned char PDU_Specific;
	unsigned char Source_Address;       

	unsigned char Data[8];   
};
#pragma pack()

struct st_CAN_Message_Ring_Buffer_Tx_Single
{
	unsigned char Head;
	unsigned char Tail;     

	struct st_CAN_Message1 Message[MAX_CAN_TX_DATA_SINGLE];   
};



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern u8 tp_cm_bam_TotPacketNum;
/* Exported functions ------------------------------------------------------- */
extern void CAN_COMInit(void);
extern void WL9F_CAN_Variables_Init(void);
extern void SetCanID(u8 PF, u8 PS, u8 Priority);
extern void CAN_TX_Data(u8* Data);
extern void SendTP_CM_BAM_MultiPacket_69(void);
extern void SendFirstMultiPacket_69(void);
extern void SendSecondMultiPacket_69(void);
extern void SendThirdMultiPacket_69(void);
extern void SendTP_CM_BAM_MultiPacket_161(void);
extern void SendMultiPacketData_161(u8 packet_no);
extern void SendTP_CM_BAM_MultiPacket_61184_23(void);
extern void SendMultiPacketData_61184_23(u8 packet_no);
extern void SendTP_CM_BAM_MultiPacket_145(void);
extern void SendMultiPacketData_145(u8 packet_no);
extern void Send_RTS_61184(u8* Arr);
extern void Send_CTS_61184(u8* Arr, u8 SA);
extern void Send_ACK_61184(u8* Arr, u8 SA);



extern void CheckASDataLen(void);
extern void SendTP_CM_BAM_MultiPacket_202_AS(void);
extern void SendMultiPacketData_202_AS(u8 packet_no);
extern void SendTP_CM_BAM_MultiPacket_MachInfo(void);
extern void SendMultiPacket_MachInfo(void);
extern void SendTP_CM_BAM_MultiPacket_MoniInfo(void);
extern void SendMultiPacket_MoniInfo(void);
extern void RequestMachBasicInfo(void);
extern void CompareMachBasicInfo(void);



extern void CAN_TX(void);
extern void MonitorStatus_CAN_TX(void);

extern void Write_CAN_Single(struct st_CAN_Message1 Message);

#endif /* __CAN_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
