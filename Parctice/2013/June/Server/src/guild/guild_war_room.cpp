/****************************************************************
 * Filename: guild_war_room.h
 * 
 * Description: 帮战房间类
 *
 * Original Author : bison, 2012-8-28
 *
 ****************************************************************/

#include"guild_war_room.h"
#include"my_time.h"
#include "systemMessage.h"
#include "guild_war_asist.h"
#include"offline_unhandle_event.h"
#include<algorithm>

#define NORMAL_VESION_FOR_GUILD_WAR1
#if defined(NORMAL_VESION_FOR_GUILD_WAR1)

#define GUILD_WAR_LOCK_TIME_LIMIT		guildWarCtl.lockTime		//密保时限--2分钟
#define GUILD_WAR_PREPARE_TIME_LIMIT	guildWarCtl.perpareTime		//准备时限--1.5分钟
#define GUILD_WAR_READY_TIME_LIMIT		guildWarCtl.readyTime		//就绪时限--5秒
#define GUILD_WAR_PK_TIME_LIMIT			guildWarCtl.pkTime			//战斗时限--10分钟
#define GUILD_WAR_DEFEND_FLAG_LIMIT		guildWarCtl.protectTime		//flag守护需要时间
#define GUILD_WAR_RESET_TIME_LIMIT		guildWarCtl.rewardTime		//重置时限--1分钟
#define GUILD_PREPARE_MEMBS_NUM			guildWarCtl.quickStartNeedHeroNum		//帮战准备需要达到的人数

#else

#define GUILD_WAR_LOCK_TIME_LIMIT		20		//密保时限--2分钟
#define GUILD_WAR_PREPARE_TIME_LIMIT	60		//准备时限--1.5分钟
#define GUILD_WAR_READY_TIME_LIMIT		5		//就绪时限--5秒
#define GUILD_WAR_PK_TIME_LIMIT			100		//战斗时限--30分钟
#define GUILD_WAR_DEFEND_FLAG_LIMIT		180		//flag守护需要时间
#define GUILD_WAR_RESET_TIME_LIMIT		3		//重置时限--1分钟
#define GUILD_PREPARE_MEMBS_NUM			3		//帮战准备需要达到的人数
#endif

extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*> mapId_connect_map;
extern struct ev_loop *loops;
extern GuildWarAsist *guildWarManage;			//帮派战管理

//帮派战经验奖励基数
const int rewardExpBase = 150;
//帮派战资金奖励基数
const int rewardMoneyBase = 10000;
//帮派战帮贡奖励基数
const int rewardGloryBase = 5;

// list<GuildWarRoom*> gwr_locked_que;						//上锁房间队列
// list<GuildWarRoom*> gwr_prepare_que;						//准备倒计时的房间队列
// list<GuildWarRoom*> gwr_ready_que;						//就绪的5秒钟后开始战斗的房间队列
// list<GuildWarRoom*> gwr_start_que;						//已经开始战斗的房间10分钟后帮战强制结束
// list<GuildWarRoom*> gwr_reset_que;						//重置定时器队列
/***********************************************************
 * int2str - 整型数转换成固定长度的字符串，位数不够的补零
 *author: bison
 * @val: 所要转换的整形数
 * @figure: 所要转换成的字符串位数
 * Return: 返回转换的字符串。如figure为4时,23则转成"0023"
 ***********************************************************/
static string int2str(int val, int figure)
{
	string str;
	while(figure--)
	{
		str.insert(str.begin(), (char)('0' + val % 10));
		val /= 10;
	}
	return str;
}

//密码保护定时器（3分钟定时）的到期处理
static void lock_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	if (room != NULL)
	{
		room->unlockRoom();
	}
}

//准备开始的定时器（3分钟定时）到期处理
static void prepare_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	if (room != NULL)
	{
		room->setRoomState(GWR_READY);
		room->startReadyTimer();
	}
}


//已经就绪的房间5秒钟后开始帮战
static void ready_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	if (room == NULL)
	{
		return;
	}
	room->setRoomState(GWR_START);
	room->startStartTimer();
	char msg[16];
	sprintf(msg, "18,%d,%d", GUILD_WAR_START, GUILD_WAR_PK_TIME_LIMIT);
	//向两边发消息，帮战已开始
	room->sendMsgToOneGroup(0, msg, 0);
	room->sendMsgToOneGroup(1, msg, 0);
}

//开战10分钟后战斗结束
static void start_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	if (room == NULL)
	{
		return;
	}
	room->setRoomState(GWR_OVER);	//房间状态为帮战结束
	room->rankGuildWar();			//对战斗结果进行排名
	room->giveReward();				//分发奖励
	room->startResetTimer();		//开启重置定时器
}

//重置定时器（3分钟定时）到期处理
static void reset_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	if (room == NULL)
	{
		return;
	}
	guildWarManage->freeOneRoom(room);
	room->setRoomState(GWR_IDLE);
}

GuildWarRoom::GuildWarRoom(int num, Map_Inform *roomMap)
{
	// roomId = "GWR_";					//帮战房间ID前缀
	// roomId += int2str(num, 4);
	sprintf(roomId, "GWR_%04d", num);
	scene = roomMap;
	
	roomState = GWR_IDLE;				//房间状态置为空闲
	
	winIndex = -1;						//获胜方帮派
	for (int i = 0; i < 2; i++)
	{
		//清空所有信息
		memset(host[0], 0, sizeof(host[0]));
		memset(host[1], 0, sizeof(host[1]));
		memset(sideName[0], 0, sizeof(sideName[0]));
		memset(sideName[1], 0, sizeof(sideName[1]));
		// host[i] = NULL;						//房间领导无
		totalKills[i] = 0;					//总的杀人数
		totalScore[i] = 0;					//总积分
		killLastTime[i]  = 0;				//杀最后一个人的时间
		joinNum[i] = 0;						//两帮参与人数
		guildPrepare[i] = false;			//帮派开始准备
		callFreqCtl[i] = MY_TV_SEC;			//初始为当前时间
		groupFlagState[i] = 0;
		// warGuild[i] = NULL;					//参战帮派
	}
	
	//初始化房间信息
	initRoomInfo();
	
}

char* GuildWarRoom::getId()
{
	return roomId;
}

void GuildWarRoom::lockRoom(char* pass)
{
	strncpy(password, pass, strlen(pass));
	setRoomState(GWR_LOCK);
}

//获取地图
Map_Inform* GuildWarRoom::getScene()
{
	return scene;
}

void GuildWarRoom::setRoomState(int state)
{
	if (state == GWR_IDLE)
	{
		roomState = GWR_IDLE;
	} else {
		roomState |= state;
	}
	
	if (state == GWR_IDLE)
	{
		scene->initTakeGoods();
	}
	if (state == GWR_START)
	{
		scene->brushTakeSource(3, true);
	}
}

//查看房间状态
int GuildWarRoom::getRoomState(void)
{
	return roomState;
}

//解锁房间
void GuildWarRoom::unlockRoom()
{
	memset(password, 0, sizeof(password));
	roomState &= ~GWR_LOCK;
}

void GuildWarRoom::startLockTimer()
{
	//定时3分钟，房间自动解锁
	ext_ev_timer_init(&timer, lock_timer_cb, GUILD_WAR_LOCK_TIME_LIMIT, 0, this);
    ev_timer_start(loops, &timer);
}

//限时3分钟开始战斗
void GuildWarRoom::startPrepareTimer()
{
	//定时3分钟，房间开始战斗
	ext_ev_timer_init(&timer, prepare_timer_cb, GUILD_WAR_PREPARE_TIME_LIMIT, 0, this);
    ev_timer_start(loops, &timer);
}

//5秒倒计时
void GuildWarRoom::startReadyTimer()
{
	//倒计时5秒钟后开始
	ext_ev_timer_init(&timer, ready_timer_cb, GUILD_WAR_READY_TIME_LIMIT, 0, this);
    ev_timer_start(loops, &timer);
	//群发消息通知倒计5秒钟后开始
	char msg[20];
	// msg = "18";
	// msg += intTostring(GUILD_WAR_READY);				//暂定18,7命令头
	// msg += intTostring(GUILD_WAR_READY_TIME_LIMIT);		//通知内容为倒计5秒后开始
	sprintf(msg, "18,%d,%d", GUILD_WAR_READY, GUILD_WAR_READY_TIME_LIMIT);
	//向两边发消息,通知开启5秒倒计时
	sendMsgToOneGroup(0, msg, 0);
	sendMsgToOneGroup(1, msg, 0);
}

//帮战开始后启动一个帮战限时的定时器
void GuildWarRoom::startStartTimer()
{
	//10分钟后战斗结束
	ext_ev_timer_init(&timer, start_timer_cb, GUILD_WAR_PK_TIME_LIMIT, 0, this);
    ev_timer_start(loops, &timer);
}

//开始房间重置定时器计时3分钟
void GuildWarRoom::startResetTimer()
{
	//定时3分钟，房间重置
	ext_ev_timer_init(&timer, reset_timer_cb, GUILD_WAR_RESET_TIME_LIMIT, 0, this);
    ev_timer_start(loops, &timer);
}

//停止房间锁定
void GuildWarRoom::stopLockTimer()
{
	ev_timer_stop(loops, &timer);
	// list<GuildWarRoom*>::iterator it;
	// it = gwr_locked_que.begin();
	// for(it; it != gwr_locked_que.end(); it++)
	// {
		// if ((*it)->getId() == roomId)
		// {
			// gwr_locked_que.erase(it);
			// ev_timer_stop(loops, &timer);
			// break;
		// }
	// }
}

//终止房间的准备状态并开始战斗
void GuildWarRoom::stopPrepareTimer()
{
	ev_timer_stop(loops, &timer);
	// list<GuildWarRoom*>::iterator it;
	// it = gwr_prepare_que.begin();
	// for(it; it != gwr_prepare_que.end(); it++)
	// {
		// if ((*it)->getId() == roomId)
		// {
			// gwr_prepare_que.erase(it);
			// ev_timer_stop(loops, &timer);
			// break;
		// }
	// }
}

//终止房间的就绪定时器
void GuildWarRoom::stopReadyTimer()
{
	ev_timer_stop(loops, &timer);
	// list<GuildWarRoom*>::iterator it;
	// it = gwr_ready_que.begin();
	// for(it; it != gwr_ready_que.end(); it++)
	// {
		// if ((*it)->getId() == roomId)
		// {
			// gwr_ready_que.erase(it);
			// ev_timer_stop(loops, &timer);
			// break;
		// }
	// }
}

	
//检查密码是否正确
bool GuildWarRoom::isPassOK(char* pass)
{
	if (!strcmp(password, pass))
	{
		return true;
	}
	return false;
}

//占领房间
int GuildWarRoom::holdRoom(Hero *managerHero)
{
	int order = ((joinNum[0] == 0) ? 0 : ((joinNum[1] == 0) ? 1 : -1));
	
	if (order == -1)
	{
		if (roomState & GWR_TWO)
		{
			roomState &= 0xffffFFFA;
		}
		return -1;
	}
	
	Guild *guild = managerHero->getGuild();
	// warGuild[order] = guild;
	char *managerId = managerHero->getIdentity();
	strncpy(host[order], managerId, IDL + 1);
	// host[order] = managerHero;
	if (strcmp(sideName[order], managerHero->getGuildName()) == 0
		|| strcmp(sideName[1 - order], managerHero->getGuildName()) == 0)
	{
		if (roomState & GWR_TWO)
		{
			roomState &= 0xffffFFFA;
		}
		return -2;
	}
	
	strncpy(sideName[order], managerHero->getGuildName(), IDL + 1);
	joinNum[order]++;				//帮派人数加1
#if 0
	CountInfo_T *count = new CountInfo_T();
	//初始他的统计信息
	countTable[order].insert(pair<string, CountInfo_T*>(managerId, count));
#endif
	
	
	//把帮主切入地图
	enterMap(managerHero, order);
	//设置玩家状态，外面可以知道玩家在帮派战房间中
	managerHero->setInGuildWarRoom(true, roomId);
	
	//给帮主刷出面板信息
	// char prepareMsg[16000];
	// prepareMsg += intTostring(GUILD_WAR_START_TIMER);
	// prepareMsg += intTostring(1);				//是否为房主
	int remainTime = 0;
	if (roomState & GWR_TWO)
	{
		//第二个帮主加入
		if (roomState & GWR_LOCK)
		{
			//解锁房间
			unlockRoom();
			stopLockTimer();
		}
		//第二个帮派加入3分钟后强制开始比赛
		startPrepareTimer();
		
		//通知第二个帮派，挑战成功
		char msg[16];
		// string msg_head = "18";					//命令头18,2
		// msg = msg + msg_head + intTostring(CHALLENGE_GUILD_WAR);
		// msg += intTostring(SUCCESS);
		sprintf(msg, "18,%d,1", CHALLENGE_GUILD_WAR);
		send_msg(managerHero->getFd(), msg);
		//发送通知开始倒计时
		remainTime = GUILD_WAR_PREPARE_TIME_LIMIT;
		// prepareMsg += intTostring(GUILD_WAR_PREPARE_TIME_LIMIT);	//强开倒计时
		
	} else {
		remainTime = 0;
		// prepareMsg += intTostring(0);				//强开倒计时没开
	}

	char myGuildMsg[12000] = {0};
	char theirGuildMsg[12000] = {0};
	viewOneGuildMsg(order, myGuildMsg);
	viewOneGuildMsg(1 - order, theirGuildMsg);
	// char* myGuildMsg = viewOneGuildMsg(order);
	// char* theirGuildMsg = viewOneGuildMsg(1 - order);
	
	char myMsg[16000] = {0};
	// myMsg += myGuildMsg;
	// myMsg += theirGuildMsg;
	sprintf(myMsg, "18,%d,1,%d%s%s", GUILD_WAR_START_TIMER, remainTime, myGuildMsg, theirGuildMsg);
	//给自己发房间信息
	send_msg(managerHero->getFd(), myMsg);
	
	//给对方帮派发上线一个人
	char joinMsg[400] = {0};
	// joinMsg += intTostring(GUILD_WAR_JOIN_ONE);				//表明帮派加入一个人
	// joinMsg += "," + sideName[order];						//加入者所在帮派
	// joinMsg += "," + managerId;								//加入者ID
	// joinMsg += charTostring(managerHero->getNickName());	//加入玩家名
	// joinMsg += charTostring(managerHero->getParty());		//加入者门派
	// joinMsg += intTostring(managerHero->getLevel());		//加入者等级
	// joinMsg += intTostring(getRemainTime());				//定时器剩余时间
	// string otherGuildJoinMsg = joinMsg + intTostring(0);	//他帮派加入了一个成员
	sprintf(joinMsg, "18,%d,%s,%s,%s,%s,%d,%d,0", GUILD_WAR_JOIN_ONE, sideName[order], managerId,
		managerHero->getNickName(), managerHero->getParty(), managerHero->getLevel(),
		remainTime);
	sendMsgToOneGroup(1 - order, joinMsg, 0);		//发给对方帮派的信息
	
	//测试使用
	// if (roomState & GWR_TWO)
	// {
		// cout<<"*********************************************************"<<endl;
		// informManagerCanStart(host[0]);
		// cout<<"*********************************************************"<<endl;
		// cout<<"BisonTest to make sure there are two guild been informed!"<<endl;
		// cout<<"*********************************************************"<<endl;
		// informManagerCanStart(host[1]);
		// cout<<"*********************************************************"<<endl;
	// }
	return 0;
}

//召唤加入
void GuildWarRoom::callJoin(Hero *manager)
{
	Guild *guild = manager->getGuild();
	char* managerId = manager->getIdentity();
	if (strcmp(managerId, host[0]) != 0 && strcmp(managerId, host[1]) != 0)
	{
		//不是房间头领，不能召唤
		return;
	}
	
	//频率控制
	int group = groupJudge(manager);
	if (MY_TV_SEC - callFreqCtl[group] < 5)
	{
		return;
	}
	
	callFreqCtl[group] = MY_TV_SEC;
	
	//帮主召唤加入帮派
	set<string> membsList = guild->getMembsList();
	char* heroId;					//帮众ID
	Hero *hero;						//帮众实例
	char msg[16];
	// msg = "18";
	// msg += intTostring(GUILD_WAR_CALL_JOIN);		//18,3命令头
	// msg += "," + roomId;				//帮战房间ID
	sprintf(msg, "18,%d,1,%s", GUILD_WAR_CALL_JOIN, roomId);
	set<string>::iterator it = membsList.begin();
	for(it; it != membsList.end(); it++)
	{
		// heroId = (*it);
		
		//角色id得到角色实例
		map<string, Hero*>::iterator it_hero;
		it_hero = heroId_to_pHero.find((*it));
		if(it_hero == heroId_to_pHero.end())
		{
			//不在线的就不发
			continue;
		}
		hero = it_hero->second;
		//如果是已经在房间中的就不发了
		if (hero->isInGuildWarRoom())
		{
			continue;
		}
		send_msg(hero->getFd(), msg);
	}
}

	
//切入房间地图
void GuildWarRoom::enterMap(Hero *hero, int group)
{
	char mapNewId[IDL + 1] = {0};
	if (scene == NULL)
	{
		return;
	}
	
	//帮派战一方加入一个成员
	if (addOneGroupMem(group, hero->getIdentity()) != 0)
	{
		return;
	}
	
	hero->setHaveJoinedGuildWar();
	//切地图的通信消息
	char msg[400] = {0};
	//保存切图前的点
	char* oldMapId = hero->getMapId();
	if (strlen(oldMapId) > 8)
	{
		//如果在动态衍生图（副本图，阵营战图，帮战图）中，就设置为主城
		// strncpy(oldMapId, "map_001", 8);
		oldMapId = "map_001";
		Point beforePt(8002, 3771);
		hero->setBeforePiexPt(beforePt);
	} else {
		hero->setBeforePiexPt(hero->getLocation());
	}
	hero->setMainSrc(oldMapId);	//设置跳转前的地图,便于返回；
	//切入地图诞生点
	Point targetPt = scene->getCampWarPt(group);
	
	hero->quit_scene();
	hero->setMap(scene);
	char *nowMapId = scene->getMapId();
	//int pos = findChar(nowMapId, '_', strlen(nowMapId));
#if 0	
	if (strlen(nowMapId) < 14)
	{
		return;
	}
	sub_str(mapNewId, nowMapId, 0, 14);
#else
	char* pChar = strrchr(nowMapId, '_');
	int size = pChar - nowMapId;
	if (size >= 14)
	{
		size = 14;
	}
	strncpy(mapNewId, nowMapId, size);
#endif
	// msg += "2";
	// msg += intTostring(CHANGE_SCENE);
	// msg += intTostring(SUCCESS);
	// msg += "," + mapNewId;
	// msg += intTostring(targetPt._x);
	// msg += intTostring(targetPt._y);
	
	sprintf(msg, "2,%d,1,%s,%d,%d", CHANGE_SCENE, mapNewId, targetPt._x, targetPt._y);
	send_msg(hero->getFd(),msg);  
	
	hero->setLocation(targetPt);
	hero->setWalkingFlg(false);	
	// hero->enter_scene();
}

//切出房间地图
void GuildWarRoom::exitMap(Hero *hero)
{
	char* mainSrcId;   
	Map_Inform *mainSrcMap;
	
	mainSrcId = hero->getMainSrc();	
	map<string,Map_Inform*>::iterator mainSrc_it;
	mainSrc_it = mapId_connect_map.find(mainSrcId);
	if(mainSrc_it == mapId_connect_map.end())
	{
		//没有原来的地图
		cout<<"when hero out guild war map can't find his srcMap!"<<endl;
		return;
	}
	
	mainSrcMap = mainSrc_it->second;
	/*退出房间地图*/
	quit_scene(hero, hero->getMap());
	/*进入原来地图*/
	enter_scenes(hero, mainSrcMap, 3);  	
}

//进入帮派战房间--这里可以用groupJudge调整
int GuildWarRoom::joinRoom(Hero *hero)
{
	if (hero->isInGuildWarRoom())
	{
		//玩家已经在某个帮战房间中
		return -1;
	}
	int group = groupJudge(hero);
	if (group < 0)
	{
		//玩家所在帮派未占领该房间
		return -2;
	}
	if (roomState & GWR_READY)
	{
		//房间已经就绪不能再加入
		return -3;
	}
	
	char* heroId = hero->getIdentity();
	enterMap(hero, group);
#if 0	
	//初始他的统计信息
	CountInfo_T *count = new CountInfo_T();		//统计信息
	countTable[0].insert(pair<string, CountInfo_T*>(heroId, count));
#endif
	
	joinNum[group]++;
	//超过5个人，帮主可以点击开始按钮
	if (joinNum[group] >= GUILD_PREPARE_MEMBS_NUM)
	{
		Hero *hostHero = heroid_to_hero(host[group]);
		if (hostHero != NULL)
		{
			//通知帮主可以点准备按钮
			informManagerCanStart(hostHero);
		}
	}
	
	//发给自己的消息
	int remainTime = getRemainTime();
	
	//设置玩家状态可以使外面知道玩家在帮派战房间中
	hero->setInGuildWarRoom(true, roomId);
	char joinMsg[200] = {0};
	// = "18";
	// joinMsg += intTostring(GUILD_WAR_JOIN_ONE);
	// joinMsg += "," + sideName[group];						//所在的帮派
	// joinMsg += "," + heroId;								//加入者ID
	// joinMsg += charTostring(hero->getNickName());			//加入玩家名
	// joinMsg += charTostring(hero->getParty());				//加入者门派
	// joinMsg += intTostring(hero->getLevel());				//加入者等级
	// joinMsg += intTostring(remainTime);				//定时器剩余时间
	sprintf(joinMsg, "18,%d,%s,%s,%s,%s,%d,%d,1", GUILD_WAR_JOIN_ONE, sideName[group], heroId,
		hero->getNickName(), hero->getParty(), hero->getLevel(), remainTime);
	// string myGuildJoinMsg = joinMsg + intTostring(1);		//我帮派加入了一个成员
	// string otherGuildJoinMsg = joinMsg + intTostring(0);	//他帮派加入了一个成员
	sendMsgToOneGroup(group, joinMsg, 0);			//发给自己帮派成员的信息
	memset(joinMsg, 0, sizeof(joinMsg));
	sprintf(joinMsg, "18,%d,%s,%s,%s,%s,%d,%d,0", GUILD_WAR_JOIN_ONE, sideName[group], heroId,
		hero->getNickName(), hero->getParty(), hero->getLevel(), remainTime);
	sendMsgToOneGroup(1 - group, joinMsg, 0);		//发给对方帮派的信息
	
	map<string, int>::iterator it_memb;
	char selfMsg[16000];
	// selfMsg += intTostring(GUILD_WAR_START_TIMER);
	// selfMsg += intTostring(0);							//是否为房主
	// selfMsg += intTostring(remainTime);					//剩余时间
	
	sprintf(selfMsg, "18,%d,0,%d", GUILD_WAR_START_TIMER, remainTime);
	int myGuildMsg = viewOneGuildMsg(group, selfMsg + strlen(selfMsg));
	int theirGuildMsg = viewOneGuildMsg(1 - group, selfMsg + strlen(selfMsg));
	// selfMsg += myGuildMsg;
	// selfMsg += theirGuildMsg;
	send_msg(hero->getFd(), selfMsg);
	return 0;
	
}

//通知帮主可以开始
void GuildWarRoom::informManagerCanStart(Hero *hero)
{
	char msg[16];
	// msg = "18";
	// msg += intTostring(INFORM_PREPARE_GUILD_WAR);				//18,6命令头
	// msg += "," + roomId;										//帮战房间ID
	sprintf(msg, "18,%d,%s", INFORM_PREPARE_GUILD_WAR, roomId);
	send_msg(hero->getFd(), msg);
}

//判断玩家所属
int GuildWarRoom::groupJudge(Hero *hero)
{
	if (hero->getGuildTitle() == -1)
	{
		return -1;
	} 
	
	char* guildName = hero->getGuildName();
	if (!strcmp(guildName, sideName[0]))
	{
		return 0;
	}
	if (!strcmp(guildName, sideName[1]))
	{
		return 1;
	}
	return -2;
}

//玩家的帮会已经占领了该房间
bool GuildWarRoom::isInThisRoom(char* heroId, int index)
{
#if 0
	if (countTable[index].find(heroId) == countTable[index].end())
#endif
	if (heroId_2_countInfo[index].find(heroId) == heroId_2_countInfo[index].end())
	{
		return false;
	} else {
		return true;
	}
}

//帮主点击开始按钮，（一个帮主点击开始另外一个帮主还没点击开始，之后是重新启用一个强制开始的定时器还是用前面的定时器？）
int GuildWarRoom::prepareGuildWar(Hero *manager)
{
	char* managerId = manager->getIdentity();
	int group = groupJudge(manager);
	if (group < 0)
	{
		//玩家所在帮派不是该房间占领帮
		
		return -1;
	}
	if (strcmp(managerId, host[group]) != 0)
	{
		//不是帮战领头羊--有这个判断就不用再判断玩家是否在本房间
		return -2;
	}
	if (!(roomState & GWR_TWO))
	{
		//房间还没进入两个帮派
		return -6;
	}
	if (joinNum[group] < GUILD_PREPARE_MEMBS_NUM)
	//if (joinNum[group] < 1)
	{
		//现在还不能开始
		return -3;
	}
	//开始的是自己帮的开始怎么判断
	if (guildPrepare[group])
	{
		//加一个标记自己帮派准备的标志guildPrepare
		//自己帮派已经准备过
		return -4;
	}
	if (roomState & GWR_READY)
	{
		//房间已经被定时器强制开始,再准备也晚了
		return -5;
	}
	
	if (roomState & GWR_PREPARE)
	{
		setRoomState(GWR_READY);
		//停下准备定时器的倒计时
		stopPrepareTimer();
		//开始5秒钟帮派战开始倒计时
		startReadyTimer();
	} else {
		setRoomState(GWR_PREPARE);
	}
	//标记自己帮派已经准备
	guildPrepare[group] = true;
	
	//准备成功，发消息通知玩家自己帮派已经准备
	if (!(roomState & GWR_READY))
	{
		char msg[65] = {0};
		// msg = "18";
		// msg += intTostring(WE_PREPARE_GUILD_WAR);				//18,7命令头
		// msg += "," + sideName[group];							//点击准备的帮派名
		sprintf(msg, "18,%d,1,%s", WE_PREPARE_GUILD_WAR, sideName[group]);
		sendMsgToOneGroup(group, msg, 0);
		memset(msg, 0, sizeof msg);
		sprintf(msg, "18,%d,0,%s", WE_PREPARE_GUILD_WAR, sideName[group]);
		sendMsgToOneGroup(1 - group, msg, 0);
	}
	return 0;
}

#if 0
//帮派战排名的比较函数
static bool guildWarComp(GuildWarSortItem first, GuildWarSortItem second)
{
	CountInfo_T *a, *b;
	a = first.second;
	b =	second.second;
	
	//先比较杀人数
	int aKillNum = a->killCount;
	int bKillNum = b->killCount;
	if (aKillNum > bKillNum)
	{
		return true;
		
	} else if (bKillNum > aKillNum) {
		return false;
		
	} else {
		//再比较伤害输出
		int aHurtCount = a->hurtCount;
		int bHurtCount = b->hurtCount;
		if (aHurtCount >= bHurtCount)
		{
			return true;
			
		} else {
			return false;
		}
	}
}
#endif

//帮派战玩家杀人数统计，杀人数和统计积分转换比例是1:5000
void GuildWarRoom::guildWarAddOneHeroKillNum(Hero *hero)
{
	int group = groupJudge(hero);
	if (group < 0)
	{
		return;
	}
	
	map<string, GuildWarCount_T*>::iterator it_cnt = heroId_2_countInfo[group].find(hero->getIdentity());
	if (it_cnt == heroId_2_countInfo[group].end())
	{
		return;
	}
	
	GuildWarCount_T *p = it_cnt->second;
	int index = p->index;
	warCount[group][index].score += guildWarCtl.killScoreOfHero;
	warCount[group][index].killNum += 1;
	
	totalKills[group] += 1;						//自己帮派的杀人数加1
	totalScore[group] += guildWarCtl.killScoreOfGuild;		//自己帮派总积分
	killLastTime[group] = MY_TV_SEC;			//自己帮派的最后一个杀人时间
}

//帮派战玩家伤害输出统计，伤害值和统计积分转换的比例是1:1
void GuildWarRoom::guildWarAddHurtCount(Hero *hero, int hurt)
{
	int group = groupJudge(hero);
	if (group < 0)
	{
		return;
	}
	if (hurt < 0)
	{
		return;
	}
	
	map<string, GuildWarCount_T*>::iterator it;
	it = heroId_2_countInfo[group].find(hero->getIdentity());
	for (it; it != heroId_2_countInfo[group].end(); it++)
	{
		//
	}
}

//帮派战排名
void GuildWarRoom::rankGuildWar()
{
	if (totalScore[0] > totalScore[1])
	{
		winIndex = 0;
	} else if (totalScore[1] > totalScore[0]) {
		winIndex = 1;
	} else {
		if (killLastTime[0] < killLastTime[1])
		{
			winIndex = 0;
		} else {
			winIndex = 1;
		}
	}
	Guild *warGuild[2];
	warGuild[0] = getGuildWithName(sideName[0]);
	warGuild[1] = getGuildWithName(sideName[1]);

	//生成帮派战日志
	//战胜帮派的日志
	if (warGuild[winIndex] != NULL)
	{
		warGuild[winIndex]->makeHistory(4, 7, sideName[1 - winIndex], sideName[1 - winIndex]);
	}
	//战败帮的日志
	if (warGuild[1 - winIndex] != NULL)
	{
		warGuild[1 - winIndex]->makeHistory(4, 9, sideName[winIndex], sideName[winIndex]);
	}
	
	//帮派战结束的消息
	char overMsg[128];
	
	// overMsg += intTostring(GUILD_WAR_OVER);
	// overMsg += "," + sideName[winIndex];		//获胜方帮派
	// overMsg += "," + sideName[1 - winIndex];	//战败方帮派
	sprintf(overMsg, "18,%d,%s,%s", GUILD_WAR_OVER, sideName[winIndex], sideName[1 - winIndex]);
	sendMsgToOneGroup(0, overMsg, 1);
	sendMsgToOneGroup(1, overMsg, 1);
	
#if 0	
	sort(guildWarRank[0].begin(), guildWarRank[0].end(), guildWarComp);
	sort(guildWarRank[1].begin(), guildWarRank[1].end(), guildWarComp);
	
	int i = 0;
	for(i; i < guildWarRank[0].size(); i++)
	{
		guildWarRank[0][i].second->ranking = i + 1;
	}
	
	for(i = 0; i < guildWarRank[1].size(); i++)
	{
		guildWarRank[1][i].second->ranking = i + 1;
	}
#endif
}

void GuildWarRoom::giveReward()
{
	//成员参战信息排序
	newCompMethod();
	
	Guild *warGuild[2];
	//把有奖励的玩家的帮战奖励给玩家
	for (int i = 0; i < 2; i++)
	{
		int k;
		int rewardGuildExp = rewardExpBase,
			rewardMoney = rewardMoneyBase,
			rewardGlory = rewardGloryBase;
		// string rewardMsg = "18";
		// rewardMsg += intTostring(GUILD_WAR_REWARD);
		bool isWinner;
		if (i == winIndex)
		{	
			isWinner = true;
			// rewardMsg += intTostring(SUCCESS);			//获胜方
			rewardGuildExp = rewardExpBase * 2;
			rewardMoney = rewardMoneyBase * 2;
			rewardGlory = rewardGloryBase * 2;
		} else {
			isWinner = false;
			// rewardMsg += intTostring(FAILED);			//战败方
		}
		warGuild[i] = getGuildWithName(sideName[winIndex]);
		if (warGuild[i] == NULL)
		{
			continue;
		}
		//帮派等级越高奖励越高
		rewardGuildExp *= warGuild[i]->getLevel();
		rewardMoney *= warGuild[i]->getLevel();
		rewardGlory *= warGuild[i]->getLevel();
#if 0		
		map<int, string>::reverse_iterator it;
		it = score_2_heroId[i].rbegin();
		int size = joinNum[i];
		for(it, k = 1; it != score_2_heroId[i].rend(); k++, it++)
		{
			// rewardMsg += intTostring(k);		//帮战获得的名次
			int times = ((k >= 10) ? 1 : (10 - k));
			if (it->first < 5000)
			{
				//积分小于5000没有奖励
				times = 0;
			}
#endif	
		for (k = 0; k < joinNum[i]; k++)
		{
			int times = ((k >= 9) ? 1 : (10 - k - 1));
			if (p_rank[i][k]->score < guildWarCtl.killScoreOfHero)
			{
				//如果一个人都没杀，奖励为0
				times = 0;
			}
			
			int oneRewardGuildExp = rewardGuildExp * times;
			int oneRewardMoney = rewardMoney * times;
			int oneRewardGlory = rewardGlory * times;
			char heroId[IDL + 1];
#if 0			
			sprintf(heroId, "%s", it->second.c_str());
#endif
			sprintf(heroId, "%s", p_rank[i][k]->heroId);
			//把帮派相关的加到帮派属性
			int contb = addGuildExp(sideName[i], heroId, oneRewardGuildExp);
			addMyGuildGlory(sideName[i], heroId, oneRewardGlory);
			//生成一条历史记录，记录玩家帮派战奖励
			warGuild[i]->makeHistory(2, 2, heroId, warGuild[i]->getHeroNickName(heroId),
				oneRewardGuildExp, oneRewardGlory, oneRewardMoney, contb);
				
			// cout<<oneRewardGuildExp<<endl;
			// cout<<oneRewardGlory<<endl;
			// cout<<oneRewardMoney<<endl;
			
			//角色id得到角色实例
			map<string, Hero*>::iterator it_hero;
			it_hero = heroId_to_pHero.find(heroId);
			if(it_hero == heroId_to_pHero.end())
			{
				//金钱加不上去了，先记录成未处理事件，等到他在上线的时候再处理
				UnhandleAttr_T moneyData(UNHANDLE_BOUND_GAME_MONEY, oneRewardMoney);
				UNHANDLE_FUNC(heroId, 5, moneyData);
				continue;
			}
			Hero *hero = it_hero->second;
			// Money *heroMoney = hero->getMoney();
			// heroMoney->increaseBoundGameMoney(oneRewardMoney);
			hero->increaseMoney(3, oneRewardMoney);
			/* char rewd[256];
			if (winIndex == i) {
				sprintf(rewd, "所在帮派在帮派战中获胜！个人积分为%d,获得了%d名，获得了%d绑定游戏币，%d帮贡，为帮派增加了%d经验。", it->first, k, oneRewardMoney, oneRewardGlory, oneRewardGuildExp);
			} else {	
				sprintf(rewd, "所在帮派在帮派战中战败！个人积分为%d,获得了%d名，获得了%d绑定游戏币，%d帮贡，为帮派增加了%d经验。", it->first, k, oneRewardMoney, oneRewardGlory, oneRewardGuildExp);
			
			}
			rewardMsg = rewad; 
			systemSendMssage(hero, rewardMsg, 0); */
			// rewardMsg += intTostring(oneRewardGuildExp);
			// rewardMsg += intTostring(oneRewardMoney);
			// rewardMsg += intTostring(rewardGlory);
			char rewardMsg[256] = {0};
			sprintf(rewardMsg, "18,%d,%d,%d,%d,%d,%d", GUILD_WAR_REWARD, isWinner, k + 1,
				oneRewardGuildExp, oneRewardMoney, oneRewardGlory);
			send_msg(hero->getFd(), rewardMsg);
			
		}
	}
}

//获取房间领头人
Hero* GuildWarRoom::getHost(int index)
{
	return heroid_to_hero(host[index]);
}

//获取定时器剩余时间
int GuildWarRoom::getRemainTime()
{
	double remain = ev_timer_remaining(loops, &timer);		//定时器还剩余的时间
	if (remain < 0 || remain > 600)
	{
		remain = 0;
	}
	return remain;
}

//退出帮派战
void GuildWarRoom::exit(Hero *hero, bool offlineFlag)
{
	int group = groupJudge(hero);
	if (group < 0)
	{
		//玩家所在帮派未占领该房间
		return;
	}
	
	//判断是不是房主
	char* heroId = hero->getIdentity();
	//设置玩家状态不在帮派战房间中
	hero->setInGuildWarRoom(false, NULL);
	//不叉掉了，维亮说中途退出的也给奖励
	//heroId_2_score[group].erase(heroId);
	//wellion去死，给你妹
	
	int delRet = delOneGroupMem(group, heroId);
	if (delRet != 0)
	{
		char msg[400] = {0};
		sprintf(msg, "exit from guildWarRoom error for delOneGroupMem fail and return %d", delRet);
		send_msg(hero->getFd(), msg);
	}
	//是否有一帮全部退出
	bool oneSideAllExitFlag = false;
	//是否更换房主
	bool changerLeaderFlag = false; 
	if (joinNum[group] == 1)
	{
		Guild *guild = getGuildWithName(sideName[group]);
		if (guild != NULL)
		{
			send_msg(hero->getFd(), "50,0,0,this guy is last one in the room so set his guild inwarstate no");
			guild->setJoinGuildWar(false);
		}
		//该帮派的最后一个人退出
		if (roomState & GWR_START)
		{
			//在战斗开始后的退出，这个时候已经有奖励信息，已经空的这个帮派数据不清除
			
		} else {
			//没有开始战斗，房间状态都要还原
			memset(host[group], 0, sizeof(host[group]));
			// warGuild[group] = NULL;
			memset(sideName[group], 0, sizeof(sideName[group]));
			guildPrepare[group] = false;
			callFreqCtl[group] = MY_TV_SEC;
			totalKills[group] = 0;
			totalScore[group] = 0;
			
			if (roomState & GWR_READY)
			{
				//在准备后的退出，这个时候要清空一边的信息，房间置为重新可再加入帮派，定时器换做无
				stopReadyTimer();
				//向客户端发消息通知客户端，另外一个帮派的人都退出完了
				oneSideAllExitFlag = true;
				//重新设置房间状态
				roomState = GWR_ONE;
				
			} else if (roomState & GWR_TWO)
			{
				//在强开定时器开始计时后的退出
				stopPrepareTimer();
				//向另外一个帮派的客户端发消息，房间重置了
				oneSideAllExitFlag = true;
				//重新设置房间状态
				roomState = GWR_ONE;
				
			} else if (roomState & GWR_LOCK)
			{
				//在房间密码保护期间的退出
				unlockRoom();
				stopLockTimer();
				roomState = GWR_IDLE;
				startResetTimer();			//开启重置定时器
			}else if (roomState & GWR_ONE)
			{
				roomState = GWR_IDLE;
				startResetTimer();			//开启重置定时器
			}
		}
	} else {
		//不是帮派的最后一个人退出
		if (!strcmp(heroId, host[group]))
		{
			//退出者是房主,要再选一个房主
			map<string, GuildWarCount_T*>::iterator it;
			
			Hero *nextHero = NULL;
			for (it = heroId_2_countInfo[group].begin(); it != heroId_2_countInfo[group].end(); it++)
			{
				string nextHeroId = it->first;
				//角色id得到角色实例
				map<string, Hero*>::iterator it_hero;
				it_hero = heroId_to_pHero.find(nextHeroId);
				if(it_hero == heroId_to_pHero.end())
				{
					//角色不在线，换下一个
					continue;
				}
				nextHero = it_hero->second;
				//还要看他在不在房间中，因为即使他退出了，这里也要存着到他发了奖励
				if (!nextHero->isInGuildWarRoom())
				{
					continue;
				}
				
				strncpy(host[group], nextHeroId.c_str(), nextHeroId.size() + 1);
				changerLeaderFlag = true;
				
			}
			
		} else {
			//退出者不是房主
		}
	}
	
	//下线的共同处理
	
	joinNum[group] -= 1;
	if (offlineFlag)
	{
		//玩家是下线的
		//string mapId = "map_001";
		hero->setMapId(hero->getMainSrc());
		hero->setLocation(hero->getBeforePiexPt());
	}
	
	//发消息通知下线了一个人
	// string exitOneMsg = "18";
	// exitOneMsg += intTostring(GUILD_WAR_ONE_EXIT);
	// exitOneMsg += "," + sideName[group];
	// exitOneMsg += "," + heroId;
	// string myGuildExitOneMsg = exitOneMsg;
	// myGuildExitOneMsg += intTostring(1);
	// string theirGuildExitOneMsg = exitOneMsg;
	// theirGuildExitOneMsg += intTostring(0);
	char exitOneMsg[256];
	sprintf(exitOneMsg, "18,%d,%s,%s,1", GUILD_WAR_ONE_EXIT, sideName[group], heroId);
	sendMsgToOneGroup(group, exitOneMsg, 0);
	sprintf(exitOneMsg, "18,%d,%s,%s,0", GUILD_WAR_ONE_EXIT, sideName[group], heroId);
	sendMsgToOneGroup(1 - group, exitOneMsg, 0);
	
	//如果有以帮派全部退出
	if (oneSideAllExitFlag)
	{	
		char exitAllMsg[16];
		// = "18";
		// exitAllMsg += intTostring(GUILD_WAR_ONE_SIDE_EXIT);
		sprintf(exitAllMsg, "18,%d", GUILD_WAR_ONE_SIDE_EXIT);
		sendMsgToOneGroup(1 - group, exitAllMsg, 0);
	}
	
	//如果退出者是帮主，且退出后换了帮主
	if (changerLeaderFlag)
	{
		int remainTime = getRemainTime();
		// string myMsg = "18";
		// myMsg += intTostring(GUILD_WAR_START_TIMER);
		// myMsg += intTostring(1);				//是否为房主
		// myMsg += intTostring(remainTime);		//定时器剩余时间
		char myMsg[16000];
		sprintf(myMsg, "18,%d,1,%d", GUILD_WAR_CHANGE_LEADER, remainTime);
		viewOneGuildMsg(group, myMsg + strlen(myMsg));
		viewOneGuildMsg(1 - group, myMsg + strlen(myMsg));
		
		// myMsg += myGuildMsg;
		// myMsg += theirGuildMsg;
		Hero *nextHost = heroid_to_hero(host[group]);
		if (nextHost != NULL)
		{
			send_msg(nextHost->getFd(), myMsg);
		}
	}
	if (!offlineFlag)
	{
		//玩家不是下线的退出
		// string selfExitMsg = "18";
		// selfExitMsg += intTostring(GUILD_WAR_SELF_EXIT);		//给自己发，通知自己退出帮派成功
		char selfExitMsg[16];
		sprintf(selfExitMsg, "18,%d", GUILD_WAR_SELF_EXIT);
		send_msg(hero->getFd(), selfExitMsg);
		//把他切出房间地图
		exitMap(hero);
	}
}

//向一边的参战人员发消息, flag = 0：只向房间中的人发，1：向战斗开始后曾经在房间中的人发
void GuildWarRoom::sendMsgToOneGroup(int group, char* msg, int flag)
{
	map<string, GuildWarCount_T*>::iterator it;
	for (it = heroId_2_countInfo[group].begin(); it != heroId_2_countInfo[group].end(); it++)
	{
		// string nextHeroId = it->first;
		//角色id得到角色实例
		map<string, Hero*>::iterator it_hero;
		it_hero = heroId_to_pHero.find(it->first);
		if(it_hero == heroId_to_pHero.end())
		{
			//角色不在线，换下一个
			continue;
		}
		Hero *nextHero = it_hero->second;
		if (flag = 0)
		{
			if (nextHero->isInGuildWarRoom())
			{
				continue;
			}
		}
		
		send_msg(nextHero->getFd(), msg);
	}
}

//重置房间
void GuildWarRoom::resetRoom()
{
	int i = 0;
	for (i; i < 2; i++)
	{
		map<string, GuildWarCount_T*>::iterator it;
		for(it = heroId_2_countInfo[i].begin(); it != heroId_2_countInfo[i].end(); it++)
		{
			// string nextHeroId = it->first;
			//角色id得到角色实例
			map<string, Hero*>::iterator it_hero;
			it_hero = heroId_to_pHero.find(it->first);
			if(it_hero == heroId_to_pHero.end())
			{
				//角色不在线，换下一个
				continue;
			}
			Hero *nextHero = it_hero->second;
			
			nextHero->setInGuildWarRoom(false, NULL);
			//把他切出房间地图
			exitMap(nextHero);
		}
		memset(host[i], 0, sizeof(host[i]));			//host[0]:房主，host[1]:房客
		// warGuild[i] = NULL;					//参战帮派
		
		Guild *guild = getGuildWithName(sideName[i]);
		if (guild != NULL)
		{
			// send_msg(sock_fd, "50,0,0,It's time to reset the room ,so if there is guild in this room need clear guild state");
			guild->setJoinGuildWar(false);
		}
		memset(sideName[i], 0, sizeof(sideName[i]));	//sideName[0]:主帮名；sideName[1]:客帮名
		joinNum[i] = 0;						//每帮的参与人数
		guildPrepare[i] = false;			//帮派开始准备
		callFreqCtl[i] = MY_TV_SEC;			//重置为当前时间
		totalKills[i] = 0;					//总的杀人数
		totalScore[i] = 0;
		groupFlagState[i] = 0;
	}
	
	guildFlag[0].init();
	guildFlag[1].init();
	guildFlag[2].init();
	
	initRoomInfo();						//统计数据初始化
	roomState = 0;
	memset(password, 0, sizeof(password));
	scene->initTakeGoods();
}

//查看一方帮派房间信息
int GuildWarRoom::viewOneGuildMsg(int group, char* result)
{
	
	map<string, GuildWarCount_T*>::iterator it_memb;
	// string groupMsg;
	// groupMsg += "," + sideName[group];		//自己帮派帮派名
	// groupMsg += intTostring(joinNum[group]);			//自己帮派加入人数
	sprintf(result, ",%s,%d", sideName[group], joinNum[group]);
	for (it_memb = heroId_2_countInfo[group].begin(); it_memb != heroId_2_countInfo[group].end(); it_memb++)
	{
		char membId[IDL + 1];
		sprintf(membId, "%s", it_memb->first.c_str());		//成员名
		Hero *memb = heroId_to_pHero.find(membId)->second;
		if (memb->isInGuildWarRoom())
		{
			// groupMsg += "," + membId;							//成员Id，便于查看成员信息
			// groupMsg += charTostring(memb->getNickName());		//成员昵称，用于显示
			// groupMsg += charTostring(memb->getParty());			//成员
			// groupMsg += intTostring(memb->getLevel());			//成员等级
			sprintf(result + strlen(result), ",%s,%s,%s,%d", membId,
				memb->getNickName(), memb->getParty(), memb->getLevel());
		}
	}
	
	return 0;
}

//帮战中复活
int GuildWarRoom::revival(Hero* hero)
{
	cout<<"have enter guild war room's revival!!!"<<endl;
	int group = groupJudge(hero);
	if (group != 0 && group != 1)
	{
		cout<<"hero in guild war and his group is invalid & group is "<<group<<endl;
		return -1;
	}
	Point revivalPt = scene->getCampWarPt(group);
	int revival_life=hero->getLifeUpperVal();
	int revival_magic=hero->getMagicUpperVal();
	hero->setLifeVal(revival_life);
	hero->setMagicVal(revival_magic);
	char mapNewId[IDL + 1] = {0};
	char *nowMapId = scene->getMapId();
	//int pos = findChar(nowMapId, '_', strlen(nowMapId));
#if 0	
	if (strlen(nowMapId) < 14)
	{
		cout<<"hero guild war map id is "<<nowMapId<<" it's invalid"<<endl;
		return -2;
	}
	sub_str(mapNewId, nowMapId, 0, 14);
#else
	char* pChar = strrchr(nowMapId, '_');
	int size = pChar - nowMapId;
	if (size >= 14)
	{
		size = 14;
	}
	strncpy(mapNewId, nowMapId, size);
#endif

	hero->quit_scene();
	hero->setMap(scene);
	hero->setMapId(nowMapId);
	hero->setLocation(revivalPt);
	
	char msg[1024] = {0};
	snprintf(msg, sizeof(msg), "%d,%d,%d,%s,%d,%d", 2, CHANGE_SCENE, SUCCESS, mapNewId, revivalPt._x, revivalPt._y);
	cout<<"msg is "<<msg<<endl;
	send_msg(hero->getFd(), msg);
	hero->setWalkingFlg(false);

	hero->setLifeStation(1);
	memset(msg, 0, sizeof(msg));
	snprintf(msg, sizeof(msg), "%d,%d,%d,%d", 7, 0, revival_life, revival_magic);
	send_msg(hero->getFd(), msg);	
	return 0;
}

//初始房间数据
void GuildWarRoom::initRoomInfo()
{
	int i = 0, j = 0;
	for (i; i < 2; i++)
	{
		firstFreeIndex[i] = 0;
		heroId_2_countInfo[i].clear();
		
		for (j = 0; j < MAX_GUILD_MEMBS - 1; j++)
		{
			memset(warCount[i][j].heroId, 0, sizeof warCount[i][j].heroId);
			warCount[i][j].index = j;
			warCount[i][j].score = 0;
			warCount[i][j].killNum = 0;
			warCount[i][j].ranking = 0;
			warCount[i][j].nextFreeIndex = j + 1;
			p_rank[i][j] = NULL;
		}
		warCount[i][j].nextFreeIndex = GUILD_END_FLAG;
	}
}

//参战一方增加一个成员
int GuildWarRoom::addOneGroupMem(int group, char* heroId)
{
	//参数检查
	if (group < 0 || group > 1)
	{
		return 1;
	}
	
	if (heroId == NULL || strlen(heroId) == 0)
	{
		return 2;
	}
	
	//
	GuildWarCount_T *p = NULL;
	if (firstFreeIndex[group] == GUILD_END_FLAG)
	{
		//人数已经加满
		return 3;
	}
	int temp = firstFreeIndex[group];
	firstFreeIndex[group] = warCount[group][temp].nextFreeIndex;
	strncpy(warCount[group][temp].heroId, heroId, sizeof (warCount[group][temp].heroId));
	warCount[group][temp].score = 0;
	warCount[group][temp].killNum = 0;
	warCount[group][temp].ranking = 0;
	warCount[group][temp].nextFreeIndex = GUILD_USED_FLAG;
	p = &warCount[group][temp];
	heroId_2_countInfo[group].insert(pair<string, GuildWarCount_T*>(heroId, p));
	return 0;
}

//删除参战一方的一个成员
int GuildWarRoom::delOneGroupMem(int group, char* heroId)
{
	if (group < 0 || group > 1)
	{
		return 1;
	}
	if (heroId == NULL || strlen(heroId) == 0)
	{
		return 2;
	}
	map<string, GuildWarCount_T*>::iterator it_cnt;
	GuildWarCount_T *p = NULL;
	it_cnt = heroId_2_countInfo[group].find(heroId);
	if (it_cnt == heroId_2_countInfo[group].end())
	{
		return 3;
	}
	p = it_cnt->second;
	int index = p->index;
	memset(warCount[group][index].heroId, 0, sizeof warCount[group][index].heroId);
	warCount[group][index].score = 0;
	warCount[group][index].killNum = 0;
	warCount[group][index].ranking = 0;
	warCount[group][index].nextFreeIndex = firstFreeIndex[group];
	firstFreeIndex[group] = index;
	heroId_2_countInfo[group].erase(heroId);
	return 0;
}


//帮战一方帮派成员内排序
void GuildWarRoom::newCompMethod()
{
	int i = 0, j;
	
	map<string, GuildWarCount_T*>::iterator it_cnt;
	GuildWarCount_T* temp = NULL;
	//用以排序的指针指向所有待排序的项
	for (i; i < 2; i++)
	{
		j = 0;
		for (it_cnt = heroId_2_countInfo[i].begin(); it_cnt != heroId_2_countInfo[i].end(); it_cnt++)
		{
			p_rank[i][j++] = it_cnt->second;
		}
		
		if (j != joinNum[i])
		{
			cout<<"There must somewhere count hero error!"<<endl;
			joinNum[i] = j;
		}
		
		int m = 0, n = 0;
		for (m = 0; m < joinNum[i]; m++)
		{
			for (n = joinNum[i] - 1; n != m; n--)
			{
				if (p_rank[i][n]->score > p_rank[i][m]->score)
				{
					temp = p_rank[i][n];
					p_rank[i][n] = p_rank[i][m];
					p_rank[i][m] = temp;
				}
			}
		}
	}
	
}

//密码保护定时器（3分钟定时）的到期处理
static void defend_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	int flagIndex = atoi(think->targetId);
	if (flagIndex < 0 || flagIndex > 2)
	{
		return;
	}
	
	GuildWarRoom *room = (GuildWarRoom *)think->target;
	
	if (room != NULL)
	{
		room->occupyFlag(flagIndex);
	}
}
	
int GuildWarRoom::startDefendFlagTimer(int index)
{
	if (index < 0 || index > 2)
	{
		return 1;
	}
	
	char flagIndexStr[32] = {0};
	sprintf(flagIndexStr, "%d", index);
	ext_ev_timer_init(&flagTimer[index], defend_timer_cb, GUILD_WAR_DEFEND_FLAG_LIMIT, 0, this, flagIndexStr);
    ev_timer_start(loops, &flagTimer[index]);
	return 0;
}

int GuildWarRoom::stopDefendFlagTimer(int index)
{
	if (index < 0 || index > 2)
	{
		return 1;
	}
	
	ev_timer_stop(loops, &flagTimer[index]);
	return 0;
}

//玩家是否可以采集某个旗帜
int GuildWarRoom::isPickFlagOk(Hero* hero, int index)
{
	if (index < 0 || index > 2)
	{
		return -1;
	}
	int group = groupJudge(hero);
	if (guildFlag[index].state == 1)
	{
		return -2;
	}
	else if (guildFlag[index].state == 3)
	{
		return -3;
	}
	else if (guildFlag[index].state == 2 && (groupFlagState[group] >> index) & 1)
	{
		return -4;
	}
	else if (guildFlag[index].state == 0 && index == 2 && (guildFlag[0].state != 3 || guildFlag[1].state != 3)){
		return -5;
	}
	
	guildFlag[index].state = 1;
	
	return 0;
}

//采旗结束
int GuildWarRoom::finishPickFlag(Hero* hero, int index)
{
	if (index < 0 || index > 2)
	{
		return -1;
	}
	
	if (!(roomState & GWR_START))
	{
		return -2;
	}
	
	int group = groupJudge(hero);
	
	//已经被采集走
	if (guildFlag[index].state != 1)
	{
		return -3;
	}
	
	stopDefendFlagTimer(index);
	groupFlagState[0] &= ~(1 << index);
	groupFlagState[1] &= ~(1 << index);
	guildFlag[index].state = 2;
	groupFlagState[group] |= 1 << index;
	strncpy(guildFlag[index].ownerHeroId, hero->getIdentity(), sizeof guildFlag[index].ownerHeroId);
	strncpy(guildFlag[index].ownerGuildName, sideName[group], sizeof guildFlag[index].ownerGuildName);
	guildFlag[index].group = group;
	startDefendFlagTimer(index);
	return 0;
	
}

//停止采旗
int GuildWarRoom::stopPickFlag(int index)
{
	
	if (index < 0 || index > 2)
	{
		return -1;
	}
	
	if (guildFlag[index].state != 1)
	{
		return -2;
	}
	
	if (strlen(guildFlag[index].ownerHeroId) != 0)
	{
		guildFlag[index].state = 2;
	} else {
		guildFlag[index].state = 0;
	}
	
	return 0;
}


//占据旗帜
void GuildWarRoom::occupyFlag(int index)
{
	if (strlen(guildFlag[index].ownerHeroId) != 0)
	{
		guildFlag[index].state = 3;
	}
	
	int group = guildFlag[index].group;
	totalScore[group] += guildWarCtl.flagScoreOfGuild[index];

	
	map<string, GuildWarCount_T*>::iterator it_cnt = heroId_2_countInfo[group].find(guildFlag[index].ownerHeroId);
	if (it_cnt == heroId_2_countInfo[group].end())
	{
		return;
	}
	
	GuildWarCount_T *p = it_cnt->second;
	int heroIndex = p->index;
	warCount[group][heroIndex].score += guildWarCtl.flagScoreOfHero[index];
}
