#include "myiic.h"
#include "delay.h"
#include "sys.h" 
/*********************************************************************
**  STM32ģ��IICͨ��
**  �ļ����룺 GBK2312
**********************************************************************/
 
 
/*****************************
**  ��ʼ��IIC��IO��
**
******************************/
void IIC_IOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );  //ʹ��IO��ʱ��
     
    GPIO_InitStructure.GPIO_Pin = IIC_SCL_IO | IIC_SDA_IO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;       //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
     
    GPIO_SetBits(GPIOB,IIC_SCL_IO | IIC_SDA_IO);            //��λSDA��SCL   
}
 
/*****************************
**  ��ʼ�ź�
**
******************************/
void IIC_Start(void)
{
    SDA_OUT(); //sda �����
    IIC_SDA = 1;
    IIC_SCL = 1;
    IIC_DELAY(4);
     
    IIC_SDA=0;//��ʱ����Ϊ��ʱ��SDA��������ʼ�źŲ���Ч
    IIC_DELAY(4);
     
    IIC_SCL=0;//ǯס I2C ���ߣ�׼�����ͻ��������
}
 
/*****************************
**  ֹͣ�ź�
**
******************************/
void IIC_Stop(void)
{
    SDA_OUT();//sda �����
    IIC_SCL=0;
    IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    IIC_DELAY(4);
     
    IIC_SCL=1;
    IIC_DELAY(1);
    IIC_SDA=1;//���� I2C ���߽����ź�
    IIC_DELAY(4);
}
 
/*****************************
**  �ȴ�Ӧ���ź�
**  ����ֵ�� 1-����Ӧ��ʧ�ܣ� 0-Ϊ���ճɹ�
******************************/
unsigned char IIC_Wait_Ack(void)
{
    unsigned char ucErrTime=0;
    SDA_IN(); //SDA ����Ϊ����
    IIC_SDA=1;IIC_DELAY(1);
    IIC_SCL=1;IIC_DELAY(1);
     
    while(READ_SDA)       //�ж�SDA���Ƿ��е͵�ƽ����
    {
        ucErrTime++;
        if(ucErrTime>250)   //�����һ��ʱ����û�н��յ�Ӧ���źţ�����ֹͣ�ź�
        {
            IIC_Stop();
            return 1;
        }
    }
     
    IIC_SCL=0;//ʱ����� 0
    return 0;
}
 
/*****************************
**  ����Ӧ���ź�
** 
******************************/
void IIC_Ack(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;
    IIC_DELAY(2);   //���ݸı���Ч
     
    IIC_SCL=1;
    IIC_DELAY(2);
    IIC_SCL=0;
}
 
/*****************************
**  ������Ӧ���ź�
** 
******************************/
void IIC_NoAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;
    IIC_DELAY(2);
     
    IIC_SCL=1;
    IIC_DELAY(2);
    IIC_SCL=0;
}
 
/*****************************
**  ����һ���ֽڵ�����
** 
******************************/
void IIC_Send_Byte(unsigned char txd)
{
    unsigned char t;
    SDA_OUT();
     
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ��䣬ʱSDA�ϵ����ݸı���Ч
    for(t=0;t<8;t++)
    {
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        IIC_DELAY(2); //�� TEA5767 ��������ʱ���Ǳ����
         
        IIC_SCL=1;
        IIC_DELAY(2); //��������һ��ʱ��
         
        IIC_SCL=0;
        IIC_DELAY(2);
    }
}
 
/*****************************
**  ��һ���ֽڵ�����
**  ��ʽ������ack=1������ACK�� ack=0������NACK
******************************/
unsigned char IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA ����Ϊ����
     
    for(i=0;i<8;i++ )
    {
        IIC_SCL=0;
        IIC_DELAY(2);
        IIC_SCL=1;
        receive<<=1;
         
        if(READ_SDA)receive++;
        IIC_DELAY(1);
    }
    if (!ack)
        IIC_NoAck();//���� nACK
    else
        IIC_Ack(); //���� ACK
     
    return receive;
}

