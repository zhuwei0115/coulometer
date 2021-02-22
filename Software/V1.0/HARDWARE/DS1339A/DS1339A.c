#ifndef __DS1339A_C
#define __DS1339A_C

#include "ds1339a.h"
#include "myiic.h"

#define Seconds_Address 0x00
#define Minutes_Address 0x01
#define Hours_Address   0x02
#define Day_Address     0x03
#define Date_Address    0x04
#define Month_Century_Address     0x05
#define Year_Address    0x06

u8 Ds1339a_IIC_Read_Byte(u8 Address)
{
	IIC_Start();
	IIC_Send_Byte(DS1339A_IIC_Write_Address);
	IIC_Wait_Ack();
	IIC_Send_Byte(Address);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(DS1339A_IIC_Read_Address);
	Value = IIC_Read_Byte(NACK);
	IIC_Stop();
	return Value;
}

void Ds1339a_IIC_Write_Byte(u8 Address , u8 Value)
{
	IIC_Start();
	IIC_Send_Byte(DS1339A_IIC_Write_Address);
	IIC_Wait_Ack();
	IIC_Send_Byte(Address);
	IIC_Wait_Ack();
	IIC_Send_Byte(Value);
	IIC_Wait_Ack();
	IIC_Stop();
}

void Get_Ds1339a_Value(void)
{
	u8 temp;
	temp = Ds1339a_IIC_Read_Byte(Seconds_Address);
	RTC_Value1.Seconds = (temp&0x70>>4)*10 + temp&0x0f; 
	
	temp = Ds1339a_IIC_Read_Byte(Minutes_Address);
	RTC_Value1.Minutes = (temp&0x70>>4)*10 + temp&0x0f; 
	
	temp = Ds1339a_IIC_Read_Byte(Hours_Address);
	if(temp&0x40)     //12小时制
		temp = (temp&0x20>>5)*12 + (temp&0x10>>4)*10 + (temp&0x0f);   //转换成24小时制
	else 			 //24小时制
		temp = (temp&0x20>>5)*20 + (temp&0x10>>4)*10 + (temp&0x0f);
	RTC_Value1.Hours = temp;

	temp = Ds1339a_IIC_Read_Byte(Day_Address); 
	RTC_Value1.Day = temp;

	temp = Ds1339a_IIC_Read_Byte(Date_Address); 
	RTC_Value1.Date = (temp&0x30>>4)*10 + temp&0x0f;

	temp = Ds1339a_IIC_Read_Byte(Month_Century_Address); 
	RTC_Value1.Month = (temp&0x1>>4)*10 + temp&0x0f;

	RTC_Value1.Centry = temp&0x80>>7;

	temp = Ds1339a_IIC_Read_Byte(Year_Address);	
	RTC_Value1.Year = (temp>>4)*10 + temp&0x0f;

}

void Set_Ds1339a_Value(void)
{
	u8 temp;
	temp = ((RTC_Value1.Seconds/10)&0x07<<4) | RTC_Value1.Seconds%10;
	Ds1339a_IIC_Write_Byte(Seconds_Address , temp);
	
	temp = ((RTC_Value1.Minutes/10)&0x07<<4) | RTC_Value1.Minutes%10;
	Ds1339a_IIC_Write_Byte(Minutes_Address , temp);	
	
	temp = ((RTC_Value1.Hours/10)&0x03<<4) | RTC_Value1.Hours%10;  //强制设置24小时制
	Ds1339a_IIC_Write_Byte(Hours_Address , temp);
	
	temp = RTC_Value1.Day;	
	Ds1339a_IIC_Write_Byte(Day_Address , temp);
	
	temp = ((RTC_Value1.Date/10)&0x03<<4) | RTC_Value1.Date%10;  
	Ds1339a_IIC_Write_Byte(Date_Address , temp);
	
	temp = RTC_Value1.Centry<<7 | ((RTC_Value1.Date/10)&0x3<<4) | RTC_Value1.Date%10;
	Ds1339a_IIC_Write_Byte(Month_Century_Address , temp);	

	temp = ((RTC_Value1.Year/10<<4) | RTC_Value1.Year%10;  
	Ds1339a_IIC_Write_Byte(Year_Address , temp);	

}


