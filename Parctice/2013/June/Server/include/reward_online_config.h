#ifndef REWARD_ONLINE_CONFIG
#define REWARD_ONLINE_CONFIG

#include<iostream>
#include<string>
#include<vector>

using namespace std;
class Reward_online_config
{
private:
	char stage[20];							//阶段
	int time;							//时间
	vector<int> moneyPercent;			//随即游戏币概率
	vector<int> moneyNum;				//随即游戏币数量

	vector<int> goldPercent;			//随即元宝概率
	vector<int> goldNum;				//随即元宝数量
	
	vector<int> goodsPercent;			//随即物品概率
	vector<string> goodsid;				//随即物品id

public:
	Reward_online_config(char *_stage,int _time,vector<int> _moneyPercent,vector<int> _moneyNum,vector<int> _goldPercent,\
	vector<int> _goldNum,vector<int> _goodsPercent,vector<string> _goodsid);
	
	char* getStage(void);

	int getTime(void);

	vector<int> getMoneyPercent(void);

	vector<int> getMoneyNum(void);

	vector<int> getGoldPercent(void);

	vector<int> getGoldNum(void);

	vector<int> getGoodsPercent(void);
	
	vector<string> getGoodsid(void);
};

#endif