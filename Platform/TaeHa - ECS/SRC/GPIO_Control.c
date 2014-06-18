/**
  ******************************************************************************
  * @file    GPIO_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   GPIO_Control.c module
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

void WL9FM_EXYNOS_POWER_ONOFF(uint8_t BitData)
{
	GPIO_WriteBit(EXYNOS_PWR_CTRL_PORT, EXYNOS_PWR_CTRL, (BitAction) BitData);
}

void WL9FM_EXYNOS_PMIC_ONOFF(void)
{
	GPIO_WriteBit(EXYNOS_PMIC_CTRL_PORT, EXYNOS_PMIC_CTRL, Bit_SET);
	TimeDelay_msec(100);
	GPIO_WriteBit(EXYNOS_PMIC_CTRL_PORT, EXYNOS_PMIC_CTRL, Bit_RESET);
	//TimeDelay_msec(100);
}

void WL9FM_CAMERA_nRESET(void)
{
	GPIO_WriteBit(CAMERA_nRESET_PORT, CAMERA_nRESET, Bit_RESET);
	TimeDelay_msec(100);
	GPIO_WriteBit(CAMERA_nRESET_PORT, CAMERA_nRESET, Bit_SET);
}

void WL9FM_PowerIG(uint8_t BitData)
{
    GPIO_WriteBit(PWR_CTRL_PORT, PWR_CTRL, (BitAction) BitData);
}

uint8_t WL9FM_GetPowerIG(void)
{
    return GPIO_ReadInputDataBit(PWR_IGMON_PORT, PWR_IGMON);
}



/*********(C) COPYRIGHT 2013 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
