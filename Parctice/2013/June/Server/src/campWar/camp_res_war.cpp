#include"camp_res_war.h"
#include "money_operator.h"
#define NORMAL_CAMP_RES_WAR_VERSION

#if defined(NORMAL_CAMP_RES_WAR_VERSION)

#define CAMP_RES_WAR_PREPARE_TIME 	30
#define CAMP_RES_WAR_BRUSH_TIME		60
#define CAMP_RES_WAR_BRUSH_TIMES	10
#define CAMP_RES_WAR_RESET_TIME		60
#define CAMP_RES_WAR_PK_TIME		600

#else

#define CAMP_RES_WAR_PREPARE_TIME 	30
#define CAMP_RES_WAR_BRUSH_TIME		10
#define CAMP_RES_WAR_BRUSH_TIMES	10
#define CAMP_RES_WAR_RESET_TIME		10
#define CAMP_RES_WAR_PK_TIME		50

#endif

extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern map<string,Map_Src*> mapId_connect_map;

set<string> joinCampResWarHeroIds;		//所有参加了阵营资源战的角色Id
map<string, CampResWarReward_T*> campResWarRewardInfo;

int campResWarLastOpenRoomIndex;		//阵营战最后一个开启的房间

static void givePaticipationAward()
{
	if (joinCampResWarHeroIds.size() == 0)
	{
		return;
	}
	
	char awardMsg[1024] = {0};
	
	sprintf(awardMsg, "32,20,0,%d,%d", campResWarCtl.joinRewardMoney, campResWarCtl.joinRewardPtg);
	
	set<string>::iterator it;
	for (it = joinCampResWarHeroIds.begin(); it != joinCampResWarHeroIds.end(); it++)
	{
		Hero *hero = heroid_to_hero(*it);
		if (hero != NULL)
		{
			// increaseBoundGameMoney(hero, campResWarCtl.joinRewardMoney);
			// hero->addPrestigeValue(campResWarCtl.joinRewardPtg);
			CampResWarReward_T* rewardInfo = new CampResWarReward_T(hero->getIdentity(), campResWarCtl.joinRewardMoney, campResWarCtl.joinRewardPtg, NULL);
			campResWarRewardInfo.insert(pair<string, CampResWarReward_T*>(*it, rewardInfo));
			send_msg(hero->getFd(), awardMsg);
		}
	}
	
	joinCampResWarHeroIds.clear();
}

//准备定时器到期处理
static void prepare_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	CampResWar *room = (CampResWar *)think->target;
	if (room != NULL)
	{
		room->startPkTimer();
		room->startBrushTimer();
		room->start();
	}
}

//刷资源定时器到期处理
static void brush_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	CampResWar *room = (CampResWar *)think->target;
	if (room != NULL)
	{
		
		
		int ret = room->brush();
		if (ret == 0)
		{
			cout<<"the room 's brush timer have been stopped"<<endl;
			return;
		}
		
		room->startBrushTimer();
	}
}

//准备定时器到期处理
static void pk_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	CampResWar *room = (CampResWar *)think->target;
	if (room != NULL)
	{
		room->stopBrushTimer();
		room->over();
		room->award();
		cout<<"have called the room->startResetTimer()"<<endl;
		room->startResetTimer();
	}
}


//准备定时器到期处理
static void reset_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	CampResWar *room = (CampResWar *)think->target;
	if (room != NULL)
	{
		cout<<"before clear()"<<endl;
		room->clear();
		cout<<"after clear() and before reset()"<<endl;
		if (room->getRoomIndex() == campResWarLastOpenRoomIndex)
		{
			givePaticipationAward();
		}
		room->reset();
		cout<<"after reset()"<<endl;
	}
}

CampResWar::CampResWar()
{
	totalJoinNum = 0;
	remainResCnt = 0;
	for (int i = 0; i < 3; i++)
	{
		heroId_2_resNum[i].clear();
		perCampJoinNum[i] = 0;
		perCampResCnt[i] = 0;
	}
	scene = NULL;
	memset(mapId, 0, sizeof (mapId));
	index = 0;
	times = 0;
	
	timeState = CAMP_RES_WAR_IDLE_STATE;
}

CampResWar::~CampResWar()
{
	totalJoinNum = 0;
	remainResCnt = 0;
	for (int i = 0; i < 3; i++)
	{
		heroId_2_resNum[i].clear();
		perCampJoinNum[i] = 0;
		perCampResCnt[i] = 0;
	}
	times = 0;
	index = 0;
}

//房间开启
void CampResWar::open()
{
	roomState = 0;
	reset();
	timeState = CAMP_RES_WAR_PREPARE_STATE;
	startPrepareTimer();
}

//判断房间是否开启
bool CampResWar::isOpen()
{
	return (timeState > CAMP_RES_WAR_IDLE_STATE);
}
	
//获取房间号
int CampResWar::getRoomIndex()
{
	return index;
}

//获取房间状态
int CampResWar::getRoomState()
{
	return roomState;
}

//获取房间时间状态
int CampResWar::getTimeState()
{
	return timeState;
}

void CampResWar::create(int _index, Map_Src* map)
{
	index = _index;
	scene = map;
	strncpy(mapId, scene->getIdentity(), sizeof(mapId));
}

void CampResWar::reset()
{
	timeState = CAMP_RES_WAR_IDLE_STATE;
	totalJoinNum = 0;
	remainResCnt = 0;
	for (int i = 0; i < 3; i++)
	{
		heroId_2_resNum[i].clear();
		perCampJoinNum[i] = 0;
		perCampResCnt[i] = 0;
	}
	if (scene != NULL)
	{
		scene->initTakeGoods();
	}
	times = 0;
}

//获取房间人数
int CampResWar::getJoinNum(int index)
{
	if (index >= 0 && index < 3)
	{
		return perCampJoinNum[index];
	}
	else if(index == 3)
	{
		return totalJoinNum;
	}
	else {
		return 0;
	}
	
}

int CampResWar::join(Hero *hero, int &openNext)
{
	//如果玩家不在阵营战NPC附近
	if (campResWarCtl.from.distance(hero->getMapId(), hero->getLocation()) > 800)
	{
		return -1;
	}
	
	if (totalJoinNum >= campResWarCtl.roomLimitHeros)
	{
		return -2;
	}
	
	int camp = hero->getCamp();
	if (perCampJoinNum[camp] >= campResWarCtl.perCampLimitHeros)
	{
		return -3;
	}
	
	if (timeState != CAMP_RES_WAR_PREPARE_STATE && timeState != CAMP_RES_WAR_START_STATE)
	{
		return -4;
	}
	totalJoinNum += 1;
	perCampJoinNum[camp] += 1;
	//达到触发开启下一个房间的条件
	if (perCampJoinNum[camp] == campResWarCtl.perCampLimitHeros)
	{
		roomState |= 1 << (camp);
		openNext = 1;
	} else {
		openNext = 0;
	}
	
	heroId_2_resNum[camp].insert(pair<string, int>(hero->getIdentity(), 0));
	joinCampResWarHeroIds.insert(hero->getIdentity());
	return 0;
}

int CampResWar::exit(Hero* hero)
{
	cout<<"in CampResWar::exit(Hero* hero)"<<endl;
	int camp = hero->getCamp();
	map<string, int>::iterator it = heroId_2_resNum[camp].find(hero->getIdentity());
	if (it == heroId_2_resNum[camp].end())
	{
		cout<<"CampResWar::exit111111111111111111111111111111111111111"<<endl;
		return -1;
	}
	
	string mainSrcId = mapTypeInfo.mainCityMapId;
	map<string,Map_Src*>::iterator mainSrc_it;
	mainSrc_it = mapId_connect_map.find(mainSrcId);
	
	if(mainSrc_it == mapId_connect_map.end())
	{
		cout<<"have not find back map from camp_res_war map to "<<mainSrcId<<endl;
		return -2;
	}
	
	Map_Inform *mapDest=mainSrc_it->second;
	Point targetPt=mapDest->getEntPt();	
	
	hero->quit_scene();
	hero->setMap(mainSrc_it->second);
	hero->setMapId(mapDest->getMapId());
	hero->setLocation(targetPt);
	char changeMsg[1024] = {0};
	sprintf(changeMsg,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS, mapDest->getMapId(),targetPt._x,targetPt._y,\
													mapDest->getWarType(),mapDest->getChangePkType(),mapDest->getMapType());	
													
	send_msg(hero->getFd(), changeMsg); 
	cout<<"CampResWar::exit2222222222222222222222222222222222222222222"<<endl;
	if (perCampJoinNum[camp] == campResWarCtl.perCampLimitHeros)
	{
		roomState &= ~(1 << camp);
	}
	
	heroId_2_resNum[camp].erase(hero->getIdentity());
	totalJoinNum -= 1;
	perCampJoinNum[camp] -= 1;
	perCampResCnt[camp] -= it->second;
	hero->setCampWarData(-1, -1, false, true);
	return 0;
}

//更新房间信息
void CampResWar::update_room_infor()
{
	char publicMsg[512] = {0};
	
	int remain = getCtlTimerRemain();
	int brushRemain = getBrushTimerRemain();
	if (timeState == CAMP_RES_WAR_PREPARE_STATE)
	{
		remain += campResWarCtl.pkTime;
		brushRemain = getCtlTimerRemain();
	}
	
	sprintf(publicMsg, "32,3,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", remain, brushRemain, remainResCnt * 100, perCampJoinNum[0], perCampResCnt[0], perCampJoinNum[1], perCampResCnt[1], perCampJoinNum[2], perCampResCnt[2], timeState);
	send_room_msg(publicMsg);

}

//房间内发送消息
void CampResWar::send_room_msg(char *msg, int flag, int tag)
{
	map<string, int>::iterator it;
	if (flag >= 0 && flag < 3)
	{
		for (it = heroId_2_resNum[flag].begin(); it != heroId_2_resNum[flag].end(); it++)
		{
			Hero* hero = heroid_to_hero(it->first);
			if (hero != NULL)
			{
				if (tag == 1)
				{
					char tempMsg[1024] = {0};
					sprintf(tempMsg, "%s,%d", msg, it->second);
					send_msg(hero->getFd(), tempMsg);
				}
				else {
					send_msg(hero->getFd(), msg);
				}
			}
		}
	}
	else
	{
		for (int campIndex = 0; campIndex < 3; campIndex < campIndex++)
		{
			for (it = heroId_2_resNum[campIndex].begin(); it != heroId_2_resNum[campIndex].end(); it++)
			{
				Hero* hero = heroid_to_hero(it->first);
				if (hero != NULL)
				{
					if (tag == 1)
					{
						char tempMsg[1024] = {0};
						sprintf(tempMsg, "%s,%d", msg, it->second);
						send_msg(hero->getFd(), tempMsg);
					}
					else {
						send_msg(hero->getFd(), msg);
					}
				}
			}
		}
	}
}


//资源战开始
void CampResWar::start()
{
	char startMsg[1024] = {0};
	times = 1;
	timeState = CAMP_RES_WAR_START_STATE;
	sprintf(startMsg, "32,4,%d", campResWarCtl.pkTime);
	send_room_msg(startMsg);
	
	brush();
	
}

//刷出资源
int CampResWar::brush()
{
	if (timeState != CAMP_RES_WAR_START_STATE)
	{
		return 0;
	}
	
	char brushMsg[1024] = {0};
	if (totalJoinNum * campResWarCtl.brushNumPerTimes > remainResCnt)
	{
		scene->brushTakeSource((totalJoinNum  * campResWarCtl.brushNumPerTimes - remainResCnt));
		remainResCnt = totalJoinNum * campResWarCtl.brushNumPerTimes;
	}
	
	int remain = getCtlTimerRemain();
	int brushRemain = campResWarCtl.brushTime;
	if (timeState == CAMP_RES_WAR_PREPARE_STATE)
	{
		remain += campResWarCtl.pkTime;
		brushRemain = getCtlTimerRemain();
	}
	if (brushRemain > remain)
	{
		brushRemain = 0;
	}
	
	sprintf(brushMsg, "32,5,%d,%d,%d,%d,%d,%d,%d,%d,%d", remain, brushRemain, remainResCnt * 100, perCampJoinNum[0], perCampResCnt[0], perCampJoinNum[1], perCampResCnt[1], perCampJoinNum[2], perCampResCnt[2]);
	send_room_msg(brushMsg);
	
	times += 1;
	return 1;
}

//资源战结束
void CampResWar::over()
{
	char overMsg[1024] = {0};
	timeState = CAMP_RES_WAR_OVER_STATE;
	sprintf(overMsg, "32,6");
	send_room_msg(overMsg);
}

//开启准备计时
void CampResWar::startPrepareTimer()
{
	//准备30秒
	ext_ev_timer_init(&roomCtlTimer, prepare_timer_cb, campResWarCtl.prepareTime, 0, this);
    ev_timer_start(loops, &roomCtlTimer);
}

//开启战斗计时
void CampResWar::startPkTimer()
{
	//准备30秒
	ext_ev_timer_init(&roomCtlTimer, pk_timer_cb, campResWarCtl.pkTime, 0, this);
    ev_timer_start(loops, &roomCtlTimer);
}

//开启刷资源计时
void CampResWar::startBrushTimer()
{
	//60秒刷新
	if (getCtlTimerRemain() < campResWarCtl.brushTime)
	{
		return;
	}
	ext_ev_timer_init(&brushResTimer, brush_timer_cb, campResWarCtl.brushTime, 0, this);
    ev_timer_start(loops, &brushResTimer);
}

//开启房间重置计时
void CampResWar::startResetTimer()
{
	//60秒房间重置
	ext_ev_timer_init(&roomCtlTimer, reset_timer_cb, campResWarCtl.rewardTime, 0, this);
    ev_timer_start(loops, &roomCtlTimer);
}

//停止刷资源定时器
void CampResWar::stopBrushTimer()
{
	if (ev_timer_is_running(loops, &brushResTimer))
	{
		ev_timer_stop(loops, &brushResTimer);
	}
}

//资源采集
int CampResWar::collect(Hero* hero)
{
	int camp = hero->getCamp();
	map<string, int>::iterator *it = &heroId_2_resNum[camp].find(hero->getIdentity());
	if (*it == heroId_2_resNum[camp].end())
	{
		return -1;
	}
	
	if (timeState != CAMP_RES_WAR_START_STATE)
	{
		return -2;
	}

	remainResCnt -= 1;
	(*it)->second += campResWarCtl.pickScore;
	perCampResCnt[camp] += campResWarCtl.pickScore;
	
	int remain = getCtlTimerRemain();
	int brushRemain = getBrushTimerRemain();
	if (timeState == CAMP_RES_WAR_PREPARE_STATE)
	{
		remain += campResWarCtl.pkTime;
		brushRemain = getCtlTimerRemain();
	}
	
	char collectMsg[1024] = {0};
	sprintf(collectMsg, "32,7,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d", remain, brushRemain, remainResCnt * 100, perCampJoinNum[0], perCampResCnt[0], perCampJoinNum[1], perCampResCnt[1], perCampJoinNum[2], perCampResCnt[2], hero->getIdentity(), (*it)->second);
	send_room_msg(collectMsg);
	
	return 0;
}

//杀人抢资源
int CampResWar::kill(Hero* atker, Hero* atked)
{
	int campA = atker->getCamp();
	int campB = atked->getCamp();
	map<string, int>::iterator *it_A = &heroId_2_resNum[campA].find(atker->getIdentity());
	map<string, int>::iterator *it_B = &heroId_2_resNum[campB].find(atked->getIdentity());
	if (*it_A == heroId_2_resNum[campA].end() || *it_B == heroId_2_resNum[campB].end())
	{
		return -1;
	}
	
	if (times == 11)
	{
		return -2;
	}
	
	int transNum = (*it_B)->second / 2 + ((*it_B)->second % 2);
	(*it_A)->second += transNum;
	perCampResCnt[campA] += transNum;
	(*it_B)->second -= transNum;
	perCampResCnt[campB] -= transNum;
	
	char killMsg[1024] = {0};
	
	int remain = getCtlTimerRemain();
	int brushRemain = getBrushTimerRemain();
	if (timeState == CAMP_RES_WAR_PREPARE_STATE)
	{
		remain += campResWarCtl.pkTime;
		brushRemain = getCtlTimerRemain();
	}
	
	sprintf(killMsg, "32,8,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%s,%d", remain, brushRemain, remainResCnt * 100, perCampJoinNum[0], perCampResCnt[0], perCampJoinNum[1], perCampResCnt[1], perCampJoinNum[2], perCampResCnt[2], atker->getIdentity(), (*it_A)->second, atked->getIdentity(), (*it_B)->second);
	send_room_msg(killMsg);
	
	return 0;
}

//房间清场
void CampResWar::clear()
{
	cout<<"have come into campResWar's clear()"<<endl;
	map<string, int>::iterator it;
	for (int campIndex = 0; campIndex < 3; campIndex++)
	{
		for (it = heroId_2_resNum[campIndex].begin(); it != heroId_2_resNum[campIndex].end(); it++)
		{
			cout<<"have come into campResWar's clear() and there is a hero!!!!!!"<<endl;
			Hero* hero = heroid_to_hero(it->first);
			if (hero != NULL)
			{
				exit(hero);
			}
		}
		heroId_2_resNum[campIndex].clear();
		cout<<"clear heroId_2_resNum[campIndex]'s campIndex is "<<campIndex<<endl;
	}
}

//奖励
void CampResWar::award()
{
	char campResMsg[1024] = {0};
	char campRewardMsg[3][1024] = {0};
	char topThreeResMsg[2048] = {0};
	char paticipationRewardMsg[1024] = {0};
	int campRewardMoney[3] = {0, 0, 0};
	int campRewardPtg[3] = {0, 0, 0};
	// char rewardMsg[1024] = {0};
	// sprintf(rewardMsg, "32,20,1%s%s%s%s%s%s", campResMsg, topThreeResMsg, campRewardMsg[0], rankRewardMsg, resNumRewardMsg, paticipationRewardMsg);
	
	sprintf(paticipationRewardMsg, ",%d,%d", campResWarCtl.joinRewardMoney, campResWarCtl.joinRewardPtg);
	
	int maxCampResNum = perCampResCnt[0];
	for (int i = 0; i < 3; i++)
	{
		if (maxCampResNum < perCampResCnt[i])
		{
			maxCampResNum = perCampResCnt[i];
		}
	}
	
	int winCampNum = 0;
	for (int i = 0; i < 3; i++)
	{
		if (perCampResCnt[i] == maxCampResNum)
		{
			isWinnerCamp[i] = 1;
			winCampNum += 1;
			if (winCampNum == 1)
			{
				sprintf(campResMsg + strlen(campResMsg), ",%d", i);
			} else {
				sprintf(campResMsg + strlen(campResMsg), "_%d", i);
			}
			
			if (perCampResCnt[i] > campResWarCtl.winCampRewardMinScore)
			{
				campRewardMoney[i] = campResWarCtl.winCampRewardMoney;
				campRewardPtg[i] = campResWarCtl.winCampRewardPtg;
				sprintf(campRewardMsg[i], ",%d,%d", campRewardMoney[i], campRewardPtg[i]);
				
			} else {
				campRewardMoney[i] = 0;
				campRewardPtg[i] = 0;
				sprintf(campRewardMsg[i], ",0,0");
			}
			
		} else {
			isWinnerCamp[i] = 0;
			campRewardMoney[i] = 0;
			campRewardPtg[i] = 0;
			sprintf(campRewardMsg[i], ",0,0");
		}
		
	}
	sprintf(campResMsg + strlen(campResMsg), ",%d", maxCampResNum);
	
	map<string,int>::iterator it;
	for (int i = 0; i < 3; i++)
	{
		for (it = heroId_2_resNum[i].begin(); it != heroId_2_resNum[i].end(); it++)
		{
			rankAll.insert(pair<INT, string>(it->second, it->first));
		}
	}
	
	
	map<INT, string>::iterator it_rank;
	int heroRank = 0, lastScore = 0;
	for (it_rank = rankAll.begin(); it_rank != rankAll.end(); it_rank++)
	{
		if (int(it_rank->first) == 0)
		{
			break;
		}
		
		Hero* rankHero = heroid_to_hero(it_rank->second);
		char nickName[51] = {0};
		if (rankHero != NULL)
		{
			strcpy(nickName, rankHero->getNickName());
		}
		
		if (lastScore != int(it_rank->first))
		{
			heroRank += 1;
			if (heroRank > 3)
			{
				heroRank -= 1;
				break;
			}
			
			sprintf(topThreeResMsg + strlen(topThreeResMsg), ",%d,%s", int(it_rank->first), nickName);
			
			lastScore = int(it_rank->first);
		} else {
			sprintf(topThreeResMsg + strlen(topThreeResMsg), "_%s", nickName);
		}
		
	}
	
	if (heroRank == 0)
	{
		sprintf(topThreeResMsg, ",,,,,,");
	} else if (heroRank == 1) {
		sprintf(topThreeResMsg  + strlen(topThreeResMsg), ",,,,");
	} else if (heroRank == 2) {
		sprintf(topThreeResMsg  + strlen(topThreeResMsg), ",,");
	}
	
	bool rewardAllTopFlag = false;
	int rankAgain = 0;
	lastScore = 0;
	for (it_rank = rankAll.begin(); it_rank != rankAll.end(); it_rank++)
	{
		char rankRewardMsg[1024] = {0};
		char resNumRewardMsg[1024] = {0};
		char rewardMsg[2048] = {0};
		int rankRewardMoney = 0;
		int rankRewardPtg = 0;
		char rankRewardGoodsId[51] = {0};
		int resNumRewardMoney = 0;
		int resNumRewardPtg = 0;
		
		joinCampResWarHeroIds.erase(it_rank->second);	//参与奖在这边发了
		
		if (int(it_rank->first) == 0)
		{
			sprintf(rankRewardMsg, ",0,0,0,0,");
			sprintf(resNumRewardMsg, ",0,0");
		} else {
			
			// if (!rewardAllTopFlag)
			{
				if (lastScore != int(it_rank->first))
				{
					lastScore = int(it_rank->first);
					rankAgain += 1;
					if (rankAgain > 3)
					{
						rewardAllTopFlag = true;
					}
				}
			}
			
			if (rankAgain <= 3)
			{
				if(int(it_rank->first) >= campResWarCtl.rankReward[rankAgain - 1].minScore)
				{
					rankRewardMoney = campResWarCtl.rankReward[rankAgain - 1].money;
					rankRewardPtg = campResWarCtl.rankReward[rankAgain - 1].prestige;
					strncpy(rankRewardGoodsId, campResWarCtl.rankReward[rankAgain - 1].goodsId, sizeof (rankRewardGoodsId));
					sprintf(rankRewardMsg, ",%d,%d,%d,%d,%s", rankAgain, int(it_rank->first), rankRewardMoney, rankRewardPtg, rankRewardGoodsId);
				} else {
					rankRewardMoney = 0;
					rankRewardPtg = 0;
					memset(rankRewardGoodsId, 0, sizeof (rankRewardGoodsId));
					sprintf(rankRewardMsg, ",%d,%d,0,0,%s", rankAgain, int(it_rank->first), rankRewardGoodsId);
				}
			} else {
				rankRewardMoney = 0;
				rankRewardPtg = 0;
				memset(rankRewardGoodsId, 0, sizeof (rankRewardGoodsId));
				sprintf(rankRewardMsg, ",%d,%d,0,0,%s", rankAgain, int(it_rank->first), rankRewardGoodsId);
			}
			
			resNumRewardMoney = campResWarCtl.resNumRewardMoneyBase * int(it_rank->first);
			resNumRewardPtg = campResWarCtl.resNumRewardPtgBases * int(it_rank->first) / 100;
			sprintf(resNumRewardMsg, ",%d,%d", resNumRewardMoney, resNumRewardPtg);
		}
		
		Hero* hero = heroid_to_hero(it_rank->second);
		if (hero == NULL)
		{
			continue;
		}
		
		int heroCamp = hero->getCamp();
		
		// increaseBoundGameMoney(hero, campRewardMoney[heroCamp] + rankRewardMoney + resNumRewardMoney + campResWarCtl.joinRewardMoney);
		// hero->addPrestigeValue(campRewardPtg[heroCamp] + rankRewardPtg + resNumRewardPtg + campResWarCtl.joinRewardPtg);
		// if (strlen(rankRewardGoodsId) != 0)
		// {
			// saveGoodsInBag(hero, rankRewardGoodsId, 1);
		// }
		
		CampResWarReward_T* rewardInfo = new CampResWarReward_T(hero->getIdentity(),
			campRewardMoney[heroCamp] + rankRewardMoney + resNumRewardMoney + campResWarCtl.joinRewardMoney,
			campRewardPtg[heroCamp] + rankRewardPtg + resNumRewardPtg + campResWarCtl.joinRewardPtg,
			rankRewardGoodsId);
		campResWarRewardInfo.insert(pair<string, CampResWarReward_T*>(hero->getIdentity(), rewardInfo));
		
		sprintf(rewardMsg, "32,20,1%s%s%s%s%s%s", campResMsg, topThreeResMsg, rankRewardMsg, paticipationRewardMsg, resNumRewardMsg, campRewardMsg[heroCamp]);
		send_msg(hero->getFd(), rewardMsg);
	}
	
}

//复活
int CampResWar::revival(Hero* hero)
{	
	cout<<"have enter camp res war room's revival!!!"<<endl;
	int camp = hero->getCamp();
	
	Point revivalPt = scene->getCampWarPt(camp);
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


//获取房间控制定时器剩余时间
int CampResWar::getCtlTimerRemain()
{
	double remain = ev_timer_remaining(loops, &roomCtlTimer);		//定时器还剩余的时间
	if (remain < 0)
	{
		remain = 0;
	}
	return remain;
}

//获取房间控制定时器剩余时间
int CampResWar::getBrushTimerRemain()
{
	double remain = ev_timer_remaining(loops, &brushResTimer);		//定时器还剩余的时间
	if (remain < 0)
	{
		remain = 0;
	}
	return remain;
}

int CampResWar::viewResNum(Hero* hero, char* heroId)
{
	int camp = hero->getCamp();
	map<string, int>::iterator it = heroId_2_resNum[camp].find(heroId);
	if (it == heroId_2_resNum[camp].end())
	{
		return -1;
	}
	
	char viewMsg[1024] = {0};
	sprintf(viewMsg, "32,9,1,%s,%d", heroId, it->second);
	send_msg(hero->getFd(), viewMsg);
	return 0;
}
