/************************************************************
	文件名：brutype.cpp
	文件作用：类BruType类方法的实现
	作者：chenzhen
	创建日期：2012.08.15
************************************************************/
#include"bruType.h"
#include"monsterBase.h"
#include"map_inform.h"
#include"monsterActive.h"
#include"monsterPassivity.h"
#include"monsterPatrol.h"
BruType::BruType(map<string,MonsterBase *>& _monId_connect_monster,\
				 map<string,BruMonInfor*>& _brushMonInform,double _time,\
				 bool _allFlg,bool _apply,GroupBrush *_groupBrush)
{
	monId_connect_monster = _monId_connect_monster;
	brushMonInform = _brushMonInform;	
	time = _time;	
	allFlg = _allFlg;	
	apply = _apply;
	mapTmeCtn = ceil(_time/MAP_THINK_TIME);
	starCtn = 0;
	groupBrush = _groupBrush;
	initMonBruStu();
	againBru = false;
}

/*判断刷怪时间是否到期*/
bool BruType::judgeTme(void)           
{
	if(starCtn >= mapTmeCtn)
	{
		starCtn = 0;
		return true;
	}
	else
	{
		starCtn++;
		return false;
	}
}

/*通过传入参数判断怪物类型号*/
bool BruType::judgebrushMonTpy(int _monTyp)
{
	
	if(_monTyp == 1)
	{
		eachBru.generNum++;
		return true;
	}
	else if(_monTyp == 2)
	{
		eachBru.eliteNum++;
		return true;
	}
	else if(_monTyp == 3)
	{
		eachBru.bossNum++;
		return true;
	}
	else if(_monTyp == 4)
	{
		eachBru.activeNum++;
		return true;
	}
	if(_monTyp == 5)
	{
		eachBru.passNum++;
		return true;
	}
	else if(_monTyp == 6)
	{
		eachBru.patNum++;
		return true;
	}
	else
	{
		return false;
	}
}

/*通过传入参数判断和输出怪物相对应int型的类型号*/
int BruType::typeMatchInt(MonsterBase *mon,bool _flgKind)
{
	if(_flgKind)
	{
		if(judgeGenerNum() && strcmp(mon->getKind(),"General") == 0)
		{
			return 1;
		}
		else if(judgeEliteNum() || strcmp(mon->getKind(),"Elite") == 0)
		{
			return 2;
		}
		else if(judgeBossNum() || strcmp(mon->getKind(),"Boss") == 0)
		{
			return 3;
		}
	}
	else
	{
		if(judgeActiveNum() || strcmp(mon->getType(),"Active") == 0)
		{
			return 4;
		}
		else if(judgePassNum() || strcmp(mon->getType(),"Passivity") == 0)
		{
			return 5;
		}
		else if(judgePatNum() || strcmp(mon->getType(),"Patrol") == 0)
		{
			return 6;
		}
	}
	return -1;
}

/*判断普通怪数量是否刷够*/
bool BruType::judgeGenerNum(void)
{
	return eachBru.generNum < monBruNumSdu.generNum;
}

/*判断精英怪数量是否刷够*/
bool BruType::judgeEliteNum(void)
{
	return eachBru.eliteNum < monBruNumSdu.eliteNum;
}
	
/*判断主动怪数量是否刷够*/
bool BruType::judgeActiveNum(void)
{
	return eachBru.activeNum < monBruNumSdu.activeNum;
}
	
/*判断被动怪数量是否刷够*/
bool BruType::judgePassNum(void)
{
	return eachBru.passNum < monBruNumSdu.passNum;
}
	
/*判断巡逻怪数量是否刷够*/
bool BruType::judgePatNum(void)
{
	return eachBru.patNum < monBruNumSdu.patNum;
}
	
/*判断BOSS怪数量是否刷够*/
bool BruType::judgeBossNum(void)
{
	return eachBru.bossNum < monBruNumSdu.bossNum;
}
	
/*判断所有怪数量是否刷够*/
bool BruType::judgeSum(void)
{
	return eachBru.sum < monBruNumSdu.sum;
}


/*刷怪外部接口,供地图调用*/
void BruType::brushMonFun(int _Cpyflg)
{
	/*刷怪时间没到*/
	if(!judgeTme())
	{
		return;
	}
	/*全刷只刷一次*/
	if(againBru && _Cpyflg)
	{
		return;
	}
	
	if(allFlg)
	{
		/*全刷*/
		brushAllMon();
		againBru = true;
	}
	else
	{
		if(!apply)
		{
			/*按模式刷*/
			brushMonByModle();
		}
		else
		{
			/*补刷*/
			return;
		}
	}
}

/*初始化刷怪记录表的迭代器*/		
void BruType::initBruIt(void)         
{
	bruMon_it = brushMonInform.begin();
}

/*一次性全刷出*/
void BruType::brushAllMon(void)
{
	MonsterBase *monBru;
	set<string>::iterator bru_it;
	monBru = NULL;
	bruMon_it = brushMonInform.begin();
	while(bruMon_it != brushMonInform.end())
	{
		if(bruMon_it->second->getBushMonId().empty())
		{
			bruMon_it++;
			continue;
		}
		for(bru_it = bruMon_it->second->getBushMonId().begin();\
			bru_it != bruMon_it->second->getBushMonId().end();\
			)
		{	
			monBru = getMon(const_cast<char*>((*bru_it).c_str()));
			if(monBru == NULL)
			{
				bru_it++;
				continue;
			}
			monBru->brushMon();		
			bruMon_it->second->inputOneLve(const_cast<char *>((*bru_it).c_str()));
			bruMon_it->second->getBushMonId().erase(bru_it);			
			bru_it++;
			// bruMon_it->second->InputLiveId(const_cast<char *>((*bru_it).c_str()));
		}
		bruMon_it++;
	}
	if(bruMon_it == brushMonInform.end())
	{
		bruMon_it = brushMonInform.begin();
	}
}

/*按模式刷怪*/
void BruType::brushMonByModle(void)
{
	MonsterBase *monBru;
	set<string>::iterator bru_it;
	bool flg;
	int flgMonTyp;
	
	monBru = NULL;	
	flgMonTyp = -1;
	
	while(bruMon_it != brushMonInform.end() && judgeSum())
	{
		if(bruMon_it->second->getBushMonId().empty())
		{
			bruMon_it++;
			continue;
		}
		for(bru_it = bruMon_it->second->getBushMonId().begin();\
			bru_it != bruMon_it->second->getBushMonId().end();\
			)
		{	
			monBru = getMon(const_cast<char*>((*bru_it).c_str()));
			if(monBru == NULL)
			{
				bru_it++;
				continue;
			}
			flgMonTyp = typeMatchInt(monBru);
			if(judgebrushMonTpy(flgMonTyp))
			{
				monBru->brushMon();
				bruMon_it->second->inputOneLve(const_cast<char *>((*bru_it).c_str()));
				bruMon_it->second->getBushMonId().erase(bru_it);
				bru_it++;
				// bruMon_it->second->InputLiveId(const_cast<char *>((*bru_it).c_str()));
			}
		}
		bruMon_it++;
	}
	if(bruMon_it == brushMonInform.end())
	{
		bruMon_it = brushMonInform.begin();
	}
}				
	
/*通过怪物id获得怪物实例指针*/
MonsterBase* BruType::getMon(char *monId)
{
	if(monId == NULL)
	{
		return NULL;
	}
	map<string,MonsterBase*>::iterator mon_it;
	mon_it = monId_connect_monster.find(monId);
	if(mon_it == monId_connect_monster.end())
	{
		return NULL;
	}
	return mon_it->second;
}	

/*复制怪物实例以及和刷怪记录表*/	
void BruType::copyMapMon(map<string,MonsterBase*> &newMonIn,\
						map<string,BruMonInfor*> &newBrushInt,\
						char *newMapId)
{
	map<string,MonsterBase*>::iterator mon_it;
	map<string,BruMonInfor*>::iterator typeId_it;	

	string typeId;
	MonsterBase *newMon;	
	
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{		 
		/*复制一个怪物实例*/		
		newMon = NULL;  
		newMon = mon_it->second->copyMon(newMapId);	
		
		/*生成刷怪记录表*/
		typeId =  newMon->getTypeId();		
		typeId_it = newBrushInt.find(typeId);
		
		if(typeId_it == newBrushInt.end())
		{
			BruMonInfor *node = new BruMonInfor(const_cast<char *>(typeId.c_str()),0,0,0);
			node->inputBruId(newMon->getIdentity());			
			newBrushInt[typeId] = node;				
		}		
		else
		{
		
			typeId_it->second->inputBruId(newMon->getIdentity());
		}
		newMonIn[newMon->getIdentity()] = newMon;	
	}
}

/*初始化刷怪各数目标准*/
void BruType::initMonBruStu(void)
{
	if(groupBrush != NULL)
	{
		monBruNumSdu = groupBrush->getMonGroNum(sum);
	}
}

/*复制刷怪模式*/
BruType* BruType::copyBruTpy(char *newMapId)
{
	BruType *newBruTpy;
	GroupBrush *newGroBru;
	newBruTpy = NULL;
	newGroBru = NULL;
	map<string,MonsterBase*> newMonIn;
	map<string,BruMonInfor*> newBrushInt;
	copyMapMon(newMonIn,newBrushInt,newMapId);
	if(groupBrush != NULL)
	{
		newGroBru = groupBrush->CopyGroBru();
	}
	newBruTpy = new BruType(newMonIn,newBrushInt,time,\
							allFlg,apply,newGroBru);
	return newBruTpy;
}

/*重置那些还活着的怪物*/
void BruType::initLveMon(void)
{
	map<string,MonsterBase *>::iterator monLiv_it;
	for(monLiv_it = monId_connect_monster.begin();\
		monLiv_it != monId_connect_monster.end();monLiv_it++)
	{
		if(monLiv_it->second->getLifeStation() == LIVE)
		{
			monLiv_it->second->die();
		}
	}
}

/*重置地图刷怪记录表信息*/
void BruType::initBrushRed(void)
{	
	map<string,BruMonInfor*>::iterator brush_it; 	
	for(brush_it = brushMonInform.begin();brush_it != brushMonInform.end();brush_it++)
	{
		brush_it->second->initBrush();		
	}
}

/*还原刷怪模式*/
void BruType::initBruTpy(void)
{
	initLveMon();
	initBrushRed();
	starCtn = 0;
	eachBru.initMonGroNum();
}

/*析构函数*/
BruType::~BruType(void)
{
	/*析构此地图的怪物记录表*/
	map<string,BruMonInfor*>::iterator brush_it; 	
	BruMonInfor *brush = NULL;
	for(brush_it = brushMonInform.begin();brush_it != brushMonInform.end();brush_it++)
	{
		brush = brush_it->second;
		delete brush;
		brush = NULL;
	}
	brushMonInform.clear();
	
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
	
	/*析构批次刷怪实例*/
	if(groupBrush != NULL)
	{
		delete groupBrush;
		groupBrush = NULL;
	}
}

/*暂停此地图上所有怪的思考,后面也许会以九宫格为单位*/
void BruType::stopMonThk(void)
{
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->stopThk();
	}
}


/*启动此地图上所有怪的思考,后面也许会以九宫格为单位*/
void BruType::reSetMonThk(void)
{
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it)
	{
		mon_it->second->resetTimer();
	}
}

/*获得现存活怪的数量*/
int BruType::getLveMonNum(void)
{
	int monNum = 0;
	map<string,BruMonInfor*>::iterator bruMon_it;
	for(bruMon_it = brushMonInform.begin();bruMon_it != brushMonInform.end();bruMon_it++)
	{
		monNum += bruMon_it->second->getSumCnt();
	}
	return monNum;
}

/*获得总怪的数量*/
int BruType::getAllMonNum(void)
{
	int monNum = 0;
	monNum = monId_connect_monster.size();
	return monNum;
}


/*打印测试怪物信息*/
void BruType::printMonsterInform(void)
{
	map<string,MonsterBase*>::iterator mon_it;
	map<string,BruMonInfor*>::iterator typeId_it;	
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
	
	/*测试怪物记录表*/
	map<string,BruMonInfor*>::iterator brush_it; 	
	BruMonInfor *brush = NULL;
	for(brush_it = brushMonInform.begin();brush_it != brushMonInform.end();brush_it++)
	{
		
		brush = brush_it->second;
		set<string> monsId;
		set<string>::iterator monId_it;
		
		cout<<"TyId:"<<brush->getTyId()<<endl;
		cout<<"number:"<<brush->getBushMonId().size()<<endl;
		monsId = brush->getBushMonId();
		for(monId_it = monsId.begin(); monId_it != monsId.end();monId_it++)
		{
			cout<<"monsterId:"<<*monId_it<<endl;
		}
		
		brush = NULL;
	}
}

/*设置所有在此地图上的怪的地图指针*/
void BruType::setMonMap(Map_Inform *_map) 
{
	map<string,MonsterBase*>::iterator mon_it;
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		mon_it->second->setMap(_map);
	}
}

/*获得此地图所有怪物类型id集合*/
void BruType::getTypeMonOneMap(set<string> &monAllType)
{		
	/*注意，此处是所有，包括已死的*/
	map<string,BruMonInfor*>::iterator brush_it; 
	for(brush_it = brushMonInform.begin();brush_it != brushMonInform.end();brush_it++)
	{
		monAllType.insert(brush_it->first);		
	}
}

/*获得整个怪物信息*/

/*
map<string,MonsterBase*>& BruType::getMonId_connect_monster(void)
{
	return monId_connect_monster;
}
*/

/*获得怪物记录表*/
/*  
map<string,BruMonInfor*>& BruType::getBrushMonInform(void)
{
	return brushMonInform;
}
*/

/*获得整个怪物信息*/
void BruType::getAllMonObj(vector<MonsterBase*> &monObj)
{
	map<string,MonsterBase*>::iterator mon_it;
	
	for(mon_it = monId_connect_monster.begin();mon_it != monId_connect_monster.end();mon_it++)
	{
		monObj.push_back(mon_it->second);
	}
}

/*怪物死亡函数里调用,放进怪物死亡容器中*/
bool BruType::monIdInputDie(char *monTypId,char *monId)
{
	map<string,BruMonInfor*>::iterator bruMon_it;
	bruMon_it = brushMonInform.find(monTypId);
	if(bruMon_it != brushMonInform.end())	
	{
		cout<<"test in monIdInput befor:"<<endl;
		bruMon_it->second->testPrintDie();
		bruMon_it->second->InputDieId(monId);
		cout<<"test in monIdInput aftere:"<<endl;
		bruMon_it->second->testPrintDie();
		return true;
	}
	return false;
}

/*怪物析构函数里调用，删除在地图里面的信息*/
bool BruType::EraInMap(char *monId)
{
	map<string,MonsterBase*>::iterator mon_it;	
	mon_it = monId_connect_monster.find(monId);
	if(mon_it != monId_connect_monster.end())
	{		
		monId_connect_monster.erase(mon_it);
		return true;
	}
	return false;
}

/*怪物死亡函数里调用,直接删除*/
bool BruType::monIdErase(char *monTypId,char *monId)
{
	map<string,BruMonInfor*>::iterator bruMon_it;
	set<string>::iterator monId_it;
	bruMon_it = brushMonInform.find(monTypId);
	if(bruMon_it != brushMonInform.end())
	{
		monId_it = bruMon_it->second->getLivMonId().find(monId);
		if(monId_it == bruMon_it->second->getLivMonId().end())
		{
			bruMon_it->second->getLivMonId().erase(monId_it);
			return true;
		}
	}
	return false;
}

/*普通场景怪物复活*/
void BruType::exchageDieMon(void)
{
	map<string,BruMonInfor*>::iterator bru_it;
	for(bru_it = brushMonInform.begin();bru_it != brushMonInform.end();bru_it++)
	{		
		bruMon_it->second->exchage();
	}
}