#include "iwdg.h"
#include "Device.h"

/**
 * @note
   @���Ź���Ҫ��������ʱ�̵�ϵͳ����������Ŀǰû�г��ֹ��������
    Ҳ���ڼ����ջ��Ƿ��ڵ�����������ģʽ�ظ���Ƶ�л�
    ֮ǰ���ֹ������������ǽ��ջ���ң���ϻ������⣬����ʱ���Ź��ܹ�Ӧ���������������λ����
 */


//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//rlr:�Զ���װ��ֵ,0~0XFFF.
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶ�IWDG->PR IWDG->RLR��д
	
	IWDG_SetPrescaler(prer); //����IWDG��Ƶϵ��

	IWDG_SetReload(rlr);   //����IWDGװ��ֵ

	IWDG_ReloadCounter(); //reload
	
	IWDG_Enable();       //ʹ�ܿ��Ź�
}

//ι�������Ź�
void IWDG_Feed(void)
{
  /* ����û��nan && ��̨û��nan */
  if(!CHAS_Report_IF_NAN() && !GIM_Report_IF_NAN())
	IWDG_ReloadCounter();//reload
}
