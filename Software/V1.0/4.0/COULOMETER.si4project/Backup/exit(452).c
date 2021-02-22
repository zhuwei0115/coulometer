#include "exit.h"

void EXTIX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


//外部中断初始化函数
void EXTIX_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	EXTIX_GPIO_Init();	//初始化按键对应io模式 PE6 PE7
	
    //GPIOA6 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 

}

//中断服务函数
void EXTI9_5_IRQHandler(void)
{
	delay_ms(1);	//*************很重要*******************
	if(EC11_A==1)	
		{
			if(EC11_B == 1)
			{
				printf("EC11: +1 \r\n");//顺时针
		   	}
			else
			{
				printf("knob: -1 \r\n");//逆时针
			}
	  }		
 	 EXTI_ClearITPendingBit(EXTI_Line6);    //清除LINE6上的中断标志位 
}
