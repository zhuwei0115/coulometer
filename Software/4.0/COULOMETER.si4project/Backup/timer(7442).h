#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

typedef struct
{
	u16 ADC_Voltage;
	u16 ADC_NTC1;
	u16 ADC_NTC2;
	u16 ADC_Current;
	u16 ADC_REF_2V5;
}ADC_Value;




void TIM3_Int_Init(u16 arr,u16 psc); 
 
#endif
