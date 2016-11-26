/****************************************************************
 * Filename: goods_use_reward.h
 * 
 * Description: 物品使用奖励
 *
 * Original Author : xhm, 2013-02-02
 *
 ****************************************************************/

#ifndef MY_GOODS_USE_REWARD_H_
#define MY_GOODS_USE_REWARD_H_

#include<map>
#include<string>

using namespace std;

class Goods_use_reward{
public:
	Goods_use_reward();
	~Goods_use_reward();
	
	bool send_use_reward(void);
	bool send_gain_reward(void);
	bool init_reward(void);
	
	bool save_goods_use_reward_info(void);	
	bool save_goods_gain_reward_info(void);

	int add_goods_use_id_reward_team(char *myHeroId,int size);
	int add_goods_gain_id_reward_team(char *myHeroId,int size);	
public:
	bool isUseActivity;
	bool isGainActivity;
	int min_use_size;
	int min_gain_size;
	map<string,int> goods_use_reward_heroId;
	map<string,int> goods_gain_reward_heroId;	
	
private:
	map<string,int>::iterator reward_iter;	// 排序用的容器； 
	pair< map< string,int>::iterator,bool > reward_insert_ret;//用于insert的返回值，判断insert是否成功。
};
#endif