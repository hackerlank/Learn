/************************************************************
	文件名：partyRoomLimit.h
	文件作用：定义PartyRoomLimit的属性和函数
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#ifndef PARTY_ROOM_LIMIT_H
#define PARTY_ROOM_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>

/*没有加入任何帮派*/
const int PARMAP_ERROR_NOT_PARTY = 0;

/*帮派等级不够*/
const int PARMAP_ERROR_RANK_LEVEL = 1;

/*摆摊状态*/
const int PARMAP_ERROR_IN_SELL_STATION = 2;

/*押镖状态*/
const int PARMAP_ERROR_IN_YA_BIAO_STATION = 3;

class Map_Src;

using namespace std;
class PartyRoomLimit
{	
	int num;         //所要求人数
	int partyRank;   //进副本所要求帮派等级
	int room;        //副本房间数
	char partyMapId[SHOR_MID_VALUE_LENGTH + 1];     //vip包间类型
	char partyLimitId[SHOR_MID_VALUE_LENGTH +1];  //副本限制id
	vector<Map_Src*> initPartyRom; //副本房间
	list<int> asistList;     //辅助链表，用以管理副本房间
	map<int,string>roomNumToPartyId;    
	map<string,int>partyIdToRoomNum;
	bool activeFlg;   //是否为活动系统点菜，如果是，则为真
	bool todayActiveFlg;   //今天是否有系统点菜活动，真为是
	
public:
	/*帮派房间构造函数*/
	PartyRoomLimit(char *_partyLimitId,char *_partyMapId,int _num,int _partyRank,int _room);
	
	/*析构帮派房间*/
	~PartyRoomLimit(void);
	
	/*初始化帮派房间*/
	void initPartyMap(void);
	
	/*设置帮派每个房间的包厢实例指针*/
	void setMapPartyRoom(void);
	
	/*单人进帮派包厢检测*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*进帮派包厢函数*/
	bool entPartyRoom(vector<string> &heroId,int _roomNum);
	
	/*退出帮派包厢*/
	void exitPartyRoomAsist(vector<string> &heroId);
	
	/*分配帮派包厢房间*/
	void assignRom(vector<string> &heroId,char *partyId);
	
	/*回收帮派包间*/
	void recoverPartyRom(int _room);
	
	/*获得是否为系统点菜标记值*/
	bool getActiveFlg(void);
	
	/*设置是否为系统点菜标记值*/
	void setActiveFlg(bool _isActiveFlg);
	
	/*系统点菜*/
	void systemDish(Map_Src *treatMap,char *myGuildId);
	
	/*获得是否今天为系统点菜标记值*/
	bool getTodayActiveFlg(void);
	
	/*设置是否今天为系统点菜标记值*/
	void setTodayActiveFlg(bool _todayActiveFlg);
	
	/*更改系统宴席为可吃状态*/
	void setSystemDishState(int _dishState);
	
	/*更改系统宴席为没有刷出状态*/
	void setIsActiveDishBru(void);
	
	/*更改系统宴席为有刷出状态*/
	void setIsActiveDishBruTrue(void);
	
	/*系统宴席,那些已经*/
	void isTmeToDinner(void);
	
	/*关闭系统宴请活动*/
	void closeSystemDish(void);
};
#endif
