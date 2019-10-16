#include "timer.h"
#include "adc.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

ADC_Value ADC_Value1;


//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	u32 temp1_val=0,temp2_val=0,temp3_val=0,temp4_val=0,temp5_val=0;
	u8  t;

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 		
		if(t<ADC_Average_times)
		{
			temp1_val+=Get_Adc(ADC_Voltage_CH);
			temp2_val+=Get_Adc(ADC_NTC1_CH);
			temp3_val+=Get_Adc(ADC_NTC2_CH);
			temp4_val+=Get_Adc(ADC_Current_CH);
			temp5_val+=Get_Adc(ADC_REF_2V5_CH);
			t++ ;
		}
		else
		{
			temp1_val = temp1_val/ADC_Average_times;
			temp2_val = temp2_val/ADC_Average_times;
			temp3_val = temp3_val/ADC_Average_times;
			temp4_val = temp4_val/ADC_Average_times;
			temp5_val = temp5_val/ADC_Average_times;
			 
			ADC_Value1.ADC_Voltage = (u16)Voltage_REF*temp1_val*ADC_Voltage_Divider/temp5_val;   //��Դ�����ѹ
			ADC_Value1.ADC_NTC1    = temp2_val;
			ADC_Value1.ADC_NTC2    = temp3_val;
			ADC_Value1.ADC_Current = 
			ADC_Value1.ADC_REF_2V5 = temp5_val


			
			temp1_val = 0;
			temp2_val = 0;
			temp3_val = 0;
			temp4_val = 0;
			temp5_val = 0;
			t = 0;

			
		}		
	}
}












