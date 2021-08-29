#ifndef __SYSTEM_H
#define __SYSTEM_H


typedef enum {
	NONE_ERR,		// ����(�޴���)
	DEV_ID_ERR,		// �豸ID����
	DEV_INIT_ERR,	// �豸��ʼ������
	DEV_DATA_ERR,	// �豸���ݴ���
} dev_errno_t;

typedef enum {
	DEV_ONLINE,     //�豸����
	DEV_OFFLINE,    //�豸����
} dev_work_state_t;


/*��������*/
#define MASTER_DOWN  0
#define MASTER_UP 1
/*Ħ���ֵ������*/
#define Fric_3508   0
#define Fric_Bee    1

#define Infantry_3  1
#define Infantry_4  3
#define Infantry_5  2

//1����3��    2���ϲ��������²���   3����3��

/*�������*/
#define Infantry  Infantry_5

/*��������ѡ��*/ //1������������   0�ӻ���������
#define  Master     MASTER_UP
//Ħ�����Ƿ��ò���ϵͳ��������Ϣ
#define   IF_REFER_CONNECT   1        //����ϵͳ�Ƿ���װ��
//�������Ƿ�������
#define IF_MASTER_DOWN_CONNECT   1    //��ǹ��ʱ��0

#if (Infantry == 1)
  #define Fric_motor  Fric_3508  
  #if (Master == MASTER_UP)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050     0
    #define BMI270      1
    #define BMI_Kp      2.f
  #elif (Master == MASTER_DOWN)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050 0
    #define BMI270  1
    #define BMI_Kp  14.f 
    #define BMI_Kp_2  2.f
  #endif

#elif (Infantry == 2)//2020�경�������²���
  #define Fric_motor  Fric_3508 
  #if (Master == MASTER_UP)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050 0
    #define BMI270  1
    #define BMI_Kp  2.f 
  #elif (Master == MASTER_DOWN)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050 0
    #define BMI270  1
    #define BMI_Kp  14.f 
    #define BMI_Kp_2  2.f
  #endif
  
#elif (Infantry == 3)
  #define Fric_motor  Fric_Bee  
  #if (Master == MASTER_UP)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050     0
    #define BMI270      1
    #define BMI_Kp      2.f
  #elif (Master == MASTER_DOWN)
    #define NEW_CTRL  1 //������
    /*ѡ��imu������*/
    #define MPU6050 0
    #define BMI270  1
    #define BMI_Kp  14.f 
    #define BMI_Kp_2  2.f
  #endif
#endif


#define YES true
#define NO  false

#include <stdio.h>
#include "stdbool.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx.h"
#include "stdint.h"
#include "sys.h" 
#include "usart.h"
#include "string.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "myiic.h" 
#include "mpu6050.h"

#include "bmi270.h"
#include "bmi.h"

#include "can1.h"
#include "can2.h"
#include "led.h"
#include "uart4.h"
#include "uart3.h"
#include "uart1.h"

#include "crc.h"
#include "SinCosTable.h"
#include "kalman.h"
#include "arm_math.h"
#include "referee.h"

#include "iwdg.h"
#include "TIM.h"

/**
 * @brief 
 * @param 
 */
extern volatile uint32_t sysTickUptime;

#define abs(x) ((x)>0? (x):(-(x)))       //����ֵ�궨��

/**
 * @@@@��������
 */
float constrain(float amt,float high,float low);
float anti_constrain(float amt,float high,float low);
float Slope(float M ,float *queue ,uint16_t len);


uint32_t micros(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

uint32_t millis(void);
void systemInit(void);
void Time_Init(void);

void Single_time_cal(void);
bool Judge_IF_NAN(float x );
#endif


