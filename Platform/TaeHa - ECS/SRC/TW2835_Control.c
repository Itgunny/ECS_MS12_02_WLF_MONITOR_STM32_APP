/**
  ******************************************************************************
  * @file    TW2835_Control.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TW2835_Control.c module
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
//==================================================================================
//						Page1 initialize table description
//==================================================================================
unsigned char	tbl_pg1_x_cmn[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	     0x02,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0xd7,0x23,0x2d,0x1e,0xa7,	//...  0x01
	0x80,0x02,0x00,0x00,0x02,0x00,0x10,0x00,	0x81,0x02,0x00,0x01,0x02,0x00,0x11,0x00,	//...  0x10	//... normal quad
	0x82,0x02,0x00,0x02,0x02,0x00,0x12,0x00,	0x83,0x02,0x00,0x03,0x02,0x00,0x13,0x00,	//...  0x20
//	0x90,0x02,0x00,0x90,0x02,0x00,0x10,0x00,	0x91,0x02,0x00,0x91,0x02,0x00,0x11,0x00,	//... 0x10	//... non-realtime
//	0x92,0x02,0x00,0x92,0x02,0x00,0x12,0x00,	0x93,0x02,0x00,0x93,0x02,0x00,0x13,0x00,	//... 0x20
};

//--------------------------		NTSC		------------------------------//
//... H:60(3c),90(5a),120(78),180(b4), V:40(28),60(3c),80(50),120(78) for NTSC, 48(30),72(48),96(60),144(90) for PAL
unsigned char	tbl_ntsc_pg1_pic_fl[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0xb4,0x00,0x78,0x00,0xb4,0x00,0x78,	0x00,0xb4,0x00,0x78,0x00,0xb4,0x00,0x78	//...  
};

unsigned char	tbl_ntsc_pg1_pic_qd[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0x5a,0x00,0x3c,0x5a,0xb4,0x00,0x3c,	0x00,0x5a,0x3c,0x78,0x5a,0xb4,0x3c,0x78	//...  
};

unsigned char	tbl_ntsc_pg1_pic_9_lt[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0x3c,0x00,0x28,0x3c,0x78,0x00,0x28,	0x78,0xb4,0x00,0x28,0x00,0x3c,0x28,0x50	//...   
};

unsigned char	tbl_ntsc_pg1_pic_9_rb[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x78,0xb4,0x28,0x50,0x00,0x3c,0x50,0x78,	0x3c,0x78,0x50,0x78,0x78,0xb4,0x50,0x78	//...   
};

//--------------------------		PAL		------------------------------//
//... H:60(3c),90(5a),120(78),180(b4), V:40(28),60(3c),80(50),120(78) for NTSC, 48(30),72(48),96(60),144(90) for PAL
unsigned char	tbl_pal_pg1_pic_fl[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0xb4,0x00,0x90,0x00,0xb4,0x00,0x90,	0x00,0xb4,0x00,0x90,0x00,0xb4,0x00,0x90	//...  
};

unsigned char	tbl_pal_pg1_pic_qd[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0x5a,0x00,0x48,0x5a,0xb4,0x00,0x48,	0x00,0x5a,0x48,0x90,0x5a,0xb4,0x48,0x90	//...  
};

unsigned char	tbl_pal_pg1_pic_9_lt[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x00,0x3c,0x00,0x30,0x3c,0x78,0x00,0x30,	0x78,0xb4,0x00,0x30,0x00,0x3c,0x30,0x60	//...   
};

unsigned char	tbl_pal_pg1_pic_9_rb[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x78,0xb4,0x30,0x60,0x00,0x3c,0x60,0x90,	0x3c,0x78,0x60,0x90,0x78,0xb4,0x60,0x90	//...   
};

//=================================================================================

unsigned char	tbl_pg1_y_cmn[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x28,0x00,0x10,0xa0,0x00,0x00,0x00,0x03,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa7,//... 0x50 
	0x80,0x02,0x00,0x81,0x02,0x00,0x82,0x02,	0x00,0x83,0x02,0x00,0x00,0xe4,0x00,0x00,//... 0x60	//... normal quad
//	0x90,0x02,0x00,0x91,0x02,0x00,0x92,0x02,	0x00,0x93,0x02,0x00,0x00,0xe4,0x00,0x00,//...0x60	//...non-realtime
	0x00,0x03,0x00,0x00,0x00,0x00,0x02,0x00,	0xff,0xff,0xff,0xff,0xf0,0x00,0x8b,0x84,//... 0x70 
//	0xff,0x00,0x51,0x07,0xeb,0x10,0xa8,0x00,	0x51,0xe7,0x80,0x00,0x00,0x00,0x00,0x00,//...0x80
	0xdf,0x00,0x91,0x07,0xeb,0x10,0xa8,0x00,	0x91,0xe7,0x80,0x00,0x00,0x00,0x00,0x00,//... 0x80	//... update:060715
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	//... 0x90
};

//--------------------------		NTSC		------------------------------//
//=================================================================================
unsigned char	tbl_ntsc_pg1_enc[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x77,0x23,0xd7,0x01,0x80,0x20,0x00,0x0c,	0x20,0x09,0xaa,0x00,0x40,0x40,0x00,0x00	//... 0xa0
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	//...0xb0
};
//--------------------------		PAL		------------------------------//
//=================================================================================
unsigned char	tbl_pal_pg1_enc[] = {
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	0x77,0x23,0xd7,0x01,0x80,0x20,0x00,0x0c,	0x20,0x4c,0xaa,0x00,0x40,0x40,0x00,0x00	//... 0xa0
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	//...0xb0
};
//=================================================================================

//==================================================================================
//						Page2 initialize table description
//==================================================================================

//--------------------------		PAGE 2		------------------------------//
unsigned char	tbl_pg2_mse_box[] = {		// 80 EA
//  00   01   02   03   04   05   06   07		 08   09   0A   0B   0C   0D   0E   0F
	//... mouse & LUT
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//...  0x10
	//... single box
	0x00,0xb0,0x00,0x00,0x00,0x00,0x40,0x00,	0x00,0x00,0x00,0x00,0x00,0xb0,0x00,0x00,//...  0x20
	0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//...  0x30
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//...  0x40
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x40,0x40,0x40,0x42,0xff	//...  0x50
};

unsigned char	tbl_ntsc_pg2_2dbox[] = {		// 32 EA
	//... 2d array box
	0x88,0x00,0x00,0x00,0x00,0x00,0xfb,0x00,	0x89,0x00,0x00,0x00,0x00,0x00,0xfb,0x00,//...  0x60
	0x8a,0x00,0x00,0x00,0x00,0x00,0xfb,0x00,	0x8b,0x00,0x00,0x00,0x00,0x00,0xfb,0x00	//...  0x70
};

unsigned char	tbl_ntsc_pg2_mtn[] = {		// 32 EA
	//... sensitivity & mask info
	0x17,0x73,0x88,0x4a,0x07,0x24,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//...  0x80
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	//...  0x90
};


unsigned char	tbl_pal_pg2_2dbox[] = {		// 32 EA
	//... 2d array box
	0x20,0x28,0x00,0x00,0x00,0x00,0xfb,0x00,	0x21,0x28,0x00,0x00,0x00,0x00,0xfb,0x00,//...  0x60
	0x22,0x28,0x00,0x00,0x00,0x00,0xfb,0x00,	0x23,0x28,0x00,0x00,0x00,0x00,0xfb,0x00	//...  0x70
};

unsigned char	tbl_pal_pg2_mtn[] = {		// 32 EA
	//... sensitivity & mask info
	0x17,0x73,0x88,0x4a,0x07,0x24,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//...  0x80
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00	//...  0x90
};

unsigned char Register_Table_Page0[] = {
//  0    1    2    3    4    5    6    7       8    9    a    b    c    d    e    f   
    0x00,0xC8,0x20,0xD0,0x06,0xF0,0x08,0x80,   0x80,0x80,0x80,0x00,0x00,0x00,0x11,0x00, //  0x00 
    0x80,0xC8,0x20,0xD0,0x06,0xF0,0x08,0x80,   0x80,0x80,0x80,0x00,0x00,0x00,0x11,0x00, //  0x10
    0x80,0xC8,0x20,0xD0,0x06,0xF0,0x08,0x80,   0x80,0x80,0x80,0x00,0x00,0x00,0x11,0x00, //  0x20
    0x80,0xC8,0x20,0xD0,0x06,0xF0,0x08,0x80,   0x80,0x80,0x80,0x00,0x00,0x00,0x11,0x00, //  0x30
    0x00,0x77,0x77,0x45,0xA0,0xD0,0x2F,0x64,   0x80,0x80,0x82,0x82,0x30,0x0F,0x05,0x00, //  0x40
    0x00,0x80,0x06,0x00,0x40,0xFF,0x00,0x00,   0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0x50
    0xFF,0xFF,0x00,0x00,0x10,0x32,0x54,0x76,   0x00,0xBA,0xDC,0xFE,0x00,0x00,0x88,0x88, //  0x60
    0x08,0x54,0x00,0x00,0x00,0x00,0x00,0x00,   0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0x70
    0x01,0x7F,0xFF,0x7F,0xFF,0x00,0xFF,0xFF,   0xFF,0xFF,0x31,0x00,0xD0,0x00,0xF0,0x08, //  0x80
    0x41,0x7F,0xFF,0x7F,0xFF,0x00,0xFF,0xFF,   0xFF,0xFF,0x71,0x00,0xD0,0x00,0xF0,0x08, //  0x90
    0x81,0x7F,0xFF,0x7F,0xFF,0x00,0xFF,0xFF,   0xFF,0xFF,0xB1,0x00,0xD0,0x00,0xF0,0x08, //  0xa0 
    0xC1,0x7F,0xFF,0x7F,0xFF,0x00,0xFF,0xFF,   0xFF,0xFF,0xF1,0x00,0xD0,0x00,0xF0,0x08, //  0xb0 
    0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,   0x00,0x3C,0x4F,0x00,0x00,0x00,0x00,0x00, //  0xc0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xd0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xe0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x00  //  0xf0 
};
unsigned char Register_Table_Page1[] = { 
//  0    1    2    3    4    5    6    7                         8    9         a       b       c    d    e    f       
    0x00,0x00,0x00,0x00,0x0F,0x04,0x00,0x00,   0x00,0x00,0x20,0xD7,0x23,0x2D,0x1E,0xA3, //  0x00 
    0x80,0x02,0x00,0x00,0x02,0x00,0x10,0x00,   0x81,0x02,0x00,0x01,0x02,0x00,0x11,0x00, //  0x10 
    0x82,0x02,0x00,0x02,0x02,0x00,0x12,0x00,   0x83,0x02,0x00,0x03,0x02,0x00,0x13,0x00, //  0x20
    //0x00,0x02,0x00,0x00,0x02,0x00,0x10,0x00,   0x01,0x02,0x00,0x01,0x02,0x00,0x11,0x00, //  0x10 
    //0x02,0x02,0x00,0x02,0x02,0x00,0x12,0x00,   0x03,0x02,0x00,0x03,0x02,0x00,0x13,0x00, //  0x20
    0x00,0x58,0x00,0x3C,0x58,0xB0,0x00,0x3C,   0x00,0x58,0x3C,0x78,0x58,0xB0,0x3C,0x78, //  0x30 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0x40 
    0x28,0x41,0x10,0xa0,0x00,0x00,0x00,0x03,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa3, //  0x50 
    0x80,0x00,0x00,0x81,0x00,0x00,0x82,0x00,   0x00,0x83,0x00,0x00,0x00,0xe4,0x00,0x00, //  0x60 
    0x00,0x03,0x00,0x00,0x00,0x00,0x02,0x00,   0xff,0xff,0xff,0xff,0xf0,0x00,0x89,0x84, //  0x70 
    0xdf,0x00,0x91,0x07,0xeb,0x10,0xa8,0x00,   0x91,0xe7,0x80,0x00,0x00,0x00,0x00,0x00, //  0x80 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0x90 
    0x77,0x88,0x88,0x00,0x80,0x20,0x00,0x0c,   0x20,0x09,0xaa,0x00,0x40,0x40,0x00,0x00, //  0xa0 
    0x00,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x0F,   0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xb0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xc0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xd0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  0xe0 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  //  0xf0
};

struct	{							//	struct cmn_flg Byte   
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

struct	{							//	struct cmn_flg Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//  Bit  Access 
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

struct	{							//	struct cmn_flg Byte   
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

struct	{							//	struct cmn_flg Byte   
	union {							//	ST        
       	u8 BYTE;					//  Byte Access 
       	struct {					//  Bit  Access 
       	    u8 b_ch_src:1;	    	//  Bit 7     
            u8 b_ado_lv_mr:1;	    //  Bit 6     
            u8 b_ado_lv_mr_arw_pb:1;//  Bit 5     
            u8 b_cmn_NA:5;  		//  Bit 0~4     
            
      	}	BIT;						
	}		ST;							
}			wndw_flg;



u8	cmn_bot;
u8	cmn_cnt_vs = 0;
u8	cmn_cnt_vs_sub = 0;
u8	cmn_vga_det = 0;				//... __WTH_VGA__일때 idata 없애면 compile시 error 발생.


u8	cmn_dvc = MASTER;
u8	cmn_lst_slvr_x = MASTER;
u8	cmn_lst_slvr_y = MASTER;
u8	cmn_max_ch = 4;

u8 	read_data[0x0100];
u8 	Temp;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SetAsicFlgType(u8 _dvc, u8 _pg, u8 _addr, u8 _flg, u8 _data)
{
	u8 _t1_;

	_t1_ = ReadAsicByte(_dvc,_pg,_addr);
	_t1_ = (_t1_ & ~_flg)|_data;
	WriteAsicByte(_dvc,_pg,_addr,_t1_);
}

void InitPg0(void)
{
    	WriteAsicTable(MASTER,DVC_PG0,0x00,Register_Table_Page0,0xff);
}

void InitPg1(void)
{
	WriteAsicTable(MASTER,DVC_PG1,0x00,Register_Table_Page1,0xff);
}

void InitPg2(void)
{
	u8 _t1_;

	//... OSD color index
	InitOSDCol();

	WriteAsicByte(MASTER,DVC_PG2,0x0f,0x0f);		//... OSD Enable for Display/Capture	

	WriteOSDClrX(MASTER,0,0,0,45,31);				//... max line num is 310 line for OSD
	WriteOSDClrX(MASTER,1,0,0,45,31);				//... max line num is 310 line for OSD
	WriteOSDClrX(MASTER,2,0,0,45,31);				//... max line num is 310 line for OSD
	WriteOSDClrX(MASTER,3,0,0,45,31);				//... max line num is 310 line for OSD
	WriteOSDClrY(MASTER,0,0,45,31);					//... max line num is 310 line for OSD

	WriteAsicByte(MASTER,DVC_PG2,0x10,0xf0);		//... cursor

	//... other ( mouse, single box, 2d box, mask ..)
	WriteAsicTable(MASTER,DVC_PG2,0x10,tbl_pg2_mse_box,80);
	if(cmn_flg.ST.BIT.b_cmn_jp_vdo == VDO_NTSC){
		WriteAsicTable(MASTER,DVC_PG2,0x60,tbl_ntsc_pg2_2dbox,32);
		for(_t1_=0;_t1_<4;_t1_++)	WriteAsicTable(MASTER,DVC_PG2,0x80+0x20*_t1_,tbl_ntsc_pg2_mtn,32);
	}
	else{
		WriteAsicTable(MASTER,DVC_PG2,0x60,tbl_pal_pg2_2dbox,32);
		for(_t1_=0;_t1_<4;_t1_++)	WriteAsicTable(MASTER,DVC_PG2,0x80+0x20*_t1_,tbl_pal_pg2_mtn,32);
	}
}

void WriteAsicByteOSD(u8 _dvc, u8 _addr, u8 _wdat)
{
#if	defined(__EN_ISR__)
	EA = 0;
#endif
	Temp = _dvc;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;

	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	Write_TW2835(_wdat);
	HWRB_RESET;
	HWRB_SET;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	Write_TW2835(0xFF);

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;
#if	defined(__EN_ISR__)
	EA = 1;
#endif
}

void WriteAsicTableOSD(u8 _dvc, u8 _addr, u8 *_tbl_ptr)
{
	u8 _t1_;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;

	Write_TW2835(_addr);

	HALE_SET;
	HALE_RESET;


	for(_t1_=0;_t1_<5;_t1_++)
	{
		Write_TW2835(_tbl_ptr[_t1_]);
		HWRB_RESET;
		HWRB_SET;
	}

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;


	HCSB0_SET;
	HCSB1_SET;

	Write_TW2835(0xFF);


	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;
#if	defined(__EN_ISR__)
	EA = 1;
#endif

}

void WriteAsicByte(u8 _dvc, u8 _pg, u8 _addr, u8 _wdat)
{

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
        
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	_dvc = 0;							//... temporal
	if(_pg == DVC_PG0)
	{	
		HCSB1_RESET;	HCSB0_RESET;
	}
	else if(_pg == DVC_PG1)
	{	
		HCSB1_RESET;	
		HCSB0_SET;
	}
	else if(_pg == DVC_PG2)
	{	
		HCSB1_SET;	
		HCSB0_RESET;
	}

	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	Write_TW2835(_wdat);
	HWRB_RESET;
	HWRB_SET;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	Write_TW2835(0xFF);

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;
#if	defined(__EN_ISR__)
	EA = 1;
#endif
}

void WriteAsicTable(u8 _dvc, u8 _pg, u8 _addr, u8 *_tbl_ptr, u16 _tbl_cnt)
{
	u16 _t1_;


#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;


	_dvc = 0;							//... temporal
	if(_pg == DVC_PG0)      
	{	
		HCSB1_RESET;	
		HCSB0_RESET;
	}
	else if(_pg == DVC_PG1) 
	{	
		HCSB1_RESET;	
		HCSB0_SET;
	}
	else if(_pg == DVC_PG2)
	{	
		HCSB1_SET;	 
		HCSB0_RESET;
	}


	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;


	for(_t1_=0;_t1_<_tbl_cnt;_t1_++)
	{
		Write_TW2835(_tbl_ptr[_t1_]);
		HWRB_RESET;
		HWRB_SET;   
	}	

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	Write_TW2835(0xFF);

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;

#if	defined(__EN_ISR__)
	EA = 1;
#endif
}

void ReadAsicTable(u8 _dvc, u8 _pg, u8 _addr, u16 _data_cnt)
{
	u16 _t1_;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
    
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	_dvc = 0;							//... temporal
	if(_pg == DVC_PG0)     
	{
		HCSB1_RESET;	
		HCSB0_RESET;
	}
	else if(_pg == DVC_PG1) 
	{
		HCSB1_RESET;	
		HCSB0_SET;
	}
	else if(_pg == DVC_PG2) 
	{
		HCSB1_SET;	    
		HCSB0_RESET;
	}

	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	for(_t1_=0;_t1_<_data_cnt;_t1_++)
	{
		//Write_TW2835(0xFF);
		HRDB_RESET;		
		read_data[_t1_]= Read_TW2835();
		HRDB_SET;
	}

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;

#if	defined(__EN_ISR__)
	EA = 1;
#endif

}

u8 ReadAsicByte(u8 _dvc, u8 _pg, u8 _addr)
{
	u8 _rdat_;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
    
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	if(_pg == DVC_PG0)      
	{	
		HCSB1_RESET;	
		HCSB0_RESET;
	}
	else if(_pg == DVC_PG1)
	{
		HCSB1_RESET;
		HCSB0_SET;
	}
	else if(_pg == DVC_PG2) 
	{	
		HCSB1_SET;	 
		HCSB0_RESET;
	}

	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	//Write_TW2835(0xFF);

	HRDB_RESET;
	_rdat_ = Read_TW2835();
	HRDB_SET;


	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;

#if	defined(__EN_ISR__)
	EA = 1;
#endif

	return _rdat_;
}

u8	ReadAsicOSDMemWr(u8 _dvc)
{
	u8 _rdat_;
//	u16 temp_16;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;

	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;


	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;


	Write_TW2835(0x0A);
	HALE_SET;
	HALE_RESET;


	Write_TW2835(0xFF);
	HRDB_RESET;


	_rdat_ = Read_TW2835();
	HRDB_SET;


	HALE_RESET;	
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;

#if	defined(__EN_ISR__)
	EA = 1;
#endif

	return _rdat_;
}

void	InitVdo(void)
{
	cmn_flg.ST.BIT.b_cmn_jp_vdo = VDO_NTSC;
	cmn_bot = 120;
	cmn_cnt_vs_sub = 54;
}


void Write_TW2835(u8 Data)
{
	u16 TempData;

	Port_Change(TW2835_WRITE);

	TempData = GPIO_ReadOutputData(TW2835_DATAPORT) & 0xFF00;
	TempData |= ((u16)Data & 0x00FF);
	
	GPIO_Write(TW2835_DATAPORT,TempData);
}

u8 Read_TW2835()
{
	u8 Result;
	Port_Change(TW2835_READ);

	Result = (u8)(GPIO_ReadInputData(TW2835_DATAPORT) & 0x00FF);
	

	return Result;
}

void Port_Change(u8 in_Dir)
{
	GPIO_InitTypeDef GPIO_InitStructure;


	if(in_Dir == TW2835_WRITE)
	{
		GPIO_InitStructure.GPIO_Pin = TW2835_D0 | TW2835_D1 | TW2835_D2 | TW2835_D3 | TW2835_D4 | 
										TW2835_D5 | TW2835_D6 | TW2835_D7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
                GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;    
		GPIO_Init(TW2835_DATAPORT, &GPIO_InitStructure);
	}
	else if(in_Dir == TW2835_READ)
	{
		GPIO_InitStructure.GPIO_Pin = TW2835_D0 | TW2835_D1 | TW2835_D2 | TW2835_D3 | TW2835_D4 | 
										TW2835_D5 | TW2835_D6 | TW2835_D7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
                GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;    
		GPIO_Init(TW2835_DATAPORT, &GPIO_InitStructure);
	}
}

void ClearCheckCamera()
{
	WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,20,45,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,110,45,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,20,165,0x00,0x00,gt_CHANNEL_blank);
	WriteOSDBmpX(MASTER,110,165,0x00,0x00,gt_CHANNEL_blank);
}

//	++, kutelf, 140801
//	RevD 보드와 호환성을 위하여 함수 이름 변경
//  ++, kutelf, 131007
//u8 Temp0, Temp1, Temp2, Temp3;
void TW2835_CheckCamera_Input(u8 Mode)
{

	//	입력이 없으면, return 0x80
	//	입력이 있으면, return 0x9f
	u8 Signal1 = ReadAsicByte(MASTER,DVC_PG0,0x00); 	//  ch1
	u8 Signal2 = ReadAsicByte(MASTER,DVC_PG0,0x10);	//	ch2
	u8 Signal3 = ReadAsicByte(MASTER,DVC_PG0,0x20);	//	ch3
	u8 Signal4 = ReadAsicByte(MASTER,DVC_PG0,0x30);	//	ch4

	
	ClearCheckCamera();
	if(Mode == 0x00)
	{
		
		if(Signal1 != 0x80)
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_x);
		}

		
	}

	else if(Mode == 0x01)
	{
		if(Signal2 != 0x80)
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_x);
		}

	}

	else if(Mode == 0x02)
	{
		if(Signal3 != 0x80)
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_x);
		}

		
	}

	else if(Mode == 0x03)
	{
		if(Signal4 != 0x80)
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,65,100,0x00,0x00,gt_CHANNEL_x);
		}

	}
	else if(Mode == 0x04)
	{
		if(Signal1 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal2 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}
	}

	else if(Mode == 0x05)
	{
		if(Signal1 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal3 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}
	}
	else if(Mode == 0x06)
	{
		if(Signal1 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal4 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}

	}
	else if(Mode == 0x07)
	{
		if(Signal2 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal3 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}

	}
	else if(Mode == 0x08)
	{
		if(Signal2 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal4 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}

	}

	else if(Mode == 0x09)
	{
		if(Signal3 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,100,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal4 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,100,0x00,0x00,gt_CHANNEL_x);
		}

	}

	else if(Mode == 0x0A)
	{
		if(Signal1 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,45,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,45,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal2 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,45,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,45,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal3 != 0x80)
		{
			WriteOSDBmpX(MASTER,20,165,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,20,165,0x00,0x00,gt_CHANNEL_x);
		}

		if(Signal4 != 0x80)
		{
			WriteOSDBmpX(MASTER,110,165,0x00,0x00,gt_CHANNEL_blank);
		}
		else
		{
			WriteOSDBmpX(MASTER,110,165,0x00,0x00,gt_CHANNEL_x);
		}

	}

}
//  --, kutelf, 131007
//	--, kutelf, 140801

//	++, kutelf, 140801
//	RevD 보드와 호환성을 위하여 함수 이름 변경
//  ++, kutelf, 131007
void TW2835_CameraMode(u8 Mode, u8 OSD)
{

	if(Mode == 0x00)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH1_O);
		}
		
		// Scale CAM_0 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x80,0x01);    
		WriteAsicByte(MASTER,DVC_PG0,0x81,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x82,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x83,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x84,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x80);    // ON CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);	// OFF CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);    // OFF CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);    // OFF CAM_3

		WriteAsicByte(MASTER,DVC_PG1,0x30,0x00);    // Position CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x31,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x32,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x33,0x78);
	}
	else if(Mode == 0x01)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);	
			WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH2_O);
		}

		// Scale CAM_1 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x90,0x41);
		WriteAsicByte(MASTER,DVC_PG0,0x91,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x92,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x93,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x94,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);    // ON/OFF CAM
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x81);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);    // OFF CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);    // OFF CAM_4

		WriteAsicByte(MASTER,DVC_PG1,0x34,0x00);    // Position CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x35,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x36,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x37,0x78);
	}
	else if(Mode == 0x02)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH3_O);
		}

		// Scale CAM_2 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xa0,0x81);
		WriteAsicByte(MASTER,DVC_PG0,0xa1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);    // ON/OFF CAM
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x82);    // OFF CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);    // OFF CAM_4

		WriteAsicByte(MASTER,DVC_PG1,0x38,0x00);    // Position CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x39,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3a,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3b,0x78);
	}
	else if(Mode == 0x03)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH4_O);
		}
		
		// Scale CAM_3 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xb0,0xc1);
		WriteAsicByte(MASTER,DVC_PG0,0xb1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);    // ON/OFF CAM
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);    // OFF CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x83);    // OFF CAM_4

		WriteAsicByte(MASTER,DVC_PG1,0x3c,0x00);    // Position CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x3d,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3e,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3f,0x78); 
  	}
	else if(Mode == 0x04)
	{
		
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH1_O);
       		WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH2_O);
		}
		
		// Scale CAM_0 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x80,0x01);    
		WriteAsicByte(MASTER,DVC_PG0,0x81,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x82,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x83,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x84,0xff);
		// Scale CAM_1 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x90,0x41);
		WriteAsicByte(MASTER,DVC_PG0,0x91,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x92,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x93,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x94,0xff);


		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x80);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x81);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);   

		WriteAsicByte(MASTER,DVC_PG1,0x30,0x00);    // Position CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x31,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x32,0x00);    //0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x33,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x34,0x58);    // Position CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x35,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x36,0x00);    //0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x37,0x78);
	}
	else if(Mode == 0x05)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH1_O);
       	 	WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH3_O);
		}

		// Scale CAM_0 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x80,0x01);    
		WriteAsicByte(MASTER,DVC_PG0,0x81,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x82,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x83,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x84,0xff);

		// Scale CAM_2 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xa0,0x81);
		WriteAsicByte(MASTER,DVC_PG0,0xa1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x80);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x82);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);    

		WriteAsicByte(MASTER,DVC_PG1,0x30,0x00);    // Position CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x31,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x32,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x33,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x38,0x58);    // Position CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x39,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3a,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3b,0x78); 
	}
	else if(Mode == 0x06)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH1_O);
       	 	WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH4_O);
		}

		// Scale CAM_0 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x80,0x01);    
		WriteAsicByte(MASTER,DVC_PG0,0x81,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x82,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x83,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x84,0xff);

		// Scale CAM_3 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xb0,0xc1);
		WriteAsicByte(MASTER,DVC_PG0,0xb1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x80);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x83);    

		WriteAsicByte(MASTER,DVC_PG1,0x30,0x00);    // Position CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x31,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x32,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x33,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x3c,0x58);    // Position CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x3d,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3e,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3f,0x78); 
	}
	else if(Mode == 0x07)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH2_O);
       	 	WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH3_O);
		}

		// Scale CAM_1 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x90,0x41);
		WriteAsicByte(MASTER,DVC_PG0,0x91,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x92,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x93,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x94,0xff);

		// Scale CAM_2 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xa0,0x81);
		WriteAsicByte(MASTER,DVC_PG0,0xa1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa3,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xa4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x81);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x82);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x03);    

		WriteAsicByte(MASTER,DVC_PG1,0x34,0x00);    // Position CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x35,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x36,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x37,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x38,0x58);    // Position CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x39,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3a,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3b,0x78); 
	}
	else if(Mode == 0x08)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH2_O);
       	 	WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH4_O);
		}

		// Scale CAM_1 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x90,0x41);
		WriteAsicByte(MASTER,DVC_PG0,0x91,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x92,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x93,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x94,0xff);

		// Scale CAM_3 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xb0,0xc1);
		WriteAsicByte(MASTER,DVC_PG0,0xb1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x81);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x02);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x83);    

		WriteAsicByte(MASTER,DVC_PG1,0x34,0x00);    // Position CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x35,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x36,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x37,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x3c,0x58);    // Position CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x3d,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3e,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3f,0x78); 
	}
	else if(Mode == 0x09)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH3_O);
       	 	WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH4_O);
		}

		// Scale CAM_2 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xa0,0x81);
		WriteAsicByte(MASTER,DVC_PG0,0xa1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa3,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xa4,0xff);

		// Scale CAM_3 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xb0,0xc1);
		WriteAsicByte(MASTER,DVC_PG0,0xb1,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb3,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb4,0xff);
		    
		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x00);  
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x01);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x82);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x83);    

		WriteAsicByte(MASTER,DVC_PG1,0x38,0x00);    // Position CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x39,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x3a,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3b,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x3c,0x58);    // Position CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x3d,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3e,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x3f,0x78); 
	}
	else if (Mode == 0x0A)
	{
		if(OSD)
		{
			WriteOSDClrX(MASTER, 0, 0, 0, 45, 31);
			WriteOSDBmpX(MASTER,76,5,0x00,0x00,gt_CHANNEL_CH1_O);
		    WriteOSDBmpX(MASTER,162,5,0x00,0x00,gt_CHANNEL_CH2_O);
		    WriteOSDBmpX(MASTER,76,125,0x00,0x00,gt_CHANNEL_CH3_O);
		    WriteOSDBmpX(MASTER,162,125,0x00,0x00,gt_CHANNEL_CH4_O);
		}
		
		// Scale CAM_0 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x80,0x01);    
		WriteAsicByte(MASTER,DVC_PG0,0x81,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x82,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x83,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x84,0xff);
		// Scale CAM_1 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0x90,0x41);
		WriteAsicByte(MASTER,DVC_PG0,0x91,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x92,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0x93,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0x94,0xff);
		// Scale CAM_2 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xa0,0x81);
		WriteAsicByte(MASTER,DVC_PG0,0xa1,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xa2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xa3,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xa4,0xff);
		// Scale CAM_3 // Select CAM
		WriteAsicByte(MASTER,DVC_PG0,0xb0,0xc1);
		WriteAsicByte(MASTER,DVC_PG0,0xb1,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xb2,0xff);
		WriteAsicByte(MASTER,DVC_PG0,0xb3,0x7f);
		WriteAsicByte(MASTER,DVC_PG0,0xb4,0xff);

		// ON/OFF CAMERA
		WriteAsicByte(MASTER,DVC_PG1,0x10,0x80);   
		WriteAsicByte(MASTER,DVC_PG1,0x18,0x81);
		WriteAsicByte(MASTER,DVC_PG1,0x20,0x82);   
		WriteAsicByte(MASTER,DVC_PG1,0x28,0x83); 

		WriteAsicByte(MASTER,DVC_PG1,0x30,0x00);    // Position CAM_0
		WriteAsicByte(MASTER,DVC_PG1,0x31,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x32,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x33,0x3C);

		WriteAsicByte(MASTER,DVC_PG1,0x34,0x58);    // Position CAM_1
		WriteAsicByte(MASTER,DVC_PG1,0x35,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x36,0x00);
		WriteAsicByte(MASTER,DVC_PG1,0x37,0x3C);

		WriteAsicByte(MASTER,DVC_PG1,0x38,0x00);    // Position CAM_2
		WriteAsicByte(MASTER,DVC_PG1,0x39,0x58);
		WriteAsicByte(MASTER,DVC_PG1,0x3a,0x3C);
		WriteAsicByte(MASTER,DVC_PG1,0x3b,0x78);

		WriteAsicByte(MASTER,DVC_PG1,0x3c,0x58);    // Position CAM_3
		WriteAsicByte(MASTER,DVC_PG1,0x3d,0xb0);
		WriteAsicByte(MASTER,DVC_PG1,0x3e,0x3C);
		WriteAsicByte(MASTER,DVC_PG1,0x3f,0x78); 
	}
}
//  --, kutelf, 131007
//	--, kutelf, 140801

/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void TW2835_Control_Init(void)
{
	DebugMsg_printf("++ TW2835_Control_Init (GPIO Mode), Initialize START\r\n");

	InitPg0();
	InitPg1();
	InitPg2();

	DebugMsg_printf("-- TW2835_Control_Init (GPIO Mode), Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
