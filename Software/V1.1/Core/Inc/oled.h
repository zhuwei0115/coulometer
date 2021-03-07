#ifndef __OLED_H_
#define __OLED_H_	

#include "stdint.h"
#include "i2c.h"


//系统状态
typedef struct 
{
	uint8_t RTC_Hours;				//实时时钟 时
	uint8_t RTC_Minutes;			//实时时钟 分
	uint8_t RTC_Seconds;			//实时时钟 秒	
	uint8_t Run_Hours;				//运行时钟 时
	uint8_t Run_Minutes;			//运行时钟 分
	uint8_t Run_Seconds;			//运行时钟 秒
	uint16_t Total_Capicity;			//电池最大总容量
	uint16_t Current_Capicity;		//电池当前容量
	uint8_t SOC;				//电池剩余电量
	uint16_t Voltage;			//电池电压
	uint16_t Current;			//放电或充电电流
	uint16_t Power;			//当前功率
	uint8_t Chrg_or_Dischrg;			//运行时钟 分
}Sys_StausTypeDef;

	
void WriteCmd(void);
//向设备写控制命令
void OLED_WR_CMD(uint8_t cmd);
//向设备写数据
void OLED_WR_DATA(uint8_t data);
//初始化oled屏幕
void OLED_Init(void);
	//清屏
void OLED_Clear(void);
//清行
void OLED_Clearrow(uint8_t i);
//开启OLED显示    
void OLED_Display_On(void);
//关闭OLED显示     
void OLED_Display_Off(void);
//设置光标
void OLED_Set_Pos(uint8_t x, uint8_t y);
//填充图片数据
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_On(void);
	
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode);

 //显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2,uint8_t mode);

//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode);

//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围1～128，y为页的范围1～8*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

//显示制定菜单格式
void OLED_Display_Main(Sys_StausTypeDef Sys_Staus);
#endif
