/***      《 电机管理代码 》

 *      ┌─┐       ┌─┐ + +
 *   ┌──┘ ┴───────┘ ┴──┐++
 *   │                 │
 *   │       ───       │++ + + +
 *   ███████───███████ │+
 *   │                 │+
 *   │      ─┴─        │
 *   │                 │
 *   └───┐         ┌───┘
 *       │         │
 *       │         │   + +
 *       │         │
 *       │         └──────────────┐
 *       │                        │
 *       │                        ├─┐
 *       │                        ┌─┘
 *       │                        │
 *       └─┐  ┐  ┌───────┬──┐  ┌──┘  + + + +
 *         │ ─┤ ─┤       │ ─┤ ─┤
 *         └──┴──┘       └──┴──┘  + + + +
 *              
 *               代码无BUG!
 */
 
#include "motor.h"
#include "Device.h"

 


 /**
 * @brief PID不同模式的参数汇总(初始赋值)
 * @param 
 */
#if (Infantry == 1)
PID_Parameter_t PID_Speed_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 12.5,
      .I = 0.4,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 12.5,
      .I = 4,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [RC_MECH] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 15,
      .I = 1.5,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 15,   //15  
      .I = 1.2,    //1
      .D = 0,      
    },
    [RC_MECH] = {
      .P = 15,     
      .I = 1.2,    
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 15,     
      .I = 1.2,    
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 15,     
      .I = 1.2,    
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 15,   //15  
      .I = 1.2,    //1
      .D = 0,     
    },
    [ACT_SMALL_BUFF] = {
      .P = 15,   //15  
      .I = 1.2,    //1
      .D = 0,     
    },
    [ACT_AUTO_AIM] = {
      .P = 15,     
      .I = 1.2,    
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 15,   //15  
      .I = 1.2,    //1
      .D = 0,  
    },

  },
  [M_2006]  = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
PID_Parameter_t PID_Angle_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 18,   
      .I = 0,
      .D = 0,
    },

  },
  [M_2006]  = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
 
 

#elif (Infantry == 2)
PID_Parameter_t PID_Speed_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 14, //11.5
      .I = 1.2,  //2
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 14,
      .I = 1.2,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 14,
      .I = 1.2,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 14,
      .I = 1.2,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 14, //11.5
      .I = 1.2,  //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 14, //11.5
      .I = 1.2,  //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 14,
      .I = 1.2,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 14, //11.5
      .I = 1.2,  //2
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [RC_MECH] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 15,
      .I = 1.5,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 13,   //15  
      .I = 0.7,    //1
      .D = 0,      
    },
    [RC_MECH] = {
      .P = 13,     
      .I = 0.7,    
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 13,     
      .I = 0.7,    
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 13,     
      .I = 0.7,    
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 13,   //15  
      .I = 0.7,    //1
      .D = 0,     
    },
    [ACT_SMALL_BUFF] = {
      .P = 13,   //15  
      .I = 0.7,    //1
      .D = 0,     
    },
    [ACT_AUTO_AIM] = {
      .P = 13,     
      .I = 0.7,    
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 13,   //15  
      .I = 0.7,    //1
      .D = 0,  
    },

  },
  [M_2006]  = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
PID_Parameter_t PID_Angle_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },

  },
  [M_2006]  = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
 
 

#elif (Infantry == 3)
PID_Parameter_t PID_Speed_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 12.5,
      .I = 0.7,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 12.5, //11.5
      .I = 0.7,  //2
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [RC_MECH] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 15,
      .I = 1.5,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 15,//15
      .I = 2, //2
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 15,
      .I = 2,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 15, //15
      .I = 1.5,//1.5
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 15,   //15  
      .I = 1,    //1
      .D = 0,      
    },
    [RC_MECH] = {
      .P = 15,     
      .I = 1,    
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 15,     
      .I = 1,    
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 15,     
      .I = 1,    
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 15,   //15  
      .I = 1,    //1
      .D = 0,     
    },
    [ACT_SMALL_BUFF] = {
      .P = 15,   //15  
      .I = 1,    //1
      .D = 0,     
    },
    [ACT_AUTO_AIM] = {
      .P = 15,     
      .I = 1,    
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 15,   //15  
      .I = 1,    //1
      .D = 0,  
    },

  },
  [M_2006]  = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 8,
      .I = 0.1,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
PID_Parameter_t PID_Angle_Param[MOTOR_TYPE_CNT][PID_TYPE_CNT] = {
  [RM_3508] = {
    [Turn_off]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_MECH]    = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED]  = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK]   = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_YAW] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 30,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 25,
      .I = 0,
      .D = 0,
    },

  },
  [GM_6020_PIT] = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 20,   
      .I = 0,
      .D = 0,
    },

  },
  [M_2006]  = {
    [Turn_off] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [RC_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [RC_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [KEY_GYRO] = {
      .P = 0.1,
      .I = 0,
      .D = 0,
    },
    [KEY_MECH] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_BIG_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SMALL_BUFF] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_AUTO_AIM] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_SPEED] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },
    [ACT_PARK] = {
      .P = 0,
      .I = 0,
      .D = 0,
    },

  },
};
 
 

#endif
/**
 * @brief 总电机初始化
 * @param 
 */
void MOTOR_Init(void)
{
  RM_3508_Init();
  Fric_3508_Init();
  GM_6020_Init();
  M_2006_Init();
}

/*底盘RM3508电机--------------------------------------*/
/**
 * @brief 底盘电机初始化
 * @param 
 */
void RM_3508_Init(void)
{
  Chassis.motor_info.motor_type = RM_3508;
  //还包括PID参数等
  RM_3508_ParamInit(&Chassis.CHAS_Motor[CHAS_LF].PID.Speed_Loop);
  RM_3508_ParamInit(&Chassis.CHAS_Motor[CHAS_RF].PID.Speed_Loop);
  RM_3508_ParamInit(&Chassis.CHAS_Motor[CHAS_LB].PID.Speed_Loop);
  RM_3508_ParamInit(&Chassis.CHAS_Motor[CHAS_RB].PID.Speed_Loop);
  CHAS_ParamInit();
}

void Fric_3508_Init(void)
{
  //摩擦轮电机
  RM_3508_ParamInit(&Module.Friction.Fric[righ].PID.Speed_Loop);
  RM_3508_ParamInit(&Module.Friction.Fric[left].PID.Speed_Loop);
  
  Module.Friction.Fric[righ].PID.Speed_Loop.I_Accu_Err_Max = 2500;
  Module.Friction.Fric[left].PID.Speed_Loop.I_Accu_Err_Max = 2500;
}

/**
 * @brief PID限幅设置 
 * @param 
 */
void RM_3508_ParamInit(PID_Loop_t *str)
{
  /* 这里只针对速度环 */
  str->PID_Err_Max = 16000;
  str->I_Accu_Err_Max = 50000;//50000   2500
  str->PID_I_Out_Max = 10000; //25000   10000
  str->PID_P_Out_Max = 50000;
  str->PID_Output_Max = 15000;
  str->PID_Err_Dead = 5;
}

/**
 * @brief 底盘速度解算参数设置
 * @param 
 */
void CHAS_ParamInit(void)
{
  #if (Infantry == 1)
  Chassis.RC_Move.FB_Speed_k = 16;
  Chassis.RC_Move.LR_Speed_k = 16;
  Chassis.RC_Move.Z_Speed_k = 1.2;//1
  Chassis.RC_Move.Slow_Inc = 60;//斜坡斜率（速度） 50
  //角度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 1.8;//1.8 1.6
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 13000;//40000
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 2;//1.8 1.5
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.01;//1.2 1.4
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.Key_Move.FB_Speed_k = 16;
  Chassis.Key_Move.LR_Speed_k = 16;
  Chassis.Key_Move.Z_Speed_k = 1.2;
  Chassis.Key_Move.Slow_Inc = 10;//斜坡斜率（速度）55
  //角度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 1.63;//1.6  
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 12000;//12000
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.7;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.01;//0.01
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 5000;//10000
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.SPIN_Move.FB_Speed_k = 6.5;//3
  Chassis.SPIN_Move.LR_Speed_k = 6.5;//2
  Chassis.SPIN_Move.Z_Speed_k = 1;//让陀螺速度由SPEED决定，不被k影响到
  Chassis.SPIN_Move.Slow_Inc = 50;//斜坡斜率（速度）
  //角度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 2;  
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.8;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.01;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  #elif (Infantry == 2)
  Chassis.RC_Move.FB_Speed_k = 16;
  Chassis.RC_Move.LR_Speed_k = 16;
  Chassis.RC_Move.Z_Speed_k = 1.2;//1
  Chassis.RC_Move.Slow_Inc = 65;//斜坡斜率（速度） 50
  //角度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;//10000
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 2.5;//1.8 1.6
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 13000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 2.0;//1.8 1.5  2.0
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.015;//1.2 1.4 0.015
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.Key_Move.FB_Speed_k = 16;
  Chassis.Key_Move.LR_Speed_k = 16;
  Chassis.Key_Move.Z_Speed_k = 1.2;
  Chassis.Key_Move.Slow_Inc = 55;//斜坡斜率（速度）35
  //角度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 2000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 2;  
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 12000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.75;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.025;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.SPIN_Move.FB_Speed_k = 3;//3
  Chassis.SPIN_Move.LR_Speed_k = 2;//2
  Chassis.SPIN_Move.Z_Speed_k = 1;//让陀螺速度由SPEED决定，不被k影响到
  Chassis.SPIN_Move.Slow_Inc = 50;//斜坡斜率（速度）
  //角度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 2;  
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.8;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.012;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
   
  
  #elif (Infantry == 3)
  Chassis.RC_Move.FB_Speed_k = 16;
  Chassis.RC_Move.LR_Speed_k = 16;
  Chassis.RC_Move.Z_Speed_k = 1.2;//1
  Chassis.RC_Move.Slow_Inc = 60;//斜坡斜率（速度） 50
  //角度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 1.55;//1.8 1.6
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 13000;//40000
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.5;//1.8 1.5
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.007;//1.2 1.4
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 2000;//太大是跑歪的原因？
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 5000;
  Chassis.RC_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.Key_Move.FB_Speed_k = 16;
  Chassis.Key_Move.LR_Speed_k = 16;
  Chassis.Key_Move.Z_Speed_k = 1.2;
  Chassis.Key_Move.Slow_Inc = 40;//斜坡斜率（速度）55
  //角度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 1.55;//1.6  
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 12000;//12000
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.5;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.007;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 2000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 5000;
  Chassis.Key_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;
  
  
  Chassis.SPIN_Move.FB_Speed_k = 6.5;//3
  Chassis.SPIN_Move.LR_Speed_k = 6.5;//2
  Chassis.SPIN_Move.Z_Speed_k = 1;//让陀螺速度由SPEED决定，不被k影响到
  Chassis.SPIN_Move.Slow_Inc = 50;//斜坡斜率（速度）
  //角度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Dead = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_Param.P = 1.55;  
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Angle_Loop.PID_P_Out_Max = 50000;
  //速度环
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Dead = 5;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Err_Max = 20000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Output_Max = 40000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.P = 1.5;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.I = 0.01;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_Param.D = 0;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.I_Accu_Err_Max = 10000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_I_Out_Max = 25000;
  Chassis.SPIN_Move.GYRO_Move.GYRO_Ctrl.Speed_Loop.PID_P_Out_Max = 50000;

  #endif
}

/*云台GM6020电机--------------------------------------*/
/**
 * @brief Yaw轴的PID限幅设置
          云台Yaw速度解算参数设置
 * @param 
 */
void GIM_YawParamInit(AXIS_Info_t *str)
{
  //若以后想把陀螺仪模式和机械模式的限幅参数分开，就用switch来分开
  //一般不会分开，两个模式的限幅可以是一样的，差别应该不大
  #if (Infantry == 1)
    /* 速度环 */
    str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
    str->PID.Speed_Loop.PID_I_Out_Max = 25000;
    str->PID.Speed_Loop.PID_P_Out_Max = 50000;
    str->PID.Speed_Loop.PID_Output_Max = 25000;
    str->PID.Speed_Loop.PID_Err_Max = 20000;
    str->PID.Speed_Loop.PID_Err_Dead = 0;
    /* 角度环 */
    str->PID.Angle_Loop.I_Accu_Err_Max = 25000;
    str->PID.Angle_Loop.PID_I_Out_Max = 25000;
    str->PID.Angle_Loop.PID_P_Out_Max = 50000;
    str->PID.Angle_Loop.PID_Output_Max = 13000;
    str->PID.Angle_Loop.PID_Err_Max = 4000;//20000
    str->PID.Angle_Loop.PID_Err_Dead = 0;
    /* 遥控模式 */
    str->RC_Move.AXIS_Angle_Inc = 0;
    str->RC_Move.AXIS_Angle_k = 0.015;
    str->RC_Move.Slow_Inc = 0;
    /* 键盘模式 */
    str->Key_Move.AXIS_Angle_Inc = 0;
    str->Key_Move.AXIS_Angle_k = 0.38;
    str->Key_Move.Slow_Inc = 0;

    
  #elif (Infantry == 2)
    /* 速度环 */
    str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
    str->PID.Speed_Loop.PID_I_Out_Max = 25000;
    str->PID.Speed_Loop.PID_P_Out_Max = 50000;
    str->PID.Speed_Loop.PID_Output_Max = 25000;
    str->PID.Speed_Loop.PID_Err_Max = 20000;
    str->PID.Speed_Loop.PID_Err_Dead = 0;
    /* 角度环 */
    str->PID.Angle_Loop.I_Accu_Err_Max = 25000;
    str->PID.Angle_Loop.PID_I_Out_Max = 25000;
    str->PID.Angle_Loop.PID_P_Out_Max = 50000;
    str->PID.Angle_Loop.PID_Output_Max = 13000;
    str->PID.Angle_Loop.PID_Err_Max = 4000;//20000 
    str->PID.Angle_Loop.PID_Err_Dead = 0;
    /* 遥控模式 */
    str->RC_Move.AXIS_Angle_Inc = 0;
    str->RC_Move.AXIS_Angle_k = 0.015;  //0.03
    str->RC_Move.Slow_Inc = 0;
    /* 键盘模式 */
    str->Key_Move.AXIS_Angle_Inc = 0;
    str->Key_Move.AXIS_Angle_k = 0.38;//0.52
    str->Key_Move.Slow_Inc = 0;

    
  #elif (Infantry == 3)
    /* 速度环 */
    str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
    str->PID.Speed_Loop.PID_I_Out_Max = 25000;
    str->PID.Speed_Loop.PID_P_Out_Max = 50000;
    str->PID.Speed_Loop.PID_Output_Max = 25000;
    str->PID.Speed_Loop.PID_Err_Max = 20000;
    str->PID.Speed_Loop.PID_Err_Dead = 0;
    /* 角度环 */
    str->PID.Angle_Loop.I_Accu_Err_Max = 25000;
    str->PID.Angle_Loop.PID_I_Out_Max = 25000;
    str->PID.Angle_Loop.PID_P_Out_Max = 50000;
    str->PID.Angle_Loop.PID_Output_Max = 13000;
    str->PID.Angle_Loop.PID_Err_Max = 4000; 
    str->PID.Angle_Loop.PID_Err_Dead = 0;
    /* 遥控模式 */
    str->RC_Move.AXIS_Angle_Inc = 0;
    str->RC_Move.AXIS_Angle_k = 0.015;
    str->RC_Move.Slow_Inc = 0;
    /* 键盘模式 */
    str->Key_Move.AXIS_Angle_Inc = 0;
    str->Key_Move.AXIS_Angle_k = 0.38;
    str->Key_Move.Slow_Inc = 0;
  #endif
}

/**
 * @brief Pitch轴的PID限幅设置
          云台PITCH速度解算参数设置
 * @param 
 */
void GIM_PitParamInit(AXIS_Info_t *str)
{
  #if (Infantry == 1)
  /* 速度环 */
  str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
  str->PID.Speed_Loop.PID_I_Out_Max = 25000;
  str->PID.Speed_Loop.PID_P_Out_Max = 50000;
  str->PID.Speed_Loop.PID_Output_Max = 25000;
  str->PID.Speed_Loop.PID_Err_Max = 20000;
  str->PID.Speed_Loop.PID_Err_Dead = 0;
  /* 角度环 */
  str->PID.Angle_Loop.I_Accu_Err_Max = 12000;
  str->PID.Angle_Loop.PID_I_Out_Max = 25000;
  str->PID.Angle_Loop.PID_P_Out_Max = 50000;
  str->PID.Angle_Loop.PID_Output_Max = 13000;
  str->PID.Angle_Loop.PID_Err_Max = 20000;
  str->PID.Angle_Loop.PID_Err_Dead = 0;  
  /* 遥控模式 */
  str->RC_Move.AXIS_Angle_Inc = 0;
  str->RC_Move.AXIS_Angle_k = 0.02;
  str->RC_Move.Slow_Inc = 0;
  /* 键盘模式 */
  str->Key_Move.AXIS_Angle_Inc = 0;
  str->Key_Move.AXIS_Angle_k = 0.3;
  str->Key_Move.Slow_Inc = 0;

  
  #elif (Infantry == 2)
  /* 速度环 */
  str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
  str->PID.Speed_Loop.PID_I_Out_Max = 25000;
  str->PID.Speed_Loop.PID_P_Out_Max = 50000;
  str->PID.Speed_Loop.PID_Output_Max = 25000;
  str->PID.Speed_Loop.PID_Err_Max = 20000;
  str->PID.Speed_Loop.PID_Err_Dead = 0;
  /* 角度环 */
  str->PID.Angle_Loop.I_Accu_Err_Max = 12000;
  str->PID.Angle_Loop.PID_I_Out_Max = 25000;
  str->PID.Angle_Loop.PID_P_Out_Max = 50000;
  str->PID.Angle_Loop.PID_Output_Max = 13000;
  str->PID.Angle_Loop.PID_Err_Max = 20000;
  str->PID.Angle_Loop.PID_Err_Dead = 0;  
  /* 遥控模式 */
  str->RC_Move.AXIS_Angle_Inc = 0;
  str->RC_Move.AXIS_Angle_k = 0.02;
  str->RC_Move.Slow_Inc = 0;
  /* 键盘模式 */
  str->Key_Move.AXIS_Angle_Inc = 0;
  str->Key_Move.AXIS_Angle_k = 0.3;
  str->Key_Move.Slow_Inc = 0;

  
  #elif (Infantry == 3)
  /* 速度环 */
  str->PID.Speed_Loop.I_Accu_Err_Max = 50000;
  str->PID.Speed_Loop.PID_I_Out_Max = 25000;
  str->PID.Speed_Loop.PID_P_Out_Max = 50000;
  str->PID.Speed_Loop.PID_Output_Max = 25000;
  str->PID.Speed_Loop.PID_Err_Max = 20000;
  str->PID.Speed_Loop.PID_Err_Dead = 0;
  /* 角度环 */
  str->PID.Angle_Loop.I_Accu_Err_Max = 12000;
  str->PID.Angle_Loop.PID_I_Out_Max = 25000;
  str->PID.Angle_Loop.PID_P_Out_Max = 50000;
  str->PID.Angle_Loop.PID_Output_Max = 13000;
  str->PID.Angle_Loop.PID_Err_Max = 20000;
  str->PID.Angle_Loop.PID_Err_Dead = 0;  
  /* 遥控模式 */
  str->RC_Move.AXIS_Angle_Inc = 0;
  str->RC_Move.AXIS_Angle_k = 0.02;
  str->RC_Move.Slow_Inc = 0;
  /* 键盘模式 */
  str->Key_Move.AXIS_Angle_Inc = 0;
  str->Key_Move.AXIS_Angle_k = 0.3;
  str->Key_Move.Slow_Inc = 0;
  #endif
}

/**
 * @brief 云台电机初始化
 * @param 
 */
void GM_6020_Init(void)
{
  Gimbal.YAW.motor_info.motor_type = GM_6020_YAW;
  Gimbal.PIT.motor_info.motor_type = GM_6020_PIT;
  
  GIM_YawParamInit(&Gimbal.YAW);
  GIM_PitParamInit(&Gimbal.PIT);
}


/*拨盘M2006电机--------------------------------------*/
/**
 * @brief 拨盘电机初始化
 * @param 
 */
void M_2006_Init(void)
{
  Rifle.Motor[RIFLE].motor_info.motor_type = M_2006;
  M_2006_ParamInit();
}

void M_2006_ParamInit(void)
{
  PID_Info_t *str = &(Rifle.Motor[RIFLE].PID);
  
  str->Speed_Loop.I_Accu_Err_Max = 50000;
  str->Speed_Loop.PID_I_Out_Max = 25000;
  str->Speed_Loop.PID_Output_Max = 10000;//速度环最终输出限制10000，防止电流过大，断线+疯转
  str->Speed_Loop.PID_Err_Max = 50000;
  str->Speed_Loop.PID_P_Out_Max = 13000;
  str->Speed_Loop.PID_Err_Dead = 0;
  
  str->Angle_Loop.I_Accu_Err_Max = 50000;
  str->Angle_Loop.PID_I_Out_Max = 25000;
  str->Angle_Loop.PID_Output_Max = 13000;
  str->Angle_Loop.PID_Err_Max = 20000;
  str->Angle_Loop.PID_P_Out_Max = 13000;
  str->Angle_Loop.PID_Err_Dead = 0;
}


/**
 * @brief 斜坡
 * @note  键盘 
 */
void Slow(float *rec , float target , float slow_Inc)
{
  if(abs(*rec) - abs(target) < 0);
  if(abs(*rec) - abs(target) > 0)slow_Inc = slow_Inc * 6;//减速时放大6倍
  
  if(abs(*rec - target) < slow_Inc) *rec = target;
  else {
    if((*rec) > target) (*rec) -= slow_Inc;
    if((*rec) < target) (*rec) += slow_Inc;
  }
}

/**
 * @brief 电机输出斜坡
 * @param 
 */
void MotorSlow(float *rec , float target , float slow_Inc)
{
  if(abs(*rec) - abs(target) < 0);
  if(abs(*rec) - abs(target) > 0)slow_Inc = slow_Inc * 6;//减速时放大6倍
    
  if(abs(*rec - target) < slow_Inc) *rec = target;
  else {
    if((*rec) > target) (*rec) -= slow_Inc;
    if((*rec) < target) (*rec) += slow_Inc;
  }
}


void global_slow(float *rec , float target , float slow_Inc)
{
  if(abs(*rec - target) < slow_Inc) *rec = target;
  else {
    if((*rec) > target) (*rec) -= slow_Inc;
    if((*rec) < target) (*rec) += slow_Inc;
  }
}




