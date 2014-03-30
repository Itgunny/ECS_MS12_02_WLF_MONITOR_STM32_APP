/**
  ******************************************************************************
  * @file    UART_Control.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for UART_Control.c module
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
#ifndef __UART_Control_H
#define __UART_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
typedef enum 
{
    COMPORT2 = 2,
    COMPORT4 = 4,
}   Serial_PortTypeDef;

/* Private define ------------------------------------------------------------*/
//  Protocol Control Code                                               
#define STX                         0x02                //  Start of Text(Start of Data)
#define ETX                         0x03                //  End of Test(End of Data)
#define EOT					0x04
#define ENQ                         0x05                //  Enquiry(Communication request)
#define ACK                         0x06                //  Acknowledge(No data error detected)
#define LF                          0x0a                //  Line Feed
#define CR_                         0x0d                //  Carriage Return
#define NAK                         0x15                //  Negative Acknowledge(Data error detected)

#define HI_BYTE(x)	                ((x >> 8) & 0xFF)	//  High Bype
#define LO_BYTE(x)	                (x & 0xFF)		    //  Low bype

//  System_Init.c 에서 이미 설정하였지만, 다시 지정하기 위해서 아래의 define 선언.!!!
//  System_Init.h 에서 선언한 것과 macro value만 다른 것이다. 
/**
 * @brief Definition for COM port2, connected to USART2
 */ 
#define Serial_COM2                   USART2
#define Serial_COM2_GPIO              GPIOA
#define Serial_COM2_CLK               RCC_APB1Periph_USART2
#define Serial_COM2_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define Serial_COM2_RxPin             GPIO_Pin_3
#define Serial_COM2_TxPin             GPIO_Pin_2

/**
 * @brief Definition for COM port4, connected to USART4
 */ 
#define Serial_COM4                   UART4
#define Serial_COM4_GPIO              GPIOA
#define Serial_COM4_CLK               RCC_APB1Periph_UART4
#define Serial_COM4_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define Serial_COM4_RxPin             GPIO_Pin_1
#define Serial_COM4_TxPin             GPIO_Pin_0


//  TxSize를 255보다 크게 변경하려면, 
//  void USARTx_printf(uint8_t COM, char *fmt,...) func에서 string size를 크게 해야한다.
#define Serial_COM2_TxSize            255
#define Serial_COM4_TxSize            4

#define Serial_COM2_RxSize            255
#define Serial_COM4_RxSize            4   

#define Serial_file_RxSize            1030

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct 
{
	uint8_t COM2_TxBuf[Serial_COM2_TxSize];
	uint8_t COM4_TxBuf[Serial_COM4_TxSize];

	uint8_t COM2_RxBuf[Serial_COM2_RxSize];
	uint8_t COM4_RxBuf[Serial_COM4_RxSize];
} USARTx_DATA;

typedef struct
{
	uint8_t  COM2_TxIdx;    
	uint8_t  COM4_TxIdx;    

	uint8_t  COM2_TxCnt;    
	uint8_t  COM4_TxCnt;    

	uint8_t  COM2_RxCnt;    
	uint8_t  COM4_RxCnt;    
} USARTx_INDEX;

#pragma pack(1)
typedef struct 
{
	uint8_t  _STX;    
	uint16_t index   ;
	uint8_t  data[1024];    
	uint16_t  CRC_data;  
	uint8_t  _ETX;  
} USARTx_RX_BUF;
 #pragma pack()
 
typedef struct 
{
	union
	{
		uint8_t 	File_RxBuf[Serial_file_RxSize];
     		USARTx_RX_BUF Bin_Data;
	};
	uint16_t	File_RxCnt;
	
} USARTx_FILE_RX_DATA;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern USARTx_DATA  WL9FM_USART_DATA;
extern USARTx_INDEX WL9FM_USART_INDEX;

extern USARTx_FILE_RX_DATA WL9FM_USART_RX_FILE_DATA;
extern USARTx_FILE_RX_DATA WL9FM_USART_FILE_DATA;
/* Exported functions ------------------------------------------------------- */
extern void USART_COMInit(uint8_t COM);
extern void USARTx_PutChar(uint8_t COM, uint8_t data);

extern void USARTx_PutHex(uint8_t COM, uint8_t hex);
extern void USARTx_printf(uint8_t COM, char *fmt,...);
extern void USARTx_printk(uint8_t COM, char *fmt,...);

extern char HexToAscii(uint8_t hex);
extern uint8_t AsciiToHex(char ascii);
extern int HexToDec(int def);
extern void USARTx_EXYNOS(uint8_t COM, char *TmpBuffer);

#endif /* __UART_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
