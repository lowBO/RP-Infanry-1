#include "zigbee_upper.h"

FPC_t FPC;


uint8_t zigbee_Tx[DATA_LEN] = {0};
uint8_t zigbee_Rx[DATA_LEN] = {0};



/*-------------------------������------------------------*/
int16_t zigbee_CHAS_Output[4] = {0};
int16_t zigbee_GIM_Output[2] = {0};
void Get_CHAS_Data(FPC_CHAS_Data_t *str)
{
//  str->CHAS_OUT_CHAS_LF = zigbee_CHAS_Output[CHAS_LF];//CHAS_Report_Output_LF();
//  str->CHAS_OUT_CHAS_RF = zigbee_CHAS_Output[CHAS_RF];//CHAS_Report_Output_RF();
//  str->CHAS_OUT_CHAS_LB = zigbee_CHAS_Output[CHAS_LB];//CHAS_Report_Output_LB();
//  str->CHAS_OUT_CHAS_RB = zigbee_CHAS_Output[CHAS_RB];//CHAS_Report_Output_RB();

//  str->YAW_OUT = zigbee_GIM_Output[GIM_YAW];
//  str->PIT_OUT = zigbee_GIM_Output[GIM_PIT];
  
  str->Speed_LB = CHAS_Report_Speed_LB();
  str->Speed_LF = CHAS_Report_Speed_LF();
  str->Speed_RB = CHAS_Report_Speed_RB();
  str->Speed_RF = CHAS_Report_Speed_RF();
  str->rc1 = RC_CH1;
//  str->PIT_Angle = DUM_Report_CHAS_IMU_PIT_Angle();
  
  memcpy(&zigbee_Tx[CHAS_Data_Offset] , str , sizeof(FPC_CHAS_Data_t));
}

void ZIGBEE_SendData(void)
{
  float Frame_Len = sizeof(FPC_DataInfo_t);
  /* д��֡ͷ */
  zigbee_Tx[SOF_FPC] = FPC_FRAME_HEADER;
  /* д��֡ͷCRC8 */
  Append_CRC8_Check_Sum(zigbee_Tx , FPC_FRAME_HEADER_LEN);
  /* ���ݶ���� */
  Get_CHAS_Data(&FPC.TxDataInfo.FPC_CHAS_Data);

//  /*��������*/
//	for(int i = 0; i < Frame_Len; i++) {
//		USART1_SendChar(zigbee_Tx[i]);
//	}
  /*����ͬ��*/
  memcpy(&FPC.TxDataInfo , zigbee_Tx ,Frame_Len);
	/* �������ݰ����� */
	memset(zigbee_Tx, 0, Frame_Len);
}



/*-------------------------������------------------------*/
bool ZIGBEE_ReceiveData(uint8_t *Rx)
{
  float Frame_Len = sizeof(FPC_DataInfo_t);
  bool res = false;
	/* ֡���ֽ��Ƿ�Ϊ0xA5 */
	if(Rx[SOF_FPC] == FPC_FRAME_HEADER) 
	{
		/* ֡ͷCRC8У��*/
		if(Verify_CRC8_Check_Sum( Rx, FPC_FRAME_HEADER_LEN ))
		{
      /* ������ȷ�򿽱����հ� */
      memcpy(&FPC.RxDataInfo, Rx, Frame_Len);
      res = true;
    }else res = false;
	}else res = false;
  return res;
}
