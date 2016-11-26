#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"
#include "campWarManagement.h"
#include "guild_war_asist.h"
#include "rob_flag_war_logic.h"

extern GuildWarAsist *guildWarManage;			//帮派战管理
extern map<string,TakeGoods*> takeGoodsMap;
extern campWarManagement campWarController;//阵营战管理实例；
void collect_cb(struct event_base* loop, ev_timer *think, int revents);
void deal_collect_success(Hero* hero, char* collectId);
int deal_collect_fail(Hero* hero, char* collectId, int reason);
//开始采集定时器
int Hero::startCollectTimer(int collectTime, char* collectId)
{
	heroState = 7;
	ext_ev_timer_init(&collectTimer, collect_cb, collectTime, 0, this, collectId);
	ev_timer_start(loops, &collectTimer);
	return 0;
}

bool Hero::isInCollecting()
{
	return ev_timer_is_running(loops, &collectTimer);
}

//reason=1：移动打断；reason=2:攻击打断；reason=3:被攻击打断；reason=4:打坐打断；reason=5:摆摊打断; reason=6:下线掉线打断; reason=7:死亡打断（因为有采集不被攻击打断）
int Hero::stopCollectTimer(int reason)
{
	char msg[64] = {0};
	if (ev_timer_is_running(loops, &collectTimer))
	{	
		int ret = deal_collect_fail(this, collectTimer.targetId, reason);
		if (ret != 0)
		{
			cout<<"Can't stop this kind of collectTimer"<<endl;
			return 1;
		}
		ev_timer_stop(loops, &collectTimer);
		
		sprintf(msg, "28,1,0,%d", reason);
		send_msg(getFd(), msg);
		heroState = 0;
	}
	return 0;
}

void collect_cb(struct event_base* loop, ev_timer *think, int revents)
{
	char msg[64] = {0};
	Hero* hero = (Hero*)think->target;
	char *collectId = think->targetId;
	cout<<"herehereherehere"<<endl;
	hero->setHeroState(0);
	deal_collect_success(hero, collectId);

	sprintf(msg, "28,1,1");
	send_msg(hero->getFd(), msg);
}

void deal_collect_success(Hero* hero, char* collectId)
{
	Map_Inform* heroMap = hero->getMap();
	//实例ID找到实例指针
	TakeGoods *take = heroMap->getTakeObj(collectId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return;
	}
	
	take->clearOwner(hero->getIdentity());
	
	int type = take->getTaskStyle();
	int brandType = take->getBrandType();
	//获得物品ID
	char *goodsId = take->getGoodsId();
	//任务采集类型
	if (type == 1)
	{
		//hero下接的有收集道具的任务
		if (strlen(goodsId) != 16)
		{
			//物品ID不是任务道具
			return;
		}

		if (brandType == 0)
		{
			//采集物品，采集成功将物品放到背包中
			if (saveGoodsInBag(hero, goodsId, 1))
			{
				heroMap->disperTakeGood(collectId);
				//更新任务数据，类型为采集
				hero->updateHeroTaskStatus(PICKUP_TASK_NEED_TYPE, goodsId);
			} else {
				//物品存入包裹不成功
				return;
			}
		} else if (brandType == 1)
		{
			//采集后不会得到物品类型，如救死扶伤任务
			heroMap->disperTakeGood(collectId);
			//更新任务数据，类型为采集
			hero->updateHeroTaskStatus(RESCUE_TASK_NEED_TYPE, goodsId);
		} else if (brandType == 2)
		{
			//如果是藏宝图任务，打开宝箱要随机一个物品出来
			if (useRandomGoods(hero, goodsId, -1))
			{
				heroMap->disperTakeGood(collectId);
				//更新任务数据，类型为采集
				hero->updateHeroTaskStatus(TREASURE_MAP_TASK_NEED_TYPE, goodsId);
			}
		}
		else if (brandType == 3)
		{
			heroMap->disperTakeGood(collectId);
			//更新任务数据，类型为采集
			hero->updateHeroTaskStatus(RESCUE_TASK_NEED_TYPE, goodsId);
			heroMap->brushTaskMon(hero, take->getTypeId(), 4);
		}
		return;
		
	}
	else if (type == 2)
	{
		if (hero->getGuild()!=NULL)
		{
			hero->getGuild()->eatGuildFeast(hero,collectId);
		}
		else 
		{
			msg_error(g_out_buf,102);
			send_msg(hero->getFd(),g_out_buf);
		}
	}
	else if (type == 4)
	{
		if (useBagGoods(hero,"b_cl_132_100",1)==0||useBagGoods(hero,"f_cl_132_100",1)==0)
		{		
			cout<<"useGoods success"<<endl;
			heroMap->disperTakeGood(collectId);
			int spe=take->getBrandType();			//取子类型
			spe=spe-2;
			cout<<"spe:"<<spe<<endl;
			char petAgg[20]={0};
			int number=random_number(0,9);
			cout<<"random number:"<<number<<endl;
			if (number<2)
			{
				snprintf(petAgg,sizeof(petAgg),"f_dj_106_1%d%d",1,spe);
				cout<<"petAgg:"<<petAgg<<endl;
			}
			else
			{
				snprintf(petAgg,sizeof(petAgg),"f_dj_106_1%d%d",2,spe);
				cout<<"petAgg:"<<petAgg<<endl;
			}
			hero->updateHeroTaskStatus(PICKUP_TASK_NEED_TYPE, "pet");
			saveGoodsInBag(hero,petAgg,1);
			
			cout<<"saveGoodsInBag Finish"<<endl;
		}	
	}
	else if (type == 5)
	{
		campWarController.campResWarCollect(hero);
		heroMap->disperTakeGood(collectId);
	} else if (type == 3)
	{
		// guildWarManage->finishPickFlag(hero, brandType);
		// take->changeName(hero->getNickName(), hero->getGuildName());
		int ret = robFlagWarManage->finishPick(hero, brandType);
		if (ret == 0)
		{
			heroMap->disperTakeGood(collectId);
		}
	}
}

int deal_collect_fail(Hero* hero, char* collectId, int reason)
{
	Map_Inform* heroMap = hero->getMap();
	//实例ID找到实例指针
	TakeGoods *take = heroMap->getTakeObj(collectId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return 0;
	}
	
	if (reason == 3 && !take->IsInterrupt())
	{
		return 2;
	}
	
	int type = take->getTaskStyle();
	if (type == 3)
	{
		if (reason == 3)
		{
			return 1;
		}
		
		int brandType = take->getBrandType();
		robFlagWarManage->stopPicking(hero);
	}
	take->clearOwner(hero->getIdentity());
	return 0;
}