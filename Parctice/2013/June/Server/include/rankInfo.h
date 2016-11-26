/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server排名数据逻辑实现源文件；

**************************************************/
#ifndef _RANK_INFO_H
#define _RANK_INFO_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "hero.h"
#include "my_memcached.h"

#define MAX_INFO_TYPE	8						//排名信息类型大小

#define MAX_WEALTH_RANK_VALUE 40				//财富排名位数
#define MAX_ACTIVITY_RANK_VALUE 40				//活动排名位数
#define MAX_POWER_RANK_VALUE 40					//战力排名位数
#define MAX_SHAMBLES_RANK_VALUE 40				//红名排名位数
#define MAX_READNAME_RANK_VALUE 40				//击杀红名排名位数
#define MAX_PRESTIGE_RANK_VALUE 40				//声望排名位数
#define MAX_LEVEL_RANK_VALUE 40					//等级排名

#define MAX_RANK_VALUE 40

#define COUNT_FACTIONWAR_MODULUS 2				//参与帮战次数系数
#define COUNT_ORDCAMPWAR_MODULUS 2				//参与阵营战1次数系数
#define COUNT_LEADERCAMPWAR_MODULUS 2			//参与阵营战2次数系数
#define COUNT_CHIEFCAMPWAR_MODULUS 2			//参与阵营战3次数系数
#define COUNT_ENTER_DUPLICATION_MODULUS 1		//下副本次数系数
#define COUNT_ATTRACK_BOSS_MODULUS 1			//击杀活动boss次数系数

#define LIFE_VALUE_MODULUS  0.01				//玩家总生命值系数
#define MAGIC_VALUE_MODULUS 0.01				//玩家总魔法值系数
#define OUTER_ATTACK_MODULUS  0.5				//外功攻击系数	
#define INTER_ATTACK_MODULUS 0.5				//内功攻击系数	
#define OUTER_DEF_MODULUS 0.2					//外功防御系数	
#define INTER_DEF_MODULUS 0.2					//内功防御系数	
#define HIT_MODULUS 4							//命中系数	
#define CRIT_MODULUS 4							//暴击系数	
#define DUCK_MODULUS 3							//闪避系数	
#define TOUGH_MODULUS 3						//韧性系数	

#define COUNT_BE_READNAME_MODULUS 1				//成为红名次数系数
#define VALUE_SIN_MODULUS 1						//罪恶值系数

#define COUNT_READKILLS_MODULUS 1				//杀红名数系数

#define PRESTIGE_MODULUS 1						//声望系数

using namespace std;


/**
	排名信息结构体
*/
typedef struct RankInfo_S{											
	int grade;														//当前等级				宠物坐骑:等级
	int camp;														//阵营；				宠物坐骑:不用
	char party[2];													//门派；				宠物坐骑:不用
	char HeroName[HERO_MAME_LEN];									//英雄名字				宠物坐骑:主人名字
	char HeroId[HERO_ID_LEN+1];										//英雄ID				宠物坐骑:主人id
	char petId[50];													//宠物id 没有则为0		宠物坐骑:宠物实例id
	unsigned long 	value;											//排序值大小			宠物坐骑:战力
	char petName[50];
	int power;														//任务战力
	
	/*形参构造函数*/
	RankInfo_S(int _grade,unsigned long _value,char* _HeroName,int _camp,char* _party,char* _heroId,int _power)		
	{
		camp=_camp;
		grade=_grade;
		value=_value;
		memcpy(party,_party,strlen(_party));
		party[strlen(_party)]='\0';
		
		memcpy(HeroId,_heroId,strlen(_heroId));
		HeroId[strlen(_heroId)]='\0';	
		
		memcpy(HeroName,_HeroName,strlen(_HeroName));
		HeroName[strlen(_HeroName)]='\0';
		
		strncpy(petId,"0",sizeof(petId));
		
		strncpy(petName,"0",sizeof(petName));
		
		power=_power;
	}
	
	/*形参构造函数*/
	RankInfo_S(int _grade,unsigned long _value,char* _HeroName,char* _heroId,char *_petId,char *_petName)		
	{
		grade=_grade;
		value=_value;
		
		memcpy(HeroId,_heroId,strlen(_heroId));
		HeroId[strlen(_heroId)]='\0';	
		
		memcpy(HeroName,_HeroName,strlen(_HeroName));
		HeroName[strlen(_HeroName)]='\0';
		
		strncpy(petId,_petId,sizeof(petId));
		
		strncpy(petName,_petName,sizeof(petName));
		
		camp=-1;
		strncpy(party,"0",sizeof(party));
		power=-1;
	}
	
	/*默认构造函数*/
	RankInfo_S()												
	{
		grade=0;
		value=0;
		camp=-1;
		memset(party,'\0',strlen(party));
		memset(HeroId,'\0',strlen(HeroId));
		memset(HeroName,'\0',strlen(HeroName));
		memset(petId,'\0',strlen(petId));
	}
	
}RankInfo_T;

/**
	角色参加排名基本信息存缓存结构体
*/
typedef struct MemRankInfo_S{	
	char powerRankKey[MAX_POWER_RANK_VALUE][HERO_ID_LEN+1];						//人物战力
	RankInfo_T powerRankInfo[MAX_POWER_RANK_VALUE];		
	
	char levelRankKey[40][50];													//等级排名
	RankInfo_T levelRankInfo[40];	

	char wealthRankKey[MAX_WEALTH_RANK_VALUE][HERO_ID_LEN+1];					//财富
	RankInfo_T wealthRankInfo[MAX_WEALTH_RANK_VALUE];
	
	char activityRankKey[MAX_ACTIVITY_RANK_VALUE][HERO_ID_LEN+1];				//活跃度
	RankInfo_T activityRankInfo[MAX_ACTIVITY_RANK_VALUE];
	
	char shamblesRankKey[MAX_SHAMBLES_RANK_VALUE][HERO_ID_LEN+1];				//杀戮
	RankInfo_T shamblesRankInfo[MAX_SHAMBLES_RANK_VALUE];
	
	char prestigeRankKey[MAX_PRESTIGE_RANK_VALUE][HERO_ID_LEN+1];				//声望
	RankInfo_T prestigeRankInfo[MAX_PRESTIGE_RANK_VALUE];
	
	char petRankKey[40][50];													//宠物
	RankInfo_T petRankInfo[40];
	
	char rideRankKey[40][50];													//坐骑
	RankInfo_T rideRankInfo[40];
	
}MemRankInfo_T;

typedef pair<string,RankInfo_T> RANK_PAIR; 								//自定义pair对象

#define AddRankInfo(a,b) (map<string,RankInfo_T>::value_type(a,b)) 	
#define AddBasicRankInfo(a,b) (map<string,RankBasicInfo_T>::value_type(a,b))	//用于map数据的插入；

using namespace std;

class RankInfo{

public:

RankInfo();
~RankInfo();

/**************************
函数作用  初始化数据；
***************************/
void initBasicData();



/**************************
函数作用 根据类型，将角色信息加入到用于排序列表中；
函数参数 _type  加入排序信息类型；
		 _value 用于当前角色类型排名值的大小；
  返回值 bool 	加入成功ture 否则false; 
    调用 角色获取排名信息时；
***************************/
bool updateRankInfo(int _type,unsigned long _value);



/**************************
函数作用 获取排名信息，信息用string类型表示；
函数参数 _index 将要获取的信息类型下标；
  返回值 string 获取信息的具体值; 
***************************/
char*  gainRankInfo(int _index);

/**************************
函数作用 开始获取排名信息列表，从memcached里面读取到能参加排名的角色信息并且保存；
  返回值 bool 获取信息成功; 
    调用 排序时间调用；
***************************/
void setInfoToLocal(void);


/**************************
函数作用 更新临时数据保存map；
  返回值 bool 获取信息成功; 
	调用 角色下线时调用；
***************************/
bool updateTempData(Hero* hero);

void saveRankLog(void);



public:
	vector<map<string,RankInfo_T>*>myRankVector;	//参加排名角色信息类型管理；

	map<string,RankInfo_T>powerRank;				//战力资格排名信息容器
	map<string,RankInfo_T>levelRank;				//等级资格信息容器
	map<string,RankInfo_T>wealthRank;				//财富资格排名信息容器
	map<string,RankInfo_T>shamblesRank;				//杀戮资格排名信息容器
	map<string,RankInfo_T>prestigeRank;				//声望资格信息容器
	map<string,RankInfo_T>activityRankInfo;			//活动次数资格排名信息容器
	map<string,RankInfo_T>petRank;					//宠物资格信息容器
	map<string,RankInfo_T>rideRank;					//坐骑资格信息容器

	MemRankInfo_T myMemRankInfo;					//存储memcache的数据缓冲区；
	
	char rewardHero[9][50];				//0-2人物 3-5宠物 6-8坐骑
	
	void analysis(void);
	
	char rankInfoMsg[50][4096];			// 顺序:战力,等级,财富,杀戮,声望,活动,宠物,坐骑

public:
	int power;
	int grade;										//当前等级；
	int camp;										//阵营
	char party[2];									//门派；
	char heroId[HERO_ID_LEN+1];						//当前英雄id;
	char heroName[HERO_MAME_LEN];					//当前英雄昵称；
	char petId[50];									//宠物实例id
	char petName[50];

	int	RankInfoLastSize[8];			//上一次排序数据的大小；
	unsigned long lowLimit[8];			//当前限制加入排名的最低限制；
	int RankCountLimit[8];				//类型排名个数限制；
};

#endif
