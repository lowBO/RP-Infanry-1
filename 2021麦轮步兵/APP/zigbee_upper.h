#ifndef __ZIGBEE_SENSOR_H
#define __ZIGBEE_SENSOR_H
#include "Device.h"

#define FPC_FRAME_HEADER		(0xA5)

typedef enum 
{
  SOF_FPC = 0,
  CRC8_FPC = 1,
  CHAS_Data_Offset = 2,
  FPC_FRAME_HEADER_LEN = 2,// ����
  DATA_LEN = 22,
}FPC_Data_Offset_t;

typedef enum
{
  CHAS = 0,
}FPC_Data_ID_t;

/* ֡ͷ��ʽ */
typedef __packed struct
{
	uint8_t  			sof;		// ͬ��ͷ
//  Data_ID_t     data_id;
	uint8_t  			crc8;		// CRC8У����
} FPC_Frame_Header_t;

/* ֡β��ʽ */
typedef __packed struct 
{
	uint16_t crc16;					// CRC16У����
} FPC_Frame_Tailer_t;


typedef __packed struct
{
  //�޸ĺ�ǵø������DATA_LEN
  
//  int16_t CHAS_OUT_CHAS_LF;
//  int16_t CHAS_OUT_CHAS_RF;
//  int16_t CHAS_OUT_CHAS_LB;
//  int16_t CHAS_OUT_CHAS_RB;
//  int16_t YAW_OUT;
//  int16_t PIT_OUT;
  
  float Speed_LF;
  float Speed_LB;
  float Speed_RF;
  float Speed_RB;
  float PIT_Angle;
  int16_t rc1;
}FPC_CHAS_Data_t;

typedef __packed struct
{
  //֡ͷ
  FPC_Frame_Header_t FPC_Frame_Header;
  //���ݶ�
  FPC_CHAS_Data_t FPC_CHAS_Data;
  
}FPC_DataInfo_t;


typedef struct
{
  FPC_DataInfo_t RxDataInfo;
  FPC_DataInfo_t TxDataInfo;
}FPC_t;


void ZIGBEE_SendData(void);
bool ZIGBEE_ReceiveData(uint8_t *Rx);

#endif
