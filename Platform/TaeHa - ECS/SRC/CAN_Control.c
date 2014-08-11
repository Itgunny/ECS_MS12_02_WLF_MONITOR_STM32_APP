/**
  ******************************************************************************
  * @file    UART_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   UART_Control.c module
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
#pragma pack(1)
struct st_CAN_Message
{	
	unsigned char Priority;
	unsigned char Data_Page;
	unsigned char PDU_Format;	
	unsigned char PDU_Specific;		// 50
	unsigned char Source_Address;	// 52
};
#pragma pack()


#pragma pack(1)
typedef struct
{
	u8 Control;
	u16 TotMsgSize;
	u8 TotPacketNum;
	u8 Reserved;
	u16 pgn_low;
	u8 pgn_high;
} TP_CM;
#pragma pack()



struct st_CAN_Message Identifier;
TP_CM* tp_cm_bam;

/* Private define ------------------------------------------------------------*/

/*
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

#define RX_MSG174		0x2000
#define RX_MSG239_121	0x4000
*/
#define RX_MSG11	0x01
#define RX_MSG12	0x02
#define RX_MSG21	0x04
#define RX_MSG23	0x08
#define RX_MSG61	0x10
#define RX_MSG62	0x20
#define RX_MSG101	0x40
#define RX_MSG104	0x80
#define RX_MSG105	0x100
#define RX_MSG109	0x200
#define RX_MSG121	0x400
#define RX_MSG123	0x800
#define RX_MSG201	0x1000
#define RX_MSG203	0x2000
	
	
#define RX_MSG47	0x4000
	
#define RX_MSG145	0x8000
#define RX_MSG247	0x10000

struct st_CAN_Message_Ring_Buffer_Tx_Single CAN_Message_Ring_Buffer_Tx_Single;
struct st_CAN_Message_Ring_Buffer_Rx_Single CAN_Message_Ring_Buffer_Rx_Single;

#define UART2_Tx_BUF_SIZE		17
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 tmpBuf[8];

u8 as_data_len;
u8 tmpbuf_AS[13];
u8 check_as_data_len = 0;


u8 Uart2_RxMsg_Save_Data1[8];
u8 Uart2_RxMsg_Save_Data2[8];
u8 Uart2_RxMsg_AS_Phone_Data[8];
u8 Uart2_RxMsg_Smk_Reg_Eli[8];

u8 Uart2_RxMsg_Single_46[8];
u8 Uart2_RxMsg_Single_69[8];
u8 Uart2_RxMsg_Multi_69[21];
u8 Uart2_RxMsg_Single_160[8];
u8 Uart2_RxMsg_Multi_161[16];
u8 Uart2_RxMsg_Single_162[8];
u8 Uart2_RxMsg_Single_163[8];
u8 Uart2_RxMsg_Single_174[8];
u8 Uart2_RxMsg_Single_251[8];
u8 Uart2_RxMsg_Single_252[8];
u8 Uart2_RxMsg_Single_253[8];
u8 Uart2_RxMsg_Single_239[8];
u8 Uart2_RxMsg_Single_247[8];
u8 Uart2_RxMsg_Single_239_121[8];

//61184
u8 Uart2_RxMsg_Single_11[8];
u8 Uart2_RxMsg_Single_12[8];
u8 Uart2_RxMsg_Single_21[8];
u8 Uart2_RxMsg_Multi_23[13];
u8 Uart2_RxMsg_Single_61[8];
u8 Uart2_RxMsg_Single_62[8];
u8 Uart2_RxMsg_Single_101[8];
u8 Uart2_RxMsg_Single_104[8];
u8 Uart2_RxMsg_Single_105[8];
u8 Uart2_RxMsg_Single_109[8];
u8 Uart2_RxMsg_Single_121[8];
u8 Uart2_RxMsg_Single_123[8];
u8 Uart2_RxMsg_Single_201[8];
u8 Uart2_RxMsg_Single_203[8];
//0xFFxx
u8 Uart2_RxMsg_Single_47[8];
u8 Uart2_RxMsg_Multi_145[22];
u8 Uart2_RxMsg_Single_247[8];



u8 McuInfoData1[79];
u8 MachineBasicInformation[78];
u8 tmpMcuInfoData[78];


u8 T_Packet_No = 0;
u8 flag_skip_multi_packet = 0;
u8 RecvMachInfo = 0;
u8 TotalRequestCnt = 0;
u8 CompareAsterisk = 0;

u32 Flag_SerialRxMsg = 0;
u8 tp_cm_bam_TotPacketNum = 0;

extern u8 CanRecvCnt;
extern u16 TotMsgSize;

extern u16 Flag_1Sec_MachInfo;
extern u8 MachInfoTotalPacketNum;
extern u8 MoniInfoTotalPacketNum;
extern u8 MachInfoSendCnt;
extern u8 MoniInfoSendCnt;
extern u8 MultiPacketSendOrder;
extern u8 MoniInfoData[21];
extern u8 DiffMachInfo;
extern u8 SerialMsgRTC[16];
extern u8 RTSFlag_61184;
extern u8 CTSFlag_61184;
extern u8 RecvTotalPacket_61184;
extern u8 ACK_Multi_61184[8];
extern u8 RMCU_CTSFlag_61184;
extern u8 RMCU_RecvTotalPacket_61184;
extern u8 RMCU_ACK_Multi_61184[8];


extern u8 Uart2_SerialTxMsg[UART2_Tx_BUF_SIZE];
extern Realy_Control rx_Realy_Control;
extern EHCU_Status rx_EHCU_Status;

extern unsigned long long SerialTXIndex;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  CAN1, CAN2 Initialize 
  * @param  
  * @retval None
  */
void CAN_COMInit(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef        NVIC_InitStructure;

	DebugMsg_printf("++ CAN1, CAN2 Initialize START\r\n");

	CAN_DeInit(CAN1);
	CAN_DeInit(CAN2);
	CAN_StructInit(&CAN_InitStructure);

	CAN_InitStructure.CAN_TTCM = DISABLE;
	//CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_6tq;  
	CAN_InitStructure.CAN_Prescaler = 8;   // 2:1M, 4:500k, 8:250k. 16:125k
	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_Init(CAN2, &CAN_InitStructure);

	//CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	//CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	// 부팅시 EEPROM Data를 Main CPU에 올리고 나서 ENABLE시킨다.
	//CAN_ITConfig(CAN_IT_FMP0, ENABLE);		

	//  Enable the CAN1_RX0_IRQn  Interrupt
	NVIC_InitStructure.NVIC_IRQChannel                   = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	
	//CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);		
	
    DebugMsg_printf("++ CAN1, CAN2 Initialize END\r\n");
}




void WL9F_CAN_Variables_Init(void)
{
	check_as_data_len = 0;
	Flag_SerialRxMsg = 0;

	Identifier.Priority = 6;
	Identifier.Data_Page = 0;
	Identifier.PDU_Format = 255;	
	Identifier.Source_Address = 40;		

	flag_skip_multi_packet = 0;
	TotMsgSize = 0;
	RecvMachInfo = 0;
	TotalRequestCnt = 0;
	CompareAsterisk = 0;
	CanRecvCnt = 0;



	tp_cm_bam = (TP_CM*)&tmpBuf[0];
	
	memset((u8*)&Uart2_RxMsg_Save_Data1[0], 0xff, sizeof(Uart2_RxMsg_Save_Data1));
	memset((u8*)&Uart2_RxMsg_Save_Data2[0], 0xff, sizeof(Uart2_RxMsg_Save_Data2));
	memset((u8*)&Uart2_RxMsg_AS_Phone_Data[0], 0xff, sizeof(Uart2_RxMsg_AS_Phone_Data));
	memset((u8*)&Uart2_RxMsg_Smk_Reg_Eli[0], 0xff, sizeof(Uart2_RxMsg_Smk_Reg_Eli));	
	memset((u8*)&Uart2_RxMsg_Single_46[0], 0xff, sizeof(Uart2_RxMsg_Single_46));
	memset((u8*)&Uart2_RxMsg_Single_69[0], 0xff, sizeof(Uart2_RxMsg_Single_69));
	memset((u8*)&Uart2_RxMsg_Single_160[0], 0xff, sizeof(Uart2_RxMsg_Single_160));
	memset((u8*)&Uart2_RxMsg_Single_162[0], 0xff, sizeof(Uart2_RxMsg_Single_162));
	Uart2_RxMsg_Single_162[4] = 0;		// Monitor Switch Status
	memset((u8*)&Uart2_RxMsg_Single_163[0], 0xff, sizeof(Uart2_RxMsg_Single_163));
	memset((u8*)&Uart2_RxMsg_Single_174[0], 0xff, sizeof(Uart2_RxMsg_Single_174));
	memset((u8*)&Uart2_RxMsg_Single_251[0], 0xff, sizeof(Uart2_RxMsg_Single_251));
	memset((u8*)&Uart2_RxMsg_Single_252[0], 0xff, sizeof(Uart2_RxMsg_Single_252));
	memset((u8*)&Uart2_RxMsg_Single_253[0], 0xff, sizeof(Uart2_RxMsg_Single_253));

	memset((u8*)&Uart2_RxMsg_Single_239[0], 0xff, sizeof(Uart2_RxMsg_Single_239));

	memset((u8*)&Uart2_RxMsg_Single_239_121[0], 0xff, sizeof(Uart2_RxMsg_Single_239_121));

	
	memset((u8*)&Uart2_RxMsg_Single_247[0], 0xff, sizeof(Uart2_RxMsg_Single_247));

	
	memset((u8*)&Uart2_RxMsg_Multi_161[0], 0xff, sizeof(Uart2_RxMsg_Multi_161));
	memset((u8*)&Uart2_RxMsg_Multi_69[0], 0xff, sizeof(Uart2_RxMsg_Multi_69));




	memset((u8*)&Uart2_RxMsg_Single_11[0], 0xff, sizeof(Uart2_RxMsg_Single_11));
	memset((u8*)&Uart2_RxMsg_Single_12[0], 0xff, sizeof(Uart2_RxMsg_Multi_69));
	memset((u8*)&Uart2_RxMsg_Single_21[0], 0xff, sizeof(Uart2_RxMsg_Single_21));
	memset((u8*)&Uart2_RxMsg_Multi_23[0], 0xff, sizeof(Uart2_RxMsg_Multi_23));
	memset((u8*)&Uart2_RxMsg_Single_61[0], 0xff, sizeof(Uart2_RxMsg_Single_61));
	memset((u8*)&Uart2_RxMsg_Single_62[0], 0xff, sizeof(Uart2_RxMsg_Single_62));
	memset((u8*)&Uart2_RxMsg_Single_101[0], 0xff, sizeof(Uart2_RxMsg_Single_101));
	memset((u8*)&Uart2_RxMsg_Single_104[0], 0xff, sizeof(Uart2_RxMsg_Single_104));
	memset((u8*)&Uart2_RxMsg_Single_105[0], 0xff, sizeof(Uart2_RxMsg_Single_105));
	memset((u8*)&Uart2_RxMsg_Single_109[0], 0xff, sizeof(Uart2_RxMsg_Single_109));
	memset((u8*)&Uart2_RxMsg_Single_121[0], 0xff, sizeof(Uart2_RxMsg_Single_121));
	memset((u8*)&Uart2_RxMsg_Single_123[0], 0xff, sizeof(Uart2_RxMsg_Single_123));
	memset((u8*)&Uart2_RxMsg_Single_201[0], 0xff, sizeof(Uart2_RxMsg_Single_201));
	memset((u8*)&Uart2_RxMsg_Single_203[0], 0xff, sizeof(Uart2_RxMsg_Single_203));
	memset((u8*)&Uart2_RxMsg_Single_47[0], 0xff, sizeof(Uart2_RxMsg_Single_47));
	memset((u8*)&Uart2_RxMsg_Multi_145[0], 0xff, sizeof(Uart2_RxMsg_Multi_145));
	memset((u8*)&Uart2_RxMsg_Single_247[0], 0xff, sizeof(Uart2_RxMsg_Single_247));



	memset((u8*)&rx_Realy_Control, 0xff, sizeof(rx_Realy_Control));


	memset((u8*)&SerialMsgRTC[0], 0xA5, 2);
	memset((u8*)&SerialMsgRTC[2], 0xF0, 2);
}

u8 can_data_temp[255];
u8 old_can_data;

void Write_CAN_Single(struct st_CAN_Message1 Message)
{
	if(Message.PDU_Specific != 47)  // 비주기 테이터 
	{
		memcpy(&CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Head],&Message,12);
		
		if (++(CAN_Message_Ring_Buffer_Tx_Single.Head) >= MAX_CAN_TX_DATA_SINGLE)
			CAN_Message_Ring_Buffer_Tx_Single.Head = 0;
	}
	else  // 주기 데이터  PS = 47
	{
		if(Message.PDU_Specific == 47)
			memcpy(&Uart2_RxMsg_Single_47,&Message.Data,8);
	}
}

void Write_UART_Single(void)
{
	static unsigned short Tx_Rountine_Count_UART;

	/*
	if((++Tx_Rountine_Count_UART%3)==0)
	{
		Tx_Rountine_Count_UART = 0;
		if (CAN_Message_Ring_Buffer_Rx_Single.Head != CAN_Message_Ring_Buffer_Rx_Single.Tail)
		{
			int i;
			u8 UARTTxMessage[17];
			memcpy(&UARTTxMessage[0],(u8*)&CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Tail],17);
			for(i = 0; i < 17; i++)
				USARTx_PutChar(2,(uint8_t)UARTTxMessage[i]);
			//	USART_SendData(USART2, UARTTxMessage[i]);	 
 			
			SerialTXIndex++;
			if (++(CAN_Message_Ring_Buffer_Rx_Single.Tail) >= MAX_CAN_RX_DATA_SINGLE)
				CAN_Message_Ring_Buffer_Rx_Single.Tail = 0;
		}

	}
	*/

	if((++Tx_Rountine_Count_UART%3)==0)
	{
		Tx_Rountine_Count_UART = 0;
		if (CAN_Message_Ring_Buffer_Rx_Single.Head != CAN_Message_Ring_Buffer_Rx_Single.Tail)
		{
			int i;
			//u8 UARTTxMessage[17];

			DMA_UART_SendFrame(&Uart2_SerialTxMsg[0],(u8*)&CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Tail],17);
			
			SerialTXIndex++;
			if (++(CAN_Message_Ring_Buffer_Rx_Single.Tail) >= MAX_CAN_RX_DATA_SINGLE)
				CAN_Message_Ring_Buffer_Rx_Single.Tail = 0;
		}

	}

}


void SetCanID(u8 PF, u8 PS, u8 Priority)
{
	if(PF != 0)
		Identifier.PDU_Format = PF;	

	if(PS != 0)
		Identifier.PDU_Specific = PS;	

	if(Priority != 0)
		Identifier.Priority = Priority;	
}

void CAN_TX_Data(u8* Data)
{
	//u8 TransmitMailbox;
	CanTxMsg TxMessage;
	
	TxMessage.ExtId=((unsigned long)(Identifier.Priority) << 26)+((unsigned long)(Identifier.Data_Page) << 24)+((unsigned long)(Identifier.PDU_Format) << 16)
				                      + ((unsigned long)(Identifier.PDU_Specific) << 8) + ((unsigned long)(Identifier.Source_Address) << 0) ;
			
	TxMessage.IDE = CAN_ID_EXT;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	memcpy((u8*)&TxMessage.Data[0], (u8*)&Data[0], 8);

	
	CAN_Transmit(CAN1,&TxMessage);
}
u8 can_status;
u8 can_status_buf[100];
u8 can_tx_error_count;

void CAN_TX(void)
{
	CanTxMsg TxMessage;
	unsigned char i;
	static unsigned short Tx_Rountine_Count_CAN;

	
	if((++Tx_Rountine_Count_CAN%2)==0)
	{
		if (CAN_Message_Ring_Buffer_Tx_Single.Head != CAN_Message_Ring_Buffer_Tx_Single.Tail)
		{
			
			TxMessage.ExtId = (CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Tail].Priority<<24)+
							(CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Tail].PDU_Format<<16)+
							(CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Tail].PDU_Specific<<8)+
							CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Tail].Source_Address;
			TxMessage.IDE = CAN_ID_EXT;
			TxMessage.RTR = CAN_RTR_DATA;
			TxMessage.DLC = 8;

			
			for (i = 0; i < 8; i++)
			{
				TxMessage.Data[i] = CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Tail].Data[i];
			}

			can_status = CAN_Transmit(CAN1,&TxMessage);
			

							
			if(can_status !=CAN_TxStatus_NoMailBox)
			{
				if (++(CAN_Message_Ring_Buffer_Tx_Single.Tail) >= MAX_CAN_TX_DATA_SINGLE)
					CAN_Message_Ring_Buffer_Tx_Single.Tail = 0;
			}
			else
			{
				can_status_buf[can_tx_error_count++] = can_status;
				if(can_tx_error_count>100)	can_tx_error_count=0;
			}


		}
		
	}


	 //if(Tx_Rountine_Count_CAN++ > 500)
	 //{
	//		Tx_Rountine_Count_CAN = 0;
	 //}
       	
}

void CAN_RX(CanRxMsg RxMessage)
{
	
	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_STX = 0x02;
	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_ID = 0xF5;
	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_LEN = 0x08;
	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_SAVE_DATA = 0x00;
	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_ETX = 0x03;

	CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].Rx_ExtID = RxMessage.ExtId;

	memcpy(&CAN_Message_Ring_Buffer_Rx_Single.Message[CAN_Message_Ring_Buffer_Rx_Single.Head].RX_DATA[0],&RxMessage.Data[0],8);
		
	
	if (++(CAN_Message_Ring_Buffer_Rx_Single.Head) >= MAX_CAN_RX_DATA_SINGLE)
		CAN_Message_Ring_Buffer_Rx_Single.Head = 0;

	
}
void MonitorStatus_CAN_TX(void)
{
	struct st_CAN_Message1 Send_Message;


	Send_Message.Priority = 0x18;
	Send_Message.PDU_Format = 0xFF;		// 255
	Send_Message.PDU_Specific = 0x2F;	// 47
	Send_Message.Source_Address = 0x28;
	memcpy(&Send_Message.Data,&Uart2_RxMsg_Single_47,8);
	memcpy(&CAN_Message_Ring_Buffer_Tx_Single.Message[CAN_Message_Ring_Buffer_Tx_Single.Head],&Send_Message,12);

	if (++(CAN_Message_Ring_Buffer_Tx_Single.Head) >= MAX_CAN_TX_DATA_SINGLE)
		CAN_Message_Ring_Buffer_Tx_Single.Head = 0;
	//if( (Uart2_RxMsg_Single_47[4] & 0x10 ) == 0x10 )
	//{
	//	if( WL9FM_BUZZER.Status == 0 )
	//		Uart2_RxMsg_Single_47[4] = Uart2_RxMsg_Single_47[4] & 0xCF;
	//}
}



void SendTP_CM_BAM_MultiPacket_161(void)
{
	// TP.CM_BAM
	SetCanID(236, 255, 7);

	tp_cm_bam->Control = 32;	// Control Byte
	
	tp_cm_bam->TotMsgSize = 10;

	tp_cm_bam->TotPacketNum = 2;
	tp_cm_bam_TotPacketNum = tp_cm_bam->TotPacketNum;

	tp_cm_bam->Reserved = 0xff;

	tp_cm_bam->pgn_low = 0xFFA1;
	tp_cm_bam->pgn_high = 0;

	CAN_TX_Data(&tmpBuf[0]);
}

void SendMultiPacketData_161(u8 packet_no)
{
	u8 tmpBuf1[8];
	
	SetCanID(235, 255, 7);

	tmpBuf1[0] = packet_no;
	memcpy(&tmpBuf1[1], &Uart2_RxMsg_Multi_161[(packet_no-1)*7], 7);
	CAN_TX_Data(&tmpBuf1[0]);
}

void SendTP_CM_BAM_MultiPacket_61184_23(void)
{
	// TP.CM_BAM
	SetCanID(236, 71, 7);

	tp_cm_bam->Control = 16;	// Control Byte
	
	tp_cm_bam->TotMsgSize = 13;

	tp_cm_bam->TotPacketNum = 2;
	tp_cm_bam_TotPacketNum = tp_cm_bam->TotPacketNum;

	tp_cm_bam->Reserved = 0xff;

	tp_cm_bam->pgn_low = 0xEF00;
	tp_cm_bam->pgn_high = 00;

	CAN_TX_Data(&tmpBuf[0]);

}
void SendMultiPacketData_61184_23(u8 packet_no)
{
	u8 tmpBuf1[8];
	
	SetCanID(235, 71, 7);

	tmpBuf1[0] = packet_no;
	memcpy(&tmpBuf1[1], &Uart2_RxMsg_Multi_23[(packet_no-1)*7], 7);
	CAN_TX_Data(&tmpBuf1[0]);

}
void SendTP_CM_BAM_MultiPacket_145(void)
{
	int Asterisk = 0;
	for(int i = 0; i < 22; i++)
	{
		if(Uart2_RxMsg_Multi_145[i] == 0x2A)
		{
			break;
		}
		else
		{
			Asterisk++;
		}
	}
	// TP.CM_BAM
	SetCanID(236, 255, 7);

	tp_cm_bam->Control = 32;	// Control Byte
	
	tp_cm_bam->TotMsgSize = Asterisk + 1;

	if((tp_cm_bam->TotMsgSize % 7) == 0)
	{
		tp_cm_bam->TotPacketNum = tp_cm_bam->TotMsgSize / 7;
	}
	else
	{
		tp_cm_bam->TotPacketNum = (tp_cm_bam->TotMsgSize / 7) + 1;
	}

	tp_cm_bam_TotPacketNum = tp_cm_bam->TotPacketNum;

	tp_cm_bam->Reserved = 0xff;

	tp_cm_bam->pgn_low = 0xFF91;
	tp_cm_bam->pgn_high = 0;

	CAN_TX_Data(&tmpBuf[0]);
}
void SendMultiPacketData_145(u8 packet_no)
{
	u8 tmpBuf1[8];
	
	SetCanID(235, 255, 7);

	tmpBuf1[0] = packet_no;
	memcpy(&tmpBuf1[1], &Uart2_RxMsg_Multi_145[(packet_no-1)*7], 7);
	CAN_TX_Data(&tmpBuf1[0]);
}

void Send_CTS_61184(u8* Arr, u8 SA)
{
	SetCanID(236, SA, 7);
	tmpBuf[0] = 17;	// Control Byte;l
	tmpBuf[1] = Arr[3];
	tmpBuf[2] = 1;
	tmpBuf[3] = 0xFF;
	tmpBuf[4] = 0xFF;
	tmpBuf[5] = Arr[5];
	tmpBuf[6] = Arr[6];
	tmpBuf[7] = Arr[7];

	CAN_TX_Data(&tmpBuf[0]);
	
}

void Send_ACK_61184(u8* Arr, u8 SA)
{
	SetCanID(236, SA, 7);
	tmpBuf[0] = 19;	// Control Byte;l
	tmpBuf[1] = Arr[1];
	tmpBuf[2] = Arr[2];
	tmpBuf[3] = Arr[3];
	tmpBuf[4] = Arr[4];
	tmpBuf[5] = Arr[5];
	tmpBuf[6] = Arr[6];
	tmpBuf[7] = Arr[7];

	CAN_TX_Data(&tmpBuf[0]);
}

void CheckASDataLen(void)
{
	u8 i;

	as_data_len = 0;
	memset((u8*)&tmpbuf_AS[0], 0x2A, 13);

	for(i = 0 ; i < 12 ; i+=2)
	{
		tmpbuf_AS[i] = Uart2_RxMsg_AS_Phone_Data[i/2] & 0x0F;
		tmpbuf_AS[i+1] = (Uart2_RxMsg_AS_Phone_Data[i/2] & 0xF0) >> 4;
	}


	for(i = 0 ; i < 12 ; i++)
	{
		if(tmpbuf_AS[i] != 0x0F)
		{
			tmpbuf_AS[i] += 0x30;
			as_data_len++;
		}
		else
		{
			tmpbuf_AS[i] = 0x2A;
			break;
		}
		
	}

	check_as_data_len = 1;
}

void SendTP_CM_BAM_MultiPacket_202_AS(void)
{
	// TP.CM_BAM
	SetCanID(236, 255, 7);

	tp_cm_bam->Control = 32;	// Control Byte
	
	tp_cm_bam->TotMsgSize = as_data_len;

	tp_cm_bam->TotPacketNum = 2;
	tp_cm_bam_TotPacketNum = tp_cm_bam->TotPacketNum;

	tp_cm_bam->Reserved = 0xff;

	//tp_cm_bam->pgn_low = 0xEC00;
	tp_cm_bam->pgn_low = 0xFF91;
	tp_cm_bam->pgn_high = 0;

	CAN_TX_Data(&tmpBuf[0]);
}

void SendMultiPacketData_202_AS(u8 packet_no)
{
	u8 tmpBuf1[8];
	
	SetCanID(235, 255, 7);

	tmpBuf1[0] = packet_no;
	memcpy(&tmpBuf1[1], &tmpbuf_AS[(packet_no-1)*7], 7);
	CAN_TX_Data(&tmpBuf1[0]);
}

void RequestMachBasicInfo(void)
{
	u8 Request[8];

	SetCanID(255, 251, 6);
	
	if(RecvMachInfo != 1)
	{
		if(++TotalRequestCnt <= 10)
		{
			Request[0] = 60;		// PS
			Request[1] = 255;		// PF
			CAN_TX_Data(&Request[0]);
		}
	}
}

void CompareMachBasicInfo(void)
{
	u8 i;

	if((RecvMachInfo == 1) && (DiffMachInfo == 0))
	{
		for(i = 0 ; i < TotMsgSize ; i++)
		{
			if(McuInfoData1[i+1] != MachineBasicInformation[i])
			{
				memcpy(&McuInfoData1[1] , &MachineBasicInformation[0], TotMsgSize);

				
				if(McuInfoData1[0] == 0xff)
					McuInfoData1[0] = 0;
				else
					McuInfoData1[0] += 1;

				tmpMcuInfoData[0] = McuInfoData1[0];
				
				switch(tmpMcuInfoData[0])
				{
					case 0 :
						memcpy(&tmpMcuInfoData[1] , &McuInfoData1[1], 4);	
						memset(&tmpMcuInfoData[5] , 0xff, 12);
						break;
					case 1 :
						memcpy(&tmpMcuInfoData[5] , &tmpMcuInfoData[1], 4);		
						memcpy(&tmpMcuInfoData[1] , &McuInfoData1[1], 4);	
						memset(&tmpMcuInfoData[9] , 0xff, 8);
						break;
					case 2 :
						memcpy(&tmpMcuInfoData[9] , &tmpMcuInfoData[5], 4);		
						memcpy(&tmpMcuInfoData[5] , &tmpMcuInfoData[1], 4);		
						memcpy(&tmpMcuInfoData[1] , &McuInfoData1[1], 4);	
						memset(&tmpMcuInfoData[13] , 0xff, 4);
						break;
					case 3 :
						memcpy(&tmpMcuInfoData[13] , &tmpMcuInfoData[9], 4);		
						memcpy(&tmpMcuInfoData[9] , &tmpMcuInfoData[5], 4);		
						memcpy(&tmpMcuInfoData[5] , &tmpMcuInfoData[1], 4);		
						memcpy(&tmpMcuInfoData[1] , &McuInfoData1[1], 4);	
						break;
					default :
						memcpy(&tmpMcuInfoData[13] , &tmpMcuInfoData[9], 4);		
						memcpy(&tmpMcuInfoData[9] , &tmpMcuInfoData[5], 4);		
						memcpy(&tmpMcuInfoData[5] , &tmpMcuInfoData[1], 4);		
						memcpy(&tmpMcuInfoData[1] , &McuInfoData1[1], 4);	
						break;							
				}

				
				if(tmpMcuInfoData[0] > 250)
					tmpMcuInfoData[0] = 250;
				DiffMachInfo = 1;
				
				return;
			}

			if(MachineBasicInformation[i] == 0x2A)		//Asterisk
			{
				if(++CompareAsterisk >= 3)
				{	
					DiffMachInfo = 0;
					return;
				}
			}
		}
	}
}


/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
