#ifndef __REMOTE_H
#define __REMOTE_H


#include "Driver.h"


#if (Infantry == 1)
#define    KeySlope_FB_60W_NO     1
#define    KeySlope_FB_80W_NO     1.1
#define    KeySlope_FB_100W_NO    1.25
#define    KeySlope_FB_120W_NO    1.4
#define    KeySlope_FB_50W_NO     0.8

#define    KeySlope_FB_60W_YES    1.1
#define    KeySlope_FB_80W_YES    1.25
#define    KeySlope_FB_100W_YES   1.4
#define    KeySlope_FB_120W_YES   1.55
#define    KeySlope_FB_50W_YES    1

#define    KeySlope_LR_60W_NO     1
#define    KeySlope_LR_80W_NO     1.1
#define    KeySlope_LR_100W_NO    1.25
#define    KeySlope_LR_120W_NO    1.4
#define    KeySlope_LR_50W_NO     0.8

#define    KeySlope_LR_60W_YES    1.1
#define    KeySlope_LR_80W_YES    1.25
#define    KeySlope_LR_100W_YES   1.4
#define    KeySlope_LR_120W_YES   1.55
#define    KeySlope_LR_50W_YES    1

#elif (Infantry == 2)
#define    KeySlope_FB_60W_NO     1.7
#define    KeySlope_FB_80W_NO     2.8
#define    KeySlope_FB_100W_NO    4
#define    KeySlope_FB_120W_NO    6
#define    KeySlope_FB_50W_NO     1.2

#define    KeySlope_FB_60W_YES    4
#define    KeySlope_FB_80W_YES    5.5
#define    KeySlope_FB_100W_YES   8
#define    KeySlope_FB_120W_YES   10
#define    KeySlope_FB_50W_YES    4

#define    KeySlope_LR_60W_NO     2.8
#define    KeySlope_LR_80W_NO     3.3
#define    KeySlope_LR_100W_NO    5
#define    KeySlope_LR_120W_NO    7.8
#define    KeySlope_LR_50W_NO     2.5

#define    KeySlope_LR_60W_YES    3.3
#define    KeySlope_LR_80W_YES    5.7
#define    KeySlope_LR_100W_YES   9.5
#define    KeySlope_LR_120W_YES   11.8
#define    KeySlope_LR_50W_YES    3

#elif (Infantry == 3)
#define    KeySlope_FB_60W_NO     1
#define    KeySlope_FB_80W_NO     1.1
#define    KeySlope_FB_100W_NO    1.25
#define    KeySlope_FB_120W_NO    1.4
#define    KeySlope_FB_50W_NO     0.8

#define    KeySlope_FB_60W_YES    1.1
#define    KeySlope_FB_80W_YES    1.25
#define    KeySlope_FB_100W_YES   1.4
#define    KeySlope_FB_120W_YES   1.55
#define    KeySlope_FB_50W_YES    1

#define    KeySlope_LR_60W_NO     1
#define    KeySlope_LR_80W_NO     1.1
#define    KeySlope_LR_100W_NO    1.25
#define    KeySlope_LR_120W_NO    1.4
#define    KeySlope_LR_50W_NO     0.8

#define    KeySlope_LR_60W_YES    1.1
#define    KeySlope_LR_80W_YES    1.25
#define    KeySlope_LR_100W_YES   1.4
#define    KeySlope_LR_120W_YES   1.55
#define    KeySlope_LR_50W_YES    1
#endif



typedef enum 
{
  RC_NO_CHANGE = 0,
  RC_MID_2_UP ,
  RC_MID_2_DOWN,
  RC_UP_2_MID,
  RC_DOWM_2_MID,
  
  RC_Err_2_UP,
  RC_Err_2_MID,  
  RC_Err_2_DOWN,  
}RC_S_Change_t;

typedef enum 
{
  SW_MID =0,
  SW_UP , 
  SW_DOWM ,
}RC_SW_Change_t;
  

/*����״̬ö��*/
typedef enum 
{
  UP = 0,   //0
  PRESS,    //0->1
  SHORT_DOWN,//1�̰�
  DOWN,      //1����
  RELAX,    //1->0
}KEY_State_t;


/*����������Ϣ*/
typedef struct 
{
  int state_cnt ;
  KEY_State_t State;
  KEY_State_t prev_State;
  uint8_t prev_KEY_PRESS;
  uint8_t KEY_PRESS;
}KEY_Info_t;

/*����ʱ�� ���̰����ж�*/
#define CHANGE_TIM            5    //ms
#define LONG_CHANGE_TIM_W               1000   //ms
#define LONG_CHANGE_TIM_S               1000   //ms
#define LONG_CHANGE_TIM_A               1000   //ms
#define LONG_CHANGE_TIM_D               1000   //ms
#define LONG_CHANGE_TIM_Q               500    //ms
#define LONG_CHANGE_TIM_E               500    //ms
#define LONG_CHANGE_TIM_R               500    //ms
#define LONG_CHANGE_TIM_F               500    //ms
#define LONG_CHANGE_TIM_G               500    //ms
#define LONG_CHANGE_TIM_Z               500    //ms
#define LONG_CHANGE_TIM_X               500    //ms
#define LONG_CHANGE_TIM_C               500    //ms
#define LONG_CHANGE_TIM_V               500    //ms
#define LONG_CHANGE_TIM_B               300    //ms
#define LONG_CHANGE_TIM_CTRL            1000   //ms
#define LONG_CHANGE_TIM_SHIFT           500    //ms
#define LONG_CHANGE_TIM_MOUSE_L         350    //ms
#define LONG_CHANGE_TIM_MOUSE_R         500    //ms

/*ң���������ж�ʱ��*/
#define RC_S_TIM   50    //ms

/*����ٶ����ֵ����*/
#define Xmax    300//300
#define Ymax    300//300
/*��껬���˲�����*/
#define SF_LENGTH 70  

typedef struct
{
  float Slope;
  float MoveData;
  float K;
}KEY_DirInfo_t;

typedef struct
{
  KEY_DirInfo_t FB_dir;
  KEY_DirInfo_t LR_dir;
}KEY_MoveInfo_t;

typedef struct
{
  float SFX[SF_LENGTH]; 
  float SFY[SF_LENGTH];  
}Mouse_SF_t;

/*������̰�����Ϣ*/
typedef struct 
{
  KEY_Info_t W;
  KEY_Info_t S;
  KEY_Info_t A;
  KEY_Info_t D;
  KEY_Info_t Q;       //��ת90��
  KEY_Info_t E;       //��ת90��
  KEY_Info_t R;       //�򿪵���
  KEY_Info_t F;       //С����
  KEY_Info_t G;       //����̧ͷ
  KEY_Info_t Z;
  KEY_Info_t X;
  KEY_Info_t C;       //�Ӿ�ģʽ�л�
  KEY_Info_t V;       //���Һ�ת180��
  KEY_Info_t B;       //��λģʽ��
  KEY_Info_t CTRL;    //��еģʽ�л�
  KEY_Info_t SHIFT;   //����ģʽ�л�
  KEY_Info_t Mouse_L;
  KEY_Info_t Mouse_R;  
  KEY_MoveInfo_t MoveInfo;
  Mouse_SF_t MouseSF; 
}Keyboard_Info_t;
extern Keyboard_Info_t Keyboard;

/* ----------------------- Data Struct ------------------------------------- */
typedef struct
{
  struct
  {
      int16_t ch0;
      int16_t ch1;
      int16_t ch2;
      int16_t ch3;
      uint8_t s1;
      uint8_t s2;
      int16_t sw;
  }rc;
  struct
  {
      int16_t x;
      int16_t y;
      int16_t z;
      uint8_t press_l;
      uint8_t press_r;
  }mouse;
  union {
    uint16_t key_code;
    struct
    {
      uint16_t W : 1;
      uint16_t S : 1;
      uint16_t A : 1;
      uint16_t D : 1;
      uint16_t SHIFT : 1;
      uint16_t CTRL : 1;
      uint16_t Q : 1;
      uint16_t E : 1;
      uint16_t R : 1;
      uint16_t F : 1;
      uint16_t G : 1;
      uint16_t Z : 1;
      uint16_t X : 1;
      uint16_t C : 1;
      uint16_t V : 1;
      uint16_t B : 1;
    } bit;
  } kb;
}RC_Ctl_t;
/* ----------------------- Internal Data ----------------------------------- */

extern RC_Ctl_t RC_Ctl;
extern uint32_t Remote_time ;//ң����

/** ��ң������Ϣͼ��
 * ����������������������������������������������������������������������������������������
 * �� ����������1  660                  660  ����������1 ��
 * �� ��S 1��3   ��                    ��   ��S 2��3 ��
 * �� ����������2   ��                    ��   ����������2 ��
 * ��          ��                    ��          ��
 * �� CH2<�����������੤��������>660  CH0<�����������੤��������>660 ��
 * ��          ��                    ��          ��
 * ��          ��                    ��          ��
 * ��          V                    V          ��
 * ��         CH3                  CH1         ��
 * ����������������������������������������������������������������������������������������
 */



/* -----------------------RC Channel---------------------------- */
#define RC_CH0              RC_Ctl.rc.ch0
#define RC_CH1              RC_Ctl.rc.ch1
#define RC_CH2              RC_Ctl.rc.ch2
#define RC_CH3              RC_Ctl.rc.ch3
#define RC_CH_VALUE_MIN     ((int16_t)-660 )
#define RC_CH_VALUE_OFFSET  ((int16_t)0)
#define RC_CH_VALUE_MAX     ((int16_t)660)
#define RC_S1               RC_Ctl.rc.s1      
#define RC_S2               RC_Ctl.rc.s2
#define RC_SW               RC_Ctl.rc.sw
#define RC_SW_VALUE_MIN     ((int16_t)-660 )
#define RC_SW_VALUE_OFFSET  ((int16_t)0)
#define RC_SW_VALUE_MAX     ((int16_t)660)
/* -----
#define RC_S_Err           ((uint8_t)4------------------RC Switch----------------------------- */
#define RC_S_UP            ((uint8_t)1)
#define RC_S_MID           ((uint8_t)3)
#define RC_S_DOWN          ((uint8_t)2)
#define RC_S_Err           ((uint8_t)4)
/* -----------------------PC Key-------------------------------- */
#define KEY_W               RC_Ctl.kb.bit.W		
#define KEY_S               RC_Ctl.kb.bit.S		
#define KEY_A               RC_Ctl.kb.bit.A		
#define KEY_D               RC_Ctl.kb.bit.D	
#define KEY_SHIFT           RC_Ctl.kb.bit.SHIFT	
#define KEY_CTRL            RC_Ctl.kb.bit.CTRL		
#define KEY_Q               RC_Ctl.kb.bit.Q		
#define KEY_E               RC_Ctl.kb.bit.E		
#define KEY_R               RC_Ctl.kb.bit.R		
#define KEY_F               RC_Ctl.kb.bit.F		
#define KEY_G               RC_Ctl.kb.bit.G		
#define KEY_Z               RC_Ctl.kb.bit.Z		
#define KEY_X               RC_Ctl.kb.bit.X		
#define KEY_C               RC_Ctl.kb.bit.C		
#define KEY_V               RC_Ctl.kb.bit.V		
#define KEY_B               RC_Ctl.kb.bit.B		

#define KEY_ALL_CODE        RC_Ctl.kb.key_code

/*���������ƶ��ٶ�*/
#define    MOUSE_X_MOVE_SPEED    (RC_Ctl.mouse.x)
#define    MOUSE_Y_MOVE_SPEED    (RC_Ctl.mouse.y)
#define    MOUSE_Z_MOVE_SPEED    (RC_Ctl.mouse.z)

/* �����갴��״̬ */
#define    MOUSE_LEFT    (RC_Ctl.mouse.press_l )
#define    MOUSE_RIGH    (RC_Ctl.mouse.press_r )

/* �����̰���״̬ */
#define KEY_UP                    0x00
#define KEY_DOWN                  0x01

/* ��ⰴ��������Ƿ��а��� */
#define KEY_CTRL_STATE (KEY_ALL_CODE || MOUSE_LEFT || MOUSE_RIGH)

uint8_t Report_S2(void);

void Remote_Init(void);
void usart2_Init(void);
void Get_RC_Data(void);

bool Judge_RC_DataErr(void);
bool Judge_RC_Lost(void);

void RC_Mistake_Report(void);
void RC_lost_Report(void);
System_State_t RC_Check(void);
void RC_State_Report(void);

void RC_Ctrl(void);
void RC_Mode_Ctrl(void);

void RC_Err_Process(void);
void RC_Lost_Process(void);
void RC_Protect(void);

RC_S_Change_t RC_Judge_s1_Change(void);
RC_S_Change_t RC_Judge_s2_Change(void);
RC_SW_Change_t RC_Judge_sw_Change(void);

void RC_Function_Ctrl(void);
void KEY_Function_Ctrl(void);

void Infantry_Action_Ctrl(void);
void SYS_Err_Public(void);

void RC_prev_s1_Err(void);
void RC_prev_s2_Err(void);

float Report_MECH_SlowlyTurn(void);
//void KEY_State_Judge(KEY_Info_t *str , uint8_t KEY_PRESS);
void KEY_State_Judge(KEY_Info_t *str , uint8_t KEY_PRESS , int change_tim ,int long_change_tim);
void KEY_InfoInit(void);
void KEY_InfoReset(void);
float KEY_FB_Ctrl(void);
float KEY_LR_Ctrl(void);
float Mouse_X_Speed(void);
float Mouse_Y_Speed(void);
void KEY_Move_Init(void);

void Function_turnOFF(void);

#define    IF_RC_DATAERR   Judge_RC_DataErr()
#define    IF_RC_LOST      Judge_RC_Lost()
#define    IF_RC_NORMAL    !(IF_RC_DATAERR || IF_RC_LOST)


#endif


