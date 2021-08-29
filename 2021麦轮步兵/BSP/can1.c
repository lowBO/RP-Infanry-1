#include "can1.h"
#include "Device.h"



void CAN1_Init()
{
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;
	CAN_InitTypeDef can;
	CAN_FilterInitTypeDef filter;

	RCC_AHB1PeriphClockCmd(CAN1_IO_CLOCK,ENABLE);
	RCC_APB1PeriphClockCmd(CAN1_CLOCK,ENABLE);

	gpio.GPIO_Mode=GPIO_Mode_AF;
	gpio.GPIO_Pin=CAN1_IO_H|CAN1_IO_L;
	GPIO_Init(CAN1_IO_Port,&gpio);

	GPIO_PinAFConfig(CAN1_IO_Port,CAN1_IO_PinSource_L,GPIO_AF_CAN1);
	GPIO_PinAFConfig(CAN1_IO_Port,CAN1_IO_PinSource_H,GPIO_AF_CAN1);

	nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
  
  nvic.NVIC_IRQChannel = CAN1_TX_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 1;
  nvic.NVIC_IRQChannelSubPriority = 3;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic); 
	
	can.CAN_TTCM = DISABLE;		//��ʱ�䴥��ͨ��ģʽ
	can.CAN_ABOM = ENABLE;		//����Զ����߹���88888888888888
	can.CAN_AWUM = ENABLE;		//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)888888888888888
	can.CAN_NART = DISABLE;		//��ֹ�����Զ����� ���߸������һ��CAN ��Ӱ�췢�� ��ʱ�ɸ�ΪENABLE
	can.CAN_RFLM = DISABLE;		//���Ĳ��������µĸ��Ǿɵ�
	can.CAN_TXFP = ENABLE;		//���ȼ��ɱ��ı�ʶ������
	can.CAN_BS1=CAN_BS1_9tq;
	can.CAN_BS2=CAN_BS2_4tq;
	can.CAN_Mode=CAN_Mode_Normal;
	can.CAN_Prescaler=3;
	can.CAN_SJW=CAN_SJW_1tq;
	CAN_Init(CAN1,&can);
	
	filter.CAN_FilterNumber=0;  							 			//������0
	filter.CAN_FilterMode=CAN_FilterMode_IdMask;   	//����ģʽ
	filter.CAN_FilterScale=CAN_FilterScale_32bit;   // 32λ��
	filter.CAN_FilterFIFOAssignment=0;              //������0������FIFO0
	filter.CAN_FilterActivation=ENABLE;   				  //���������
	filter.CAN_FilterIdHigh=0x0000;                 //32λID
	filter.CAN_FilterIdLow=0x0000;
	filter.CAN_FilterMaskIdHigh=0x0000;             //32λMask
	filter.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInit(&filter);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);    ////FIFO0��Ϣ�Һ��ж�����
  CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


CanTxMsg Tx_CAN1;
void CAN1_Send(uint32_t Equipment_ID,int16_t *Data)		//���̵��
{		
	Tx_CAN1.StdId = Equipment_ID;					 //ʹ�õ���չID�����820R��ʶ��0X200
	Tx_CAN1.IDE = CAN_ID_STD;				 //��׼ģʽ
	Tx_CAN1.RTR = CAN_RTR_DATA;			 //����֡RTR=0��Զ��֡RTR=1
	Tx_CAN1.DLC = 8;							 	 //���ݳ���Ϊ8�ֽ�

	Tx_CAN1.Data[0] = Data[0]>>8; 
	Tx_CAN1.Data[1] = Data[0];
	Tx_CAN1.Data[2] = Data[1]>>8; 
	Tx_CAN1.Data[3] = Data[1];
	Tx_CAN1.Data[4] = Data[2]>>8; 
	Tx_CAN1.Data[5] =	Data[2];
	Tx_CAN1.Data[6] = Data[3]>>8; 
	Tx_CAN1.Data[7] =	Data[3];

	CAN_Transmit(CAN1, &Tx_CAN1);	//��������
}

uint8_t CAN1_DUM_Send(uint32_t Equipment_ID,uint8_t *Data)
{
	Tx_CAN1.StdId = Equipment_ID;					 //ʹ�õ���չID�����820R��ʶ��0X200
	Tx_CAN1.IDE = CAN_ID_STD;				 //��׼ģʽ
	Tx_CAN1.RTR = CAN_RTR_DATA;			 //����֡RTR=0��Զ��֡RTR=1
	Tx_CAN1.DLC = 8;							 	 //���ݳ���Ϊ8�ֽ�
  
  memcpy(Tx_CAN1.Data,Data,8);

	CAN_Transmit(CAN1, &Tx_CAN1);	//��������
  return 8;
}


void CAN1_RX0_IRQHandler()
{
  CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!=RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);		//����жϹ���
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);		//����can����
    CAN1_time = micros() + 30000;
	}
  DataUpdate(&RxMessage);//�����ز��������ж�
}

void CAN1_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
	}
}

/**
 * @brief ���ݽ��롢ת��
 * @param 
 */
void Data_Decode(CanRxMsg *Rx , CAN_GET_DATA_t *str)
{
  CAN_GET_DATA_t Data;
  
  Data.Motor_Angle = (Rx->Data[0]<<8)|Rx->Data[1];
  
  Data.Motor_Speed = (Rx->Data[2]<<8)|Rx->Data[3];
  
  Data.Motor_ELC = (Rx->Data[4]<<8)|Rx->Data[5];
  
  Data.temp = Rx->Data[6];
  
  memcpy(str,&Data,sizeof(CAN_GET_DATA_t));
}


/**
 * @brief ������ݸ���
 * @param 
 */
void DataUpdate(CanRxMsg *Rx)
{
  switch (Rx->StdId)
  {
    case CHAS_LF_ID:
      Data_Decode(Rx,&Chassis.CHAS_Motor[CHAS_LF].motor_data.CAN_GetData);
      break;
    case CHAS_RF_ID:
      Data_Decode(Rx,&Chassis.CHAS_Motor[CHAS_RF].motor_data.CAN_GetData);
      break;
    case CHAS_LB_ID:
      Data_Decode(Rx,&Chassis.CHAS_Motor[CHAS_LB].motor_data.CAN_GetData);
      break;
    case CHAS_RB_ID:
      Data_Decode(Rx,&Chassis.CHAS_Motor[CHAS_RB].motor_data.CAN_GetData);
      break;
    case GIM_YAW_ID:
      Data_Decode(Rx,&Gimbal.YAW.motor_data.CAN_GetData);
      break;
    case GIM_PIT_ID:
      Data_Decode(Rx,&Gimbal.PIT.motor_data.CAN_GetData);
      break;
    
    case GameRobotStat_ID:    
      DUM_Connect_time = micros() + 1000000;
      DUM_Data_Receive(Rx->Data,GameRobotStat_ID);
      break;
    case PowerHeatData_ID:    
      DUM_Connect_time = micros() + 1000000;
      DUM_Data_Receive(Rx->Data,PowerHeatData_ID);
      break;
    case IMU_DATA_ID :
      DUM_Connect_time = micros() + 1000000;
      DUM_Data_Receive(Rx->Data,IMU_DATA_ID);
      break;
    case ShootSpeed_ID:
      DUM_Connect_time = micros() + 1000000;
      Reset_Block_num();
      DUM_Data_Receive(Rx->Data,ShootSpeed_ID);
      break;
    
    case SuperCap_rx_ID:
      DUM_Data_Receive(Rx->Data,SuperCap_rx_ID);
      break;
    
    case UI_Ctrl_ID:
      DUM_Data_Receive(Rx->Data,UI_Ctrl_ID);
      break;
    
    default:
      break;    
  }
}






/**
 * @brief CAN1ϵͳ�Ƿ�����
 * @param 
 */
bool Judge_IF_CAN1_Normal(void)
{
  bool res = true;
  if(micros() >= CAN1_time)
  {
    res = false;
  }
  return res;
}


/**
 * @brief CAN1ϵͳ�Ƿ�����
 * @param 
 */
bool Judge_IF_DUM_Normal(void)
{
  bool res = true;
  if(micros() >= DUM_Connect_time)
  {
    res = false;
  }
  if(!IF_MASTER_DOWN_CONNECT) res = true;
  return res;
}
