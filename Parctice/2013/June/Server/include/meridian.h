/****************************************************************
 * Filename: meridian.h
 * 
 * Description: 经脉
 *
 * Original Author : bison, 2012-7-13
 *
 ****************************************************************/

#ifndef _MERIDIAN_H_
#define _MERIDIAN_H_

#include"libev.h"
#define MAX_MERIDIAN_LEVEL		90

typedef enum
{
	RENM,			//任脉
	DUM,			//督脉
	CHONGM,			//冲脉
	DAIM,			//带脉
	YINW,			//阴维
	YANGW,			//阳维
	YINQ,			//阴跷
	YANGQ			//阳跷
}MERID_TYPE_T;

typedef struct MeridItem_S
{
	int needHeroLevel[100];
	int time[100];
	int incType1[100];
	int incVal1[100];
	int incTotalVal1[100];
	int incType2[100];
	int incVal2[100];
	int incTotalVal2[100];
} MeridItem_T;

typedef struct MeridConf_S
{
	int startLevel;					//开始修炼经脉等级
	int needBoundGoldPerFiveMin;	//每减少5分钟经脉修炼时间需要绑定元宝数
	MeridItem_T item[8];
} MeridConf_T;

extern MeridConf_T heroMeridConf;			//人物经脉配置

typedef struct MeridData_S
{
	int now;
	int level;
	bool timerBusy;
	int remainTime;
	MeridData_S()
	{
		now = 7;
		level = 0;
		timerBusy = false;
		remainTime = 0;
	}
	void operator =(const MeridData_S &data)
	{
		//memcpy(acc, data.acc, sizeof(acc));
		//memcpy(fin, data.fin, sizeof(fin));
		now = data.now;
		level = data.level;
		timerBusy = data.timerBusy;
		remainTime = data.remainTime;
	}
}MeridData_T;

class Meridian
{
	private:
		MERID_TYPE_T now;			//当前已经达到的经脉点
		int level;					//经脉等级，据策划的方案可以把普通等级和强化等级作为一个变量保存 
		ev_timer *meridTimer;		//经脉计时器
		bool timerBusy;				//是否在修炼
	public:
		Meridian();
		Meridian(MERID_TYPE_T _now, int _level);
		//有memcache上来的数据来恢复
		Meridian(MeridData_T meridData);
		~Meridian();
		//经脉升级
		bool upgrade();
		//经脉强化
		bool strengthen();
		MERID_TYPE_T getNow();
		int getLevel();
		ev_timer* getTimer();
		//获取定时器是否占用
		bool getTimerBusy();
		//设置定时器占用
		void setTimerBusy(bool busy);
		//获取经脉所加属性总值
		int getIncTotalVal(int &val1, int &val2, int now);
};

#endif
