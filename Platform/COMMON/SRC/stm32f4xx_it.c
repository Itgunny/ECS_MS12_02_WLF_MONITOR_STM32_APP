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

/* Private define ------------------------------------------------------------*/

#define RING_BUF_SIZE			1024*10
#define UART2_Tx_BUF_SIZE		21


#define UART2_RX_BUF_SIZE		26			// Max Multi Packet Data -> 3개
#define UART2_Tx_BUF_SIZE		21

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 ring_buf[RING_BUF_SIZE];		
u16 pWriteBufPos = 0;
u16 pReadBufPos = 0;
u8 CanRecvCnt = 0;
u16 TotPacketNum = 0;
u32 pgn = 0;
u16 TotMsgSize = 0;
u8 Uart2_SerialTxMsg[UART2_Tx_BUF_SIZE];

u8 Uart2_SerialTxCnt = 0;
u16 CommErrCnt = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void WL9F_CAN_Buffer_Init(void)
{
	Uart2_SerialTxMsg[0]  = 0x02;	// STX
	Uart2_SerialTxMsg[1]  = 0xF5;	// ID
	Uart2_SerialTxMsg[2]  = 8;		// Data Length
	Uart2_SerialTxMsg[19] = 0;		// CRC
	Uart2_SerialTxMsg[20] = 0x03;	// ETX

	pWriteBufPos = 0;
	
	TotPacketNum = 0;
	pgn = 0;
	
	Uart2_SerialTxCnt = 0;
	CommErrCnt = 0;
}

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

				if (WL9FM_TIME.Cnt_1mSec % 1000 == 0)    //  1000 msec
				{
					WL9FM_TIME.Flag_1Sec = 1;
					WL9FM_TIME.Cnt_1mSec = 0;
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

	CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);
				
	Iden.Source_Address = (RxMsg.ExtId & 0x000000ff)  >> 0;
	Iden.PDU_Specific = (RxMsg.ExtId  & 0x0000ff00) >> 8;
	
			
	// Iden.Source_Address == 0x29	 -->>	Smart Key Source Address
	// Iden.Source_Address == 0x2E	 -->>	EHCU Source Address
	if((Iden.Source_Address == 71) || (Iden.Source_Address == 23) || (Iden.Source_Address == 77) || 
		(Iden.Source_Address == 0x29) || (Iden.Source_Address == 0x2E))
		{
			if(++CanRecvCnt >= 50)
			{
				CanRecvCnt = 0;
	
				if(pWriteBufPos >= (1024*10-1)) // End of Ring Buffer
					pWriteBufPos = 0;
	
				//memcpy(&ring_buf[pWriteBufPos], (u8*)&SerialMsgRTC[0], 16);
				
				//pWriteBufPos += 16;
			}
	
	
			PF = (RxMsg.ExtId  & 0x00ff0000) >> 16;
	
			if((PF == 254) || (PF == 255))
			{			
				OperateRingBuffer();		
			}
			else if((PF == 235) || (PF == 236))
			{
				if(Iden.PDU_Specific == 255)
				{
					if(PF == 236)		// TP.CM_BAM
					{
						if(RxMsg.Data[0] == 32) 	// Control Byte
						{
							pgn = (RxMsg.Data[6] << 8) | (RxMsg.Data[5]);
							if(pgn == 65340)
							{
								TotPacketNum = RxMsg.Data[3];		// Total number of packets
								TotMsgSize = (RxMsg.Data[2] << 8) | RxMsg.Data[1];
							}
							else
							{
								Uart2_SerialTxMsg[19] = 0;
								OperateRingBuffer();
							}
							return;
						}
					}
	
					if(pgn != 0)
					{
						if(PF == 235)
						{
							Uart2_SerialTxMsg[19] = 0;
							OperateRingBuffer();
						}
					}
				}
			}
	
			CommErrCnt = 0;
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

	#if 0
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
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{

	}

	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	{   
		if((USART2->SR & 0x80) == RESET)
			return;

		if(pReadBufPos >= (RING_BUF_SIZE-1))
			pReadBufPos = 0;


		if((pWriteBufPos != pReadBufPos) && (Uart2_SerialTxCnt == 0))
			memcpy(&Uart2_SerialTxMsg[3] , &ring_buf[pReadBufPos], 12);

	
		USART_SendData(USART2, (u16)(Uart2_SerialTxMsg[Uart2_SerialTxCnt++]));    

		if (Uart2_SerialTxCnt >= UART2_Tx_BUF_SIZE)
		{
			Uart2_SerialTxCnt = 0;
			pReadBufPos += 12;
		}
        
	}
}

void UART4_IRQHandler(void)
{
    //  UART4 receive interrupt routine
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 
    {
		//  Read one byte to the receive data register
		WL9FM_USART_DATA.COM4_RxBuf[WL9FM_USART_INDEX.COM4_RxCnt] = USART_ReceiveData(UART4);

        //  디버깅할 때만 사용할 것
		#ifdef DEBUG_CMD_RX
		DebugMsg_printf("%2x ", WL9FM_USART_DATA.COM4_RxBuf[WL9FM_USART_INDEX.COM4_RxCnt]);
        #endif
		
		switch (WL9FM_USART_INDEX.COM4_RxCnt)
		{
			case 0:
					if (WL9FM_USART_DATA.COM4_RxBuf[0] == 0x02)
					{
						WL9FM_USART_INDEX.COM4_RxCnt++;
					}						
					break;
			case 1:
					if (WL9FM_USART_DATA.COM4_RxBuf[1]      == KeyCMD)		WL9FM_USART_INDEX.COM4_RxCnt++;
					else if (WL9FM_USART_DATA.COM4_RxBuf[1] == LCDBLCMD)	WL9FM_USART_INDEX.COM4_RxCnt++;
					else if (WL9FM_USART_DATA.COM4_RxBuf[1] == BUZZERCMD)	WL9FM_USART_INDEX.COM4_RxCnt++;
					
					break;

			case 3: 
					WL9FM_USART_INDEX.COM4_RxCnt = 0;
					
					//  디버깅할 때만 사용할 것
					#ifdef DEBUG_CMD_RX
					DebugMsg_printf("\r\n");
					#endif
					
					//	사용안함.					
                    #if 0
                    if (WL9FM_USART_DATA.COM4_RxBuf[Serial_COM4_RxSize-1] == 0x03)
					{
						memcpy(WL9FM_USART_DATA.COM4_TxBuf, WL9FM_USART_DATA.COM4_RxBuf, Serial_COM4_TxSize); 
                        memset(WL9FM_USART_DATA.COM4_RxBuf, 0x0, Serial_COM4_RxSize);
                               
						WL9FM_USART_INDEX.COM4_TxIdx = Serial_COM4_TxSize;
						WL9FM_USART_INDEX.COM4_TxCnt = 0;
						USART_ITConfig(UART4, USART_IT_TXE, ENABLE);							

						//  디버깅할 때만 사용할 것
				        //DebugMsg_printf("CMD Data Received.. \r\n");
                    }
					#else

                    if (WL9FM_USART_DATA.COM4_RxBuf[Serial_COM4_RxSize-1] == 0x03)
					{
						switch (WL9FM_USART_DATA.COM4_RxBuf[1])
						{
							case KeyCMD   :		//	Key Command

										break;
										
							case LCDBLCMD :		//	LCD BackLight Command

										//	LCD BackLight Level 조절.. Level0 ~ Level8
										if (WL9FM_USART_DATA.COM4_RxBuf[2] < MaxBackLightLEVEL) 												
										{
											LCDBL_PWM_LEVEL(WL9FM_USART_DATA.COM4_RxBuf[2]);
										}

										break;

							case BUZZERCMD :	//	Buzzer Command

										if (WL9FM_USART_DATA.COM4_RxBuf[2] == BUZZERDAT_ON) 
                                        {
                                            Buzzer_UnLimitOn();
                                        }
										else if (WL9FM_USART_DATA.COM4_RxBuf[2] == BUZZERDAT_OFF) 
                                        {
                                            Buzzer_UnLimitOff();											
                                        }

										break;
						}
                    }						

                    memset(WL9FM_USART_DATA.COM4_RxBuf, 0x0, Serial_COM4_RxSize);					
                    #endif

					break;
					
			default :

					WL9FM_USART_INDEX.COM4_RxCnt++;
					break;
		}					

		//	사용안함.					
		#if 0
		if (WL9FM_USART_INDEX.COM4_RxCnt >= Serial_COM4_RxSize) 
        {	
			WL9FM_USART_INDEX.COM4_RxCnt = 0; //  Overflow the receive buffer
		}
		#endif
	}

    //  UART4 transmit interrupt routine
    if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
    {   
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
    }           
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
