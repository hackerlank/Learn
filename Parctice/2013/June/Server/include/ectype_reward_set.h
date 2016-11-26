/****************************************************************
 * Filename: ectype_reward_set.h
 * 
 * Description: 某一实例副本的所有玩家奖励集合类。封装了副本奖励与
 *				玩家需要交互的方法
 *
 * Original Author : bison, 2012-6-28
 *
 ****************************************************************/
 
#ifndef _ECTYPE_REWARD_SET_H_
#define _ECTYPE_REWARD_SET_H_

#include "ectype_reward_info.h"
#include "hero.h"
#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;

typedef struct GoodsNode_S
{
	char goodsId[51];	//奖励物品ID
	bool flag;			//对应节点是否已选择
}GoodsNode_T;

//当前次数抽得的物品 bison added 7.6
typedef struct GoodsNow_S
{
	int times;		//掷骰子的次数
	//int freeTimes;	//免费次数,非会员可以免费一次，会员可以免费更多
	char goodsId[51];	//该次投掷得到的物品
	char extraGoodsId[51];
	GoodsNow_S()
	{
		times = 0;
		memset(goodsId, 0, sizeof(goodsId));
		memset(extraGoodsId, 0, sizeof extraGoodsId);
		//freeTimes = 0;
	}
}GoodsNow_T;

//某一实例副本奖励集合
class EctypeRewardSet
{
	private:
	//副本的固定奖励 公用的
	Ectype_Reward_Info *rewardInfo;
	int exp;
	int money;
	int silver;
	int petSkillExp;
	int heroSkillExp;
	map<string, GoodsNow_T> heroId2goodsNow;				//角色id查找英雄当前获得的物品

	public:
	EctypeRewardSet(){};
	//副本奖励信息构造，在玩家副本通关后进行实例构造
	EctypeRewardSet(Ectype_Reward_Info* _rewardInfo, vector<string> hero_unit, char* result, int missed);
	
	//得到副本的固定奖励信息
	void getConstRewardMsg(char* result);
	
	int getGoodsRewardMsg(char* heroId, char *result);
	
	int directGetRewardGoodsId(Hero *hero, char* goodsId);
	//把玩家得到的副本奖励加给玩家
	int setRewardToHero(char* heroId, int mustGiveFlag = 0);
	
	//判断是否全部玩家都领取了副本奖励
	bool isAllReward(void);
};
EctypeRewardSet *helpNewEctypeReward(char *idNum, vector<string> hero_unit, char *result, int missed = -1);
#endif
