#ifndef __MY_IMU_H
#define __MY_IMU_H

#include "system.h"
#define CALCULATE_LENGTH 3 //���㾲���õ����鳤�ȣ����ɵ���
#define JUDGE_ERR   0      //�����жϵ�������Χ��ԽСԽ��ϸ
#define SPEED_FILTER_LEN 3 //�ٶ��˲�����

#define prev_Imu_Yaw_LEN   20//��¼������ǰn֡����
#define prev_Imu_Pit_LEN   20//��¼������ǰn֡����

///* IMU����̨̧ͷ��ͷ�߽� */ /*MAX��MINָ����̧ͷ�͵�ͷ����˼*/
//#if (Infantry == 1)
//#define   PIT_IMU_MAX_ANGLE   154 //PIT��ͷ���ֵ
//#define   PIT_IMU_MIN_ANGLE   192 //PIŢͷ���ֵ

//#elif (Infantry == 2)
//#define   PIT_IMU_MAX_ANGLE   -20 //PIT��ͷ���ֵ
//#define   PIT_IMU_MIN_ANGLE   15 //PIŢͷ���ֵ

//#elif (Infantry == 3)
//#endif

typedef struct 
{ 
  bool IF_GET_StaticErr;    //��ȡ����ɹ���־
  float YAW_Err_Init;       //������YAW����
  float PIT_Err_Init;       //������PIT����
  short gyrox,gyroy,gyroz;  //�����Ƿ������ٶ�
  float IMU_YAW_Speed;      //IMU YAW �ٶ�
  float IMU_YAW_Angle;      //IMU YAW �Ƕ�
  float IMU_PIT_Speed;      //IMU PIT �ٶ�
  float IMU_PIT_Angle;      //IMU PIT �Ƕ�
  float prev_Imu_Yaw[prev_Imu_Yaw_LEN];
  float prev_Imu_Pit[prev_Imu_Pit_LEN];
}IMU_Info_t;

void IMU_Init(void);
void IMU_Ctrl(void);

bool Static_Error_Calculate(void);
void Speed_Filter(short gx,short gy,short gz);//�ٶ��˲�
void IMU_get_angle_to_use(void);          //��ȡ�����Ǿ��ԽǶ�

float Report_prev_imu_yaw_angle(int i);
float Report_prev_imu_pit_angle(int i);
float Report_YawSpeed(void);
float Report_YawAngle(void);
float Report_PitSpeed(void);
float Report_PitAngle(void);
bool IF_IMU_InitOver(void);


void Gimbal_Measure_Data(IMU_Info_t *str);

#endif



