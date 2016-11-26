/************************************************************
	文件名：map_inform.cpp
	文件作用：类Map_Inform类的属性和方法的实现
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#include"user_role_manage_assist.h"
#include"timerContainer.h"
#include"monsterBase.h"
#include"takeGoods.h"
#include"map_cpy.h"
#include <sstream>
#include"bottle.h"
#include"trap.h"
#include"cpy.h"

extern TimerContainer<Map_Inform*> *mapThkContain;

Map_Cpy::Map_Cpy(char *_mapId,char *_mapFilePath,char *_mapName,\
int _mapWidth,int _mapHeight,int _row,int _col,int _baseDigst,\
Point _entPt,Point _outPt,Point _tribesPt,Point _religionPt,\
Point _rangerPt,map<string,MonsterBase *>& _monId_connect_monster,\
vector<BruGro> _bruGropVec,vector<int>_bruEachTme,\
map<string,const jumpId_infor*>&_jumpId_connect_jumpInfo,\
map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
int _sumMon,int _warType,int _changePkType,int _mapType,\
int _campEntFlag,int _levelLowerLimit,int _levelUpperLimit)\
:Map_Inform(_mapId,_mapFilePath,_mapName,_mapWidth,_mapHeight,_row,_col,\
_baseDigst,_entPt,_outPt,_tribesPt,_religionPt,_rangerPt,\
_monId_connect_monster,_jumpId_connect_jumpInfo,_takeGoodsMap,\
_botInMap,_trapInstMap,_dishPtSet,_centerPt,_radius,_flgCpy,_warType,_changePkType,_mapType,\
_campEntFlag,_levelLowerLimit,_levelUpperLimit)
{
	
	bruGropVec = _bruGropVec;
	
	bruEachTme = _bruEachTme;
	
	takeGoodsMap = _takeGoodsMap;
	
	index = 0;
	
	cpy = NULL;
	
	ctnBru = 0;
	
	pasFlg = true;
	
	sumMon = _sumMon;
	
	lveSumMon = sumMon;	
	
	goNext = true;			

#if 0	
	if(strncmp(mapId, "ectype_map_034", 14) == 0)
	{
		// cout<<"test the tower monster begin:"<<endl;
		// testMapInfor();
		// cout<<"test the tower monster end:"<<endl;
		return;
	}
#endif	
}

/*析构函数*/
Map_Cpy::~Map_Cpy(void)     
{
	cpy = NULL;	
}

/*地图思考回调函数*/
void Map_Cpy::mapThkCalBak(void)
{

#if 0
	if(strncmp(mapId, "ectype_map_034", 14) == 0)
	{
		cout<<"@@Tory It's tower defence instancing"<<endl;
		return;
	}
#endif
	if(!pasFlg)
	{
		return;
	}	
	
	/*检测副本是否可以到达下一层*/
	getNextStage();  
	
	stopThk();	
	

	/*如果地图已经暂停思考*/
	if(flgThk == 1)
	{
		return;
	}	
	
	bruMonByGroFun(index);
	bruMapFun();	
}
	
/*刷新地图信息函数*/
void Map_Cpy::bruMapFun(void)
{	
	bruMonByGroMod();	
}
	
/*进入副本下一层以及回收副本*/
void Map_Cpy::getNextStage(void)
{
	if(index == bruGropVec.size() - 1 && lveSumMon == 0)
	{
			if(cpy != NULL)
			{
				/*已通关*/
				if(cpy->PassCpyJudge(mapId))
				{
					if(pasFlg)
					{
						/*add by chenzhen 201302211702 to void pass the cpy but attacked by trap*/
						stopTrapThk();
						
						cout<<"Map_Cpy::getNextStage it is pass the copy:"<<endl;
						// cpy->goleDeal();						
						/*add chenzhen 20130321 减去耐力值*/
						cpy->minusStrlength();
						
						cpy->passRecord();
						cpy->recordLessTme();
						pasFlg = false;
						cpy->initRewardSet();	
					}
								
				}
				else
				{
					if(goNext)
					{
						/*下一层*/
						cpy->inPutCanEntset();
						goNext = false;
					}
				}			
				
			}
			
	}
	// cpy->recoverCpy();
}

/*复制地图信息，传参数是为了区分副本中的怪的id*/
Map_Cpy* Map_Cpy::copyMap(int roomNum, char *cpyId)
{
	map<string,const jumpId_infor*> newjumpId_connect_jumpInfo;
	char newMapId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,MonsterBase*> newMonInt;
	map<string,TakeGoods*> _takeGoodsMap;		
	map<string,Bottle*> _botInMap;	
	map<string,Trap*> _trapInstMap;
	vector<BruGro> _bruGropVec;	
	Map_Cpy *newMap;	
		
		
	strncpy(newMapId,mapId,strlen(mapId));
	
	if(cpyId != NULL)
	{	
		strncat(newMapId,"_",strlen("_"));
		strncat(newMapId,cpyId,strlen(cpyId));
	}
	else
	{
		strncat(newMapId,"_",strlen("_"));	
		appendNum(newMapId,roomNum,4);
	}

	copyMapMon(newMonInt,newMapId,newjumpId_connect_jumpInfo);
	
	/*复制刷怪模式*/
	copyBruGropVec(_bruGropVec,newMapId);
	
	/*复制瓶罐函数*/
	copyBotInMap( _botInMap,newMapId);
	
	/*复制可摘取物品*/
	copyTakeGoods(_takeGoodsMap,newMapId);
	
	/*复制陷阱*/
	copyTrapVec(_trapInstMap,newMapId);
	
	/*调用构造函数，生成一个地图实例*/
	newMap = new Map_Cpy(newMapId,mapFilePath,mapName,mapWidth,mapHeight,\
	row,col,baseDigst,entPt,outPt,tribesPt,religionPt,rangerPt,newMonInt,\
	_bruGropVec,bruEachTme,newjumpId_connect_jumpInfo,_takeGoodsMap,\
	_botInMap,_trapInstMap,dishPtSet,centerPt,radius,flgCpy,sumMon,warType,changePkType,\
	mapType,campEntFlag,levelLowerLimit,levelUpperLimit);

	
	/*设置障碍信息*/
	newMap->setMapHinder(map_hinder);
	
	/*初始化九宫格*/
	newMap->InitBox();
	
	/*设置此地图上怪物的地图实例指针*/
	newMap->setMonMap();
	
	/*设置瓶罐地图实例指针*/
	newMap->setBotMap();
	
	/*设置陷阱地图实例指针*/
	newMap->setTrapMap();
	
	/*设置可摘取地图实例指针*/
	newMap->setTakeGoodsMap();

	return newMap;
}

/*设置副本值*/
void Map_Cpy::SetCpy(Cpy *_cpy)
{
	/*只设置一次值*/
	if(cpy == NULL && _cpy != NULL )         
	{
		cpy = _cpy;
	}
}

/*重置整张地图信息*/
void Map_Cpy::initMap(void)
{		
	stopThk();
	
	initMonLvMager();	
	
	initGroMon();	
	
	/*先停*/
	ev_timer_stop(loops,&timer);

		
	flgThk = -1;	
	
	/*清空九宫格中的内容*/
	clearBox();
	
	index = 0;
	
	ctnBru = 0;
	
	pasFlg = true;
	
	lveSumMon = sumMon;
	
	goNext = true;
	
	/*重置陷阱信息*/
	initTrap();
	
	/*重置瓶罐信息*/
	initBot();
	
	clearDropMap();
	
	/*情调宴席*/
	clearDish();
	
	/*重置可摘取物品*/
	initTakeGoods();
	
}

/*重置批次刷怪容器*/
bool Map_Cpy::initGroBru(void)
{
	int length,i;
	length = bruGropVec.size();
	for(i = 0;i < length;i++)
	{
		bruGropVec[i].init();
	}
}

/*下一批怪刷出条件判断*/
bool Map_Cpy::judgeGroDieOut(void)
{
	if(bruGropVec[index].judDieCtn())
	{
		return true;
	}
	return false;
}

/*所有批次是否刷完*/
bool Map_Cpy::judgeBruGroIndex(void)
{
	if(index < bruGropVec.size())
	{
		return true;
	}
	return false;
}

/*批次时间是否到*/
bool Map_Cpy::judgeBruGroTmeOut(void)
{
	//cout<<"index:"<<index<<endl;
	if(index < bruGropVec.size() && !bruEachTme.empty() && ctnBru >= bruEachTme[index])
	{
		ctnBru = 0;
		return true;
	}
	ctnBru++;
	return false;
}

/*按批次模式刷怪接口*/
void Map_Cpy::bruMonByGroMod(void)
{	
	bool flgDieOutIndex,flgIndex,tmeFlg;	
	
	/*如果只有一批怪的情况*/
	if(bruEachTme.empty())
	{
		return;
	}
	
	/*判断下标是否越界*/
	flgIndex = judgeBruGroIndex();
	
	/*判断上批是否被杀光*/
	flgDieOutIndex = judgeGroDieOut();	
	if(flgDieOutIndex && flgIndex )
	{		
		/*判断下批时间刷出是否已到*/
		tmeFlg = judgeBruGroTmeOut();
		
		/*发送下一波怪物即将刷出消息*/
		if(cpy != NULL && index < bruGropVec.size() - 1)
		{
			int delay = bruEachTme[index] - ctnBru * MAP_THINK_TIME;
			/*稍稍延迟一下*/
			if(delay >= 0 && delay <= 5)
			{
				cpy->formNextMonMsg(index + 2,delay); //这里总是core, 先注释掉 benliao,<已经改好，chenzhen，12.25>
			}
		}
		
		if(tmeFlg)
		{
			index++;
			if(judgeBruGroIndex()) //add by chenzhen 201302261713 to void core
			{
				bruMonId_it = bruGropVec[index].monId.begin();
				bruMonByGroFun(index);
			}
		}
	}	
}
	
/*副本具体刷怪函数*/
void Map_Cpy::bruMonByGroFun(int _index)
{	
	map<string,MonsterBase*>::iterator monInst_it;
	MonsterBase *monBru;
	int i = 0;
	
	if(bruGropVec.empty())
	{
		cout<<"Map_Cpy::bruMonByGroFun bruGropVec is empty:"<<endl;
		return;
	}
	
	for(;bruMonId_it != bruGropVec[_index].monId.end();)
	{
		monBru = NULL;
		monInst_it = monId_connect_monster.find(*bruMonId_it);
		if(monInst_it == monId_connect_monster.end())
		{
			/*找不到的情况*/
			++bruMonId_it;
			continue;
		}
		
#if 1
		/*任务怪*/
		if(monInst_it->second->getOwnerAttriType() == 3 || monInst_it->second->getOwnerAttriType() == 4)
		{
			continue;
		}
#endif		


#if 1
		/*召唤怪*/
		if(monInst_it->second->getIsCallType())
		{
			continue;
		}
#endif		
		monBru = monInst_it->second;		
		monBru->brushMon();			
		++bruMonId_it;	
		++i;
	}
	
//	cout<<"the brush monster sum:"<<i<<" index:"<<index<<endl;
}
		
/*复制刷怪批次*/
void Map_Cpy::copyBruGropVec(vector<BruGro> &_bruGropVec,char *newMap)
{
	char newIntId[SHOR_MID_VALUE_LENGTH + 1]= {'\0'};
	set<string>::iterator bruMonId_it;	
	int length,i;		  
	
	length = bruGropVec.size();
	
	for(i = 0;i < length;i++)
	{
		set<string>monId;
		for(bruMonId_it = bruGropVec[i].monId.begin();bruMonId_it != bruGropVec[i].monId.end();bruMonId_it++)
		{	
			strncpy(newIntId,newMap,strlen(newMap));
			strncat(newIntId,"_",strlen("_"));
			strncat(newIntId,(*bruMonId_it).c_str(),strlen((*bruMonId_it).c_str()));		
			monId.insert(newIntId);
			memset(newIntId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		}
		BruGro bruGro(monId);
		_bruGropVec.push_back(bruGro);
	}
}
		
		
/*怪物死亡*/
void Map_Cpy::GromonDead(char *monId)
{
	bruGropVec[index].monDie(monId);
}

/*重置按批刷怪模式*/
void Map_Cpy::initGroMon(void)
{
	int length,i;		  
	length = bruGropVec.size();
	for(i = 0;i < length;i++)
	{
		bruGropVec[i].init();
	}
}


/*第一次进入副本*/
void Map_Cpy::fristEntMap(void)
{	
//	testGroMonId();
	
	if(!bruGropVec.empty())
	{
		bruMonId_it = bruGropVec[index].monId.begin();
	}
	
	flgThk = -1;
	
	bruMonByGroFun(index);
	
	initTimer();
	
	/*刷出瓶罐信息*/
	brushBotMsg();
	
	/*刷出陷阱信息*/
	brushTrapMsg();
	
	/*刷出可摘取信息*/
	bruTakeMsg();
}

/*暂停此地图上已刷出怪的思考*/
void Map_Cpy::stopAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		if(mon_it->second->getLifeStation())
		{
			mon_it->second->stopThk();
		}
	}
}

/*暂停此地图上已刷出怪的思考*/
void Map_Cpy::reSetAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		if(mon_it->second->getLifeStation())
		{
			mon_it->second->resetTimer();
		}
	}
}

/*测试各刷怪批次怪物id*/	
void Map_Cpy::testGroMonId(void)
{
	int length,i;
	
	cout<<"test the map :"<<mapId<<" groupBruMonId begin:"<<endl;
	
	length = bruGropVec.size();
	
	for(i = 0;i < length; i++)
	{
		cout<<"the gruopNum :"<<i<<" test begin"<<endl;
		// bruGropVec[i].testPrint();
		testLveMager(bruGropVec[i].monId);
		cout<<"the gruopNum :"<<i<<" test end"<<endl;
	}
	cout<<"test the map :"<<mapId<<" groupBruMonId end:"<<endl;
}

/*测试各刷怪批次时间*/	
void Map_Cpy::testGroCtn(void)
{

	int length,i;
	length = bruEachTme.size();
	cout<<"Map_Cpy::testGroCtn test the map :"<<mapId<<" bruEachTme begin:"<<endl;
	for(i = 0;i < length;i++)
	{
		cout<<"the groupNum is :"<<i<<" the ctn:"<<bruEachTme[i]<<endl;
	}
	cout<<"Map_Cpy::testGroCtn test the map :"<<mapId<<" bruEachTme end:"<<endl;
}

/*测试打印刷怪时间容器*/
void Map_Cpy::testBruEachTme(void)
{
	int length,i;		  
	length = bruEachTme.size();
	cout<<"test the map :"<<mapId<<"  the bruEachTme begin:"<<endl;
	for(i = 0;i < length;i++)
	{
		cout<<"the :"<<i<<" gruopNum the brushTme is:"<<bruEachTme[i]<<endl;
	}
	cout<<"test the map :"<<mapId<<"  the bruEachTme end:"<<endl;
}


/*副本回收标志*/
bool Map_Cpy::recoverCpy(void)
{
	if(cpy == NULL)
	{
		return false;
	}
	cpy->recoverCpy();
	
	if(!cpy->getFlgBusy())
	{
		if(cpy->getIsBorrowFlg())
		{
			cpy->deleteMap();
		}
		return true;
	}
	
	return false;
}

/*测试打印副本重置信息*/
void Map_Cpy::testMapInfor(void)
{
	testGroMonId();
	testGroCtn();
	cout<<"index:"<<index<<endl;
	cout<<"ctnBru:"<<ctnBru<<endl;
	testMonsterWait();
}

/*生成怪物数目信息*/
void Map_Cpy::formSumMonMsg(void)
{
	int costSecond;
	
	if(cpy == NULL)
	{
		return;
	}
	memset(sumMonMsg,'\0',SHOR_MID_VALUE_LENGTH + 1);
	
	costSecond = cpy->getTmeSecond();
	
	snprintf(sumMonMsg,sizeof(sumMonMsg),"%d%s%d%s%d%s%d%s%d",\
			2,",",7,",",sumMon,",",lveSumMon,",",costSecond);
}

/*生成怪物数目信息*/
char* Map_Cpy::getSumMonMsg(void)	
{
	formSumMonMsg();
	return sumMonMsg;
}

/*更新副本怪物数目*/
void Map_Cpy::sentSumMonMsg(void)
{
	if(cpy == NULL)
	{
		return;
	}
	cpy->sentLveMonMsg();
}

/*杀死一个怪*/
void Map_Cpy::killOneMon(void)
{
	if(lveSumMon > 0)
	{
		lveSumMon -= 1;
		cout<<"lveSumMon:"<<lveSumMon<<endl;
	}
}

/*测试怪物存活次数*/
void Map_Cpy::testLveMager(set<string> &monId)
{
	set<string>::iterator monId_it;
	MonsterBase *lveMon;
	int sums = 0;
	cout<<"the num of the monsterId:"<<monId.size()<<endl;
	for(monId_it = monId.begin();monId_it != monId.end();monId_it++)
	{
		lveMon = getMonsterObj(const_cast<char *>((*monId_it).c_str()));
		if(lveMon == NULL)
		{
			cout<<"can not find the monsterId:"<<*monId_it<<endl;
			continue;
		}
		sums += lveMon->testLveManger();
	}
	cout<<"the monsterSum is :"<<sums<<endl;
	cout<<"test oneObject groupGruMonId end:"<<endl;
	
}

/*地图暂停思考函数*/
void Map_Cpy::stopThk(void)
{
	set<string>::iterator lve_it;
	MonsterBase *mon;
	
	/*如果地图没人*/
	if(heroFd.size() == 0)
	{
		/*如果此地图的怪物已经暂停思考*/
		if(flgThk == 1)
		{
			return;
		}		
		/*暂停此地图上已刷出怪的思考*/		
		stopAllLveMonThk();
		
		/*暂停陷阱计时器*/
		stopTrapThk();
		
		/*设置地图思考标记值为怪物已经暂停思考*/
		flgThk = 1; 
		
		return;
	}
	else
	{
		/*如果怪物已经被暂停思考*/
		if(flgThk == 1)
		{
			/*启动怪物思考*/
			reSetAllLveMonThk();
			
			/*启动陷阱计时器*/
			reSetTrapThk();
		}
		/*设置地图思考标记值为怪物在已经思考*/
		flgThk = 0;
	}
}

void Map_Cpy::getMonObj(vector< vector<string> > &mon_vec)      //tory add
{
        vector<BruGro>::iterator iter = bruGropVec.begin();
        for(iter; iter != bruGropVec.end(); iter++)
        {
                vector<string> vec;
                set<string>::iterator it = (*iter).monId.begin();
                for(it; it != (*iter).monId.end(); it++)
                {
                        vec.push_back(*it);
                }
                mon_vec.push_back(vec);
        }

}

/*返回副本势力指针*/
Cpy* Map_Cpy::getCpy(void)
{
	return cpy;
}



