/****************************************************************
 * Filename: ectype_reward_info.h
 * 
 * Description: 副本奖励的信息，包括奖励物品和各类型物品奖励率等
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/

 #include"data_structure_struct.h"
#include"command_other_function_all_over.h"
#include<stdlib.h>
#include<stdarg.h>
#include <string>
#include<vector>
#include<map>
#include<iostream>
using namespace std;
#pragma once
//塔防副本经验随波数增加的步长
#define EXP_INC_STEP			5000
//塔防副本金钱随波数增加的步长
#define MONEY_INC_STEP			500
//塔防副本银两随漏怪数减少的步长
#define SILVER_DEC_STEP			100
//塔防副本怪刷完一波怪的基本经验值		added on 6.29
#define TD_BASE_EXP				50000
//塔防副本怪刷完一波的基本金钱奖励值	added on 6.29
#define TD_BASE_MONEY			2000

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

//由一个点数和随机生成三个骰子点数
inline string rand3Num(int sum)
{
	int num1, num2, num3;
	int min, max;
	min = MAX(1, sum - 12);
	max = MIN(sum - 2, 6);
	num1 = (max == min) ? max : rand() % (max - min + 1) + min;
	sum -= num1;
	min = MAX(1, sum - 6);
	max = MIN(sum - 1, 6);
	num2 = (max == min) ? max : rand() % (max - min + 1) + min;
	num3 = sum - num2;
	cout<<"num1: "<<num1<<endl;
	cout<<"num2: "<<num2<<endl;
	cout<<"num3: "<<num3<<endl;
	string msg = intTostring(num1) + intTostring(num2) + intTostring(num3);
	return msg;

}

typedef struct EctypeRewardItem_S
{
	char typeId[51];
	double vipRate[50];
} EctypeRewardItem_T;

class Ectype_Reward_Info
{
	private:
		char ectypeId[51];						//id
		int exp;								//经验奖励
		int money;								//金钱奖励
		int silver;								//银两奖励
		int heroSkillExp;						//人物技能点
		int petSkillExp;						//宠物技能点
		int useGoldRateIndex;					//元宝刷新对应某vip等级的概率
		vector<EctypeRewardItem_T> rewardGoods;	//奖励的物品信息
		//从指定类型物品中随机获取一件物品id
		char* getOneGoods(char* typeId);
	public:
	
		Ectype_Reward_Info(char *_ectypeId, int _heroSkill, int _petSkill, int _exp, int _money, int _silver, int useGold);
		void addOneRewardItem(char *typeId, int num, ...);
		void addOneReward(char *typeId, int num, double* rateList);
		void testData();
		
		int getExp();
		int getMoney();
		int getSilver();
		int getPetSkillExp();
		int getHeroSkillExp();
		int getDefendSilver(int missed);
		
		//也许外部用不着
		int getUseGoldRateIndex();
		
		char* getGoods(int vipClass = 0);
#if 0		
		//得到副本奖励的经验值
		int getExp(ECTYPE_CLASS_T step);
		//得到副本奖励的金钱值
		int getMoney(ECTYPE_CLASS_T step);
		//得到副本奖励的银两值
		int getSilver(ECTYPE_CLASS_T step);
		//得到副本奖励的物品id, flag(0:普通奖励率，1:vip奖励率，2:花元宝奖励率)
		char* getGoods(ECTYPE_CLASS_T step, int flag = 0);
		
		//得到塔防副本第times波怪的经验奖励，只有45级的塔防副本能调用此接口
		int getDefendExp(ECTYPE_CLASS_T step, int times);
		//得到塔防副本第times波怪的金钱奖励，只有45级的塔防副本能调用此接口
		int getDefendMoney(ECTYPE_CLASS_T step, int times);
		//得到塔防副本漏missed只怪的银两奖励，只有45级的塔防副本能调用此接口
		int getDefendSilver(ECTYPE_CLASS_T step, int missed);
#endif		
};
