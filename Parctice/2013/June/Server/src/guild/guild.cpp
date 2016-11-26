/****************************************************************
 * Filename: guild.cpp
 * 
 * Description: 帮派
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/

#include"guild.h"
#include<cstdlib>
#include<ctime>
#include"command_other_function_all_over.h"
#include"my_time.h"
#include "my_memcached.h"
#include "my_mem_group.h"

//#define GUILD_TEST

//每个帮派都要用到的公共数据
#ifndef GUILD_CONST
#define GUILD_CONST

//guild test模式
#if defined(GUILD_TEST)
const int upgradeNeedExp[4] = {100, 200, 400, 600};
//帮派升级需要金钱
const int upgradeNeedMoney[4] = {200000, 400000, 600000, 800000};
//帮派升级需要帮贡
const int upgradeNeedGlory[4] = {90, 120, 150, 200};
#else
//帮派升级需要经验(upgradeNeedExp[0]表示由1级帮会升到2级帮会需要的经验)
const int upgradeNeedExp[5] = {195000, 812500, 2340000, 5460000, 5460000};
//帮派升级需要金钱
const int upgradeNeedMoney[5] = {2500000, 4500000, 7000000, 10000000, 10000000};
//帮派升级需要帮贡
const int upgradeNeedGlory[5] = {9000, 45000, 126000, 288000, 288000};
#endif

//技能消耗帮贡的基数(skillNeedGloryBase[0]表示第一个技能需要升级时需要消耗的帮贡基数)
const int skillNeedGloryBase[10] = {3, 3, 3, 3, 5, 5, 5, 5, 6, 6};

#endif

Guild_Skill_T global_guild_skill[10];

//缓存组
extern MyMemGroup* mem_group;

void Guild::memSet(void)
{
    bool isSuccess = mem_group->set_data(guildInfoData.id, (char*)&guildInfoData, (int)sizeof(guildInfoData), PUBLIC_MEMCACHED_INDEX);
    if(isSuccess == true)
    {
        // cout<<"set guildInfoData into memcached server success"<<endl;
    } else
    {
        // cout<<"set guildInfoData into memcached server failure"<<endl;
    }

}
//帮派编号暂时从10000开始计数
int Guild::count = 10000;
/**
 * totalPages - 帮派排行榜总页数
 * 		totalPages[0] -- 支派阵营的帮派总页数
 * 		totalPages[1] -- 宗教阵营帮派的总页数
 * 		totalPages[2] -- 游侠阵营帮派的总页数
 * 		totalPages[3] -- 所有阵营帮派的总页数
 */
int Guild::totalPages[4] = {1,1,1,1};

//帮会构造
Guild::Guild(char* guildId, char* _name, char* heroId, char* nickName, char* party, int heroLevel, int _camp, int _level)
{
	membsInfoArrFindMap.clear();
	applyArrFindMap.clear();
	int idNum = ++count;					//帮派编号加1
	guildInfoData.guildInfoDataInit(guildId, _name, heroId, nickName, party, heroLevel, _camp, _level, idNum);
	setCanOpenSkill();					//设置当前等级能激活的技能
	membsInfoArrFindMap.insert(pair<string, int>(heroId, guildInfoData.firstFree_MI));
	guildInfoData.addOneMemb(0, heroLevel, heroId, nickName, party, 0);
	guildFeastMap.clear();
	//设置帮派战未参与帮派战标志
	setJoinGuildWar(false);
	memSet();
}

//从memcache上来数据还原帮派
Guild::Guild(GuildInfoData_T newGuildMemData)
{
	memcpy(&guildInfoData, &newGuildMemData, sizeof(GuildInfoData_T));
	for (int i = 0; i < MAX_GUILD_MEMBS; i++)
	{
		if (guildInfoData.applyArr[i].flag == GUILD_USED_FLAG)
		{
			applyArrFindMap.insert(pair<string, int>(guildInfoData.applyArr[i].heroId, i));
		}
		if (guildInfoData.membsInfoArr[i].flag == GUILD_USED_FLAG)
		{
			membsInfoArrFindMap.insert(pair<string, int>(guildInfoData.membsInfoArr[i].heroId, i));
		}
	}
	
	//设置帮派战未参与帮派战标志
	setJoinGuildWar(false);
	guildInfoData.limitMembs = 15 + guildInfoData.level * 5;
	// guildInfoData.limitMembs = 60;
	guildFeastMap.clear();
}

void Guild::cardingGuild()
{
	map<string, int>::iterator it_mem = membsInfoArrFindMap.begin();
	for (it_mem; it_mem != membsInfoArrFindMap.end(); it_mem++)
	{
		if (heroid_to_hero(it_mem->first) == NULL)
		{
			if (guildInfoData.membsInfoArr[it_mem->second].online == 0 || guildInfoData.membsInfoArr[it_mem->second].online == 1)
			{
				guildInfoData.membsInfoArr[it_mem->second].online = MY_TV_SEC - 86400;
			}
		}
	}
}


int Guild::applyJoin(char* heroId, char* nickName, char* party, int heroLevel)
{
	if (applyArrFindMap.find(heroId) != applyArrFindMap.end())
	{
		//已经在申请列表中
		return -1;
	}
	int index = guildInfoData.firstFree_AP;
	
	//如果申请列表达到最大数，新加入的就要顶去最早加入的
	if (index == GUILD_END_FLAG)
	{
		char oldHeroId[IDL + 1];
		memset(oldHeroId, 0, sizeof(oldHeroId));
		guildInfoData.delOneApply(guildInfoData.applyHead, oldHeroId);
		applyArrFindMap.erase(applyArrFindMap.find(oldHeroId));
	}
	
	index = guildInfoData.addOneApply(heroId, nickName, party, heroLevel);
	applyArrFindMap.insert(pair<string, int>(heroId, index));
	memSet();
	return 0;
}

//移除申请列表中的一个玩家，返回值表明列表中是否存在该id
bool Guild::removeOneApply(char* heroId)
{
	map<string, int>::iterator it;
	it = applyArrFindMap.find(heroId);
	if (it == applyArrFindMap.end())
	{
		return false;
	}
	
	int index = it->second;
	applyArrFindMap.erase(it);
	char oldHeroId[IDL + 1];
	guildInfoData.delOneApply(index, oldHeroId);
	memSet();
	return true;
}

void Guild::removeAllApply(void)
{
	guildInfoData.initApply();
	applyArrFindMap.clear();
	memSet();
}

int Guild::join(char* heroId, char* nickName, char* party, int heroLevel, unsigned online)
{
	if (membsInfoArrFindMap.find(heroId) != membsInfoArrFindMap.end())
	{
		//已经加入帮会
		return -1;
	}
	
	if (guildInfoData.curMembs >= guildInfoData.limitMembs)
	{
		//帮会成员数达到上限
		return -2;
	}
	//成员数加1，这一步肯定能成功,肯定在线
	int index = guildInfoData.addOneMemb(5, heroLevel, heroId, nickName, party, online);
	if (index == GUILD_END_FLAG)
	{
		cout<<"BisonTest: you can't see this when pull one membs into guild!"<<endl;
	}
	membsInfoArrFindMap.insert(pair<string, int>(heroId, index));
	memSet();
	
	return 0;
}

void Guild::exit(char* heroId)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//不一定是玩家自己出去，有可能是被踢的，这样帮派实例不是根据他来找的，要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		//帮会中没有该成员
		return;
	}
	int index = it->second;
	guildInfoData.delOneMemb(index);		//从成员信息表删除
	membsInfoArrFindMap.erase(heroId);			//从查找表删除
	memSet();
}

void Guild::addMoney(int val)
{
	if (val > 0)
	{
		if (guildInfoData.money + val < 0)
		{
			guildInfoData.money = INT_MAX;
		} else {
			guildInfoData.money += val;
		}
	}
}

bool Guild::addExp(int val)
{
	if (guildInfoData.level >= 5)
	{
		return false;
	}
	if (val <= 0)
	{
		return false;
	}
	int level = guildInfoData.level;
	if (guildInfoData.expNow >= upgradeNeedExp[level - 1])
	{
		//经验到了不再增加
		return false;
	}
#if 0
	if (expNow + val > upgradeNeedExp[level - 1])
	{
		expNow = upgradeNeedExp[level - 1];
	
	} else {
		expNow += val;
		
	}
#endif	
	// guildInfoData.expNow += val;			//经验值可以比升级所需高一点，因此不做判断
	if (guildInfoData.expNow + val > upgradeNeedExp[level - 1]
		|| guildInfoData.expNow + val < 0)
	{
		guildInfoData.expNow = upgradeNeedExp[level - 1];
	} else {
		guildInfoData.expNow += val;
	}
	return true;
}

void Guild::addGlory(int val)
{
	if (val <= 0)
	{
		return;
	}
	
	guildInfoData.glory += val;
}

bool Guild::useMoney(int val)
{
	if (val <= 0)
	{
		return false;
	}
	
	if (guildInfoData.money < val)
	{
		return false;
	}
	
	guildInfoData.money -= val;
	return true;
}

bool Guild::useGlory(int val)
{
	if (val <= 0)
	{
		return false;
	}
	
	if (guildInfoData.glory < val)
	{
		return false;
	}
	
	guildInfoData.glory -= val;
	return true;
}

void Guild::setPresident(char* heroId, char* nickName)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		return;
	}
	
	//string presidName = guildInfoData.presidName;
	if (!strcmp(guildInfoData.presidName, "\0"))
	//if (presidName.size() != 0)
	{
		//帮主还在位
		return;
	}
	
	int index = it->second;
	strcpy(guildInfoData.presidName, nickName);
	strcpy(guildInfoData.presidId, heroId);
	guildInfoData.membsInfoArr[index].title = 0;
	memSet();
}

//任命副帮主
bool Guild::setVicePresident(char* heroId, char* nickName)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		cout<<"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"<<endl;
		cout<<"Guild no this hero when set vicePresid!!!!!!!"<<endl;
		return false;
	}
	
	//string vicePresidName = guildInfoData.vicePresidName;
	
	//if (vicePresidName.size() != 0)
	if (strlen(guildInfoData.vicePresidName) != 0)
	{
		//有副帮主还在位
		cout<<"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<endl;
		cout<<"there is still a vicePresid here when set vicePresid"<<endl;
		return false;
	}
	
	int index = it->second;
	strcpy(guildInfoData.vicePresidName, nickName);
	cout<<"guildInfoData.presidName is "<<guildInfoData.presidName<<endl;
	strcpy(guildInfoData.vicePresidId, heroId);
	cout<<"guildInfoData.presidId "<<guildInfoData.presidId<<endl;
	guildInfoData.membsInfoArr[index].title = 1;
	cout<<"index is "<<index<<endl;
	cout<<"guildInfoData.membsInfoArr[index].title "<<guildInfoData.membsInfoArr[index].title<<endl;
	memSet();
	return true;
}
//任命高层
//调用此接口前请确认heroId对应的hero没有职务,所要任命的职位也为空缺
void Guild::setManager(char* heroId, char* nickName, int title)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		return;
	}
	int index = it->second;
	if (index == GUILD_END_FLAG || index < 0 || index >= guildInfoData.limitMembs)
	{
		return;
	}
	
	if (title == 0)
	{
		strcpy(guildInfoData.presidName, nickName);
		strcpy(guildInfoData.presidId, heroId);
		guildInfoData.membsInfoArr[index].title = 0;
		
	} else if (title == 1) {
		strcpy(guildInfoData.vicePresidName, nickName);
		strcpy(guildInfoData.vicePresidId, heroId);
		guildInfoData.membsInfoArr[index].title = 1;
	}
	memSet();
}

//管理者卸任
bool Guild::managerRetired(char* heroId, int title)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		cout<<"##############Guild find no this membs!!!"<<endl;
		if (strcmp(guildInfoData.vicePresidId, heroId) == 0)
		{
			memset(guildInfoData.vicePresidName, 0, sizeof guildInfoData.vicePresidName);
			memset(guildInfoData.vicePresidId, 0, sizeof guildInfoData.vicePresidId);
		}
		return false;
	}
	int index = it->second;
	if (index == GUILD_END_FLAG || index < 0 || index >= guildInfoData.limitMembs)
	{
		cout<<"##############Guild this membs index isn't correct!!!"<<endl;
		if (strcmp(guildInfoData.vicePresidId, heroId) == 0)
		{
			memset(guildInfoData.vicePresidName, 0, sizeof guildInfoData.vicePresidName);
			memset(guildInfoData.vicePresidId, 0, sizeof guildInfoData.vicePresidId);
		}
		return false;
	}
	
	int managerTitle = guildInfoData.membsInfoArr[index].title;

	if (managerTitle == 0)
	{
		strcpy(guildInfoData.presidName, "");
		strcpy(guildInfoData.presidId, "");
		
	} else if (managerTitle == 1) {
		strcpy(guildInfoData.vicePresidName, "");
		strcpy(guildInfoData.vicePresidId, "");
	
	} else {
		return false;
	}
	
	//前面的那个，职位为帮众了
	guildInfoData.membsInfoArr[index].title = 5;
	memSet();
	return true;
	
}

void Guild::changeMembsInfo(char* heroId, int order, int val)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	
	//调用前要保证heroId在帮派中，index范围为0~25, val 不为负数
	if (val < 0 || order < 0 || order > 24 || it == membsInfoArrFindMap.end())
	{
		return;
	}
	
	int index = it->second;
	
	int *p = (int *)&(guildInfoData.membsInfoArr[index]);
	
	*(p + order) += val;
	memSet();
	
}

char* Guild::getPresident()
{
	return guildInfoData.presidName;
}

char* Guild::getVicePresident()
{
	return guildInfoData.vicePresidName;
}

//查帮主ID
char* Guild::getPresidId()
{
	return guildInfoData.presidId;
}

//查副帮主ID
char* Guild::getVicePresidId()
{
	return guildInfoData.vicePresidId;
}
	
//解散的时候会用
//如果hero下保存职位属性，要进行遍历，把hero所有涉及帮派的东西清除
Guild::~Guild()
{
	applyArrFindMap.clear();
	membsInfoArrFindMap.clear();
	// mem_operate->delete_mem_data(guildInfoData.id);
	mem_group->delete_data(guildInfoData.id, PUBLIC_MEMCACHED_INDEX);
}

//随机一个区间内的整数
static int randMyNum(int max, int min)
{
	int rank = max - min + 1;
	int val = min + rand() % rank;
	return val;
}

//获取签到奖励，mode表明是否使用道具
int Guild::getSignInReward(char* heroId, char* nickName, int mode, char *result)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		return -1;
	}
	int index = it->second;
	if (index == GUILD_END_FLAG || index < 0 || index >= guildInfoData.limitMembs)
	{
		return -2;
	}
	int incExp, incGlory;
	//string reward;					//返回给玩家看的
	//至于他是否签到过，就要在外面判断了，为的是避免他一天之内到处串帮赚签到奖励
	//随机个种子
	//srand(MY_TV_USEC + MY_TV_SEC);
	int level = guildInfoData.level;
	map<string, GuildReward_T>::iterator it_gr;
	int brandType = 0;
	GuildReward_T *p_gr;
	if (mode == 0)
	{
		//普通签到
		it_gr = id_2_guildReward.find("guildNormSign");
		p_gr = &it_gr->second;
		incExp = p_gr->rewardGuildExp[level - 1];
		incGlory = p_gr->rewardGuildGlory[level - 1];
		brandType = p_gr->brandType;
		
	} else if (mode == 1) {
		//使用道具的就多给点
		it_gr = id_2_guildReward.find("guildGoldSign");
		p_gr = &it_gr->second;
		incExp = p_gr->rewardGuildExp[level - 1];
		incGlory = p_gr->rewardGuildGlory[level - 1];
		brandType = p_gr->brandType;
	}
	
	addExp(incExp);
	//expNow += incExp;
	guildInfoData.glory += incGlory;
	int contb = guildInfoData.membsInfoArr[index].doubleReward(incGlory, incExp);
	guildInfoData.totalContb += contb;
	//reward = intTostring(incExp) + intTostring(incGlory) + intTostring(contb);
	sprintf(result, ",%d,%d,%d", incExp, incGlory, contb);
	//生成日志：”XXX普通签到（使用道具签到），获得incExp经验incGlory帮贡incMoney金钱，为帮派做成contb点贡献.“
	makeHistory(2, brandType, heroId, nickName, incExp, incGlory, contb);
	memSet();
	return 0;
}

//获取帮派活动奖励, index是帮派任务下标
int Guild::getTaskReward(char* heroId, char* nickName, GuildReward_T* p_guildReward, float rewardTimes, char *result)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	//因为指定的是另外一个角色，需要判断他是不是本帮的
	if (it == membsInfoArrFindMap.end())
	{
		return -1;
	}
	int arrIndex = it->second;
	if (arrIndex == GUILD_END_FLAG || arrIndex < 0 || arrIndex >= guildInfoData.limitMembs)
	{
		return -2;
	}

	int incExp, incGlory;
	//string reward;					//返回给玩家看的信息
	int level = guildInfoData.level;
	incExp = p_guildReward->rewardGuildExp[level - 1] * rewardTimes;
	incGlory = p_guildReward->rewardGuildGlory[level - 1] * rewardTimes;
	
	addGlory(incGlory);
	addExp(incExp);
	int contb = guildInfoData.membsInfoArr[arrIndex].doubleReward(incGlory, incExp);
	guildInfoData.totalContb += contb;
	int incMoney = p_guildReward->rewardSelfMoney[level -1] * rewardTimes;
	//reward = intTostring(incExp) + intTostring(incGlory) + intTostring(incMoney);
	//char rewd[60];
	//sprintf(rewd, "完成帮派任务，获得%d帮贡,为帮派做出了%d贡献。", incGlory, contb);
	//reward = rewd;
	//sprintf(result, "完成帮派任务，为帮派增长%d经验，获得%d帮派/自身帮贡值,为帮派做出了%d贡献。", incExp, incGlory, contb);
	char warnId[32] = {0};
	sprintf(warnId, "xf%03d", 17 + p_guildReward->brandType);
	sprintf(result, "%s,5,1,%s,%s,0,0,3,%d,0,0,0,3,%d,0,0,0,3,%d,0,0,0,3,%d,0,0,0",warnId, nickName, heroId,
		incExp, incGlory, incMoney, contb);
	//生成帮派日志："XXX完成帮派任务index,使帮会增加incExp经验，incGlory帮贡，incMoney金钱，为帮会做出contb贡献。"
	makeHistory(1, p_guildReward->brandType, heroId, nickName, incExp, incGlory, incMoney, contb);
	memSet();
	return 0;
}

//玩家捐献游戏币
int Guild::donateMoney(char* heroId, int val)
{
	//游戏币够不够是外面判断的
	guildInfoData.money += val;
	int index = membsInfoArrFindMap.find(heroId)->second;
	int contb = guildInfoData.membsInfoArr[index].donate(val, 0);
	guildInfoData.totalContb += contb;
	memSet();
	return contb;
}

//玩家捐献glory
int Guild::donateGlory(char* heroId, int val)
{
	int index = membsInfoArrFindMap.find(heroId)->second;
	//先确定玩家有这么多glory
	int *p = (int *)&guildInfoData.membsInfoArr[index];
	if (*(p + GLORY) < val)
	{
		//玩家的glory不够
		return -1;
	}
	
	//帮派的加上
	guildInfoData.glory += val;
	//玩家的扣除
	int contb = ((MembInfo_T *)p)->donate(val, 1);
	guildInfoData.totalContb += contb;
	memSet();
	return contb;
}

//贡献帮派经验,返回玩家获得的帮派贡献度
int Guild::donateExp(char* heroId, int val)
{
	int index = membsInfoArrFindMap.find(heroId)->second;
	if (val < 0)
	{
		return 0;
	}
	MembInfo_T *p = &guildInfoData.membsInfoArr[index];
	//帮派的加上增加的经验
	addExp(val);
	//玩家贡献帮派经验
	int contb = p->donate(val, 2);
	guildInfoData.totalContb += contb;
	memSet();
	return contb;
}

//日贡献或周贡献排名,只要找前9名，就用冒泡排序
//mode为0为日排名，mode为1是周排名
void Guild::rankInGuild(int mode)
{
	if (membsInfoArrFindMap.size() != guildInfoData.curMembs)
	{
		return;
	}
	
	int *p[MAX_GUILD_MEMBS], i;
	map<string, int>::iterator it;
	

	for (i = 0, it = membsInfoArrFindMap.begin(); i < guildInfoData.curMembs && it != membsInfoArrFindMap.end(); i++, it++)
	{
		//强转结构体为int*
		p[i] = (int *)&guildInfoData.membsInfoArr[it->second];
		
	}
	
	//冒泡了
	int *temp, flag, j = 0;
	int Item;
	//看是日排名还是周排名
	//Item = (mode == 0) ? DAYCONTB : WEEKCONTB;  //周排名改成按总贡献度排了
	Item = (mode == 0) ? DAYCONTB : TOTALCONTB;
	//只要求前9名，冒泡最合算，少于9n次
	int maxRank = (guildInfoData.curMembs > 9) ? 9 : guildInfoData.curMembs;
	for(i = 0; i < maxRank; i++)
	{
		for(j = guildInfoData.curMembs - 1; j != i; j--)
		{
			if (*(p[j] + Item) > *(p[i] + Item))
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
		
	}
	
	//生成排名队列
	/* if (mode == 0)
	{
		dayRankList.clear();		//清除之前的排名
		for (i = 0; i < curMembs; i++)
		{	
			dayRankList.push_back(((MembInfo_T*)p[i])->heroId);
			((MembInfo_T*)p[i])->dayRanking = ((i > 8) ? 9 : i) + 1;
		}
		
	} else if (mode == 1) {
		weekRankList.clear();		//清除之前的排名
		for (i = 0; i < curMembs; i++)
		{
			weekRankList.push_back(((MembInfo_T*)p[i])->heroId);
			((MembInfo_T*)p[i])->weekRanking = ((i > 8) ? 9 : i) + 1;
		}
	} */	
	
	//这样才叫一个快
	for (int i = 1; i <= maxRank; i++)
	{
		//第10名之前名次
		*(p[i - 1] + DAYRANKING + mode) = i;		*(p[i - 1] + DAYCONTB + mode) = 0;
		// if (mode == 0)
		// {
			// ((MembInfo_T*)p[i - 1])->dayRanking = i;
			// //日贡献度还是周贡献度排名用后就清零
			// ((MembInfo_T*)p[i - 1])->dayContb = 0;
		// }
		// else if (mode == 1)
		// {
			// ((MembInfo_T*)p[i - 1])->weekRanking = i;
			// ((MembInfo_T*)p[i - 1])->weekContb = 0;
		// }
	}
	i = i + 1;
	
	for (;i <= guildInfoData.curMembs; i++)
	{
		if(!p[i - 1]){
			continue;
		}
		if (mode == 0)
		{
			((MembInfo_T*)p[i - 1])->dayRanking = 10;
			//日贡献度还是周贡献度排名用后就清零
			((MembInfo_T*)p[i - 1])->dayContb = 0;
		}
		else if (mode == 1)
		{
			((MembInfo_T*)p[i - 1])->weekRanking = 10;
			((MembInfo_T*)p[i - 1])->weekContb = 0;
		}
	}
	
	if (mode == 0)
	{
		resetRefreshGuildTaskTime();
	}
	memSet();
}

//获取排名奖励，ranking为玩家对应排名，flag表明是日排名还是周排名
void Guild::getRankReward(char* heroId, int rewardGlory, int flag)
{
	if (rewardGlory <= 0)
	{
		return;
	}
	
	
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return;
	}
	int index = it->second;
	
	MembInfo_T* p = (MembInfo_T *)&guildInfoData.membsInfoArr[index];
	
	//增加的帮贡加到玩家帮会信息里
	p->oneReward(rewardGlory);
	
	//奖励都领了，排名也清了,以防他下次再领
	if (flag == 0)
	{
		p->dayRanking += 1000;
	} else if (flag == 1) {
		p->weekRanking += 1000;
	}
	//*((int *)p + DAYRANKING + flag) = 0;
	memSet();
	
}

//获取昨日或者上周名次
int Guild::getRankOrder(char* heroId, int mode)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -1;
	}
	int index = it->second;
	if (mode == 0)
	{
		return guildInfoData.membsInfoArr[index].dayRanking;
	} else {
		return guildInfoData.membsInfoArr[index].weekRanking;
	}
}

//帮派升级
int Guild::upgrade()
{
	int level = guildInfoData.level;
	//先审核下你升级的资本够不够
	if (guildInfoData.expNow < upgradeNeedExp[level - 1])
	{
		//经验不够
		return -1;
	}
	if (guildInfoData.money < upgradeNeedMoney[level - 1])
	{
		//资金不够
		return -2;
	}
	if (guildInfoData.glory < upgradeNeedGlory[level - 1])
	{
		//繁荣度不够
		return -3;
	}
	
	//可以升级
	guildInfoData.expNow -= upgradeNeedExp[level - 1];
	guildInfoData.money -= upgradeNeedMoney[level - 1];
	guildInfoData.glory -= upgradeNeedGlory[level - 1];
	
	//这可是1级1级的升，一次别想升多级
	guildInfoData.level++;
	setCanOpenSkill();				//设置当前等级能激活的技能
	if (level <= 5)
	{
		guildInfoData.limitMembs = 15 + guildInfoData.level * 5;
	} else {
	}
	
	memSet();
	//升级成功
	return 0;
}

//帮派阵营
int Guild::getCamp()
{
	return guildInfoData.camp;
}

//返回帮派等级
int Guild::getLevel()
{
	return guildInfoData.level;
}

int Guild::getMoney()
{
	return guildInfoData.money;
}

int Guild::getGlory()
{
	return guildInfoData.glory;
}

int Guild::getExp()
{
	return guildInfoData.expNow;
}

int Guild::getTotalContb()
{
	return guildInfoData.totalContb;
}

//获取帮派当前人数
int Guild::getCurMembs()
{
	return guildInfoData.curMembs;
}


//获取在所有帮派中的排名
int Guild::getRankInAll()
{
	return guildInfoData.rankInAll;
}

//获取在阵营内的排名
int Guild::getRankInCamp()
{
	return guildInfoData.rankInCamp;
}
	
int Guild::getIdNum()
{
	return guildInfoData.idNum;
}

char* Guild::getName()
{
	return guildInfoData.name;
}

char* Guild::getId()
{
	return guildInfoData.id;
}

bool Guild::getNotices(char *result, int flag)
{
	int k = 0;
	char msg[1024] = {0};
	if (result == NULL)
	{
		return false;
	}
	if (flag == 0)
	{
		for (int i = 0; i < MAX_NOTICES_SIZE - 1; i++)
		{
			if (guildInfoData.notices[i] == ',')
			{
				msg[k] = '\\';
				msg[++k]=':';
			} else {
				msg[k] = guildInfoData.notices[i];
			}
			k++;
		}
		strncpy(result, msg, strlen(msg));
		return true;
	} else if (flag == 1)
	{
		for (int i = 0; i < sizeof(guildInfoData.qqGroup) - 1; i++)
		{
			if (guildInfoData.qqGroup[i] == ',')
			{
				msg[k] = '\\';
				msg[++k]=':';
			} else {
				msg[k] = guildInfoData.qqGroup[i];
			}
			k++;
		}
		strncpy(result, msg, strlen(msg));
		return true;
	} else if (flag == 2)
	{
		for (int i = 0; i < sizeof(guildInfoData.yyGroup) - 1; i++)
		{
			if (guildInfoData.yyGroup[i] == ',')
			{
				msg[k] = '\\';
				msg[++k]=':';
			} else {
				msg[k] = guildInfoData.yyGroup[i];
			}
			k++;
		}
		strncpy(result, msg, strlen(msg));
		return true;
	}
	return false;
}

//设置在所有中的排名
void Guild::setRankInAll(int rankNum)
{
	guildInfoData.rankInAll = rankNum;
	memSet();
}

//设置帮派在阵营内的排名
void Guild::setRankInCamp(int rankNum)
{
	guildInfoData.rankInCamp = rankNum;
	memSet();
}

//更改帮会公告
void Guild::setNotices(char* newNotices, int flag)
{
	cout<<"[GuildShow] THe new notices to be changed is "<<newNotices<<endl;
	if (flag == 0)
	{
		memset(guildInfoData.notices, 0, MAX_NOTICES_SIZE);
		strcpy(guildInfoData.notices, newNotices);
	} else if (flag == 1)
	{
		memset(guildInfoData.qqGroup, 0, sizeof guildInfoData.qqGroup);
		strcpy(guildInfoData.qqGroup, newNotices);
	} else if (flag == 2)
	{
		memset(guildInfoData.yyGroup, 0, sizeof guildInfoData.yyGroup);
		strcpy(guildInfoData.yyGroup, newNotices);
	}
	memSet();
}

//设置技能可以激活
void Guild::setCanOpenSkill()
{
	if (guildInfoData.level == 2)
	{
		//2级可以激活1,2,3,4技能
		guildInfoData.openSkillFlag[0] = 0;
		guildInfoData.openSkillFlag[1] = 0;
		guildInfoData.openSkillFlag[2] = 0;
		guildInfoData.openSkillFlag[3] = 0;
	
	} else if (guildInfoData.level == 3) {
		//3级可以激活5,6,7,9技能
		guildInfoData.openSkillFlag[4] = 0;
		guildInfoData.openSkillFlag[5] = 0;
		guildInfoData.openSkillFlag[6] = 0;
		guildInfoData.openSkillFlag[7] = 0;
		
	} else if (guildInfoData.level == 4) {
		//4级可以激活8,10技能
		guildInfoData.openSkillFlag[8] = 0;
		guildInfoData.openSkillFlag[9] = 0;
	}
	memSet();
}

//开启帮派技能（只有副帮主以上的身份能开启放在外面判断，就不要heroId了）
int Guild::openSkill(int index)
{
	if (guildInfoData.openSkillFlag[index] == -1)
	{
		//该技能在该等级下不可开启
		return -1;
	}
	
	if (guildInfoData.openSkillFlag[index] == 1)
	{
		//该技能已经开启
		cout<<"233333333333333333333333333333333333333"<<endl;
		cout<<"233333333333333333333333333333333333333"<<endl;
		cout<<"index i s  is  is si s i "<<index<<endl;
		return -2;
	}
	
	//开启技能消耗
	// int moneyNeed = 12000 * (index + 1);
	int moneyNeed = global_guild_skill[index].openNeedGuildMoney;
	int gloryNeed = global_guild_skill[index].openNeedGuildGlory;
	// int gloryNeed = 40 *(index + 1);
	
	if (guildInfoData.money < moneyNeed)
	{
		//帮派资金不够
		return -3;
	}
	
	if (guildInfoData.glory < gloryNeed)
	{
		//帮派繁荣度不够
		return -4;
	}
	
	//扣去所需的资金和繁荣度
	guildInfoData.money -= moneyNeed;
	guildInfoData.glory -= gloryNeed;
	guildInfoData.openSkillFlag[index] = 1;
	
	//更改帮派内玩家的状态数据，表明玩家可学该技能
	map<string, int>::iterator it;
	for (it = membsInfoArrFindMap.begin(); it != membsInfoArrFindMap.end(); it++)
	{
		//把帮派内所有玩家的该技能置为0级，表示玩家可以学习该技能
		cout<<"BisonTest first in membsInfoArrFindMap is "<<it->first<<endl;
		int arrIndex = it->second;
		cout<<"BisonTest second in membsInfoArrFindMap is "<<arrIndex<<endl;
		guildInfoData.membsInfoArr[arrIndex].skillLevel[index] = 0;
	}
	memSet();
	return 0;
}

//升级帮派技能
int Guild::upgradeSkill(char* heroId, int index)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -1;
	}
	int arrIndex = it->second;
	MembInfo_T* p = (MembInfo_T *)&guildInfoData.membsInfoArr[arrIndex];
	if (p->skillLevel[index] > global_guild_skill[index].limit[guildInfoData.level])
	{
		//由于帮派等级限制，玩家还不能学习该技能
		return -1;
	}
	
	//计算学习技能需要消耗荣耀度
	// int gloryNeed = 2 * skillNeedGloryBase[index] * (p->skillLevel[index] + 1);
	int gloryNeed = global_guild_skill[index].upNeedGlory[p->skillLevel[index] + 1];
	if (!p->skillUpgrade(gloryNeed))
	{
		//glory不够扣
		return -2;
	}
	
	p->skillLevel[index] += 1;
	memSet();
	return 0;
}

//获取玩家的帮派技能等级
int Guild::getSkillLevel(char* heroId, int index)
{
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -1;
	}
	int arrIndex = it->second;
	return guildInfoData.membsInfoArr[arrIndex].skillLevel[index];
}

//查看玩家的帮派技能信息，如果是帮主副帮主要加上技能是否可以激活的标志
//至于技能是否可以升级，客户端是可以根据帮派等级和玩家等级进行判断的，
//服务器就不专门保存一个状态数组来告诉客户端是否可以升级，
//因为针对每个玩家都要添加的话，毕竟不是个小的量
int Guild::viewSkillInfo(char* heroId, bool managerFlag, char* result)
{
	int i;
	//string skillMsg;
	
	map<string, int>::iterator pos;
	pos = membsInfoArrFindMap.find(heroId);
	if(pos ==  membsInfoArrFindMap.end()){
		return 1;  //error
	}
	//以上代码benliao 2013.6.15加上保护，因为core了。
	
	int index = pos->second;
	MembInfo_T* p = (MembInfo_T *)&guildInfoData.membsInfoArr[index];
	int flag = 0;
	
	for (i = 0; i < 10; i++)
	{
		//skillMsg += intTostring(p->skillLevel[i]);
		sprintf(result + strlen(result), ",%d", p->skillLevel[i]);
		if (p->skillLevel[i] < 1)
		{
			flag = 1;
		}
	}
	
	//是副帮主以上身份可以看到当前技能是否可以开启
	if (managerFlag)
	{
		for (i = 0; i < 10; i++)
		{
			//skillMsg += intTostring((guildInfoData.openSkillFlag[i] > -1));
			sprintf(result + strlen(result), ",%d", (guildInfoData.openSkillFlag[i] > -1));
			// sprintf(result + strlen(result), ",%d", guildInfoData.openSkillFlag[i]);
		}
	}
	
	return flag;
}

//查看帮派的基本信息
int Guild::viewGuildInfo(char *result, int title)
{
	// string guildInfo;
	int level = guildInfoData.level;
	// guildInfo = charTostring(guildInfoData.name)			+ 
				// intTostring(level) 							+
				// charTostring(guildInfoData.presidName) 		+
				// charTostring(guildInfoData.vicePresidName) 	+
				// intTostring(guildInfoData.curMembs)			+
				// intTostring(guildInfoData.limitMembs)		+
				// intTostring(guildInfoData.money)			+
				// intTostring(guildInfoData.glory)			+
				// intTostring(guildInfoData.expNow)			+
				// intTostring(upgradeNeedExp[level - 1]);	
	int canUpgrade = 0;
	if (title == 0 || title == 1)
	{
		canUpgrade |= 1;
	}
	if (guildInfoData.money >= upgradeNeedMoney[level - 1])
	{
		canUpgrade |= 2;
	}
	if (guildInfoData.glory >= upgradeNeedGlory[level - 1])
	{
		canUpgrade |= 4;
	}
	if (guildInfoData.expNow >= upgradeNeedExp[level - 1])
	{
		canUpgrade |= 8;
	}
	sprintf(result, ",%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d", guildInfoData.name, level, canUpgrade,
		guildInfoData.presidName, guildInfoData.vicePresidName, guildInfoData.curMembs, 
		guildInfoData.limitMembs, guildInfoData.money, upgradeNeedMoney[level - 1],
		guildInfoData.glory, upgradeNeedGlory[level - 1], guildInfoData.expNow,
		upgradeNeedExp[level - 1]);
	cout<<"BisonTest:guildInfo is "<<result<<endl;
	return 0;
}

//查看玩家的基本信息
int Guild::viewHeroInfo(char* heroId, char *result)
{
	// string heroInfo;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -1;
	}
	int index = it->second;
	
	MembInfo_T* p = (MembInfo_T *)&guildInfoData.membsInfoArr[index];
	
	// heroInfo = intTostring(p->title)
			   // + intTostring(p->glory)
			   // + intTostring(p->totalContb);
	sprintf(result, ",%d,%d,%d,%d,%d", p->title, p->glory, p->dayContb, p->weekContb, p->totalContb);
	cout<<"BisonTest: hero Info is "<<result<<endl;   
	return 0;
}
#if 0
int Guild::viewHistory(int page, char *result)
{
	// string viewResult;
	int end = guildInfoData.historyEnd;
	int start = guildInfoData.historyStart;
	int size = end + 1 - start;				//历史总条数
	//cout<<"BisonTest end is "<<end<<"start is "<<start<<"size is "<<size<<endl;
	if (end < start)
	{
		size = MAX_HISTORY_SIZE;
	}
	//cout<<"BisonTest: history page is "<<page<<endl;
	//总的帮派页数
	int totalPages = size / 15 + ((size % 15) ? 1 : 0);	
	//cout<<"BisonTest totalPages is "<<totalPages<<endl;
	//客户端要求一条都没有的时候总页数也发1
	// viewResult = intTostring(((totalPages == 0) ? 1 : totalPages));
	sprintf(result, ",%d", ((totalPages == 0) ? 1 : totalPages));
	if ((page > totalPages) || (page < 1))
	{
		//所请求页面不存在
		//cout<<"BisonWarning: You have give a error page when view guild history!"<<endl;
		return -1;
	}
	
	int startPos = ((page - 1) * 15 + start) % MAX_HISTORY_SIZE;
	int endPos = (startPos + 15);
	cout<<"BisonTest startPos is "<<startPos<<endl;
	cout<<"BisonTest endPos before is "<<endPos<<endl;
	if (page == totalPages)
	{
		if (end < start)
		{
			endPos = end + MAX_HISTORY_SIZE;
		} else {
			endPos = end;
		}
	}
	cout<<"BisonTest endPos after is "<<endPos<<endl;
	HistoryItem_T *temp;
	int i;
	for (i = startPos; i <= endPos; i++)
	{
		temp = &guildInfoData.historyArr[i % MAX_HISTORY_SIZE];
		viewResult += intTostring(MY_TV_SEC - temp->time);
		viewResult += intTostring(temp->mainType);
		viewResult += intTostring(temp->brandType);
		viewResult += charTostring(temp->linkId);
		viewResult += charTostring(temp->showName);
		viewResult += intTostring(temp->value1);
		viewResult += intTostring(temp->value2);
		viewResult += intTostring(temp->value3);
		viewResult += intTostring(temp->value4);
		
		sprintf(result + strlen(result), ",%d,%d,%d,%s,%s,%d,%d,%d,%d", MY_TV_SEC - temp->time, temp->mainType,
			temp->brandType, temp->linkId, temp->showName, temp->value1, temp->value2, temp->value3, temp->value4);
	}
	return 0;
	
}
#endif

int Guild::viewHistory(int page, char *result)
{
	// string viewResult;
	int startLoc = guildInfoData.historyEnd;
	int endLoc = guildInfoData.historyStart;
	int size = 0;
	if (endLoc == GUILD_END_FLAG)
	{
		size = 0;
	} else if (endLoc <= startLoc)
	{
		size = startLoc + 1 - endLoc;
	} else {
		size = MAX_HISTORY_SIZE;
	}
	//cout<<"BisonTest: history page is "<<page<<endl;
	//总的帮派页数
	int totalPages = size / GUILD_HISTORY_PRE_PAGE + ((size % GUILD_HISTORY_PRE_PAGE) ? 1 : 0);	
	//cout<<"BisonTest totalPages is "<<totalPages<<endl;
	//客户端要求一条都没有的时候总页数也发1
	//viewResult = intTostring(((totalPages == 0) ? 1 : totalPages));
	sprintf(result, ",%d", ((totalPages == 0) ? 1 : totalPages));
	if ((page > totalPages) || (page < 1))
	{
		//所请求页面不存在
		//cout<<"BisonWarning: You have give a error page when view guild history!"<<endl;
		return -1;
	}
	
	int startPos = startLoc - (page - 1) * GUILD_HISTORY_PRE_PAGE;
	if (startPos < 0)
	{
		startPos += MAX_HISTORY_SIZE;
	}
	int endPos = startLoc - page * GUILD_HISTORY_PRE_PAGE;
	if (size < page * GUILD_HISTORY_PRE_PAGE)
	{
		endPos = endLoc;
	}
	if (endPos < 0)
	{
		endPos += MAX_HISTORY_SIZE;
	}
	
	cout<<"BisonTest startPos is "<<startPos<<endl;
	cout<<"BisonTest endPos before is "<<endPos<<endl;
	if (startPos < endPos)
	{
		startPos += MAX_HISTORY_SIZE;
	}
	
	HistoryItem_T *temp;
	for (int i = startPos; i >= endPos; i--)
	{
		temp = &guildInfoData.historyArr[i % MAX_HISTORY_SIZE];
		// viewResult += intTostring(MY_TV_SEC - temp->time);
		// viewResult += intTostring(temp->mainType);
		// viewResult += intTostring(temp->brandType);
		// viewResult += charTostring(temp->linkId);
		// viewResult += charTostring(temp->showName);
		// viewResult += intTostring(temp->value1);
		// viewResult += intTostring(temp->value2);
		// viewResult += intTostring(temp->value3);
		// viewResult += intTostring(temp->value4);
		sprintf(result + strlen(result), ",%d,%d,%d,%s,%s,%d,%d,%d,%d", (int)(MY_TV_SEC - temp->time), temp->mainType,
			temp->brandType, temp->linkId, temp->showName, temp->value1, temp->value2, temp->value3, temp->value4);
	}
	return 0;
	
}


//生成一条历史记录并插入头部
void Guild::makeHistory(int type1, int type2, char* id, char* name, int val1,
	int val2, int val3, int val4)
{
	int curSecond = MY_TV_SEC;
	guildInfoData.addOneHistoryItem(curSecond, type1, type2, id, name, val1, val2, val3, val4);
	memSet();
}

//获得帮派成员列表
set<string> Guild::getMembsList()
{
	set<string> membsList;
	map<string, int>::iterator it;
	for (it = membsInfoArrFindMap.begin(); it != membsInfoArrFindMap.end(); it++)
	{
		membsList.insert(it->first);
	}
	return membsList;
}

//获得帮派申请成员列表
vector<string> Guild::getApplyMembsList()
{
	vector<string> applyList;
	map<string, int>::iterator it;
	for (it = applyArrFindMap.begin(); it != applyArrFindMap.end(); it++)
	{
		applyList.push_back(it->first);
	}
	return applyList;
}


//查看帮派成员信息
int Guild::viewGuildMembsListInfo(char* result)
{
	MembInfo_T *p;
	// string membsInfo;
	
	int heroAwayTime = 0;
	map<string, int>::iterator it;
	for (it = membsInfoArrFindMap.begin(); it != membsInfoArrFindMap.end(); it++)
	{
		if (it->second < 0 || it->second > MAX_GUILD_MEMBS - 1)
		{
			continue;
		}
		p = &guildInfoData.membsInfoArr[it->second];
		// membsInfo += charTostring(p->heroId);
		// membsInfo += charTostring(p->nickName);
		// 门派
		// membsInfo += charTostring(p->party);
		// 等级
		// membsInfo += intTostring(p->level);
		// membsInfo += intTostring(p->title);
		// membsInfo += intTostring(p->dayContb);
		// membsInfo += intTostring(p->weekContb);
		// membsInfo += intTostring(p->totalContb);
		// 是否在线
		// membsInfo += intTostring(p->online);
		if (p->online < 10)
		{
			heroAwayTime = 0;
		} else {
			heroAwayTime = MY_TV_SEC - p->online;
		}
		if (heroAwayTime < 0 || heroAwayTime > 63072000)
		{
			heroAwayTime = 86400;
			p->online = MY_TV_SEC - 86400;
		}
		
		sprintf(result + strlen(result), ",%s,%s,%s,%d,%d,%d,%d,%d,%d", p->heroId, p->nickName, p->party,
			p->level, p->title, p->dayContb, p->weekContb, p->totalContb, heroAwayTime);
		
	}
	cout<<"BisonTest:membsInfo is "<<result<<endl;
	return 0;
}

//查看申请列表信息
int Guild::viewGuildApplyListInfo(char *result)
{
	int index = guildInfoData.applyHead;
	// string applyInfo;
	while (index != GUILD_END_FLAG)
	{
		ApplyListItem_T *p = &guildInfoData.applyArr[index];
		// applyInfo += charTostring(p->heroId);
		// applyInfo += charTostring(p->nickName);
		// applyInfo += charTostring(p->party);
		// applyInfo += intTostring(p->level);
		// applyInfo += intTostring(1);			//表示玩家是否在线，现在都定为在线
		sprintf(result + strlen(result), ",%s,%s,%s,%d,%d", p->heroId, p->nickName, p->party, p->level, 1);
		index = guildInfoData.applyArr[index].next;
	}
	
	return 0;

}

//增加玩家个人的帮派glory
int Guild::addGloryOfHero(char* heroId, int val)
{
	if (heroId == NULL || val < 0)
	{
		return -1;
	}
	
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -2;
	}
	int index = it->second;
	MembInfo_T* p = &guildInfoData.membsInfoArr[index];
	if ((p->totalGlory + val) < 0)
	{
		return -3;
	}
	p->glory += val;
	p->totalGlory += val;
	memSet();
	return 0;
}


//查看帮派中是否有该成员
bool Guild::checkIsInGuild(char* heroId)
{
	if (heroId == NULL)
	{
		return false;
	}
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		return false;
	}
	return true;
}

//获取一个成员头衔
int Guild::getHeroTitle(char* heroId)
{
	if (heroId == NULL)
	{
		return -1;
	}
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return -1;
	}
	
	int index = it->second;
	int title = guildInfoData.membsInfoArr[index].title;
	
	//技能检查
	for (int i = 0; i < 10; i++)
	{
		if (guildInfoData.openSkillFlag[i] != -1 && guildInfoData.membsInfoArr[index].skillLevel[i] == -1)
		{
			guildInfoData.membsInfoArr[index].skillLevel[i] = 0;
		}
	}
	return title;
}
//更改帮派中玩家昵称
void Guild::changeHeroNickName(char *heroId, char* newNickName)
{
	if (heroId == NULL || newNickName == NULL)
	{
		return;
	}
	// string nickName;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return;
	}
	int index = it->second;
	memset(guildInfoData.membsInfoArr[index].nickName, 0, sizeof (guildInfoData.membsInfoArr[index].nickName));
	strncpy(guildInfoData.membsInfoArr[index].nickName, newNickName, strlen(newNickName));
	if (guildInfoData.membsInfoArr[index].title == 0)
	{
		memset(guildInfoData.presidName, 0, sizeof (guildInfoData.presidName));
		strncpy(guildInfoData.presidName, newNickName, strlen(newNickName));
	} else if (guildInfoData.membsInfoArr[index].title == 1) {
		memset(guildInfoData.vicePresidName, 0, sizeof (guildInfoData.vicePresidName));
		strncpy(guildInfoData.vicePresidName, newNickName, strlen(newNickName));
	}
}
	
//获取玩家昵称，保证在玩家不在线的时候调用，也能查到玩家昵称
char* Guild::getHeroNickName(char* heroId)
{
	if (heroId == NULL)
	{
		return NULL;
	}
	// string nickName;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return NULL;
	}
	int index = it->second;
	return guildInfoData.membsInfoArr[index].nickName;
}

//设置玩家在线
void Guild::setHeroOnline(char* heroId, bool online)
{	
	if (heroId == NULL)
	{	
		return;
	}
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return;
	}
	
	int index = it->second;
	if (online)
	{
		guildInfoData.membsInfoArr[index].online = 0;
	} else {
		guildInfoData.membsInfoArr[index].online = MY_TV_SEC - 1;			//离线至少显示离线1秒
	}
	
}

//查看帮主的详细信息
int Guild::viewPresidInfo(char *result)
{	
	if (result == NULL)
	{
		return -2;
	}
	// string presidInfo;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(guildInfoData.presidId);
	if (it == membsInfoArrFindMap.end())
	{
		//这里不会走到，帮主的信息肯定有
		return -1;
	}
	int index = it->second;
	// presidInfo = charTostring(guildInfoData.presidId);
	// presidInfo += charTostring(guildInfoData.presidName);
	// presidInfo += intTostring(guildInfoData.membsInfoArr[index].level);
	// presidInfo += charTostring(guildInfoData.membsInfoArr[index].party);
	// presidInfo += charTostring(guildInfoData.name);
	// return presidInfo;
	sprintf(result, ",%s,%s,%d,%s,%s", guildInfoData.presidId, guildInfoData.presidName,
		guildInfoData.membsInfoArr[index].level, guildInfoData.membsInfoArr[index].party, guildInfoData.name);
	return 0;
}

//获取帮主或副帮主的昵称
char* Guild::getPresidNickName(int flag)
{
	if (flag == 0)
	{
		return guildInfoData.presidName;
	} else {
		return guildInfoData.vicePresidName;
	}
}

/*判断是否为此帮派成员*/
bool Guild::isNumber(const char* herId)
{
	if (herId == NULL)
	{	
		return false;
	}
	map<string, int>::iterator mem_it;
	mem_it = membsInfoArrFindMap.find(herId);
	if(mem_it == membsInfoArrFindMap.end())
	{
		return false;
	}
	return true;
}

int Guild::getHeroGlory(const char* heroId)
{
	if (heroId == NULL)
	{	
		return 0;
	}
	int glory;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return 0;
	}
	int index = it->second;
	return guildInfoData.membsInfoArr[index].glory;
}

int Guild::getHeroTotalGlory(const char* heroId)
{
	if (heroId == NULL)
	{	
		return 0;
	}
	int glory;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return 0;
	}
	int index = it->second;
	return guildInfoData.membsInfoArr[index].totalGlory;
}

bool Guild::decHeroGlory(const char* heroId, int val)
{
	if (heroId == NULL)
	{
		return false;
	}
	int glory;
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return false;
	}
	int index = it->second;
	glory = guildInfoData.membsInfoArr[index].glory;
	if (val < 0 || glory < val)
	{
		return false;
	}
	
	guildInfoData.membsInfoArr[index].glory -= val;
	memSet();
	return true;
}

bool Guild::addHeroContb(const char* heroId, int val)
{
	if (heroId == NULL || val < 0)
	{
		return false;
	}
	
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return false;
	}
	int index = it->second;
	guildInfoData.membsInfoArr[index].dayContb += val;
	guildInfoData.membsInfoArr[index].weekContb += val;
	guildInfoData.membsInfoArr[index].totalContb += val;
	guildInfoData.totalContb += val;
	memSet();
	return true;
}

//设置玩家等级
void Guild::setHeroLevel(char *heroId, int newLevel)
{
	if (heroId == NULL)
	{
		return;
	}
	map<string, int>::iterator it;
	it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		//未加入帮派
		return;
	}
	int index = it->second;
	guildInfoData.membsInfoArr[index].level = newLevel;
	memSet();
}
	
//设置阵营头衔, flag = 0获得；flag = 1取消
void Guild::setCampTitle(char title, int flag)
{
	if (flag == 0)
	{
		guildInfoData.campTitle |= title;
	} else if (flag == 1)
	{
		guildInfoData.campTitle &= ~title;
	}
	
}

//获取阵营头衔
char Guild::getCampTitle()
{
	return guildInfoData.campTitle;
}

//玩家进入帮派盛宴地图,向玩家发送,地图中,盛宴的详细信息
void Guild::send_msg_feast(void)
{
	// char msg[1024] = {0};
	// snprintf(msg,sizeof(msg),"%d,%d",12,30);
	// map<int,GuildClub*>::iterator it;
	// int i=0;
	// int flag=0;
	// for (;i<4;i++)
	// {
		// it=guildFeastMap.find(i);
		// if (it==guildFeastMap.end())
		// {
			// cout<<"jolly:guildFeastMap is error guild.cpp 1622"<<endl;
		// }
		// else
		// {
			// if (it->second->feastStart())
			// {
				// snprintf(msg+strlen(msg),sizeof(msg)-strlen(msg),",%s,%s,%d",it->second->getIdentity(),getHeroNickName(it->second->getInvitePerson()),it->second->getRemainTime());
				// flag++;
			// }
			// else
			// {
				// break;
			// }
		// }
	// }
	// cout<<"g_out_buf:"<<g_out_buf<<endl;
	// cout<<"i:"<<i<<endl;
	// if (flag!=0)
	// {
		// send_msg(pg_hero->getFd(),g_out_buf);
	// }
}

//玩家开帮派盛宴
void Guild::beginGuildFeast(Hero *hero,char* id,char *_identity)
{
	if (hero==NULL||id==NULL)
	{
		return;
	}
	
	// cout<<"&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	// cout<<"size::"<<guildFeastMap.size()<<endl;
	// cout<<"&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	
	if (guildFeastMap.size()>=4)
	{
		msg_error(g_out_buf,82);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		GuildClub *guildClub=new GuildClub();
		guildClub->treat(hero,id,this,_identity);
		guildFeastMap.insert(map<string,GuildClub*>::value_type(guildClub->getIdentity(),guildClub));
	}
}

//玩家吃帮派盛宴
void Guild::eatGuildFeast(Hero *hero,char *id)
{
	if (hero==NULL||id==NULL)
	{
		return;
	}
	
	map<string,GuildClub*>::iterator it;
	it = guildFeastMap.find(id);
	if (it==guildFeastMap.end())
	{		
		msg_error(g_out_buf,103);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		if (it->second->feastStart())
		{
			it->second->joinDinner(hero,this);
		}
	}	
}

long Guild::getGuildScore()
{
	long score = guildInfoData.level * 1000000 + guildInfoData.expNow + guildInfoData.glory * 20 + guildInfoData.curMembs * 100000;
	return score;
}

//判断玩家是否可以吃帮派盛宴
bool Guild::ifHeroCanEatFeast(Hero *hero,char *id)
{
	if (hero==NULL||id==NULL)
	{
		return false;
	}
	
	map<string,GuildClub*>::iterator it;
	
	it = guildFeastMap.find(id);
	if (it==guildFeastMap.end())
	{		
		msg_error(g_out_buf,103);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		if (it->second->feastStart())
		{
			if (it->second->canEatDish(hero))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}	
	
	return false;
}

//根据盛宴实例id 返回盛宴实例
GuildClub *Guild::getGuildClub(char *guildClubId)
{
	map<string,GuildClub*>::iterator it;
	
	it = guildFeastMap.find(guildClubId);
	if (it==guildFeastMap.end())
	{		
		return NULL;
	}
	else
	{
		return it->second;
	}	
}

//帮派盛宴结束,删除相关数据
void Guild::deleteGuildClub(char *guildClubId)
{
	map<string,GuildClub*>::iterator it;
	
	it = guildFeastMap.find(guildClubId);
	if (it==guildFeastMap.end())
	{		
		return;
	}
	else
	{
		GuildClub *guildClub=it->second;
		guildFeastMap.erase(it);
		delete guildClub;
	}	
}

//判断玩家是否可以开盛宴
bool Guild::isCanOpenFeast(void)
{
	if (guildFeastMap.size()>=4)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//判断该帮派是否是正在帮派战中
bool Guild::isInGuildWarRoom()
{
	return isInGuildWar;
}

//设置参加了帮派战
void Guild::setJoinGuildWar(bool flag, char *roomId)
{
	isInGuildWar = flag;
	
	if (flag == true)
	{
		if (roomId != NULL)
		{
			strncpy(guildWarRoomId, roomId, sizeof (guildWarRoomId));
		}
	} else {
		memset(guildWarRoomId, 0, sizeof (guildWarRoomId));
	}
}

//帮派所在的帮战房间Id
char *Guild::getGuildWarRoomId()
{
	return guildWarRoomId;
}

//系统请客帮派盛宴
void Guild::systemTreat(Map_Inform *_mapNow,char* _typeId)
{	
	
	if (_mapNow==NULL||_typeId==NULL)
	{
		cout<<"Guild::systemTreat the argument is error:"<<endl;
		return;
	}
	
	if (guildFeastMap.size()>=4)
	{
		cout<<"Guild::systemTreat guildFeastMap.size() is more than 4:"<<endl;
		return;
	}
	else
	{
		GuildClub *guildClub=new GuildClub();
		guildClub->sysTreat(_mapNow,_typeId,this);
		guildFeastMap.insert(map<string,GuildClub*>::value_type(guildClub->getIdentity(),guildClub));
	}
}

//刷新帮派任务
void Guild::refreshGuildTask()
{
	guildInfoData.refreshTaskTime++;
	map<string, int>::iterator it;
	for (it = membsInfoArrFindMap.begin(); it != membsInfoArrFindMap.end(); it++)
	{
		int index = it->second;
		guildInfoData.membsInfoArr[index].needRefreshTask = 1;
	}
}

int Guild::getRefreshGuildTaskTime()
{
	return guildInfoData.refreshTaskTime;
}

void Guild::resetRefreshGuildTaskTime()
{
	guildInfoData.refreshTaskTime = 0;
}

void Guild::clrHeroRefreshTaskNeed(char *heroId)
{
	map<string, int>::iterator it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		return;
	}
	
	int index = it->second;
	guildInfoData.membsInfoArr[index].needRefreshTask = 0;
}

bool Guild::getHeroRefreshTaskNeed(char *heroId)
{
	map<string, int>::iterator it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		return false;
	}
	
	int index = it->second;
	
	if (guildInfoData.membsInfoArr[index].needRefreshTask == 1)
	{
		guildInfoData.membsInfoArr[index].needRefreshTask = 0;
		return true;
	} else {
		return false;
	}
}


int Guild::checkHeroGuildSkill(char *heroId)
{
	map<string, int>::iterator it = membsInfoArrFindMap.find(heroId);
	if (it == membsInfoArrFindMap.end())
	{
		return 0;
	}
	int index = it->second;
	
	int flag = 0;
	int tag = 0;
	for (int i = 0; i < 10; i++)
	{
		if (guildInfoData.membsInfoArr[index].skillLevel[i] < 1)
		{
			flag = 1;
		}
		if (guildInfoData.membsInfoArr[index].skillLevel[i] != 10)
		{
			tag = 1;
		}
	}
	
	if (tag == 0)
	{
		return 2;
	}
	
	if (flag == 0)
	{
		return 1;
	}
	
	return 0;
}

