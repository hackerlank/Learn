/************************************************************
	文件名：action.h
	文件作用：类Action类的属性和方法的声明
	作者：chenzhen
	创建日期：2012.08.04
************************************************************/
#ifndef ACTION_H
#define ACTION_H
#include"astar.h"
#include"map_inform.h"
class Action
{
	Astar *astar;             //a星
	
	Map_Inform *mapNow;
	/*寻路前的条件检测*/
	bool judgeFindCondition(Point &logic,Point &logicWantGo);
	
	/*检测点的合法性*/
	bool judgeFindPt(Point &logic);
	
	/*初始化astar*/
	void initAstar(Map_Inform *map);
	
	/*换地图时,主要是宠物用*/
	void chgMapAstar(Map_Inform *map);
	
	/*初始化地图*/
	void setMap(Map_Inform *_map);
	
public:
	
	Action(void);
	
	/*初始化地图和astar*/
	void init(Map_Inform *_map);	
	
	/*寻路*/
	list<Point> findWay(Point &logic,Point &logicWantGo);	
	
	Astar* getAstar(void);
	
	/*析构函数*/
	~Action(void);	
};
#endif
	