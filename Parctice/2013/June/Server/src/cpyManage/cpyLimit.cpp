/*
	文件名：cpyLimit.cpp
	文件作用：实现类CpyLimit类的方法
	作者：chenzhen
	创建日期：2012.06.11
*/
#include"heroCpyRecord.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"cpyManager.h"
#include"hero.h"
#include"towerLayerRecord.h"
#include"team.h"
#include"teamManager.h"
#include"my_mem_group.h"

/*金陵普通副本npc传送点*/
extern Point JLGENPT;

/*开封普通副本npc传送点*/
extern Point KFGENPT;

/*开封帮派副本npc传送点*/
extern Point KFPARPT;

/*金陵帮派副本npc传送点*/
extern Point JLPARPT;

/*角色离帮派副本npc传送点多少距离才能传送*/
extern int LIMPRTRAG;

/*角色离普通副本npc传送点多少距离才能传送*/
extern int LIMGENRAG;



extern map<string, Hero*> heroId_to_pHero;
extern CpyManger *cpyManger;
extern Hero* pg_hero;
extern map<string,map<string,string> >towerMapConf;
extern MyMemGroup* mem_group;

CpyLimit::CpyLimit(char *_cpyLimitId,char *_cpyId,char *_name,int _baseGole,int _judgeTme,\
					double _jugGodRat,int _num,int _rank,size_t _costFatigue,int _room)
{
	memset(cpyLimitId,'\0',sizeof(cpyLimitId));
	memset(cpyId,'\0',sizeof(cpyId));
	memset(name,'\0',sizeof(name));
	
	strncpy(cpyLimitId,_cpyLimitId,strlen(_cpyLimitId));	
	strncpy(cpyId,_cpyId,strlen(_cpyId));
	strncpy(name,_name,strlen(_name));
	
	num = _num;
	rank = _rank;
	room = _room;	
	judgeTme = _judgeTme;
	jugGodRat = _jugGodRat;
	baseGole = _baseGole;
	totalSize = room;
	costFatigue = _costFatigue;
	memRecord = NULL;
//	initMemRecord();
}

char *CpyLimit::getCpyId(void)
{
	return cpyId;
}

int CpyLimit::getRoom(void)
{
	return room;
}

void CpyLimit::PushCpy(Cpy *newCpy)
{
	initCpyRom.push_back(newCpy);
	int size = initCpyRom.size() -1;
	asistList.push_back(size);
}

/*单人进副本检测*/
bool CpyLimit::qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,bool tolFlg,bool isParty)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	
	
	length = heroId.size();
	
	/*没有空房间*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*人数限制*/
	if(length < num) 
	{
		
		return false;
	}
		
	for(i = 0;i < length;i++)
	{

		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			return false;
		}
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		if(i == 0)
		{
			npcMapId = lastMap->getMapId();
		}
		
		if(lastMap == NULL || record == NULL || mapId == NULL || strlen(mapId) == 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_OTHER;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			return false;
		}
		
		/*你已经在队伍中且不是队长*/
		if(length == 1 && !SingleOrTeamLeader(myHero->getIdentity()))
		{			
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_TEAM;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;			
			return false;
		}
		/*此人处于摆摊状态*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
#if 0
		/*不在同一张地图*/
		if(strcmp(mapId,npcMapId) != 0 )
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
		/*此人不在主城*/
		if(strcmp(mapId,"map_001") != 0 && strcmp(mapId,"map_010") != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}	
#endif
		
		if(isParty)
		{
#if 0
			if(strcmp(mapId,"map_001") == 0)
			{
				if(sqrt(pow(fabs(piexPt._x - KFPARPT._x),2)+pow(fabs(piexPt._y - KFPARPT._y),2)) > LIMPRTRAG)
				{
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;
				}
			}
			if(strcmp(mapId,"map_010") == 0)
			{
				if(sqrt(pow(fabs(piexPt._x - JLPARPT._x),2)+pow(fabs(piexPt._y - JLPARPT._y),2)) > LIMPRTRAG)
				{
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;
				}
			}
#endif			
			myGuild = myHero->getGuild();
			if(myGuild == NULL)
			{
				/*没有加入帮派*/
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_JOIN_PARTY;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));		
				failure_reason->size += 1;
				return false;
				
			}
			else
			{
				/*帮派等级限制*/
				if(myGuild->getLevel() < rank)
				{
					/*帮派等级不够*/
					failure_reason->member[sizeFail].failure_flag = IS_PARTY_LEVE_LOW;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
					failure_reason->size += 1;
					return false;			
				}
			}
		}
		else
		{			
	
#if 0
			if(myHero->getLevel() < 40)
			{
				
				if(strcmp(mapId,"map_010") == 0 || !judRange(piexPt,KFGENPT,LIMGENRAG))
				{					
					failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
					strlen(perNikName));
					failure_reason->size += 1;
					return false;
				
				}	
			}
			else
			{
			
				if(strcmp(mapId,"map_001") == 0)
				{
					if(!judRange(piexPt,KFGENPT,LIMGENRAG))
					{
						failure_reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
						strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
						strlen(perNikName));
						failure_reason->size += 1;
						return false;
					}
				}
				else
				{						
					if(!judRange(piexPt,JLGENPT,LIMGENRAG))
					{
						failure_reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
						strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
						strlen(perNikName));
						failure_reason->size += 1;
						return false;
					}
				}
			}
#endif

#if 1				
			/*判断副本副本等级与人物等级相符否*/
			if(myHero->getLevel() < rank)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName,\
				strlen(perNikName));	
				failure_reason->size += 1;	
				return false;
			}
#endif				
			/*副本没有开启*/
			if(!record->judUperRank(cpyId))
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NO_OPEN;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
				failure_reason->size += 1;	
				return false;			
			}			
		}		
			
		cout<<"myHero->memHero->lastStrength:"<<myHero->memHero->lastStrength<<endl;
#if 1
		/*判断耐力值够否*/
		if(myHero->memHero->lastStrength < costFatigue)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_LAST_POWER;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;	
		}			
#endif		
				
		/*此人处于押镖状态*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list threeEvent:"<<endl;
			return false;
		}
		/*此人处于副本状态*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
		
		/*此人处于pk状态*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			return false;
		}
		
		/*此人处于娱乐地图状态*/
		if(isHappyMap(lastMap->getMapId()))
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_HAPPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			return false;
		}			
	}
	
	return true;
}

string CpyLimit::enable_enter_cpy(vector<string> &heroId, Failure_Reason* reason ,bool isParty)
{
	map<string,Hero*>::iterator hero_it;	
	char *nickNme,*mapId,*wagonId,*npcMapId;	
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;
	string inst_room_id;
	Guild *myGuild;
	Hero *myHero;	
	Point piexPt;
	
	length = heroId.size();
	
	/*没有空房间*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{			
			cout<<"three is not resorce to this cpy:"<<cpyId<<endl;		
			return inst_room_id;
		}
	}
		
	for(i = 0;i < length;i++)
	{
		sizeFail = reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}
		
		record = myHero->getCpyRecord();
		nickNme = myHero->getNickName();
		wagonId = myHero->memHero->wagonId;	
		lastMap = myHero->getMap();
		mapId = lastMap->getMapId();
		piexPt = myHero->getLocation();
		
		/*必须处于一张地图上*/
		if(i == 0)
		{
			npcMapId = lastMap->getMapId();
		}
		
		if(lastMap == NULL || record == NULL || mapId == NULL || strlen(mapId) == 0)
		{
			return inst_room_id;
		}
		
		/*此人处于摆摊状态*/
		if(myHero->getHeroState()==5)
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	

#if 0		
		/*不在同一张地图*/
		if(strcmp(mapId,npcMapId) != 0 )
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	
	
		/*此人不在主城*/
		if(strcmp(mapId,"map_001") != 0 && strcmp(mapId,"map_010") != 0)
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_MAIN_CITY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}	
#endif			
		if(isParty)
		{
		
#if 0
			if(strcmp(mapId,"map_001") == 0)
			{
				if(!judRange(piexPt,KFPARPT,LIMPRTRAG))
				{
					reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				}
			
			}
			else
			{
				if(!judRange(piexPt,JLPARPT,LIMPRTRAG))
				{
					reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				}
			
			}
#endif
			myGuild = myHero->getGuild();
			if(myGuild == NULL)
			{
				/*没有加入帮派*/
				reason->member[sizeFail].failure_flag = ERROR_NOT_JOIN_PARTY;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;
				return inst_room_id;
			}
			else
			{
				/*帮派等级限制*/
				if(myGuild->getLevel() < rank)
				{					
					reason->member[sizeFail].failure_flag = IS_PARTY_LEVE_LOW;			
					strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
					reason->size += 1;		//失败人数加1
					return inst_room_id;	//返回空房间号
			
				}
			}
		}		
		else
		{
#if 0
			if(myHero->getGradeNow() < 40)
			{
				
				if(strcmp(mapId,"map_010") == 0 || !judRange(piexPt,KFGENPT,LIMGENRAG))
				{					
					reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
					strncpy(reason->member[sizeFail].nickName, nickNme,\
					strlen(nickNme));
					reason->size += 1;
					return inst_room_id;
				
				}	
			}
			else
			{
				if(strcmp(mapId,"map_001") == 0)
				{
					if(!judRange(piexPt,KFGENPT,LIMGENRAG))
					{
						reason->member[sizeFail].failure_flag = ERROR_IN_KF_NPC;
						strncpy(reason->member[sizeFail].nickName, nickNme,\
						strlen(nickNme));
						reason->size += 1;
						return inst_room_id;
					}
				}
				else
				{						
					if(!judRange(piexPt,JLGENPT,LIMGENRAG))
					{
						reason->member[sizeFail].failure_flag = ERROR_IN_JL_NPC;
						strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
						reason->size += 1;
						return inst_room_id;
					}
				}
			}
#endif

#if 1			
			/*判断副本副本等级与人物等级相符否*/
			if(myHero->getLevel() < rank)
			{
				
				reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;		
				return inst_room_id;
			}
#endif			

#if 1
			/*判断副本是否已开启*/
			if(!record->judUperRank(cpyId))
			{
				
				reason->member[sizeFail].failure_flag = ERROR_NO_OPEN;
				strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
				reason->size += 1;		
				return inst_room_id;
			}			
#endif			
		}
#if 1		
		/*判断耐力值够否*/
		if(myHero->memHero->lastStrength < costFatigue)
		{
				
			reason->member[sizeFail].failure_flag = ERROR_LOWER_LAST_POWER;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));		
			reason->size += 1;		
			return inst_room_id;
		}			
#endif

		/*此人处于押镖状态*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}
			
		/*此人处于副本状态*/
		if(lastMap->getFlgCpy())
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}		
		/*此人处于pk状态*/
		if(lastMap->getWarType() !=1)
		{
			reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}				
		
		/*此人处于娱乐地图状态*/
		if(isHappyMap(lastMap->getMapId()))
		{
			reason->member[sizeFail].failure_flag = ERROR_IN_HAPPY;
			strncpy(reason->member[sizeFail].nickName, nickNme, strlen(nickNme));
			reason->size += 1;
			return inst_room_id;
		}			
	}
	
	
	int roomNum = asistList.front();
	
	asistList.pop_front();
	
	/*此副本有人，加临时保护*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"the error roomNum:"<<roomNum<<endl;
		return inst_room_id;
	}
	
	initCpyRom[roomNum]->setFlgBusy(false);
	
	return initCpyRom[roomNum]->getCpyId();

}

/*分配房间，且进副本*/
void CpyLimit::assignRom(vector<string> &heroId,int roomNum)
{	
	if(roomNum >= initCpyRom.size() || roomNum < 0 || !initCpyRom[roomNum])
	{
		cout<<"CpyLimit::assignRom roomNum is error :"<<roomNum<<endl;
		return;
	}
	
	/*此副本有人，加临时保护*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"CpyLimit::assignRom roomNum is busy :"<<roomNum<<endl;
		return;
	}

	
	/*分配房间失败*/
	if(!initCpyRom[roomNum]->entCpy(heroId))	//初次进入副本
	{
		cout<<"CpyLimit::assignRom assignRom failed :"<<roomNum<<endl;
		asistList.push_front(roomNum);
		return;
	}
		
	initCpyRom[roomNum]->setFlgBusy(true);
	
	/*add chenzhen 20130128 队伍进入副本*/
	initCpyRom[roomNum]->setIsTeam(true);
}

/*分配房间，且进副本,单人进*/
void CpyLimit::assignRom(vector<string> &heroId)
{
	int roomNum = asistList.front();
	asistList.pop_front();
	
	
	
	/*此副本有人，加临时保护*/
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		cout<<"CpyLimit::assignRom room is busy:"<<roomNum<<endl;
		return;
	}
	
	/*分配房间失败*/
	if(!initCpyRom[roomNum]->entCpy(heroId))	//初次进入副本
	{
		cout<<"CpyLimit::assignRom room is failed:"<<roomNum<<endl;
		asistList.push_front(roomNum);
		return;
	}
		
	initCpyRom[roomNum]->setFlgBusy(true);
}

/*进副本场景地图*/
void CpyLimit::enterRom(int _roomNum,vector<string> &heroId,char *_mapId,Point *pTargetPt)
{
	if(_mapId == 0) return;
	
	/*判断副本房间是否有效*/
	if(!roomExist(_roomNum))
	{
		cout<<"CpyLimit::enterRom the _roomNum is error:"<<_roomNum<<endl;
		return;
	}
	/*判断房间是否为空*/
	if(initCpyRom[_roomNum]->getFlgBusy())
	{
		
		/*且进副本场景地图*/
		initCpyRom[_roomNum]->entCpyMap(heroId,_mapId,pTargetPt);
	}
	
}

/*副本回收房间*/
void CpyLimit::recoverRom(char *_cpyIdRom)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};		
	int roomNum;	

	if(!dealSerNumStr(_cpyIdRom,numStr,lastStr))
	{
		cout<<" CpyLimit::recoverRom the _cpyIdRom is error:"<<_cpyIdRom<<endl;
		return;
	}
	
	roomNum = atoi(numStr);
	
	/*判断副本房间是否有效*/
	if(!roomExist(roomNum))
	{
		cout<<" CpyLimit::recoverRom the roomNum is error:"<<roomNum<<endl;
		return;
	}
	/*回收扩展副本*/
	if(roomNum >= room)
	{
		recoverBorrowCpy(roomNum);
		return;
	}
	if(initCpyRom[roomNum]->getFlgBusy())
	{
		/*标记值重置*/
		initCpyRom[roomNum]->setFlgBusy(false);
		
		/*回收副本房间*/
		asistList.push_front(roomNum);				
	}
}

/*退出副本*/
void CpyLimit::exitCpy(int _roomNum,vector<string> &heroId)
{
	if(!roomExist(_roomNum))
	{
		cout<<"CpyLimit::exitCpy the _roomNum is error:"<<_roomNum<<endl;
		return;
	}
	if(initCpyRom[_roomNum]->getFlgBusy())
	{
		/*退出副本场景地图*/
		initCpyRom[_roomNum]->exitCpy(heroId);
	}
}

/*判断副本房间是否超出总房间数*/
bool CpyLimit::roomExist(int _roomNum)
{
	return _roomNum < initCpyRom.size() && _roomNum >= 0;
	
#if 0
	return _roomNum < newNum && _roomNum >= 0;
#endif
	// return _roomNum < room && _roomNum >= 0;
}

/*获得副本房间数*/
Cpy* CpyLimit::getRoomCpy(int roomNum)
{
	if(roomExist(roomNum))
	{
		if(initCpyRom[roomNum]->getFlgBusy())
		{
			return initCpyRom[roomNum];
		}
	}
	return NULL;
}
	
/*获得要求等级*/
int CpyLimit::getRank(void)
{
	return rank;
}
	
/*获得副本难度*/
int CpyLimit::getDiffcult(void)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};		
	int level;	

	if(!dealSerNumStr(cpyId,numStr,lastStr))
	{
		cout<<"CpyLimit::getDiffcult the cpyId is error:"<<cpyId<<endl;
		return -1;
	}
	
	level = atoi(numStr);
}


/*进副本之前进行申请房间号确认*/
bool CpyLimit::qualifyExamLast(vector<string> &heroId,int &_roomNum)
{

	char *cpyApplyId,numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	HeroCpyRecord *record;	
	int length,i;		
		
	
	if(heroId.empty())
	{
		return false;
	}
	
	hero_it = heroId_to_pHero.find(heroId[0]);
	
	if(hero_it == heroId_to_pHero.end())
	{
			return false;          
	}
	
	cpyApplyId = hero_it->second->getFbRom();
	
	if(cpyApplyId == NULL || strlen(cpyApplyId) == 0)
	{
		return false;
	}
	
	length = heroId.size();
	
	for(i = 1;i < length;i++)
	{
		hero_it = heroId_to_pHero.find(heroId[i]);
		
		if(hero_it == heroId_to_pHero.end())
		{
			return false;          
		}
		
		if(strcmp(cpyApplyId,hero_it->second->getFbRom()) != 0)
		{
			return false;
		}
	}		

	if(!dealSerNumStr(cpyApplyId,numStr,lastStr))
	{
		cout<<"CpyLimit::qualifyExamLast the cpyApplyId is error:"<<cpyApplyId<<endl;
		return false;
	}
	
	_roomNum = atoi(numStr);

	return true;
}

/*获得评分时间*/
int CpyLimit::getJdgTme(void)
{
	return judgeTme;
}

/*获得评分系数*/
double CpyLimit::getJdgRat(void)
{
	return jugGodRat;
}


/*析构函数*/
CpyLimit::~CpyLimit(void)
{
	storeMemRecord();
	
	vector<Cpy*>::iterator cpy_it;
	Cpy *val;
		
	for(cpy_it = initCpyRom.begin();cpy_it != initCpyRom.end();cpy_it++)
	{
		val = *cpy_it;		
		delete val;		
		val = NULL;
	}
	
	initCpyRom.clear();
	
	asistList.clear();
	
	clearWipeOut();
	
}

/*通过room,以及mapId找到map实例*/
Map_Cpy* CpyLimit::getMapCpy(int roomNum,char *mapId)
{
	if(!roomExist(roomNum))
	{
		cout<<"CpyLimit::getMapCpy cpy roomNum is error:"<<roomNum<<endl;
		return NULL;
	}
	if(mapId == NULL || strlen(mapId) == 0)
	{
		cout<<"CpyLimit::getMapCpy cpy mapId is error:"<<mapId<<endl;
		return NULL;
	}
	
	return initCpyRom[roomNum]->getCpyMap(mapId);
}

/*扩展副本*/
bool CpyLimit::borrowCpyFun(void)
{
	/*副本实例id，即副本id后面追加流水号*/
	char initCpyId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};        
	Cpy *borrowCpy,*modCpy;
	int flgIndex;
	
	if(initCpyRom.empty())
	{
		cout<<"CpyLimit::borrowCpyFun the initCpyRom is empty:"<<endl;
		return false;
	}
	modCpy = initCpyRom[0];
	borrowCpy = cpyManger->offerCpy(flgIndex);
	if(flgIndex == -1 || borrowCpy == NULL)
	{
		cout<<"CpyLimit::borrowCpyFun it is fail to borrow the cpy:"<<cpyId<<endl;
		return false;
	}

	size_t dynamicIndex;
	
	//没有孔，则往后面追加
	if(dynamicUseAbleIndex.empty())
	{
		dynamicIndex = totalSize;
		++totalSize;
	}
	
	//有孔，则插入
	else
	{
		dynamicIndex = dynamicUseAbleIndex.front();
	}
	
	strncpy(initCpyId,cpyId,strlen(cpyId));
	strncat(initCpyId,"_",strlen("_"));
	appendNum(initCpyId,dynamicIndex,4);
	
	
	borrowCpy->initBorrowCpy(initCpyId,modCpy->getCpyMapSet(),this);
	
	//如果数据异常，则要查
	pair<map<int,int>::iterator,bool> insert_it = dyRomIndexToMagIndex.insert(pair<int,int>(dynamicIndex,flgIndex));
	if(!insert_it.second)
	{
		cout<<"CpyLimit::borrowCpyFun error  the dynamicIndex is exist before:"<<dynamicIndex<<endl;
		return false;
	}
	
	if(initCpyRom.size() <= dynamicIndex)
	{		
		initCpyRom.push_back(borrowCpy);
	}
	else
	{
		initCpyRom[dynamicIndex] = borrowCpy;
		dynamicUseAbleIndex.pop_front();
	}
	
	
	
	asistList.push_front(dynamicIndex);
	
	return true;
}

/*扩展副本回收*/
void CpyLimit::recoverBorrowCpy(int romIndex)
{
	map<int,int>::iterator index_it = dyRomIndexToMagIndex.find(romIndex);
	if(index_it == dyRomIndexToMagIndex.end())
	{
		cout<<"CpyLimit::recoverBorrowCpy the romIndex is not lend :"<<romIndex<<endl;
		return;
	}	
	
	Cpy *borrowCpy = initCpyRom[romIndex];
	borrowCpy->recoverBorrowCpy();	
	if(!cpyManger->recover(borrowCpy,index_it->second))
	{
		cout<<"CpyLimit::recoverBorrowCpy it is error to recover borrowCpy:"<<cpyId<<endl;
	}
	
	dynamicUseAbleIndex.push_front(romIndex);
	
	dyRomIndexToMagIndex.erase(index_it);
	
	//把空洞用空值堵上
	initCpyRom[romIndex] = NULL;
}

/*获得基础分*/
int CpyLimit::getBaseGole(void)
{
	return baseGole;
}

/*组队后，有队员不同意之后，回收那个预定的房间号*/
void CpyLimit::recoverRom(int roomNum)
{
	
	/*判断副本房间是否有效*/
	if(!roomExist(roomNum))
	{
		cout<<"CpyLimit::recoverRom the roomNum is error:"<<roomNum<<endl;
		return;
	}
	/*回收扩展副本*/
	if(roomNum >= room)
	{
		recoverBorrowCpy(roomNum);
		return;
	}
	/*标记值重置*/
	initCpyRom[roomNum]->setFlgBusy(false);
	
	/*回收副本房间*/
	asistList.push_front(roomNum);	
}

/*只能单人进任务副本检测*/
bool CpyLimit::taskCpyQualifyExam(vector<string> &heroId,Failure_Reason* failure_reason)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	string teamId;         //队伍id
	Team *team;
	map<string,Team*>::iterator team_it;
	
	length = heroId.size();
	
	/*没有空房间*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*人数限制*/
	if(length < num) 
	{
		cout<<"If you want enter it, you must have "<<num<<" members and you only have "<<length<<endl;
		return false;
	}
		
	for(i = 0;i < length;i++)
	{

		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			cout<<"one of the heroid in hero vector is invalid"<<endl;
			return false;
		}
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		
		/*不是单人进*/
		if(length > 1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"the cpy only need one hero if he want come in"<<endl;
			return false;
		}

		
		const char *teamId = myHero->getTeamerId();
		if(strlen(teamId) != 0)
		{	
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			cout<<"CpyLimit::taskCpyQualifyExam This map forbidden coming with any partners"<<endl;
			return false;
			
	#if 0			
			/*为了简做，只要组队，都不让就进*/
			TeamManager* teamManger = TeamManager::getManagerInst();
			
			Team *team = teamManger->getTeamHandle(teamId);
		
			if(!team)
			{
				cout<<"CpyLimit::taskCpyQualifyExam team is NULL:"<<endl;
				return false;
			}
			
			if(team->size() > 1)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
				failure_reason->size += 1;
				return false;
			}
		
			team->sendMsg(msg_buf);
	#endif				
		}
		
		/*此人处于摆摊状态*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"This hero is in bussines state"<<endl;
			return false;
		}	
				
		/*此人处于押镖状态*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"The hero mustn't come in with a wagon"<<endl;
			return false;
		}
		/*此人处于副本状态*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"This hero is already in a cpy map!"<<endl;
			return false;
		}
		
		/*此人处于pk状态*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"enter list fiveLevent:"<<endl;
			cout<<"The hero mustn't come from a PK map!"<<endl;
			return false;
		}			
	}
	return true;
}	


/*单人进黑木崖副本检测*/
bool CpyLimit::qualifyExamTowerLayerCopy(vector<string> &heroId,Failure_Reason* failure_reason)
{
	
	map<string,Hero*>::iterator hero_it;
	char *perNikName,*wagonId,*mapId,*npcMapId;
	int length,i,sizeFail;	
	HeroCpyRecord *record;
	Map_Inform *lastMap;	
	Guild *myGuild;	
	Hero *myHero;
	Point piexPt;
	map<string,Team*>::iterator team_it;
	
	length = heroId.size();
	
	/*没有空房间*/
	if(asistList.empty())
	{
		if(!borrowCpyFun())
		{
			char failReason[100] = "6,13,";
			char idTset[10]={'\0'};
			strncpy(idTset,cpyId,strlen(cpyId) -2);			
			if(pg_hero == NULL)
			{
				return false;
			}
			sprintf(failReason + strlen(failReason),"%s",idTset);
			send_msg(pg_hero->getFd(), failReason);
			cout<<"CpyLimit::qualifyExamTowerLayerCopy three is not resorce to this cpy:"<<idTset<<endl;		
			return false;
		}		
	}
	
	/*人数限制*/
	if(length < num) 
	{
		cout<<"CpyLimit::qualifyExamTowerLayerCopy If you want enter it, you must have "<<num<<" members and you only have "<<length<<endl;
		return false;
	}
		
	for(i = 0;i < length;i++)
	{

		sizeFail = failure_reason->size;
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			cout<<"CpyLimit::qualifyExamTowerLayerCopy one of the heroid in hero vector is invalid"<<endl;
			return false;
		}
		record = myHero->getCpyRecord();
		perNikName = myHero->getNickName();
		lastMap = myHero->getMap();
		wagonId = myHero->memHero->wagonId;	
		piexPt = myHero->getLocation();
		mapId = lastMap->getMapId();
		
		/*不是单人进*/
		if(length > 1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy the cpy only need one hero if he want come in"<<endl;
			return false;
		}	
		
		const char *teamId = myHero->getTeamerId();
		if(strlen(teamId) != 0)
		{	
			failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This map forbidden coming with any partners"<<endl;
			return false;
			
	#if 0			
			/*为了简做，只要组队，都不让就进*/
			TeamManager* teamManger = TeamManager::getManagerInst();
			
			Team *team = teamManger->getTeamHandle(teamId);
		
			if(!team)
			{
				cout<<"CpyLimit::qualifyExamTowerLayerCopy team is NULL:"<<endl;
				return false;
			}
			
			if(team->size() > 1)
			{
				failure_reason->member[sizeFail].failure_flag = ERROR_NOT_ONE_PERSON;
				strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));	
				failure_reason->size += 1;				
				return false;
			}
		
			team->sendMsg(msg_buf);
	#endif				
		}
		
		/*此人处于摆摊状态*/
		if(myHero->getHeroState()==5)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_SELL;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This hero is in bussines state"<<endl;
			return false;
		}	
				
		/*此人处于押镖状态*/
		if(wagonId != NULL && strlen(wagonId) != 0)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_YA_BIAO;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy The hero mustn't come in with a wagon"<<endl;
			return false;
		}
		/*此人处于副本状态*/
		if(lastMap->getFlgCpy())
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_IN_COPY;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy This hero is already in a cpy map!"<<endl;
			return false;
		}
		
		/*此人处于pk状态*/
		if(lastMap->getWarType() !=1)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_PK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			cout<<"CpyLimit::qualifyExamTowerLayerCopy The hero mustn't come from a PK map!"<<endl;
			return false;
		}	
		
#if 1
		/*判断副本副本等级与人物等级相符否*/
		if(myHero->getLevel() < rank)
		{
			failure_reason->member[sizeFail].failure_flag = ERROR_LOWER_RANK;
			strncpy(failure_reason->member[sizeFail].nickName, perNikName, strlen(perNikName));
			failure_reason->size += 1;
			return false;
		}
#endif
			
	}
	return true;
}	


/*生成扫荡副本奖励*/
void CpyLimit::insertWipeOut(char *heroId)
{	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"CpyLimit::insertWipeOut the heroId is NULL:"<<endl;
		return ;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	swap_it = swapHeroRewardMap.find(heroId);
	if(swap_it != swapHeroRewardMap.end())
	{
		cout<<"CpyLimit::insertWipeOut the heroId is exist:"<<endl;
		return ;
	}
	char *goleStr = "towerCopy";
	vector<string>herVec;
	herVec.push_back(heroId);
	char cpyNowId[6] = {'\0'};
	strncpy(cpyNowId,cpyId,5);
	EctypeRewardSet *reward = helpNewEctypeReward(cpyNowId, herVec, goleStr); 
	if(reward == NULL)
	{
		cout<<"CpyLimit::insertWipeOut the reward is NULL:"<<endl;
		return;
	}
	swapHeroRewardMap[heroId] = reward;	
}	


/*删除扫荡副本奖励*/
void CpyLimit::eraseWipeOut(char *heroId)
{	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"CpyLimit::eraseWipeOut the heroId is NULL:"<<endl;
		return ;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	swap_it = swapHeroRewardMap.find(heroId);
	if(swap_it == swapHeroRewardMap.end())
	{
		cout<<"CpyLimit::eraseWipeOut the heroId is not exist:"<<heroId<<endl;
		return;
	}
	
	delete swap_it->second;
	swap_it->second = NULL;
	swapHeroRewardMap.erase(swap_it);
}

/*清除扫荡副本奖励*/
void CpyLimit::clearWipeOut(void)
{	
	if(swapHeroRewardMap.empty())
	{
		cout<<"CpyLimit::clearWipeOut the swapHeroRewardMap is empty:"<<endl;
		return;
	}
	
	map<string,EctypeRewardSet*>::iterator swap_it;
	for(swap_it = swapHeroRewardMap.begin();swap_it != swapHeroRewardMap.end();++swap_it)
	{
		delete swap_it->second;
		swap_it->second = NULL;
	}
	
	swapHeroRewardMap.clear();
}

const char* CpyLimit::getName() const
{
	return name;
}

size_t CpyLimit::getCostFatigue() const
{
	return costFatigue;
}

CpyMemRecord* CpyLimit::getRecord()
{
	return memRecord;
}
	
//取
void CpyLimit::initMemRecord()
{
	int where = -1,size = 0;
		
	char *MemRecord = mem_group->get_data(cpyLimitId, &size,&where);
		
	if(size != sizeof(CpyMemRecord) || MemRecord == NULL || where != 0)
	{
		cout<<"CpyLimit::initMemRecord is NULL:"<<endl;
		
		memRecord = new CpyMemRecord();
		
		return;
	}
		
		
	CpyMemRecord *_memRecord = (CpyMemRecord*)malloc(sizeof(CpyMemRecord));
	
	memRecord = new CpyMemRecord(*_memRecord);		
	
	free(_memRecord);
}

//存
void CpyLimit::storeMemRecord()
{
		
	bool isSuccess = mem_group->set_data(cpyLimitId,(char*)memRecord,(int)sizeof(CpyMemRecord),PUBLIC_MEMCACHED_INDEX);
	
	if(isSuccess)
	{
		cout<<"CpyLimit::storeMemRecord() set memRecord into memcached server success"<<endl;
	}	
	else
	{
		cout<<"CpyLimit::storeMemRecord() set memRecord into memcached server failure"<<endl;
	} 
}

void CpyLimit::recordLessTme(const char* recordHeroId,size_t secondstimes)
{
	if(!recordHeroId)
	{
		cout<<"CpyLimit::recordLessTme the recordHeroId is NULL:"<<endl;
		return;
	}
	Hero *recordHero = heroid_to_hero(recordHeroId);
	if(!recordHero)
	{
		cout<<"CpyLimit::recordLessTme the recordHero is NULL:"<<endl;
		return;
	}	
	if(!memRecord)
	{
		cout<<"CpyLimit::recordLessTme the memRecord is NULL:"<<endl;
		return;
	}
	if(memRecord->changeRecord(recordHero,secondstimes))
	{
		cout<<"CpyLimit::recordLessTme  the cpyLimitId the :"<<cpyLimitId<<" recordHeroId :"<<recordHeroId<<" brush the new record:"<<secondstimes<<endl;
	}
}
	
		
	