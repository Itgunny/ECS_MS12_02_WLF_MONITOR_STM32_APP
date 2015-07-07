/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

//#define		DEBUG_CMD_RX
//#define		DEBUG_CMD_TX
//#define		DEBUG_CAN_RX
//#define		DEBUG_CAN_TX
#pragma pack(1)
struct st_CAN_Msg
{	
	unsigned char Priority;
	unsigned char Data_Page;
	unsigned char PDU_Format;	
	unsigned char PDU_Specific;		// 50
	unsigned char Source_Address;	// 52
};
#pragma pack()

CanRxMsg RxMsg;
struct st_CAN_Msg Iden; 

extern Realy_Control		rx_Realy_Control;
extern EHCU_Status		rx_EHCU_Status;
extern Auto_position_Status rx_Auto_position_Status;
extern st_CANDATA_HCEPGN_65428	RX_HCEPGN_65428;
extern WEIGHING_SYSTEM_STATUS_65450 rx_Weighing_System_Status;
extern CMD_LAMP rx_CMD_LAMP;
/* Private define ------------------------------------------------------------*/

#define RING_BUF_SIZE			768
#define UART2_Rx_BUF_SIZE		14			
#define UART2_Tx_BUF_SIZE		17

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





/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 ring_buf[RING_BUF_SIZE];		
u16 pWriteBufPos = 0;
u16 pReadBufPos = 0;
u8 CanRecvCnt = 0;
u16 TotPacketNum = 0;
u32 pgn = 0;
u32 RMCUpgn = 0;
u16 TotMsgSize = 0;
u8 Uart2_SerialTxMsg[UART2_Tx_BUF_SIZE];
u8 Uart2_SerialRxMsg[UART2_Rx_BUF_SIZE];

u8 Uart2_SerialTxCnt = 0;
u8 Uart2_SerialRxCnt = 0;
u16 CommErrCnt = 0;

u8 SendEEPROMDataCnt = 0;
u8 Flag_TxE2pRomData = 0;
u8 stop_send_as_phone_data = 0;
u8 Stm32_Update_CMD;
u8 FatoryInit_Flag = 0;
u8 CANUpdateFlag = 0;
u8 CANUpdateSA = 0;


u8 Buz1;

extern u8 MoniInfoSendCnt;
extern u8 MoniInfoTotalPacketNum;
extern u8 RecvMachInfo;
extern u8 MachineBasicInformation[78];
extern u8 RTSFlag_61184;
extern u8 CTSFlag_61184;
extern u8 RecvTotalPacket_61184;
extern u8 ACK_Multi_61184[8];
extern u8 RMCU_CTSFlag_61184;
extern u8 RMCU_RecvTotalPacket_61184;
extern u8 RMCU_ACK_Multi_61184[8];



extern u8 Flag_UartTxStart;
extern u32 Flag_SerialRxMsg;
extern u8 eepRomReadData1[32];

extern u8 Uart2_RxMsg_Save_Data1[8];
extern u8 Uart2_RxMsg_Save_Data2[8];
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
extern u8 Uart2_RxMsg_Single_239_121[8];
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




extern u8 SerialMsgRTC[16];
extern u8 Lamp_name;
extern u8 Lamp_Value;

//////////////// stm32 update /////////////////////
extern u8 Change_UART4_for_Download;
extern u8 ST_Update;
extern u8 UpdateMode;


// Smart Key
extern WL9FM_receive_smartkey recv_smartkey;
extern WL9FM_flag_data smk_flag_data;
extern int SMKSuccess;


unsigned long long CANRXIndex = 0;
unsigned long long SerialTXIndex = 0;

extern u8 LCDOffCount;
extern u16 OSUpdateCount;

extern u8 Flag_ESL;

extern u8 SmartKeyUse;

extern u8 CameraCommFlag;

extern uint16_t ADC3ConvertedValue;


extern u16 pWriteBufPos;



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void WL9F_CAN_Buffer_Init(void)
{
	Uart2_SerialTxMsg[0]  = 0x02;	// STX
	Uart2_SerialTxMsg[1]  = 0xF5;	// ID
	Uart2_SerialTxMsg[2]  = 8;		// Data Length
	Uart2_SerialTxMsg[15] = 0;		// CRC
	Uart2_SerialTxMsg[16] = 0x03;	// ETX

	pWriteBufPos = 0;

	TotPacketNum = 0;
	pgn = 0;

	Uart2_SerialTxCnt = 0;
	CommErrCnt = 0;
}

uint16_t test,old_test;

unsigned char test_temp[8];

#if 0
void OperateRingBuffer(void)
{
	if(pWriteBufPos >= (RING_BUF_SIZE-1))	// End of Ring Buffer
		pWriteBufPos = 0;

	memcpy(&ring_buf[pWriteBufPos], (u8*)&RxMsg.ExtId, 4);

	pWriteBufPos += 4;

	memcpy(&ring_buf[pWriteBufPos], (u8*)&RxMsg.Data, 8);
	
	pWriteBufPos += 8;	

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	
}
#endif

void RTCSend(void)
{
	if(pWriteBufPos >= (RING_BUF_SIZE-1)) // End of Ring Buffer
		pWriteBufPos = 0;

	memcpy(&ring_buf[pWriteBufPos], (u8*)&SerialMsgRTC[0], 12);

	pWriteBufPos += 12;

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}


void SendTo_E2PROM(void)
{
#if 1
	if (SendEEPROMDataCnt < 2)	//	2번 보낸다.
	{
		memcpy(&Uart2_SerialTxMsg[7], &eepRomReadData1[0], 8);
		Uart2_SerialTxMsg[15] = 0xE1;
	}	
	else if (SendEEPROMDataCnt < 4)	//	2번 보낸다.
	{
		memcpy(&Uart2_SerialTxMsg[7], &eepRomReadData1[8], 8);
		Uart2_SerialTxMsg[15] = 0xE2;
	}	
	else
	{
		memcpy(&Uart2_SerialTxMsg[7], &eepRomReadData1[16], 8);
		Uart2_SerialTxMsg[15] = 0xE3;
	}		

	//  Enable the USART3 Transmit interrupt
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
#endif
}

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  	TimeDelay_Decrement();

    ++WL9FM_TIME.Cnt_1mSec;

	if (WL9FM_TIME.Cnt_1mSec % 1 == 0)                   //  1msec
	{
        WL9FM_TIME.Flag_1mSec = 1;

		if (WL9FM_TIME.Cnt_1mSec % 10 == 0)              //  10msec
		{
			WL9FM_TIME.Flag_10mSec = 1;

			if (WL9FM_TIME.Cnt_1mSec % 100 == 0)         //  100msec
			{
				WL9FM_TIME.Flag_100mSec = 1;

				if(WL9FM_TIME.Cnt_1mSec % 500 == 0)			// 500msec
				{
					WL9FM_TIME.Flag_500mSec = 1;
					if (WL9FM_TIME.Cnt_1mSec % 1000 == 0)    //  1000 msec
					{
						WL9FM_TIME.Flag_1Sec = 1;
						WL9FM_TIME.Cnt_1mSec = 0;
					}
				}

				
			}
		}
	}    
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles CAN1 global interrupt request.
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
{
	u32 PF; 
	u32 PS;
	u32 PGN;

	CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);
				
	Iden.Source_Address = (RxMsg.ExtId & 0x000000ff)  >> 0;
	Iden.PDU_Specific = (RxMsg.ExtId  & 0x0000ff00) >> 8;
	
	// Iden.Source_Address == 71	 -->>	MCU
	// Iden.Source_Address == 228	 -->>	EHCU	
	// Iden.Source_Address == 0x29	 -->>	Smart Key
	// Iden.Source_Address == 23	 -->>	Cluster
	// Iden.Source_Address == 221	 -->>	RCU
	// Iden.Source_Address == 0	 -->>	ECM
	// Iden.Source_Address == 3	 -->>	TCU
	// Iden.Source_Address == 25	 -->>	ACU
	// Iden.Source_Address == 52	 -->>	BKCU
	if((Iden.Source_Address == 0x47) || (Iden.Source_Address == 0x17) || (Iden.Source_Address == 0x29) || 
		(Iden.Source_Address == 0xE4) || (Iden.Source_Address == 0xDD)|| (Iden.Source_Address == 0x4a)|| (Iden.Source_Address == 0xf4)
		|| (Iden.Source_Address == 0x00)|| (Iden.Source_Address == 0x03) || (Iden.Source_Address == 0x02) || (Iden.Source_Address == 0x19)
		|| (Iden.Source_Address == 0x34))
		{
		#if 1
			
			if(CANUpdateFlag == 0)
			{
				PF = (RxMsg.ExtId  & 0x00ff0000) >> 16;
				if((PF == 254) || (PF == 255) || (PF == 239) )
				{	
					
					if(Iden.PDU_Specific == 232)	// Smart Key
					{
						smk_flag_data.recv_resp_packet |= RESPONSE_AUTHENTICATION;	
						//smk_flag_data.recv_resp_packet |= 0x0100; 
						memcpy((u8*)&recv_smartkey, (u8*)&RxMsg.Data[0], 8);
					}
					else
					{
		
						//if(Iden.PDU_Specific == 0x9b)
							CAN_RX(RxMsg);
					}
				}
				
				else
				{                    
	                		CAN_RX(RxMsg);
				}
		
				CommErrCnt = 0;
			}
			else if(CANUpdateFlag == 1)
			{
				if(Iden.Source_Address == CANUpdateSA)
				{
					PF = (RxMsg.ExtId  & 0x00ff0000) >> 16;
					PS = (RxMsg.ExtId  & 0x0000FF00) >> 8;
					PGN = (RxMsg.ExtId  & 0x00FFFF00) >> 8;
					if(PGN == 0xEFFA || PGN  == 0xECFA || PGN  == 0xEBFA)
					{
						CAN_RX(RxMsg);
					}

				}
				
			}
		#else
			if(CANUpdateFlag == 1)
			{
				if(Iden.Source_Address == CANUpdateSA)
				{
					PF = (RxMsg.ExtId  & 0x00ff0000) >> 16;
					PS = (RxMsg.ExtId  & 0x0000FF00) >> 8;
					PGN = (RxMsg.ExtId  & 0x00FFFF00) >> 8;
					if(PGN == 0xEFFA || PGN  == 0xECFA || PGN  == 0xEBFA)
					{
						//OperateRingBuffer();
						CAN_RX(RxMsg);
						CANRXIndex++;
					}

				}
				
			}
		#endif
			
			

			
			
		}

}

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)  //  10msec Timer / TimeBase UP Counter
{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    
    //  BUZZER Status가 "2" 일 경우 BUZZER OnTime 만큼 BUZZER On
    if (WL9FM_BUZZER.Status == 2)
    {
        if (WL9FM_BUZZER.OnCnt++ < WL9FM_BUZZER.OnTime)
        {
            Buzzer_On();
        }
        else
        {
            WL9FM_BUZZER.Status = 0;               
        }
    }        
    //  BUZZER Status가 "1" 일 경우 UnLimit BUZZER On
    else if (WL9FM_BUZZER.Status == 1)
    {
        Buzzer_On();    
    }    
    else
    {
        Buzzer_Off();
        
        WL9FM_BUZZER.Status = 0;               
        WL9FM_BUZZER.OnTime = 0;
        WL9FM_BUZZER.OnCnt  = 0;
    }

#if 1
	CommErrCnt++;

	if(CommErrCnt >= 1000)
		CommErrCnt = 1001;
#endif
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)  //  5msec Timer / TimeBase UP Counter    
{
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

	KeySwitch_Process();    //  KeySwitch.c Func
}

/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
  // STM32F407 <-> exynos4412 can_data

unsigned char temp_61184;

void USART2_IRQHandler(void)
{
	struct st_CAN_Message1 Send_Message;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Uart2_SerialRxMsg[Uart2_SerialRxCnt] = (u8)USART_ReceiveData(USART2);

		  //  디버깅할 때만 사용할 것
		#ifdef DEBUG_CAN_RX
		DebugMsg_printf("%2x ", Uart2_SerialRxMsg[Uart2_SerialRxCnt]);
		#endif
		
		switch(Uart2_SerialRxCnt)
		{
			case 0:
				if(Uart2_SerialRxMsg[0] == 0x02)		// STX
					Uart2_SerialRxCnt++;
				break;
			case UART2_Rx_BUF_SIZE-1:
				Uart2_SerialRxCnt = 0;

				if(Uart2_SerialRxMsg[UART2_Rx_BUF_SIZE-1] == 0x03)		// ETX
				{
					memcpy(&Send_Message,&Uart2_SerialRxMsg[1],12);	
					Write_CAN_Single(Send_Message);
				}
				else
				{
					//  디버깅할 때만 사용할 것
					//DebugMsg_printf("Protocol Fail\r\n");
				}

				break;
			
			default :
				Uart2_SerialRxCnt++;
				break;
		}
	}

#if 0
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	{   
		if((USART2->SR & 0x80) == RESET)
			return;

		if (pWriteBufPos == pReadBufPos)
		{
			if(Flag_TxE2pRomData == 1)
			{
			    USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			    return;
		    }
		}

		if(pReadBufPos >= (RING_BUF_SIZE-1))
			pReadBufPos = 0;

		if((Uart2_SerialTxCnt == 0) && (pWriteBufPos != pReadBufPos))
		{
			memcpy(&Uart2_SerialTxMsg[3] , &ring_buf[pReadBufPos], 12);
			
		}
		
		USART_SendData(USART2, (u16)(Uart2_SerialTxMsg[Uart2_SerialTxCnt++]));    
		
		if (Uart2_SerialTxCnt >= UART2_Tx_BUF_SIZE)
		{
			#if 0
			//Uart2_SerialTxCnt = 0;
			//pReadBufPos += 12;
			//USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

			if(Flag_TxE2pRomData == 0)
			{
                //  보내는 횟수 중요하다. 초기에 버그가 생실 수 있으니, 테스트 필요함!!!
				//	EEPROM Data를 6번 보낸다.
				if(SendEEPROMDataCnt > 5)	
				{
					Uart2_SerialTxCnt = 0;	
					Uart2_SerialTxMsg[15] = 0;
					Flag_TxE2pRomData = 1;
						
					//	EEPROM Data를 그만 보내고 CAN Data를 보낸다. 
					Flag_UartTxStart = 0;
					
					//  Enable the USART2 Transmit interrupt
					USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
					CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);			
				}
				else
				{
					SendEEPROMDataCnt++;
			        	Uart2_SerialTxCnt = 0;

					//  Disable the USART3 Transmit interrupt
					USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
				}
			}
			else
			{
				Uart2_SerialTxCnt = 0;
				pReadBufPos += 12;
			}
			#else
			if(Flag_TxE2pRomData == 0)
			{
              
				Uart2_SerialTxCnt = 0;	
				Uart2_SerialTxMsg[15] = 0;
				Flag_TxE2pRomData = 1;
					
				//	EEPROM Data를 그만 보내고 CAN Data를 보낸다. 
				Flag_UartTxStart = 0;
				
				//  Enable the USART2 Transmit interrupt
				USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
				CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);		
				
				
			}
			else
			{
				Uart2_SerialTxCnt = 0;
				pReadBufPos += 12;
				SerialTXIndex++;
			}
			#endif
		}  
	}
#else
	

#endif

}

/*
void DMA1_Stream6_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6) != RESET) 
    	{
    		if(pReadBufPos >= (RING_BUF_SIZE-1))
			pReadBufPos = 0;

		if((Uart2_SerialTxCnt == 0) && (pWriteBufPos != pReadBufPos))
		{
			memcpy(&Uart2_SerialTxMsg[3] , &ring_buf[pReadBufPos], 12);	
		}
		USART_SendData(USART2, (u16)(Uart2_SerialTxMsg[Uart2_SerialTxCnt++]));    
		
		if (Uart2_SerialTxCnt >= UART2_Tx_BUF_SIZE)
		{
			Uart2_SerialTxCnt = 0;
			pReadBufPos += 12;
			SerialTXIndex++;
		}  
	}
}*/



void UART4_IRQHandler(void)
{
	//  UART4 receive interrupt routine
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 
    	{
    		if(Change_UART4_for_Download==0)
			UART4_Receive_CMD();
		else
			UART4_Receive_File();
				
	}
	//  UART4 transmit interrupt routine
	if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
	{   
		UART4_transmit_CMD();
	}
}

u8 temp_rx_buf[4];

void UART4_Receive_CMD(void)
{
	uint8_t Temp[Serial_COM4_TxSize];
	//  Read one byte to the receive data register
	WL9FM_USART_DATA.COM4_RxBuf[WL9FM_USART_INDEX.COM4_RxCnt] = USART_ReceiveData(UART4);

	
    	//  디버깅할 때만 사용할 것
	#ifdef DEBUG_CMD_RX
	DebugMsg_printf("%2x ", WL9FM_USART_DATA.COM4_RxBuf[WL9FM_USART_INDEX.COM4_RxCnt]);
	#endif

	
	switch (WL9FM_USART_INDEX.COM4_RxCnt)
	{
		case 0:
				if (WL9FM_USART_DATA.COM4_RxBuf[0] == STX)
				{
					WL9FM_USART_INDEX.COM4_RxCnt++;
				}	
				else
				{
					WL9FM_USART_INDEX.COM4_RxCnt=0;
				}
				
				break;
		case 1:
				if (WL9FM_USART_DATA.COM4_RxBuf[1]      == KeyCMD)		WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == LCDBLCMD)	WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == BUZZERCMD)	WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == LAMPCMD)		WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == CAMCMD)		WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == DOWNCMD)	WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == VersionCMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == StartCANCMD) WL9FM_USART_INDEX.COM4_RxCnt++;    
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == RTCCMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == CANUPDATECMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == SMKCMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == OSUPDATECMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == EEPROMTESTCMD) WL9FM_USART_INDEX.COM4_RxCnt++;
				else if (WL9FM_USART_DATA.COM4_RxBuf[1] == FLASHTESTCMD) WL9FM_USART_INDEX.COM4_RxCnt++;

                else
                {
                  	WL9FM_USART_INDEX.COM4_RxCnt = 0;
                }
				break;

		case Serial_COM4_RxSize-1: 
				WL9FM_USART_INDEX.COM4_RxCnt = 0;
				
				//  디버깅할 때만 사용할 것
				#ifdef DEBUG_CMD_RX
				DebugMsg_printf("\r\n");
				#endif

		if (WL9FM_USART_DATA.COM4_RxBuf[Serial_COM4_RxSize-1] == ETX)
		{
			switch (WL9FM_USART_DATA.COM4_RxBuf[1])
			{
				case KeyCMD   :		//	Key Command

					break;
							
				case LCDBLCMD :		//	LCD BackLight Command

					//	LCD BackLight Level 조절.. Level0 ~ Level8
					if (WL9FM_USART_DATA.COM4_RxBuf[2] < MaxBackLightLEVEL && (WL9FM_USART_DATA.COM4_RxBuf[2] > 0)) 												
					{
						LCDBL_PWM_LEVEL(WL9FM_USART_DATA.COM4_RxBuf[2]);
					}

					break;

				case BUZZERCMD :	//	Buzzer Command
					if (WL9FM_USART_DATA.COM4_RxBuf[2] == 0)	//	Buzzer Off
					{
						Buzzer_UnLimitOff();
					}
					else if(WL9FM_USART_DATA.COM4_RxBuf[2] == 1)					//	Buzzer On
					{
						Buzzer_UnLimitOn();
					}
					break;

				case LAMPCMD :	//	Buzzer Command
					Lamp_name = (WL9FM_USART_DATA.COM4_RxBuf[2] & 0xf0)>>4;
					Lamp_Value = (WL9FM_USART_DATA.COM4_RxBuf[2] & 0x0f);
					memcpy(&rx_CMD_LAMP , &WL9FM_USART_DATA.COM4_RxBuf[2], 8);	
					Lamp_Update_State();
					//Lamp_Update_System();
					break;
					
				case CAMCMD:
					if(CameraCommFlag == 0)
					{
						CameraCommFlag = 1;
						Camera_Mode = WL9FM_USART_DATA.COM4_RxBuf[2];
					}					
					break;

				case DOWNCMD:
					Stm32_Update_CMD = WL9FM_USART_DATA.COM4_RxBuf[2];
					FatoryInit_Flag = WL9FM_USART_DATA.COM4_RxBuf[3];
					ST_Update=1;

					break;
				case VersionCMD:
					
					Temp[0] = 0x02;				
					Temp[1] = VersionRES;				
					Temp[2] = ((VERSION_HIGH  << 4) & 0xF0 ) + (VERSION_LOW & 0x0F);	
					Temp[3] = ((VERSION_SUB_HIGH  << 4) & 0xF0 )+ (VERSION_SUB_LOW & 0x0F);	
					// HW Version/////
					Temp[4] = (ADC3ConvertedValue & 0xFF);
					Temp[5] = (ADC3ConvertedValue & 0xFF00) >> 8;
					Temp[6] = VERSION_HIDDEN & 0x0F;
					//////////////////
					Temp[Serial_COM4_RxSize-1] = 0x03;	
					USARTx_EXYNOS(COM4, (char *)Temp);	
					break;
				case StartCANCMD:
					//Flag_UartTxStart = 1;
					CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);	
					break;
				case RTCCMD:
					WL9FM_RTC.Year = WL9FM_USART_DATA.COM4_RxBuf[2];
					WL9FM_RTC.Month = WL9FM_USART_DATA.COM4_RxBuf[3];
					WL9FM_RTC.Date = WL9FM_USART_DATA.COM4_RxBuf[4];
					WL9FM_RTC.Day = WL9FM_USART_DATA.COM4_RxBuf[5];
					WL9FM_RTC.Hour = WL9FM_USART_DATA.COM4_RxBuf[6];
					WL9FM_RTC.Minute= WL9FM_USART_DATA.COM4_RxBuf[7];
					WL9FM_RTC.Second= WL9FM_USART_DATA.COM4_RxBuf[8];
					WRITE_RTC(WL9FM_RTC);
					break;

				case SMKCMD:
					
					if(WL9FM_USART_DATA.COM4_RxBuf[2] == 0x00)
					{
						SendSMKAuthResult(SMKSuccess);
					}
					else if(WL9FM_USART_DATA.COM4_RxBuf[2] == 0x03)
					{
						SaveSMKUseToEEPROM(WL9FM_USART_DATA.COM4_RxBuf[3]);
					}
					else
					{
						memcpy(&Uart2_RxMsg_Smk_Reg_Eli[0], &WL9FM_USART_DATA.COM4_RxBuf[0], 8);
					}
					break;
				case CANUPDATECMD:
					CANUpdateFlag = WL9FM_USART_DATA.COM4_RxBuf[2];
					CANUpdateSA = WL9FM_USART_DATA.COM4_RxBuf[3];
					break;
				case OSUPDATECMD:
					LCDOffCount = 0;
					OSUpdateCount = 0;
					break;
				case EEPROMTESTCMD:
					if(WL9FM_USART_DATA.COM4_RxBuf[2] == 1)
					{
						InitE2PROM();
					}
					else
					{
						SaveTestToEEPROM(WL9FM_USART_DATA.COM4_RxBuf[3]);
					}
					Temp[0] = 0x02;				
					Temp[1] = EEPROMTESTRES;	
					Temp[2] = WL9FM_USART_DATA.COM4_RxBuf[2];	
					Temp[3] = LoadTestToEEPROM(); 	
					Temp[Serial_COM4_RxSize-1] = 0x03;	
					USARTx_EXYNOS(COM4, (char *)Temp);	
					break;
				case FLASHTESTCMD:
					if(WL9FM_USART_DATA.COM4_RxBuf[2] == 1)
					{
						SPI_FLASH_BulkErase();
					}
					else
					{
						SPI_FLASH_SectorErase(0x3d0000);	//Sector60
						SPI_FLASH_PageWrite(&WL9FM_USART_DATA.COM4_RxBuf[3],0x3d0000,7);
						SPI_FLASH_BufferRead(&Temp[3],0x3d0000,7);
						Temp[0] = 0x02;
						Temp[1] = FLASHTESTRES;
						Temp[2] = WL9FM_USART_DATA.COM4_RxBuf[2];
						Temp[Serial_COM4_RxSize-1] = 0x03;	
						USARTx_EXYNOS(COM4, (char *)Temp);	
						SPI_FLASH_SectorErase(0x3d0000);	//Sector60
					}

					break;
				default :
					break;								
			}
                }						

		//memset(WL9FM_USART_DATA.COM4_RxBuf, 0x0, Serial_COM4_RxSize);					
				break;
		
		default :

			WL9FM_USART_INDEX.COM4_RxCnt++;
			break;
	}	
}

void UART4_Receive_File(void)
{
	
	//  Read one byte to the receive data register
	WL9FM_USART_RX_FILE_DATA.File_RxBuf[WL9FM_USART_RX_FILE_DATA.File_RxCnt] = USART_ReceiveData(UART4);
	
	switch (WL9FM_USART_RX_FILE_DATA.File_RxCnt)
	{
		case 0:
				if (WL9FM_USART_RX_FILE_DATA.File_RxBuf[0] == STX)
				{
					WL9FM_USART_RX_FILE_DATA.File_RxCnt++;
				}						
				break;
		case 1029: 
				WL9FM_USART_RX_FILE_DATA.File_RxCnt = 0;
					
				if (WL9FM_USART_RX_FILE_DATA.File_RxBuf[1029] == ETX)
				{
					memcpy(&WL9FM_USART_FILE_DATA , &WL9FM_USART_RX_FILE_DATA, Serial_file_RxSize);	
					ST_Update=1;
				}
				else if (WL9FM_USART_RX_FILE_DATA.File_RxBuf[1029] == EOT)
				{
					memcpy(&WL9FM_USART_FILE_DATA , &WL9FM_USART_RX_FILE_DATA, Serial_file_RxSize);	
					Change_UART4_for_Download =2;
					ST_Update=1;
				}
				else
				{
					ACK_NACK_SendToExynos(NAK);
				}
                                break;
		default :

			WL9FM_USART_RX_FILE_DATA.File_RxCnt++;
			break;
	}					
}


void UART4_transmit_CMD(void)
{
// ++, 150707 sys
#if 0
	//  Write one byte to the transmit data register
	USART_SendData(UART4, WL9FM_USART_DATA.COM4_TxBuf[WL9FM_USART_INDEX.COM4_TxCnt++]);

	if (WL9FM_USART_INDEX.COM4_TxIdx >= Serial_COM4_TxSize)
	{
		WL9FM_USART_INDEX.COM4_TxIdx = Serial_COM4_TxSize;
	}    
	if (WL9FM_USART_INDEX.COM4_TxCnt == WL9FM_USART_INDEX.COM4_TxIdx)
	{
		//  Disable the UART4 Transmit interrupt
		USART_ITConfig(UART4, USART_IT_TXE, DISABLE);

		WL9FM_USART_INDEX.COM4_TxIdx = 0; //  transmit buffer Index clear
		WL9FM_USART_INDEX.COM4_TxCnt = 0; //  transmit buffer Cnt   clear
	}      
#endif

	if((UART4->SR & 0x80) == RESET)
		return;

	if (pWriteBufPos == pReadBufPos)
	{
		    USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
		    return;
	}

	if(pReadBufPos >= (RING_BUF_SIZE-1))
			pReadBufPos = 0;


	if((pWriteBufPos != pReadBufPos) && (WL9FM_USART_INDEX.COM4_TxCnt == 0))
		memcpy(&WL9FM_USART_DATA.COM4_TxBuf[0] , &ring_buf[pReadBufPos], Serial_COM4_TxSize);

	USART_SendData(UART4, WL9FM_USART_DATA.COM4_TxBuf[WL9FM_USART_INDEX.COM4_TxCnt++]);

	if (WL9FM_USART_INDEX.COM4_TxCnt >= Serial_COM4_TxSize)
	{
		WL9FM_USART_INDEX.COM4_TxCnt = 0;
		pReadBufPos += Serial_COM4_TxSize;
	}
// --, 150707 sys
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
