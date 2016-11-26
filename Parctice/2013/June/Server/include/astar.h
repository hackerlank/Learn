/******************************
* created:   2012/2/06  9:24
* 文件名：	astar.h
* author:       Tory 
* purpose:  
* 修改：	2012.2.16
******************************/
#ifndef __ASTAR__
#define __ASTAR__
using namespace std;
#include <list>
#include<vector>
#include <stdio.h>
#include <algorithm>
#include"data_structure_struct.h"
#define SLANT 14		//斜走评分值
#define STRAIGHT 10		//直走评分值

class Astar;
class Map_Inform;

class Mark
{
	friend class Astar;
	public:
		Mark(){};
		Mark(int posX, int posY, Mark* pareMark, int currentG, int currentH);
		Mark(const Mark& mark);				//拷贝构造函数
		Mark& operator=(const Mark &m);		//=操作符
		~Mark();

		Mark*	get_pareMark();				//获得父节点
		int		get_f();
		Point 	point();
	private:
		Mark* 	_pareMark;					//父节点
		int		_g;
		int 	_h;
		int 	_f;
		int 	_posX;
		int		_posY;
};


class Astar
{
	public:
		Astar(Map_Inform *newMap);
		~Astar();

	public:
		list<Point> 	findWay(Point start, Point end);
		list<Point>& getWayArr(void);
	private:
		int 	_startX;		//开始点横坐标
		int		_startY;		//开始点纵坐标
		int 	_endX;			//目标点横坐标
		int		_endY;			//目标点纵坐标
		int		_w_map;			//地图宽度
		int		_h_map;			//地图高度
		vector< vector<int> > _mapArr;		//地图数组信息（可过点与不可过点）
		list<Mark *>	_openList;			//	mark点开启列表，用于评分后选取最小_f值点
		list<Point> 	_wayArr;
		vector< vector <bool> >		_markFlagArr;	//用于标记某个点是否已加入开启列表或关闭列表，与地图数组对应着使用
		list<Mark *>	_closeList;					//mark点关闭列表，存放寻路时得到的一系列最小_f值点，返回路径数组后用于释放内存
	private:
		void	addOpenList(Mark *pmark);
		Mark* 	new_Mark(int posX, int posY, bool isSlant, Mark* pareMark);		
		
};

bool compare(Mark* first, Mark* second);			//自定义list比较函数，用于list排序比较

#endif
