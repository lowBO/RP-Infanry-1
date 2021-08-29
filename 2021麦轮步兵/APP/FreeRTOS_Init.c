#include "FreeRTOS_Init.h"


static u8  fac_us=0;						//us��ʱ������			   
static u16 fac_ms=0;						//ms��ʱ������,��os��,����ÿ�����ĵ�ms��
 


//��ʼ���ӳٺ���
//SYSTICK ��ʱ�ӹ̶�Ϊ AHB ʱ�ӣ������������� SYSTICK ʱ��Ƶ��Ϊ AHB/8
//����Ϊ�˼��� FreeRTOS�����Խ� SYSTICK ��ʱ��Ƶ�ʸ�Ϊ AHB ��Ƶ�ʣ�
//SYSCLK:ϵͳʱ��Ƶ��
void Delay_init(u8 SYSCLK)
{
	u32 reload;
	//SysTickƵ��ΪHCLK
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); 
	fac_us=SYSCLK;							//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
	reload=SYSCLK;							//ÿ���ӵļ������� ��λΪM	   
	reload*=1000000/configTICK_RATE_HZ;		//��configTICK_RATE_HZ�����ʱ��
											//reloadΪ24λ�Ĵ���,���ֵ:16777216,��168M��,Լ��0.0998s����	
	fac_ms=1000/configTICK_RATE_HZ;			//����OS������ʱ�����ٵ�λ	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//����SYSTICK�ж�
	SysTick->LOAD=reload; 					//ÿ1/delay_ostickspersec���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //����SYSTICK     
}								    

#if SYSTEM_SUPPORT_OS 
//��ʱnus
//nus:Ҫ��ʱ��us��.	
//nus:0~204522252(���ֵ��2^32/fac_us@fac_us=168)	    								   
void delay_us(u32 nus)
{ 
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;  //LOAD ��ֵ
	ticks=nus*fac_us; //��Ҫ�Ľ�����
	told=SysTick->VAL; //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL; 
		if(tnow!=told)
		{ 
			//����ע��һ�� SYSTICK ��һ���ݼ��ļ������Ϳ�����.
			if(tnow<told)tcnt+=told-tnow; 
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;  //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
	}
}; 
}//��ʱnms
//nms:Ҫ��ʱ��ms��
//nms:0~65535
void delay_ms(u32 nms)
{ 
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{ 
		if(nms>=fac_ms) //��ʱ��ʱ����� OS ������ʱ������
		{
			vTaskDelay(nms/fac_ms);  //FreeRTOS ��ʱ
		}
		nms%=fac_ms;  //OS �Ѿ��޷��ṩ��ôС����ʱ��,
		//������ͨ��ʽ��ʱ
	}
	delay_us((u32)(nms*1000)); //��ͨ��ʽ��ʱ
}
//��ʱ nms,���������������
//nms:Ҫ��ʱ�� ms ��
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}


#define START_TASK_PRIO		1			// �������ȼ�
#define START_STK_SIZE		128			// �����ջ��С
TaskHandle_t SystemStartTask_Handler;			// ������
extern void System_Start_Task(void *p_arg);
/* ## Task Manangement Table ## ------------------------------------------------*/
//--- Start Task ---//
// Defined in the init.c file => #define START_TASK_PRIO	1
//--- System State Task ---//
#define SYSTEM_STATE_TASK_PRIO				1		// �������ȼ�
#define SYSTEM_STATE_STK_SIZE				256		// �����ջ��С
TaskHandle_t SystemState_Task_Handler;				// ������
extern void SYSTEM_STATE_TASK(void *p_arg);
//--- Chassis Task ---//
#define CHASSIS_TASK_PRIO					2		// �������ȼ�
#define CHASSIS_STK_SIZE					256		// �����ջ��С
TaskHandle_t Chassis_Task_Handler;					// ������
extern void CHASSIS_TASK(void *p_arg);
//--- Gimbal Task ---//
#define GIMBAL_TASK_PRIO					2		// �������ȼ�
#define GIMBAL_STK_SIZE						256		// �����ջ��С
TaskHandle_t Gimbal_Task_Handler;					// ������
extern void GIMBAL_TASK(void *p_arg);
//--- Revolver Task ---//
#define RIFLE_TASK_PRIO					2		// �������ȼ�
#define RIFLE_STK_SIZE					256		// �����ջ��С
TaskHandle_t Rifle_Task_Handler;					// ������
extern void RIFLE_TASK(void *p_arg);
//--- Friction Task ---//
#define MODULE_TASK_PRIO						2		// �������ȼ�
#define MODULE_STK_SIZE						128		// �����ջ��С
TaskHandle_t Module_Task_Handler;						// ������
extern void MODULE_TASK(void *p_arg);
//--- Vision Task ---//
#define VISION_TASK_PRIO					1		// �������ȼ�
#define VISION_STK_SIZE						256		// �����ջ��С
TaskHandle_t Vision_Task_Handler;					// ������
extern void VISION_TASK(void *p_arg);
//--- Imu Task ---//
#define IMU_TASK_PRIO						1		// �������ȼ�
#define IMU_STK_SIZE						256		// �����ջ��С
TaskHandle_t Imu_Task_Handler;						// ������
extern void IMU_TASK(void *p_arg);
//--- PID Task ---//
#define PID_TASK_PRIO						3		// �������ȼ�
#define PID_STK_SIZE						256		// �����ջ��С
TaskHandle_t Pid_Task_Handler;						// ������
extern void PID_TASK(void *p_arg);
//--- Masterlink Task ---//
#define MASTERLINK_TASK_PRIO						1		// �������ȼ�
#define MASTERLINK_STK_SIZE						256		// �����ջ��С
TaskHandle_t Masterlink_Task_Handler;						// ������
extern void MASTERLINK_TASK(void *p_arg);
//--- CUSUI Task ---//
#define CUSUI_TASK_PRIO						1		// �������ȼ�
#define CUSUI_STK_SIZE						256		// �����ջ��С
TaskHandle_t CUSUI_Task_Handler;						// ������
extern void CUSUI_TASK(void *p_arg);
//--- ZIGBEE Task ---//
#define ZIGBEE_TASK_PRIO					1		// �������ȼ�
#define ZIGBEE_STK_SIZE						256		// �����ջ��С
TaskHandle_t ZIGBEE_Task_Handler;						// ������
extern void ZIGBEE_TASK(void *p_arg);
//--- TRIGGER Task ---//
#define TRIGGER_TASK_PRIO					1		// �������ȼ�
#define TRIGGER_STK_SIZE						256		// �����ջ��С
TaskHandle_t TRIGGER_Task_Handler;						// ������
extern void VISION_TRIGGER_TASK(void *p_arg);
//--- SONIC Task ---//
#define SONIC_TASK_PRIO					1		// �������ȼ�
#define SONIC_STK_SIZE						256		// �����ջ��С
TaskHandle_t SONIC_Task_Handler;						// ������
extern void SONIC_TASK(void *p_arg);

void FreeRTOS_Init(void)
{
	/* ������ʼ������ */
	xTaskCreate((TaskFunction_t		)System_Start_Task,						// ������
							(const char*		)"System_Start_Task",			// ��������
							(uint16_t			)START_STK_SIZE,		// �����ջ��С
							(void*				)NULL,					// ���ݸ��������Ĳ���
							(UBaseType_t		)START_TASK_PRIO,		// �������ȼ�
							(TaskHandle_t*		)&SystemStartTask_Handler);	// ������
	vTaskStartScheduler();	// �����������
}

void System_Start_Task(void *p_arg)
{
	taskENTER_CRITICAL();	// �����ٽ���
  if (Master == MASTER_UP)
  {
	/* ����ϵͳ״̬������ */
	xTaskCreate((TaskFunction_t		)SYSTEM_STATE_TASK,						// ������
							(const char*		)"system_state_task",		// ��������
							(uint16_t			)SYSTEM_STATE_STK_SIZE,		// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)SYSTEM_STATE_TASK_PRIO,	// �������ȼ�
							(TaskHandle_t*		)&SystemState_Task_Handler);	// ������
	/* ������������ */
	xTaskCreate((TaskFunction_t		)CHASSIS_TASK,							// ������
							(const char*		)"chassis_task",			// ��������
							(uint16_t			)CHASSIS_STK_SIZE,			// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)CHASSIS_TASK_PRIO,			// �������ȼ�
							(TaskHandle_t*		)&Chassis_Task_Handler);		// ������
	/* ������̨���� */
	xTaskCreate((TaskFunction_t		)GIMBAL_TASK,							// ������
							(const char*		)"gimbal_task",				// ��������
							(uint16_t			)GIMBAL_STK_SIZE,			// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)GIMBAL_TASK_PRIO,			// �������ȼ�
							(TaskHandle_t*		)&Gimbal_Task_Handler);		// ������							
	/* �������̵������ */
	xTaskCreate((TaskFunction_t		)RIFLE_TASK,							// ������
							(const char*		)"rifle_task",			// ��������
							(uint16_t			)RIFLE_STK_SIZE,			// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)RIFLE_TASK_PRIO,		// �������ȼ�
							(TaskHandle_t*		)&Rifle_Task_Handler);	// ������							
	/* ������������ */
	xTaskCreate((TaskFunction_t		)MODULE_TASK,								// ������
							(const char*		)"module_task",				// ��������
							(uint16_t			)MODULE_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)MODULE_TASK_PRIO,			// �������ȼ�
							(TaskHandle_t*		)&Module_Task_Handler);		// ������
	/* �����Ӿ����� */
	xTaskCreate((TaskFunction_t		)VISION_TASK,							// ������
							(const char*		)"vision_task",				// ��������
							(uint16_t			)VISION_STK_SIZE,			// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)VISION_TASK_PRIO,			// �������ȼ�
							(TaskHandle_t*		)&Vision_Task_Handler);		// ������
	/* ����IMU���� */
	xTaskCreate((TaskFunction_t		)IMU_TASK,								// ������
							(const char*		)"imu_task",				// ��������
							(uint16_t			)IMU_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)IMU_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&Imu_Task_Handler);
	/* ����PID���� */
	xTaskCreate((TaskFunction_t		)PID_TASK,								// ������
							(const char*		)"pid_task",				// ��������
							(uint16_t			)PID_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)PID_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&Pid_Task_Handler);
	/* ����Masterlink���� */
	xTaskCreate((TaskFunction_t		)MASTERLINK_TASK,								// ������
							(const char*		)"Masterlink_task",				// ��������
							(uint16_t			)MASTERLINK_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)MASTERLINK_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&Masterlink_Task_Handler);
//	/* ����ZIGBEE���� */
//	xTaskCreate((TaskFunction_t		)ZIGBEE_TASK,								// ������
//							(const char*		)"zigbee_task",				// ��������
//							(uint16_t			)ZIGBEE_STK_SIZE,				// �����ջ��С
//							(void*				)NULL,						// ���ݸ��������Ĳ���
//							(UBaseType_t		)ZIGBEE_TASK_PRIO,				// �������ȼ�
//							(TaskHandle_t*		)&ZIGBEE_Task_Handler);
	/* ����Ӳ�������� */
	xTaskCreate((TaskFunction_t		)VISION_TRIGGER_TASK,								// ������
							(const char*		)"trigger_task",				// ��������
							(uint16_t			)TRIGGER_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)TRIGGER_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&TRIGGER_Task_Handler);
  }
  if (Master == MASTER_DOWN)
  {
	/* ����ϵͳ״̬������ */
	xTaskCreate((TaskFunction_t		)SYSTEM_STATE_TASK,						// ������
							(const char*		)"system_state_task",		// ��������
							(uint16_t			)SYSTEM_STATE_STK_SIZE,		// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)SYSTEM_STATE_TASK_PRIO,	// �������ȼ�
							(TaskHandle_t*		)&SystemState_Task_Handler);	// ������
	/* ����Masterlink���� */
	xTaskCreate((TaskFunction_t		)MASTERLINK_TASK,								// ������
							(const char*		)"Masterlink_task",				// ��������
							(uint16_t			)MASTERLINK_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)MASTERLINK_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&Masterlink_Task_Handler);
	/* ����CUSUI���� */
	xTaskCreate((TaskFunction_t		)CUSUI_TASK,								// ������
							(const char*		)"CUSUI_task",				// ��������
							(uint16_t			)CUSUI_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)CUSUI_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&CUSUI_Task_Handler);
	/* ����IMU���� */
	xTaskCreate((TaskFunction_t		)IMU_TASK,								// ������
							(const char*		)"imu_task",				// ��������
							(uint16_t			)IMU_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)IMU_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&Imu_Task_Handler);
//	/* ����ZIGBEE���� */
//	xTaskCreate((TaskFunction_t		)ZIGBEE_TASK,								// ������
//							(const char*		)"zigbee_task",				// ��������
//							(uint16_t			)ZIGBEE_STK_SIZE,				// �����ջ��С
//							(void*				)NULL,						// ���ݸ��������Ĳ���
//							(UBaseType_t		)ZIGBEE_TASK_PRIO,				// �������ȼ�
//							(TaskHandle_t*		)&ZIGBEE_Task_Handler);
	/* ����SONIC���� */
	xTaskCreate((TaskFunction_t		)SONIC_TASK,								// ������
							(const char*		)"sonic_task",				// ��������
							(uint16_t			)SONIC_STK_SIZE,				// �����ջ��С
							(void*				)NULL,						// ���ݸ��������Ĳ���
							(UBaseType_t		)SONIC_TASK_PRIO,				// �������ȼ�
							(TaskHandle_t*		)&SONIC_Task_Handler);

  }
							
	vTaskDelete(SystemStartTask_Handler);	//ɾ����ʼ����
	taskEXIT_CRITICAL();	// �˳��ٽ���
}
			 
#endif
