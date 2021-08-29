/***      �� �����㷨���� ��

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
#include "AUTO.h"
#include "Device.h"
#include "Function.h"

AutoAim_t AutoAim = {
  .Init_Over = NO,
  .YAW.TargerFix = 0,
  .PIT.TargerFix = PIT_FIX,
};


//�Ӿ�������ʼ��
void AutoAimInit(void)
{
  #if (Infantry == 1)
  AutoAim.YAW.Param.Ke = AutoAim_Ke;//0.22
  AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;//10.5
  AutoAim.YAW.Param.Ka = 7.5;//7.5
  AutoAim.YAW.Coordinate.Axis = YAW;
  AutoAim.YAW.Coordinate.fix = 18.85;

  AutoAim.PIT.Param.Ke = 0.22;
  AutoAim.PIT.Param.Ko = 0;
  AutoAim.PIT.Param.Ka = 0;
  AutoAim.PIT.Coordinate.Axis = PIT;
  AutoAim.PIT.Coordinate.fix = 18.85;
  
  #elif (Infantry == 2)
  AutoAim.YAW.Param.Ke = AutoAim_Ke;//�Ӿ���һ�ȵ����ҵ�21�ȣ����ԽǶ���ҪС
  AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;//Ԥ����������һ�� 10.7
  AutoAim.YAW.Param.Ka = 9;//9
  AutoAim.YAW.Coordinate.Axis = YAW;
  AutoAim.YAW.Coordinate.fix = 21;//�ȵ������ԽǶȲ���
  
  AutoAim.PIT.Param.Ke = 0.23;//�Ӿ���һ�ȵ����ҵ�100�ȣ����ԽǶ���ҪС
  AutoAim.PIT.Param.Ko = 0;//Ԥ����������һ��
  AutoAim.PIT.Param.Ka = 0;
  AutoAim.PIT.Coordinate.Axis = PIT;
  AutoAim.PIT.Coordinate.fix = 21;//�ȵ������ԽǶȲ���

  
  #elif (Infantry == 3)
  AutoAim.YAW.Param.Ke = AutoAim_Ke;//0.22
  AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;//10.5
  AutoAim.YAW.Param.Ka = 7.5;//7.5
  AutoAim.YAW.Coordinate.Axis = YAW;
  AutoAim.YAW.Coordinate.fix = 18.85;

  AutoAim.PIT.Param.Ke = 0.22;
  AutoAim.PIT.Param.Ko = 0;
  AutoAim.PIT.Param.Ka = 0;
  AutoAim.PIT.Coordinate.Axis = PIT;
  AutoAim.PIT.Coordinate.fix = 18.85;
  #endif

}




/**
 * @brief �������齨������ϵ
 * @note   ��һ�ν���ʱִֻ��һ��    ��vision.c����
 */
void AutoAim_ON(void)
{
  Coordinate_t *YAW = &AutoAim.YAW.Coordinate;
  Coordinate_t *PIT = &AutoAim.PIT.Coordinate;
  if(!AutoAim.Init_Over)
  {
    Predict_Reset();
    VErrSlope_Reset();
    YAW->abso_Angle = Report_prev_imu_yaw_angle(6);//YAW_GetGyroAngle();
    PIT->abso_Angle = PIT_GetMechAngle();
    AutoAim.Init_Over = YES;
  }
}

/**
 * @brief ����ر�
 * @note  ��vision.c�ر�
 */
void AutoAim_OFF(void)
{
  AutoAim.Init_Over = NO;
  Predict_Reset();
  VErrSlope_Reset();
}

/**
 * @brief ���������Ƿ���
 * @note  
 */
bool Report_IF_AutoAim_ON(void)
{
  return AutoAim.Init_Over;
}
//--------------------------�㷨��---------------------------


/**
 * @brief ��������ϵ�Ƕ�
 * @param 
 */
float VisionYawErr_queue[VErrSlope_LEN];
float VisionPitErr_queue[VErrSlope_LEN];
float GetAngle(Coordinate_t *str)
{
  switch(str->Axis)
  {
    case YAW:
        str->Vision_Err = Slope(-YAW_GetAutoAimErr() * str->fix,
                                VisionYawErr_queue,
                                VErrSlope_LEN);
        str->Gim_Err = Report_prev_imu_yaw_angle(6) - str->abso_Angle;//YAW_GetGyroAngle();
      break;
    case PIT:
        str->Vision_Err = Slope(-PIT_GetAutoAimErr() * str->fix,
                                VisionPitErr_queue,
                                VErrSlope_LEN);
        str->Gim_Err = PIT_GetMechAngle() - str->abso_Angle;   
      break;
  }
  
  return str->Vision_Err + str->Gim_Err ;
}
void VErrSlope_Reset(void)
{
  for(int i = 0;i<VErrSlope_LEN;i++)
  {
    VisionYawErr_queue[i] = 0;
    VisionPitErr_queue[i] = 0;
  } 
}

/**
 * @brief �����˲�����
 * @note  ����������һ�����
           �Ƕ�->�ٶ�
           �ٶ�->���ٶ�
           
 *  �˲����Ȳ�Ҫ����100
 */
float Get_SlopeTarget(float M ,float *queue ,uint16_t len)
{
	float sum=0;
	float res=0;
  
//  if(VISION_GetFlagStatus(IF_CHANGE_ARMOR))
//    for(uint16_t k=0;k<len-1;k++)
//    {
//      queue[k] = M;
//    }
  
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
	
//	res = (M - res);	
	
	return res;
}

float prev_yaw_A = 0,prev_pit_A = 0;
float Get_OmigaData(AutoAim_Data_t *str)
{
  float time = Get_FrameTime();
  float res = 0;
  res = (str->Angle - str->prev_Angle) / time ;
  switch(str->Coordinate.Axis)
  {
    case YAW:
        if(abs(res) <= 0.5f)
        {
          prev_yaw_A = res;
        }
        else res = prev_yaw_A;
        break;
      
    case PIT:
        if(abs(res) <= 0.5f)
        {
          prev_pit_A = res;
        }
        else res = prev_pit_A;   
        break;
  }
  str->prev_Angle = str->Angle;  
  
  return res;
}

float prev_yaw_S = 0,prev_pit_S = 0;
float Get_AccelData(AutoAim_Data_t *str)
{
  float time = Get_FrameTime();
  float res = 0;
  res = (str->Omiga - str->prev_Omiga) / time ;
  switch(str->Coordinate.Axis)
  {
    case YAW:
        if(abs(res) <= 0.5f)
        {
          prev_yaw_S = res;
        }
        else res = prev_yaw_S;
        break;
      
    case PIT:
        if(abs(res) <= 0.5f)
        {
          prev_pit_S = res;
        }
        else res = prev_pit_S;   
        break;
  }
  str->prev_Omiga = str->Omiga;  
  
  return res;
}

//Ԥ�����л�
void PRE_switch(void)
{
  AutoAim.YAW.Param.Ke = AutoAim_Ke;
  if(IF_DUM_NORMAL)
  switch(DUM_Report_Shoot_SpeedLimit())
  {
    case 15:
      AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;
      break;
    
    case 18:
      AutoAim.YAW.Param.Ko = ShootSpeed_18_PRE;
      break;
    
    case 30:
      AutoAim.YAW.Param.Ko = ShootSpeed_30_PRE;
      break;
    
    default:
      AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;
      break;
  }
  else AutoAim.YAW.Param.Ko = ShootSpeed_15_PRE;
}

/**
 * @brief �����㷨
 * @param 
 */
float AutoAim_Algorithm(AutoAim_Data_t *str)
{
  float res;
  str->Predict.start_predict_TIM++;
  /*��ȡ����*/
  str->Angle = //KalmanFilter(&str->KF.Angle_KF,
                           GetAngle(&str->Coordinate);//);

  str->Omiga = KalmanFilter(&str->KF.Omiga_KF,
                           Get_SlopeTarget(Get_OmigaData(str) ,str->Angle_queue , AngleSlope_LEN));

  str->Accel = KalmanFilter(&str->KF.Accel_KF,
                           Get_SlopeTarget(Get_AccelData(str) ,str->Omiga_queue , OmigaSlope_LEN));
  
 /*��ȡ�������*/
  str->Angle_Out = str->Coordinate.Vision_Err * str->Param.Ke  ;
  str->Omiga_Out = str->Omiga * str->Param.Ko;
  str->Accel_Out = str->Accel/2 * str->Param.Ka;
  
  if(str->Predict.start_predict_TIM > 30)//30ms����Ԥ��,��ֹ����ͻ��
    str->Predict.START_PREDICT = NO;//YES;
  if(str->Predict.START_PREDICT)
    str->Out = str->Angle_Out + str->Omiga_Out + str->Accel_Out;
  else str->Out = str->Angle_Out;
  
  res = str->Out;
  res = KalmanFilter(&str->KF.Out_KF , str->Out);
  return res;
}

/**
 * @brief �����˲������������
 * @param 
 */
void SlopeData_Reset(void)
{
  for(int i;i<OmigaSlope_LEN;i++)
  {
    AutoAim.YAW.Omiga_queue[i] = 0;
    AutoAim.YAW.Angle_queue[i] = 0;
    
    AutoAim.PIT.Omiga_queue[i] = 0;
    AutoAim.PIT.Angle_queue[i] = 0;
  }
}

void Predict_Reset(void)
{
  //���Խ��в����ı仯
  SlopeData_Reset();
  AutoAim.YAW.Predict.START_PREDICT = NO;
  AutoAim.PIT.Predict.START_PREDICT = NO;
  AutoAim.YAW.Predict.start_predict_TIM = 0;
  AutoAim.PIT.Predict.start_predict_TIM = 0;
}

bool Report_IF_START_yawPREDICT(void)
{
  return AutoAim.YAW.Predict.START_PREDICT ;
}
bool Report_IF_START_pitPREDICT(void)
{
  return AutoAim.PIT.Predict.START_PREDICT ;
}
/**
 * @brief YAW��������ڣ�����̨����
 * @param 
 */
bool YawAutoAim_Data_Update = false;
float AutoAimYaw_Ctrl(void)
{
  float res;
  
  /*���ݲ���ϵͳ�����л�Ԥ����*/
  PRE_switch();
  
  if(YawAutoAim_Data_Update == true){
    if(VISION_GetFlagStatus(IF_LOCK_ARMOR))
    {
//      //�л�װ�װ��ʶ��С���ݶ���Ԥ��
//      if(VISION_GetFlagStatus(IF_CHANGE_ARMOR) || VISION_GetFlagStatus(IF_IDENTIFY_SPIN))
//        Predict_Reset();
      
////      //����̫����Ԥ��
////      if(Get_Aim_distance()<680.1f)
////      {
////        Predict_Reset();
////        AutoAim.YAW.Param.Ke = 0.6;//��߸�����
////      }
      
      //��������������ģʽ����Ԥ��
      if(Report_IF_anti_GYRO())
      {
        Predict_Reset();
        AutoAim.YAW.Param.Ke = 0.25;//����������
      }
      
      res = AutoAim_Algorithm(&AutoAim.YAW) + AutoAim.YAW.TargerFix;
      YawAutoAim_Data_Update = false;
    }
    else 
    {
      res = YawVision_nolook();
      Predict_Reset();
      YawAutoAim_Data_Update = false;
    }
//    /*������֮�����ѽ�����һ��Ӳ����*/
//    TriggerSignal_YES();
  }else res = YawVision_nolook();//if(!VISION_GetFlagStatus(IF_LOCK_ARMOR))
  return res;
}

/**
 * @brief Pit��������ڣ�����̨����
 * @param 
 */
bool PitAutoAim_Data_Update = false;
float AutoAimPit_Ctrl(void)
{
  float res;
  
  if(PitAutoAim_Data_Update == true){
    if(VISION_GetFlagStatus(IF_LOCK_ARMOR))
    {
      res = AutoAim_Algorithm(&AutoAim.PIT) + AutoAim.PIT.TargerFix + Report_PIT_AUTO_NUM();
      PitAutoAim_Data_Update = false;
    }
    else 
    {
      res = PitVision_nolook();
      Predict_Reset();
      PitAutoAim_Data_Update = false;
    }
//    /*������֮�����ѽ�����һ��Ӳ����*/
//    TriggerSignal_YES();
  }else res = PitVision_nolook(); 
 
  return res;
}


//-------------------------------�Զ���------------------------------------

void AutoShoot_Reset(void)
{
  AutoAim_Data_t *str = &AutoAim.YAW;
  AutoShoot_t *Shoot = &str->AutoShoot;
    if(Shoot->ConFireAllow_cnt>=1000)
      ContinFire_OFF();//������
    Shoot->SinFireAllow_cnt = 0;//������ʱ��0
    Shoot->ConFireAllow_cnt = 0;//������ʱ��0 
}

void Yaw_AutoShoot(void)
{
  AutoAim_Data_t *str = &AutoAim.YAW;
  AutoShoot_t *Shoot = &str->AutoShoot;
  if(Report_IF_START_yawPREDICT()){
  if(VISION_GetFlagStatus(IF_LOCK_ARMOR))
  {
    if(str->Omiga > 2 && str->Coordinate.Vision_Err < -14)//��
    {
      //���ϴ���������
      Shoot->SinFireAllow_cnt++;//��ʱ
      //Shoot->ConFireAllow_cnt++;//��ʱ
      if(Shoot->SinFireAllow_cnt > 350 && Shoot->ConFireAllow_cnt<1000)//��ʱ��Ч
      {
        SingleFireRequest();//�����
        Shoot->SinFireAllow_cnt = 0;
      }
      if(Shoot->ConFireAllow_cnt >= 1000)
      {
        ContinFire_ON();//������
      }
      
    }
    else if(str->Omiga < -2 && str->Coordinate.Vision_Err > 14)//�ҳ�
    {
      //���ϴ���������
      Shoot->SinFireAllow_cnt++;//��ʱ
      //Shoot->ConFireAllow_cnt++;//��ʱ
      if(Shoot->SinFireAllow_cnt > 150 && Shoot->ConFireAllow_cnt<1000)//��ʱ��Ч
      {
        SingleFireRequest();//�����
        Shoot->SinFireAllow_cnt = 0;
      }
      if(Shoot->ConFireAllow_cnt >= 1000)
      {
        ContinFire_ON();//������
      }
    }else AutoShoot_Reset();    //�������Զ�����������λ 
  }else AutoShoot_Reset();      //�Ӿ�ûʶ����λ
  }else AutoShoot_Reset();      //û����Ԥ����λ
}


bool Report_IF_Auto_InitOver(void)
{
  return AutoAim.Init_Over;
}


//--------------------------------------Ӳ����----------------------------------------------//
/**
 * @brief ����Ӳ������
 * @param 
 */
float YAW_IMU_Angle[2];//������ֵ�������
float PIT_IMU_Angle[2];//������ֵ�������
void AutoAim_Trigger(void)
{
  AutoAim.YAW.Coordinate.Gim_Err = YAW_GetGyroAngle() - AutoAim.YAW.Coordinate.abso_Angle;
  AutoAim.PIT.Coordinate.Gim_Err = PIT_GetMechAngle() - AutoAim.PIT.Coordinate.abso_Angle;
}


float PIT_AUTO_NUM = 0;
void PIT_AUTO_ADD(void)
{
  PIT_AUTO_NUM = PIT_AUTO_NUM - 10;
}
void PIT_AUTO_DEC(void)
{
  PIT_AUTO_NUM = PIT_AUTO_NUM + 10;
}
float Report_PIT_AUTO_NUM(void)
{
  return PIT_AUTO_NUM;
}




