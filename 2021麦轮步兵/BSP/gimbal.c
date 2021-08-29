/***      �� ��̨���ƴ��� ��

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
 
#include "gimbal.h"
#include "Device.h"
#include "Function.h"

/* Init start */
GIM_Info_t Gimbal = {
  .ctrl_mode = Ctrl_Err,
  .pid_mode = PID_Err,
  .action_mode = ACT_Err,
  .PID_type = Turn_off,
  .GIM_Cal_state = NO_Cal,
  .IF_CALIBRATE_OK = NO,
  .IF_NAN = false,
  .YAW.MECH_Mid_Angle = YAW_MOTOR_MID_ANGLE,
  .PIT.MECH_Mid_Angle = PIT_MOTOR_MID_ANGLE,
};//��̨��Ϣ�ṹ��

/* Init end   */
static System_Ctrl_Mode_t G_prev_ctrl_mode = Ctrl_Err;
static PID_type_t G_prev_pid_type = Turn_off;
static PID_type_t YAW_prev_pid_type = Turn_off;
static PID_type_t PIT_prev_pid_type = Turn_off;
/* --------------------------�����------------------------- */
/**
 * @brief ��̨�ܿ�
 * @param 
 */
void GIMBAL_Ctrl(void)
{
  if(IF_IMU_InitOver())//IMU��ʼ�����֮���ٿ�����̨
  switch (Gimbal.ctrl_mode)
  {
    case RC_CTRL_MODE:
      GIM_RC_Ctrl();
      break;
    case KEY_CTRL_MODE: 
      GIM_KET_Ctrl();
      break;
  }
}

/**
 * @brief ��̨��Ϣ��ȡ
 * @param 
 */
void GIM_GET_Info(void)
{
  Gimbal.ctrl_mode = System.ctrl_mode;
  Gimbal.pid_mode = System.pid_mode;
  Gimbal.action_mode = System.action_mode;
  Gimbal.PID_type = GET_PID_Type();
  Gimbal.Defense_Mode = System.Defense_Mode;
  IMU_Data_Report();
  Judge_IF_TurnOver();
  SystemSet_IF_CarHalfMove();//�����ж�����б���ƶ�ʱ�ĳ���
}

/**
 * @brief PID�����ȡ
 * @param 
 */
void GIM_GET_PID_Type(AXIS_Info_t *strAxis)
{
  strAxis->PID.PID_type = Gimbal.PID_type;
}
void GIM_AXIS_SetPID_type(void)
{
  GIM_GET_PID_Type(&Gimbal.YAW);
  
  GIM_GET_PID_Type(&Gimbal.PIT);    
}

/**
 * @brief ��̨PID�����ܺ���
 * @param 
 */
void GIM_SetPID(void)
{
  GIM_AXIS_SetPID_type();
  
  GIM_PID_Switch(&Gimbal.YAW);

  GIM_PID_Switch(&Gimbal.PIT); 
}
/**
 * @brief PID�л�
          yaw��pitch
 * @param ԭ�棺Motor_Data_t *str , Motor_Info_t *strx
          �°棺AXIS_Info_t
 */
void GIM_PID_Switch(AXIS_Info_t *strAxis)
{
  PID_Info_t *str = &(strAxis->PID);
  Motor_Info_t *strx = &(strAxis->motor_info);
  static int length = sizeof(PID_Parameter_t);
  switch(strx->motor_type)
  {
    case GM_6020_YAW:  
      switch (str->PID_type)
      {
        case RC_GYRO:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][RC_GYRO],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][RC_GYRO],length);
        }break;
        
        case RC_MECH:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][RC_MECH],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][RC_MECH],length);
        }break;
        
        case KEY_GYRO:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][KEY_GYRO],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][KEY_GYRO],length);
        }break;
        
        case KEY_MECH:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][KEY_MECH],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][KEY_MECH],length);
        }break;
        
        case ACT_BIG_BUFF:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][ACT_BIG_BUFF],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][ACT_BIG_BUFF],length);
        }break;
        case ACT_SMALL_BUFF:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][ACT_SMALL_BUFF],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][ACT_SMALL_BUFF],length);
        }break;
        case ACT_AUTO_AIM:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][ACT_AUTO_AIM],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][ACT_AUTO_AIM],length);
        }break;
        
        case ACT_SPEED:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][ACT_SPEED],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][ACT_SPEED],length);
        }break;
        
        case ACT_PARK:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][ACT_PARK],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][ACT_PARK],length);
        }break;
        
        default :{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_YAW][Turn_off],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_YAW][Turn_off],length);
        }break;      
      }break;
    case GM_6020_PIT:
      switch (str->PID_type)
      {
        case RC_GYRO:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][RC_GYRO],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][RC_GYRO],length);
        }break;
        
        case RC_MECH:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][RC_MECH],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][RC_MECH],length);
        }break;
        
        case KEY_GYRO:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][KEY_GYRO],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][KEY_GYRO],length);
        }break;
        
        case KEY_MECH:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][KEY_MECH],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][KEY_MECH],length);
        }break;
        
        case ACT_BIG_BUFF:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][ACT_BIG_BUFF],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][ACT_BIG_BUFF],length);
        }break;
        case ACT_SMALL_BUFF:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][ACT_SMALL_BUFF],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][ACT_SMALL_BUFF],length);
        }break;
        case ACT_AUTO_AIM:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][ACT_AUTO_AIM],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][ACT_AUTO_AIM],length);
        }break;
        
        case ACT_SPEED:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][ACT_SPEED],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][ACT_SPEED],length);
        }break;
        
        case ACT_PARK:{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][ACT_PARK],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][ACT_PARK],length);
        }break;

        default :{
          memcpy(&(str->Speed_Loop.PID_Param),&PID_Speed_Param[GM_6020_PIT][Turn_off],length);
          memcpy(&(str->Angle_Loop.PID_Param),&PID_Angle_Param[GM_6020_PIT][Turn_off],length);
        }break;      
      }break;
  }
}

/**
 * @brief ��̨ң�ؿ���
 * @param 
 */
void GIM_RC_Ctrl(void)
{
  if(G_prev_ctrl_mode != Gimbal.ctrl_mode)
  {/* ��һ�ν���RCģʽ */
    G_prev_ctrl_mode = Gimbal.ctrl_mode;
    Start_GIM_Calibrate();
  }
  switch(Gimbal.IF_CALIBRATE_OK)
  {
    case true :
      GIM_Remote_Ctrl();
      break;
    case false :
      GIM_Calibrate();
      break;
  }
}
/**
 * @brief ��̨���̿���
 * @param 
 */
void GIM_KET_Ctrl(void)
{
  if(G_prev_ctrl_mode != Gimbal.ctrl_mode)
  {/* ��һ�ν���KEYģʽ */
    G_prev_ctrl_mode = Gimbal.ctrl_mode;
    Start_GIM_Calibrate();
  }
  switch(Gimbal.IF_CALIBRATE_OK)
  {
    case true :
      GIM_Keyboard_Ctrl();
      break;
    case false :
      GIM_Calibrate();
      break;
  }
}

/**
 * @brief ���ϵͳ�Ĺ����л�����
 * @param 
 */
void GIM_Function_Switch(void)
{
  switch(Gimbal.ctrl_mode)
  {
    case RC_CTRL_MODE:
      break;
      
    case KEY_CTRL_MODE:
      break;
  }
}





/* --------------------------���Ʋ�------------------------- */
/*-----------------------��ģʽ�Ŀ�����--------------------------*/
/**
 * @brief ����������ģʽ��ͷ����Ҫ��ǰ����̫��
 * @param 
 */
void RC_GYRO_AngleLimit(AXIS_Info_t *str)
{
  if(abs(YAW_AngleErrReport()) > 1000)
   str->motor_data.PID_Angle_target -= str->RC_Move.AXIS_Angle_Inc ;
}
/**
 * @brief GIM_YAW��Ŀ��� ң����ң��ģʽ
 * @param 
 */
void Remote_Ctrl_YAW(AXIS_Info_t *str)
{
//  /*PID��������*/
//  PID_Debug(&str->PID);

  switch(str->PID.PID_type)
  { 
    case RC_GYRO:
      if(YAW_prev_pid_type != Gimbal.PID_type)
      {/* ��һ�ν���ģʽ */
        YAW_prev_pid_type = Gimbal.PID_type;
        
        GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
      }
      /*��̨�˶����ƽ���*/
      str->RC_Move.AXIS_Angle_Inc = str->RC_Move.AXIS_Angle_k * (-RC_CH0);
     
      /*��̨����ֵ��ȡ*/
      str->motor_data.PID_Angle_target += str->RC_Move.AXIS_Angle_Inc;
      
//      //������С����ģʽ����г�ǰ�Ƕ�����
//      if(!CHAS_SPIN_Report())RC_GYRO_AngleLimit(str);
    
      /*ͬ��������ģʽYAW����*/
      GIM_YawDataSync_GYRO(&str->motor_data);
    break;
        
    case RC_MECH:
      if(YAW_prev_pid_type != Gimbal.PID_type)
      {/* ��һ�ν���ģʽ */
        YAW_prev_pid_type = Gimbal.PID_type;
        
        GIM_MECH_FirstYawAngle(&Gimbal.YAW);
      }
      
      /*��̨�˶����ƽ���*/     
      str->RC_Move.AXIS_Angle_Inc = str-> MECH_Mid_Angle ;
    
      /*��̨����ֵ��ȡ*/
      str->motor_data.PID_Angle_target = str->RC_Move.AXIS_Angle_Inc;
    
      /*ͬ��������ģʽYAW����*/    
      GIM_YawDataSync_MECH(&str->motor_data);        
    break;
  }
}

/**
 * @brief GIM_PIT��Ŀ��� ң����ң��ģʽ
 * @param 
 */
void Remote_Ctrl_PIT(AXIS_Info_t *str)
{
  if(PIT_prev_pid_type != Gimbal.PID_type)
  {/* ��һ�ν���ģʽ */
    PIT_prev_pid_type = Gimbal.PID_type;
    
    GIM_FirstPitAngle(&Gimbal.PIT);
  }
  
//  /*PID��������*/
//  PID_Debug(&str->PID); 
  
  /*��̨�˶����ƽ���*/
  str->RC_Move.AXIS_Angle_Inc = str->RC_Move.AXIS_Angle_k * (-RC_CH1);

  /*��̨����ֵ��ȡ*/
  str->motor_data.PID_Angle_target = \
  constrain(str->motor_data.PID_Angle_target + str->RC_Move.AXIS_Angle_Inc,
            PIT_MOTOR_MAX_ANGLE,
            PIT_MOTOR_MIN_ANGLE); 
 
  /*ͬ��������ģʽPITCH����*/
  GIM_PitchDataSync(&str->motor_data);
}

/**
 * @brief GIM �ܿ��� ң����ң��ģʽ
 * @param 
 */
void GIM_Remote_Ctrl(void)
{  
  if(CHAS_SPIN_Report())
    //ң��С����ģʽ->�޶���̨�˶�Ϊ������ģʽ
    Gimbal.PID_type = RC_GYRO;
  
  if(G_prev_pid_type != Gimbal.PID_type)
  {/* ��һ�ν���ģʽ */
    G_prev_pid_type = Gimbal.PID_type;
    
    GIM_SetPID();
    GM_6020_Init();
    
  }  
  Remote_Ctrl_YAW(&Gimbal.YAW);
  Remote_Ctrl_PIT(&Gimbal.PIT);
  
  /*��̨���*/
  GIM_Output();
}


//��ͨ���̿�����-------------------
/**
 * @brief GIM_YAW��Ŀ��� ����ģʽ
 * @param 
 */
void Keyboard_Ctrl_YAW(AXIS_Info_t *str)
{
//  /*PID��������*/
//  PID_Debug(&str->PID);
  
  switch(str->PID.PID_type)
  { 
    case KEY_GYRO:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data);  
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * Mouse_X_Speed();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target += str->Key_Move.AXIS_Angle_Inc;
        break;
    
    case KEY_MECH:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstYawAngle(&Gimbal.YAW);
//          
//          SPIN_OFF();//�ر�С����
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_MECH(&str->motor_data);  
        
        /*��̨�˶����ƽ���*/      
        str->Key_Move.AXIS_Angle_Inc = str-> MECH_Mid_Angle;
      
        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = str->Key_Move.AXIS_Angle_Inc;
        break;
    
    case ACT_AUTO_AIM:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        } 
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data); 
        

        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = AutoAimYaw_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = str->motor_data.PID_Angle + \
                                           str->Key_Move.AXIS_Angle_Inc;
        break;
      
    case ACT_SMALL_BUFF:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data);  
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = BuffAimYaw_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = str->motor_data.PID_Angle + \
                                           str->Key_Move.AXIS_Angle_Inc;
        break;
      
    case ACT_BIG_BUFF:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data);  
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = BuffAimYaw_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = str->motor_data.PID_Angle + \
                                           str->Key_Move.AXIS_Angle_Inc;
        break;
        
        
    case ACT_PARK:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data);  
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * (Mouse_X_Speed() + Report_MECH_SlowlyTurn());

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target += str->Key_Move.AXIS_Angle_Inc;
        break;

    default:
        if(YAW_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          YAW_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstYawAngle(&Gimbal.YAW);
        }
        /*ͬ��������ģʽYAW����*/
        GIM_YawDataSync_GYRO(&str->motor_data);  

        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * Mouse_X_Speed();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target += str->Key_Move.AXIS_Angle_Inc;
        break;
  }
}

/**
 * @brief GIM_PIT��Ŀ��� ����ģʽ
 * @param 
 */
void Keyboard_Ctrl_PIT(AXIS_Info_t *str)
{
//  /*PID��������*/
//  PID_Debug(&str->PID); 
  
  
  switch(str->PID.PID_type)
  {      
    case ACT_AUTO_AIM:
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstPitAngle(&Gimbal.PIT);
          
          if(Report_IF_ShoorSentry())
            Gim_Sentry_UP();//���ڱ��Ŀ���̧ͷ
        } 
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync(&str->motor_data); 
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = AutoAimPit_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle + str->Key_Move.AXIS_Angle_Inc,
                  PIT_MOTOR_MAX_ANGLE,
                  PIT_MOTOR_MIN_ANGLE);  
        break;
 
    case ACT_SMALL_BUFF:
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstPitAngle(&Gimbal.PIT);
        } 
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync(&str->motor_data); 
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = BuffAimPit_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle - str->Key_Move.AXIS_Angle_Inc,
                  PIT_MOTOR_MAX_ANGLE,
                  PIT_MOTOR_MIN_ANGLE);  
        break;
    
    case ACT_BIG_BUFF:
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstPitAngle(&Gimbal.PIT);
        } 
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync(&str->motor_data); 
        
        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = BuffAimPit_Ctrl();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle - str->Key_Move.AXIS_Angle_Inc,
                  PIT_MOTOR_MAX_ANGLE,
                  PIT_MOTOR_MIN_ANGLE);  
        break;
    
    case KEY_GYRO:
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstPitAngle(&Gimbal.PIT);
        }
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync(&str->motor_data);

        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * Mouse_Y_Speed();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle_target + str->Key_Move.AXIS_Angle_Inc,
                  PIT_MOTOR_MAX_ANGLE,
                  PIT_MOTOR_MIN_ANGLE);
        break;
        
    case ACT_PARK:
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_MECH_FirstPitAngle(&Gimbal.PIT);
        }
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync(&str->motor_data);

        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * Mouse_Y_Speed();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle_target + str->Key_Move.AXIS_Angle_Inc,
                  PIT_MOTOR_MAX_ANGLE,
                  PIT_MOTOR_MIN_ANGLE);
        break;
    
    
    default ://��еģʽ
        if(PIT_prev_pid_type != Gimbal.PID_type)
        {/* ��һ�ν���ģʽ */
          PIT_prev_pid_type = Gimbal.PID_type;
          
          GIM_GYRO_FirstPitAngle(&Gimbal.PIT);
        }
        /*ͬ��������ģʽPITCH����*/
        GIM_PitchDataSync_GYRO(&str->motor_data);

        /*��̨�˶����ƽ���*/
        str->Key_Move.AXIS_Angle_Inc = str->Key_Move.AXIS_Angle_k * Mouse_Y_Speed();

        /*��̨����ֵ��ȡ*/
        str->motor_data.PID_Angle_target = \
        constrain(str->motor_data.PID_Angle_target + str->Key_Move.AXIS_Angle_Inc,
                  PIT_IMU_MAX_ANGLE,
                  PIT_IMU_MIN_ANGLE);
        break;
  }
}

/**
 * @brief GIM �ܿ��� ����ģʽ
 * @param 
 */
void GIM_Keyboard_Ctrl(void)
{
  if(G_prev_pid_type != Gimbal.PID_type)
  {/* ��һ�ν���������ģʽ */
    G_prev_pid_type = Gimbal.PID_type;
    GIM_SetPID();    
  }
  Keyboard_Ctrl_YAW(&Gimbal.YAW);
  Keyboard_Ctrl_PIT(&Gimbal.PIT);
  
  /*��̨���*/
  GIM_Output();
}


/**
 * @brief ��̨��λ����
 * @param 
 */
void GIM_Reset(void)
{
  if(G_prev_ctrl_mode != Gimbal.ctrl_mode)
  {/* ��һ�ν��븴λģʽ */
    G_prev_ctrl_mode = Gimbal.ctrl_mode;
    /*�������*/
    GIM_SetEmpty(&Gimbal.YAW.PID);
    GIM_SetEmpty(&Gimbal.PIT.PID);
  }
  
  if(G_prev_pid_type != Gimbal.PID_type)
  {/* ��һ�ν��븴λģʽ */
    G_prev_pid_type = Gimbal.PID_type;
    YAW_prev_pid_type = Gimbal.PID_type;
    PIT_prev_pid_type = Gimbal.PID_type;
    GIM_SetPID();//����PID״̬
  }
  
  GIM_Stop();//ж��
}





/* --------------------------���ܲ�------------------------- */
//PID���������---------------
/**
 * @brief ��YAW����ǶȽ��д���
 * @note  �� ��еģʽ�������ǵ��̸��桢С���ݻ��� ���õ���yaw����Ƕ�
          �����д����˴����൱�ھͽ�����
 */
float YAW_MotorAngle_Proc(int16_t Angle)
{
  if(Angle < Gimbal.YAW.MECH_Mid_Angle - Motor_180)
    Angle += Motor_360;
  if(Angle > Gimbal.YAW.MECH_Mid_Angle + Motor_180)
    Angle -= Motor_360;   

  return (float)Angle;
}
float PIT_MotorAngle_Proc(int16_t Angle)
{
  if(Angle < Gimbal.PIT.MECH_Mid_Angle - Motor_180)
    Angle += Motor_360;
  if(Angle > Gimbal.PIT.MECH_Mid_Angle + Motor_180)
    Angle -= Motor_360;   

  return (float)Angle;
}

float YAW_IMUAngle_Proc(float Angle)
{
  if(Angle < Gimbal.YAW.motor_data.PID_Angle_target - IMU_180)
    Angle += IMU_360;
  if(Angle > Gimbal.YAW.motor_data.PID_Angle_target + IMU_180)
    Angle -= IMU_360;   

  return (float)Angle;
}


/**
 * @brief ͬ��IMU�õ������ݺͼ�������PID���������
 *        ������ģʽ YAW
 */
void GIM_YawDataSync_GYRO(Motor_Data_t *str)
{
  str->PID_Speed = str->IMU_GetData.IMU_Speed;
//  str->PID_Angle = str->IMU_GetData.IMU_Angle;//������ģʽ�޷������
  str->PID_Angle = YAW_IMUAngle_Proc(str->IMU_GetData.IMU_Angle);
}

/**
 * @brief ͬ��IMU��CAN�õ������ݺͼ�������PID���������
 *        ��еģʽ YAW
 */
void GIM_YawDataSync_MECH(Motor_Data_t *str)
{
  str->PID_Speed = str->IMU_GetData.IMU_Speed;
  str->PID_Angle = YAW_MotorAngle_Proc(str->CAN_GetData.Motor_Angle);
}

/**
 * @brief ͬ��CAN�õ������ݺͼ�������PID���������
 *        ������ģʽ�ͻ�еģʽ��PITCH
 */
void GIM_PitchDataSync(Motor_Data_t *str)
{
  str->PID_Speed = str->IMU_GetData.IMU_Speed;
  str->PID_Angle = PIT_MotorAngle_Proc(str->CAN_GetData.Motor_Angle);
}

void GIM_PitchDataSync_GYRO(Motor_Data_t *str)
{
  str->PID_Speed = str->IMU_GetData.IMU_Speed;
  str->PID_Angle = str->IMU_GetData.IMU_Angle;
}

/**
 * @brief ��ȡ����PID���
 * @param 
 */
float GIM_GetOutput(AXIS_Info_t *str)
{
  PID_Info_t *PID = &(str->PID);
  Motor_Data_t *DATA = &(str->motor_data);
  float res;
 
  /*��ȡ�ǶȻ��������*/
  PID->Angle_Loop.Err = GIM_Get_AngleErr(str);
  
  /*�ٶȻ����� = �ǶȻ�PID���*/
  DATA->PID_Speed_target = PID_Algorithm(&PID->Angle_Loop);

  /*��ȡ�ٶȻ��������*/  
  PID->Speed_Loop.Err = GIM_Get_SpeedErr(str);
  
  /*����ֵ = �ٶȻ�PID���*/
  res = PID_Algorithm(&PID->Speed_Loop);
  
  return res;
}


/**
 * @brief GIM����������
 * @param 
 */
extern int16_t zigbee_GIM_Output[2];
void GIM_Output(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
	
	/* �ٶȻ�������� */
  pid_out[GIM_YAW] = (int16_t)GIM_GetOutput(&Gimbal.YAW);
  pid_out[GIM_PIT] = (int16_t)GIM_GetOutput(&Gimbal.PIT);
  
  /* �ж��Ƿ����NAN */
  Gimbal.IF_NAN = Judge_IF_NAN(Gimbal.YAW.PID.Speed_Loop.PID_Output) |
                  Judge_IF_NAN(Gimbal.PIT.PID.Speed_Loop.PID_Output);

  /* CAN���� */
	CAN1_Send(GIM_ESC, pid_out);	
  
  /*zigbee ������*/
  zigbee_GIM_Output[GIM_YAW] = pid_out[GIM_YAW];
  zigbee_GIM_Output[GIM_PIT] = pid_out[GIM_PIT];
}
  



//-----------------------------------------
  
//����������----%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/**
 * @brief ��������
 * @param 
 */
void Start_GIM_Calibrate(void)
{
  Gimbal.IF_CALIBRATE_OK = false;
  GIM_Cal_StateSync(NO_Cal);
//  SPIN_Reset();//��λС����
}

/**
 * @brief Yaw��������
 * @param 
 */
void GIM_YAW_Calibrate(AXIS_Info_t *str)
{
  /*�����ٶȿ��ƣ��Ƕȱ仯��Ԫ�Ĵ�С*/
  str->PID.Angle_Loop.PID_Err_Max = Yaw_CalErrLimit;
  
  /*����YAW��Ƕ�Ŀ��Ϊ��е��ֵ*/
  str->motor_data.PID_Angle_target = str->MECH_Mid_Angle;
  
  /*ͬ��������ģʽYAW����*/    
  GIM_YawDataSync_MECH(&str->motor_data);
}

/**
 * @brief Pitch��������
 * @param 
 */
void GIM_PIT_Calibrate(AXIS_Info_t *str)
{
  /*�����ٶȿ��ƣ��Ƕȱ仯��Ԫ�Ĵ�С*/
  str->PID.Angle_Loop.PID_Err_Max = Yaw_CalErrLimit;
  
  /*����PITCH��Ƕ�Ŀ��Ϊ��е��ֵ*/
  str->motor_data.PID_Angle_target = str->MECH_Mid_Angle;
  
  /*ͬ��������ģʽPITCH����*/    
  GIM_PitchDataSync(&str->motor_data);  
}

/**
 * @brief �жϻ���״̬
 * @param 
 */
void GIM_Calibrate_state(void)
{
  AXIS_Info_t *YAW = &(Gimbal.YAW),*PIT = &(Gimbal.PIT);
  
  //yaw�ж�
  if(abs(YAW_AngleErrReport()) <= Calibrate_AngleErr)
    YAW->Calibrate_Info.OK_cnt++;
  else
    YAW->Calibrate_Info.ING_cnt++;
  if(YAW->Calibrate_Info.ING_cnt > GIM_Calibrate_CNT ||
     YAW->Calibrate_Info.OK_cnt > GIM_CalibrateOK_CNT)
    //����ʱ�������������
    YAW->Calibrate_Info.State = Cal_OK;
    
  //pitch�ж� 
  if(abs(PIT_AngleErrReport()) <= Calibrate_AngleErr)
    PIT->Calibrate_Info.OK_cnt++;
  else 
    PIT->Calibrate_Info.ING_cnt++;
  if(PIT->Calibrate_Info.ING_cnt > GIM_Calibrate_CNT ||
     PIT->Calibrate_Info.OK_cnt > GIM_CalibrateOK_CNT)
    //����ʱ�������������
    PIT->Calibrate_Info.State = Cal_OK;  
  
  if(YAW->Calibrate_Info.State == Cal_OK &&
     PIT->Calibrate_Info.State == Cal_OK)
    //������ɣ����ñ�־λ
    {  
      Gimbal.IF_CALIBRATE_OK = true;
      Gimbal.GIM_Cal_state = Cal_OK;
    }
  
  if(Gimbal.IF_CALIBRATE_OK == true)
  {
    //������ɣ�������ݸĻ�ȥ
    GM_6020_Init();    
  }
}

/**
 * @brief ͬ����̨����״̬��Ϣ
 * @param 
 */
void GIM_Cal_StateSync(Calibrate_State_t state)
{
  Gimbal.GIM_Cal_state = state;
  Gimbal.YAW.Calibrate_Info.State = Gimbal.GIM_Cal_state;
  Gimbal.PIT.Calibrate_Info.State = Gimbal.GIM_Cal_state;
}

/**
 * @brief �����ܺ���
 * @param 
 */
void GIM_Calibrate(void)
{
  if(Gimbal.GIM_Cal_state == NO_Cal)
  {/* ��һ�ν���ģʽ */ /*�������û�еģʽ*/
    GIM_Cal_StateSync(Calibrating);
    
    Gimbal.PID_type = RC_MECH;//��еģʽ
    GIM_AXIS_SetPID_type();
    GIM_SetPID();
    GM_6020_Init();
    memset(&Gimbal.YAW.Calibrate_Info,0,sizeof(Calibrate_Info_t));
    memset(&Gimbal.PIT.Calibrate_Info,0,sizeof(Calibrate_Info_t));   
  #if (Infantry != 2)
    YAW_MECH_Mid_Angle_Proc();//���ô˺������Ծ�ͷβ����
  #endif    
  }    
  
  GIM_YAW_Calibrate(&Gimbal.YAW);
  GIM_PIT_Calibrate(&Gimbal.PIT);

  /*��̨���*/
  GIM_Output(); 

  //������״̬
  GIM_Calibrate_state();
}

bool GIM_CalOK_Report(void)
{
  return Gimbal.IF_CALIBRATE_OK;
}

//--------------------------------------

//---------------------����ת����-------------------
/* -----------------------��������------------------------------ */
/**
 * @brief �Ƕ������ı�
 * @param 
 */
void TurnLeft_90(void)
{
  if(GIM_CalOK_Report())//������ɺ�
  if(Gimbal.pid_mode == GYRO)//ֻ��������ģʽ��
  if(Gimbal.Turn_Info.Left.IF_Turn_90 == false)
  {
    TurnRighReset();//��ת����ת��λ
    Gimbal.YAW.motor_data.PID_Angle_target += Turn_90;//2048; 
    Gimbal.Turn_Info.Left.IF_Turn_90 = true;
  }
}
void TurnRigh_90(void)
{
  if(GIM_CalOK_Report())//������ɺ�
  if(Gimbal.pid_mode == GYRO)//ֻ��������ģʽ��
  if(Gimbal.Turn_Info.Righ.IF_Turn_90 == false)
  {
    TurnLeftReset();//��ת����ת��λ
    Gimbal.YAW.motor_data.PID_Angle_target -= Turn_90;//2048; 
    Gimbal.Turn_Info.Righ.IF_Turn_90 = true;
  }
}
void TurnLeft_180(void)
{
  if(GIM_CalOK_Report())//������ɺ�
  if(Gimbal.pid_mode == GYRO)//ֻ��������ģʽ��
  if(Gimbal.Turn_Info.Left.IF_Turn_180 == false)
  {
    TurnRighReset();//��ת����ת��λ
    Gimbal.YAW.motor_data.PID_Angle_target += Turn_180-100;//4096;
    Gimbal.Turn_Info.Left.IF_Turn_180 = true;
  }
}
void TurnRigh_180(void)
{
  if(GIM_CalOK_Report())//������ɺ�
  if(Gimbal.pid_mode == GYRO)//ֻ��������ģʽ��
  if(Gimbal.Turn_Info.Righ.IF_Turn_180 == false)
  {
    TurnLeftReset();//��ת����ת��λ
    Gimbal.YAW.motor_data.PID_Angle_target -= Turn_180-100;//4096; 
    Gimbal.Turn_Info.Righ.IF_Turn_180 = true;
  }
}
/**
 * @brief �ж��Ƿ�ת�����
 * @param 
 */
void Judge_IF_TurnOver(void)
{
  Car_Turn_t *Left = &Gimbal.Turn_Info.Left;
  Car_Turn_t *Righ = &Gimbal.Turn_Info.Righ;
  
  if(Left->IF_Turn_90 == true ||
     Left->IF_Turn_180 == true)
  {
    Left->cnt++;
    if(abs(GIM_Get_AngleErr(&Gimbal.YAW)) <= 15 || Left->cnt >=800)
    {
      TurnLeftReset();
      Gimbal.YAW.motor_data.PID_Angle_target = Gimbal.YAW.motor_data.PID_Angle;
    }
  }
  
  if(Righ->IF_Turn_90 == true ||
     Righ->IF_Turn_180 == true)
  {
    Righ->cnt++;
    if(abs(GIM_Get_AngleErr(&Gimbal.YAW)) <= 15 || Righ->cnt >=800)
    {
      TurnRighReset();
      Gimbal.YAW.motor_data.PID_Angle_target = Gimbal.YAW.motor_data.PID_Angle;
    }
  }
}
/**
 * @brief ת����Ϣ��λ
 * @param 
 */
void TurnLeftReset(void)
{
  Gimbal.Turn_Info.Left.IF_Turn_90 = false;
  Gimbal.Turn_Info.Left.IF_Turn_180 = false;
  Gimbal.Turn_Info.Left.cnt = 0;
}
void TurnRighReset(void)
{
  Gimbal.Turn_Info.Righ.IF_Turn_90 = false;
  Gimbal.Turn_Info.Righ.IF_Turn_180 = false;
  Gimbal.Turn_Info.Righ.cnt = 0;
}
void TurnReset(void)
{
  TurnLeftReset();
  TurnRighReset();
}
/* ----------------���̷���-------------------- */
void Judge_DIR(void)
{
  //������̨�����Ƕ��жϵ��̷���
  if(Gimbal.YAW.MECH_Mid_Angle == YAW_MOTOR_MID_ANGLE)
    CHAS_Dir_HEAD();
  else CHAS_Dir_TAIL();
}
void CHAS_Turn_180(void)
{
  if(Gimbal.YAW.MECH_Mid_Angle > 4096)
  {
    Gimbal.YAW.MECH_Mid_Angle -= 4096;
  }
  else 
  {
    Gimbal.YAW.MECH_Mid_Angle += 4096;
  }
}
void YAW_MECH_Mid_Angle_Proc(void)
{
  //�ͽ�ͷβ����
  int16_t Proc_Angle = 0;
  Proc_Angle = YAW_MotorAngle_Proc(Gimbal.YAW.motor_data.CAN_GetData.Motor_Angle);
  if(abs(Gimbal.YAW.MECH_Mid_Angle - Proc_Angle) > Motor_90){
    CHAS_Turn_180();
  }
}
/* ----------------ͷ������-------------------- */
/**
 * @brief �Ƕ������ı�
 * @param 
 */
void GimReverseTurn(void)
{
  if(Gimbal.Turn_Info.GIM_Reverse.IF_ReverseOver == true)
  {
    if(Gimbal.YAW.MECH_Mid_Angle >=4096)
      Gimbal.YAW.MECH_Mid_Angle -= 4096;//���ݵı仯
    else if(Gimbal.YAW.MECH_Mid_Angle < 4096)
      Gimbal.YAW.MECH_Mid_Angle += 4096;//���ݵı仯      
    Gimbal.Turn_Info.GIM_Reverse.IF_ReverseOver = false;
    Gimbal.Turn_Info.GIM_Reverse.IF_TurnReverse = true;
  }
}
/**
 * @brief �ж��Ƿ�ת�����
 * @param 
 */
void Judge_IF_ReverseOver(void)
{
  Gim_Reverse_t *str = &Gimbal.Turn_Info.GIM_Reverse;
  if(str->IF_ReverseOver == false)
  {
    if(GIM_Get_AngleErr(&Gimbal.YAW)<50)
      str->Over_cnt++;
    str->cnt++;
    if(str->Over_cnt >= 60 || str->cnt > 2500)
    {
      str->IF_ReverseOver = true;
      str->IF_TurnReverse = false;
    }
  }
}
/**
 * @brief �ж�GIM�Ƿ������ת��
 * @note  Ϊ�˷�����ϵͳ
 */
bool prev_IF_TurnReverse = false;
bool Report_IF_Reverse(void)
{
  bool res = false;
  Gim_Reverse_t *str = &Gimbal.Turn_Info.GIM_Reverse;
  if(prev_IF_TurnReverse != str->IF_TurnReverse)
  {
    if(prev_IF_TurnReverse == true && str->IF_TurnReverse == false)
    //�ɼ��½����ź�
      res = true;
    prev_IF_TurnReverse = str->IF_TurnReverse;
  }
  return res;
}

//------------------------------ƽ��ʱ����ת------------------
bool W_move = NO,S_move = NO,A_move = NO,D_move = NO;
void UserSet_W_move(bool a)
{
  W_move = a;
}
void UserSet_S_move(bool a)
{
  S_move = a;
}
void UserSet_A_move(bool a)
{
  A_move = a;
}
void UserSet_D_move(bool a)
{
  D_move = a;
}
void HalfMove_KeyReset(void)
{
  W_move = NO;
  S_move = NO;
  A_move = NO;
  D_move = NO;
}
bool IF_CarHalfMove = NO , IF_MECH_StopHalfMove = NO , IF_SPIN_StopHalfMove = NO;
void Judge_HalfMove_type(void)
{
  Gimbal.HalfMove_type = Normal_yaw;
  if(!IF_MECH_StopHalfMove)
  if(!IF_SPIN_StopHalfMove)
  if(IF_CarHalfMove){//������б��Ž����ж�
    
    if(A_move)
    {
      Gimbal.HalfMove_type = Normal_yaw;
      if(W_move)Gimbal.HalfMove_type = LF_yaw;
      if(S_move)Gimbal.HalfMove_type = RF_yaw;
    }
    if(D_move)
    {
      Gimbal.HalfMove_type = Normal_yaw;
      if(W_move)Gimbal.HalfMove_type = RF_yaw;
      if(S_move)Gimbal.HalfMove_type = LF_yaw;
    }
    if((A_move && D_move) || (!A_move && !D_move))//ADȫ���»���ȫû���¶��ж�Ϊ��ͨģʽ
      Gimbal.HalfMove_type = Normal_yaw;
  
  }
}
void Reset_IF_MECH_StopHalfMove(void)
{//�˳���еģʽ����б��
  IF_MECH_StopHalfMove = NO;
}
void Set_IF_MECH_StopHalfMove(void)
{//�����еģʽ�ر�б��
  IF_MECH_StopHalfMove = YES;
}
void Reset_IF_SPIN_StopHalfMove(void)
{//�˳�����ģʽ����б��
  IF_SPIN_StopHalfMove = NO;
}
void Set_IF_SPIN_StopHalfMove(void)
{//��������ģʽ�ر�б��
  IF_SPIN_StopHalfMove = YES;
}
void Reset_IF_CarHalfMove(void)
{//�ر�б���ܿ���
  IF_CarHalfMove = NO;
}
void Set_IF_CarHalfMove(void)
{//����б���ܿ���
  IF_CarHalfMove = YES;
}
void Reset_CarHalfMove(void)
{//���帴λ����ʼΪ�ر�״̬
  Reset_IF_SPIN_StopHalfMove();
  Reset_IF_MECH_StopHalfMove();
  Reset_IF_CarHalfMove();
  HalfMove_KeyReset();//��λб��ģʽ�İ�����������ʱ������ʾȫ��̧��
}
void IF_CarHalfMove_Switch(void)
{
  //���俪��
  switch(IF_CarHalfMove)
  {
    case NO:
      Set_IF_CarHalfMove();
      break;
    case YES:
      Reset_IF_CarHalfMove();
      break;
  }
}
void SystemSet_IF_CarHalfMove(void)
{
  //�ж�б����
  if(CHAS_SPIN_Report())//С����
    Set_IF_SPIN_StopHalfMove();//��ֹб��
  else 
    Reset_IF_SPIN_StopHalfMove();//����б��
  
  Judge_HalfMove_type();
}
float Get_CarHalfMove_Angle(void)
{
  //��ȡб��Ƕ�
  float res = 0;
  switch(Gimbal.HalfMove_type)
  {
    case Normal_yaw:
        res = 0;
        break;
        
    case L_yaw:
        res = -Turn_HalfMove;
        break;
    
    case R_yaw:
        res = Turn_HalfMove;
        break;
    
    case LF_yaw:
        res = -Turn_HalfMove;
        break;
    
    case RF_yaw:
        res = Turn_HalfMove;
        break;
  }
  return res;
}


//------------------------------------------------------------------

/**
 * @brief ��ȡIMU����
 * @param 
 */
void IMU_YawData_Report(Motor_Data_t *str)
{
  str->IMU_GetData.IMU_Speed = Report_YawSpeed();
  str->IMU_GetData.IMU_Angle = Report_YawAngle();
}
void IMU_PitData_Report(Motor_Data_t *str)
{
  str->IMU_GetData.IMU_Speed = Report_PitSpeed();
  str->IMU_GetData.IMU_Angle = Report_PitAngle();
}
void IMU_Data_Report(void)
{
  IMU_YawData_Report(&Gimbal.YAW.motor_data);
  IMU_PitData_Report(&Gimbal.PIT.motor_data);
}


/**
 * @brief ����PID����ȫ����0����
 * @param 
 */
void GIM_SetEmpty(PID_Info_t *str)
{
  memset(&str->Speed_Loop,0,sizeof(PID_Loop_t));
  memset(&str->Angle_Loop,0,sizeof(PID_Loop_t));
}
 
/**
 * @brief ж������
 * @param 
 */
void GIM_Stop(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
	
	/* �ٶȻ�������� */
  pid_out[CHAS_LF] = 0;
  pid_out[CHAS_RF] = 0;
  
	CAN1_Send(GIM_ESC, pid_out);	  
}


/**
 * @brief ��ʼ��������ģʽYAW��Ƕ�
 * @param 
 */
void GIM_GYRO_FirstYawAngle(AXIS_Info_t *str)
{
  str->motor_data.PID_Angle_target = str->motor_data.IMU_GetData.IMU_Angle;
}
/**
 * @brief ��ʼ����еģʽYAW��Ƕ�
 * @param 
 */
void GIM_MECH_FirstYawAngle(AXIS_Info_t *str)
{
  str->motor_data.PID_Angle_target = str->MECH_Mid_Angle;
}
/**
 * @brief ��ʼ��PIT��Ƕ�
 * @param 
 */
void GIM_FirstPitAngle(AXIS_Info_t *str)
{
  //str->motor_data.PID_Angle_target = str->motor_data.CAN_GetData.Motor_Angle;
  str->motor_data.PID_Angle_target = str->MECH_Mid_Angle;
}
void GIM_GYRO_FirstPitAngle(AXIS_Info_t *str)
{
  str->motor_data.PID_Angle_target = str->motor_data.IMU_GetData.IMU_Angle;
}
void GIM_MECH_FirstPitAngle(AXIS_Info_t *str)
{
  str->motor_data.PID_Angle_target = PIT_MotorAngle_Proc(str->motor_data.CAN_GetData.Motor_Angle);
}

//-----------��ȡ���-----------
/**
 * @brief ��ȡ��Ӧ������ǰ�ǶȻ���Err
 * @note  ���뿨�����˲� 
 */
float GIM_Get_AngleErr(AXIS_Info_t *str)
{
  float res;
  res = str->motor_data.PID_Angle_target - str->motor_data.PID_Angle;
  res = KalmanFilter(&str->KF_Angle[str->PID.PID_type],res);//�������˲�
  return res;
}

/**
 * @brief ��ȡ��Ӧ������ǰ�ٶȻ���Err
 * @note  û�ӿ������˲�������֮��Ч������ 
 */
float GIM_Get_SpeedErr(AXIS_Info_t *str)
{
  float res;
  res = str->motor_data.PID_Speed_target - str->motor_data.PID_Speed;
  return res;
}

/**
 * @brief YAW������е��ֵ�Ƕ����
 * @note  ʹ�õ���ĽǶ�
 */
float YAW_AngleErrReport(void)
{
  float res;
  AXIS_Info_t *str = &(Gimbal.YAW);
  Motor_Data_t *DATA = &(str->motor_data);
  
  res = str->MECH_Mid_Angle - //�����yaw�������Ƕȴ�����
         YAW_MotorAngle_Proc(DATA->CAN_GetData.Motor_Angle)  ;
  return res;
}

/**
 * @brief PIT������е��ֵ�Ƕ���� 
 * @note  ʹ�õ���ĽǶ�
 */
float PIT_AngleErrReport(void)
{
  float res;
  AXIS_Info_t *str = &(Gimbal.PIT);
  Motor_Data_t *DATA = &(str->motor_data);
  
  res = (float)DATA->CAN_GetData.Motor_Angle - str->MECH_Mid_Angle;
  return res;
}

/**
 * @brief �õ�yaw�������ǽǶ�ֵ
 */
float YAW_GetGyroAngle(void)
{
  return Gimbal.YAW.motor_data.PID_Angle;
}

/**
 * @brief �õ�pitch�������ǽǶ�ֵ
 */
float PIT_GetGyroAngle(void)
{
  return Gimbal.PIT.motor_data.PID_Angle;
}

/**
 * @brief �õ�pitch�����е��ֵ
 */
float PIT_GetMechAngle(void)
{
  return (float)Gimbal.PIT.motor_data.CAN_GetData.Motor_Angle;
}

/**
 * @brief �����ڱ�����̧ͷ
 */
void Gim_Sentry_UP(void)
{
  Gimbal.PIT.motor_data.PID_Angle_target = PIT_SENTRY;//PIT_MOTOR_MIN_ANGLE + 200;
}

/**
 * @brief �ϱ��Ƿ����NAN
 */
bool GIM_Report_IF_NAN(void)
{
  return Gimbal.IF_NAN;
}



