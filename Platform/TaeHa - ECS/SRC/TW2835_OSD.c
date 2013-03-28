/**
  ******************************************************************************
  * @file    TW2835_OSD.c 
  * @author  kutelf (kutelf@taeha.co.kr)
  * @version V1.0.0
  * @date    02/22/2013
  * @brief   TW2835_OSD.c module
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
u8 osd_bmp_pos_y;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//==================================================================================
//						OSD function description
//==================================================================================
void WriteOSDBmpX(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp_pg, u8 _indx, u8 *_bmp_ptr)
//... _pos_x: ~ 180(4 pixel/_pos_x), _pos_y: ~ 240/288 domain
{
//	u8 _wdat_;
	u8 _t1_;
	u8 _pg_;//, _bf_sz_;
	u8 _bf_dt_[5];
	u16 _num_h_, _num_v_;
	u16 _wdth_, _hght_;
	u16 _wt1_, _wt2_;
	u16 _ofst_indx_, _ofst_v_od_, _ofst_v_evn_;
	
	_pg_ = _prp_pg & 0x07;
	_prp_pg &= 0xc0;

	_hght_ = ((_bmp_ptr[OSD_TBL_V_SZ_MSB])<<8) + _bmp_ptr[OSD_TBL_V_SZ_LSB];
	_wdth_ = ((_bmp_ptr[OSD_TBL_H_SZ_MSB])<<8) + _bmp_ptr[OSD_TBL_H_SZ_LSB];
	//_wdth_ >>= 1;
	_ofst_indx_ = (_wdth_*_hght_)*_bmp_ptr[OSD_TBL_CLMN];
	_ofst_indx_ = _ofst_indx_*(_indx/_bmp_ptr[OSD_TBL_CLMN]);			//... data size of one index row (= (one bitmap icon size)*column)
	_ofst_indx_ = _ofst_indx_+((_indx%_bmp_ptr[OSD_TBL_CLMN])*_wdth_);	//... add array_index to offset for 1 index column

	//_wdth_ = _bmp_ptr[OSD_TBL_H_SZ_LSB]>>2;							//... horizontal size / 4(pixels)

	WriteAsicByteOSD(_dvc,0x06,0x00);
	WriteAsicByteOSD(_dvc,0x08,0x00);

	_wt1_ = _wdth_*_bmp_ptr[OSD_TBL_CLMN];

	for(_num_v_=0;_num_v_<_hght_;_num_v_+=2)

	{//(1<<_bmp_ptr[OSD_TBL_RSLTN])){	//... if(_bmp_ptr[OSD_TBL_RSLTN]==0)	field resolution, else	frame resolution
		_ofst_v_od_ = _num_v_*_wt1_;
		_ofst_v_evn_ = _ofst_v_od_+_wt1_;//(_num_v_+1)*_wt1_;

		WriteAsicByteOSD(_dvc, 0x07, (_pos_y+(_num_v_>>1))&0xff);

		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;								//... define max buffer size
			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_od_+_num_h_;		//
			_bf_dt_[0] = _prp_pg|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp_pg|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp_pg|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp_pg|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc, 0x00, _bf_dt_);

			if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc, 0x05, _pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc, 0x09, (_t1_<<4)|(((_pos_y+(_num_v_>>1))>>8)<<2));		
				while(ReadAsicOSDMemWr(_dvc) & BIT7);								//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc, 0x0a, 0x80 + (_pg_<<2));					//... x path
			}
		}


		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;
			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_evn_+_num_h_;
			_bf_dt_[0] = _prp_pg|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp_pg|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp_pg|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp_pg|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc,0x00,_bf_dt_);

			if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc, 0x05, _pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc, 0x09,(_t1_<<4)|0x0a|(((_pos_y+(_num_v_>>1))>>8)<<2));		
				while(ReadAsicOSDMemWr(_dvc) & BIT7);							//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc, 0x0a, 0x80 + (_pg_<<2));					//... x path
			}
		}
	}
}
//	*/

//==================================================================================
//*
void WriteOSDBmp_DP(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp_pg, u8 _indx, u8 *_bmp_ptr)
//... _pos_x: ~ 180(4 pixel/_pos_x), _pos_y: ~ 240/288 domain
{
//	u8 _wdat_;
	u8 _t1_;
	u8 _pg_;//, _bf_sz_;
	u8 _bf_dt_[5];
	u16 _num_h_, _num_v_;
	u16 _wdth_, _hght_;
	u16 _wt1_, _wt2_;
	u16 _ofst_indx_, _ofst_v_od_, _ofst_v_evn_;

	_pg_ = _prp_pg & 0x07;
	_prp_pg &= 0xc0;

	_hght_ = ((_bmp_ptr[OSD_TBL_V_SZ_MSB])<<8)+_bmp_ptr[OSD_TBL_V_SZ_LSB];
	_wdth_ = ((_bmp_ptr[OSD_TBL_H_SZ_MSB])<<8)+_bmp_ptr[OSD_TBL_H_SZ_LSB];
	
	_ofst_indx_ = (_wdth_*_hght_)*_bmp_ptr[OSD_TBL_CLMN];
	_ofst_indx_ = _ofst_indx_*(_indx/_bmp_ptr[OSD_TBL_CLMN]);		    //... data size of one index row (= (one bitmap icon size)*column)
	_ofst_indx_ = _ofst_indx_+((_indx%_bmp_ptr[OSD_TBL_CLMN])*_wdth_);	//... add array_index to offset for 1 index column

	//_wdth_ = _bmp_ptr[OSD_TBL_H_SZ_LSB]>>2;							//... horizontal size / 4(pixels)

	WriteAsicByteOSD(_dvc,0x06,0x00);
	WriteAsicByteOSD(_dvc,0x08,0x00);

	_wt1_ = _wdth_*_bmp_ptr[OSD_TBL_CLMN];

	for(_num_v_=0;_num_v_<_hght_;_num_v_+=2)

	{//(1<<_bmp_ptr[OSD_TBL_RSLTN])){	//... if(_bmp_ptr[OSD_TBL_RSLTN]==0)	field resolution, else	frame resolution
		_ofst_v_od_ = _num_v_*_wt1_;
		_ofst_v_evn_ = _ofst_v_od_+_wt1_;//(_num_v_+1)*_wt1_;
        
		WriteAsicByteOSD(_dvc,0x07,(_pos_y+(_num_v_>>1))&0xff);

		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;								//... define max buffer size
			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_od_+_num_h_;	//
			_bf_dt_[0] = _prp_pg|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp_pg|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp_pg|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp_pg|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc,0x00,_bf_dt_);

			if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc,0x05,_pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc,0x09,(_t1_<<4)|(((_pos_y+(_num_v_>>1))>>8)<<2));		

				while(ReadAsicOSDMemWr(_dvc)&BIT7);					//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc,0x0a,0x80+(_pg_<<2));			//... x path
			}
		}
		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;

			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_evn_+_num_h_;
			_bf_dt_[0] = _prp_pg|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp_pg|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp_pg|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp_pg|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc,0x00,_bf_dt_);

			if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc,0x05,_pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc,0x09,(_t1_<<4)|0x0a|(((_pos_y+(_num_v_>>1))>>8)<<2));		
				while(ReadAsicOSDMemWr(_dvc)&BIT7);					//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc,0x0a,0x80+(_pg_<<2));			//... x path
			}
		}
	}
}
//	*/
//==================================================================================

//==================================================================================
//*
void WriteOSDBmpY(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _prp, u8 _indx, u8 *_bmp_ptr)
//... _pos_x: ~ 180(4 pixel/_pos_x), _pos_y: ~ 240/288 domain
{
//	u8 _wdat_;
	u8 _t1_;
//	u8 _pg_;//, _bf_sz_;
	u8 _bf_dt_[5];
	u16 _num_h_, _num_v_;
	u16 _wdth_, _hght_;
	u16 _wt1_, _wt2_;
	u16 _ofst_indx_, _ofst_v_od_, _ofst_v_evn_;
	
#if	defined(__EN_ISR__)
//	EA = 0;
#endif

    _prp |= _prp>>4;    //  y path

	_hght_ = ((_bmp_ptr[OSD_TBL_V_SZ_MSB])<<8)+_bmp_ptr[OSD_TBL_V_SZ_LSB];
	_wdth_ = ((_bmp_ptr[OSD_TBL_H_SZ_MSB])<<8)+_bmp_ptr[OSD_TBL_H_SZ_LSB];
	_wdth_ >>= 1;
	
	_ofst_indx_ = (_wdth_*_hght_)*_bmp_ptr[OSD_TBL_CLMN];
	_ofst_indx_ = _ofst_indx_*(_indx/_bmp_ptr[OSD_TBL_CLMN]);		//... data size of one index row (= (one bitmap icon size)*column)
	_ofst_indx_ = _ofst_indx_+((_indx%_bmp_ptr[OSD_TBL_CLMN])*_wdth_);	//... add array_index to offset for 1 index column

	WriteAsicByteOSD(_dvc,0x06,0x00);
	WriteAsicByteOSD(_dvc,0x08,0x00);

	_wt1_ = _wdth_*_bmp_ptr[OSD_TBL_CLMN];

	for(_num_v_=0;_num_v_<_hght_;_num_v_+=2){//(1<<_bmp_ptr[OSD_TBL_RSLTN])){	//... if(_bmp_ptr[OSD_TBL_RSLTN]==0)	field resolution, else	frame resolution
		_ofst_v_od_ = _num_v_*_wt1_;
		_ofst_v_evn_ = _ofst_v_od_+_wt1_;//(_num_v_+1)*_wt1_;

		WriteAsicByteOSD(_dvc,0x07,(_pos_y+(_num_v_>>1))&0xff);

		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;								//... define max buffer size

			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_od_+_num_h_;		//
			_bf_dt_[0] = _prp|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc,0x00,_bf_dt_);

			if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc,0x05,_pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc,0x09,(_t1_<<4)|(((_pos_y+(_num_v_>>1))>>8)<<2));		

				while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc,0x0a,0xa0);					//... y path
				//WriteAsicByteOSD(_dvc,0x0a,0x80);					//... X path
			}
		}

		//if(_bmp_ptr[OSD_TBL_RSLTN]){
		for(_num_h_=0;_num_h_<_wdth_;_num_h_+=4){
			_t1_ = (_num_h_>>2)&0x0f;
			_wt2_ = OSD_TBL_DAT+_ofst_indx_+_ofst_v_evn_+_num_h_;
			_bf_dt_[0] = _prp|_bmp_ptr[_wt2_+0];
			_bf_dt_[1] = _prp|_bmp_ptr[_wt2_+1];
			_bf_dt_[2] = _prp|_bmp_ptr[_wt2_+2];
			_bf_dt_[3] = _prp|_bmp_ptr[_wt2_+3];
			_bf_dt_[4] = 0x80+_t1_;
			WriteAsicTableOSD(_dvc,0x00,_bf_dt_);
				if((_t1_==0x0f)||((_num_h_+4)>=_wdth_)){
				WriteAsicByteOSD(_dvc,0x05,_pos_x+(_num_h_>>2)-_t1_);
				WriteAsicByteOSD(_dvc,0x09,(_t1_<<4)|0x0a|(((_pos_y+(_num_v_>>1))>>8)<<2));		
					while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for odd field
				WriteAsicByteOSD(_dvc,0x0a,0xa0);					//... y path
				//WriteAsicByteOSD(_dvc,0x0a,0x80);					//... X path
			}
		}
	//}
}

#if	defined(__EN_ISR__)
//	EA = 1;
#endif
}
//	*/
//==================================================================================
void WriteOSDClrX(u8 _dvc, u8 _osd_pg, u8 _pos_x, u16 _pos_y, u8 _wdth, u16 _hght)	//... only one _pth at once
{
//	u8 _t1_;
	u8 _t2_, _t3_;
	
#if	defined(__EN_ISR__)
//	EA = 0;
#endif
//	u8 _t1_;

	WriteAsicByteOSD(_dvc,0x00,0xff);					//... 1st pixel
	WriteAsicByteOSD(_dvc,0x01,0xff);					//... 2nd pixel
	WriteAsicByteOSD(_dvc,0x02,0xff);					//... 3rd pixel
	WriteAsicByteOSD(_dvc,0x03,0xff);					//... 4th pixel
	//... acceleration 을 사용할 경우 buffer write 과정 생략가능.
//	WriteAsicByteOSD(_dvc,0x04,0x80);					//... write to buffer

//... start position
//	_pos_x <<= 2;														//... (_pos_x)*4 -> 4 pixel * 4 -> 16 pixel char
	_pos_y = (_pos_y<<1)+(_pos_y<<3);							//... (_pos_y)*(2+8)

//	WriteAsicByteOSD(_dvc,0x05,_pos_x);
	WriteAsicByteOSD(_dvc,0x07,_pos_y&0xff);

//... end position
//	_pos_x += _wdth<<2;
	_hght = _pos_y+((_hght<<1)+(_hght<<3));

//	WriteAsicByteOSD(_dvc,0x06,--_pos_x);
	WriteAsicByteOSD(_dvc,0x08,(--_hght)&0xff);

//	WriteAsicByteOSD(_dvc,0x09,((_pos_y>>8)<<2)+(_hght>>8));		//... odd field
//	WriteAsicByteOSD(_dvc,0x0a,0xc0);										//... acceleration|x path
//
//	while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for odd field
////Delay(1);

	WriteAsicByteOSD(_dvc,0x09,0x02|((_pos_y>>8)<<2)+(_hght>>8));	//... ~ even field
//	WriteAsicByteOSD(_dvc,0x0a,0xc0);										//... acceleration|x path
//
//	while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for even field
////Delay(1);
	_pos_x <<= 2;
	_wdth <<= 2;
	
	_t2_ = _wdth>>4;
	_t3_ = _wdth&0x0f;
	
	if (_t2_ != 0) {
			WriteAsicByteOSD(0,0x05,_pos_x);
			WriteAsicByteOSD(0,0x06,_pos_x+(_t2_<<4));//79);
		WriteAsicByteOSD(0,0x0a,0xc0+(_osd_pg<<2));										//... acceleration|x path
		//  read_data[0] = ReadAsicOSDMemWr(_dvc);
		while(ReadAsicOSDMemWr(_dvc)&BIT7){}								//... wait finishing write for even field
	}
	if (_t3_ != 0){
			WriteAsicByteOSD(0,0x05,_pos_x+(_t2_<<4));//_t1_);
			WriteAsicByteOSD(0,0x06,_pos_x+((_t2_<<4)+_t3_-1));//79);
		WriteAsicByteOSD(0,0x0a,0xc0+(_osd_pg<<2));										//... acceleration|x path
		while(ReadAsicOSDMemWr(_dvc)&BIT7){}								//... wait finishing write for even field
	}
	

#if	defined(__EN_ISR__)
//	EA = 1;
#endif
}
//==================================================================================
void WriteOSDClrY(u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _wdth, u16 _hght)	//... only one _pth at once
{
//	u8 _t1_;
	u8 _t2_, _t3_;
	
#if	defined(__EN_ISR__)
//	EA = 0;
#endif
//	u8 _t1_;

	WriteAsicByteOSD(_dvc,0x00,0xff);					//... 1st pixel
	WriteAsicByteOSD(_dvc,0x01,0xff);					//... 2nd pixel
	WriteAsicByteOSD(_dvc,0x02,0xff);					//... 3rd pixel
	WriteAsicByteOSD(_dvc,0x03,0xff);					//... 4th pixel
	//... acceleration 을 사용할 경우 buffer write 과정 생략가능.
//	WriteAsicByteOSD(_dvc,0x04,0x80);					//... write to buffer

//... start position
//	_pos_x <<= 1;														//... (_pos_x)*2 -> 8 pixel * 2 -> 16 pixel char
	_pos_y = (_pos_y<<1)+(_pos_y<<3);							//... (_pos_y)*(2+8)

//	WriteAsicByteOSD(_dvc,0x05,_pos_x);
	WriteAsicByteOSD(_dvc,0x07,_pos_y&0xff);

//... end position
//	_pos_x += _wdth<<1;
	_hght = _pos_y+((_hght<<1)+(_hght<<3));

//	WriteAsicByteOSD(_dvc,0x06,--_pos_x);
	WriteAsicByteOSD(_dvc,0x08,(--_hght)&0xff);

//	WriteAsicByteOSD(_dvc,0x09,((_pos_y>>8)<<2)+(_hght>>8));		//... odd field
//	WriteAsicByteOSD(_dvc,0x0a,0xe0);										//... acceleration|y path
//
//	while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for odd field
////Delay(1);

	WriteAsicByteOSD(_dvc,0x09,0x02|((_pos_y>>8)<<2)+(_hght>>8));	//... ~ even field
//	WriteAsicByteOSD(_dvc,0x0a,0xe0);										//... acceleration|y path
//
//	while(ReadAsicOSDMemWr(_dvc)&BIT7);								//... wait finishing write for even field
////Delay(1);
	_pos_x <<= 1;														//... (_pos_x)*2 -> 8 pixel * 2 -> 16 pixel char
	_wdth <<= 1;
	
	_t2_ = _wdth>>4;
	_t3_ = _wdth&0x0f;
	
	if (_t2_ != 0) {
			WriteAsicByteOSD(0,0x05,_pos_x);
			WriteAsicByteOSD(0,0x06,_pos_x+(_t2_<<4));//79);
		WriteAsicByteOSD(0,0x0a,0xe0);										//... acceleration|y path
		while(ReadAsicOSDMemWr(_dvc)&BIT7){}								//... wait finishing write for even field
	}
	if (_t3_ != 0){
			WriteAsicByteOSD(0,0x05,_pos_x+(_t2_<<4));//_t1_);
			WriteAsicByteOSD(0,0x06,_pos_x+((_t2_<<4)+_t3_-1));//79);
		WriteAsicByteOSD(0,0x0a,0xe0);										//... acceleration|y path
		while(ReadAsicOSDMemWr(_dvc)&BIT7){}								//... wait finishing write for even field
	}

#if	defined(__EN_ISR__)
//	EA = 1;
#endif
}
//==================================================================================
//void WriteOSDClr(u8 _pth, u8 _dvc, u8 _pos_x, u16 _pos_y, u8 _wdth, u16 _hght)	//... 16x20 font 기준.
//{
//	if(BitSet(_pth,PTH_X))	WriteOSDClrX(_dvc,_pos_x,_pos_y,_wdth,_hght);
//	if(BitSet(_pth,PTH_Y))	WriteOSDClrY(_dvc,_pos_x,_pos_y,_wdth,_hght);
//}
//==================================================================================
void	SetOSDCol(u8 *_tbl_osd_clr)//u8 _col_num, u8 _y, u8 _cb, u8 _cr)
{
	u8 _t1_, _t2_;//, _t3_;
	
	_t1_ = _tbl_osd_clr[0];
	for(_t2_=0;_t2_<_t1_;_t2_++){
		WriteAsicByte(MASTER,DVC_PG2,0x0b,_tbl_osd_clr[1+(_t2_<<2)]);
		WriteAsicByte(MASTER,DVC_PG2,0x0c,_tbl_osd_clr[1+(_t2_<<2)+1]);
		WriteAsicByte(MASTER,DVC_PG2,0x0d,_tbl_osd_clr[1+(_t2_<<2)+2]);
		WriteAsicByte(MASTER,DVC_PG2,0x0e,_tbl_osd_clr[1+(_t2_<<2)+3]);

//		while(ReadAsicByte(MASTER,DVC_PG2,0x0e)&BIT7);
	}
}
//==================================================================================
void	InitOSDCol(void)
{

	//SetOSDCol(ct_tst_24bit);
	//SetOSDCol(ct_tst_fnt_16x20);
    //SetOSDCol(ct_ALPHA_NUM_32x40_4c);
    SetOSDCol(ct_CHANNEL);
}
//==================================================================================

u8	GetCodeLength(unsigned char *_str)
{
	 u8 _cnt_=0;

  while((*_str++)!='\0')++_cnt_;
  return (_cnt_);
}

void WriteOSDStrX(u8 _dvc, u8 _pos_x, u8 _pos_y, u8 _prp, unsigned char *_str_ptr)
{
	u8 _lngth_ = GetCodeLength(_str_ptr);
	u8 _indx_;
	u8 _t1_, _t2_ = 0;

    
	for(_t1_=0 ;_t1_< 3 ;_t1_++){
        if(_str_ptr[_t1_] <0x40)
		    _indx_ = _str_ptr[_t1_]-0x15;	
        else if(_str_ptr[_t1_] >= 0x40)
            _indx_ = _str_ptr[_t1_]-0x40;	
        
        WriteOSDBmpX(_dvc,_pos_x+_t2_,_pos_y,_prp,_indx_,gt_ALPHA_NUM_32x40_4c_Alpha_Num_32x40);
        _t2_ += 4;
    }
    /*
    for(_t1_=0;_t1_<_lngth_;_t1_++){
        if(_str_ptr[_t1_] <0x40)
		    _indx_ = _str_ptr[_t1_]-0x20;
        
        
        //WriteOSDBmp_DP(_dvc,_pos_x+_t2_,_pos_y,_prp,_indx_,gt_tst_fnt_16x20_tst_fnt_16x20);
		WriteOSDBmpX(_dvc,_pos_x+_t2_,_pos_y,_prp,_indx_,gt_tst_fnt_16x20_tst_fnt_16x20);
        //WriteOSDBmpY(_dvc,_pos_x+_t1_,_pos_y,_prp,_indx_,gt_tst_fnt_16x20_tst_fnt_16x20);
        _t2_ += 2;
	}
	*/
}

/*********(C) COPYRIGHT 2010 TaeHa Mechatronics Co., Ltd. *****END OF FILE****/
