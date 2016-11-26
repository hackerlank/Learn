#include "reward_recharge_config.h"
#include <string.h>

Reward_recharge_config::Reward_recharge_config(int _type,int _flag,int _money,int _repeat,int _num,char* _goodsid)
{
	
	type=_type;
	flag=_flag;
	money=_money;
	repeat=_repeat;
	num=_num;
	
	strncpy(goodsid,_goodsid,sizeof(goodsid));
}

int Reward_recharge_config::getType(void)
{
	return type;
}

int Reward_recharge_config::getFlag(void)
{
	return flag;
}

int Reward_recharge_config::getMoney(void)
{
	return money;
}

int Reward_recharge_config::getRepeat(void)
{
	return repeat;
}

int Reward_recharge_config::getNum(void)
{
	return num;
}

char* Reward_recharge_config::getGoodsid(void)
{
	return goodsid;
}