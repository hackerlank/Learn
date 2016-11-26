/****************************************************************
 * Filename: transcrip_reward_info.h
 * 
 * Description: 副本奖励的信息，包括奖励物品和各类型物品奖励率等
 *
 * Original Author : bison, 2012-6-11
 *
 ****************************************************************/
 
#pragma once
#include <string>
#include<vector>
#include<iostream>
using namespace std;

//副本难度层级类型
typedef struct ectypeClass_S 
{
	int level;					//副本难度层级
	int exp;					//奖励经验
	int money;					//奖励金钱
	double wEqpRate;			//白色装备的中奖率
	double bEqpRate;			//蓝色装备的中奖率
	double pEqpRate;			//紫色装备的中奖率
	double yEqpRate;			//黄色装备的中奖率
	double oEqpRate;			//橙色装备的中奖率
	double petEggRate;			//宠物蛋的中奖率
	double otherRate;			//其他物品中奖率
	double reserveRate;			//预留
	//副本难度层级的构造
	ectypeClass_S(int _level, int _exp, int _money, double _white, double _blue, double _purple,
		double _yellow, double _orange, double _pet, double _other, double _reserve)
	{
		level = _level;
		exp = _exp;
		money = _money;
		wEqpRate = _white;
		bEqpRate = _blue;
		pEqpRate = _purple;
		yEqpRate = _yellow;
		oEqpRate = _orange;
		petEggRate = _pet;
		otherRate = _other;
		reserveRate = _reserve;
	}
	//空构造
	ectypeClass_S(){};
}ectypeClas_T;

//奖励物品的类型
typedef enum{WHITE,BLUE,PURPLE,YELLOW,ORANGE,PETEGG,OTHER,RESERVE}GOODS_TYPE_T;

//副本的难度值
typedef enum{NORMAL_LEVEL = 1, MIDDLE_LEVEL, HARD_LEVEL} ECTYPE_LEVLE_T;

class Transcrip_Reward_Info
{
private:
	int EntLevel;				//进入副本等级要求
	//奖励物品范围
	vector<string> wEqps;		//白色装备列表
	vector<string> bEqps;		//蓝色装备列表
	vector<string> pEqps;		//紫色装备列表
	vector<string> yEqps;		//黄色装备列表
	vector<string> oEqps;		//橙色装备列表
	
	vector<string> petEggs;		//宠物蛋id列表
	vector<string> others;		//其他奖励物品id列表
	vector<string> reserve;		//预留
	
	ectypeClas_T Normal;		//简单难度
	ectypeClas_T Middle;		//中等难度
	ectypeClas_T Hard;			//困难难度
	
	//从type指定的物品类型对应的物品列表中随即分配一个物品
	string getOneGoods(GOODS_TYPE_T type);

public:
	Transcrip_Reward_Info(int _EntLevel, vector<string> _wEqps, vector<string> _bEqps,
		vector<string> _pEqps, vector<string> _yEqps, vector<string> _oEqps,
		vector<string> _petEggs, vector<string> _others, vector<string> _reserve,
		ectypeClas_T _Normal, ectypeClas_T _Middle, ectypeClas_T _Hard);
	
	//得到副本奖励经验
	int getExp(ECTYPE_LEVLE_T level);
	//得到副本奖励金钱
	int getMoney(ECTYPE_LEVLE_T level);
	//得到副本奖励物品id
	string getGoods(ECTYPE_LEVLE_T level);

	~Transcrip_Reward_Info(void);
};


