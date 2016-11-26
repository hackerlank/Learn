/****************************************************************
 * Filename: guild_asist.h
 * 
 * Description: 帮派功能补充
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/

#include"guild_asist.h"
#include"guild_activity.h"
#include"command_other_function_all_over.h"
#include"offline_unhandle_event.h"
#include "money_operator.h"
//#include"filter_dirty_words.h"
#include"dictionary_asist.h"
#include<queue>
#include<algorithm> 
//缓存操作头文件
#include "my_memcached.h"
#include "my_mem_group.h"
//缓存操作类实例指针，全局变量
// extern MyMemcache* mem_operate;
//缓存组
extern MyMemGroup* mem_group;
extern int sock_fd;
extern Role *pg_role;
extern map<string, GuildActivity*> id_2_guildAct;		//帮派活动全局变量
/*帮派ID索引帮派
 *			--id_2_guild[0]支派阵营的帮派集合
 *			--id_2_guild[1]宗教阵营的帮派集合
 *			--id_2_guild[2]游侠阵营的帮派集合
 *			--id_2_guild[3]所有阵营的帮派集合
 */
extern map<string, Guild*> id_2_guild[4];
 
 /*帮派排名榜
 *			--guildRankList[0]支派阵营的帮派排名榜
 *			--guildRankList[1]宗教阵营的帮派排名榜
 *			--guildRankList[2]游侠阵营的帮派排名榜
 *			--guildRankList[3]所有阵营的帮派排名榜
 */
extern vector<GuildSortItem> guildRankList[4];
//帮派名到帮派ID查找
extern map<string, string> name_2_guildId;

//帮派编号索引帮派
map<int, Guild*> idNum_2_guild;

extern map<string, Hero*> heroId_to_pHero;

extern char server_name[10];

//编号为10000的服务器中所有帮派Id在memcached中的索引  
string memcAllGuildIdKey = "10000_all_guilds_id_version4";

//合服后所有帮派ID索引
// string mergeServerAllGuildIdKey = "merge_server_all_guilds_id_00005";
string mergeServerAllGuildIdKey = "merge_server_all_guilds_id_00010";

set<string> existGuildIdSet;			//所有帮派Id集合

char allGuildIds[51000] = {0};
#ifndef GUILD_ASIST_CONST
//帮派对外功能所用到的常量
#define GUILD_ASIST_CONST
//升级帮派技能消耗金钱的基数(guildSkillNeedMoneyBase[0]表示第一个技能需要升级时需要消耗的金钱基数)
const int guildSkillNeedMoneyBase[10] = {1000, 1000, 1000, 1000, 1500, 1500, 1200, 1200, 1200, 1500};
//消耗金钱增长系数(guildSkillNeedMoneyFacotr[0]表示第一个技能升级金钱增长系数)
const int guildSkillNeedMoneyFactor[10] = {50, 50, 50, 50, 80, 80, 60, 60, 60, 80};
//帮派技能增加人物属性的基数(guildSkillAddBase[0]表示第一个技能增长对应属性基数)
const int guildSkillAddBase[10] = {1000, 250, 60, 60, 30, 30, 5, 5, 5, 5};
////帮派技能增加人物属性的系数(guildSkillAddFactor[0]表示第一个技能升级增长对应属性系数)
const int guildSkillAddFactor[10] = {12, 15, 10, 10, 5, 5, 1, 1, 1, 1};
#endif

#if defined(SORT_WITH_PRIO_QUE)
priority_queue<Guild*, vector<Guild*>, CompGuild> pq;
#endif

/**
 * createGuild - 创建帮会
 * @hero: 帮会创始人
 * @name: 新建的帮会名
 * @mode: 创建帮会方式：0:花绑定游戏币建帮；1:使用建帮令建帮
 * @index: 如果使用建帮令，建帮令在背包中的位置
 * Return: 返回类型为int；
			0:建帮成功；1:玩家有所属帮会；2:帮会重名；
			3:玩家没有阵营；4:游戏币不够；5:没有建帮令
 */
int createGuild(Hero *hero, char* giveName, int mode, int index)
{
	cout<<"before BisonCheck is guild name valid"<<endl;
	//if (!charsCheckingName(name.c_str()) || !charsCheckingChat(name.c_str()))
	// int nameLen = alphaCharLen(name);
	
	// if (nameLen < 1 || nameLen > 6)
	// {
		// 名字长度不够
		// return 8;
	// }
	if (giveName == NULL || strlen(giveName) < 1 || strlen(giveName) > 18)
	{
		//名字过长
		return 8;
	}
	//名字中含非法字符
	if (isHaveIllSymbol(giveName) == 1)
	{
		return 9;
	}
  
	if (isHaveDirtyWords(giveName) == 1)
	{
		//名字中含有敏感
		
		return 10;
	}
	
	char name[32] = {0};
	//新建的帮派区号就是公共缓存下标
	sprintf(name, "%s[%03d]", giveName, PUBLIC_MEMCACHED_INDEX);
	
	cout<<"after BisonCheck is guild name valid"<<endl;
	
	char *heroId = hero->getIdentity();
	//string heroId = hero->getIdentity();
	char *nickName = hero->getNickName();
	//string nickName = hero->getNickName();
	char *party = hero->getParty();
	//string party = hero->getParty();
	int level = hero->getLevel();
	//不到18级不能创建帮派
	if (level < 18)
	{	
		return 7;
	}
	//hero没有所属帮会
	//if (hero->getGuildName().size() != 0) return -2;
	if (hero->getGuildTitle() != -1)
	{
		//玩家已经有所属帮会
		return 1;
	}
	
	Guild *newGuild = NULL;
	//创帮会前的判断
	
	//判断name是否重名
	if (name_2_guildId.find(name) != name_2_guildId.end())
	{
		return 2;
	}
	
	int camp = hero->getCamp();
	if (camp < 0 || camp > 2)
	{
		//玩家还没加入阵营不能创建帮派
		return 3;
	}
	//生成帮派ID，生成失败就继续生成新的
	//string guildId = "BP";
	char guildId[IDL + 1];
	char* uuid =  cid();
	sprintf(guildId, "%s%s", "BP", uuid);
	free(uuid);
	//guildId += cid();
	// while (guildId.size() == 0)
	// {
		// guildId = cid();
	// }
	
	Bag *bag = hero->getBag();
	//判断创建帮会的方式，进而扣除玩家的游戏币或者道具
	
	Money *heroMoney = hero->getMoney();
	if (mode == 0)
	{
		//花游戏币创建一级帮会
		if (useGameMoney(hero,20000))
		{
			newGuild = new Guild(guildId, name, heroId, nickName, party, level, camp, 1);
			//帮派名查找帮派ID的map中加入该记录
			name_2_guildId.insert(pair<string, string>(name, guildId));
			//所在阵营帮派集中加入该帮派
			id_2_guild[camp].insert(pair<string, Guild*>(guildId, newGuild));
			//全部阵营的帮派集中加入该帮派
			id_2_guild[3].insert(pair<string, Guild*>(guildId, newGuild));
			
			//新创建的帮派加载排行榜的最后
			guildRankList[camp].push_back(pair<string, Guild*>(guildId, newGuild));
			//设置新帮派在阵营中的排名
			newGuild->setRankInCamp(guildRankList[camp].size());
			
			//全阵营排行榜中也加入该帮信息--加到最后
			guildRankList[3].push_back(pair<string, Guild*>(guildId, newGuild));
			//设置帮派在所有已存中的排名
			newGuild->setRankInAll(guildRankList[3].size());
			
			idNum_2_guild.insert(pair<int, Guild*>(newGuild->getIdNum(), newGuild));
			
			hero->setGuildInfo(newGuild, 0);					//设置玩家的帮派信息
			//生成日志
			//"XXX创建了本帮."
			newGuild->makeHistory(4, 5, heroId, nickName);
			//"XXX成为了帮主."
			newGuild->makeHistory(4, 1, heroId, nickName);
			//把帮派ID存到memcached中的帮派名列表
			saveOneGuildIdToMemc(guildId);
			existGuildIdSet.insert(guildId);
			
			
			/*记录创建帮派的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,0,server_name,(int)myTime.tv_sec,heroId,hero->getNickName(),name);
			write_log(account_msg);	
			/*记录创建帮派的流水账 jolly 12.11 end*/
			
			return 0;
		}
		
		//绑定游戏币不够
		return 4;
		
	} else if (mode == 1) {
		//使用道具直接创建2级帮会
		//if (useBagGoods(hero,"b_cl_121_100", index, 1) || useBagGoods(hero,"f_cl_121_100", index, 1))
		if (useGold(hero,500))
		{
			newGuild = new Guild(guildId, name, heroId, nickName, party, level, camp, 2);
			//帮派名查找帮派ID的map中加入该记录
			name_2_guildId.insert(pair<string, string>(name, guildId));
			//所在阵营帮派集中加入该帮派
			id_2_guild[camp].insert(pair<string, Guild*>(guildId, newGuild));
			//全部阵营的帮派集中加入该帮派
			id_2_guild[3].insert(pair<string, Guild*>(guildId, newGuild));
			
			//新创建的帮派加载排行榜的最后
			guildRankList[camp].push_back(pair<string, Guild*>(guildId, newGuild));//设置新帮派在阵营中的排名
			newGuild->setRankInCamp(guildRankList[camp].size());
			
			//全阵营排行榜中也加入该帮信息--加到最后
			guildRankList[3].push_back(pair<string, Guild*>(guildId, newGuild));
			//设置帮派在所有已存中的排名
			newGuild->setRankInAll(guildRankList[3].size());
			
			idNum_2_guild.insert(pair<int, Guild*>(newGuild->getIdNum(), newGuild));

			hero->setGuildInfo(newGuild, 0);					//设置玩家的帮派信息
			//生成日志
			//"XXX创建了本帮."
			newGuild->makeHistory(4, 5, heroId, nickName);
			//"XXX成为了帮主."
			newGuild->makeHistory(4, 1, heroId, nickName);
			//把帮派ID存到memcached中的帮派名列表
			saveOneGuildIdToMemc(guildId);
			existGuildIdSet.insert(guildId);
						
			/*记录创建帮派的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,0,server_name,(int)myTime.tv_sec,heroId,hero->getNickName(),name);
			write_log(account_msg);	
			/*记录创建帮派的流水账 jolly 12.11 end*/
			
			//记录日志2013.4.28
			memset(account_msg,0,sizeof(account_msg));
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,4,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),pg_role->getUserName(),500);
			write_log(account_msg);	
						
			return 0;
		}
		
		//元宝数不足
		return 5;
	} else {
		//不存在该建帮方式
		return 6;
	}
}

/**
 * applyJoinGuild - 申请加入帮会
 * @hero: 申请加入帮会的玩家
 * @guildName: 所申请要加入的帮会名
 * Return: 返回值为int类型
		0：申请成功；1:玩家已经有所属阵营；2:玩家还没加入阵营；3:当前阵营中没有这个帮派	
 */
//int applyJoinGuild(Hero *hero, string guildName)
int applyJoinGuild(Hero *hero, char* guildName)
{
	if (guildName == NULL)
	{
		//无效帮派名
		return 3;
	}
	if (hero->getGuildTitle() != -1)
	{
		//已经有所属帮会
		return 1;
	}
	
	int camp = hero->getCamp();
	if (camp < 0 || camp > 2)
	{
		//玩家还没有加入阵营，不能申请加入帮会
		return 2;
	}
	
	if (hero->getLevel() < 18)
	{
		//申请者没有达到18级
		return 4;
	}
	//char *guildId;
	//string guildId;
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		//没有这个帮派
		return 3;
	}
	//guildId = it_guildId->second;
	Guild *guild;
	map<string, Guild*>::iterator it_guild;
	//it_guild = id_2_guild[camp].find(guildId);
	it_guild = id_2_guild[camp].find(it_guildId->second);
	if (it_guild == id_2_guild[camp].end())
	{
		//玩家阵营和帮派所在阵营不同
		return 5;
	}

	guild = it_guild->second;
	
	int ret;
	ret = guild->applyJoin(hero->getIdentity(), hero->getNickName(), hero->getParty(), hero->getLevel());
	if (ret == 0)
	{	
		// string heroId = guild->getPresidId();
		Hero *manager;
		map<string, Hero*>::iterator it_hero;
		it_hero = heroId_to_pHero.find(guild->getPresidId());
		if(it_hero != heroId_to_pHero.end())
		{
			manager = it_hero->second;
			char managerMsg[20];
			// string managerMsg = "12";
			sprintf(managerMsg, "%d,%d", 12, INFORM_ONE_APPLY_GUILD);
			// managerMsg += intTostring(INFORM_ONE_APPLY_GUILD);
			send_msg(manager->getFd(), managerMsg);
		}
	}
	return ret;
}

/**
 * agreeOneJoinGuild - 同意添加成员入帮会
 * @manager: 帮主或副帮主
 * @heroId:	所要加入帮会的成员
 * Return: 返回值为int类型
			0:加入成功；-1:所要添加玩家已经在帮会中；-2:帮会人数已满；
			1:不是帮主或副帮主；2:对应Id的玩家不存在；3:所有加入的玩家不在帮派申请列表中；
 */
int agreeOneJoinGuild(Hero *manager, char* heroId)
{
	if (heroId == NULL)
	{
		//无效ID
		return 2;
	}
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0 && managerTitle != 1)
	{
		//不是帮主或者副帮主，没有权限同意加入成员
		return 1;
	}
	
	Guild *guild = manager->getGuild();
	// string guildName = manager->getGuildName();

	//这里是策划（wellion）定的：只要帮主点击同意加入，不论成功与否，申请列表里面肯定就没这个玩家了，
	int ret = guild->removeOneApply(heroId);
	//检查其是否在申请列表
	if (!ret)
	{
		return 3;
	
	}
	
	//角色id得到角色实例
	unsigned online = 0;			//是否在线(默认在线)
	//在哪个服的
	int where = 1;
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		int size = 0;
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero join guild send a error heroId!"<<endl;
			return 2;
		}
		
		//拉上来玩家的帮派头衔看一下，他是否已经加过帮派
		if (mem_data_hero->heroGuildData.guildTitle != -1)
		{
			free(mem_data_hero);
			return 4;
		} else {
			//没有加帮派的新鲜人
			mem_data_hero->heroGuildData.guildTitle = 5;
			strncpy(mem_data_hero->heroGuildData.guildId,
				guild->getId(), sizeof(mem_data_hero->heroGuildData.guildId));
			bool isSuccess = mem_group->set_data(heroId, (char*)mem_data_hero, sizeof(MemHero), where);
			if (!isSuccess)
			{
				free(mem_data_hero);
				return 4;
			}
			int ret = guild->join(heroId, mem_data_hero->nickName, mem_data_hero->basicHeroData.party,
				mem_data_hero->level, mem_data_hero->offlineTime);
				
			if (ret == 0)
			{
				//加入成功
				//生成离线玩家未处理事件
				// UnhandleJoinGuild_T joinGuildData(UNHANDLE_JOIN_GUILD, manager->getGuildName());
				//存入邮件中
				// UNHANDLE_FUNC(heroId, 8, joinGuildData);
				
				
				/*记录加入帮派的流水账 jolly 12.11 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,1,server_name,(int)myTime.tv_sec,heroId,mem_data_hero->nickName,guild->getName());
				write_log(account_msg);	
				/*记录加入帮派的流水账 jolly 12.11 end*/
	
			}
			free(mem_data_hero);
			return ret;
		}
	}
	hero = it_hero->second;
	
	if (hero->getGuildTitle() != -1)
	{
		//这个申请者已经加入过帮派
		return 4;
	}
	
	else {
		//-1之前已把他加入帮会，-2帮会人数已满，无法加入，0加入成功
		online = 0;
		ret = guild->join(heroId, hero->getNickName(), hero->getParty(), hero->getLevel(), online);
		
		if (ret == 0)
		{	
			hero->setGuildInfo(guild, 5);					//设置玩家的帮派信息
			sendJoinGuildMsg(heroId, manager->getGuildName(), guild->getLevel());
			
			/*记录加入帮派的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,1,server_name,(int)myTime.tv_sec,heroId,hero->getNickName(),guild->getName());
			write_log(account_msg);	
			/*记录加入帮派的流水账 jolly 12.11 end*/
			
		}
		return ret;
	}
	
}

/**
 * agreeAllApply -- 同意全部申请者加入帮派
 * @manager: 帮主
 * @result: 被同意加入的人数及每个人的ID
 * Return: 返回是否成功，0为成功
 */
int agreeAllApply(Hero *manager, char *result)
{
	// string agreeMsg;
	if (result == NULL)
	{
		//无效参数
		return 1;
	}
	int guildTitle = manager->getGuildTitle();
	if (guildTitle == -1)
	{
		*result = 0;
		return 2;
		// return agreeMsg;
	}
	
	Guild *guild = manager->getGuild();
	vector<string> applyList = guild->getApplyMembsList();
	int size = applyList.size();
	if (size == 0)
	{
		*result = 0;
		return 3;
		// return agreeMsg;
	}
	
	int count = 0;
	char temp[6400] = {0};
	for(int i = 0; i < size; i++)
	{
		// string heroId = applyList[i];
		if (agreeOneJoinGuild(manager, const_cast<char *>(applyList[i].c_str())) == 0)
		{
			count++;
			//temp += "," + heroId;
			sprintf(temp + strlen(temp), ",%s", applyList[i].c_str());
		}
	}
	// agreeMsg += intTostring(count);
	// agreeMsg += temp;
	sprintf(result, ",%d%s", count, temp);
	return 0;
}
 

/**
 * disagreeJoinGuild - 拒绝申请
 * @manager: 帮主或副帮主
 * @mode: mode=0拒绝单人加入，mode=1清空帮派的申请列表
 * @heroId:	被拒绝者的ID
 * Return: 无返回值
 */
bool disagreeJoinGuild(Hero *manager, int mode, char* heroId)
{
	if (mode == 0 && heroId == NULL)
	{
		//无效Id
		return false;
	}
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0 && managerTitle != 1)
	{
		//不是帮主或者副帮主，没有权限拒绝申请
		return false;
	}
	
	Guild *guild = manager->getGuild();
	
	if (mode == 0)
	{
		//拒绝单个人的加入
		guild->removeOneApply(heroId);
		sendJoinGuildMsg(heroId, manager->getGuildName(), 0);
	} else if (mode == 1) {
		//清空申请列表
		vector<string> applyList = guild->getApplyMembsList();
		int size = applyList.size();
		for(int i = 0; i < size; i++)
		{	
			sendJoinGuildMsg(const_cast<char *>(applyList[i].c_str()), manager->getGuildName(), 0);
		}
		
		guild->removeAllApply();
		
	}
	return true;
}

//玩家退出帮会
bool exitGuild(Hero *hero)
{
	char* heroId = hero->getIdentity();
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//玩家没在帮派
		return false;
	}
	
	//如果在帮派战中，不能退出帮派
	if (hero->isInGuildWarRoom() || hero->isInCampWar())
	{
		return false;
	}
	
	Guild *guild = hero->getGuild();
	if (title == 0)
	{
		//帮主如果要退出，请把帮主职位转让给信任的成员，帮会不能一日无帮主
		if (guild->getCurMembs() == 1)
		{
			disbandGuild(hero);
			return true;
		}
		return false;
	
	} else if (title == 1) {
		//副帮主走了，建议客户端给个提醒，走之前是否转让副帮主职位
		//自我开除,肯定成功，他就是副帮主。不用判断返回值
		guild->managerRetired(heroId, 1);
		
	}
	
	hero->clrGuildInfo();				//清除玩家的帮派信息

	//帮派得到的福利也要还原，如技能提升的属性
	//todo:......
	hero->clrGuildSkillAddTotal();		//只要一句话，把所有的帮派技能附加属性都清除了
	
	guild->exit(hero->getIdentity());			//帮会不记录你的数据了
	//生成帮派日志："XXX退出了帮会。"
	guild->makeHistory(4, 8, hero->getIdentity(), hero->getNickName());
	
	
	/*记录退出的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,2,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),guild->getName());
	write_log(account_msg);	
	/*记录退出的流水账 jolly 12.11 end*/
	
	return true;
}

//驱逐出帮会
int driveOutGuild(Hero *manager, char* heroId)
{
	if (heroId == NULL)
	{
		return 1;
	}
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0 && managerTitle != 1)
	{
		//不是帮主或者副帮主，没有权限驱逐成员
		return 2;
	}
	
	if (strcmp(manager->getIdentity(), heroId) == 0)
	{
		//不能踢出自己
		return 3;
	}
	
	Guild *guild = manager->getGuild();
	
	//得到被驱逐角色实例
	Hero *hero = NULL;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	
	char hisNickName[IDL + 1] = {0};
	char hisGuildId[IDL + 1] = {0};
	int hisGuildTitle;
	int where = 0;
	if(it_hero == heroId_to_pHero.end())
	{
		//玩家不在线
		int size = 0;
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero driveOutGuild send a error heroId!"<<endl;
			//帮会将遗忘他,不论他之前何等荣耀过
			guild->exit(heroId);
			//生成帮派日志："XXX被请出帮派。"
			guild->makeHistory(4, 4, heroId, hisNickName);
			
			//jolly你忘了在这里玩家指针是否为空了，尽管之前你判断了，但是
			//添加新功能的时候，还是漏掉了，你的荣耀被抹灭了。benliao 2013.1.2
			//帮你改过来了，不用hero指针了。
			/*记录退出的流水账 jolly 12.11 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,2,server_name,(int)myTime.tv_sec,heroId,hisNickName,guild->getName());
			write_log(account_msg);	
			/*记录退出的流水账 jolly 12.11 end*/
			return 0;
		}
		
		//拉上来玩家的信息
		strncpy(hisNickName, mem_data_hero->nickName, strlen(mem_data_hero->nickName) + 1);
		strncpy(hisGuildId, mem_data_hero->heroGuildData.guildId, strlen(mem_data_hero->heroGuildData.guildId) + 1);
		hisGuildTitle = mem_data_hero->heroGuildData.guildTitle;
		//不生成未处理事件了，直接玩家上来的时候检查自己是否还在帮派中
		free(mem_data_hero);
	} else {
		hero = it_hero->second;
		
		//如果在帮派战中，不能退出帮派; 阵营战也不行
		if (hero->isInGuildWarRoom() || hero->isInCampWar())
		{
			//玩家在阵营战或帮派战中
			return 4;
		}
		
		strncpy(hisNickName, hero->getNickName(), strlen(hero->getNickName()) + 1);
		strncpy(hisGuildId, hero->getGuildId(), strlen(hero->getGuildId()) + 1);
		hisGuildTitle = hero->getGuildTitle();
	}
	
	if (strcmp(hisGuildId, manager->getGuildId()) != 0)
	{
		//不是一个帮
		char tipMsg[300] = {0};
		sprintf(tipMsg, "you want remove the guy's guildName is %s and you(The manager)'s guildId is %s!", hisGuildId, manager->getGuildId());
		send_msg(manager->getFd(), tipMsg);
		// return 3;
	}
	
	cout<<"[BisonShow] managerTitle is "<<managerTitle<<" and the guildTitle of the hero be droven out is "<<hisGuildTitle<<endl; 
	if (managerTitle >= hisGuildTitle && hisGuildTitle <= 1)
	{
		//被驱逐者比自己职位高
		return 5;
	}
	
	if (hisGuildTitle != 5 && hisGuildTitle >= 0)
	{
		//被驱逐者是管理者，先清除他的管理者身份
		guild->managerRetired(heroId, hisGuildTitle);
	}
	
	if (hero != NULL)
	{	
		//对于在线玩家，直接清除
		//清除玩家的帮派信息
		hero->clrGuildInfo();
		//清除玩家技能锁附加的属性
		hero->clrGuildSkillAddTotal();
		
		// string removeMsg = "12";
		// removeMsg += intTostring(INFORM_REMOVED_GUILD);
		char removeMsg[10];
		sprintf(removeMsg, "%d,%d", 12, INFORM_REMOVED_GUILD);
		send_msg(hero->getFd(), removeMsg);
	}
	//帮会将遗忘他,不论他之前何等荣耀过
	guild->exit(heroId);
	//生成帮派日志："XXX被请出帮派。"
	guild->makeHistory(4, 4, heroId, hisNickName);
	
	//jolly你忘了在这里玩家指针是否为空了，尽管之前你判断了，但是
	//添加新功能的时候，还是漏掉了，你的荣耀被抹灭了。benliao 2013.1.2
	//帮你改过来了，不用hero指针了。
	/*记录退出的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",9,2,server_name,(int)myTime.tv_sec,heroId,hisNickName,guild->getName());
	write_log(account_msg);	
	/*记录退出的流水账 jolly 12.11 end*/
	
	
	return 0;
	
}

int changeGuildTitle(Hero *manager, char* heroId, int title)
{
	if (heroId == NULL)
	{
		//无效ID
		return 1;
	}
	char* managerId = manager->getIdentity();
	if (!strcmp(managerId, heroId))
	{
		//不能对自己操作
		return 2;
	}
	
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0 && managerTitle != 1)
	{
		//不是帮主也不是副帮主
		return 3;
	}
	
	if (title < managerTitle)
	{
		//无权操作
		return 4;
	}
	
	Guild *guild = manager->getGuild();
	char* guildName = manager->getGuildName();
	//即位的玩家实例
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		//被操作的玩家不在线
		return 5;
	}
	hero = it_hero->second;
	
	if (strcmp(hero->getGuildName(), guildName) != 0)
	{
		//和操作的玩家不在一个帮
		return 6;
	}
	
	//高职位的先辞职，空出职位，变成帮众
	guild->managerRetired(managerId, managerTitle);
	manager->setGuildInfo(guild, 5);
	
	//新官上任
	guild->setManager(heroId, hero->getNickName(), managerTitle);
	hero->setGuildInfo(guild, managerTitle);
	
	//生成帮派日志："XXX成为了（副）帮主。"
	if (managerTitle== 0)
	{
		guild->makeHistory(4, 1, heroId, hero->getNickName());
	} else {
		guild->makeHistory(4, 2, heroId, hero->getNickName());
	}
	
	
	if (title == 0)
	{
		//转让帮主职位
		
	} else if (title == 1 && managerTitle == 0) {
		//帮主任命副帮主
		
	} else if (title == 1 && managerTitle == 1) {
		//副帮主转让
		
	} else if (title == 5 && managerTitle == 0) {
		//帮主把副帮主免职
	} else {
		//无效职务调整
		return 6;
	}
}

//任命 -- 目前只有帮主可以任命副帮主
bool appointGuildTitle(Hero *manager, char* heroId)
{
	if (heroId == NULL)
	{
		//无效ID
		return false;
	}
	
	char* managerId = manager->getIdentity();
	if (!strcmp(managerId, heroId))
	{
		//不能对自己使用任命功能
		return false;
	}
	
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0)
	{
		//帮会现在只有1个帮主1个副帮主，要任命只有一个副帮主职位可以任命
		//能任命副帮主的则必须是帮主
		return false;
	}
	
	Guild *guild = manager->getGuild();
	if (guild == NULL)
	{
		return false;
	}
	
	//帮会名
	char* guildName = manager->getGuildName();
	
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	
	char hisNickName[IDL + 1] = {0};
	char hisGuildId[IDL + 1] = {0};
	int hisGuildTitle;
	int where = 0;
	if(it_hero == heroId_to_pHero.end())
	{
		//玩家不在线
		int size = 0;
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero driveOutGuild send a error heroId!"<<endl;
			return false;
		}
		
		//拉上来玩家的信息
		strncpy(hisNickName, mem_data_hero->nickName, strlen(mem_data_hero->nickName) + 1);
		strncpy(hisGuildId, mem_data_hero->heroGuildData.guildId, strlen(mem_data_hero->heroGuildData.guildId) + 1);
		hisGuildTitle = mem_data_hero->heroGuildData.guildTitle;
		//不生成未处理事件了，直接玩家上来的时候检查自己是否还在帮派中
		free(mem_data_hero);
	} else {
		hero = it_hero->second;
	
		strncpy(hisNickName, hero->getNickName(), strlen(hero->getNickName()) + 1);
		strncpy(hisGuildId, hero->getGuildId(), strlen(hero->getGuildId()) + 1);
		hisGuildTitle = hero->getGuildTitle();
		//对于在线玩家，直接设置他职位
		hero->setGuildInfo(guild, 1);
	}
	
	if (strcmp(hisGuildId, guild->getId()) != 0)
	{
		//都不是一个帮的，不能跨帮任命
		return false;
	}
	
	if (hisGuildTitle == 1)
	{
		//已经是副帮主，再任命没有意义
		return false;
	}
	
	if (strlen(guild->getVicePresident()) != 0)
	{
		//帮会有副帮主，要先把前副帮主免职才能任命新副帮主
		if (!deposeGuildTitle(manager, guild->getVicePresidId()))
		{
			return false;
		}
	}
	
	//前面已经判断了，现在副帮主位置空着呢，不用检查它返回值了
	guild->setVicePresident(heroId, hisNickName);
	//生成帮派日志："XXX成为副帮主."
	guild->makeHistory(4, 2, heroId, hisNickName);
	return true;
	
}

//免职 -- 帮主可以免副帮主的职
bool deposeGuildTitle(Hero *manager, char* heroId)
{
	if (manager == NULL || heroId == NULL)
	{
		//无效ID
		return false;
	}
	
	char* managerId = manager->getIdentity();
	if (!strcmp(managerId, heroId))
	{
		//不能对自己使用免职功能
		return false;
	}
	
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0)
	{
		//帮会现在只有1个帮主1个副帮主，要撤销只有一个副帮主职位可以撤销
		//能撤销副帮主的则必须是帮主
		return false;
	}
	
	Guild *guild = manager->getGuild();
	if (guild == NULL)
	{
		return false;
	}
	//帮会名
	char* guildName = manager->getGuildName();
	
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	
	bool findHeroOKFlag = false;
	char hisGuildId[IDL + 1] = {0};
	int hisGuildTitle;
	int where = 0;
	if(it_hero == heroId_to_pHero.end())
	{
		//玩家不在线
		int size = 0;
		// MemHero *mem_data_hero = (MemHero*)mem_operate->get_mem_data(heroId, &size);
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero driveOutGuild send a error heroId!"<<endl;
			//开除副帮主
			guild->managerRetired(heroId, 1);
			return true;
		}
		
		//拉上来玩家的信息
		strncpy(hisGuildId, mem_data_hero->heroGuildData.guildId, strlen(mem_data_hero->heroGuildData.guildId) + 1);
		hisGuildTitle = mem_data_hero->heroGuildData.guildTitle;
		//不生成未处理事件了，直接玩家上来的时候检查自己帮派信息
		free(mem_data_hero);
	} else {
		hero = it_hero->second;
		strncpy(hisGuildId, hero->getGuildId(), strlen(hero->getGuildId()) + 1);
		hisGuildTitle = hero->getGuildTitle();
		findHeroOKFlag = true;
	}
	
	
	if (strcmp(hisGuildId, guild->getId()) != 0)
	{
		//都不是一个帮的，不能跨帮任命
		return false;
	}
	
	if (hisGuildTitle == 5)
	{
		//普通帮众，本来就没职位
		return false;
	}
	
	//开除副帮主
	guild->managerRetired(heroId, 1);
	if (findHeroOKFlag)
	{	
		//对于在线玩家，直接设置他职位
		hero->setGuildInfo(guild, 5);
	}
	return true;
	
}


//让贤 -- 帮主或副帮主可以让贤给帮派内比自身职位低的玩家
bool demiseGuildTitle(Hero *manager, char* heroId)
{
	if (heroId == NULL)
	{
		//无效ID
		return false;
	}
	
	char* managerId = manager->getIdentity();
	if (managerId == heroId)
	{
		//不能对自己使用让贤操作
		return false;
	}
	
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0 && managerTitle != 1)
	{
		//不是帮主或者副帮主，让贤就不用你不操心了
		return false;
	}
	
	Guild *guild = manager->getGuild();
	if (guild == NULL)
	{
		return false;
	}
	
	//即位的玩家实例
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	
	bool findHeroFlag = false;
	char hisNickName[IDL + 1] = {0};
	char hisGuildId[IDL + 1] = {0};
	int hisGuildTitle = 5;
	int where = 0;
	if(it_hero == heroId_to_pHero.end())
	{
		//玩家不在线
		int size = 0;
		// MemHero *mem_data_hero = (MemHero*)mem_operate->get_mem_data(heroId, &size);
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero demiseGuildTitle send a error heroId!"<<endl;
			return false;
		}
		
		//拉上来玩家的信息
		strncpy(hisNickName, mem_data_hero->nickName, strlen(mem_data_hero->nickName) + 1);
		strncpy(hisGuildId, mem_data_hero->heroGuildData.guildId, strlen(mem_data_hero->heroGuildData.guildId) + 1);
		hisGuildTitle = mem_data_hero->heroGuildData.guildTitle;
		//不生成未处理事件了，直接玩家上来的时候更新自己帮派信息
	} else {
		hero = it_hero->second;
	
		strncpy(hisNickName, hero->getNickName(), strlen(hero->getNickName()) + 1);
		strncpy(hisGuildId, hero->getGuildId(), strlen(hero->getGuildId()) + 1);
		hisGuildTitle = hero->getGuildTitle();
		findHeroFlag = true;
	}
	
	
	//禅让者的帮会名
	char* guildName = manager->getGuildName();
	
	if (strcmp(hisGuildId, guild->getId()) != 0)
	{
		//都不是一个帮的，不能跨帮让贤
		return false;
	}
	
	if (hisGuildTitle <= managerTitle && hisGuildTitle >= 0)
	{
		//只能让贤给自己职位低的
		return false;
	}
	
	if (hisGuildTitle != 5 && hisGuildTitle >= 0)
	{
		//有职位，但是有高职位的让贤，去低就高
		if (!guild->managerRetired(heroId, hisGuildTitle))
		{
			return false;
		}
	}
	
	//高职位的先辞职，空出职位，变成帮众
	guild->managerRetired(managerId, managerTitle);
	manager->setGuildInfo(guild, 5);
	
	//新官上任
	guild->setManager(heroId, hisNickName, managerTitle);
	
	if (findHeroFlag)
	{
		//玩家在线
		hero->setGuildInfo(guild, managerTitle);
	}
	
	//生成帮派日志："XXX成为了（副）帮主。"
	if (managerTitle== 0)
	{
		guild->makeHistory(4, 1, heroId, hisNickName);
	} else {
		guild->makeHistory(4, 2, heroId, hisNickName);
	}
	return true;
	
}

bool GM_setGuildPresid(char* heroId)
{
	if (heroId == NULL)
	{
		//无效ID
		return false;
	}
	
	int managerTitle = 0;
	
	
	//即位的玩家实例
	Hero *hero = heroid_to_hero(heroId);
	
	bool findHeroFlag = false;
	char hisNickName[IDL + 1] = {0};
	char hisGuildId[IDL + 1] = {0};
	int hisGuildTitle = -1;
	int where = 0;
	
	if(hero == NULL)
	{
		//玩家不在线
		int size = 0;
		// MemHero *mem_data_hero = (MemHero*)mem_operate->get_mem_data(heroId, &size);
		MemHero *mem_data_hero = (MemHero*)mem_group->get_data(heroId, &size, &where);
		
        if(mem_data_hero == NULL)
        {
			//实在对不起了，查无此角色，连memcached都没有
			cout<<"BisonWarning: when agree one hero demiseGuildTitle send a error heroId!"<<endl;
			return false;
		}
		
		//拉上来玩家的信息
		strncpy(hisNickName, mem_data_hero->nickName, strlen(mem_data_hero->nickName) + 1);
		strncpy(hisGuildId, mem_data_hero->heroGuildData.guildId, strlen(mem_data_hero->heroGuildData.guildId) + 1);
		hisGuildTitle = mem_data_hero->heroGuildData.guildTitle;
		//不生成未处理事件了，直接玩家上来的时候更新自己帮派信息
	} else {
	
		strncpy(hisNickName, hero->getNickName(), strlen(hero->getNickName()) + 1);
		strncpy(hisGuildId, hero->getGuildId(), strlen(hero->getGuildId()) + 1);
		hisGuildTitle = hero->getGuildTitle();
		findHeroFlag = true;
	}
	
	
	Guild* guild = getGuildWithId(hisGuildId);
	if (guild == NULL)
	{
		return false;
	}
	
	if (hisGuildTitle <= managerTitle && hisGuildTitle >= 0)
	{
		//只能让贤给自己职位低的
		return false;
	}
	
	if (hisGuildTitle != 5 && hisGuildTitle >= 0)
	{
		//有职位，但是有高职位的让贤，去低就高
		if (!guild->managerRetired(heroId, hisGuildTitle))
		{
			return false;
		}
	}
	
	//新官上任
	guild->setManager(heroId, hisNickName, managerTitle);
	
	if (findHeroFlag)
	{
		//玩家在线
		hero->setGuildInfo(guild, managerTitle);
	}
	
	//生成帮派日志："XXX成为了（副）帮主。"
	if (managerTitle== 0)
	{
		guild->makeHistory(4, 1, heroId, hisNickName);
	} else {
		guild->makeHistory(4, 2, heroId, hisNickName);
	}
	return true;
}

//辞职 - 目前只有副帮主可以做此操作
bool resignGuildTitle(Hero *manager)
{
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0)
	{
		//只有副帮主才能辞职，帮主辞职了就没有老大了
		return false;
	}
	
	Guild *guild = manager->getGuild();
	if (guild == NULL)
	{
		return false;
	}
	
	//副帮主炒了自己
	guild->managerRetired(manager->getIdentity(), 1);
	//变成帮众了
	manager->setGuildInfo(guild, 0);
	return true;
}


//对全部帮派进行帮内的贡献度排名,mode=0为日排名，mode=1为周排名
void guildRank(int mode)
{
	Guild *guild;
	map<string, Guild*>::iterator it_guild;
	it_guild = id_2_guild[3].begin();
	
	//因为要对全部帮会都要操作，
	for (it_guild; it_guild != id_2_guild[3].end(); it_guild++)
	{
		guild = it_guild->second;
		//按帮贡献度排名
		guild->rankInGuild(mode);
	}

}

//查看自身帮派的福利
int viewRankGuildRewardInfo(Hero *hero, int mode, char* result)
{
	if (result == NULL)
	{
		return 3;
	}
	// string rewardInfo = intTostring(mode);
	// string noReward = ",0,0,0,0";
	sprintf(result, ",%d,0,0,0,0", mode);
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有加入帮派
		// return (rewardInfo + noReward);
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	
	map<string, GuildReward_T>::iterator it_gr;
	GuildReward_T *p_gr = NULL;
	if (mode == 0)
	{
		it_gr = id_2_guildReward.find("dayRankReward");
	} else if (mode == 1)
	{
		it_gr = id_2_guildReward.find("weekRankReward");
	} else {
		return 5;
	}
	
	if (it_gr == id_2_guildReward.end())
	{
		return 5;
	}
	
	p_gr = &it_gr->second;
	
	int ranking = guild->getRankOrder(hero->getIdentity(), mode);
	if (ranking == 0)
	{
		//当前没有排名奖励或者已经领取过排名奖励
		// return (rewardInfo + noReward);
		return 2;
	}
	
	int rewardMoney, rewardExp, rewardGlory;
	int level = guild->getLevel();
	int cntRank = 0;
	if (ranking > 1000)
	{
		cntRank = ranking - 1000;
	}
	else {
		cntRank = ranking;
	}
	
	rewardExp = p_gr->rewardSelfExp[level - 1] * (11 - cntRank);
	rewardMoney = p_gr->rewardSelfMoney[level - 1] * (11 - cntRank);
	rewardGlory = p_gr->rewardSelfGlory[level - 1] * (11 - cntRank);

#if 0		
	int factor = level * (11 - cntRank);
	if (mode == 0)
	{
		rewardMoney = DAY_REWARD_MONEY_BASE * factor;
		rewardExp = DAY_REWARD_EXP_BASE * factor;
		rewardGlory = DAY_REWARD_GLORY_BASE * factor;
	} else {
		rewardMoney = WEEK_REWARD_MONEY_BASE * factor;
		rewardExp = WEEK_REWARD_EXP_BASE * factor;
		rewardGlory = WEEK_REWARD_GLORY_BASE * factor;
	}
#endif	
	// rewardInfo += intTostring(ranking);
	// rewardInfo += intTostring(rewardMoney);
	// rewardInfo += intTostring(rewardExp);
	// rewardInfo += intTostring(rewardGlory);
	sprintf(result, ",%d,%d,%d,%d,%d", mode, ranking, rewardMoney, rewardExp, rewardGlory);
	return 0;

}

/**
 * getGuildReward - 领取帮派福利
 * @hero: 领取者
 * @mode: 领取项，mode = 0:领取昨日排名奖；mode = 1:领取上周排名奖励
 * Return: 返回是否领取成功
 */
bool getGuildRankReward(Hero *hero, int mode)
{
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有加入帮派
		return false;
	}
	
	Guild *guild = hero->getGuild();
	map<string, GuildReward_T>::iterator it_gr;
	int level = guild->getLevel();
	GuildReward_T *p_gr = NULL;

	if (mode == 0)
	{
		it_gr = id_2_guildReward.find("dayRankReward");
	} else if (mode == 1)
	{
		it_gr = id_2_guildReward.find("weekRankReward");
	} else if (mode == 2)
	{
		it_gr = id_2_guildReward.find("campLeader");
	} else if (mode == 3)
	{
		it_gr = id_2_guildReward.find("campChief");
	} else {
		return false;
	}
	
	if (it_gr == id_2_guildReward.end())
	{
		return false;
	}
	p_gr = &it_gr->second;
	
	if (mode == 0 || mode == 1)
	{
		int ranking = guild->getRankOrder(hero->getIdentity(), mode);
		
		if (ranking >= 1000)
		{
			//当前没有排名奖励或者已经领取过排名奖励
			return false;
		}
	
		int incExp = p_gr->rewardSelfExp[level - 1] * (11 - ranking);
		int incMoney = p_gr->rewardSelfMoney[level - 1] * (11 - ranking);
		int incGlory = p_gr->rewardSelfGlory[level - 1] * (11 - ranking);
		hero->setExpNow(incExp);
		increaseBoundGameMoney(hero, incMoney);
		
		//加帮贡的事交给帮派来处理，这里面还做了一件事，把玩家名次变成0，以免他下次再领
		guild->getRankReward(hero->getIdentity(), incGlory, mode);
		
		if (mode == 0)
		{
			hero->incGuildDayRewardTime();
		}
		
		int heroNowGlory = guild->getHeroTotalGlory(hero->getIdentity());
		if (heroNowGlory > 10000)
		{
			hero->addTitle("T036");
		}
		return true;
	} else if (mode == 2 || mode == 3)
	{
		char campTitle = guild->getCampTitle();
		int incExp = p_gr->rewardGuildExp[level - 1];
		int incMoney = p_gr->rewardSelfMoney[level - 1];
		int incGlory = p_gr->rewardSelfGlory[level - 1];
		if (mode == 2)
		{
			if (campTitle & 0x1)
			{
				if (hero->dayLmtFindGroup.isOneItemFull("campLeaderReward") == 1)
				{
					return false;
				}
				guild->donateExp(hero->getIdentity(), incExp);
				increaseBoundGameMoney(hero, incMoney);
				guild->addGloryOfHero(hero->getIdentity(), incGlory);
				int index = hero->dayLmtFindGroup.incOneItem("campLeaderReward");
				if (index != -1)
				{
					//更新到memcached保存数据
					hero->memHero->dayLmtItemArr[index].incVal();
				}
				
				int heroNowGlory = guild->getHeroTotalGlory(hero->getIdentity());
				if (heroNowGlory > 10000)
				{
					hero->addTitle("T036");
				}
				return true;
			}else {
				return false;
			}
		} else if (mode == 3) {
			if (campTitle & 0x2)
			{
				if (hero->dayLmtFindGroup.isOneItemFull("campChiefReward") == 1)
				{
					return false;
				}
				guild->donateExp(hero->getIdentity(), incExp);
				increaseBoundGameMoney(hero, incMoney);
				guild->addGloryOfHero(hero->getIdentity(), incGlory);
				int index = hero->dayLmtFindGroup.incOneItem("campChiefReward");
				if (index != -1)
				{
					//更新到memcached保存数据
					hero->memHero->dayLmtItemArr[index].incVal();
				}
				
				int heroNowGlory = guild->getHeroTotalGlory(hero->getIdentity());
				if (heroNowGlory > 10000)
				{
					hero->addTitle("T036");
				}
				return true;
			}else {
				return false;
			}
		}
	} else {
		return false;
	}
}

//为帮会捐钱
int donateMoneyToGuild(Hero *hero, int val, char* result)
{
	if (result == NULL)
	{
		//无效参数
		return 1;
	}
	
	//test
	// guildRank(0);		//日排行
	// guildRank(1);		//周排行
	// string donateMsg;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//阁下帮会都没有，要捐给空气不成
		*result = 0;
		return 1;
	}
	
	if (val <= 0)
	{
		*result = 0;
		//捐献金钱少于0
		return 2;
	}
	Money *money =hero->getMoney();
	if (money->money_getBoundGameMoney() < val)
	{
		//游戏币不够
		*result = 0;
		return 3;
	}
	
	//小轩子规定:钱够了，肯定能用成功。这里不用做返回值判断
	useBoundGameMoney(hero,val);
	
	Guild *guild = hero->getGuild();
	
	//捐钱加帮会贡献度
	int contb = guild->donateMoney(hero->getIdentity(), val);
	
	//生成帮派日志：”XXX为帮派做出捐赠, 捐val银两，为帮派做出val4点贡献。“
	guild->makeHistory(3, 0, hero->getIdentity(), hero->getNickName(),  val, contb);
	// donateMsg = intTostring(contb);
	sprintf(result, ",%d", contb);
#if 0	
	/****************************************************
	 ****************************************************
	 *****************FOR----TEST************************
	 ****************************************************
	 ****************************************************
	 */
	guild->donateExp(hero->getIdentity(), val);
	addMyGuildGlory(guild->getName(), hero->getIdentity(), val);
	guild->donateGlory(hero->getIdentity(), val);
	/****************************************************
	 ****************************************************
	 *****************FOR----TEST************************
	 ****************************************************
	 ****************************************************
	 */
#endif

	if (val>=10000)
	{
		hero->updataSingleTarget(3,4);
	}
	
	return 0;
}

//捐帮贡
int donateGloryToGuild(Hero *hero, int val, char *result)
{
	if (result == NULL)
	{
		//无效参数
		return 1;
	}
	// string donateMsg;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//敢问你帮会都米有，何来的帮贡捐
		*result = 0;
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	
	//捐帮贡加帮会贡献度, 成不成功我也不知道，这是帮会判断的
	int contb = guild->donateGlory(hero->getIdentity(), val);
	if (contb < 0)
	{
		return 2;
	} else {
		//生成帮派日志：”XXX为帮派做出捐赠, 捐val帮贡，为帮派做出val4点贡献。“
		guild->makeHistory(3, 1, hero->getIdentity(), hero->getNickName(), val, contb);
		//donateMsg = intTostring(contb);
		sprintf(result, ",%d", contb);
		return 0;
	}
}

//升级帮会
int upgradeGuild(Hero *manager)
{
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//不是帮主也不是副帮主，权限不够
		return 1;
	}
	
	Guild *guild = manager->getGuild();
	if (guild->getLevel() >= 5)
	{
		return 2;
	}
	int ret = guild->upgrade();
	
	if (ret == 0)
	{
		//生成帮派日志：“帮派升到level级！” id,nickname 用不到，为防止策划以后用
		guild->makeHistory(5, guild->getLevel() - 2, NULL, NULL, guild->getLevel());
	}
	
	return ret;
	
}

//获取帮派任务奖励，index：帮派任务下标
int getGuildTaskReward(Hero *hero, char* taskId, char* result, float rewardTimes)
{
	if (taskId == NULL || result == NULL)
	{
		return 3;
	}
	// string reward;
	//这里只奖励和帮派相关的福利，玩家自身的另外获得
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有帮会，就没有帮会任务奖励
		*result = 0;
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	int guildLevel = guild->getLevel();
	map<string, GuildReward_T>::iterator it_gr;
	it_gr = id_2_guildReward.find(taskId);
	if (it_gr == id_2_guildReward.end())
	{
		*result = 0;
		return 2;
	}
	
	GuildReward_T *p_gr = &it_gr->second;
	int rewardMoney = p_gr->rewardSelfMoney[guildLevel -1] * rewardTimes;
	increaseBoundGameMoney(hero, rewardMoney);

	 //传nickname是为了生成帮派日志用到，这里的帮派日志在内部生成
	int ret = guild->getTaskReward(hero->getIdentity(), hero->getNickName(), p_gr, rewardTimes, result);
	
	int heroNowGlory = guild->getHeroTotalGlory(hero->getIdentity());
	if (heroNowGlory > 10000)
	{
		hero->addTitle("T036");
	}
	
	return ret;
}

//获取签到奖励,mode表明签到时是否使用道具
int getGuildSignReaward(Hero *hero, int mode, int *err, char *result)
{
	if (result == NULL)
	{
		return 4;
	}
	int title = hero->getGuildTitle();
	string reward;
	if (title == -1)
	{
		//没有帮会，不要想着领签到礼了
		*err = 1;
		return 1;
	}
	
	if (hero->getGuildSigned())
	{
		//签过到的，不要再打歪主意了
		*err = 2;
		return 2;
	}
	
	//现在改成花元宝来做特殊签到了
	if (mode == 1)
	{
		//花元宝签到
		if (!useGold(hero,2))
		{
			//元宝不够
			*err = 3;
			return 3;
		}
		else
		{
			//记录日志2013.4.28
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,7,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),pg_role->getUserName(),2);
			write_log(account_msg);	
		}
	}
	
	Guild *guild = hero->getGuild();
	//传nickname是为了生成帮派日志用到，这里的帮派日志在内部生成
	guild->getSignInReward(hero->getIdentity(), hero->getNickName(), mode, result);
	hero->setGuildSigned(true);

	int heroNowGlory = guild->getHeroTotalGlory(hero->getIdentity());
	if (heroNowGlory > 10000)
	{
		hero->addTitle("T036");
	}
	*err = 0;
	return 0;
}

//开启第index + 1个帮派技能
int openGuildSkill(Hero *manager, int index)
{
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//不是帮主也不是副帮主，权限不够
		return 1;
	}
	
	if (index < 0 || index > 9)
	{
		//帮派哪有这技能
		return 2;
	}
	
	Guild *guild = manager->getGuild();
	int ret = guild->openSkill(index);
	if (ret == 0)
	{
		guild->makeHistory(6 + title, index, manager->getIdentity(), manager->getNickName()); 
	}
	return ret;
}

//升级第index+1个帮派技能
int upgradeGuildSkill(Hero *hero, int index)
{
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有帮会，就没有帮会任务奖励
		return 1;
	}
	
	if (index < 0 || index > 9)
	{
		//不是帮派的技能
		return 2;
	}
	
	Guild *guild = hero->getGuild();
	
	//先看玩家有没有足够的金钱
	//当前技能等级
	int curSkillLevel = guild->getSkillLevel(hero->getIdentity(), index);
	int nextLevel = curSkillLevel + 1;
	// int moneyNeed = guildSkillNeedMoneyBase[index]
				// + guildSkillNeedMoneyFactor[index] * (nextLevel * (nextLevel + 1) * (2 * nextLevel + 1)) /6;
	int moneyNeed = global_guild_skill[index].upNeedMoney[nextLevel];
	Money *heroMoney = hero->getMoney();
	//这里还不能直接用，等里面返回升级成功了再用，但是要再那之前判断钱是够用的
	if (heroMoney->money_getBoundGameMoney() < moneyNeed)
	{
		//游戏币不够，不能学习该技能
		return 3;
	}
	
	int inRet = guild->upgradeSkill(hero->getIdentity(), index);
	if ( inRet == 0)
	{
		//技能升级成功
		useBoundGameMoney(hero,moneyNeed);	//肯定能用成功，前面判断了，够用
		//jolly add wulintarget 12.4 start
		hero->updataSingleTarget(3,1);
		//jolly add wulintarget 12.4 end
		//玩家属性要加
		//int addVal = hero->getGuildSkillAdd(index);
		//维亮的现在属性加成算法有变
		int addVal = global_guild_skill[index].addAttr[nextLevel];
		
		int skillCheck = guild->checkHeroGuildSkill(hero->getIdentity());
		if (skillCheck > 1)
		{
			hero->updataSingleTarget(7,0);
		}
		if (skillCheck == 2)
		{
			hero->updataSingleTarget(7,6);
		}
#if 0
		int addVal = 0;
		//技能升级后所加属性计算
		if (index == 0 || index == 1)
		{	
			//1,2技能
			if (nextLevel == 1)
			{
				//由0级->1级
				addVal = guildSkillAddBase[index] + guildSkillAddFactor[index] * nextLevel * nextLevel;
			} else {
				//1级之后 
				//addVal += guildSkillAddFactor[index] * nextLevel * nextLevel;
				//新改法不加上一级的加成了
				addVal = guildSkillAddFactor[index] * nextLevel * nextLevel;
			}
		} else {
			//3,4,5,6,7,8,9,10技能
			if (nextLevel == 1)
			{
				addVal = guildSkillAddBase[index] + guildSkillAddFactor[index] * nextLevel;
			} else {
				//addVal += guildSkillAddFactor[index] * nextLevel;
				addVal = guildSkillAddFactor[index] * nextLevel;
			}
		}
// #if 0		
		switch(index)
		{
		case 0:
			hero->setLifeVal(hero->getLifeVal() + addVal);
			break;
		case 1:
			hero->setMagicVal(hero->getMagicVal() + addVal);
			break;
		case 2:
			hero->setOutDefense(hero->getOutDefense() + addVal);
			break;
		case 3:
			hero->setInDefense(hero->getInDefense() + addVal);
			break;
		case 4:
			hero->setOutAttack(hero->getLifeVal() + addVal);
			break;
		case 5:
			hero->setInAttack(hero->getInAttack() + addVal);
			break;	
		case 6:
			hero->setHited(hero->getHited() + addVal);
			break;
		case 7:
			hero->setDodge(hero->getDodge() + addVal);
			break;
		case 8:
			hero->setTenacity(hero->getTenacity() + addVal);
			break;	
		case 9:
			hero->setCrit(hero->getCrit() + addVal);
			break;			
		default:
			break;
		}
#else
//	hero->incAttr(index, addVal);		//人物属性的加成
	hero->setNewGuildSkillAdd(index, addVal);				//技能附加属性的加成及人物附加属性累加值记录
	//向客户端发送玩家属性更新的消息
	hero->send_msg_att();
	
#endif			
	}

	return inRet;

	
}

//查看玩家对应的帮派技能信息
int viewGuildSkillInfo(Hero *hero, char* result)
{
	if (result == NULL)
	{
		return 3;
	}
	// string skillMsg;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有帮会，就没有帮会任务奖励
		return 1;
	}
	
	bool isManager = false;
	if (title == 0 || title == 1)
	{
		//帮主或副帮主才有权限看技能能否激活的信息
		isManager = true;
	}
	
	Guild *guild = hero->getGuild();
	
	int ret = hero->getGuildSkillTotalAdd(result);
	if (ret != 0)
	{
		return 2;
	}
	
	ret = guild->viewSkillInfo(hero->getIdentity(), isManager, result + strlen(result));
	if (!ret)
	{
		hero->updataSingleTarget(7,0);
	}
	return 0;
}

//帮派排名的比较函数
static bool guildComp(GuildSortItem first, GuildSortItem second)
{
	Guild *guild1, *guild2;
	guild1 = first.second;
	guild2 = second.second;
	long score1 = guild1->getGuildScore();
	long score2 = guild2->getGuildScore();
	if (score1 > score2)
	{
		return true;
	
	} else {
		return false;
		
	}
	
#if 0	
	//先看等级
	int level1 = guild1->getLevel();
	int level2 = guild2->getLevel();
	if(level1 > level2)
	{
		return true;
		
	} else if (level2 > level1) {
		return false;
		
	} else {
		//第二重，判断当前经验
		int exp1 = guild1->getExp();
		int exp2 = guild2->getExp();
		if (exp1 > exp2)
		{
			return true;
		
		}else if (exp2 > exp1) {
			return false;
			
		} else {
			//第三重，判断总帮贡
			int glory1 = guild1->getGlory();
			int glory2 = guild2->getGlory();
			if (glory1 > glory2)
			{
				return true;
			
			} else if (glory2 > glory1) {
				return false;
				
			} else {
				//第四重，判断帮会人数
				int num1 = guild1->getCurMembs();
				int num2 = guild2->getCurMembs();
				if (num1 > num2)
				{
					return true;
				
				} else if (num2 > num1) {
					return false;
					
				}else {
					//第五重，判断帮会资金,再分不出胜负就不管了
					int money1 = guild1->getMoney();
					int money2 = guild2->getMoney();
					if (money1 >= money2)
					{
						return true;
					
					} else {
						return false;
					}
				}
			}
		}
	}
#endif	
}

/**
 * rankBetweenGuilds - 帮派间排名
 * @camp:对camp阵营的帮派进行排名
 		camp=0,1,2分别代表支派，宗教，游侠阵营
		camp=3为全阵营
 */
static void rankBetweenGuilds(int camp)
{
	map<string, Guild*>::iterator it;
	it = id_2_guild[camp].begin();
	//把之前的排名清除掉，再对全部阵营重新排名
	guildRankList[camp].clear();
	for (it; it != id_2_guild[camp].end(); it++)
	{
		guildRankList[camp].push_back(pair<string, Guild*>(it->first, it->second));
	}
	
	sort(guildRankList[camp].begin(), guildRankList[camp].end(), guildComp);
	
	//分别记录每个帮派对应排名
	int size = guildRankList[camp].size();
	for (int i = 0; i < size; i++)
	{
		if (camp == 3)
		{
			guildRankList[camp][i].second->setRankInAll(i + 1);
		} else {
			guildRankList[camp][i].second->setRankInCamp(i + 1);
		}
		
	}
	//更新排行榜总页数
	Guild::totalPages[camp] = size / 12 + ((size % 12) ? 1 : 0);
	if (size == 0)
	{
		Guild::totalPages[camp] = 1;
	}
}

void allGuildRank()
{
	rankBetweenGuilds(0);	//对支派阵营帮派排名
	rankBetweenGuilds(1);	//对宗教阵营帮派排名
	rankBetweenGuilds(2);	//对游侠阵营帮派排名
	rankBetweenGuilds(3);	//对所有阵营帮派排名
}

extern Hero* pg_hero;
/**
 * viewGuildRankInfo - 查看帮派排名信息
 * @page: 所查看的排行榜的页序
 * @camp: 所查看排行榜的阵营
 * Return: 返回当所查看页的帮派信息
 */
int viewGuildRankInfo(int page, int camp, char* result)
{
	char scoreStr[10000] = {0};
	//这里先加这一句触发帮派排名，但这一句真不是该加这里的，以后移走
	//allGuildRank();
	if (result == NULL)
	{
		return 2;
	}
	// string viewResult;
	//更新帮派页数
	int size = guildRankList[camp].size();
	Guild::totalPages[camp] = size / GUILD_NUM_PER_PAGE + ((size % GUILD_NUM_PER_PAGE) ? 1 : 0);
	//总的帮派页数
	int totalPages = Guild::totalPages[camp];
	//viewResult = intTostring(((totalPages == 0) ? 1 : totalPages));
	sprintf(result, ",%d", ((totalPages == 0) ? 1 : totalPages));
	if (page > totalPages || page < 1)
	{
		//所请求页面不存在
		return 1;
	}
	
	int i, num;
	if (page != totalPages)
	{
		num = page * GUILD_NUM_PER_PAGE;
	} else {
		//该页小于12个
		num = guildRankList[camp].size();
	}
	cout<<"[BisonShow] this  page has "<<num<<"guild info"<<endl;
	for (i = (page - 1) * GUILD_NUM_PER_PAGE; i < num; i++)
	{
		Guild *guild = guildRankList[camp][i].second;
		sprintf(scoreStr + strlen(scoreStr), "%ld,", guild->getGuildScore());
		int rankNum = i + 1;
		if (camp == 3)
		{
			guild->setRankInAll(rankNum);
		} else {
			guild->setRankInCamp(rankNum);
		}

		// viewResult += intTostring(rankNum);
		// viewResult += "," + guild->getName();
		// viewResult += intTostring(guild->getCamp());
		// viewResult += "," + guild->getPresident();
		// viewResult += intTostring(guild->getLevel());
		// viewResult += intTostring(guild->getCurMembs());
		sprintf(result + strlen(result), ",%d,%s,%d,%s,%d,%d", rankNum, guild->getName(), guild->getCamp(),
			guild->getPresident(), guild->getLevel(), guild->getCurMembs());
	}
	send_msg(pg_hero->getFd(), scoreStr);
	return 0;
	//guildRankList.size
}

int viewGuildGameInfo(int camp, int num, int page, char *result)
{
	if (camp < 0 || camp > 3 || num < 0 || page < 1 || result == NULL)
	{
		//接收客户端数据有误
		return 1;
	}
	
	//更新帮派页数
	int size = guildRankList[camp].size();
	Guild::totalPages[camp] = size / num + ((size % num) ? 1 : 0);
	//总的帮派页数
	int totalPages = Guild::totalPages[camp];
	//viewResult = intTostring(((totalPages == 0) ? 1 : totalPages));
	sprintf(result, ",%d", ((totalPages == 0) ? 1 : totalPages));
	if (page > totalPages || page < 1)
	{
		//所请求页面不存在
		return 2;
	}
	
	int i, pageMaxNum = 0;
	if (page != totalPages)
	{
		pageMaxNum = page * num;
	} else {
		//该页小于num个
		pageMaxNum = guildRankList[camp].size();
	}
	cout<<"[BisonShow] this  page has "<<pageMaxNum<<"guild info"<<endl;
	for (i = (page - 1) * num; i < pageMaxNum; i++)
	{
		Guild *guild = guildRankList[camp][i].second;
		int rankNum = i + 1;
		if (camp == 3)
		{
			guild->setRankInAll(rankNum);
		} else {
			guild->setRankInCamp(rankNum);
		}

		// viewResult += intTostring(rankNum);
		// viewResult += "," + guild->getName();
		// viewResult += intTostring(guild->getCamp());
		// viewResult += "," + guild->getPresident();
		// viewResult += intTostring(guild->getLevel());
		// viewResult += intTostring(guild->getCurMembs());
		sprintf(result + strlen(result), ",%s,%d,%d", guild->getName(), guild->getLevel(), guild->getCurMembs());
	}
	return 0;
	//guildRankList.size
}

/**
 * searchOneGuild - 搜索某个帮派
 * @guildName: 帮派名
 * @camp: 阵营，0为支派，1为宗教，2为游侠，3为所有阵营
 * Return: 没有查到该帮派，返回空字符串；查到该帮派返回该帮派的单条信息
 */
int searchOneGuild(char* guildName, int camp, char* result)
{
	if (guildName == NULL || result == NULL)
	{
		return 3;
	}
	// string viewResult;
	map<string, string>::iterator it_guildId;
#if 1	
	for (it_guildId = name_2_guildId.begin(); it_guildId != name_2_guildId.end(); it_guildId++)
	{
		char tempGuildName[32] = {0};
		strncpy(tempGuildName, it_guildId->first.c_str(), it_guildId->first.size() - 5);
		if (strstr(tempGuildName, guildName))
		{
			string guildId = it_guildId->second;
			map<string, Guild*>::iterator it;
			
			it = id_2_guild[camp].find(guildId);
			if (it == id_2_guild[camp].end())
			{
				continue;
			}
			
			Guild *guild = it->second;
			int rankNum;
			if (camp == 3)
			{
				rankNum = guild->getRankInAll();
			} else {
				rankNum = guild->getRankInCamp();
			}
			
			// viewResult += intTostring(rankNum);
			// viewResult += "," + guild->getName();
			// viewResult += intTostring(guild->getCamp());
			// viewResult += "," + guild->getPresident();
			// viewResult += intTostring(guild->getLevel());
			// viewResult += intTostring(guild->getCurMembs());
			sprintf(result + strlen(result), ",%d,%s,%d,%s,%d,%d", rankNum, guild->getName(), guild->getCamp(),
				guild->getPresident(), guild->getLevel(), guild->getCurMembs());
		}
	}
	
	if (strlen(result) == 0)
	{
		return 2;
	} else {
		return 0;
	}
#else
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return 1;
	}
	string guildId = it_guildId->second;
	map<string, Guild*>::iterator it;
	
	it = id_2_guild[3].find(guildId);
	if (it == id_2_guild[3].end())
	{
		return 2;
	}
	
	Guild *guild = it->second;
	int rankNum;
	if (camp == 3)
	{
		rankNum = guild->getRankInAll();
	} else {
		rankNum = guild->getRankInCamp();
	}
	
	// viewResult += intTostring(rankNum);
	// viewResult += "," + guild->getName();
	// viewResult += intTostring(guild->getCamp());
	// viewResult += "," + guild->getPresident();
	// viewResult += intTostring(guild->getLevel());
	// viewResult += intTostring(guild->getCurMembs());
	sprintf(result, ",%d,%s,%d,%s,%d,%d", rankNum, guild->getName(), guild->getCamp(),
		guild->getPresident(), guild->getLevel(), guild->getCurMembs());
	return 0;
#endif	
}

//string viewRankGuildRewardInfo(Hero *hero, int mode);
//查看自己帮派信息
int viewMyGuildInfo(Hero *hero, char *result)
{
	if (result == NULL)
	{
		return 2;
	}
	// string viewResult;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//自己没有帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	char guildNotices[1024] = {0};
	char guildQQGroup[300] = {0};
	char guildYYGroup[300] = {0};
	guild->getNotices(guildNotices, 0);
	guild->getNotices(guildQQGroup, 1);
	guild->getNotices(guildYYGroup, 2);
	// viewResult = guild->viewGuildInfo();
	// viewResult += guild->viewHeroInfo(hero->getIdentity());
	// viewResult += "," + guild->getNotices();
	// viewResult += viewRankGuildRewardInfo(hero, 0);
	// viewResult += viewRankGuildRewardInfo(hero, 1);
	guild->viewGuildInfo(result, title);
	guild->viewHeroInfo(hero->getIdentity(), result + strlen(result));
	sprintf(result + strlen(result), ",%s,%s,%s", guildNotices, guildQQGroup, guildYYGroup);
	viewRankGuildRewardInfo(hero, 0, result + strlen(result));
	viewRankGuildRewardInfo(hero, 1, result + strlen(result));
	char campTitle = guild->getCampTitle();
	int canGetReward = 0;
	//如果帮主是阵营统领
	if (campTitle & 0x1)
	{
		map<string, GuildReward_T>::iterator it_gr;
		int level = guild->getLevel();
		GuildReward_T *p_gr = NULL;
		it_gr = id_2_guildReward.find("campLeader");
		if (it_gr != id_2_guildReward.end())
		{
			p_gr = &it_gr->second;
			canGetReward = !(hero->dayLmtFindGroup.isOneItemFull("campLeaderReward") == 1);
			sprintf(result + strlen(result), ",%d,%d,%d,%d", canGetReward,
				p_gr->rewardSelfMoney[level - 1], p_gr->rewardGuildExp[level - 1], p_gr->rewardSelfGlory[level - 1]);
		} else {
			sprintf(result + strlen(result), ",0,0,0,0");
		}
	} else
	{
		sprintf(result + strlen(result), ",0,0,0,0");
	}
	
	if (campTitle & 0x2)
	{
		map<string, GuildReward_T>::iterator it_gr;
		int level = guild->getLevel();
		GuildReward_T *p_gr = NULL;
		it_gr = id_2_guildReward.find("campChief");
		if (it_gr != id_2_guildReward.end())
		{
			p_gr = &it_gr->second;
			canGetReward = !(hero->dayLmtFindGroup.isOneItemFull("campChiefReward") == 1);
			sprintf(result + strlen(result), ",%d,%d,%d,%d", canGetReward,
				p_gr->rewardSelfMoney[level - 1], p_gr->rewardGuildExp[level - 1], p_gr->rewardSelfGlory[level - 1]);
		} else {
			sprintf(result + strlen(result), ",0,0,0,0");
		}
	} else
	{
		sprintf(result + strlen(result), ",0,0,0,0");
	}
	return 0;
	
}

//查看某个帮派的信息
int viewOneGuildInfo(char* guildName, char *result)
{
	// string viewResult;
	if (guildName == NULL || result == NULL)
	{
		return 3;
	}
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return 1;
	}
	string guildId = it_guildId->second;
	
	map<string, Guild*>::iterator it;
	
	it = id_2_guild[3].find(guildId);
	if (it == id_2_guild[3].end())
	{
		return 2;
	}
	
	Guild *guild = it->second;
	char guildNotices[1024];
	guild->getNotices(guildNotices, 0);
	/* //viewResult += intTostring(guild->getRankNum());
	viewResult += "," + guild->getName();
	viewResult += intTostring(guild->getLevel());
	//viewResult += intTostring(guild->getCamp());
	viewResult += "," + guild->getPresident();
	viewResult += "," + guild->getVicePresident();
	viewResult += intTostring(guild->getCurMembs());
	viewResult += intTostring(guild->getMoney());
	viewResult += "," + guild->getNotices();
	//viewResult = guild->viewGuildInfo(); */
	sprintf(result, ",%s,%d,%s,%s,%d,%d,%s", guild->getName(), guild->getLevel(),
		guild->getPresident(), guild->getVicePresident(), guild->getCurMembs(),
		guild->getMoney(), guildNotices);
	return 0;
}

static bool isAllDigit(char *check)
{
	char *p = check;
	while (*p != 0)
	{
		if (*p < '0' || *p > '9')
		{
			return false;
		}
		p++;
	}
	return true;
}

//更改帮会公告
int changeNotices(Hero *manager, char* newNotices, int flag)
{
	if (newNotices == NULL)
	{
		return 4;
	}
	int title = manager->getGuildTitle();
	
	if (title != 0 && title != 1)
	{
		//不是帮主也不是副帮主，权限不够
		return 1;
	}
	if (flag == 0)
	{
		if (strlen(newNotices) > MAX_NOTICES_SIZE - 1)
		{
			//公告太长
			return 2;
		}
		
		if (isHaveDirtyWords(newNotices) == 1)
		{
			//公告中含有脏字
			
			return 3;
		}
	} else if (flag == 1 || flag == 2)
	{
		if (strlen(newNotices) > MAX_QY_GROUP_SIZE - 1)
		{
			return 2;
		}
		if (!isAllDigit(newNotices))
		{
			//qq群或yy群中含有非数字
			return 5;
		}
	}
	else {
		//flag err
		return 4;
	}
	
	Guild *guild = manager->getGuild();
	guild->setNotices(newNotices, flag);
	
	return 0;
	
}

//查看帮派历史记录
int viewGuildHistory(Hero *hero, int page, char *result)
{
	if (result == NULL)
	{
		return 2;
	}
	// string viewResult;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//自己没有帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	int ret = guild->viewHistory(page, result);
	return ret;
}

//得到帮派在对应阵营中的排名
int getGuildRankInCamp(char* guildId, int camp)
{
	if (guildId == NULL)
	{
		return -2;
	}
	for(int i = 0; i < guildRankList[camp].size(); i++)
	{
		if (guildRankList[camp][i].first == guildId)
		{
			return i + 1;
		}
	}
	//该阵营中没有这个帮
	cout<<"getGuildRankInCamp return is -1 because guildName is "<<guildId<<" camp is "<<camp<<endl;
	return -1;
} 

//得到帮主ID
char* getGuildPresidId(char* guildName)
{
	if (guildName == NULL)
	{
		return NULL;
	}
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return NULL;
	}
	string guildId = it_guildId->second;
	
	map<string, Guild*>::iterator it;
	it = id_2_guild[3].find(guildId);
	if (it == id_2_guild[3].end())
	{	
		return NULL;
	}
	
	return it->second->getPresidId();
}


//得到副帮主ID
char* getGuildVicePresidId(char* guildName)
{
	if (guildName == NULL)
	{
		return NULL;
	}
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return NULL;
	}
	// string guildId = it_guildId->second;
	
	map<string, Guild*>::iterator it;
	it = id_2_guild[3].find(it_guildId->second);
	if (it == id_2_guild[3].end())
	{	
		return NULL;
	}
	
	return it->second->getVicePresidId();
}

//花费帮派资金	--向慧明专用接口，这里就不检查是不是帮主副帮主身份。
int useGuildMoney(char* guildName, int value)
{
	if (guildName == NULL || value <= 0)
	{
		//value值有误
		return 1;
	}
	
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return 2;
	}
	string guildId = it_guildId->second;
	
	map<string, Guild*>::iterator it;
	it = id_2_guild[3].find(guildId);
	if (it == id_2_guild[3].end())
	{	
		//没有该帮派信息
		return 2;
	}
	
	Guild *guild = it->second;
	return guild->useMoney(value);
	
}

//查看帮派成员信息
int viewGuildMembsList(Hero *hero, char* result)
{
	if (result == NULL)
	{
		return 2;
	}
	// string viewResult;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//自己没有帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	int ret = guild->viewGuildMembsListInfo(result);
	return ret;
}

//查看申请成员列表
int viewGuildApplyList(Hero *hero, char* result)
{
	if (result == NULL)
	{
		return 2;
	}
	// string viewResult;
	
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//自己没有帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	int ret = guild->viewGuildApplyListInfo(result);
	return ret;
}

//增加帮派经验
int addGuildExp(char* guildName, char* heroId, int expVal)
{
	if (guildName == NULL || heroId == NULL)
	{
		return 0;
	}
	Guild *guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		return 0;
	}
	
	if (!guild->checkIsInGuild(heroId))
	{
		return 0;
	}
	
	int ret = guild->donateExp(heroId, expVal);
	return ret;
}

//增加个人帮贡
int addMyGuildGlory(char* guildName, char* heroId, int glory)
{
	if (guildName == NULL || heroId == NULL)
	{
		return 3;
	}
	
	Guild *guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		//帮派名没有对应的帮派
		return 1;
	}
	
	if (!guild->checkIsInGuild(heroId))
	{
		//玩家没有帮派
		return 2;
	}
	
	int ret = guild->addGloryOfHero(heroId, glory);
	int heroNowGlory = guild->getHeroTotalGlory(heroId);
	if (heroNowGlory > 10000)
	{
		Hero* hero = heroid_to_hero(heroId);
		if (hero != NULL)
		{
			hero->addTitle("T036");
		}
	}
	return ret;
}

//查看帮派活动
int viewGuildActivity(Hero *hero, char* result)
{
	if (result == NULL)
	{
		return 2;
	}
	// string viewMsg;
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//玩家没有自己的帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	int guildLevel = guild->getLevel();
	int state;			//-1:帮派等级不够参加帮派，0:不在帮派活动时间；1:可以参与
	map<string, GuildActivity*>::iterator iter;
	iter = id_2_guildAct.begin();
	// viewMsg = intTostring(id_2_guildAct.size());
	sprintf(result, ",%d", (int)id_2_guildAct.size());
	for(iter; iter != id_2_guildAct.end(); iter++)
	{
		GuildActivity* guildAct = iter->second;
		
		state = guildAct->isInGuildActTime();
		string actId = guildAct->getId();
		if (actId == "bphd_001")
		{
			state = (!hero->getGuildSigned());
		}
		
		int limitLevel = guildAct->getLevelLimit();
		if (limitLevel > guildLevel)
		{
			//帮派当前等级还不能参加该任务
			state = -1;
		}
		// viewMsg += "," + iter->first;
		// viewMsg += intTostring(state);
		sprintf(result + strlen(result), ",%s,%d", iter->first.c_str(), state);
	}
	
	return 0;
}

bool disBandOneGuild(Guild* guild, int camp, char* guildName)
{
	char* guildId = guild->getId();
	
	set<string> membsList = guild->getMembsList();
	set<string>::iterator it;
	it = membsList.begin();
	for (it; it != membsList.end(); it++)
	{
		string heroId = (*it);
		//角色id得到角色实例
		Hero *hero;
		map<string, Hero*>::iterator it_hero;
		it_hero = heroId_to_pHero.find(heroId);
		if(it_hero == heroId_to_pHero.end())
		{
			//可以不记录未处理事件，等玩家上来时更新时发现自己的帮派已经找不到了，就会清掉自己帮派数据
			cout<<"BisonTest can't find hero when disband guild"<<endl;
			continue;
		}
		hero = it_hero->second;
		cout<<"BisonTest Come here! to clear guild info"<<endl;
		char *heroGuildName = hero->getGuildName();
		if (!strcmp(heroGuildName, guildName))
		{
			hero->clrGuildInfo();				//清除玩家的帮派信息
			hero->clrGuildSkillAddTotal();		//只要一句话，把所有的帮派技能附加属性都清除了
		}
	}
	name_2_guildId.erase(guildName);
	id_2_guild[3].erase(guildId);
	id_2_guild[camp].erase(guildId);
	
	//帮派Id集合中叉掉该帮派
	existGuildIdSet.erase(guildId);
	//重新保存榜排名到memcached
	//saveAllGuildIdToMemc();
	//排行榜中也删除对应帮派
	vector<GuildSortItem>::iterator it_rank;
	
	//自己阵营排行榜中删除
	it_rank = guildRankList[camp].begin();
	for (it_rank; it_rank != guildRankList[camp].end(); it_rank++)
	{
		if ((*it_rank).first == guildId)
		{
			guildRankList[camp].erase(it_rank);
			break;
		}
	}
	
	//全阵营排行榜中删除
	it_rank = guildRankList[3].begin();
	for (it_rank; it_rank != guildRankList[3].end(); it_rank++)
	{
		if ((*it_rank).first == guildId)
		{
			guildRankList[3].erase(it_rank);
			break; 
		}
	}
	
	delete guild;
	//查看帮派某页排行榜信息返回
	char msg[2048];
	sprintf(msg, "12,1");
	int ret = viewGuildRankInfo(1, 3, msg + strlen(msg));
	
	send_msg(sock_fd, msg);
}

//解散帮派
bool disbandGuild(Hero *manager)
{
	char* managerId = manager->getIdentity();
	int managerTitle = manager->getGuildTitle();
	if (managerTitle != 0)
	{
		//不是帮主不能执行此操作
		return false;
	}
	
	char* guildName = manager->getGuildName();
	int camp = manager->getCamp();
	Guild* guild = manager->getGuild();
	disBandOneGuild(guild, camp, guildName);
	return true;
}

bool GM_disbandGuildByRank(int camp, int rank)
{
	if (camp < 0 || camp > 3)
	{
		return false;
	}
	
	if (rank < 1 || guildRankList[camp].size() < rank)
	{
		return false;
	}
	
	Guild *guild = guildRankList[camp][rank - 1].second;
	char *guildName = guild->getName();
	disBandOneGuild(guild, camp, guildName);
	return true;
	
}

bool GM_disbandGuildByName(char* guildName)
{
	if (guildName == NULL)
	{
		return false;
	}
	
	Guild* guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		return false;
	}
	int camp = guild->getCamp();
	
	disBandOneGuild(guild, camp, guildName);
	return true;
}

Guild *getGuildWithName(char* guildName)
{
	if (guildName == NULL || strlen(guildName) <= 0)
	{
		return NULL;
	}
	map<string, string>::iterator it_guildId;
	it_guildId = name_2_guildId.find(guildName);
	if (it_guildId == name_2_guildId.end())
	{
		return NULL;
	}
	// string guildId = it_guildId->second;
	
	map<string, Guild*>::iterator it;
	if (it_guildId->second.size() == 0)
	{
		return NULL;
	}
	it = id_2_guild[3].find(it_guildId->second);
	if (it == id_2_guild[3].end())
	{	
		return NULL;
	}
	return it->second;
}

Guild *getGuildWithId(char* guildId)
{
	if (guildId == NULL || strlen(guildId) <= 0)
	{
		return NULL;
	}
	map<string, Guild*>::iterator it;
	it = id_2_guild[3].find(guildId);
	if (it == id_2_guild[3].end())
	{	
		return NULL;
	}
	return it->second;
}

void saveOneGuildIdToMemc(char* guildId)
{
	// guildId += ",";					//后面加一个逗号，和之后的ID隔开
	char oneGuildId[IDL + 1] = {0};
	sprintf(oneGuildId, "%s,", guildId);
	int size = 0;
	int where = 0;
	// char* oldAllGuildId = mem_operate->get_mem_data(memcAllGuildIdKey, &size);
	char* oldAllGuildId = mem_group->get_data(mergeServerAllGuildIdKey, &size, &where, PUBLIC_MEMCACHED_INDEX);
	if (oldAllGuildId == NULL)
	{
		strncpy(allGuildIds, oneGuildId, strlen(oneGuildId) + 1);
		// bool isSuccess = mem_operate->set_mem_data(memcAllGuildIdKey.c_str(),
			// allGuildIds, sizeof(allGuildIds));
		bool isSuccess = mem_group->set_data(mergeServerAllGuildIdKey.c_str(),	allGuildIds, sizeof(allGuildIds), PUBLIC_MEMCACHED_INDEX);
		if (!isSuccess)
		{
			cout<<"BisonWarning: save one guildId to memcached failed!"<<endl;
		}
	}
	else
	{
		sprintf(allGuildIds, "%s%s", oldAllGuildId, oneGuildId);
		free(oldAllGuildId);
		// string newAllGuildId = oldAllGuildId;
		// newAllGuildId += guildId;
		// strncpy(allGuildIds, newAllGuildId.c_str(), newAllGuildId.size() + 1);
		// bool isSuccess = mem_operate->set_mem_data(memcAllGuildIdKey.c_str(), 
			// allGuildIds, sizeof(allGuildIds));
		bool isSuccess = mem_group->set_data(mergeServerAllGuildIdKey.c_str(),	allGuildIds, sizeof(allGuildIds), PUBLIC_MEMCACHED_INDEX);
		if (!isSuccess)
		{
			cout<<"BisonWarning: save many guildId to memcached failed!"<<endl;
		}
	}
}

//所有帮派名的存储
void saveAllGuildIdToMemc()
{
	//保存所有帮派名到memcached
	memset(allGuildIds, 0, sizeof(allGuildIds));
	set<string>::iterator iter;
	iter = existGuildIdSet.begin();
	for (iter; iter != existGuildIdSet.end(); iter++)
	{	
		sprintf(allGuildIds + strlen(allGuildIds), "%s,", (*iter).c_str());
	}
	// bool isSuccess = mem_operate->set_mem_data(memcAllGuildIdKey.c_str(), 
		// allGuildIds, sizeof(allGuildIds));
	bool isSuccess = mem_group->set_data(mergeServerAllGuildIdKey.c_str(), allGuildIds, sizeof(allGuildIds), PUBLIC_MEMCACHED_INDEX);
	if (!isSuccess)
	{
		cout<<"BisonWarning: save many guildId to memcached failed!"<<endl;
	}
	
}
//把帮派系统信息保存到memcached
void saveGuildSystemToMemc()
{
	//保存所有帮派详细信息到memcached
	saveAllGuildIdToMemc();
	map<string, Guild*>::iterator it_guild;
	for (it_guild = id_2_guild[3].begin(); it_guild != id_2_guild[3].end(); it_guild++)
	{
		//cout<<"BiosnShow in save all guildInfoData ****************************"<<endl;
		Guild *guild = it_guild->second;
		guild->memSet();
	}
}

//初始化所有存在的帮派
void initAllExistGuild()
{
	//当之前所有创建的帮派需要清除的时候就解开这里的注释，一次，只要一次，然后你再把它注释掉
	// string guildId = "";
	// mem_operate->set_mem_data(memcAllGuildIdKey.c_str(),
			// const_cast<char *>(guildId.c_str()), guildId.size());
	existGuildIdSet.clear();				//帮派ID集合清空
	int size = 0;
	int where = 0;
	
	char *allGuildIdSet = mem_group->get_data(mergeServerAllGuildIdKey, &size, &where, PUBLIC_MEMCACHED_INDEX);
	if (allGuildIdSet == NULL)
	{
		cout<<"BisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNO"<<endl;
		cout<<"BisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNO"<<endl;
		cout<<"BisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNOBisonFIndNO"<<endl;
//如果是合服版
#if defined(MERGE_SERVER_FIRST_VERSION)
		//合服前区的个数
		int memNumber = mem_group->number - 1;
		for (int memIndex = 1; memIndex <= memNumber; memIndex++)
		{
			allGuildIdSet = mem_group->get_data(memcAllGuildIdKey, &size, &where, memIndex);
			if (allGuildIdSet == NULL)
			{
				continue;
			}
			
			//各服接龙
			snprintf(allGuildIds + strlen(allGuildIds), sizeof(allGuildIds) - strlen(allGuildIds), "%s", allGuildIdSet);
			
			cout<<"long dragon allGuildIds is "<<allGuildIds<<endl;
			//逐服处理
			char tempAllGuildIds[51000] = {0};
			strcpy(tempAllGuildIds, allGuildIdSet);
			free(allGuildIdSet);
			allGuildIdSet = NULL;
			int pos = 0;
			char oneGuildId[IDL + 1] = {0};
			char *temp = tempAllGuildIds;
			int len = strlen(temp);
			while (len > 36)
			{
				pos = findChar(temp, ',', len);
				if (pos == -1)
				{
					strncpy(oneGuildId, temp, len);
					temp = temp + len;
				}
				else
				{
					sub_str(oneGuildId, temp, 0, pos);
					temp = temp + pos + 1;
				}
				len = strlen(temp);
				cout<<"oneGuildId is "<<oneGuildId<<endl;
				GuildInfoData_T *guildData = (GuildInfoData_T*)mem_group->get_data(oneGuildId, &size, &where, memIndex);
				if (guildData != NULL)
				{
					//是老帮派名，换新帮派名，并重新存
					if (isOldGuildName(guildData->name))
					{
						char tempName[51] = {0};
						sprintf(tempName, "%s[%03d]", guildData->name, memIndex);
						strncpy(guildData->name, tempName, sizeof(tempName));
						//这里先不删除，以备不成功还有回旋
						// mem_group->delete_data(oneGuildId, memIndex);
					}
					
					//存到公共缓存中
					mem_group->set_data(oneGuildId, (char*)guildData, sizeof(GuildInfoData_T), PUBLIC_MEMCACHED_INDEX);
					
					existGuildIdSet.insert(oneGuildId);
					Guild* newGuild = new Guild(*guildData);
					
					//释放掉缓存拿到的帮派数据
					free(guildData);
					
					int camp = newGuild->getCamp();
					string guildName = newGuild->getName();
					//帮派名查找帮派ID的map中加入该记录
					name_2_guildId.insert(pair<string, string>(guildName, oneGuildId));
					//所在阵营帮派集中加入该帮派
					id_2_guild[camp].insert(pair<string, Guild*>(oneGuildId, newGuild));
					//全部阵营的帮派集中加入该帮派
					id_2_guild[3].insert(pair<string, Guild*>(oneGuildId, newGuild));
					
					//新读到的帮派加载排行榜的最后
					guildRankList[camp].push_back(pair<string, Guild*>(oneGuildId, newGuild));//设置新帮派在阵营中的排名
					newGuild->setRankInCamp(guildRankList[camp].size());
					
					//全阵营排行榜中也加入该帮信息--加到最后
					guildRankList[3].push_back(pair<string, Guild*>(oneGuildId, newGuild));
					//设置帮派在所有已存中的排名
					newGuild->setRankInAll(guildRankList[3].size());
					
					idNum_2_guild.insert(pair<int, Guild*>(newGuild->getIdNum(), newGuild));
				}
			}
		}
#else
	return;
#endif
	} else {
		sprintf(allGuildIds, "%s", allGuildIdSet);
		// cout<<"BisonTest BisonTest BisonTest BisonTeset"<<endl;
		// cout<<"BisonTest BisonTest BisonTest BisonTeset"<<endl;
		// cout<<"BisonTest BisonTest BisonTest BisonTeset"<<endl;
		cout<<"allGuildIds is "<<allGuildIds<<endl;
		free(allGuildIdSet);
		//string allGuildId = allGuildIdSet;
		int pos = 0;
		char oneGuildId[IDL + 1] = {0};
		char *temp = allGuildIds;
		int len = strlen(temp);
		while (len > 36)
		{
			pos = findChar(temp, ',', len);
			if (pos == -1)
			{
				strncpy(oneGuildId, temp, len);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneGuildId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			// cout<<"BisonShow get guildId from memcached one guildId is "<<oneGuildId<<endl;
			GuildInfoData_T *guildData = (GuildInfoData_T*)mem_group->get_data(oneGuildId, &size, &where, PUBLIC_MEMCACHED_INDEX);
			if(guildData != NULL)
			{
				//帮派Id集合中加入该帮派
				existGuildIdSet.insert(oneGuildId);
				Guild* newGuild = new Guild(*guildData);
				free(guildData);
#if 1
				newGuild->cardingGuild();
				char *presidId = newGuild->getPresidId();
				int heroWhere = 1;
				MemHero *mem_data_hero = (MemHero*)mem_group->get_data(presidId, &size, &heroWhere);
				if (mem_data_hero != NULL)
				{
					if (mem_data_hero->heroGuildData.guildTitle == -1)
					{
						mem_data_hero->heroGuildData.guildTitle = 0;
						strncpy(mem_data_hero->heroGuildData.guildId, oneGuildId, sizeof(mem_data_hero->heroGuildData.guildId));
						mem_group->set_data(presidId, (char*)mem_data_hero, sizeof(MemHero), heroWhere);
					}
					free(mem_data_hero);
				}
#endif				
				int camp = newGuild->getCamp();
				string guildName = newGuild->getName();
				//帮派名查找帮派ID的map中加入该记录
				name_2_guildId.insert(pair<string, string>(guildName, oneGuildId));
				//所在阵营帮派集中加入该帮派
				id_2_guild[camp].insert(pair<string, Guild*>(oneGuildId, newGuild));
				//全部阵营的帮派集中加入该帮派
				id_2_guild[3].insert(pair<string, Guild*>(oneGuildId, newGuild));
				
				//新读入的帮派加载排行榜的最后
				guildRankList[camp].push_back(pair<string, Guild*>(oneGuildId, newGuild));//设置新帮派在阵营中的排名
				newGuild->setRankInCamp(guildRankList[camp].size());
				
				//全阵营排行榜中也加入该帮信息--加到最后
				guildRankList[3].push_back(pair<string, Guild*>(oneGuildId, newGuild));
				//设置帮派在所有已存中的排名
				newGuild->setRankInAll(guildRankList[3].size());
				
				idNum_2_guild.insert(pair<int, Guild*>(newGuild->getIdNum(), newGuild));
			}
		}
	}
	
	//重新把无异常的帮派ID存入缓存
	saveAllGuildIdToMemc();
	//初始化完后对所有帮派重新进行一次排名
	allGuildRank();

}

//查看一个阵营中的帮主列表
int viewAllPresidInCamp(int camp, char *result)
{
	if (result == NULL)
	{
		return 1;
	}
	// string viewMsg;
	int size = guildRankList[camp].size();
	// viewMsg += intTostring(size);
	sprintf(result, ",%d", size);
	for (int i = 0; i < size; i++)
	{
		Guild *guild = guildRankList[camp][i].second;
		//viewMsg += guild->viewPresidInfo();
		guild->viewPresidInfo(result + strlen(result));
	}
	return 0;
}

//查看帮主或副帮主昵称
char* viewGuildPresidNick(int flag, char* guildName)
{
	if (guildName == NULL)
	{
		return NULL;
	}
	// string viewResult;
	Guild *guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		return NULL;
	}
	
	return guild->getPresidNickName(flag);
}

void sendGuildMsg(char* guildName, char* msg)
{
	if (guildName == NULL || msg == NULL)
	{
		return;
	}
	Guild *guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		return;
	}
	
	Hero *hero = NULL;
	// char* heroId;
	set<string> membsList = guild->getMembsList();
	set<string>::iterator it = membsList.begin();
	for(it; it != membsList.end(); it++)
	{
		// heroId = (*it).c_str();
		
		//角色id得到角色实例
		map<string, Hero*>::iterator it_hero;
		it_hero = heroId_to_pHero.find((*it));
		if(it_hero == heroId_to_pHero.end())
		{
			//不在线的就不发
			continue;
		}
		hero = it_hero->second;
		if (hero != NULL)
		{
			send_msg(hero->getFd(), msg);
		}
	}
}

//邀请加入帮派
int inviteJoinGuild(Hero* manager, char *heroId)
{
	int title = manager->getGuildTitle();
	
	if (title != 0 && title != 1)
	{
		//不是帮主也不是副帮主，权限不够
		return 1;
	}
	
	Guild *guild = manager->getGuild();
	
	return 0;
}

//系统请客 吃饭
void systemTreatGuild(Map_Inform *mapNow,char *typeId,char *guildId)
{
	cout<<" systemTreatGuild fun begin:"<<endl;
	
	if (mapNow==NULL||typeId==NULL||guildId==NULL)
	{
		return;
	}
	
	cout<<" systemTreatGuild fun mid:"<<endl;
	
	Guild *guild=getGuildWithId(guildId);
	if (guild==NULL)
	{
		return;
	}
	else
	{
		guild->systemTreat(mapNow,typeId);
	}
	cout<<" systemTreatGuild fun end:"<<endl;
}

//判断guildName是否是老的帮派名（内部只做是否判断，guildName合法性判断请在调用之前做）
bool isOldGuildName(char* guildName)
{
	for (int i = 0; *guildName != 0; i++)
	{
		//新帮派名有"[区号]"作后缀，区号是三位数，不够三位前补0
		if (*guildName++ == '[')
		{
			if (*guildName && *(guildName + 1) && *(guildName + 2) && *(guildName + 3) == ']')
			{
				return false;
			}
		}
	}
	return true;
}

void viewFreshGuildTaskInfo(Hero* hero, char* result)
{
	Guild* guild = hero->getGuild();
	if (guild != 0)
	{
		int refreshGuildTaskTime = guild->getRefreshGuildTaskTime();
		int remainFreshTimes = 4 - refreshGuildTaskTime;
		if (remainFreshTimes > 0)
		{
			int needGold = 500 * (1 << refreshGuildTaskTime);
			sprintf(result + strlen(result), ",%d,%d", remainFreshTimes, needGold);
			return;
		}
	}
	
	sprintf(result + strlen(result), ",0,0");
}

int refreshGuildTaskForAll(Hero* hero)
{
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//自己没有帮派
		return 1;
	}
	
	Guild *guild = hero->getGuild();
	
	int refreshGuildTaskTime = guild->getRefreshGuildTaskTime();
	if (refreshGuildTaskTime > 4)
	{
		return 2;
	}
	
	int guildLevel = guild->getLevel();
	
	int needGold = 10 * (20 + 5 * (guildLevel - 1)) * (1 << refreshGuildTaskTime);
	
	if (!useGold(hero, 500))
	{
		return 3;
	}
	
	guild->refreshGuildTask();
	
	char refreshMsg[1024] = {0};
	sprintf(refreshMsg, "12,36");
	// char* heroId;
	set<string> membsList = guild->getMembsList();
	set<string>::iterator it = membsList.begin();
	for(it; it != membsList.end(); it++)
	{
		Hero *tempHero = heroid_to_hero(*it);
		if (tempHero == NULL)
		{
			continue;
		}
		tempHero->refreshGuildTask();
		guild->clrHeroRefreshTaskNeed(tempHero->getIdentity());
		send_msg(tempHero->getFd(), refreshMsg);
	}
	
	return 0;
}

#if defined(SORT_WITH_PRIO_QUE)
priority_queue<Guild*, vector<Guild*>, CompGuild> GuildPQ;
void RankGuildPQ(Guild *guild)
{
	GuildPQ.push(guild);
}
#endif
