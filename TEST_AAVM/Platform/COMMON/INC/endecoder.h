
#define CIPHER_COMMON_CRC_PARAM	0x1211

#define CIPHER_COMMON_COMMON_ENKEY 0x6757

//#include "sys/extypes.h"
//#include "stm32f10x_lib.h"

#define TDES


#ifdef TDES


typedef unsigned long  DKEY;		// Tiny Des ��

#else

typedef unsigned __int64 DKEY;		// Des64 ��

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

// ��ȣȭ Ű�� set �ϴ� �Լ� , encode , decode ���� set ���ֱ� �ٶ� 	
void setCipherParam(WORD param1,WORD param2); 

// ��ȣȭ �ϴ� �Լ�
// inbufsize ũ���� inbuf ���� ������ outbuf�� ����. �̶� ��ȣȭ�� �� ũ��� ���ϰ�����.
INT8 encode(BYTE* inbuf,int16_t inbufsize,BYTE* outbuf,int16_t outbufsize);

// ��ȣ�ؼ� �ϴ� �Լ�
// inbuf size ũ���� inbuf ���� ������ �ؼ��Ͽ� outbuf �� ����. �̶� �ؼ��� ������ �� ũ��� ��������
INT8 decode(BYTE* inbuf,int16_t inbufsize,BYTE* outbuf,int16_t outbufsize);


#ifdef __cplusplus 
}
#endif 

