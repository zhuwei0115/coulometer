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
	u8 FirstSetPara_flag = 1;
	u8 Usart_Rx_Len;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	EXTIX_Init();
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	Adc_Init();	
	
	IIC_IOInit();        
	oled_init();

	oled_poweron_display();
	delay_ms(2000);

	if(STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR) == 0xaa55);  //�Ƿ�ͨ�����ڻ����������ù�eeprom
	{
		FirstSetPara_flag = 0;	
	}
	else
	{
		FirstSetPara_flag = 1;
	}
	oled_clear_diplay();
	
	while(1)
	{
		if(FirstSetPara_flag == 1)
		{
			oled_para_unset_display();
			if(USART1_RX_STA&0x8000)
			{
				Usart_Rx_Len = USART1_RX_STA&0x3fff;
				if(Usart_Rx_Len > 8)     //����֡��С�ֽ���
				{
					if((USART1_RX_BUF[0]==0xaa)&&(USART1_RX_BUF[1]==0x55)&&(USART1_RX_BUF[2]==0x7e))   //֡ͷ
					{
						if(USART1_RX_BUF[3]==0x12)   //�豸��ַ
						{


						}
					}
				}
			}

		}
		
		temp = Get_Adc_Average(1,50);
 		temp = (temp*2501*20)/4096;
		printf("CH1=%d\n",temp);

				
		oled_update_display(test1);

	}	 
} 


