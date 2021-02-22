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

	u16 Bat_Total_Capacity = 4000;   //Ĭ��4000*0.01AH
	u16 Bat_Total_Voltage = 6720;   //Ĭ��16s=6720*0.01V
	Bat_Status Bat_Old_Status_Typedef;
	Bat_Status Bat_New_Status_Typedef;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	EXTIX_Init();
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	Adc_Init();	
	TIM3_Int_Init(99,7199);  //�ж�ʱ�� (99+1)*(7199+1)/72M     = 10ms
	
	IIC_IOInit();        
	oled_init();

	oled_poweron_display();
	delay_ms(2000);

	Bat_Old_Status_Typedef = Get_OCV_SOC(ADC_Value * ADC_Value_Struct ,u16 Bat_Capacity);
	Bat_New_Status_Typedef = Bat_Old_Status_Typedef;

	if(STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_CHECK) == 0xaa55);  //�Ƿ�ͨ�����ڻ����������ù�eeprom
	{
		FirstSetPara_flag = 0;
		Bat_Total_Capacity = STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_TOTAL_CAPCITY);   //��ȡ���õ�������
		Bat_Total_Voltage = STMFLASH_ReadHalfWord(FLASH_SAVE_ADDR+EEPROM_OFFSET_TOTAL_VOLTAGE);    //��ȡ���õ��ܵ�ѹ		
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
				if(Usart_Rx_Len > 9)     //����֡��С�ֽ���
				{
					if((USART1_RX_BUF[0]==0xaa)&&(USART1_RX_BUF[1]==0x55)&&(USART1_RX_BUF[2]==0x7e))   //֡ͷ
					{
						if(USART1_RX_BUF[3]==0x12)   //�豸��ַ
						{
							for(i=0;i<Usart_Rx_Len-5;i++)   //�ܳ���-֡ͷ3byte-У��2byte
							{
								Usart_SUM = Usart_SUM + USART1_RX_BUF[i+3];
								Usart_XOR = Usart_XOR ^ USART1_RX_BUF[i+3];
							}
							if((USART1_RX_BUF[Usart_Rx_Len-2]==Usart_SUM)&&(USART1_RX_BUF[Usart_Rx_Len-1]==Usart_XOR)  //����У��ok
							{
								STMFLASH_Write(FLASH_SAVE_ADDR+USART1_RX_BUF[4],(u16)(USART1_RX_BUF+6),USART1_RX_BUF[5]);  //����д���յ�����Ч���ݵ�flash									
								FirstSetPara_flag = 0;   //eepromд��ɹ�����´˱�־λ
							}
						}
					}
				}
			}

		}

		else
		{
			Bat_New_Status_Typedef = Get_Realtime_SOC(&ADC_Value1 , &Bat_Old_Status_Typedef , ADC_Sample_Interval , Bat_Total_Capacity);
			if(Bat_New_Status_Typedef != Bat_Old_Status_Typedef)  //���״̬�����仯ʱ��д��eeprom
			{
				STMFLASH_Write(FLASH_SAVE_ADDR+EEPROM_OFFSET_CURRENT_CAPCITY,Bat_New_Status_Typedef.Current_Capacity,1);
			}
			Bat_New_Status_Typedef.Current_Capacity;
			Bat_New_Status_Typedef.SOC;
		}				
//		oled_update_display(test1);

	}	 
} 


