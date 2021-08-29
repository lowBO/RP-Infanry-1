#ifndef __AUTO_H
#define __AUTO_H

#include "system.h"

#define  OmigaSlope_LEN   5   //�����˲�����
#define  AngleSlope_LEN   5   //�����˲�����
#define  VErrSlope_LEN    1   //�Ӿ������˲�  5

#if (Infantry == 1)
#define  PIT_FIX       0//-78
#define  AutoAim_Ke          0.4
#define  ShootSpeed_15_PRE   10.5
#define  ShootSpeed_18_PRE   9.5
#define  ShootSpeed_30_PRE   8.7

#elif (Infantry == 2)
#define  PIT_FIX     0//-16
#define  AutoAim_Ke          0.4//0.255
#define  ShootSpeed_15_PRE   120//11.2
#define  ShootSpeed_18_PRE   110//10.2
#define  ShootSpeed_30_PRE   100//6

#elif (Infantry == 3)
#define  PIT_FIX       0//-78
#define  AutoAim_Ke          0.4
#define  ShootSpeed_15_PRE   10.5
#define  ShootSpeed_18_PRE   9.5
#define  ShootSpeed_30_PRE   8.7
#endif



typedef enum
{
  YAW = 1,
  PIT = 2,
}AxisType_t;

typedef struct
{
  float Ke,Ko,Ka;
}AutoAim_Param_t;

typedef struct
{
  AxisType_t Axis;
  float abso_Angle;
  float Gim_Err;
  float Vision_Err;
  float Vision_Err_MAX;
  float fix;
}Coordinate_t;


typedef struct
{
  extKalman_t Angle_KF;
  extKalman_t Omiga_KF;
  extKalman_t Accel_KF;
  extKalman_t Out_KF;
}KF_t;


typedef struct
{
  int SinFireAllow_cnt;
  int ConFireAllow_cnt;

}AutoShoot_t;

typedef struct
{
  int start_predict_TIM;
  bool START_PREDICT;
}Predict_t;

typedef struct
{
  float Omiga_queue[OmigaSlope_LEN];
  float Angle_queue[AngleSlope_LEN];
  KF_t KF;                          //������
  AutoAim_Param_t Param;            //����
  Coordinate_t Coordinate;          //��ʼ��������ϵ�ĽǶ�
  float Angle;                      //�Ƕ�  ������ϵ�ĽǶ���ʵ������
  float prev_Angle;
  float Omiga;                      //���ٶ�
  float prev_Omiga;
  float Accel;                      //�Ǽ��ٶ�
  
  float Angle_Out;//�Ƕ����
  float Omiga_Out;//�ٶ����
  float Accel_Out;//���ٶ����

  float Out;//�����
  Predict_t Predict;
  float TargerFix;
  AutoShoot_t AutoShoot;
}AutoAim_Data_t;


typedef struct
{
  bool Init_Over;
  AutoAim_Data_t YAW;
  AutoAim_Data_t PIT;
}AutoAim_t;


extern bool YawAutoAim_Data_Update;
extern bool PitAutoAim_Data_Update;
extern AutoAim_t AutoAim;

void SlopeData_Reset(void);
void AutoAim_ON(void);
void AutoAim_OFF(void);
void AutoAimInit(void);
float GetAngle(Coordinate_t *str);
float AutoAim_Algorithm(AutoAim_Data_t *str);
float Get_SlopeTarget(float M ,float *queue ,uint16_t len);
void Predict_Reset(void);//Ԥ�⸴λ���������ȴ�һ��ʱ�����Ԥ��
void VErrSlope_Reset(void);//�Ӿ������˲�������0

float AutoAimYaw_Ctrl(void);
float AutoAimPit_Ctrl(void);

void Yaw_AutoShoot(void);//�Զ��򵯿���

bool Report_IF_Auto_InitOver(void);//�����Ƿ���������

void AutoAim_Trigger(void);//Ӳ����

void PIT_AUTO_ADD(void);
void PIT_AUTO_DEC(void);
float Report_PIT_AUTO_NUM(void);

#endif

