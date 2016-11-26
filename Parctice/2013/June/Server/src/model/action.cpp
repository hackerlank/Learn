/************************************************************
	文件名：action.cpp
	文件作用：实现类Action类的方法
	作者：chenzhen
	创建日期：2012.08.04
************************************************************/
#include"action.h"

Action::Action(void)
{
	mapNow = NULL;
	astar = NULL;
}

/*初始化地图和astar*/
void Action::init(Map_Inform *_map)
{
	setMap(_map);
	initAstar(_map);
}

/*初始化astar*/
void Action::initAstar(Map_Inform *map)
{
	if(astar == NULL)
	{
        astar = new Astar(map);
    }	
}

/*初始化地图*/
void Action::setMap(Map_Inform *_map)
{
	if(_map != NULL)
	{
		mapNow = _map;	
	}
}

/*换地图时,主要是宠物用*/
void Action::chgMapAstar(Map_Inform *map)
{
	if(astar != NULL)
	{
		delete astar;
		astar = NULL;        
    }	
	astar = new Astar(map);
}

/*寻路*/
list<Point> Action::findWay(Point &logic,Point &logicWantGo)
{
	list<Point> resultRod;
	if(!judgeFindCondition(logic,logicWantGo))
	{
		return resultRod;
	}
	astar->findWay(logic,logicWantGo);
	return astar->getWayArr();
}

/*寻路前的条件检测*/
bool Action::judgeFindCondition(Point &logic,Point &logicWantGo)
{
	/*判断a星是否为空*/
	if(astar == NULL)
	{
		return false;
	}
	
	/*判断点是否相等*/
	if(logic._x == logicWantGo._x && logic._x == logicWantGo._x)
	{
		return false;
	}
	
	/*判断点的合法性*/
	if(judgeFindPt(logic) && judgeFindPt(logicWantGo))
	{			
		return true;
	}
	return false;
}

/*检测点的合法性*/
bool Action::judgeFindPt(Point &logic)
{
	/*x坐标是否越界*/
	if(logic._x < 0 && logic._x > mapNow->getRow())
	{
		return false;
	}
	
	/*y坐标是否越界*/
	if(logic._y < 0 && logic._y > mapNow->getCol())
	{
		return false;
	}
	
	/*是否为障碍点*/
	if(mapNow->getMapHinder()[logic._x][logic._y] == 1)
	{
		return false;
	}
	return true;	
}

/*析构函数*/
Action::~Action(void)
{
	if(astar != NULL)
	{
		delete astar;
		astar = NULL;
	}
	
	if(mapNow != NULL)
	{
		mapNow = NULL;
	}
}

Astar* Action::getAstar(void)
{
	return astar;
}


		