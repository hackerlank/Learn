#include "reward_online_config.h"
#include <string.h>

Reward_online_config::Reward_online_config(char *_stage,int _time,vector<int> _moneyPercent,vector<int> _moneyNum,\
										vector<int> _goldPercent,vector<int> _goldNum,vector<int> _goodsPercent,vector<string> _goodsid)
{	
	memset(stage,0,sizeof(stage));
	strncpy(stage,_stage,sizeof(stage));
	
	time=_time;							//时间
	
	moneyPercent=_moneyPercent;			//随即游戏币概率
	moneyNum=_moneyNum;				//随即游戏币数量

	goldPercent=_goldPercent;			//随即元宝概率
	goldNum=_goldNum;				//随即元宝数量
	
	goodsPercent=_goodsPercent;			//随即物品概率
	goodsid=_goodsid;				//随即物品id
	
}

char* Reward_online_config::getStage(void)
{
	return stage;
}

int Reward_online_config::getTime(void)
{
	return time;
}

vector<int> Reward_online_config::getMoneyPercent(void)
{
	return moneyPercent;
}

vector<int> Reward_online_config::getMoneyNum(void)
{
	return moneyNum;
}

vector<int> Reward_online_config::getGoldPercent(void)
{
	return goldPercent;
}

vector<int> Reward_online_config::getGoldNum(void)
{
	return goldNum;
}

vector<int> Reward_online_config::getGoodsPercent(void)
{
	return goodsPercent;
}
vector<string> Reward_online_config::getGoodsid(void)
{
	return goodsid;
}