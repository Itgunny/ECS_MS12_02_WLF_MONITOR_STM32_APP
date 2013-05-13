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
#define STM32_BUZZER
/* Private define ------------------------------------------------------------*/
#define	Key_Menu			0x41
#define	Key_Left			0x42
#define	Key_Enter			0x44
#define	Key_Right			0x48
#define	Key_ESC			0x50
#define	Key_Info			0x60

#define	Key_CAM			0x81
#define	Key_Work_Load		0x82
#define	Key_EH_MODE		0x84
#define	Key_Ride_Control	0x88
#define	Key_Quick_Coupler	0x90
#define	Key_Auto_Grease	0xa0

#define	Key_Beacon			0xc1
#define	Key_Mirror_Heat		0xc2
#define	Key_Rear_Wiper		0xc4
#define	Key_USER			0xc8
#define	Key_Reserved1		0xd0
#define	Key_Reserved2		0xe0

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
                                                KEYSWITCH_ESC,    
                                                KEYSWITCH_RIGHT,    
                                                KEYSWITCH_ENTER,    
                                            };                                                
uint8_t     KeySwitchScan;
uint32_t    Temp_Value1, Temp_Value2, Temp_Value3, Temp_Cnt;
uint32_t	New_Value;

uint8_t		Test1 = 0, Test2 = 0;	

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void KeySwitch_SendToEXYNOS(uint8_t KeyValue, uint8_t ShortKey)
{
	uint8_t KeyValueBuffer[Serial_COM4_TxSize];
	uint8_t KeyValue_temp;

	//	KeyValue에 + 0x40을 한다. 
	//	윈도우에서 VK_A에서부터 순서대로 부여하기 위해서 더한다.
	//	연속키 일 경우, 0x40 + 0x30을 해서 0x70의 값을 만들어 내기 위해서..
	if(ShortKey)
	{
		if((KeyValue & 0xc0)==0x00)		KeyValue_temp = KeyValue+ 0x40;    // first line    
		else if((KeyValue & 0x40)==0x40)	KeyValue_temp = KeyValue+ 0x40;    // second line
		else if((KeyValue & 0x80)==0x80)	KeyValue_temp = KeyValue+ 0x40;    // third line
	}
	else
	{
		KeyValue_temp = KeyValue+ 0x40 + 0x20;    // first line    
	}
	KeyValueBuffer[0] = 0x02;				//	STX
	KeyValueBuffer[1] = KeyCMD;				//	KeyValue Command, 0x4B
	KeyValueBuffer[2] = KeyValue_temp ;	//	Key Value HexCode, 
	KeyValueBuffer[3] = 0x03;				//	ETX
	
    //  STM32에서 KeySwitch에 따른 BUZZER에 관한 명령을 MCU로 보내기 위해서 추가~
    
	if( KeyValue_temp == KEYSWITCH_RIGHT )
	{
		if( WL9FM_BUZZER.Status == 1 )
		{
			Uart2_RxMsg_Single_160[0] |= 0x10;
			Buzzer_Off();
		}
	}
	else if(KeyValue_temp == KEYSWITCH_CAM )
	{
		cam_mode_change();	
	}
	
	USARTx_EXYNOS(COM4, (char *)KeyValueBuffer);	

    DebugMsg_printf("KEYSWITCH %x\r\n", KeyValueBuffer[2]);
}


void RTC_SendToExynos(uint8_t Rtc_Hour, uint8_t Rtc_Min)
{
	uint8_t KeyValueBuffer[Serial_COM2_TxSize];

	KeyValueBuffer[0] = 0x02;				//	STX
	KeyValueBuffer[1] = (Rtc_Hour|0x80);				//	KeyValue Command, 0x4B
	KeyValueBuffer[2] = Rtc_Min;	//	Key Value HexCode, 
	KeyValueBuffer[3] = 0x03;				//	ETX
	
	USARTx_EXYNOS(COM4, (char *)KeyValueBuffer);	
}

void KeyTest_TEST(uint8_t value)
{
#if 1
	switch (value)
	{

		case 0x01:
			CameraMode(0,1);
			break;
		case 0x02:
			CameraMode(1,1);
			break;
		case 0x04:
			CameraMode(2,1);
			break;
		case 0x08:
			CameraMode(3,1);
			break;
		case 0x10:
			CameraMode(4,1);
			break;
		case 0x20:
			CameraMode(5,1);
			break;	
	}
#endif
}

/**
  * @brief  KeySwitch GPIO Reading & Value
  * @param  None
  * @retval None
  */
//  5msec 마다 실행.. -> stm32f10x_it.c -> TIM5_IRQHandler
void KeySwitch_Process(void)
{
	uint8_t i, j, k;
	uint32_t New_Value;
    

	
	if (KeySwitchScan == 0) 
	{
		Temp_Value1 = 0;

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_RESET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);					
	}
	else if (KeySwitchScan == 1) 
	{

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_RESET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);					
	}	
	else if (KeySwitchScan == 2) 
	{

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_RESET);					
	}	
	else
	{
		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
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

		New_Value <<= 1;    //  1Bit씩 Shitf하여 총 5Bit를 만든다.
		New_Value  += j;    //  0 or 1
	}

	//  KeySwitch Value 생성
	if ( (Temp_Value1 == 0) && (New_Value != 0) ) 
	{
		Temp_Value1 = New_Value+(KeySwitchScan<<6);
	}
    
	if (KeySwitchScan == 5)    //  25msec
	{
		if (Temp_Value1 == 0) Temp_Value3 = Temp_Cnt = 0;
		else
        	{
	            if (Temp_Value3 == Temp_Value1) //  눌려있던 키?
	            {
                		Temp_Cnt++;                 //  계속 눌려 있는가?
                
				if (Temp_Cnt == 4)          //  2번 연속 체크 되었을 때, 100msec
				{
					KeySwitch_Value = Temp_Value1;   

					//  STM32 BUZZER를 사용할 경우.. 버튼 클릭 
					#ifdef STM32_BUZZER
					Buzzer_Set(10);
					#endif

					KeySwitch_SendToEXYNOS(KeySwitch_Value,1);
					//KeyTest_TEST(KeySwitch_Value);
					//  디버깅할 때만 사용할 것
					//DebugMsg_printf("KEYSWITCH %x\r\n", KeySwitch_Value);
				}
				if (Temp_Cnt == 100)         //  10번 연속 체크 되었을 때
				{
					//  연속 스위치 루틴..                              
					KeySwitch_Value = Temp_Value1;   
					Temp_Cnt -= 5;
					
					if(KeySwitch_Value<0x20)
					{
						#ifdef STM32_BUZZER
							Buzzer_Set(10);
						#endif
						KeySwitch_SendToEXYNOS(KeySwitch_Value,0);
					}
				//KeyTest_TEST(KeySwitch_Value);

				//  디버깅할 때만 사용할 것
				//DebugMsg_printf("KEYSWITCH %x\r\n", KeySwitch_Value);
				}
			}
			else    //  순간적으로 눌렸는가?
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

    //  KeySwitch GPIO는 System_Init.c 에서 설정
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
