/**
  ******************************************************************************
  * @file    TW2835_Control.h
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW2835_Control.c module
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
#ifndef __TW2835_Control_H
#define __TW2835_Control_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define nGCS3_TW2835_ADDR       			((uint32_t)0x68000000)
#define nGCS4_TW2835_ADDR       			((uint32_t)0x6C000000)

#define nGCS3_TW2835_ADDR_SHIFT(A) 			(nGCS3_TW2835_ADDR + (2 * (A)))
#define nGCS4_TW2835_ADDR_SHIFT(A) 			(nGCS4_TW2835_ADDR + (2 * (A)))

#if 1
	#define nGCS3_TW2835_WRITE(Data)  			(*(__IO uint16_t *)(nGCS3_TW2835_ADDR) = (Data))
	#define nGCS3_TW2835_READ  					(*(__IO uint16_t *)(nGCS3_TW2835_ADDR))

	#define nGCS4_TW2835_WRITE(Data)  			(*(__IO uint16_t *)(nGCS4_TW2835_ADDR) = (Data))
	#define nGCS4_TW2835_READ  					(*(__IO uint16_t *)(nGCS4_TW2835_ADDR))
#else
	#define nGCS3_TW2835_WRITE(Address, Data)  	(*(__IO uint16_t *)(Address) = (Data))
	#define nGCS3_TW2835_READ  					((*(__IO uint16_t *)(nGCS3_TW2835_ADDR))

	#define nGCS4_TW2835_WRITE(Address, Data)  	(*(__IO uint16_t *)(Address) = (Data))
	#define nGCS4_TW2835_READ  					((*(__IO uint16_t *)(nGCS4_TW2835_ADDR))
#endif

#define	BIT0					(0x0001)
#define	BIT1					(0x0002)
#define	BIT2					(0x0004)
#define	BIT3					(0x0008)
#define	BIT4					(0x0010)
#define	BIT5					(0x0020)
#define	BIT6					(0x0040)
#define	BIT7					(0x0080)
#define	BIT8					(0x0100)
#define	BIT9					(0x0200)
#define	BIT10					(0x0400)
#define	BIT11					(0x0800)
#define	BIT12					(0x1000)
#define	BIT13					(0x2000)
#define	BIT14					(0x4000)
#define	BIT15					(0x8000)

//==================================================================================
#define U8  					unsigned char
#define U16 					unsigned int
#define S8  					signed char
#define S16 					signed int

//==================================================================================
#define	ON						1
#define	OFF						0

//==================================================================================
#define	SetBit(x,y)				((x) |= (y))         
#define	ClearBit(x,y)			((x) &= ~(y))        
#define	BitSet(x,y)				(((x)&(y))== (y))    
#define	BitClear(x,y)			(((x)&(y))== 0)      
#define	IfBitSet(x,y)			if(((x)&(y)) == (y)) 
#define	IfBitClear(x,y)			if(((x)&(y)) == 0)

//==================================================================================
#define	DLY_FOR(x)				for(_dly_=0;_dly_<(x);_dly_++)
#define	DLY_I2C					60		//... SCL : 80 kHz at 4.7 kΩ
#define	DLY_PRLL_TBL			50
#define	DLY_IO					5
#define	DLY_SW_STRB				20000//10

//==================================================================================
#define	LOSS_MODE_BYPS			0
#define	LOSS_MODE_FRZ			1
#define	LOSS_MODE_BLAK			2
#define	LOSS_MODE_BLK_FRZ		3

//==================================================================================

//==================================================================================
#define	VDO_NTSC				0
#define	VDO_PAL					1

#define	CH_SRC_LV				0
#define	CH_SRC_PB				1

#define	RC_MD_120_FPS			0
#define	RC_MD_240_FPS			1
#define	RC_MD_480_FPS			2
//==================================================================================

#define	ALL_CHIP				(0xff)
#define	MASTER					(0x03)
#define	SLAVE1					(0x0c)
#define	SLAVE2					(0x30)
#define	SLAVE3					(0xc0)

#define	DVC_PG0					0
#define	DVC_PG1					1
#define	DVC_PG2					2

#define	PTH_X					BIT0
#define	PTH_Y					BIT1
#define	PTH_PB					BIT2
#define	PTH_ALL					(PTH_X|PTH_Y)

#define INIT_PUBLICS
#define I2C_PUBLICS

//==================================================================================
//						Host definition & variable description
//==================================================================================

#define	HSPB_SET				GPIO_SetBits(TW2835_PORT, TW2835_HSPB)
#define	HSPB_RESET				GPIO_ResetBits(TW2835_PORT, TW2835_HSPB)

#define	HALE_SET				GPIO_SetBits(TW2835_PORT, TW2835_HALE)
#define	HALE_RESET				GPIO_ResetBits(TW2835_PORT, TW2835_HALE)

#define	HWRB_SET				GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define	HWRB_RESET				GPIO_ResetBits(GPIOD, GPIO_Pin_5)

#define	HRDB_SET				GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define	HRDB_RESET				GPIO_ResetBits(GPIOD, GPIO_Pin_4)

#if 0
#define	HCSB1_SET				GPIO_SetBits(GPIOG, GPIO_Pin_12)
#define	HCSB1_RESET				GPIO_ResetBits(GPIOG, GPIO_Pin_12)

#define	HCSB0_SET				GPIO_SetBits(GPIOG, GPIO_Pin_10)
#define	HCSB0_RESET				GPIO_ResetBits(GPIOG, GPIO_Pin_10)

#else

#define	HCSB1_SET				GPIO_SetBits(FSMC_nNE4_PORT, FSMC_nNE4)
#define	HCSB1_RESET				GPIO_ResetBits(FSMC_nNE4_PORT, FSMC_nNE4)

#define	HCSB0_SET				GPIO_SetBits(FSMC_nNE3_PORT, FSMC_nNE3)
#define	HCSB0_RESET				GPIO_ResetBits(FSMC_nNE3_PORT, FSMC_nNE3)

#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if 0
extern struct	{					//	struct cmn_flg Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//  Bit  Access 
            u8 b_cmn_tmp:1;	    	//  Bit 7     
            u8 b_cmn_NA:1;       	//  Bit 6     
            u8 b_cmn_prtcl_bsy:1;	//  Bit 5     
            u8 b_cmn_irq:1;		    //  Bit 4     
            u8 b_cmn_wndw_mn:1;		//  Bit 3     
            u8 b_cmn_wndw_pop:1;	//  Bit 2     
          	u8 b_cmn_jp_vdo:2;	    //  Bit 1     
           	u8 b_cmn_dtct_vs:1;		//  Bit 0     
          	
      	}	BIT;					
	}		ST;						
}			cmn_flg;

extern struct	{					//	struct cmn_flg_cnt Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//	Bit  Access 
       	    u8 b_cmn_NA:1;	    	//  Bit 7     
            u8 b_cmn_cnt_1s:1;	    //  Bit 6     
            u8 b_cmn_cnt_05s:1;	    //  Bit 5     
            u8 b_cmn_cnt_02s:1;		//  Bit 4     
            u8 b_cmn_cnt_01s:1;		//  Bit 3     
            u8 b_cmn_cnt_tgl:1;	    //  Bit 2     
          	u8 b_cmn_cnt_fld:2;	    //  Bit 1     
           	u8 b_cmn_cnt_vs:1;		//  Bit 0     
          	
      	}	BIT;						
	}		ST;							
}			cmn_flg_cnt;

extern struct	{					//	struct wndw_flg_ds Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//  Bit  Access 
            u8 b_ds_wth_cif:1;	    //  Bit 7     
            u8 b_ds_wth_4pb:1;	    //  Bit 6     
            u8 b_ds_wth_16pb:1;		//  Bit 5     
            u8 b_ds_wth_rc:1;		//  Bit 4     
            u8 b_ds_in_run:2;	    //  Bit 3     
           	u8 b_ds_in_auto:1;		//  Bit 2     
           	u8 b_cmn_NA:2;	    	//  Bit 0~1
          	
      	}	BIT;					
	}		ST;						
}			wndw_flg_ds;

extern struct	{					//	struct wndw_flg Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//  Bit  Access 
       	    u8 b_ch_src:1;	    	//    Bit 7     
            u8 b_ado_lv_mr:1;	    //    Bit 6     
            u8 b_ado_lv_mr_arw_pb:1;//    Bit 5     
            u8 b_cmn_NA:5;  		//    Bit 4~0     
            
      	}	BIT;					
	}		ST;						
}			wndw_flg;
#endif

extern u8	cmn_bot;

extern u8	cmn_cnt_vs;
extern u8	cmn_cnt_vs_sub;
extern u8 	cmn_vga_det;			//... __WTH_VGA__일때 idata 없애면 compile시 error 발생.

extern u8	cmn_dvc;
extern u8	cmn_lst_slvr_x;
extern u8	cmn_lst_slvr_y;
extern u8	cmn_max_ch;

/* Exported functions ------------------------------------------------------- */
extern void TW2835_Control_Init(void);


extern void	SetAsicFlgType(U8 _dvc, U8 _pg, U8 _addr, U8 _flg, U8 _data);

extern void WriteAsicByteOSD(u8 _dvc, u8 _addr, u8 _wdat);
extern void WriteAsicTableOSD(u8 _dvc, u8 _addr, u8 *_tbl_ptr);
extern void WriteAsicByte(u8 _dvc, u8 _pg, u8 _addr, u8 _wdat);
extern void WriteAsicTable(u8 _dvc, u8 _pg, u8 _addr, u8 *_tbl_ptr, u16 _tbl_cnt);
extern u8 ReadAsicByte(u8 _dvc, u8 _pg, u8 _addr);
extern void ReadAsicTable(u8 _dvc, u8 _pg, u8 _addr, u16 _data_cnt);
extern u8	ReadAsicOSDMemWr(u8 _dvc);

extern void InitPg0(void);
extern void InitPg1(void);
extern void InitPg2(void);
extern void InitVdo(void);

extern void Port_Change(u8 in_Dir);
extern void Write_TW2835(u8 Data);
extern u8 Read_TW2835();


extern unsigned char	tbl_ntsc_pg0_cmn[];
extern unsigned char	tbl_ntsc_pg0_sfr1[];
extern unsigned char	tbl_ntsc_pg0_sfr2[];
extern unsigned char	tbl_ntsc_pg0_scl[];
extern unsigned char	tbl_ntsc_pg0_sfr3[];
extern unsigned char	tbl_pal_pg0_cmn[];
extern unsigned char	tbl_pal_pg0_sfr1[];
extern unsigned char	tbl_pal_pg0_sfr2[];
extern unsigned char	tbl_pal_pg0_scl[];
extern unsigned char	tbl_pal_pg0_sfr3[];

extern unsigned char 	Register_Table_Page0[];

//==================================================================================
//						Page1 initialize table description
//==================================================================================
extern unsigned char	tbl_pg1_x_cmn[];
extern unsigned char	tbl_ntsc_pg1_pic_fl[];
extern unsigned char	tbl_ntsc_pg1_pic_qd[];
extern unsigned char	tbl_ntsc_pg1_pic_9_lt[];
extern unsigned char	tbl_ntsc_pg1_pic_9_rb[];
extern unsigned char	tbl_pal_pg1_pic_fl[];
extern unsigned char	tbl_pal_pg1_pic_qd[];
extern unsigned char	tbl_pal_pg1_pic_9_lt[];
extern unsigned char	tbl_pal_pg1_pic_9_rb[];
extern unsigned char	tbl_pg1_y_cmn[];
extern unsigned char	tbl_ntsc_pg1_enc[];
extern unsigned char	tbl_pal_pg1_enc[];

extern unsigned char 	Register_Table_Page1[];
//==================================================================================
//						Page2 initialize table description
//==================================================================================

extern unsigned char	tbl_pg2_mse_box[];
extern unsigned char	tbl_ntsc_pg2_2dbox[];
extern unsigned char	tbl_ntsc_pg2_mtn[];

extern unsigned char	tbl_pal_pg2_2dbox[];
extern unsigned char	tbl_pal_pg2_mtn[];

#endif /* __TW2835_Control_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
