#include "masters_RTX.h"
#include "Function.h"
#include "Device.h"

uint8_t Rx[8];
uint8_t Tx[8];

DUM_t DUM;

//---------------------------��Ϣ��---------------------
/**
 * @brief ��������ϵͳ���ݸ��±�־λ
 * @note  Ƶ��Խ��Խ��ǰ ,�첽����Ҳ��ǰ
 */
Data_ID_t Report_IF_DataUpdate(void)
{
  if     (DUM.TxDataInfo.REF_UD_Flag.ShootSpeed_UD) //�첽����
    return ShootSpeed_ID;
  else if(DUM.TxDataInfo.REF_UD_Flag.GameRobotStat_UD) //10hz
    return GameRobotStat_ID;
  else if(DUM.TxDataInfo.REF_UD_Flag.PowerHeatData_UD) //50hz
    return PowerHeatData_ID;
  else if(DUM.TxDataInfo.REF_UD_Flag.UI_Data_UD)
    return UI_Ctrl_ID;
  else if(DUM.TxDataInfo.REF_UD_Flag.SuperCap_UD) //200hz
    return SuperCap_tx_ID;
  else if(DUM.TxDataInfo.REF_UD_Flag.DUM_IMU_UD) //1000hz
    return IMU_DATA_ID;
  else
    return NO_DATA;
}

/**
 * @brief �����ظı����ϵͳ���ݸ���״̬
 * @note  �ڲ���ϵͳ�����ж��е��� 
 */
void Referee_Update(Data_ID_t ID)
{
  switch(ID)
  {
    case GameRobotStat_ID:
      DUM.TxDataInfo.REF_UD_Flag.GameRobotStat_UD = YES;
      break;
    
    case PowerHeatData_ID:
      DUM.TxDataInfo.REF_UD_Flag.PowerHeatData_UD = YES;
      break;
    
    case ShootSpeed_ID:
      DUM.TxDataInfo.REF_UD_Flag.ShootSpeed_UD = YES;
      break;
    
    case IMU_DATA_ID:
      DUM.TxDataInfo.REF_UD_Flag.DUM_IMU_UD = YES;
      break;
    
    case SuperCap_tx_ID:
      DUM.TxDataInfo.REF_UD_Flag.SuperCap_UD = YES;
      break;
    
    case UI_Ctrl_ID:
      DUM.TxDataInfo.REF_UD_Flag.UI_Data_UD = YES;
      break;
  }
}



//-------------------------------������---------------------------
//-------------------------��ȡ���� װ������-------------------------
/**
 * @brief ��ȡ����ϵͳ����
 * @param 
 */
void Get_GameRobotStat_Info(GameRobotStat_Info_t *str)
{
  str->MaxPower         = REF_Report_CHAS_MaxPower();
  str->Robot_ID         = REF_Report_robot_ID();
  str->Shoot_SpeedLimit = REF_Report_Shoot_SpeedLimit();
  str->Shooter_Output   = REF_Report_IF_shooter_output();
  str->Cooling_Limit    = REF_Report_Shoot_CoolingLimit(); 
  str->EMPTY = 0;
  memcpy(Tx , str , 8);
}
void Get_PowerHeatData_Info(PowerHeatData_Info_t *str)
{
  str->CHAS_Power        = REF_Report_CHAS_Power();
  str->CHAS_PowerBuffer  = REF_Report_CHAS_PowerBuffer();
  str->Shooter_Heat      = REF_Report_Shooter_Heat();
  memcpy(Tx , str , 8);
}
void Get_IMU_Info(DUM_IMU_Info_t *str)
{
  str->Yaw_Speed = Report_YawSpeed();
  str->IF_FLY = Judge_IF_Fly();//�Ƿ����
  str->Park_F = Park_Judge_F();//ǰ���λ
  str->Park_R = Park_Judge_R();//���Ҷ�λ
  str->Park_Z = Park_Judge_Z();//ת���λ
  memcpy(Tx , str , 8);
}

extern uint8_t Report_SuperCap_cmd(void);
void Get_SuperCap_Info(SuperCap_tx_Info_t *str)
{
  str->order = Report_SuperCap_cmd();
  str->CHAS_Power = DUM_Report_CHAS_Power();
  str->CHAS_PowerBuffer = DUM_Report_PowerBuffer();
  str->MaxPower = (uint8_t)DUM_Report_CHAS_MaxPower();
  memcpy(Tx , str , 8);
}

void Get_ShootSpeed_Info(ShootSpeed_Info_t *str)
{
  str->real_ShootSpeed = REF_Report_RealShootSpeed();
  str->Shoot_CNT += 1;
  memcpy(Tx , str , 8);
}

void Get_UI_ctrl_cmd(UI_User_cmd_t *str)
{
  str->IF_AUTO = Report_IF_Auto_InitOver();
  str->IF_CLIP = Report_IF_CLIP_OPEN();
  str->IF_SPIN = CHAS_SPIN_Report();
  str->IF_Block_Much = Report_IF_SinBlocks();
  str->IF_Shootheatlimit = Report_IF_ShootHeatLimit();
  str->IF_Bullet_Warning = Report_IF_BulletWarning();
  memcpy(Tx , str , 8);
}

//----------------------------�����Ͳ�----------------------------//
/**
 * @brief ���ͺ���
 * @param 
 */
void Master_Sent(void)
{
  SuperCap_Update();//ֻ�������ش���
  
  UI_Data_Update();//ֻ�������ش���
  
  Data_ID_t ID = Report_IF_DataUpdate();
  switch(ID)
  {
    case GameRobotStat_ID:
        Get_GameRobotStat_Info(&DUM.TxDataInfo.GameRobotStat_Info);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.GameRobotStat_UD = NO;
        break;
    case PowerHeatData_ID:
        Get_PowerHeatData_Info(&DUM.TxDataInfo.PowerHeatData_Info);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.PowerHeatData_UD = NO;
        break;
    case ShootSpeed_ID:
        Get_ShootSpeed_Info(&DUM.TxDataInfo.ShootSpeed_Info);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.ShootSpeed_UD = NO;
        break;
    case IMU_DATA_ID:
        Get_IMU_Info(&DUM.TxDataInfo.DUM_IMU_Info);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.DUM_IMU_UD = NO;
        break;
    case SuperCap_tx_ID:
        Get_SuperCap_Info(&DUM.TxDataInfo.SuperCap_tx_Info);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.SuperCap_UD = NO;          
        break;
    case UI_Ctrl_ID:
        Get_UI_ctrl_cmd(&DUM.TxDataInfo.UI_User_cmd);
        CAN1_DUM_Send(ID , Tx);
        DUM.TxDataInfo.REF_UD_Flag.UI_Data_UD = NO; 
        break;
    default :
        break;
  }
}



/**
 * @brief ������IMU���ݸ���
 * @param 
 */
void DUM_Set_IMU_DataUpdate(void)
{
  Referee_Update(IMU_DATA_ID);
}

/**
 * @brief �������볬�����ͨ��
 * @param 
 */
void Set_SuperCap_cmd_Update(void)
{
  Referee_Update(SuperCap_tx_ID);
}
int supercap_cnt = 0;
void SuperCap_Update(void)
{
  supercap_cnt++;
  if(supercap_cnt == 5){//5ms��һ��
    if(Master == MASTER_UP) //ֻ�������ش���
      Set_SuperCap_cmd_Update();
    supercap_cnt = 0;
  }
}

void Set_UI_Data_Update(void)
{
  Referee_Update(UI_Ctrl_ID);
}
int UI_Data_cnt = 0;
void UI_Data_Update(void)
{
  UI_Data_cnt++;
  if(UI_Data_cnt == 10){//10ms����һ��
    if(Master == MASTER_UP)//ֻ�������ش���
      Set_UI_Data_Update();
    UI_Data_cnt = 0;
  }
}


//-------------------------------������---------------------------
/**
 * @brief ���ػ�ȡ���յ�������
 * @param 
 */
void DUM_Data_Receive(uint8_t *rx,Data_ID_t ID)
{
  switch(ID)
  {
    case GameRobotStat_ID:
        memcpy(&DUM.RxDataInfo.GameRobotStat_Info, rx , 8);
        break;
    case PowerHeatData_ID:
        memcpy(&DUM.RxDataInfo.PowerHeatData_Info, rx , 8);
        break;  
    case IMU_DATA_ID:
        memcpy(&DUM.RxDataInfo.DUM_IMU_Info , rx , 8);
        break;
    case ShootSpeed_ID:
        memcpy(&DUM.RxDataInfo.ShootSpeed_Info , rx , 8);
        break;
    
    case SuperCap_rx_ID:
        memcpy(&DUM.RxDataInfo.SuperCap_rx_Info , rx , 8);
        break;
    
    case UI_Ctrl_ID:
        memcpy(&DUM.RxDataInfo.UI_User_cmd , rx , 8);
        break;
  }
}


/**
 * @brief �����س����ȡ���ݽӿ�
 * @param 
 */
/*���̹���*/
float DUM_Report_CHAS_Power(void)
{
  return DUM.RxDataInfo.PowerHeatData_Info.CHAS_Power;
}
/*���������*/
float DUM_Report_CHAS_MaxPower(void)
{
  return DUM.RxDataInfo.GameRobotStat_Info.MaxPower;
}
/*������������*/
uint16_t DUM_Report_PowerBuffer(void)
{
  return DUM.RxDataInfo.PowerHeatData_Info.CHAS_PowerBuffer;
}
/*��������*/
uint8_t DUM_Report_Shoot_SpeedLimit(void)
{
  return DUM.RxDataInfo.GameRobotStat_Info.Shoot_SpeedLimit;
}
/*������ID*/
uint8_t DUM_Report_Robot_ID(void)
{
  return DUM.RxDataInfo.GameRobotStat_Info.Robot_ID;
}
/*�������������*/
uint16_t DUM_Report_Shoot_Heat(void)
{
  return DUM.RxDataInfo.PowerHeatData_Info.Shooter_Heat;
}
/*�������������������*/
uint16_t DUM_Report_CoolingLimit(void)
{
  /*������û������*/
  if(!IF_MASTER_DOWN_CONNECT) DUM.RxDataInfo.GameRobotStat_Info.Cooling_Limit = 120;//�����Ӳ�������������
  return DUM.RxDataInfo.GameRobotStat_Info.Cooling_Limit;
}
/*����������yaw�ٶ�*/
float DUM_Report_CHAS_IMU_YAW_Speed(void)
{
  return DUM.RxDataInfo.DUM_IMU_Info.Yaw_Speed;
}
///*����������pit�ٶ�*/
//float DUM_Report_CHAS_IMU_PIT_Angle(void)
//{
//  return DUM.RxDataInfo.DUM_IMU_Info.PIT_Angle;
//}
/*Ħ�����Ƿ�ϵ�*/
bool DUM_Report_IF_ArmorBooster_work(void)
{
  bool res;
  if(DUM.RxDataInfo.GameRobotStat_Info.Shooter_Output == 1)
    res = YES;
  else res = NO;
  if(!IF_MASTER_DOWN_CONNECT)res = YES;//������Ĭ�ϵ�Դ����
  return res;
}
/*������ʵ����*/
float DUM_Report_RealShootSpeed(void)
{
  return DUM.RxDataInfo.ShootSpeed_Info.real_ShootSpeed;
}
/*����������*/
uint32_t DUM_Report_Shoot_NUM(void)
{
  return DUM.RxDataInfo.ShootSpeed_Info.Shoot_CNT;
}
/*�����Ƿ����*/
bool DUM_Report_IF_CarFly(void)
{
  bool res = NO;
  if(DUM.RxDataInfo.DUM_IMU_Info.IF_FLY == 1)
    res = YES;
  else res = NO;
  return res;
}
/*������λ�����ƶ�ָ��*/
Sonic_mode_t DUM_Report_Park_Fmove(void)
{
  return DUM.RxDataInfo.DUM_IMU_Info.Park_F;
}
Sonic_mode_t DUM_Report_Park_Rmove(void)
{
  return DUM.RxDataInfo.DUM_IMU_Info.Park_R;
}
Sonic_mode_t DUM_Report_Park_Zmove(void)
{
  return DUM.RxDataInfo.DUM_IMU_Info.Park_Z;
}

//**********************UI**************************//
/*UI��������*/
float Report_SuperCap_Vremain(void)
{
  return DUM.RxDataInfo.SuperCap_rx_Info.V_CAP;
}
/*UI�Ƿ�����*/
uint8_t Report_UI_User_cmd_SPIN(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_SPIN;
}
/*UI�Ƿ�����*/
uint8_t Report_UI_User_cmd_AUTO(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_AUTO;
}
/*UI�Ƿ񿪵���*/
uint8_t Report_UI_User_cmd_CLIP(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_CLIP;
}
/*UI�Ƿ���������*/
uint8_t Report_UI_User_cmd_SHOOTLIMIT(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_Shootheatlimit;
}
/*UI�Ƿ��ο���*/
uint8_t Report_UI_User_cmd_BlockMuch(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_Block_Much;
}
/*UI�Ƿ񲹵�����*/
uint8_t Report_UI_User_cmd_BulletWarning(void)
{
  return DUM.RxDataInfo.UI_User_cmd.IF_Bullet_Warning;
}

//��������գ��������ض�ȡ�������������0
void ShootNum_Reset(void)
{
  DUM.RxDataInfo.ShootSpeed_Info.Shoot_CNT = 0;
  DUM.TxDataInfo.ShootSpeed_Info.Shoot_CNT = 0;
}

