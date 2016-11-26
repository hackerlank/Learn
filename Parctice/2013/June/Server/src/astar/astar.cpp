/******************************
* created:   2012/2/06  9:24
* 文件名：	astar.cpp
* author:       Tory 
* purpose:  Astar.h的实现文件	
* 修改：	2012.2.16
******************************/
#include "astar.h"
#include <math.h>
#include <list>
#include <vector>
#include <iostream>
#include"map_inform.h"
//Mark构造函数
Mark::Mark(int posX, int posY, Mark* pareMark, int currentG, int currentH)
{
	_pareMark = pareMark;
	_posX = posX;
	_posY = posY;
	if(pareMark != NULL)
	{
		_h = currentH;
		_g = currentG;
		_f = _g + _h;
	}
}

//拷贝构造函数
Mark::Mark(const Mark& m)
{
	
	_pareMark = m._pareMark;
	_posX = m._posX;
	_posY = m._posY;
	_h = m._h;
	_g = m._g;
	_f = m._f;
	
}
//析构函数
Mark::~Mark()
{
	
}

//=操作法重载函数
Mark& Mark::operator=(const Mark&m) 
{
	_pareMark = m._pareMark;
	_posX = m._posX;
	_posY = m._posY;
	_h = m._h;
	_g = m._g;
	_f = m._f;

	return *(this);
}


//purpose:  获得父节点
Mark* Mark::get_pareMark()
{
	return _pareMark; 
}

int Mark::get_f()
{
	return _f;
}

/*构造函数*/
Astar::Astar(Map_Inform *map_now)
{
	_mapArr = map_now->getMapHinder();
	_w_map = map_now->getRow();
	_h_map = map_now->getCol();
	int i,j=0;

	for(i=0;i<_mapArr.size();i++)
	{
		vector<bool> line;
		for(j=0;j<_mapArr[i].size();j++)
		{
			line.push_back(false);
		}
		_markFlagArr.push_back(line);
	}
}
// Astar析构函数
Astar::~Astar(){}

list<Point>& Astar::getWayArr(void)
{
	return _wayArr;
}

/******************************
* created:   2012/1/10  11:07
* purpose:  Astar寻路函数，返回list<Point>
********************************/
list<Point> Astar::findWay(Point start, Point end)
{	
	/*	
		清空上次寻路得到的路径数组，用于再次寻路
	*/
	if(!_wayArr.empty())
	{
		_wayArr.clear();	
	}

	_startX = start._x;
	_startY = start._y;
	_endX = end._x;
	_endY = end._y;
	
	//判断列越界 by benliao 2012.12.5
	if(_startX < 0 || _startX >= _mapArr.size() || _endX < 0 || _endX >= _mapArr.size())
	{
		return _wayArr;	
	}
	//判断行越界 by benliao 2012.12.5
	if(_startY < 0 || _startY >=_mapArr[_startX].size() || _endY < 0 || _endY >= _mapArr[_endX].size())
	{
		return _wayArr;
	}
	//判断寻路起点和终点是否是障碍点
	if(_mapArr[_startX][_startY] == 1 || _mapArr[_endX][_endY] == 1)
	{
		_wayArr.clear();	
		return _wayArr;
	}
	Mark* pmark = new Mark(_startX, _startY, NULL, 0, 0);
	if(pmark  == NULL)
	{
		_wayArr.clear();
                return _wayArr;
	}
	_closeList.push_back(pmark);		//将开始点加入关闭列表
	_markFlagArr[pmark->_posX][pmark->_posY] = true;	//将加入开启列表和关闭列表的点都标记为已标记
	
	int currentX = _startX;
	int currentY = _startY;
	while(true)
	{
		//将当前点周围的八个点按照条件，有选择的加入开启列表
		addOpenList(new_Mark(currentX + 1, currentY - 1, true, pmark)); 
		addOpenList(new_Mark(currentX + 1, currentY + 1, true, pmark));
		addOpenList(new_Mark(currentX - 1, currentY + 1, true, pmark));
		addOpenList(new_Mark(currentX - 1, currentY - 1, true, pmark));
		addOpenList(new_Mark(currentX    , currentY - 1, false,pmark));
		addOpenList(new_Mark(currentX    , currentY + 1, false,pmark));
		addOpenList(new_Mark(currentX - 1, currentY    , false,pmark));
		addOpenList(new_Mark(currentX + 1, currentY    , false,pmark));

		//如果开启列表为空，表示寻路失败，无路径到达终点
		if(_openList.empty())
		{
			break;
		}
		
		//对开启列表中的中mark点按_f由小到大排序，自定义排序函数compare
		_openList.sort(compare);
		pmark = _openList.front();					//获得_f最小的mark点
		_closeList.push_back(_openList.front());	//将得到的最小_f值的mark点加入关闭列表；
		_openList.pop_front();						//将得到的最小_f值的mark点从开启列表中删掉；
		
		//将当前点移至得到的最小_f值mark点位置，如若没到终点，则继续对当前点周围的八个点评分
		currentX = pmark->_posX;
		currentY = pmark->_posY;
		if(_endX == currentX && _endY == currentY)
		{
			while(pmark != NULL)
			{
				Point pt(pmark->_posX, pmark->_posY);		//从终点依次往前得到路径点（开始点最好得到，终点最先得到）			
				_wayArr.push_front(pt);					//将得到的路径点放入路径数组
				pmark = pmark->get_pareMark();			//从终点依次往前循环获取父节点，直到开始点为止
			}

			break;
		}
	}
	
	/*	
		清空开启列表，释放本次寻路时new的mark对象，
		同时将相应点的开启点标记值置0，用于下次寻路
	*/
	if(!_openList.empty())	
	{
	
		list<Mark*>::iterator it_m;
		it_m = _openList.begin();
		for(; it_m != _openList.end(); it_m++)
		{
			_markFlagArr[(*it_m)->_posX][(*it_m)->_posY] = false;	//置0上次寻路用过的开启标记点
			delete *it_m;										//释放内存
			*it_m = NULL;
		}
		_openList.clear();
	}
	
	/*	
		清空关闭列表，并释放本次寻路时
		new的mark对象，用于下次寻路
	*/
	if(!_closeList.empty())
	{
		list<Mark*>::iterator it_c;
		it_c = _closeList.begin();
		for(; it_c != _closeList.end(); it_c++)
		{
			_markFlagArr[(*it_c)->_posX][(*it_c)->_posY] = false;	//置0上次寻路用过的开启标记点
			delete *it_c;										//释放内存
			*it_c = NULL;
		}
		_closeList.clear();
	}
	
	return _wayArr;
}

/******************************
* created:   2012/1/10  11:07
* purpose:  用于list排序的比较函数
********************************/
bool compare(Mark *first, Mark *second)
{
	if(first->get_f() < second->get_f())
		 return true; 
	else 
		return false;
}


void Astar::addOpenList(Mark *pmark)
{
	if(pmark != NULL)
	{
		_openList.push_back(pmark);		
		_markFlagArr[pmark->_posX][pmark->_posY] = true;
	}
}


/******************************
* created:   2012/1/10  11:07
* purpose:  用于标记某个点并为其评分
********************************/
Mark*  Astar::new_Mark(int posX, int posY, bool isSlant, Mark* pareMark)
{
	//判断标记点是否在地图范围内
	if(posX < 0 || posY < 0 || posX >= _w_map || posY >= _h_map)
	{
		return NULL;
	} 
	//判断标记点是否为障碍灯，若是则不再对其进行评分，返回NULL
	//说明：posX相当于地图数组中所在的列,posY相对于地图数组中的行
	if(_mapArr[posX][posY] == 1)
	{
		return NULL;
	}
	//判断将要标记的点是否已经加入了开启列表，若已加入则返回NULL
	if(_markFlagArr[posX][posY] == 1)
	{
		return NULL;
	}
	//判断将要标记的点和当前点是否是斜线关系 ，如若是，需保证其周围的两个点都为可过点（防止穿墙），否则返回NULL
	/*
	说明：	posX---->将要标记点在地图数组中的列号；
			posY---->将要标记点在地图数组中的行号；
			pareMark->_posX---->将要标记点的父节点在地图数组中的列号；
			pareMark->_posY---->将要标记点的父节点在地图数组中的行号；
	*/		
	if(isSlant)
	{
		if(_mapArr[posX][pareMark->_posY] == 1 && _mapArr[pareMark->_posX][posY] == 1)
		{
			return NULL;
		}
	}
	int absX = (_endX - posX)>0 ? (_endX - posX) : (posX - _endX);
	int absY = (_endY - posY)>0 ? (_endY - posY) : (posY - _endY);

	Mark *pmark = new Mark(posX, posY, pareMark, isSlant ? SLANT : STRAIGHT, (absX+absY)*STRAIGHT);

	return pmark;
}


