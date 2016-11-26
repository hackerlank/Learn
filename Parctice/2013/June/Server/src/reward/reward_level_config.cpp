#include "reward_level_config.h"
#include <string.h>

Reward_level_config::Reward_level_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid)
{
	type=_type;
	flag=_flag;
	money=_money;
	repeat=_repeat;
	num=_num;
	strncpy(goodsid,_goodsid,sizeof(goodsid));
}

int Reward_level_config::getType(void)
{
	return type;
}

int Reward_level_config::getFlag(void)
{
	return flag;
}

int Reward_level_config::getMoney(void)
{
	return money;
}

int Reward_level_config::getRepeat(void)
{
	return repeat;
}

int Reward_level_config::getNum(void)
{
	return num;
}

char* Reward_level_config::getGoodsid(void)
{
	return goodsid;
}