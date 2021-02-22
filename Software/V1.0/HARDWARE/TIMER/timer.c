#include "timer.h"
#include "adc.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 

ADC_Value ADC_Value1;


//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	u32 temp1_val=0,temp2_val=0,temp3_val=0,temp4_val=0,temp5_val=0;
	u8  t;

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 		
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
			 
			ADC_Value1.ADC_Voltage = (u16)(Voltage_REF*temp1_val*ADC_Voltage_Divider)/temp5_val;   //电源输入电压*100倍
			ADC_Value1.ADC_NTC1    = temp2_val;
			ADC_Value1.ADC_NTC2    = temp3_val;
			ADC_Value1.ADC_REF_2V5 = temp5_val;
												 //运放参考电压1.5V为2.5V的3/5
			if(temp4_val>(temp5_val*3/5 + 20))	//考虑采样误差，需要+20确保有一段电压值表示空闲
			{
				ADC_Value1.Bat_Status = Bat_Discharging;
				ADC_Value1.ADC_Current = (u16)(Voltage_REF*(temp4_val-temp5_val*3/5)*400)/(temp5_val*ADC_Current_Gain);	//采样电阻R=0.0025R，1/R=400					
			}
			else if(temp4_val<(temp5_val*3/5 - 20))  ////考虑采样误差，需要-20确保有一段电压值表示空闲
			{
				ADC_Value1.Bat_Status = Bat_Charging;
				ADC_Value1.ADC_Current = (u16)(Voltage_REF*(temp5_val*3/5-temp4_val)*400)/(temp5_val*ADC_Current_Gain);	//采样电阻R=0.0025R，1/R=400			
			}
			else
			{
				ADC_Value1.Bat_Status = Bat_Idle;
				ADC_Value1.ADC_Current = 0;
			}
			
			temp1_val = 0;
			temp2_val = 0;
			temp3_val = 0;
			temp4_val = 0;
			temp5_val = 0;
			t = 0;

			
		}		
	}
}












