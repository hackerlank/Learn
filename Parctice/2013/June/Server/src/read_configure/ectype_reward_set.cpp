/****************************************************************
 * Filename: ectype_reward_set.cpp
 * 
 * Description: 某一实例副本的所有玩家奖励集合类。封装了副本奖励与
 *				玩家需要交互的方法
 *
 * Original Author : bison, 2012-6-28
 *
 ****************************************************************/

#include"ectype_reward_set.h"
#include "command_return_define_data.h"
#include "offline_unhandle_event.h"
#include"bag_operator.h"
//向玩家设置经验
#include"my_time.h"
#include "money_operator.h"
#include<cstdlib>
#include<ctime>
using namespace std;
extern char server_name[10];
extern Role *pg_role;
extern char server_name[10];

//副本编号查找副本奖励信息
extern map<string, Ectype_Reward_Info*> idNum_2_rewardInfo;
extern map<string, Hero*> heroId_to_pHero;


EctypeRewardSet *helpNewEctypeReward(char *idNum, vector<string> hero_unit, char *result, int missed)
{
	if (idNum == NULL || result == NULL)
	{
		cout<<"when new EctypeReward idNum is error"<<endl;
		return NULL;
	}
	
	if (hero_unit.size() == 0)
	{
		cout<<"hero set is error when new the EctypeRewardSet"<<endl;
		return NULL;
	}
	
	map<string, Ectype_Reward_Info*>::iterator iterInfo;
	iterInfo = idNum_2_rewardInfo.find(idNum);
	if (iterInfo == idNum_2_rewardInfo.end())
	{
		//没有对应等级的副本奖励信息
		cout<<"Have no ectype reward of this idNum!"<<endl;
		return NULL;
	}
	
	Ectype_Reward_Info *rewardInfo = iterInfo->second;
	
	
	EctypeRewardSet *rewardInst = new EctypeRewardSet(rewardInfo, hero_unit, result, missed);
	return rewardInst;
}

/************************************************************************
 * EctypeRewardSet -- 某一副本内组队玩家奖励信息的构造
 * @idNum: 副本编号
 * @_step: 副本难度等级
 * @missed: 副本漏怪数，只有45级塔防副本用，其他副本传参数-1
 * @hero_unit: 需要获取副本奖励的玩家队伍容器
 ************************************************************************/
EctypeRewardSet::EctypeRewardSet(Ectype_Reward_Info* _rewardInfo, vector<string> hero_unit, char* result, int missed)
{
	rewardInfo = _rewardInfo;
	
	exp = rewardInfo->getExp();
	money = rewardInfo->getMoney();
	if (missed >= 0)
	{
		silver = rewardInfo->getDefendSilver(missed);
	} else {
		silver = rewardInfo->getSilver();
	}
	petSkillExp = rewardInfo->getPetSkillExp();
	heroSkillExp = rewardInfo->getHeroSkillExp();

	/*注意：原来多人组不能弹出奖励面板，是因为此处字符串长度不够*/
	char oneRewardMsg[5000] = {0};
	int i, j;
	int size = hero_unit.size();
	for(i = 0; i < size; i++)
	{
		//得到角色实例
		Hero *hero;
		map<string, Hero*>::iterator iter_hero;
		iter_hero = heroId_to_pHero.find(hero_unit[i]);	
		if(iter_hero == heroId_to_pHero.end())
		{
			cout<<"No hero has this id!"<<endl;
			continue;
		}
		hero = iter_hero->second;
		
		GoodsNow_T newGoodsItem;
		heroId2goodsNow.insert(pair<string, GoodsNow_T>(hero_unit[i], newGoodsItem));
		
		getConstRewardMsg(oneRewardMsg);
		char rewardMsg[5000] = {0};
		if (strlen(result) == 0)
		{
			char directGoodsId[51] = {0};
			int flag = 0;
			if(directGetRewardGoodsId(hero, directGoodsId) == 0)
			{
				flag = 1;
			}				
			sprintf(rewardMsg, "6,14%s,%d,%s", oneRewardMsg,flag,directGoodsId);
		} else {
			sprintf(rewardMsg, "6,%d%s%s", INST_REWARD_CONST_RETURN, oneRewardMsg, result);
		}
		send_msg(hero->getFd(), rewardMsg);
		cout<<"rewardMsg:"<<rewardMsg<<endl;
	}
}

/************************************************************************
 * getConstRewardMsg -- 得到副本固定奖励信息，包括经验，金钱，银两
 * Return: 返回格式为："经验值，金钱值，银两值"的字符串
 ************************************************************************/
void EctypeRewardSet::getConstRewardMsg(char* result)
{
	if (result == NULL)
	{
		return;
	}
	// sprintf(result, ",%d,%d,%d", exp, money,petSkillExp);
	sprintf(result, ",%d,%d,%d,%d,%d", exp, money, silver, heroSkillExp, petSkillExp);
	
}

int EctypeRewardSet::getGoodsRewardMsg(char* heroId, char* result)
{	
	// string rewardMsg;
	if (heroId == NULL || result == NULL)
	{
		// 参数有误
		return 1;
	}
	Hero *hero;
	map<string, Hero*>::iterator iter;
	iter = heroId_to_pHero.find(heroId);	
	if(iter == heroId_to_pHero.end())
	{
		//角色ID错误
		return 2;
	}
	hero = iter->second;
	
	//如果副本奖励已领取过，就不能再领取了,虽然不能领了，还让他们可以花钱继续刷，策划要这么坑
	// if (hero->dayLmtFindGroup.isOneItemFull("ectypeReward") == 1)
	// {
		// return rewardMsg;
	// }
	int nextTimeNeedMoney = 0;
	GoodsNow_T *goodsNow;
	map<string, GoodsNow_T>::iterator iter_goodsNow;
	iter_goodsNow = heroId2goodsNow.find(heroId);
	if (iter_goodsNow == heroId2goodsNow.end())
	{
		//副本奖励没有该玩家信息
		return 3;
	}
	
	goodsNow = &(iter_goodsNow->second);
	//第一次抽取免费
	int rateFlag = 0;
	if (goodsNow->times == 0)
	{
		//goodsNow->freeTimes = 1;
		//非会员第二次抽取收10元宝
		nextTimeNeedMoney = 10;
		if (hero->memHero->vipDailyData.stage!=0)
		{
			//会员的免费抽取概率不同
			rateFlag = 1;
		}
	} else {
		if(!useGold(hero, 5 * (goodsNow->times + 1)))
		{
			//元宝不足
			return 5;
		}
		nextTimeNeedMoney = 5 * (goodsNow->times + 2);
		rateFlag = 2;
		
		//记录日志2013.4.28
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,5,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),pg_role->getUserName(),5 * (goodsNow->times + 1));
		write_log(account_msg);	
	}
	
	goodsNow->times++;
	//srand(MY_TV_USEC + MY_TV_SEC); //随机种子点
	char*  pGoods = NULL;
	int vipClass = hero->getVipStage();
	
	if (rateFlag == 2)
	{
		pGoods = rewardInfo->getGoods(-1);
	} else {
		pGoods = rewardInfo->getGoods(vipClass);
	}
	if(!pGoods)
	{
		//副本奖励配置出错
		cout<<"The ectype reward config is not correct, please check it!!!"<<endl;
		return 6;
	}
	
	char*  pExtraGoods = NULL;
	if (hero->getVipCpyFreshNum() == 2)
	{
		if (rateFlag == 2)
		{
			pExtraGoods = rewardInfo->getGoods(-1);
		} else {
			pExtraGoods = rewardInfo->getGoods(vipClass);
		}
	}
	
	strncpy(goodsNow->goodsId, pGoods, sizeof(goodsNow->goodsId)-1); //update by benliao to ensure good copy 2012.11.26
	if (pExtraGoods)
	{
		strncpy(goodsNow->extraGoodsId, pExtraGoods, sizeof goodsNow->extraGoodsId);
	}
	
	/*多人组队通关不弹奖励面板，是字符串太短了*/
	char groupMsg[1024];
	map<string, GoodsNow_T>::iterator iter_membs;
	iter_membs = heroId2goodsNow.begin();
	for (iter_membs; iter_membs != heroId2goodsNow.end(); iter_membs++)
	{
		string teamHeroId = iter_membs->first;
		if (teamHeroId == heroId)
		{
			continue;
		}
		Hero *teamHero;
		map<string, Hero*>::iterator iter_hero;
		iter_hero = heroId_to_pHero.find(teamHeroId);	
		if(iter_hero == heroId_to_pHero.end())
		{
			cout<<"No teamHero has this id!"<<endl;
			continue;
		}
		
		teamHero = iter_hero->second;
		if (pExtraGoods)
		{
			sprintf(groupMsg, "6,%d,%s,%s,%d,%s,%d,%s", INST_GROUP_REWARD_GOODS, hero->getIdentity(), hero->getNickName(),
				getGoodsType(goodsNow->goodsId), goodsNow->goodsId, getGoodsType(goodsNow->extraGoodsId), goodsNow->extraGoodsId);
		} else {
			sprintf(groupMsg, "6,%d,%s,%s,%d,%s", INST_GROUP_REWARD_GOODS, hero->getIdentity(), hero->getNickName(),
				getGoodsType(goodsNow->goodsId), goodsNow->goodsId);
		}
		send_msg(teamHero->getFd(), groupMsg);
	}
	
	if (pExtraGoods)
	{
		sprintf(result, ",%d,%s,%d,%d,%s", getGoodsType(goodsNow->goodsId), goodsNow->goodsId, nextTimeNeedMoney, getGoodsType(goodsNow->extraGoodsId), goodsNow->extraGoodsId);
	} else {
		sprintf(result, ",%d,%s,%d", getGoodsType(goodsNow->goodsId), goodsNow->goodsId, nextTimeNeedMoney);
	}
	
	return 0;
	
	
}

int EctypeRewardSet::directGetRewardGoodsId(Hero *hero, char* goodsId)
{
	GoodsNow_T *goodsNow;
	map<string, GoodsNow_T>::iterator iter_goodsNow;
	iter_goodsNow = heroId2goodsNow.find(hero->getIdentity());
	if (iter_goodsNow == heroId2goodsNow.end())
	{
		//副本奖励没有该玩家信息
		return 1;
	}
	
	goodsNow = &(iter_goodsNow->second);
	goodsNow->times++;
	//srand(MY_TV_USEC + MY_TV_SEC); //随机种子点
	char*  pGoods = NULL;
	
	pGoods = rewardInfo->getGoods(hero->getVipStage());
	
	if(!pGoods)
	{
		//副本奖励配置出错
		cout<<"The ectype reward config is not correct, please check it!!!"<<endl;
		return 2;
	}
	strncpy(goodsNow->goodsId, pGoods, sizeof goodsNow->goodsId);
	strncpy(goodsId, pGoods, strlen(pGoods));
	return 0;
}


/************************************************************************
 * setRewardToHero -- 将指定玩家的副本奖励信息设置给指定玩家
 * @heroId: 角色ID
 * @mustGiveFlag: 强制给奖励，如果副本回收时玩家还没领取奖励就要强制给
 * Return: false:设置失败，true：设置成功
 ************************************************************************/
int EctypeRewardSet::setRewardToHero(char* heroId, int mustGiveFlag)
{
	if (heroId == NULL)
	{	
		return 1;
	}
	
	GoodsNow_T *goodsNow;
	map<string, GoodsNow_T>::iterator iter_goodsNow;
	iter_goodsNow = heroId2goodsNow.find(heroId);
	if (iter_goodsNow == heroId2goodsNow.end())
	{
		//奖励已领取或者副本没通关不能获得奖励
		cout<<"The hero now doesn't have ectype reward!"<<endl;
		return 2;
	}
	
	goodsNow = &iter_goodsNow->second;
	if (goodsNow->times > 0 && strlen(goodsNow->goodsId) == 0)
	{
		//玩家奖励已经领取（策划说不抽奖不能领取，所以已经领取过，times一定大于0）
		cout<<"The hero has received the ectype reward he deserved"<<endl;
		return 3;
	}
	
	Hero *hero;
	map<string, Hero*>::iterator iter;
	iter = heroId_to_pHero.find(heroId);	
	if(iter == heroId_to_pHero.end())
	{
#if 0
		//玩家不在线，先用邮件存做未处理，等到上线的时候再处理
		UnhandleAttr_T moneyData(UNHANDLE_BOUND_GAME_MONEY, money);
		UnhandleAttr_T silverData(UNHANDLE_GAME_MONEY, silver);
		UnhandleAttr_T expData(UNHANDLE_HERO_EXP, exp);
		
		UNHANDLE_FUNC(heroId, 5, moneyData);
		UNHANDLE_FUNC(heroId, 5, silverData);
		UNHANDLE_FUNC(heroId, 5, expData);
		//策划定的玩家不在线，副本奖励有物品也不给他们了
		return false;
#endif
		return 4;
	}
	hero = iter->second;
	
	if (goodsNow->times == 0)
	{
		if (mustGiveFlag == 0)
		{
			//非强制领取模式下，玩家还没投掷骰子
			cout<<"The hero haven't selected reward goods!"<<endl;
			return 5;
		}
	} else {
		//先设置物品，
		Bag *bag = hero->getBag();
		char* goodsId = goodsNow->goodsId;
		if (strlen(goodsNow->extraGoodsId) != 0)
		{
			Bag* bag = hero->getBag();
			if (bag == NULL)
			{
				return 7;
			}
			else if (bag->remainGridNum() < 2)
			{
				return 6;
			}
		}
		
		int setBagReturn = saveGoodsInBag(hero, goodsId, 1, 1);
		if (setBagReturn != 1)
		{
			if (mustGiveFlag == 0)
			{
				//不是强制领取模式的话就等玩家整理好包裹再领取
				return 6;
			}
			//强制奖励模式时，玩家背包满了就不给物品了
		}
		saveGoodsInBag(hero, goodsNow->extraGoodsId, 1, 1);
	}
	
	memset(goodsNow->goodsId, 0, sizeof(goodsNow->goodsId));
	memset(goodsNow->extraGoodsId, 0, sizeof goodsNow->extraGoodsId);
	hero->setExpNow(exp);
	increaseBoundGameMoney(hero,money);
	increaseGameMoney(hero,silver);
	hero->addHeroSkillExp(heroSkillExp);
	hero->addPetSkillExp(petSkillExp);
	heroId2goodsNow.erase(heroId);
	return 0;
}


//判断是否全部玩家都领取了副本奖励
bool EctypeRewardSet::isAllReward(void)
{
	// if (heroId2goodsSetMsg.size() == 0)
	// {
	GoodsNow_T *goodsNow;
	map<string, GoodsNow_T>::iterator iter_goodsNow;
	iter_goodsNow = heroId2goodsNow.begin();
	for(iter_goodsNow; iter_goodsNow != heroId2goodsNow.end(); iter_goodsNow++)
	{
		goodsNow = &iter_goodsNow->second;
		if (goodsNow->times != 0 && strlen(goodsNow->goodsId) == 0)
		{
			continue;
		}
		else 
		{
			return false;
		}
	}
	
	return true;
}
