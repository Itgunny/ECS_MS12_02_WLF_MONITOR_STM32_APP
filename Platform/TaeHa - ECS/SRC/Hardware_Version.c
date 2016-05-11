/**
  ******************************************************************************
  * @file    Hardware_Version.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Hardware_Version.c module
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
uint16_t ADC3ConvertedValue = 0;
uint8_t Hardware_Revision=0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : ADC_Configuration
* Description    : Configure the ADC.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

// ++, sys3215, 141211
void ADC_Configuration(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	ADC_DeInit();
	
	/* ADC Common Init **********************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);


	/* ADC2 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);


	/* ADC2 regular channel12 configuration *************************************/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_3Cycles);


	/* Enable ADC2 */
	ADC_Cmd(ADC1, ENABLE);


	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

}


void Check_Hardware_Revision(void)
{
	ADC3ConvertedValue = ADC_GetConversionValue(ADC1) ; //first

//	if(ADC3ConvertedValue>390 && ADC3ConvertedValue<420) // R5 = 9.1K RevD.02.01
//	{
//		Hardware_Revision = REVD_02_01;
//	}
//	else //if(ADC3ConvertedValue>357 && ADC3ConvertedValue<387) // R5 = 10K RevB       372
//	{
//		Hardware_Revision = REVB;
//	}
	if(ADC3ConvertedValue>357 && ADC3ConvertedValue<387) // R5 = 10K RevB		372
	{
		Hardware_Revision = REVB;
	}
	// ++, 160511 bwk
	else if(ADC3ConvertedValue>1092 && ADC3ConvertedValue<1122) // R5 = 2.7K RevH		1107
	{
		Hardware_Revision = REVH;
	}
	// --, 160511 bwk
	else //if(ADC3ConvertedValue>390 && ADC3ConvertedValue<420) // R5 = 9.1K RevD.02.01
	{
		Hardware_Revision = REVD_02_01;
	}

	// ++, 160511 bwk
	if(Hardware_Revision >= REVH)
	{
		write_RTC_Companion(0xf, 0x0);
		TimeDelay_msec(100);
		write_RTC_Companion(0xf, 0x20);
	}
	// --, 160511 bwk
	
}
// --, sys3215, 141211

/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void Hardware_Version_Init(void)
{
	DebugMsg_printf("++ Hardware_Version (ADC : IN13), ADC Initialize START\r\n");

	ADC_Configuration();

	// ++, sys3215, 141211
	Check_Hardware_Revision();
	// --, sys3215, 141211
	
	DebugMsg_printf("-- Hardware_Version (ADC : IN13), ADC Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
