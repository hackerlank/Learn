/****************************************************************
 * Filename: meridian.cpp
 * 
 * Description: 经脉系统
 *
 * Original Author : bison, 2012-7-13
 *
 ****************************************************************/

#include"meridian.h"
#include<map>
using namespace std;

//经脉属性默认构造
Meridian::Meridian()
{
	level = 0;
	now = YANGQ;
	meridTimer = new ev_timer;
	timerBusy = false;
}

//经脉的指定构造
Meridian::Meridian(MERID_TYPE_T _now, int _level)
{
	now = _now;
	level = _level;
	meridTimer = new ev_timer;
	timerBusy = false;
}

//使用从memcache上来的数据对经脉进行恢复
Meridian::Meridian(MeridData_T meridData)
{
	now = (MERID_TYPE_T)meridData.now;
	level = meridData.level;
	meridTimer = new ev_timer;
	timerBusy = meridData.timerBusy;
}

//经脉的升级
bool Meridian::upgrade()
{
	//经脉正常升级最多升到60级
	if (level >= MAX_MERIDIAN_LEVEL && now == YANGQ)
	{
		return false;
	}
	
	//跳到下一经脉点
	now = (MERID_TYPE_T)((now + 1) % 8);
	
	//如果一个轮回后，新等级加1
	if (now == RENM)
	{
		level++;
	}
	
	return true;
}

//经脉强化
bool Meridian::strengthen()
{
	//经脉强化最多强化30级
	if (level < MAX_MERIDIAN_LEVEL || level >= MAX_MERIDIAN_LEVEL + 30)
	{
		return false;
	}
	
	if (now == RENM)
	{
		level++;
	}
	
	now = (MERID_TYPE_T)((now + 1) % 8);
	return true;
}

MERID_TYPE_T Meridian::getNow()
{
	return now;
}

//八种经脉总等级 (now + 1) * level + (7 - now) * (level - 1);
int Meridian::getLevel()
{
	return level;
}

ev_timer* Meridian::getTimer()
{
	return meridTimer;
}

Meridian::~Meridian()
{
	delete meridTimer;
}

bool Meridian::getTimerBusy()
{
	return timerBusy;
}

void Meridian::setTimerBusy(bool busy)
{
	timerBusy = busy;
}


//获取经脉所加属性总值
int Meridian::getIncTotalVal(int &val1, int &val2, int node)
{
	if (node <= now)
	{
		val1 = heroMeridConf.item[node].incTotalVal1[level];
		val2 = heroMeridConf.item[node].incTotalVal2[level];
	} else {
		val1 = heroMeridConf.item[node].incTotalVal1[level - 1];
		val2 = heroMeridConf.item[node].incTotalVal2[level - 1];
	}
	return 0;
}