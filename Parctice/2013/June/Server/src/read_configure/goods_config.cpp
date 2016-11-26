#include"goods_config.h"
#include<string.h>
#include<string>
#include<iostream>
using namespace::std;
Goods_Config::Goods_Config(char* _id,char* _name,char* _effect,int _order,int _repeat,int _type,int _levelLimit,int _gold,int _goldBound,int _money,int _moneyBound,int _price)
{
	int len;
	len = strlen(_id);
	id = new char[len+1];
	strncpy(id,_id,len);
	id[len]='\0';		//物品id

	len = strlen(_name);
	name = new char[len+1];
	strncpy(name,_name,len);
	name[len]='\0';				//物品名称
	
	len = strlen(_effect);
	effect = new char[len+1];
	strncpy(effect,_effect,len);
	effect[len]='\0';			//物品效果
	
	order=_order;			//排序序号
	repeat=_repeat;				//堆叠数量
	type=_type;				//类型
	levelLimit=_levelLimit;			//等级限制
	gold=_gold;				//买入元宝价格
	goldBound=_goldBound;
	moneyBound=_moneyBound;//卖出游戏币价格
	money=_money;	
	price=_price;
}

char* Goods_Config::getId(void)           //物品id
{
	return id;
}

char* Goods_Config::getName(void)		 //物品名称
{
	return name;
}

char* Goods_Config::getEffect(void)        //物品效果
{
	return effect;
}

int Goods_Config::getOrder(void)			//排序序号
{
	return order;
}

int Goods_Config::getRepeat(void)         //堆叠数量
{
	return repeat;
}

int	Goods_Config::getType(void)         //类型
{
	return type;
}

int Goods_Config::getLevelLimit(void)        //等级限制
{
	return levelLimit;
}

int Goods_Config::getGold(void)    //买入元宝价格
{
	return gold;
}

int Goods_Config::getGoldBound(void)
{
	return goldBound;
}

int Goods_Config::getMoneyBound(void)
{
	return moneyBound;
}

int Goods_Config::getMoney(void)      //卖出游戏币价格
{
	return money;
}

int Goods_Config::getPrice(void)      //卖出游戏币价格
{
	return price;
}