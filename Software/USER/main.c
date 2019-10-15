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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//	EXTIX_Init();
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	Adc_Init();	
	
	IIC_IOInit();        
	oled_init();

	oled_poweron_display();
	delay_ms(2000);

	if(STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR) == 0xaa55);  //是否通过串口或者蓝牙配置过eeprom
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
				if(Usart_Rx_Len > 8)     //数据帧最小字节数
				{
					if((USART1_RX_BUF[0]==0xaa)&&(USART1_RX_BUF[1]==0x55)&&(USART1_RX_BUF[2]==0x7e))   //帧头
					{
						if(USART1_RX_BUF[3]==0x12)   //设备地址
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


