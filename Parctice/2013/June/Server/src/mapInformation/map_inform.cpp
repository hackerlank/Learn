/************************************************************
	文件名：map_inform.cpp
	文件作用：类Map_Inform类的属性和方法的实现
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#include"command_other_function_all_over.h"
#include"user_role_manage_assist.h"
#include"data_structure_struct.h"
#include"monsterActiveBoss.h"
#include"timerContainer.h"
#include"monsterBase.h"
#include"map_inform.h"
#include"commodity.h"
#include"bottle.h"
#include <sstream>
#include"wagon.h"
#include"cpy.h"
#include"pet.h"
#include"trap.h"
#include"pick.h"
#include"equipment.h"
#include"monsterByHero.h"
#include"statuaryHero.h"
#include"monsterStatuary.h"

extern struct ev_loop *loops;
extern map<string,Equipment*> dropEquipMent;
extern map<string, Hero*> heroId_to_pHero;
extern TimerContainer<Map_Inform*> *mapThkContain;
extern map<string,Wagon*> wagonInstMap;
extern map<string,Pet*>id_to_activePet;
extern map<string,Pick*> goods_to_hero; 
extern map<string,TakeGoods*> takeGoodsConfMap;
extern Hero *pg_hero;
extern map<string,StatuaryHero*> statuaryTypeToStatuaryHero;

Map_Inform::Map_Inform(char *_mapId,char *_mapFilePath,char *_mapName,\
int _mapWidth,int _mapHeight,int _row,int _col,int _baseDigst,\
Point _entPt,Point _outPt,Point _tribesPt,Point _religionPt,\
Point _rangerPt,map<string,MonsterBase *>& _monId_connect_monster,\
map<string,const jumpId_infor*>&_jumpId_connect_jumpInfo,\
map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
int _warType,int _changePkType,int _mapType,int _campEntFlag,\
int _levelLowerLimit,int _levelUpperLimit)
{
	memset(mapId,'\0',sizeof(mapId));
	memset(mapFilePath,'\0',sizeof(mapFilePath));
	memset(mapName,'\0',sizeof(mapName));
	
	strncpy(mapId,_mapId,strlen(_mapId));	
	strncpy(mapFilePath,_mapFilePath,strlen(_mapFilePath));	
	strncpy(mapName,_mapName,strlen(_mapName));
	
	
	mapWidth=_mapWidth;
	mapHeight=_mapHeight;
	row=_row;
	col=_col;
	baseDigst=_baseDigst;
	
	box=NULL;
	
	entPt = _entPt;       
	
	outPt = _outPt; 
	
	tribesPt = _tribesPt;
	
	religionPt = _religionPt;
	
	rangerPt = _rangerPt;
	
	
	monId_connect_monster = _monId_connect_monster;
	
	jumpId_connect_jumpInfo = _jumpId_connect_jumpInfo;
	
	
	flgThk = -1;
	
	takeGoodsMap = _takeGoodsMap;		
	
	botInMap = _botInMap;
	
	trapInstMap = _trapInstMap;
	
	flgCpy = _flgCpy;
	
	warType=_warType;						//作战模式；
	
	changePkType=_changePkType;
	
	mapType=_mapType;			//地图类型；
	
	campEntFlag=_campEntFlag;		//不加阵营是否可进图该地图标记值（0，可进入 1，不可进入）；
	
	levelLowerLimit=_levelLowerLimit;	//跳转点等级下限制；
	
	levelUpperLimit=_levelUpperLimit;	//地图跳转点等级上限值；
	
	escapePt_it = monId_connect_monster.begin();
		
	/*宴席刷出点*/
	dishPtSet = _dishPtSet;
	
	isActiveDishBru = false;
	
	centerPt = _centerPt;
	
	radius = _radius;
	
	randPtCtn = 0;
}

/*初始化九宫格*/
void Map_Inform::InitBox(void)
{
	if(box == NULL)
	{
		if(strncmp(mapId, "ectype_map_034", 14) == 0)
		{
			// cout<<"@@Tory it's tower defence map"<<endl;
			Point SCREEN_SIZE(10000,5000);
			box = new Nbox(this,SCREEN_SIZE);
			return;
		}		
		if(strncmp(mapId,"ectype_map",10) == 0)
		{
			// cout<<"cpy is all map send msg:"<<endl;
			Point SCREEN_SIZE(10000,5000);
			box = new Nbox(this,SCREEN_SIZE);
			return;
		}			
		else
		{
			Point SCREEN_SIZE(1180,600);
			box = new Nbox(this,SCREEN_SIZE);	
		}	
	}
}

/*获得九宫格*/
Nbox* Map_Inform::getBox(void)
{
	if(box == NULL)
	{
		return NULL;
	}
	return box;
}

/*获得地图id*/
char* Map_Inform::getMapId(void)
{
	return mapId;
}

/*获得地图id*/
char* Map_Inform::getIdentity(void)
{
	return mapId;
}

/*获得地图的偏移量*/
int Map_Inform::getBaseDigst(void)
{
	return baseDigst;
}

/*获得地图的宽*/
int Map_Inform::getRow(void)
{
	return row;
}

/*获得地图的高*/
int Map_Inform::getCol(void)
{
	return col;
}

/*设置地图的障碍点信息*/
void Map_Inform::setMapHinder(vector< vector<int> > &_map_hinder)
{
	map_hinder=_map_hinder;
}

/*获得地图的障碍点信息*/
vector< vector<int> >& Map_Inform::getMapHinder(void)
{
	return map_hinder;
}

/*获得此地图的怪物map，键为怪的实例id，值为怪物实例指针*/
map<string,MonsterBase *>& Map_Inform::getMonId_connect_monster(void)
{
	return monId_connect_monster;
}
/*获得此地图的跳转点ID，键为跳转点id，值为跳转点所指向信息的指针*/
map<string,const jumpId_infor*>& Map_Inform::getJumpId_connect_jumpInfo(void)
{
	return jumpId_connect_jumpInfo; 
}

/*获得地图的高*/
int Map_Inform::getHeight(void)
{
	return mapHeight;
}

/*获得地图的宽*/
int Map_Inform::getWidth(void)
{
	return mapWidth;
}

/*析构函数*/
Map_Inform::~Map_Inform(void)      //此类里面，此方法不能省
{
	ev_timer_stop(loops,&timer);
	
	/*析构此地图中的怪物*/
	map<string,MonsterBase *>::iterator monId_it;
	MonsterBase *monster = NULL;
	for(monId_it = monId_connect_monster.begin();monId_it != monId_connect_monster.end();monId_it++)
	{
		monster = monId_it->second;
		delete monster;
		monster = NULL;
	}
	monId_connect_monster.clear();
	
	map<string,TakeGoods*>::iterator take_it; 
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();take_it++)
	{
		delete take_it->second;
		take_it->second = NULL;
	}	
	takeGoodsMap.clear();
	
	map<string,Bottle*>::iterator bot_it;
	for(bot_it = botInMap.begin();bot_it != botInMap.end();bot_it++)
	{
		delete bot_it->second;
		bot_it->second = NULL;
	}
	botInMap.clear();
	
	map<string,Trap*>::iterator trap_it;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		delete trap_it->second;
		trap_it->second = NULL;
	}
	trapInstMap.clear();
	
	map<string,Pick*>::iterator drop_it; ;
	for(drop_it = dropGoodsMap.begin();drop_it != dropGoodsMap.end();drop_it++)
	{
		delete drop_it->second;
		drop_it->second = NULL;
	}
	dropGoodsMap.clear();
	//added by benliao 2012.12.23
	if(box)
	{
		delete box;
		box = NULL;
	}
		
}

/*启动计时器*/
void Map_Inform::initTimer(void)
{
	if(flgThk != -1)
	{
		return;
	}
	
	ext_ev_timer_init(&timer,MapThkCalBak,MAP_THINK_TIME,0,this,mapId);
	ev_timer_start(loops,&timer);
}

	
/*获得此地图的入点*/		
Point Map_Inform::getEntPt(void)
{
	return entPt;
}

/*获得此地图的出点*/
Point Map_Inform::getOutPt(void)
{
	return outPt;
}

/*删除地图信息中的heroId的方法，在exit_exception_cpp、exit_normal.cpp内调用*/
bool Map_Inform::deleteID(StyObj &obj)
{

    if(box == NULL){ //added by benliao 2012.12.23
	return false;
    } 
	/*从九宫格内删掉*/
    if(!box->deleteInOldSrc(obj))
	{
		// cout<<"obj in box delete is woring:"<<obj.objId<<endl;
		// cout<<"obj in box delete is woring of the type:"<<obj.type<<endl;
		
		/*删除失败*/
		return false;
	}
	return true;
}

/*插入*/
bool Map_Inform::insertID(StyObj &obj)
{
    return box->inputInOldSrc(obj);	
}

/*修改heroId在Map_Inform中九宫格内的位置，在command_time_poll.cpp内调用*/
bool Map_Inform::updateID(StyObj &obj,Point &newPt)
{	
	if(!judgePiex(newPt))
	{
		/*逻辑坐标非法*/
		cout<<"objId of piexPt is illeay:"<<obj.objId<<endl;	
		cout<<"objId of piexPt is illeay of the type:"<<obj.type<<endl;		
		cout<<"newPt._x:"<<newPt._x<<endl;
		cout<<"newPt._y:"<<newPt._y<<endl;		
		return false;
	}

	return box->MovePt(obj,newPt);    

}

/*重载获得九宫格内容函数，通过id*/
void Map_Inform::getStaInSrcVec(StyObj &obj,map<string,StyObj> &reselt)
{
	if(box == NULL)
	{
		return;
	}
}	

/*获取当前id的逻辑坐标点*/
bool Map_Inform::getPtNow(StyObj &obj,Point &piexPt)
{
	/*类型判断*/
	if(!isStyObjTpe(obj.type))
	{
		return false;
	}

	if(HERO_STYLE_TYPE == obj.type)
	{
		return getPtHeroNow(obj.objId,piexPt);
	}
	
	if(MONSTER_STYLE_TYPE == obj.type)
	{
		return getPtMonNow(obj.objId,piexPt);
	}
	if(PET_STYLE_TYPE == obj.type)
	{
		return getPtPetNow(obj.objId,piexPt);
	}
	if(WAGON_STYLE_TYPE == obj.type)
	{
		return getPtWagonNow(obj.objId,piexPt);
	}
	if(BOTTLE_STYLE_TYPE == obj.type)
	{
		return getPtBotNow(obj.objId,piexPt);
	}
	if(TAKEGOODS_STYLE_TYPE == obj.type)
	{
		return getPtTakeGoodsNow(obj.objId,piexPt);
	}
	if(PICK_STYLE_TYPE == obj.type)
	{
		return getPtPickNow(obj.objId,piexPt);
	}
	if(TRAP_STYLE_TYPE == obj.type)
	{
		return getPtTrapNow(obj.objId,piexPt);
	}
	if(DROP_EQUIP_STYLE_TYPE == obj.type)
	{
		return getPtEquipNow(obj.objId,piexPt);
	}
	if(STATUARY_STYLE_TYPE == obj.type)
	{
		return getPtStatuaryNow(obj.objId,piexPt);
	}
	return false;
}

/*获取玩家的当前像素坐标点*/
bool Map_Inform::getPtHeroNow(string heroId,Point &piexPt)
{
	Hero *myHero;
	if(heroId.empty())
	{
		return false;
	}	
	myHero = heroid_to_hero(heroId);
	if(myHero == NULL)
	{
		return false;
	}
	piexPt = myHero->getLocation();
	return true;
}

/*获取掉落物品的当前像素坐标点*/
bool Map_Inform::getPtPickNow(string pickid,Point &piexPt)
{
	Pick *myPick;
	
	if(pickid.empty())
	{
		return false;
	}
	
	myPick = getDropPickInst(const_cast<char *>(pickid.c_str()));
	if(myPick == NULL)
	{
		return false;
	}
	piexPt = myPick->getPiexPt();	
	return true;
}

/*获取马车的当前像素坐标点*/
bool Map_Inform::getPtWagonNow(string wagonId,Point &piexPt)
{
	map<string,Wagon*>::iterator wagon_it; 
	
	if(wagonId.empty())
	{
		return false;
	}
	
	wagon_it = wagonInstMap.find(wagonId);
	if(wagon_it == wagonInstMap.end())
	{
		return false;
	}
	piexPt = wagon_it->second->getPt();
	return true;
}

/*获取玩家的当前像素坐标点*/
bool Map_Inform::getPtPetNow(string petId,Point &piexPt)
{
	Pet* myPet;
	
	if(petId.empty())
	{
		cout<<"the petId is empty error:"<<endl;
		return false;
	}
	
	myPet = id_to_getActivePet(const_cast<char*>(petId.c_str()));
	// cout<<"pet identity is:"<<petId<<endl;
	// cout<<"------------------jollyTest Begin---------------"<<endl;
	// map<string,Pet*>::iterator it;
	// for (it=id_to_activePet.begin();it!=id_to_activePet.end();it++)
	// {
		// cout<<it->second->getIdentity()<<endl;
	// }
	// cout<<"------------------jollyTest end----------------"<<endl;
	
	if(myPet == NULL)
	{
		cout<<"the petInst is NULL error:"<<petId<<endl;
		return false;
	}
	piexPt = myPet->getPiexPt();
	return true;
}

/*获取摘取物品的当前像素坐标点*/
bool Map_Inform::getPtTakeGoodsNow(string takeGoodId,Point &piexPt)
{
	TakeGoods* myTakeGoods;
	if(takeGoodId.empty())
	{
		return false;
	}
	myTakeGoods = getTakeObj(takeGoodId);
	if(myTakeGoods == NULL)
	{
		return false;
	}
	piexPt = myTakeGoods->getPt();
	return true;
}
/*获取怪物的当前像素坐标点*/
bool Map_Inform::getPtMonNow(string monId,Point &piexPt)
{
	MonsterBase *mon;
	
	if(monId.empty())
	{
		cout<<"the monId is empty:"<<endl;
		return false;
	}
	
	mon = getMonsterObj(monId);
	if(mon == NULL)
	{
		cout<<"the mon is NULL:"<<monId<<endl;
		return false;
	}
	piexPt = mon->getLocation();
	return true;
}

/*获取掉落装备的当前像素坐标点*/
bool Map_Inform::getPtEquipNow(string equipId,Point &piexPt)
{
	Equipment *equip;
	map<string,Equipment*>::iterator equip_it;
	if(equipId.empty() || dropEquipMent.empty())
	{
		cout<<"the id is error or the drioEquipMent is empty:"<<equipId<<endl;
		return false;
	}
	equip_it = dropEquipMent.find(equipId);
	if(equip_it == dropEquipMent.end())
	{
		cout<<"can not find the equipInst the id is error :"<<equipId<<endl;
		return false;
	}
	
	piexPt = equip_it->second->getPiexPt();
	return true;
}

/*获取雕像的当前像素坐标点*/
bool Map_Inform::getPtStatuaryNow(string statuaryId,Point &piexPt)
{
	
	StatuaryHero* statuaryHero;
	map<string,StatuaryHero*>::iterator statuary_it;
	statuary_it = statuaryTypeToStatuaryHero.find(statuaryId);
	if(statuary_it == statuaryTypeToStatuaryHero.end())
	{
		cout<<"Map_Inform::getPtStatuaryNow not find StatuaryHero :"<<statuaryId<<endl;
		return false;
	}
	
	statuaryHero = statuary_it->second;
	
	piexPt = statuaryHero->getPiexPt();
	
	return true;
}

/*获取瓶罐的当前像素坐标点*/
bool Map_Inform::getPtBotNow(string botId,Point &piexPt)
{
	Bottle *myBottle;
	
	if(botId.empty())
	{
		return false;
	}
	
	myBottle = getBotInst(const_cast<char *>(botId.c_str()));
	if(myBottle == NULL)
	{
		return false;
	}
	piexPt = myBottle->getPiexPt();
	return true;
}

/*获取陷阱的当前像素坐标点*/
bool Map_Inform::getPtTrapNow(string trapId,Point &piexPt)
{
	Trap *myTrap;
	
	if(trapId.empty())
	{
		return false;
	}
	
	myTrap = getTrapInst(const_cast<char *>(trapId.c_str()));
	if(myTrap == NULL)
	{
		cout<<"can not find the trapInst:"<<trapId<<endl;
		return false;
	}
	piexPt = myTrap->getPiexPt();
	return true;
}

/*设置地图的怪物信息map*/
void Map_Inform::setMonId_connect_monster(map<string,MonsterBase *>& _monId_connect_monster)
{
	monId_connect_monster = _monId_connect_monster;	
}


/*地图暂停思考函数*/
void Map_Inform::stopThk(void)
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
		}
		/*设置地图思考标记值为怪物在已经思考*/
		flgThk = 0;
	}
}
	

/*插入玩家fd*/
void Map_Inform::inPutFd(int fd)
{
	heroFd.insert(fd);
}

/*获得此地图所以玩家fd*/
set<int> Map_Inform::getHeroFd(void)
{
	return heroFd;
}

/*玩家离开此地图，删除fd*/
void Map_Inform::delFd(int fd)//add cehnzhen 6.5	
{
	set<int>::iterator fd_it;
	fd_it = heroFd.find(fd);
	if(fd_it != heroFd.end())
	{
		heroFd.erase(fd_it);
	}
}

/*所有在此地图上的玩家的数量*/
int Map_Inform::getFdSze(void)
{
	return heroFd.size();
}

/*设置所有在此地图上的怪的地图指针*/
void Map_Inform::setMonMap(void) 
{
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{		
		mon_it->second->setMap(this);
		if(strcmp(mon_it->second->getType(),"AttRedMon") == 0)
		{
			monAttRedList.push_back(mon_it->first);
		}
	}
	redMon_it = monAttRedList.begin();
	bruRedMonCtn = 0;
}

	 
/*复制地图怪物实例以及和刷怪记录表*/	
void Map_Inform::copyMapMon(map<string,MonsterBase*> &newMonIn,char *newMapId,\
							map<string,const jumpId_infor*>&newjumpId_connect_jumpInfo)
{
	map<string,MonsterBase*>::iterator mon_it;	
	map<string,const jumpId_infor*>::iterator jumpId_it;
	
	string typeId;
	MonsterBase *newMon;
    newjumpId_connect_jumpInfo=jumpId_connect_jumpInfo;  //map直接赋值,map<string,const jumpId_infor*> 指向为只读，不能修改；
	
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{		 
		/*复制一个怪物实例*/		
		newMon = NULL;  
		newMon = mon_it->second->copyMon(newMapId);	
		
		/*生成刷怪记录表*/
		typeId =  newMon->getTypeId();		
		newMonIn[newMon->getIdentity()] = newMon;	
	}
}

/*打印测试地图信息*/
void Map_Inform::printMonsterInform(void)
{
	map<string,MonsterBase*>::iterator mon_it;
	string typeId;
	MonsterBase *newMon;
	
	/*测试地图怪物信息*/	
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{		 
		newMon = NULL;
		newMon = mon_it->second;
		cout<<"monsterId:"<<newMon->getIdentity()<<endl;
		cout<<"monsterMapId:"<<newMon->getMapId()<<endl;
		cout<<"monsterMapId:"<<newMon->getMap()->getMapId()<<endl;
		cout<<"monsterTypeId:"<<newMon->getTypeId()<<endl;			
	}
}


Point Map_Inform::getLogicEntPt(void)
{
	Point entLogicPt;
	entLogicPt = MapExchangeLogical(entPt);	
	entLogicPt._y += baseDigst;
	return entLogicPt;
}

/*
argument _index 阵营所属的下标，0，支派，1，宗教，2，游侠；其他参数默认为支派；
  return Point  诞生点的逻辑点坐标；
*/
Point Map_Inform::getCampWarPt(int _index)
{
	if(_index==0)
		return tribesPt;
	else if(_index==1)
		return religionPt;	
	else if(_index==2)
		return rangerPt;	
	else
		return tribesPt;
}

/*重置整张地图信息*/
void Map_Inform::initMap(void)
{	
	/*先停*/
	ev_timer_stop(loops,&timer);
	flgThk = -1;
}

/*设置地图思考标记值*/
void Map_Inform::setThkFlg(int _thkFlg)
{
	flgThk = -1;
}


/*通过怪物id获得怪物实例指针*/
MonsterBase* Map_Inform::getMonsterObj(string monId)
{
	if(monId.empty())
	{
		return NULL;
	}
	
	// if(monId_connect_monster.empty())
	// {		
		// return NULL;
	// }
	
	map<string,MonsterActiveBoss*>::iterator boss_it; 
	map<string,MonsterBase*>::iterator mon_it;
	mon_it = monId_connect_monster.find(monId);
	if(mon_it == monId_connect_monster.end())
	{
		boss_it = monActBoss.find(monId);
		if(boss_it == monActBoss.end())
		{
			return getToolMonster(const_cast<char *>(monId.c_str()));
		}
		return boss_it->second;
			
	}
	return mon_it->second;
}


/*获得整个怪物信息*/
void Map_Inform::getAllMonObj(vector<MonsterBase*> &monObj)
{
	map<string,MonsterBase*>::iterator mon_it;
	
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		monObj.push_back(mon_it->second);
	}
}

/*判断逻辑点是否正确*/
bool Map_Inform::judgeLogPt(Point &logPt)
{
	if(logPt._x < 0 || logPt._x >= row)
	{ 
		return false;
	}
	if(logPt._y < 0 || logPt._y >= col)
	{
		return false;
	}
	
	if(map_hinder.size() < logPt._x || map_hinder[0].size() < logPt._y)
	{
		return false;
	}
	
	return true;
}

/*判断逻辑点是否为障碍点<传入点为逻辑点>*/
bool Map_Inform::judgeLogPtHind(Point &logPt)
{
	if (logPt._x<0||logPt._y<0)
	{
		cout<<"logPt._x:"<<logPt._x<<endl;
		cout<<"logPt._y:"<<logPt._y<<endl;
		cout<<"point error in map_inform 837"<<endl;
		return false;
	}
	if(!judgeLogPt(logPt))
	{
		cout<<"the error logPt._x:"<<logPt._x<<" logPt._y:"<<logPt._y<<endl;
		return false;
	}
	
	if(map_hinder[logPt._x][logPt._y] == 1)
	{
		// cout<<"is hinder logPt._x:"<<logPt._x<<" logPt._y:"<<logPt._y<<endl;
		return false;
	}
	
	return true;
}


/*把一个逻辑点转换成字符串*/
void Map_Inform::logPtToStr(string &logPtStr,Point &logPt)
{
    stringstream ss ;
    ss << logPt._x;
    ss << logPt._y;
    ss >> logPtStr;
}


/*从lPos_to_heroId中删除一个对象的id*/
bool Map_Inform::eraseObjId(string &logPtStr,string &objId)
{
	map<string,set<string> >::iterator set_it;
	set<string>::iterator objId_it;
	set_it = lPos_to_heroId.find(logPtStr);	
    if(set_it != lPos_to_heroId.end())
    {
		objId_it = set_it->second.find(objId);
		
		if(objId_it == set_it->second.end())
		{
			return false;
		}
		
		set_it->second.erase(objId_it);
		return true;
    }
	return false;
}


/*从lPos_to_heroId中插入一个对象的id*/
bool Map_Inform::insertObjId(string &logPtStr,string &objId)
{
	map<string,set<string> >::iterator set_it;
	set<string>::iterator objId_it;
	set<string> newSet;
	
	set_it = lPos_to_heroId.find(logPtStr);	
    if(set_it != lPos_to_heroId.end())
    {
		objId_it = set_it->second.find(objId);
		
		if(objId_it == set_it->second.end())
		{
			set_it->second.insert(objId);
			return true;
		}	
		
		/*已经存在*/
		return false;
    }	
	newSet.insert(objId);
	lPos_to_heroId[logPtStr] = newSet;
	return true;
}

/*复制可摘取物品*/
void Map_Inform::copyTakeGoods(map<string,TakeGoods*> &_takeGoodsMap,char *_mapId)
{
	map<string,TakeGoods*>::iterator takeGoods_it;
	TakeGoods *newTakeGoods;
	for(takeGoods_it = takeGoodsMap.begin();takeGoods_it != takeGoodsMap.end();takeGoods_it++)
	{
		newTakeGoods = takeGoods_it->second->copyTakeGoods(_mapId);
		_takeGoodsMap[newTakeGoods->getId()] = newTakeGoods;
	}
}


/*设置可摘取物品地图实例指针*/
void Map_Inform::setTakeGoodsMap(void)
{
	
	map<string,TakeGoods*>::iterator take_it; 	
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();take_it++)
	{
		take_it->second->setLogicMap(this);
	}
}

/*通过摘取id获得摘取实例指针*/
TakeGoods* Map_Inform::getTakeObj(string takeGoodsId)
{
	map<string,TakeGoods*>::iterator take_it; 
	
	if(takeGoodsMap.empty() || takeGoodsId.empty())
	{
		return NULL;
	}	
	
	take_it = takeGoodsMap.find(takeGoodsId);
	if(take_it == takeGoodsMap.end())
	{
		return NULL;
	}
	return take_it->second;
}

/*设置可摘取物品地图实例指针*/
void Map_Inform::bruTakeMsg(void)
{	

	map<string,TakeGoods*>::iterator take_it; 
	TakeGoods *takeGoods;
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();take_it++)
	{
		takeGoods = take_it->second;
		
		/*消息触发方式或者资源战中的资源*/
		if(takeGoods->getTrigFlg() || takeGoods->getIsCampSource())
		{
			continue;
		}
		takeGoods->brushMsg();
	}
}

/*摘取物品消亡*/
void Map_Inform::disperTakeGood(string _takeGoodId)
{
	TakeGoods* takeGoods;
	
	takeGoods = getTakeObj(_takeGoodId);
	if(takeGoods == NULL)
	{
		return;
	}
	takeGoods->disperMsg();
}


/*复制瓶罐物品*/
void Map_Inform::copyBotInMap(map<string,Bottle*>& _botInMap,char *_mapId)
{
	map<string,Bottle*>::iterator bot_it;
	Bottle* newBottle;
	for(bot_it = botInMap.begin();bot_it != botInMap.end();bot_it++)
	{
		newBottle = bot_it->second->copyBottle(_mapId);
		_botInMap[newBottle->getId()] = newBottle;
	}
}

/*设置瓶罐物品地图信息*/
void Map_Inform::setBotMap(void)
{
	map<string,Bottle*>::iterator bot_it;
	for(bot_it = botInMap.begin();bot_it != botInMap.end();bot_it++)
	{
		bot_it->second->setMap(this);
	}
}

/*设置陷阱地图信息*/
void Map_Inform::setTrapMap(void)
{	
	map<string,Trap*>::iterator trap_it; 
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		trap_it->second->setMap(this);
	}
}

/*通过瓶罐实例id获得瓶罐实例*/
Bottle* Map_Inform::getBotInst(char *_botId)
{	
	map<string,Bottle*>::iterator bot_it;
	bot_it = botInMap.find(_botId);
	if(bot_it == botInMap.end())
	{
		return NULL;
	}
	return bot_it->second;
}
/*通过陷阱实例id获得陷阱实例*/
Trap* Map_Inform::getTrapInst(char *_trapId)
{
	map<string,Trap*>::iterator trap_it;
	trap_it = trapInstMap.find(_trapId);
	if(trap_it == trapInstMap.end())
	{
		return NULL;
	}
	return trap_it->second;
}

/*刷出地图瓶罐信息*/
void Map_Inform::brushBotMsg(void)
{
	map<string,Bottle*>::iterator bot_it;
	for(bot_it = botInMap.begin();bot_it != botInMap.end();bot_it++)
	{
		bot_it->second->brushMsg();		
	}
}

/*刷出地图陷阱信息*/
void Map_Inform::brushTrapMsg(void)
{
	map<string,Trap*>::iterator trap_it; 
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		/*召唤出来的则continue*/
		if(trap_it->second->getIsCalled())
		{
			continue;
		}
		
		trap_it->second->brushMsg();
		trap_it->second->initTimer();
	}
}

/*复制陷阱*/
void Map_Inform::copyTrapVec(map<string,Trap*> &_trapInstMap,char *_mapId)
{
	map<string,Trap*>::iterator trap_it; 
	Trap* newTrap;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		newTrap = trap_it->second->copyTrap(_mapId);
		_trapInstMap[newTrap->getId()] = newTrap;
	}
}	


/*获取玩家实例指针*/
Hero* Map_Inform::getHero(char *heroId)
{ 
	map<string,Hero*>::iterator hero_it;
	hero_it = heroId_to_pHero.find(heroId);
	if(hero_it == heroId_to_pHero.end())
	{
		return NULL;
	}
	return hero_it->second;
}

/*获取玩家实例指针*/
void Map_Inform::trapAttack(void)
{
	map<string,Trap*>::iterator trap_it;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		trap_it->second->AttackPerson();
	}
}

/************* xhm added start**************/
int Map_Inform::getWarType()
{
	return warType;
}

void Map_Inform::setWarType(int _index)
{
	warType = _index;
}

int Map_Inform::getChangePkType()
{
	return changePkType;
}

int Map_Inform::getMapType(void)
{
	return mapType;
}

void Map_Inform::setMapType(int _index)
{
	mapType = _index;
}

int Map_Inform::getCampEntFlag(void)
{
	return campEntFlag;
}

int Map_Inform::getLevelLowerLimit(void)
{
	return levelLowerLimit;
}
	
int Map_Inform::getLevelUpperLimit(void)
{
	return levelUpperLimit;
}

/******************xhm added end***********/

/*怪物死亡*/
void Map_Inform::GromonDead(char *monId)
{

}

string Map_Inform::getTd_roomid(void)
{
	return td_room;
}

void Map_Inform::setTd_roomid(string td_inst_room)
{
	td_room = td_inst_room;
}

bool Map_Inform::getFlgCpy()
{
	return flgCpy;
}

/*副本回收标志*/
bool Map_Inform::recoverCpy(void)
{
	return false;
}

/*清空九宫格中的内容*/
void Map_Inform::clearBox(void)
{
	if(box != NULL)
	{
		box->clearBox();
	}
}


/*测试打印副本中存活列表信息*/
void Map_Inform::testMonsterWait(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	cout<<"test monsterWaitTme begin:"<<endl;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		cout<<"monId:"<<mon_it->first<<endl;
		cout<<"waitTme:"<<mon_it->second->getLveMag().waitTme<<endl;
		cout<<"liveTme:"<<mon_it->second->getLveMag().lvedCtn<<endl;
	}
	cout<<"test monsterWaitTme end:"<<endl;
}


/*重置怪物的存货管理器*/
void Map_Inform::initMonLvMager(void)
{
	map<string,MonsterBase *>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->initMonsterALL();
	}
}

/*更新副本怪物数目*/
void Map_Inform::sentSumMonMsg(void)
{

}

/*杀死一个怪*/
void Map_Inform::killOneMon(void)
{
}


/*插入野外boss*/
void Map_Inform::insertBoss(MonsterActiveBoss* newBoss)
{
	map<string,MonsterActiveBoss*>::iterator boss_it;
	if(newBoss == NULL)
	{
		return;
	}
	boss_it = monActBoss.find(newBoss->getIdentity());
	if(boss_it != monActBoss.end())
	{
		return;
	}
	monActBoss[newBoss->getIdentity()] = newBoss;
}
	


/*设置所有在此地图上的野外BOSS的地图指针*/
void Map_Inform::setMonBossMap(void) 
{
	map<string,MonsterActiveBoss*>::iterator boss_it;
	
	if(monActBoss.empty())
	{
		return;
	}
	
	for(boss_it = monActBoss.begin();boss_it != monActBoss.end();boss_it++)
	{
		boss_it->second->setMap(this);
	}
}


/*刷出所有在此地图上的野外BOSS*/
void Map_Inform::brushMonBoss(void) 
{
	map<string,MonsterActiveBoss*>::iterator boss_it;
	
	if(monActBoss.empty())
	{
		return;
	}
	 
	for(boss_it = monActBoss.begin();boss_it != monActBoss.end();++boss_it)
	{
		boss_it->second->brushMon();
		if(boss_it->second->getOwnerAttriType() == 3)
		{
			cout<<"Map_Inform::brushMonBoss begin:"<<boss_it->second->getIdentity()<<endl;
			cout<<"boss_it->second->getBshMsg:"<<boss_it->second->getBshMsg()<<endl;
			cout<<"Map_Inform::brushMonBoss end:"<<boss_it->second->getIdentity()<<endl;
		}
		
		
	}
}


/*重置所有在此地图上的野外BOSS*/
void Map_Inform::initMonBoss(void) 
{
	map<string,MonsterActiveBoss*>::iterator boss_it;
	
	if(monActBoss.empty())
	{
		return;
	}
	 
	for(boss_it = monActBoss.begin();boss_it != monActBoss.end();boss_it++)
	{
		boss_it->second->initMonsterALL();
	}
}


/*判断像素坐标是否合法*/
bool Map_Inform::judgePiex(Point &piexPt)
{
	if(piexPt._x < 0 || piexPt._x > mapWidth)
	{
		return false;
	}
	if(piexPt._y < 0 || piexPt._y > mapHeight)
	{
		return false;
	}
	return true;
}


/*重置陷阱信息*/
void Map_Inform::initTrap(void)
{	
	map<string,Trap*>::iterator trap_it;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		trap_it->second->initTrap();
	}
}

/*暂停陷阱计时器*/
void Map_Inform::stopTrapThk(void)
{	
	map<string,Trap*>::iterator trap_it;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		trap_it->second->stopTimer();
	}
}

/*启动陷阱计时器*/
void Map_Inform::reSetTrapThk(void)
{	
	map<string,Trap*>::iterator trap_it;
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();trap_it++)
	{
		trap_it->second->initTimer();
	}
}

/*按队列每次刷出一个击杀红名的怪*/
void Map_Inform::brushRedMon(void)
{
	
	map<string,MonsterBase*>::iterator monInst_it;
	
	MonsterBase *monBru;


	if(monAttRedList.empty() || redMon_it == monAttRedList.end())
	{
		return;
	}
	
	if(!isNextRedMonOut())
	{
		return;
	}
	monInst_it = monId_connect_monster.find(*redMon_it);
	if(monInst_it == monId_connect_monster.end())
	{
		return;
	}
	monBru = monInst_it->second;		
	monBru->brushMon();	
	
	if(monBru->getOwnerAttriType() == 3)
	{
		cout<<"Map_Inform::brushRedMon begin:"<<monBru->getIdentity()<<endl;
		cout<<"monBru->getBshMsg:"<<monBru->getBshMsg()<<endl;
		cout<<"Map_Inform::brushRedMon end:"<<monBru->getIdentity()<<endl;
	}
	
	++redMon_it;
}

/*队列中每只怪刷出来的间隔时间*/
bool Map_Inform::isNextRedMonOut(void)
{
	bruRedMonCtn++;
	if(bruRedMonCtn == 1)
	{
		bruRedMonCtn = 0;
		cout<<"it is true:"<<endl;
		return true;
	}
	return false;
}

/*重置地图的时候,清空该地图中的所有掉落物品*/
void Map_Inform::clearDropMap(void)
{
	map<string,Pick*>::iterator pick_it;
	Pick *dropGoods;	
	for(pick_it = dropGoodsMap.begin(); pick_it != dropGoodsMap.end(); pick_it++)
	{
		dropGoods = pick_it->second;
		delete dropGoods;
		dropGoods = NULL;
		pick_it->second = dropGoods;
	}
	dropGoodsMap.clear();
	{
		std::map<string,Pick*> tmp;   
		dropGoodsMap.swap(tmp);  
	}
}

/*掉落时，插入掉落物*/
void Map_Inform::insertDropInst(Pick *dropGoods)
{
	if(dropGoods == NULL)
	{
		cout<<"the dropGoods is NULL:"<<endl;
		return;
	}
	cout<<"dropGoods->getFlag():"<<dropGoods->getFlag()<<endl;
	dropGoodsMap[dropGoods->getFlag()] = dropGoods;
	
	dropGoods->initPickTimer();
}

/*删掉某个掉落物*/
void Map_Inform::deleteDropInst(char *pickId)
{
	map<string,Pick*>::iterator pick_it;
	Pick *dropGoods;
	
	if(pickId == NULL || strlen(pickId) == 0)
	{
		cout<<"the pickId is NUll or the size is 0:"<<endl;
		return;
	}	
	pick_it = dropGoodsMap.find(pickId);
	if(pick_it == dropGoodsMap.end())
	{
		// cout<<"can not find the pickInst:"<<pickId<<endl;
		return;
	}
	
	dropGoods = pick_it->second;
	dropGoods->stopThreeTimer();
	dropGoods->stopFiveTimer();
	delete dropGoods;
	dropGoods = NULL;
	pick_it->second = dropGoods;
	dropGoodsMap.erase(pick_it);
}
	
/*查找某个掉落物*/
Pick* Map_Inform::getDropPickInst(char *pickId)
{
	map<string,Pick*>::iterator pick_it;
	Pick *dropGoods;
	
	if(pickId == NULL || strlen(pickId) == 0)
	{
		cout<<"the pickId is NUll or the size is 0:"<<endl;
		return NULL;
	}	
	
	pick_it = dropGoodsMap.find(pickId);
	if(pick_it == dropGoodsMap.end())
	{
		cout<<"can not find the pickInst:"<<pickId<<endl;
		return NULL;
	}
	
	return pick_it->second;
}


/*随机一个逃窜点*/
bool Map_Inform::randEscapePt(Point &endFinPt)
{
	escapePt_it++;
	if(escapePt_it == monId_connect_monster.end())
	{
		escapePt_it = monId_connect_monster.begin();
	}
	endFinPt = escapePt_it->second->getLocation();
}

/*点菜*/
TakeGoods * Map_Inform::olderKandy(char *dishId,char *_onwerId,char *_nickName)
{
	TakeGoods *newDish = NULL,*confDish;
	
#if 0

	/*原来的吃饭模式*/
	newDish = newDishInst(dishId);
	
#endif
	
	/*add chenzhen 20130325 把空桌子换成有菜的桌子*/
	map<string,TakeGoods*>::iterator take_it;	
	take_it = takeGoodsConfMap.find(dishId);
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"not find the dishId of the confMap:"<<dishId<<endl;
		return NULL;
	}
	
	confDish = take_it->second;
	
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();++take_it)
	{
		newDish = take_it->second;
		
		if(newDish->getTrigFlg() && !newDish->getIsDished())
		{
			break;
		}
	}
	
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::olderKandy the desk it not enough :"<<dishId<<endl;
		return NULL;
	}
	
	if(newDish==NULL || _onwerId == NULL || _nickName == NULL)
	{
		cout<<"the newDish is NULL:"<<endl;
		return NULL;
	}
	else
	{	
		/*add chenzhen 20130325 更换桌子名称*/
		newDish->setName(confDish->getName());
		newDish->setPhotoId(confDish->getPhotoId());
		
		newDish->setDIshOwner(_onwerId);
		newDish->setDishNewNme(_nickName);	
		
		/*add chenzhen 20130325 更换桌子图片*/
		newDish->setIsDished(true);
		newDish->brushMsg();
		return newDish;
	}
}






/*动态生成宴席*/
TakeGoods* Map_Inform::newDishInst(char *dishId)
{
	map<string,TakeGoods*>::iterator take_it;
	set<Point>::reverse_iterator dishPt_it;
	Point dishPt;
	TakeGoods *newDish,*confDish;
	
	if(dishId == NULL || strlen(dishId) == 0)
	{
		cout<<"the dishId is NULL:"<<endl;
		return NULL;
	}
	

	if(dishPtSet.empty())
	{
		cout<<"it is e dishPtSet is empty:"<<endl;

		msg_error(g_out_buf,82);
		send_msg(pg_hero->getFd(),g_out_buf);

		return NULL;
	}

	
	dishPt_it = dishPtSet.rbegin();
	
	dishPt = (*dishPt_it);
	
	take_it = takeGoodsConfMap.find(dishId);
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"not find the dishId of the confMap:"<<dishId<<endl;
		return NULL;
	}
	
	confDish = take_it->second;
	
	newDish = confDish->copyTakeGoods(dishPt,true);
	
	if(newDish == NULL)
	{
		return NULL;
	}
	
	
	takeGoodsMap[newDish->getTakeId()] = newDish;
	
	newDish->setLogicMap(this);

	dishPtSet.erase(dishPt);
	
	return newDish;
}

/*清掉宴席*/
void Map_Inform::clearDish(void)
{
#if 0
	map<string,TakeGoods*>::iterator take_it;
	TakeGoods *dish;
	
	take_it = takeGoodsMap.begin();
	while(take_it != takeGoodsMap.end())
	{
		if(take_it->second->getTrigFlg())
		{			
			dishPtSet.insert(take_it->second->getPt());			
			delete take_it->second;
			take_it->second = NULL;
			takeGoodsMap.erase(take_it++);
		}
		else
		{
			take_it++;
		}
	}
#endif
	
	map<string,TakeGoods*>::iterator take_it;
	TakeGoods *dish;
	
	take_it = takeGoodsMap.begin();
	while(take_it != takeGoodsMap.end())
	{
		if(take_it->second->getTrigFlg())
		{				
			delOneDish(const_cast<char *>((take_it->first).c_str()));
		}
		take_it++;
		
	}

}

/*通过菜单id删掉某个宴席实例*/
void Map_Inform::delOneDish(char *takeGoodsId)
{			
	map<string,TakeGoods*>::iterator take_it; 
	TakeGoods *instDish,*confDish;
	if(takeGoodsMap.empty() || takeGoodsId == NULL || strlen(takeGoodsId) == 0)
	{
		cout<<"Map_Inform::delOneDish the takeGoodsMap is empty or the argument takeGoodsId is NULL:"<<mapId<<endl;
		return ;
	}	
	
	take_it = takeGoodsMap.find(takeGoodsId);
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::delOneDish not find the :"<<takeGoodsId<<"in mapId:"<<mapId<<endl;
		return;
	}
	instDish = take_it->second;
	
	take_it = takeGoodsConfMap.find(instDish->getTypeId());
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"Map_Inform::delOneDish not find the dishId of the confMap :"<<instDish->getTypeId()<<"in mapId:"<<mapId<<endl;
		return ;
	}
	
	confDish = take_it->second;
	
	instDish->setName(confDish->getName());
	instDish->setPhotoId(confDish->getPhotoId());		
	instDish->initDishNewNme();
	instDish->initDishOwner();	
	instDish->setIsDished(false);
	instDish->brushMsg();
	
#if 0

	dishPtSet.insert(take_it->second->getPt());
	
	delete  take_it->second;
	
	take_it->second = NULL;
	
	takeGoodsMap.erase(take_it);
	
#endif
	
}

/*判断两个逻辑点之间是否存在障碍点,有障碍点，则返回假，否则为真*/		
bool Map_Inform::judgeLineCanPas(Point &logBeginPt,Point &logEndinPt)
{
	if(!judgeLogPtHind(logBeginPt) || !judgeLogPtHind(logEndinPt))
	{
		cout<<"the logBeginPt is hinder pt._x:"<<logBeginPt._x<<" pt._y:"<<logBeginPt._y<<endl;
		return false;
	}
	if(logBeginPt == logEndinPt)
	{
		return true;
	}
	
	/*垂直于x轴的直线*/
	if(logBeginPt._x == logEndinPt._x)
	{
		return verticlalLineX(logBeginPt,logEndinPt);
	}
	
	/*垂直于y轴的直线*/
	else if(logBeginPt._y == logEndinPt._y)
	{
		return verticlalLineY(logBeginPt,logEndinPt);		
	}
	
	/*其他直线*/
	else
	{
		return slantLine(logBeginPt,logEndinPt);		
	}
}

/*垂直于x轴的直线之间是否有障碍点，有障碍点，则返回假，否则为真*/
bool Map_Inform::verticlalLineX(Point &logBeginPt,Point &logEndinPt)
{
	int offSet;
	Point valuePt;
	
	valuePt._x = logBeginPt._x;	
	
	if(logBeginPt._y < logEndinPt._y)
	{
		valuePt._y = logBeginPt._y + 1;
		offSet = logEndinPt._y;
	}
	else
	{
		valuePt._y = logEndinPt._y + 1;
		offSet = logBeginPt._y;
	}
	
	while(valuePt._y < offSet)
	{
		/*判断是否为障碍点*/
		if(!judgeLogPtHind(valuePt))
		{
			cout<<"this point is hindPt._x:"<<valuePt._x<<"  hindPt._y:"<<valuePt._y<<endl;
			return false;
		}
		valuePt._y += 1;
	}		
	
}

/*垂直于y轴的直线之间是否有障碍点，有障碍点，则返回假，否则为真*/
bool Map_Inform::verticlalLineY(Point &logBeginPt,Point &logEndinPt)
{
	int offSet;
	Point valuePt;
	
	valuePt._y = logBeginPt._y;	
	
	if(logBeginPt._x < logEndinPt._x)
	{
		valuePt._x = logBeginPt._x + 1;
		offSet = logEndinPt._x;
	}
	else
	{
		valuePt._x = logEndinPt._x + 1;
		offSet = logBeginPt._x;
	}
	
	while(valuePt._x < offSet)
	{
		/*判断是否为障碍点*/
		if(!judgeLogPtHind(valuePt))
		{
			cout<<"this point is hindPt._x:"<<valuePt._x<<"  hindPt._y:"<<valuePt._y<<endl;
			return false;
		}
		valuePt._x += 1;
	}
}


/*斜线之间是否有障碍点，有障碍点，则返回假，否则为真*/
bool Map_Inform::slantLine(Point &logBeginPt,Point &logEndinPt)
{
	double valueY;
	int offSet;
	Point valuePt;
	
	valuePt._y = logBeginPt._y;	
	
	if(logBeginPt._x < logEndinPt._x)
	{
		valuePt._x = logBeginPt._x + 1;
		offSet = logEndinPt._x;
	}
	else
	{
		valuePt._x = logEndinPt._x + 1;
		offSet = logBeginPt._x;
	}
	cout<<"test in slantLine begin:"<<endl;
	cout<<"the test slantLine logBeginPt._x:"<<logBeginPt._x<<" logBeginPt._y:"<<logBeginPt._y<<endl;
	cout<<"the test slantLine logEndinPt._x:"<<logEndinPt._x<<" logEndinPt._y:"<<logEndinPt._y<<endl;
	cout<<"test in slantLine end:"<<endl;
		
	while(valuePt._x < offSet)
	{
		/*这是数学中的两点求直线公式*/
		valueY = 1.0 * (logEndinPt._y - logBeginPt._y)/(logEndinPt._x - logBeginPt._x) *\
		valuePt._x + 1.0 * (logEndinPt._x * logBeginPt._y - logEndinPt._y *\
		logBeginPt._x)/(logEndinPt._x - logBeginPt._x);
		
		cout<<"valuePt._x:"<<valuePt._x<<endl;
		cout<<"valueY:"<<valueY<<endl;
		
		if(isIntDigst(valueY,valuePt._y))
		{
			cout<<"this valuePt._x is :"<<valuePt._x<<"  valuePt._y:"<<valuePt._y<<endl;
			/*判断是否为障碍点*/
			if(!judgeLogPtHind(valuePt))
			{
				cout<<"this valuePt is hindPt._x:"<<valuePt._x<<"  hindPt._y:"<<valuePt._y<<endl;
				return false;
			}
		}
		valuePt._x += 1;
	}
	return true;
}


/*判断一个double是否为整形,如果是则返回真，且intValues为此整数*/
bool Map_Inform::isIntDigst(double y,int &intValues)
{
	double ptDistance;
	ptDistance = y - (int)y;
	if(ptDistance < 1e-15) 
	{
		intValues = (int)y;
		return true;
	}
	else if(ptDistance  > 0.999999999999999)
	{
		intValues = (int)y + 1;
		return true;
	}
	return false;
}


/*重置地图瓶罐信息*/
void Map_Inform::initBot(void)
{
	map<string,Bottle*>::iterator bot_it;
	for(bot_it = botInMap.begin();bot_it != botInMap.end();++bot_it)
	{
		bot_it->second->initBot();		
	}
}

/*根据角色生成怪物属性*/
void Map_Inform::initMonValues(Hero *enterHero)
{
	map<string,MonsterBase *>::iterator monIt_it;
	MonsterBase *mon;
	
	if(enterHero == NULL || monId_connect_monster.empty())
	{
		cout<<"the enterHero is NULL:"<<endl;
	}
	
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end();++monIt_it)
	{
		mon = monIt_it->second;
		
		if(strcmp(mon->getType(),"MonByHero") == 0)
		{
			cout<<"initMonValues in map:"<<endl;
			
			((MonsterByHero*)mon)->initMonsterValuesByHero(enterHero);
		}
	}
}


/*系统请客*/
void Map_Inform::systemTreat(void)
{	
#if 0
	map<string,TakeGoods*>::iterator take_it; 
	TakeGoods *takeGoods,*newDish;
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();take_it++)
	{
		takeGoods = take_it->second;
		
		/*消息触发方式*/
		if(takeGoods->getTrigFlg())
		{
			break;
		}
	}
	
	if(take_it == takeGoodsMap.end())
	{
		cout<<"it is NULL of the newDish:"<<endl;
		return NULL;
	}
	
	newDish = newDishInst(takeGoods);
	
	return newDish;
	
	
	if(newDish == NULL)
	{
		cout<<"it is NULL of the newDish:"<<endl;
		return NULL;
	}
#endif

}


/*动态生成宴席*/
TakeGoods* Map_Inform::newDishInst(TakeGoods *confDish)
{
	map<string,TakeGoods*>::iterator take_it;
	set<Point>::reverse_iterator dishPt_it;
	Point dishPt;
	TakeGoods *newDish;
	
	
	if(dishPtSet.empty() || confDish == NULL)
	{
		cout<<"it is end the dishPtSet or the dishPtSet is empty:"<<endl;
		return NULL;
	}
	
	dishPt_it = dishPtSet.rbegin();
	
	dishPt = *dishPt_it;	
	
	newDish = confDish->copyTakeGoods(dishPt,true);
	
	if(newDish == NULL)
	{
		return NULL;
	}
	
	
	takeGoodsMap[newDish->getTakeId()] = newDish;
	
	newDish->setLogicMap(this);
	
	dishPtSet.erase(dishPt);
	
	return newDish;
}

/*系统请客辅助函数*/
TakeGoods* Map_Inform::systemTreatAsist(void)
{

#if 0	
	/*原来的系统请吃饭*/
	map<string,TakeGoods*>::iterator take_it; 
	TakeGoods *takeGoods,*newDish;
	
	cout<<"Map_Inform::systemTreatAsist begin:"<<endl;
	
	for(take_it = takeGoodsConfMap.begin();take_it != takeGoodsConfMap.end();++take_it)
	{
		takeGoods = take_it->second;
		
		/*消息触发方式*/
		if(takeGoods->getTrigFlg())
		{
			break;
		}
	}
	
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"it is NULL of the newDish:"<<endl;
		return NULL;
	}
	
	newDish = newDishInst(takeGoods);
	
	cout<<"Map_Inform::systemTreatAsist end:"<<endl;
	
	return newDish;
	
#endif	
	
	
	
	TakeGoods *newDish,*confDish;
	
	
	/*add chenzhen 20130325 把空桌子换成有菜的桌子*/
	map<string,TakeGoods*>::iterator take_it;	
	for(take_it = takeGoodsConfMap.begin();take_it != takeGoodsConfMap.end();++take_it)
	{
		confDish = take_it->second;
		
		/*消息触发方式*/
		if(confDish->getTrigFlg())
		{
			break;
		}
	}
	
	
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"Map_Inform::systemTreatAsist not find the dishId of the confMap:"<<mapId<<endl;
		return NULL;
	}
	
	confDish = take_it->second;
	
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();++take_it)
	{
		newDish = take_it->second;
		
		if(newDish->getTrigFlg() && !newDish->getIsDished())
		{
			break;
		}
	}
		
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::systemTreatAsist not find the dishId of the confMap:"<<mapId<<endl;
		return NULL;
	}
	
	else
	{	
		/*add chenzhen 20130325 更换桌子名称*/
		newDish->setName(confDish->getName());
		newDish->setPhotoId(confDish->getPhotoId());
		newDish->setDishNewNme("系统");	
		
		/*add chenzhen 20130325 更换桌子图片*/
		newDish->setIsDished(true);
		newDish->setDishState(2);
		return newDish;
	}	
}


/*系统请客辅助函数*/
char* Map_Inform::getSystemTreatId(void)
{
	
	map<string,TakeGoods*>::iterator take_it; 
	TakeGoods *takeGoods,*newDish;
	
	for(take_it = takeGoodsConfMap.begin();take_it != takeGoodsConfMap.end();++take_it)
	{
		takeGoods = take_it->second;
		
		cout<<"Map_Inform::getSystemTreatId:"<<takeGoods->getTypeId()<<endl;
		
		/*消息触发方式*/
		if(takeGoods->getTrigFlg())
		{			
			return takeGoods->getTypeId();
		}
	}
	
	return NULL;
}

/*获得系统是否已点过菜，是表示点过*/
bool Map_Inform::getIsActiveDishBru(void)
{
	return isActiveDishBru;
}

/*设置系统是否已点过菜，是表示点过*/
void Map_Inform::setIsActiveDishBru(bool _isActiveDishBru)
{
	isActiveDishBru = _isActiveDishBru;
}


/*更改系统宴席为可吃状态*/
void Map_Inform::setSystemDishState(int _dishState)
{
	map<string,TakeGoods*>::iterator take_it;
	
	if(_dishState != 1 && _dishState != 2)
	{
		cout<<"Map_Inform::setSystemDishState the argument of _dishState is error:"<<_dishState<<endl;
		return;
	}
		
	take_it = takeGoodsMap.begin();
	while(take_it != takeGoodsMap.end())
	{
		if(take_it->second->getTrigFlg())
		{
#if 0
			/*原来有是否可以吃的状态值*/
			if(take_it->second->getDishState() == 1 || take_it->second->getDishState() == 2)
#endif
			/*空桌子，或者已经是系统宴请的*/
			if(!take_it->second->getIsDished())
			{
				take_it->second->setDishState(_dishState);
				break;
			}

		}	
		++take_it;		
	}
	
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::setSystemDishState not empty desk to system dish :"<<mapId<<endl;
	}
	
	
}

/*初始化雕像怪*/
void Map_Inform::initMonStatuary(void)
{
	map<string,StatuaryHero*>::iterator statuary_it;
	map<string,MonsterBase *>::iterator monIt_it;
	StatuaryHero* statuaryHero;
	MonsterBase *mon;
	if(statuaryTypeToStatuaryHero.empty() || monId_connect_monster.empty())
	{
		cout<<"Map_Inform::initMonStatuary the statuaryTypeToStatuaryHero or monId_connect_monster empty:"<<mapId<<endl;
		return;
	}
	
	statuary_it = statuaryTypeToStatuaryHero.begin();
	statuaryHero = statuary_it->second;
	
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end();++monIt_it)
	{
		mon = monIt_it->second;
		
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{			
			cout<<"Map_Inform::initMonStatuary finish:"<<mapId<<endl;
			((MonsterStatuary*)mon)->setStatuaryAttrit(statuaryHero->getMemStatuaryHero());
			break;
		}
	}
}

/*初始化雕像怪*/
void Map_Inform::initMonStatuaryByHero(Hero *hero)
{
	map<string,MonsterBase *>::iterator monIt_it;
	StatuaryHero* statuaryHero;
	MonsterBase *mon;
	if(monId_connect_monster.empty())
	{
		cout<<"Map_Inform::initMonStatuaryByHero the monId_connect_monster empty:"<<mapId<<endl;
		return;
	}
	
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end();++monIt_it)
	{
		mon = monIt_it->second;
		
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{			
			cout<<"Map_Inform::initMonStatuaryByHero finish:"<<mapId<<endl;
			((MonsterStatuary*)mon)->setStatuaryAttritByHero(hero);
			mon->brushMon();
			
			
			if(mon->getOwnerAttriType() == 3)
			{
				cout<<"Map_Inform::initMonStatuaryByHero begin:"<<mon->getIdentity()<<endl;
				cout<<"mon->getBshMsg:"<<mon->getBshMsg()<<endl;
				cout<<"Map_Inform::initMonStatuaryByHero end:"<<mon->getIdentity()<<endl;
			}
			break;
		}
	}
}


/*刷出四张桌子*/
void Map_Inform::brushTable(void)
{	
	map<string,TakeGoods*>::iterator take_it; 
	set<Point>::reverse_iterator dishPt_it;
	TakeGoods *confDish,*newDish;
	Point dishPt;
	
	if(dishPtSet.empty() || takeGoodsConfMap.empty())
	{
		cout<<"Map_Inform::brushTable dishPtSet or takeGoodsConfMap is empty:"<<mapId<<endl;
		return ;
	}
	
	for(take_it = takeGoodsConfMap.begin();take_it != takeGoodsConfMap.end() && !dishPtSet.empty();++take_it)
	{
		confDish = take_it->second;
		
		/*消息触发方式*/
		if(confDish->getTrigFlg())
		{
			dishPt_it = dishPtSet.rbegin();
			dishPt = *dishPt_it;	
			newDish = confDish->copyTakeGoods(dishPt,true);
			
			if(newDish == NULL)
			{
				cout<<"Map_Inform::brushTable newDish is NULL:"<<mapId<<endl;
				return;
			}			
			dishPtSet.erase(dishPt);
			takeGoodsMap[newDish->getTakeId()] = newDish;	
			newDish->setLogicMap(this);		
			newDish->brushMsg();
		}
	}
}

/*资源战中刷出资源数,默认为资源战资源*/
void Map_Inform::brushTakeSource(int _num,bool isPartyWar,int _flagA)
{
	if(_num <= 0)
	{
		cout<<"the argument is error:"<<_num<<endl;
		return;
	}
	TakeGoods *takeResource;
	map<string,TakeGoods*>::iterator take_it;	
	
	for(take_it = takeGoodsMap.begin();_num > 0 && take_it != takeGoodsMap.end();++take_it)
	{
		takeResource = take_it->second;
	
		/*是阵营资源战里面的可采集资源，且还木有被刷出来*/
		if(takeResource->getIsCampSource() && !takeResource->getIsUsed())
		{
			/*如果是帮派战旗*/
			if(isPartyWar)
			{
				if(takeResource->getTaskStyle() == 3)
				{
					if(_flagA == 0 && strncmp(takeResource->getTypeId(),"item114",7) == 0)
					{
						takeResource->brushMsg();
						takeResource->setIsUsed(true);
						--_num;
					}
					
					else if(_flagA == 1 && strncmp(takeResource->getTypeId(),"item115",7) == 0)
					{
						takeResource->brushMsg();
						takeResource->setIsUsed(true);
						--_num;
					}
					
				}
			}
			else
			{				
				/*如果是资源战中的资源（不是帮派战旗）*/
				Point resultPt;
				if(randRescePt(resultPt))
				{
					takeResource->setLocation(resultPt);
					takeResource->brushMsg();
					takeResource->setIsUsed(true);
					--_num;
				}				
			}
			
		}
		
	}
	
	if(_num > 0 && take_it == takeGoodsMap.end())
	{
		cout<<"the num of last is not enough:"<<_num<<endl;
	}
}


/*重置可摘取物品的数据*/
void Map_Inform::initTakeGoods(void)
{
	TakeGoods *takeGoods;
	map<string,TakeGoods*>::iterator take_it;	
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();++take_it)
	{
		takeGoods = take_it->second;	
		takeGoods->disperMsg();
		takeGoods->initTakeGoods();		
	}
	
}


/*点菜*/
TakeGoods* Map_Inform::olderKandy(char *dishId,char *deskInstId,char *_onwerId,char *_nickName)
{
	TakeGoods *newDish,*confDish;
	
	if(dishId == NULL || deskInstId == NULL || _onwerId == NULL || _nickName == NULL)
	{
		cout<<"Map_Inform::olderKandy the argument is NULL:"<<endl;
		return NULL;
	}
	
	/*add chenzhen 20130325 把空桌子换成有菜的桌子*/
	map<string,TakeGoods*>::iterator take_it;	
	take_it = takeGoodsConfMap.find(dishId);
	if(take_it == takeGoodsConfMap.end())
	{
		cout<<"not find the dishId of the confMap:"<<dishId<<endl;
		return NULL;
	}
	
	confDish = take_it->second;
	take_it = takeGoodsMap.find(deskInstId);
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::olderKandy the deskInstId is not found:"<<endl;
		return NULL;
	}
	
	newDish = take_it->second;
	
	if(newDish==NULL || _onwerId == NULL || _nickName == NULL || newDish->getIsDished())
	{
		cout<<"the newDish is NULL or dished before :"<<endl;
		return NULL;
	}
	else
	{	
		/*add chenzhen 20130325 更换桌子名称*/
		newDish->setName(confDish->getName());
		newDish->setPhotoId(confDish->getPhotoId());
		
		newDish->setDIshOwner(_onwerId);
		newDish->setDishNewNme(_nickName);	
		
		/*add chenzhen 20130325 更换桌子图片*/
		newDish->setIsDished(true);
		newDish->brushMsg();
		return newDish;
	}
}



/*系统宴请活动结束*/
void Map_Inform::activeCloseDish(void)
{
	map<string,TakeGoods*>::iterator take_it;	
	if(takeGoodsMap.empty())
	{
		cout<<"Map_Inform::activeCloseDish the takeGoodsMap is empty:"<<mapId<<endl;
		return;
	}
	
	for(take_it = takeGoodsMap.begin();take_it != takeGoodsMap.end();++take_it)
	{
		/*不是空桌子，且是系统点的菜*/
		if(take_it->second->getIsDished() && (take_it->second->getDishState() == 2))
		{
			delOneDish(const_cast<char*>((take_it->first).c_str()));
			take_it->second->setDishState(0);
			return;
		}
	}
	
	if(take_it == takeGoodsMap.end())
	{
		cout<<"Map_Inform::activeCloseDish there is not system dish:"<<mapId<<endl;
	}	
}

/*随机生成点*/
bool Map_Inform::randRescePt(Point &resultPt)
{
	/*是否给出了随机规则*/
	if(centerPt._x <= 0 || centerPt._y <= 0 || radius == 0)
	{
		cout<<"Map_Inform::randRescePt the centerPt or the radius is error:"<<mapId<<endl;
		return false;
	}
	
	int randNumX = rand() % (2 * radius) - radius ;
	
	int randNumy = rand() % (2 * radius) - radius ;
	
	
	resultPt._x = centerPt._x + randNumX;
	resultPt._y = centerPt._y + randNumy;
	
	if(judgePiex(resultPt))
	{
		/*设置相对应坐标*/
		Point logPT = MapExchangeLogical(resultPt);
		logPT._y += getBaseDigst();  
		
		if(!judgeLogPtHind(logPT))
		{
			randRescePt(resultPt);
		}
		
		return true;
	}
	else
	{
		randRescePt(resultPt);
	}
}


/*刷出任务怪*/
char* Map_Inform::brushTaskMon(Hero *hero,char *npcId,int taskType)
{
	map<string,MonsterBase *>::iterator monIt_it;
	MonsterBase *mon;
	if(monId_connect_monster.empty())
	{
		cout<<"Map_Inform::brushTaskMon the monId_connect_monster empty:"<<mapId<<endl;
		return NULL;
	}
	if(hero == NULL || npcId == NULL)
	{
		cout<<"Map_Inform::brushTaskMon the hero or npcId is NULL:"<<mapId<<endl;
		return NULL;
	}
	
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end();++monIt_it)
	{
		mon = monIt_it->second;

		/*任务怪*/
		if(mon->getOwnerAttriType() == taskType && strcmp(mon->getOwnerAttri(),npcId) == 0 && !mon->getIsUsed())
		{
			if(mon->appendTaskInfo(hero))
			{
				return mon->getIdentity();
			}
		}
	}
	
	cout<<"Map_Inform::there is not enough taskMon to brush:"<<endl;
	return NULL;
}


/*召唤n个陷阱*/
void Map_Inform::callTrap(size_t n)
{
	map<string,Trap*>::iterator trap_it; 
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end() && n > 0;++trap_it,--n)
	{
		/*没用，且又是召唤出来的*/
		if(trap_it->second->getIsCalled() && trap_it->second->getIsUsed())
		{
			trap_it->second->brushMsg();
			trap_it->second->initTimer();
		}		
	}
	
	if(n > 0)
	{
		cout<<"Map_Inform::callTrap the trap in map resource is not enough:"<<n<<endl;
	}
}

/*召唤所有陷阱*/
void Map_Inform::callTrap(const vector<string> &herIdSet)
{
	map<string,Trap*>::iterator trap_it; 
	size_t herIndex = 0;
	if(herIdSet.empty())
	{
		cout<<"Map_Inform::callTrap the herIdSet is empty:"<<mapId<<endl;
		return;
	}
	
	vector<const Hero*> herInstVec;
	getHeroInstSet(herIdSet,herInstVec);
	if(herInstVec.empty())
	{
		cout<<"Map_Inform::callTrap the herInstVec is empty:"<<mapId<<endl;
		return;
	}
	for(trap_it = trapInstMap.begin();trap_it != trapInstMap.end();++trap_it)
	{
		/*没用，且又是召唤出来的*/
		if(trap_it->second->getIsCalled() && !trap_it->second->getIsUsed())
		{			
			Point randTrapPiexPt = herInstVec[herIndex]->getLocation();
			++herIndex;
			if(herIndex >= herInstVec.size())
			{
				herIndex = 0;
			}			
			
			trap_it->second->setPiexPt(randTrapPiexPt,true);
			trap_it->second->formBornMsg();
			trap_it->second->brushMsg();
			trap_it->second->initTimer();
		}	
	}
}

/*召唤所有怪*/
void Map_Inform::callMon(MonsterBase *callBoss)
{
	map<string,MonsterBase *>::iterator monIt_it;
	MonsterBase *mon;
	
	if(monId_connect_monster.empty() || !callBoss)
	{
		cout<<"Map_Inform::callMon the monId_connect_monster empty:"<<mapId<<endl;
		return;
	}
	
	Point bossPt = callBoss->getLocation();
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end();++monIt_it)
	{
		mon = monIt_it->second;
		
		/*被召唤*/
		if(mon->getIsCallType() && !mon->getIsCalled())
		{
			Point monRandPiexPt;
			randCallMonPt(bossPt,monRandPiexPt,20);
			mon->setLocation(monRandPiexPt);
			mon->setCallBoss(callBoss);
			mon->brushMon();
		}
	}
}

/*召唤n个怪*/
void Map_Inform::callMon(size_t n)
{
	map<string,MonsterBase *>::iterator monIt_it;
	MonsterBase *mon;
	if(monId_connect_monster.empty())
	{
		cout<<"Map_Inform::callMon the monId_connect_monster empty:"<<mapId<<endl;
		return;
	}
	
	for(monIt_it = monId_connect_monster.begin();monIt_it != monId_connect_monster.end() && n > 0;++monIt_it,--n)
	{
		mon = monIt_it->second;
		
		/*被召唤*/
		if(mon->getIsCallType() && !mon->getIsCalled())
		{
			mon->brushMon();
			
			if(mon->getOwnerAttriType() == 3)
			{
				cout<<"Map_Inform::callMon(size_t n) begin:"<<mon->getIdentity()<<endl;
				cout<<"mon->getBshMsg:"<<mon->getBshMsg()<<endl;
				cout<<"Map_Inform::callMon(size_t n) end:"<<mon->getIdentity()<<endl;
			}
		}
	}
	
	if(n > 0)
	{
		cout<<"Map_Inform::callMon there is not enough monster to called:"<<n<<endl;
	}
}



void Map_Inform::getHeroInstSet(const vector<string> &herIdSet,vector<const Hero*> &herInstVec)
{
	if(herIdSet.empty())
	{
		cout<<"Map_Inform::getHeroSet the herIdSet is empty:"<<mapId<<endl;
		return;
	}
	
	for(vector<string>::const_iterator hero_it = herIdSet.begin();hero_it != herIdSet.end();++hero_it)
	{
		const Hero *trapHero = getHero(const_cast<char*>((*hero_it).c_str()));
		if(trapHero)
		{
			herInstVec.push_back(trapHero);
		}
	}
}


bool Map_Inform::randCallMonPt(const Point &bossPt,Point &resultPt,const int &bossRadius)
{
	/*是否给出了随机规则*/
	if(bossPt._x <= 0 || bossPt._y <= 0 || bossRadius == 0)
	{
		cout<<"Map_Inform::randCallMonPt the bossPt or the bossRadius is error:"<<mapId<<endl;
		return false;
	}
	
	int randNumX = rand() % (2 * bossRadius) - bossRadius ;
	
	int randNumy = rand() % (2 * bossRadius) - bossRadius ;
	
	
	resultPt._x = bossPt._x + randNumX;
	resultPt._y = bossPt._y + randNumy;
	
	if(judgePiex(resultPt))
	{
		/*设置相对应坐标*/
		Point logPT = MapExchangeLogical(resultPt);
		logPT._y += getBaseDigst();  
		
		if(!judgeLogPtHind(logPT))
		{
			randCallMonPt(bossPt,resultPt,bossRadius);
		}
		
		return true;
	}
	else
	{
		randCallMonPt(bossPt,resultPt,bossRadius);
	}
}

	
	
		