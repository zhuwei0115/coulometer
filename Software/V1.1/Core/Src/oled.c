#include "oled.h"
#include "oledfont.h"
#include "bmp.h"
//几个变量声明
uint8_t **Hzk;


uint8_t CMD_Data[]={
0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F,
					
0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,
					
0xD8, 0x30, 0x8D, 0x14, 0xAF};
void WriteCmd()
{
	uint8_t i = 0;
	for(i=0; i<27; i++)
	{
		
		HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,CMD_Data+i,1,0x100);

	}
}
//向设备写控制命令
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
}
//向设备写数据
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,0x100);
}
//初始化oled屏幕
void OLED_Init(void)
{ 	
	HAL_Delay(200);
	WriteCmd();
}
//清屏size12 size16要清两行，其他函数有类似情况
void OLED_Clear()
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x00); 
		OLED_WR_CMD (0x10); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0);
	} 
}
//清行
void OLED_Clearrow(uint8_t i)
{
	uint8_t n;
	OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x00); 
		OLED_WR_CMD (0x10); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0);
}
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}		   			 
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_WR_CMD(0xb0+y);
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);
	OLED_WR_CMD(x&0x0f);
} 
 
void OLED_On(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);    //设置页地址（0~7）
		OLED_WR_CMD(0x00);      //设置显示位置—列低地址
		OLED_WR_CMD(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OLED_WR_DATA(1); 
	} //更新显示
}

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_CMD(0xb0+m);		//page0-page1
		OLED_WR_CMD(0x00);		//low column start address
		OLED_WR_CMD(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_DATA(fill_Data);
			}
	}
}

unsigned int oled_pow(uint8_t m,uint8_t n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>128-1){x=0;y=y+2;}
		if(mode==1)
		{
			if(Char_Size ==16)
				{
				OLED_Set_Pos(x,y);	
				for(i=0;i<8;i++)
				OLED_WR_DATA(F8x16[c*16+i]);
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
				OLED_WR_DATA(F8x16[c*16+i+8]);
				}
				else {	
					OLED_Set_Pos(x,y);
					for(i=0;i<6;i++)
					OLED_WR_DATA(F6x8[c][i]);	
				}
		}
		else
		{
				if(Char_Size ==16)
				{
				OLED_Set_Pos(x,y);	
				for(i=0;i<8;i++)
				OLED_WR_DATA(~F8x16[c*16+i]);
				OLED_Set_Pos(x,y+1);
				for(i=0;i<8;i++)
				OLED_WR_DATA(~F8x16[c*16+i+8]);
				}
				else {	
					OLED_Set_Pos(x,y);
					for(i=0;i<6;i++)
					OLED_WR_DATA(~F6x8[c][i]);	
				}
		}
}
 //显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2,uint8_t mode)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2,mode);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2,mode); 
	}
} 
//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size,mode);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_DATA(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_DATA(Hzk[2*no+1][t]);
				adder+=1;
      }					
}


/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围1～128，y为页的范围1～8*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_DATA(BMP[j++]);	    	
	    }
	}
} 

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围1～128，y为页的范围1～8*****************/
void OLED_Display_Main(Sys_StausTypeDef Sys_Staus)
{
/*         第一行              */
	OLED_ShowChar(0,0,' ',16,0);
	OLED_ShowNum(8,0,Sys_Staus.RTC_Hours,2,16,0);
	OLED_ShowChar(24,0,':',16,0);
	OLED_ShowNum(32,0,Sys_Staus.RTC_Minutes,2,16,0);
	OLED_ShowChar(48,0,':',16,0);
	OLED_ShowNum(56,0,Sys_Staus.RTC_Seconds,2,16,0);
	OLED_ShowChar(72,0,' ',16,0);
	OLED_ShowNum(80,0,Sys_Staus.Total_Capicity/10,2,16,0);
	OLED_ShowChar(96,0,'.',16,0);
	OLED_ShowNum(104,0,Sys_Staus.Total_Capicity%10,1,16,0);
	OLED_ShowChar(112,0,'A',16,0);
	OLED_ShowChar(120,0,'H',16,0);
	
/*         第二行电压部分              */
	OLED_ShowChar(0,2,'U',16,1);
	OLED_ShowChar(8,2,'=',16,1);
	OLED_ShowChar(16,2,' ',16,1);
	OLED_ShowNum(24,2,Sys_Staus.Voltage/10,2,16,1);
	OLED_ShowChar(40,2,'.',16,1);
	OLED_ShowNum(48,2,Sys_Staus.Voltage%10,1,16,1);
	OLED_ShowChar(56,2,' ',16,1);
	OLED_ShowChar(64,2,'V',16,1);
	
/*         第二行SOC部分              */	
	OLED_ShowNum(96,2,Sys_Staus.SOC,2,16,1);
	OLED_ShowChar(120,2,'%',16,1);
	
/*         第三行电流部分              */
	OLED_ShowChar(0,4,'I',16,1);
	OLED_ShowChar(8,4,'=',16,1);
	if(Sys_Staus.Chrg_or_Dischrg == 1)		
		OLED_ShowChar(16,4,' ',16,1);
	else
		OLED_ShowChar(16,4,'-',16,1);
	OLED_ShowNum(24,4,Sys_Staus.Current/10,2,16,1);
	OLED_ShowChar(40,4,'.',16,1);
	OLED_ShowNum(48,4,Sys_Staus.Current%10,1,16,1);
	OLED_ShowChar(56,4,' ',16,1);
	OLED_ShowChar(64,4,'A',16,1);
	
/*         第四行功率部分              */
	OLED_ShowChar(0,6,'P',16,1);
	OLED_ShowChar(8,6,'=',16,1);
	OLED_ShowChar(16,6,' ',16,1);
	OLED_ShowNum(24,6,Sys_Staus.Power,4,16,1);
	OLED_ShowChar(56,6,' ',16,1);
	OLED_ShowChar(64,6,'W',16,1);
	
/*         第三四行电量图标部分              */
	OLED_DrawBMP(80, 4,128, 8,BMP4);
	
//	OLED_ShowNum(8,0,Sys_Staus.RTC_Hours,2,16,0);
//	Sys_StausTypeDef Sys_Staus1={0};
//	Sys_Staus1.RTC_Hours = 0;
//	Sys_Staus1->;
//	Sys_Staus1.RTC_Hours = 23;
//	Sys_Staus1.RTC_Minutes = 59;
//	Sys_Staus1.RTC_Seconds	= 59;
////	Sys_Staus1.Run_Minutes = 0;
////	Sys_Staus1.Run_Hours = 10;
////	Sys_Staus1.Run_Minutes = 00; 	
//	Sys_Staus1.RTC_Seconds	= 59;
////初始化命令	
//	OLED_ShowChar(uint8_t x,uint8_t y,,16)；
} 