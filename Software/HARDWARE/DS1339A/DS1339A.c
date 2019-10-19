#include "ds1339a.h"
#include "myiic.h"

RTC_Value RTC_Value_Typedef;


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




