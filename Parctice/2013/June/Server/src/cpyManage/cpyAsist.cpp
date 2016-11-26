/************************************************************
	文件名：cpyAsist.cpp
	文件作用：进副本辅助函数
	作者：chenzhen
	创建日期：2012.06.29
************************************************************/
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"hero.h"
#include"team.h"
#include"guild.h"
#include "instancing_communication.h"
#include"partyRoomLimit.h"
#include"guild_asist.h"
#include"map_src.h"
#include"towerLayerRecord.h"
#include"teamManager.h"
extern map<string,PartyRoomLimit*> mapIdToPartyRomLimit;	
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string, Hero*> heroId_to_pHero;
extern map<int,string> levelToMapId;    
extern char server_name[10];
extern int partyHightestLevel;
extern map<string,Map_Inform*>mapId_connect_map;
//单身或者队长为真
bool SingleOrTeamLeader(const char* memberId)
{	
	if(!memberId || strlen(memberId) == 0)
	{
		return false;
	}
	
	Hero *teamLeaderHero = heroid_to_hero(memberId);
	if(!teamLeaderHero)
	{
		return false;
	}
	
	const char *teamId = teamLeaderHero->getTeamerId();
	
	if(strlen(teamId) == 0)
	{
		return true;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"entCpyAsist team is NULL:"<<endl;
		return true;		
	}
	
	if(!team->isHeader(teamLeaderHero->getIdentity()))
	{
		return false;
	}
	
	return true;
}

/*判断是否为同一个帮派的人,如果是，则partyId为帮派id，否则partyId的长度为0*/
bool judgeSameParty(vector<string> &heroId,char *partyId)
{	
	map<string,Hero*>::iterator hero_it;
	Guild *myGuild;
	int length,i;
	char *partyid;
	bool result;

	/*是否为空*/
	if(heroId.empty())
	{
		return false;
	}
	
	/*是否找到实例*/
	hero_it = heroId_to_pHero.find(heroId[0]);
	if(hero_it == heroId_to_pHero.end())
	{
		return false;           
	}
	
	/*是否加入帮派*/
	myGuild = hero_it->second->getGuild();
	if(myGuild == NULL)
	{
		return false;
	}
		
	length = heroId.size();		
	for(i = 1;i < length;i++)
	{
		if(!myGuild->isNumber(const_cast<char*>(heroId[i].c_str())))
		{
			return false;
		}
	}
	/*判断是否为同一个帮派的人,如果是，则partyId为帮派id，否则partyId的长度为0*/
	//以下代码临时保护，避免coredump, 陈真你个混蛋，又把一个两个不相干的逻辑混在一个函数中，
	//为什么在一个判断性的函数中夹带参数外部传递的功能?
	if(partyId != NULL)
	{ //added by benliao 2013.1.1 to avoid coredump 
		partyid = myGuild->getId();
		if(partyid==NULL)
		{
			return false;//added by benliao 2013.1.1
		}
		strncpy(partyId,partyid,strlen(partyid));
	}
	return true;
}


/*进入副本失败原因发送*/
void sendFailMsg(vector<string> &heroId,char *failMsg)
{			
	int i,length;
	Hero *myHero;
	map<string, Hero*>::iterator hero_it;
	
	if(failMsg == NULL || strlen(failMsg) == 0 || heroId.empty())
	{
		return;
	}
	
	length = heroId.size();	
	
	for(i = 0 ;i < length; i++)
	{
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}	
		send_msg(myHero->getFd(), failMsg);
		
	}
}

/*进入副本失败原因生成消息*/	
void dealFailRson(Failure_Reason* failure_reason,char *failMsg,int lengthStr,int entTye)
{
	int i,length;
	int head_f,head_s;
	i = 0;
	length = failure_reason->size;
	
	if(length < 1 || failMsg == NULL)
	{
		return;
	}
	
	/*进入副本失败原因头命令*/
	if(entTye == 0)
	{
		head_f = 6;
		head_s = 7;
	}
	/*进入vip包厢失败原因头命令*/
	else if(entTye == 1)
	{
		head_f = 12;
		head_s = 34;
	}
	/*进入帮派盛宴失败原因头命令*/
	else if(entTye == 2)
	{
		head_f = 12;
		head_s = 33;
	}
	/*进入帮派大本营失败原因头命令*/
	else if(entTye == 3)
	{
		head_f = 12;
		head_s = 32;
	}
	
	snprintf(failMsg + strlen(failMsg),lengthStr - strlen(failMsg),"%d,%d",head_f,head_s); 
    
	while(i < length)
	{
		snprintf(failMsg + strlen(failMsg),lengthStr - strlen(failMsg),",%d,%s",failure_reason->member[i].failure_flag,\
		failure_reason->member[i].nickName);	
		i++;
	}
}


/*用于处理带有流水号的字符串<主要是id>，且不改变原参数*/
bool dealSerNumStr(char *resore,char *last,char *ahead,bool isLast,char *tok)
{
	char *token,res[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	bool result;	
	
	/*待处理的字符串为空*/
	if(resore == NULL || strlen(resore) == 0 || ahead == NULL)
	{
		return false;
	}
	/*标记字符串为空，或者用于存储的字符串为空*/
	if(tok == NULL || strlen(tok) == 0 || last == NULL)
	{
		return false;
	}
	
	memset(last,'\0',strlen(last));
	memset(ahead,'\0',strlen(ahead));
	
	result = false;
	
	strncpy(res,resore,strlen(resore));

	token = strtok(res,tok);
	
	/*匹配最前面第一个标记值*/
	if(!isLast)
	{
		if(token == NULL)
		{
			return false;
		}

		memset(last,'\0',strlen(last));

		strncpy(last,token,strlen(token));
		
		memset(ahead,'\0',strlen(ahead));
		
		strncpy(ahead,resore + strlen(last) + 1,strlen(resore) - strlen(last) - 1);
		
		return true;
	}	
	
	if(token == NULL)
	{
		return false;
	}	
	
	/*匹配最后面第一个标记值*/
	while(token != NULL)
	{
		memset(last,'\0',strlen(last));
		strncpy(last,token,strlen(token));		
		token = strtok(NULL,tok);
		result = true;
	}
	
	memset(ahead,'\0',strlen(ahead));	
	strncpy(ahead,resore,strlen(resore) - strlen(last) - 1);
	return result;
}


/*退出副本*/
void outCpy(Hero *myHero)
{
	char *fbRom,*heroId,room[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char mapId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'}; 	
	char fbId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,CpyLimit*>::iterator cpyLimt_it;
	int found,roomNum;
    vector<string> heroIdVec;    

    if(myHero == NULL)
    {
        return;
    }
	
	fbRom = myHero->getFbRom();
	if(!dealSerNumStr(fbRom,room,fbId))
	{
		outSomeWhere(myHero);
		cout<<"the fbRom is error:"<<fbRom<<endl;
		return;
	}
	
	roomNum = atoi(room);
	
	if(roomNum < 0)
	{
		cout<<"the fb room is error:"<<roomNum<<endl;
		return;
	}
	
#if 0	
	if(strncmp(fbId,"008",3) == 0)
	{		
		/*调用退出塔防副本的接口*/
		cout<<"exit the tafang cpy cpyTyeId:"<<fbId<<endl;
		exitFromTowerDefence(myHero);
		return;
	}
#endif
	
    /*查找相对应副本*/
    cpyLimt_it = cpyId_to_cpyLimit.find(fbId);
    if(cpyLimt_it == cpyId_to_cpyLimit.end())
    {
		outSomeWhere(myHero);
       return;
    }
	
	heroId = myHero->getIdentity();	
    heroIdVec.push_back(heroId);
	
    /*执行退出副本函数*/
    cpyLimt_it->second->exitCpy(roomNum,heroIdVec);
	
	
	/*记录进入副本的流水账 jolly 12.11 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",6,1,server_name,(int)myTime.tv_sec,myHero->getIdentity(),myHero->getNickName(),cpyLimt_it->second->getCpyId());
	write_log(account_msg);	
	/*记录进入副本的流水账 jolly 12.11 end*/
	
}


/*副本面板相应辅助函数*/
void cpyPanelResponse(Hero *owner)
{		
	HeroCpyRecord *myCopyRecord;
	
	if(owner == NULL)
	{
		cout<<"the owner is NULL of cpyPanelRes:"<<endl;
		return;
	}	    
	
	myCopyRecord = owner->getCpyRecord();
	
	if(myCopyRecord == NULL)
	{
		cout<<"the copyRecord is error:"<<owner->memHero->identity<<endl;
		return;
	}
	
	myCopyRecord->sendEntMsg();
}

/*判断两个点之间的距离*/
bool judRange(Point &piexA,const Point &piexB,int const range)
{
	return sqrt(pow(fabs(piexA._x - piexB._x),2)+pow(fabs(piexA._y - piexB._y),2)) <= range;
}


/*初始化进副本失败结构体数据*/
bool initFailReson(Failure_Reason *reason)
{
	int i,size;	
	if(reason == NULL)
	{
		return false;
	}
	
	size = sizeof((reason->member))/sizeof((reason->member)[0]);
	
	for(i = 0;i < size; i++)
	{
		memset(((reason->member)[i]).nickName,'\0',sizeof(((reason->member)[i]).nickName));
		((reason->member)[i]).failure_flag = 0;
	}
	
	reason->size = 0;	
	return true;
}

/*进入帮派吃饭的地方<忠义堂>*/
void enterPartyEat(char *heroId,char *mapEatId)
{
	
	map<string,PartyRoomLimit*>::iterator partyRom_it;	
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char partyId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Failure_Reason* failure_reason;
	PartyRoomLimit *partyRoom;
	vector<string> herIdVec;
	int sizeFail;
	Hero *myHero;
	char *wagonId;	
	
	if(heroId == NULL || mapEatId == NULL)
	{
		cout<<"the argument is error:"<<endl;
		return;
	}
	
	myHero = heroid_to_hero(heroId);
	if(myHero == NULL)
	{
		cout<<"can not find the heroInst:"<<heroId<<endl;
		return;
	}
	
	cout<<"go party eat second:"<<mapEatId<<endl;
	herIdVec.push_back(heroId);
	failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
	failure_reason->size = 0;

	if(!initFailReson(failure_reason))
	{
		free(failure_reason);
		cout<<"failure_reason is NULL:"<<endl;
		return;
	}		
	
	sizeFail = failure_reason->size;	
	
	/*没有加入帮派*/
	if(!judgeSameParty(herIdVec,partyId) || strlen(partyId) == 0)
	{
		
		failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_NOT_PARTY;
		strncpy(failure_reason->member[sizeFail].nickName,herIdVec[0].c_str(),\
		strlen(herIdVec[0].c_str()));	
		failure_reason->size += 1;
		dealFailRson(failure_reason,failMsg,sizeof(failMsg),2);
		sendFailMsg(herIdVec,failMsg);				
		free(failure_reason);			
	    return;
	}
	
	wagonId = myHero->memHero->wagonId;
	
	/*此人处于摆摊状态*/
	if(myHero->getHeroState()==5)
	{
		failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_IN_SELL_STATION;
		strncpy(failure_reason->member[sizeFail].nickName, herIdVec[0].c_str(),\
		strlen(herIdVec[0].c_str()));
		failure_reason->size += 1;
		dealFailRson(failure_reason,failMsg,sizeof(failMsg),2);
		sendFailMsg(herIdVec,failMsg);				
		free(failure_reason);			
		return;
	}	
		
	/*此人处于押镖状态*/
	if(wagonId != NULL && strlen(wagonId) != 0)
	{
		failure_reason->member[sizeFail].failure_flag = PARMAP_ERROR_IN_YA_BIAO_STATION;
		strncpy(failure_reason->member[sizeFail].nickName, herIdVec[0].c_str(),\
		strlen(herIdVec[0].c_str()));
		failure_reason->size += 1;
		dealFailRson(failure_reason,failMsg,sizeof(failMsg),2);
		sendFailMsg(herIdVec,failMsg);				
		free(failure_reason);	
		return;
	}		
	
	free(failure_reason);		
	partyRom_it = mapIdToPartyRomLimit.find(mapEatId);	
	if(partyRom_it == mapIdToPartyRomLimit.end())
	{
		cout<<"the mapEatId mapId is error:"<<mapEatId<<endl;		
		return;
	}		
	partyRoom = partyRom_it->second;
	partyRoom->assignRom(herIdVec,partyId);
	
	cout<<"go party eat thrid:"<<mapEatId<<endl;
}

/*补齐等级对应的帮派大本营地图*/
bool insertCampMap(int key,string &values)
{
	map<int,string>::iterator level_it;
	level_it = levelToMapId.find(key);
	if(level_it == levelToMapId.end())
	{
		levelToMapId[key] = values;		
		return true;
	}
	return false;
}
		
/*插入等级对应的帮派大本营地图*/
void insertLevelCampMap(int level,string &values)
{
	map<int,string>::reverse_iterator level_it;
	int i;
	if(!levelToMapId.empty())
	{
		level_it = levelToMapId.rbegin();
		if(level_it->first >= level)
		{
			cout<<"the partybaseCamp.xml is error:"<<level<<endl;
			return;
		}	
	
		for(i = level - level_it->first; i < level;i++)
		{
			insertCampMap(i,level_it->second);
		}
	}	
	insertCampMap(level,values);
}


/*补齐最高等级对应的帮派大本营地图*/
void insertHightestLevelCampMap(void)
{
	map<int,string>::reverse_iterator level_it;
	level_it = levelToMapId.rbegin();
	insertLevelCampMap(partyHightestLevel,level_it->second);
}

/*插入等级对应的帮派大本营地图*/
void testPrintLevelCampMap(void)
{
	cout<<"test the campLevelMapId begin:"<<endl;
	map<int,string>::iterator level_it;
	for(level_it = levelToMapId.begin();level_it != levelToMapId.end();level_it++)
	{
		cout<<"the party level:"<<level_it->first<<endl;
		cout<<"the camp mapId:"<<level_it->second<<endl;
	}
	cout<<"test the campLevelMapId end:"<<endl;
}

/*退出帮派大本营*/
bool outCampMap(Hero *myHero)
{
	Guild *myGuild;
	Map_Src *mapNow; 
	vector<string> herVec;
	if(myHero == NULL)
	{
		cout<<"the myHero is NULL:"<<endl;
		return false;
	}
	myGuild = myHero->getGuild();
	
	if(myGuild == NULL)
	{
		cout<<"the guild is NULL:"<<myHero->getIdentity()<<endl;
		return false;
	}
	mapNow = (Map_Src*)(myHero->getMap());
	if(mapNow == NULL || !mapNow->getIsCampRomBusy())
	{
		cout<<"the map is NULL or not the campMap:"<<myHero->getIdentity()<<endl;
		return false;
	}	
	
	herVec.push_back(myHero->getIdentity());
	mapNow->exitCampRoom(herVec);
	return true;
}
	
/*进入任务副本法海不懂爱*/
void entTaskCpy(char *heroid,char *cpyTyeId)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	map<string,CpyLimit*>::iterator cpyLimt_it;	
	vector<string> heroId;  	
	
	/*入参检查*/
	if(heroid == NULL || cpyTyeId == NULL || strlen(heroid) == 0 || strlen(cpyTyeId) == 0)
	{
		cout<<"the argument heroid or cpyTyeId is empty or NULL:"<<endl;
		return;
	}	
	
	/*不是任务副本*/
	if(strcmp(cpyTyeId,"021_0") != 0)
	{
		cout<<"the cpyTyeId is not the taskCpy:"<<cpyTyeId<<endl;
		return;
	}
	
	heroId.push_back(heroid);	
	
   
    cpyLimt_it = cpyId_to_cpyLimit.find(cpyTyeId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		cout<<"can not find the cpyTyeId:"<<cpyTyeId<<endl;
		return;	
	}
	
	Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
	failure_reason->size = 0;

	if(!initFailReson(failure_reason))
	{
		cout<<"failure_reason is NULL:"<<endl;
		return;
	}
	
	/*资格审查*/
	if(!cpyLimt_it->second->taskCpyQualifyExam(heroId,failure_reason))
	{			
		dealFailRson(failure_reason,failMsg,sizeof(failMsg));
		sendFailMsg(heroId,failMsg);			
		free(failure_reason);	
		cout<<"It doesn't pass the check of enter task cpy conditions"<<endl;
		return;
	}
	
	cpyLimt_it->second->assignRom(heroId);
	free(failure_reason); 
}

/*体力值面板相应辅助函数*/
void fatigueResponse(Hero *owner)
{
	char fatigueMsg[200] = {'\0'};
	if(owner == NULL)
	{
		cout<<"the owner is NULL of fatigueResponse:"<<endl;
		return;
	}	 
	
	sprintf(fatigueMsg,"8,12,%s,%d,%d",owner->getIdentity(),owner->memHero->lastStrength,owner->memHero->fatigueUpperVal);
	send_msg(owner->getFd(), fatigueMsg);
}

/*20130412 chenzhen*/
bool isHappyMap(char *newMap)
{	
	if(newMap == NULL)
	{
		return false;
	}
	
	if (strcmp(newMap, "map_023") == 0 || strcmp(newMap, "map_024") == 0)
	{
		return true;
	}	
	return false;
}


/*黑木崖副本面板相应辅助函数*/
void towerLayerCpyResponse(Hero *owner)
{
	if(owner == NULL)
	{
		cout<<"towerLayerCpyResponse the owner is NULL :"<<endl;
		return;
	}	 
	
	/*获得黑木崖数据*/
	TowerLayerRecord* towerLayer = owner->getTowerLayerRecord();
	if(towerLayer == NULL)
	{
		cout<<"towerLayerCpyResponse the towerLayer is NULL :"<<endl;
		return;
	}
	send_msg(owner->getFd(), towerLayer->getTowerMsg());
	send_msg(owner->getFd(), towerLayer->getLayerMsg());
}


void initCpyLimitMemRecord()
{
	for(map<string,CpyLimit*>::iterator limit_it = cpyId_to_cpyLimit.begin();limit_it != cpyId_to_cpyLimit.end();++limit_it)
	{
		limit_it->second->initMemRecord();
	}
}

void storeCpyLimitMemRecord()
{
	for(map<string,CpyLimit*>::iterator limit_it = cpyId_to_cpyLimit.begin();limit_it != cpyId_to_cpyLimit.end();++limit_it)
	{
		limit_it->second->storeMemRecord();
	}
}


void outSomeWhere(Hero *myHero)
{
	char *mainSrcId = myHero->getMainSrc();	
	char chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Map_Inform*>::iterator mainSrc_it = mapId_connect_map.find(mainSrcId);
	
	Point beforePiexPt = myHero->getBeforePiexPt();
	
	/*找不到进副本之前的地图*/
	if(mainSrc_it == mapId_connect_map.end() || beforePiexPt._x <= 0 || beforePiexPt._y <= 0 )
	{
		myHero->setMainSrc("map_001");		
		mainSrc_it = mapId_connect_map.find(myHero->getMainSrc());
		beforePiexPt = mainSrc_it->second->getEntPt();
	}
	
		
		
	Map_Inform *mainSrcMap = mainSrc_it->second;
		
	/*退出原来地图*/
	myHero->quit_scene();
		
	/*进入副本地图*/
	myHero->setMap(mainSrcMap);		
	
		
	myHero->setLocation(beforePiexPt);
		
	/*开始生成切换场景信息*/
	snprintf(chageSre,sizeof(chageSre),"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,\
	CHANGE_SCENE,SUCCESS,mainSrcId,beforePiexPt._x,beforePiexPt._y,\
	mainSrcMap->getWarType(),mainSrcMap->getChangePkType(),mainSrcMap->getMapType());
		
	send_msg(myHero->getFd(),chageSre); 
		
	myHero->setWalkingFlg(false);		
		
	myHero->enter_scene();
}
	
