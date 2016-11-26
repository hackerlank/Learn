/************************************************************
	文件名：cpy.cpp
	文件作用：实现类Cpy类的方法
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/
#include"command_other_function_all_over.h"
#include"user_role_manage_assist.h"
#include"heroCpyRecord.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"cpy.h"
#include"towerLayerRecord.h"
extern map<string,Map_Cpy*> cpyMapConf;    
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map; 
extern TimerContainer<Map_Inform*> *mapThkContain;

Cpy::Cpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds)
{	
	memset(cpyId,'\0',sizeof(cpyId));	
	strncpy(cpyId,_cpyId,strlen(_cpyId));
	cpyMap = _cpyMap;
	cpyLimit = _cpyLimit;
	seconds = _seconds;
	flgBusy = false;
	isBorrowFlg = false;
	initMapSet();	
	rewardSet = NULL;
	isTeam = false;
	
}

/*初始化扩展副本*/
void Cpy::initBorrowCpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds)
{	
	list<string>::iterator map_it;
	char confMapId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	memset(cpyId,'\0',sizeof(cpyId));	
	strncpy(cpyId,_cpyId,strlen(_cpyId));	
	
	
	cout<<"_cpyMap.size:"<<_cpyMap.size()<<endl;
	for(map_it = _cpyMap.begin();map_it != _cpyMap.end();map_it++)
	{
		memset(confMapId,'\0',sizeof(confMapId));
		cout<<"*map_it:"<<*map_it<<endl;
		strncpy(confMapId,(*map_it).c_str(),strlen((*map_it).c_str()) - 11);
		cpyMap.push_back(confMapId);
	}
	cpyLimit = _cpyLimit;
	seconds = _seconds;
	flgBusy = false;
	initMapSet();		
}



/*构造函数*/
Cpy::Cpy(void)
{
	memset(cpyId,'\0',sizeof(cpyId));	
	instMapSet.clear();	
	canEntMapId.clear();
	olderMapId.clear();
	heroDieCtn.clear();
	heroGold.clear();
	cpyMap.clear();
	isBorrowFlg = true;
	flgBusy = false;	
	cpyLimit = NULL;	
	rewardSet = NULL;
	seconds = 0;
	costTme = 0;
	isTeam = false;
}
	
	
/*进副本*/
bool Cpy::entCpy(vector<string> &heroId)  
{
	if(flgBusy)
	{
		return false;
	}
	
	return entCpyAssist(heroId,0,const_cast<char *>((*src_it).c_str())); 
}

/*进副本场景*/
bool Cpy::entCpyMap(vector<string> &heroId,char *_mapId,Point* pTargetPt)  
{
	if(!flgBusy)
	{
		return false;
	}
	
	return entCpyAssist(heroId,1,_mapId,pTargetPt);
}

/*初始实例化地图信息*/
void Cpy::initMapSet(void)
{
	char roomStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Map_Cpy*>::iterator cpyMap_it;	
	list<string>::iterator map_it;
	list<string> newMapSet;
	Map_Cpy *map_conf;
	int rooms;
	size_t found;	
	
	
	if(!dealSerNumStr(cpyId,roomStr,lastStr))
	{
		cout<<"Cpy::initMapSet cpyId is error:"<<cpyId<<endl;		
		return;
	}
	rooms = atoi(roomStr);
	
	/*生成相对应的地图实例*/
	for(map_it = cpyMap.begin();map_it != cpyMap.end();++map_it)
	{
		
		Map_Cpy *map_int = NULL;
		cpyMap_it = cpyMapConf.find(*map_it);
		if(cpyMap_it == cpyMapConf.end())
		{
			cout<<"the map_it is not exit of the mapId in the sence:"<<*map_it<<endl;
			continue;		
		}
		map_conf = cpyMap_it->second;

		/*调用地图里面的复制方法*/
		map_int = map_conf->copyMap(rooms,cpyId);
		
		/*设置地图副本实例指针*/
		map_int->SetCpy(this);
		
	
		instMapSet[map_int->getMapId()] = map_int;	
		newMapSet.push_back(map_int->getMapId());
		
		/*为何用string，因为他有find方法*/
		olderMapId += map_int->getMapId();
		olderMapId += " ";
		
		
	}	
	
	if(cpyMap.empty())
	{
		cout<<"Cpy::initMapSet it is error:"<<cpyId<<endl;
	}
	
	/*交换两个容器的内容，使得cpyMap里面是经过处理后的mapId*/
	cpyMap.swap(newMapSet);
	
	src_it = cpyMap.begin();
	
	/*第一张可以进*/
	canEntMapId.insert(*src_it);  
	rewardSet = NULL;
	/*测试内容*/
//	printCpyMap();	
}

/*把下一个副本mapId放入当前玩家可进入mapId集合里面*/
void Cpy::inPutCanEntset(void)
{
	src_it++;
	if(src_it == cpyMap.end())
	{
		return;
	}
	canEntMapId.insert(*src_it);
}
	

Cpy::~Cpy(void)
{
	map<string,Map_Cpy*>::iterator cpyMap_it;	
	Map_Cpy *map_int;
	map_int = NULL;	
	for(cpyMap_it = instMapSet.begin();cpyMap_it != instMapSet.end();cpyMap_it++)
	{
		map_int = cpyMap_it->second;
		delete map_int;
		map_int = NULL;
	}
	instMapSet.clear();
	mapNow = NULL;
	cpyMap.clear();
	if(rewardSet != NULL)
	{
		delete rewardSet;
		rewardSet = NULL;
	}
}


bool Cpy::instMapNow(char *_mapId)
{
	
	map<string,Map_Cpy*>::iterator map_it;
	set<string>::iterator canEnt_it;
	/*判断是否能进入此地图*/
 	canEnt_it = canEntMapId.find(_mapId);
	if(canEnt_it == canEntMapId.end())
	{
		cout<<"Cpy::instMapNow can not pass the cant:"<<_mapId<<endl;
		return false;
	}
	/*判断是否有对应实例指针*/
	map_it = instMapSet.find(_mapId);
	if(map_it == instMapSet.end())
	{
		cout<<"Cpy::instMapNow can not find the mapInst:"<<_mapId<<endl;
		return false;
	}
	mapNow = map_it->second;
	return true;
}

/*测试cpyMap内容*/
void Cpy::printCpyMap(void)
{
	list<string>::iterator map_it;	
	for(map_it = cpyMap.begin();map_it != cpyMap.end();map_it++)
	{		
		cout<<"mapId:"<<*map_it<<endl;
	}	
}

/*设置副本空闲标志值*/
void Cpy::setFlgBusy(bool _flgBusy)
{
	flgBusy = _flgBusy;
}

/*获得副本空闲标志值*/
bool Cpy::getFlgBusy()
{
	return flgBusy;
}

/*副本回收*/
void Cpy::recover(void)
{
	/*退出副本*/
	exitCpy();
	
	/*回收副本*/
	flgBusy = false;	
	map<string,Map_Cpy*>::iterator map_it;
	for(map_it = instMapSet.begin();map_it != instMapSet.end();map_it++)
	{
		mapNow = map_it->second;
		delete mapNow;
		mapNow = NULL;
	}
	instMapSet.clear();	
	canEntMapId.clear();
	delete rewardSet;
	rewardSet = NULL;
	initMapSet();
	costTme = 0;
	cpyLimit->recoverRom(cpyId);
}


/*进副本辅助函数，times 1，表示进副本场景，0 表示进副本*/
bool Cpy::entCpyAssist(vector<string> &heroId,int times,char *_mapId,Point* pTargetPt)  
{	
	if(_mapId==0) return false;

	/*加临时保护此副本已经有人了*/
	if(cpyMap.empty())
	{
		return false;
	}	
	
	/*进入场景失败*/
	if(!instMapNow(_mapId))
	{
		return false;
	}
	
	/*test for monsterbyHERO*/
	Hero *myHero = heroid_to_hero(heroId[0]);
	
	/*是任务副本法海不懂爱*/
	if(strncmp(cpyId,"021_0",5) == 0)
	{
		mapNow->initMonValues(myHero);
	}
	
	/*刷出第一批怪*/
	mapNow->fristEntMap();	
	
	if(times == 0)
	{
		return entAssist(heroId,1);
	}
	
	/*进场景*/
	return entMapAssist(heroId,_mapId,pTargetPt);
}

/*获得相对上下层关系*/
int Cpy::getEntMapOlder(char *oldMapId,char *newMapId)
{
	int olderFound,newFound;
	olderFound = olderMapId.find(oldMapId);
	newFound = olderMapId.find(newMapId);
	
	/*如果旧地图或者新地图都找不到，则返回0*/
	if(olderFound == string::npos || newFound == string::npos)
	{
		return 0;
	}
	else
	{
		/*如果旧地图是在新地图的上层，则返回-1*/
		if(olderFound > newFound)
		{
			return -1;
		}
		
		/*如果旧地图是在新地图的下层，则返回1*/
		else
		{
			return 1;
		}
	}
}


/*退出副本*/
void Cpy::exitCpy(vector<string> &heroId)
{	
	char *mainSrcId,chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Map_Inform*>::iterator mainSrc_it;
	map<string,Hero*>::iterator hero_it;
	Map_Inform *mainSrcMap;
	Point beforePiexPt;
	int length,i;	
	Hero *myHero;	
	
	
	length = heroId.size();
	
	if(heroId.empty())
	{
		return;
	}	
	
	/*修改玩家角色信息*/
	for(i = 0;i < length;i++)
	{
		memset(chageSre,'\0',sizeof(chageSre));
		hero_it = heroId_to_pHero.find(heroId[i]);
		if(hero_it == heroId_to_pHero.end())
		{
			continue;           
		}
		
		myHero = hero_it->second;
		
		mainSrcId = myHero->getMainSrc();	
		
		mainSrc_it = mapId_connect_map.find(mainSrcId);
		
		if(mainSrc_it == mapId_connect_map.end())
		{
			/*找不到进副本之前的地图*/
			continue;
		}
		
		mainSrcMap = mainSrc_it->second;
		
		/*退出原来地图*/
		myHero->quit_scene();
		
		/*进入副本地图*/
		myHero->setMap(mainSrcMap);
		
		beforePiexPt = myHero->getBeforePiexPt();
		
		myHero->setLocation(beforePiexPt);
		
		myHero->setFbRom(NULL);
		
		/*开始生成切换场景信息*/
		snprintf(chageSre,sizeof(chageSre),"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,\
		CHANGE_SCENE,SUCCESS,mainSrcId,beforePiexPt._x,beforePiexPt._y,\
		mainSrcMap->getWarType(),mainSrcMap->getChangePkType(),mainSrcMap->getMapType());
		
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		
		myHero->enter_scene();
	}
	/*单人退出副本处理*/
	exitHero(heroId);	
}


/*全体退出副本*/
void Cpy::exitCpy(void)
{	

	char *mainSrcId,chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Map_Inform*>::iterator mainSrc_it;
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator die_it;	
	Map_Inform *mainSrcMap;
	Point beforePiexPt;	
	Hero *myHero;		
	
	if(heroDieCtn.empty())
	{
		cout<<"the heroDieCtn is empty:"<<endl;
		return;
	}
	
	/*修改玩家角色信息*/
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{
		memset(chageSre,'\0',sizeof(chageSre));
		
		hero_it = heroId_to_pHero.find(die_it->first);
		if(hero_it == heroId_to_pHero.end())
		{
			cout<<"can not find the hero:"<<die_it->first<<endl;
			continue;           
		}
		
		myHero = hero_it->second;
		
		mainSrcId = myHero->getMainSrc();	
		
		mainSrc_it = mapId_connect_map.find(mainSrcId);
		
		/*找不到进副本之前的地图*/
		if(mainSrc_it == mapId_connect_map.end())
		{
			cout<<"can not find the mapInst before enter the cpy:"<<mainSrcId<<endl;
			continue;
		}
		
		mainSrcMap = mainSrc_it->second;
		
		/*退出原来地图*/
		myHero->quit_scene();
		
		/*进入副本地图*/
		myHero->setMap(mainSrcMap);
		
		beforePiexPt = myHero->getBeforePiexPt();
		
		myHero->setLocation(beforePiexPt);
		
		/*开始生成切换场景信息*/
		snprintf(chageSre,sizeof(chageSre),"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,\
		CHANGE_SCENE,SUCCESS,mainSrcId,beforePiexPt._x,beforePiexPt._y,\
		mainSrcMap->getWarType(),mainSrcMap->getChangePkType(),mainSrcMap->getMapType());
		
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		
		myHero->enter_scene(); 
	}
	
	/*全体退出副本处理*/
	exitHero();
}

/*副本房间自动回收*/
void Cpy::recoverCpy(void)
{
	/*时间到，则回收*/
	// if(timeOut())
	// {
		// return;
	// }
	
	int persons;
	persons = 0;
	map<string,Map_Cpy*>::iterator map_it;
	for(map_it = instMapSet.begin();map_it != instMapSet.end();map_it++)
	{
		persons += map_it->second->getFdSze();
	}
	/*没有人，则回收*/
	if(persons == 0 && heroDieCtn.empty())
	{
		cout<<"the person:"<<persons<<endl;
		/*重置*/
		initCpy();
		
		/*new的形式重置*/
	//	recover();
	}
}

/*副本通关*/
bool Cpy::PassCpyJudge(char *_mapId)
{
	int founds;
	
	if(strlen(_mapId) == 0)
	{
		return false;
	}	
	founds = olderMapId.find(_mapId);
	if(founds == string::npos)
	{
		return false;
	}
	if(olderMapId.size()- founds != strlen(_mapId) + 1)
	{
		return false;
	}
	
	return true;
}

/*获得副本奖励实例指针*/
EctypeRewardSet *Cpy::getRewardSet(void)
{
	return rewardSet;
}

/*初始化副本奖励*/
void Cpy::initRewardSet(void)
{
	char typStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyTypId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char goleStr[1000] = {'\0'};	
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	vector<string> heroIdVec;
	int level,step;
	
	level = cpyLimit->getRank();	
	
	if(!dealSerNumStr(cpyId,typStr,cpyTypId,false))
	{
		cout<<"the cpyId is error:"<<cpyId<<endl;
		return;
	}
	if(!dealSerNumStr(cpyTypId,numStr,goleStr,false))
	{
		cout<<"the cpyTypId is error:"<<cpyTypId<<endl;
		return;
	}	
	
	
	
	
	step = atoi(numStr);
	step %= 3;
	cout<<"typStr:"<<typStr<<endl;
	cout<<"step:"<<step<<endl;
	cout<<"cpyTypId:"<<cpyTypId<<endl;
	cout<<"cpyId:"<<cpyId<<endl;
	
	memset(goleStr,'\0',sizeof(goleStr));		
	mapToVec(heroIdVec);
	
	memset(cpyTypId,'\0',sizeof(cpyTypId));
	strncpy(cpyTypId,cpyId,5);
	
	/*如果是黑木崖副本就往这儿走了*/
	if(strncmp(cpyId,"021",3) > 0)
	{
		if(rewardSet == NULL)
		{
			rewardSet = helpNewEctypeReward(cpyTypId, heroIdVec, goleStr);
		}
		
		return;
	}
	
	if(rewardSet == NULL)
	{
		goleDeal(goleStr,sizeof(goleStr));
		strncpy(typStr, cpyId, 5);
		cout<<"BisonTest typStr is "<<typStr<<endl;
		cout<<"accept reward:"<<endl;
		rewardSet = helpNewEctypeReward(typStr, heroIdVec, goleStr);
		cout<<"goleStr:"<<goleStr<<endl;
	}
}

bool Cpy::timeOut(void)
{
	struct timeval end;	
	
	gettimeofday(&end,NULL);	
	costTme = end.tv_sec - begin.tv_sec;
	
	if(costTme >= seconds)	
	{
		if(flgBusy)
		{
			/*以复员的形式重置*/			
			initCpy();
			
			/*new 形式重置*/
			// recover();			
		}
		return true;
	}
	if(seconds - costTme == 300)
	{
		cout<<"send the msg of the system will push you out of the cpy after :"<<seconds - costTme<<" seconds"<<endl;
	}
	return false;
}

/*重置副本房间信息*/	
void Cpy::initCpy(void)
{
	/*退出副本*/
	exitCpy();
	
	map<string,Map_Cpy*>::iterator map_it;
	for(map_it = instMapSet.begin();map_it != instMapSet.end();map_it++)
	{
		map_it->second->initMap();
	}

	src_it = cpyMap.begin();
	
	canEntMapId.clear();	
	
	canEntMapId.insert(*src_it);  
	
	if(rewardSet != NULL)
	{
		delete rewardSet;
		rewardSet = NULL;
	}	
	
	heroDieCtn.clear();
	{
		std::map<string,int> tmp;
		heroDieCtn.swap(tmp);
	}
	
	heroGold.clear();
	{
		std::map<string,int> tmp;
		heroGold.swap(tmp);
	}
	
	costTme = 0;
	
	flgBusy = true;
	
	mapNow = NULL;
	
	cpyLimit->recoverRom(cpyId);
	
	isTeam = false;
	
}

/*副本回收后条件判断*/
bool Cpy::judgeRecover(void)
{
	if(mapNow == NULL || flgBusy == false)
	{
		return true;
	}
	return false;
}

/*通关后数据记录*/
void Cpy::passRecord(void)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char typeStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};	
	
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator die_it;
	int level;
	Hero * hero;		

	/*组队的不算,add by chenzhen 201302201246避免角色被顶掉时，isTeam属性出错*/
	if(heroDieCtn.empty() || heroDieCtn.size() != 1 || isTeam)
	{
		cout<<"Cpy::passRecord more than one person in the copy:"<<endl;
		return;
	}
		
	/*判断是否为黑木崖副本*/
	if(passTowerLayer())
	{
		cout<<"the copy is towerLayer copy:"<<cpyId<<endl;
		return;
	}
	
	/*处理房间号*/
	if(!dealSerNumStr(cpyId,numStr,lastStr))
	{
		cout<<"Cpy::passRecord the cpyId is woring:"<<cpyId<<endl;
		return;
	}
	
	/*处理副本难度*/
	if(!dealSerNumStr(lastStr,numStr,typeStr))
	{
		cout<<"Cpy::passRecord the cpyStr is woring:"<<lastStr<<endl;
		return;
	}
	
	
	level = atoi(numStr);
	
	
	if(level <= 0 || level > 3)
	{
		return;
	}	
	
	

	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{		
		hero_it = heroId_to_pHero.find(die_it->first);
		if(hero_it != heroId_to_pHero.end())
		{
			/*通关副本记录*/
			hero_it->second->getCpyRecord()->inputPasCtn(typeStr);
			
			if(hero_it->second->getCpyRecord()->isPassCpy("016"))
			{
				/*通关所有副本，给头衔，都是浮云*/
				hero_it->second->addTitle("T022");
			}
				
			
			//jolly add wulinTarget 12,4 start
			char mapIdentity[40]={'\0'};
			strncpy(mapIdentity,hero_it->second->getMap()->getIdentity(),sizeof(mapIdentity));
			cout<<"############################################"<<endl;
			cout<<"mapIdentity:"<<mapIdentity<<endl;
			cout<<"############################################"<<endl;
			if (strncmp(mapIdentity,"ectype_map_025_1",16)==0)			//桃花厅（12级）
			{
				hero_it->second->updataSingleTarget(1,3);
			}
			else if (strncmp(mapIdentity,"ectype_map_026_1",16)==0)		//金瓯水道（20级）
			{
				hero_it->second->updataSingleTarget(1,8);
			}
			else if (strncmp(mapIdentity,"ectype_map_028_1",16)==0)		//迎春阁（25级）
			{
				hero_it->second->updataSingleTarget(2,6);
			}
			else if (strncmp(mapIdentity,"ectype_map_029_1",16)==0)		//迎春阁地下室（30级）
			{
				hero_it->second->updataSingleTarget(2,10);
			}
			else if (strncmp(mapIdentity,"ectype_map_032_1",16)==0)		//珠光宝气阁（35级）
			{
				hero_it->second->updataSingleTarget(3,0);
			}
			else if (strncmp(mapIdentity,"ectype_map_027_1",16)==0)		//幻宫迷境一层（40级）
			{
				hero_it->second->updataSingleTarget(3,3);
			}
			else if (strncmp(mapIdentity,"ectype_map_033_1",16)==0)		//幻宫迷境二层（45级）
			{
				hero_it->second->updataSingleTarget(4,0);
			}
			else if (strncmp(mapIdentity,"ectype_map_034_1",16)==0)			//渡劫（50级）
			{
				hero_it->second->updataSingleTarget(4,5);
			}
			else if (strncmp(mapIdentity,"ectype_map_035_1",16)==0)		//石甲阵（52级）
			{
				hero_it->second->updataSingleTarget(5,1);
			}
			else if (strncmp(mapIdentity,"ectype_map_036_1",16)==0)			//落阳坡（54级）
			{
				hero_it->second->updataSingleTarget(5,3);
			}
			else if (strncmp(mapIdentity,"ectype_map_037_1",16)==0)			//通天神台（56级）
			{
				hero_it->second->updataSingleTarget(5,5);
			}
			else if (strncmp(mapIdentity,"ectype_map_038_1",16)==0)		//桃园刺杀（60级）
			{
				hero_it->second->updataSingleTarget(5,7);
			}
			else if (strncmp(mapIdentity,"ectype_map_039_1",16)==0)		//英雄岛（65级）
			{
				hero_it->second->updataSingleTarget(6,4);
			}
			else if (strncmp(mapIdentity,"ectype_map_031_1",16)==0)		//九龙棋手（70级）
			{
				hero_it->second->updataSingleTarget(6,8);
			}
			else if (strncmp(mapIdentity,"ectype_map_030_1",16)==0)		//鬼蜮密室（75级）
			{
				hero_it->second->updataSingleTarget(7,2);
			}
			else if (strncmp(mapIdentity,"ectype_map_040_1",16)==0)		//清风三观（80级）
			{
				hero_it->second->updataSingleTarget(7,4);
			}
			//jolly add wulinTarget 12,4 end
			cout << "hero_it->second->getCpyRecord()->inputPasCtn(typeStr);" << endl;
		}
	}
}

/*单人退出副本处理*/
void Cpy::exitHero(vector<string> &heroId)
{
	map<string,int>::iterator die_it;
	int i,length;
	
	if(heroId.empty() || heroDieCtn.empty())
	{
		return;
	}
	
	length = heroId.size();
	
	for(i = 0;i < length && !heroDieCtn.empty();i++)
	{
		die_it = heroDieCtn.find(heroId[i]);
		if(die_it != heroDieCtn.end())
		{
			heroDieCtn.erase(die_it);
		}
	}
	
#if 0
	/*add by chenzhen 201302281411 to exam the person of cpy*/
	cout<<"Cpy::exitHero to call recoverCpy() begin:"<<endl;
	recoverCpy();
	cout<<"Cpy::exitHero to call recoverCpy() end:"<<endl;
#endif
}
	
/*所有人退出副本处理*/
void Cpy::exitHero(void)
{
	if(heroDieCtn.empty())
	{
		return;
	}
	heroDieCtn.clear();
	
	/*add by chenzhen 201302281411 to exam the person of cpy*/	
	//recoverCpy();
}
	
/*进副本辅助函数*/
bool Cpy::entAssist(vector<string> &heroId,int olderNext)  
{
	char roomStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyTypId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char mapRealId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	Point beforePiexPt,enterPt;
	HeroCpyRecord *myCpyRecord;	
	Map_Inform *oldMap;	
	char* mainSrcId,*mapId,*sumMonMsg;
	Hero *myHero;	
	int length,i;
	
	
	
	
	mapId = mapNow->getMapId();
	
	enterPt = mapNow->getEntPt();
	
	/*处理地图id，以便客户端识别*/
	strncpy(mapRealId,mapId,14);
	
#if 0	
	/*处理地图id，以便客户端识别*/
	strncpy(mapRealId,mapId,strlen(mapId) - 13);
#endif	
	/*开始生成切换场景信息*/
	sprintf(chageSre,"%d,%d,%d,%s,%d,%d,%d,%d,%d",SELECT_HERO_RETURN,CHANGE_SCENE,SUCCESS,\
			mapRealId,enterPt._x,enterPt._y,mapNow->getWarType(),mapNow->getChangePkType(),\
			mapNow->getMapType());
			
	cout<<"go entAssist before:"<<chageSre<<endl;
	
	if(!dealSerNumStr(cpyId,roomStr,cpyTypId))
	{
		cout<<"the cpyId is error:"<<cpyId<<endl;
		return false;
	}		
	
	length = heroId.size();	
	
	sumMonMsg = mapNow->getSumMonMsg();
	
	/*修改玩家角色信息*/
	for(i = 0;i < length;i++)
	{
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}		
		Map_Inform *oldMap = myHero->getMap();
		mainSrcId = oldMap->getMapId();
		
		myHero->setFbRom(cpyId);
		myHero->setMainSrc(mainSrcId);
		
		/*记住进副本之前的点*/
		beforePiexPt = myHero->getLocation();
		myHero->setBeforePiexPt(beforePiexPt);
		myHero->initCpyRecTme();
		
		heroDieCtn[heroId[i]] = 0;
		
		/*退出原来地图*/
		myHero->quit_scene();		
		
		/*设置新图*/
		myHero->setMap(mapNow);
		
		myHero->setLocation(enterPt);
		 
		/*副本进入状态*/		
		myCpyRecord = myHero->getCpyRecord();
		if(myCpyRecord != NULL)
		{
			myCpyRecord->inputEntCtn(cpyTypId);
		}	
		send_msg(myHero->getFd(),chageSre); 
		
		myHero->setWalkingFlg(false);		
		// send_msg(myHero->getFd(),sumMonMsg);
		myHero->enter_scene();
	}
	cout<<"go entAssist end:"<<chageSre<<endl;
	gettimeofday(&begin,NULL);
	return true;
}



/*进副本场景辅助函数*/
bool Cpy::entMapAssist(vector<string> &heroId,char *_mapId,Point* pTargetPt)  
{	
	char *sumMonMsg,chageSre[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	char roomStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char mapStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	int i,index,length;	
	Hero *myHero;
	
	strncpy(mapStr,_mapId,strlen(_mapId) - 13);	
	snprintf(chageSre + strlen(chageSre),sizeof(chageSre) - strlen(chageSre),\
				"%d%s%d%s%d%s%s%s%d%s%d%s%d%s%d,%d",\
				SELECT_HERO_RETURN,",",CHANGE_SCENE,",",SUCCESS,",",\
				mapStr,",",pTargetPt->_x,",",pTargetPt->_y,\
				",",mapNow->getWarType(),",",mapNow->getChangePkType(), mapNow->getMapType());	
				
	cout<<"chageSre:"<<chageSre<<endl;
	
	length = heroId.size();
	
	sumMonMsg = mapNow->getSumMonMsg();
	
	for(i = 0;i < length;i++)
	{
		hero_it = heroId_to_pHero.find(heroId[i]);
		if(hero_it == heroId_to_pHero.end())
		{
			continue;           
		}
		myHero = hero_it->second;
		
		myHero->quit_scene();
		
	    myHero->setMap(mapNow);		
		
		myHero->setLocation(*pTargetPt);
		
		send_msg(myHero->getFd(),chageSre); 	  
		
		myHero->setWalkingFlg(false);
		// send_msg(myHero->getFd(),sumMonMsg);
		myHero->enter_scene();
	}
	return true;
}		



/*副本进入前的"预定副本房间"函数*/
void Cpy::goAheadCpy(vector<string> &heroId)
{
	map<string,Hero*>::iterator hero_it;
	int length, i;	
	
	length = heroId.size();
				
	for(i = 0;i < length;i++)
	{
		hero_it = heroId_to_pHero.find(heroId[i]);
		
		if(hero_it == heroId_to_pHero.end())
		{
			continue;          
		}
		
		hero_it->second->setFbRom(cpyId);
	}
}

char* Cpy::getCpyId(void)
{
	return cpyId;
}


/*发送副本怪物实时数量*/
void Cpy::sentLveMonMsg(void)
{
	
	map<string,Hero*>::iterator hero_it;	
	map<string,int>::iterator die_it;
	char *sumMonMsg;
	
	if(mapNow==NULL){//added by benliao 2012.12.23 fix core
		return;
	}
	
	mapNow->formSumMonMsg();
	
	sumMonMsg = mapNow->getSumMonMsg();
	
	if(sumMonMsg == NULL || strlen(sumMonMsg) == 0)
	{
		return;
	}
	
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{
		hero_it = heroId_to_pHero.find(die_it->first);
		
		if(hero_it == heroId_to_pHero.end())
		{
			continue;          
		}
		send_msg(hero_it->second->getFd(),sumMonMsg); 
	}
}


/*获得副本难度*/
int Cpy::getDiffcult(string _cpyIds)
{
	int level;
	int founds;
	founds = _cpyIds.find_last_of("_");
	if(founds == string::npos)
	{
		return -1;
	}
	level = atoi(_cpyIds.substr(founds+1).c_str());
	return level;
}

/*计算时间为参数所得分数*/
int Cpy::judgeTmeGole(void)
{
	int midTme;	
	struct timeval end;		
	
	midTme = cpyLimit->getJdgTme();	
	
	gettimeofday(&end,NULL);
	
	// costTme = end.tv_sec - begin.tv_sec;
	
	cout<<"second is :"<<costTme<<endl;	
	
	if(costTme >= midTme)
	{
		return 0;
	}
	return (midTme - costTme)/60; 
}	


/*计算时间为参数所得分数*/
int Cpy::getTmeSecond(void)
{	
	struct timeval end;	
	
	gettimeofday(&end,NULL);
	
	costTme = end.tv_sec - begin.tv_sec;
	
	return costTme;
}	

/*计算死亡次数为参数所得分数*/
void Cpy::judgeDieGole(void)	
{
	ctnDieTme();
	
	map<string,int>::iterator die_it;
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{
		heroGold[die_it->first] = -(die_it->second * 5);
		cout<<"dieGole:"<<-(die_it->second * 5)<<endl;
	}
	cout<<"heroGold.size:"<<heroGold.size()<<endl;
}

/*计算死亡次数*/
void Cpy::ctnDieTme(void)	
{
	map<string,Hero*>::iterator hero_it;    
	map<string,int>::iterator die_it;
	
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{
		hero_it = heroId_to_pHero.find(die_it->first);
		if(hero_it == heroId_to_pHero.end())
		{
			cout<<"can not find the heroInst:"<<die_it->first<<endl;
	//		continue;
			return;
		}
		die_it->second =  hero_it->second->getCpyRevTme();
	}
}


/*计算死亡次数为参数所得分数*/
void Cpy::judgeAllGole(void)
{
	int timeGole,baseGole,passGole;

	map<string,int>::iterator gold_it;
	
	timeGole = judgeTmeGole();
	baseGole = cpyLimit->getBaseGole();
	passGole = int(cpyLimit->getJdgRat());
	cout<<"baseGole:"<<baseGole<<endl;
	
	if(heroGold.empty())
	{
		cout<<"heroGold is empty:"<<endl;
	}
	
	for(gold_it = heroGold.begin();gold_it != heroGold.end();gold_it++)
	{
		gold_it->second += timeGole;
		gold_it->second += baseGole;
		gold_it->second += passGole;
		
		/*最低分10分*/
		if(gold_it->second <= 10)
		{
			gold_it->second = 10;
		}
		cout<<"the total gole:"<<gold_it->second<<endl;
	}
}


/*生成得分消息*/
void Cpy::formGoleMsg(char *goleMsg,int length)
{	
	char midStr[1000] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator gold_it;
	map<string,int>::iterator die_it;	
	int person;
	
	if(heroGold.empty())
	{
		cout<<"it is empty:"<<endl;
		return;
	}	
	person = 0;
	for(gold_it = heroGold.begin(),die_it = heroDieCtn.begin();\
		gold_it != heroGold.end() && die_it != heroDieCtn.end();\
		gold_it++,die_it++)
	{
		hero_it = heroId_to_pHero.find(gold_it->first);
		if(hero_it != heroId_to_pHero.end())
		{
			snprintf(midStr + strlen(midStr),sizeof(midStr) - strlen(midStr),",%s%s%s%s%d%s%d%s%d",\
			hero_it->second->getIdentity(),",",hero_it->second->getNickName(),",",costTme,",",die_it->second,",",gold_it->second);
			person += 1;
		}
	}
	
	snprintf(goleMsg + strlen(goleMsg),length - strlen(goleMsg),"%s%d",",",person);
	strncat(goleMsg,midStr,strlen(midStr));	
	
	if(person < 1)
	{
		memset(goleMsg,'\0',strlen(goleMsg));
	}
	
}

/*发送得分消息*/
void Cpy::sentGoleMsg(char *goleMsg)
{
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator gold_it;
	
	if(goleMsg == NULL)
	{
		return;
	}
	
	for(gold_it = heroGold.begin();gold_it != heroGold.end();gold_it++)
	{
		hero_it = heroId_to_pHero.find(gold_it->first);
		if(hero_it != heroId_to_pHero.end())
		{	
			send_msg(hero_it->second->getFd(),goleMsg); 
		}
	}
}

/*得分处理*/
void Cpy::goleDeal(char *goleMsg,int length)
{
	if(goleMsg == NULL || length <= 0)
	{
		return;
	}
	judgeDieGole();
	judgeAllGole();
	formGoleMsg(goleMsg,length);
}

/*存储分数*/
void Cpy::storeGole(void)
{
	char roomStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyTypId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator gold_it;
	
	if(!dealSerNumStr(cpyId,roomStr,cpyTypId))
	{
		cout<<"the cpyId is error:"<<cpyId<<endl;
		return;
	}
	for(gold_it = heroGold.begin();gold_it != heroGold.end();gold_it++)
	{
		hero_it = heroId_to_pHero.find(gold_it->first);
		if(hero_it != heroId_to_pHero.end())
		{
			hero_it->second->getCpyRecord()->inputPasGold(cpyTypId,gold_it->second);
		}
	}
}

/*用vec装玩家的id*/
void Cpy::mapToVec(vector<string> &herId)
{
	herId.clear();
	{
		std::vector<string> tmp;
		herId.swap(tmp);
	}
	map<string,int>::iterator die_it;
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();die_it++)
	{
		herId.push_back(die_it->first);
	}
}

/*发送此地图上怪物的数目信息*/
void Cpy::sentMonSumMsg(vector<string> &heroId)
{
	Hero *myHero;	
	char *sumMonMsg;	
	int length,i;
	mapNow->formSumMonMsg();	
	sumMonMsg = mapNow->getSumMonMsg();
	length = heroId.size();	
	
	/*发送地图怪物数目信息*/
	for(i = 0;i < length;i++)
	{
		myHero = heroid_to_hero(heroId[i]);
		if(myHero == NULL)
		{
			continue;
		}
		send_msg(myHero->getFd(),sumMonMsg);
	}	
}

/*测试已通过副本层次*/
void Cpy::testCanPas(void)
{	
	set<string>::iterator canEnt_it;	
	cout<<"test the canEntMap begin:"<<endl;
	for(canEnt_it = canEntMapId.begin();canEnt_it != canEntMapId.end();canEnt_it++)
	{
		cout<<"can pass mapId:"<<*canEnt_it<<endl;
	}
	cout<<"test the canEntMap end:"<<endl;
}

/*通过mapId找到map实例*/
Map_Cpy* Cpy::getCpyMap(char *mapId)
{
	map<string,Map_Cpy*>::iterator mapCpy_it; 
	if(mapId == NULL || strlen(mapId) == 0)
	{
		return NULL;
	}
	mapCpy_it = instMapSet.find(mapId);
	if(mapCpy_it == instMapSet.end())
	{
		return NULL;
	}
	return mapCpy_it->second;
}

/*获得地图id容器*/
list<string>& Cpy::getCpyMapSet(void)
{
	return cpyMap;
}

/*重置扩展副本*/
void Cpy::recoverBorrowCpy(void)
{

#if 0
	Map_Cpy *borrowCpy;	
	map<string,Map_Cpy*>::iterator MapCpy_it;
	for(MapCpy_it = instMapSet.begin();MapCpy_it != instMapSet.end();MapCpy_it++)
	{
		borrowCpy = MapCpy_it->second;		
		delete borrowCpy;
		borrowCpy = NULL;
	}	

	instMapSet.clear();	
	{
		std::map<string,Map_Cpy*> tmp;
		instMapSet.swap(tmp);
	}
#endif
	memset(cpyId,'\0',sizeof(cpyId));	
	
	canEntMapId.clear();
	olderMapId.clear();
	
	heroDieCtn.clear();
	{
		std::map<string,int> tmp;
		heroDieCtn.swap(tmp);
	}
	
	heroGold.clear();
	{
		std::map<string,int> tmp;
		heroGold.swap(tmp);
	}
	
	cpyMap.clear();
	
	flgBusy = false;
	
	cpyLimit = NULL;
	
	if(rewardSet != NULL)
	{
		delete rewardSet;
		rewardSet = NULL;
	}
	seconds = 0;
	costTme = 0;
	
	isTeam = false;
}

/*下一波怪刷出前的提示*/
void Cpy::formNextMonMsg(int grops,int timeSecods)
{
	
	char monMsg[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,int>::iterator her_it;
	Hero *myHero;		
	int length,i;	
	
	if(heroDieCtn.empty())
	{
		return;
	}
	
	
	snprintf(monMsg,sizeof(monMsg),"%d,%d,%d,%d",6,11,grops,timeSecods);	
	
	
	for(her_it = heroDieCtn.begin();her_it != heroDieCtn.end();her_it++)
	{
		myHero = heroid_to_hero(her_it->first);
		if(myHero == NULL)
		{
			continue;
		}
		send_msg(myHero->getFd(),monMsg);
	}
}

/*删除地图*/
void Cpy::deleteMap(void)
{
	Map_Cpy *borrowCpy;	
	map<string,Map_Cpy*>::iterator MapCpy_it;
	for(MapCpy_it = instMapSet.begin();MapCpy_it != instMapSet.end();++MapCpy_it)
	{
		borrowCpy = MapCpy_it->second;		
		delete borrowCpy;
		borrowCpy = NULL;
	}
	instMapSet.clear();	
	{
		std::map<string,Map_Cpy*> tmp;
		instMapSet.swap(tmp);
	}
}

/*获得是否为借的标记值*/
bool Cpy::getIsBorrowFlg(void)
{
	return isBorrowFlg;
}


/*设置进入副本的状态*/
void Cpy::setIsTeam(bool _isTeam)
{
	isTeam = _isTeam;
}


/*通关后减去耐力值*/
void Cpy::minusStrlength(void)
{
	Hero* hero;
	map<string,int>::iterator die_it;	
	map<string,Hero*>::iterator hero_it;
	if(heroDieCtn.empty())
	{
		return;
	}
	
	/*如果是黑木崖副本就不扣体力值*/
	if(strncmp(cpyId,"021",3) > 0)
	{
		cout<<"Cpy::minusStrlength the copy is towerLayer copy:"<<cpyId<<endl;
		return ;
	}
	
	char fatigueMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	for(die_it = heroDieCtn.begin();die_it != heroDieCtn.end();++die_it)
	{
		hero_it = heroId_to_pHero.find(die_it->first);
		
		if(hero_it == heroId_to_pHero.end())
		{
			continue;          
		}
		
		memset(fatigueMsg,'\0',sizeof(fatigueMsg));
		
		hero = hero_it->second;
		
		hero->memHero->lastStrength -= cpyLimit->getCostFatigue();
		
		if(hero->memHero->lastStrength < 0)
		{
			hero->memHero->lastStrength = 0;			
		}
		
		sprintf(fatigueMsg,"8,12,%s,%d,%d",hero->getIdentity(),hero->memHero->lastStrength,hero->memHero->fatigueUpperVal);
		
		send_msg(hero->getFd(),fatigueMsg);
	}
}

/*黑木崖副本通关数据处理*/
bool Cpy::passTowerLayer(void)
{
	TowerLayerRecord* towerLayerRecord;
	map<string,Hero*>::iterator hero_it;
	map<string,int>::iterator die_it;
	Hero * hero;		
	
	
	
	if(strncmp(cpyId,"021",3) <= 0)
	{
		return false;
	}
	
	die_it = heroDieCtn.begin();
	hero_it = heroId_to_pHero.find(die_it->first);
	if(hero_it == heroId_to_pHero.end())
	{
		cout<<"the heroId is error:"<<die_it->first<<endl;
		return false;
	}
	
	hero = hero_it->second;	
	towerLayerRecord = hero->getTowerLayerRecord();
	
	if(towerLayerRecord == NULL)
	{
		cout<<"Cpy::passTowerLayer the towerLayerRecord is NULL:"<<hero->getIdentity()<<endl;
		return false;
	}
	towerLayerRecord->changeLayerId();
	
	char *nowLayerId = hero->memHero->nowLayerId;
	char *nowTowerId = hero->memHero->nowTowerId;
	
	//单人通过青衣楼第一层
	cout<<"nowTowerId:"<<nowTowerId<<endl;
	cout<<"nowLayerId:"<<nowLayerId<<endl;
	if(strcmp(nowTowerId,"tower_001") == 0 && strcmp(nowLayerId,"layer_002")==0)	//1
	{
		hero->updataSingleTarget(0,4);
	}
	else if(strcmp(nowTowerId,"tower_003") == 0 && strcmp(nowLayerId,"layer_001")==0)  //10
	{
		hero->updataSingleTarget(3,5);
	}
	else if(strcmp(nowTowerId,"tower_007") == 0 && strcmp(nowLayerId,"layer_001")==0)		//30
	{
		hero->updataSingleTarget(5,8);
	}
	
	return true;
}

//刷记录
void Cpy::recordLessTme()
{
	if(isTeam || heroDieCtn.empty())
	{
		cout<<"Cpy::recordLessTme() the joinTeam is not suit:"<<endl;
		return;
	}
	if(!cpyLimit)
	{
		cout<<"Cpy::recordLessTme() the cpyLimit is NULL:"<<endl;
		return;
	}
	cpyLimit->recordLessTme((heroDieCtn.begin()->first).c_str(),costTme);
}
		
	
		
	
	
