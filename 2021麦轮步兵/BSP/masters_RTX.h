#ifndef __MASTER_RTX_H
#define __MASTER_RTX_H

#include "System.h"

#include "Sonic.h"

typedef __packed struct
{
  uint8_t Robot_ID;    //������ID
  uint8_t Shoot_SpeedLimit; //��������
  uint16_t Cooling_Limit;  //��������
//  uint16_t CoolingRate;  //��ȴ�ٶ�
  uint8_t Shooter_Output;  //�����Դ���Ƿ�ϵ�
  uint16_t MaxPower;//����� 
  uint8_t EMPTY;
}GameRobotStat_Info_t;

typedef __packed struct
{
  float CHAS_Power; //����˲ʱ����
  uint16_t CHAS_PowerBuffer;//����˲ʱ��������
  uint16_t Shooter_Heat; //ʵʱ�������
}PowerHeatData_Info_t;

typedef __packed struct
{
  float Yaw_Speed;
  Sonic_mode_t IF_FLY;
  Sonic_mode_t Park_F;
  Sonic_mode_t Park_R;
  Sonic_mode_t Park_Z;
}DUM_IMU_Info_t;

typedef __packed struct
{
  float real_ShootSpeed;
  uint32_t Shoot_CNT;
}ShootSpeed_Info_t;

typedef __packed struct
{
  uint8_t order;
  uint8_t MaxPower;//�����
  float CHAS_Power; //����˲ʱ����
  uint16_t CHAS_PowerBuffer;//����˲ʱ��������
}SuperCap_tx_Info_t;

typedef __packed struct
{
  float  V_CAP;
  uint32_t EMPTY;
}SuperCap_rx_Info_t;

typedef __packed struct
{
  uint8_t IF_SPIN;
  uint8_t IF_AUTO;
  uint8_t IF_CLIP;
  uint8_t IF_Shootheatlimit;
  uint8_t IF_Block_Much;
  uint8_t IF_Bullet_Warning;
  uint8_t EMPTY2;
  uint8_t EMPTY3;
}UI_User_cmd_t;

typedef enum
{
  NO_DATA = 0x000,
  GameRobotStat_ID = 0x100,
  PowerHeatData_ID = 0x101,
  IMU_DATA_ID      = 0X102,
  ShootSpeed_ID = 0x009,
  SuperCap_tx_ID = 0x501,
  SuperCap_rx_ID = 0x502,
  UI_Ctrl_ID = 0x601,
}Data_ID_t;


typedef struct
{
  bool GameRobotStat_UD;
  bool PowerHeatData_UD;
  bool ShootSpeed_UD;
  bool DUM_IMU_UD;
  bool SuperCap_UD;
  bool UI_Data_UD;
}REF_UD_Flag_t;

typedef struct
{
  REF_UD_Flag_t REF_UD_Flag;
  GameRobotStat_Info_t GameRobotStat_Info;
  PowerHeatData_Info_t PowerHeatData_Info;
  DUM_IMU_Info_t       DUM_IMU_Info;
  ShootSpeed_Info_t   ShootSpeed_Info;
  SuperCap_tx_Info_t  SuperCap_tx_Info;
  SuperCap_rx_Info_t  SuperCap_rx_Info;
  UI_User_cmd_t UI_User_cmd;
}DUM_DataInfo_t;

typedef struct
{
  DUM_DataInfo_t TxDataInfo;
  DUM_DataInfo_t RxDataInfo;
}DUM_t;



Data_ID_t Report_IF_DataUpdate(void);
void Referee_Update(Data_ID_t ID);


void Get_GameRobotStat_Info(GameRobotStat_Info_t *str);
void Get_PowerHeatData_Info(PowerHeatData_Info_t *str);
void Get_ShootSpeed_Info(ShootSpeed_Info_t *str);
void Get_SuperCap_Info(SuperCap_tx_Info_t *str);
void Get_IMU_Info(DUM_IMU_Info_t *str);

void Master_Sent(void);

void DUM_Set_IMU_DataUpdate(void);

void Set_SuperCap_cmd_Update(void);
void SuperCap_Update(void);

void Set_UI_Data_Update(void);
void UI_Data_Update(void);

void DUM_Data_Receive(uint8_t *rx,Data_ID_t ID);


//---�����ݲ�
float    DUM_Report_CHAS_Power(void);
float    DUM_Report_CHAS_MaxPower(void);
uint16_t DUM_Report_PowerBuffer(void);
uint8_t  DUM_Report_Shoot_SpeedLimit(void);
uint8_t  DUM_Report_Robot_ID(void);
uint16_t DUM_Report_Shoot_Heat(void);
float    DUM_Report_CHAS_IMU_YAW_Speed(void);
//float    DUM_Report_CHAS_IMU_PIT_Angle(void);
uint16_t DUM_Report_CoolingLimit(void);
bool     DUM_Report_IF_ArmorBooster_work(void);
float    DUM_Report_RealShootSpeed(void);
uint32_t DUM_Report_Shoot_NUM(void);
bool     DUM_Report_IF_CarFly(void);
//---UI
void ShootNum_Reset(void);

float   Report_SuperCap_Vremain(void);
uint8_t Report_UI_User_cmd_SPIN(void);
uint8_t Report_UI_User_cmd_AUTO(void);
uint8_t Report_UI_User_cmd_CLIP(void);
uint8_t Report_UI_User_cmd_SHOOTLIMIT(void);
uint8_t Report_UI_User_cmd_BlockMuch(void);
uint8_t Report_UI_User_cmd_BulletWarning(void);
#endif 


