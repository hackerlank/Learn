#include"ointment.h"
#include<iostream>
using namespace::std;
Ointment::Ointment(string _id,string _name,int _cd,int _sellPriceBoundGold,int _ointmentType,			
		int _sellPriceNoBoundGold,int _sellPriceBoundMoney,int _sellPriceNoBoundMoney,
		int _levelLimits,int _pileUp,int _type,int _value,int _level,int _factor)	
		{
			id=_id;															
			name=_name;	
			cd=_cd;  
			sellPriceBoundGold	=_sellPriceBoundGold;		//npc处售出价格	绑定元宝				
			sellPriceNoBoundGold=_sellPriceNoBoundGold;	 //npc处售出价格	非绑定元宝
			sellPriceBoundMoney=_sellPriceBoundMoney;	//npc处售出价格	绑定游戏币
			sellPriceNoBoundMoney	=_sellPriceNoBoundMoney;//npc处售出价格	非绑定游戏币
			levelLimits	=_levelLimits;	//等级限制							
			pileUp=_pileUp;//堆叠上限	
			type=_type;//药品类型	
			ointmentType=_ointmentType;
			value=_value;//药品影响角色属性数值
			level = _level;//药品等级
			factor=_factor;
		}
string Ointment::getId(void)
{
	return	id;
}		
string Ointment::getIdentity(void)
{
	return	id;
}													
string Ointment::getName(void)
{
	return name;
}	
int Ointment::getCd(void)
{
	return cd;
}	          			
int Ointment::getSellPriceBoundGold(void)
{
	return sellPriceBoundGold;
}					
int Ointment::getSellPriceNoBoundGold(void)
{
	return sellPriceNoBoundGold;
}	
int Ointment::getSellPriceBoundMoney(void)
{
	return sellPriceBoundMoney;
}	
int Ointment::getSellPriceNoBoundMoney(void)
{
	return sellPriceNoBoundMoney;
}	
int Ointment::getLevelLimits(void)
{
	return levelLimits;
}							
int Ointment::getPileUp(void)
{
	return pileUp;
}	
int Ointment::getType(void)
{
	return type;
}	
int Ointment::getOintmentType(void)
{
	return ointmentType;
}	
int Ointment::getValue(void)
{
	return value;
}	
int Ointment::getLevel(void)
{
	return level;
}

int Ointment::getFactor(void)
{
	return factor;
}