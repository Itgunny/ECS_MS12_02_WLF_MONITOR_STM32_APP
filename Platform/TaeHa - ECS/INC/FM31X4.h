/**
  ******************************************************************************
  * @file    FM31X4.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for FM31X4.c module
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
#ifndef __FM31X4_H
#define __FM31X4_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Display_APP.h" 

/* Private typedef -----------------------------------------------------------*/
#pragma pack(1)
typedef struct
{
    unsigned char   Year;
    unsigned char   Month;
    unsigned char   Date;
    unsigned char   Day;
    unsigned char   Hour;
    unsigned char   Minute;
    unsigned char   Second;
} WL9F_DATA_RTC;
#pragma pack()

#pragma pack(1)
typedef struct 
{
	uint8_t         Brightness;
	uint8_t         Language:4;
	uint8_t         SpeedUnit:2;
	uint8_t         UsePassword:1;
	uint8_t         UseMaintenance:1;
	uint8_t         PasswordData[5];
	uint8_t         Maintenance[5];
	uint8_t         PwrMode;
	uint8_t         Turtle;
	uint8_t         HourCounter;
	uint32_t        Maintenance_ORG;
} WL9FM_DATA_EEPROM;
#pragma pack()

#pragma pack(1)
typedef struct
{
	u8 WorkLoad:2;		// ¾ç»ê   ²¨Áü / ÄÑÁü   0, 1
	u8 testWorkLoad:2;	// Å×½ºÆ® ²¨Áü / ÄÑÁü   0, 1
	u8 Unit:4;
	u8 DispType:2;
	u8 InfoViewPriority:2;
	u8 UnitPressure:2;
	u8 Reserved0:2;
	u8 Lang;
	u8 ManualBackLight;
	u8 AutoBackLight;
	u8 TopInfoView:4;
	u8 BottomInfoView:4;
	u8 InfoViewCnt:2;
	u8 HR_Start:2;
	u8 RearCamReverseMode:2;
	u8 ActiveCamNum:2;
	u8 FirstCam:2;
	u8 SecondCam:2;
	u8 ThirdCam:2;
	u8 Reserved1:2;
}WL9FM_SaveE2PROM1;
#pragma pack()

#pragma pack(1)
typedef struct
{
	u8 LightMode:2;
	u8 JobTimeView:2;
	u8 OdoMeterView:2;
	u8 JobOdoSelect:2;
	u8 LightLowTime;
	u8 LightUpperTime;
	u8 AutoLightDay:4;
	u8 AutoLightNight:4;
	u32 Reserved1;
} WL9FM_SaveE2PROM2;
#pragma pack()

#pragma pack(1)
typedef struct
{
	u8 Phone_1:4;
	u8 Phone_2:4;
	u8 Phone_3:4;
	u8 Phone_4:4;
	u8 Phone_5:4;
	u8 Phone_6:4;
	u8 Phone_7:4;
	u8 Phone_8:4;
	u8 Phone_9:4;
	u8 Phone_10:4;
	u8 Phone_11:4;
	u8 Phone_12:4;
} WL9FM_SaveE2PROM3;
#pragma pack()

#pragma pack(1)
typedef struct
{
	u8 ManufactureYear;
	u8 ManufactureMonth;
	u8 ManufactureDay;
	u8 MoniPorgramVer;
	u8 MoniSerialNo[11];
	u8 MoniModel[6];
} WL9FM_SaveE2PROMoniInfo;
#pragma pack()

/* Private define ------------------------------------------------------------*/

#define SCL0					GPIO_ResetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SCL)
#define SCL1					GPIO_SetBits(FM31X4_I2C1_PORT, FM31X4_I2C1_SCL)
#define SDA_READ				GPIO_ReadInputDataBit(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA)

#define SDAIN   				EEPROM_PortChange(0)
#define SDAOUT  				EEPROM_PortChange(1) 


//	EEPROM Address & Map
#define ADDR_RTC_YEAR			0x08	//	RTC Year
#define ADDR_RTC_MONTH			0x07	//	RTC Month
#define ADDR_RTC_DATE			0x06	//	RTC Date
#define ADDR_RTC_DAY			0x05	//	RTC Day
#define ADDR_RTC_HOUR			0x04	//	RTC Hour
#define ADDR_RTC_MINUTE	    	0x03	//	RTC Minute
#define ADDR_RTC_SECOND	    	0x02	//	RTC Second

#define ADDR_LCDTYPE			0x10	//	LCD Type Address
#define ADDR_LCDBL	    		0x11	//	LCD BackLight Address

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern WL9FM_SaveE2PROM1		*SaveE2PROM1;
extern WL9FM_SaveE2PROM2		*SaveE2PROM2;
extern WL9FM_SaveE2PROM3		*SaveE2PROM3;
extern WL9FM_SaveE2PROMoniInfo	*SaveE2PROMoniInfo;

extern WL9F_DATA_RTC   	    	WL9FM_RTC;
extern WL9FM_DATA_EEPROM		WL9FM_DATASAVE;

/* Exported functions ------------------------------------------------------- */
extern void EEPROM_PortChange(unsigned char dir);
extern void EEPROM_ByteWrite ( unsigned char WData );
extern void EEPROM_Write ( unsigned long Add, unsigned char WData );
extern void EEPROM_PageWrite ( unsigned long Add, unsigned char *WData, unsigned char No );
extern void EEPROM_PageRead ( unsigned long Add, unsigned char *RData, unsigned char NoC );
extern void FM3164_Watchdog_Init(unsigned char watchdog);
extern void FM3164_Restart(void);

extern unsigned char EEPROM_Read ( unsigned long Add );

extern void WRITE_FM31xx_RTC_Companion(unsigned char address, unsigned char data);
extern void WRITE_RTC_Year(unsigned char data);
extern void WRITE_RTC_Month(unsigned char data);
extern void WRITE_RTC_Date(unsigned char data);
extern void WRITE_RTC_Day(unsigned char data);
extern void WRITE_RTC_Hour(unsigned char data);
extern void WRITE_RTC_Minute(unsigned char data);
extern void WRITE_RTC_Second(unsigned char data);

extern unsigned char READ_FM31xx_RTC_Companion(unsigned char Add);
extern unsigned char READ_RTC_Year(void);
extern unsigned char READ_RTC_Month(void);
extern unsigned char READ_RTC_Date(void);
extern unsigned char READ_RTC_Day(void);
extern unsigned char READ_RTC_Hour(void);
extern unsigned char READ_RTC_Minute(void);
extern unsigned char READ_RTC_Second(void);

extern void WRITE_RTC(WL9F_DATA_RTC RTC_Data);
extern void READ_RTC(WL9F_DATA_RTC *RTC_Data);

extern void InitEEPROM(void);

#endif /* __FM31X4_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/


