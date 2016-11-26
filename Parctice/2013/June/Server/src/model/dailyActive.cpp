/************************************************************
	文件名：dailyActive.cpp
	文件作用：日常活动类的实现
	作者：chenzhen
	创建日期：2012.10.25
************************************************************/
#include"command_other_function_all_over.h"
#include "systemMessage.h"
#include"dailyActive.h"
#include"map_src.h"
#include"my_time.h"

extern map<string,Map_Src*>mapId_connect_map;
static struct tm* timeNow;

DailyActive::DailyActive(char *_activeId,char *_mapId,set<int> _whichDay,\
set<OffTmeStr> _offTme,set<string> _beginTme,set<string> _endTme,\
set<string>_peaceTme,Point _peixPt,int _level)
{
	memset(activeId,'\0',sizeof(activeId));
	memset(mapId,'\0',sizeof(mapId));
	memset(openMsg,'\0',sizeof(openMsg));
	memset(offMsg,'\0',sizeof(offMsg));
	strncpy(activeId,_activeId,strlen(_activeId));	
	strncpy(mapId,_mapId,strlen(_mapId));
	
	peixPt = _peixPt;
	level = _level;
	isOpen = false;
	whichDay = _whichDay;
	beginTme = _beginTme;
	endTme = _endTme;
	offType = true;     //如果为活动开启前提示，则为true;
	
	offTme = _offTme;
	peaceTme = _peaceTme;
	
	duringTmeSeconds = 0;
	lastTmeSeconds = 0;
	goToTmeSeconds = 0;
	int durTme = getdurTme();
	if(durTme < 0)
	{
		cout<<"DailyActive::DailyActive the during time is error:"<<activeId<<endl;
	}
	else
	{
		duringTmeSeconds = getdurTme();
	}
	
}

/*提前开启*/
void DailyActive::formOpenMsg(void)
{
	int flg;
	
	memset(openMsg,'\0',SHOR_MID_VALUE_LENGTH + 1);
	
	if(isOpen)
	{
		flg = 1;		
	}
	else
	{
		flg = 0;		
	}
	sprintf(openMsg + strlen(openMsg),"%d,%d,%s,%d",\
			2,16,activeId,flg);
}

/*开启前提示信息*/
void DailyActive::formOffMsg(void)
{	
	int flag;
	
	/*开启前提示*/
	if(offType)
	{
		/*如果活动已开启*/
		if(isOpen)
		{
			return;
		}
		flag = 1;
		offType = false;
	}
	
	/*关闭前提示*/
	else
	{
		/*如果活动已关闭*/
		if(!isOpen)
		{
			return;
		}
		flag = 0;
		offType = true;
	}

	memset(offMsg,'\0',sizeof(offMsg));
	sprintf(offMsg,"%d,%d,%s,%d",2,17,activeId,flag);
}

/*设置开启标记值*/
void DailyActive::setisOpen(bool _isOpen)
{
	isOpen = _isOpen;
}

/*获得开启标记值*/
bool DailyActive::getisOpen(void)
{
	return isOpen;
}

/*获得开启消息*/
char* DailyActive::getOpenMsg(void)
{
	return openMsg;
}

/*获得开启提示消息*/
char* DailyActive::getOffMsg(void)
{
	return offMsg;
}

/*查看等级是否容许*/
bool DailyActive::examLevel(int _level)
{
	return level <= _level;
}

/*把角色传送到活动开始的点*/
bool DailyActive::takePart(Hero *myHero)
{
	if(myHero == NULL)
	{
		cout<<"the hero of takePart is NULL:"<<endl;
		return false;
	}
	
	Map_Src *myMap;
	map<string,Map_Src*>::iterator src_it;
	src_it = mapId_connect_map.find(mapId);
	if(src_it == mapId_connect_map.end())
	{
		cout<<"the map is error:"<<mapId<<endl;
		return false;
	}
	
	myMap = src_it->second;	
	return sendInMapPoint(myMap,peixPt,myHero);
}

/*获得日常活动id*/
char* DailyActive::getActiveId(void)
{
	return activeId;
}
	
/*判断这天活动是否开启*/
bool DailyActive::isRightDay(int dayInt)
{
	set<int>::iterator day_it;
	if(whichDay.empty())
	{
		return true;
	}
	day_it = whichDay.find(dayInt);
	if(day_it == whichDay.end())
	{
		return false;
	}
	return true;
}

/*是否到达开启时间*/
bool DailyActive::isBegin(char *timeNow)
{
	set<string>::iterator begin_it;
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	begin_it = beginTme.find(timeNow);
	if(begin_it == beginTme.end())
	{
		return false;
	}
	
	someActiveBeginTme = timeNow;
	
	return true;
}

/*是否到达关闭时间*/
bool DailyActive::isEnd(char *timeNow)
{
	set<string>::iterator end_it;
	set<string>::iterator peace_it;
	
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	
	/*和平时间*/
	if(!peaceTme.empty())
	{
		peace_it = peaceTme.find(timeNow);	
		if(peace_it != peaceTme.end())
		{
			cout<<"the peace time is now:"<<activeId<<endl;
			return true;
		}
	}
	
	end_it = endTme.find(timeNow);
	if(end_it == endTme.end())
	{
		return false;
	}
	
	lastTmeSeconds = 0;
	goToTmeSeconds = 0;
	someActiveBeginTme.clear();
	
	return true;
}

/*判断在某个时间段此活动是否开启*/
bool DailyActive::isMidTme(char *timeNow)
{	
	set<string>::iterator end_it;
	set<string>::iterator begin_it;
	
	if(timeNow == NULL || strlen(timeNow) ==0)
	{
		cout<<"the argument is empty:"<<endl;
		return false;
	}
	for(begin_it = beginTme.begin(),end_it = endTme.begin();\
		begin_it != beginTme.end() && end_it != endTme.end();\
		++begin_it,++end_it)
	{
		if((*begin_it).compare(timeNow) <= 0 && (*end_it).compare(timeNow) == 1)
		{
			someActiveBeginTme = *begin_it;
			return true;
		}
	}
}

/*获得某个活动的持续时间*/
int DailyActive::getdurTme(void)
{
	int hour1,min1,hour2,min2;
	int result;
	set<string>::iterator begin_it,end_it;
	if(beginTme.empty() || endTme.empty())
	{
		cout<<"the beginTme and the endTme is empty:"<<activeId<<endl;
		return -1;
	}
	
	begin_it = beginTme.begin();
	end_it = endTme.begin();
	
	if(!tmeStrChgInt(hour1,min1,const_cast<char *>((*begin_it).c_str())))
	{
		cout<<"the begin_it is error:"<<*begin_it<<endl;
		return -1;
	}
	if(!tmeStrChgInt(hour2,min2,const_cast<char *>((*end_it).c_str())))
	{
		cout<<"the end_it is error:"<<*end_it<<endl;
		return -1;
	}
	// cout<<"test begin:"<<activeId<<endl;
	// cout<<"begin_it:"<<*begin_it<<endl;
	// cout<<"hour1:"<<hour1<<"  min1:"<<min1<<endl;
	// cout<<"end_it:"<<*end_it<<endl;
	// cout<<"hour2:"<<hour2<<"  min2:"<<min2<<endl;
	// cout<<"test end:"<<activeId<<endl;
	return (hour2 - hour1) * 3600 + (min2 - min1) * 60;
}

/*提示时间是否已到如果到了，则发送消息*/
bool DailyActive::isOffTme(char *timeNow)
{
	set<OffTmeStr>::iterator off_it;
	
	if(timeNow == NULL || strlen(timeNow) == 0 || offTme.empty())
	{
		return false;
	}
	OffTmeStr tmeNow(timeNow);
	
	off_it = offTme.find(tmeNow);
	if(off_it == offTme.end())
	{
		return false;
	}
	
	/*更新提示消息*/
	formOffMsg();
	
	/*发送全服公告*/
	SYSTEM_MESSAGE::systemActivityMsg(offMsg,(*off_it).offTimes,(*off_it).durTimes,level);
	
	return true;
}

/*设置提示类型标记值*/
void DailyActive::setOffType(bool _offType)
{
	offType = _offType;
}

/*获得和平时间*/
int DailyActive::getPeaceTme(void)
{
	int hour1,min1,hour2,min2;
	int result;
	set<string>::iterator begin_it,end_it;
	if(beginTme.empty() || peaceTme.empty())
	{
		cout<<"the beginTme and the peaceTme is empty:"<<activeId<<endl;
		return -1;
	}
	
	begin_it = beginTme.begin();
	end_it = peaceTme.begin();
	
	if(!tmeStrChgInt(hour1,min1,const_cast<char *>((*begin_it).c_str())))
	{
		cout<<"the begin_it is error:"<<*begin_it<<endl;
		return -1;
	}
	if(!tmeStrChgInt(hour2,min2,const_cast<char *>((*end_it).c_str())))
	{
		cout<<"the end_it is error:"<<*end_it<<endl;
		return -1;
	}
	// cout<<"test begin:"<<activeId<<endl;
	// cout<<"begin_it:"<<*begin_it<<endl;
	// cout<<"hour1:"<<hour1<<"  min1:"<<min1<<endl;
	// cout<<"end_it:"<<*end_it<<endl;
	// cout<<"hour2:"<<hour2<<"  min2:"<<min2<<endl;
	// cout<<"test end:"<<activeId<<endl;
	return (hour2 - hour1) * 3600 + (min2 - min1) * 60;
}

/*求出活动开始多长时间*/
void DailyActive::formGoToTmeSeconds(void)
{
	if(someActiveBeginTme.empty())
	{
		cout<<"DailyActive::formGoToTmeSeconds the someActiveBeginTme is empty:"<<activeId<<endl;
		return;
	}
	int beginhour = -1, beginmin = -1;
	/*把字符型时间转换成int型*/
	if(!tmeStrChgInt(beginhour,beginmin,const_cast<char *>(someActiveBeginTme.c_str())) || beginhour < 0 || beginmin < 0)
	{
		cout<<"DailyActive::formGoToTmeSeconds the someActiveBeginTme is error:"<<activeId<<endl;
		return;
	}
	
	gettimeofday(&myTime, NULL);	
	timeNow = localtime(&myTime.tv_sec);
	
	int totalSeconds = (timeNow->tm_hour - beginhour) * 3600 + (timeNow->tm_min - beginmin) * 60 + timeNow->tm_sec;
	
	if(totalSeconds > 0)
	{
		goToTmeSeconds = totalSeconds;
	}
}

/*获得活动的活动开始多长时间*/
size_t DailyActive::getGoToTmeSeconds(void)
{
	formGoToTmeSeconds();
	return goToTmeSeconds;
}

/*获得活动的剩余时间*/
size_t DailyActive::getLastTmeSeconds(void)
{
	int lastTme;
	formGoToTmeSeconds();
	lastTme = duringTmeSeconds - goToTmeSeconds;
	if(lastTme <=0 || goToTmeSeconds == 0)
	{
		lastTmeSeconds = 0;
	}
	else
	{
		lastTmeSeconds = lastTme;
	}
	return lastTmeSeconds;
}

/*打印测试活动中的时间*/
void DailyActive::printTme(void)
{
	cout<<"the activeId begin:"<<activeId<<endl;
	cout<<"duringTmeSeconds:"<<duringTmeSeconds<<endl;
	cout<<"goToTmeSeconds:"<<getGoToTmeSeconds()<<endl;
	cout<<"lastTmeSeconds:"<<getLastTmeSeconds()<<endl;
	if(!someActiveBeginTme.empty())
	{
		cout<<"someActiveBeginTme:"<<someActiveBeginTme<<endl;
	}
	cout<<"the activeId end:"<<activeId<<endl;
}

int DailyActive::getLimitLevel()
{
	return level;
}
	
	