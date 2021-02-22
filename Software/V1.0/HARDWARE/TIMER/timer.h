#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

#define Bat_Idle 		 0
#define Bat_Discharging  1
#define Bat_Charging 	 2	

typedef struct
{
	u16 ADC_Voltage;
	u16 ADC_NTC1;
	u16 ADC_NTC2;
	u16 ADC_Current;
	u8  Bat_Status;
	u16 ADC_REF_2V5;
}ADC_Value;


ADC_Value ADC_Value1;

void TIM3_Int_Init(u16 arr,u16 psc); 
 
#endif
