/************************************************************
	文件名：dailyActive.h
	文件作用：日常活动类的申明
	作者：chenzhen
	创建日期：2012.10.25
************************************************************/
#ifndef DALY_ACTIVE_H
#define DALY_ACTIVE_H
#include"data_structure_struct.h"
#include"activeAsist.h"
#include<string>
#include"hero.h"

using namespace std;

typedef struct OffTmeStr
{
	string beginTime;    //提示开始时间
	int offTimes;       //提示次数
	int durTimes;       //每次提示间隔时间
	OffTmeStr(char *_beginTime,int _offTimes = 0,int _durTimes = 0)
	{
		beginTime = _beginTime;
		offTimes = _offTimes;
		durTimes = _durTimes;
	}
	bool operator < (const OffTmeStr &offTme) const
	{
		if(beginTime.compare(offTme.beginTime) == -1)
		{
			return true;
		}
		return false;
	}
	
	bool operator == (const OffTmeStr &offTme) const
	{
		if(beginTime.compare(offTme.beginTime) == 0)
		{
			return true;
		}
		return false;
	}
}OffTmeStr;

class DailyActive
{
	char activeId[SHOR_MID_VALUE_LENGTH + 1];	
	char openMsg[SHOR_MID_VALUE_LENGTH + 1];
	char offMsg[SHOR_MID_VALUE_LENGTH + 1];
	char mapId[SHOR_MID_VALUE_LENGTH + 1];
	Point peixPt;
	bool isOpen;	
	int level;
	set<int> whichDay;
	set<string>beginTme;
	set<string>endTme;
	set<string>peaceTme;
	set<OffTmeStr> offTme;
	
	bool offType;
	
	/*活动持续时间，秒*/
	size_t duringTmeSeconds;
	
	/*活动一开始时间，秒*/
	size_t goToTmeSeconds;
	
	/*活动还剩余时间，秒*/
	size_t lastTmeSeconds;
	
	/*活动最近某次的开始时间*/
	string someActiveBeginTme;
	
	public:
	
	DailyActive(char *_activeId,char *_mapId,set<int> _whichDay,\
	set<OffTmeStr> _offTme,set<string> _beginTme,set<string> _endTme,\
	set<string>_peaceTme,Point _peixPt,int _level);
	
	/*提前开启*/
	void formOpenMsg(void);
	
	/*设置开启标记值*/
	void setisOpen(bool _isOpen);
	
	/*获得开启标记值*/
	bool getisOpen(void);
	
	/*获得开启消息*/
	char* getOpenMsg(void);
	
	/*查看等级是否容许*/
	bool examLevel(int _level);
	
	/*把角色传送到活动开始的点*/
	bool takePart(Hero *myHero);
	
	/*获得日常活动id*/
	char* getActiveId(void);
	
	/*判断这天活动是否开启*/
	bool isRightDay(int dayInt);
	
	/*是否到达开启时间*/
	bool isBegin(char *timeNow);
	
	/*是否到达关闭时间*/
	bool isEnd(char *timeNow);
	
	/*判断在某个时间段此活动是否开启*/
	bool isMidTme(char *timeNow);
	
	/*获得某个活动的持续时间*/
	int getdurTme(void);
	
	/*开启前提示信息*/
	void formOffMsg(void);
	
	/*获得开启提示消息*/
	char* getOffMsg(void);
	
	/*提示时间是否已到如果到了，则发送消息*/
	bool isOffTme(char *timeNow);
	
	/*设置提示类型标记值*/
	void setOffType(bool _offType);
	
	/*获得和平时间*/
	int getPeaceTme(void);
	
	/*获得活动的活动开始多长时间*/
	size_t getGoToTmeSeconds(void);
	
	/*求出活动开始多长时间*/
	void formGoToTmeSeconds(void);
	
	/*获得活动的剩余时间*/
	size_t getLastTmeSeconds(void);
	
	/*打印测试活动中的时间*/
	void printTme(void);
	
	int getLimitLevel();
};
#endif