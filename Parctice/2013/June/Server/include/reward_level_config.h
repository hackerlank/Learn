#ifndef REWARD_LEVEL_CONFIG
#define REWARD_LEVEL_CONFIG

#include<iostream>
#include<string>

using namespace std;
class Reward_level_config
{
private:
	int type;							//等级要求
	int flag;							//金币标志
	int money;							//金币数量
	int repeat;							//奖励送的物品所占用的格子数
	int num;							//goodsid的数目
	char goodsid[1024];						//包含goodsid和赠送的数量
public:
	Reward_level_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid);
	int getType(void);
	int getFlag(void);
	int getMoney(void);
	int getRepeat(void);
	int getNum(void);
	char* getGoodsid(void);
};

#endif