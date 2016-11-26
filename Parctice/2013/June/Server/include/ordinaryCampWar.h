#ifndef ORDINARY_WAR_CAMP__H
#define ORDINARY_WAR_CAMP__H

#include <map>
#include <string>
#include <algorithm> 									//sort 函数头文件；
#include <sys/time.h>

#define MAX_WAR_COUNTS 120								//最大阵营战上限；
#define MAX_CAMP_WAR_COUNTS  40							//每种阵营最大人数；
#define ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE	9		//奖励最低排名，此排名后，奖励一样；

class Hero;

/**
KillsInfo 杀敌信息结构体，kills杀敌数，lastKillTime最后杀敌时间；	
*/
typedef struct Kills{
	int kills;
	time_t lastKillTime; 
	Kills(int _kills,time_t _lastKillTime)
	{
		kills=_kills;										//杀敌数
		lastKillTime=_lastKillTime;							//最后杀敌时间；	
	}
}KillsInfo;

typedef pair<string,KillsInfo> ORD_CAMP_WAR_DATA_PAIR; 
#define HeroId_Val(a,b) ( map<string,KillsInfo>::value_type( (a),(b)) )


class OrdinaryCampWar
{
public:
/**
	构造函数
*/
	OrdinaryCampWar();
	
/**
	析构函数
*/	
	~OrdinaryCampWar();	
	
	
/**
argument：void；
return:   bool; ture 成功，失败；
function: 数据初始化；
*/
bool initCampWar(void);							//初始化阵营战数据；

	
/**
argument：Hero* myHero 英雄实例指针；
  return: int   -1,表示实例指针为空；
				-2,表示这个英雄ID阵营信息没有在系统中找到；
		        -3,表示该英雄没有在这阵营战对应的阵营队伍中；
		        >=0,表示杀敌数；
function: 角色获取杀敌数；
*/	
int  getKills(Hero* hero);						//获取杀敌数；


/**
argument：void；
return:   int  阵营战总人数；
function: 获取阵营战总人数；
*/
int  getWarHeroSize(void);						//获取阵营战的所有人数；
	

/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-2:	英雄实例的阵营不属于系统三个阵营之内；
				 0：在阵营tribes（支教/正派）里面。
				 1：在阵营religion（宗教/邪派）里面。
				 2：在阵营ranger（游侠）里面。
function:  查找阵营下标；这函数是由于开始阵营保存的是个字符串，此函数有用，现在改成int,意义不大；
*/	
int  findCampIndex(Hero* hero);					//获取阵营下标；  


/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-4:	英雄实例的阵营不属于系统三个阵营之内；
				-9: 在此次阵营战中，在其阵营队列中找不到；				 
				 0：表示删除成功。
function:  从阵营战中删除角色信息；
*/   
int  delHeroFromWar(Hero* hero);	  			//从杀敌战中删除；


/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-2: 表示阵营战已饱和，达到最大允许人数；
				-3：表示插入insert失败；
				-4:	英雄实例的阵营不属于系统三个阵营之内；
				 0：表示添加成功。
function:  插入阵营参加角色；
*/
int  addHero2war(Hero* hero,int _kills=0);		//添加英雄ID到阵营战；
	

/**
argument：Hero* myHero 英雄实例指针,此实例指向杀敌数加1；
return:   int  -1,myHero为空；
		       -2,表示该英雄没有在这阵营战对应的阵营队伍中；
			   -3,表示这个英雄ID阵营信息没有在系统中找到;
		       >0,表示杀敌数；
*/	
int addKills(Hero* myhero);						//杀敌处理；


/**
argument； void;
  return:  map<string,KillsInfo>&  返回此房间的前9名，如果没有9名，有多少，返回多少；
function:  战斗结束处理，算出优胜者；  
*/
const map<string, KillsInfo>& finishCampWar(void); 	//阵营战争结束处理；


/**
	获取这次普通阵营战的ID；
*/
string getIdentity(void);						//获取普通阵营战房间号；



/**
argument：Hero* myHero 英雄实例指针；
return:   int  -1,英雄实例指针为空；
			   -2,阵营类型不是默认类型；
		       -3,表示该英雄没有在这阵营战对应的阵营队伍中；
		        0,表示减少成功；
*/
int reduceActiveHero(Hero* myHero);				//减少房间活动人数；	


/**
	设置这次普通阵营战的ID；
*/
void setIdentity(string _ordinaryId);			//设置普通阵营战房间号；


/**
argument myHero 实例英雄指针，_rank 排名(默认为AWARDS_LEADT_RANGE)；
  return char* 奖励的字符串；
*/	
char* viewAwards(Hero* myHero,int _rank=ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE);		//查看奖励；


/**
argument myHero 实例英雄指针，_rank 排名(默认为AWARDS_LEADT_RANGE)；
  return int -1 实例英雄指针为空
			 -2 不属于系统默认阵营类型；
			 -3  在此房间没有找到英雄战斗痕迹；
			 -4  给背包装东西失败；
			  0  表示成功；
*/
int receiveAwards(Hero* myHero,int _rank=ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE);		//领取奖励；


/**
argument void
  return bool 如果成功，返回true,失败false;
*/
bool sengMsgStartCampWar();


/**
argument void
  return int 值的大小;
function 获取支派/正派此房间活动人数；
*/	
inline int getTribesSize(void)				
{	
	return 	activeSize[0];
		
}


/**
argument void
  return int 值的大小;
function 获取宗教/邪派此房间活动人数；
*/
inline int getReligionSize(void)		
{
	return 	activeSize[1];
}

/**
argument void
  return bool 是否成功;
function 更新普通阵营战房间任务信息；
*/
bool update_ord_camp_info(void);

/**
argument Hero* my_hero角色实例指针；
  return bool 是否成功;
function 更新角色信息；
*/
bool update_hero_info(Hero* my_hero,int time);


/**
argument void
  return int 值的大小;
function 获取游侠此房间活动人数；
*/
inline int getRangerSize(void)			
{
	return 	activeSize[2];
}


private:
	int sumSize;								//所有人数大小；
	int activeSize[3];							//三种阵营活动人数大小；
	
	string ordinaryId;							//此房间ID；
	
	map<string,KillsInfo> religion; 			//宗教信息；	
	map<string,KillsInfo> tribes;   			//邪派信息；
	map<string,KillsInfo> ranger;				//游侠信息；
	
	map<string,KillsInfo> WinnerHero;			//保存此房间杀敌数前ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE名，战争结束后完成返回；
	vector<map<string,KillsInfo>*> campVector;	//用于查找；
	
};

#endif