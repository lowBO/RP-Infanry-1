#ifndef __REFEREE_H
#define __REFEREE_H

#include "system.h"
/***************������ID********************/

/* 

	ID: 0x0001  Byte:  3    ����״̬����       			����Ƶ�� 1Hz      
	ID: 0x0002  Byte:  1    �����������         		������������      
	ID: 0x0003  Byte:  32   ����������Ѫ������   		1Hz����       **
	ID: 0x0004  Byte:  3   	���ڷ���״̬  		?		���ڷ���ʱ����**
	ID: 0x0005  Byte:  3   	�˹�������ս���ӳ���ͷ�����   **
	
	ID: 0x0101  Byte:  4    �����¼�����   				�¼��ı����
	ID: 0x0102  Byte:  3    ���ز���վ������ʶ����    	�����ı���� 
	ID: 0X0104  Byte:  2    ���о�������
	ID: 0x0105  Byte:  1    ���ڷ���ڵ���ʱ
	
	ID: 0X0201  Byte: 15    ������״̬����        		10Hz
	ID: 0X0202  Byte: 14    ʵʱ������������   			50Hz       
	ID: 0x0203  Byte: 16    ������λ������           	10Hz
	ID: 0x0204  Byte:  1    ��������������           	����״̬�ı����
	ID: 0x0205  Byte:  3    ���л���������״̬����      10Hz
	ID: 0x0206  Byte:  1    �˺�״̬����           		�˺���������
	ID: 0x0207  Byte:  6    ʵʱ�������           		�ӵ��������
	ID: 0x0208  Byte:  2    ����ʣ������  �����л����� �ڱ�
	ID: 0x0209  Byte:  4    ������RFID״̬
	
	ID: 0x0301  Byte:  n    �����˼佻������           	���ͷ���������,10Hz
	
*/

#define JUDGE_BUFFER_LEN 200              //����������

#define JUDGE_FRAME_HEADER 0xA5           //֡ͷ

#define    JUDGE_DATA_ERROR      0
#define    JUDGE_DATA_CORRECT    1     //����ϵͳ���Բ�������

#define shoot_speed_limit 20;

#define TRUE 1
#define FALSE 0

#define BLUE 0
#define RED 1

//���ȸ���Э�鶨��,���ݶγ���Ϊn��Ҫ����֡ͷ�ڶ��ֽ�����ȡ
#define    LEN_HEADER    5        //֡ͷ��
#define    LEN_CMDID     2        //�����볤��
#define    LEN_TAIL      2	      //֡βCRC16

/* RFID������ */
#define    CARD_ATTACK        ((uint8_t)0x00)
#define    CARD_PROTECT       ((uint8_t)0x01)
#define    CARD_BLOOD_RED     ((uint8_t)0x02)
#define    CARD_BLOOD_BLUE    ((uint8_t)0x03)
#define    CARD_HEAL_RED      ((uint8_t)0x04)
#define    CARD_HEAL_BLUE     ((uint8_t)0x05)
#define    CARD_COLD_RED      ((uint8_t)0x06)
#define    CARD_COLD_BLUE     ((uint8_t)0x07)
#define    CARD_FORT          ((uint8_t)0x08)


#define    LEN_HEADER    5        //֡ͷ��
#define    LEN_CMDID     2        //�����볤��
#define    LEN_TAIL      2	      //֡βCRC16

/*����*/
bool Judge_IF_Refer_Normal(void);
#define     IF_REFER_NORMAL      Judge_IF_Refer_Normal()


//ͨ��Э���ʽ
typedef enum  
{
	FRAME_HEADER         = 0,
	CMD_ID               = 5,
	DATA                 = 7,
	
}JudgeFrameOffset;

// frame_header ��ʽ
typedef enum
{
	SOF          = 0,//��ʼλ
	DATA_LENGTH  = 1,//֡�����ݳ���,�����������ȡ���ݳ���
	SEQ          = 3,//�����
	CRC8         = 4 //CRC8	
}	FrameHeaderOffset;


typedef enum
{
	ID_game_state       = 0x0001,
	ID_game_result      = 0x0002,
	ID_game_robot_survivors       	= 0x0003,//���������˴������
	ID_game_missile_state = 0x0004, //���ڷ���״̬
	ID_game_buff         =0x0005,//buff
	
	ID_event_data  					= 0x0101,//�����¼����� 
	ID_supply_projectile_action   	= 0x0102,//���ز���վ������ʶ����
	ID_supply_warm 	= 0x0104,//����ϵͳ��������
	ID_missile_shoot_time =0x0105  , //���ڷ���ڵ���ʱ
	
	ID_game_robot_state    			= 0x0201,//������״̬����
	ID_power_heat_data    			= 0x0202,//ʵʱ������������
	ID_game_robot_pos        		= 0x0203,//������λ������
	ID_buff_musk					= 0x0204,//��������������
	ID_aerial_robot_energy			= 0x0205,//���л���������״̬����
	ID_robot_hurt					= 0x0206,//�˺�״̬����
	ID_shoot_data					= 0x0207,//ʵʱ�������
	ID_bullet_remaining          = 0x0208,//ʣ�෢����
	ID_rfid_status									= 0x0209,//������RFID״̬��1Hz
	
	ID_dart_client_directive        = 0x020A,//���ڻ����˿ͻ���ָ����, 10Hz
  
	ID_robot_interactive_header_data			= 0x0301,//�����˽������ݣ��������ͷ������������� 10Hz
	ID_controller_interactive_header_data = 0x0302,//�Զ���������������ݽӿڣ�ͨ�������ͻ��˴����������� 30Hz
	ID_map_interactive_header_data        = 0x0303,//�ͻ���С��ͼ�������ݣ������������͡���
	ID_keyboard_information               = 0x0304//���̡������Ϣ��ͨ������ͼ�����ڡ�������

}CmdID;

typedef enum
{
	/* Std */
	LEN_FRAME_HEAD 	                 = 5,	// ֡ͷ����
	LEN_CMD_ID 		                   = 2,	// �����볤��
	LEN_FRAME_TAIL 	                 = 2,	// ֡βCRC16
	/* Ext */  

	LEN_game_state       				=  11,	//0x0001
	LEN_game_result       				=  1,	//0x0002
	LEN_game_robot_survivors       		=  32,	//0x0003  ����������Ѫ������
	LED_game_missile_state      =3  , //0X0004���ڷ���״̬
	LED_game_buff               =11 , //0X0005
	
	LEN_event_data  					=  4,	//0x0101  �����¼����� 
	LEN_supply_projectile_action        =  4,	//0x0102���ز���վ������ʶ����
	LEN_supply_warm        =2, //����ϵͳ���� 0x0104
	LEN_missile_shoot_time =1  , //���ڷ���ڵ���ʱ
	
	LEN_game_robot_state    			= 27,	//0x0201������״̬����
	LEN_power_heat_data   				= 16,	//0x0202ʵʱ������������
	LEN_game_robot_pos        			= 16,	//0x0203������λ������
	LEN_buff_musk        				=  1,	//0x0204��������������
	LEN_aerial_robot_energy        		=  1,	//0x0205���л���������״̬����
	LEN_robot_hurt        				=  1,	//0x0206�˺�״̬����
	LEN_shoot_data       				=  7,	//0x0207	ʵʱ�������
	LEN_bullet_remaining          = 6,//ʣ�෢����
  
	LEN_rfid_status					         = 4,
	LEN_dart_client_directive        = 12,//0x020A
	// 0x030x
	//LEN_robot_interactive_header_data      = n,
	//LEN_controller_interactive_header_data = n,
	LEN_map_interactive_headerdata           = 15,
	LEN_keyboard_information                 = 12,//0x0304

}JudgeDataLength;

/* �Զ���֡ͷ */
typedef __packed struct
{
	uint8_t  SOF;
	uint16_t DataLength;
	uint8_t  Seq;
	uint8_t  CRC8;
	
} xFrameHeader;

/* ID: 0x0001  Byte:  11    ����״̬���� */
typedef __packed struct 
{ 
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_state_t; 

/* ID: 0x0002  Byte:  1    ����������� */
typedef __packed struct 
{ 
	uint8_t winner;
} ext_game_result_t; 

/* ID: 0x0003  Byte:  32    ����������Ѫ������ */
typedef __packed struct 
{ 
	uint16_t red_1_robot_HP;   
	uint16_t red_2_robot_HP;  
	uint16_t red_3_robot_HP;  
	uint16_t red_4_robot_HP;  
	uint16_t red_5_robot_HP;  
	uint16_t red_6_robot_HP;  
	uint16_t red_7_robot_HP;  
	uint16_t red_outpost_HP; 
  uint16_t red_base_HP; 
	
	uint16_t blue_1_robot_HP;   
	uint16_t blue_2_robot_HP;   
	uint16_t blue_3_robot_HP;   
	uint16_t blue_4_robot_HP;   
	uint16_t blue_5_robot_HP;   
	uint16_t blue_6_robot_HP;   
	uint16_t blue_7_robot_HP; 

	uint16_t blue_outpost_HP; 
  uint16_t blue_base_HP;   
}  ext_game_robot_HP_t; 

/* ID: 0x0004  Byte:  3    ���ڷ���״̬ */
typedef __packed struct 
{  
	uint8_t dart_belong; 
	uint16_t stage_remaining_time; 
} ext_dart_status_t;

/* ID: 0x0005  Byte:  11    buff */
typedef __packed struct
{ 
	uint8_t F1_zone_status:1;  
	uint8_t F1_zone_buff_debuff_status:3;   
	
	uint8_t F2_zone_status:1;  
	uint8_t F2_zone_buff_debuff_status:3;   
	
	uint8_t F3_zone_status:1;  
	uint8_t F3_zone_buff_debuff_status:3;  
	
	uint8_t F4_zone_status:1;  
	uint8_t F4_zone_buff_debuff_status:3;  
	
	uint8_t F5_zone_status:1;  
	uint8_t F5_zone_buff_debuff_status:3;  
	
	uint8_t F6_zone_status:1;  
	uint8_t F6_zone_buff_debuff_status:3;  
  
  uint16_t red1_bullet_left;
  
  uint16_t red2_bullet_left;
  
  uint16_t blue1_bullet_left;
  
  uint16_t blue2_bullet_left;
  
} ext_ICRA_buff_debuff_zone_status_t; 

/* ID: 0x0101  Byte:  4    �����¼����� */
typedef __packed struct 
{ 
	uint32_t event_type;
} ext_event_data_t; 


/* ID: 0x0102  Byte:  4    ���ز���վ������ʶ���� */
typedef __packed struct 
{ 
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
  uint8_t supply_projectile_num;
} ext_supply_projectile_action_t; 

/* ID: 0x0104  Byte: 2   ����ϵͳ������Ϣ */
typedef __packed struct 
{ 
  uint8_t level; 
	uint8_t foul_robot_id;
}  ext_referee_warning_t;  

/* ID: 0x0105  Byte:1  ���ڷ���ڵ���ʱ */
typedef __packed struct 
{ 
	uint8_t dart_remaining_time; 
}  ext_dart_remaining_time_t; 

/* ID: 0X0201  Byte: 27    ������״̬���� */
typedef __packed struct 
{ 
	uint8_t robot_id;   //������ID��������У�鷢��
	uint8_t robot_level;  //1һ����2������3����
	uint16_t remain_HP;  //������ʣ��Ѫ��
	uint16_t max_HP; //��������Ѫ��

  uint16_t shooter1_17mm_cooling_rate;  //������ 17mm �ӵ�������ȴ�ٶ� ��λ /s
  uint16_t shooter1_17mm_cooling_limit;   // ������ 17mm �ӵ���������  
  uint16_t shooter1_17mm_speed_limit;

  
  uint16_t shooter2_17mm_cooling_rate;
  uint16_t shooter2_17mm_cooling_limit;  
  uint16_t shooter2_17mm_speed_limit;

  
  uint16_t shooter_42mm_cooling_rate;
  uint16_t shooter_42mm_cooling_limit;
  uint16_t shooter_42mm_speed_limit;

  
	uint16_t max_chassis_power; 
	uint8_t mains_power_gimbal_output : 1;  
	uint8_t mains_power_chassis_output : 1;  
	uint8_t mains_power_shooter_output : 1; 
} ext_game_robot_state_t;   

/* ID: 0X0202  Byte: 16    ʵʱ������������ */
typedef __packed struct 
{ 
	uint16_t chassis_volt;   
	uint16_t chassis_current;    
	float chassis_power;   //˲ʱ���� 
	uint16_t chassis_power_buffer;//60������������
	uint16_t shooter_heat0;//17mm
	uint16_t shooter_heat1;  
	uint16_t mobile_shooter_heat2; 
} ext_power_heat_data_t; 

/* ID: 0x0203  Byte: 16    ������λ������ */
typedef __packed struct 
{   
	float x;   
	float y;   
	float z;   
	float yaw; 
} ext_game_robot_pos_t; 

/* ID: 0x0204  Byte:  1    �������������� */
typedef __packed struct 
{ 
	uint8_t power_rune_buff; 
} ext_buff_musk_t; 

/* ID: 0x0205  Byte:  1    ���л���������״̬���� */
typedef __packed struct 
{ 
  uint8_t attack_time;
} aerial_robot_energy_t; 

/* ID: 0x0206  Byte:  1    �˺�״̬���� */
typedef __packed struct 
{ 
	uint8_t armor_id : 4; 
	uint8_t hurt_type : 4; 
} ext_robot_hurt_t; 

/* ID: 0x0207  Byte:  7    ʵʱ������� */
typedef __packed struct 
{ 
	uint8_t bullet_type; 
  uint8_t shooter_id;  //���������17����42
	uint8_t bullet_freq;   
	float bullet_speed;  
} ext_shoot_data_t; 


/* ID: 0x0208  Byte:  6    �ӵ�ʣ������ */
typedef __packed struct 
{ 
  uint16_t bullet_remaining_num_17mm;
  uint16_t bullet_remaining_num_42mm;
  uint16_t coin_remaining_num;//���ʣ��
}  ext_bullet_remaining_t; 

/* ID: 0x0209  Byte:  4 	������RFID״̬ */
typedef __packed struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;

typedef __packed struct{
	uint8_t dart_launch_opening_status;//��ǰ���ڷ���ڵ�״̬
	uint8_t dart_attack_target;        //���ڵĴ��Ŀ�꣬Ĭ��Ϊǰ��վ��1��ǰ��վ��2�����أ�
	uint16_t target_change_time;       //�л����Ŀ��ʱ�ı���ʣ��ʱ��
	uint8_t first_dart_speed;          //��⵽�ĵ�һö�����ٶȣ���λ 0.1m/s/LSB
	uint8_t second_dart_speed;         //��⵽�ĵڶ�ö�����ٶȣ���λ 0.1m/s/LSB
	uint8_t third_dart_speed;          //��⵽�ĵ���ö�����ٶȣ���λ 0.1m/s/LSB
	uint8_t fourth_dart_speed;         //��⵽�ĵ���ö�����ٶȣ���λ 0.1m/s/LSB
	uint16_t last_dart_launch_time;    //���һ�εķ�����ڵı���ʣ��ʱ�䣬��λ��
	uint16_t operate_launch_cmd_time;  //���һ�β�����ȷ������ָ��ʱ�ı���ʣ��ʱ�䣬��λ��
} ext_dart_client_cmd_t; //LEN_DART_CLIENT_DIRECTIVE  ��3-19

/* 
	
	�������ݣ�����һ��ͳһ�����ݶ�ͷ�ṹ��
	���������� ID���������Լ������ߵ� ID ���������ݶΣ�
	�����������ݵİ��ܹ������Ϊ 128 ���ֽڣ�
	��ȥ frame_header,cmd_id,frame_tail �Լ����ݶ�ͷ�ṹ�� 6 ���ֽڣ�
	�ʶ����͵��������ݶ����Ϊ 113��
	������������ 0x0301 �İ�����Ƶ��Ϊ 10Hz��

	������ ID��
	1��Ӣ��(��)��
	2������(��)��
	3/4/5������(��)��
	6������(��)��
	7���ڱ�(��)��
	11��Ӣ��(��)��
	12������(��)��
	13/14/15������(��)��
	16������(��)��
	17���ڱ�(��)�� 
	�ͻ��� ID�� 
	0x0101 ΪӢ�۲����ֿͻ���( ��) ��
	0x0102 �����̲����ֿͻ��� ((�� )��
	0x0103/0x0104/0x0105�����������ֿͻ���(��)��
	0x0106�����в����ֿͻ���((��)�� 
	0x0111��Ӣ�۲����ֿͻ���(��)��
	0x0112�����̲����ֿͻ���(��)��
	0x0113/0x0114/0x0115�������ֿͻ��˲���(��)��
	0x0116�����в����ֿͻ���(��)�� 
*/

/* �������ݽ�����Ϣ��0x0301  */
typedef __packed struct 
{ 
	uint16_t data_cmd_id;    
	uint16_t send_ID;    
	uint16_t receiver_ID; 
} ext_student_interactive_header_data_t; 

enum judge_robot_ID{
	hero_red       = 1,
	engineer_red   = 2,
	infantry3_red  = 3,
	infantry4_red  = 4,
	infantry5_red  = 5,
	plane_red      = 6,
	
	hero_blue      = 101,
	engineer_blue  = 102,
	infantry3_blue = 103,
	infantry4_blue = 104,
	infantry5_blue = 105,
	plane_blue     = 106,
};
typedef struct{
	uint16_t teammate_hero;
	uint16_t teammate_engineer;
	uint16_t teammate_infantry3;
	uint16_t teammate_infantry4;
	uint16_t teammate_infantry5;
	uint16_t teammate_plane;
	uint16_t teammate_sentry;
	
	uint16_t client_hero;
	uint16_t client_engineer;
	uint16_t client_infantry3;
	uint16_t client_infantry4;
	uint16_t client_infantry5;
	uint16_t client_plane;
} ext_interact_id_t;



/* 
	ѧ�������˼�ͨ�� cmd_id 0x0301������ ID:0x0200~0x02FF
	�������� �����˼�ͨ�ţ�0x0301��
	����Ƶ�ʣ����� 10Hz  

	�ֽ�ƫ���� 	��С 	˵�� 			��ע 
	0 			2 		���ݵ����� ID 	0x0200~0x02FF 
										���������� ID ��ѡȡ������ ID �����ɲ������Զ��� 
	
	2 			2 		�����ߵ� ID 	��ҪУ�鷢���ߵ� ID ��ȷ�ԣ� 
	
	4 			2 		�����ߵ� ID 	��ҪУ������ߵ� ID ��ȷ�ԣ�
										���粻�ܷ��͵��жԻ����˵�ID 
	
	6 			n 		���ݶ� 			n ��ҪС�� 113 

*/
typedef __packed struct 
{ 
	uint8_t data[113]; //���ݶ�,n��ҪС��113
} robot_interactive_data_t;




/**
  * @brief  ��ȡ��������,loop��ѭ�����ô˺�������ȡ����
  * @param  ��������
  * @retval �Ƿ�������ж�������
  * @attention  �ڴ��ж�֡ͷ��CRCУ��,������д������
  */
bool Judege_read_data(u8 *ReadFromUsart );





typedef struct judge_info_struct {
	xFrameHeader							FrameHeader;				// ֡ͷ��Ϣ
	
	ext_game_state_t 							GameState;				// 0x0001           ����״̬����
	ext_game_result_t 							GameResult;				// 0x0002         �����������
	ext_game_robot_HP_t 						GameRobotHP;			// 0x0003         ������Ѫ������
	ext_dart_status_t								GameRobotmissile;				// 0x0004         ���ڷ���״̬
	ext_ICRA_buff_debuff_zone_status_t	Game_ICRA_buff;      //                �˹�������ս���ӳ���ͷ���״̬
	
	ext_event_data_t								EventData;					// 0x0101         �����¼�����
	ext_supply_projectile_action_t	SupplyProjectileAction;		// 0x0102 ����վ������ʶ
	ext_referee_warning_t						RefereeWarning;		// 0x0104         ���о�����Ϣ
	ext_dart_remaining_time_t				dart_remaining_time;// 0x0105         ���ڷ���ڵ���ʱ
	
	ext_game_robot_state_t					GameRobotStat;	// 0x0201         ����������״̬
	ext_power_heat_data_t						PowerHeatData;		// 0x0202         ʵʱ������������
	ext_game_robot_pos_t						GameRobotPos;			// 0x0203         ������λ��
	ext_buff_musk_t											Buff;								// 0x0204     ����������
	aerial_robot_energy_t				AerialRobotEnergy;// 0x0205             ���л���������״̬
	ext_robot_hurt_t								RobotHurt;					// 0x0206         �˺�״̬
	ext_shoot_data_t								ShootData;					// 0x0207         ʵʱ�����Ϣ(��Ƶ  ����  �ӵ���Ϣ)
	ext_bullet_remaining_t					bullet_remaining;		// 0x0208	        �ӵ�ʣ�෢����
	ext_rfid_status_t								rfid_status;				// 0x0209	        RFID��Ϣ
	ext_dart_client_cmd_t           dart_client;        // 0x020A         ���ڿͻ���
	
	ext_interact_id_t								ids;								//�뱾�������Ļ�����id
	uint16_t                        self_client;        //�����ͻ���
	bool	 		IF_REF_ONL;

} Referee_info_t;
/* 
	ѧ�������˼�ͨ�� cmd_id 0x0301������ data_ID:0x0200~0x02FF
	�������� �����˼�ͨ�ţ�0x0301��
	����Ƶ�ʣ����������кϼƴ������� 5000 Byte�� �����з���Ƶ�ʷֱ𲻳���30Hz��
 * +------+------+-------------+------------------------------------+
 * | byte | size |    breif    |            note                    |
 * |offset|      |             |                                    |
 * +------+------+-------------+------------------------------------+
 * |  0   |  2   | 	 data_ID   | 0x0200~0x02FF,��������Щ ID ��ѡȡ |
 * |      |      |             | ����ID�����ɲ������Զ���           |
 * +------|------|-------------|------------------------------------|
 * |  2   |  2   | 	sender_ID  | ��ҪУ�鷢���ߵ� ID ��ȷ��					|
 * +------|------|-------------|------------------------------------|
 * |  4   |  2   | receiver_ID | ��ҪУ������ߵ� ID ��ȷ��					|
 * |      |      |             | ���粻�ܷ��͵��жԻ����˵�ID				| 
 * +------|------|-------------|------------------------------------|
 * |  6   |  n   | 		Data     | n ��ҪС�� 113 										|
 * +------+------+-------------+------------------------------------+
*/

/******************************�ͻ��˽�������**************************************/
enum
{
	//0x200-0x02ff 	�����Զ������� ��ʽ  INTERACT_ID_XXXX
	INTERACT_ID_delete_graphic 			= 0x0100,	/*�ͻ���ɾ��ͼ��*/
	INTERACT_ID_draw_one_graphic 		= 0x0101,	/*�ͻ��˻���һ��ͼ��*/
	INTERACT_ID_draw_two_graphic 		= 0x0102,	/*�ͻ��˻���2��ͼ��*/
	INTERACT_ID_draw_five_graphic 	= 0x0103,	/*�ͻ��˻���5��ͼ��*/
	INTERACT_ID_draw_seven_graphic 	= 0x0104,	/*�ͻ��˻���7��ͼ��*/
	INTERACT_ID_draw_char_graphic 	= 0x0110,	/*�ͻ��˻����ַ�ͼ��*/
	INTERACT_ID_bigbome_num					= 0x02ff
};
//��λ���ֽڣ�
enum
{
	LEN_INTERACT_delete_graphic     = 8,  //ɾ��ͼ�� 2(��������ID)+2(������ID)+2��������ID��+2���������ݣ�  
	LEN_INTERACT_draw_one_graphic   = 21, // ����2+2+2+15
	LEN_INTERACT_draw_two_graphic   = 36, //6+15*2
	LEN_INTERACT_draw_five_graphic  = 81, //6+15*5
	LEN_INTERACT_draw_seven_graphic = 111,//6+15*7
	LEN_INTERACT_draw_char_graphic  = 51, //6+15+30���ַ������ݣ�
};
//****************************��ͼ�����ݶ�����****************************/
typedef __packed struct//ͼ��
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; //ֱ��  ����  ��Բ  ��Բ  Բ��  ����  ����  �ַ�
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t start_angle:9;  //��    ��    ��    ��    �Ƕ�  ��С  ��С  ��С
	uint32_t end_angle:9;    //��    ��    ��    ��          λ��  ��    ����
	uint32_t width:10;       
	uint32_t start_x:11;     //���  ���  Բ��  Բ��  Բ��  ���  ���  ���
	uint32_t start_y:11;     //
	uint32_t radius:10;      //��    ��    �뾶  ��    ��    ��    ��    ��
	uint32_t end_x:11;       //�յ�  �Զ�  ��    ����  ����  ��    ��    ��
	uint32_t end_y:11;       //                              ��    ��    ��
} graphic_data_struct_t;
typedef __packed struct//������
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; 
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t start_angle:9;  
	uint32_t end_angle:9;    
	uint32_t width:10;       
	uint32_t start_x:11;    
	uint32_t start_y:11;     
  float number;       
} Float_data_struct_t;
typedef __packed struct//������
{                          
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; 
	uint32_t layer:4;        
	uint32_t color:4;        
	uint32_t start_angle:9;  
	uint32_t end_angle:9;    
	uint32_t width:10;       
	uint32_t start_x:11;    
	uint32_t start_y:11;     
  int number;       
} Int_data_struct_t;
/* data_ID: 0X0100  Byte:  2	    �ͻ���ɾ��ͼ��*/
typedef __packed struct
{
	uint8_t operate_type; 
	uint8_t layer;//ͼ������0~9
}ext_client_custom_graphic_delete_t;
typedef enum
{
	NONE_delete    = 0,
	GRAPHIC_delete = 1,
	ALL_delete     = 2
}delete_Graphic_Operate;//ext_client_custom_graphic_delete_t��uint8_t operate_type
/*ͼ��ɾ������*/

//bit 0-2
typedef enum
{
	NONE   = 0,/*�ղ���*/
	ADD    = 1,/*����ͼ��*/
	MODIFY = 2,/*�޸�ͼ��*/
	DELETE = 3,/*ɾ��ͼ��*/
}Graphic_Operate;//graphic_data_struct_t��uint32_t operate_tpye
/*ͼ�����*/
//bit3-5
typedef enum
{
	LINE      = 0,//ֱ��
	RECTANGLE = 1,//����
	CIRCLE    = 2,//��Բ
	OVAL      = 3,//��Բ
	ARC       = 4,//Բ��
	FLOAT     = 5,//������
	INT       = 6,//������
	CHAR      = 7 //�ַ�
}Graphic_Type;
/*ͼ������*/
//bit 6-9ͼ���� ���Ϊ9����С0
//bit 10-13��ɫ
typedef enum
{
	RED_BLUE  = 0,//������ɫ	
	YELLOW    = 1,
	GREEN     = 2,
	ORANGE    = 3,
	FUCHSIA   = 4,	/*�Ϻ�ɫ*/
	PINK      = 5,
	CYAN_BLUE = 6,	/*��ɫ*/
	BLACK     = 7,
	WHITE     = 8
}Graphic_Color;
/*ͼ����ɫ����*/
//bit 14-31 �Ƕ� [0,360]
/**********************************�ͻ��˻�ͼ************************************************/
//ɾ��ͼ��
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	ext_client_custom_graphic_delete_t clientData;		
	uint16_t	FrameTail;								
}ext_deleteLayer_data_t;

//���ַ���
typedef __packed struct
{
	graphic_data_struct_t grapic_data_struct;
	uint8_t data[30];
} ext_client_string_t;


//�̶����ݶγ������ݰ�
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//֡ͷ
	uint16_t  CmdID;										//������
	ext_student_interactive_header_data_t   dataFrameHeader;//���ݶ�ͷ�ṹ
	ext_client_string_t clientData;//���ݶ�
	uint16_t	FrameTail;								//֡β
}ext_charstring_data_t;
//������ͼ
typedef __packed struct
{
	xFrameHeader txFrameHeader;			//֡ͷ
	uint16_t  CmdID;										//������
	ext_student_interactive_header_data_t   dataFrameHeader;//���ݶ�ͷ�ṹ
	graphic_data_struct_t clientData;		//���ݶ�
	uint16_t	FrameTail;								//֡β
}ext_graphic_one_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_graphic_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[5];		
	uint16_t	FrameTail;								
}ext_graphic_five_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	graphic_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_graphic_seven_data_t;
//���Ƹ�����
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Float_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_float_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Float_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_float_seven_data_t;
//��������
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Int_data_struct_t clientData[2];		
	uint16_t	FrameTail;								
}ext_int_two_data_t;
typedef __packed struct
{
	xFrameHeader txFrameHeader;			
	uint16_t  CmdID;										
	ext_student_interactive_header_data_t   dataFrameHeader;
	Int_data_struct_t clientData[7];		
	uint16_t	FrameTail;								
}ext_int_seven_data_t;


void Client_graphic_Init(void);
void Client_graphic_delete_update(uint8_t delete_layer);//ɾ��ͼ����Ϣ
void Client_graphic_Info_update(void);


void Client_aim_update(void);//׼��
void Client_supercapacitor_update(void);//��������
void Client_gimbal_angle_update(void);//����Ƕ�
void Client_bullet_int_update(void);//������Ϣ

//Ӣ��
void Client_aim_line(void);//
void _high_aim_(void);
void _lowshort_aim_2(void);
void _lowshort_aim_3(void);
void _lowshortstem_aim_4(void);
void _lowlong_aim_(void);


void Judge_IF_REF_ONL(void);

//------------PowerHeatData------------//              ��
float REF_Report_CHAS_Power(void);   //4
uint16_t REF_Report_CHAS_PowerBuffer(void);   //2  
uint16_t REF_Report_Shooter_Heat(void);    //2
//------------------RFID-------------------------//    ��
uint8_t REF_Report_RFID_State(void);
//------------ShootInfo----------------//
float REF_Report_RealShootSpeed(void);//4
//------------GameRobotStat------------//              ��
uint8_t REF_Report_robot_ID(void); //1
uint8_t REF_Report_Shoot_SpeedLimit(void); //1
uint16_t REF_Report_Shoot_CoolingLimit(void);  //2
uint16_t REF_Report_Shoot_CoolingRate(void);  //2 ��
uint16_t REF_Report_CHAS_MaxPower(void) ; //2
uint8_t REF_Report_IF_shooter_output(void);//1
/***************************����ϵͳ���ڳ�ʼ��***********************************/
void UART5_Init( void );
void UART5_DMA_Init( void );
/**
  * @brief  ����һ�η���һ���ֽ�����
  * @param  �Լ�����õ�Ҫ�������е�����
  * @retval void
  * @attention  ������λ����
  */
void UART5_SendChar(uint8_t cData);
void Determine_ID(void);//�ж��Լ����ĸ�����
#endif 

