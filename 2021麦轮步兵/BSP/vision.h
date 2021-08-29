#ifndef __VISION_H_
#define __VISION_H_

#include "GO.h"


#define VISION_TX_BUFFER_LEN	50
#define VISION_FRAME_HEADER		(0xA5)

#define Trigger_IO_UP  	   GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define Trigger_IO_DOWN	   GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define Trigger_IO       PDout(13)


/**
 *	@brief	������ɫ
 */
typedef enum
{
  UNKNOWN = 0x00,
  I_AM_BLUE = 0x01,
  I_AM_RED = 0x02,
  BASE = 0x03,
}Color_t;

/**
 *	@brief	�Ӿ���ȡ��Ŀ
 */
typedef enum
{
	IF_LOCK_BUFF = 0, // ʶ�𵽷�
  IF_LOCK_ARMOR = 1,//ʶ��װ�װ�
  IF_FRAMEDROP = 2,
  IF_CHANGE_ARMOR = 3,//ʶ���л�װ�װ�
  IF_IDENTIFY_SPIN = 4,
  IF_CHANGE_ARMOR_BUFF = 5,
} Vision_Flag;

/**
 *	���->�Ӿ�
 */
typedef enum {
  NO_VISION = 0x00,//�ɿ���ʱ
	CMD_AIM_AUTO		= 0x01,	// ����
	CMD_AIM_SMALL_BUFF	= 0x02,	// ʶ��С��
	CMD_AIM_BIG_BUFF	= 0x03,	// ʶ����
	CMD_AIM_SENTRY		= 0x04,	// �����ڱ�
	CMD_AIM_BASE		= 0x05	,// �������
} Vision_Cmd_Id_t;

/* ֡ͷ��ʽ */
typedef __packed struct
{
	uint8_t  			sof;		// ͬ��ͷ
	Vision_Cmd_Id_t  	cmd_id;		// ������
	uint8_t  			crc8;		// CRC8У����
} Vision_Frame_Header_t;

/* ֡β��ʽ */
typedef __packed struct 
{
	uint16_t crc16;					// CRC16У����
} Vision_Frame_Tailer_t;

/* ֡ͷ�ֽ�ƫ�� */
typedef enum {
	 SOF_Vision    =  0 ,//֡ͷƫ��
	 CMD_ID_Vision	=  1 ,//IDƫ��
	 CRC8_Vision   =  2 ,//crc8ƫ��
	 DATA_Vision	 = 3 , //������ʼƫ��
	 LEN_FRAME_HEADER = 3	,	// ֡ͷ����
	 LEN_FRAME_TAILER = 2	,	// ֡βCRC16 
}Frame_Header_Offset_t;

/* �������ݳ�����Ϣ */
typedef struct {
	/* Std */
	uint8_t LEN_RX_DATA 			;	// �������ݶγ���
  uint8_t LEN_RX_PACKET	    ;	// ���հ���������
} DataRX_Length_t;

/* �������ݳ�����Ϣ */
typedef struct {
	/* Std */
  uint8_t TX_CRC16          ;//crc16ƫ�� 
	uint8_t LEN_TX_DATA 		  ;	// �������ݶγ���
	uint8_t LEN_TX_PACKET	    ;	// ���Ͱ���������
} DataTX_Length_t;

//------------------------------�����------------------------


/* �������ݶθ�ʽ */
typedef __packed struct 
{
	float 	pitch_angle;	// pitchƫ��Ƕ�/���ص�	��λ���Ƕ�/���ص�
	float 	yaw_angle;		// yawƫ��Ƕ�/���ص�	��λ���Ƕ�/���ص�
	float 	distance;			// ����				��λ��mm
	uint8_t identify_framedrop;	// �Ƿ��֡		��λ��0/1
	uint8_t identify_target;// �Ƿ�ʶ��Ŀ��	��λ��0/1
	uint8_t identify_buff;	// �Ƿ�ʶ��Buff	��λ��0/1
	uint8_t identify_too_close;	// Ŀ��������	��λ��0/1
	uint8_t anti_gyro;	// �Ƿ�ʶ��С����	��λ��0/1
	uint8_t	change_armor;	// �Ƿ��ڷ�����״̬���л�װ�װ�	��λ��0/1
} BuffAim_Rx_Data_t;

/* ����������ݶθ�ʽ */
typedef __packed struct
{
	uint8_t fric_speed;		// ���ٵ�λ(���ݵȼ�����)
	Color_t my_color;			// �������Լ�����ɫ
  float IMU_YAW;
  float IMU_PIT;
  bool IF_CHANGE_PLAN;
} BuffAim_Tx_Data_t;

/* ������հ���ʽ */
typedef __packed struct 
{
	Vision_Frame_Header_t FrameHeader;	// ֡ͷ
	BuffAim_Rx_Data_t	  RxData;		// ����
	Vision_Frame_Tailer_t FrameTailer;	// ֡β	
} BuffAim_Rx_Packet_t;


/* ������Ͱ���ʽ */
typedef __packed struct
{
	Vision_Frame_Header_t FrameHeader;	// ֡ͷ
	BuffAim_Tx_Data_t	  TxData;		// ����
	Vision_Frame_Tailer_t FrameTailer;	// ֡β		
} BuffAim_Tx_Packet_t;

/*���ն˵���Ϣ*/
typedef struct
{
  BuffAim_Rx_Packet_t Packet; 
  DataRX_Length_t  LEN;
}BuffAim_Rx_Info_t;

/*���Ͷ˵���Ϣ*/
typedef struct
{
  BuffAim_Tx_Packet_t Packet;
  DataTX_Length_t  LEN;
}BuffAim_Tx_Info_t;




//------------------------------������------------------------

/* �������ݶθ�ʽ */
typedef __packed struct 
{
	float 	pitch_angle;	// pitchƫ��Ƕ�/���ص�	��λ���Ƕ�/���ص�
	float 	yaw_angle;		// yawƫ��Ƕ�/���ص�	��λ���Ƕ�/���ص�
	float 	distance;			// ����				��λ��mm
	uint8_t identify_framedrop;	// �Ƿ��֡		��λ��0/1
	uint8_t identify_target;// �Ƿ�ʶ��Ŀ��	��λ��0/1
	uint8_t identify_buff;	// �Ƿ�ʶ��Buff	��λ��0/1
	uint8_t identify_too_close;	// Ŀ��������	��λ��0/1
	uint8_t anti_gyro;	// �Ƿ�ʶ��С����	��λ��0/1
	uint8_t	change_armor;	// �Ƿ��ڷ�����״̬��/���״̬�л�װ�װ�	��λ��0/1
} AutoAim_Rx_Data_t;

/* ���鷢�����ݶθ�ʽ */
typedef __packed struct
{
  //����50���ֽھ���Ҫ�޸ķ��ͻ���ĳ���
	uint8_t fric_speed;		// ���ٵ�λ(���ݵȼ�����)
	Color_t my_color;			// �������Լ�����ɫ    //0����ɫ ���˺�ɫ 1�Һ�ɫ
  float IMU_YAW;
  float IMU_PIT;
  bool IF_anti_top;
} AutoAim_Tx_Data_t;

/* ������հ���ʽ */
typedef __packed struct 
{
	Vision_Frame_Header_t FrameHeader;	// ֡ͷ
	AutoAim_Rx_Data_t	  RxData;		// ����
	Vision_Frame_Tailer_t FrameTailer;	// ֡β	
} AutoAim_Rx_Packet_t;

/* ���鷢�Ͱ���ʽ */
typedef __packed struct
{
	Vision_Frame_Header_t FrameHeader;	// ֡ͷ
	AutoAim_Tx_Data_t	  TxData;		// ����
	Vision_Frame_Tailer_t FrameTailer;	// ֡β		
} AutoAim_Tx_Packet_t;

/*���ն˵���Ϣ*/
typedef struct
{
  AutoAim_Rx_Packet_t Packet;
  DataRX_Length_t  LEN;
}AutoAim_Rx_Info_t;

/*���Ͷ˵���Ϣ*/
typedef struct
{
  AutoAim_Tx_Packet_t Packet;
  DataTX_Length_t  LEN;
}AutoAim_Tx_Info_t;

//------------------------------------------



/*���<-->�Ӿ� ͨ����Ϣ*/
typedef struct
{
  BuffAim_Rx_Info_t BuffAim_RX;
  BuffAim_Tx_Info_t BuffAim_Tx;
  AutoAim_Rx_Info_t AutoAim_Rx;
  AutoAim_Tx_Info_t AutoAim_Tx;
}VisionRTx_t;

typedef struct
{
  int FrameRate;
  float FrameTime;
  bool IF_GET_CNT;
}FrameRate_Cnt_t;


/*�Ӿ������ܿؽṹ��*/
typedef struct
{
  System_Action_t action_mode;
  VisionRTx_t  VisionRTx;
  Vision_Cmd_Id_t System_Cmd_Id;
  bool Trigger_Signal;
  FrameRate_Cnt_t FrameRate_Cnt;
}Vision_Info_t;

extern Vision_Info_t Vision;

void Set_IF_AutoAim(void);
void VISION_GET_Info(void);
void VISION_Ctrl(void);
void AUTO_AIM_Ctrl(void);
void BIG_BUFF_Ctrl(void);
void SMALL_BUFF_Ctrl(void);
void Vision_Reset(void);
void Vision_Init(void);
bool VISION_ReadData(uint8_t *rxBuf);   
void VISION_SendData(Vision_Cmd_Id_t cmd_id);

bool VISION_GetFlagStatus(Vision_Flag flag);

float Get_Aim_distance(void);
Color_t Judge_MyColor(uint8_t robotID);
float Get_FrameTime(void);
float YAW_GetAutoAimErr(void);
float PIT_GetAutoAimErr(void);
float Get_VisionDistance(void);
float YAW_GetBuffCoordinate(void);
float PIT_GetBuffCoordinate(void);

System_Action_t Vision_Handler(void); //�Ӿ���ģʽ���ƣ��ڲ�������
void Vision_OFF(void);               //�Ӿ��ر�
void Vision_BuffCmd_Switch(void);

void Trigger_ON(void);
void Trigger_OFF(void);
void VisionTrigger_Init(void);
void Trigger(void);//ż������ 2 4 6 8ms
void Trigger_5ms(void);//�������� 5ms
void TriggerSignal_YES(void);
void TriggerSignal_NO(void);
bool Report_TriggerSignal(void);

void Set_IF_ShootSentry(void);
void Reset_IF_ShootSentry(void);
bool Report_IF_ShoorSentry(void);
void Set_IF_BigBuff(void);
void Set_IF_SmallBuff(void);
void Reset_IF_BuffMode(void);

float YawVision_nolook(void);
float PitVision_nolook(void);

void Set_anti_GYRO(void);
void Reset_anti_GYRO(void);
bool Report_IF_anti_GYRO(void);

void Set_IF_CHANGE_PLAN_BUFF(void);
void Reset_IF_CHANGE_PLAN_BUFF(void);
bool Report_IF_CHANGE_PLAN_BUFF(void);

void Set_ShootBase(void);
void Reset_ShootBase(void);
bool Report_IF_ShootBase(void);

#endif
