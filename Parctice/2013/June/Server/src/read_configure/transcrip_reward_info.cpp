/****************************************************************
 * Filename: transcrip_reward_info.cpp
 * 
 * Description: 副本奖励的信息的构造函数和奖励信息获取方法的定义
 *
 * Original Author : bison, 2012-6-11
 *
 ****************************************************************/
 
#include "transcrip_reward_info.h"
#include<cstdlib>
#include<ctime>
using namespace std;

/************************************************************************/
/* Transcrip_Reward_Info -- 副本奖励信息构造函数
/* @_EntLevel: 副本等级
/* @_wEqps: 可能奖励的白色装备id列表
/* @_bEqps: 可能奖励的蓝色装备id列表
/* @_pEqps: 可能奖励的紫色装备id列表
/* @_yEqps: 可能奖励的黄色装备id列表
/* @_oEqps: 可能奖励的橙色装备id列表
/* @_petEggs: 可能奖励的宠物蛋id列表
/* @_others: 可能奖励的其他物品id列表
/* @_reserve: 预留可能奖励物品id列表
/* @_Normal: 普通副本奖励值信息
/* @_Middle: 中等难度副本奖励值信息
/* @_Hard:	困难副本奖励值信息0
/************************************************************************/
Transcrip_Reward_Info::Transcrip_Reward_Info(int _EntLevel, vector<string> _wEqps,
	vector<string> _bEqps,vector<string> _pEqps, vector<string> _yEqps, vector<string> _oEqps,
	vector<string> _petEggs, vector<string> _others, vector<string> _reserve,
	ectypeClas_T _Normal, ectypeClas_T _Middle, ectypeClas_T _Hard)
{
	EntLevel = _EntLevel;
	wEqps = _wEqps;
	bEqps = _bEqps;
	pEqps = _pEqps;
	yEqps = _yEqps;
	oEqps = _oEqps;
	petEggs = _petEggs;
	others = _others;
	reserve = _reserve;
	Normal = _Normal;
	Middle = _Middle;
	Hard = _Hard;
}

/************************************************************************/
/* getExp -- 根据副本难度获得副本奖励经验
/* @level: 副本难度等级
/* @return: 返回副本奖励经验值
/************************************************************************/
int Transcrip_Reward_Info::getExp(ECTYPE_LEVLE_T level)
{
	int rewardExp = 0;
	switch (level)
	{
	case NORMAL_LEVEL:
		rewardExp = Normal.exp;
		break;
	case MIDDLE_LEVEL:
		rewardExp = Middle.exp;
		break;
	case HARD_LEVEL:
		rewardExp = Hard.exp;
		break;
	default:
		rewardExp = 0;
		break;
	}
	return rewardExp;
}

/************************************************************************/
/* getMoney -- 根据副本难度获得副本奖励金钱
/* @level: 副本难度等级
/* @return: 返回副本奖励金钱值
/************************************************************************/
int Transcrip_Reward_Info::getMoney(ECTYPE_LEVLE_T level)
{
	int rewardMoney = 0;
	switch (level)
	{
	case NORMAL_LEVEL:
		rewardMoney = Normal.money;
		break;
	case MIDDLE_LEVEL:
		rewardMoney = Middle.money;
		break;
	case HARD_LEVEL:
		rewardMoney = Hard.money;
		break;
	default:
		rewardMoney = 0;
		break;
	}
	return rewardMoney;
}

/************************************************************************/
/* getGoods -- 根据副本难度获得副本奖励物品id
/* @level: 副本难度等级
/* @return: 返回副本奖励物品id
/************************************************************************/
string Transcrip_Reward_Info::getGoods(ECTYPE_LEVLE_T level)
{
	string goodsId;
	unsigned temp = 0;          //概率累加值
	ectypeClas_T classTemp;		//副本难度层级

	switch (level)
	{
	case NORMAL_LEVEL:
		classTemp = Normal;
		break;
	case MIDDLE_LEVEL:
		classTemp = Middle;
		break;
	case HARD_LEVEL:
		classTemp = Hard;
		break;
	default:
		//DEBUGMSG();
		return goodsId;
	}

	double wEqpRate = classTemp.wEqpRate;			//白色装备的中奖率
	double bEqpRate = classTemp.bEqpRate;			//蓝色装备的中奖率
	double pEqpRate = classTemp.pEqpRate;			//紫色装备的中奖率
	double yEqpRate = classTemp.yEqpRate;			//黄色装备的中奖率
	double oEqpRate = classTemp.oEqpRate;			//橙色装备的中奖率
	double petEggRate = classTemp.petEggRate;		//宠物蛋的中奖率
	double otherRate = classTemp.otherRate;			//其他物品中奖率
	double reserveRate = classTemp.reserveRate;		//预留

	//srand((unsigned)time(NULL));
	unsigned rand_value = rand() % 10000;

	if (rand_value < (temp += (unsigned)(wEqpRate * 100)))
	{
		goodsId = getOneGoods(WHITE);

	} else if (rand_value < (temp += (unsigned)(bEqpRate * 100))) {
		goodsId = getOneGoods(BLUE);

	} else if (rand_value < (temp += (unsigned)(pEqpRate * 100))) {
		goodsId = getOneGoods(PURPLE);

	} else if (rand_value < (temp += (unsigned)(yEqpRate * 100))) {
		goodsId = getOneGoods(YELLOW);

	} else if (rand_value < (temp += (unsigned)(oEqpRate * 100))) {
		goodsId = getOneGoods(ORANGE);

	} else if (rand_value < (temp += (unsigned)(petEggRate * 100))) {
		goodsId = getOneGoods(PETEGG);

	} else if (rand_value < (temp += (unsigned)(otherRate * 100))) {
		goodsId = getOneGoods(OTHER);

	} else if (rand_value < (temp += (unsigned)(reserveRate * 100))) {
		goodsId = getOneGoods(RESERVE);
	}

	return goodsId;
}

/************************************************************************/
/* getOneGoods -- 从指定类型的物品id序列中随机得到一个
/* @type: 奖励物品的指定类型
/* @return: 随机奖励物品的id
/************************************************************************/
string Transcrip_Reward_Info::getOneGoods(GOODS_TYPE_T type)
{
	string GoodsId;					//返回的物品id
	vector<string> idsTemp;			//奖励物品的某一序列
	int size = 0;					//对应的某一奖励物品序列的总数

	switch (type)
	{
	case WHITE:
		idsTemp = wEqps;            //物品奖励序列取白色装备
		break;
	case BLUE:
		idsTemp = bEqps;			//物品奖励序列取蓝色装备
		break;
	case PURPLE:
		idsTemp = pEqps;			//物品奖励序列取紫色装备
		break;
	case YELLOW:
		idsTemp = yEqps;			//物品奖励序列取黄色装备
		break;
	case ORANGE:
		idsTemp = oEqps;			//物品奖励序列取橙色装备
		break;
	case PETEGG:
		idsTemp = petEggs;          //物品奖励序列取宠物蛋集
		break;
	case OTHER:
		idsTemp = others;           //物品奖励序列取其他物品
		break;
	case RESERVE:
		idsTemp = reserve;			//预留
		break;
	default:
		return GoodsId;				//传物品类型参数有误
	}

	size = idsTemp.size();
	//srand((unsigned)time(NULL));
	unsigned rand_value = rand() % size;		//随机产生一个不大于物品容器容量的正整数

	GoodsId = idsTemp[rand_value];
	return GoodsId;
}
Transcrip_Reward_Info::~Transcrip_Reward_Info(void)
{
}
