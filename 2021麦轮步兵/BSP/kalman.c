/**    
  * @author  Liu heng
  * һ�׿������˲�������RoboMaster��̳  
  *   һά�������˲���                     
  *   ʹ��ʱ�ȶ���һ��kalmanָ�룬Ȼ�����kalmanCreate()����һ���˲��� 
  *   ÿ�ζ�ȡ�����������ݺ󼴿ɵ���KalmanFilter()�������ݽ����˲�
  *          ʹ��ʾ��                                             
  *          extKalman_t p;                  //����һ���������˲����ṹ��                                                 
  *          float SersorData;             //��Ҫ�����˲�������                                          
  *          KalmanCreate(&p,20,200);      //��ʼ�����˲�����Q=20 R=200����                                                  
  *          while(1)                                                                
  *          {                                                                            
  *             SersorData = sersor();                     //��ȡ����                                           
  *             SersorData = KalmanFilter(&p,SersorData);  //�����ݽ����˲�                                                                            
  *          }                                                                            
  */

#include "kalman.h"
#include "Device.h"
#include "Function.h"

/**
  * @name   kalmanCreate
  * @brief  ����һ���������˲���
  * @param  p:  �˲���
  *         T_Q:ϵͳ����Э����
  *         T_R:��������Э����
  *         
  * @retval none
  * @attention R�̶���QԽ�󣬴���Խ���β���ֵ��Q�������ֻ�ò���ֵ
  *		       	��֮��QԽС����Խ����ģ��Ԥ��ֵ��QΪ������ֻ��ģ��Ԥ��
  */
void KalmanCreate(extKalman_t *p,float T_Q,float T_R)
{
    p->X_last = (float)0;
    p->P_last = 0;
    p->Q = T_Q;
    p->R = T_R;
    p->A = 1;
    p->B = 0;
    p->H = 1;
    p->X_mid = p->X_last;
}

/**
  * @name   KalmanFilter
  * @brief  �������˲���
  * @param  p:  �˲���
  *         dat:���˲�����
  * @retval �˲��������
  * @attention Z(k)��ϵͳ����,������ֵ   X(k|k)�ǿ������˲����ֵ,���������
  *            A=1 B=0 H=1 I=1  W(K)  V(k)�Ǹ�˹������,�����ڲ���ֵ����,���Բ��ù�
  *            �����ǿ�������5�����Ĺ�ʽ
  *            һ��H'��Ϊ������,����Ϊת�þ���
  */

float KalmanFilter(extKalman_t* p,float dat)
{
    p->X_mid =p->A*p->X_last;                     //�ٶȶ�Ӧ��ʽ(1)    x(k|k-1) = A*X(k-1|k-1)+B*U(k)+W(K)     ״̬����
    p->P_mid = p->A*p->P_last+p->Q;               //�ٶȶ�Ӧ��ʽ(2)    p(k|k-1) = A*p(k-1|k-1)*A'+Q            �۲ⷽ��
    p->kg = p->P_mid/(p->P_mid+p->R);             //�ٶȶ�Ӧ��ʽ(4)    kg(k) = p(k|k-1)*H'/(H*p(k|k-1)*H'+R)   ���¿���������
    p->X_now = p->X_mid + p->kg*(dat-p->X_mid);   //�ٶȶ�Ӧ��ʽ(3)    x(k|k) = X(k|k-1)+kg(k)*(Z(k)-H*X(k|k-1))  ��������ֵ
    p->P_now = (1-p->kg)*p->P_mid;                //�ٶȶ�Ӧ��ʽ(5)    p(k|k) = (I-kg(k)*H)*P(k|k-1)           ���º������Э����
    p->P_last = p->P_now;                         //״̬����
    p->X_last = p->X_now;
    return p->X_now;							  //���Ԥ����x(k|k)
}



extern extKalman_t KF_Mouse_X_Speed,KF_Mouse_Y_Speed;
void Kalman_Init(void)
{
  //���
    KalmanCreate(&KF_Mouse_X_Speed,1,60);
    KalmanCreate(&KF_Mouse_Y_Speed,1,60);
  #if (Infantry == 1)
  //��ͨģʽ
    //��̨yaw
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_PARK],1,30);

    //��̨pitch
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_GYRO],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_PARK],1,30);
    
    //���̵��
    KalmanCreate(&Chassis.RC_Move.GYRO_Move.KF_GYRO_Angle,1,10);
    KalmanCreate(&Chassis.Key_Move.GYRO_Move.KF_GYRO_Angle,1,10);  
    KalmanCreate(&Chassis.SPIN_Move.GYRO_Move.KF_GYRO_Angle,1,0); 

  //����ģʽ
    //����
    KalmanCreate(&AutoAim.YAW.KF.Angle_KF , 1,40);
    KalmanCreate(&AutoAim.YAW.KF.Omiga_KF , 1,35);
    KalmanCreate(&AutoAim.YAW.KF.Accel_KF , 1,35);
    KalmanCreate(&AutoAim.YAW.KF.Out_KF , 1 ,35);
    KalmanCreate(&AutoAim.PIT.KF.Angle_KF , 1,40);
    KalmanCreate(&AutoAim.PIT.KF.Omiga_KF , 1,35);
    KalmanCreate(&AutoAim.PIT.KF.Accel_KF , 1,35);
    KalmanCreate(&AutoAim.PIT.KF.Out_KF , 1 ,35);
    //���
    KalmanCreate(&BuffAim.YAW.KF , 1 , 20 );
    KalmanCreate(&BuffAim.PIT.KF , 1 , 20 );   
    
    
  #elif (Infantry == 2)
  //��ͨģʽ
    //��̨yaw
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_PARK],1,30);
        
    //��̨pitch
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_GYRO],1,30);//30
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_PARK],1,30);
    
    //���̵��
    KalmanCreate(&Chassis.RC_Move.GYRO_Move.KF_GYRO_Angle,1,20);
    KalmanCreate(&Chassis.Key_Move.GYRO_Move.KF_GYRO_Angle,1,20);  
    KalmanCreate(&Chassis.SPIN_Move.GYRO_Move.KF_GYRO_Angle,1,20); 
  
  //����ģʽ
    //����
    KalmanCreate(&AutoAim.YAW.KF.Angle_KF , 1,20);
    KalmanCreate(&AutoAim.YAW.KF.Omiga_KF , 1,20);
    KalmanCreate(&AutoAim.YAW.KF.Accel_KF , 1,20);
    KalmanCreate(&AutoAim.YAW.KF.Out_KF , 1 ,50);
    KalmanCreate(&AutoAim.PIT.KF.Angle_KF , 1,20);
    KalmanCreate(&AutoAim.PIT.KF.Omiga_KF , 1,20);
    KalmanCreate(&AutoAim.PIT.KF.Accel_KF , 1,20);
    KalmanCreate(&AutoAim.PIT.KF.Out_KF , 1 ,50);
    //���
    KalmanCreate(&BuffAim.YAW.KF , 1 , 20 );
    KalmanCreate(&BuffAim.PIT.KF , 1 , 20 );   
  
  #elif (Infantry == 3)
  //��ͨģʽ
    //��̨yaw
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[RC_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.YAW.KF_Angle[ACT_PARK],1,30);

    //��̨pitch
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[RC_GYRO],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_MECH],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[KEY_GYRO],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_AUTO_AIM],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_BIG_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_SMALL_BUFF],1,30);
    KalmanCreate(&Gimbal.PIT.KF_Angle[ACT_PARK],1,30);
    
    //���̵��
    KalmanCreate(&Chassis.RC_Move.GYRO_Move.KF_GYRO_Angle,1,10);
    KalmanCreate(&Chassis.Key_Move.GYRO_Move.KF_GYRO_Angle,1,10);  
    KalmanCreate(&Chassis.SPIN_Move.GYRO_Move.KF_GYRO_Angle,1,0); 

  //����ģʽ
    //����
    KalmanCreate(&AutoAim.YAW.KF.Angle_KF , 1,40);
    KalmanCreate(&AutoAim.YAW.KF.Omiga_KF , 1,35);
    KalmanCreate(&AutoAim.YAW.KF.Accel_KF , 1,35);
    KalmanCreate(&AutoAim.YAW.KF.Out_KF , 1 ,35);
    KalmanCreate(&AutoAim.PIT.KF.Angle_KF , 1,40);
    KalmanCreate(&AutoAim.PIT.KF.Omiga_KF , 1,35);
    KalmanCreate(&AutoAim.PIT.KF.Accel_KF , 1,35);
    KalmanCreate(&AutoAim.PIT.KF.Out_KF , 1 ,35);
    //���
    KalmanCreate(&BuffAim.YAW.KF , 1 , 20 );
    KalmanCreate(&BuffAim.PIT.KF , 1 , 20 );   
      
  #endif
  
}
