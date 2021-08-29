#include "Sonic.h"

Sonic_Info_t  Sonic_Info = {

  .Fly_Info.time = 0,
  .Fly_Info.distance = 0,
  
  .Park_Info.FL_TIM = 0,
  .Park_Info.FL_DIS = 0,
  
  .Park_Info.FR_TIM = 0,
  .Park_Info.FR_DIS = 0,
  
  .Park_Info.R_TIM = 0,
  .Park_Info.R_DIS = 0,
  
  .Fly_Info.IF_Data_Update = YES,
  .Park_Info.IF_Data_Update_FL = YES,
  .Park_Info.IF_Data_Update_FR = YES,
  .Park_Info.IF_Data_Update_R = YES,
};

void Sonic_Ctrl(void)
{
  if(Sonic_Info.Fly_Info.IF_Data_Update)
    KS103_FLY_Explore();
  
  if(Sonic_Info.Park_Info.IF_Data_Update_FL)
    KS103_FL_Explore();
  
  if(Sonic_Info.Park_Info.IF_Data_Update_FR)
    KS103_FR_Explore();
  
  if(Sonic_Info.Park_Info.IF_Data_Update_R)
    KS103_R_Explore();
}

#define SONIC_SPEED 0.34f  			//unit mm/us
void Sonic_ReadData_Fly(uint8_t *rxBuf)
{
  int16_t sonic_time = 0;
  //��ȡ���Ҵ�����յ������� 
  sonic_time = (((uint16_t)(rxBuf[0])<<8) + (uint16_t)rxBuf[1]);
  //��¼ʱ������
	Sonic_Info.Fly_Info.time = sonic_time;
	//��ʱ����������
	Sonic_Info.Fly_Info.distance = SONIC_SPEED * sonic_time /2.f;
  //���ݸ��±�־λ��1
	Sonic_Info.Fly_Info.IF_Data_Update = YES;
}

void Sonic_ReadData_FL(uint8_t *rxBuf)
{
  int16_t sonic_time = 0;
  //��ȡ���Ҵ�����յ������� 
  sonic_time = (((uint16_t)(rxBuf[0])<<8) + (uint16_t)rxBuf[1]);
  //��¼ʱ������
	Sonic_Info.Park_Info.FL_TIM = sonic_time;
	//��ʱ����������
	Sonic_Info.Park_Info.FL_DIS = SONIC_SPEED * sonic_time /2.f;
  //���ݸ��±�־λ��1
	Sonic_Info.Park_Info.IF_Data_Update_FL = YES;
}

void Sonic_ReadData_FR(uint8_t *rxBuf)
{
  int16_t sonic_time = 0;
  //��ȡ���Ҵ�����յ������� 
  sonic_time = (((uint16_t)(rxBuf[0])<<8) + (uint16_t)rxBuf[1]);
  //��¼ʱ������
	Sonic_Info.Park_Info.FR_TIM = sonic_time;
	//��ʱ����������
	Sonic_Info.Park_Info.FR_DIS = SONIC_SPEED * sonic_time /2.f;
  //���ݸ��±�־λ��1
	Sonic_Info.Park_Info.IF_Data_Update_FR = YES;
}

void Sonic_ReadData_R(uint8_t *rxBuf)
{
  int16_t sonic_time = 0;
  //��ȡ���Ҵ�����յ������� 
  sonic_time = (((uint16_t)(rxBuf[0])<<8) + (uint16_t)rxBuf[1]);
  //��¼ʱ������
	Sonic_Info.Park_Info.R_TIM = sonic_time;
	//��ʱ����������
	Sonic_Info.Park_Info.R_DIS = SONIC_SPEED * sonic_time /2.f;
  //���ݸ��±�־λ��1
	Sonic_Info.Park_Info.IF_Data_Update_R = YES;
}


//���³�����
void KS103_FLY_Explore(void)
{
	//ks103����  
	static uint8_t TxBuf[3] = {0xd8,0x02,0x0a};
	if(Sonic_Info.Fly_Info.IF_Data_Update)
	{
		USART1_SendChar(TxBuf[0]);
		delay_us(100);
		
		USART1_SendChar(TxBuf[1]);
		delay_us(100);
		
		USART1_SendChar(TxBuf[2]);
		
		Sonic_Info.Fly_Info.IF_Data_Update = NO;
	}
}
//��ǰ��λ������
void KS103_FL_Explore(void)
{
	//ks103����  
	static uint8_t TxBuf[3] = {0xe8,0x02,0x0a};
	if(Sonic_Info.Park_Info.IF_Data_Update_FL)
	{
		UART4_SendChar(TxBuf[0]);
		delay_us(100);
		
		UART4_SendChar(TxBuf[1]);
		delay_us(100);
		
		UART4_SendChar(TxBuf[2]);
		
		Sonic_Info.Park_Info.IF_Data_Update_FL = NO;
	}
}
//��ǰ��λ������
void KS103_FR_Explore(void)
{
	//ks103����  
	static uint8_t TxBuf[3] = {0xe8,0x02,0x0a};
	if(Sonic_Info.Park_Info.IF_Data_Update_FR)
	{
		USART3_SendChar(TxBuf[0]);
		delay_us(100);
		
		USART3_SendChar(TxBuf[1]);
		delay_us(100);
		
		USART3_SendChar(TxBuf[2]);
		
		Sonic_Info.Park_Info.IF_Data_Update_FR = NO;
	}
}
//�����ұ߶�λ������
void KS103_R_Explore(void)
{
	//ks103����  
	static uint8_t TxBuf[3] = {0xd8,0x02,0x0a};
	if(Sonic_Info.Park_Info.IF_Data_Update_R)
	{
		USART1_SendChar(TxBuf[0]);
		delay_us(100);
		
		USART1_SendChar(TxBuf[1]);
		delay_us(100);
		
		USART1_SendChar(TxBuf[2]);
		
		Sonic_Info.Park_Info.IF_Data_Update_R = NO;
	}
}



//�ж��Ƿ����
Sonic_mode_t Judge_IF_Fly(void)
{
  Sonic_mode_t res;
  
  if(Sonic_Info.Fly_Info.distance >= FLY_DIS)
  {
    Sonic_Info.Sonic_mode = FLY;
    res = FLY;
  }
  else 
  {
    Sonic_Info.Sonic_mode = NO_FLY;
    res = NO_FLY;
  }
  
  return res;
}

/* ǰ����Ķ�λ�ж� */
Sonic_mode_t Park_Judge_F(void)
{
  Sonic_mode_t res;
  res = Judge_IF_Fly();
  if(res != FLY)//û�з���
  {
    if(Sonic_Info.Park_Info.FL_DIS - FL_DIS_Standard >18 && 
       Sonic_Info.Park_Info.FR_DIS - FR_DIS_Standard >18  ) //�����Զ
    {
      res = PARK_MoveFront;
    }
    else if(Sonic_Info.Park_Info.FL_DIS - FL_DIS_Standard < -18 && 
            Sonic_Info.Park_Info.FR_DIS - FR_DIS_Standard < -18  ) //�����Զ
    {
      res = PARK_MoveBehind;
    }
    else //����ʼ��
    {
      res = PARK_FrontGood;
    }
  }
  return res;
}

Sonic_mode_t Park_Judge_Z(void)
{
  Sonic_mode_t res;
  res = Judge_IF_Fly();
  if(res != FLY)//û�з���
  {
    if(Sonic_Info.Park_Info.FL_DIS < Sonic_Info.Park_Info.FR_DIS - 25)//��ͷ����
      res = PARK_TurnLeft;//��ת
    else if(Sonic_Info.Park_Info.FL_DIS > Sonic_Info.Park_Info.FR_DIS + 25)//��ͷ����
      res = PARK_TurnRigh;//��ת
    else 
      res = PARK_TurnGood;
  }
  return res;
}


/* ���ҷ���Ķ�λ�ж� */
Sonic_mode_t Park_Judge_R(void)
{
  Sonic_mode_t res;
  res = Judge_IF_Fly();
  if(res != FLY)//û�з���
  {
    if(Sonic_Info.Park_Info.R_DIS - R_DIS_Standard > 15)//�ұ߾���̫Զ
      res = PARK_MoveRigh;//��ƽ��
    
    else if(Sonic_Info.Park_Info.R_DIS - R_DIS_Standard < -15)//�ұ߾���̫��
      res = PARK_MoveLeft;//��ƽ��
    
    else 
      res = PARK_RighGood;
  }
 
  return res;
}



//-------------------------------�ϱ����̿���ָ��--------------------��chassis.c����
//��������λ��master_RTX.C��
extern Sonic_mode_t DUM_Report_Park_Fmove(void);
extern Sonic_mode_t DUM_Report_Park_Rmove(void);
extern Sonic_mode_t DUM_Report_Park_Zmove(void);

float CHAS_Park_FB_Speed(void)
{
  float res = 0;
  switch(DUM_Report_Park_Fmove())
  {
    case PARK_MoveFront:
        res = 110;
        break;
    
    case PARK_MoveBehind:
        res = -110;
        break;
    
    case PARK_FrontGood:
        res = 0;
        break;
    
    default:
        res = 0;
        break;
  }
  return res;
}

float CHAS_Park_LR_Speed(void)
{
  float res = 0;
  if(DUM_Report_Park_Fmove() == PARK_FrontGood)//ǰ���λ���
  switch(DUM_Report_Park_Rmove())
  {
    case PARK_MoveLeft:
        res = 110;
        break;
    
    case PARK_MoveRigh:
        res = -110;
        break;
    
    case PARK_RighGood:
        res = 0;
        break;
    
    default:
        res = 0;
        break;
  }
  return res;
}

float CHAS_Park_Z_Speed(void)
{
  float res = 0;
  if(DUM_Report_Park_Fmove() == PARK_FrontGood)//ǰ���λ���
  switch(DUM_Report_Park_Zmove())
  {
    case PARK_TurnLeft:
        res = 105;
        break;
    
    case PARK_TurnRigh:
        res = -105;
        break;
    
    case PARK_TurnGood:
        res = 0;
        break;
    
    default:
        res = 0;
        break;
  }
  return res;
}


