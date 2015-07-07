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
#define UART2_Rx_BUF_SIZE		14			
#define UART2_Tx_BUF_SIZE		17
#define RING_BUF_SIZE			768

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_TypeDef* Serial_USART[5]     = {  0, 
                                        0, 
                                        Serial_COM2, 
                                        0,
                                        Serial_COM4, 
                                        }; 

GPIO_TypeDef*  Serial_PORT[5]      = {  0, 
                                        0, 
                                        Serial_COM2_GPIO, 
                                        0,
	                                    Serial_COM4_GPIO, 
                                        };

const uint32_t Serial_USART_CLK[5] = {  0, 
                                        0, 
                                        Serial_COM2_CLK, 
                                        0,
                                        Serial_COM4_CLK, 
                                        };

const uint32_t Serial_PORT_CLK[5]  = {  0, 
                                        0, 
                                        Serial_COM2_GPIO_CLK, 
                                        0,
                                        Serial_COM4_GPIO_CLK, 
                                        };

const uint16_t Serial_TX_PIN[5]    = {  0, 
                                        0, 
                                        Serial_COM2_TxPin, 
                                        0,
                                        Serial_COM4_TxPin,
                                        };

const uint16_t Serial_RX_PIN[5]    = {  0, 
                                        0, 
                                        Serial_COM2_RxPin,
                                        0,
                                        Serial_COM4_RxPin,
                                        };

const uint32_t Serial_BaudRate[5]  = {  0,
                                        0, 
                                        115200,	//  USART2
                                        57600,
                                        115200,  //  USART4
                                        };

const uint16_t Serial_IRQ_Channel[5]= { 0, 
                                        0, 
                                        USART2_IRQn,
                                        0,
                                        UART4_IRQn,
                                        };

extern u16 pWriteBufPos;
extern u8 ring_buf[RING_BUF_SIZE];
extern u16 pWriteBufPos;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  USART2, UART4 Initialize (COM param을 받아서. Port를 초기화 한다.)
  * @param  COM
  * @retval None
  */
void USART_COMInit(uint8_t COM)
{
	USART_InitTypeDef   	USART_InitStructure;
	NVIC_InitTypeDef    	NVIC_InitStructure;

	DebugMsg_printf("++ USART %d Initialize START\r\n", COM);

#if 0
	USART_ClockInitStructure.USART_Clock   = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL    = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA    = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	if (COM != 4) USART_ClockInit(Serial_USART[COM], &USART_ClockInitStructure);
#endif

	/* 
	USARTx configuration

	- BaudRate = xxxx baudrate
	- Word Length = 8 Bits
	- One Stop Bit
	- No parity
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled/Disabled
	*/

	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate            = Serial_BaudRate[COM];
	// USART_InitStructure.USART_BaudRate            = 57600;
	
	//  USART configuration
	USART_Init(Serial_USART[COM], &USART_InitStructure);

	//  Enable USART
	USART_Cmd(Serial_USART[COM], ENABLE);

	//  Enable USART2 ~ UART5 Receive interrupt
	USART_ITConfig(Serial_USART[COM], USART_IT_RXNE, ENABLE);    
	USART_ITConfig(Serial_USART[COM], USART_IT_TXE, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel                   = Serial_IRQ_Channel[COM];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DebugMsg_printf("-- USART %d Initialize END\r\n", COM);
}

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  USART2, UART4 Initialize (COM param을 받아서. Port를 초기화 한다.)
  * @param  COM
  * @retval None
  */
void USART_COMInit_DMA(uint8_t COM, unsigned char *TxBuf)
{
	USART_InitTypeDef   	USART_InitStructure;
	DMA_InitTypeDef 		DMA_InitStructure;
	NVIC_InitTypeDef    	NVIC_InitStructure;
	
	DebugMsg_printf("++ USART %d Initialize START\r\n", COM);

#if 0
	USART_ClockInitStructure.USART_Clock   = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL    = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA    = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	if (COM != 4) USART_ClockInit(Serial_USART[COM], &USART_ClockInitStructure);
#endif

	
  //DMA_Init(SD_SDIO_DMA_STREAM, &SDDMA_InitStructure);
 // DMA_ITConfig(SD_SDIO_DMA_STREAM, DMA_IT_TC, ENABLE);
  //DMA_FlowControllerConfig(SD_SDIO_DMA_STREAM, DMA_FlowCtrl_Peripheral);


	/* USARTy TX DMA1 Channel (triggered by USARTy Tx event) Config */
	DMA_DeInit(DMA1_Stream6);	
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&USART2->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr 	= (u32)TxBuf;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize 			= 17;
	DMA_InitStructure.DMA_PeripheralInc 			= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_FIFOMode			= DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_Mode 				= DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);

	DMA_ITConfig(DMA1_Stream6,DMA_IT_TC,DISABLE);

	/* USARTy RX DMA1 Channel (triggered by USARTy Rx event) Config 
	DMA_DeInit(DMA1_Stream5);  
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= APB1PERIPH_BASE + 0x4400 + 0x04;
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (u32)RxBuf;
	DMA_InitStructure.DMA_Mode 				= DMA_Mode_Circular;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize 			= UART2_Rx_BUF_SIZE;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);	*/
	
	/* 
	USARTx configuration

	- BaudRate = xxxx baudrate
	- Word Length = 8 Bits
	- One Stop Bit
	- No parity
	- Hardware flow control disabled (RTS and CTS signals)
	- Receive and transmit enabled/Disabled
	*/

	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_BaudRate            = Serial_BaudRate[COM];
	// USART_InitStructure.USART_BaudRate            = 57600;
	
	//  USART configuration
	USART_Init(Serial_USART[COM], &USART_InitStructure);


	USART_DMACmd(USART2,USART_DMAReq_Tx, ENABLE);

	//DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
	
	//DMA_Configuration(DMA1_Channel2, UART3_RxBuf, USART1_BASE, DMA_DIR_PeripheralSRC);
	//DMA_Cmd(DMA1_Stream5, ENABLE);      

	//  Enable USART2 ~ UART5 Receive interrupt
	USART_ITConfig(Serial_USART[COM], USART_IT_RXNE, ENABLE);    
	
	//NVIC_InitStructure.NVIC_IRQChannel                   = Serial_IRQ_Channel[COM] | DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannel                   = Serial_IRQ_Channel[COM];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//  Enable USART
	USART_Cmd(Serial_USART[COM], ENABLE);

}

u8 count_DMA;

void DMA_UART_SendFrame(unsigned char *dst, unsigned char *src, unsigned short size)
{ 

	DMA_Cmd(DMA1_Stream6, DISABLE); 

	memcpy(dst, src, size);

	DMA1_Stream6->NDTR = size;

	DMA_Cmd(DMA1_Stream6, ENABLE);  	

	while(DMA_GetCurrDataCounter(DMA1_Stream6));

	DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6);
	
}


/**
  * @brief  One Byte ASCII Sending
  * @param  None
  * @retval None
  */
void USARTx_PutChar(uint8_t COM, uint8_t data)
{
   USART_SendData(Serial_USART[COM], data);
   
   while (USART_GetFlagStatus(Serial_USART[COM], USART_FLAG_TXE) == RESET)
   {
   }
}

/**
  * @brief  String Data Sending
  * @param  None
  * @retval None
  */
void USARTx_PutStr(uint8_t COM, char *pStr)
{
	while (*pStr != '\0') 
    {
        USARTx_PutChar(COM, *(pStr++));
    }        
}

/**
  * @brief  One Byte Hex Sending
  * @param  None
  * @retval None
  */
void USARTx_PutHex(uint8_t COM, uint8_t hex)
{
	USARTx_PutChar(COM, HexToAscii(hex >> 4));
	USARTx_PutChar(COM, HexToAscii(hex & 0x0F));
}


/**
  * @brief  Hex code to ASCII code
  * @param  
  * @retval ASCII
  */
char HexToAscii(uint8_t hex)
{	
	return hex < 10 ? hex + '0' : hex - 10 + 'A';
}

/**
  * @brief  ASCII Code to Hex Code
  * @param  None
  * @retval Hex 
  */
uint8_t AsciiToHex(char ascii)
{	
	ascii = toupper(ascii);
	
    return ascii >= 'A' ? ascii - 'A' + 10 : ascii - '0';
}

/**
  * @brief  Hex Code to Decimal
  * @param  None
  * @retval Hex 
  */
int HexToDec(int def)
{
    int ten, one;

    one = def & 0x0f;
    ten = 0;
    ten = (def & 0x70) >> 4;
    def =ten * 10 + one;
    
    return def;
}

/**
  * @brief  Decimal to Hex
  * @param  None
  * @retval Hex 
  */
/*
char *DecToHex(uint8_t *Hex, uint16_t Dec)
{
    char Hex[5];
        
    
    // 65535 = FFFF
    if (Dec > 65535) return "1";
    
    sprintf(Hex, "%4x", Dec);

    return Hex;
}
*/


/**
  * @brief  usartx printf, polling
  * @param  None
  * @retval Hex 
  */
void USARTx_printf(uint8_t COM, char *fmt,...)
{
    va_list ap;
    
    char string[255];
    
    va_start(ap, fmt);
    vsprintf(string, fmt, ap);
    USARTx_PutStr(COM, string);
    va_end(ap);
}  

/**
  * @brief  usartx printk, interrupt
  * @param  None
  * @retval None 
  */
void USARTx_printk(uint8_t COM, char *fmt,...)
{
    va_list ap;
    
    char string[255];
    
    va_start(ap, fmt);
    vsprintf(string, fmt, ap);
    va_end(ap);
    
    switch (COM)
    {
        case COMPORT2 : 
                    strcpy((char *)WL9FM_USART_DATA.COM2_TxBuf, string);
                    
			        WL9FM_USART_INDEX.COM2_TxCnt = 0;
			        WL9FM_USART_INDEX.COM2_TxIdx = strlen((char *)WL9FM_USART_DATA.COM2_TxBuf);
                            
                    break;

        case COMPORT4 :
                    strcpy((char *)WL9FM_USART_DATA.COM4_TxBuf, string);
                    
			        WL9FM_USART_INDEX.COM4_TxCnt = 0;
			        WL9FM_USART_INDEX.COM4_TxIdx = strlen((char *)WL9FM_USART_DATA.COM4_TxBuf);
					
                    break;
                    
        default   : return;
    }                    
        
    USART_ITConfig(Serial_USART[COM], USART_IT_TXE, ENABLE);
}  

/**
  * @brief  None
  * @param  None
  * @retval None
  */
//  


void USARTx_EXYNOS(uint8_t COM, char *TmpBuffer)
{
//++, 150707 sys
#if 0
	memcpy((char *)WL9FM_USART_DATA.COM4_TxBuf, TmpBuffer, Serial_COM4_TxSize);
						
	WL9FM_USART_INDEX.COM4_TxCnt = 0;
	WL9FM_USART_INDEX.COM4_TxIdx = Serial_COM4_TxSize;
	    
	USART_ITConfig(Serial_USART[COM], USART_IT_TXE, ENABLE);
#endif

#if 1
	if(pWriteBufPos >= (RING_BUF_SIZE-1))	// End of Ring Buffer
		pWriteBufPos = 0;

	memcpy(&ring_buf[pWriteBufPos], TmpBuffer, Serial_COM4_TxSize);

	pWriteBufPos += Serial_COM4_TxSize;

	USART_ITConfig(Serial_USART[COM], USART_IT_TXE, ENABLE);
#endif

// --, 150707 sys
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
