#ifndef __DS1339A_H
#define __DS1339A_H

#define DS1339A_IIC_Read_Address 0xd1
#define DS1339A_IIC_Write_Address 0xd0

typedef	struct{
	u8 Seconds;
	u8 Minutes;
	u8 Hours;
	u8 Day;
	u8 Date;
	u8 Month;
	u8 Year;
	u8 Centry;
}RTC_Value;



#endif



