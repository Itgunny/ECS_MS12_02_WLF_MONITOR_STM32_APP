/**
  ******************************************************************************
  * @file    TW2835_OSD.h 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   Header for TW2835_OSD.c module
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
#ifndef __TW2835_OSD_H
#define __TW2835_OSD_H

/* Includes ------------------------------------------------------------------*/
#include "WL9F_Monitor_APP.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//==================================================================================
//						OSD definition & variable description
//==================================================================================
#define	OSD_RDO_BLK				0x04//(0x68)
#define	OSD_RDO_CHK				0x05//(0x69)
#define	OSD_CHK_BOX_BLK			0x06//(0x6a)
#define	OSD_CHK_BOX_CHK			0x07//(0x6b)

#define	OSD_R_UPPER				('R'-0x20)
#define	OSD_W_UPPER				('W'-0x20)
#define	OSD_W_SML				(0x57)//(0x63)//
#define	OSD_B_LOWER				('b'-0x20)
#define	OSD_H_LOWER				('h'-0x20)
#define	OSD_PLUS_SML			('+'-0x20)
#define	OSD_PLUS_BIG			(0x61)
#define	OSD_MINUS_SML			('-'-0x20)
#define	OSD_MINUS_BIG			(0x62)

#define	OSD_ARW_L_BIG			(0x64)
#define	OSD_ARW_R_BIG			(0x65)
#define	OSD_ARW_L_SML			(0x66)
#define	OSD_ARW_R_SML			(0x67)

#define	OSD_ARW_U_BIG			(0x6c)
#define	OSD_ARW_D_BIG			(0x6d)
#define	OSD_ARW_U_SML			(0x6e)
#define	OSD_ARW_D_SML			(0x6f)

#define	OSD_X_SMALL				('x'-0x20)		//... (= '\') -> 'x'

#define	OSD_QUIT					(0x60)
#define	OSD_DD					(':'-0x20)

#define	OSD_GRP_LE				(0x3b)
#define	OSD_GRP_LH				(0x3c)
#define	OSD_GRP_RE				(0x3d)
#define	OSD_GRP_LT				(0x5b)
#define	OSD_GRP_RT				(0x5c)
#define	OSD_GRP_LB				(0x5d)
#define	OSD_GRP_RB				(0x5e)
#define	OSD_GRP_LV				(0x5f)

//... tbl_osd_nr_typ
#define	OSD_SQR_CHK				(0x00)
#define	OSD_SQR_BLK				(0x01)

#define	OSD_COL_BLK				1
#define	OSD_COL_50WHT			2
#define	OSD_COL_75WHT			3
#define	OSD_COL_25WHT			4
#define	OSD_COL_100WHT			5
#define	OSD_COL_BLU				6
#define	OSD_COL_RED				7
#define	OSD_COL_ORNG			8
#define	OSD_COL_CYN				9
#define	OSD_COL_MGN				10
#define	OSD_COL_GRN				11
#define	OSD_COL_OCN				12
#define	OSD_COL_YLW				13

#define	OSD_DLY_V				0

#define	OSD_CLR					(0xff)
#define	OSD_BLK					BIT6
#define	OSD_MIX					BIT7

#define	OSD_POS_V_ODD			0
#define	OSD_POS_V_EVEN			BIT9

#define	OSD_PTH_POS_X			2
#define	OSD_PTH_POS_Y			1

#define	OSD_TBL_V_SZ_MSB		0
#define	OSD_TBL_V_SZ_LSB		1
#define	OSD_TBL_H_SZ_MSB		2
#define	OSD_TBL_H_SZ_LSB		3
//#define	OSD_TBL_RSLTN		4
#define	OSD_TBL_CLMN			4
#define	OSD_TBL_DAT				5

#define	OSD_BMP_POS_X			58
#define	OSD_BMP_POS_Y_NTSC		74
#define	OSD_BMP_POS_Y_PAL		98
#define	OSD_BMP_WTH				22
#define	OSD_BMP_HGHT			51

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern u8 osd_bmp_pos_y;

//... string array
extern u8 str_null[];

//extern code u8 gt_tst____24bit[];
//extern code u8 gt_tst_circle_24bit[];
extern u8 gt_tst1_house_and_tree[];
extern u8 ct_tst1[];

extern u8 ct_tst_24bit[];
extern u8 gt_tst_24bit_tst_24bit_01[];
extern u8 gt_tst_24bit_tst_24bit_02[];
extern u8 gt_tst_24bit_tst_24bit_03[];

extern u8 ct_tst_fnt_16x20[];
extern u8 gt_tst_fnt_16x20_tst_fnt_16x20[];
extern u8 ct_ALPHA_NUM_32x40_4c[];
extern u8 gt_ALPHA_NUM_32x40_4c_Alpha_Num_32x40[];

extern u8 ct_CHANNEL[];
extern u8 gt_CHANNEL_x[];
extern u8 gt_CHANNEL_blank[]; 
extern u8 gt_CHANNEL_CH1_O[];
extern u8 gt_CHANNEL_CH2_O[];
extern u8 gt_CHANNEL_CH3_O[];
extern u8 gt_CHANNEL_CH4_O[];

/* Exported functions ------------------------------------------------------- */
extern void WriteOSDBmpX(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx, u8 *_bmp_ptr);		//... only one _pth at once
extern void WriteOSDBmpY(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx, u8 *_bmp_ptr);		//... only one _pth at once
extern void WriteOSDBmp_DP(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx, u8 *_bmp_ptr);

extern void WriteOSDFntX(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx);						//... only one _path at once
extern void WriteOSDFntY(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx);						//... only one _path at once
extern void WriteOSDFnt(u8 _pth, u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx);
extern void WriteOSDStrX(u8 _dvc, u8 _pos_x, u8 _pos_y, u8 _prp, u8 *_str_ptr);
extern void WriteOSDStrY(u8 _dvc, u8 _pos_x, u8 _pos_y, u8 _prp, u8 *_str_ptr);
extern void WriteOSDStr(u8 _pth, u8 _dvc, u8 _pos_x, u8 _pos_y, u8 _prp, u8 *_str_ptr);
extern void WriteOSDClrX(u8 _dvc, u8 _osd_pg, u8 _pos_x, u16 _pos_y, u8 _wdth, u16 _hght);			//... only one _path at once
extern void WriteOSDClrY(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _wdth, u16 _hght);						//... only one _path at once

extern u8 DsplyOSDDatHexY(u8 _dvc, u8 _pos_x, u8 _pos_y, u8 _pg, u8 _addr);

extern void	SetOSDCol(u8 *_tbl_osd_clr);
extern void	InitOSDCol(void);

#endif /* __TW2835_OSD_H */

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
