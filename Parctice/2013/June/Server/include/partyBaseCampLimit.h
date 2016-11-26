/************************************************************
	文件名：partyBaseCampLimit.h
	文件作用：定义PartyBaseCampLimit的属性和函数
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#ifndef PARTY_BASE_CAMP_LIMIT_H
#define PARTY_BASE_CAMP_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>



/*没有加入任何帮派*/
const int CAMP_ERROR_NOT_PARTY = 0;

/*帮派等级不够*/
const int CAMP_ERROR_RANK_LEVEL = 1;

/*处于摆摊*/
const int CAMP_ERROR_IN_SELL_STATION = 2;

/*押镖*/
const int CAMP_ERROR_IN_YA_BIAO_STATION = 3;


/*探营时间还没有到*/
const int CAMP_ERROR_TIME_NOT_OPEN = 4;

class Map_Src;

using namespace std;
class PartyBaseCampLimit
{
	bool isOpen;     //通过时间控制开启
	int num;         //所要求人数
	int partyRank;   //所要求帮派等级
	int room;        //房间数
	char campMapId[SHOR_MID_VALUE_LENGTH + 1];     //包间类型
	char campLimitId[SHOR_MID_VALUE_LENGTH +1];  //限制id
	vector<Map_Src*> initCampRom; //副本房间
	list<int> asistList;     //辅助链表，用以管理副本房间
	map<int,string>roomNumToPartyId;    
	map<string,int>partyIdToRoomNum;
	
public:
	/*帮派房间构造函数*/
	PartyBaseCampLimit(char *_campLimitId,char *_campMapId,int _num,int _partyRank,int _room);
	
	/*析构帮派房间*/
	~PartyBaseCampLimit(void);
	
	/*初始化帮派房间*/
	void initCampMap(void);
	
	/*设置帮派每个房间的包厢实例指针*/
	void setMapCampRoom(void);
	
	/*单人进帮派包厢检测*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,\
	bool _enterFlg = false);
	
	/*进帮派包厢函数*/
	bool entCampRoom(vector<string> &heroId,int _roomNum);
	
	/*退出帮派包厢*/
	void exitCampRoomAsist(vector<string> &heroId);
	
	/*分配帮派包厢房间*/
	void assignRom(vector<string> &heroId,char *partyId);
	
	/*回收帮派包间*/
	void recoverCampRom(int _room);
	
	/*设置开启标记值*/
	void setOpenFlg(bool _openFlg);
	
	/*获得开启标记值*/
	bool getOpenFlg(void);
	
};
#endif
