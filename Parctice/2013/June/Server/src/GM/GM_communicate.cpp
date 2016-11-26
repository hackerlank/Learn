#include "user_role_accept_task.h"
#include "GM_communicate.h"
#include"cpyAsist.h"
#include "guild_asist.h"
#include"libev.h"
#include"map_inform.h"
#include"monster_configuration.h"
#include"hero_configuration.h"
#include"skill_configuration.h"
#include"five_configuration.h"
#include"hatValRue.h"
#include"role.h"
#include"function_read_configuration_files.h"
#include"pick.h"
#include"team.h"
#include"equip_config.h"
#include<sstream>
#include"task_configuration.h"
#include"npc_configuration.h"
#include"droplist_configuration.h"
#include"task_touch_configuration.h"
#include"ectype_reward_info.h"
// #include"TD_Instancing.h"
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
#include "money_operator.h"
#include "friendInfoManagement.h"
#include "guild_asist.h"
#include"guild_war_asist.h"
#include "rankInfo.h"
#include"takeGoods.h"
#include"wagon.h"
#include"bottle.h"
#include"trap.h"
#include "my_memcached.h"
#include "data_structure_struct.h"
#include "mail_systerm_interface.h"
#include"guild_activity.h"
#include"vip.h"
#include"revival_config.h"
#include"map_cpy.h"
#include"map_src.h"
//#include"filter_dirty_words.h"
#include"my_memcached.h" 
#include"dailyActive.h"
#include"heroCpyRecord.h"
// #include "towerDefTeam.h"
#include "guild_club.h"
#include "reward_online_config.h"
#include"cpyManager.h"
#include"monsterTool.h"
#include "mailSysterm.h"
#include"heroCpyRecord.h"
#include"teamManager.h"
using namespace std;
extern char server_name[10];

/** 缓存服务器配置表 added by Tory**/
extern map<string, Mem_configure> mem_configure_table;

	/**全局容器，保存在线的玩家所创建的角色拥有的邮件数据，Tory 2012.9.17**/
extern map<string, MailSysterm*> mail_map;	

	/**全局容器，邮件处理队列 tory 2012.9.20**/
extern list<string>  handle_quene;
extern ev_timer shutDownTimer;
	/**初始化命令处理的函数**/
extern vector<FUN>command_map;
extern set<string> freeWorldTalk;
	/**	与套接字描述符绑定的消息接收队列 **/
extern map<int, Message_Receive>   message_queue;

	/**	空闲用户列表,用于玩家登陆 **/
extern list<Role*> idle_role_list;

	/**	空闲角色列表,用于玩家选择角色进入游戏 **/
extern list<Hero*> idle_hero_list;
extern int sock_fd;
	/*
	玩家升级所需要的经验值
	*/
extern map<int,int> exp_upgrade_list; //evan add 2012.9.19

extern map<string,Monster_Inform*>	monTypeId_connect_property;

extern char heroRankContent[1024];
	/*
	*	全局变量，角色(Hero)ID索引Hero对象指针的map容器
	*	管理所有已初始化的Hero对象，heroId可通过Role对象里
	*/
extern map<string, Hero*> heroId_to_pHero;

	/*
	*	全局变量，当前fd索引Role对象指针的map容器
	*	管理在线用户
	*/
extern map<int, Role*> fd_to_pRole;
extern int shutDownRemainTime;
	// add by chenzhen 2012.4.23 start
extern map<string,Map_Cpy*> cpyMapConf; //副本地图编号id对应副本地图实例指针（存配置文件）


	//  add by chenzhen in 4.23 end

	/*
	*	全局变量，技能(skill)ID索引技能配置对象指针的map容器，
	* 	管理游戏角色所有技能配置信息
	*/
extern map<string,Skill_Configuration*>id_to_skill;

extern map<string,Five_Configuration*>id_to_five;
	/*
		by cookie 队伍容器
	*/
extern map<string,set<string > > tid;                //根据组队目的存放teamid

// extern map<string,set<string> > pid;				//根据组队目的存放角色id


extern map<string,Equip_config*>id_to_equip; //装备模版类容器


extern map<string,Task_Configuration*> id_to_task; //任务全局变量   Evan add

extern map<string,Task_Touch_Configuration*> id_to_touch; //任务触发条件 added by bison

extern map<string,Npc_Configuration*> 	id_to_npc;  //NPC全局变量   Evan add

extern map<string,DropList_Configuration*> id_to_dropgoods;  //掉落列表全局变量 jolly add

extern map<string, Ectype_Reward_Info*> idNum_2_rewardInfo;	//副本奖励信息的全局变量 added by bison
extern map<string, vector<string> > type_2_goodsList;			//副本奖励物品序列的全局变量 added by bison
extern map<string, TD_Conf_T> id_2_tdConf;					//副本配置信息，根据副本id来索引 added by bison

extern map<string,Ointment *>id_to_ointment; //物品配置类容器 cookie 
	
extern map<string,Pick*> goods_to_hero;  //拾取物品 jolly add

extern map<string,Pet_Config*> id_to_pet;		//add by jolly

extern map<string,Pet*>id_to_activePet;		//add by jolly 2012.8.30

	/*副本限制类*/
extern map<string,CpyLimit*> cpyId_to_cpyLimit;               //add chenzhen 2012.06.11 

	/*刷怪批次*/
extern map<string,GroupBrush*> groupBrush;

extern map<string, TaskGoodsInfo*> id2taskGoodsInfo;			//added by bison 2012.7.6

extern map<string,SkillBase*> monster_skill_map;

extern map<string,SkillBase*> monSkiInst;                    //Boss怪技能（不能放在怪物类里头）

extern map<string,const jumpId_infor*> jumpId2mapInfo;				//jumpID对应的信息；

extern map<string,PetSkill_Config*> id_to_petSkill;		//add by jolly 2012.7.31

extern map<string,Goods_Config*> id_to_dj;				//add by jolly 2012.8.14
	
extern map<string,Goods_Config*> id_to_cl;				//add by jolly 2012.8.14

extern map<string,Suit*>	suit_lists;		//套装集合的全局变量  evan add 2012.8.30


extern set<string>shop; //商城
	// map<string ,PrivateStall* > onLineStall; //在线摊位
extern map<string ,PrivateStall* >	offLineStall;//离线摊位

extern int shutDownCount;

	//帮派名查帮派ID
extern map<string, string> name_2_guildId;
	/*帮派名索引帮派
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

	/*可采摘道具*/
extern map<string,TakeGoods*> takeGoodsConfMap;

	/*马车配置文件*/
extern map<string,Wagon*> wagonConfMap;

	/*马车实例*/
extern map<string,Wagon*> wagonInstMap;

	/*奖励系统 jolly 2012.9.10 start*/
extern map<int,Reward_level_config*>id_to_reward_level;
extern map<int,Reward_recharge_config*>id_to_reward_recharge;
	/*奖励系统 jolly 2012.9.10 end*/

	/*瓶罐的配置文件*/
extern map<string,Bottle*> bottleConfMap;

	/*陷阱的配置文件*/
extern map<string,Trap*> trapConfMap;



extern map<string , map <string ,Point > > npc; //npc容器

	//帮派活动全局数据
extern map<string, GuildActivity*> id_2_guildAct;

	//gm 容器
extern set<string> heroid_to_gm;

	//全局id,保存所有注册用户的Id；
extern vector<string> globalHeroId;	
extern map<string,string>nickName2heroId;

extern vector<string> heroNameCheckName;
extern vector<string> heroNameCheckHeroId;


	/*GM账号管理 jolly start*/
	//禁言列表
extern set<string> ban_speak;
	//冻结交易列表
extern set<string> freeze_money;
	//封号列表
extern set<string> lock_hero;
	/*GM账号管理 jolly start*/

extern map<string ,VipDataInitial> vipDataStore;

extern set<string>allTitle; //所有头衔容器

extern map<string,string> mapIdToGoodsId; //副本id 找副本令id

extern set<string> guildTaskList;				//帮派任务列表
extern set<string> dayTaskList;				//日常任务
extern set<string> campTaskList;				//阵营任务

extern map<string,Revival_Config*> mapId_to_revival;		//复活点坐标信息

extern map<string,MysteriousBussiness_Config*> stage_to_mysteriousBussiness; 	//神秘商人配置文件 10.11

extern set<string> dirtyWordsPack;					//脏词库
extern set<string> illegalCharPack;				//命名非法符号

extern map<string,DailyActive*> dailyActiveConfMap;

extern map<string,string> timeToDailyActiveId;           //时间对应活动id

extern map<string, wagonColorRank_T*> wagonId_2_rankRate;	//每种马车颜色刷新率
extern map<string, string> heroId_2_colorWagon;			//玩家有彩色马车

extern list<CpyStateFlg> CPYEntState;                   //副本通关顺序
#include "set_camp.h"
// extern map<string,TowerTeam*>towerDefTeamInfo;			//塔防组队容器；

// extern list<TowerTeam*>idleTowerDefTeam;				//空闲塔防房间容器；

extern map<string,int> goodsId_to_price; 			//帮派商店

extern map<string, GuildFeastConf_T> feastId_2_feastConf;	//帮派盛宴配置

extern map<string,Reward_online_config*> id_to_reward_online;			//在线奖励

extern set<string> innerIPSet;

#include "libev.h"
extern map<string,Equipment*> dropEquipMent;

extern map<string,int> goodsId_to_price_shengWang; 		 //声望商店

#include "rankInfoAsist.h"
extern vector<string> wuLinTarget;

extern map<string,MonsterTool*>toolToMonster;            //道具对应刷出副本*/

extern map<string,Map_Inform*>mapId_connect_map;

extern map<string,MonsterTool*> toolMonsterIdToInst;     //道具刷出的怪管理容器

extern char shutDownContent[1024];

static void shutDown_cb(struct event_base *loop, ev_timer* think, int revents)
{
	ev_timer_stop(loop, think);
	
	shutDownRemainTime--;
	
	map<string, Hero*>::iterator it;
	
	cout<<"shutDownRemainTime:"<<shutDownRemainTime<<endl;
	if (shutDownRemainTime==0)
	{		
		for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
		{
			if (it->second!=NULL)
			{			
				it->second->memSet();
				close(it->second->getFd());
			}
		}
	}
	
	if (shutDownRemainTime==-5)
	{
		saveCampNumber();
		saveRankInfo2Mem();
		_exit(0);
	}
	
	if (shutDownRemainTime<=300)
	{
		if (shutDownRemainTime%60==0)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),shutDownContent,shutDownRemainTime);
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,g_out_buf,0);
				}
			}		
		}
		else if (shutDownRemainTime==30)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),shutDownContent,shutDownRemainTime);
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,g_out_buf,0);
				}
			}	
		}
		else if (shutDownRemainTime==10)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),shutDownContent,shutDownRemainTime);
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,g_out_buf,0);
				}
			}		
		}
		else if (shutDownRemainTime<=5)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),shutDownContent,shutDownRemainTime);
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,g_out_buf,0);
				}
			}		
		}
	}
	
	ev_timer_start(loop,think);
}

void GM_goods(char *buffer)
{	
	char* flag;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(flag);
	
	if (isGM(pg_hero))
	{
		if (strcmp(flag,"0")==0)
		{			
			char *identity;
			
			char* goodsid;
			
			char* num_c;
			int num;
			
			MSG_CHAR(identity);
			MSG_CHAR(goodsid);
			MSG_CHAR_END(num_c);
			num=atoi(num_c);		
			
			cout<<"16,0,"<<identity<<","<<goodsid<<","<<num<<endl;
			
			if (strcmp(identity,"1")==0)
			{				
				saveGoodsInBag(pg_hero,goodsid,num);
			}
			else
			{			
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 57"<<endl;
				}
				else
				{
					Hero *otherhero=it->second;
					saveGoodsInBag(otherhero,goodsid,num);
				}
			}
		}
		else if (strcmp(flag , "1")==0)
		{
			char *identity;
			
			char *index_c;
			int index;
			
			char* num_c;
			int num;
			
			MSG_CHAR(identity);
			MSG_CHAR(index_c);
			MSG_CHAR_END(num_c);
			index=atoi(index_c);
			num=atoi(num_c);
			
			Pet *pet;
			
			cout<<"16,1,"<<identity<<","<<index<<","<<num<<endl;
			
			if (strcmp(identity,"1")==0)
			{				
				pet=pg_hero->getPetBox()->getPet(index);
				if (pet==NULL)
				{
					cout<<"jolly:index is error GM_communicate.cpp 117"<<endl;
				}
				else
				{
					pet->growExp(num,pg_hero->getLevel(),pg_hero);
				}
			}
			else
			{		
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 130"<<endl;
				}
				else
				{
					Hero *_hero=it->second;
					pet=_hero->getPetBox()->getPet(index);
					if (pet==NULL)
					{
						cout<<"jolly:index is error GM_communicate.cpp 138"<<endl;
					}
					else
					{
						pet->growExp(num,_hero->getLevel(),_hero);
					}
				}
			}				
		}
		else if (strcmp(flag , "2")==0)
		{
			char *identity;
			
			char* gold_c;
			int gold;
			
			char* goldBound_c;
			int goldBound;
			
			char* money_c;
			int money;
			
			char *moneyBound_c;
			int moneyBound;
			
			MSG_CHAR(identity);
			MSG_CHAR(gold_c);
			MSG_CHAR(goldBound_c);
			MSG_CHAR(money_c);
			MSG_CHAR_END(moneyBound_c);
			gold=atoi(gold_c);
			goldBound=atoi(goldBound_c);
			money=atoi(money_c);
			moneyBound=atoi(moneyBound_c);
			
			cout<<"16,2,"<<identity<<","<<gold<<","<<goldBound<<","<<money<<","<<moneyBound<<endl;
			
			if (strcmp(identity,"1")==0)
			{					
				if (goldBound!=-1)
				{					
					pg_hero->getMoney()->money_setBoundGold((long)goldBound);
				}
				if (gold!=-1)
				{
					pg_hero->getMoney()->money_setGold((long)gold);
				}
				if (moneyBound!=-1)
				{
					pg_hero->getMoney()->money_setBoundGameMoney((long)moneyBound);
				}
				if (money!=-1)
				{
					pg_hero->getMoney()->money_setGameMoney((long)money);
				}
				pg_hero->getMoney()->money_inform(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			else
			{	
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 221"<<endl;
				}
				else
				{
					Hero *_hero=it->second;		
					if (goldBound!=-1)
					{					
						_hero->getMoney()->money_setBoundGold((long)goldBound);
					}
					if (gold!=-1)
					{
						_hero->getMoney()->money_setGold((long)gold);
					}
					if (moneyBound!=-1)
					{
						_hero->getMoney()->money_setBoundGameMoney((long)moneyBound);
					}
					if (money!=-1)
					{
						_hero->getMoney()->money_setGameMoney((long)money);
					}
					_hero->getMoney()->money_inform(g_out_buf,sizeof(g_out_buf));
					send_msg(_hero->getFd(),g_out_buf);
				}
			}
		}
		else if (strcmp(flag , "3")==0)			//给人物经验
		{
			char *identity;
			
			char *exp_c;
			int exp;
				
			MSG_CHAR(identity);
			MSG_CHAR_END(exp_c);
			exp=atoi(exp_c);
			
			cout<<"16,3,"<<identity<<","<<exp<<endl;
			
			if (strcmp(identity,"1")==0)
			{				
				pg_hero->setExpNow(exp);
			}
			else
			{		
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 130"<<endl;
				}
				else
				{
					char msg[20]={'\0'};
					// msg+=intTostring(REWARD_EXP);
					// msg+=intTostring(exp);
					send_msg(pg_hero->getFd(),msg);
					Hero *_hero=it->second;
					_hero->setExpNow(exp);
					sprintf(msg,"%d,%d,%d",9,REWARD_EXP,exp);
				}
			}	
		}
		else if (strcmp(flag  , "4")==0)				//禁言
		{
			char *stage;
			
			char *identity;
			
			MSG_CHAR(stage);
			MSG_CHAR_END(identity);			
			
			cout<<"16,4,"<<flag<<","<<identity<<endl;
			
			if (strcmp(stage,"1")==0)
			{
				ban_speak.insert(identity);
			}
			else if (stage=="0")
			{
				ban_speak.erase(identity);
			}
		}
		else if (strcmp(flag,"5")==0)			//跳转地图
		{
			char *identity;
			
			char *mapId_c;
			
			char *Point_x_c;
			
			char *Point_y_c;
			
			MSG_CHAR(identity);
			MSG_CHAR(mapId_c);
			MSG_CHAR(Point_x_c);
			MSG_CHAR(Point_y_c);
			Point point;			
			point._x=atoi(Point_x_c);
			point._y=atoi(Point_y_c);	
			
			cout<<"16,5,"<<identity<<","<<mapId_c<<","<<Point_x_c<<","<<Point_y_c<<endl;
								
			if (strcmp(identity,"1")!=0)
			{
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 130"<<endl;
				}
				else
				{
					pg_hero=it->second;
				}
			}
			string msg_body="2";
			string mapid=mapId_c;
			Map_Inform *mapnow=pg_hero->getMap();
			char* mapnowid=mapnow->getMapId();
			string nowmapid=mapId_c;
			nowmapid=nowmapid.substr(0,6);	
			if (mapnow->getFlgCpy())
			{			
				outCpy(pg_hero);
			}
			else
			{
				map<string,Map_Inform*>::iterator map_it;
				map_it = mapId_connect_map.find(mapid);
				if(map_it == mapId_connect_map.end())
				{
					cout<<"Acording to mapid can't find the Mapinform (in hero_revival)"<<endl;
				}
				else
				{
					pg_hero->quit_scene();
					Map_Inform *scene_map = map_it->second;
					pg_hero->setMap(scene_map);
					pg_hero->setMapId(mapid.c_str());
					if (point._x==-1||point._y==-1)
					{
						pg_hero->setLocation(scene_map->getEntPt());
					}
					else
					{
						pg_hero->setLocation(point);   
					}           
					msg_body+=intTostring(CHANGE_SCENE);
					msg_body+=intTostring(SUCCESS);
					msg_body=msg_body+","+mapid;	
					if (point._x==-1||point._y==-1)
					{					
						msg_body+=intTostring(scene_map->getEntPt()._x);             //进入新场景的入点坐标			
						msg_body+=intTostring(scene_map->getEntPt()._y);
					}
					else
					{
						msg_body+=intTostring(point._x);             //进入新场景的入点坐标			
						msg_body+=intTostring(point._y);
					}
					send_msg(pg_hero->getFd(), const_cast<char *>(msg_body.c_str()));
					// cout<<msg_body<<endl;
					// pg_hero->enter_scene();
				}
			}
		}
		else if (strcmp(flag , "6")==0)				//发布广播
		{	
			int times;
			
			char *msgInfo;
			
			MSG_CHAR(char* ptimes);
			times=atoi(ptimes);
			
			MSG_CHAR_END(msgInfo);
			
			cout<<"16,6,"<<times<<","<<msgInfo<<endl;
			
			char msg[10000]={'\0'};
			sprintf(msg,"%d,%d,%d,%s",16,GM_BROADCAST,times,msgInfo);
			
			map<string, Hero*>::iterator it;
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				send_msg(it->second->getFd(),msg);
			}
		}	
		else if (strcmp(flag, "7")==0)					//发布系统消息
		{
			MSG_CHAR_END(char *msg_info);
			map<string, Hero*>::iterator it;
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,msg_info,0);
				}
			}
		}
		else if (strcmp(flag, "8")==0)					//充值
		{
			MSG_CHAR_END(char *gold_c)
			int gold=atoi(gold_c);
			increaseAccMoney(pg_hero,gold);
		}
		else if (strcmp(flag,"9")==0)					//返回公共变量的大小
		{
			returnGlobalSize();
		}
		
		else if (strcmp(flag , "10")==0)				//设置vip等级
		{
			MSG_CHAR_END(char* stage_c)
			int stage=atoi(stage_c);
			pg_hero->setVipRights(stage);			
		}
		else if (strcmp(flag, "11")==0)					//开启快捷栏的所有功能
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",16,3);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
		else if (strcmp(flag , "13")==0)				//查看在线人数
		{			
			snprintf(g_out_buf,sizeof(g_out_buf),"%s%d,","current online pg_hero is :  ",(int)heroId_to_pHero.size());
			systemSendMssage(pg_hero,g_out_buf,0);
		}
		else if (strcmp(flag , "14")==0)
		{
			char *taskId;
			MSG_CHAR_END(taskId);
			GM_accept_one_task(taskId);
		}
		else if (strcmp(flag, "15") == 0)
		{
			char* mode;
			char* camp;
			char* rank;
			MSG_CHAR(mode);
			cout<<"mode is mode is mode is mode is "<<mode<<endl;
			if (strcmp(mode, "0") == 0)
			{
				
			cout<<"Why can't you come here!!!!!!"<<endl;
				char *guildName;
				MSG_CHAR_END(guildName);
				GM_disbandGuildByName(guildName);
				cout<<"Come here guild Name is "<<guildName<<endl;
			}
			else if (strcmp(mode, "1") == 0)
			{
				
			cout<<"Why111111111 can't you come here!!!!!!"<<endl;
				MSG_CHAR(camp);
				MSG_CHAR_END(rank);
				GM_disbandGuildByRank(atoi(camp), atoi(rank));
				cout<<"Come here guild camp is "<<atoi(camp)<<" rank is "<<atoi(rank)<<endl;
			}
		}
		else if (strcmp(flag, "16") == 0)
		{
			char* c_glory;
			int glory = 0;
			MSG_CHAR(c_glory);
			glory = atoi(c_glory);
			if (glory < 0)
			{
				systemSendMssage(pg_hero, (char*)("you are a greedy GM, I can give you 1 million"), 0);
				glory = 1000000;
			}
			//增加个人帮贡
			Guild *guild = pg_hero->getGuild();
			if (guild == NULL)
			{
				systemSendMssage(pg_hero, (char*)"GM, you havn't join guild", 0);
				return;
			}
			char *guildName = pg_hero->getGuildName();
			int ret = addMyGuildGlory(guildName, pg_hero->getIdentity(), glory);
			if (ret > 0)
			{
				systemSendMssage(pg_hero, (char*)"GM, you havn't join guild", 0);
			} 
			else if (ret < 0)
			{
				systemSendMssage(pg_hero, (char*)"GM, you can't want so many, your total glory will overflow!", 0);
			}
			else 
			{
				systemSendMssage(pg_hero, (char*)"Get glory OK!", 0);
			}
		}
		else if (strcmp(flag, "17") == 0)
		{
			char* c_exp;
			int exp = 0;
			MSG_CHAR(c_exp);
			exp = atoi(c_exp);
			if (exp < 0)
			{
				systemSendMssage(pg_hero, (char*)("you are a greedy GM, I can give you 1 million"), 0);
				exp = 1000000;
			}
			//增加个人帮贡
			Guild *guild = pg_hero->getGuild();
			if (guild == NULL)
			{
				systemSendMssage(pg_hero, (char*)("GM, you havn't join guild"), 0);
				return;
			}
			char *guildName = pg_hero->getGuildName();
			int ret = addGuildExp(guildName, pg_hero->getIdentity(), exp);
			if (ret > 0)
			{
				systemSendMssage(pg_hero, (char*)"GM, get guild exp OK!", 0);
			}
		}
		else if (strcmp(flag, "18") == 0)
		{
			//热读cdkey配置文件
			int rc = read_files_cdkey("config/cdkey.xml");
			if(rc != 0)
			{
				cout<<"read read_files_cdkey error"<<endl;
			}
		}
		else if (strcmp(flag, "19") == 0)
		{
			if(pg_hero->getCpyRecord())
			{
				pg_hero->getCpyRecord()->GMPassAll();
			}
		}
		else if (strcmp(flag, "20") == 0)
		{
			MSG_CHAR_END(char* number_c)
			int number=atoi(number_c);
			cout<<"gm:16,0,"<<number<<endl;
			number=pg_hero->getNowDay()+number;
			pg_hero->setNowDay(number);
			int allowSign=number-pg_hero->memHero->downLineDay+1;
			pg_hero->setAllowSign(allowSign);
		}
		else if (strcmp(flag, "21") == 0)
		{
			int inFors = 0;
			char* inForsStr;
			MSG_CHAR(inForsStr);
			inFors = atoi(inForsStr);
			pg_hero->addInternalForces(inFors);
		}
		else if (strcmp(flag, "22") == 0)
		{
			int skillExp = 0;
			char* skillExpStr;
			MSG_CHAR(skillExpStr);
			skillExp = atoi(skillExpStr);
			pg_hero->addHeroSkillExp(skillExp);
		}
		else if (strcmp(flag, "23") == 0)				//系统发邮件
		{
			char content[2048]={0};
			snprintf(content,sizeof(content),heroRankContent,1);
			cout<<"content:"<<content<<endl;
			Mail_Txt mail("系统", "活动", content);//构建收件箱中的邮件数据
			mail.isRead = 1;//收件箱内未读	hai
			MailSystermInterface::add_mail_data(pg_hero, 0, (int)sizeof(mail), &mail);
		}
		else if (strcmp(flag,"24")==0)
		{
			MSG_CHAR(char* type_c)
			MSG_CHAR_END(char* identity)
			int type=atoi(type_c);
			if (type==1)
			{	
				freeWorldTalk.insert(identity);
			}
			else if (type==0)
			{
				freeWorldTalk.erase(identity);
			}
		}
		else if (strcmp(flag,"25")==0)
		{
			char *identity;
			
			char* gold_c;
			int gold;
			
			char* goldBound_c;
			int goldBound;
			
			char* money_c;
			int money;
			
			char *moneyBound_c;
			int moneyBound;
			
			MSG_CHAR(identity);
			MSG_CHAR(gold_c);
			MSG_CHAR(goldBound_c);
			MSG_CHAR(money_c);
			MSG_CHAR_END(moneyBound_c);
			gold=atoi(gold_c);
			goldBound=atoi(goldBound_c);
			money=atoi(money_c);
			moneyBound=atoi(moneyBound_c);
			
			cout<<"16,25,"<<identity<<","<<gold<<","<<goldBound<<","<<money<<","<<moneyBound<<endl;
			
			if (strcmp(identity,"1")==0)
			{
				if (gold!=-1)
				{
					pg_hero->getMoney()->money_increaseGold((long)gold);
				}
				if (goldBound!=-1)
				{					
					pg_hero->getMoney()->money_increaseBoundGold((long)goldBound);
				}
				if (moneyBound!=-1)
				{
					pg_hero->getMoney()->money_increaseBoundGameMoney((long)moneyBound);
				}
				if (money!=-1)
				{
					pg_hero->getMoney()->money_increaseGameMoney((long)money);
				}
				pg_hero->getMoney()->money_inform(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			else
			{	
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(identity);
				if (it==heroId_to_pHero.end())
				{
					cout<<"jolly:no pg_hero identity GM_communicate.cpp 221"<<endl;
				}
				else
				{
					Hero *_hero=it->second;		
					if (gold!=-1)
					{
						_hero->getMoney()->money_increaseGold((long)gold);
					}
					if (goldBound!=-1)
					{					
						_hero->getMoney()->money_increaseBoundGold((long)goldBound);
					}
					if (moneyBound!=-1)
					{
						_hero->getMoney()->money_increaseBoundGameMoney((long)moneyBound);
					}
					if (money!=-1)
					{
						_hero->getMoney()->money_increaseGameMoney((long)money);
					}
					_hero->getMoney()->money_inform(g_out_buf,sizeof(g_out_buf));
					send_msg(_hero->getFd(),g_out_buf);
				}
			}
		}
		else if (strcmp(flag,"26")==0)
		{
			pg_hero->setAllowSign(pg_hero->getAllowSign()+1);
			pg_hero->memHero->rewarddata.last_day_flag=1;
		}
		else if (strcmp(flag, "27") == 0)
		{
			MSG_CHAR(char* identity);
			if (GM_setGuildPresid(identity))
			{
				systemSendMssage(pg_hero, (char*)("Set Guild Manager OK!!!"), 0);
			}
		}
		else if (strcmp(flag,"50")==0)
		{
			MSG_CHAR(char *time_c);
			MSG_CHAR(char *msg);
			
			shutDownRemainTime=atoi(time_c);
			
			cout<<"16,50,"<<shutDownRemainTime<<","<<msg<<endl;
			
			map<string, Hero*>::iterator it;
			
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{						
					systemSendMssage(it->second,msg,0);
				}
			}
			
			
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",16,GM_BROADCAST,1,msg);
						
			for (it=heroId_to_pHero.begin();it!=heroId_to_pHero.end();it++)
			{
				if (it->second!=NULL)
				{
					send_msg(it->second->getFd(),g_out_buf);
				}
			}
			
			ext_ev_timer_init(&shutDownTimer, shutDown_cb, 1, 0);
			ev_timer_start(loops, &shutDownTimer);
		}
	}
	else
	{
		cout<<"jolly:you are not a gm GM_communicate 534"<<endl;
	}
}

void GM_bugCommit(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *select)
	MSG_CHAR(char *title)
	MSG_CHAR_END(char *content)
		
	/*记录GM信息提交的流水账 jolly 2.20 start*/
	char account_msg[1024]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%s,%s",13,1,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),title,content);
	write_log(account_msg);
	/*记录GM信息提交的流水账 jolly 2.20 end*/
}
	
void returnGlobalSize(void)
{	
	/** 缓存服务器配置表 added by Tory**/
	int Mem_configure_Size=mem_configure_table.size();

	/**全局容器，保存在线的玩家所创建的角色拥有的邮件数据，Tory 2012.9.17**/
	int Mail_list_Size=mail_map.size();

	/**全局容器，邮件处理队列 tory 2012.9.20**/
	int handle_quene_Size=handle_quene.size();

	/**初始化命令处理的函数**/
	int command_map_Size=command_map.size();

	/**	与套接字描述符绑定的消息接收队列 **/
	int message_queue_Size=message_queue.size();

	/**	空闲用户列表,用于玩家登陆 **/
	int idle_role_list_Size=idle_role_list.size();

	/**	空闲角色列表,用于玩家选择角色进入游戏 **/
	int idle_hero_list_Size=idle_hero_list.size();

	/*
	玩家升级所需要的经验值
	*/
	int exp_upgrade_list_Size=exp_upgrade_list.size(); //evan add 2012.9.19

	int monTypeId_connect_property_Size=monTypeId_connect_property.size();

	/*
	*	全局变量，角色(Hero)ID索引Hero对象指针的map容器
	*	管理所有已初始化的Hero对象，heroId可通过Role对象里
	*/
	int heroId_to_pHero_Size=heroId_to_pHero.size();

	/*
	*	全局变量，当前fd索引Role对象指针的map容器
	*	管理在线用户
	*/
	int fd_to_pRole_Size=fd_to_pRole.size();

	int cpyMapConf_Size=cpyMapConf.size(); //副本地图编号id对应副本地图实例指针（存配置文件）
	/*
	*	全局变量，技能(skill)ID索引技能配置对象指针的map容器，
	* 	管理游戏角色所有技能配置信息
	*/
	int id_to_skill_Size=id_to_skill.size();

	int id_to_five_Size=id_to_five.size();
	/*
		by cookie 队伍容器
	*/
	int tid_Size=tid.size();                //根据组队目的存放teamid

	// int pid_Size=pid.size();				//根据组队目的存放角色id
	
	TeamManager* teamManger = TeamManager::getManagerInst();
			

	int id_to_team_Size=(int)teamManger->size();

	int id_to_equip_Size=id_to_equip.size(); //装备模版类容器


	int id_to_task_Size=id_to_task.size(); //任务全局变量   Evan add
	
	//20

	int id_to_touch_Size=id_to_touch.size(); //任务触发条件 added by bison

	int id_to_npc_Size=id_to_npc.size();  //NPC全局变量   Evan add

	int id_to_dropgoods_Size=id_to_dropgoods.size();  //掉落列表全局变量 jolly add

	int idNum_2_rewardInfo_Size=idNum_2_rewardInfo.size();	//副本奖励信息的全局变量 added by bison
	
	int type_2_goodsList_Size=type_2_goodsList.size();			//副本奖励物品序列的全局变量 added by bison
	
	int id_2_tdConf_Size=id_2_tdConf.size();					//副本配置信息，根据副本id来索引 added by bison

	int id_to_ointment_Size=id_to_ointment.size(); //物品配置类容器 cookie 
	
	int goods_to_hero_Size=goods_to_hero.size();  //拾取物品 jolly add

	int id_to_pet_Size=id_to_pet.size();		//add by jolly

	int id_to_activePet_Size=id_to_activePet.size();		//add by jolly 2012.8.30

	/*副本限制类*/
	int cpyId_to_cpyLimit_Size=cpyId_to_cpyLimit.size();               //add chenzhen 2012.06.11 

	/*刷怪批次*/
	int groupBrush_Size=groupBrush.size();

	int id2taskGoodsInfo_Size=id2taskGoodsInfo.size();			//added by bison 2012.7.6

	int monster_skill_map_Size=monster_skill_map.size();

	int monSkiInst_Size=monSkiInst.size();                    //Boss怪技能（不能放在怪物类里头）

	int jumpId2mapInfo_Size=jumpId2mapInfo.size();				//jumpID对应的信息；

	int id_to_petSkill_Size=id_to_petSkill.size();		//add by jolly 2012.7.31

	int id_to_dj_Size=id_to_dj.size();				//add by jolly 2012.8.14
	
	int id_to_cl_Size=id_to_cl.size();				//add by jolly 2012.8.14

	int suit_lists_Size=suit_lists.size();		//套装集合的全局变量  evan add 2012.8.30

	int shop_Size=shop.size(); //商城

	//帮派名查帮派ID
	int name_2_guildId_Size=name_2_guildId.size();
	/*帮派名索引帮派
	 *			--id_2_guild[0]支派阵营的帮派集合
	 *			--id_2_guild[1]宗教阵营的帮派集合
	 *			--id_2_guild[2]游侠阵营的帮派集合
	 *			--id_2_guild[3]所有阵营的帮派集合
	 */
	int id_2_guild0_Size=id_2_guild[0].size();
	
	int id_2_guild1_Size=id_2_guild[1].size();
	
	int id_2_guild2_Size=id_2_guild[2].size();
	
	int id_2_guild3_Size=id_2_guild[3].size();
	 
	/*帮派排名榜
	 *			--guildRankList[0]支派阵营的帮派排名榜
	 *			--guildRankList[1]宗教阵营的帮派排名榜
	 *			--guildRankList[2]游侠阵营的帮派排名榜
	 *			--guildRankList[3]所有阵营的帮派排名榜
	 */
	int guildRankList0_Size=guildRankList[0].size();

	int guildRankList1_Size=guildRankList[1].size();
	
	int guildRankList2_Size=guildRankList[2].size();
	
	int guildRankList3_Size=guildRankList[3].size();

	/*可采摘道具*/
	int takeGoodsMap_Size=takeGoodsConfMap.size();

	/*马车配置文件*/
	int wagonConfMap_Size=wagonConfMap.size();

	/*马车实例*/
	int wagonInstMap_Size=wagonInstMap.size();

	/*奖励系统 jolly 2012.9.10 start*/
	int id_to_reward_level_Size=id_to_reward_level.size();

	int id_to_reward_recharge_Size=id_to_reward_recharge.size();
	
	/*奖励系统 jolly 2012.9.10 end*/

	/*瓶罐的配置文件*/
	int bottleConfMap_Size=bottleConfMap.size();

	/*陷阱的配置文件*/
	int trapConfMap_Size=trapConfMap.size();
	
	int npc_Size=npc.size(); //npc容器
	
	//60

	//帮派活动全局数据
	int id_2_guildAct_Size=id_2_guildAct.size();

	//gm 容器
	int heroid_to_gm_Size=heroid_to_gm.size();

	//全局id,保存所有注册用户的Id；
	int globalHeroId_Size=globalHeroId.size();	

	int nickName2heroId_Size=nickName2heroId.size();

	int heroNameCheckName_Size=heroNameCheckName.size();
	
	//65
	
	int heroNameCheckHeroId_Size=heroNameCheckHeroId.size();
	/*GM账号管理 jolly start*/
	//禁言列表
	int ban_speak_Size=ban_speak.size();
	//冻结交易列表
	int freeze_money_Size=freeze_money.size();
	//封号列表
	int lock_hero_Size=lock_hero.size();
	/*GM账号管理 jolly start*/

	int vipDataStore_Size=vipDataStore.size();
	
	//70

	int allTitle_Size=allTitle.size(); //所有头衔容器

	int mapIdToGoodsId_Size=mapIdToGoodsId.size(); //副本id 找副本令id

	int guildTaskList_Size=guildTaskList.size();				//帮派任务列表
	
	int dayTaskList_Size=dayTaskList.size();				//日常任务

	int campTaskList_Size=campTaskList.size();				//阵营任务

	int mapId_to_revival_Size=mapId_to_revival.size();		//复活点坐标信息

	int stage_to_mysteriousBussiness_Size=stage_to_mysteriousBussiness.size(); 	//神秘商人配置文件 10.11

	int dirtyWordsPack_Size=dirtyWordsPack.size();					//脏词库
	
	int illegalCharPack_Size=illegalCharPack.size();				//命名非法符号
	
	//80
	
	int dailyActiveConfMap_Size=dailyActiveConfMap.size();

	int wagonId_2_rankRate_Size=wagonId_2_rankRate.size();	//每种马车颜色刷新率
	
	int heroId_2_colorWagon_Size=heroId_2_colorWagon.size();			//玩家有彩色马车

	int CPYEntState_Size=CPYEntState.size();                   //副本通关顺序

	// int towerDefTeamInfo_Size=towerDefTeamInfo.size();			//塔防组队容器；

	// int idleTowerDefTeam_Size=idleTowerDefTeam.size();				//空闲塔防房间容器；

	int goodsId_to_price_Size=goodsId_to_price.size(); 			//帮派商店

	int feastId_2_feastConf_Size=feastId_2_feastConf.size();	//帮派盛宴配置
	//90

	int id_to_reward_online_Size=id_to_reward_online.size();			//在线奖励

	int innerIPSet_Size=innerIPSet.size();

	int dropEquipMent_Size=dropEquipMent.size();

	int goodsId_to_price_shengWang_Size=goodsId_to_price_shengWang.size(); 		 //声望商店

	int wuLinTarget_Size=wuLinTarget.size();

	int toolToMonster_Size=toolToMonster.size();            //道具对应刷出副本*/

	int mapId_connect_map_Size=mapId_connect_map.size();

	int toolMonsterIdToInst_Size=toolMonsterIdToInst.size();     //道具刷出的怪管理容器	
	
	
	
	
	
	ostringstream stream;	
	
	stream<<"Mem_configure_Size is "<<Mem_configure_Size<<endl;
	stream<<"Mail_list_Size is "<<Mail_list_Size<<endl;
	stream<<"handle_quene_Size is "<<handle_quene_Size<<endl;
	stream<<"command_map_Size is "<<command_map_Size<<endl;
	stream<<"message_queue_Size is "<<message_queue_Size<<endl;
	stream<<"idle_role_list_Size is "<<idle_role_list_Size<<endl;
	stream<<"idle_hero_list_Size is "<<idle_hero_list_Size<<endl;
	stream<<"exp_upgrade_list_Size is "<<exp_upgrade_list_Size<<endl;
	stream<<"monTypeId_connect_property_Size is "<<monTypeId_connect_property_Size<<endl;
	stream<<"heroId_to_pHero_Size is "<<heroId_to_pHero_Size<<endl;
	stream<<"fd_to_pRole_Size is "<<fd_to_pRole_Size<<endl;
	stream<<"cpyMapConf_Size is "<<cpyMapConf_Size<<endl;
	stream<<"id_to_skill_Size is "<<id_to_skill_Size<<endl;
	stream<<"id_to_five_Size is "<<id_to_five_Size<<endl;
	stream<<"tid_Size is "<<tid_Size<<endl;
	// stream<<"pid_Size is "<<pid_Size<<endl;
	stream<<"id_to_team_Size is "<<id_to_team_Size<<endl;
	stream<<"id_to_equip_Size is "<<id_to_equip_Size<<endl;
	stream<<"id_to_task_Size is "<<id_to_task_Size<<endl;
	//20
	stream<<"id_to_touch_Size is "<<id_to_touch_Size<<endl;
	stream<<"id_to_npc_Size is "<<id_to_npc_Size<<endl;
	stream<<"id_to_dropgoods_Size is "<<id_to_dropgoods_Size<<endl;
	stream<<"idNum_2_rewardInfo_Size is "<<idNum_2_rewardInfo_Size<<endl;
	stream<<"type_2_goodsList_Size is "<<type_2_goodsList_Size<<endl;
	stream<<"id_2_tdConf_Size is "<<id_2_tdConf_Size<<endl;
	stream<<"id_to_ointment_Size is "<<id_to_ointment_Size<<endl;
	stream<<"goods_to_hero_Size is "<<goods_to_hero_Size<<endl;
	stream<<"id_to_pet_Size is "<<id_to_pet_Size<<endl;
	stream<<"id_to_activePet_Size is "<<id_to_activePet_Size<<endl;
	stream<<"cpyId_to_cpyLimit_Size is "<<cpyId_to_cpyLimit_Size<<endl;
	stream<<"groupBrush_Size is "<<groupBrush_Size<<endl;
	stream<<"id2taskGoodsInfo_Size is "<<id2taskGoodsInfo_Size<<endl;
	stream<<"monster_skill_map_Size is "<<monster_skill_map_Size<<endl;
	stream<<"monSkiInst_Size is "<<monSkiInst_Size<<endl;
	stream<<"jumpId2mapInfo_Size is "<<jumpId2mapInfo_Size<<endl;
	stream<<"id_to_petSkill_Size is "<<id_to_petSkill_Size<<endl;
	stream<<"id_to_dj_Size is "<<id_to_dj_Size<<endl;
	stream<<"id_to_cl_Size is "<<id_to_cl_Size<<endl;
	stream<<"suit_lists_Size is "<<suit_lists_Size<<endl;
	stream<<"shop_Size is "<<shop_Size<<endl;
	stream<<"name_2_guildId_Size is "<<name_2_guildId_Size<<endl;
	stream<<"id_2_guild0_Size is "<<id_2_guild0_Size<<endl;
	stream<<"id_2_guild1_Size is "<<id_2_guild1_Size<<endl;
	stream<<"id_2_guild2_Size is "<<id_2_guild2_Size<<endl;
	stream<<"id_2_guild3_Size is "<<id_2_guild3_Size<<endl;
	stream<<"guildRankList0_Size is "<<guildRankList0_Size<<endl;
	stream<<"guildRankList1_Size is "<<guildRankList1_Size<<endl;
	stream<<"guildRankList2_Size is "<<guildRankList2_Size<<endl;
	stream<<"guildRankList3_Size is "<<guildRankList3_Size<<endl;
	stream<<"takeGoodsMap_Size is "<<takeGoodsMap_Size<<endl;
	stream<<"wagonConfMap_Size is "<<wagonConfMap_Size<<endl;
	stream<<"wagonInstMap_Size is "<<wagonInstMap_Size<<endl;
	stream<<"id_to_reward_level_Size is "<<id_to_reward_level_Size<<endl;
	stream<<"id_to_reward_recharge_Size is "<<id_to_reward_recharge_Size<<endl;
	stream<<"bottleConfMap_Size is "<<bottleConfMap_Size<<endl;
	stream<<"trapConfMap_Size is "<<trapConfMap_Size<<endl;
	stream<<"npc_Size is "<<npc_Size<<endl;
	//60
	stream<<"id_2_guildAct_Size is "<<id_2_guildAct_Size<<endl;
	stream<<"heroid_to_gm_Size is "<<heroid_to_gm_Size<<endl;
	stream<<"globalHeroId_Size is "<<globalHeroId_Size<<endl;
	stream<<"nickName2heroId_Size is "<<nickName2heroId_Size<<endl;
	stream<<"heroNameCheckName_Size is "<<heroNameCheckName_Size<<endl;
	//65
	stream<<"heroNameCheckHeroId_Size is "<<heroNameCheckHeroId_Size<<endl;
	stream<<"ban_speak_Size is "<<ban_speak_Size<<endl;
	stream<<"freeze_money_Size is "<<freeze_money_Size<<endl;
	stream<<"lock_hero_Size is "<<lock_hero_Size<<endl;
	stream<<"vipDataStore_Size is "<<vipDataStore_Size<<endl;
	//70
	stream<<"allTitle_Size is "<<allTitle_Size<<endl;
	stream<<"mapIdToGoodsId_Size is "<<mapIdToGoodsId_Size<<endl;
	stream<<"guildTaskList_Size is "<<guildTaskList_Size<<endl;
	stream<<"dayTaskList_Size is "<<dayTaskList_Size<<endl;
	stream<<"campTaskList_Size is "<<campTaskList_Size<<endl;
	stream<<"mapId_to_revival_Size is "<<mapId_to_revival_Size<<endl;
	stream<<"stage_to_mysteriousBussiness_Size is "<<stage_to_mysteriousBussiness_Size<<endl;
	stream<<"dirtyWordsPack_Size is "<<dirtyWordsPack_Size<<endl;
	stream<<"illegalCharPack_Size is "<<illegalCharPack_Size<<endl;
	//80
	stream<<"dailyActiveConfMap_Size is "<<dailyActiveConfMap_Size<<endl;	
	stream<<"wagonId_2_rankRate_Size is "<<wagonId_2_rankRate_Size<<endl;
	stream<<"heroId_2_colorWagon_Size is "<<heroId_2_colorWagon_Size<<endl;
	stream<<"CPYEntState_Size is "<<CPYEntState_Size<<endl;
	// stream<<"towerDefTeamInfo_Size is "<<towerDefTeamInfo_Size<<endl;
	// stream<<"idleTowerDefTeam_Size is "<<idleTowerDefTeam_Size<<endl;
	stream<<"goodsId_to_price_Size is "<<goodsId_to_price_Size<<endl;
	stream<<"feastId_2_feastConf_Size is "<<feastId_2_feastConf_Size<<endl;
	//90
	stream<<"id_to_reward_online_Size is "<<id_to_reward_online_Size<<endl;
	stream<<"innerIPSet_Size is "<<innerIPSet_Size<<endl;
	stream<<"dropEquipMent_Size is "<<dropEquipMent_Size<<endl;
	stream<<"goodsId_to_price_shengWang_Size is "<<goodsId_to_price_shengWang_Size<<endl;
	stream<<"wuLinTarget_Size is "<<wuLinTarget_Size<<endl;
	stream<<"toolToMonster_Size is "<<toolToMonster_Size<<endl;
	stream<<"mapId_connect_map_Size is "<<mapId_connect_map_Size<<endl;
	stream<<"toolMonsterIdToInst_Size is "<<toolMonsterIdToInst_Size<<endl;
	//98
	
	
	
	
	
	
	
	
	
	int total=Mem_configure_Size+Mail_list_Size+handle_quene_Size+command_map_Size+message_queue_Size+\
	idle_role_list_Size+idle_hero_list_Size+exp_upgrade_list_Size+monTypeId_connect_property_Size+heroId_to_pHero_Size+\
	fd_to_pRole_Size+cpyMapConf_Size+id_to_skill_Size+id_to_five_Size+\
	tid_Size+id_to_team_Size+id_to_equip_Size+id_to_task_Size+\
	id_to_touch_Size+id_to_npc_Size+id_to_dropgoods_Size+idNum_2_rewardInfo_Size+type_2_goodsList_Size+\
	id_2_tdConf_Size+id_to_ointment_Size+goods_to_hero_Size+id_to_pet_Size+id_to_activePet_Size+\
	cpyId_to_cpyLimit_Size+groupBrush_Size+id2taskGoodsInfo_Size+monster_skill_map_Size+monSkiInst_Size+\
	jumpId2mapInfo_Size+id_to_petSkill_Size+id_to_dj_Size+id_to_cl_Size+\
	suit_lists_Size+shop_Size+name_2_guildId_Size+id_2_guild0_Size+id_2_guild1_Size+\
	id_2_guild2_Size+id_2_guild3_Size+guildRankList0_Size+guildRankList1_Size+guildRankList2_Size+\
	guildRankList3_Size+takeGoodsMap_Size+wagonConfMap_Size+wagonInstMap_Size+id_to_reward_level_Size+\
	id_to_reward_recharge_Size+bottleConfMap_Size+trapConfMap_Size+npc_Size+\
	id_2_guildAct_Size+heroid_to_gm_Size+globalHeroId_Size+nickName2heroId_Size+heroNameCheckName_Size+\
	heroNameCheckHeroId_Size+ban_speak_Size+freeze_money_Size+lock_hero_Size+vipDataStore_Size+\
	allTitle_Size+mapIdToGoodsId_Size+guildTaskList_Size+dayTaskList_Size+\
	campTaskList_Size+mapId_to_revival_Size+stage_to_mysteriousBussiness_Size+dirtyWordsPack_Size+illegalCharPack_Size+\
	dailyActiveConfMap_Size+wagonId_2_rankRate_Size+heroId_2_colorWagon_Size+\
	CPYEntState_Size+goodsId_to_price_Size+feastId_2_feastConf_Size+\
	id_to_reward_online_Size+innerIPSet_Size+dropEquipMent_Size+goodsId_to_price_shengWang_Size+wuLinTarget_Size+\
	toolToMonster_Size+mapId_connect_map_Size+toolMonsterIdToInst_Size;
	stream<<"globy total size is::"<<total<<endl;
	
	string result=stream.str();
	// cout<<stream.str()<<endl;
	send_msg(sock_fd,result);
}

void GM_whisper(char *buffer)
{
	cout<<"16,1"<<endl;
	int len=heroid_to_gm.size();
	if (len==0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",16,1,0);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		int number=random_number(1,len);
		cout<<"number is "<<number<<endl;
		set<string>::iterator it;
		number--;
		it=heroid_to_gm.begin();
		if (number!=0)
		{
			for (int i=0;i<number;i++)
			{
				++it;
			}
		}		
		cout<<"*it is "<<*it<<endl;
		map<string, Hero*>::iterator hero_it;
		char _identity[40]={'\0'};
		strncpy(_identity,(*it).c_str(),sizeof(_identity));
		hero_it=heroId_to_pHero.find(_identity);
		if (hero_it==heroId_to_pHero.end())
		{
			cout<<"jolly:According to the gm id can't find the hero  entity gm_communicate.cpp 1194"<<endl;
		}
		else
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%s,%s",16,1,pg_hero->getIdentity(),_identity,hero_it->second->getNickName());
			send_msg(pg_hero->getFd(),g_out_buf);
		}
	}	
}

static void systemShutDownCount(struct ev_loop *loop,ev_timer *think,int revents)
{
	ev_timer_stop(loop,think);
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (shutDownCount==300||shutDownCount==240||shutDownCount==180||shutDownCount==120||shutDownCount==60||shutDownCount==30||shutDownCount==20||shutDownCount==10||shutDownCount==5)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf026",1,8,shutDownCount,0,0,0);
		map<string,Hero*>::iterator iter;
		for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
		{	
			if(iter->second!= NULL)
			{
				send_msg(iter->second->getFd(),g_out_buf);
			}
		}
	}
	shutDownCount--;
	
	ev_timer_start(loop,think);
}

void GM_advertise(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int shutDownTime)
	MSG_CHAR(char *message)
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	map<string,Hero*>::iterator iter;
	for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
	{	
		if(iter->second!= NULL)
		{
			systemSendMssage(iter->second,message,0);
		}
	}
	shutDownCount=shutDownTime;
	ev_timer *shutDownTimer=new ev_timer;
	ext_ev_timer_init(shutDownTimer,systemShutDownCount,30,0);
	ev_timer_start(loops,shutDownTimer);
}
