
#define CIPHER_COMMON_CRC_PARAM	0x1211

#define CIPHER_COMMON_COMMON_ENKEY 0x6757

//#include "sys/extypes.h"
//#include "stm32f10x_lib.h"

#define TDES


#ifdef TDES


typedef unsigned long  DKEY;		// Tiny Des 용

#else

typedef unsigned __int64 DKEY;		// Des64 용

#endif

#define uint8_t unsigned char
#define uint16_t unsigned short
#define int8_t signed char
#define int16_t signed short


#define BYTE uint8_t
#define WORD uint16_t
#define UINT8 uint8_t
#define INT8 int8_t

#if 0
#define BYTE unsigned char
#define WORD unsigned short
#define UINT8 unsigned char
#define INT8 signed char
#endif

#ifdef __cplusplus 
extern "C" { 
#endif 

// 암호화 키를 set 하는 함수 , encode , decode 전에 set 해주기 바람 	
void setCipherParam(WORD param1,WORD param2); 

// 암호화 하는 함수
// inbufsize 크기의 inbuf 안의 내용을 outbuf에 쓴다. 이때 암호화된 그 크기는 리턴값으로.
INT8 encode(BYTE* inbuf,int16_t inbufsize,BYTE* outbuf,int16_t outbufsize);

// 암호해석 하는 함수
// inbuf size 크기의 inbuf 안의 내용을 해석하여 outbuf 에 쓴다. 이때 해석된 원문의 그 크기는 원문으로
INT8 decode(BYTE* inbuf,int16_t inbufsize,BYTE* outbuf,int16_t outbufsize);


#ifdef __cplusplus 
}
#endif 

