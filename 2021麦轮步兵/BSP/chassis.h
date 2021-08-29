#ifndef __CHASSIS_H
#define __CHASSIS_H


#include "Driver.h"

#define CHAS_Buffer_Urgent  18 //10 ����Ϊ10��ʱ��ò�ƻᳬ����
#define CHAS_PARK_FB_k  2.7
#define CHAS_PARK_LR_k  2.7
#define CHAS_PARK_Z_k   1



#if (Infantry == 1)
#define   SPIN_SPEED   3000
#define   SPIN_SPEED_50W  3000//-3300
#define   SPIN_SPEED_60W  3300//-3450w
#define   SPIN_SPEED_80W  3600//-3600
#define   SPIN_SPEED_100W  3900//-4000
#define   SPIN_SPEED_120W  4200//-4500
#define   SPIN_SPEED_SUPER 6500//-5000

#define   SPIN_FBk_50W   4+1
#define   SPIN_FBk_60W   4.5+1
#define   SPIN_FBk_80W   5.5+1
#define   SPIN_FBk_100W  6.5+1
#define   SPIN_FBk_120W  7.5+1
#define   SPIN_FBk_SUPER  12
#define   SPIN_LRk_50W   4
#define   SPIN_LRk_60W   4.5
#define   SPIN_LRk_80W   5.5
#define   SPIN_LRk_100W  6.5
#define   SPIN_LRk_120W  7.5
#define   SPIN_LRk_SUPER  12

#define   RC_CHAS_GYRO_FB_k   11
#define   RC_CHAS_GYRO_LR_k   11
#define   RC_CHAS_GYRO_Z_k    1
#define   RC_CHAS_MECH_FB_k   5
#define   RC_CHAS_MECH_LR_k   5
#define   RC_CHAS_MECH_Z_k    8

#define   KEY_CHAS_GYRO_FB_k   11
#define   KEY_CHAS_GYRO_LR_k   11
#define   KEY_CHAS_GYRO_Z_k    1
#define   KEY_CHAS_MECH_FB_k   5
#define   KEY_CHAS_MECH_LR_k   5
#define   KEY_CHAS_MECH_Z_k    -45

#define   SUP_CHAS_GYRO_FB_k   13.2
#define   SUP_CHAS_GYRO_LR_k   13.2
#define   SUP_CHAS_GYRO_Z_k    1.2 //1
#define   SUP_CHAS_MECH_FB_k   13.2
#define   SUP_CHAS_MECH_LR_k   13.2//4
#define   SUP_CHAS_MECH_Z_k    -45



#elif (Infantry == 2)
#define   SPIN_SPEED   3000
#define   SPIN_SPEED_50W  3000//-3300
#define   SPIN_SPEED_60W  3300//-3450w
#define   SPIN_SPEED_80W  3600//-3600
#define   SPIN_SPEED_100W  3900//-4000
#define   SPIN_SPEED_120W  4200//-4500
#define   SPIN_SPEED_SUPER 6500//-5000

#define   SPIN_FBk_50W   4+1
#define   SPIN_FBk_60W   4.5+1
#define   SPIN_FBk_80W   5.5+1
#define   SPIN_FBk_100W  6.5+1
#define   SPIN_FBk_120W  7.5+1
#define   SPIN_FBk_SUPER  12
#define   SPIN_LRk_50W   4
#define   SPIN_LRk_60W   4.5
#define   SPIN_LRk_80W   5.5
#define   SPIN_LRk_100W  6.5
#define   SPIN_LRk_120W  7.5
#define   SPIN_LRk_SUPER  12

#define   RC_CHAS_GYRO_FB_k   11
#define   RC_CHAS_GYRO_LR_k   11
#define   RC_CHAS_GYRO_Z_k    1
#define   RC_CHAS_MECH_FB_k   5
#define   RC_CHAS_MECH_LR_k   5
#define   RC_CHAS_MECH_Z_k    8

#define   KEY_CHAS_GYRO_FB_k   11
#define   KEY_CHAS_GYRO_LR_k   11
#define   KEY_CHAS_GYRO_Z_k    1
#define   KEY_CHAS_MECH_FB_k   5
#define   KEY_CHAS_MECH_LR_k   5
#define   KEY_CHAS_MECH_Z_k    -70

#define   SUP_CHAS_GYRO_FB_k   13.2
#define   SUP_CHAS_GYRO_LR_k   13.2
#define   SUP_CHAS_GYRO_Z_k    1.2 //1
#define   SUP_CHAS_MECH_FB_k   13.2
#define   SUP_CHAS_MECH_LR_k   13.2//4
#define   SUP_CHAS_MECH_Z_k    -70
//#define   SPIN_SPEED   3000
//#define   SPIN_SPEED_50W  2800
//#define   SPIN_SPEED_60W  3050
//#define   SPIN_SPEED_80W  3450
//#define   SPIN_SPEED_100W  3950
//#define   SPIN_SPEED_120W  4200
//#define   SPIN_SPEED_SUPER 5000

//#define   SPIN_FBk_50W   3
//#define   SPIN_FBk_60W   3
//#define   SPIN_FBk_80W   3
//#define   SPIN_FBk_100W  3
//#define   SPIN_FBk_120W  3
//#define   SPIN_FBk_SUPER  3
//#define   SPIN_LRk_50W   3-1
//#define   SPIN_LRk_60W   3-1
//#define   SPIN_LRk_80W   3-1
//#define   SPIN_LRk_100W  3-1
//#define   SPIN_LRk_120W  3-1
//#define   SPIN_LRk_SUPER  3-1


//#define   RC_CHAS_GYRO_FB_k   13.2
//#define   RC_CHAS_GYRO_LR_k   13.2
//#define   RC_CHAS_GYRO_Z_k    1
//#define   RC_CHAS_MECH_FB_k   13.2
//#define   RC_CHAS_MECH_LR_k   13.2//4
//#define   RC_CHAS_MECH_Z_k    8
//#define   KEY_CHAS_GYRO_FB_k   13.2
//#define   KEY_CHAS_GYRO_LR_k   13.2
//#define   KEY_CHAS_GYRO_Z_k    1
//#define   KEY_CHAS_MECH_FB_k   14.7
//#define   KEY_CHAS_MECH_LR_k   14.7
//#define   KEY_CHAS_MECH_Z_k    -45

#elif (Infantry == 3)
#define   SPIN_SPEED   3000
#define   SPIN_SPEED_50W  3000//-3300
#define   SPIN_SPEED_60W  3300//-3450w
#define   SPIN_SPEED_80W  3600//-3600
#define   SPIN_SPEED_100W  3900//-4000
#define   SPIN_SPEED_120W  4200//-4500
#define   SPIN_SPEED_SUPER 6500//-5000

#define   SPIN_FBk_50W   4+1
#define   SPIN_FBk_60W   4.5+1
#define   SPIN_FBk_80W   5.5+1
#define   SPIN_FBk_100W  6.5+1
#define   SPIN_FBk_120W  7.5+1
#define   SPIN_FBk_SUPER  12
#define   SPIN_LRk_50W   4
#define   SPIN_LRk_60W   4.5
#define   SPIN_LRk_80W   5.5
#define   SPIN_LRk_100W  6.5
#define   SPIN_LRk_120W  7.5
#define   SPIN_LRk_SUPER  12

#define   RC_CHAS_GYRO_FB_k   9
#define   RC_CHAS_GYRO_LR_k   9
#define   RC_CHAS_GYRO_Z_k    1
#define   RC_CHAS_MECH_FB_k   5
#define   RC_CHAS_MECH_LR_k   5
#define   RC_CHAS_MECH_Z_k    8

#define   KEY_CHAS_GYRO_FB_k   7
#define   KEY_CHAS_GYRO_LR_k   7
#define   KEY_CHAS_GYRO_Z_k    1
#define   KEY_CHAS_MECH_FB_k   5
#define   KEY_CHAS_MECH_LR_k   5
#define   KEY_CHAS_MECH_Z_k    -45

#define   SUP_CHAS_GYRO_FB_k   13.2
#define   SUP_CHAS_GYRO_LR_k   13.2
#define   SUP_CHAS_GYRO_Z_k    1.2 //1
#define   SUP_CHAS_MECH_FB_k   13.2
#define   SUP_CHAS_MECH_LR_k   13.2//4
#define   SUP_CHAS_MECH_Z_k    -45


#endif


#define   CHAS_Z_SPEED_MAX  11000  //11*660 = 7260 ��7500
#define   CHAS_MOTOR_SPEED_MAX  13000//10000

//��������
#define   ANCESTRAL_ALGORITHM  YES //�Ƿ����洫�㷨
#define   CHAS_TOTAL_OUTPUT_MAX   50000    //������������ 50000
#define   CHAS_LIMIT_POWERBUFFER  60

//ÿ�����ӵ����ת��
 //֮ǰ��6000   �����ڷ����ٶȱ��������ֵ����������һ�������ֵ����Ϊ�й�������
#define Car_SPEED   CHAS_MOTOR_SPEED_MAX 


/* ���̵�������±� */
typedef enum 
{
  CHAS_LF = 0,
  CHAS_RF = 1,
  CHAS_LB = 2,
  CHAS_RB = 3,
  CHAS_MOTOR_CNT = 4,
}CHAS_Motor_cnt_t;

typedef struct 
{
  extKalman_t KF_GYRO_Angle;
  PID_Info_t GYRO_Ctrl;  
}CHAS_GYRO_t;//������ģʽ���̸�����̨�����ݽṹ��

typedef struct 
{
  float FB_Speed,LR_Speed,Z_Speed ;
  float FB_Speed_k,LR_Speed_k,Z_Speed_k; //ң��->�ٶ� �仯�ķ��ȵ�������
  float Motor_SpeedTarget[CHAS_MOTOR_CNT];
  float Slow_Inc;
  CHAS_GYRO_t GYRO_Move;
}CHAS_Move_t;

typedef struct 
{
  Motor_Data_t motor_data;
  PID_Info_t PID;
}CHAS_Motor_t;

typedef struct
{
  float Limit_k;
  float Real_PowerBuffer;
  float Max_PowerBuffer;
  float CHAS_TotalOutput;
  float CHAS_LimitOutput;
}CHAS_PowerLimit_t;

typedef enum
{
  HEAD = 1,
  TAIL = -1,
}Dir_t;

typedef struct
{
  Dir_t mode;
  float num;
}CHAS_Dir_t;



/* ������Ϣ�ṹ�� */
typedef struct
{
  System_Ctrl_Mode_t ctrl_mode;
  System_Pid_Mode_t pid_mode;
  System_Action_t action_mode;  
  PID_type_t PID_type;
  
  Motor_Info_t motor_info;
  CHAS_Motor_t CHAS_Motor[CHAS_MOTOR_CNT];
  
  CHAS_Move_t RC_Move;
  CHAS_Move_t Key_Move;
  CHAS_Move_t SPIN_Move;
  float Speed_MAX;
  bool IF_NAN;
  bool IF_SPIN_START;//С���ݿ���
  bool IF_SPIN_CLOSING;//С�����Ƿ����ڹر�
  CHAS_PowerLimit_t CHAS_PowerLimit;
  Defense_Mode_t Defense_Mode;
  CHAS_Dir_t Dir;
}CHAS_Info_t;



extern CHAS_Info_t Chassis;
extern float power_limit_K;

void CHAS_SetPID_type(void);
void CHAS_SetPID(void);
void CHAS_PID_Switch(PID_Info_t *str);
void CHAS_Dir_HEAD(void);
void CHAS_Dir_TAIL(void);
void CHAS_Dir_Switch(void);
bool Judge_IF_CHAS_HeadF(void);
void CHASSIS_Ctrl(void);
void CHAS_GET_Info(void);
void CHAS_GET_PID_Type(PID_Info_t *str );
void CHAS_KET_Ctrl(void);
void CHAS_RC_Ctrl(void);
void CHAS_Remote_Ctrl(void);
void CHAS_Keyboard_Ctrl(void);

void CHAS_Reset(void);
void CHAS_Stop(void);
void CHAS_SetEmpty(PID_Info_t *str);

void CHAS_SetChasSpeed(CHAS_Move_t *str);
void CHAS_SetMotorSpeed(CHAS_Move_t *str);
void CHAS_DataSync(Motor_Data_t *str);
float CHAS_GetOutput(CHAS_Motor_t *str);
void CHAS_Output(void);
void CHAS_Handler(CHAS_Move_t *str);

float CHAS_Get_AngleErr(Motor_Data_t *str);
float CHAS_Get_SpeedErr(Motor_Data_t *str);
float CHAS_Get_Zerror(CHAS_Move_t *str);
float CHAS_Get_Z_Speed(CHAS_Move_t *MOVE);
  
//��������
void power_limit(void);

//С����
float SPIN_GetSpeed_LR(float Angle , float FB_ctrl , float LR_ctrl);
float SPIN_GetSpeed_FB(float Angle , float FB_ctrl , float LR_ctrl);
void CHAS_SPIN(void);
bool CHAS_SPIN_Report(void);
void SPIN_ON(void);
void SPIN_OFF(void);
void SPIN_Reset(void);
void SPIN_KEY_Switch(void);
void SPIN_CLOSING_Judge(void);
bool Report_IF_SPIN_CLOSING(void);
void SPIN_Defense_Mode_Switch(void);
void SPIN_Defense_Mode_Reset(void);
//zigbee�� �����������  
float CHAS_Report_Output_LF(void);
float CHAS_Report_Output_RF(void);
float CHAS_Report_Output_LB(void);
float CHAS_Report_Output_RB(void);
//zigbee�� �����ٶ�
float CHAS_Report_Speed_LF(void);
float CHAS_Report_Speed_RF(void);
float CHAS_Report_Speed_LB(void);
float CHAS_Report_Speed_RB(void);
//zigbee�� ������������ٶ�
//void SPIN_Speed_up20(void);
//void SPIN_Speed_down20(void);
//float Get_test_spin_speed(void);
uint8_t Report_SuperCap_cmd(void);
void SuperCap_KEY_ON(void);
void SuperCap_KEY_OFF(void);
void SuperCap_Urgent_ON(void);//�������翪
void SuperCap_Urgent_OFF(void);//���������
void SuperCap_Emergency(float Buffer);//�������繦�ܺ���
void SuperCap_CHAS_K_change_GYRO(void);
void SuperCap_CHAS_K_change_MECH(void);
//�ϱ�NAN
bool CHAS_Report_IF_NAN(void);

#endif

