#ifndef __RIFLE_H
#define __RIFLE_H


#include "Driver.h"

/*����һ��ĽǶ�*/
#define SINGLE_ANGLE   -36859.5
/*�������̵�ת��*/
#define CONTIN_FREQ_20  20
#define CONTIN_FREQ_15  15
#define CONTIN_FREQ_12  12
#define CONTIN_FREQ_10  10  //��Ƶ  ����/�룩
#define CONTIN_FREQ_05   5
#define CONTIN_FREQ_03   3

#define MOTOR_1RPS_SPEED     2160          //60*36һ��תһȦ1RPM*60 *36(1��36���ٱ�)= 1RPS
#define GRID_NUM    8    //������
#define MOTOR_1GPS_SPEED   (MOTOR_1RPS_SPEED/GRID_NUM)//һ��תһ��GPS: Grid Per Second 

#define MOTOR_SPEED_20  (CONTIN_FREQ_20 * MOTOR_1GPS_SPEED)   //�̶���Ƶ���������ת��
#define MOTOR_SPEED_15  (CONTIN_FREQ_15 * MOTOR_1GPS_SPEED)   //�̶���Ƶ���������ת��
#define MOTOR_SPEED_10  (CONTIN_FREQ_10 * MOTOR_1GPS_SPEED)   //�̶���Ƶ���������ת��
#define MOTOR_SPEED_05  (CONTIN_FREQ_05 * MOTOR_1GPS_SPEED)   //�̶���Ƶ���������ת��
#define MOTOR_SPEED_03  (CONTIN_FREQ_03 * MOTOR_1GPS_SPEED)   //�̶���Ƶ���������ת��

/* �жϷ�����ɵĽǶ�������̶� */
#define Judge_AngleErr  700
#define Judge_SinBlock_TIM 500  //1S  ��ⵥ������
#define Judge_ConBlock_TIM 320   //0.5S�����������

/*��ת���*/
#define Judge_Stuck_SpeedMAX  520
#define Judge_Stuck_OutputMIN  800

/*Ħ���ֿ�����ʱ*/
#define FricNormal_Delay    700

/*���Ѳ����Ĵ�������*/
#define ShootWarningNum     140

/*���ѿ�����������Ŀ�����*/
#define Block_WarningNUM    2

/*������������*/
#define SingleHeatLimitErr    20
#define ContinHeatLimitErr    20

/*������������*/

/* ���̵�������±� */
typedef enum 
{
  RIFLE = 0,
  RIFLE_MOTOR_CNT = 1,
}RIFLE_Motor_cnt_t;

typedef enum
{
  NO_Block = 0,
  SinBlock ,
  ConBlock ,
}Block_type_t;

typedef struct
{
  bool IF_FireBlock ; //ͨ�������־λ�ֿ�����
  bool BlockReact_Over;
  int cnt;
  Block_type_t type;
}BlockState_t;

typedef struct
{
  Motor_Info_t motor_info;
  Motor_Data_t motor_data;
  PID_Info_t PID;
  BlockState_t BlockState;
}RIFLE_Motor_t;

typedef struct
{
  bool IF_SinFire_Request; //��������λ
  bool IF_ConFire_Request; //��������λ
  bool IF_SingleFire_OVER; //����������־λ
  bool IF_SinFire_Block;
  bool IF_ConFire_Block;
  bool IF_Block;
  bool IF_Stuck;
}Flag_t;

/* ������Ϣ�ṹ�� */
typedef struct
{
  System_Ctrl_Mode_t ctrl_mode;
  System_Pid_Mode_t pid_mode;
  System_Action_t action_mode;
  PID_type_t PID_type;  
  RIFLE_Motor_t Motor[RIFLE_MOTOR_CNT];
  Flag_t flag;
  float SingleAngle;//�����Ƕ�
  float ContinuFreq;//��Ƶ
}RIFLE_Info_t;

extern RIFLE_Info_t Rifle;

void RIFLE_Ctrl(void);
void RIFLE_GET_Info(void);
void RIFLE_SetPID(void);
void RIFLE_PID_Switch(PID_Info_t *str );
void RIFLE_GET_PID_Type(PID_Info_t *str);
void RIFLE_RC_Ctrl(void);
void RIFLE_KET_Ctrl(void);
void RIFLE_MECH_RC_Ctrl(void);
void RIFLE_GYRO_RC_Ctrl(void);
void Keyboard_Ctrl(void);

void FlagUpdate(void);
void SingleFire(void);
void ContinFire(void);
void RIFLE_MotorAngleInit(void);
void RIFLE_Output(void);

void RIFLE_Reset(void);
void FlagReset(void);

bool Judge_IF_SingleFire_OVER(void);
bool Judge_FireBlock(void);

void RIFLE_Stop(void);
void RIFLE_Handler(void);

void SingleFireRequest(void);
bool SinFireRequest_Report(void);
bool ConFireRequest_Report(void);

void ContinFire_ON(void);
void ContinFire_OFF(void);

void BlockReact(void);
bool Judge_SinFireBlock(void);
bool Judge_ConFireBlock(void);
void BlockState_Reset(void);
bool IF_FireBlock(void);
bool Stuck_Judge(void);

void Single_Forward(void);
void Single_Forward_HALF(void);
void Single_Reverse(void);
void Single_Reverse_HALF(void);

void ContinFreq_20(void);
void ContinFreq_15(void);
void ContinFreq_12(void);
void ContinFreq_10(void);
void ContinFreq_05(void);
void ContinFreq_03(void);
void Judge_IF_Change_HeatLimit(void);

//��������
bool Judge_IF_SingleHeat_ShootAllow(void);
bool Judge_IF_Heat_ShootAllow(void);//����һ����������
bool Report_IF_ShootHeatLimit(void);//����һ����������

void Brust_ON(void);
void Brust_OFF(void);

void Check_IF_FricSpeed_Normal(void);
bool Report_IF_FricSpeed_Normal(void);

void Reset_Block_num(void);
bool Judge_IF_SinBlocks(void);
bool Report_IF_SinBlocks(void);

void Reset_BulletWarning(void);
bool Judge_IF_BulletWarning(void);
bool Report_IF_BulletWarning(void);


#endif

