#ifndef _IIC_
#define _IIC_
 
#include "stm32f10x.h"
#include "sys.h" 

 
/* ����IIC��SDA��SCL�����˿� */
#define IIC_SCL_IO   GPIO_Pin_6
#define IIC_SDA_IO   GPIO_Pin_7
 
/*  SDA�˿ڶ�̬�ı��������״̬���� */
#define SDA_IN() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X80000000;}    //������������
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0X30000000;}   //�����������
 
/* IIC �������� */
#define IIC_DELAY(time)  delay_us(time)

#define IIC_SCL    PBout(6) 		//SCL
#define IIC_SDA    PBout(7) 		//SDA	 
#define READ_SDA   PBin(7) 	 		//����SDA 

 
/* ����ĺ���ԭ�� */
void IIC_IOInit(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_Wait_Ack(void);
void IIC_NoAck(void);
void IIC_Ack(void);
void IIC_Send_Byte(unsigned char txd);
unsigned char IIC_Read_Byte(unsigned char ack);
 
#endif
















