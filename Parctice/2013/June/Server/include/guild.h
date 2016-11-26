/****************************************************************
 * Filename: guild.h
 * 
 * Description: 帮派
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/

#ifndef _GUILD_H_
#define _GUILD_H_
#include<set>
#include<map>
#include<list>
#include<deque>
#include<vector>
#include<string>
#include<iostream>
#include<string.h>
#include"wholeDefine.h"
#include"map_inform.h"
#include"guild_club.h"
using namespace std;

#ifndef INT_MAX
#define INT_MAX 		2147483647
#endif
#define GLORY_2_CONTB	5				//5点荣耀度转成一点贡献度
#define MONEY_2_CONTB	5000			//5000游戏币转成一点贡献度
#define EXP_2_CONTB		5				//5点帮会经验加一滴贡献度
#define DAY_REWARD_MONEY_BASE	10000	//日排名金钱奖励基数
#define DAY_REWARD_EXP_BASE		20000	//日排名经验奖励基数
#define DAY_REWARD_GLORY_BASE	2		//日排名帮贡奖励基数
#define WEEK_REWARD_MONEY_BASE	50000	//周排名金钱奖励基数
#define WEEK_REWARD_EXP_BASE	100000	//周排名经验奖励基数
#define WEEK_REWARD_GLORY_BASE	10		//周排名帮贡奖励基数

#define MAX_NOTICES_SIZE		151		//帮会公告最多存150个字符
#define MAX_QY_GROUP_SIZE		25		//qq群或yy群大小
#define MAX_GUILD_MEMBS			100		//帮派最大成员数
#define MAX_HISTORY_SIZE		1000	//历史最大记录数

#define GUILD_USED_FLAG			0x5555ffff		//占用标志
#define GUILD_END_FLAG			0xffffFFFF		//结束标志
#define GUILD_HISTORY_PRE_PAGE 	9				//帮派历史每页显示16个
#define GUILD_NUM_PER_PAGE		13

//string转字符串数组
// inline void strcpy(char p[], string src)
// {
	// strncpy(p, src.c_str(), src.size() + 1);
// }

typedef struct GuildSkill_S
{
	char skillId[IDL + 1];
	unsigned skillOrder;
	unsigned openNeedGuildMoney;
	unsigned openNeedGuildGlory;
	unsigned addFactor;
	unsigned upNeedGloryFactor;
	unsigned upNeedMoneyFactor;
	unsigned limit[5];
	unsigned upNeedGlory[21];
	unsigned upNeedMoney[21];
	unsigned addAttr[21];
	unsigned addTotal[21];
} Guild_Skill_T;

extern Guild_Skill_T global_guild_skill[10];

//帮派奖励项
typedef struct GuildReward_S
{
	char id[51];
	int brandType;				//帮派历史分类索引
	int rewardGuildGlory[5];
	int rewardGuildExp[5];
	// int rewardGuildMoney[5];
	int rewardSelfGlory[5];
	int rewardSelfExp[5];
	int rewardSelfMoney[5];
} GuildReward_T;
extern map<string, GuildReward_T> id_2_guildReward;			//帮派奖励

//申请列表项
typedef struct ApplyListItem_S
{
	int flag;					//管理标志
	int prev;					//前一项下标
	int next;					//下一项下标
	char heroId[IDL + 1];		//玩家ID
	char nickName[IDL + 1];		//玩家昵称
	char party[2];				//玩家门派
	int level;					//玩家等级
	ApplyListItem_S(){};
	bool applyInit(char *_heroId, char *_nickName, char *_party, int _level)
	{
		strcpy(heroId, _heroId);
		strcpy(nickName, _nickName);
		strcpy(party, _party);
		level = _level;
	}
} ApplyListItem_T;

//日志记录项,这个因为会很多，就尽量减少字段，不加flag
typedef struct HistoryItem_S
{
	char linkId[IDL + 1];	//链接名
	char showName[IDL + 1];	//显示名
	int time;				//事件时间
	int mainType;			//主类型
	int brandType;			//副类型
	int value1;				//数据1
	int value2;				//数值2
	int value3;				//数值3
	int value4;				//数值4
	HistoryItem_S(){};
	void historyInit(int curSecond, int type1, int type2, char *id = NULL, char *name = NULL,
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1)
	{
		time = curSecond;
		mainType = type1;
		brandType = type2;
		if (id == NULL)
		{
			memset(linkId, 0, sizeof(linkId));
		} else
		{
			strcpy(linkId, id);
		}
		if (name == NULL)
		{
			memset(showName, 0, sizeof(showName));
		}
		else {
			strcpy(showName, name);
		}
		value1 = val1;
		value2 = val2;
		value3 = val3;
		value4 = val4;
	}
} HistoryItem_T;

typedef enum {
	FLAG,
	TITLE,
	GLORY,
	TOTALGLORY,
	DONATEMONEY,
	DONATEGLORY,
	DAYCONTB,
	WEEKCONTB,
	TOTALCONTB,
	DAYRANKING,
	WEEKRANKING,
	SKILL
} INFO_TYPE_T;

//帮派玩家信息
typedef struct MembInfo_S
{
	int flag;			//管理标志
	int title;			//职位
	int glory;			//当前荣耀度
	int totalGlory;		//累计荣耀度
	int donateMoney;	//捐献金钱
	int donateGlory;	//捐献荣誉值
	int dayContb;		//日贡献
	int weekContb;		//周贡献
	int totalContb;		//总贡献
	int dayRanking;		//日名次
	int weekRanking;	//周名次
	int skillLevel[10];	//帮派技能
	int expTail;		//经验出来不够加一点贡献的尾子
	int gloryTail;		//荣耀度出来不够加一点贡献的尾子
	int moneyTail;		//金钱多出来不够加一点贡献的尾子
	int level;			//玩家等级
	unsigned online;	//玩家在线与否(0:在线；非0:玩家离线时间)
	int needRefreshTask;
	char heroId[IDL + 1];	//成员ID
	char nickName[IDL + 1];	//玩家名
	char party[2];		//门派
	
	MembInfo_S(){
	};
	void membInfoInit(int _title, int _level, char* _heroId, char* _nickName, char* _party, unsigned _online)
	{
		
		//-1表示未加入帮会，0为帮主，1为副帮主，5为帮众
		title = _title;
		// heroId = _heroId;
		// nickName = _nickName;
		// party = _party;
		strcpy(heroId, _heroId);
		strcpy(nickName, _nickName);
		strcpy(party, _party);
		level = _level;
		//贡献值都初始为0
		dayContb = 0;
		weekContb = 0;
		totalContb = 0;
		
		//捐献的金钱和荣耀值也为0
		donateMoney = 0;
		donateGlory = 0;
		
		//荣耀度也为0
		glory = 0;
		totalGlory = 0;
		
		//小尾子都记为0
		expTail = 0;
		gloryTail = 0;
		moneyTail = 0;
		
		//日排名周排名都为0,即无排名
		dayRanking = 0;
		weekRanking = 0;
		
		for (int i = 0; i < 10; i++)
		{
			//技能不可学
			skillLevel[i] = -1;
		}
		
		online = _online;			//置为在线
		
		needRefreshTask = 0;
	}
	
	//改变玩家帮派职务
	void changeTitle(int newTitle)
	{
		title = newTitle;
	}
	
	//双奖，帮会积累增加，玩家积累也增加，包括签到礼和任务奖励
	int doubleReward(int incGlory, int incExp)
	{
		glory += incGlory;
		totalGlory += incGlory;
		incGlory += gloryTail;						//加上上次没够一点贡献度的多余荣誉
		gloryTail = incGlory % GLORY_2_CONTB;		//计算新的尾子
		incExp += expTail;							//加上上次没够一点贡献度多余经验
		expTail = incExp % EXP_2_CONTB;				//计算新的经验尾子
		int contb = incGlory / GLORY_2_CONTB + incExp / EXP_2_CONTB;
		dayContb += contb;
		weekContb += contb;
		totalContb += contb;
		
		return contb;
	}
	
	//单奖，只有玩家会增加积累
	void oneReward(int incGlory)
	{
		glory += incGlory;
		totalGlory += incGlory;
	}
	
	//捐献，flag为0捐献绑定游戏币，flag为1捐献帮贡,返回做出的贡献度
	int donate(int val, int flag)
	{
		int contb = 0;
		if (flag == 0)
		{
			donateMoney += val;
			val += moneyTail;
			moneyTail = val % MONEY_2_CONTB;
			contb = val / MONEY_2_CONTB;
		}
		else if (flag == 1)
		{
			//在外面判断是否够扣
			glory -= val;
			donateGlory += val;
			val += gloryTail;
			gloryTail = val % GLORY_2_CONTB;
			contb = val / GLORY_2_CONTB;
		}
		else if (flag == 2)
		{
			//贡献经验
			val += expTail;
			expTail = val % EXP_2_CONTB;
			contb = val / EXP_2_CONTB;
		}
		
		dayContb += contb;
		weekContb += contb;
		totalContb += contb;
		
		return contb;
	}
	
	//消耗玩家帮贡升级技能
	bool skillUpgrade(int val)
	{
		if (glory < val)
		{
			return false;
		}
		
		glory -= val;
		return true;
	}
	
	//清除日积累
	void dayClr()
	{
		dayContb = 0;
	}
	
	//清除周积累
	void weekClr()
	{
		dayContb = 0;
		weekContb = 0;
	}
	
} MembInfo_T;


typedef struct GuildInfoData_S
{
	char name[IDL + 1];								//帮派名
	char id[IDL + 1];								//帮派ID
	char presidName[IDL + 1];						//帮主名
	char presidId[IDL + 1];							//帮主ID
	char vicePresidName[IDL + 1];					//副帮主名
	char vicePresidId[IDL + 1];						//副帮主ID
	char notices[1024];								//帮派公告
	char qqGroup[25];								//qq群
	char yyGroup[25];								//yy群
	char campTitle;									//阵营职务
	int	idNum;										//帮派编号
	int camp;										//帮派所属阵营
	int level;										//帮会等级
	int expNow;										//帮会经验
	int glory;										//帮会繁荣度
	int money;										//帮派资金
	int weekContb;									//帮会周贡献度
	int totalContb;									//帮会总贡献度
	int curMembs;									//当前成员数
	int limitMembs;									//可容纳成员数
	int refreshTaskTime;							//刷新任务次数
	//int ranking;									//帮会排名
	int rankInAll;									//帮派在所有帮派的排名
	int rankInCamp;									//帮派在阵营内的排名
	int openSkillFlag[10];							//技能开启状态
	int firstFree_AP;								//第一个可用申请列表数组下标
	int applyHead;									//申请列表头下标
	int applyTail;									//申请列表尾下标
	ApplyListItem_T applyArr[MAX_GUILD_MEMBS];		//申请加入的成员列表
	int firstFree_MI;								//第一个可用成员信息列表数组下标
	MembInfo_T membsInfoArr[MAX_GUILD_MEMBS];		//成员信息数组
	int historyStart;								//第一条历史下标
	int historyEnd;									//最后一条历史下标
	HistoryItem_T historyArr[MAX_HISTORY_SIZE];		//历史数组
	
	//帮派基础数据的初始化
	GuildInfoData_S()
	{
		curMembs = 0;
		expNow = 0;
		glory = 0;
		money = 0;
		weekContb = 0;
		totalContb = 0;
		campTitle = 0;
		initApply();
		initMembsInfo();
		historyStart = GUILD_END_FLAG;
		historyEnd = GUILD_END_FLAG;
		
		for(int i = 0; i < 10; i++)
		{
			openSkillFlag[i] = -1;
		}
		
		refreshTaskTime = 0;
	}
	
	//初始化申请列表相关数据
	void initApply()
	{
		firstFree_AP = 0;				//第一个可使用的申请列表数组下标
		applyHead = GUILD_END_FLAG;		//申请头指向的下标置为无效
		applyTail = GUILD_END_FLAG;		//申请列表尾下标也置为无效
		
		int i;
		for(i = 0; i < MAX_GUILD_MEMBS - 1; i++)
		{
			applyArr[i].flag = i + 1;
		}
		applyArr[i].flag = GUILD_END_FLAG;
	}
	
	//初始化成员信息列表数据
	void initMembsInfo()
	{
		firstFree_MI = 0;				//第一个可使用的成员信息列表数组下标
		
		int i;
		for(i = 0; i < MAX_GUILD_MEMBS - 1; i++)
		{
			membsInfoArr[i].flag = i + 1;
		}
		
		membsInfoArr[i].flag = GUILD_END_FLAG;
	}
	
	//创帮时的初始化
	void guildInfoDataInit(char* guildId, char* _name, char* heroId, char* nickName, char* party, int heroLevel, int _camp, int _level, int _idNum)
	{
		strcpy(name, _name);
		strcpy(id, guildId);
		strcpy(presidName, nickName);
		strcpy(presidId, heroId);
		memset(vicePresidName, 0, sizeof vicePresidName);
		memset(vicePresidId, 0, sizeof vicePresidId);
		memset(notices, 0, sizeof notices);
		memset(qqGroup, 0, sizeof qqGroup);
		memset(yyGroup, 0, sizeof yyGroup);
		campTitle = 0;
		camp = _camp;
		level = _level;
		idNum = _idNum;
		if (level <= 5)
		{
			// limitMembs = 60;
			limitMembs = 15 + 5 * _level;
		}
		refreshTaskTime = 0;
	}
	
	//增加一个帮派成员
	int addOneMemb(int _title, int _heroLevel, char* _heroId, char* _nickName, char* _party, unsigned online)
	{
		int temp = firstFree_MI;
		if((temp < 0) || (temp) >= sizeof(membsInfoArr)){
			return GUILD_END_FLAG;
		}
		if (temp == GUILD_END_FLAG){
			//超过了帮派的最大人数
			cout<<"BisonWarn: when you see this, you should expand the size of MAX_GUILD_MEMBS "<<endl;
			return temp;
		}
		else 
		{
			membsInfoArr[temp].membInfoInit(_title, _heroLevel, _heroId, _nickName, _party, online);
			curMembs += 1;
			for (int i = 0; i < 10; i++)
			{
				if (openSkillFlag[i] == 1)
				{
					membsInfoArr[temp].skillLevel[i] = 0;
				}
			}
			firstFree_MI = membsInfoArr[temp].flag;
			membsInfoArr[temp].flag = GUILD_USED_FLAG;
			
			return temp;
		}
	}
	
	//删除一个成员，此操作之前要在成员查找表中删除对应项
	void delOneMemb(int index)
	{
		
		if((index < 0) || (index) >= sizeof(membsInfoArr)){
                        return;
                }

		curMembs -= 1;
		membsInfoArr[index].flag = firstFree_MI;
		firstFree_MI = index;	//标明该项可使用，数据部删除，因为增加时会重置
		
		membsInfoArr[index].needRefreshTask = 0;
	}
	
	//增加一个申请成员
	int addOneApply(char* _heroId, char* _nickName, char* _party, int heroLevel)
	{
		int temp = firstFree_AP;
                if((temp < 0) || (temp) >= sizeof(applyArr)){
                        return GUILD_END_FLAG;
                }

		if (temp == GUILD_END_FLAG)
		{
			return temp;
		} else
		{
			if (applyHead == GUILD_END_FLAG)
			{
				//加入的是第一个申请者
				applyArr[temp].prev = applyArr[temp].next = GUILD_END_FLAG;
				applyHead = applyTail = temp;
			} else {
				//所有的加入都是从尾部加入
				applyArr[temp].prev = applyTail;
				applyArr[temp].next = GUILD_END_FLAG;
				applyArr[applyTail].next = temp;
				applyTail = temp;
			}
			applyArr[temp].applyInit(_heroId, _nickName, _party, heroLevel);
			firstFree_AP = applyArr[temp].flag;
			applyArr[temp].flag = GUILD_USED_FLAG;
			return temp;
		}
		
	}
	
	//删除一个申请成员
	bool delOneApply(int index, char oldHeroId[])
	{
		if((index < 0) || (index) >= sizeof(applyArr)){
                        return false;
                }

		if (applyHead == GUILD_END_FLAG)
		{
			strncpy(oldHeroId, "\0", 2);
			return false;
		}
		applyArr[index].flag = firstFree_AP;
		firstFree_AP = index;
		strncpy(oldHeroId, applyArr[index].heroId, IDL + 1);
		
		int next = applyArr[index].next;
		int prev = applyArr[index].prev;
		if (applyHead == index)
		{
			applyHead = next;
			if (applyHead == GUILD_END_FLAG)
			{
				applyTail = GUILD_END_FLAG;
			} else {
				applyArr[next].prev = GUILD_END_FLAG;
			}
		} else if (applyTail == index) {
			applyTail = prev;
			applyArr[prev].next = GUILD_END_FLAG;
		} else {
			applyArr[next].prev = prev;
			applyArr[prev].next = next;
		}
		return true;
	}
	
	void addOneHistoryItem(int itemTime, int type1, int type2, char* id = NULL, char* name = NULL,
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1)
	{
		if (historyEnd == GUILD_END_FLAG)
		{
			historyStart = 0;
			historyEnd = 0;
		} else {
			historyEnd = (historyEnd + 1) % MAX_HISTORY_SIZE;
			if (historyEnd == historyStart)
			{
				historyStart = (historyStart + 1) % MAX_HISTORY_SIZE;
			}
		}
		historyArr[historyEnd].historyInit(itemTime, type1, type2, id, name, val1, val2, val3, val4);
	}
	
} GuildInfoData_T;

class GuildClub;
class Guild
{
private:

	GuildInfoData_T guildInfoData;
	map<string, int> applyArrFindMap;
	map<string, int> membsInfoArrFindMap;
	map<string,GuildClub*> guildFeastMap;		//帮派盛宴表
	
	//设置对应技能可以激活
	void setCanOpenSkill();
	bool isInGuildWar;
	char guildWarRoomId[51];
public:
	//从memcache上来数据还原帮派
	Guild(GuildInfoData_T newGuildMemData);
	void memSet(void);
	//帮会构造
	Guild(char* guildId, char* _name, char* heroId, char* nickName, char* party, int level, int camp, int _level);
	
	//帮派数据梳理
	void cardingGuild();
	//申请加入
	int applyJoin(char* heroId, char* nickName, char* party, int level);
	//清除申请表中某一项
	bool removeOneApply(char* heroId);
	//清除所有
	void removeAllApply(void);
	//加入帮会
	int join(char* heroId, char* nickName, char* party, int level, unsigned online);
	//离开帮会
	void exit(char* heroId);
	
	//增加帮会资金.
	void addMoney(int val);
	//增加帮会经验
	bool addExp(int val);
	//增加帮会繁荣度
	void addGlory(int val);
	//花费帮派资金
	bool useMoney(int val);
	//花费帮派繁荣度
	bool useGlory(int val);
	//经验只在升级时用，其他时候不会用，因此不用有使用经验的接口
	
	//更改帮会通知
	bool changeNotice();
	
	//转让帮主
	void setPresident(char* heroId, char* nickName);
	//任命副帮主
	bool setVicePresident(char* heroId, char* nickName);
	//任命高层
	void setManager(char* heroId, char* nickName, int title);
	//高层卸任
	bool managerRetired(char* heroId, int title);
	
	//查找帮主
	char* getPresident();
	//查找副帮主
	char* getVicePresident();
	//查帮主ID
	char* getPresidId();
	//查副帮主ID
	char* getVicePresidId();
	//帮派阵营
	int getCamp();
	
	//帮派等级
	int getLevel();
	int getMoney();
	int getGlory();
	int getExp();
	int getTotalContb();
	int getCurMembs();
	//int getRankNum();
	//获取在所有帮派中的排名
	int getRankInAll();
	//获取在阵营内的排名
	int getRankInCamp();
	int getIdNum();
	char* getName();
	char* getId();
	bool getNotices(char *result, int flag = 0);
	//获得帮派成员列表
	set<string> getMembsList();
	//获取申请成员列表
	vector<string> getApplyMembsList();
	
	//外部调用设置帮派排名
	//设置在所有中的排名
	void setRankInAll(int rankNum);
	//设置帮派在阵营内的排名
	void setRankInCamp(int rankNum);
	//void setRankNum(int rankNum);
	//修改公告
	void setNotices(char* newNotices, int flag = 0);
	//生成一条历史记录并加到记录的头部
	void makeHistory(int type1, int type2, char* id = NULL, char* name = NULL, 
		int val1 = -1, int val2 = -1, int val3 = -1, int val4 = -1);
	//获取签到奖励，mode表明是否使用道具
	int getSignInReward(char* heroId, char* nickName, int mode, char *result);
	//获取帮派活动奖励, index是帮派任务下标
	int getTaskReward(char* heroId, char* nickName, GuildReward_T* p_guildReward, float rewardTimes, char *result);

	//玩家捐献游戏币
	int donateMoney(char* heroId, int val);
	//玩家捐献声望
	int donateGlory(char* heroId, int val);
	//贡献帮派经验
	int donateExp(char* heroId, int val);
	//日贡献排名或周贡献排名
	void rankInGuild(int mode);	
	//获取昨日或者上周名次
	int getRankOrder(char* heroId, int mode);
	//获取排名奖励，rewardGlory玩家对应帮贡，flag表明是日排名还是周排名
	void getRankReward(char* heroId, int rewardGlory, int flag);
	//增加玩家个人的帮派glory
	int addGloryOfHero(char* heroId, int val);
	//帮派升级
	int upgrade();
	
	//开启帮派技能
	int openSkill(int index);
	//升级玩家的帮派技能
	int upgradeSkill(char* heroId, int index);
	//获取玩家的帮派技能等级
	int getSkillLevel(char* heroId, int index);
	//查看玩家的帮派技能信息，如果是帮主副帮主要加上技能是否可以激活的标志
	int viewSkillInfo(char* heroId, bool managerFlag, char* result);
	
	void changeMembsInfo(char* heroId, int index, int val);
	
	//查看帮派的基本信息
	int viewGuildInfo(char* result, int title);
	//查看玩家的基本信息
	int viewHeroInfo(char* heroId, char* result);
	//查看帮派历史的某页信息
	int viewHistory(int page, char* result);
	//查看帮派成员信息
	int viewGuildMembsListInfo(char* result);
	//查看申请列表信息
	int viewGuildApplyListInfo(char* result);
	//查看帮派中是否有该成员
	bool checkIsInGuild(char* heroId);
	//获取一个成员头衔
	int getHeroTitle(char* heroId);
	//更改帮派中玩家昵称
	void changeHeroNickName(char *heroId, char* newNickName);
	//获取玩家昵称，保证在玩家不在线的时候调用，也能查到玩家昵称
	char* getHeroNickName(char* heroId);
	//获取帮主或副帮主的昵称
	char* getPresidNickName(int flag);
	//设置玩家在线
	void setHeroOnline(char* heroId, bool online);
	
	//解散帮会
	//bool disband();
	~Guild();
	
	static int count;						//帮派编号
	static int totalPages[4];				//帮派总页数
	
	//查看帮主的详细信息
	int viewPresidInfo(char *result);
	/*判断是否为此帮派成员*/
	bool isNumber(const char*herId);
	//获取玩家的帮贡
	int getHeroGlory(const char* heroId);
	
	int getHeroTotalGlory(const char* heroId);
	//减少玩家的帮贡
	bool decHeroGlory(const char* heroId, int val);
	//增加玩家贡献度
	bool addHeroContb(const char* heroId, int val);
	//设置阵营头衔
	void setCampTitle(char title, int flag = 0);
	//获取阵营头衔
	char getCampTitle();
	//设置玩家等级
	void setHeroLevel(char *heroId, int newLevel);
	//玩家进入帮派盛宴地图,向玩家发送,地图中,盛宴的详细信息
	void send_msg_feast(void);
	//玩家开帮派盛宴
	void beginGuildFeast(Hero *hero,char* id,char *_identity);	
	//玩家吃帮派盛宴
	void eatGuildFeast(Hero *hero,char *id);
	//帮派积分
	long getGuildScore();
	//判断玩家是否可以吃帮派盛宴
	bool ifHeroCanEatFeast(Hero *hero,char *id);
	//根据盛宴实例id 返回盛宴实例
	GuildClub *getGuildClub(char *guildClubId);
	//帮派盛宴结束,删除相关数据
	void deleteGuildClub(char *guildClubId);
	//判断玩家是否可以开盛宴
	bool isCanOpenFeast(void);
	//判断该帮派是否是正在帮派战中
	bool isInGuildWarRoom();
	//设置参加了帮派战
	void setJoinGuildWar(bool flag, char *roomId = NULL);
	//帮派所在的帮战房间Id
	char *getGuildWarRoomId();
	//系统请客帮派盛宴
	void systemTreat(Map_Inform *_mapNow,char* _typeId);
	//刷新帮派任务
	void refreshGuildTask();
	int getRefreshGuildTaskTime();
	void resetRefreshGuildTaskTime();
	void clrHeroRefreshTaskNeed(char *heroId);
	bool getHeroRefreshTaskNeed(char *heroId);
	int checkHeroGuildSkill(char *heroId);
	
};

//帮派比较
class CompGuild
{
	public:
	bool operator()(Guild *guild1, Guild *guild2)
	{
		int level1 = guild1->getLevel();
		int level2 = guild2->getLevel();
		if (level1 > level2)
		{
			return true;
		}
		int exp1 = guild1->getExp();
		int exp2 = guild2->getExp();
		if (level1 == level2 && exp1 > exp2)
		{
			return true;
		}
		
		int glory1 = guild1->getGlory();
		int glory2 = guild2->getGlory();
		if (level1 == level2 && exp1 == exp2 && glory1 > glory2)
		{
			return true;
		
		}
		
		int num1 = guild1->getCurMembs();
		int num2 = guild2->getCurMembs();
		if (level1 == level2 && exp1 == exp2 && glory1 == glory2 && num1 > num2)
		{
			return true;
		
		}
				
		//第五重，判断帮会资金,再分不出胜负就不管了
		int money1 = guild1->getMoney();
		int money2 = guild2->getMoney();
		if (level1 == level2 && exp1 == exp2 && glory1 == glory2 && num1 > num2 && money1 >= money2)
		{
			return true;
		}
		return false;
	}
};

#endif