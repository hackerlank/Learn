#ifndef REWARD_ONLINE_H
#define REWARD_ONLINE_H
#include <iostream>
#include <string>
#include "hero.h"
#include "reward_online_config.h"
#include "data_structure_struct.h"

class Reward_Online
{
	private:
		OnlineRewarData onlineReward;	
	public:
		Reward_Online(void);
		Reward_Online(OnlineRewarData _onlineReward);
		
		void startOnlineReward(char *msg,int len);
		
		void normalRefresh(char *msg,int len);
		
		void goldRefresh(char *msg,int len);
		
		void judgeTotalTime(void);
		
		OnlineRewarData getMemStruct(void);
		
		void setStage(char *msg,int len);
		
		void levelSetStage(void);
		
		char *getGoodsId(void);
		
		int getMoney(void);
		
		int getGold(void);
		
		void msg_return(char *msg,int len);
		
		void setNewDay(void);
				
		void onlineReward_msg(char *msg,int len);
		
		bool judgeCanReceive(void);
};
#endif