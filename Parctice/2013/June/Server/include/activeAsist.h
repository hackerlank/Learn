/************************************************************
	文件名：activeAsist.h
	文件作用：定义活动辅助函数
	作者：chenzhen
	创建日期：2012.10.25
************************************************************/

#ifndef ACTIVE_ASIST_H
#define ACTIVE_ASIST_H
#include"hero.h"
#include"map_inform.h"
class DailyActive;


typedef struct DurCampTme
{
	/*阵营战场令持续时间*/
	int campBatFldOlder;
	
	/*欢乐斗持续时间*/
	int camphappyFight;
	
	/*阵营争夺战持续时间*/
	int campcompeteFight;
	
	/*武林盟主持续时间*/
	int kungFuMaster;
	
	/*报名持续时间*/
	int takePartDurTme;
	
	/*阵营争夺战和平时间*/
	int campPeaceTme;
	
	/*武林盟主战和平时间*/
	int kungPeaceTme;
	
	DurCampTme(int odlerTme = 0,int fightTme = 0,int competeTme = 0,\
	int masterTme = 0,int _takeTme = 0,int _campPeaceTme = 0,\
	int _kungPeaceTme = 0)
	{
		campBatFldOlder = odlerTme;
		camphappyFight = fightTme;
		campcompeteFight = competeTme;
		kungFuMaster = masterTme;
		takePartDurTme = _takeTme;
		campPeaceTme = _campPeaceTme;
		kungPeaceTme = _kungPeaceTme;
	}
	
	/*测试打印内容*/
	void printDurTme(void)
	{
		cout<<"test the struct DurCampTme begin:"<<endl;
		cout<<"campBatFldOlder:"<<campBatFldOlder<<endl;
		cout<<"camphappyFight:"<<camphappyFight<<endl;
		cout<<"campcompeteFight:"<<campcompeteFight<<endl;
		cout<<"kungFuMaster:"<<kungFuMaster<<endl;
		cout<<"campPeaceTme:"<<campPeaceTme<<endl;
		cout<<"kungPeaceTme:"<<kungPeaceTme<<endl;
		cout<<"test the struct DurCampTme end:"<<endl;
	}
		
}DurCampTme;

/*传送到活动地点*/
bool sendInMapPoint(Map_Inform *mapSend,Point piexPtSend,Hero *myHero);

/*活动面板响应函数*/
void activePanelResponse(Hero *owner);

/*把int的时间变成字符型*/
bool timeToStr(int hour,int min,char *tmeStr,int lengStr);

/*把字符型时间转换成int型*/
bool tmeStrChgInt(int &hour,int &min,char *timStr);

/*比较两个时间的大小，如果前者小于后者，则返回真*/
bool timeLess(int &hour1,int &min1,int &hour2,int &min2);

/*比较2个时间，如果前者小，则返回真*/
bool timeStrLess(char *timStr1,char *timStr2);

/*控制整个活动的开启与关闭*/
void controlActiveOpenAndClose(int hour,int min,int whichDay);

/*开启活动*/
void openActive(DailyActive *active);

/*关闭活动*/
void closeActive(DailyActive *active);

/*开启服务器时，判断在此时，哪些活动应该开始*/
void controlActiveOpenStartServer(int hour,int min,int whichDay);

/*服务器开启时，初始化阵营活动的持续时间*/
void initCampeDurTme(void);

/*开启帮派探营活动*/
void openCampActive(void);

/*关闭帮派探营活动*/
void closeCampActive(void);

//刷新全服日常
void refreshSrvDaily();

/*开启帮派盛宴活动*/
void openDishActive(void);

/*关闭帮派盛宴活动*/
void closeDishActive(void);

/*设置帮派盛宴活动是否为今天的标记值*/
void setDishTodayActiveFlg(void);

/*设置关闭帮派盛宴活动是否为今天的标记值*/
void setCloseDishTodayActiveFlg(void);

/*设置关闭帮派盛宴活动是否为今天的标记值,测试用*/
void setCloseDishTodayActiveFlgTset(void);

#endif