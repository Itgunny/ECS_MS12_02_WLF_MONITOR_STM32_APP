/**
  ******************************************************************************
  * @file    System_Init.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   System_Init.c module
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

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Init_RTC(void)
{
    WL9FM_RTC.Year   = 0;
	WL9FM_RTC.Month  = 1;
	WL9FM_RTC.Date   = 1;
	WL9FM_RTC.Day    = 1;
	WL9FM_RTC.Hour   = 12;
	WL9FM_RTC.Minute = 0;
	WL9FM_RTC.Second = 0;

	WRITE_RTC(WL9FM_RTC);
}

void InitE2PROM(void)
{
	u8 i;
	u8 tmpBuf1[8];
	u8 tmpBuf2[8];
	u8 tmpBuf3[8];
	u8 tmpBuf4[21];
	
	SaveE2PROM1 = (WL9FM_SaveE2PROM1*)&tmpBuf1[0];
	SaveE2PROM2 = (WL9FM_SaveE2PROM2*)&tmpBuf2[0];
	SaveE2PROM3 = (WL9FM_SaveE2PROM3*)&tmpBuf3[0];
	SaveE2PROMoniInfo = (WL9FM_SaveE2PROMoniInfo*)&tmpBuf4[0];

	SaveE2PROM1->WorkLoad 				= 0;
	SaveE2PROM1->testWorkLoad 			= 0;
	SaveE2PROM1->Unit 					= 3;	//	섭씨 ( C ) , km/h
	SaveE2PROM1->DispType	 			= 0;
	SaveE2PROM1->InfoViewPriority 		= 0;
	SaveE2PROM1->UnitPressure 			= 0;
	SaveE2PROM1->Reserved0 				= 0;
	SaveE2PROM1->Lang 					= 0;
	SaveE2PROM1->ManualBackLight 		= 7;
	SaveE2PROM1->AutoBackLight 			= 0;
	SaveE2PROM1->TopInfoView 			= 1;	// 	Hyd Temp
	SaveE2PROM1->BottomInfoView 		= 3;	// 	Cool Temp
	SaveE2PROM1->InfoViewCnt 			= 2;
	SaveE2PROM1->HR_Start 				= 0;
	SaveE2PROM1->RearCamReverseMode 	= 0;	// 	Off
	SaveE2PROM1->ActiveCamNum 			= 1;
	SaveE2PROM1->FirstCam 				= 0;
	SaveE2PROM1->SecondCam 				= 1;
	SaveE2PROM1->ThirdCam 				= 2;
	SaveE2PROM1->Reserved1 				= 0;

	SaveE2PROM2->LightMode 				= 0;
	SaveE2PROM2->JobTimeView 			= 0;
	SaveE2PROM2->OdoMeterView 			= 0;
	SaveE2PROM2->JobOdoSelect 			= 0;
	SaveE2PROM2->LightLowTime 			= 8;
	SaveE2PROM2->LightUpperTime 		= 16;
	SaveE2PROM2->AutoLightDay 			= 0;
	SaveE2PROM2->AutoLightNight 		= 0;
	SaveE2PROM2->Reserved1 				= 0;

	SaveE2PROM3->Phone_1  				= 0;
	SaveE2PROM3->Phone_2  				= 8;
	SaveE2PROM3->Phone_3  				= 0;
	SaveE2PROM3->Phone_4  				= 5;
	SaveE2PROM3->Phone_5  				= 5;
	SaveE2PROM3->Phone_6  				= 5;
	SaveE2PROM3->Phone_7  				= 8;
	SaveE2PROM3->Phone_8  				= 2;
	SaveE2PROM3->Phone_9  				= 7;
	SaveE2PROM3->Phone_10 				= 2;
	SaveE2PROM3->Phone_11 				= 0xf;
	SaveE2PROM3->Phone_12 				= 0xf;

#if 1	// Monitor Change History - temp
	SaveE2PROMoniInfo->ManufactureYear  = 0;
	SaveE2PROMoniInfo->ManufactureMonth = 0;
	SaveE2PROMoniInfo->ManufactureDay   = 0;
	SaveE2PROMoniInfo->MoniPorgramVer   = 0;
	SaveE2PROMoniInfo->MoniSerialNo[0]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[1]  = 0;	// 9
	SaveE2PROMoniInfo->MoniSerialNo[2]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[3]  = 0;	// 8
	SaveE2PROMoniInfo->MoniSerialNo[4]  = 0;	// M
	SaveE2PROMoniInfo->MoniSerialNo[5]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[6]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[7]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[8]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[9]  = 0;	// 0
	SaveE2PROMoniInfo->MoniSerialNo[10] = 0;	// *
	SaveE2PROMoniInfo->MoniModel[0]     = 0;	// N
	SaveE2PROMoniInfo->MoniModel[1]     = 0;	// -
	SaveE2PROMoniInfo->MoniModel[2]     = 0;	// H
	SaveE2PROMoniInfo->MoniModel[3]     = 0;	// -
	SaveE2PROMoniInfo->MoniModel[4]     = 0;	// W
	SaveE2PROMoniInfo->MoniModel[5]     = 0;	// *
#endif

	SerialPutString("\n\rInitialize : 10 %%\n\r");

	EEPROM_Write(0, 0);	// tmp
	EEPROM_Write(0, 0);	// tmp
	EEPROM_Write(0, 0);	// tmp

	for(i = 0 ; i < 8 ; i++)
	{
		EEPROM_Write(i+8, tmpBuf1[i]);
		TimeDelay_msec(5);
		EEPROM_Write(i+16, tmpBuf2[i]);
		TimeDelay_msec(5);
		EEPROM_Write(i+24, tmpBuf3[i]);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 30 %%\n\r");
	
#if 1	// Monitor Change History - temp
	for(i = 0 ; i < 21 ; i++)
	{
		EEPROM_Write(i+50, tmpBuf4[i]);
		TimeDelay_msec(5);
	}
#endif

	for(i = 0 ; i < 79 ; i++)
	{
		EEPROM_Write(i+100, 0xff);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 60 %%\n\r");

	for(i = 0 ; i < 30 ; i++)
	{
		EEPROM_Write(i+200, 0xff);
		TimeDelay_msec(5);
	}

	for(i = 0 ; i < 29 ; i++)
	{
		EEPROM_Write(i+230, 0xff);
		TimeDelay_msec(5);
	}

	SerialPutString("Initialize : 95 %%\n\r");
	Init_RTC();
	SerialPutString("Initialize : 100 %%\n\r\n\r");
}

void ReadE2PROM_ToSend()
{
#if 0
	u8 i;

	adc_value = (ADC1->DR & 0x0000FFFF);
	
	i = EepromRead(0);	
	i = EepromRead(0);
	i = EepromRead(0);
    i = 0;
    
	adc_value = (ADC1->DR & 0x0000FFFF);

	for(i = 0 ; i < 24 ; i++)
		eepRomReadData1[i] = EepromRead(i+8);

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_Save_Data1[i] = eepRomReadData1[i];

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_Save_Data2[i] = eepRomReadData1[i+8];

	for(i = 0 ; i < 8 ; i++)
		Uart3_RxMsg_AS_Phone_Data[i] = eepRomReadData1[i+16];

	for(i = 0 ; i < 21 ; i++)
		MoniInfoData[i] = EepromRead(i+50);
	
	for(i = 0 ; i < 79 ; i++)
		McuInfoData1[i] = EepromRead(i+100);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData2[i] = EepromRead(i+200);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData3[i] = EepromRead(i+210);

	for(i = 0 ; i < 4 ; i++)
		McuInfoData4[i] = EepromRead(i+220);

	memset(&tmpMcuInfoData[1] , 0xff, 77);
	memcpy((u8*)&tmpMcuInfoData[0], (u8*)&McuInfoData1[0], 5);
	memcpy((u8*)&tmpMcuInfoData[5], (u8*)&McuInfoData2[0], 4);
	memcpy((u8*)&tmpMcuInfoData[9], (u8*)&McuInfoData3[0], 4);
	memcpy((u8*)&tmpMcuInfoData[13], (u8*)&McuInfoData4[0], 4);


	adc_value = (ADC1->DR & 0x0000FFFF);
	
	eepRomReadData1[12] = (adc_value & 0xff);
	eepRomReadData1[13] = (adc_value & 0xff00) >> 8;
//	DebugMsg_printf("%2x %2x\r\n", eepRomReadData1[13], eepRomReadData1[12]);

	System_PowerIG(PowerIG_ON);
#endif
}

/**
  * @brief  Clock Setting.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
	RCC_ClocksTypeDef RCC_Clocks;

  	//	SysTick end of count event each 1ms
  	RCC_GetClocksFreq(&RCC_Clocks);

	//	SysTick Timer을 사용하려면, 아래의 설정을 해야되고, 아래의 설정값은 1msec 설정이다.
	#if 1		
	//	Setup SysTick Timer for 1 msec interrupts
	if (SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000))
	{ 
	    /* Capture error */ 
    	while (1);
  	}
	#endif
	
	RCC_ClockSecuritySystemCmd(ENABLE);

/**
  * @brief  Enables or disables the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.   
  * @param  RCC_AHBPeriph: specifies the AHB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB1Periph_GPIOA:       GPIOA clock
  *            @arg RCC_AHB1Periph_GPIOB:       GPIOB clock 
  *            @arg RCC_AHB1Periph_GPIOC:       GPIOC clock
  *            @arg RCC_AHB1Periph_GPIOD:       GPIOD clock
  *            @arg RCC_AHB1Periph_GPIOE:       GPIOE clock
  *            @arg RCC_AHB1Periph_GPIOF:       GPIOF clock
  *            @arg RCC_AHB1Periph_GPIOG:       GPIOG clock
  *            @arg RCC_AHB1Periph_GPIOG:       GPIOG clock
  *            @arg RCC_AHB1Periph_GPIOI:       GPIOI clock
  *            @arg RCC_AHB1Periph_CRC:         CRC clock
  *            @arg RCC_AHB1Periph_BKPSRAM:     BKPSRAM interface clock
  *            @arg RCC_AHB1Periph_CCMDATARAMEN CCM data RAM interface clock
  *            @arg RCC_AHB1Periph_DMA1:        DMA1 clock
  *            @arg RCC_AHB1Periph_DMA2:        DMA2 clock
  *            @arg RCC_AHB1Periph_ETH_MAC:     Ethernet MAC clock
  *            @arg RCC_AHB1Periph_ETH_MAC_Tx:  Ethernet Transmission clock
  *            @arg RCC_AHB1Periph_ETH_MAC_Rx:  Ethernet Reception clock
  *            @arg RCC_AHB1Periph_ETH_MAC_PTP: Ethernet PTP clock
  *            @arg RCC_AHB1Periph_OTG_HS:      USB OTG HS clock
  *            @arg RCC_AHB1Periph_OTG_HS_ULPI: USB OTG HS ULPI clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

/**
  * @brief  Enables or disables the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @param  RCC_AHBPeriph: specifies the AHB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB2Periph_DCMI:   DCMI clock
  *            @arg RCC_AHB2Periph_CRYP:   CRYP clock
  *            @arg RCC_AHB2Periph_HASH:   HASH clock
  *            @arg RCC_AHB2Periph_RNG:    RNG clock
  *            @arg RCC_AHB2Periph_OTG_FS: USB OTG FS clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
	//RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState)

/**
  * @brief  Enables or disables the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @param  RCC_AHBPeriph: specifies the AHB3 peripheral to gates its clock.
  *          This parameter must be: RCC_AHB3Periph_FSMC
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it. 
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB1Periph_TIM2:   TIM2 clock
  *            @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *            @arg RCC_APB1Periph_TIM4:   TIM4 clock
  *            @arg RCC_APB1Periph_TIM5:   TIM5 clock
  *            @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *            @arg RCC_APB1Periph_TIM7:   TIM7 clock
  *            @arg RCC_APB1Periph_TIM12:  TIM12 clock
  *            @arg RCC_APB1Periph_TIM13:  TIM13 clock
  *            @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *            @arg RCC_APB1Periph_WWDG:   WWDG clock
  *            @arg RCC_APB1Periph_SPI2:   SPI2 clock
  *            @arg RCC_APB1Periph_SPI3:   SPI3 clock
  *            @arg RCC_APB1Periph_USART2: USART2 clock
  *            @arg RCC_APB1Periph_USART3: USART3 clock
  *            @arg RCC_APB1Periph_UART4:  UART4 clock
  *            @arg RCC_APB1Periph_UART5:  UART5 clock
  *            @arg RCC_APB1Periph_I2C1:   I2C1 clock
  *            @arg RCC_APB1Periph_I2C2:   I2C2 clock
  *            @arg RCC_APB1Periph_I2C3:   I2C3 clock
  *            @arg RCC_APB1Periph_CAN1:   CAN1 clock
  *            @arg RCC_APB1Periph_CAN2:   CAN2 clock
  *            @arg RCC_APB1Periph_PWR:    PWR clock
  *            @arg RCC_APB1Periph_DAC:    DAC clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4  , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2  , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1  , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2  , ENABLE);

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_APB2Periph_TIM1:   TIM1 clock
  *            @arg RCC_APB2Periph_TIM8:   TIM8 clock
  *            @arg RCC_APB2Periph_USART1: USART1 clock
  *            @arg RCC_APB2Periph_USART6: USART6 clock
  *            @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *            @arg RCC_APB2Periph_ADC2:   ADC2 clock
  *            @arg RCC_APB2Periph_ADC3:   ADC3 clock
  *            @arg RCC_APB2Periph_SDIO:   SDIO clock
  *            @arg RCC_APB2Periph_SPI1:   SPI1 clock
  *            @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *            @arg RCC_APB2Periph_TIM9:   TIM9 clock
  *            @arg RCC_APB2Periph_TIM10:  TIM10 clock
  *            @arg RCC_APB2Periph_TIM11:  TIM11 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  NVIC Setting.
  * @param  Configures Vector Table base location.
  * @retval None
  */
void NVIC_Configuration(void)
{
	//	Set the Vector Table base location at 0x08004000
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);   
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  GPIO Setting.
  * @param  Configures the different GPIO ports.
  * @retval None
  */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;


    //  Configure UART1 pins: DEBUG_UART1TX, DEBUG_UART1RX 
    //  UART1은 Debugging으로 사용한다. 이미 설정되어 있음.
    #if 0

    GPIO_InitStructure.GPIO_Pin   = DEBUG_UART1TX | DEBUG_UART1RX;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_UART1_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(DEBUG_UART1_PORT, DEBUG_UART1TX_PinSource, GPIO_AF_USART1);
	GPIO_PinAFConfig(DEBUG_UART1_PORT, DEBUG_UART1RX_PinSource, GPIO_AF_USART1);
	
    #endif    
   
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

	//	STM32 UART2 <-> EXYNOS UART1
    GPIO_InitStructure.GPIO_Pin   = UART2TX_EXYNOS1 | UART2RX_EXYNOS1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART2_EXYNOS1_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART2_EXYNOS1_PORT, UART2TX_EXYNOS1_PinSource, GPIO_AF_USART2);
	GPIO_PinAFConfig(UART2_EXYNOS1_PORT, UART2RX_EXYNOS1_PinSource, GPIO_AF_USART2);

	//	STM32 UART4 <-> EXYNOS UART3
    GPIO_InitStructure.GPIO_Pin   = UART4TX_EXYNOS3 | UART4RX_EXYNOS3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART4_EXYNOS3_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART4_EXYNOS3_PORT, UART4TX_EXYNOS3_PinSource, GPIO_AF_USART2);
	GPIO_PinAFConfig(UART4_EXYNOS3_PORT, UART4RX_EXYNOS3_PinSource, GPIO_AF_USART2);
	
	//  EXYNOS PWR_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = EXYNOS_PWR_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(EXYNOS_PWR_CTRL_PORT, &GPIO_InitStructure);

	//  EXYNOS PMIC_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = EXYNOS_PMIC_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(EXYNOS_PMIC_CTRL_PORT, &GPIO_InitStructure);

	//	Serial Flash -> STM32 Update (SPI1)
    GPIO_InitStructure.GPIO_Pin   = SFLASH_SPI1_CS | SFLASH_SPI1_SCK | SFLASH_SPI1_MISO | SFLASH_SPI1_MOSI;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SFLASH_SPI1_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SFLASH_SPI1_PORT, SFLASH_SPI1_CS_PinSource, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SFLASH_SPI1_PORT, SFLASH_SPI1_SCK_PinSource, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SFLASH_SPI1_PORT, SFLASH_SPI1_MISO_PinSource, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SFLASH_SPI1_PORT, SFLASH_SPI1_MOSI_PinSource, GPIO_AF_SPI1);

    GPIO_InitStructure.GPIO_Pin   = SFLASH_HOLD | SFLASH_WP;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SFLASH_PORT, &GPIO_InitStructure);
	
	//	TW8832 -> I2C2
	//  GPIO로 I2C2 사용
    //  Alternate Function 사용안함
	#if 0
	GPIO_InitStructure.GPIO_Pin   = TW8832_I2C2_SCL | TW8832_I2C2_SDA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TW8832_I2C2_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TW8832_I2C2_PORT, TW8832_I2C2_SCL_PinSource, GPIO_AF_I2C2);
	GPIO_PinAFConfig(TW8832_I2C2_PORT, TW8832_I2C2_SDA_PinSource, GPIO_AF_I2C2);
	#else
	GPIO_InitStructure.GPIO_Pin   = TW8832_I2C2_SCL | TW8832_I2C2_SDA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TW8832_I2C2_PORT, &GPIO_InitStructure);
	#endif
	
	//	TW8832 SPI2 Control/Serial Flash(OSD)
    GPIO_InitStructure.GPIO_Pin   = TW8832_SFLASH_SPI2_CS | TW8832_SFLASH_SPI2_SCK | TW8832_SFLASH_SPI2_MISO | TW8832_SFLASH_SPI2_MOSI;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TW8832_SFLASH_SPI2_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TW8832_SFLASH_SPI2_PORT, TW8832_SFLASH_SPI2_CS_PinSource, GPIO_AF_SPI2);
	GPIO_PinAFConfig(TW8832_SFLASH_SPI2_PORT, TW8832_SFLASH_SPI2_SCK_PinSource, GPIO_AF_SPI2);
	GPIO_PinAFConfig(TW8832_SFLASH_SPI2_PORT, TW8832_SFLASH_SPI2_MISO_PinSource, GPIO_AF_SPI2);
	GPIO_PinAFConfig(TW8832_SFLASH_SPI2_PORT, TW8832_SFLASH_SPI2_MOSI_PinSource, GPIO_AF_SPI2);

	//	Hardware Version -> ADC
    GPIO_InitStructure.GPIO_Pin   = HW_VERSION;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;   
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(HW_VERSION_PORT, &GPIO_InitStructure);

	//	KeySwitch -> GPIO Input
    GPIO_InitStructure.GPIO_Pin   = KeySW0 | KeySW1 | KeySW2 | KeySW3 | KeySW4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KeySWx_PORT, &GPIO_InitStructure);

	//  POWER_IGMON -> GPIO Input
    GPIO_InitStructure.GPIO_Pin   = PWR_IGMON;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PWR_IGMON_PORT, &GPIO_InitStructure);
	
	//  POWER_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = PWR_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PWR_CTRL_PORT, &GPIO_InitStructure);

	//  LCDPWR_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = LCDPWR_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCDPWR_PORT, &GPIO_InitStructure);

	//  FW_UPDATE -> GPIO Input
    GPIO_InitStructure.GPIO_Pin   = FW_UPDATE;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FW_UPDATE_PORT, &GPIO_InitStructure);
	
	//	LCDBL_PWM -> PWM
    GPIO_InitStructure.GPIO_Pin   = LCDBL_PWM;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(LCDBL_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(LCDBL_PORT, LCDBL_PWM_PinSource, GPIO_AF_TIM8);

	//  LCDBL_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = LCDBL_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCDBL_PORT, &GPIO_InitStructure);
	
	//  LCD_STM32 -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = LCD_STM32;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_STM32_PORT, &GPIO_InitStructure);

	//  LCD_EXYNOS -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = LCD_EXYNOS;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_EXYNOS_PORT, &GPIO_InitStructure);

	//  BUZZER_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = BUZZER_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);

	//  LED_CTRL -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = LED_CTRL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

	//  FM31X4(EEPROM) -> GPIO Output
	//  GPIO로 I2C1 사용
    //  Alternate Function 사용안함
    GPIO_InitStructure.GPIO_Pin   = FM31X4_I2C1_SCL | FM31X4_I2C1_SDA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(FM31X4_I2C1_PORT, &GPIO_InitStructure);
	
	//  TW2835 -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = TW2835_IRQ| TW2835_HALE | TW2835_HSPB;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TW2835_PORT, &GPIO_InitStructure);

	//  DPRAM -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = DPRAM_INT | DPRAM_ADVL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DPRAM_PORT, &GPIO_InitStructure);

	//  CAMERA nRESET -> GPIO Output
    GPIO_InitStructure.GPIO_Pin   = CAMERA_nRESET;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAMERA_nRESET_PORT, &GPIO_InitStructure);


    // 	FSMC Data Line
    //  D15 ~ D0 : D15  D14  D13 D12  D11  D10  D9   D8   D7   D6  D5  D4  D3  D2  D1   D0   
    //             PD10 PD9  PD8 PE15 PE14 PE13 PE12 PE11 PE10 PE9 PE8 PE7 PD1 PD0 PD15 PD14
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10| GPIO_Pin_9  | GPIO_Pin_8 | GPIO_Pin_1 |
                                    GPIO_Pin_0 | GPIO_Pin_15 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);	
  
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 |
                                    GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9  |
                                    GPIO_Pin_8  | GPIO_Pin_7;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);	
	
    //  FSMC Address Line
    //  A25 ~ A10 : A25  A24   A23  A22  A21  A20  A19  A18  A17  A16  A15 A14 A13 A12 A11 A10
    //              PG14 PG13  PE2  PE6  PE5  PE4  PE3  PD13 PD12 PD11 PG5 PG4 PG3 PG2 PG1 PG0           
    //  A9  ~ A0  : A9   A8   A7   A6   A5  A4  A3  A2  A1  A0
    //              PF15 PF14 PF13 PF12 PF5 PF4 PF3 PF2 PF1 PF0

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 |
                                    GPIO_Pin_5  | GPIO_Pin_4  | GPIO_Pin_3  | GPIO_Pin_2  |
                                    GPIO_Pin_1  | GPIO_Pin_0;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC);
	
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_5 |
                                    GPIO_Pin_4  | GPIO_Pin_3  | GPIO_Pin_2 |
    	                            GPIO_Pin_1  | GPIO_Pin_0;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource3 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource2 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1 , GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0 , GPIO_AF_FSMC);
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_FSMC);	

    //  nCLK, nOE, nWE, nWait
    GPIO_InitStructure.GPIO_Pin = FSMC_nOE | FSMC_nWE | FSMC_nWAIT | FSMC_nCLK;
    GPIO_Init(FSMC_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(FSMC_PORT, FSMC_nOE_PinSource  , GPIO_AF_FSMC);
	GPIO_PinAFConfig(FSMC_PORT, FSMC_nWE_PinSource  , GPIO_AF_FSMC);
	GPIO_PinAFConfig(FSMC_PORT, FSMC_nWAIT_PinSource, GPIO_AF_FSMC);	 
	GPIO_PinAFConfig(FSMC_PORT, FSMC_nCLK_PinSource , GPIO_AF_FSMC);

    //  nBL0, nBL1
    GPIO_InitStructure.GPIO_Pin = FSMC_nBL0 | FSMC_nBL1;
    GPIO_Init(FSMC_nBL_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(FSMC_nBL_PORT, FSMC_nBL0_PinSource  , GPIO_AF_FSMC);
	GPIO_PinAFConfig(FSMC_nBL_PORT, FSMC_nBL1_PinSource  , GPIO_AF_FSMC);
    
    // NE1, NE2, NE3, NE4 configuration
    GPIO_InitStructure.GPIO_Pin = FSMC_nNE1;
    GPIO_Init(FSMC_nNE1_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(FSMC_nNE1_PORT, FSMC_nNE1_PinSource  , GPIO_AF_FSMC);
	
    GPIO_InitStructure.GPIO_Pin = FSMC_nNE2;
    GPIO_Init(FSMC_nNE2_PORT, &GPIO_InitStructure);    

	GPIO_PinAFConfig(FSMC_nNE2_PORT, FSMC_nNE2_PinSource  , GPIO_AF_FSMC);
    
    GPIO_InitStructure.GPIO_Pin = FSMC_nNE3;
    GPIO_Init(FSMC_nNE3_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(FSMC_nNE3_PORT, FSMC_nNE3_PinSource  , GPIO_AF_FSMC);
    
    GPIO_InitStructure.GPIO_Pin = FSMC_nNE4;
    GPIO_Init(FSMC_nNE4_PORT, &GPIO_InitStructure);    

	GPIO_PinAFConfig(FSMC_nNE4_PORT, FSMC_nNE4_PinSource  , GPIO_AF_FSMC);

    //  사용하지 않는 GPIO Pin은 Output -> Low 상태로 만들어 놓는다.
    GPIO_Configuration_NotUsed();
}

/**
  * @brief  GPIO Setting.
  * @param  Configures the different GPIO ports. (사용하지 않는 GPIO는 Output Low 상태로 만든다.)
  * @retval None
  */
void GPIO_Configuration_NotUsed(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	//  PC2
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	//  PC8
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	//  PB7
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	//  PC15
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    GPIO_ResetBits(GPIOC, GPIO_Pin_2);
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);
    GPIO_ResetBits(GPIOC, GPIO_Pin_15);
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);	
}

/**
  * @brief  Hardware, Software System Configuration.
  * @param  None
  * @retval None
  */
void System_Configuration(void)
{
	RCC_Configuration();		    // 	Configure the system clocks
	NVIC_Configuration();		    //	NVIC Configuration
	GPIO_Configuration();		    // 	Configure the GPIO ports
}

void System_Initialize(void)
{
	//  PWR_CTRL -> BootLoader에서는 Sub Power Enable을 Off 
    GPIO_ResetBits(PWR_CTRL_PORT, PWR_CTRL);   	//	24V Power Enable 
                                                //  Set   : Power Enable On
                                                //  Reset : Power Enable Off    	

    //  LCDPWR_CTRL -> BootLoader에서는 VLCD12 Power Enable을 Off 
    GPIO_ResetBits(LCDPWR_PORT, LCDPWR_CTRL);  	//	LCD Power Enable 
                                                //  Set   : LCD Power Enable 
                                                //  Reset : LCD Power Disable	

	//  BootLoader Bootting시에, LCDBL는 Off 상태로 만든다.
    GPIO_ResetBits(LCDBL_PORT, LCDBL_CTRL);	    //	LCD BackLight Power On/Off (LCDBL_CTRL)
                                               	//  Set   : BackLight Power On
                                               	//  Reset : BackLight Power Off			
                                               	
    GPIO_ResetBits(BUZZER_PORT, BUZZER_CTRL);	//	BUZZER Off
                                                //  Set   : BUZZER On
                                                //  Reset : BUZZER Off
  
    GPIO_ResetBits(LED_PORT, LED_CTRL);			//	LED Enable Off
                                                //  Set   : LED Enable  -> On
                                                //  Reset : LED Disable -> Off

    GPIO_ResetBits(EXYNOS_PWR_CTRL_PORT, EXYNOS_PWR_CTRL);	//	Exynos-4412 Power On/Off
                                                			//  Set   : Exynos-4412 -> Power On
                                                			//  Reset : Exynos-4412 -> Power Off
                                                			
    GPIO_ResetBits(EXYNOS_PMIC_CTRL_PORT, EXYNOS_PMIC_CTRL);	//	Exynos-4412 PMIC On/Off
                                                				//  PMIC On  : Low -> High
                                                				//       Off : Low -> High

    GPIO_SetBits(LCD_EXYNOS_PORT, LCD_EXYNOS);	//	Exynos-4412 LCD Display
                                                //  Set   : HI-Z
                                                //  Reset : Display
	                                                				
    GPIO_ResetBits(LCD_STM32_PORT, LCD_STM32);	//	STM32 LCD Display
                                                //  Set   : HI-Z
                                                //  Reset : Display
	
	GPIO_ResetBits(CAMERA_nRESET_PORT, CAMERA_nRESET);	//	CAMERA nRESET
		                                                //  Set   : On
        		                                        //  Reset : Off												
}

void System_Variable_Init(void)
{
	memset((void *)(&WL9FM_TIME),       	0x0, sizeof(WL9F_TIME_DATA));
    memset((void *)(&WL9FM_RTC),            0x0, sizeof(WL9F_DATA_RTC));	
    memset((void *)(&WL9FM_BUZZER),         0x0, sizeof(WL9FM_BUZZER_DATA));	
    memset((void *)(&WL9FM_LCDBL),          0x0, sizeof(WL9FM_LCDBL_DATA));	

	
}

void WL9FM_EXYNOS_POWER_ONOFF(uint8_t BitData)
{
	GPIO_WriteBit(EXYNOS_PWR_CTRL_PORT, EXYNOS_PWR_CTRL, (BitAction) BitData);
}

void WL9FM_EXYNOS_PMIC_ONOFF(void)
{
	GPIO_WriteBit(EXYNOS_PMIC_CTRL_PORT, EXYNOS_PMIC_CTRL, Bit_SET);
	TimeDelay_msec(100);
	GPIO_WriteBit(EXYNOS_PMIC_CTRL_PORT, EXYNOS_PMIC_CTRL, Bit_RESET);
	TimeDelay_msec(100);
}

void WL9FM_CAMERA_nRESET(void)
{
	GPIO_WriteBit(CAMERA_nRESET_PORT, CAMERA_nRESET, Bit_RESET);
	TimeDelay_msec(100);
	GPIO_WriteBit(CAMERA_nRESET_PORT, CAMERA_nRESET, Bit_SET);
}

void WL9F_System_Init_Start(void)
{
	WL9FM_EXYNOS_POWER_ONOFF(EXYNOS_POWER_ON);	//	EXYNOS-4412 Power On..
	//WL9FM_EXYNOS_PMIC_ONOFF();
	
	Hardware_Version_Init();	//  ->  Hardware_Version.c (Hardware Version ADC Start)
	Buzzer_Init();              //  ->  Buzzer.c (Buzzer Timer Start)
	FM3164_Watchdog_Init(0x00);	//  ->  FM31X4.c (Integrated Processor Companion ON)
	KeySwitch_Init();           //  ->  KeySwitch.c
	
	LED_POWER_ONOFF(LED_ON);	//	->	LCD_Control.c (LED On/Off)
	LCD_POWER_ONOFF(LCDPWR_ON);	//	-> 	LCD_Control.c (LCD 12V Power On/Off)

	WL9FM_CAMERA_nRESET();		//	-> 	TW2835, TW8832 Power On..
	LCD_CONTROL_Init();			//	-> 	LCD_Control.c (LCDBL, ON/OFF)
	TW2835_Control_Init();		//	-> 	TW2835_Control.c (CAMERA -> Decoder)
	TW8832_Control_Init();		//	-> 	TW8832_Control.c (LCD Interface)

//    System_PowerIG(PowerIG_OFF);	//  PowerIG를 OFF로 만들어 놓고, EEPROM을 READ -> 거기서 ON으로 만든다.
    
	//InitE2PROM();
	ReadE2PROM_ToSend();		//	-> EEPROM Data Read
}


/*********(C) COPYRIGHT 2013 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/


