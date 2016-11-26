/****************************************************************
 * Filename: recharge_reward_assist.h
 * 
 * Description: 充值.消费奖励管理文件
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/
#ifndef _RECHARGE_REWARD_ASSIST_H_
#define _RECHARGE_REWARD_ASSIST_H_

#include <string.h>
#include"wholeDefine.h"

#define MAX_REWARD_LEVEL 10
#define MAX_GOODS_ID_LEN 20
#define MAX_RECHARGE_HERO 1000
#define MAX_SPECIAL_REWARD_HERO 10


typedef struct Recharge_reward_time_S{
	int year;//充值奖励活动年份
	int month;//充值奖励活动月份
	int start_day;//充值奖励活动开始日期
	int end_day;//充值奖励活动结束日期
	
	void init()
	{
		year=0;//充值奖励活动年份
		month=0;//充值奖励活动月份
		start_day=0;//充值奖励活动开始日期
		end_day=0;//充值奖励活动结束日期	
	
	}
}Recharge_reward_time_T;

typedef struct Consume_reward_time_S{
	int year;//消费奖励活动年份
	int month;//消费奖励活动月份
	int start_day;//消费奖励活动开始日期
	int end_day;//消费奖励活动结束日期
	
	void init()
	{
		year=0;//消费奖励活动年份
		month=0;//消费奖励活动月份
		start_day=0;//消费奖励活动开始日期
		end_day=0;//消费奖励活动结束日期	
	
	}
}Consume_reward_time_T;

typedef struct Recharge_reward_obj_S{
	Recharge_reward_time_T recharge_reward_time;//时间存储；
	char heroId[MAX_RECHARGE_HERO*8][HEROID_LENGTH];//充值奖励1heroid集合
	int	 recharge_num[MAX_RECHARGE_HERO*8];
	char special_reward_obj[MAX_SPECIAL_REWARD_HERO][HEROID_LENGTH];//特殊奖励角色Id；
	
	void init(){
		recharge_reward_time.init();
		memset(heroId,0,sizeof(heroId));
		memset(recharge_num,0,sizeof(recharge_num));
		memset(special_reward_obj,0,sizeof(special_reward_obj));
	}	
}Recharge_reward_obj_T;

typedef struct Consume_reward_obj_S{
	Consume_reward_time_T consume_reward_time;//时间存储；
	char heroId[MAX_RECHARGE_HERO*8][HEROID_LENGTH];//充值奖励1heroid集合
	int	 consume_num[MAX_RECHARGE_HERO*8];
	char special_reward_obj[MAX_SPECIAL_REWARD_HERO][HEROID_LENGTH];//特殊奖励角色Id；
	
	void init(){
		consume_reward_time.init();
		memset(heroId,0,sizeof(heroId));
		memset(consume_num,0,sizeof(consume_num));
		memset(special_reward_obj,0,sizeof(special_reward_obj));
	}	
}Consume_reward_obj_T;

typedef struct Recharge_reward_detail_S{
	char reward_goods_id[MAX_REWARD_LEVEL][MAX_GOODS_ID_LEN];
	int  reward_goods_num[MAX_REWARD_LEVEL];
	char reward_goods_id2[MAX_REWARD_LEVEL][MAX_GOODS_ID_LEN];//added;
	int  reward_goods_num2[MAX_REWARD_LEVEL];	
	int bind_gold[MAX_REWARD_LEVEL];	
	int levelSize[MAX_REWARD_LEVEL];
	int levelcounts;
	void init()
	{
		memset(reward_goods_id,0,sizeof(reward_goods_id));
		memset(reward_goods_id2,0,sizeof(reward_goods_id2));		
		memset(levelSize,0,sizeof(levelSize));
		memset(bind_gold,0,sizeof(bind_gold));
		memset(reward_goods_num,0,sizeof(reward_goods_num));
		memset(reward_goods_num2,0,sizeof(reward_goods_num2));		
		levelcounts=0;
	}
}Recharge_reward_detail_T;


typedef struct Consume_reward_detail_S{
	char reward_goods_id[MAX_REWARD_LEVEL][MAX_GOODS_ID_LEN];
	int  reward_goods_num[MAX_REWARD_LEVEL];
	char reward_goods_id2[MAX_REWARD_LEVEL][MAX_GOODS_ID_LEN];//added;
	int  reward_goods_num2[MAX_REWARD_LEVEL];	
	int bind_gold[MAX_REWARD_LEVEL];	
	int levelSize[MAX_REWARD_LEVEL];
	int levelcounts;
	void init()
	{
		memset(reward_goods_id,0,sizeof(reward_goods_id));
		memset(reward_goods_id2,0,sizeof(reward_goods_id2));		
		memset(levelSize,0,sizeof(levelSize));
		memset(bind_gold,0,sizeof(bind_gold));
		memset(reward_goods_num,0,sizeof(reward_goods_num));
		memset(reward_goods_num2,0,sizeof(reward_goods_num2));		
		levelcounts=0;
	}
}Consume_reward_detail_T;


typedef struct Goods_reward_obj_S{
	char reward_goods_id[MAX_GOODS_ID_LEN];
	int size;
	
	void init(void){
		memset(reward_goods_id,0,sizeof(reward_goods_id));
		size = 0;
	}
}Goods_reward_obj_T;

typedef struct Goods_oper_reward_S{
	Goods_reward_obj_T goods_reward_obj[3];
	int year;//物品使用奖励年
	int month;//物品使用奖励月份
	int start_day;//物品使用奖励开始日期
	int end_day;//物品使用奖励结束日期

	char good_id[3][MAX_GOODS_ID_LEN];
	
	void init(void){
		year = 0;
		month = 0;
		start_day = 0;
		end_day=0;
		memset(good_id,0,sizeof(good_id));	
		goods_reward_obj[0].init();
		goods_reward_obj[1].init();
		goods_reward_obj[2].init();		
	}
	
}Goods_oper_reward_T;

typedef struct Goods_oper_reward_obj_S{	
	char reward_obj[MAX_RECHARGE_HERO][HEROID_LENGTH];
	int  reward_obj_value[MAX_RECHARGE_HERO];
	int year;//物品使用奖励年
	int month;//物品使用奖励月份
	int start_day;//物品使用奖励开始日期
	int end_day;//物品使用奖励结束日期
	
	void init(void){
		memset(reward_obj,0,sizeof(reward_obj));
		memset(reward_obj_value,0,sizeof(reward_obj_value));
		year = 0;
		month = 0;
		start_day = 0;
		end_day=0;
	}
	
	void clean_reward(void){
		memset(reward_obj,0,sizeof(reward_obj));
		memset(reward_obj_value,0,sizeof(reward_obj_value));	
	}
}Goods_oper_reward_obj_T;


//充值累积奖励
bool isNowRechargeReward(long second);

bool init_rechargeInfo_reward(void);
	
bool save_rechargeInfo_to_mem(void);

bool read_rechargeInfo_from_mem(void);


//消费累积奖励
bool isNowConsumeReward(long second);

bool init_consumeInfo_reward(void);
	
bool save_consumeInfo_to_mem(void);

bool read_consumeInfo_from_mem(void);


//送鲜花，获得鲜花奖励
bool isNowGoodsUseReward(long second);

bool isNowGoodsGainReward(long second);

bool init_goods_opr_reward(void);
	
bool save_goods_gain_info_2_mem();

bool save_goods_use_info_2_mem();

bool read_goods_use_info_from_mem(void);

bool read_goods_gain_info_from_mem(void);



#endif
