#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Oled.h"
#include "adc.h"
#include "exit.h"
#include "key.h"
#include "stmflash.h"




u16 test1[]={12000,1000,12011,999};

int main(void)
 {
	u16 temp;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	EXTIX_Init();
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	oled_initDev();
	Adc_Init();	 
	oled_const_display();	
	while(1)
	{	
//		delay_ms(1000);		
		temp = Get_Adc_Average(1,50);
 		temp = (temp*2501*20)/4096;
		printf("CH1=%d\n",temp);
		test1[2] = temp;
		
		temp = Get_Adc_Average(2,50);
 		temp = (temp*2501*10)/4096;
		printf("CH2=%d\n",temp);
		test1[3] = temp;	
		
		oled_update_display(test1);

//		Key_Scan();
//		Key_Proc();
	}	 
} 


