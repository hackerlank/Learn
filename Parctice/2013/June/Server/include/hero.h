#ifndef HERO_H
#define HERO_H

#include<map>
#include<string>
#include<vector>
#include<list>
#include<iostream>

using namespace std;

#include"task.h"
#include"skill.h"
#include"data_structure_struct.h"
#include"library_head.h"
#include"map_inform.h"
#include"equip_config.h"
#include"equipment.h"
#include"bag.h"
#include"hero_help.h"
#include"bit_ops.h"
#include"money.h"
#include"five_elements.h"
#include"meridian.h"
#include"pet_box.h"
#include"my_time.h"
#define CELL_SIZE 8
#define SELECT_CAMP_GRADE 100
#include"wholeDefine.h"
#include "hero_configuration.h"
#include "guild.h"
#include "friend.h"
#include "warehouse.h"
#include"day_limit_item.h"
#include"skill_struct.h"
#include"vip.h"
#include "reward_online.h"
#include"mysteriousBussiness.h"
#include"midasTouch.h"
#include"team.h"
#include"heroCpyRecord.h"
#include "command_other_function_all_over.h"
#include "reward_online.h"
#include "ointment.h"
#include "commodity.h"
#include "buff_debuff.h"
#include "hero_skill.h"
#include "hero_conf.h"
#include "ride.h"
#include "internal_forces.h"

#define  MAX_ACTIVITY_TYPE 6			//活动次数统计类型大小；
#define  DEAL_FRIENDLEVEL_ADD_LIMIT 10 //交易成功增加好友度限制次数；

#define TASK_NEED_KILL_MONSTER			0x3FF		//有杀怪需求
#define TASK_NEED_COLLECT_GOODS			0xFFC00		//有采集需求
#define TASK_NEED_FIRST_CUILI			0x100000	//第一次淬砺
#define TASK_NEED_FIRST_JINGLIAN		0x200000	//第一次精炼
#define TASK_NEED_JOIN_CAMP				0x400000	//加阵营
#define TASK_NEED_JOIN_GUILD			0x800000	//加帮派
#define TASK_NEED_BUY_EQUIP				0x1000000	//需要买装备
#define TASK_NEED_BUY_DAOJU				0x2000000	//需要买道具
#define TASK_NEED_PK_HERO				0x4000000	//需要PK
#define TASK_NEED_PASS_ECTYPE			0x8000000	//需要通关副本
#define TASK_NEED_KILL_NPC_BOSS			0x10000000	//需要杀死NPCboss
#define TASK_NEED_PASS_TOWER_LAYER		0x20000000	//需要通关通天塔
#define TASK_NEED_LEVEL_UP				0x40000000	//需要升级

#define MAX_HERO_LEVEL					80			//当前英雄最大等级
#define MAX_TASK_MAP_SIZE 				25
#define MAX_TASK_CHAPT_NUM				100
#define BEGIN_CYCLE_TASK_LEVEL			30			//循环任务开始登记
#define WORLD_SPEAK_CD	10					//世界说话cd时间


#define RIDE_PREPARE_TIME				2			//骑乘准备时间

class TowerLayerRecord;

//骑乘状态
typedef enum RIDE_STATE_E{
	RIDE_STATE_FREE,			//裸奔状态
	RIDE_STATE_PREPARE,			//准备乘骑状态
	RIDE_STATE_RIDING			//乘骑状态
} RIDE_STATE_T;

class BuffOintment;
class HeroCpyRecord;
class Drug;
class Team;
struct HeroCpyRecMem;
typedef struct RewardData_T{
	int offline_time,last_day,last_day_flag,chief_flag;
	int offline_timeFlag,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	void operator = (const RewardData_T &data)
	{
		offline_time=data.offline_time;
		last_day=data.last_day;
		last_day_flag=data.last_day_flag;
		chief_flag=data.chief_flag;
		offline_timeFlag=data.offline_timeFlag;
		value2=data.value2;
		value3=data.value3;
		value4=data.value4;
		value5=data.value5;
		memcpy(value6,data.value6,sizeof(value6));
		memcpy(value7,data.value7,sizeof(value7));
		memcpy(value8,data.value8,sizeof(value8));
		// memcpy(level_flag,data.level_flag,sizeof(level_flag));
	}
}RewardData;							//福利相关

typedef struct{
	int physique;					//体魄
	int wushu;						//武术
	int will;						//意志
	int shenfa;						//身法
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
}ExerciseData;

typedef struct memSkills
{
	MemSkill skills[15];
	int size;
	char	reserved[1024];
	memSkills()
	{
		size=0;
	}
}MemSkills;

//用于存储的药包数据
typedef struct medicineBagData_T{
	int value;				//药包的剩余量
	int cd;					//药包的cd时间
	int lastTime;			//上次自动使用的时间
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	medicineBagData_T()
	{
		value=0;
		cd=10;
		lastTime=myTime.tv_sec;
		value1=0;
		value2=0;
		value3=0;
		value4=0;
		value5=0;
		strncpy(value6,"0",sizeof(value6));
		strncpy(value7,"0",sizeof(value7));
		strncpy(value8,"0",sizeof(value8));
	}	
}medicineBagData;


typedef struct CampData_S{
	int 	campWarType;		//阵营战类型，1，表示普通战，2，表示统领战，3，表示盟主战；
	int 	campWarRoomNum;		//所在阵营战类型的房间编号；
	bool 	campWarStartMark;	//阵营战开启标记；
	bool 	CampWarFinishMark;	//阵营战结束处理完成标志；
	CampData_S()				//默认构造函数；
	{
	campWarType=-1;
	campWarRoomNum=-1;
	campWarStartMark=false;
	CampWarFinishMark=true;
	}
}CampData_T;

typedef struct taskSaveData_S
{
	TaskData_T acced[10];								//最多10个已接任务
	int finMap[MAX_TASK_MAP_SIZE];						//完成任务位图
	int passChapt[MAX_TASK_CHAPT_NUM];					//已经完成的章节
	int rewardChapt[MAX_TASK_CHAPT_NUM];				//章节礼包是否已经领过
	unsigned cycleTaskLevel;
	unsigned cycleTaskLoop;
	unsigned cycleTaskFinishFlag[10];
	char cycleTaskId[10][51];
	char reserved[466];
	taskSaveData_S ()
	{
		cout<<"Have init taskSaveData_T"<<endl;
		for (int i = 0; i < MAX_TASK_MAP_SIZE; i++)
		{
			finMap[i] = 0;
		}
		for (int j = 0; j < MAX_TASK_CHAPT_NUM; j++)
		{
			passChapt[j] = 0;
			rewardChapt[j] = 0;
		}
		
		cycleTaskLevel = 0;
		cycleTaskLoop = 0;
		memset(cycleTaskFinishFlag, 0, sizeof cycleTaskFinishFlag);
		memset(cycleTaskId, 0, sizeof cycleTaskId);
		
		//
		memset(reserved, 0, sizeof reserved);
	}
	void operator =(const taskSaveData_S &data)
	{
		memcpy(acced, data.acced, sizeof(acced));
		memcpy(finMap, data.finMap, sizeof(finMap));
		memcpy(passChapt, data.passChapt, sizeof passChapt);
		memcpy(rewardChapt, data.rewardChapt, sizeof rewardChapt);
		cycleTaskLevel = data.cycleTaskLevel;
		cycleTaskLoop = data.cycleTaskLoop;
		memcpy(cycleTaskId, data.cycleTaskId, sizeof cycleTaskId);
		memcpy(cycleTaskFinishFlag, data.cycleTaskFinishFlag, sizeof cycleTaskFinishFlag);
		
	}
}TaskSaveData_T;

typedef struct heroGuildData_S
{
	char 	guildId[IDL + 1];				//所属帮会的Id
	int		guildTitle;						//帮会的职位	
	int		guildSkillAdd[10];				//当前等级帮派技能附加属性
	int		guildSkillAddTotal[10];			//帮派技能附加的所有属性
	bool	guildSigned;					//是否帮派签到过
	int		guildDayRewardTime;				//帮派日排名奖励领取次数
	char	reserved[1024];
	
} heroGuildData_T;

typedef struct FingerGuessingGame_T{
	char identity[40];		//对战的玩家实例id
	int flag;				//标志,标志自己是否已经准备开始游戏 -1为和电脑队长,0为未参加,1为参加猜拳为准备,2为参加猜拳,已经准本,3为已经开始游戏
	int finger;				//对方出的标志,0,没出,1石头,2剪刀,3布
	int money;				//猜拳的赌注
	int value1,value2,value3,value4,value5;
	char value6[50],value7[50],value8[50];
	
	FingerGuessingGame_T(void)
	{
		strncpy(identity,"0",sizeof(identity));
		flag=0;
		finger=0;
		money=0;
	}
	
	void operator = (const FingerGuessingGame_T &data)
	{
		strncpy(identity,data.identity,sizeof(identity));
		flag=data.flag;
		finger=data.finger;
		money=data.money;
	}
}FingerGuessingGame;

//玩家交易结构体 不用保存memcached
typedef struct BussinessData_T{
	char identity[40];				//交易流水号 uuid
	int bussinessFlag;				//1.交易中,没有点锁定,也没有点交易  2.点了锁定,没有点交易   3.点了锁定 也点了交易  0没在交易中
	int businessMoney; 				//交易金币	
	char businessPartnerId[40];  	//交易玩家id	
	BussinessData_T(void)
	{
		strncpy(identity,"0",sizeof(identity));
		strncpy(businessPartnerId,"0",sizeof(businessPartnerId));
		bussinessFlag=0;
		businessMoney=0;
	}
	void init(void)
	{
		strncpy(identity,"0",sizeof(identity));
		strncpy(businessPartnerId,"0",sizeof(businessPartnerId));
		bussinessFlag=0;
		businessMoney=0;
	}
}BussinessData;

typedef struct
{
	//角色基本数据，向斌(测试结果，29项数据内容，冗余数据包括cost(eat)消耗，五行five_elements_value，已测试完成by Tory 2012.9.13）
	HeroBasicData basicHeroData;		
	//角色下五行数据， 牛志国
	FiveElementData fiveElementData;
	//角色下任务状态数据，牛志国
	TaskSaveData_T taskSaveData;
	//角色的帮派信息
	heroGuildData_T heroGuildData;
	//日限制项目
	DayLimitItem_T dayLmtItemArr[MAX_DAY_LMT_ITEM_SIZE];
	//日限制项目使用的数量
	int dayLmtUsedNum;
	//玩家技能数据
	HeroMemSkill_T skills[HERO_SKILL_MAX_NUM + 20];
	//新宠物结构体,史哲轩
	Pet_BoxDataNew petboxdataNew;		
	//角色下包裹数据,史哲轩
	BagData bagData;
	//角色下经脉数据
	MeridData_T meridData;
	//角色下金钱数据，史哲轩
	moneyData moneydata;
	//角色仓库数据，史哲轩
	WarehouseData warehousedata;
	//福利相关数据保存,史哲轩
	RewardData rewarddata;
	//好友相关数据保存，向慧明
	MemFriend_T myFriendInfo;
	//人物训练相关数据保存,史哲轩
	ExerciseData exercisedata;
	//人物身上穿的装备数据保存,史哲轩
	WearEquipData wearequipdata[20];				//0为时装,13为翅膀
	//神秘商人数据保存,史哲轩
	MysteriousBussinessData mysteriousBussinessData; 
	
	medicineBagData bloodBagdata;		//jolly modify
	medicineBagData	magicBagdata;		//jolly modify
	
	int expNow, expForGrow, level, expAgo, camp/*0,表示支派，1，表示宗教 2，表示游侠；*/, crimeValue/* 罪恶值 */ ,usePrestigeTime/* 一天声望书使用次数 */;

	//基本数据 向慧明 有疑问RTX xhm
	int friendLevel;								//好友度(它又是魅力值，尼玛，坑爹)(策划改成魅力值呢，就是魅力值)
	int cum_recharge_awards;						//累积充值奖励；
	char hangUpdata[HANG_UP_DATA_SIZE+1];			//挂机配置数据存档；
	char shortCutData[SHORT_CUT_BAR_DATA_SIZE+1];   //快捷栏配置数据存档；
	char systemSetData[SYSTEM_SET_DATA_SIZE+1];		//系统设置数据；
	char operationSetData[OPERATION_SET_DATA_SIZE+1];//操作设置基本数据；
	unsigned int prestige;							//声望值
	unsigned int readNameKills;						//红名击杀数目
	unsigned int activityCounts[MAX_ACTIVITY_TYPE];	//活动参与活跃度；
	int offlineTime;								//玩家离线时间
	long taskState;									//任务状态		added by bison
	char identity[IDL+1];		
	char nickName[IDL+1];
	
	char titleStore[ALLTITLELEN];//玩家头衔容器
	
	char title[TITLELEN]; //玩家当前头衔
	
	char copyCause[COPYCAUSELEN];//副本令的使用状态容器保存有已使用过的副本id	
	
	char wagonId[IDL + 1];		//马车的实例Id
	
	HeroCpyRecMem cpyRecordMem;   //副本记录
	
	MidasTouchData midasTouchData;//点石成金
	
	int autoRecover;			//自动回血时间验证

	OnlineRewarData onlineReward;		//在线奖励
	
	int levelFlag;			//等级奖励
	
	char recharge_flag[20];		//充值奖励
	
	int dropProbabty;           //红名掉落概率	jolly	废弃 
	
	int bloodBagRecoverValue;		//血包回复系数
	int magicBagRecoverValue;		//蓝包回复系数
	
	int expDrug[3];					//人物经验药使用限制,每种经验药最多每天只能使用5次
	
	int online_money_index,online_gold_index,online_goods_index;		//在线奖励的金钱索引,元宝索引和物品索引
	
	int expTimes;					//人数使用双倍经验或者三倍经验标志,默认值为1
	int expTimesCount;				//人物使用双倍经验或者三倍经验的剩余时间,下线仍然计时
	char heroInfor[1024];			//角色个人资料
	
	int festivalRewardFlag;			//圣诞节奖励领取标志,每天可以领取一次,每天重置
	
	int fingerGuessingGameCount;	//猜拳赢的局数记录,用于以后排名,目前没用
	
	int useGoldForActive;			//活动用,记录元宝的使用数量,用来发礼品
		
 	BuffDrugData allBuffDrug[10];	//使用的buff药品记录
	
	long recharge_time;				//上一次充值的时间 added by xhm；
	
	char activeCodeId[30];        //激活码id，如果没领激活码，则长度为0；

	int goods_use_size;				//特定物品使用次数；
	
	int goods_gain_size;			//特定物品获得次数；
	
	int worldSpeakTimes;			//非会员每天喊话10次;
	
	int rideState;					//骑乘状态
			
	int heroVersion;					//人物属性的版本号
		
	int lastStrength;              //耐力值
	
	RideData rideData;
	
	VipDailyData vipDailyData;
	
	char nowTowerId[LITTLE_MID_VALUE_LENGTH + 1];        //当前塔id
	
	char nowLayerId[LITTLE_MID_VALUE_LENGTH + 1];         //当前层id
	
	int fatigueUpperVal;           //耐力值上限
	
	size_t buyFatigueTmes;        //已购买体力值次数
	
	int petSkillNumber;
	
	char systemOpen[1024];
	
	int layerFlg[10];			//记录每一层是否可打
	
	unsigned heroSkillExp;			//人物阅历（用于技能升级）
	
	char peiouId[50],peiouName[50];
	
	int testVipTime;				//体验vip时间
	
	int internalForcesLevel;		//内力等级
	unsigned internalForces;				//内力值	
	unsigned internalForcesExpNow;			//内力经验
	unsigned internalForcesUpgradeNeedExp;	//升级需要经验
	unsigned internalForcesBrushExpTimes;	//内力刷经验次数
	unsigned goldBrushExpTimes;				//元宝刷经验次数
	
	
	unsigned int buyThreeTmeExpCtn;         //购买3倍经验丹的数量
	
	int downLineDay;
	
	char teamerId[HEROID_LENGTH + 1];
	
	int targetItem[10][50];
	int targetFinishNumber[10];
	
	char partyCodeId[30];        //公会礼包激活码	
}MemHero;

class Ride;
class Reward_Online;
class MidasTouch;
class MysteriousBussiness;
class Pet_Box;
class Map_Inform;
class Skill;
class Bag;
class Warehouse;
class Money;
class HeroHelp;
class Guild;
class Hero 
{
private: 

	//阵营战数据；
	CampData_T 	campWarData;	
	
	//角色各种称号或ID
	string 	photoId;						//图片组编号（随着等级的提升和装备更换将发生变化,无需赋初始值）					
	string teamAim;							//发布个人信息时的组队目的
	
	//头衔 
	set<string> titleStore;					//角色头衔容器
	string 	title;							//角色头衔(暂时无用 Tory 2012.9.23)		

	//角色状态数据
	int 	_fd;            				//fd
	int 	life_station;   				//生死状态	
	bool 	isLoading;						//刚进入游戏加载场景数据状态 tory	
	Point 	logPt;             				//当前逻辑坐标,无需存memcached
	
	int 	attack_request;   				//攻击请求是否接受   ，只有请求为大于零的整数时，才接受请求攻击，否则不接受请求攻击
	int 	max_accepted_size;				//??????? what's this
	bool 	stillFlg;              			//定身标记值
	bool 	isRedName;						//玩家是否红名，false，不红名；true，红名 evan add 2012.8.31
		
	int 	status;							//角色的无敌状态,不需要保存memcached,每次上线都初始化为0; jolly
	list<string> fightlist;					//正在攻击人物的monsterid列表   jolly add by2012.8.7
	list<string> fighthero;					//正在攻击人物的heroid列表		jolly add bt 2012 8.28	
	

	Map_Inform *map_now;         			//chenzhen 4.23
			
	Guild 	*guild;							//玩家所属帮会
	char 	guildName[IDL + 1];				//所属帮会的榜排名
	FiveElem *fiveElement;					//五行
	Meridian *merid;						//经脉
	
	Friend *friendInfo;						//好友信息实例指针；
	map<string,int> suitlist;				//玩家身上的套装集合 evan add 2012.8.30
	Warehouse *warehouse;					//仓库 jolly add2012.9.5	
		
	Bag *bag;     								//jolly added 6.25
	
	Money *money;								//jolly added 7.10
	
	Pet_Box *pet_box;							//jolly added 7.16

	Reward_Online *online_reward;				//在线奖励 jolly added 
	
	FingerGuessingGame fingerGuessingGame;		//猜拳 jolly  added
	
	Ride *ride;									//jolly added 2.26
	
	MysteriousBussiness *mysteriousbussiness;		//人物的神秘商人
	
	//帮派数据
	bool	inGuildWarRoom;					//在帮派战房间中
	list<Task*> accepted_task_list;			//已接任务列表

	MidasTouch *midasTouch;					//???
	list<string> 	attracMonStore;			//该角色吸引的所有怪物ID集合
	string mainSrcId;                      	//进入副本之前的地图id，这是为了出副本用的

	char fbRom[SHOR_MID_VALUE_LENGTH + 1]; 	//副本房间号	 
	set<string >copyCauseStore;				//副本令的使用状态容器保存有已使用过的副本id
	HeroCpyRecord*	cpyRecord;				//副本状态记录表 

	//奖励系统相关 
	int online_time;						//本次上线时间
	int offline_exp;
	
	//连续签到奖励
	int last_exp;
		
	/******************added by xhm *************************/
	string   myTowerDefTeamId;							//塔防队伍ID；
	unsigned int activityCounts[MAX_ACTIVITY_TYPE];		//1参与帮战次数 2 参与阵营战1次数 3 参与阵营战2次数 4参与阵营战3次数 5下副本次数 6击打活动boss次数
	unsigned int prestige;								//玩家声望大小；
	unsigned int readNameKills;							//红名击杀个数；
	/*****************added end *****************************/
	
	int hero_PK_status;			//玩家PK模式：1，不能战斗；2，自由模式；3，阵营模式；4，帮派模式； evan add 2012.9.23
	
	//人物训练相关jolly 9.24 
	int physiqueMax;				//体魄最大值
	int wushuMax;					//武术最大值
	int willMax;					//意志最大值
	int shenfaMax;					//身法最大值
	int exerciseTemp[4];			//训练处的临时值
	int exerciseNeedMoney;			//训练需要的金币
		
	map<string,Equipment*> heroAllEquip;//角色拥有的所有装备

	Point beforGoCpyPiexPt;               //进入副本之前的像素点
	
	bool canWalking;                   	// 为true时表示处在可移动状态，否则为切图状态
		
	ev_timer tongBuTimer;				//鍚屾璁℃椂鍣?
	
	ev_timer happyTimer;				//娱乐图定时器
	
	unsigned happyAddExp;
	unsigned happyAddMoney;
	unsigned stayHappyTime;
	
	
	ev_timer skillAnimationTimer;		//技能动画时间
	int recoverTmeCtn;                  //副本复活次数
	
	ev_timer collectTimer;				//采集定时器
	
	ev_timer revivalTimer;				//复活倒计时
	
	//发起骑乘时间
	int prepareRideSecond;
	
	//罪恶点扣出标志
	int crimCount;
	int powerCount;
	Hero_Conf_T *p_conf;
	
	int heroState; 						//是否已经摆摊, =7:表示在采集中,6打坐,5摆摊
	int where;							//角色数据属于第几区，在选择角色进入游戏时初始化
		
	TowerLayerRecord *towerLayerRecord;
	
	
	char choiseLayerId[LITTLE_MID_VALUE_LENGTH + 1];         //正在打的那一层
	
	char taskNeedKillNpcBossId[51];
	
	set<string> chatGroupIdSet;        //私聊，群聊句柄id
	
	int nowDay;				//当前的登录日子
	int allowSign;			//可以补签的天数
	int allowSignGold;		//补签所需元宝
	
private:
	void initHelp(void);	
	
	/*角色下线删掉黑木崖塔数据开启情况*/
	void deleteTowerLayerRecord(void);
	
	
	
	
public:

	
	int saveCount;			//保存memcached的计数器

	//交易相关 jolly 2013.2.25
	BussinessData bussinessData;
	//debuff定时
	SkillBuff_T skillBuff[15];				//buff或debuff技能
	MemHero *memHero;
	ev_timer moveTimer;					//移动定时器
	list<Point> keyPath;				//路径点
	Point currPt, endPt;		//本次路径搜寻起点与终点
	int skillBuffState;						//技能状态
	int speed;						//移动速度
	int lastSpeed;					//上次速度
	
	int bloodBottle;						//血瓶使用时间
	int magicBottle;						//蓝瓶使用时间
		
	//罪恶系统
	int 	crimeTime;								//罪恶值 初始时间
	void initCrimeTime(void);   //初始化罪恶时间
	bool getisRedName(void);				//玩家是否红名，false，不红名；true，红名 evan add 2012.8.31
	void setisRedName(bool _isRedName);
	int  getCrimeValue(void);				//罪恶值 evan add 2012.8.31
	void setCrimeValue(int _crimeValue);	//修改罪恶值
	void addCrimeValue(void);	//增加罪恶值
	void cutCrimeValue(void);	//减少罪恶值
	void changeRedName(void);	//判断是否为红名
	void term(Hero *hit); //判断是否增加罪恶值			
	void crimeTitle(void);  	//罪恶值对应头衔获取
	
	//交易系统
	int getHeroState(void);
	void setHeroState(int _heroState);
	
	void sendMsgByStall(char* msg,int len);  //广播摊位消息 */
	
	

	
	//头衔功能
	void	setTitle(string _title);	//设置角色头衔
	string	getTitle(void);				//获得角色头衔	
	bool chooseTitle(string id);		//选择头衔
	bool addTitle(string id);		//增加头衔
	void cutTitle(string id);	//删除头衔
	void  ownTitle(void); //通过自己逻辑数据同步更新memcached数据
	void initTitle();	//根据memcached初始化头衔
	void sendMsgTitle(void); //测试头衔用
	
	//副本令相关功能
	// bool useCopyCause(string _mapId);		//副本令使用 true 为成功 false失败
	void initMemCopyCause(void);
	void initCopyCauseStore(void);
	
	DayLmtFindGroup_T dayLmtFindGroup;		//日限制项目管理
	int finishTaskMap[MAX_TASK_MAP_SIZE];		//记录完成任务的位图
	char guildWarRoomId[IDL + 1];		//帮派战房间ID
	
	
	struct timeval awayTime;		//离开时间
	bool isFirstLoginInDay;			//是否为一天中的第一次登陆
	
	int  gethero_PK_status(void);						//玩家PK模式：1，不能战斗；2，自由模式；3，阵营模式；4，帮派模式； evan add 2012.9.23
	void sethero_PK_status(int _hero_PK_status);

	Hero(MemHero *_memHero, int connect_fd, int _where);
   
	Hero(char *_nickName, char *_party, int _where);	 
		    
	~Hero(void);                 		//析构函数，释放内存
	
	void init_ratio(void);             //初始化成长系数
	char* getMapId(void);
	void setMapId(const char *_mapId);
	void changeMapId(char *_mapId);
	
	bool memSet(void);
	bool memEquipSet(void);
	
	char* getIdentity(void) const;			//获得角色实例ID	
	void setIdentity(char *_identity);	//设置角色实例ID	

	char* getNickName(void) const; 		 	//获得昵称
	void setNickName(string nickName); 	//修改昵称
	
	
	string 	getPhotoId(void);			//获得图片组编号
	
	
	/************************************************************
	函数作用：  阵营相关操作函数；有疑问RTX xhm;
	参数说明：  _camp	0:宗教 1:邪教 2:游侠；
				campWarType 阵营战类型（1,普通阵营战 2,统领战 3,盟主战）；
				campWarRoomNum  阵营战房间号；
				campWarStartMark 阵营战是否正是开启；
				CampWarFinishMark 阵营战是否结束；
	  返回值：  CampData_T 阵营战数据；
				bool 成功true，失败false；
	************************************************************/	
	void  setCamp(int _camp);//设置阵营信息
	int   getCamp(void);//获得角色阵营信息
	void  setCampWarData(int campWarType,int campWarRoomNum,bool campWarStartMark=false,bool CampWarFinishMark=true);//设置阵营战数据；
	CampData_T getCampWarData(void);//获得阵营战数据结构体；
	int   getCampWarType(void);//获取阵营战类型；
	bool  isInCampWar(void);//判断是否是在阵营战中；
	bool  exitCampWar(void);//退出阵营战；
	void  setCampWarStartMark(bool _isStart);//设置阵营战开启标志；
	bool isInCampResWar();
	
	/************************************************************
	函数作用：  增加活动列表对应类型的次数 有疑问RTX xhm;
	参数说明：  type 0:参与帮战次数 1:参与阵营战1次数 2:参与阵营战2次数 3:参与阵营战3次数 4:下副本次数 5:击打活动boss次数
				size 本次增加的次数；
				
	  返回值：  bool 成功true，失败false；
	************************************************************/
	bool addActivityCounts(int type,unsigned int size);
	void getActivityCounts(unsigned long _activityCounts[]);//注意：_activityCounts[]，必须要大于MAX_ACTIVITY_TYPE；
	
	
	/*****************************************************
	函数作用：  下面六个函数说明 有疑问RTX xhm;
	参数说明：  addValue    要增加的Value大小；
				reduceValue 将要减少后的value大小；			
	  返回值：  unsigned int 操作后当前value的值；
	******************************************************/
	//声望操作
	unsigned int getPrestigeValue(void);
	unsigned int addPrestigeValue(unsigned int addValue);
	unsigned int reducePrestigeValue(unsigned int reduceValue);
	//int usePrestigeTime;		//一天声望书使用次数 Cookie
	//红名击杀个数；
	unsigned int getReadNameKills(void);
	unsigned int addReadNameKillsValue(unsigned int addValue);
	unsigned int reduceReadNameKillsValue(unsigned int reduceValue);
	

	/*****************************************************************
	函数作用：  获取战力大小；这个函数获取数据用于排名，有疑问 RTX xhm
	参数说明：  注意：powerInfo必须大于5；
				将战力数据存储到参数powerInfo里面
				（ 0技能总等级  1装备总等级 2装备总颜色
				 3当前强化总等级 4装备一级宝石总个数 5升星总星数）
		调用    src/viewInfo/rankInfo.cpp,注意：powerInfo必须大于5；
	******************************************************************/
	void getPowerInfo(unsigned long powerInfo[]);
	
	
	/*****************************************************************
	函数作用：  好友度的相关操作，有疑问 RTX xhm
	参数说明：  _addValue将要增加的好友度的大小；
				_type增加好友度类型（0，交易成功 1，赠送异彩纷呈)
				_reduceValue将要减少的好友度的大小；
	  返回值：	当前操作后好友度的大小；
	******************************************************************/
	int getFriendLevel(void);
	int addFriendLevel(int _addValue);
	int reduceFriendLevel(int _reduceValue);
	
	/*****************************************************************
	函数作用：  塔防组队有关函数，有疑问 RTX xhm
	参数说明：  _towerDefTeamId设置的塔防队伍ID；
	  返回值：	当前当前塔防队伍的ID；
	******************************************************************/
	string  getTowerDefTeamId(void);
	void 	setTowerDefTeamId(string _towerDefTeamId);
	

	void 	setFaction(string _faction_id, string _faction_name);//设置帮派信息
	string	getFaction_id(void);		//获得角色帮派ID
	string 	getFaction_name(void);		//获得角色帮派名称

	
	int 	getExpForGrow(void);        //获取当前升级所需经验
	int 	getExpNow(void);			//获取当前角色已拥有的经验

	int 	getGradeNow(void);          //获取当前角色等级	
	void	setGradeNow(int level);		//设置角色当前等级
	int		getLevel(void) ;				//获得角色等级
	
	char*	getParty(void);				//获得角色门派

	Point getLocation(void) const;      		//获得当前像素点坐标
	void setLocation(Point _pt, int flag = 0);  		//修改当前位置像素点坐标，同时更新逻辑坐标
	
	void setLogPt(Point _logPt);		//获得当前逻辑点坐标
	Point getLogPt(void);				//
	
	void setPlayIndex(int _index); 		//修改玩家在玩家容器里面的下标值
	int getPlayIndex(void);        		//获得玩家在玩家容器里面的下标值
	
	void setAttack(int _attack);   		//修改攻击力
	int getAttack(void);           		//获得攻击力
	
	void 	setFd(int fd);           				//修改fd
	int 	getFd(void) const;             				//获得fd
	
	int 	getLifeStation(void);    				//获得生死状态
	void 	setLifeStation(int life);  				//修改生死状态
	
	void 	setLoadState(bool );				//将角色状态设置为登陆加载状态 tory	
	bool 	getLoadState();						//获得角色的的登陆加载状态 tory
	
	int	 	getAtk_range();							//获得角色攻击范围
	
	/**Evan add 2012.3.29   start**/
	int  getLifeUpperVal(void); 			//获得生命上限值
	void setLifeUpperVal(int _lifeUpperVal);//修改当前生命值  
	
	int  getLifeVal(void);      			//获得当前生命值
	void setLifeVal(int _lifeVal);   		//修改当前生命值
	int  getMagicUpperVal(void) ; 			//获得魔法上限值
	void setMagicUpperVal(int _magicUpperVal);//设置魔法值上限
	int  getMagicVal(void);       			//获得当前魔法值	
	void setMagicVal(int _magicVal);  		//修改当前魔法值
	
	int  getAttackAndDefense(void);       	//攻防总值
	void setAttackAndDefense(int _AttackAndDefense);
	               
	int getBufferCD(void);			 		//攻击CD
	void setBufferCD(int _bufferCD);
			 
	int getHited(void);						//命中
	void setHited(int _hited);
	                  
	int getCrit(void);        				//暴击
	void setCrit(int _crit);
	                        
	int getDodge(void);						//闪避
	void setDodge(int _dodge);
	               
	int  getTenacity(void);			 		//韧性
	void setTenacity(int _tenacity);
				
	int  getOutRatio(void);					//外攻比例
	void setOutRatio(int _outratio);
	
	                   
	int getInRatio(void);					//内攻比例
	void setInRatio(int _inratio);  
	
	              
	int getAttackRatio(void);				//攻击比例
	void setAttackRatio(int _attackratio);
	
	                
	int getDefenseRatio(void);				//防御比例
	void setDefenseRatio(int _defenseratio);
		
	int  getOutAttack(void);    			//外功攻击
	void setOutAttack(int _outattack);
	                     
	int   getInAttack(void);				//内功攻击
	void setInAttack(int _inattack);
                 
	int getOutDefense(void);  				//外功防御
	void setOutDefense(int _outdefense);
	
	int getInDefense(void);  				//内功防御
	void setInDefense(int _indefense);
	
	int getSec_Hurt(void);            		//秒伤害
	void setSec_Hurt(int _sec_hurt);
	int  getOutHurt(void);              	//外功伤害
	void setOutHurt(int _out_hurt);
	int  getInHurt(void);               	//内功伤害
	void setInHurt(int _inhurt);
	
	int getAttkType();
	
	int  getexpAgo(void);							//上一级升级所需经验 evan 2012.6.26
		
	string getFive_Elements(void);       	//五行属性
	void   setFive_Elements(string _five_elements);
	
	int    getFive_Elements_Value(void);  	//五行属性值
	void   setFive_Elements_Value(int _five_elements_value);
	
	void iEquip_holder(string _equipId,int iter);				//插入装备
	
	void oEquip_holder(int iter);								//删除装备
	
	void growExp(void);							//人物升级所需经验，人物升级时调用
		
	void setExpNow(int exp, int flag = 0);					//增加当前角色拥有经验（当前角色获得经验时调用）
	
	bool useExpNow(int _expnow);				//更新当前角色拥有的经验值
	
	void growUp(void);                   		//人物升级

	void herogrowup(void);						//玩家升级改变玩家自身属性  num为玩家一次升了几级 2012.7.4 evan
	
	int buffIncreaseAtt(int index,int value);		//buff药增加人物的属性	
	
	Map_Inform* getMap(void);
	void setMap(Map_Inform *map_now);

	
	/*evan add  2012.4.16 start*/
	Equipment* getWearEquip(int _index);   //角色身上装备属性，键：为身体部位名称，值：为装备Id
	void setWearEquip(int _index,Equipment* _equipment);
	Equipment* getEquip(string _identity);
	bool deleteEquip(string _identity);		//删除装备实例
	char* identity_to_goodsid(char* _identity);
	void msg_warehouse(char *msg);
	void insertEquip(Equipment *equipment);
	/*evan add  2012.4.16 end*/
	
	/*evan add  2012.4.18 start*/
	void setAttack_Request(int _attack_request);   //攻击请求是否接受
	int getAttack_Request(void);
			
	/*
		evan add 2012.4.20 start
		以下两个方法都是实现穿装备和卸装备改变角色属性值。
	*/
	void wear_equip(Equipment *equipment);   //所涉及到的参数为:1,当前角色实例指针；2，即将要穿上的装备实例指针。
	
	void drop_equip(Equipment *equipment);   //所涉及到的参数为:1,当前角色实例指针；2，即将要穿上的装备实例指针。
	
	list<Task*> getAccepted_Task_List(void);
	//玩家任务状态更新
	bool updateHeroTaskStatus(int needType, char* needId, int monsterLevel = 1);
	//发送任务状态更新消息
	void sendTaskStatusUpdateMsg(char* taskId, int statusType, char* statusId, int statusVal);
	//增加一条已接任务
	int incAcceptedTaskList(Task* _task);
	//删除一条已接任务
	Task* delAcceptedTaskList(char* _taskId);
	//在已接任务中查找任务
	Task* findAcceptedTaskList(char* _taskId);
	// set 和 get 玩家已接任务列表的最大容量
	void setMaxAcceptedSize(int _size);
	int getMaxAcceptedSize(void);
	
	/*修改副本房间信息*/
	void setFbRom(const char *newFbRom);                   //add chenzhen 6.12
	/*获得副本房间信息*/                             
	char* getFbRom(void);                              //add chenzhen 6.12

	//added by bison 6.19 
	void setEctypeNextOpen(string typeId);				//开启下一难度副本
	bool isOpenEctypeOK(string typeId);					//查询副本难度是否开启

	//added by Tory 9.27
	int enterInstCount_Day(string typeId);				//查询角色当天进入副本的次数
	
	void setMainSrc(char *_mainSrc);                  	//设置进入副本之前的地图id
	char* getMainSrc(void);                				//获得进入副本之前的地图id
	
	void addAttracMonId(string attracMonId);
	void delAttracMonId(string attracMonId);
	int  getAttracMonNum(void);
	
	bool   quit_scene();             					//退出游戏场景
	bool   enter_scene();
	bool   ent_fb_scene();	
	FiveElem *getFiveElem(void);						//外部获得五行属性接口
	
	bool getStillFlg(void);                             //获得定身标记值
	void setStillFlg(bool _flg);                        //设置定身标记值
	
	Meridian *getMerid(void);							//获得经脉指针的接口	
	
	PrivateStall stall;				//摊位结构体,不需要保存memcached
	
	char viewIdentity[50];
	
	void initTimer(int num);      // evan add 2012.7.19
	void deleteTimer(void);		  //evan add 2012.7.19
	bool isEntCamp(void);	      //是否在加入阵营；
	
	//taskList的初始化
	void memInitTask();

	//对完成任务位图进行操作
	void setFinishTaskMap(char* taskId);
	//清除单条任务的已完成状态
	void clrOneFinishTaskMap(char* taskId);
	//每天第一次登陆清空日更新任务的已完成位图
	void clrDayTaskFinishMap(void);
	//查看任务是否完成
	bool isTaskFinish(char* taskId);
	
	
	bool insertAttList(string id);						//将怪物id插入fightlist
	bool deleteAttList(string id);						//将怪物id从fightlist删除
	string getMonsterId(void);							//从fightlist中取得第一个
		
	bool useGoods(void);	/*物品操作 end add by jolly*/
		
	void setGuildInfo(Guild* _guild, int title);				//要设置帮派信息就一起设置
	void setGuildSigned(bool val);								//设置签到
	void clrGuildInfo();										//清除帮派信息也一起清除
	char* 	getGuildName();								//外部获取玩家帮会名
	char*	getGuildId();								//外部获取玩家帮派ID
	int 	getGuildTitle();							//外部获取玩家在帮会头衔
	Guild*	getGuild();									//外部获取所属帮派
	bool	getGuildSigned();							//查看是否帮派签到
	void incGuildDayRewardTime();
	
	void (Hero::*setFun[12])(int val);					//属性设置合集
	int (Hero::*getFun[12])(void);						//属性获取合集
	
	void selSetFun(int index, int val);					//选择属性设置合集中的一个
	int selGetFun(int index);							//选择属性获取合集中的一个
	void incAttr(int index, int val);					//人物属性的增
	void decAttr(int index, int val);					//人物属性的减少
	
	void setNewGuildSkillAdd(int index, int val);		//设置新等级的帮派技能附加属性，同时更新总附加值
	int getGuildSkillAdd(int index);					//获取当前帮派等级属性附加值
	int getGuildSkillTotalAdd(char*);					//帮派技能所加属性总值
	void clrGuildSkillAddTotal(void);					//去除玩家帮派技能附加属性
	void setInGuildWarRoom(bool flag, char* roomId = NULL);	//设置是否在帮派战房间中
	char* getGuildWarRoomId();							//获取帮派战房间ID
	bool isInGuildWarRoom();							//查看是否在帮战房间中
	void updateGuildInfo();								//更新帮派信息
	/*add text start*/
	map<string,int> getsuitlist(void);			//玩家身上的套装集合 evan add 2012.8.30
	void setsuitlist(map<string,int> _suitlist);	//玩家身上的套装集合 evan add 2012.8.30
	/*add text end*/
	Friend* getFriendInfo(void);						//获取好友信息实例指针,有疑问请RTX xhm;
 
	
	Warehouse* getWarehouse(void);	//jolly 2012.9.7
	bool isInFight(void);				//判断角色是否在战斗状态,若在战斗状态则返回true;
	void send_msg_attackFailed(void);
	
	/*奖励系统相关 jolly add 2012.9.6 start */
	
	//离线奖励
	int getOffline_time(void);				//上次下线时间
	int getOnline_time(void);				//本次上线时间
	void setOffline_time(int _offline_time);
	void setOnline_time(int _online_time);	
	int getOffline_exp(void);
	void setOffline_exp(int _offline_exp);
	void countOffline_exp(void);	

	//连续签到奖励
	int getLast_day(void);					//持续签到时间
	int getLast_day_flag(void);
	void setLast_day_flag(int _last_day_flag);
	void setLast_day(int _last_day);
	int getLast_exp(void);
	void setLast_exp(int _last_exp);
	
	//武陵盟主奖励
	int getChief_flag(void);
	void setChief_flag(int _chief_flag);
	
	//等级奖励
	int getLevelFlag(void);
	void setLevelFlag(int _levelFlag);
	//充值奖励
	bool isRechargeRewardReceive(int index);
	void receiveRechargeChange(int index);
	void canReceiveRechargeChange(int index);
	void judgeRechargeReward(void);
	/*奖励系统相关 jolly add 2012.9.6 end */	
	bool isFirstLogin();				//返回是否为一天中的第一次登陆
	void insertWarehouseEquipmentToBag(void);				//jolly add 9.14
	int expDrugUsedNum(int _num);
	void setDrugUsedNum(int _index,int _num);
	int getStatus(void);
	void setStatus(int _status);
	
	
	
	HeroCpyRecord* getCpyRecord(void);

	void send_msg_reward(void);

	/*将类中的数据存贮在memcached中 jolly start*/
	// void saveBagStruct(void);
	// void savePetStruct(int _index);
	// void saveMoneyStruct(void);
	// void saveWarehouseStruct(void);
	/*将类中的数据存贮在memcached中 jolly end*/
	void judgeSignFlag(void);				//判断本次登录是否拥有领取签到奖励的权限

	MysteriousBussiness* getMysteriousBussiness(void);
	void saveWarehouseEquip(void);
	void saveBagEquip(void);
	
	/*人物训练相关jolly 9.24 start*/
	void send_msg_att(void);
	void judgeExercise(void);		//根据等级判断人物训练的各种最大值
	void Exercise(void);			//人物训练
	void moneySaveExercise(void);		//游戏币保存训练结果
	void onKeySaveExercise(void);		//一键保存结果
	void goldSaveExercise(int index);		//元宝保存训练结果
	void savePhysique(void);			//保存体魄
	void saveWushu(void);				//保存武术
	void saveWill(void);				//保存意志
	void saveShenfa(void);				//保存身法
	void send_msg_exercise(void);		//发送锻炼信息 
	/*人物训练相关jolly 9.24 end*/
	void saveHeroEquip(int _index,char* identity,char* typeId,int flag);				//玩家穿装备,并保存入结构体
	void msg_wearEquip(char *msg,int len);					//玩家身上的装备信息返回
	bool destoryWearEquip(int index,string _identity);		//摧毁身上的装备
	
	/*生成技能消息*/
	string formSklMsg(void);
	void send_bag_msg(char *msg,int len);
	long getTaskState();
	int SetInTskStFstTenBit();
	int SetInTskStScdTenBit();
	int setTskStOneBit(int index);
	int setTskStSomeBit(int val);
	int clrTskStOneBit(int index);
	int clrTskStSomeBit(int val);
	//放弃NPCboss任务
	void abandTaskBySubType(int subType, bool offlineFlag);
	//
	void setTaskNeedKillNpcBossId(char *bossId = NULL);
	//
	char* getTaskNeedKillNpcBossId();
	
	/*出战宠物计时器 jolly 10.25 start*/
	void initPetTimer(void);	
	void stopPetTimer(void);
	void restartPetTimer(void);
	/*出战宠物计时器 jolly 10.25 end*/
	char* getPetMatingCo(void);			//宠物繁殖合作者
	void setPetMatingCo(char* _heroid);			//宠物繁殖合作者
	int getMatingInviteTime(void);			//邀请繁殖开始时间
	void setMatingInviteTime(int _time);			//邀请繁殖开始时间
	int getMatingFlag(void);			//宠物繁殖标志 0为无邀请,1为已邀请,2为正在繁殖
	void setMatingFlag(int _flag);			//宠物繁殖标志 0为无邀请,1为已邀请,2为正在繁殖,3为锁定,4为确认
	int getMatingPetIndex(void);			//将要繁殖的宠物索引
	void setMatingPetIndex(int _index);			//将要繁殖的宠物索引
	int getMatingGoods_index(void);			//繁殖丹在背包中索引
	void setMatingGoods_index(int _index);			//繁殖丹在背包中索引
	int getLuckyGoods_index(void);			//灵宠丹在背包中的索引
	void setLuckyGoods_index(int _index);			//灵宠丹在背包中的索引
	int getLuckyGoods_number(void);			//灵宠丹的数量
	void setLuckyGoods_number(int _number);			//灵宠丹的数量

	MidasTouch *getMidasTouch(void);
	
	Point getBeforePiexPt(void);
	
	void setBeforePiexPt(Point beforePt);
		
	//使用vip功能时，必须先调用此函数检测vip的到期时间
	bool isVip();
	//vip剩余时间
	// int vipRemainTime();
	
	/*获得跳转地图bool值*/
	bool getWalkingFlg(void);
	
	/*修改bool值*/
	bool setWalkingFlg(bool _judFlg);
	
	
	void initTongBuTimer(void);
	void stopTongBuTimer(void);
	
	
	
	/*获得角色在副本里面复活次数*/
	int getCpyRevTme(void);
	
	/*角色在副本里面复活次数自增1*/
	void addCpyRecTme(void);
	
	/*初始化副本里面复活次数*/
	void initCpyRecTme(void);
		
	//若完成武林目标 ，则根据对应索引修改武林目标完成状态 ，参数 容器下标
	bool setWulinTarget(int page,int id);	
	//领取奖励,更改目标标志为2
	bool receiveTargetSuccess(int page,int id);
	
	//取bag指针
	Bag* getBag(void);     								//jolly added 6.25
	//取moeny指针
	Money* getMoney(void);								//jolly added 7.10
	//取pet_box指针
	Pet_Box* getPetBox(void);							//jolly added 7.16
	//取online_reward指针
	Reward_Online* getRewardOnline(void);
	//取ride指针
	Ride *getRide(void);
	
	void startHappyTimer();										//开始娱乐
	void endHappyTimer(int flag = 0);										//娱乐结束
	int happyAdd();												//单位时间娱乐收获
	int happyCheck(const char *oldMapId, const char *newMapId);
	
	//flag = 0: 元宝；flag = 1:绑定元宝；flag = 2:银两；flag = 3:绑定银两
	// void setMoney(int flag, int val);					//设置金钱
	bool increaseMoney(int flag, int val);				//增长金钱
	bool useMoney(int flag, int val);					//使用金钱
	
	/*红名装备掉落*/
	void dropEquip(Hero *redHero);
	
	
	//更新武林目标
	void updataSingleTarget(int page,int id);
	//检查索引为index的目标是否完成		若完成返回false 
	bool isTargetFinish(int page,int id);
	
	//取扣出罪恶值的标志
	int getCrimCount(void);
	void setCrimCount(int _crimCount);
	
	//取扣出耐力值的标志
	int getPowerCount(void);
	void setPowerCount(int _powerCount);
	
	/*掉落装备*/
	bool dropEquipInst(string _identity);
	
	/*捡起掉落的装备放到bag里面*/
	bool pickDropEquipment(Equipment *equip);
	
	/*判断是否掉装备*/
	bool isDropEquip(void);
	//返回摊位
	// PrivateStall getPrivateStall(void);
	// void setPrivateStall(PrivateStall _stall);
	
	void startMoveTimer();
	void stopMoveTimer();
	int getSpeed();
	int getLastSpeed();
	void stopMove();
	void setSpeed(int speed);
	//设置成当前速度
	void setLastSpeed(int speed);
	int startBufOrDebuffTimer(char *heroId, char *skillId, int skillLevel);
	void stop_buff_debuff_timer(int flag = 0);
	void stop_buff_debuff_by_index(int index);
	int getIndexByState(int state);
	
	//节日活动相关
	int getFestivalRewardFlag(void);
	void setFestivalRewardFlag(int _festivalRewardFlag);
	int startHeroSkillAnimationTimer(float time);
	
	//猜拳相关 jolly 12-26
	void winFingerGuessingGame(void);			//赢了一局
	void joinFingerGuessingGameAi(int money);	//加入与电脑对战猜拳
	void joinFingerGuessingGame(int money);		//加入与人对战猜拳
	void exitFingerGuessingGame(void);			//退出猜拳
	void exitFingerGuessingGameInit(void);		//退出猜拳,数据还原
	void otherExitFingerModifyMineData(void);	//对方退出猜拳,修改我的数据
	void startFingerGuessingGame(void);			//猜拳,点击开始按钮
	void fingerGuessingAi(int other);			//猜拳ai逻辑,返回ai结果,目前暂定为纯随机 1为石头,2为剪刀,3为布
	void fingerGuessGamePlayerFight(int mine);	//玩家对战,猜拳逻辑
	int judgeFingerGuessingGameWin(int finger1,int finger2);		//决定猜拳输赢
	
	//人物属性增加
	bool addAttr(int flag, int val);
	int startCollectTimer(int collectTime, char* collectId);
	int stopCollectTimer(int reason);
	//开启玩家复活倒计时
	int startRevivalTimer(int revivalTime);
	//停止玩家复活倒计时
	int stopRevivalTimer();
	//在采集中
	bool isInCollecting();
	
	//骑马准备
	int prepareRide();
	//打断乘骑过程
	int breakRide();
	//开始骑乘
	int startRide();
	//下马
	int stopRide();
	//获取骑乘状态
	int getRideState();
	
	/*使用激活码,默认非公会激活码*/
	void useActiveCode(char *activeCode,int type = 0);
	
	/*判断是否已使用激活码，如果是则返回真*/
	bool isActiveCodeUse(void);

	//更新日常
	void updateHeroDaily(void);
	//重新计算人物属性
	void reCountHeroArr(void);
	//设置hero参加了一次帮派战
	void setHaveJoinedGuildWar();
	//判断玩家可以参加帮派战
	bool canJoinGuildWar();

	//玩家首次登录送时装
	void firstIntoGame(void);
	//非会员是否可以免费世界喊话
	bool ifNotVipCanSpeak(void);
	//喊话成功,免费喊话次数-1,同时返回剩余的返回次数
	int getWorldSpeakTimes(void);

	//获取当前用户所在服务器的区编号
	int 	getArea();		
	
	void setVipRights(int stage,bool isMemCahed = false);
	
	void judgeVipLevel(void);

	/*创建角色时，开启第一层塔的第一层*/
	void initNowTowerId(void);
	
	/*初始化黑木崖数据*/
	void initTowerLayerRecord(void);
	
	/*获得黑木崖数据*/
	TowerLayerRecord* getTowerLayerRecord(void);	
	
	/*原先的创建角色时，开启第一层塔的第一层*/
	void initOldNowTowerId(void);
	
	/*调整体力值*/
	void adjustFatigue(void);
	
	/*设置体力值*/
	void setFatigueVal(int _fatigueVal);
	
	/*判断是否可以购买体力值*/
	bool isCanBuyFatigue(void);
	
	/*计算防御伤害率*/
	double ctnDefenseRatio(bool isInnerAttack);
	
	/*计算防御伤害率*/
	double ctnTenacityRatio(void);
	
	/*设置角色在哪个层*/
	void setChoiseLayerId(char *_choiseLayerId);
	
	/*获得角色在哪个层*/
	char* getChoiseLayerId(void);
	
	/*把可进层数组置0*/
	void initZoreLayerFlg(void);
	
	/*更具当前层次设置每层可进入状态*/
	void initTowerLayerFlg(void);
	
	//取vip等级
	int getVipStage(void);
	
	//宠物技能点增加
	void addPetSkillExp(int addVal);
	
	int getHeroSkillExp();
	void addHeroSkillExp(int addVal);
	int useHeroSkillExp(int useVal);
	
	//体验vip
	void startTestVip(void);
	void setVipData(int stage,bool isMemCahed = false);
	
	int getInternalForcesLevel();
	bool internalForcesLevelUp();
	int getInternalForces();
	void addInternalForces(int value);
	bool useInternalForces(int value);
	int getInternalForcesExpNow();
	void setInternalForcesExpNow(int newExp);
	int getInternalForcesUpgradeNeedExp();
	void setInternalForcesUpgradeNeedExp(int nextExp);
	int getInternalForcesBrushExpTimes();
	void incInternalForcesBrushExpTimes();
	int getGoldBrushExpTimes();
	void incGoldBrushExpTimes();
	//判断装备是否有12件紫装，给相应头衔，基础达标者
	void titleOfPurpleEquip(void)	;
	
	//判断装备是否有4件橙装，给相应头衔，名牌
	void titleOfOrangeEquip(void)	;
	
	//刷新帮派任务
	void refreshGuildTask();
	
	
	//加入聊天
	void insertGroupId(const char *gorupId);
	
	//退出聊天
	void eraseGroupId(const char *gorupId);
	
	//退出时
	void clearChatSet();
	
	bool isPassTowerLayer(char *towerLayerId);
	
	int getNowDay(void);
	void setNowDay(int _nowDay);
	
	int getAllowSign(void);
	void setAllowSign(int _allowSign);
	
	int getAllowSignGold(void);
	void setAllowSignGold(int _allowSignGold);
	
	int getVipCpyFreshNum();
	
	void setTaskPassChapt(int chapt);
	
	int isChaptTaskPass(int chapt);
	
	bool isTaskChaptReward(int chapt);
	
	int getTaskChaptReward(int chapt);
	
	void setGotTaskChaptReward(int chapt);
	
	const char* getTeamerId()const;
	
	void setTeamerId(const char *_teamerId);
	
	void adjustTeamerId(void);
	
	void offLineTeam();
	
	void initTeamerId(void);
	
	void brushTeamStation();
	
	int getAllFourDiamonNumber();		//取身上所有装备的4级宝石数量

	//上线头衔检查（4个）
	void checkTitle(void);
	
	
	int getCycleTaskLevel();
	void updateCycleTaskLevel();
	int getCycleLoop();
	int getTaskFinishFlag(char* cycleTaskId);
	void setCycleTaskAccepted(char* cycleTaskId);
	void viewCycleTaskInfo();
	void setCycleTaskFinish(char* cycleTaskId);
	void setOneCycleTask(int index, char* newTaskId);
	void incCycleTaskLoop();
	void initCycleTask();
	void clearLastLoopTask();
	double getCycleTaskRewardFactor();
	
};

int showHeroGrow(MemHero* mem_data_hero, char *outfile);

#endif

