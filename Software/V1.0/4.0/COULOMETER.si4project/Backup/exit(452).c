#include "exit.h"

void EXTIX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	EXTIX_GPIO_Init();	//��ʼ��������Ӧioģʽ PE6 PE7
	
    //GPIOA6 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 

}

//�жϷ�����
void EXTI9_5_IRQHandler(void)
{
	delay_ms(1);	//*************����Ҫ*******************
	if(EC11_A==1)	
		{
			if(EC11_B == 1)
			{
				printf("EC11: +1 \r\n");//˳ʱ��
		   	}
			else
			{
				printf("knob: -1 \r\n");//��ʱ��
			}
	  }		
 	 EXTI_ClearITPendingBit(EXTI_Line6);    //���LINE6�ϵ��жϱ�־λ 
}
