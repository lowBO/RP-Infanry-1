/***      �� �������ƴ��� ��

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
 

#include "system.h"
#include "Device.h"
#include "Function.h"
#include "FreeRTOS_Init.h"

uint32_t currentTime = 0;

/**
 * @brief �豸���ʼ��
 * @param 
 */
void Device_Init(void)
{
  /* ���������豸���ʼ�� */
  MODULE_Init();
  MOTOR_Init();
  IMU_Init();
  Kalman_Init();
}

void Function_Init(void)
{
  /* ���⹦�ܳ�ʼ�� */
    //�Ӿ�
    Vision_Init();
    AutoAimInit();
}
/**
 * @brief ϵͳ��ʼ������
 */
void System_Init(void)
{
	Delay_init(168);// 1ms Systick
	CRC_init();	
	CAN1_Init();
	CAN2_Init();
  Led_Init();
	usart2_Init();
  UART5_Init();
  UART4_Init();
  USART1_Init();
  USART3_Init(); 
  
  Device_Init();
  Function_Init();

  Time_Init();
  IWDG_Init(4,250); //���Ź���ʼ�������Ƶ��Ϊ64,����ֵΪ250,���ʱ��Ϊ0.5s	
  FreeRTOS_Init();
}

/* -----------------Init start--------------------- */

/* ϵͳ��Ϣ�ṹ���ʼ�� */
Sys_Info_t System = 
{
  .state = SYSTEM_RCLOST,         //Ĭ��ʧ��
  .ctrl_mode = Ctrl_Err,      //Ĭ��ң��������
  .pid_mode = PID_Err,               //Ĭ�ϻ�еģʽ
  .action_mode = ACT_Err,  //Ĭ����ͨ�˶���ʽ
  .Defense_Mode = Defense_SPIN,
};

/* ------------------Init end---------------------- */

/**
 * @brief ״̬������
 * @param ��������SYSTEM_STATE_TASK_TIM
 */
void SYSTEM_STATE_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    /* ϵͳι�� */
    IWDG_Feed();
    /* ϵͳ״̬���� */
    system_state_Ctrl();
    /* ϵͳ״̬�� */
    System_LED_Hint(Hint_LED);
    /* ϵͳ����״̬ͬ����ȡ */
    Car_StateSync(&System.car_actFLAG);
    /* ϵͳ��������/����״̬��ȡ */
    User_StateSyne(&System.user_state);
    
    #if (Master == MASTER_DOWN)
    /* ������������Kp�����ȶ� */
    Calm_BMI_Kp();
    #endif
    
    vTaskDelayUntil(&currentTime, SYSTEM_STATE_TASK_TIM);//������ʱ
	}
}


/**
 * @brief ��̨����
 * @param ��������GIMBAL_TASK_TIM
 */
void GIMBAL_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    GIM_GET_Info();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        GIMBAL_Ctrl();
        break;
      case SYSTEM_RCLOST:
        GIM_Reset();
        break;
      case SYSTEM_RCERR :
        GIM_Reset();
        break;
    }
    vTaskDelayUntil(&currentTime, GIMBAL_TASK_TIM);//������ʱ
	}
}
/**
 * @brief ��������
 * @param ��������CHASSIS_TASK_TIM
 */
void CHASSIS_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    CHAS_GET_Info();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        CHASSIS_Ctrl();
        break;
      case SYSTEM_RCLOST:
        CHAS_Reset();
        break;
      case SYSTEM_RCERR :
        CHAS_Reset();        
        break;
    }
    vTaskDelayUntil(&currentTime, CHASSIS_TASK_TIM);//������ʱ
	}
}

/**
 * @brief ��������
 * @param ��������MODULE_TASK_TIM
 */
void MODULE_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    MODULE_GetInfo();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        MODULE_Ctrl();
        break;
      case SYSTEM_RCLOST: 
        MODULE_Reset();
        break;
      case SYSTEM_RCERR:  
        MODULE_Reset();
        break;
    }
    vTaskDelayUntil(&currentTime, MODULE_TASK_TIM);//������ʱ
	}
}
/**
 * @brief ��������
 * @param ��������REVOLVER_TASK_TIM
 */
void RIFLE_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    RIFLE_GET_Info();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        RIFLE_Ctrl();
        break;
      case SYSTEM_RCLOST:
        RIFLE_Reset();
        break;
      case SYSTEM_RCERR :
        RIFLE_Reset();
        break;        
    }     
    vTaskDelayUntil(&currentTime, RIFLE_TASK_TIM);//������ʱ
	}
}
/**
 * @brief IMU����
 * @param ��������IMU_TASK_TIM  
 */
void IMU_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    IMU_Ctrl();
    
    vTaskDelayUntil(&currentTime, IMU_TASK_TIM);//������ʱ
	}
}

/**
 * @brief �Ӿ�����
 * @param ��������VISION_TASK_TIM
 */
float test_tast_tim = 2;
void VISION_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    VISION_GET_Info();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        VISION_Ctrl();
        break;
      case SYSTEM_RCLOST:
        Vision_Reset();
        break;
      case SYSTEM_RCERR :
        Vision_Reset();
        break;
    }  
    vTaskDelayUntil(&currentTime, VISION_TASK_TIM);//������ʱ    
	}
}

/**
 * @brief PID����������
 * @param ��������PID_TASK_TIM
 */
void PID_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    PID_GET_Info();
    switch (System.state)
    {
      case SYSTEM_NORMAL:
        PID_Ctrl();
        break;
      case SYSTEM_RCLOST:
        PID_Reset();
        break;
      case SYSTEM_RCERR :
        PID_Reset();
        break;
    }    
    vTaskDelayUntil(&currentTime, PID_TASK_TIM);//������ʱ 
	}
}

/**
 * @brief Ӳ��������
 * @param ��������VISION_TRIGGER_TASK_TIM
 */
int test_task_tim_trig = 4;
void VISION_TRIGGER_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    Trigger();
    //Trigger_5ms();

    vTaskDelayUntil(&currentTime, test_task_tim_trig);//VISION_TRIGGER_TASK_TIM);//������ʱ
  }
}
//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void *p_arg)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
//    if(System.action_mode == SYS_ACT_AUTO_AIM)
		  Trigger();
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ

}



/**
 * @brief �������ع�ͨ����
 * @param ��������MASTERLINK_TASK_TIM
 */
void MASTERLINK_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    Master_Sent();
    
    vTaskDelayUntil(&currentTime, MASTERLINK_TASK_TIM);//������ʱ
  }
}

/**
 * @brief Zigbee��������
 * @param ��������ZIGBEE_TASK_TIM
 */
void ZIGBEE_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    ZIGBEE_SendData();
    
    vTaskDelayUntil(&currentTime, ZIGBEE_TASK_TIM);//������ʱ
  }
}

/**
 * @brief ͼ����������
 * @param ��������CUSUI_TASK_TIM
 */
void CUSUI_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    Startjudge_task();

    vTaskDelayUntil(&currentTime, CUSUI_TASK_TIM);//������ʱ
  }
}

/**
 * @brief ��������������
 * @param ��������SONIC_TASK_TIM
 */
void SONIC_TASK(void *p_arg)
{
  uint32_t currentTime;
  for(;;)   
	{	
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
    
    Sonic_Ctrl();

    vTaskDelayUntil(&currentTime, SONIC_TASK_TIM);//������ʱ
  }
}






