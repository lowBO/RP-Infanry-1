#ifndef __TIM_H
#define __TIM_H

#include "system.h"

void PWM_Friction_Init(u16 arr,u16 psc);
void PWM_Clip_Init(u16 arr,u16 psc);
void Trigger_Cnt_Init(u16 arr,u16 psc);

#endif 
