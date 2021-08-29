/***      �� ����������ƴ��� ��

 *      ������       ������ + +
 *   �������� �ة��������������� �ة�����++
 *   ��                 ��
 *   ��       ������       ��++ + + +
 *   ���������������������������������� ��+
 *   ��                 ��+
 *   ��       ���ة�       ��
 *   ��                 ��
 *   ����������         ����������
 *       ��         ��
 *       ��         ��   + +
 *       ��         ��
 *       ��         ��������������������������������
 *       ��                        ��
 *       ��                        ������
 *       ��                        ������
 *       ��                        ��
 *       ������  ��  �����������������Щ�����  ��������  + + + +
 *         �� ���� ����       �� ���� ����
 *         �������ة�����       �������ة�����  + + + +
 *              
 *               ������BUG!
 */
 
#include "rifle.h"
#include "Device.h"
#include "Function.h"
 
/* Init start */
RIFLE_Info_t Rifle = {
  .ctrl_mode = Ctrl_Err,
  .pid_mode = PID_Err,
  .action_mode = ACT_Err,
  .PID_type = Turn_off,
  .SingleAngle = SINGLE_ANGLE,
  .ContinuFreq = CONTIN_FREQ_10,
};//������Ϣ�ṹ��


/* Init end   */

/* --------------------------�����------------------------- */
/**
 * @brief ���̴򵯻�������
 * @param 
 */
void RIFLE_Ctrl(void)
{
  switch(Rifle.ctrl_mode)
  {
    case  RC_CTRL_MODE:
      RIFLE_RC_Ctrl();
      break;
    
    case  KEY_CTRL_MODE:
      RIFLE_KET_Ctrl();
      break;
  }
  RIFLE_Handler();
}
 
/**
 * @brief ���̵����Ϣ��ȡ
 * @param 
 */
void RIFLE_GET_Info(void)
{
  Rifle.ctrl_mode = System.ctrl_mode;
  Rifle.pid_mode = System.pid_mode;
  Rifle.action_mode = System.action_mode;
  Rifle.PID_type = GET_PID_Type();
  FlagUpdate();
  Check_IF_FricSpeed_Normal();
}

 /**
 * @brief ���̵��PID�����ܺ���
 * @param 
 */
void RIFLE_SetPID(void)
{
  RIFLE_GET_PID_Type(&Rifle.Motor[RIFLE].PID);
  RIFLE_PID_Switch(&Rifle.Motor[RIFLE].PID);
}

/**
 * @brief PID�����ȡ
 * @param 
 */
void RIFLE_GET_PID_Type(PID_Info_t *str)
{
  str->PID_type = Rifle.PID_type;
}
 
/**
 * @brief PID�л�
 * @param 
 */
void RIFLE_PID_Switch(PID_Info_t *str )
{
  static int length = sizeof(PID_Parameter_t);
  switch (str->PID_type)
  {   
    case Turn_off :{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[M_2006][Turn_off],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[M_2006][Turn_off],length);
    }break;  

    default :{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[M_2006][RC_GYRO],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[M_2006][RC_GYRO],length);
    }break; 
  }
}



/**
 * @brief ����ң�ؿ���
 * @param 
 */
 System_Ctrl_Mode_t R_prev_ctrl_mode = Ctrl_Err;
void RIFLE_RC_Ctrl(void)
{
  if(R_prev_ctrl_mode != Rifle.ctrl_mode)
  {/* ��һ�ν���RCģʽ */
    R_prev_ctrl_mode = Rifle.ctrl_mode;
    RIFLE_MotorAngleInit();
    M_2006_Init();
  }
//  /*PID��������*/
//  PID_Debug(&Rifle.Motor[RIFLE].PID);
  
  if(Rifle.flag.IF_Block)BlockReact();//��������
  else//����������
  switch (Rifle.PID_type)
  {
    case RC_MECH:
      RIFLE_MECH_RC_Ctrl();
      break;
    case RC_GYRO:
      RIFLE_GYRO_RC_Ctrl();
      break; 
  }
  
}
/**
 * @brief ���̼��̿���
 * @param 
 */
void RIFLE_KET_Ctrl(void)
{
  if(R_prev_ctrl_mode != Rifle.ctrl_mode)
  {/* ��һ�ν���KEYģʽ */
    R_prev_ctrl_mode = Rifle.ctrl_mode;
    RIFLE_MotorAngleInit(); 
    M_2006_Init();   
  }
  if(Rifle.flag.IF_Block)BlockReact();//��������
  else//����������
  {
    Keyboard_Ctrl();
//    Yaw_AutoShoot();//�����Զ���
    Buff_AutoShoot();//����Զ���
  }
}


/* --------------------------���Ʋ�------------------------- */

/**
 * @brief ��еģʽ
 * @param 
 */
static PID_type_t R_prev_pid_type = Turn_off;
void RIFLE_MECH_RC_Ctrl(void)
{
  if(R_prev_pid_type != Rifle.PID_type)
  {/* ��һ�ν����еģʽ */
    R_prev_pid_type = Rifle.PID_type;
    RIFLE_MotorAngleInit();
    RIFLE_SetPID();
    FlagReset();

  }
  SingleFire();
}

/**
 * @brief ������ģʽ
 * @param 
 */
void RIFLE_GYRO_RC_Ctrl(void)
{
  if(R_prev_pid_type != Rifle.PID_type)
  {/* ��һ�ν���������ģʽ */
    R_prev_pid_type = Rifle.PID_type;
    RIFLE_MotorAngleInit();
    RIFLE_SetPID();
    ContinFreq_10();//������Ƶ�ָ�Ϊ���
    FlagReset();
    
  }
  ContinFire();
}

void Keyboard_Ctrl(void)
{
  if(R_prev_pid_type != Rifle.PID_type)
  {
    R_prev_pid_type = Rifle.PID_type;
    RIFLE_SetPID();
    ContinFreq_10();//������Ƶ�ָ�Ϊ���
    FlagReset();
  }
  SingleFire();
  ContinFire();
}

/**
 * @brief ��λ����
 * @note 
 * @param 
 */
void RIFLE_Reset(void)
{  
  if(R_prev_ctrl_mode != Rifle.ctrl_mode)
  {/* ��һ�ν��븴λģʽ */
    R_prev_ctrl_mode = Rifle.ctrl_mode;
    //�������
    memset(&Rifle.Motor[RIFLE].PID.Speed_Loop,0,sizeof(PID_Loop_t));
    memset(&Rifle.Motor[RIFLE].PID.Angle_Loop,0,sizeof(PID_Loop_t));
    FlagReset();
  }
  
  if(R_prev_pid_type != Rifle.PID_type)
  {/* ��һ�ν��븴λģʽ */
    R_prev_pid_type = Rifle.PID_type;
    RIFLE_SetPID();    
  } 
  //ж��
  RIFLE_Stop();
}
/* --------------------------���ܲ�------------------------- */
/**
 * @brief ״̬����
 * @param 
 */
void FlagUpdate(void)
{
  Rifle.flag.IF_SinFire_Request = SinFireRequest_Report(); 
  Rifle.flag.IF_ConFire_Request = ConFireRequest_Report();
  Rifle.flag.IF_SingleFire_OVER = Judge_IF_SingleFire_OVER();
  
  //�������
  if(!Rifle.flag.IF_ConFire_Request)
    //�������
    Rifle.flag.IF_SinFire_Block = Judge_SinFireBlock();
  else          
    //�������
    Rifle.flag.IF_ConFire_Block = Judge_ConFireBlock();
  
  Rifle.flag.IF_Block = IF_FireBlock();
  Rifle.flag.IF_Stuck = Stuck_Judge();
}
void FlagReset(void)
{
  Rifle.flag.IF_ConFire_Request = false;//ȡ����������
  Rifle.flag.IF_SinFire_Request = false;//ȡ����������
//  Rifle.flag.IF_SingleFire_OVER = YES;  //����׼������
}

/**
 * @brief �жϵ������
 * @note  ��������򷵻�YES 1
 * @param 
 */
bool Judge_IF_SingleFire_OVER(void)
{ 
  bool res;
  Motor_Data_t *DATA = &(Rifle.Motor[RIFLE].motor_data);
  
  if(abs(DATA->PID_Angle_target-DATA->PID_Angle) <= Judge_AngleErr)   
    res = YES;
  else 
    res = NO;
  if(Rifle.flag.IF_ConFire_Request)
    res = YES;//������������  
  return res;
}

//��תһ��
void Single_Forward(void)
{
  Rifle.Motor[RIFLE].motor_data.PID_Angle_target += Rifle.SingleAngle;
}
void Single_Forward_HALF(void)
{
  Rifle.Motor[RIFLE].motor_data.PID_Angle_target += Rifle.SingleAngle/2;
}
void SetAngle_stay(void)
{
  Rifle.Motor[RIFLE].motor_data.PID_Angle_target = Rifle.Motor[RIFLE].motor_data.PID_Angle;
}
//��תһ��
void Single_Reverse(void)
{
  Rifle.Motor[RIFLE].motor_data.PID_Angle_target -= Rifle.SingleAngle;
}
void Single_Reverse_HALF(void)
{
  Rifle.Motor[RIFLE].motor_data.PID_Angle_target -= Rifle.SingleAngle/2;
}
/**
 * @brief ����
 * @note  ���������λ�����ж���һ���Ƿ�����ɣ�����������������һ�ε���
 * @param 
 */
void SingleFire(void)
{
  if(Rifle.flag.IF_SinFire_Request)//�е�������
  if(Report_IF_Fric3508_SetSpeed()){//��Ħ����Ϊ3508ʱ��3508�дﵽĿ��ת������
  if(Judge_IF_SingleHeat_ShootAllow()){//��������
  if(Rifle.flag.IF_SingleFire_OVER)//��һ�ε�������
  {
    Single_Forward();
    Rifle.flag.IF_SinFire_Request = false;
  }
  }else RIFLE_MotorAngleInit();
  }else RIFLE_MotorAngleInit();
}
/**
 * @brief ����
 * @param 
 */
void ContinFreq_20(void)
{
  /*20��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_20;
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit() - ContinHeatLimitErr - 30)
    ContinFreq_03();
}
void ContinFreq_15(void)
{
  /*15��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_15;
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit() - ContinHeatLimitErr - 30)
    ContinFreq_03();
}
void ContinFreq_12(void)
{
  /*12��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_12;
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit() - ContinHeatLimitErr - 30)
    ContinFreq_03();
}
void ContinFreq_10(void)
{
  /*10��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_10;
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit() - ContinHeatLimitErr - 30)
    ContinFreq_03();
}
//����ʱͻȻ�ı��������ƣ�Ӧ�Դ�ʩ
void Judge_IF_Change_HeatLimit(void)
{
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit() - ContinHeatLimitErr - 30)
    ContinFreq_03();
}
void ContinFreq_05(void)
{
  /* 5��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_05;
}

void ContinFreq_03(void)
{
  /* 3��Ƶ*/
  Rifle.ContinuFreq = CONTIN_FREQ_03;
}

void ContinFire(void)
{
  if(Rifle.flag.IF_ConFire_Request)//����������
  if(Report_IF_Fric3508_SetSpeed()){//��Ħ����Ϊ3508ʱ��3508�дﵽĿ��ת������
  if(Judge_IF_Heat_ShootAllow()){//��������
  if(Rifle.flag.IF_SingleFire_OVER)//��һ�ε�������
  {
    Rifle.flag.IF_SingleFire_OVER = YES;
    Rifle.Motor[RIFLE].motor_data.PID_Speed_target = -Rifle.ContinuFreq * MOTOR_1GPS_SPEED;
  }
  }else RIFLE_MotorAngleInit();
  }else RIFLE_MotorAngleInit();
}
//----------------------------��������-------------------
//������Ϣ��λ
void BlockState_Reset(void)
{
  BlockState_t *str = &Rifle.Motor[RIFLE].BlockState;
  str->IF_FireBlock = false; //������־λ��0����ʾ�Ѳ�����
  str->BlockReact_Over = YES;
  str->type = NO_Block;
  str->cnt = 0;
}
//��ת���
bool Stuck_Judge(void)
{
  Motor_Data_t *DATA = &Rifle.Motor[RIFLE].motor_data;
  PID_Info_t *PID = &Rifle.Motor[RIFLE].PID;
  if(abs(DATA->PID_Speed) <= Judge_Stuck_SpeedMAX && 
      abs(PID->Speed_Loop.PID_Output) > Judge_Stuck_OutputMIN)
    return YES;
  else return NO;
}
/**
 * @brief ���������Ӧ
 * @note  
 */
bool First = 0;
int Block_num = 0; //�����Ĵ���
void SinFireBlock_React(void)
{
  BlockState_t *str = &Rifle.Motor[RIFLE].BlockState;
  //�ȷ�ת
//  if(Block_num == 1)//�����ﵽ6��  ��ֹ���޿���
//  {
//    //���ذ��Ŀ��Ƕȣ��Ա��´�������
//    Rifle.Motor[RIFLE].motor_data.PID_Angle_target -= Rifle.SingleAngle/4;
//    str->BlockReact_Over = YES;//������Ӧ���
//    Block_num = 0;//����������0
//  }
//  else   //�����û����6��
//  {
    if(First == 0)
    {
      Single_Reverse();//��ת
      First = 1;//ִֻ��һ��
    }
    str->cnt--;
    if(Rifle.flag.IF_SingleFire_OVER || str->cnt == 0)
    {
//      //��ת����/ʱ�䵽�� ����ת
//      Single_Forward();
      SetAngle_stay();//ͣ��ԭ��
      str->BlockReact_Over = YES; 
      Block_num++;//����������1
            First = 0;
    }
//  }
  
  if(str->BlockReact_Over == YES)
  //������Ӧ��ɺ�
    BlockState_Reset();
}
/**
 * @brief ���ѿ�������̫�� 
 * @note  
 */
void Reset_Block_num(void)
{
  Block_num = 0;
}
bool Judge_IF_SinBlocks(void)
{
  bool res = NO; 
  if(Block_num >= Block_WarningNUM)
    res = YES;
  else res = NO;
  return res;
}
bool Report_IF_SinBlocks(void)
{
  return Judge_IF_SinBlocks();
}
/**
 * @brief ����������� 
 * @note  
 */
void ConFireBlock_React(void)
{
  BlockState_t *str = &Rifle.Motor[RIFLE].BlockState;
  //�ȷ�ת
  Rifle.Motor[RIFLE].motor_data.PID_Speed_target = MOTOR_SPEED_05;
  str->cnt --;
//  //�����ת��ס����ӿ췴ת��ʱ�ٶ�
//  if(Stuck_Judge())str->cnt -= 100;
  if( str->cnt <= Judge_ConBlock_TIM - 300)
  {//ʱ�䵽�� �͸�λ
    RIFLE_MotorAngleInit();
    str->BlockReact_Over = YES;
  }
  
  if(str->BlockReact_Over == YES)
  //������Ӧ��ɺ�
    BlockState_Reset();
}

void BlockReact(void)
{
  RIFLE_Motor_t *str = &Rifle.Motor[RIFLE];
  switch(str->BlockState.type)
  {
    case SinBlock:
      //��������
      SinFireBlock_React();
      break;
    case ConBlock:
      //��������
      ConFireBlock_React();
      break;
  }
}
/**
 * @brief ����ʱ���� 
 * @note   �������
 */
bool Judge_SinFireBlock(void)
{
  BlockState_t *str = &Rifle.Motor[RIFLE].BlockState;
  
  if(str->IF_FireBlock == NO)//ֻ�����޿�����־λ��ʱ��ż��
  {
    if(Judge_IF_SingleFire_OVER() == NO)
    //ʱ����
    str->cnt++;
    else str->cnt = 0;
  }
  
  if(str->cnt >= Judge_SinBlock_TIM)//��ʱ����һ��ʱ����Ϊ����
  {
    str->IF_FireBlock = YES;//�ж�Ϊ����
    str->type = SinBlock; //�ж�Ϊ��������
    str->BlockReact_Over = NO;  //������Ӧ��û��
  }
  
  return str->IF_FireBlock;//���ؿ���״̬
}
/**
 * @brief ������ת��� 
 * @note   �������
 */
bool Judge_ConFireBlock(void)
{
  BlockState_t *str = &Rifle.Motor[RIFLE].BlockState;
  
  if(str->IF_FireBlock == false)//ֻ�����޿�����־λ��ʱ��ż��
  {
    if(Stuck_Judge())
    //��ת���
    str->cnt++;
    else str->cnt = 0;
  }
  
  if(str->cnt >= Judge_ConBlock_TIM)//��ʱ����һ��ʱ����Ϊ����
  {
    str->IF_FireBlock = YES;
    str->type = ConBlock;
    str->BlockReact_Over = NO;
  }
  
  return str->IF_FireBlock;//���ؿ���״̬
}
bool IF_FireBlock(void)
{
  return Rifle.Motor[RIFLE].BlockState.IF_FireBlock;
}
//-----------------------------------------------
/**
 * @brief Ħ���������Ĵ��ӳ�
 * @note   ���̫��������Դ򵯣�
           �ڲ����ֿ񰴵������
           �����Ħ���ֱ���ס������ת
 */
int FricCheck_cnt = 0;
bool IF_FricSpeed_Normal = NO;
void Check_IF_FricSpeed_Normal(void)
{
  bool res = NO;
  
  if(IF_MODULE_WORK)
    FricCheck_cnt++;
  else FricCheck_cnt = 0;
  
  if(FricCheck_cnt >= FricNormal_Delay) {
    res = YES;
    FricCheck_cnt = FricNormal_Delay;//�����
  }
  IF_FricSpeed_Normal = res;
}
bool Report_IF_FricSpeed_Normal(void)
{
  return IF_FricSpeed_Normal;
}

/**
 * @brief ���󵥷�
 * @note 
 * @param 
 */
void SingleFireRequest(void)
{
  if(IF_MODULE_WORK)
  //ȷ������ģ�鿪������ܴ�
  if(Report_IF_FricSpeed_Normal())
  //ȷ��Ħ�����ٶ�����
  if(!ConFireRequest_Report())
  //������
  if(!IF_FireBlock())//������
  {
    Rifle.flag.IF_SinFire_Request = true;
    Buff_AutoShoot_CntReset();//������ʱ����Զ��򵯵ļ������ù�0
  }
}

void ContinFire_ON(void)
{
  if(IF_MODULE_WORK)
  //ȷ������ģ�鿪������ܴ�
  if(Report_IF_FricSpeed_Normal())
  //ȷ��Ħ�����ٶ�����
  if(!SinFireRequest_Report())
  //�޵���
  if(!IF_FireBlock())//������
    Rifle.flag.IF_ConFire_Request = true;
}

void ContinFire_OFF(void)
{
  if(Rifle.flag.IF_ConFire_Request == true)
  {
    RIFLE_MotorAngleInit();
    Rifle.flag.IF_ConFire_Request = false;
  }
}

bool SinFireRequest_Report(void)
{
  return Rifle.flag.IF_SinFire_Request;
}

bool ConFireRequest_Report(void)
{
  return Rifle.flag.IF_ConFire_Request;
}


//----------------------������---------------------
/**
 * @brief �õ����Err
 * @param 
 */
float RIFLE_Get_AngleErr(Motor_Data_t *str)
{
  float res;
  res = str->PID_Angle_target - str->PID_Angle;
  return res;
}
/**
 * @brief �õ����Err
 * @param 
 */
float RIFLE_Get_SpeedErr(Motor_Data_t *str)
{
  float res;
  res = str->PID_Speed_target - str->PID_Speed;
  return res;
}

/**
 * @brief �Ե�����صĽǶ�ֵ����һ��Խ�紦��
 * @param 
 */
int16_t prev_Angle = 4096;
int ROUND = 0;
float RIFLE_MotorAngle_Proc(int16_t Angle)
{
  float res;
  if(Angle - prev_Angle >= 7200)
    ROUND--;
  if(Angle - prev_Angle <=-7200)
    ROUND++;
  prev_Angle = Angle;
  res = ROUND * 8192 + Angle;
  return (float)res;
}
/**
 * @brief ����ǶȺͼ���ֵ��ʼ��/��λ
 * @param 
 */
void RIFLE_MotorAngleInit(void)
{
  Rifle.flag.IF_SinFire_Request = false;//ȡ��һֱ�񰴵��µĵ�������������ȡ����һֱ�����ܴ�ʹ�
  
  Motor_Data_t *str = &(Rifle.Motor[RIFLE].motor_data);
  str->PID_Angle_target = str->CAN_GetData.Motor_Angle;
  str->PID_Speed_target = 0;
  prev_Angle = 4096;
  ROUND = 0;
}
/**
 * @brief ����ͬ��
 * @param 
 */
void RIFLE_DataSync(Motor_Data_t *str)
{
  str->PID_Angle = RIFLE_MotorAngle_Proc(str->CAN_GetData.Motor_Angle);
  str->PID_Speed = str->CAN_GetData.Motor_Speed;
}
/**
 * @brief �õ�������
 * @param 
 */
float RIFLE_GetOutput(RIFLE_Motor_t *str)
{
  PID_Info_t *PID = &str->PID;
  Motor_Data_t *DATA = &str->motor_data;
  int16_t res;
  
  RIFLE_DataSync(DATA);//����ͬ��

  PID->Angle_Loop.Err = RIFLE_Get_AngleErr(DATA);
  
  if(!Rifle.flag.IF_ConFire_Request)
  //�����������ýǶȻ���������ر�
    DATA->PID_Speed_target = PID_Algorithm(&PID->Angle_Loop);//�ǶȻ�
  
  PID->Speed_Loop.Err = RIFLE_Get_SpeedErr(DATA);
  
  res = (int16_t)PID_Algorithm(&PID->Speed_Loop);//�ٶȻ�
  
  return res;
}

/**
 * @brief RIFLE������
 * @note 
 */
void RIFLE_Output(void)
{
	static int16_t pid_out[4] = {0,0,0,0};
	/* �ٶȻ�������� */
  pid_out[RIFLE] = (int16_t)RIFLE_GetOutput(&Rifle.Motor[RIFLE]);

	CAN2_Send(RIFLE_ESC, pid_out);	
} 

void RIFLE_Stop(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
	CAN2_Send(RIFLE_ESC, pid_out);  
}

void RIFLE_Handler(void)
{
    /*������*/  
    RIFLE_Output();
}


bool ShootAllow = YES,SingleAllow = YES;
bool IF_Brust = NO;//�������
bool Judge_IF_SingleHeat_ShootAllow(void)
{
  /*�ж��Ƿ�����*/
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit()-SingleHeatLimitErr )
    SingleAllow = NO;
  
  /*������֮��ȴ�������������������*/
  if(SingleAllow == NO)
    if(DUM_Report_Shoot_Heat() < DUM_Report_CoolingLimit()-SingleHeatLimitErr )
      SingleAllow = YES;
    
  /*��������ͨѶ�쳣*/
  if(!IF_DUM_NORMAL)SingleAllow = YES;
    
  /*�����������Ѫģʽ*/
  if(IF_Brust == YES)SingleAllow = YES;
    
  return SingleAllow;
}
bool Judge_IF_Heat_ShootAllow(void)
{
  /*�ж��Ƿ�����*/
  if(DUM_Report_Shoot_Heat() >= DUM_Report_CoolingLimit()-ContinHeatLimitErr  )
    ShootAllow = NO;
  
  /*������֮��ȴ�������������������*/
  if(ShootAllow == NO)
    if(DUM_Report_Shoot_Heat() < DUM_Report_CoolingLimit()-ContinHeatLimitErr )
      ShootAllow = YES;
  
  /*��������ͨѶ�쳣*/
  if(!IF_DUM_NORMAL)ShootAllow = YES;
    
  /*�����������Ѫģʽ*/
  if(IF_Brust == YES)ShootAllow = YES;
    
    
  return ShootAllow;
}
/**
 * @brief �����Ƿ���������
 * @note  1--��������  0--û������
 */
bool Report_IF_ShootHeatLimit(void)
{
  return !ShootAllow;
}

void Brust_ON(void)
{
  IF_Brust = YES;
}
void Brust_OFF(void)
{
  IF_Brust = NO;
}

/**
 * @brief �����Ƿ���Ҫ����
 * @note  
 */
bool BulletWarning = NO;
bool Judge_IF_BulletWarning(void)
{
  bool res;
  if(DUM_Report_Shoot_NUM() >= ShootWarningNum )
    res = YES;
  else res = NO;
  return res;
}
bool Report_IF_BulletWarning(void)
{
  return Judge_IF_BulletWarning();
}
void Reset_BulletWarning(void)
{
  BulletWarning = NO;
}
