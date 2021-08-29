#ifndef __MYIIC_H
#define __MYIIC_H
//#include "sys.h" 
#include "system.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#include "my_imu.h"

#if MPU6050
#define GPIO_Port   GPIOB
#define GPIO_PIN1   GPIO_Pin_6
#define GPIO_PIN2   GPIO_Pin_7
#define GPIO_Periph   RCC_AHB1Periph_GPIOB
#define MPU_ADDR				0X68

//IO��������
#define SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} //PB9���ģʽ
//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 
#endif


#if BMI270

#define GPIO_Port   GPIOB
#define GPIO_PIN1   GPIO_Pin_13
#define GPIO_PIN2   GPIO_Pin_15
#define GPIO_Periph   RCC_AHB1Periph_GPIOB
#define MPU_ADDR				0X69

//IO�ڷ�������
#define SDA_IN() 	{GPIOB->MODER&=~((uint32_t)3<<(15*2));GPIOB->MODER|=(uint32_t)0<<(15*2);}	//PB7����ģʽ
#define SDA_OUT() 	{GPIOB->MODER&=~((uint32_t)3<<(15*2));GPIOB->MODER|=(uint32_t)1<<(15*2);}	//PB7����ģʽ
//IO�ڲ�������
#define IIC_SCL 	PBout(13)
#define IIC_SDA 	PBout(15)
#define READ_SDA 	PBin(15)		

#endif



//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
uint8_t MPU_Read_Byte(uint8_t reg);
uint8_t MPU_Write_Byte(uint8_t reg,uint8_t data);

#endif














