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

//===================================================================
//	全局变量定义及声明
//===================================================================

#ifdef	__DS1339A_C
			RTC_Value RTC_Value1;
#else
extern		RTC_Value RTC_Value1;
#endif	

u8 Ds1339a_IIC_Read_Byte(u8 Address);
void Ds1339a_IIC_Write_Byte(u8 Address , u8 Value);
void Get_Ds1339a_Value(void);
void Set_Ds1339a_Value(void);

#endif



