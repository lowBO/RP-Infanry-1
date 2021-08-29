#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Driver.h"

#if (Infantry == 1)
  #define   YAW_MOTOR_MID_ANGLE   780  //电机角度中间值
  #define   PIT_MOTOR_MID_ANGLE   8133 //电机角度中间值
  #define   PIT_MOTOR_MAX_ANGLE   (570 + 8192) //PIT低头最大值
  #define   PIT_MOTOR_MIN_ANGLE   7600 //PIT抬头最大值
  
  #define   PIT_IMU_MID_ANGLE     4128 //IMU角度中间值
  #define   PIT_IMU_MAX_ANGLE     4563 //PIT低头最大值
  #define   PIT_IMU_MIN_ANGLE     3624 //PIT抬头最大值

  #define   PIT_SENTRY            7891

#elif (Infantry == 2)
  #define   YAW_MOTOR_MID_ANGLE   3536  //电机角度中间值
  #define   PIT_MOTOR_MID_ANGLE   1365 //电机角度中间值
  #define   PIT_MOTOR_MAX_ANGLE   1943 //PIT低头最大值
  #define   PIT_MOTOR_MIN_ANGLE   804 //PIT抬头最大值

  #define   PIT_IMU_MID_ANGLE     4128 //IMU角度中间值
  #define   PIT_IMU_MAX_ANGLE     4563 //PIT低头最大值
  #define   PIT_IMU_MIN_ANGLE     3624 //PIT抬头最大值

  #define   PIT_SENTRY            953

#elif (Infantry == 3)
  #define   YAW_MOTOR_MID_ANGLE   813  //电机角度中间值
  #define   PIT_MOTOR_MID_ANGLE   5555 //电机角度中间值
  #define   PIT_MOTOR_MAX_ANGLE   6234 //PIT低头最大值
  #define   PIT_MOTOR_MIN_ANGLE   4639 //PIT抬头最大值
  
  #define   PIT_IMU_MID_ANGLE     4128 //IMU角度中间值
  #define   PIT_IMU_MAX_ANGLE     4563 //PIT低头最大值
  #define   PIT_IMU_MIN_ANGLE     3624 //PIT抬头最大值

  #define   PIT_SENTRY            4900

#endif


void MOTOR_Init(void);
void RM_3508_Init(void);
void Fric_3508_Init(void);
void GM_6020_Init(void);
void M_2006_Init(void);
void Slow(float *rec , float target , float slow_Inc);
void MotorSlow(float *rec , float target , float slow_Inc);
void M_2006_ParamInit(void);
void CHAS_ParamInit(void);
void RM_3508_ParamInit(PID_Loop_t *str);

#endif



