/***      �� ����ģ����ƴ��� ��

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
 
#include "module.h"
#include "Device.h"
 
Module_Info_t Module = {
  .ctrl_mode = RC_CTRL_MODE,
  .pid_mode = GYRO,
  
  .REMOTE_or_REFER_NORMAL = false,
    
  .Friction.IF_WORK = false,  
  .Friction.IF_INIT_OK = false,  
  .Friction.friction_num = FRICTION_INIT_SPEED,
  .Friction.friciont_num_target = FRICTION_INIT_SPEED,
  .Clip.Clip_State = CLIP_CLOSE_NUM,
}; 
 


/* �����������������������������������������������������������������������������������������������Ʋ㡪������������������������������������������������������������������������������������������ */

/**
 * @brief ����ģ������
 * @param 
 */
void MODULE_Ctrl(void)
{
//  MODULE_GetInfo();
  switch(Module.ctrl_mode)
  {
    case  RC_CTRL_MODE:
      First_GetInto_Mode();//��һ�ν���ģʽ�Ĵ���
      
      RC_Friction_Ctrl();/*Ħ����*/
      
      RC_AimLED_Ctrl();/* LED */
      
      RC_Clip_Ctrl();/* ���ն�� */
      break;
    
    case  KEY_CTRL_MODE:
      First_GetInto_Mode();//��һ�ν���ģʽ�Ĵ���
      
      KEY_Friction_Ctrl();/*Ħ����*/
      
      KEY_AimLED_Ctrl();/* LED */
      
      KEY_Clip_Ctrl();/* ���ն�� */
      break;
  }
}
 
/**
 * @brief ����ģ���ȡϵͳ������Ϣ
 * @param 
 */
void MODULE_GetInfo(void)
{
  Module.ctrl_mode = System.ctrl_mode;
  Module.pid_mode = System.pid_mode;
  Friction_SetInitNum();
  Judge_Clip_state();
  if(IF_DUM_NORMAL)
  {
    Check_IF_ArmorBooster_Deinit();//�ж�armorbooster�Ƿ�ϵ磬�ϵ�Ļ���Ҫ���³�ʼ��
    #if (Fric_motor == Fric_3508)
      Friction_SpeedFIX();//��������Ӧ
    #endif
  }
}

/**
 * @brief Ħ���ָ�λ
 * @param 
 */
void Friction_Reset(void)
{
  Fric_Speed_Slope(&Module.Friction.friction_num ,FRICTION_STOP_SPEED);//FRICTION_INIT_SPEED);
  #if (Fric_motor == Fric_3508)
  Fric_3508_Handler();
  #endif
  Module.Friction.IF_WORK = false;
}

/**
 * @brief ���⸴λ
 * @param 
 */
void AimLED_Reset(void)
{
  AimLED_Ctrl = 0;
  Module.AimLED.IF_WORK = false;
}

/**
 * @brief �����λ
 * @param 
 */
void Clip_Reset(void)
{
  Clip_turn(DISABLE);
}

/**
 * @brief �ж��Ƿ��һ�ν��� ң����/���� ģʽ
 * @param 
 */
static System_Ctrl_Mode_t M_prev_ctrl_mode = RC_CTRL_MODE;
void First_GetInto_Mode(void)
{
  if(M_prev_ctrl_mode != Module.ctrl_mode)
  {
    Clip_turn(ENABLE);
    M_prev_ctrl_mode = Module.ctrl_mode;
    Module.Friction.IF_WORK = false;
    Module.AimLED.IF_WORK = false;
    Module.Clip.Clip_State = CLIP_CLOSE_NUM;
  }
}

/**
 * @brief ��������λ
 * @param 
 */
void MODULE_Reset(void)
{
  if(M_prev_ctrl_mode != Module.ctrl_mode)
  {
    M_prev_ctrl_mode = Module.ctrl_mode;
    Module.REMOTE_or_REFER_NORMAL = false;
  }
  Friction_Reset();
  AimLED_Reset();
  Clip_Reset();
}
/**
 * @brief Ħ���ֳ�ʼ�������У׼
 * @note  С�۷��� 
 */
void Friction_Init(void)
{
  PWM_Friction_Init(2500-1,84-1);//2500-1,84-1
}

void Friction_Init_Reset(void)//����
{
  Module.Friction.IF_INIT_OK = NO;
}

void Friction_SetInitNum(void)
{
  if(Module.Friction.IF_INIT_OK != true)
  {
    if(IF_DUM_NORMAL)//����������
    if(DUM_Report_IF_ArmorBooster_work())
    {
      #if (Fric_motor == Fric_Bee)
        TIM_SetCompare1(TIM3,FRICTION_INIT_SPEED);//��
        TIM_SetCompare2(TIM3,FRICTION_INIT_SPEED);//��
        Friction_Init_Delay();//3����ʼ���ɹ�
      #elif (Fric_motor == Fric_3508)
        Module.Friction.IF_INIT_OK = YES;
      #endif
    }
  }
}
int Init_cnt = 0;
void Friction_Init_Delay(void)
{
  Init_cnt++;
  if(Init_cnt == FRICTION_INIT_DELAT)//2�����Ϊ��ʼ���ɹ�
  {
    Module.Friction.IF_INIT_OK = YES;
    Init_cnt = 0;
  }
}
/*����Ħ�����Ƿ�����*/
bool Report_IF_Fric_Init_Over(void)
{
  return Module.Friction.IF_INIT_OK;
}
/**
 * @brief ���ն����ʼ��
 * @param 
 */
void Clip_Init(void)
{
  PWM_Clip_Init(999,(84*20)-1);
}
/**
 * @brief ���ն�� ʹ��/ʧ�ܿ���
 * @param 
 */
void Clip_turn(FunctionalState state)
{
   TIM_Cmd(TIM1, state);  //ʹ��TIM3
}

/**
 * @brief ���������豸���ܳ�ʼ��
 * @note  ������׼�Ƶ�io��ʼ�����������㣬�˴�����
 * @param 
 */
void MODULE_Init(void)
{
  Friction_Init();
  Clip_Init();
}

/**    ��ң�����������ơ�
 * 
 *           _____                    _____                    _____                    _____          
 *          /\    \                  /\    \                  /\    \                  /\    \         
 *         /::\____\                /::\    \                /::\    \                /::\    \        
 *        /:::/    /                \:::\    \              /::::\    \              /::::\    \       
 *       /:::/    /                  \:::\    \            /::::::\    \            /::::::\    \      
 *      /:::/    /                    \:::\    \          /:::/\:::\    \          /:::/\:::\    \     
 *     /:::/____/                      \:::\    \        /:::/__\:::\    \        /:::/__\:::\    \    
 *    /::::\    \                      /::::\    \      /::::\   \:::\    \      /::::\   \:::\    \   
 *   /::::::\    \   _____    ____    /::::::\    \    /::::::\   \:::\    \    /::::::\   \:::\    \  
 *  /:::/\:::\    \ /\    \  /\   \  /:::/\:::\    \  /:::/\:::\   \:::\____\  /:::/\:::\   \:::\    \ 
 * /:::/  \:::\    /::\____\/::\   \/:::/  \:::\____\/:::/  \:::\   \:::|    |/:::/__\:::\   \:::\____\
 * \::/    \:::\  /:::/    /\:::\  /:::/    \::/    /\::/   |::::\  /:::|____|\:::\   \:::\   \::/    /
 *  \/____/ \:::\/:::/    /  \:::\/:::/    / \/____/  \/____|:::::\/:::/    /  \:::\   \:::\   \/____/ 
 *           \::::::/    /    \::::::/    /                 |:::::::::/    /    \:::\   \:::\    \     
 *            \::::/    /      \::::/____/                  |::|\::::/    /      \:::\   \:::\____\    
 *            /:::/    /        \:::\    \                  |::| \::/____/        \:::\   \::/    /    
 *           /:::/    /          \:::\    \                 |::|  ~|               \:::\   \/____/     
 *          /:::/    /            \:::\    \                |::|   |                \:::\    \         
 *         /:::/    /              \:::\____\               \::|   |                 \:::\____\        
 *         \::/    /                \::/    /                \:|   |                  \::/    /        
 *          \/____/                  \/____/                  \|___|                   \/____/         
 */ 



/**
 * @brief ң���� Ħ���ֿ��ؿ���
 * @note  �������е�������ʱ���أ�������һ���ܿؿ��ƿ���
 */
void RC_Friction_Ctrl(void)
{
  Fric_3508_SetPID();
  switch(Module.Friction.IF_WORK)
  {
    case (false): 
      Friction_Off();
      break;
    case (true):
      Friction_On();
      break;
  }
  #if (Fric_motor == Fric_3508)
  Fric_3508_Handler();
  #endif
}


/**
 * @brief ��׼�� ң�����ܿ�
 * @note  �������е�������ʱ���أ�������һ���ܿؿ��ƿ��� 
 */
void RC_AimLED_Ctrl(void)
{
  switch(Module.AimLED.IF_WORK)
  {
    case (true):
      AimLED_On();
      break;
    case (false): 
      AimLED_Off();
      break;
  }
}

/**
 * @brief ��������״̬����
 * @note  ��Ϊ��ң����s2�����У���ͨ���м�->�����������̫���Ƴ���ģ��һ��һ�ص�
          ������һ�����ƴ�������״̬���ƺ�����s2���ƺ������ã�RC��KEY������ͬ
 * @param 
 */
void RC_MODULE_State_Update(void)
{
  switch(IF_MODULE_WORK)
  {/* �����������ر� */
    case  YES:
      Module.Friction.IF_WORK = false;
      Module.AimLED.IF_WORK = false;
      break;
    
    case  NO:
      if(Report_IF_Fric_Init_Over())
      {//ֻ�г�ʼ���ɹ��ˣ����ܿ���Ħ����
        Module.Friction.IF_WORK = true;
        Module.AimLED.IF_WORK = true;
      }
      break;
  }
}

/**
 * @brief ң�������տ���
 * @param 
 */
void RC_Clip_Ctrl(void)
{
  switch(CLIP_STATE)
  {
    case CLIP_OPEN_NUM:
      Clip_Open();
      break;
    case CLIP_CLOSE_NUM:
      Clip_Close();
      break;
  }
}

/**
 * @brief ͬ����ģ��״̬�л���������ң���������ش��������л�����Ҫһ�����ƴ�������������״̬�л�����
 * @param 
 */
void RC_Clip_State_Updata(void)
{
  switch(CLIP_STATE)
  {
    case CLIP_OPEN_NUM:
      CLIP_STATE = CLIP_CLOSE_NUM;
      break;
    case CLIP_CLOSE_NUM:
      CLIP_STATE = CLIP_OPEN_NUM;
      break;
  }
}
/**
 * @brief �жϵ���״̬
 * @param 
 */
void Judge_Clip_state(void)
{
  if(CLIP_STATE == CLIP_OPEN_NUM)
    Module.Clip.IF_CLIP_OPEN = YES;
  else Module.Clip.IF_CLIP_OPEN = NO;
}
/**
 * @brief ��������״̬
 * @param 
 */
bool Report_IF_CLIP_OPEN(void)
{
  return Module.Clip.IF_CLIP_OPEN;
}


/**          �����̲������ơ�
 * ����������   ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ�������
 * ��Esc��   �� F1�� F2�� F3�� F4�� �� F5�� F6�� F7�� F8�� �� F9��F10��F11��F12�� ��P/S��S L��P/B��  ����    ����    ����
 * ����������   ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة�������  ����    ����    ����
 * ���������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ��������������� ���������Щ������Щ������� ���������Щ������Щ������Щ�������
 * ��~ `��! 1��@ 2��# 3��$ 4��% 5��^ 6��& 7��* 8��( 9��) 0��_ -��+ =�� BacSp �� ��Ins��Hom��PUp�� ��N L�� / �� * �� - ��
 * ���������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ����������� ���������੤�����੤������ ���������੤�����੤�����੤������
 * �� Tab �� Q �� W �� E �� R �� T �� Y �� U �� I �� O �� P ��{ [��} ]�� | \ �� ��Del��End��PDn�� �� 7 �� 8 �� 9 ��   ��
 * �������������ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ة����������� ���������ة������ة������� ���������੤�����੤������ + ��
 * �� Caps �� A �� S �� D �� F �� G �� H �� J �� K �� L ��: ;��" '�� Enter  ��               �� 4 �� 5 �� 6 ��   ��
 * ���������������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة�����������������     ����������     ���������੤�����੤�����੤������
 * �� Shift  �� Z �� X �� C �� V �� B �� N �� M ��< ,��> .��? /��  Shift   ��     �� �� ��     �� 1 �� 2 �� 3 ��   ��
 * �������������Щ����ة��Щ��ة����Щة������ة������ة������ة������ة������ة����Щة������੤�����ةЩ��������Щ��������� ���������੤�����੤������ ���������ة������੤������ E����
 * �� Ctrl��    ��Alt ��         Space         �� Alt�� FN ��    ��Ctrl�� �� �� �� �� �� �� �� ��   0   �� . ����������
 * �������������ة��������ة��������ة����������������������������������������������ة��������ة��������ة��������ة��������� ���������ة������ة������� �����������������ة������ة�������
 */

/**
 * @brief ���� Ħ���ֿ��ؿ���
 * @note  �������е�������ʱ���أ�������һ���ܿؿ��ƿ���
 */
void KEY_Clip_Ctrl(void)
{
  switch(CLIP_STATE)
  {
    case CLIP_OPEN_NUM:
      Clip_Open();
      break;
    case CLIP_CLOSE_NUM:
      Clip_Close();
      break;
  }
}

/**
 * @brief ��׼�� �����ܿ�
 * @note  �������е�������ʱ���أ�������һ���ܿؿ��ƿ��� 
 */
void KEY_AimLED_Ctrl(void)
{
  switch(Module.AimLED.IF_WORK)
  {
    case (true):
      AimLED_On();
      break;
    case (false): 
      AimLED_Off();
      break;
  }  
}

/**
 * @brief ���̿��ص���
 * @param 
 */
void KEY_Friction_Ctrl(void)
{
  Fric_3508_SetPID();
  switch(Module.Friction.IF_WORK)
  {
    case (false): 
      Friction_Off();
      break;
    case (true):
      Friction_On();
      break;
  }
  #if (Fric_motor == Fric_3508)
  Fric_3508_Handler();
  #endif
}
/**
 * @brief ͬ����ģ��״̬�л���������ң���������ش��������л�����Ҫһ�����ƴ�������������״̬�л�����
 * @param 
 */
void CLIP_Set_CloseNum(void)
{
  CLIP_STATE = CLIP_CLOSE_NUM;
}
void CLIP_Set_OpenNum(void)
{
  CLIP_STATE = CLIP_OPEN_NUM;
}
void KEY_Clip_State_Updata(void)
{
  switch(CLIP_STATE)
  {
    case CLIP_OPEN_NUM:
      ShootNum_Reset();
      CLIP_Set_CloseNum();
      break;
    case CLIP_CLOSE_NUM:
      CLIP_Set_OpenNum();
      break;
  }
}

/* �����������������������������������������������������������������������������������������������ܲ㡪������������������������������������������������������������������������������������������ */
/**
 * @brief ��ȡ����ϵͳ����Ϣ
 * @param 
 */
void Module_GetReferInfo(void)
{
  Module.Friction.speed_limit_level = DUM_Report_Shoot_SpeedLimit();
  if(Module.Friction.now_speed_level != Module.Friction.speed_limit_level)
    Module.Friction.now_speed_level = Module.Friction.speed_limit_level;
}
/**
 * @brief �������
 * @note  Ħ���ֱ��٣���̬����ת��
 */
void Temp_Fix_30S(void)
{
  float temp_scope = 35;//����仯��ΧΪ35���϶�
  float temp_low = 35;//��ʼ�¶��趨Ϊ35���϶�
  float res = 0;
  float temp_real;
  
  temp_real = ((float)Module.Friction.Fric[0].motor_Data.CAN_GetData.temp + 
               (float)Module.Friction.Fric[1].motor_Data.CAN_GetData.temp)/2;
  
  if(temp_real >= temp_low)
    res = (temp_real - temp_low)/temp_scope * (-168);
  if(temp_real < temp_low)
    res = 0;
  if(temp_real > temp_low + temp_scope)
    res = -168;
  
  Module.Friction.Level_3_TEMP_fix_num = res;
}
void Temp_Fix_18S(void)
{
  float temp_scope = 35;//����仯��ΧΪ25���϶�
  float temp_low = 35;//��ʼ�¶��趨Ϊ35���϶�
  float res = 0;
  float temp_real;
  
  temp_real = ((float)Module.Friction.Fric[0].motor_Data.CAN_GetData.temp + 
               (float)Module.Friction.Fric[1].motor_Data.CAN_GetData.temp)/2;
  
  if(temp_real >= temp_low)
    res = (temp_real - temp_low)/temp_scope * (-70);
  if(temp_real < temp_low)
    res = 0;
  if(temp_real > temp_low + temp_scope)
    res = -70;
  
  Module.Friction.Level_2_TEMP_fix_num = res;
}
void Temp_Fix_15S(void)
{
  float temp_scope = 35;//����仯��ΧΪ50���϶�
  float temp_low = 35;//��ʼ�¶��趨Ϊ35���϶�
  float res = 0;
  float temp_real;
  
  temp_real = ((float)Module.Friction.Fric[0].motor_Data.CAN_GetData.temp + 
               (float)Module.Friction.Fric[1].motor_Data.CAN_GetData.temp)/2;
  
  if(temp_real >= temp_low)
    res = (temp_real - temp_low)/temp_scope * (-50);
  if(temp_real < temp_low)
    res = 0;
  if(temp_real > temp_low + temp_scope)
    res = -50;
  
  Module.Friction.Level_1_TEMP_fix_num = res;
}
uint8_t SpeedErr_cnt=0;
void SpeedAdapt(float real_S , float min_S, float max_S,float *fix , float up_num , float down_num)
{
  if(real_S < min_S && real_S > 8)
    SpeedErr_cnt++;
  else if(real_S >= min_S && real_S <= max_S )SpeedErr_cnt = 0;
  if(SpeedErr_cnt == 1)//����ƫ��
  {
    SpeedErr_cnt = 0;
    *fix += up_num;
  }
  if(real_S > max_S)//����ƫ��
    *fix -= down_num;
}
uint8_t prev_Shoot_num = 0;
bool IF_SpeedUpdate = NO;
void Friction_SpeedFIX(void)
{
  float realspeed = DUM_Report_RealShootSpeed();
  if(prev_Shoot_num != DUM_Report_Shoot_NUM())
  {
    //�ô������ĸ������ж������ٶ��Ƿ����
    prev_Shoot_num = DUM_Report_Shoot_NUM();
    IF_SpeedUpdate = YES;
  }else IF_SpeedUpdate = NO;
  
  if(IF_SpeedUpdate)
  switch(Module.Friction.now_speed_level)
  {
    case SHOOT_L1_SPEED:
      SpeedAdapt(realspeed , 12.5 , 13.5 , &Module.Friction.Level_1_fix_num , 15 , 35);
      Temp_Fix_15S();
      break;
    
    case SHOOT_L2_SPEED:
      SpeedAdapt(realspeed , 15.8 , 16.8 , &Module.Friction.Level_2_fix_num , 15 , 35);
      Temp_Fix_18S();
      break;
  
    case SHOOT_L3_SPEED:
      SpeedAdapt(realspeed , 27.5 , 28.5 , &Module.Friction.Level_3_fix_num , 25 , 50);
      Temp_Fix_30S();//3508����¶Ȼ�Ӱ�����٣��¶�Խ������Խ��Խ��Խ�����̧ͷ����׼������֮���ٶ�����
      break;
  }
}


/**
 * @brief Ħ����б�¼��� 
 * @param 
 */
void Fric_Speed_Slope(float * now_speed,float change_target_speed) 
{
  #if (Fric_motor == Fric_Bee)
  if(*now_speed!=change_target_speed)
  {
    if((*now_speed) > change_target_speed) (*now_speed)-=10;
    if((*now_speed) < change_target_speed) (*now_speed)+=10;
    if(abs((*now_speed) - change_target_speed  ) < 15) 
    {
      (*now_speed) = change_target_speed;
    }
      TIM_SetCompare1(TIM3,(int16_t)(*now_speed+1000));
      TIM_SetCompare2(TIM3,(int16_t)(*now_speed+1000));
  }
  #elif (Fric_motor == Fric_3508)
//  if(*now_speed!=change_target_speed)
//  {
    if((*now_speed) > change_target_speed) (*now_speed)-=80;
    if((*now_speed) < change_target_speed) (*now_speed)+=80;
    if(abs((*now_speed) - change_target_speed  ) < 100) 
    {
      (*now_speed) = change_target_speed;
    }
//  }
    Fric_L_Set_SpeedTarget(-(*now_speed));
    Fric_R_Set_SpeedTarget((*now_speed));
//    Fric_3508_Handler();
  #endif
}

/**
 * @brief ���ݲ���ϵͳ����Ϣ�л�Ħ�����ٶ�
 * @param 
 */
float test_FricTarget = -1000;//4530;
void Fric_Speed_Change(void)
{
#if (IF_REFER_CONNECT == 1)
  if(IF_DUM_NORMAL && IF_RC_NORMAL)
  {
    Module.REMOTE_or_REFER_NORMAL = true;
    Module_GetReferInfo();
    switch(Module.Friction.now_speed_level)
    {
      case  SHOOT_L1_SPEED:
          Module.Friction.friciont_num_target = FRICTION_L1_SPEED + 
                                                Module.Friction.Level_1_fix_num + 
                                                Module.Friction.Level_1_TEMP_fix_num;
          break;
      case  SHOOT_L2_SPEED:
          Module.Friction.friciont_num_target = FRICTION_L2_SPEED + 
                                                Module.Friction.Level_2_fix_num + 
                                                Module.Friction.Level_2_TEMP_fix_num;
          break;        
      case  SHOOT_L3_SPEED:
          Module.Friction.friciont_num_target = FRICTION_L3_SPEED + 
                                                Module.Friction.Level_3_fix_num + 
                                                Module.Friction.Level_3_TEMP_fix_num;
          break;  
      
      case 75:
          Module.Friction.friciont_num_target = FRICTION_L1_SPEED + 
                                                Module.Friction.Level_1_fix_num + 
                                                Module.Friction.Level_1_TEMP_fix_num;
          break;
      default:
          Module.Friction.friciont_num_target = FRICTION_L1_SPEED;//FRICTION_INIT_SPEED;
          break;          
    }
  }
  else if(!IF_RC_NORMAL)//ң�����ر�
  {
    Module.Friction.friciont_num_target = FRICTION_STOP_SPEED;//FRICTION_INIT_SPEED;
    Module.REMOTE_or_REFER_NORMAL = false;
  }
  else if(!IF_DUM_NORMAL && IF_RC_NORMAL)
  {
  //���Ǽ����ֶ�����
    Module.Friction.friciont_num_target = FRICTION_L1_SPEED ;
  }
      
   Fric_Speed_Slope(&Module.Friction.friction_num , Module.Friction.friciont_num_target);
  
#elif (IF_REFER_CONNECT == 0)
  //���ڵ���
   Fric_Speed_Slope(&Module.Friction.friction_num , test_FricTarget);//FRICTION_L1_SPEED);
//        TIM_SetCompare1(TIM3,-1000);
//      TIM_SetCompare2(TIM3,-1000);
#endif
}

uint8_t Report_Shoot_Speed(void)
{
  return Module.Friction.now_speed_level;
}

/**
 * @brief Ħ���� ң�ؿ���
 * @param 
 */
void Friction_On(void)
{
  Fric_Speed_Change();
}

/**
 * @brief Ħ���� ң�عر�
 * @param 
 */
void Friction_Off(void)
{
  Fric_Speed_Slope(&Module.Friction.friction_num ,FRICTION_STOP_SPEED);//INITxxxx
}

/**
 * @brief ��׼�� ����
 * @param 
 */
void AimLED_On(void)
{
  AimLED_Ctrl = 1;
}

/**
 * @brief ��׼�� �ر�
 * @param 
 */
void AimLED_Off(void)
{
  AimLED_Ctrl = 0;
}

/**
 * @brief ���տ�
 * @param 
 */
void Clip_Open(void)
{
  TIM_SetCompare2(TIM1,(uint32_t)CLIP_OPEN_NUM);//��
}

/**
 * @brief ���չ�
 * @param 
 */
uint32_t test_Clip_num = 150;
void Clip_Close(void)
{
  TIM_SetCompare2(TIM1,(uint32_t)CLIP_CLOSE_NUM);//�ر�
}


/**
 * @brief ���̴�
 * @param 
 */
void Module_KEY_ON(void)
{
//  if(!IF_MODULE_WORK)Single_Reverse_HALF();//���̷�תһ��
  if(Module.Friction.IF_INIT_OK)
  {//ֻ�г�ʼ���ɹ��ˣ����ܿ���Ħ����
    Module.Friction.IF_WORK = true;
    Module.AimLED.IF_WORK = true;
  }
//  CLIP_Set_CloseNum();
}

/**
 * @brief ���ڵ�Ħ���ֲ�תʱ��ʼ����ʹ֮��ת
 * @param 
 */
void Module_KEY_OFF(void)
{
  Module.Friction.IF_WORK = false;
  Module.AimLED.IF_WORK = false;
//  CLIP_Set_CloseNum();
}

/**
 * @brief ��armorbooster�ϵ��ʱ��λĦ����
 * @param 
 */
void Check_IF_ArmorBooster_Deinit(void)
{
  if(!DUM_Report_IF_ArmorBooster_work())
  { 
    Module.Friction.IF_WORK = false;
    Module.AimLED.IF_WORK = false;
    Module.Friction.IF_INIT_OK = NO;
  }
}

//--------------------------------------------Ħ����3508------------------------------------------//

/**
 * @brief ����Ħ���������ٶ�
 * @param 
 */
void Fric_L_Set_SpeedTarget(float TargetSpeed)
{
  Motor_Data_t *str = &(Module.Friction.Fric[left].motor_Data);
  str->PID_Speed_target = TargetSpeed;
}
void Fric_R_Set_SpeedTarget(float TargetSpeed)
{
  Motor_Data_t *str = &(Module.Friction.Fric[righ].motor_Data);
  str->PID_Speed_target = TargetSpeed;
}
/**
 * @brief Ħ����3508�������ͬ��
 * @param 
 */
void Fric_3508_DataSync(Motor_Data_t *str)
{
  str->PID_Speed = str->CAN_GetData.Motor_Speed;
  str->PID_Angle = str->CAN_GetData.Motor_Angle;
}
/**
 * @brief �õ��ٶ����
 * @param 
 */
float Fric_3508_Get_SpeedErr(Motor_Data_t *str)
{
  float res;
  res = str->PID_Speed_target - str->PID_Speed;
  return res;
}
/**
 * @brief PID�㷨��ȡ���
 * @note  �ٶȻ�
 */
float Fric_3508_GetOutput(Fric_3508_Info_t *str)
{
  PID_Info_t *PID = &str->PID;
  Motor_Data_t *DATA = &str->motor_Data;
  float res;
  
  Fric_3508_DataSync(DATA);//����ͬ��

//  PID->Angle_Loop.Err = CHAS_Get_AngleErr(DATA);
//  
//  DATA->PID_Speed_target = PID_Algorithm(&PID->Angle_Loop);//�ǶȻ�
  
  PID->Speed_Loop.Err = Fric_3508_Get_SpeedErr(DATA);
  
  res = PID_Algorithm(&PID->Speed_Loop);//�ٶȻ�
  
  return res;
}
/**
 * @brief Ħ����3508�������
 * @param 
 */
float js_fric_1_speed = 0 , js_fric_2_speed = 0;//js������ٶ�
void Fric_3508_Handler(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
  
  js_fric_1_speed = Module.Friction.Fric[righ].motor_Data.PID_Speed;
  js_fric_2_speed = Module.Friction.Fric[left].motor_Data.PID_Speed;
  
  //PID�㷨���
  pid_out[left] = (int16_t)(Fric_3508_GetOutput(&Module.Friction.Fric[left]));
  pid_out[righ] = (int16_t)(Fric_3508_GetOutput(&Module.Friction.Fric[righ]));
  
  CAN2_Send(Fric_3508_ESC, pid_out);
}

void Fric_3508_stop(void)
{
	static int16_t pid_out[4] = {0, 0, 0, 0};
  
	CAN2_Send(Fric_3508_ESC, pid_out);	
}

void Fric_3508_Reset(void)
{
  memset(&Module.Friction.Fric[left],0,sizeof(Fric_3508_Info_t));
  memset(&Module.Friction.Fric[righ],0,sizeof(Fric_3508_Info_t));
}
float test_spl = 13 , test_spr = 13, test_sil = 0.18  , test_sir = 0.18;//0.28;
void Fric_3508_SetPID(void)
{
  Module.Friction.Fric[left].PID.Speed_Loop.PID_Param.P = test_spl;//20;
  Module.Friction.Fric[left].PID.Speed_Loop.PID_Param.I = test_sil;//2;
  Module.Friction.Fric[left].PID.Speed_Loop.PID_Param.D = 0;
  Module.Friction.Fric[righ].PID.Speed_Loop.PID_Param.P = test_spr;//20;
  Module.Friction.Fric[righ].PID.Speed_Loop.PID_Param.I = test_sir;//2;
  Module.Friction.Fric[righ].PID.Speed_Loop.PID_Param.D = 0;
  Fric_3508_Init();
}

//����3508����Ƿ�ﵽĿ��ת��
bool Report_IF_Fric3508_SetSpeed(void)
{
  bool res = YES;
  #if (Fric_motor == Fric_3508)
  if(abs(Module.Friction.Fric[left].motor_Data.PID_Speed - Module.Friction.Fric[left].motor_Data.PID_Speed_target) < 2000 && 
     abs(Module.Friction.Fric[righ].motor_Data.PID_Speed - Module.Friction.Fric[righ].motor_Data.PID_Speed_target) < 2000)
    res = YES;
  else 
    res = NO;
  #endif
  return res;
}
