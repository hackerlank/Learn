/************************************************************
	文件名：cpyAsist.h
	文件作用：进副本辅助函数
	作者：chenzhen
	创建日期：2012.06.29
************************************************************/

#ifndef CPY_ASIST_H
#define CPY_ASIST_H

#include "instancing_manage.h"
#include<vector>
#include<string>

using namespace std;
class Hero;

//单身或者队长为真
bool SingleOrTeamLeader(const char* memberId);

/*判断是否为同一个帮派的人*/
bool judgeSameParty(vector<string> &heroId,char *partyId = NULL);

/*进入副本失败原因生成消息*/	
void dealFailRson(Failure_Reason* failure_reason,char *failMsg,int lengthStr,int entType = 0);

/*进入副本失败原因发送*/
void sendFailMsg(vector<string> &heroId,char *failMsg);

/*用于处理带有流水号的字符串<主要是id>，且不改变原参数*/
bool dealSerNumStr(char *resore,char *last,char *ahead,bool isLast = true,char *tok = "_");

/*退出副本*/
void outCpy(Hero *myHero);

/*副本面板相应辅助函数*/
void cpyPanelResponse(Hero *owner);

/*判断两个点之间的距离*/
bool judRange(Point &piexA,const Point &piexB,int const range);

/*初始化进副本失败结构体数据*/
bool initFailReson(Failure_Reason *reason);

/*进入帮派吃饭的地方<忠义堂>*/
void enterPartyEat(char *heroId,char *mapEatId);

/*补齐等级对应的帮派大本营地图*/
bool insertCampMap(int key,string &values);

/*插入等级对应的帮派大本营地图*/
void insertLevelCampMap(int level,string &values);

/*插入等级对应的帮派大本营地图*/
void testPrintLevelCampMap(void);

/*补齐最高等级对应的帮派大本营地图*/
void insertHightestLevelCampMap(void);

/*退出帮派大本营*/
bool outCampMap(Hero *myHero);

/*进入任务副本法海不懂爱*/
void entTaskCpy(char *heroid,char *cpyTyeId);

/*体力值面板相应辅助函数*/
void fatigueResponse(Hero *owner);

/*购买体力值*/
void purchaseFatigue(char *buffer);

/*判断是否为欢乐地图20130412 chenzhen*/
bool isHappyMap(char *newMap);

/*黑木崖副本面板相应辅助函数*/
void towerLayerCpyResponse(Hero *owner);


void entCpyAsist(const char* hero_id,const char* _cpyTyeId,int cpyRank);

void initCpyLimitMemRecord();

void storeCpyLimitMemRecord();

void outSomeWhere(Hero *myHero);

#endif
