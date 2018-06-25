#include "WL9F_Monitor_APP.h"

#define RTC_PortChange_in			0x00
#define RTC_PortChange_out			0x01

#define RTC_WRITE_COMMAND			0xa2
#define RTC_READ_COMMAND			0xa3

#define PCA2119_SCL(x)					GPIO_WriteBit(FM31X4_I2C1_PORT, FM31X4_I2C1_SCL,x)
#define PCA2119_SDA_READ()				GPIO_ReadInputDataBit(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA)

#define PCA2119_SDA(x)					GPIO_WriteBit(FM31X4_I2C1_PORT, FM31X4_I2C1_SDA,x)

#define PCA2119_SDAIN()   				RTC_PortChange(RTC_PortChange_in)
#define PCA2119_SDAOUT()  				RTC_PortChange(RTC_PortChange_out) 

#define PCA2119_NACK                 			PCA2119_BIT_WRITE(1)
#define PCA2119_ACK                 			PCA2119_BIT_WRITE(0)

extern unsigned char Hardware_Revision;

void RTC_PortChange(unsigned char dir)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(dir)	// Output
	{	
		GPIO_InitStructure.GPIO_Pin = FM31X4_I2C1_SDA;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
                GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(FM31X4_I2C1_PORT, &GPIO_InitStructure);	
	}
	else		// Input
	{	
		GPIO_InitStructure.GPIO_Pin = 	FM31X4_I2C1_SDA ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
                GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(FM31X4_I2C1_PORT, &GPIO_InitStructure);
	}

}

void WRITE_RTC_Year(unsigned char data)
{
	unsigned char temp;

	if (data > 99)
		return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_YEAR, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_YEAR, temp);
}

unsigned char READ_RTC_Year(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_YEAR);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_YEAR);

	temp = 0;
	temp += ((data >> 4) & 0x0f) * 10;
	temp += data & 0x0f;

	return temp;
}

void WRITE_RTC_Month(unsigned char data)
{
	unsigned char temp;

	if (data > 12)
	    return;

	if (data < 1)
	    return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_MONTH, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_MONTH, temp);
}

unsigned char READ_RTC_Month(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_MONTH);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_MONTH);

	temp = 0;
	temp += ((data >> 4) & 0x01) * 10;
	temp += data & 0x0f;

	return temp;
}


void WRITE_RTC_Date(unsigned char data)
{
	unsigned char temp;

	if (data > 31)
		return;

	if (data < 1)
		return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_DATE, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_DATE, temp);
}

unsigned char READ_RTC_Date(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_DATE);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_DATE);

	temp = 0;
	temp += ((data >> 4) & 0x03) * 10;
	temp += data & 0x0f;

	return temp;
}


void WRITE_RTC_Day(unsigned char data)
{
	unsigned char temp;

	if(Hardware_Revision>=REVH)
	{
		temp = data;
		write_RTC_Companion(ADDRESS_RTC_DAY, temp);
	}
	else
	{
		if (data > 7)
			return;

		if (data < 1)
			return;

		temp = data;

		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_DAY, temp);
	}
}

unsigned char READ_RTC_Day(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_DAY);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_DAY);

	temp = data & 0x07;

	return temp;
}


void WRITE_RTC_Hour(unsigned char data)
{
	unsigned char temp;

	if (data > 23)
	    return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_HOUR, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_HOUR, temp);
}

unsigned char READ_RTC_Hour(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_HOUR);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_HOUR);

	temp = 0;
	temp += ((data >> 4) & 0x03) * 10;
	temp += data & 0x0f;

	return temp;
}

void WRITE_RTC_Minute(unsigned char data)
{
	unsigned char temp;

	if (data > 59)
	    return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_MINUTE, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_MINUTE, temp);
}

unsigned char READ_RTC_Minute(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_MINUTE);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_MINUTE);

	temp = 0;
	temp += ((data >> 4) & 0x07) * 10;
	temp += data & 0x0f;

	return temp;
}

void WRITE_RTC_Second(unsigned char data)
{
	unsigned char temp;

	if (data > 59)
		return;

	temp = 0;
	temp += (data / 10) << 4;
	temp += data % 10;

	if(Hardware_Revision>=REVH)
		write_RTC_Companion(ADDRESS_RTC_SECOND, temp);
	else
		WRITE_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_SECOND, temp);
}

unsigned char READ_RTC_Second(void)
{
	unsigned char data;
	unsigned char temp;

	if(Hardware_Revision>=REVH)
		data = read_RTC_Companion(ADDRESS_RTC_SECOND);
	else
		data = READ_FM31xx_RTC_Companion(ADDRESS_RTC_FM31XX_SECOND);

	temp = 0;
	temp += ((data >> 4) & 0x07) * 10;
	temp += data & 0x0f;

	return temp;
}

void WRITE_RTC(WL9FM_DATA_RTC RTC_Data)
{    
	if(Hardware_Revision >=REVH)
	{	
		WRITE_RTC_Year(RTC_Data.Year);
		WRITE_RTC_Month(RTC_Data.Month);
		WRITE_RTC_Date(RTC_Data.Date);
		WRITE_RTC_Day(RTC_Data.Day);
		WRITE_RTC_Hour(RTC_Data.Hour);
		WRITE_RTC_Minute(RTC_Data.Minute);
		WRITE_RTC_Second(RTC_Data.Second);
	}
	else
	{
		WRITE_FM31xx_RTC_Companion(0x00, 0x02);

		WRITE_RTC_Year(RTC_Data.Year);
		WRITE_RTC_Month(RTC_Data.Month);
		WRITE_RTC_Date(RTC_Data.Date);
		WRITE_RTC_Day(RTC_Data.Day);
		WRITE_RTC_Hour(RTC_Data.Hour);
		WRITE_RTC_Minute(RTC_Data.Minute);
		WRITE_RTC_Second(RTC_Data.Second);

		WRITE_FM31xx_RTC_Companion(0x00, 0x00);

		WRITE_FM31xx_RTC_Companion(0x01, 0x00);
	}
}

void READ_RTC(WL9FM_DATA_RTC *RTC_Data)
{    

	if(Hardware_Revision >=REVH)
	{	
		RTC_Data->Year 	 = READ_RTC_Year();
		RTC_Data->Month  = READ_RTC_Month();
		RTC_Data->Date 	 = READ_RTC_Date();
		RTC_Data->Day 	 = READ_RTC_Day();
		RTC_Data->Hour   = READ_RTC_Hour();
		RTC_Data->Minute = READ_RTC_Minute();
		RTC_Data->Second = READ_RTC_Second();
	}
	else
	{
		WRITE_FM31xx_RTC_Companion(0x00, 0x01);

		RTC_Data->Year 	 = READ_RTC_Year();
		RTC_Data->Month  = READ_RTC_Month();
		RTC_Data->Date 	 = READ_RTC_Date();
		RTC_Data->Day 	 = READ_RTC_Day();
		RTC_Data->Hour   = READ_RTC_Hour();
		RTC_Data->Minute = READ_RTC_Minute();
		RTC_Data->Second = READ_RTC_Second();

		WRITE_FM31xx_RTC_Companion(0x00, 0x00);
	}
}

void PCA2119_Delay(void)
{
	NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
}

void PCA2119_START(void)
{
#if 0
        // 다름.
	PCA2119_SDAOUT();
	PCA2119_SDA(Bit_SET);
	
	// start
	PCA2119_SDA(Bit_SET);
	PCA2119_SCL(Bit_SET);
	PCA2119_Delay();
	PCA2119_SDA(Bit_RESET);
	PCA2119_Delay();
	PCA2119_SCL(Bit_RESET);
	// start end 
#else
        PCA2119_SDA(Bit_SET);
        PCA2119_SDAOUT();
	PCA2119_SCL(Bit_SET);
	PCA2119_Delay();
	PCA2119_SDA(Bit_RESET);
	PCA2119_Delay();
	PCA2119_SCL(Bit_RESET);
        PCA2119_Delay();
#endif
}

void PCA2119_STOP(void)
{
#if 0
	PCA2119_SDAOUT();
	PCA2119_SDA(Bit_RESET);
	PCA2119_Delay();
	PCA2119_SCL(Bit_SET);
	PCA2119_Delay();
	PCA2119_SDA(Bit_SET);
#else
        PCA2119_SDA(Bit_RESET);
        PCA2119_SDAOUT();
	PCA2119_SCL(Bit_SET);
        PCA2119_Delay();
	PCA2119_SDA(Bit_SET);
        PCA2119_Delay();
#endif
}


void PCA2119_BIT_WRITE(unsigned char bit)
{
	#if 1
	//다름.
        PCA2119_SDA((bit) ? Bit_SET: Bit_RESET);      
        PCA2119_SDAOUT();
	PCA2119_Delay();
	PCA2119_SCL(Bit_SET);
	PCA2119_Delay();
	PCA2119_SCL(Bit_RESET);
	PCA2119_Delay();  
	#else
	PCA2119_SDAOUT();

	PCA2119_SCL(Bit_SET);

	PCA2119_Delay();
	
	PCA2119_SDA((bit) ? Bit_SET: Bit_RESET);

	PCA2119_Delay();

	PCA2119_SCL(Bit_RESET);

	PCA2119_Delay();
	#endif
	
}

unsigned char PCA2119_BIT_READ(void)
{
	unsigned char bit;

	PCA2119_SDAIN();

	PCA2119_SCL(Bit_SET);

	PCA2119_Delay();

	bit = PCA2119_SDA_READ();   

	PCA2119_Delay();

	PCA2119_SCL(Bit_RESET);

	PCA2119_Delay();

	
	return bit;
}

void PCA2119_BYTE_WRITE(unsigned char byte)
{
	unsigned char i;

	for (i = 0; i < 8; i++)
	{
		PCA2119_BIT_WRITE((byte & (1 << (7 - i))) ? 1 : 0);      
	}

	PCA2119_BIT_READ();
}

unsigned char PCA2119_BYTE_READ(void)
{
	unsigned char byte;    
	unsigned char i;

	byte = 0;

	for (i = 0; i < 8; i++)
	{
		byte <<= 1;
		byte |= PCA2119_BIT_READ();      
	}  

	return byte;
}

void write_RTC_Companion(unsigned char address, unsigned char data)
{
	PCA2119_START();    
	PCA2119_BYTE_WRITE(RTC_WRITE_COMMAND);
	PCA2119_BYTE_WRITE(address);
	PCA2119_BYTE_WRITE(data);    
	PCA2119_STOP();
}


void write_PCA2129_TimewSet(unsigned char address, unsigned char *data)
{
	unsigned char temp;
	
	PCA2119_START();    
	PCA2119_BYTE_WRITE(RTC_WRITE_COMMAND);
	PCA2119_BYTE_WRITE(address);

	temp = 0;
	temp += (data[6] / 10) << 4;
	temp += data[6] % 10;
	
	PCA2119_BYTE_WRITE(temp);  // second

	temp = 0;
	temp += (data[5] / 10) << 4;
	temp += data[5] % 10;
	
	PCA2119_BYTE_WRITE(temp);  // min

	temp = 0;
	temp += (data[4] / 10) << 4;
	temp += data[4] % 10;
	
	PCA2119_BYTE_WRITE(temp);  // hour

	temp = 0;
	temp += (data[2] / 10) << 4;
	temp += data[2] % 10;
	
	PCA2119_BYTE_WRITE(temp);  // days

	temp = data[3];
	
	PCA2119_BYTE_WRITE(temp); // weekdays
	
	temp = 0;
	temp += (data[1] / 10) << 4;
	temp += data[1] % 10;
	
	PCA2119_BYTE_WRITE(temp); // month

	temp = 0;
	temp += (data[0] / 10) << 4;
	temp += data[0] % 10;
	PCA2119_BYTE_WRITE(temp);  // year
	
	PCA2119_STOP();
}


unsigned char pca2129_get_time(unsigned char address)
{
	unsigned char data[3];
	
	PCA2119_START();    
	PCA2119_BYTE_WRITE(RTC_WRITE_COMMAND);
	PCA2119_BYTE_WRITE(address);
	PCA2119_STOP();
	
	PCA2119_START();
	PCA2119_BYTE_WRITE(RTC_READ_COMMAND);    
	data[0]= PCA2119_BYTE_READ();
	PCA2119_ACK;
	data[1]= PCA2119_BYTE_READ();
	PCA2119_ACK;
	data[2]= PCA2119_BYTE_READ();
	PCA2119_NACK;
	PCA2119_STOP();
	
	return data[0];
}
	
unsigned char read_RTC_Companion(unsigned char address)
{
	unsigned char data;
	
	PCA2119_START();    
	PCA2119_BYTE_WRITE(RTC_WRITE_COMMAND);
	PCA2119_BYTE_WRITE(address);
	PCA2119_STOP();
	
	PCA2119_START();
	PCA2119_BYTE_WRITE(RTC_READ_COMMAND);    
	data= PCA2119_BYTE_READ();
	PCA2119_NACK;
	PCA2119_STOP();
	
	return data;
}




