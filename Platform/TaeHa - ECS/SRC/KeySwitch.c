/**
  ******************************************************************************
  * @file    KeySwitch.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   KeySwitch.c module
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
//  KeySwitch.h -> KeySwitch Input GPIO Port array
GPIO_TypeDef*  KEYSWITCH_PORT[MAXSWITCH]   =   {  
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT, 
                                                KeySWx_PORT,
                                            };

//  KeySwitch.h -> KeySwitch Input GPIO Pin array
const uint16_t KEYSWITCH_PIN[MAXSWITCH]    =   { 
                                                KeySW0, 
                                                KeySW1, 
                                                KeySW2, 
                                                KeySW3,
                                                KeySW4,
                                            };

//  KeySwitch.h -> Press Input KeySwitch Value array
const uint8_t KEYSWITCH_VALUE[MAXSWITCH]   =   {
                                                KEYSWITCH_MENU,    
                                                KEYSWITCH_LEFT,    
                                                KEYSWITCH_ESC_CAM,    
                                                KEYSWITCH_RIGHT,    
                                                KEYSWITCH_ENTER,    
                                            };                                                

uint8_t     KeySwitchScan;
uint8_t     Temp_Value1, Temp_Value2, Temp_Value3, Temp_Cnt;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void KeyTest(uint8_t Test)
{
	Buzzer_Set(10);
	
	switch (Test)
	{
		case KEYSWITCH_MENU :
				
				break;

		case KEYSWITCH_LEFT :

				break;

		case KEYSWITCH_ESC_CAM :

				break;

		case KEYSWITCH_RIGHT :

				break;

		case KEYSWITCH_ENTER :

				break;

	}	
}

/**
  * @brief  KeySwitch GPIO Reading & Value
  * @param  None
  * @retval None
  */
//  5msec ���� ����.. -> stm32f10x_it.c -> TIM5_IRQHandler
void KeySwitch_Process(void)
{
    uint8_t i, j, k;
    uint8_t New_Value;
    

    if (KeySwitchScan == 0) Temp_Value1 = 0;
    
    New_Value = 0;
    
    //  KeySwitch Press Check
    for (i = 0; i < MAXSWITCH; i++)
    {
        k = 0;    
        k = GPIO_ReadInputDataBit(KEYSWITCH_PORT[i], KEYSWITCH_PIN[i]); //  Read KeySwitch Input 
        
        if (k == 0) j = 1;    
        else        j = 0;
        
        New_Value <<= 1;    //  1Bit�� Shitf�Ͽ� �� 5Bit�� �����.
        New_Value  += j;    //  0 or 1
    }

    //  KeySwitch Value ����
    if ( (Temp_Value1 == 0) && (New_Value != 0) ) 
    {
		Temp_Value1 = New_Value;
	}
    
    if (KeySwitchScan == 3)    //  5msec
    {
        if (Temp_Value1 == 0) Temp_Value3 = Temp_Cnt = 0;
        else
        {
            if (Temp_Value3 == Temp_Value1) //  �����ִ� Ű?
            {
                Temp_Cnt++;                 //  ��� ���� �ִ°�?
                
                if (Temp_Cnt == 3)          //  2�� ���� üũ �Ǿ��� ��, 45msec
                {
                    KeySwitch_Value = Temp_Value1;   

                    //  STM32 BUZZER�� ����� ���.. ��ư Ŭ�� 
                    #ifdef STM32_BUZZER
                        Buzzer_Set(10);
                    #endif

					//KeySwitch_SendToSPICA(KeySwitch_Value);
					KeyTest(KeySwitch_Value);
					
                    //  ������� ���� ����� ��
                    //DebugMsg_printf("KEYSWITCH %x\r\n", KeySwitch_Value);
                }
                if (Temp_Cnt == 10)         //  10�� ���� üũ �Ǿ��� ��
                {
					//  ���� ����ġ ��ƾ..                              
                    KeySwitch_Value = Temp_Value1;   
					Temp_Cnt -= 5;
					
                    //  STM32 BUZZER�� ����� ���.. ��ư Ŭ�� 
                    #ifdef STM32_BUZZER
                        Buzzer_Set(10);
                    #endif

					//	����Ű �� ���, 0x40 + 0x30�� �ؼ� 0x70�� ���� ����� ���� ���ؼ�..
					//KeySwitch_SendToSPICA(KeySwitch_Value + Continuous_Key);
					KeyTest(KeySwitch_Value);
					
                    //  ������� ���� ����� ��
                    //DebugMsg_printf("KEYSWITCH %x\r\n", KeySwitch_Value);
                }
            }
            else    //  ���������� ���ȴ°�?
            {
                Temp_Cnt    = 0;
                Temp_Value3 = Temp_Value1;
            }
        }
    }        

    if (++KeySwitchScan > 5) KeySwitchScan = 0;        
}

void KeySwitch_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;

    DebugMsg_printf("++ KeySwitch (TIM5 : 5msec), TIM5_IRQn Initialize START\r\n");

    //  KeySwitch GPIO�� System_Init.c ���� ����
    #if 0

    GPIO_InitTypeDef    GPIO_InitStructure;
    
	//	KeySwitch -> GPIO Input
    GPIO_InitStructure.GPIO_Pin   = KeySW0 | KeySW1 | KeySW2 | KeySW3 | KeySW4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KeySWx_PORT, &GPIO_InitStructure);
    
    #endif

    TIM_TimeBaseStructure.TIM_Period        = 0x9C4;   	//  (1 / 1MHz) * 5000 -> 5msec
    TIM_TimeBaseStructure.TIM_Prescaler     = 0xA8;     //  168 MHz / 168 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    
    //  TIM5 Enable counter
    TIM_Cmd(TIM5, ENABLE);
    
    //  Enable TIM5 Update Interrupt
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

    //  Enable the TIM5 Interrupt, KeySwitch
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    DebugMsg_printf("-- KeySwitch (TIM5 : 5msec), TIM5_IRQn Initialize END\r\n");
    
    KeySwitch_Value = 0;	
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
