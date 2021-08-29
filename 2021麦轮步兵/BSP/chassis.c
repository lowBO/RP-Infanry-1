/***      �� ���̿��ƴ��� ��

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
 
#include "chassis.h"
#include "Device.h"

/* Init start */
CHAS_Info_t Chassis = {
  .ctrl_mode = Ctrl_Err,
  .pid_mode = PID_Err,
  .action_mode = ACT_Err,  
  .PID_type = Turn_off,
  .IF_SPIN_START = false,
  .IF_SPIN_CLOSING = false,
  .IF_NAN = false,
  .Speed_MAX = Car_SPEED,
  .Dir.mode = HEAD,
  .Dir.num = 1,//ͷ
};//������Ϣ�ṹ��

/* Init end   */
static System_Ctrl_Mode_t C_prev_ctrl_mode = RC_CTRL_MODE;
static PID_type_t C_prev_pid_type = Turn_off;

/* --------------------------�����------------------------- */
/**
 * @brief �����ܿ�
 * @param 
 */
void CHASSIS_Ctrl(void)
{
  if(GIM_CalOK_Report())//��̨��λ�ɹ�֮������������
  switch (Chassis.ctrl_mode)
  {
    case RC_CTRL_MODE:
      CHAS_RC_Ctrl();
      break;
    case KEY_CTRL_MODE: 
      CHAS_KET_Ctrl();
      break;
  }
  else CHAS_Stop();
}
 
/**
* @brief ������Ϣ��ȡ
* @param 
*/
void CHAS_GET_Info(void)
{
  Chassis.ctrl_mode = System.ctrl_mode;
  Chassis.pid_mode = System.pid_mode;
  Chassis.action_mode = System.action_mode;
  Chassis.PID_type = GET_PID_Type();
  Chassis.Defense_Mode = System.Defense_Mode;
  CHAS_SetPID_type();
  CHAS_Dir_Switch();//�ı���̷���
}

/**
 * @brief PID�����ȡ
 * @note  ����ͬ��
 */
void CHAS_GET_PID_Type(PID_Info_t *str )
{
  str->PID_type = Chassis.PID_type;
}
void CHAS_SetPID_type(void)
{
  CHAS_GET_PID_Type(&Chassis.CHAS_Motor[CHAS_LF].PID);
  
  CHAS_GET_PID_Type(&Chassis.CHAS_Motor[CHAS_RF].PID);
  
  CHAS_GET_PID_Type(&Chassis.CHAS_Motor[CHAS_LB].PID); 
  
  CHAS_GET_PID_Type(&Chassis.CHAS_Motor[CHAS_RB].PID);  
}


/**
* @brief ����PID�����ܺ���
* @param 
*/
void CHAS_SetPID(void)
{
  CHAS_PID_Switch(&Chassis.CHAS_Motor[CHAS_LF].PID);
  
  CHAS_PID_Switch(&Chassis.CHAS_Motor[CHAS_RF].PID);

  CHAS_PID_Switch(&Chassis.CHAS_Motor[CHAS_LB].PID);

  CHAS_PID_Switch(&Chassis.CHAS_Motor[CHAS_RB].PID);
}

/**
 * @brief PID�л�
 * @param 
 */
void CHAS_PID_Switch(PID_Info_t *str)
{
  static int length = sizeof(PID_Parameter_t);
  switch (str->PID_type)
  {
    case RC_GYRO:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][RC_GYRO],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][RC_GYRO],length);
    }break;
    
    case RC_MECH:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][RC_MECH],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][RC_MECH],length);
    }break;
    
    case KEY_GYRO:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][KEY_GYRO],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][KEY_GYRO],length);
    }break;
    
    case KEY_MECH:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][KEY_MECH],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][KEY_MECH],length);
    }break;
    
    case ACT_BIG_BUFF:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][ACT_BIG_BUFF],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][ACT_BIG_BUFF],length);
    }break;
    case ACT_SMALL_BUFF:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][ACT_SMALL_BUFF],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][ACT_SMALL_BUFF],length);
    }break;
    case ACT_AUTO_AIM:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][ACT_AUTO_AIM],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][ACT_AUTO_AIM],length);
    }break;
    
    case ACT_SPEED:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][ACT_SPEED],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][ACT_SPEED],length);
    }break;
    
    case ACT_PARK:{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][ACT_PARK],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][ACT_PARK],length);
    }break;
    
    default :{
      memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[RM_3508][Turn_off],length);
      memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[RM_3508][Turn_off],length);
    }break;      
  }
}

/**
 * @brief ����ң�ؿ���
 * @param 
 */
void CHAS_RC_Ctrl(void)
{
  if(C_prev_ctrl_mode != Chassis.ctrl_mode)
  {/* ��һ�ν���RCģʽ */
    C_prev_ctrl_mode = Chassis.ctrl_mode;
    /*�������*/
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LB].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RB].PID); 
    RM_3508_Init();
    SPIN_Reset();//��λС����
  }
  switch (Chassis.IF_SPIN_START)
  {
    case false:
      CHAS_Remote_Ctrl();
      break;
    case true:
      CHAS_SPIN();
      break; 
  }
}
/**
 * @brief ���̼��̿���
 * @param 
 */
void CHAS_KET_Ctrl(void)
{
  if(C_prev_ctrl_mode != Chassis.ctrl_mode)
  {/* ��һ�ν���KEYģʽ */
    C_prev_ctrl_mode = Chassis.ctrl_mode;
    /*�������*/
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LB].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RB].PID); 
    RM_3508_Init();
    SPIN_Reset();//��λС����
  }
  switch (Chassis.IF_SPIN_START)
  {
    case false:
      CHAS_Keyboard_Ctrl();
      break;
    case true:
      CHAS_SPIN();
      break; 
  }
}
/**
 * @brief ���ϵͳ�л���������
 * @param 
 */
void CHAS_Dir_HEAD(void)
{
  Chassis.Dir.mode = HEAD;
}
void CHAS_Dir_TAIL(void)
{
  Chassis.Dir.mode = TAIL;
}
void CHAS_Dir_Switch(void)
{
  Judge_DIR();//�жϵ���ͷ�ķ���
  switch(Chassis.Dir.mode)
  {
    case HEAD:
      Chassis.Dir.num = 1;
      break;
      
    case TAIL:
      Chassis.Dir.num = -1;
      break;
  }
}
Dir_t CHAS_Dir_Report(void)
{
  return Chassis.Dir.mode;
}
/* ���� �����Ƿ�Ϊͷ��ǰ */
/* ����ctrl�����̸�λΪͷ��ǰ */
bool Judge_IF_CHAS_HeadF(void)
{
  bool res = YES;
  if(CHAS_Dir_Report() != HEAD)
    res = NO;
  return res;
}

/* --------------------------���Ʋ�------------------------- */
/**
 * @brief ң�ؿ���
 * @param 
 */
void CHAS_Remote_Ctrl(void)
{
  float kZ_Adapt = 0;
  switch(Chassis.PID_type)
  {
    case RC_MECH:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν����еģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.RC_Move.FB_Speed_k = RC_CHAS_MECH_FB_k;
          Chassis.RC_Move.LR_Speed_k = RC_CHAS_MECH_LR_k;
          Chassis.RC_Move.Z_Speed_k  = RC_CHAS_MECH_Z_k;
        }
        /*�����˶����ƽ���*/
        Chassis.RC_Move.FB_Speed = Chassis.RC_Move.FB_Speed_k * RC_CH3 * Chassis.Dir.num;
        Chassis.RC_Move.LR_Speed = Chassis.RC_Move.LR_Speed_k * RC_CH2 * Chassis.Dir.num;
        Chassis.RC_Move.Z_Speed  = Chassis.RC_Move.Z_Speed_k  * RC_CH0;    
    break;
        
    case RC_GYRO:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν���������ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.RC_Move.FB_Speed_k = RC_CHAS_GYRO_FB_k;//11*660 = 7260
          Chassis.RC_Move.LR_Speed_k = RC_CHAS_GYRO_LR_k;
          Chassis.RC_Move.Z_Speed_k  = RC_CHAS_GYRO_Z_k;   //3*700 = 2100
        }
        /*�����˶����ƽ���*/
        Chassis.RC_Move.FB_Speed = Chassis.RC_Move.FB_Speed_k * RC_CH3 * Chassis.Dir.num;
        Chassis.RC_Move.LR_Speed = Chassis.RC_Move.LR_Speed_k * RC_CH2 * Chassis.Dir.num;
        //Z���ٶ�����̨����
        Chassis.RC_Move.Z_Speed = Chassis.RC_Move.Z_Speed_k * CHAS_Get_Z_Speed(&Chassis.RC_Move);//CHAS_Get_Zerror(&Chassis.RC_Move);
    break;
        
  }
  
  /* �ٶȷ���ʱ ��תռ���� ��תҪ��ʱ */
  if(abs(Chassis.RC_Move.Z_Speed) > 0)
  {
    kZ_Adapt = (CHAS_Z_SPEED_MAX - abs(Chassis.RC_Move.Z_Speed))/CHAS_Z_SPEED_MAX;
    kZ_Adapt = kZ_Adapt * kZ_Adapt * kZ_Adapt;//4�η�
    kZ_Adapt = constrain(kZ_Adapt, 1.f, 0.f);
  } else kZ_Adapt = 1;
  Chassis.RC_Move.FB_Speed *=  kZ_Adapt;
  Chassis.RC_Move.LR_Speed *=  kZ_Adapt;
  
//  /*PID��������*/
//  PID_Debug(&Chassis.PID[CHAS_LF]);
//  PID_Debug(&Chassis.PID[CHAS_RF]);
//  PID_Debug(&Chassis.PID[CHAS_LB]);
//  PID_Debug(&Chassis.PID[CHAS_RB]);
  
  /*�����������*/
  CHAS_Handler(&Chassis.RC_Move);
}

/**
 * @brief ���̿���
 * @param 
 */
void CHAS_Keyboard_Ctrl(void)
{
  float kZ_Adapt = 0;
  float Zangle;
  Zangle = YAW_AngleErrReport();
  
  switch(Chassis.PID_type)
  {
    case KEY_MECH:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν����еģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();  
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = KEY_CHAS_MECH_FB_k;
          Chassis.Key_Move.LR_Speed_k = KEY_CHAS_MECH_LR_k;
          Chassis.Key_Move.Z_Speed_k  = KEY_CHAS_MECH_Z_k;  
          Chassis.Key_Move.Slow_Inc = 6;  
        }
        SuperCap_CHAS_K_change_MECH();
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = Chassis.Key_Move.FB_Speed_k * KEY_FB_Ctrl() * Chassis.Dir.num;
        Chassis.Key_Move.LR_Speed = Chassis.Key_Move.LR_Speed_k * KEY_LR_Ctrl() * Chassis.Dir.num;
        Chassis.Key_Move.Z_Speed  = Chassis.Key_Move.Z_Speed_k  * (Mouse_X_Speed() + Report_MECH_SlowlyTurn());   
    break;
        
    case KEY_GYRO:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν���������ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = KEY_CHAS_GYRO_FB_k;
          Chassis.Key_Move.LR_Speed_k = KEY_CHAS_GYRO_LR_k;//5
          Chassis.Key_Move.Z_Speed_k  = KEY_CHAS_GYRO_Z_k;  //3
          Chassis.Key_Move.Slow_Inc = 40;
        }
        SuperCap_CHAS_K_change_GYRO();
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = Chassis.Key_Move.FB_Speed_k * SPIN_GetSpeed_FB(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num;
        Chassis.Key_Move.LR_Speed = Chassis.Key_Move.LR_Speed_k * SPIN_GetSpeed_LR(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num;
        //Z���ٶ�����̨����
        Chassis.Key_Move.Z_Speed = Chassis.Key_Move.Z_Speed_k * CHAS_Get_Z_Speed(&Chassis.Key_Move);//CHAS_Get_Zerror(&Chassis.Key_Move);
    break;
        
    case ACT_AUTO_AIM:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν�������ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = KEY_CHAS_GYRO_FB_k;
          Chassis.Key_Move.LR_Speed_k = KEY_CHAS_GYRO_LR_k;
          Chassis.Key_Move.Z_Speed_k  = KEY_CHAS_GYRO_Z_k;  
          Chassis.Key_Move.Slow_Inc = 25;
        }
        SuperCap_CHAS_K_change_GYRO();
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = Chassis.Key_Move.FB_Speed_k * KEY_FB_Ctrl() * Chassis.Dir.num;
        Chassis.Key_Move.LR_Speed = Chassis.Key_Move.LR_Speed_k * KEY_LR_Ctrl() * Chassis.Dir.num;
        //Z���ٶ�����̨����
        Chassis.Key_Move.Z_Speed = Chassis.Key_Move.Z_Speed_k * CHAS_Get_Z_Speed(&Chassis.Key_Move);//CHAS_Get_Zerror(&Chassis.Key_Move);
        //Chassis.Key_Move.Z_Speed = 0;
    break;
        
    case ACT_SMALL_BUFF:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν���С��ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = KEY_CHAS_GYRO_FB_k;
          Chassis.Key_Move.LR_Speed_k = KEY_CHAS_GYRO_LR_k;
          Chassis.Key_Move.Z_Speed_k  = KEY_CHAS_GYRO_Z_k;  
        }
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = 0;
        Chassis.Key_Move.LR_Speed = 0;
        Chassis.Key_Move.Z_Speed = 0;
    break;
    
    case ACT_BIG_BUFF:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν�����ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = KEY_CHAS_GYRO_FB_k;
          Chassis.Key_Move.LR_Speed_k = KEY_CHAS_GYRO_LR_k;
          Chassis.Key_Move.Z_Speed_k  = KEY_CHAS_GYRO_Z_k;  
        }
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = 0;
        Chassis.Key_Move.LR_Speed = 0;
        Chassis.Key_Move.Z_Speed = 0;
    break;
        
    case ACT_PARK:
        if(C_prev_pid_type != Chassis.PID_type)
        {/* ��һ�ν��뻺��ģʽ */
          C_prev_pid_type = Chassis.PID_type;
          CHAS_SetPID();
          //�ɸĲ���
          Chassis.Key_Move.FB_Speed_k = CHAS_PARK_FB_k;
          Chassis.Key_Move.LR_Speed_k = CHAS_PARK_LR_k;
          Chassis.Key_Move.Z_Speed_k  = CHAS_PARK_Z_k;  
        }
//        /*�����˶����ƽ���*/
//        Chassis.Key_Move.FB_Speed = Chassis.Key_Move.FB_Speed_k * CHAS_Park_FB_Speed();
//        Chassis.Key_Move.LR_Speed = Chassis.Key_Move.LR_Speed_k * 0;//CHAS_Park_LR_Speed();
//        Chassis.Key_Move.Z_Speed = Chassis.Key_Move.Z_Speed_k   * CHAS_Park_Z_Speed();
        
        /*�����˶����ƽ���*/
        Chassis.Key_Move.FB_Speed = Chassis.Key_Move.FB_Speed_k * SPIN_GetSpeed_FB(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num;
        Chassis.Key_Move.LR_Speed = Chassis.Key_Move.LR_Speed_k * SPIN_GetSpeed_LR(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num;
        //Z���ٶ�����̨����
        Chassis.Key_Move.Z_Speed = Chassis.Key_Move.Z_Speed_k * CHAS_Get_Z_Speed(&Chassis.Key_Move);//CHAS_Get_Zerror(&Chassis.Key_Move);
    break;
        
  }
  
#if (Infantry == 1)
  /* �ٶȷ���ʱ ��תռ���� ��תҪ��ʱ */
  if(abs(Chassis.Key_Move.Z_Speed) > 0 && Chassis.PID_type != ACT_PARK)
  {
    kZ_Adapt = (CHAS_Z_SPEED_MAX - abs(Chassis.Key_Move.Z_Speed))/CHAS_Z_SPEED_MAX;
    kZ_Adapt = kZ_Adapt * kZ_Adapt;//2�η�
    kZ_Adapt = constrain(kZ_Adapt, 1.f, 0.f);
  } else kZ_Adapt = 1;
  Chassis.Key_Move.FB_Speed *=  kZ_Adapt;
  Chassis.Key_Move.LR_Speed *=  kZ_Adapt;
  
#elif (Infantry == 2)
  /* �ٶȷ���ʱ ��תռ���� ��תҪ��ʱ */
  if(abs(Chassis.Key_Move.Z_Speed) > 0)
  {
    kZ_Adapt = (CHAS_Z_SPEED_MAX - abs(Chassis.Key_Move.Z_Speed))/CHAS_Z_SPEED_MAX;
//    kZ_Adapt = kZ_Adapt * kZ_Adapt;//2�η�
    kZ_Adapt = constrain(kZ_Adapt, 1.f, 0.f);
  } else kZ_Adapt = 1;
  Chassis.Key_Move.FB_Speed *=  kZ_Adapt;
  Chassis.Key_Move.LR_Speed *=  kZ_Adapt;
  
#elif (Infantry == 3)
  /* �ٶȷ���ʱ ��תռ���� ��תҪ��ʱ */
  if(abs(Chassis.Key_Move.Z_Speed) > 0 && Chassis.PID_type != ACT_PARK)
  {
    kZ_Adapt = (CHAS_Z_SPEED_MAX - abs(Chassis.Key_Move.Z_Speed))/CHAS_Z_SPEED_MAX;
    kZ_Adapt = kZ_Adapt * kZ_Adapt;//2�η�
    kZ_Adapt = constrain(kZ_Adapt, 1.f, 0.f);
  } else kZ_Adapt = 1;
  Chassis.Key_Move.FB_Speed *=  kZ_Adapt;
  Chassis.Key_Move.LR_Speed *=  kZ_Adapt;
    
#endif
  
//  /*PID��������*/
//  PID_Debug(&Chassis.PID[CHAS_LF]);
//  PID_Debug(&Chassis.PID[CHAS_RF]);
//  PID_Debug(&Chassis.PID[CHAS_LB]);
//  PID_Debug(&Chassis.PID[CHAS_RB]);
  
  /*�����������*/
  CHAS_Handler(&Chassis.Key_Move);
}

/**
 * @brief ���̸�λ����
 * @param 
 */
void CHAS_Reset(void)
{
  if(C_prev_ctrl_mode != Chassis.ctrl_mode)
  {/* ��һ�ν��븴λģʽ */
    C_prev_ctrl_mode = Chassis.ctrl_mode;
    /*�������*/
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RF].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_LB].PID);
    CHAS_SetEmpty(&Chassis.CHAS_Motor[CHAS_RB].PID); 
  }
  
  if(C_prev_pid_type != Chassis.PID_type)
  {/* ��һ�ν��븴λģʽ */
    C_prev_pid_type = Chassis.PID_type;
    CHAS_SetPID();//����PID״̬    
  }
  
  CHAS_Stop();//ж��
}


/* --------------------------���ܲ�------------------------- */

/**
 * @brief �õ������ĸ�����Ľ����ٶ�Ŀ��ֵ
 * @note  ����ķ������ 
 */
//�ٶ����ӷ���
float Speed_Adapt(float FB,float LR,float Z)
{
  float res;
  float Speed_MAX = Chassis.Speed_MAX;
  
  
  float Adapt_K = 1;
  if(abs(FB)+abs(LR)+abs(Z) > Speed_MAX)
    Adapt_K = (Speed_MAX)/(abs(FB)+abs(LR)+abs(Z));
//    Adapt_K = abs(Speed_MAX/(FB+LR+Z));
  res = FB*Adapt_K  + LR*Adapt_K  + Z*Adapt_K ;
  return res;
}
//����ƫ�������㷨
float WHEELBASE   = 358  ;   //ǰ���־�
float WHEELTRACK  = 382  ;   //�����־�
float GIMBAL_X_OFFSET =  15 ;  //ǰ��ƫ��
float GIMBAL_Y_OFFSET =  6  ;    //����ƫ��
//float RADIAN_COEF 57.3f//����ƫ���㷨�Ļ���ϵ��
float FB_ro = 1,FB_k = 0.8995f;//0.898f
float LR_ro = 1,LR_k = 0.8995f;
void GravityCenterFIX_FB(void)
{
  FB_ro = FB_k *(WHEELBASE/2 + GIMBAL_X_OFFSET)/(WHEELBASE/2 - GIMBAL_X_OFFSET);
}
void GravityCenterFIX_LR(void)
{
  LR_ro = LR_k *(WHEELTRACK/2 + GIMBAL_Y_OFFSET)/(WHEELTRACK/2 - GIMBAL_Y_OFFSET);
}
//�����ٶȷ��䵽�����ٶ�
void CHAS_SetChasSpeed(CHAS_Move_t *str)
{
//  //��������ƫ������
//  GravityCenterFIX_FB();
//  GravityCenterFIX_LR();
  
  str->Motor_SpeedTarget[CHAS_LF] = Speed_Adapt(( str->FB_Speed ), \
                                                ( str->LR_Speed ), \
                                                ( str->Z_Speed  )) / FB_ro / LR_ro;
                                                  
  str->Motor_SpeedTarget[CHAS_RF] = Speed_Adapt((-str->FB_Speed ), \
                                                ( str->LR_Speed ), \
                                                ( str->Z_Speed  )) / FB_ro * LR_ro;  
  
  str->Motor_SpeedTarget[CHAS_LB] = Speed_Adapt(( str->FB_Speed ), \
                                                (-str->LR_Speed ), \
                                                ( str->Z_Speed  )) * FB_ro / LR_ro;  
  
  str->Motor_SpeedTarget[CHAS_RB] = Speed_Adapt((-str->FB_Speed ), \
                                                (-str->LR_Speed ), \
                                                ( str->Z_Speed  )) * FB_ro * LR_ro;   
}

/**
 * @brief ��MMKNM���ٶȽ��� б�·ָ��ĸ������PIDĿ��ֵ
 * @param 
 */
void CHAS_SetMotorSpeed(CHAS_Move_t *str)
{
  MotorSlow(&Chassis.CHAS_Motor[CHAS_LF].motor_data.PID_Speed_target,
       str->Motor_SpeedTarget[CHAS_LF],
       str->Slow_Inc);
  
  MotorSlow(&Chassis.CHAS_Motor[CHAS_RF].motor_data.PID_Speed_target,
       str->Motor_SpeedTarget[CHAS_RF],
       str->Slow_Inc);
  
  MotorSlow(&Chassis.CHAS_Motor[CHAS_LB].motor_data.PID_Speed_target,
       str->Motor_SpeedTarget[CHAS_LB],
       str->Slow_Inc);
  
  MotorSlow(&Chassis.CHAS_Motor[CHAS_RB].motor_data.PID_Speed_target,
       str->Motor_SpeedTarget[CHAS_RB],
       str->Slow_Inc);
}

/**
 * @brief ͬ��CAN�õ������ݺͼ�������PID���������
 * @param 
 */
void CHAS_DataSync(Motor_Data_t *str)
{
  str->PID_Speed = str->CAN_GetData.Motor_Speed;
  str->PID_Angle = str->CAN_GetData.Motor_Angle;
}

/**
 * @brief �õ�������
 * @param 
 */
float CHAS_GetOutput(CHAS_Motor_t *str)
{
  PID_Info_t *PID = &str->PID;
  Motor_Data_t *DATA = &str->motor_data;
  float res;
  
  CHAS_DataSync(DATA);//����ͬ��

//  PID->Angle_Loop.Err = CHAS_Get_AngleErr(DATA);
//  
//  DATA->PID_Speed_target = PID_Algorithm(&PID->Angle_Loop);//�ǶȻ�
  
  PID->Speed_Loop.Err = CHAS_Get_SpeedErr(DATA);
  
  res = PID_Algorithm(&PID->Speed_Loop);//�ٶȻ�
  
  return res;
}



//��һ������еĹ������ƣ�
short int power_lim_output[4] = {0};//�޹��ʺ��������

float power_error = 0;
float power_total_error = 0;
float power_P = 0.3,power_I = 0;
float power_P_output = 0,power_I_output = 0,power_PID_output = 0;
float power_limit_K = 1;
void power_limit(void)
{//�ҵĹ����㷨
  switch(IF_DUM_NORMAL)
  {
    case YES:
      power_error = 60 - DUM_Report_PowerBuffer();
      power_P = power_error * 0.055f;//��ϵ��
      power_P = power_P * power_P;//��ƽ��
      power_total_error = power_total_error + power_error;
      power_P_output = power_error*power_P;
      //.power_I_output = power_total_error * power_I;
      power_PID_output = power_P_output ;
      power_limit_K = 1 + power_PID_output;
    break;
    
    case NO:
      power_limit_K = 1;
    break;
  }
}
void CHAS_PowerLimit(CHAS_PowerLimit_t *str , int16_t *pid_out)
{//���������㷨
  PID_Loop_t *LF = &Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop;
  PID_Loop_t *RF = &Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop;
  PID_Loop_t *LB = &Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop;
  PID_Loop_t *RB = &Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop;
  
  switch(IF_DUM_NORMAL)
  {
    case YES:
        //����ϵͳ����
        str->Max_PowerBuffer = CHAS_LIMIT_POWERBUFFER;
        str->Real_PowerBuffer = DUM_Report_PowerBuffer();
        //SuperCap_Emergency(str->Real_PowerBuffer);//�������繦��
        if(str->Real_PowerBuffer >= 60)str->Real_PowerBuffer = 60;//��ֹ����֮�󻺳�250J��Ϊ������ϵ��
        str->Limit_k = str->Real_PowerBuffer / str->Max_PowerBuffer;
        if(str->Real_PowerBuffer < CHAS_Buffer_Urgent)
          str->Limit_k = str->Limit_k * str->Limit_k * str->Limit_k; //3��
        else
          str->Limit_k = str->Limit_k * str->Limit_k; //ƽ��
        
        if(str->Real_PowerBuffer < str->Max_PowerBuffer)
        str->CHAS_LimitOutput = str->Limit_k * CHAS_TOTAL_OUTPUT_MAX;
        else 
        str->CHAS_LimitOutput = CHAS_TOTAL_OUTPUT_MAX;    
        break;
    
    case NO:
        //����ϵͳ���ߣ�ǿ����Ϊԭ����1/8
        str->CHAS_LimitOutput = CHAS_TOTAL_OUTPUT_MAX / 6 ;
        break; 
  }
  str->CHAS_TotalOutput = abs(LF->PID_Output) +
                          abs(RF->PID_Output) +
                          abs(LB->PID_Output) +
                          abs(RB->PID_Output) ;
  if(str->CHAS_TotalOutput >= str->CHAS_LimitOutput)
  {
    pid_out[CHAS_LF] = (int16_t)(LF->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
    pid_out[CHAS_RF] = (int16_t)(RF->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
    pid_out[CHAS_LB] = (int16_t)(LB->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
    pid_out[CHAS_RB] = (int16_t)(RB->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
  }
}
//  /* ���·��� */
//  if( Report_SuperCap_cmd() &&  //���˳��� 
//      DUM_Report_IF_CarFly() && //ǰ�ַɳ�
//      KEY_W  &&
//      Chassis.CHAS_Motor[CHAS_LB].motor_data.PID_Speed > 2000 && 
//      Chassis.CHAS_Motor[CHAS_RB].motor_data.PID_Speed > 2000)   
//  {
//    //����ǰ����ж����������һ��ʹ�����еĹ���ȫ�����ں��֣��ú���pid�������
//    //��������ٶ�������������������������pid����������Ŀ���ٶȿ������ú��ָ�������
//    pid_out[CHAS_LF] = (int16_t)(LF->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
//    pid_out[CHAS_RF] = (int16_t)(RF->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
//    pid_out[CHAS_LB] = (int16_t)(LB->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
//    pid_out[CHAS_RB] = (int16_t)(RB->PID_Output / str->CHAS_TotalOutput * str->CHAS_LimitOutput);
//  }


//�������ʱ��ǰ����ж��
bool prev_fly = NO,wait_calm = NO;
float wait_calm_cnt = 0;
void CarFly_React(int16_t *pid_out)
{
  if(DUM_Report_IF_CarFly())
  {
    //���´���ǰ����pid�����0
    Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop.PID_Output = 0;
    Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop.PID_Output = 0;
    pid_out[CHAS_LF] = 0;
    pid_out[CHAS_RF] = 0;
    
    prev_fly = YES;//��¼����
  }
}
//�������ʱ���������С�������ⳬ���ʿ�Ѫ
void CarFly_Over_React(void)
{
  if(!DUM_Report_IF_CarFly() && prev_fly == YES)
  {
    //������½�������Ϊ�˷�ֹ��Ѫ����pid������� �ȴ�һ��ʱ��������
    wait_calm = YES;
    prev_fly = NO;
  }
  if(wait_calm == YES)
  {
    //���´���pid����޷�����
    Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop.PID_Output_Max = 8000;
    Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop.PID_Output_Max = 8000;
    Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop.PID_Output_Max = 8000;
    Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop.PID_Output_Max = 8000;
    
    wait_calm_cnt ++;
    if(wait_calm_cnt >= 500)//1s֮��
    {
      //����������޷��ָ�
      Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop.PID_Output_Max = 15000;
      Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop.PID_Output_Max = 15000;
      Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop.PID_Output_Max = 15000;
      Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop.PID_Output_Max = 15000;
      
      wait_calm_cnt = 0;//������ʼ��
      wait_calm = NO;//�侲��־λ��no���ȴ���һ�η��½�������
    }
  }
}

/**
 * @brief CHAS������
 * @note  ��������֮��
 */
int16_t LFs_js = 0,RFs_js = 0,LBs_js = 0,RBs_js = 0,LFo_js = 0,RFo_js = 0,LBo_js = 0,RBo_js = 0;
extern int16_t zigbee_CHAS_Output[4];
void CHAS_Output(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
  switch(ANCESTRAL_ALGORITHM)
  {
    case NO://���Լ��Ĳ����㷨
        /*��������*/
        power_limit(); 
        /* �ٶȻ�������� */
        pid_out[CHAS_LF] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_LF]) / power_limit_K);
        pid_out[CHAS_RF] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_RF]) / power_limit_K);
        pid_out[CHAS_LB] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_LB]) / power_limit_K);
        pid_out[CHAS_RB] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_RB]) / power_limit_K);
        break;
    
    case YES://�洫�㷨  

//        /*������ش���*/
//        CarFly_Over_React();
    
        /* �ٶȻ�������� */
        pid_out[CHAS_LF] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_LF]));
        pid_out[CHAS_RF] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_RF]));
        pid_out[CHAS_LB] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_LB]));
        pid_out[CHAS_RB] = (int16_t)(CHAS_GetOutput(&Chassis.CHAS_Motor[CHAS_RB]));
    
//        /*���´���*/
//        CarFly_React(pid_out);
    
        /*��������*/
        CHAS_PowerLimit(&Chassis.CHAS_PowerLimit , pid_out);
    
        /*Zigbee���Կ�������*/
        zigbee_CHAS_Output[CHAS_LF] = pid_out[CHAS_LF];
        zigbee_CHAS_Output[CHAS_RF] = pid_out[CHAS_RF];
        zigbee_CHAS_Output[CHAS_LB] = pid_out[CHAS_LB];
        zigbee_CHAS_Output[CHAS_RB] = pid_out[CHAS_RB];
    
        //���ݹ۲�
        LFo_js = pid_out[CHAS_LF];
        RFo_js = pid_out[CHAS_RF];
        LBo_js = pid_out[CHAS_LB];
        RBo_js = pid_out[CHAS_RB];
        LFs_js = Chassis.CHAS_Motor[CHAS_LF].motor_data.PID_Speed;
        RFs_js = Chassis.CHAS_Motor[CHAS_RF].motor_data.PID_Speed;
        LBs_js = Chassis.CHAS_Motor[CHAS_LB].motor_data.PID_Speed;
        RBs_js = Chassis.CHAS_Motor[CHAS_RB].motor_data.PID_Speed;
        break;
  }
  
  /* �ж��Ƿ����NAN */
  Chassis.IF_NAN = Judge_IF_NAN(Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop.PID_Output) |
                   Judge_IF_NAN(Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop.PID_Output) |
                   Judge_IF_NAN(Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop.PID_Output) |
                   Judge_IF_NAN(Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop.PID_Output) ;
  
  /* CAN����  */
	CAN1_Send(CHAS_ESC, pid_out);	
} 

/**
 * @brief CHAS�������
 * @param 
 */
void CHAS_Handler(CHAS_Move_t *str)
{
  /*�õ������ٶ�����*/
  CHAS_SetChasSpeed(str);
  
  /*�õ�����ٶ�����*/
  CHAS_SetMotorSpeed(str);
  
  /*������*/
  CHAS_Output();
}

/**
 * @brief ����PID����ȫ����0����
 * @param 
 */
void CHAS_SetEmpty(PID_Info_t *str)
{
  memset(&str->Speed_Loop,0,sizeof(PID_Loop_t));
  memset(&str->Angle_Loop,0,sizeof(PID_Loop_t));
}
 
/**
 * @brief ж������
 * @param 
 */
void CHAS_Stop(void)
{
	static int16_t pid_out[CHAS_MOTOR_CNT] = {0, 0, 0, 0};
	
	/* �ٶȻ�������� */
  pid_out[CHAS_LF] = 0;
  pid_out[CHAS_RF] = 0;
  pid_out[CHAS_LB] = 0;
  pid_out[CHAS_RB] = 0;
  
	CAN1_Send(CHAS_ESC, pid_out);	  
}

/**
 * @brief ��ȡ�ٶ����ͽǶ����
 * @note  �����뿨�����˲�
 */
float CHAS_Get_AngleErr(Motor_Data_t *str)
{
  float res;
  res = str->PID_Angle_target - str->PID_Angle;
  return res;
}

float CHAS_Get_SpeedErr(Motor_Data_t *str)
{
  float res;
  res = str->PID_Speed_target - str->PID_Speed;
  return res;
}
//��������
float CHAS_Get_Zerror(CHAS_Move_t *str)
{
  float res;
  //�������˲�
  res = //KalmanFilter(&str->GYRO_Move.KF_GYRO_Angle,
        YAW_AngleErrReport();
  
  //PID����
  //�˴���PID��������Ϊ���Ǻ����Ƿ���Լ���������Ϊ����ÿ������˲��ˣ����ܻ���õ�һЩ
  //���������PID�����Խ�Z_speed_k��Ϊ1
  str->GYRO_Move.GYRO_Ctrl.Angle_Loop.Err = res;
  res = PID_Algorithm(&str->GYRO_Move.GYRO_Ctrl.Angle_Loop);
  
  return res;
}
float CHAS_Get_Z_Speed(CHAS_Move_t *MOVE)
{
  float res = 0;
  float AngleErr = 0;//�Ƕ����
  float Speed_Target = 0;//�ٶ�����
  CHAS_GYRO_t *str = &MOVE->GYRO_Move;
  PID_Info_t *PID = &str->GYRO_Ctrl;
  
  /*�õ��������˲���ĽǶ����*/
  AngleErr = KalmanFilter(&str->KF_GYRO_Angle,
              YAW_AngleErrReport() + Get_CarHalfMove_Angle());//������������б���ƶ�
  
  /*��ȡ�ǶȻ��������*/
  PID->Angle_Loop.Err = AngleErr;
  
  /*�ٶȻ����� = �ǶȻ�PID���*/
  Speed_Target = PID_Algorithm(&PID->Angle_Loop);
  
  /*��ȡ�ٶȻ��������*/  //�����ٶ�ֵ�����෴���á�+��
  PID->Speed_Loop.Err = Speed_Target + DUM_Report_CHAS_IMU_YAW_Speed();
  
  /*����ֵ = �ٶȻ�PID���*/
  res = PID_Algorithm(&PID->Speed_Loop);
  
  return res;
}

float CHAS_Report_Output_LF(void)
{
  return Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop.PID_Output;
}
float CHAS_Report_Output_RF(void)
{
  return Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop.PID_Output;
}
float CHAS_Report_Output_LB(void)
{
  return Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop.PID_Output;
}
float CHAS_Report_Output_RB(void)
{
  return Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop.PID_Output;
}
float CHAS_Report_Speed_LF(void)
{
  return Chassis.CHAS_Motor[CHAS_LF].motor_data.PID_Speed;
}
float CHAS_Report_Speed_RF(void)
{
  return Chassis.CHAS_Motor[CHAS_RF].motor_data.PID_Speed;
}
float CHAS_Report_Speed_LB(void)
{
  return Chassis.CHAS_Motor[CHAS_LB].motor_data.PID_Speed;
}
float CHAS_Report_Speed_RB(void)
{
  return Chassis.CHAS_Motor[CHAS_RB].motor_data.PID_Speed;
}

/*/-------------------------------------------------------

����������
1��С����
2����Ť��
3��45��С����Ť��
4��������

--------------------------------------------------------*/
//С������------------------------------

float SPIN_GetSpeed_LR(float Angle , float FB_ctrl , float LR_ctrl)
{
  float res;
  res = arm_cos_f32(Angle*2*3.1415926f/8192.f) * LR_ctrl - arm_sin_f32(Angle*2*3.14f/8192.f) * FB_ctrl;
  return res;
}
float SPIN_GetSpeed_FB(float Angle , float FB_ctrl , float LR_ctrl)
{
  float res;
  res = arm_sin_f32(Angle*2*3.1415926f/8192.f) * LR_ctrl + arm_cos_f32(Angle*2*3.14f/8192.f) * FB_ctrl;
  return res;  
}

//}
float SPIN_Speed(void)
{
  float res = 0;

  switch((int)DUM_Report_CHAS_MaxPower())
  {
    case 45:
        res = SPIN_SPEED_50W+200;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_50W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_50W;
        break;
    case 55:
        res = SPIN_SPEED_50W-200;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_50W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_50W;
        break;
    case 60:
        res = SPIN_SPEED_60W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_60W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_60W;
        break;
    case 70:
        res = SPIN_SPEED_60W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_60W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_60W;
        break;
    case 80:
        res = SPIN_SPEED_80W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_80W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_80W;
        break;
    case 100:
        res = SPIN_SPEED_100W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_100W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_100W;
        break;
    case 120:
        res = SPIN_SPEED_120W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_120W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_120W;
        break;
    default:
        res = SPIN_SPEED_50W;
        Chassis.SPIN_Move.FB_Speed_k = SPIN_FBk_50W;
        Chassis.SPIN_Move.LR_Speed_k = SPIN_LRk_50W;
        break;
  }
  
  switch(Report_SuperCap_cmd())
  {
    case NO:
      if(!KEY_W && !KEY_S && !KEY_A && !KEY_D)
        #if (Infantry == 1 || Infantry == 3)
          res = res +150;
        #elif (Infantry == 2)
          res = res -150;
        #endif
      else 
      {
        #if (Infantry == 1 || Infantry == 3)
          res = res -50;
        #elif (Infantry == 2)
          res = res +50;
        #endif      
      }
      
      break;
     
    case YES:
      if(!KEY_W && !KEY_S && !KEY_A && !KEY_D)
      {
        if(res == SPIN_SPEED_80W || res == SPIN_SPEED_100W || res == SPIN_SPEED_120W)
          //�͹���ʱ��ֹ�����޲�ס
          res = SPIN_SPEED_SUPER;
        else{
          res = res + 1000;
        }
      }
      else 
      {
          res = res + 400;
      }
      break;
      
  }
  
  return res;
}
/**
 * @brief �����ܺ���
 * @note  ������СŤ�� ������Ϊ�������ս����ͳ�ƣ�
 */
float Js_Zangle = 0;
void CHAS_SPIN(void)
{
  float Zangle;
  
  float k_add = 0;//���˳�����С�����ƶ����

  Zangle = YAW_AngleErrReport();
  Js_Zangle = Zangle;
  switch(Chassis.ctrl_mode)
  {
    case RC_CTRL_MODE:
        /*�����˶����ƽ���*/
        Chassis.SPIN_Move.FB_Speed = Chassis.SPIN_Move.FB_Speed_k * 
                                     SPIN_GetSpeed_FB(-Zangle , (float)RC_CH3 , (float)RC_CH2) * Chassis.Dir.num; 
        Chassis.SPIN_Move.LR_Speed = Chassis.SPIN_Move.LR_Speed_k * 
                                     SPIN_GetSpeed_LR(-Zangle , (float)RC_CH3 , (float)RC_CH2) * Chassis.Dir.num;
        if(!Chassis.IF_SPIN_CLOSING) {
          //���ݿ��Ʋ����ڻ���״̬
          switch(Chassis.Defense_Mode)
          { 
            case Defense_SPIN:
                Chassis.SPIN_Move.Z_Speed = Chassis.SPIN_Move.Z_Speed_k * SPIN_Speed();
              break;
            
            case Defense_BIG_DODGE:
              break;
            
            case Defense_SMALL_DODGE:
              break;
          } 
        }
        else {
          //���ڻ���״̬
          Chassis.SPIN_Move.Z_Speed_k = 1;
          Chassis.SPIN_Move.Z_Speed = Chassis.SPIN_Move.Z_Speed_k * //Zangle;
                                      CHAS_Get_Z_Speed(&Chassis.SPIN_Move);
        }
        break;
    
    case KEY_CTRL_MODE:
        /*�����˶����ƽ���*/
        if(Report_SuperCap_cmd())k_add = 3;
        else k_add = 0;
    
        Chassis.SPIN_Move.FB_Speed = (Chassis.SPIN_Move.FB_Speed_k + k_add) * 
                                     SPIN_GetSpeed_FB(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num; 
        Chassis.SPIN_Move.LR_Speed = (Chassis.SPIN_Move.LR_Speed_k + k_add) * 
                                     SPIN_GetSpeed_LR(-Zangle , KEY_FB_Ctrl() , KEY_LR_Ctrl()) * Chassis.Dir.num;
        if(!Chassis.IF_SPIN_CLOSING) {
          //���ݿ��Ʋ����ڻ���״̬
          switch(Chassis.Defense_Mode)
          { 
            case Defense_SPIN:
                Chassis.SPIN_Move.Z_Speed = Chassis.SPIN_Move.Z_Speed_k * SPIN_Speed();//SPIN_SPEED;
              break;
            
            case Defense_BIG_DODGE:
                Chassis.SPIN_Move.FB_Speed += 1000 * Chassis.Dir.num; //ƫ��ת
                Chassis.SPIN_Move.Z_Speed = Chassis.SPIN_Move.Z_Speed_k * (SPIN_Speed()-500);//SPIN_SPEED;
              break;
            
            case Defense_SMALL_DODGE:
              break;
          } 
        }
        else {
          //���ڻ���״̬
          Chassis.SPIN_Move.Z_Speed_k = 1;
          Chassis.SPIN_Move.Z_Speed = Chassis.SPIN_Move.Z_Speed_k * //Zangle;
                                      CHAS_Get_Z_Speed(&Chassis.SPIN_Move);
        }
        break;
  } 
  /*�����������*/
  CHAS_Handler(&Chassis.SPIN_Move);
}

bool CHAS_SPIN_Report(void)
{ 
  return Chassis.IF_SPIN_START;
}
bool Report_IF_SPIN_CLOSING(void)
{
  return Chassis.IF_SPIN_CLOSING;
}

/**
 * @brief ����С����
 * @param 
 */
void SPIN_ON(void)
{
  if(GIM_CalOK_Report())//��ʼ��������˲���С����
  {
    SPIN_Reset();//����ʱ�����¿�С����
    //SPIN_Defense_Mode_Reset();
    Chassis.IF_SPIN_START = true;
  }
}

/**
 * @brief �ر�С����
 * @param 
 */
void SPIN_OFF(void)
{
    YAW_MECH_Mid_Angle_Proc();//���ô˺������Ծ�ͷβ����
  SPIN_Defense_Mode_Reset();
  Chassis.IF_SPIN_CLOSING = true;
}

/**
 * @brief �ж�С�����Ƿ�������
 * @param 
 */
int closing_cnt = 0;   //�����ܼ�ʱ����ʱ����ס
int Angleback_cnt = 0;   //������Ч��ʱ���ﵽʱ������ȶ�����
/* ȫ����־λ��λ */
void SPIN_Reset(void)
{
  /*���㲿�ֵĲ�����λ*/
//  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
//  Chassis.SPIN_Move.Z_Speed_k = 1.5;
  C_prev_pid_type = Turn_off;  //Ϊ��һ�ν�����ͨ������׼��
  closing_cnt = 0;             //�жϼ�ʱ��0
  Angleback_cnt = 0;           //�жϼ�ʱ��0
  Chassis.IF_SPIN_START = false;//С����δ����
  Chassis.IF_SPIN_CLOSING = false;//С����δ���йر�
}
/* �ж� */
void SPIN_CLOSING_Judge(void)
{
  if(Report_IF_SPIN_CLOSING())
  {   
    Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 18000;//2000
    if(abs(YAW_AngleErrReport()) <= 20)//��λʱ��
      Angleback_cnt++;
    closing_cnt++;//����ס��ʱ��
    if(Angleback_cnt > 60 || closing_cnt > 3000)
      //С���ݻ����ǶȲ��С�ļ�ʱ //С���ݻ������е�ʱ�䣨����ʱ�䣩
      SPIN_Reset();
  }
}

/**
 * @brief ����С���ݿ���
 * @param 
 */
void SPIN_KEY_Switch(void)
{
  switch(Chassis.IF_SPIN_START)
  {
    case true :
      SPIN_OFF();
      break;
    case false :
      SPIN_ON();
      break;
  }
}

/**
 * @brief �л����ݷ���ģʽ
 * @param 
 */
void SPIN_Defense_Mode_Switch(void)
{
  if(CHAS_SPIN_Report())
  switch(System.Defense_Mode)
  { 
    case Defense_SPIN:
      System.Defense_Mode = Defense_BIG_DODGE;
      break;
    case Defense_BIG_DODGE:
      System.Defense_Mode = Defense_SPIN;//Defense_SMALL_DODGE;
      break;
    case Defense_SMALL_DODGE:
      System.Defense_Mode = Defense_SPIN;
      break;
  }
}

void SPIN_Defense_Mode_Reset(void)
{
  System.Defense_Mode = Defense_SPIN;
}
  

//----------------------------��������--------------------------------//
/**
 * @brief �ϱ���������
 * @param 
 */
uint8_t SuperCap_cmd = 0;//�������翪��
uint8_t SuperCapUrgent_cmd = 0;//�������翪��
uint8_t Report_SuperCap_cmd(void)
{
  return (SuperCap_cmd|SuperCapUrgent_cmd);
}
void SuperCap_Emergency(float Buffer)
{
  if(Buffer < CHAS_Buffer_Urgent)
  {
    SuperCap_Urgent_ON();
  }
  else 
  {
    SuperCap_Urgent_OFF();
  }
}

/**
 * @brief ��������
 * @param 
 */
void SuperCap_KEY_ON(void)
{
  SuperCap_cmd = 1;
}
void SuperCap_Urgent_ON(void)//�������翪
{
  SuperCapUrgent_cmd = 1;
}
/**
 * @brief �رճ���
 * @param 
 */
void SuperCap_KEY_OFF(void)
{
  SuperCap_cmd = 0;
}
void SuperCap_Urgent_OFF(void)//���������
{
  SuperCapUrgent_cmd = 0;
}
void SuperCap_CHAS_K_change_GYRO(void)
{
  if(Report_SuperCap_cmd())
  {
    Chassis.Key_Move.FB_Speed_k = SUP_CHAS_GYRO_FB_k;
    Chassis.Key_Move.LR_Speed_k = SUP_CHAS_GYRO_LR_k;
    Chassis.Key_Move.Z_Speed_k = SUP_CHAS_GYRO_Z_k;
  }
  else
  {
    Chassis.Key_Move.FB_Speed_k = KEY_CHAS_GYRO_FB_k;
    Chassis.Key_Move.LR_Speed_k = KEY_CHAS_GYRO_LR_k;
    Chassis.Key_Move.Z_Speed_k = KEY_CHAS_GYRO_Z_k;
  }
}
void SuperCap_CHAS_K_change_MECH(void)
{
  if(Report_SuperCap_cmd())
  {
    Chassis.Key_Move.FB_Speed_k = SUP_CHAS_MECH_FB_k;
    Chassis.Key_Move.LR_Speed_k = SUP_CHAS_MECH_LR_k;
    Chassis.Key_Move.Z_Speed_k = SUP_CHAS_MECH_Z_k;
  }
  else
  {
    Chassis.Key_Move.FB_Speed_k = KEY_CHAS_MECH_FB_k;
    Chassis.Key_Move.LR_Speed_k = KEY_CHAS_MECH_LR_k;
    Chassis.Key_Move.Z_Speed_k = KEY_CHAS_MECH_Z_k;
  }
}


/**
 * @brief �ϱ��Ƿ����NAN
 * @param 
 */
bool CHAS_Report_IF_NAN(void)
{
  return Chassis.IF_NAN;
}
