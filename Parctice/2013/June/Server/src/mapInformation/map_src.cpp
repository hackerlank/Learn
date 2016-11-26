/************************************************************
	文件名：map_inform.cpp
	文件作用：类Map_Inform类的属性和方法的实现
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#include"map_src.h"
#include"monsterBase.h"
#include <sstream>
#include"user_role_manage_assist.h"
#include"command_other_function_all_over.h"
#include"data_structure_struct.h"
#include"timerContainer.h"
#include"vipBaleRoomLimit.h"
#include"partyRoomLimit.h"
#include"partyBaseCampLimit.h"
extern TimerContainer<Map_Inform*> *mapThkContain;
Map_Src::Map_Src(char *_mapId,char *_mapFilePath,char *_mapName,\
int _mapWidth,int _mapHeight,int _row,int _col,int _baseDigst,\
Point _entPt,Point _outPt,Point _tribesPt,Point _religionPt,\
Point _rangerPt,map<string,MonsterBase *>& _monId_connect_monster,\
map<string,const jumpId_infor*>&_jumpId_connect_jumpInfo,\
map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
int _warType,int _changePkType,int _mapType,int _campEntFlag,\
int _levelLowerLimit,int _levelUpperLimit):Map_Inform(_mapId,\
_mapFilePath,_mapName,_mapWidth,_mapHeight,_row,_col,_baseDigst,\
_entPt,_outPt,_tribesPt,_religionPt,_rangerPt,\
_monId_connect_monster,_jumpId_connect_jumpInfo,\
_takeGoodsMap,_botInMap,_trapInstMap,_dishPtSet,_centerPt,_radius,_flgCpy,_warType,\
_changePkType,_mapType,_campEntFlag,_levelLowerLimit,_levelUpperLimit)
{
	isVipRom = false;
	isVipRomBusy = false;
	vipRoom = NULL;
	vipRoomNum = -1;
	
	partyRoom = NULL;
	partyRoomNum = -1;
	isPartyRom = false;
	isPartyRomBusy = false;
	
	campRoom = NULL;
	campRoomNum = -1;
	isCampRom = false;
	isCampRomBusy = false;
	
}

/*地图思考回调函数*/
void Map_Src::mapThkCalBak(void)
{
	if(heroFd.size() == 0 && flgThk == -1)
	{
		return;
	}
	
	if(heroFd.size() > 0 && flgThk == -1)
	{
		entMap();
	}
	
	stopThk();	
	
	/*如果地图已经暂停思考*/
	if(flgThk == 1)
	{
		return;
	}	
	
	bruMonFun();	
}

/*刷怪接口*/
void Map_Src::bruMonFun(void)
{		
	/*一次刷一个,直到刷完为止*/
	brushRedMon();
	
	// if(!ctlTme(8))
	// {
		// return;
	// }		
}

/*第一次进入场景刷怪*/
void Map_Src::entMap(void)
{	

#if 0

	/*测试阵营资源涮出情况*/
	brushTakeSource(10,true);

#endif

#if 0

	/*测试雕像怪*/
	initMonStatuary();
	
#endif	

	loopBruMon(true);
	
	/*刷出瓶罐信息*/
	brushBotMsg();
	
	/*刷出陷阱信息*/
	brushTrapMsg();	
	
	/*刷出可摘取物品*/
	bruTakeMsg();
	
}

/*析构函数*/
Map_Src::~Map_Src(void)      
{
	vipRoom = NULL;
	partyRoom = NULL;
	campRoom = NULL;

}

/*控制刷怪频率*/
bool Map_Src::ctlTme(int lveTme)
{
	ctnReBruDieMon++;
	
	if(ctnReBruDieMon % lveTme == 0)
	{
		ctnReBruDieMon = 0;
		return true;
	}
	return false;
}


/*循环刷怪函数*/
void Map_Src::loopBruMon(bool isFirst)
{

	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		
		if(strcmp(mon_it->second->getType(),"AttRedMon") == 0)
		{
			continue;
		}
#if 1		
		/*任务怪*/
		if(mon_it->second->getOwnerAttriType() == 3 || mon_it->second->getOwnerAttriType() == 4)
		{
			continue;
		}
#endif

#if 1
		/*召唤怪*/
		if(mon_it->second->getIsCallType())
		{
			continue;
		}
#endif
		
		if(mon_it->second->getLifeStation())
		{
			mon_it->second->brushMon();
			
			if(mon_it->second->getOwnerAttriType() == 3)
			{
				cout<<"Map_Src::loopBruMon(bool isFirst) begin:"<<mon_it->second->getIdentity()<<endl;
				cout<<"mon_it->second->getBshMsg:"<<mon_it->second->getBshMsg()<<endl;
				cout<<"Map_Src::loopBruMon(bool isFirst) end:"<<mon_it->second->getIdentity()<<endl;
			}
		}
	}
}
	

/*暂停此地图上已刷出怪的思考*/
void Map_Src::stopAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->stopThk();
	}
}

/*暂停此地图上已刷出怪的思考*/
void Map_Src::reSetAllLveMonThk(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->resetTimer();
	}
}



/*复制地图信息，传参数是为了区分副本中的怪的id*/
Map_Src* Map_Src::copyMap(int roomNum)
{
	map<string,MonsterBase*> newMonInt;
	 
	map<string,const jumpId_infor*> newjumpId_connect_jumpInfo;
	
	map<string,Bottle*> _botInMap;
	
	map<string,TakeGoods*> _takeGoodsMap;
	
	map<string,Trap*> _trapInstMap;
	
	char newMapId[100] = {0};
	
	Map_Src *newMap;
	
	strncpy(newMapId,mapId,strlen(mapId));
	
	strncat(newMapId,"_",strlen("_"));
	
	appendNum(newMapId,roomNum,4);	//生成新地图id
	
	copyMapMon(newMonInt,newMapId,newjumpId_connect_jumpInfo);
	
	
	/*复制瓶罐函数*/
	copyBotInMap( _botInMap,newMapId);
	
	/*复制可摘取物品*/
	copyTakeGoods(_takeGoodsMap,newMapId);
	
	/*复制陷阱*/
	copyTrapVec(_trapInstMap,newMapId);
	
	/*调用构造函数，生成一个地图实例*/
	newMap = new Map_Src(newMapId,mapFilePath,mapName,\
	mapWidth,mapHeight,row,col,baseDigst,entPt,outPt,tribesPt,\
	religionPt,rangerPt,newMonInt,newjumpId_connect_jumpInfo,\
	_takeGoodsMap,_botInMap,_trapInstMap,dishPtSet,centerPt,radius,flgCpy,warType,\
	changePkType,mapType,campEntFlag,levelLowerLimit,levelUpperLimit);
							
	/*设置障碍信息*/
	newMap->setMapHinder(map_hinder);
	
	/*初始化九宫格*/
	newMap->InitBox();
	
	/*设置此地图上怪物的地图实例指针*/
	newMap->setMonMap();
	
	/*设置瓶罐地图实例指针*/
	newMap->setBotMap();
	
	/*设置瓶罐地图实例指针*/
	newMap->setTrapMap();
	
	/*设置可摘取地图实例指针*/
	newMap->setTakeGoodsMap();
	
	return newMap;
}

/*重置整张地图信息*/
void Map_Src::initMap(void)
{		
	/*暂停计时器*/
	ev_timer_stop(loops,&timer);
	
	/*重置计时器标记值*/
	flgThk = -1;	
	
	/*重置陷阱信息*/
	initTrap();
	
	/*重置瓶罐信息*/
	initBot();
	
	/*暂停地图上所有东西的定时器*/
	stopThk();		
	
	/*重置怪物存活和刷出时间属性*/
	initMonLvMager();	
	
	/*清掉地图里面的采集物*/
	initTakeGoods();	
	
	/*清空九宫格中的内容*/
	clearBox();
	
	/*包厢房间置为空闲*/
	isVipRomBusy = false;
	
	/*帮派房间置为空闲*/
	isPartyRomBusy = false;
	
	/*帮派大本营房间置为空闲*/
	isCampRomBusy = false;
	
	/*删除地图上所有还没有捡的掉落物品*/
	clearDropMap();	
	
	/*清掉宴席*/
	clearDish();
}

/*重置怪物数据*/
void Map_Src::initMon(void)
{	
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->die();
	}
}

/*地图暂停思考函数*/
void Map_Src::stopThk(void)
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

/*生成怪物数目信息*/
char* Map_Src::getSumMonMsg(void)	
{
	return NULL;
}

/*获得是否为vip包间标志*/
bool Map_Src::getIsVipRom(void)
{
	return isVipRom;
}

/*获得是否为设置*/
void Map_Src::setIsVipRom(bool _busy)
{
	isVipRom = _busy;
	
	ctnTheVipRoomNum();
}

/*获得vip包间是否被占用标志*/
bool Map_Src::getIsVipRomBusy(void)
{
	return isVipRomBusy;
}

/*获得vip包间是否被占用标志*/
void Map_Src::setIsVipRomBusy(bool _busy)
{
	isVipRomBusy = _busy;
}


/*设置vip包厢限制类实例指针*/
void Map_Src::setVipRoom(VipBaleRoomLimit *_vipRoom)
{
	if(_vipRoom == NULL)
	{
		cout<<"set the vipRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isVipRom)
	{
		cout<<"the map is not vipMapId:"<<mapId<<endl;
		vipRoom = NULL;
		return;
	}		
	vipRoom = _vipRoom;
}

/*包厢场景地图思考函数*/
bool Map_Src::vipCallBack(void)
{
	if(heroFd.empty())
	{
		if(vipRoom == NULL)
		{
			return true;
		}
		vipRoom->recoverVipRom(vipRoomNum);
		return true;
	}
	return false;
}


/*包厢场景地图思考函数*/
bool Map_Src::partyCallBack(void)
{
	if(heroFd.empty())
	{
		if(partyRoom == NULL)
		{
			return true;
		}
		partyRoom->recoverPartyRom(partyRoomNum);
		return true;
	}
	return false;
}

/*进入vip包厢*/
void Map_Src::enterVipRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}

/*进入帮派包厢*/
void Map_Src::enterPartyRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}

/*计算得到vip包间号*/
void Map_Src::ctnTheVipRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	vipRoomNum = atoi(numStr);
}

/*退出vip包厢*/
void Map_Src::exitVipRoom(vector<string> &heroVec)
{
	if(heroVec.empty() || vipRoom == NULL)
	{
		cout<<"the heroVec is empty or the vipRoom is NULL:"<<mapId<<endl;
		return;
	}
	vipRoom->exitVipRoomAsist(heroVec);
}


/*获得是否为帮派包间标志*/
bool Map_Src::getIsPartyRom(void)
{
	return isPartyRom;
}

/*设置是否为帮派地图*/
void Map_Src::setIsPartyRom(bool _busy)
{
	isPartyRom = _busy;
	
	ctnThePartyRoomNum();
}

/*获得vip包间是否被占用标志*/
bool Map_Src::getIsPartyRomBusy(void)
{
	return isPartyRomBusy;
}

/*获得vip包间是否被占用标志*/
void Map_Src::setIsPartyRomBusy(bool _busy)
{
	isPartyRomBusy = _busy;
}


/*计算得到帮派包间号*/
void Map_Src::ctnThePartyRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	partyRoomNum = atoi(numStr);
}

/*设置帮派包厢限制类实例指针*/
void Map_Src::setPartyRoom(PartyRoomLimit *_partyRoom)
{
	if(_partyRoom == NULL)
	{
		cout<<"set the partyRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isPartyRom)
	{
		cout<<"the map is not partyMapId:"<<mapId<<endl;
		partyRoom = NULL;
		return;
	}		
	partyRoom = _partyRoom;
}

PartyRoomLimit* Map_Src::getPartyRoomLimit(void)
{
	return partyRoom; 
}

/*设置帮派大本营包厢限制类实例指针*/
void Map_Src::setCampRoom(PartyBaseCampLimit *_campRoom)
{
	if(_campRoom == NULL)
	{
		cout<<"set the partyRoom is error NULL:"<<mapId<<endl;
		return;
	}
	if(!isCampRom)
	{
		cout<<"the map is not campMapId:"<<mapId<<endl;
		campRoom = NULL;
		return;
	}		
	campRoom = _campRoom;
}

/*获得帮派包间是否被占用标志*/
bool Map_Src::getIsCampRomBusy(void)
{
	return isCampRomBusy;
}

/*获得帮派包间是否被占用标志*/
void Map_Src::setIsCampRomBusy(bool _busy)
{
	isCampRomBusy = _busy;
}

/*计算得到帮派大本营包间号*/
void Map_Src::ctnTheCampRoomNum(void)
{
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	strncpy(numStr,mapId + strlen(mapId) - 4,4);
	campRoomNum = atoi(numStr);
}

/*退出帮派大本营包厢*/
void Map_Src::exitCampRoom(vector<string> &heroVec)
{
	if(heroVec.empty() || campRoom == NULL)
	{
		cout<<"the heroVec is empty or the campRoom is NULL:"<<mapId<<endl;
		return;
	}
	campRoom->exitCampRoomAsist(heroVec);
}


/*获得是否为帮派大本营包间标志*/
bool Map_Src::getIsCampRom(void)
{
	return isCampRom;
}

/*设置是否为帮派大本营地图*/
void Map_Src::setIsCampRom(bool _busy)
{
	isCampRom = _busy;
	
	ctnTheCampRoomNum();
}


/*帮派大本营包厢场景地图思考函数*/
bool Map_Src::campCallBack(void)
{
	if(heroFd.empty())
	{
		if(campRoom == NULL)
		{
			return true;
		}
		campRoom->recoverCampRom(partyRoomNum);
		return true;
	}
	return false;
}

/*进入帮派大本营包厢*/
void Map_Src::enterCampRoomFirst(void)
{
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}


/*系统请客辅助函数*/
bool Map_Src::systemTreat(TakeGoods *newDish)
{
	
	cout<<"Map_Src::systemTreat begin:"<<endl;
	
	if(newDish == NULL)
	{
		return false;
	}
	
	if(partyRoom == NULL)
	{
		return false;
	}
	
	/*add chenzhen 20130325 设置饭桌图片*/
	newDish->setIsDished(true);
	
#if 0	
	if(partyRoom->getActiveFlg())
	{
		cout<<"the time of treat is on:"<<endl;
		
		newDish->setDishState(2);
	}

	else
	{
		cout<<"the time of treat is not on:"<<endl;
		
		newDish->setDishState(1);
	}	
#endif		
	newDish->brushMsg();
	
	cout<<"Map_Src::systemTreat end:"<<endl;
	
	return true;
}
