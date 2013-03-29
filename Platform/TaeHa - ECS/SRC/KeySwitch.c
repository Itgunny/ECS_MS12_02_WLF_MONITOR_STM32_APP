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
//  KeySwitch.h -> KeySwitch Scan, Input GPIO Port array
GPIO_TypeDef*  KEYSWITCH_SCANPORT[MAXSCAN]	=   {  
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT, 
                                            };

GPIO_TypeDef*  KEYSWITCH_INPUTPORT[MAXINPUT]	=   {  
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT, 
                                                KeySWXX_PORT,
                                                KeySWXX_PORT,                                                
                                            };

//  KeySwitch.h -> KeySwitch Scan, Input GPIO Pin array
const uint16_t KEYSWITCH_SCAN[MAXSCAN]  =   { 
                                                KeySCAN0, 
                                                KeySCAN1, 
                                                KeySCAN2, 
                                            };

const uint16_t KEYSWITCH_INPUT[MAXINPUT]  =   { 
                                                KeyInput0, 
                                                KeyInput1, 
                                                KeyInput2, 
                                                KeyInput3,
                                                KeyInput4,
                                                KeyInput5,
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
uint32_t    Temp_Value1, Temp_Value2, Temp_Value3, Temp_Cnt;
uint32_t	New_Value;

uint8_t		Test1 = 0, Test2 = 0;	

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void KeyTest_TEST(uint8_t value)
{
		switch (value)
		{
			case 0x01 :

					Buzzer_Set(10);					
					
					CameraMode(Test1 , 1);

					if (Test1++ > 6)
					{
						Test1 = 0;
					}	

					break;

			case 0x02 :
					Buzzer_Set(10);					

					if (Test2 != 0)
					{
						Test2 = 0;
						LCD_Display_Change(EXYNOS_DISPLAY);
					}
					else
					{
						Test2 = 1;
						LCD_Display_Change(STM32F4_DISPLAY);
					}

					break;

			case 0x04 :

					//Buzzer_Set(25);					

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
    

    if (KeySwitchScan == 0) 
	{
		Temp_Value1 = 0;

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_RESET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);					
    }	

	New_Value = 0;
	
    //  KeySwitch Press Check
    for (i = 0; i < MAXSWITCH; i++)
    {
        k = 0;    
        k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 
        
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
					KeyTest_TEST(KeySwitch_Value);
					
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
					//KeyTest_TEST(KeySwitch_Value);
					
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
    
	//	KeySwitch Matrix -> GPIO Output
	GPIO_InitStructure.GPIO_Pin   = KeySCAN0 | KeySCAN1 | KeySCAN2;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KeySWXX_PORT, &GPIO_InitStructure);

	//	KeySwitch Matrix -> GPIO Input
	GPIO_InitStructure.GPIO_Pin   = KeyInput0 | KeyInput1 | KeyInput2 | KeyInput3 | KeyInput4 | KeyInput5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KeySWXX_PORT, &GPIO_InitStructure);
	
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
