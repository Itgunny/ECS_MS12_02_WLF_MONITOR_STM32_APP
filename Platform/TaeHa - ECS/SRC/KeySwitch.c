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
//#define STM32_BUZZER
/* Private define ------------------------------------------------------------*/
#define	Key_Menu			0x01
#define	Key_Left			0x02
#define	Key_Enter			0x04
#define	Key_Right			0x08
#define	Key_ESC				0x10
#define	Key_Info			0x20

#define	Key_CAM			    0x41
#define	Key_Work_Load		0x42
#define	Key_EH_MODE		    0x44
#define	Key_Ride_Control	0x48
#define	Key_Quick_Coupler	0x50
#define	Key_Auto_Grease	    0x60

#define	Key_Beacon			0x81
#define	Key_Mirror_Heat		0x82
#define	Key_Rear_Wiper		0x84
#define	Key_USER			0x88
#define	Key_Reserved1		0x90
#define	Key_Reserved2		0xa0

#define	KEYSwitchSendCountMax	50

#define Bank1_SRAM1_ADDR  ((uint32_t)0x60000000) 


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
uint32_t    Temp_Value1, Temp_Value2, Temp_Value3,Temp_Value4, Temp_Cnt;
uint32_t	New_Value;
uint32_t	KeySwitchSendCount = 0;

uint8_t		Test1 = 0, Test2 = 0;	
uint16_t		test_buf[10];
uint16_t		test_rx_buf[10];

unsigned char rear_wiper_oper=0;

extern Realy_Control		rx_Realy_Control;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void KeySwitch_SendToEXYNOS(uint32_t KeyValue, uint8_t LongKey)
{
	uint8_t KeyValueBuffer[Serial_COM4_TxSize];
	uint8_t KeyValue_temp;

	
	memset(KeyValueBuffer, 0, Serial_COM4_TxSize * sizeof(uint8_t));

	
	KeyValueBuffer[0] = 0x02;				//	STX
	KeyValueBuffer[1] = KeyRES;				//	KeyValue Command, 
	KeyValueBuffer[2] = KeyValue & 0x000000FF;
	KeyValueBuffer[3] = ((KeyValue & 0x0000FF00) >> 8);
	KeyValueBuffer[4] = ((KeyValue & 0x00FF0000) >> 16);
	KeyValueBuffer[5] = LongKey ;			//	Key Value Short/Long Key, 
	
	KeyValueBuffer[Serial_COM4_TxSize-1] = 0x03;				//	ETX
	
   
////////////////////////// DPRAM TEST /////////////////////
#if 0
	else if( KeyValue_temp == KEYSWITCH_MENU) 
	{
		if(Test2==0)
		{
			for(Test1=0;Test1<10;Test1++)
			{
				test_buf[Test1]=Test1+0x30;
				test_rx_buf[Test1]=0;
			}
		}
		else if(Test2==1)
		{
			for(Test1=0;Test1<10;Test1++)
			{
				test_buf[Test1]=Test1+0x40;
				test_rx_buf[Test1]=0;
			}
		}
		else if(Test2==2)
		{
			for(Test1=0;Test1<10;Test1++)
			{
				test_buf[Test1]=Test1+0x50;
				test_rx_buf[Test1]=0;
			}
		}
		if(Test2++>2)	Test2=0;
		DPRAM_WriteBuffer(&test_buf[0],0x00,10);

		//memcpy(&test_buf[0], Bank1_SRAM1_ADDR,10);
		//*(uint16_t *) (Bank1_SRAM1_ADDR + 0) = 0x0505;
                
                //test_rx_buf[0]=*(uint16_t *) (Bank1_SRAM1_ADDR + 0);
                
                
		

	}
	else if( KeyValue_temp == KEYSWITCH_LEFT) 
	{
		DPRAM_ReadBuffer(&test_rx_buf[0],0x00,10);
		for(Test1=0;Test1<10;Test1++)
		{
			test_buf[Test1]=0;
		}
		//*(uint16_t *) (Bank1_SRAM1_ADDR + 0x02) = 0x0404;
                //test_rx_buf[1]=*(uint16_t *) (Bank1_SRAM1_ADDR + 2);

	}
#endif
	if(Change_UART4_for_Download==0)
		USARTx_EXYNOS(COM4, (char *)KeyValueBuffer);	

    DebugMsg_printf("KEYSWITCH %x\r\n", KeyValueBuffer[2]);
}

void SMK_SendToExynos(uint8_t SMK_Auth, uint8_t SMK_Msg, uint8_t SMK_Count)
{
	uint8_t KeyValueBuffer[Serial_COM4_TxSize];

	KeyValueBuffer[0] = 0x02;				//	STX
	KeyValueBuffer[1] = SMKRES;				
	KeyValueBuffer[2] = SMK_Auth;	
	KeyValueBuffer[3] = SMK_Msg;	
	KeyValueBuffer[4] = SMK_Count;	
	KeyValueBuffer[Serial_COM4_TxSize-1] = 0x03;				//	ETX

	if(Change_UART4_for_Download==0)
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

#if 0
void KeySwitch_Process(void)
{
	uint8_t i, j, k;
	uint32_t New_Value,temp_Value;

	temp_Value = 0;

	GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_RESET);
	GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_RESET);
	GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_RESET);	

	for (i = 0; i < MAXSWITCH; i++)
	{
		k = 0;	  
		k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 

		if (k == 0) j = 1;	  
		else		j = 0;

		temp_Value <<= 1;	//	1Bit씩 Shitf하여 총 5Bit를 만든다.
		temp_Value  += j;	//	0 or 1
	}

	if( temp_Value !=0)
	{
		if (KeySwitchScan == 0) 
		{
			GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_RESET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);	

			for (i = 0; i < MAXSWITCH; i++)
			{
				k = 0;	  
				k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 
		
				if (k == 0) j = 1;	  
				else		j = 0;
		
				New_Value <<= 1;	//	1Bit씩 Shitf하여 총 5Bit를 만든다.
				New_Value  += j;	//	0 or 1
			}
		}
		else if (KeySwitchScan == 1) 
		{
			GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_RESET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);		
			for (i = 0; i < MAXSWITCH; i++)
			{
				k = 0;	  
				k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 
		
				if (k == 0) j = 1;	  
				else		j = 0;
		
				New_Value <<= 1;	//	1Bit씩 Shitf하여 총 5Bit를 만든다.
				New_Value  += j;	//	0 or 1
			}
		}	
		else if (KeySwitchScan == 2) 
		{

			GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
			GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_RESET);
			for (i = 0; i < MAXSWITCH; i++)
			{
				k = 0;	  
				k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 
		
				if (k == 0) j = 1;	  
				else		j = 0;
		
				New_Value <<= 1;	//	1Bit씩 Shitf하여 총 5Bit를 만든다.
				New_Value  += j;	//	0 or 1
			}
		}	
		
		//	KeySwitch Press Check
		

		if ( (Temp_Value1 == 0) && (New_Value != 0) ) 
		{
			Temp_Value1 = New_Value+(KeySwitchScan<<6);
		}
	
		//if (KeySwitchScan == 2)    //  15msec
		{
			if (Temp_Value1 == 0) 
			{
				Temp_Value3 = Temp_Cnt = 0;
			}
			else
	        	{
		            if (Temp_Value3 == Temp_Value1) //  눌려있던 키?
		            {
	                		Temp_Cnt++;                 //  계속 눌려 있는가?
	                
					if (Temp_Cnt ==2)          //  3번 연속 체크 되었을 때, 45msec
					{
						KeySwitch_Value = Temp_Value1;   

						//  STM32 BUZZER를 사용할 경우.. 버튼 클릭 
						#ifdef STM32_BUZZER
						Buzzer_Set(10);
						#endif

						KeySwitch_SendToEXYNOS(KeySwitch_Value,1);
					}
					if (Temp_Cnt == 120)         //  10번 연속 체크 되었을 때
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
					}
				}
				else    //  순간적으로 눌렸는가?
				{
					Temp_Cnt    = 0;
					Temp_Value3 = Temp_Value1;
				}
			}
		}        

		if (++KeySwitchScan > 2) KeySwitchScan = 0;
	}
	else
	{
		Temp_Value1 = Temp_Value3 = Temp_Cnt =KeySwitchScan= 0;
	}
	//  KeySwitch Value 생성
	        
}
#endif 

#if 1


void KeySwitch_Process(void)
{
	uint8_t i, j, k;
	uint32_t New_Value;
	
	if (KeySwitchScan == 0) 
	{
		Temp_Value1 = 0;

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_RESET); //R
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);					
	}
	else if (KeySwitchScan == 1) 
	{

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_RESET); //R
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_SET);					
	}	
	else if (KeySwitchScan == 2) 
	{

		GPIO_WriteBit(KEYSWITCH_SCANPORT[0], KEYSWITCH_SCAN[0], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[1], KEYSWITCH_SCAN[1], Bit_SET);
		GPIO_WriteBit(KEYSWITCH_SCANPORT[2], KEYSWITCH_SCAN[2], Bit_RESET);//R				
	}	
	
	New_Value = 0;
	
	//  KeySwitch Press Check
	//Delay(100);
	
	for (i = 0; i < MAXSWITCH; i++)
	{
		k = 0;    
		k = GPIO_ReadInputDataBit(KEYSWITCH_INPUTPORT[i], KEYSWITCH_INPUT[i]); //  Read KeySwitch Input 

		if (k == 0) j = 1;    
		else        j = 0;

		New_Value <<= 1;    //  1Bit씩 Shitf하여 총 5Bit를 만든다.
		New_Value  += j;    //  0 or 1
	}

	
    if ( (Temp_Value1 == 0) && (New_Value != 0) ) 
    //if (New_Value != 0)
    {
        //Temp_Value1 = New_Value+(KeySwitchScan<<6);
        Temp_Value1 = New_Value << (KeySwitchScan * 8);
    }
        
    if(KeySwitchSendCount < KEYSwitchSendCountMax)
    {
		KeySwitchSendCount++;
	}
	if (KeySwitchScan == 2)    //  15msec
	{
              //  KeySwitch Value 생성
		if (Temp_Value1 == 0) 
		{
			if(KeySwitch_Value != 0)
			{
				KeySwitch_Value = Temp_Value3 = Temp_Cnt = 0;	
				KeySwitch_SendToEXYNOS(KeySwitch_Value,0);
			}
			KeySwitch_Value = Temp_Value3 = Temp_Cnt = 0;		
		}
		else
        {
            if (Temp_Value3 == Temp_Value1) //  눌려있던 키?
            {
            	Temp_Cnt++;                 //  계속 눌려 있는가?
            
				if (Temp_Cnt ==3)          //  3번 연속 체크 되었을 때, 45msec
				{
					KeySwitch_Value = Temp_Value1;   

					//  STM32 BUZZER를 사용할 경우.. 버튼 클릭 
					#ifdef STM32_BUZZER
					Buzzer_Set(10);
					#endif

					if(KeySwitchSendCount >= KEYSwitchSendCountMax)
					{
						KeySwitch_SendToEXYNOS(KeySwitch_Value,0);
						KeySwitchSendCount = 0;
					}
					
				}

				if(Temp_Value3 == 0x00020000)
				{
					
					if (Temp_Cnt == 100)         //  10번 연속 체크 되었을 때
					{
						//  연속 스위치 루틴..                              
						KeySwitch_Value = Temp_Value1;   
						Temp_Cnt -= 50;
						
						//if(KeySwitch_Value<0x20)
						{
							#ifdef STM32_BUZZER
							Buzzer_Set(10);
							#endif
							if(KeySwitchSendCount >= KEYSwitchSendCountMax)
							{
								KeySwitch_SendToEXYNOS(KeySwitch_Value,1);
								KeySwitchSendCount = 0;
							}
						}
					}
				}
				else
				{
					if (Temp_Cnt == 300)         //  10번 연속 체크 되었을 때
					{
						//  연속 스위치 루틴..                              
						KeySwitch_Value = Temp_Value1;   
						Temp_Cnt -= 50;
						
						//if(KeySwitch_Value<0x20)
						{
							#ifdef STM32_BUZZER
								Buzzer_Set(10);
							#endif
							if(KeySwitchSendCount >= KEYSwitchSendCountMax)
							{
								KeySwitch_SendToEXYNOS(KeySwitch_Value,1);
								KeySwitchSendCount = 0;
							}
						}
					}
				}
				
			}
			else    //  순간적으로 눌렸는가?
			{
				Temp_Cnt    = 0;
				Temp_Value3 = Temp_Value1;
			}
		}
	}        

	if (++KeySwitchScan > 2) KeySwitchScan = 0;        
}
#endif


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

    TIM_TimeBaseStructure.TIM_Period        = 0x9c4;   	//  (1 / 1MHz) * 5000 -> 5msec

	//TIM_TimeBaseStructure.TIM_Period        = 0x4e2;   	//  (1 / 0.5MHz) * 2500 -> 5msec

	//TIM_TimeBaseStructure.TIM_Period        = 0x271; 

	TIM_TimeBaseStructure.TIM_Prescaler     = 0xA8;     //  84 MHz / 168 = 1MHz
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
