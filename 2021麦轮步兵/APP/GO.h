#ifndef __GO_H
#define __GO_H

#include "system.h"

#define     TASK_TIM_Unit   1  //FreeRTOSһ���뵥λ,��ʵʱ1ms��λ��1000
#define     FreeRTOS_1S_Unit     1000
/* ����ʱ�� */
#define     SYSTEM_STATE_TASK_TIM    ( 1    *TASK_TIM_Unit)
#define     GIMBAL_TASK_TIM          ( 2    *TASK_TIM_Unit)
#define     CHASSIS_TASK_TIM         ( 2    *TASK_TIM_Unit)
#define     RIFLE_TASK_TIM           ( 1    *TASK_TIM_Unit)
#define     IMU_TASK_TIM             ( 1    *TASK_TIM_Unit)
#define     VISION_TASK_TIM          ( 2    *TASK_TIM_Unit)
#define     MODULE_TASK_TIM          ( 2    *TASK_TIM_Unit)
#define     PID_TASK_TIM             ( 2    *TASK_TIM_Unit)
#define     MASTERLINK_TASK_TIM      ( 1    *TASK_TIM_Unit)
#define     VISION_TRIGGER_TASK_TIM  ( 3    *TASK_TIM_Unit)
#define     ZIGBEE_TASK_TIM          ( 30    *TASK_TIM_Unit)
#define     CUSUI_TASK_TIM           ( 100   *TASK_TIM_Unit)
#define     SONIC_TASK_TIM           ( 5     *TASK_TIM_Unit) 


typedef enum
{
  Defense_SPIN  = 1,   //��������
  Defense_BIG_DODGE ,   //��Ȧ����
  Defense_SMALL_DODGE ,  //����С����
}Defense_Mode_t;

/*ϵͳ�����˶�״̬��־λ*/
typedef struct 
{
  bool IF_SPIN_START;//С���ݿ���
  bool IF_CALIBRATE_OK;//��ʼ����״̬
  bool IF_IMU_InitOver;//IMU��ʼ�����
}CAR_ACT_FLAG_t;

/* ϵͳ����״̬ö�� */
typedef enum 
{
	SYSTEM_RCERR	 = 0,   //ң�ش���ģʽ
	SYSTEM_NORMAL  = 1,   //ϵͳ����ģʽ
	SYSTEM_RCLOST	 = 2,   //ң��ʧ��ģʽ
}System_State_t;

typedef struct
{
  bool CAN1_Normal;
  bool CAN2_Normal;
  bool Remote_Normal;
  bool Referee_Normal;
  bool DUM_Normal;
}User_state_t;

/* ϵͳ����״̬ö�� */
typedef enum
{
  Ctrl_Err = 0,
  RC_CTRL_MODE = 1,     //ң�ؿ���ģʽ
  KEY_CTRL_MODE = 2,    //���̿���ģʽ
  CTRL_MODE_CNT ,

}System_Ctrl_Mode_t;

/* ϵͳPIDģʽö�� */
typedef enum
{
  PID_Err = 0,
	MECH = 1,             //��еģʽ
	GYRO = 2,             //������ģʽ
  PID_MODE_CNT ,
  
}System_Pid_Mode_t;

/* ϵͳ�˶���Ϊö�� */
typedef enum
{
  ACT_Err = 0,
  SYS_ACT_NORMOL = 1,   //��ͨģʽ
  SYS_ACT_BIG_BUFF,     //���ģʽ
  SYS_ACT_SMALL_BUFF,   //С��ģʽ
  SYS_ACT_AUTO_AIM,     //����ģʽ
  SYS_ACT_SPEED,        //����ģʽ
  SYS_ACT_PARK,         //��λģʽ
  ACT_MODE_CNT,
}System_Action_t;

typedef struct
{
  float time[30];//���ڲ���ʱ��ĺ�������ý��
  int cal_time ;
}time_cal_t;//���ڲ���ʱ��

/* ϵͳ��Ϣ�ṹ�� */
typedef struct 
{
  System_State_t state;
  System_Ctrl_Mode_t ctrl_mode;
  System_Action_t action_mode;
  System_Pid_Mode_t pid_mode;
  CAR_ACT_FLAG_t car_actFLAG;
  User_state_t user_state;
  Defense_Mode_t Defense_Mode;
  time_cal_t TimeCal;
}Sys_Info_t;


/* ϵͳ��Ϣ��Ҫ�����ӿڹ���������ģ��鿴 */
extern Sys_Info_t System;

void Loop(void);
void System_Init(void);
void IF_First_GetInto_Normal(void);
System_Action_t Vision_Handler(void);
#endif


