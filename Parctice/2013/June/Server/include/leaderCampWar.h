#ifndef LEADER_H
#define LEADER_H

#include <map>
#include <string>
#include <algorithm>
#include <sys/time.h>

#define MAX_APPLY_COUNT 50
#define MAX_GUILD_NAME_LEN 30

typedef struct myLeaderCampWar{
	int	kills;//杀敌数；
	int deaths;//死亡次数；
	myLeaderCampWar(int _kills,int _deaths)
	{
		kills=_kills;
		deaths=_deaths;
	}
}LeaderCampWarData;

typedef pair<string,long> PAIR_INT; 
typedef pair<string,LeaderCampWarData> PAIR_LEADER_CAMP_WAR_DATA; 


#define FACTION_Val(a,b) ( map<string,int>::value_type( (a),(b)) )//map的插入值方法宏定义；
#define HEROID_RANK_LEADER(a,b) ( map<string,int>::value_type( (a),(b)) )//map的插入值方法宏定义；
#define HEROID_Val(a,b) ( map<string,LeaderCampWarData>::value_type( (a),(b)) )//map的插入值方法宏定义；


#define CAMP_MAX_DEATHS 5//最多死亡次数；
#define LEADER_CAMP_WAR_AWARDS_LOWEST_RANGE 9//最大排名奖励，这个排名后的奖励相同；

extern map<string, Hero*> heroId_to_pHero;

class LeaderCampWar
{
public:
LeaderCampWar();

int addHero2Factionwar(Hero* hero);//添加英雄ID到阵营战；    
int delHeroFromFactionWar(Hero* hero);//从杀敌战中删除；

bool initFactionCampWar(void);//初始化统领战数据；
string finishFactionCampWar(void);//统领战争结束处理；

bool sendMsgStart(time_t _last_time=0);//开启PK；
bool startLeaderCampWar(void);

int addKills(Hero* myHero);//增加杀敌数；
int addDeathCounts(Hero* hero);//增加英雄ID死亡次数；
int reduceActiveHero(Hero* myHero);

char*  viewAwards(Hero* myHero);
int receiveAwards(Hero* myHero);

char* viewApplyInfo();
char*  endApplyFactionWar(void);
int apply2FactionWar(string _factionName,int camp);

void setWinnerFaction(string _winnerFaction);
void setGuildLeaderAId(string _GuildLeaderAId);
void setchallengeGuild(string _GuildName);
string setFactionName(string _factionAName,string _factionBName);

inline int setIdentity(int _index)
{
	index=_index;
}

inline int getFactionASize()
{
	return factionAActiveSize;
}

inline int getFactionBSize()
{
	return factionBActiveSize;
}
public:
string factionAName;//当前阵营的统领帮派；
string factionBName;
string winnerFaction;

int index;
time_t LeaderCampWarEndTime;//统领阵营战结束时间；
time_t leaderCampWarLastTime;//统领阵营战持续时间；
time_t LeaderCampWarStartTime;//统领阵营战开始时间；	

char my_apply_info[10240];

public:
map<string,int>applyWarFactionInfo;//申请统领战的帮派信息；
	
private:
map<string,int>factionARank;//保存帮派a排名数据；
map<string,int>factionBRank;//保存帮派b排名数据；

map<string,LeaderCampWarData> factionA;//帮派a参加数据；
map<string,LeaderCampWarData> factionB;//帮派b参加数据；


string guildLeaderAId;
string guildLeaderBId;

int factionAActiveSize;//当前帮派a活动人数大小；
int factionBActiveSize;
int num_factionA_leader_deaths;//初次赋值为默认值，表示死亡次数达到最大；
int num_factionB_leader_deaths;

};
#endif