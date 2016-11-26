/****************************************************************
 * Filename: rob_flag_war.h
 * 
 * Description: 帮派夺旗战
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/

#include"rob_flag_war.h"


//房间初始化
RobFlagWar::RobFlagWar(int num, Map_Inform *mapRoom)
{
	sprintf(roomId, "GWR_%04d", num);
	scene = mapRoom;
	initRoomData();
}

void RobFlagWar::reset()
{
	cout<<"I have called RobFlagWar::reset"<<endl;
	initRoomData();
}

void RobFlagWar::initRoomData()
{
	roomState = 0;
	winIndex = -1;
	memset(password, 0, sizeof password);
	groupData[0].init();
	groupData[1].init();
	
	// cout<<"I have called the initTakeGoods"<<endl;
	scene->initMap();
}

int RobFlagWar::addOneMem(int group, char *heroId, char *nickName, char *party, int level)
{
	int temp = groupData[group].firstFreeIndex;
	if (temp == GUILD_END_FLAG)
	{
		cout<<"before -1 groupData[group].firstFreeIndex is "<<temp<<"and group is "<<group<<endl;
		return -1;
	}
	
	groupData[group].firstFreeIndex = groupData[group].warCount[temp].nextFreeIndex;
	
	cout<<"not -1 groupData[group].firstFreeIndex is "<<temp<<"and now is "<<groupData[group].firstFreeIndex<<endl;
	strncpy(groupData[group].warCount[temp].heroId, heroId, sizeof (groupData[group].warCount[temp].heroId));
	strncpy(groupData[group].warCount[temp].nickName, nickName, sizeof (groupData[group].warCount[temp].nickName));
	strncpy(groupData[group].warCount[temp].party, party, sizeof (groupData[group].warCount[temp].party));
	groupData[group].warCount[temp].level = level;
	groupData[group].warCount[temp].nextFreeIndex = GUILD_USED_FLAG;
	RobFlagWarHeroData_T *p = &groupData[group].warCount[temp];
	groupData[group].heroId_2_countInfo.insert(pair<string, RobFlagWarHeroData_T*>(heroId, p));
	groupData[group].joinNum += 1;
	return 0;
}

int RobFlagWar::delOneMem(int group, char *heroId)
{
	map<string, RobFlagWarHeroData_T*>::iterator it_cnt;
	RobFlagWarHeroData_T *p = NULL;
	it_cnt = groupData[group].heroId_2_countInfo.find(heroId);
	if (it_cnt == groupData[group].heroId_2_countInfo.end())
	{
		return -1;
	}
	
	p = it_cnt->second;
	int index = p->index;
	memset(groupData[group].warCount[index].heroId, 0, sizeof groupData[group].warCount[index].heroId);
	memset(groupData[group].warCount[index].nickName, 0, sizeof groupData[group].warCount[index].nickName);
	memset(groupData[group].warCount[index].party, 0, sizeof groupData[group].warCount[index].party);
	groupData[group].warCount[index].level = 0;
	groupData[group].warCount[index].nextFreeIndex = groupData[group].firstFreeIndex;
	groupData[group].firstFreeIndex = index;
	groupData[group].heroId_2_countInfo.erase(heroId);
	groupData[group].joinNum -= 1;
	return 0;
}

char* RobFlagWar::getRoomId()
{
	return roomId;
}

Map_Inform* RobFlagWar::getScene()
{
	return scene;
}

int RobFlagWar::getRoomState()
{
	return roomState;
}

int RobFlagWar::getWinIndex()
{
	return winIndex;
}

char *RobFlagWar::getPassword()
{
	return password;
}

ev_timer* RobFlagWar::getTimer()
{
	return &timer;
}

char *RobFlagWar::getGuildName(int group)
{
	return groupData[group].guildName;
}

char *RobFlagWar::getHostId(int group)
{
	return groupData[group].hostId;
}

int RobFlagWar::getJoinNum(int group)
{
	return groupData[group].joinNum;
}

bool RobFlagWar::getIsPrepare(int group)
{
	return groupData[group].isPrepare;
}

int RobFlagWar::getCallFreqCtl(int group)
{
	return groupData[group].callFreqCtl;
}

int RobFlagWar::getRobTimes(int group)
{
	return groupData[group].robTimes;
}

int RobFlagWar::getRobSuccessTimes(int group)
{
	return groupData[group].robSuccessTimes;
}
	
int RobFlagWar::getTotalScore(int group)
{
	return groupData[group].totalScore;
}

int RobFlagWar::getFlagState(int group)
{
	return groupData[group].flagState;
}

char* RobFlagWar::getFlagOwner(int group)
{
	return groupData[group].flagOwnerId;
}

map<string, RobFlagWarHeroData_T*> *RobFlagWar::getJoinList(int group)
{
	return &groupData[group].heroId_2_countInfo;
}

void RobFlagWar::viewOneGroupMsg(int group, char *result)
{
	sprintf(result, "%s,%d,%d,%s,%d,%d", groupData[group].guildName, groupData[group].joinNum, groupData[group].isPrepare,
		groupData[group].hostId, groupData[group].guildRank, groupData[group].totalScore);
	
	map<string, RobFlagWarHeroData_T*>::iterator it;
	for (it = groupData[group].heroId_2_countInfo.begin(); it != groupData[group].heroId_2_countInfo.end(); it++)
	{
		RobFlagWarHeroData_T *pData = it->second;
		sprintf(result + strlen(result), ",%s,%s,%s,%d", pData->heroId, pData->nickName, pData->party, pData->level);
	}
}

void RobFlagWar::setRoomState(int state)
{
	roomState = state;
}

void RobFlagWar::setFlagState(int group, int state, char *ownerId)
{
	groupData[group].flagState = state;
	if (ownerId != NULL)
	{
		strncpy(groupData[group].flagOwnerId, ownerId, sizeof groupData[group].flagOwnerId);
	} else {
		memset(groupData[group].flagOwnerId, 0, sizeof groupData[group].flagOwnerId);
	}
}

void RobFlagWar::setIsPrepare(int group, bool prepare)
{
	groupData[group].isPrepare = prepare;
}

void RobFlagWar::setcallFreqCtl(int group)
{
	groupData[group].callFreqCtl = MY_TV_SEC;
}


void RobFlagWar::addScore(int group)
{
	groupData[group].totalScore += robFlagWarCtl.flagScore;
}

void RobFlagWar::initOneGroup( int group, int _guildRank, char *guildName, char *hostId)
{
	groupData[group].init();
	if (_guildRank != 0)
	{
		groupData[group].guildRank = _guildRank;
		strncpy(groupData[group].guildName, guildName, sizeof groupData[group].guildName);
		strncpy(groupData[group].hostId, hostId, sizeof groupData[group].hostId);
	}
}

void RobFlagWar::brushFlag(int group)
{
	cout<<"IIIIIIIII have called the scene->brushTakeSource(1, true, group);"<<endl;
	scene->brushTakeSource(1, true, group);
	groupData[group].flagState = ROB_FLAG_WAR_FLAG_IDLE_STATE;
}

void RobFlagWar::setWinIndex(int _winIndex)
{
	winIndex = _winIndex;
}

void RobFlagWar::setPassword(char *_pwd)
{
	if (_pwd == NULL)
	{
		memset(password, 0, sizeof password);
		return;
	}
	strncpy(password, _pwd, sizeof password);
}

void RobFlagWar::setHostId(int group, char *id)
{
	strncpy(groupData[group].hostId, id, sizeof groupData[group].hostId);
}
	
	
int RobFlagWar::groupJudge(char *guildName)
{
	if (!strcmp(groupData[0].guildName, guildName))
	{
		return 0;
	}
	
	else if (!strcmp(groupData[1].guildName, guildName))
	{
		return 1;
	}
	
	else
	{
		return -1;
	}
}

int RobFlagWar::heroGroupJudge(char *heroId)
{
	if (groupData[0].heroId_2_countInfo.find(heroId) != groupData[0].heroId_2_countInfo.end())
	{
		return 0;
	}
	
	else if (groupData[1].heroId_2_countInfo.find(heroId) != groupData[1].heroId_2_countInfo.end())
	{
		return 1;
	}
	
	else
	{
		//还未加入
		return -1;
	}
}

int RobFlagWar::judgeWin()
{
	if (groupData[0].totalScore > groupData[1].totalScore)
	{
		winIndex = 0;
	} else if (groupData[0].totalScore < groupData[1].totalScore)
	{
		winIndex = 1;
	} else {
		winIndex = (groupData[1].guildRank < groupData[0].guildRank);
	}
	
	return winIndex;
}

bool RobFlagWar::isLock()
{
	return (strlen(password) > 0);
}

bool RobFlagWar::pwdCheckOk(char *pwd)
{
	return (!strncmp(password, pwd, sizeof password));
}
