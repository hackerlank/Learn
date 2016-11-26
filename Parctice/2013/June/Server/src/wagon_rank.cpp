#include"wagon.h"
#include"my_time.h"
#include"hero.h"
#include"guild.h"
#include"wagon_comm.h"
#include"hero_fight.h"

extern map<string, string> heroId_2_colorWagon;			    //玩家有彩色马车
extern map<string, wagonColorRank_T*> wagonId_2_rankRate;	//每种马车颜色刷新率
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Wagon*> wagonConfMap;				//马车配置文件
extern map<string,Wagon*> wagonInstMap;			//所有马车实例，还原马车任务使用

#include "wholeDefine.h"
#include "money_operator.h"
extern int g_msg_len;
extern Hero *pg_hero;
extern char server_name[10];
char firstWagonId[51] = "mc_pt_001";
char bestWagonId[51] = "mc_pt_005";
char wagonTaskId[51] = "task00295";

void viewWagonInfo(char *buffer);

static void send_guild_wagon_error_msg(int head, int ret)
{
	char msg[64] = {0};
	sprintf(msg, "5,21,%d,%d", head, ret);
	send_msg(pg_hero->getFd(), msg);
}
int rankWagonWithGold(Hero *hero, char *newWagonId)
{
	char* oldWagonId = firstWagonId;
	char* heroId = hero->getIdentity();
	map<string, string>::iterator it;
	it = heroId_2_colorWagon.find(heroId);
	
	if (it != heroId_2_colorWagon.end())
	{
		oldWagonId = const_cast<char*>(it->second.c_str());
	}
	
	wagonColorRank_T *rankItem;
	map<string, wagonColorRank_T*>::iterator iter;
	iter = wagonId_2_rankRate.find(oldWagonId);
	
	if (iter == wagonId_2_rankRate.end())
	{
		//正常不会出现这种情况
		heroId_2_colorWagon.erase(heroId);
		cout<<"Somewhere give a wrong wagonId , please check the wagonId in cpp with xml!"<<endl;
		return -1;
	}
	
	if (!strcmp(oldWagonId, bestWagonId))
	{
		//已经是最高级的马车，不用再刷新
		cout<<"The hero already has the best wagon, he does not need to refresh the color again!"<<endl;
		return -2;
	}
	
	if (!useGold(hero,10))
	{
		cout<<"the hero does have enough money to refresh the wagonColor!"<<endl;
		return -3;
	}
	
	rankItem = iter->second;
	//srand(MY_TV_SEC + MY_TV_USEC);
	int rankNum = rand() % 100;
	if (rankNum < rankItem->upRate)
	{
		strncpy(newWagonId, rankItem->betterWagonId, sizeof(rankItem->betterWagonId));
	}else if (rankNum < rankItem->upRate + rankItem->downRate)
	{
		strncpy(newWagonId, rankItem->worseWagonId, sizeof(rankItem->worseWagonId));
	} else {
		strncpy(newWagonId, oldWagonId, strlen(oldWagonId));
	}
	
	heroId_2_colorWagon.erase(heroId);
	heroId_2_colorWagon.insert(pair<string, string>(heroId, newWagonId));
	
	//记录日志2013.4.28
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),pg_role->getUserName(),10);
	write_log(account_msg);	
	
	return 0;
}

//刷新马车通信
void refreshWagonComm(char *buffer)
{
	Hero *hero = pg_hero;
	
	Point heroPt = pg_hero->getLocation();
	Point npcPt(5839,2667);
	char newWagonId[51] = {0};
	char msg[32] = {0};
	if (strlen(hero->memHero->wagonId) != 0)
	{
		//正在拉马车中，不能刷新
		send_guild_wagon_error_msg(2, 1);
		return;
	}
	if (GET_DISTANCE(heroPt, npcPt) > 400)
	{
		cout<<"distance is too far when the hero want to get wagon"<<endl;
		send_guild_wagon_error_msg(2, 2);
		return;
	}
	
	int ret = rankWagonWithGold(hero, newWagonId);

	if (ret == 0)
	{
		viewWagonInfo(NULL);
	} else {
		send_guild_wagon_error_msg(2, ret);
		return;
	}
}

void viewWagonInfo(char *buffer)
{
	char *nowWagonId = NULL;
	int guildLevel = 0, index = 0;
	nowWagonId = pg_hero->memHero->wagonId;
	char msg[400] = {0};
	if (nowWagonId == NULL || strlen(nowWagonId) != 0)
	{
		cout<<"The pg_hero is driving wagon, he can't view more wagon info!"<<endl;
		send_guild_wagon_error_msg(1, 1);
		return;
	}
	
	Guild *guild = pg_hero->getGuild();
	if (guild == NULL)
	{
		//玩家没有所属帮派，不能接帮派拉镖任务
		cout<<"The pg_hero can't refresh wagon when he doesn't join a guild!"<<endl;
		send_guild_wagon_error_msg(1, 2);
		return;
	}
	guildLevel = guild->getLevel();
	index = guildLevel - 1;
	
	if (pg_hero->findAcceptedTaskList(wagonTaskId) == NULL)
	{
		cout<<"The pg_hero havn't accepted the task so he can't refresh wagon"<<endl;
		send_guild_wagon_error_msg(1, 3);
		return;
	}
	
	Point heroPt = pg_hero->getLocation();
	Point npcPt(5839,2667);
	if (GET_DISTANCE(heroPt, npcPt) > 400)
	{
		cout<<"distance is too far when the hero want to get wagon"<<endl;
		send_guild_wagon_error_msg(1, 4);
		return;
	}
	
	//护送帮派镖任务
	map<string, string>::iterator iter_color;
	//检查玩家是否花钱刷出了好马车
	iter_color = heroId_2_colorWagon.find(pg_hero->getIdentity());
	if (iter_color != heroId_2_colorWagon.end())
	{
		nowWagonId = const_cast<char*>(iter_color->second.c_str());
	} else {
		nowWagonId = firstWagonId;
	}
	
	map<string,Wagon*>::iterator it_wagon;
	it_wagon = wagonConfMap.find(nowWagonId);
	if (it_wagon == wagonConfMap.end())
	{
		cout<<"Can't find wagon with this id and this id is "<<nowWagonId<<endl;
		send_guild_wagon_error_msg(1, 5);
		return;
	}

	//获取马车奖励系数
	Wagon *srcWagon = it_wagon->second;
	float rewardTimes = srcWagon->getRewardTimes();
	map<string, GuildReward_T>::iterator it_gr;
	it_gr = id_2_guildReward.find(wagonTaskId);
	GuildReward_T *p_gr = &it_gr->second;
	sprintf(msg, "5,20,%s,%d,%d,%d", nowWagonId, int(p_gr->rewardGuildExp[index] * rewardTimes),
		int(p_gr->rewardSelfMoney[index] * rewardTimes), int(p_gr->rewardSelfGlory[index] * rewardTimes));
	send_msg(pg_hero->getFd(), msg);

}

void getWagonComm(char* buffer)
{
	char *nowWagonId = NULL;
	int guildLevel = 0, index = 0;
	nowWagonId = pg_hero->memHero->wagonId;
	if (nowWagonId == NULL || strlen(nowWagonId) != 0)
	{
		cout<<"The hero is driving wagon, he can't view more wagon info!"<<endl;
		send_guild_wagon_error_msg(3, 1);
		return;
	}
	
	Guild *guild = pg_hero->getGuild();
	if (guild == NULL)
	{
		//玩家没有所属帮派，不能接帮派拉镖任务
		cout<<"The hero can't refresh wagon when he doesn't join a guild!"<<endl;
		send_guild_wagon_error_msg(3, 2);
		return;
	}
	guildLevel = guild->getLevel();
	index = guildLevel - 1;
	
	if (pg_hero->findAcceptedTaskList("task00295") == NULL)
	{
		cout<<"The hero havn't accepted the task so he can't refresh wagon"<<endl;
		send_guild_wagon_error_msg(3, 3);
		return;
	}
	
	Point heroPt = pg_hero->getLocation();
	Point npcPt(5839,2667);
	if (GET_DISTANCE(heroPt, npcPt) > 400)
	{
		cout<<"distance is too far when the hero want to get wagon"<<endl;
		send_guild_wagon_error_msg(3, 4);
		return;
	}
	//护送帮派镖任务
	map<string, string>::iterator iter_color;
	//检查玩家是否花钱刷出了好马车
	iter_color = heroId_2_colorWagon.find(pg_hero->getIdentity());
	if (iter_color != heroId_2_colorWagon.end())
	{
		nowWagonId = const_cast<char*>(iter_color->second.c_str());
	} else {
		nowWagonId = firstWagonId;
	}
	
	heroId_2_colorWagon.erase(pg_hero->getIdentity());
	
	map<string,Wagon*>::iterator it_wagon;
	it_wagon = wagonConfMap.find(nowWagonId);
	if (it_wagon == wagonConfMap.end())
	{
		cout<<"Can't find wagon with this id and this id is "<<nowWagonId<<endl;
		send_guild_wagon_error_msg(3, 5);
		return;
	}
	
	//获取马车奖励系数
	Wagon *srcWagon = it_wagon->second;
	Wagon *myWagon = srcWagon->copyWagon();
	//设置马车主人并在地图上刷出马车
	myWagon->dirveWagon(pg_hero->getIdentity());
	
	//人物下保存马车的实例ID
	char* wagonId = myWagon->getIdentity();
	strncpy(pg_hero->memHero->wagonId, wagonId, strlen(wagonId) + 1);
	pg_hero->updateHeroTaskStatus(WAGON_TASK_NEED_TYPE, "mc_pt_001", 1);
	cout<<"BisonTell: Now wagon have its owner."<<endl;
}

//查看马车奖励信息
void viewWagonRewardComm(char *buffer)
{
	char *wagonTypeId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(wagonTypeId);
	
	cout<<"the give wagonTypeId is "<<wagonTypeId<<endl;
	Guild *guild = pg_hero->getGuild();
	if (guild == NULL)
	{
		//玩家没有所属帮派，不能接帮派拉镖任务
		cout<<"The pg_hero can't get wagon reward info when he doesn't join a guild!"<<endl;
		send_guild_wagon_error_msg(4, 1);
		return;
	}
	int guildLevel = guild->getLevel();
	int index = guildLevel - 1;
	
	if (pg_hero->findAcceptedTaskList(wagonTaskId) == NULL)
	{
		cout<<"The pg_hero havn't accepted the task so he can't get wagon reward info"<<endl;
		send_guild_wagon_error_msg(4, 2);
		return;
	}
	
	Point heroPt = pg_hero->getLocation();
	Point npcPt(5839,2667);
	if (GET_DISTANCE(heroPt, npcPt) > 400)
	{
		cout<<"distance is too far when the hero want to get wagon reward info"<<endl;
		send_guild_wagon_error_msg(4, 3);
		return;
	}
#if 0	
	//护送帮派镖任务
	map<string, string>::iterator iter_color;
	//检查玩家是否花钱刷出了好马车
	iter_color = heroId_2_colorWagon.find(pg_hero->getIdentity());
	if (iter_color != heroId_2_colorWagon.end())
	{
		nowWagonId = const_cast<char*>(iter_color->second.c_str());
	} else {
		nowWagonId = firstWagonId;
	}
#endif	

	map<string,Wagon*>::iterator it_wagon;
	it_wagon = wagonConfMap.find(wagonTypeId);
	if (it_wagon == wagonConfMap.end())
	{
		cout<<"Can't find wagon with this id and this id is "<<wagonTypeId<<endl;
		send_guild_wagon_error_msg(4, 4);
		return;
	}

	char msg[400] = {0};
	//获取马车奖励系数
	Wagon *srcWagon = it_wagon->second;
	float rewardTimes = srcWagon->getRewardTimes();
	map<string, GuildReward_T>::iterator it_gr;
	it_gr = id_2_guildReward.find(wagonTaskId);
	GuildReward_T *p_gr = &it_gr->second;
	sprintf(msg, "5,23,%s,%d,%d,%d", wagonTypeId, int(p_gr->rewardGuildExp[index] * rewardTimes),
		int(p_gr->rewardSelfMoney[index] * rewardTimes), int(p_gr->rewardSelfGlory[index] * rewardTimes));
	send_msg(pg_hero->getFd(), msg);

}

void wagonIncSpeedComm(char *buffer)
{
	int speedColor = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(speedColor);
	
	map<string,Wagon*>::iterator it_wagon;
	
	it_wagon = wagonInstMap.find(pg_hero->memHero->wagonId);
	if (it_wagon == wagonInstMap.end())
	{
		cout<<"hero has no wagon !!!!!!!!!"<<endl;
		return;
	}
	Wagon *myWagon = it_wagon->second;
	
	myWagon->startIncSpeedTimer(speedColor);
}