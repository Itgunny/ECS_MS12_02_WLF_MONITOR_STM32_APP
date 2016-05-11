// ++, 160511 bwk
#ifndef __WLF_MONITOR_RTC_H
#define __WLF_MONITOR_RTC_H


#define ADDRESS_RTC_FM31XX_YEAR        0x08
#define ADDRESS_RTC_FM31XX_MONTH       0x07
#define ADDRESS_RTC_FM31XX_DATE        0x06
#define ADDRESS_RTC_FM31XX_DAY         0x05
#define ADDRESS_RTC_FM31XX_HOUR        0x04
#define ADDRESS_RTC_FM31XX_MINUTE      0x03
#define ADDRESS_RTC_FM31XX_SECOND      0x02

#define ADDRESS_RTC_YEAR        0x09
#define ADDRESS_RTC_MONTH       0x08
#define ADDRESS_RTC_DATE        0x06
#define ADDRESS_RTC_DAY         0x07
#define ADDRESS_RTC_HOUR        0x05
#define ADDRESS_RTC_MINUTE      0x04
#define ADDRESS_RTC_SECOND      0x03


extern void WRITE_RTC(WL9FM_DATA_RTC RTC_Data);
extern void READ_RTC(WL9FM_DATA_RTC *RTC_Data);

void PCA2119_Delay(void);
void PCA2119_START(void);
void PCA2119_STOP(void);
void PCA2119_BIT_WRITE(unsigned char bit);
unsigned char PCA2119_BIT_READ(void);
void PCA2119_BYTE_WRITE(unsigned char byte);
unsigned char PCA2119_BYTE_READ(void);
void write_RTC_Companion(unsigned char address, unsigned char data);
unsigned char read_RTC_Companion(unsigned char address);


void write_PCA2129_TimewSet(unsigned char address, unsigned char *data);
unsigned char pca2129_get_time(unsigned char address);
#endif
// --, 160511 bwk
