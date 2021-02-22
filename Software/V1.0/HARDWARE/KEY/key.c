#include "key.h"

#define KEY_UP PEin(0)
#define KEY_DOWN PEin(1)
#define KEY_LEFT PEin(2)
#define KEY_RIGHT PEin(3)
#define KEY_CENTER PEin(4)
#define EC11_KEY PEin(5)


u8 K1,K2,K3,K4,K5,K6;
u8 Time_Set_Mode;
u8 Key_Value,Key_Trig,Key_Cont;

void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 |  GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


void Key_Scan(void)
{
	if(KEY_UP==0)
		K1=0x01;
	else
		K1=0;
		
	if(KEY_DOWN==0)
		K2=0x02;
	else
		K2=0;
		
	if(KEY_LEFT==0)
		K3=0x04;
	else
		K3=0;
	
	if(KEY_RIGHT==0)
		K4=0X08;
	else
		K4=0;	
	
	if(KEY_CENTER==0)
		K5=0x10;
	else
		K5=0;
		
	if(EC11_KEY==0)
		K6=0x20;
	else
		K6=0;
	
	Key_Value = K1 | K2 | K3 | K4 | K5 | K6;
	Key_Trig = Key_Value & (Key_Value ^Key_Cont);
	Key_Cont = Key_Value;
	
}

void Key_Proc(void)
{
	if(Key_Trig & EC11_KEY_PRESS)
	{
		Time_Set_Mode++;
		if(Time_Set_Mode==4)
			Time_Set_Mode=0;
		printf("Time_Set_Mode=%d\n",Time_Set_Mode);
	}
	
}
