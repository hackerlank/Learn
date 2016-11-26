#ifndef CHIEF_H
#define CHIEF_H

#include<map>
#include<string>
#include<vector>

typedef struct myChiefCampWar_S{
	int	kills;//杀敌数；
	int deaths; //死亡次数；
	myChiefCampWar_S(int _kills,int _deaths)
	{
		kills=_kills;
		deaths=_deaths;
	}
}ChiefCampWarData_T;

extern map<string, Hero*> heroId_to_pHero;
typedef pair<string,ChiefCampWarData_T> PAIR_CHIEF_CAMP_WAR_DATA; 

#define MAX_DEATHS 2//最多死亡次数；
#define CHIEF_CAMP_WAR_AWARDS_LOWEST_RANGE 9
#define HEROID_RANK_CHIEF(a,b) ( map<string,int>::value_type( (a),(b)) )
#define HEROID_VAL_CHIEF(a,b) ( map<string,ChiefCampWarData_T>::value_type( (a),(b)) )//map的插入值方法宏定义；


class ChiefCampWar{

public:

ChiefCampWar();
~ChiefCampWar();	

bool startChiefCampWar(void);//盟主战争开始处理；

bool sendMsgStartPK(time_t allTime=0);
int getWarHeroSize(void);//获取盟主阵营战的所有人数；
int addHero2Chiefwar(Hero* hero);//添加英雄ID到阵营战；    
int delHeroFromChiefWar(Hero* hero);//从杀敌战中删除；

int addKills(Hero* myHero);//增加杀敌数；
int addDeathCounts(Hero* hero);//增加英雄ID死亡次数；
void  finishChiefCampWar(void);//盟主战争结束处理；
int JudgeWinner(int factionANum,int leaderA_deaths,string& leaderAname,int factionBNum,int leaderB_deaths,string& leaderBname);

string getIdentity(void);
void setIdentity(string _chiefCampWarId);
bool setFactionName(string _factionName,int index);//设置参加盟主战的名字；

char* viewAwards(Hero* myHero);//查看奖励；
int receiveAwards(Hero* myHero);//领取奖励；

bool setChiefHeroId(char *p_hero_id);//设置盟主；
bool setChampion(char *_Champion);

public:
time_t ChiefCampWarEndTime;									//盟主阵营战结束时间；
time_t ChiefCampWarLastTime;
time_t ChiefCampWarStartTime;								//盟主阵营战开始时间;

private:

map<string,ChiefCampWarData_T> factionA;//帮派a；
map<string,ChiefCampWarData_T> factionB;//帮派b；
map<string,ChiefCampWarData_T> factionC;//帮派c；

map<string,int>factionARank;//保存帮派a排名；
map<string,int>factionBRank;//保存帮派b排名；
map<string,int>factionCRank;//保存帮派c排名；

int num_factionA_leader_deaths;//初次赋值为默认值，表示死亡次数达到最大；
int num_factionB_leader_deaths;
int num_factionC_leader_deaths;

int curr_factionC_counts;
int curr_factionB_counts;
int curr_factionA_counts;

string factionAName;					
string factionBName;
string factionCName;

string Champion;//当前盟主阵营的帮派；
string secondPlace;	
string thirdPlace;			

string chiefHeroId;
};
#endif