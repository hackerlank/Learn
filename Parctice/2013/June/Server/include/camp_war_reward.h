#ifndef INCLUDE_CAMP_WAR_REWARD_
#define INCLUDE_CAMP_WAR_REWARD_
#include "other_define_data.h"

#define ORD_REWARD 0
#define WIN_LEADER_REWARD 1 
#define FAI_LEADER_REWARD 2
#define FIRST_CHIEF_REWARD 3
#define SECOND_CHIEF_REWARD 4
#define THIRD_CHIEF_REWARD 5

#define CAMP_WAR_REWARD_SIZE 6

#define FIRST_TITLE "T029"								//武神头衔ID
#define SECOND_TITLE "T030"								//武圣头衔ID
#define THIRD_TITLE "T031"								//武尊头衔ID

#define CAMP_LEADER_TITLE "T025"						//统领头衔ID
#define CAMP_CHIEF_TITLE "T024"							//盟主头衔ID

/*
 *阵营战奖励结构体，有疑问RTX xhm
*/
typedef struct CampRewardData_S{
	int gold_base_value;		//绑定金币基准数据（第一名奖励金币值)
	int gold_dec_value;			//绑定金币递减大小(每靠后一名减少金币大小)
	int prestige_base_value;	//声望基准数据
	int prestige_dec_value;		//声望递减大小
	int guidGlory_base_value;	//帮贡基准数据
	int guidGlory_dec_value;	//帮贡递减大小
	int guidExp_base_value;		//帮派经验基准数据
	int guidExp_dec_value;		//帮派经验递减大小
	int rank_limit_value;		//排名递减限制大小(等于或者小于这个名次，奖励不递减，												和rank_limit_value-1名次奖励相同)
	
	CampRewardData_S(){
		gold_base_value=0;		
		gold_dec_value=0;			
		prestige_base_value=0;	
		prestige_dec_value=0;		
		guidGlory_base_value=0;	
		guidGlory_dec_value=0;	
		guidExp_base_value=0;		
		guidExp_dec_value=0;		
		rank_limit_value=0;			
	}

}CampRewardData_T;

#endif