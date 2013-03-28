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
    0x00,0x77,0x77,0x45,0xA0,0xD0,0x2F,0x64,   0x80,0x80,0x82,0x82,0x00,0x0F,0x05,0x00, //  0x40
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
//  0    1    2    3    4    5    6    7       8    9    a    b    c    d    e    f       
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
    0x77,0x91,0x90,0x00,0x80,0x20,0x00,0x0c,   0x20,0x09,0xaa,0x00,0x40,0x40,0x00,0x00, //  0xa0 
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
	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;

	//MDATA =	_addr;
	Write_TW2835(_addr);

	HALE_SET;
	HALE_RESET;

	//MDATA =	_wdat;
	Write_TW2835(_wdat);

	HWRB_RESET;
	HWRB_SET;



	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	//		P2 = 0x03;					//... chip select all off
	HCSB0_SET;
	HCSB1_SET;

	//MDATA =	0xff;
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
	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;

	//MDATA =	_addr;
	Write_TW2835(_addr);

	HALE_SET;
	HALE_RESET;


	for(_t1_=0;_t1_<5;_t1_++)
	{
		//MDATA =	_tbl_ptr[_t1_];
		Write_TW2835(_tbl_ptr[_t1_]);

		HWRB_RESET;
		HWRB_SET;
	}

	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;


	HCSB0_SET;
	HCSB1_SET;

	//MDATA =	0xff;
	Write_TW2835(0xFF);


	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;
#if	defined(__EN_ISR__)
	EA = 1;
#endif

}

void WriteAsicByte(u8 _dvc, u8 _pg, u8 _addr, u8 _wdat)
{
//	u16 temp_16;
#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
        
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;
	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


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

	//MDATA =	_addr;
	Write_TW2835(_addr);

	HALE_SET;
	HALE_RESET;

	//MDATA =	_wdat;
	Write_TW2835(_wdat);

	HWRB_RESET;
	HWRB_SET;



	//P1 = 0xf6;						//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	//MDATA =	0xff;
	Write_TW2835(0xFF);

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;
#if	defined(__EN_ISR__)
	EA = 1;
#endif
}

void WriteAsicTable(u8 _dvc, u8 _pg, u8 _addr, u8 *_tbl_ptr, u16 _tbl_cnt)
{
	u16 _t1_;
//	u16 temp_16;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;

	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;
	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


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

	//MDATA =	_addr+_t1_;
	Write_TW2835(_addr);

	HALE_SET;
	HALE_RESET;


	for(_t1_=0;_t1_<_tbl_cnt;_t1_++)
	{
		Write_TW2835(_tbl_ptr[_t1_]);

		HWRB_RESET;
		HWRB_SET;   
	}	

	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	HCSB0_SET;
	HCSB1_SET;

	//MDATA =	0xff;
	Write_TW2835(0xFF);


	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=0;

#if	defined(__EN_ISR__)
	EA = 1;
#endif
}

void ReadAsicTable(u8 _dvc, u8 _pg, u8 _addr, u16 _data_cnt)
{
	u16 _t1_;

//	u16 temp_16;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
    
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;
	//	    P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


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

	//MDATA =	_addr;
	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	for(_t1_=0;_t1_<_data_cnt;_t1_++)
	{
		Write_TW2835(0xFF);
		HRDB_RESET;
		//_rdat_ =	MDATA;
		
		read_data[_t1_]= Read_TW2835();
		//DLY_FOR(30);
		HRDB_SET;
		//delay(30);

	}

	// 	P1 = 0xf6;					//... initial state
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

	//return _rdat_;
}

u8 ReadAsicByte(u8 _dvc, u8 _pg, u8 _addr)
{
	u8 _rdat_;
//	u16 temp_16;

#if	defined(__EN_ISR__)
	EA = 0;
#endif
   	Temp = _dvc;
    
	cmn_flg.ST.BIT.b_cmn_prtcl_bsy=1;
	//	    P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;
	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


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

	//MDATA =	_addr;
	Write_TW2835(_addr);
	HALE_SET;
	HALE_RESET;

	//MDATA =	0xff;					// port0(MDATA) input mode
	Write_TW2835(0xFF);

	HRDB_RESET;
	//_rdat_ =	MDATA;
	//PortC_Change(0);
	_rdat_ = Read_TW2835();
	//DLY_FOR(30);
	HRDB_SET;

	// 	P1 = 0xf6;						//... initial state
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
	//  	P1 = 0xf6;					//... initial state
	HALE_RESET;
	HRDB_SET;
	HWRB_SET;
	HSPB_RESET;

	//... P[7:4]:INT[5:2], P1_3:HALE, P1_2:HRDB, P1_1:HWRB, P1_0:HSPB


	_dvc = 0;							//... temporal
	HCSB0_RESET;
	HCSB1_SET;

	//MDATA =	0x0a;
	Write_TW2835(0x0A);
	HALE_SET;
	HALE_RESET;

	//MDATA =	0xff;					// port0(MDATA) input mode
	Write_TW2835(0xFF);
	HRDB_RESET;

	//_rdat_ =	MDATA;
	_rdat_ = Read_TW2835();
	HRDB_SET;

	// 	P1 = 0xf6;						//... initial state
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

#if 0
void Port_Change(u8 in_Dir)
{
	if(in_Dir)	// Write
	{
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
	}
	else	// Read
	{
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
	}
}
#endif

void Write_TW2835(u8 Data)
{
	u16 Read_Port_D = 0;
	u16 Read_Port_E = 0;
	u16 Write_Port_D = 0;
	u16 Write_Port_E = 0;

//	Port_Change(1);

	Read_Port_D = GPIO_ReadOutputData(GPIOD);
	Read_Port_E = GPIO_ReadOutputData(GPIOE);

	Write_Port_D = Read_Port_D & 0x3FFC; // 0,1,14,15 Pin 제외
	Write_Port_E = Read_Port_E & 0xF87F; // 7,8,9,10 Pin 제외
	if(Data & 0x01)
	{
		Write_Port_D |= GPIO_Pin_14;
	}
	if(Data & 0x02)
	{
		Write_Port_D |= GPIO_Pin_15;
	}
	if(Data & 0x04)
	{
		Write_Port_D |= GPIO_Pin_0;
	}
	if(Data & 0x08)
	{
		Write_Port_D |= GPIO_Pin_1;
	}

	if(Data & 0x10)
	{
		Write_Port_E |= GPIO_Pin_7;
	}
	if(Data & 0x20)
	{
		Write_Port_E |= GPIO_Pin_8;
	}

	if(Data & 0x40)
	{
		Write_Port_E |= GPIO_Pin_9;
	}

	if(Data & 0x80)
	{
		Write_Port_E |= GPIO_Pin_10;
	}


	GPIO_Write(GPIOD, Write_Port_D);
	GPIO_Write(GPIOE, Write_Port_E);

}

u8 Read_TW2835()
{
//	Port_Change(0);

	u16 Read_Port_D = 0;
	u16 Read_Port_E = 0;

	u8 Result = 0;

	Read_Port_D = GPIO_ReadInputData(GPIOD);
	Read_Port_E = GPIO_ReadInputData(GPIOE);

	if (Read_Port_D & GPIO_Pin_14)
	{
		Result |= 0x01;
	}
	if (Read_Port_D & GPIO_Pin_15)
	{
		Result |= 0x02;
	}
	if (Read_Port_D & GPIO_Pin_1)
	{
		Result |= 0x04;
	}
	if (Read_Port_D & GPIO_Pin_2)
	{
		Result |= 0x08;
	}

	if (Read_Port_E & GPIO_Pin_7)
	{
		Result |= 0x10;
	}
	if (Read_Port_E & GPIO_Pin_8)
	{
		Result |= 0x20;
	}
	if (Read_Port_E & GPIO_Pin_9)
	{
		Result |= 0x40;
	}
	if (Read_Port_E & GPIO_Pin_10)
	{
		Result |= 0x80;
	}

	return Result;
}

/**\
  * @brief  None
  * @param  None
  * @retval None
  */
void TW2835_Control_Init(void)
{
    DebugMsg_printf("++ TW2835_Control_Init (GPIO Mode), Initialize START\r\n");



    DebugMsg_printf("-- TW2835_Control_Init (GPIO Mode), Initialize END\r\n");
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
