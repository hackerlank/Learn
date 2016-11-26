/****************************************************************
 * Filename: rob_flag_war_logic.h
 * 
 * Description: 夺旗战逻辑
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/

#include"rob_flag_war_logic.h"
#include "money_operator.h"

#define NORMAL_VESION_FOR_ROB_FLAG_WAR

extern map<string,Map_Src*> mapId_connect_map;
extern MapType_T mapTypeInfo;		//默写特殊地图的ID；


RobFlagWarLogic::RobFlagWarLogic()
{
	Map_Src  *warMap = NULL;	
	map<string,Map_Src*>::iterator it_map;
	
	it_map = mapId_connect_map.find(mapTypeInfo.guidWarMapId);
	if(it_map == mapId_connect_map.end()){
		return ;
	}
	warMap = it_map->second;
	
	for(int i = MAX_ROB_FLAG_WAR_ROOM_NUM - 1; i >= 0; i--)
	{
		Map_Src *scene = NULL;
		scene = warMap->copyMap(i);
		
		RobFlagWar *room = new RobFlagWar(i, scene);
		
		allRobFlagWarRooms.insert(pair<string, RobFlagWar*>(room->getRoomId(), room));
		idleRobFlagWarRooms.push_back(room);
	}

#if defined(NORMAL_VESION_FOR_ROB_FLAG_WAR)
	isInRobFlagWarTime = false;
#else
	isInRobFlagWarTime = true;
#endif
}

RobFlagWar* RobFlagWarLogic::roomId_2_room(char *roomId)
{
	map<string, RobFlagWar*>::iterator it = allRobFlagWarRooms.find(roomId);
	if (it == allRobFlagWarRooms.end())
	{
		return NULL;
	} else {
		return it->second;
	}
}


int RobFlagWarLogic::viewRoomState(Hero *hero, char* result)
{	
	//channel = 0,如果帮派已经参战了就直接进了
	int ret = joinRoom(hero, NULL, NULL, 0);
	
	if (ret == 6)
	{
		int title = hero->getGuildTitle();
		if (title != 0 && title != 1)
		{
			//您所在帮派未参加夺旗战，无法从帮派NPC进入夺旗房间。
			return 6;
		}
		
		map<string, RobFlagWar*>::iterator it = allRobFlagWarRooms.begin();
		
		sprintf(result + strlen(result), "%d", (int)(allRobFlagWarRooms.size()));
		//逐个遍历房间状态
		for (it; it != allRobFlagWarRooms.end(); it++)
		{
			RobFlagWar* room;
			room = it->second;
			int remain = 0;
			
			sprintf(result + strlen(result), ",%s,%d", room->getRoomId(), remain);
			for (int i = 0; i < 2; i++)
			{
				char *guildName = room->getGuildName(i);
				if (strlen(guildName) != 0)
				{
					sprintf(result + strlen(result), ",%s", guildName);

				} else {
					
					sprintf(result + strlen(result), ",");
				}
			}
		}
		
		return 7;
	}
	
	return ret;
}
	
int RobFlagWarLogic::exitRoom(Hero* hero, bool offFlag)
{
	Guild *guild = hero->getGuild();
	if (guild == NULL)
	{
		//退出夺旗战房间失败：您未加入帮派。
		return 1;
	}
	
	if (!hero->isInGuildWarRoom())
	{
		//退出夺旗战房间失败：您当前不在夺旗战房间。
		return 2;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	
	RobFlagWar *room = roomId_2_room(roomId);
	if (room == NULL)
	{
		//退出夺旗战房间失败：您所要退出的夺旗战房间不存在。
		return 3;
	}
	
	char *guildName = hero->getGuildName();
	
	int group = room->groupJudge(guildName);
	if (group != 0 && group != 1)
	{
		//退出夺旗战房间失败：该夺旗战房间中不存在你的信息。
		return 4;
	}
	
	stopPicking(hero);
	stopBring(hero);
	
	int ret = room->delOneMem(group, hero->getIdentity());
	if (ret != 0)
	{
		//系统错误：（错误码：100632）请联系客服。
		return ret;
	}
	
	int joinNum = room->getJoinNum(group);
	int roomState = room->getRoomState();
	
	if (joinNum == 0)
	{
		if (roomState == ROB_FLAG_WAR_ROOM_OCCUPY_STATE)
		{
			resetRoom(room);
		} else if (roomState == ROB_FLAG_WAR_ROOM_LOCK_STATE)
		{
			resetRoom(room);
		} else if (roomState == ROB_FLAG_WAR_ROOM_PREPARE_STATE)
		{
			stopRoomTimer(room);
			guild->setJoinGuildWar(false);
			room->initOneGroup(group);
			room->setRoomState(ROB_FLAG_WAR_ROOM_OCCUPY_STATE);
			
		} else if (roomState == ROB_FLAG_WAR_ROOM_READY_STATE)
		{
			gameOver(room, group);
		} else if (roomState == ROB_FLAG_WAR_ROOM_START_STATE)
		{
			gameOver(room, group);
		} else if (roomState == ROB_FLAG_WAR_ROOM_OVER_STATE)
		{
			if (room->getJoinNum(1 - group) == 0)
			{
				stopRoomTimer(room);
				resetRoom(room);
			}
		}
		
	} else {
		if (roomState != ROB_FLAG_WAR_ROOM_OVER_STATE)
		{
			if (!strcmp(room->getHostId(group), hero->getIdentity()))
			{
				chgHost(room, group);
			}
			
			if (joinNum < robFlagWarCtl.quickStartNeedHeroNum)
			{
				stopRoomTimer(room);
				room->setIsPrepare(group, false);
			}
		}
		
	}
	
	hero->setInGuildWarRoom(false, NULL);
	exitMap(hero);
	
	updateRoomJoinList(room);
	
	if (!offFlag)
	{
		sendOutRobWarMsg(hero);
	}
	return 0;
}


int RobFlagWarLogic::joinRoom(Hero *hero, char *roomId, char *password, int channel)
{
#if defined(NORMAL_VESION_FOR_ROB_FLAG_WAR)
	if (!isInRobFlagWarTime)
	{
		//当前不在夺旗战时间，无法进入！
		return 1;
	}
#endif
	
	Guild* guild = hero->getGuild();
	if (guild == NULL)
	{
		//您还没加入帮派，无法参与夺旗战。
		return 2;
	}
	
	if (hero->isInGuildWarRoom())
	{
		//您已经在夺旗战房间中！
		return 3;
	}
	
	if (strlen(hero->memHero->wagonId) != 0)
	{
		//您正在运送镖车任务，不能进入夺旗战战。
		return 4;
	}
	
	RobFlagWar *room = NULL;
	map<string, RobFlagWar*>::iterator it;
	int group = 0;
	if (guild->isInGuildWarRoom())
	{
		room = roomId_2_room(guild->getGuildWarRoomId());
		if (room == NULL)
		{
			//系统错误（错误码：100619）,请联系客服。
			return 5;
		}
		else
		{
			group = room->groupJudge(hero->getGuildName());
		}
	} else {
		if (channel == 0)
		{
			//请勿使用辅助软件！
			return 6;
		}
		
		//channel = 1,2时
		int title = hero->getGuildTitle();
		if (title != 0 && title != 1)
		{
			//只有副帮主以上职务能创建夺旗战房间！
			return 7;
		}
		
		if (roomId == NULL || strlen(roomId) == 0)
		{
			//创建
			if (idleRobFlagWarRooms.size() == 0)
			{
				//当前无空闲夺旗战房间，暂时无法创建。
				return 8;
			}
			room = idleRobFlagWarRooms.back();
			idleRobFlagWarRooms.pop_back();
			group = 0;
		} else {
			//挑战
			room = roomId_2_room(roomId);
			if (room == NULL){
				//您所挑战的夺旗战房间不存在。
				return 9;
			}
			
			if (room->getRoomState() <= ROB_FLAG_WAR_ROOM_IDLE_STATE)
			{
				//挑战失败，对方帮派不存在
				return 12;
			}
			if (room->getRoomState() >= ROB_FLAG_WAR_ROOM_PREPARE_STATE)
			{
				//挑战失败，房间中已经有两个帮派
				return 13;
			}
			
			group = (room->getJoinNum(0) != 0);
			if (room->isLock())
			{
				if (password == NULL || !room->pwdCheckOk(password))
				{
					//房间密码输入错误。
					return 10;
				}
			}
		}
		
	}

	int roomState = room->getRoomState();
	if (roomState != ROB_FLAG_WAR_ROOM_IDLE_STATE
		&& roomState != ROB_FLAG_WAR_ROOM_OCCUPY_STATE
		&& roomState != ROB_FLAG_WAR_ROOM_LOCK_STATE
		&& roomState != ROB_FLAG_WAR_ROOM_PREPARE_STATE)
	{
		//房间正在发送奖励，当前阶段无法加入。
		return 11;
	} else {
		if (room->getJoinNum(group) == 0)
		{
			int guildRank = getGuildRankInCamp(hero->getGuildId());
			cout<<"guildRank is :::"<<guildRank<<endl;
			room->initOneGroup(group, guildRank, hero->getGuildName(), hero->getIdentity());
		}
		int ret = room->addOneMem(group, hero->getIdentity(), hero->getNickName(), hero->getParty(), hero->getLevel());
		if (ret != 0)
		{
			// -1
			if (room->getJoinNum(group) == 0)
			{
				room->initOneGroup(group);
			}
			//系统错误（错误码：100626）,请联系客服。
			return ret;
		} else {
			enterMap(room->getScene(), hero, group);
			hero->setInGuildWarRoom(true, room->getRoomId());
			if (room->getJoinNum(group) == 1)
			{
				//所在帮派第一个进入的人
				guild->setJoinGuildWar(true, room->getRoomId());
				if (roomState == ROB_FLAG_WAR_ROOM_IDLE_STATE)
				{
					room->setRoomState(ROB_FLAG_WAR_ROOM_OCCUPY_STATE);
					if (password != NULL && strlen(password) != 0)
					{
						room->setPassword(password);
						room->setRoomState(ROB_FLAG_WAR_ROOM_LOCK_STATE);
						startRoomTimer(room);
					}
					
				} else if (roomState == ROB_FLAG_WAR_ROOM_OCCUPY_STATE)
				{
					if (room->isLock())
					{
						stopRoomTimer(room);
						room->setPassword(NULL);
					}
					room->setRoomState(ROB_FLAG_WAR_ROOM_PREPARE_STATE);
					startRoomTimer(room);
				}
			}
			
			updateRoomJoinList(room);
			
			informHostPrepare(room, group);
			
			return 0;
		}
	}
	
}


void RobFlagWarLogic::resetRoom(RobFlagWar* room)
{
	stopRoomTimer(room);
	map<string, RobFlagWarHeroData_T*>::iterator it;
	map<string, RobFlagWarHeroData_T*> *joinList = NULL;
	for (int i = 0; i < 2; i++)
	{
		joinList = room->getJoinList(i);
		for (it = joinList->begin(); it != joinList->end(); it++)
		{
			Hero *hero = heroid_to_hero(it->first);
			if (hero != NULL)
			{
				hero->setInGuildWarRoom(false, NULL);
				sendOutRobWarMsg(hero);
				exitMap(hero);
			}
		}
		
		char *guildName = room->getGuildName(i);
		Guild *guild = getGuildWithName(guildName);
		if (guild != NULL)
		{
			guild->setJoinGuildWar(false);
		}
	}

	room->reset();
	
	idleRobFlagWarRooms.push_back(room);
}

void RobFlagWarLogic::gameOver(RobFlagWar* room, int awayGroup)
{
	stopRoomTimer(room);
	room->setFlagState(0, ROB_FLAG_WAR_FLAG_INVALID_STATE);
	room->setFlagState(1, ROB_FLAG_WAR_FLAG_INVALID_STATE);
	int winIndex = 0;
	if (awayGroup == -1)
	{
		//没有逃跑
		winIndex = room->judgeWin();
	} else {
		winIndex = 1 - awayGroup;
		room->setWinIndex(1 - awayGroup);
	}
	
	addGuildWarScoreByName(room->getGuildName(winIndex), room->getTotalScore(winIndex));
	giveAward(room, winIndex);
	room->setRoomState(ROB_FLAG_WAR_ROOM_OVER_STATE);
	// updateRoomJoinList(room);
	startRoomTimer(room);
}


//密码保护定时器（3分钟定时）的到期处理
static void lock_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	RobFlagWarLogic *control = (RobFlagWarLogic*)think->target;
	char *roomId = think->targetId;
	RobFlagWar* room = control->roomId_2_room(roomId);
	if (room != NULL)
	{
		room->setRoomState(ROB_FLAG_WAR_ROOM_OCCUPY_STATE);
		room->setPassword(NULL);
	}
}

//准备开始的定时器（3分钟定时）到期处理
static void prepare_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	RobFlagWarLogic *control = (RobFlagWarLogic*)think->target;
	char *roomId = think->targetId;
	RobFlagWar* room = control->roomId_2_room(roomId);
	if (room != NULL)
	{
		room->setRoomState(ROB_FLAG_WAR_ROOM_READY_STATE);
		control->startRoomTimer(room);
	}
}

//已经就绪的房间5秒钟后开始帮战
static void ready_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	RobFlagWarLogic *control = (RobFlagWarLogic*)think->target;
	char *roomId = think->targetId;
	RobFlagWar* room = control->roomId_2_room(roomId);
	if (room == NULL)
	{
		return;
	}
	room->setRoomState(ROB_FLAG_WAR_ROOM_START_STATE);
	cout<<"I tell them to brush when ready Timer CallBack"<<endl;
	room->brushFlag(0);
	room->brushFlag(1);
	control->startRoomTimer(room);
}

//开战10分钟后战斗结束
static void start_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	RobFlagWarLogic *control = (RobFlagWarLogic*)think->target;
	char *roomId = think->targetId;
	RobFlagWar* room = control->roomId_2_room(roomId);
	if (room == NULL)
	{
		return;
	}
	control->gameOver(room);
}

//重置定时器（3分钟定时）到期处理
static void reset_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	RobFlagWarLogic *control = (RobFlagWarLogic*)think->target;
	char *roomId = think->targetId;
	RobFlagWar* room = control->roomId_2_room(roomId);
	if (room == NULL)
	{
		return;
	}
	
	control->resetRoom(room);
}


void RobFlagWarLogic::startRoomTimer(RobFlagWar *room)
{
	ev_timer *timer = room->getTimer();
	int state = room->getRoomState();
	char *roomId = room->getRoomId();
	char msg[128] = {0};
	switch (state)
	{
	case 2:
		ext_ev_timer_init(timer, lock_timer_cb, robFlagWarCtl.lockTime, 0, this, roomId);
		
		sprintf(msg, "34,8,%d,%d", state, robFlagWarCtl.lockTime);
		ev_timer_start(loops, timer);
		break;
	case 3: ext_ev_timer_init(timer, prepare_timer_cb, robFlagWarCtl.prepareTime, 0, this, roomId);
		sprintf(msg, "34,8,%d,%d", state, robFlagWarCtl.prepareTime);
		ev_timer_start(loops, timer);
		break;
	case 4: ext_ev_timer_init(timer, ready_timer_cb, robFlagWarCtl.readyTime, 0, this, roomId);
		sprintf(msg, "34,8,%d,%d", state, robFlagWarCtl.readyTime);
		ev_timer_start(loops, timer);
		break;
	case 5: ext_ev_timer_init(timer, start_timer_cb, robFlagWarCtl.pkTime, 0, this, roomId);
		sprintf(msg, "34,8,%d,%d", state, robFlagWarCtl.pkTime);
		ev_timer_start(loops, timer);
		break;
	case 6: ext_ev_timer_init(timer, reset_timer_cb, robFlagWarCtl.rewardTime, 0, this, roomId);
		sprintf(msg, "34,8,%d,%d", state, robFlagWarCtl.rewardTime);
		ev_timer_start(loops, timer);
		break;
	default:
		return;
	}

	robFlagSendRomMsg(room, msg, 2);
}

void RobFlagWarLogic::stopRoomTimer(RobFlagWar *room)
{
	ev_timer *timer = room->getTimer();
	ev_timer_stop(loops, timer);
}

int RobFlagWarLogic::getRoomTimerRemain(RobFlagWar* room)
{
	double remain = ev_timer_remaining(loops, room->getTimer());		//定时器还剩余的时间
	if (remain < 0)
	{
		remain = 0;
	}
	return remain;
}

void RobFlagWarLogic::enterMap(Map_Inform* scene, Hero *hero, int group)
{
	char mapNewId[IDL + 1] = {0};
	//切地图的通信消息
	char msg[400] = {0};
	//保存切图前的点
	char* oldMapId = hero->getMapId();
	if (strlen(oldMapId) > 8)
	{
		Point beforePt(8002, 3771);
		hero->setBeforePiexPt(beforePt);
		char mainCityMap[32] = {"map_001"};
		hero->setMainSrc(mainCityMap);	//设置跳转前的地图,便于返回；
	} else {
		hero->setBeforePiexPt(hero->getLocation());
		hero->setMainSrc(oldMapId);	//设置跳转前的地图,便于返回；
	}
	//切入地图诞生点
	Point targetPt = scene->getCampWarPt(group);
	
	hero->quit_scene();
	hero->setMap(scene);
	char *nowMapId = scene->getMapId();
	
	char* pChar = strrchr(nowMapId, '_');
	int size = pChar - nowMapId;
	if (size >= 14)
	{
		size = 14;
	}
	strncpy(mapNewId, nowMapId, size);

	sprintf(msg, "2,%d,1,%s,%d,%d", CHANGE_SCENE, mapNewId, targetPt._x, targetPt._y);
	send_msg(hero->getFd(),msg);  
	
	hero->setLocation(targetPt);
	hero->setWalkingFlg(false);	

}

void RobFlagWarLogic::exitMap(Hero* hero)
{
	char* mainSrcId;   
	Map_Src *mainSrcMap;
	
	mainSrcId = hero->getMainSrc();	
	map<string, Map_Src*>::iterator mainSrc_it;
	mainSrc_it = mapId_connect_map.find(mainSrcId);
	if(mainSrc_it == mapId_connect_map.end())
	{
		//没有原来的地图
		cout<<"when hero out rob flag war map can't find his srcMap!"<<endl;
		return;
	}
	
	mainSrcMap = mainSrc_it->second;
	/*退出房间地图*/
	quit_scene(hero, hero->getMap());
	/*进入原来地图*/
	enter_scenes(hero, mainSrcMap, 3); 
}


void RobFlagWarLogic::informHostPrepare(RobFlagWar* room, int group)
{
	if (room->getJoinNum(group) >= robFlagWarCtl.quickStartNeedHeroNum)
	{
		if (!room->getIsPrepare(group))
		{
			char *hostId = room->getHostId(group);
			Hero *host = heroid_to_hero(hostId);
			if (host != NULL)
			{
				char informMsg[64] = {0};
				sprintf(informMsg, "34,6");
				send_msg(host->getFd(), informMsg);
			}
		}
	}
}

void RobFlagWarLogic::updateRoomJoinList(RobFlagWar* room)
{
	int state = room->getRoomState();
	int remain = getRoomTimerRemain(room);
	char groupMsg[2][4096] = {0};
	
	room->viewOneGroupMsg(0, groupMsg[0]);
	room->viewOneGroupMsg(1, groupMsg[1]);
	
	
	char msg[8192] = {0};
	sprintf(msg, "34,2,%d,%d,%s,%s", state, remain, groupMsg[0], groupMsg[1]);
	robFlagSendRomMsg(room, msg, 0);
	
	memset(msg, 0, sizeof msg);
	sprintf(msg, "34,2,%d,%d,%s,%s", state, remain, groupMsg[1], groupMsg[0]);
	robFlagSendRomMsg(room, msg, 1);
}


int RobFlagWarLogic::callJoin(Hero* hero)
{
	
	if (!hero->isInGuildWarRoom())
	{
		//召唤帮众失败：您当前不在夺旗战房间中。
		return 1;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		//系统错误（错误码：100635），请联系客服。
		return 2;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		//系统错误（错误码：100636），请联系客服。
		return 3;
	}
	
	char *hostId = room->getHostId(group);
	if (strcmp(hostId, hero->getIdentity()))
	{
		//召唤帮众失败：您不是当前房间房主！
		return 4;
	}
	
	Guild *guild = getGuildWithName(hero->getGuildName());
	if (guild == NULL)
	{
		//系统错误（错误码：100638），请联系客服。
		return 5;
	}
	
	int roomState = room->getRoomState();
	if (roomState < ROB_FLAG_WAR_ROOM_IDLE_STATE || roomState > ROB_FLAG_WAR_ROOM_READY_STATE)
	{
		//召唤帮众失败：夺旗战房间当前阶段不能进行召唤！
		return 6;
	}
	
	char msg[128] = {0};
	sprintf(msg, "34,5,1");
	set<string> membsList = guild->getMembsList();
	set<string>::iterator it = membsList.begin();
	for(it; it != membsList.end(); it++)
	{
		Hero *pHero = heroid_to_hero(*it);
		if (pHero != NULL && !pHero->isInGuildWarRoom())
		{
			cout<<"Have send one call JoinMsg"<<endl;
			cout<<"Have send one call JoinMsg"<<endl;
			cout<<"Have send one call JoinMsg"<<endl;
			send_msg(pHero->getFd(), msg);
		}
	}
	
	return 0;
}

void RobFlagWarLogic::robFlagSendRomMsg(RobFlagWar* room, char *msg, int group)
{
	map<string, RobFlagWarHeroData_T*> *joinMemList = NULL;
	map<string, RobFlagWarHeroData_T*>::iterator it;
	
	if (group == 0 || group == 1)
	{
		joinMemList = room->getJoinList(group);
		for (it = joinMemList->begin(); it != joinMemList->end(); it++)
		{
			Hero *hero = heroid_to_hero(it->first);
			if (hero != NULL)
			{
				send_msg(hero->getFd(), msg);
			}
		}
	} else {
		for (int groupIndex = 0; groupIndex < 2; groupIndex++)
		{
			joinMemList = room->getJoinList(groupIndex);
			for (it = joinMemList->begin(); it != joinMemList->end(); it++)
			{
				Hero *hero = heroid_to_hero(it->first);
				if (hero != NULL)
				{
					send_msg(hero->getFd(), msg);
				}
			}
		}
	}
	
}


void RobFlagWarLogic::sendOutRobWarMsg(Hero* hero)
{
	char msg[128] = {0};
	sprintf(msg, "34,3,1");
	send_msg(hero->getFd(), msg);
}

void RobFlagWarLogic::giveAward(RobFlagWar* room, int winIndex)
{
	char winMsg[1024] = {0};
	char loseMsg[1024] = {0};
	sprintf(winMsg, "34,13,1,%d,%d,%d", robFlagWarCtl.winGuildReward.money, robFlagWarCtl.winGuildReward.prestige, robFlagWarCtl.winGuildReward.glory);
	sprintf(loseMsg, "34,13,0,%d,%d,%d", robFlagWarCtl.loseGuildReward.money, robFlagWarCtl.loseGuildReward.prestige, robFlagWarCtl.loseGuildReward.glory);
	map<string, RobFlagWarHeroData_T*>::iterator it;
	map<string, RobFlagWarHeroData_T*> *joinList = room->getJoinList(winIndex);
	for (it = joinList->begin(); it != joinList->end(); it++)
	{
		Hero *hero = heroid_to_hero(it->first);
		if (hero != NULL)
		{
			increaseBoundGameMoney(hero, robFlagWarCtl.winGuildReward.money);
			hero->addPrestigeValue(robFlagWarCtl.winGuildReward.prestige);
			Guild* guild = hero->getGuild();
			if (guild != NULL)
			{
				// guild->addGloryOfHero(hero->getIdentity(), robFlagWarCtl.winGuildReward.glory);
				addMyGuildGlory(hero->getGuildName(), hero->getIdentity(), robFlagWarCtl.winGuildReward.glory);
			}
			
			hero->addTitle("T037");
			send_msg(hero->getFd(), winMsg);
		}
	}

	joinList = room->getJoinList(1 - winIndex);
	for (it = joinList->begin(); it != joinList->end(); it++)
	{
		Hero *hero = heroid_to_hero(it->first);
		if (hero != NULL)
		{
			increaseBoundGameMoney(hero, robFlagWarCtl.loseGuildReward.money);
			hero->addPrestigeValue(robFlagWarCtl.loseGuildReward.prestige);
			Guild* guild = hero->getGuild();
			if (guild != NULL)
			{
				// guild->addGloryOfHero(hero->getIdentity(), robFlagWarCtl.loseGuildReward.glory);
				addMyGuildGlory(hero->getGuildName(), hero->getIdentity(), robFlagWarCtl.loseGuildReward.glory);
			}
			
			send_msg(hero->getFd(), loseMsg);
		}
	}

}

void RobFlagWarLogic::chgHost(RobFlagWar* room, int group)
{
	map<string, RobFlagWarHeroData_T*>::iterator it;
	map<string, RobFlagWarHeroData_T*> *joinList = room->getJoinList(group);
	for (it = joinList->begin(); it != joinList->end(); it++)
	{
		Hero *hero = heroid_to_hero(it->first);
		if (hero != NULL)
		{
			room->setHostId(group, hero->getIdentity());
			char chgHostMsg[64] = {0};
			sprintf(chgHostMsg, "34,7");
			send_msg(hero->getFd(), chgHostMsg);
			break;
		} else {
			continue;
		}
	}
}

int RobFlagWarLogic::revival(Hero* hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		return 2;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		return 3;
	}

	Map_Inform* scene = room->getScene();
	Point revivalPt = scene->getCampWarPt(group);
	int revival_life=hero->getLifeUpperVal();
	int revival_magic=hero->getMagicUpperVal();
	hero->setLifeVal(revival_life);
	hero->setMagicVal(revival_magic);
	char mapNewId[IDL + 1] = {0};
	char *nowMapId = scene->getMapId();

	char* pChar = strrchr(nowMapId, '_');
	int size = pChar - nowMapId;
	if (size >= 14)
	{
		size = 14;
	}
	strncpy(mapNewId, nowMapId, size);

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

bool RobFlagWarLogic::IspickOk(Hero *hero, int brandType)
{
	int ret = pickFlagCheck(hero, brandType);
	if (ret != 0)
	{
		char msg[1024] = {0};
		sprintf(msg, "34,7,%d", ret);
		send_msg(hero->getFd(), msg);
		return false;
	} else {
		return true;
	}
}

int RobFlagWarLogic::pickFlagCheck(Hero *hero, int brandType)
{
	if (brandType != 0 && brandType != 1)
	{
		return 1;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		return 2;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		return 3;
	}
	
	if (group == brandType)
	{
		return 4;
	}
	
	int flagState = room->getFlagState(brandType);
	if (flagState == ROB_FLAG_WAR_FLAG_INVALID_STATE)
	{
		return 5;
	} else if (flagState == ROB_FLAG_WAR_FLAG_PICKING_STATE)
	{
		return 6;
	} else if (flagState == ROB_FLAG_WAR_FLAG_BRING_STATE)
	{
		return 7;
	} else {
		room->setFlagState(brandType, ROB_FLAG_WAR_FLAG_PICKING_STATE, hero->getIdentity());
		cout<<"roomState is "<<room->getRoomState()<<" and flagOwner is "<<room->getFlagOwner(brandType)<<endl;
		cout<<"roomState is "<<room->getRoomState()<<" and flagOwner is "<<room->getFlagOwner(brandType)<<endl;
		char msg[1024] = {0};
		sprintf(msg, "34,9,1,%d,%s", brandType, hero->getIdentity());
		robFlagSendRomMsg(room, msg, 2);
		return 0;
	}
}


int RobFlagWarLogic::stopPicking(Hero* hero)
{
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		return 1;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		return 2;
	}
	
	int flagGroup = 1 - group;
	int flagState = room->getFlagState(flagGroup);
	if (flagState != ROB_FLAG_WAR_FLAG_PICKING_STATE)
	{
		return 3;
	}
	
	char* flagOwnerId = room->getFlagOwner(flagGroup);
	if (strcmp(flagOwnerId, hero->getIdentity()))
	{
		return 4;
	}
	
	room->setFlagState(flagGroup, ROB_FLAG_WAR_FLAG_IDLE_STATE, NULL);
	
	char msg[1024] = {0};
	sprintf(msg, "34,9,0,%d,%s", flagGroup, hero->getIdentity());
	robFlagSendRomMsg(room, msg, 2);
	return 0;
	
}

int RobFlagWarLogic::finishPick(Hero *hero, int brandType)
{
	if (brandType != 0 && brandType != 1)
	{
		return 1;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		return 2;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		return 3;
	}
	
	if (group == brandType)
	{
		return 4;
	}
	
	int flagState = room->getFlagState(brandType);
	if (flagState != ROB_FLAG_WAR_FLAG_PICKING_STATE)
	{
		return 5;
	}
	
	if (strcmp(room->getFlagOwner(brandType), hero->getIdentity()))
	{
		return 6;
	}
	
	room->setFlagState(brandType, ROB_FLAG_WAR_FLAG_BRING_STATE, hero->getIdentity());
	char msg[1024] = {0};
	char flagBuffId[10] = {0};
	// if (brandType == 0)
	// {
		// strncpy(flagBuffId, "W005", sizeof flagBuffId);
	// } else {
		// strncpy(flagBuffId, "W006", sizeof flagBuffId);
	// }
	
	// sprintf(msg, "26,3,0,%s,%s,%d", flagBuffId, hero->getIdentity(), 100);
	sprintf(msg, "34,10,1,%d,%s", brandType, hero->getIdentity());
	robFlagSendRomMsg(room, msg, 2);
	return 0;
	
}

	
int RobFlagWarLogic::stopBring(Hero* hero)
{
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		return 1;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		return 2;
	}
	
	int flagGroup = 1 - group;
	int flagState = room->getFlagState(flagGroup);
	if (flagState != ROB_FLAG_WAR_FLAG_BRING_STATE)
	{
		return 3;
	}
	
	char* flagOwnerId = room->getFlagOwner(flagGroup);
	if (strcmp(flagOwnerId, hero->getIdentity()))
	{
		return 4;
	}
	
	cout<<"I tell them to brush when stopBring and flag group is "<<flagGroup<<endl;
	room->brushFlag(flagGroup);
	room->setFlagState(flagGroup, ROB_FLAG_WAR_FLAG_IDLE_STATE, NULL);
	
	char flagBuffId[10] = {0};
	// if (flagGroup == 0)
	// {
		// strncpy(flagBuffId, "W005", sizeof flagBuffId);
	// } else {
		// strncpy(flagBuffId, "W006", sizeof flagBuffId);
	// }
	
	char msg[1024] = {0};
	sprintf(msg, "34,10,0,%d,%s", flagGroup, hero->getIdentity());
	// sprintf(msg, "26,3,1,%s,%s,%d", flagBuffId, hero->getIdentity(), 100);
	robFlagSendRomMsg(room, msg, 2);
	return 0;
	
}

	
bool RobFlagWarLogic::scorePlaceCheck(Hero *hero, int group)
{
	char *heroMapId = hero->getMapId();
	char tempMapId[32] = {0};
	strncpy(tempMapId, heroMapId, 14);
	
	cout<<"tempMapId is "<<tempMapId<<endl;
	Point heroPt = hero->getLocation();
	cout<<"heroLocation is ("<<heroPt._x<<", "<<heroPt._y<<")"<<endl;
	cout<<"scorePlace[0].map is "<<robFlagWarCtl.scorePlace[0].mapId<<endl;
	cout<<"checkPt is ("<<robFlagWarCtl.scorePlace[0].pixelPt._x<<", "<<robFlagWarCtl.scorePlace[0].pixelPt._y<<")"<<endl;
	
	cout<<"scorePlace[1].map is "<<robFlagWarCtl.scorePlace[1].mapId<<endl;
	cout<<"checkPt is ("<<robFlagWarCtl.scorePlace[1].pixelPt._x<<", "<<robFlagWarCtl.scorePlace[1].pixelPt._y<<")"<<endl;
	
	cout<<"group is "<<group<<endl;
	cout<<"distance 1 is "<<robFlagWarCtl.scorePlace[0].distance(tempMapId, hero->getLocation())<<endl;
	cout<<"distance 2 is "<<robFlagWarCtl.scorePlace[1].distance(tempMapId, hero->getLocation())<<endl;
	if (group == 2)
	{
		if (robFlagWarCtl.scorePlace[0].distance(tempMapId, hero->getLocation()) <= robFlagWarCtl.scoreRadius
			|| robFlagWarCtl.scorePlace[1].distance(tempMapId, hero->getLocation()) <= robFlagWarCtl.scoreRadius)
		{
			cout<<"group == 2 return is false"<<endl;
			return true;
		} else {
			cout<<"group == 2 return is true"<<endl;
			return false;
		}
	} else {
		if (robFlagWarCtl.scorePlace[group].distance(tempMapId, hero->getLocation()) <= robFlagWarCtl.scoreRadius)
		{
			cout<<"group = "<<group<<" return is true"<<endl;
			return true;
		} else {
			cout<<"group = "<<group<<" return is false and distance is "<<robFlagWarCtl.scorePlace[group].distance(hero->getMapId(), hero->getLocation())<<endl;
			return false;
		}
	}
}

int RobFlagWarLogic::bringFlagBack(Hero *hero)
{
	cout<<"##############################Have Come into bringFlagBack"<<endl;
	cout<<"##############################Have Come into bringFlagBack"<<endl;
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		cout<<"111111111111111111111111111111111"<<endl;
		return 1;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		cout<<"2222222222222222222222222222222"<<endl;
		return 2;
	}
	
	if (!scorePlaceCheck(hero, group))
	{
		cout<<"33333333333333333333333333333333"<<endl;
		return 3;
	}
	
	int flagGroup = 1 - group;
	int flagState = room->getFlagState(flagGroup);
	if (flagState != ROB_FLAG_WAR_FLAG_BRING_STATE)
	{
		cout<<"444444444444444444444444444444444444"<<endl;
		return 4;
	}
	
	char* flagOwnerId = room->getFlagOwner(flagGroup);
	if (strcmp(flagOwnerId, hero->getIdentity()))
	{
		cout<<"5555555555555555555555555555555555"<<endl;
		return 5;
	}
	
	cout<<"OOKKKKKOOOOOOOOOOKKKKKKKKKKKKOKKKKKKKKKKKOKo"<<endl;
	// char bringMsg[1024] = {0};
	// sprintf(bringMsg, "34,11,0,%d,%s", flagGroup, hero->getIdentity());
	room->addScore(group);
	// robFlagSendRomMsg(room, bringMsg, 2);
	
	char disMsg[1024] = {0};
	// char flagBuffId[10] = {0};
	// if (flagGroup == 0)
	// {
		// strncpy(flagBuffId, "W005", sizeof flagBuffId);
	// } else {
		// strncpy(flagBuffId, "W006", sizeof flagBuffId);
	// }
	
	// sprintf(disMsg, "26,3,1,%s,%s,%d", flagBuffId, hero->getIdentity(), 100);
	sprintf(disMsg, "34,10,0,%d,%s", flagGroup, hero->getIdentity());
	robFlagSendRomMsg(room, disMsg, 2);
	
	cout<<"I tell them to brush when bringFlagBack and flag group is "<<flagGroup<<endl;
	room->brushFlag(flagGroup);
	room->setFlagState(flagGroup, ROB_FLAG_WAR_FLAG_IDLE_STATE, NULL);
	
	updateRoomJoinList(room);
	
	if (room->getTotalScore(group) >= 100)
	{
		gameOver(room);
	}
	
	return 0;
}
int RobFlagWarLogic::prepare(Hero* hero)
{
	char* roomId = hero->getGuildWarRoomId();
	RobFlagWar* room = roomId_2_room(roomId);
	if (room == NULL)
	{
		//夺旗战准备失败：您当前不在夺旗战房间中。
		return 1;
	}
	
	int group = room->groupJudge(hero->getGuildName());
	if (group == -1)
	{
		//夺旗战准备失败：您还未加入帮派。
		return 2;
	}
	
	if (strcmp(room->getHostId(group), hero->getIdentity()))
	{
		//夺旗战准备失败：你不是当前房主。
		return 3;
	}
	
	if (room->getJoinNum(group) < robFlagWarCtl.quickStartNeedHeroNum)
	{
		//夺旗战准备失败：您帮派人数没达到准备需要人数。
		return 4;
	}
	
	int roomState = room->getRoomState();
	if (roomState <= 0 || roomState > ROB_FLAG_WAR_ROOM_PREPARE_STATE)
	{
		//夺旗战准备失败：房间当前阶段准备无效。
		return 5;
	}
	
	if (room->getIsPrepare(group))
	{
		//夺旗战准备失败：您方已经准备过。
		return 6;
	}
	
	room->setIsPrepare(group, true);
	updateRoomJoinList(room);
	if (room->getIsPrepare(1- group))
	{
		stopRoomTimer(room);
		room->setRoomState(ROB_FLAG_WAR_ROOM_READY_STATE);
		startRoomTimer(room);
	}
	
	return 0;
	
}

//设置是否在夺旗战时间
void RobFlagWarLogic::setIsInRobFlagWarTime(bool start)
{
	isInRobFlagWarTime = start;
}