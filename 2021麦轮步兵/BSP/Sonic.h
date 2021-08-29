#ifndef __SONIC_H
#define __SONIC_H

#include "system.h"


///////////////////////////ע����ö����masters_RTX.c.h�ж��е��õ�
typedef enum
{
  NO_FLY = 0,
  FLY = 1,//ǰ�����(���ȼ����)
  
  PARK_FrontGood ,//��λģʽ����ǰ����λ���
  PARK_RighGood ,//��λģʽ���ұ߶�λ���
  PARK_TurnGood ,//��λģʽ��ת���λ���
  
  PARK_TurnLeft ,//��λģʽ����ת
  PARK_TurnRigh ,//��λģʽ����ת
  
  PARK_MoveRigh ,//��λģʽ������ƽ��
  PARK_MoveLeft ,//��λģʽ������ƽ��
  
  PARK_MoveFront ,//��λģʽ����ǰ��
  PARK_MoveBehind ,//��λģʽ��������
  
}Sonic_mode_t;

typedef struct
{
  int16_t time;
  float distance;
  bool IF_Data_Update;
}Sonic_Fly_Info_t;

typedef struct
{
  int16_t FL_TIM,FR_TIM,R_TIM;
  float FL_DIS,FR_DIS,R_DIS;
  bool IF_Data_Update_FL;
  bool IF_Data_Update_FR;
  bool IF_Data_Update_R;
}Sonic_Park_Info_t;

typedef struct
{
  Sonic_Fly_Info_t  Fly_Info;
  Sonic_Park_Info_t Park_Info;
  
  Sonic_mode_t Sonic_mode;
}Sonic_Info_t;

#define  FLY_DIS    200

#define FL_DIS_Standard   100
#define FR_DIS_Standard   100
#define R_DIS_Standard    100

void Sonic_Ctrl(void);

void Sonic_ReadData_Fly(uint8_t *rxBuf);
void Sonic_ReadData_FL(uint8_t *rxBuf);
void Sonic_ReadData_FR(uint8_t *rxBuf);
void Sonic_ReadData_R(uint8_t *rxBuf);

void KS103_FLY_Explore(void);
void KS103_FL_Explore(void);
void KS103_FR_Explore(void);
void KS103_R_Explore(void);

Sonic_mode_t Judge_IF_Fly(void);
Sonic_mode_t Park_Judge_F(void);
Sonic_mode_t Park_Judge_R(void);
Sonic_mode_t Park_Judge_Z(void);

float CHAS_Park_FB_Speed(void);
float CHAS_Park_LR_Speed(void);
float CHAS_Park_Z_Speed(void);



#endif 
