#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define ADC_Voltage_CH 	ADC_Channel_0
#define ADC_NTC1_CH    	ADC_Channel_1
#define ADC_NTC2_CH    	ADC_Channel_2
#define ADC_Current_CH  ADC_Channel_6
#define ADC_REF_2V5_CH 	ADC_Channel_7

#define ADC_Average_times 	 50
#define ADC_Voltage_Divider  30
#define Voltage_REF          250  //ʵ�ʵ�ѹ�Ŵ�100��
#define ADC_Current_Gain     10   //��������2.5mR,�˷ŷŴ�10������ADC


void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 
