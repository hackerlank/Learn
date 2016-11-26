/*****************************************
* Date: 	2012.9.11
* Author: 	Tory
* Description: 用于声明或定义各种工具类的实例对象，类对象的定义实现在src/test.cpp中；
* @@@@@@@@@@@  当这些变量作为全局变量被调用时，需加extern进行引用声明
******************************************/
#include"libev.h"
#include"map_inform.h"
#include"monster_configuration.h"
#include"hero_configuration.h"
#include"skill_configuration.h"
#include"five_configuration.h"
#include"hatValRue.h"
#include"role.h"
#include"pick.h"
#include"team.h"
#include"equip_config.h"
#include"task_configuration.h"
#include"npc_configuration.h"
#include"droplist_configuration.h"
#include"ride_config.h"
#include"task_touch_configuration.h"
#include"ectype_reward_info.h"
#include"TD_Instancing.h"
#include"pet_config.h"
#include"task_goods_info.h"
#include"petSkill_config.h"
#include"instancing_manage.h"
#include"cpy.h"       //by chenzhen 4.23
#include"goods_config.h"
#include"cpyLimit.h"      //add by chenzhen 2012.06.11
#include"reward_level_config.h"
#include"monsterBase.h"
#include"reward_recharge_config.h"
#include<list>
#include"ointment.h"
#include"timerContainer.h"
#include"groupBrush.h"
#include"skillBase.h"
#include"mysteriousBussiness_config.h"
#include "campWarManagement.h"
#include"suit.h"
#include "commodity.h"
#include "guild_asist.h"
#include"guild_war_asist.h"
#include "rankInfo.h"
#include"takeGoods.h"
#include"wagon.h"
#include"bottle.h"
#include"trap.h"
#include "data_structure_struct.h"
#include "mail_systerm_interface.h"
#include "mailSysterm.h"
#include"guild_activity.h"
#include"vip.h"
#include"revival_config.h"
#include"map_cpy.h"
#include"map_src.h"
//#include"filter_dirty_words.h"
#include"my_memcached.h" 
#include"dailyActive.h"
#include"heroCpyRecord.h"
#include "my_mem_group.h"
#include "guild_club.h"
#include "reward_online_config.h"
#include"cpyManager.h"
#include"monsterTool.h"
#include"vipBaleRoomLimit.h"
#include"partyRoomLimit.h"
#include"hero_skill.h"
#include"activeAsist.h"
#include"partyBaseCampLimit.h"
#include"statuaryBase.h"
#include"statuaryHero.h"
#include"chatGroupManager.h"

class Task_Touch_Configuration;

/**角色登陆的服务器区号**/
int from = 0;
/**用于操作game_server连接的所有缓存服务器的接口类对象，全局变量 added by Tory**/
MyMemGroup* mem_group = NULL;

/**用于连接单个缓存服务器的接口类对象声明，全局变量 added by Tory**/
// MyMemcache* mem_operate = NULL;

/**用于同名检查缓存的操作类指针实例引用声明**/
MyMemcache* mem_operate_nickname_inspection = NULL;

//cdkeymemcached指针
MyMemcache* cdkeyMemcached = NULL;

/**用于读取安全策略文件的缓存 added by Tory**/
char cross_domain_str[256] = {0};

/** 缓存服务器配置表，用于game_server连接的单个memcached server added by Tory**/
map<string, Mem_configure> mem_configure_table;

/** mem_group配置表，用于game_server连接多个memcached server added by Tory**/
map<int,Mem_configure*> mem_group_table;

/** 邮件数据存放路径 added by Tory**/
string mail_data_url_T;

/**全局容器，邮件处理队列 tory 2012.9.20**/
list<string>  handle_quene;

//ev_timer mail_handle_timer;//邮件处理定时器

/**用于存储服务器当前处理的socket连接fd**/
int sock_fd;

/**初始化命令处理的函数**/
vector<FUN>command_map(MAX_TYPE_COMMAND*MAX_EACH_TYPE_COMMAND);

/**注册类型退出标志（即不用通知其他玩家），此处初始化为1**/
int flag_registe_type_exit=1;

/**初始化libev的事件循环**/
struct ev_loop *loops;

/**	与套接字描述符绑定的消息接收队列 **/
map<int, Message_Receive>   message_queue;

/**	空闲用户列表,用于玩家登陆 **/
list<Role*> idle_role_list;

/**	空闲角色列表,用于玩家选择角色进入游戏 **/
list<Hero*> idle_hero_list;
/*
	map<MAP_ID_TYPE,Map_Inform*>mapId_connect_map:把地图的id跟地图实类相关联
*/
map<string,Map_Src*>mapId_connect_map;

/*
玩家升级所需要的经验值
*/
map<int,int> exp_upgrade_list; //evan add 2012.9.19
/*
	Hero_Configuration *hero_configuration:一个简单hero类，用来读取且保存配置文件的内容，用于保存读取的配置信息
*/
Hero_Configuration *hero_configuration;


/*
	map<string,Monster_Inform*>	monTypeId_connect_property:把每类怪物的id跟他的怪物配置信息类的实例指针相对照，用于保存配置信息
*/
map<string,Monster_Inform*>	monTypeId_connect_property;
/*
	TileWidth,TileHeight:网格的宽和高（像素），可以从读取配置文件里面读取，便于改写
*/
int TileWidth=64;
int TileHeight=32;

// 账号获取GM信息的匹配字符
string GM_verify_password;
//服务器名
char server_name[10]={'\0'};

/*
*	全局变量，角色(Hero)ID索引Hero对象指针的map容器
*	管理所有已初始化的Hero对象，heroId可通过Role对象里
*/
map<string, Hero*> heroId_to_pHero;

/*
*	全局变量，当前fd索引Role对象指针的map容器
*	管理在线用户
*/
map<int, Role*> fd_to_pRole;

HatValRue *hatValRue;          //仇恨值规则类实例指针

// add by chenzhen 2012.4.23 start
map<string,Map_Cpy*> cpyMapConf; //副本地图编号id对应副本地图实例指针（存配置文件）

/*
*	全局变量，技能(skill)ID索引技能配置对象指针的map容器，
* 	管理游戏角色所有技能配置信息
*/
map<string,Skill_Configuration*>id_to_skill;

map<string,Five_Configuration*>id_to_five;
/*
	by cookie 队伍容器
*/
map<string,set<string > > tid;                //根据组队目的存放teamid

// map<string,set<string> > pid;				//根据组队目的存放角色id

map<string,Equip_config*>id_to_equip; //装备模版类容器


map<string,Task_Configuration*> id_to_task; //任务全局变量   Evan add

map<string,Task_Touch_Configuration*> id_to_touch; //任务触发条件 added by bison

map<string,Npc_Configuration*> 	id_to_npc;  //NPC全局变量   Evan add

map<string,DropList_Configuration*> id_to_dropgoods;  //掉落列表全局变量 jolly add

map<string, Ectype_Reward_Info*> idNum_2_rewardInfo;	//副本奖励信息的全局变量 added by bison
map<string, vector<string> > type_2_goodsList;			//副本奖励物品序列的全局变量 added by bison
map<string, TD_Conf_T> id_2_tdConf;					//副本配置信息，根据副本id来索引 added by bison

map<string,Ointment *>id_to_ointment; //物品配置类容器 cookie 
Instancing_manage *Inst_MNG;							//副本管理类的全局变量		added by bison
int Rd = 0;   //add chenzhen 6.1,用在巡逻怪寻点上，防止产生雷同的随机数
map<string,Pick*> goods_to_hero;  //拾取物品 jolly add
 
//add jolly start
// list<ev_timer*> goods_timer;
// list<ev_timer*> pick_timer;
// list<string> time_flag;
// list<string> three_flag;
//add jolly end

map<string,Pet_Config*> id_to_pet;		//add by jolly

map<string,Pet*>id_to_activePet;		//add by jolly 2012.8.30

/*副本限制类*/
map<string,CpyLimit*> cpyId_to_cpyLimit;               //add chenzhen 2012.06.11 

/*刷怪批次*/
map<string,GroupBrush*> groupBrush;

map<string, TaskGoodsInfo*> id2taskGoodsInfo;			//added by bison 2012.7.6

map<string,SkillBase*> monster_skill_map;

map<string,SkillBase*> monSkiInst;                    //Boss怪技能（不能放在怪物类里头）

map<string,const jumpId_infor*> jumpId2mapInfo;				//jumpID对应的信息；

HeChengConfig g_heChengConfig;			//宝石合成配置数据
map<string,PetSkill_Config*> id_to_petSkill;		//add by jolly 2012.7.31

map<string,Goods_Config*> id_to_dj;				//add by jolly 2012.8.14
map<string,Goods_Config*> id_to_cl;				//add by jolly 2012.8.14

ev_timer *myTimer;
struct timeval myTime;
int mySecond;				//秒--除了my_time.h以外的其他文件千万不要用，否则你会后悔
int myMin;					//分
int myHour;					//时				
int myWeekDay;				//周几

campWarManagement campWarController;			//阵营战管理器；		

// vector<HeroBasicData *> heroBasicDataContain;tory_01_16

map<string,Suit*>	suit_lists;		//套装集合的全局变量  evan add 2012.8.30


set<string>shop; //商城
// map<string ,PrivateStall* > onLineStall; //在线摊位
map<string ,PrivateStall* >	offLineStall;//离线摊位

//帮派名查帮派ID
map<string, string> name_2_guildId;
/*帮派名索引帮派
 *			--id_2_guild[0]支派阵营的帮派集合
 *			--id_2_guild[1]宗教阵营的帮派集合
 *			--id_2_guild[2]游侠阵营的帮派集合
 *			--id_2_guild[3]所有阵营的帮派集合
 */
map<string, Guild*> id_2_guild[4];
 
/*帮派排名榜
 *			--guildRankList[0]支派阵营的帮派排名榜
 *			--guildRankList[1]宗教阵营的帮派排名榜
 *			--guildRankList[2]游侠阵营的帮派排名榜
 *			--guildRankList[3]所有阵营的帮派排名榜
 */
vector<GuildSortItem> guildRankList[4];

/*可采摘道具*/
map<string,TakeGoods*> takeGoodsConfMap;

/*马车配置文件*/
map<string,Wagon*> wagonConfMap;

/*马车实例*/
map<string,Wagon*> wagonInstMap;

/*奖励系统 jolly 2012.9.10 start*/
map<int,Reward_level_config*>id_to_reward_level;
map<int,Reward_recharge_config*>id_to_reward_recharge;
/*奖励系统 jolly 2012.9.10 end*/

/*瓶罐的配置文件*/
map<string,Bottle*> bottleConfMap;

/*陷阱的配置文件*/
map<string,Trap*> trapConfMap;



map<string , map <string ,Point > > npc; //npc容器

//帮派活动全局数据
map<string, GuildActivity*> id_2_guildAct;

//gm 容器
set<string> heroid_to_gm;

//全局id,保存所有注册用户的Id；
vector<string> globalHeroId;	
map<string,string>nickName2heroId;

int	nickNameCounts;
int preNickNameCounts;
vector<string> heroNameCheckName;
vector<string> heroNameCheckHeroId;
NickName2heroIdHash heroNameCheckHash; //用于角色创建选择同名检查；


/*GM账号管理 jolly start*/
//禁言列表
set<string> ban_speak;
//冻结交易列表
set<string> freeze_money;
//封号列表
set<string> lock_hero;
/*GM账号管理 jolly start*/

ev_timer *peaceTimer;
ev_timer *CampWartimer;	

map<string ,VipDataInitial> vipDataStore;

set<string>allTitle; //所有头衔容器

map<string,string> mapIdToGoodsId; //副本id 找副本令id
GuildWarAsist *guildWarManage;			//帮派战管理

PitchTerm pitchTerm; //地图id 找摆摊区域

DayLmtFindGroup_T dayLmtGroupForAll;	//全局的日限制项目

set<string> guildTaskList;				//帮派任务列表
set<string> dayTaskList;				//日常任务
set<string> campTaskList;				//阵营任务

map<string,Revival_Config*> mapId_to_revival;		//复活点坐标信息

map<string,MysteriousBussiness_Config*> stage_to_mysteriousBussiness; 	//神秘商人配置文件 10.11

set<string> dirtyWordsPack;					//脏词库
set<string> illegalCharPack;				//命名非法符号

MapType_T mapTypeInfo;									//地图类型信息；

map<string,DailyActive*> dailyActiveConfMap;

map<string, wagonColorRank_T*> wagonId_2_rankRate;	//每种马车颜色刷新率
map<string, string> heroId_2_colorWagon;			//玩家有彩色马车

list<CpyStateFlg> CPYEntState;                   //副本通关顺序

// map<string,TowerTeam*>towerDefTeamInfo;			//塔防组队容器；

// list<TowerTeam*>idleTowerDefTeam;				//空闲塔防房间容器；

map<string,int> goodsId_to_price; 			//帮派商店

MidasTouchNumber midasTouchNumber;				//点石成金奖励

map<string, GuildFeastConf_T> feastId_2_feastConf;	//帮派盛宴配置

map<string,Reward_online_config*> id_to_reward_online;			//在线奖励

set<string> innerIPSet;

CpyManger *cpyManger;                               //副本动态管理器


map<string,Equipment*> dropEquipMent;

map<string,int> goodsId_to_price_shengWang; 		 //声望商店

vector<string> wuLinTarget;

map<string,MonsterTool*>toolToMonster;            //道具对应刷出副本*/

map<string,MonsterTool*> toolMonsterIdToInst;     //道具刷出的怪管理容器

map<string,Map_Src*> confVipRoom;                //vip包厢地图场景配置

map<string,VipBaleRoomLimit*> mapIdToVipBaleRomLimit;   //vip包厢管理

map<string, MailSysterm*> mail_map;	//tory add 

map<string,Map_Src*> confPartyRoom;              //帮派地图

map<string,PartyRoomLimit*> mapIdToPartyRomLimit;      //帮派房间管理

map<string, HeroSkill*> skillId_2_heroSkill;		//角色技能

map<int,list<Hero*> >	fingerGuessingGamePerson;			//等待猜拳中的hero


 
DurCampTme durCampTime;                              //阵营活动持续时间数据结构

/*金陵普通副本npc传送点*/
Point JLGENPT;

/*开封普通副本npc传送点*/
Point KFGENPT;

/*开封帮派副本npc传送点*/
Point KFPARPT;

/*金陵帮派副本npc传送点*/
Point JLPARPT;

/*角色离帮派副本npc传送点多少距离才能传送*/
int LIMPRTRAG;

/*角色离普通副本npc传送点多少距离才能传送*/
int LIMGENRAG;

/*商城活动 专区*/
map<string,int> activeShop_gold;

/*消费奖励*/
// Reward_UseGold rewardUseGold;

/*帮派大本营*/
map<string,PartyBaseCampLimit*> mapIdToCampRomLimit;

/*帮派大本营地图配置*/
map<string,Map_Src*> confCampRoom;   

/*帮派等级对应的大本营地图id*/
map<int,string> levelToMapId;     

/*帮派最高等级*/
int partyHightestLevel = 5;    

//经验奖励配置
map<int,RewardFactor> factor_reward;

/*外部激活码对应goodsid容器*/
set<AvtiveCode> outerActiveCodeMap;

/*内部部激活码对应goodsid容器*/
set<AvtiveCode> innerActiveCodeMap;

//活动匹配物品
FestivalGoods festivalGoods;

//双倍奖励的配置文件信息保存
ActiveDouble activeDouble;

//双倍奖励
int yabiaoDouble=1;							//活动双倍经验,初始值为1,到了活动时间,设为2
int shengyanDouble=1;						//活动双倍经验,初始值为1,到了活动时间,设为2
int daguaiDouble=1;							//活动双倍经验,初始值为1,到了活动时间,设为2

bool isSetDishTodayActiveFlg = false;        //是否已经设置帮派盛宴活动是否为今天的标记值，是表示已设置
                 
         
//交易装备容器
map<string,set<Equipment*> > bussinessEquip;

map<string,StatuaryBase*> vocationToStatuaryBaseConf;     //职业id为键，替身雕像实例指针为值

map<string,StatuaryHero*> statuaryTypeToStatuaryHero; //以头衔id为键，雕像实例指针为值

list<string> strtuaryTitleIdList;                     //获得雕像资格的头衔列表
set<Point> statuaryPtSet;                             //雕像树立坐标点

//关服倒计时
int shutDownCount;

//服务器开服时间
int serverOpenTime;

struct tm* timeNow;

//记录阵营人数
map<int,int> campNumber;
//坐骑配置
map<string,Ride_Config*> id_to_ride;

VIPRewardData vipRewardData[20];

RideSkill_Config rideSkill_config[10];

Ride_Special_Skill_Config rideSpecialSkill_config[3];

Pet_ZhanLi pet_zhanli[10];

Pet_Xidian pet_xidian;

map<string,map<string,string> >towerMapConf;          //黑木崖配置文件

Equip_Operator equip_operator[51];

int dataVersion;

LevelRewardData levelRewardData[10];

RankReward rankReward;

char sendName[30];
char sendTitle[30];
char sendFlower[1024];
char receiveFlower[1024];
char recharge[1024];
char consume[1024];
char heroRankContent[1024];
char petRankContent[1024];
char rideRankContent[1024];
char shutDownContent[1024];

ev_timer shutDownTimer;

ChatGroupManager *chatManager;

EveryDaySignRewardData signRewardData[30];

WuLinTargetConfig wuLinTargetConfig[10];

map<string,string> cdkey_to_goodsid;

set<string> freeWorldTalk;

int shutDownRemainTime;