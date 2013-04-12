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
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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

	//  CAN GPIO는 System_Init.c 에서 설정
    #if 0

    GPIO_InitTypeDef    GPIO_InitStructure;
	
    //  CAN1_TX, CAN1_RX
    GPIO_InitStructure.GPIO_Pin   = CAN1_TX | CAN1_RX;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN1_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(CAN1_PORT, CAN1_TX_PinSource, GPIO_AF_CAN1);
	GPIO_PinAFConfig(CAN1_PORT, CAN1_RX_PinSource, GPIO_AF_CAN1);

    //  CAN2_TX, CAN2_RX
    GPIO_InitStructure.GPIO_Pin   = CAN2_TX | CAN2_RX;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN2_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(CAN2_PORT, CAN2_TX_PinSource, GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN2_PORT, CAN2_RX_PinSource, GPIO_AF_CAN2);

	#endif
	
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


	
	CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);		
	
    DebugMsg_printf("++ CAN1, CAN2 Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
