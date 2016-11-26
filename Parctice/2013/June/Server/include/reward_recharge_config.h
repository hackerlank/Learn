#ifndef REWARD_RECHARGE_CONFIG
#define REWARD_RECHARGE_CONFIG

#include<iostream>
#include<string>

using namespace std;
class Reward_recharge_config
{
private:
	int type;							//累计充值数量
	int flag;							//金币类型
	int money;							//奖励金钱数量
	int repeat;							//奖励送的物品占用的格子数量
	int num;							//goodsid的数目
	char goodsid[1024];					//包含goodsid和赠送的数量

public:
	Reward_recharge_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid);
	int getType(void);
	int getFlag(void);
	int getMoney(void);
	int getRepeat(void);
	int getNum(void);
	char* getGoodsid(void);
};

#endif