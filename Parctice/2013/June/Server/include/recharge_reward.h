/****************************************************************
 * Filename: recharge_reward.h
 * 
 * Description: 充值奖励
 *
 * Original Author : xhm, 2012-12-27
 *
 ****************************************************************/

#ifndef MY_RECHARGE_REWARD_H_
#define MY_RECHARGE_REWARD_H_

#include<map>
#include<string>

using namespace std;

class Recharge_reward{
public:
	Recharge_reward();
	~Recharge_reward();
	
	bool send_reward(void);
	bool init_recharge_reward(void);
	
	bool save_recharge_reward_info(void);	
	bool del_from_reward_team(char *myHeroId);
	int add_to_reward_team(char *myHeroId,int size);
	
public:
	bool isActivity;
	int min_recharge_size;	
	map<string,int> recharge_reward_heroId;
	
private:
	map<string,int>::iterator reward_iter;	// 排序用的容器； 
	pair< map< string,int>::iterator,bool > reward_insert_ret;//用于insert的返回值，判断insert是否成功。
};
#endif