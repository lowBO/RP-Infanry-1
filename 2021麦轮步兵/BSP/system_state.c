/***      �� ״̬�����ƴ��� ��

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
 
#include "system_state.h"
#include "Device.h"

/**
 * @brief ϵͳ״̬������ 
 * @param 
 */
void system_state_Ctrl(void)
{
  RC_Ctrl();
  switch (System.state)
  {
    case SYSTEM_NORMAL:
      System_Normal_process();
      break;
    
    case SYSTEM_RCLOST:
      RC_Lost_Process();
      break;
    
    case SYSTEM_RCERR :
      RC_Err_Process();
      break;
  }      
}

void Car_StateSync(CAR_ACT_FLAG_t *str)
{
  str->IF_CALIBRATE_OK = GIM_CalOK_Report();
  str->IF_SPIN_START = CHAS_SPIN_Report();
  str->IF_IMU_InitOver = IF_IMU_InitOver();
}

void User_StateSyne(User_state_t *str)
{
  str->CAN1_Normal =      IF_CAN1_NORMAL;
  str->CAN2_Normal =      IF_CAN2_NORMAL;
  str->Referee_Normal =   IF_REFER_NORMAL;
  str->Remote_Normal =    IF_RC_NORMAL;
  str->DUM_Normal =       IF_DUM_NORMAL;
}

/**
 * @brief ϵͳ����״̬ʱ�Ĵ��� 
 * @param 
 */
static System_State_t prev_sys_state = SYSTEM_RCLOST;
void System_Normal_process(void)
{
  if(prev_sys_state != System.state)
  {
    prev_sys_state = System.state;
    Hint_LED = System_Alive_Hint;
  }
  
}

/**
 * @brief ϵͳ��ǰ״̬�ĸı� Ϊ���жϵ�һ�ν��룬��RC�������е���
 * @param 
 */
void prev_sys_state_Err(System_State_t a)
{
  prev_sys_state = a;
}

