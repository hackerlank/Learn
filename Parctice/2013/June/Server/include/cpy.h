/************************************************************
	文件名：cpy.h
	文件作用：定义Cpy的属性和函数
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/

#ifndef COPY_H
#define COPY_H
#include"ectype_reward_set.h"
#include<iostream>
#include<string>
#include<set>
#include<list>
#include<vector>
#include<time.h>
#include"map_cpy.h"
using namespace std;
class CpyLimit;
class Cpy
{
	list<string> cpyMap;    //副本地图id	
	char cpyId[SHOR_MID_VALUE_LENGTH + 1];
	map<string,Map_Cpy*> instMapSet;   //副本地图实例指针
	list<string>::iterator src_it;        //副本地图迭代器
	Map_Cpy *mapNow;    //当前地图实例指针	
	set<string> canEntMapId;  //已通过副本mapId
	bool flgBusy;             //房间是否空闲
	CpyLimit *cpyLimit;       //此副本的限制实例指针

	string olderMapId;        //顺序存入地图
	
	EctypeRewardSet *rewardSet;		//副本奖励集合
	
	/*副本开启时间*/
	struct timeval begin;	
	
	/*副本开启总时间*/
	int seconds;
	
	/*通关副本所耗费时间*/
	int costTme;
	
	/*死亡次数*/
	map<string,int>heroDieCtn;
	
	/*得分*/
	map<string,int>heroGold;
	
	/*是否是借的，真为借的*/
	bool isBorrowFlg;
	
	/*进副本时，是否为组队状态，真为是*/
	bool isTeam;
	
public:
	Cpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds = 2400);
	
	Cpy(void);
	
	/*辅助函数，在构造函数里调用*/
	void initMapSet(void);		
	
	/*初进副本*/
	bool entCpy(vector<string> &heroId);
	
	/*设置当前副本地图实例指针*/
	bool instMapNow(char *_mapId);
	
	/*测试打印副本地图信息函数*/
	void printCpyMap(void);
	
	/*析构函数*/
	~Cpy(void);	
	
	/*进副本场景*/
	bool entCpyMap(vector<string> &heroId,char *_mapId,Point* pTargetPt=NULL);
	
	/*设置副本状态是否为空闲*/
	void setFlgBusy(bool _flgBusy);
	
	/*获得副本状态*/
	bool getFlgBusy(void);
	
	/*把下一个副本mapId放入当前玩家可进入mapId集合里面*/
	void inPutCanEntset(void);
	
	/*副本复原*/
	void recover(void);	
	
	/*进副本辅助函数*/
	bool entCpyAssist(vector<string> &heroId,int times,char *_mapId,Point* pTargetPt=NULL); 
	
	/*获得相对上下层关系*/
	int getEntMapOlder(char *oldMapId,char *newMapId);
	
	/*退出副本*/
	void exitCpy(vector<string> &heroId);
	
	/*副本房间自动回收*/
	void recoverCpy(void);
	
	/*副本通关*/
	bool PassCpyJudge(char *_mapId);
	
	/* 获得副本奖励集 */
	EctypeRewardSet *getRewardSet(void);
	
	/*初始化副本奖励*/
	void initRewardSet(void);
	
	/*判断时间是否超时*/
	bool timeOut(void);
	
	/*重置副本房间信息*/	
	void initCpy(void);
	
	/*副本回收后条件判断*/
	bool judgeRecover(void);
	
	/*通关后数据记录*/
	void passRecord(void);
	
	/*单人退出副本处理*/
	void exitHero(vector<string> &heroId);
	
	/*进副本场景辅助函数*/
	bool entMapAssist(vector<string> &heroId,char *_mapId,Point* pTargetPt);
	
	/*进副本辅助函数*/
	bool entAssist(vector<string> &heroId,int olderNext);  
	
	/*副本进入前的"预定副本房间"函数*/
	void goAheadCpy(vector<string> &heroId);
	
	char* getCpyId(void);
	
	/*发送副本怪物实时数量*/
	void sentLveMonMsg(void);
	
	/*所有人退出副本处理*/
	void exitHero(void);
	
	/*获得副本难度*/
	int getDiffcult(string _cpyIds);
	
	/*全体退出副本*/
	void exitCpy(void);
	
	/*计算时间为参数所得分数*/
	int judgeTmeGole(void);
	
	/*计算死亡次数为参数所得分数*/
	void judgeDieGole(void);
	
	/*计算死亡次数为参数所得分数*/
	void judgeAllGole(void);
	
	/*生成得分消息*/
	void formGoleMsg(char *goleMsg,int length);
	
	/*发送得分消息*/
	void sentGoleMsg(char *goleMsg);
	
	/*得分处理*/
	void goleDeal(char *goleMsg,int length);
	
	/*存储分数*/
	void storeGole(void);
	
	/*用vec装玩家的id*/
	void mapToVec(vector<string> &herId);
	
	/*计算时间为参数所得分数*/
	int getTmeSecond(void);
	
	/*发送此地图上怪物的数目信息*/
	void sentMonSumMsg(vector<string> &heroId);
	
	/*测试已通过副本层次*/
	void testCanPas(void);
	
	/*计算死亡次数*/
	void ctnDieTme(void);
	
	/*通过mapId找到map实例*/
	Map_Cpy* getCpyMap(char *mapId);
	
	/*获得地图id容器*/
	list<string>& getCpyMapSet(void);
	
	/*初始化扩展副本*/
	void initBorrowCpy(char *_cpyId,list<string>& _cpyMap,CpyLimit *_cpyLimit,int _seconds  = 30);
	
	/*重置扩展副本*/
	void recoverBorrowCpy(void);
	
	/*下一波怪刷出前的提示*/
	void formNextMonMsg(int groups,int timeSecods);
	
	/*删除地图*/
	void deleteMap(void);
	
	/*获得是否为借的标记值*/
	bool getIsBorrowFlg(void);
	
	/*设置进入副本的状态*/
	void setIsTeam(bool _isTeam);
	
	/*通关后减去耐力值*/
	void minusStrlength(void);
	
	//刷记录
	void recordLessTme();
	
	private:
	
	/*黑木崖副本通关数据处理*/
	bool passTowerLayer(void);
	
};
#endif
	
		

	
