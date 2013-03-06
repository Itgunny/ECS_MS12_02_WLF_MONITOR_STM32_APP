/**
  ******************************************************************************
  * @file    System_Init.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/28/2013
  * @brief   
  *
  * Project Name       : WL9F Display APP
  * Project Enviroment : IAREmbedded Workbench for ARM 6.5x 
  *                      STM32F407ZGT6 Firmware Library
  * Project Workspace  : WL9F_Display_APP
  * MCU Type           : STM32F407ZGT6
  *
  * TAEHA MECHATRONICS Co., Ltd (http://www.taeha.co.kr)				
  * ECS Division R&D Center. / Author by Young-Min Han (kutelf@taeha.co.kr)
  * 
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//	CAN1
#define		CAN1_TX							GPIO_Pin_12
#define		CAN1_TX_PinSource				GPIO_PinSource12
#define		CAN1_RX							GPIO_Pin_11
#define		CAN1_RX_PinSource				GPIO_PinSource11
#define		CAN1_PORT						GPIOA

//	CAN2
#define		CAN2_TX							GPIO_Pin_6
#define		CAN2_TX_PinSource				GPIO_PinSource6
#define		CAN2_RX							GPIO_Pin_5
#define		CAN2_RX_PinSource				GPIO_PinSource5
#define		CAN2_PORT						GPIOB

//	STM32 DEBUG UART1
#define		DEBUG_UART1TX					GPIO_Pin_9
#define		DEBUG_UART1TX_PinSource			GPIO_PinSource9
#define		DEBUG_UART1RX					GPIO_Pin_10
#define		DEBUG_UART1RX_PinSource			GPIO_PinSource10
#define		DEBUG_UART1_PORT				GPIOA

//	STM32 UART2 <-> EXYNOS UART1
#define		UART2TX_EXYNOS1					GPIO_Pin_2
#define		UART2TX_EXYNOS1_PinSource		GPIO_PinSource2
#define		UART2RX_EXYNOS1					GPIO_Pin_3
#define		UART2RX_EXYNOS1_PinSource		GPIO_PinSource3
#define		UART2_EXYNOS1_PORT				GPIOA

//	STM32 UART4 <-> EXYNOS UART4
#define		UART4TX_EXYNOS3					GPIO_Pin_0
#define		UART4TX_EXYNOS3_PinSource		GPIO_PinSource0
#define		UART4RX_EXYNOS3					GPIO_Pin_1
#define		UART4RX_EXYNOS3_PinSource		GPIO_PinSource1
#define		UART4_EXYNOS3_PORT				GPIOA

//	EXYNOS PWR_CTRL
#define		EXYNOS_PWR_CTRL					GPIO_Pin_12
#define		EXYNOS_PWR_CTRL_PORT			GPIOC

//	EXYNOS PMIC_CTRL
#define		EXYNOS_PMIC_CTRL				GPIO_Pin_2
#define		EXYNOS_PMIC_CTRL_PORT			GPIOD

//	Serial Flash -> STM32 Update (SPI1)
#define		SFLASH_SPI1_CS					GPIO_Pin_4
#define		SFLASH_SPI1_CS_PinSource		GPIO_PinSource4
#define		SFLASH_SPI1_SCK					GPIO_Pin_5
#define		SFLASH_SPI1_SCK_PinSource		GPIO_PinSource5

#define		SFLASH_SPI1_MISO				GPIO_Pin_6
#define		SFLASH_SPI1_MISO_PinSource		GPIO_PinSource6
#define		SFLASH_SPI1_MOSI				GPIO_Pin_7
#define		SFLASH_SPI1_MOSI_PinSource		GPIO_PinSource7
#define		SFLASH_SPI1_PORT				GPIOA

#define		SFLASH_HOLD						GPIO_Pin_11
#define		SFLASH_WP						GPIO_Pin_10
#define		SFLASH_PORT						GPIOC

//	TW8832 I2C2 Control
#define		TW8832_I2C2_SCL					GPIO_Pin_10
#define		TW8832_I2C2_SCL_PinSource		GPIO_PinSource10
#define		TW8832_I2C2_SDA					GPIO_Pin_11
#define		TW8832_I2C2_SDA_PinSource		GPIO_PinSource11
#define		TW8832_I2C2_PORT				GPIOB

//	TW8832 SPI2 Control/Serial Flash(OSD)
#define		TW8832_SFLASH_SPI2_CS			GPIO_Pin_12
#define		TW8832_SFLASH_SPI2_CS_PinSource	GPIO_PinSource12
#define		TW8832_SFLASH_SPI2_SCK			GPIO_Pin_13
#define		TW8832_SFLASH_SPI2_SCK_PinSource	GPIO_PinSource13
#define		TW8832_SFLASH_SPI2_MISO			GPIO_Pin_14
#define		TW8832_SFLASH_SPI2_MISO_PinSource	GPIO_PinSource14
#define		TW8832_SFLASH_SPI2_MOSI			GPIO_Pin_15
#define		TW8832_SFLASH_SPI2_MOSI_PinSource	GPIO_PinSource15
//#define	TW8832_SFLASH_SPI2_D2		    GPIO_Pin_0
//#define	TW8832_SFLASH_SPI2_D3		    GPIO_Pin_1
#define		TW8832_SFLASH_SPI2_PORT 		GPIOB
//#define	TW8832_SFLASH_SPI2_PORT2	    GPIOC

//	Hardware Version -> ADC
#define		HW_VERSION						GPIO_Pin_3
#define		HW_VERSION_PORT					GPIOC

//  KeySwitch -> GPIO 
#define 	KeySW0                 	 		GPIO_Pin_6  //  Input   ->  MENU
#define 	KeySW1                  		GPIO_Pin_7  //  Input   ->  LEFT
#define 	KeySW2                  		GPIO_Pin_8  //  Input   ->  ESC
#define 	KeySW3                  		GPIO_Pin_9  //  Input   ->  RIGHT
#define 	KeySW4                  		GPIO_Pin_10 //  Input   ->  ENTER
#define 	KeySWx_PORT             		GPIOF

//  POWER_IGMON -> GPIO, Input
#define 	PWR_IGMON               		GPIO_Pin_0  //  KeyIG Monitoring
#define 	PWR_IGMON_PORT          		GPIOB

//  POWER_CTRL -> GPIO, Output
#define 	PWR_CTRL                  		GPIO_Pin_1  //  System Main Power ON/OFF
#define 	PWR_CTRL_PORT             		GPIOB

//  LCD Power Enable -> GPIO
#define 	LCDPWR_CTRL            	 		GPIO_Pin_4
#define 	LCDPWR_PORT             		GPIOC

//  FW_UPDATE -> GPIO
#define 	FW_UPDATE               		GPIO_Pin_5
#define 	FW_UPDATE_PORT          		GPIOC

//	LCDBL -> PWM, GPIO
#define 	LCDBL_PWM               		GPIO_Pin_6
#define		LCDBL_PWM_PinSource				GPIO_PinSource6
#define 	LCDBL_CTRL	    	      		GPIO_Pin_7
#define 	LCDBL_PORT		         		GPIOC

//	LCD Display Control -> GPIO
#define 	LCD_STM32		          		GPIO_Pin_8
#define 	LCD_STM32_PORT		         	GPIOA
#define 	LCD_EXYNOS		          		GPIO_Pin_9
#define 	LCD_EXYNOS_PORT		         	GPIOC

//  BUZZER
#define 	BUZZER_CTRL                		GPIO_Pin_11
#define 	BUZZER_PORT             		GPIOG

//  LED Enable
#define 	LED_CTRL           				GPIO_Pin_15
#define 	LED_PORT	         			GPIOG

//	FM31X6(EEPROM) -> GPIO(I2C1)
#define 	FM31X4_I2C1_SCL    				GPIO_Pin_8
#define 	FM31X4_I2C1_SDA         		GPIO_Pin_9
#define 	FM31X4_I2C1_PORT				GPIOB

//	TW2835 -> GPIO
#define 	TW2835_IRQ						GPIO_Pin_6
#define		TW2835_HALE						GPIO_Pin_7
#define		TW2835_HSPB						GPIO_Pin_8
#define		TW2835_PORT						GPIOG

//	DPRAM -> GPIO
#define		DPRAM_INT						GPIO_Pin_13
#define		DPRAM_ADVL						GPIO_Pin_14
#define		DPRAM_PORT						GPIOC

#define		CAMERA_nRESET					GPIO_Pin_11
#define		CAMERA_nRESET_PORT				GPIOF

//  FSMC
#define		FSMC_nCLK						GPIO_Pin_3
#define		FSMC_nCLK_PinSource				GPIO_PinSource3
#define 	FSMC_nOE                		GPIO_Pin_4
#define 	FSMC_nOE_PinSource         		GPIO_PinSource4
#define 	FSMC_nWE                		GPIO_Pin_5
#define 	FSMC_nWE_PinSource         		GPIO_PinSource5
#define 	FSMC_nWAIT              		GPIO_Pin_6
#define 	FSMC_nWAIT_PinSource       		GPIO_PinSource6
#define 	FSMC_PORT               		GPIOD

#define		FSMC_nBL0						GPIO_Pin_0
#define		FSMC_nBL0_PinSource				GPIO_PinSource0
#define		FSMC_nBL1						GPIO_Pin_1
#define		FSMC_nBL1_PinSource				GPIO_PinSource1
#define		FSMC_nBL_PORT					GPIOE

#define 	FSMC_nNE1                		GPIO_Pin_7
#define 	FSMC_nNE1_PinSource        		GPIO_PinSource7
#define 	FSMC_nNE1_PORT           		GPIOD
#define 	FSMC_nNE2                		GPIO_Pin_9
#define 	FSMC_nNE2_PinSource        		GPIO_PinSource9
#define 	FSMC_nNE2_PORT           		GPIOG
#define 	FSMC_nNE3                		GPIO_Pin_10
#define 	FSMC_nNE3_PinSource        		GPIO_PinSource10
#define 	FSMC_nNE3_PORT           		GPIOG
#define 	FSMC_nNE4                		GPIO_Pin_12
#define 	FSMC_nNE4_PinSource        		GPIO_PinSource12
#define 	FSMC_nNE4_PORT           		GPIOG

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void RCC_Configuration(void);
extern void NVIC_Configuration(void);
extern void GPIO_Configuration(void);
extern void System_Configuration(void);
extern void GPIO_Configuration_NotUsed(void);
extern void System_Initialize(void);
extern void InitE2PROM(void);
#endif /* __SYSTEM_INIT_H */

