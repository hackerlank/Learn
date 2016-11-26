/************************************************************
	文件名：groupBrush.cpp
	文件作用：实现GroupBrush的属性和函数
	作者：chenzhen
	创建日期：2012.07.06
************************************************************/

#include"groupBrush.h"
#include<math.h>
GroupBrush::GroupBrush(char *_groupId,double _generRatio,\
					  double _eliteRatio,bool _randFlg,int _bossNum,\
					  double _activeRatio,double _passRatio,double _patRatio)
{
	groupId = _groupId;
	generRatio = _generRatio;
	eliteRatio = _eliteRatio;
	randFlg = _randFlg;
	bossNum = _bossNum;
	activeRatio = _activeRatio;
	passRatio = _passRatio;
	patRatio = _patRatio;
}

/*获得批次id*/
char* GroupBrush::getGroupId(void)
{
	return const_cast<char *>(groupId.c_str());
}

/*获得普通怪比例*/
double GroupBrush::getGenerRatio(void)
{
	return generRatio;
}

/*获得精英怪比例*/
double GroupBrush::getEliteRatio(void)
{
	return eliteRatio;
}

/*获得主动怪比例*/
double GroupBrush::getActiveRatio(void)
{
	return activeRatio;
}

/*获得被动怪比例*/
double GroupBrush::getPassRatio(void)
{
	return passRatio;
}

/*获得巡逻怪比例*/
double GroupBrush::getPatRatio(void)
{
	return patRatio;
}

/*获得boss是否随机涮出*/
bool GroupBrush::getRandFlg(void)
{
	return randFlg;
}

/*获得boss随机数量*/
int GroupBrush::getBossNum(void)
{
	return bossNum;
}

/*获得普通怪数量*/
int GroupBrush::getGenerNum(int _sum)
{
	return ceil(_sum * generRatio);
}
	
/*获得精英怪数量*/
int GroupBrush::getEliteNum(int _sum)
{
	return ceil(_sum * eliteRatio);
}
	
/*获得主动怪数量*/
int GroupBrush::getActiveNum(int _sum)
{
	return ceil(_sum * activeRatio);
}
	
/*获得被动怪数量*/
int GroupBrush::getPassNum(int _sum)
{
	return ceil(_sum * passRatio);
}
	
/*获得巡逻怪数量*/
int GroupBrush::getPatNum(int _sum)
{
	return ceil(_sum * patRatio);
}
/*获得批次怪物组合数量*/
MonGroNum GroupBrush::getMonGroNum(int _sum)
{
	int sum;              //怪物总数
	int generNum;        //普通怪数量
	int eliteNum;        //精英怪数量
	int activeNum;       //主动怪数量
	int passNum;         //被动怪数量
	int patNum;          //巡逻怪数量
	int bossNum;         //BOSS数量
	sum = _sum;
	generNum = getGenerNum(_sum);
	eliteNum = getEliteNum(_sum);
	activeNum = getActiveNum(_sum);
	passNum = getPassNum(_sum);
	patNum = getPatNum(_sum);
	bossNum = getBossNum();
	MonGroNum result(sum,generNum,eliteNum,bossNum,activeNum,passNum,patNum);
	return result;
}

/*复制函数*/
GroupBrush* GroupBrush::CopyGroBru(void)
{
	GroupBrush* newGroBru;
	newGroBru = NULL;
	
	newGroBru = new GroupBrush(const_cast<char *>(groupId.c_str()),generRatio,\
							   eliteRatio,randFlg,bossNum,activeRatio,passRatio,patRatio);		
	return newGroBru;	
}

/*析构函数*/
GroupBrush::~GroupBrush(void)
{
	
}


	