#include "system.h"

static volatile uint32_t usTicks = 0;
//�����˲�
float Slope(float M ,float *queue ,uint16_t len)
{
	float sum=0;
	float res=0;
  
		//����������FIFO��
		for(uint16_t i=0;i<len-1;i++)
		{
			queue[i] = queue[i+1];
			//���¶���
		}
		queue[len-1] = M;
    
	//���������
	for(uint16_t j=0;j<len;j++)
	{
		sum+=queue[j];
	}
	res = sum/(len);
	
	return res;
}


	
//�޷�
float constrain(float amt,float high,float low)
{
	if (amt < low)
		return low;
	else if (amt > high)
		return high;
	else
		return amt;
}

//���޷���������
float anti_constrain(float amt,float high,float low)
{
	if (amt > low && amt < high)
		return 0;
	else
		return amt;
}
//int32_t constrain_int32(int32_t amt, int32_t low, int32_t high)
//{
//	if (amt < low)
//		return low;
//	else if (amt > high)
//		return high;
//	else
//		return amt;
//}

//int16_t constrain_int16(int16_t amt, int16_t low, int16_t high)
//{
//	if (amt < low)
//		return low;
//	else if (amt > high)
//		return high;
//	else
//		return amt;
//}

//int constrain_int(int amt,int low,int high)
//{
//	if (amt < low)
//		return low;
//	else if (amt > high)
//		return high;
//	else
//		return amt;
//}

//��������ʼ��
static void cycleCounterInit(void)
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq(&clocks);
	usTicks = clocks.SYSCLK_Frequency / 1000000; 
}

//��΢��Ϊ��λ����ϵͳʱ��
uint32_t micros(void)
{
	register uint32_t ms, cycle_cnt;
	do {
			ms = sysTickUptime;
			cycle_cnt = SysTick->VAL;
	} while (ms != sysTickUptime);
	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

#if (SYSTEM_SUPPORT_OS == 0)
//΢�뼶��ʱ
void delay_us(uint32_t us)
{
	uint32_t now = micros();
	while (micros() - now < us);
}

//���뼶��ʱ
void delay_ms(uint32_t ms)
{
	while (ms--)
			delay_us(1000);
}
#endif

//�Ժ���Ϊ��λ����ϵͳʱ��
uint32_t millis(void)
{
	return sysTickUptime;
}

//ϵͳ��ʼ��
void systemInit(void)
{
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	//�δ�ʱ�����ã�1ms
}

//����ʱ��۲캯��
float tim1cnt = 0,tim2cnt = 0,timecnt = 0;
void Single_time_cal(void)
{
  if(System.TimeCal.cal_time < 30)
  {
    if(timecnt == 0)
      tim1cnt = micros();
    if(timecnt == 1)
      tim2cnt = micros();
    if(tim1cnt != 0 && tim2cnt != 0 )
    {
      System.TimeCal.time[System.TimeCal.cal_time] = tim2cnt - tim1cnt;
      System.TimeCal.cal_time++;
      timecnt = 0;
      tim1cnt = 0;
      tim2cnt = 0;
    }
    else   timecnt++;
  }
}


uint32_t Remote_time = 0;//ң����
uint32_t Refer_time = 0;//����ϵͳ
uint32_t CAN1_time = 0;//CAN1
uint32_t CAN2_time = 0;//CAN1
uint32_t DUM_Connect_time = 0;//����������ϵ
//ģ�鳬ʱ���Ӽ�ʱ��ʼ��
void Time_Init(void)
{
  Remote_time = micros();
  Refer_time = micros();
  CAN1_time = micros();
  CAN2_time = micros();
  DUM_Connect_time = micros();
}

//�ж��Ƿ����NAN
bool Judge_IF_NAN(float x )
{
  bool res = NO;
  res = (bool)__ARM_isnan((double)x);
  return res;
}


