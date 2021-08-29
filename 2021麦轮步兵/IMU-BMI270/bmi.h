#ifndef __BMI_H
#define __BMI_H

#include "stdint.h"
/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx_hal.h"
//#include "arm_math.h"
//#include "drv_io.h"

/* Exported macro ------------------------------------------------------------*/
#define CHIPID 0x00   //  оƬID   0xd1
#define PMU_STATUS 0x03  //��ʾ�������ĵ�Դģʽ
#define ACC_CONF 0x40   //���������������  ���ٶȴ�������ȡģʽ     Ĭ��0x28
#define ACC_RANGE 0x41   //���ü��ٶȷ�Χ                             Ĭ��0x03    +- 2g
#define GYR_CON 0x42     //���������������  �����Ƕ�ȡ��ģʽ     Ĭ��0x28
#define GYR_RANGE 0x43     //���ý��ٶȲ�����Χ          Ĭ��0x00    +-2000 ��/s
#define INT_EN 0x50        //�ж�����
#define INT_OUT_CTRL 0x53   //���ʹ�ܿ���
#define INT_LATCH 0x54   //�����ж�����
#define CMD 0x7E    //����Ĵ�����������
#define CONTROL 0x7e //  0x11:set pmu mode of accelerometer to normal   0x15:set pmu mode of gyroscope to normal

#define ACCD_X_LSB 0x0c
#define ACCD_X_MSB 0x0d
#define ACCD_Y_LSB 0x0e
#define ACCD_Y_MSB 0x0f
#define ACCD_Z_LSB 0x10
#define ACCD_Z_MSB 0x11
#define GYR_X_LSB 0x12
#define GYR_X_MSB 0x13
#define GYR_Y_LSB 0x14
#define GYR_Y_MSB 0x15
#define GYR_Z_LSB 0x16
#define GYR_Z_MSB 0x17

#define BMI_CS PBout(12)

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void BMI_Get_RawData(short *ggx,short *ggy,short *ggz,short *aax,short *aay,short *aaz);
void BMI_Get_AUX(short *au1,short *au2,short *au3,short *au4);
void BMI_Get_GRO(short *gx,short *gy,short *gz);
void BMI_Get_ACC(short *ax,short *ay,short *az);
uint8_t BMI_Get_EulerAngle(float *pitch,float *roll,float *yaw,short *ggx,short *ggy,short *ggz,short *aax,short *aay,short *aaz);
int8_t BMI_Init(void);

void Calm_BMI_Kp(void);

#endif
