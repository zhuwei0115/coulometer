#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Oled.h"
#include "adc.h"
#include "exit.h"
#include "key.h"
#include "stmflash.h"
#include "timer.h"
#include "soc.h"

#define ADC_Sample_Interval 1   //10ms = 1 * 0.01s

extern ADC_Value ADC_Value1;

int main(void)
 {
	u16 temp;
	u8 i;
	u8 FirstSetPara_flag = 1;
	u8 Usart_Rx_Len;
	u8 Usart_SUM=0, Usart_XOR=0;

	u16 Bat_Total_Capacity = 4000;   //默认4000*0.01AH
	u16 Bat_Total_Voltage = 6720;   //默认16s=6720*0.01V
	Bat_Status Bat_Old_Status_Typedef;
	Bat_Status Bat_New_Status_Typedef;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//	EXTIX_Init();
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	Adc_Init();	
	TIM3_Int_Init(99,7199);  //中断时间 (99+1)*(7199+1)/72M     = 10ms
	
	IIC_IOInit();        
	oled_init();

	oled_poweron_display();
	delay_ms(2000);

	Bat_Old_Status_Typedef = Get_OCV_SOC(ADC_Value * ADC_Value_Struct ,u16 Bat_Capacity);
	Bat_New_Status_Typedef = Bat_Old_Status_Typedef;

	if(STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_CHECK) == 0xaa55);  //是否通过串口或者蓝牙配置过eeprom
	{
		FirstSetPara_flag = 0;
		Bat_Total_Capacity = STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_TOTAL_CAPCITY);   //读取配置的总容量
		Bat_Total_Voltage = STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_TOTAL_VOLTAGE);    //读取配置的总电压		
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
				if(Usart_Rx_Len > 9)     //数据帧最小字节数
				{
					if((USART1_RX_BUF[0]==0xaa)&&(USART1_RX_BUF[1]==0x55)&&(USART1_RX_BUF[2]==0x7e))   //帧头
					{
						if(USART1_RX_BUF[3]==0x12)   //设备地址
						{
							for(i=0;i<Usart_Rx_Len-5;i++)   //总长度-帧头3byte-校验2byte
							{
								Usart_SUM = Usart_SUM + USART1_RX_BUF[i+3];
								Usart_XOR = Usart_XOR ^ USART1_RX_BUF[i+3];
							}
							if((USART1_RX_BUF[Usart_Rx_Len-2]==Usart_SUM)&&(USART1_RX_BUF[Usart_Rx_Len-1]==Usart_XOR)  //数据校验ok
							{
								STMFLASH_Write(FLASH_SAVE_ADDR+USART1_RX_BUF[4],(u16)(USART1_RX_BUF+6),USART1_RX_BUF[5]);  //连续写入收到的有效数据到flash									
								FirstSetPara_flag = 0;   //eeprom写入成功后更新此标志位
							}
						}
					}
				}
			}

		}

		else
		{
			Bat_New_Status_Typedef = Get_Realtime_SOC(&ADC_Value1 , &Bat_Old_Status_Typedef , ADC_Sample_Interval , Bat_Total_Capacity);
			if(Bat_New_Status_Typedef != Bat_Old_Status_Typedef)  //电池状态发生变化时，写入eeprom
			{
				STMFLASH_Write(FLASH_SAVE_ADDR+EEPROM_OFFSET_CURRENT_CAPCITY,Bat_New_Status_Typedef.Current_Capacity,1);
			}
			Bat_New_Status_Typedef.Current_Capacity;
			Bat_New_Status_Typedef.SOC;
		}				
//		oled_update_display(test1);

	}	 
} 


