/************************************************************
	文件名：vipBaleRoomLimit.h
	文件作用：定义VipBaleRoomLimit的属性和函数
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#ifndef VIP_BALE_ROOM_LIMIT_H
#define VIP_BALE_ROOM_LIMIT_H
#include "instancing_manage.h"
#include"wholeDefine.h"
#include<vector>
#include<string>
#include<list>

/*vip等级不够*/
const int ERROR_VIP_LEVEL = 0;

/*不在娱乐地图里面*/
const int ERROR_IN_HAPPY_CITY = 1;

/*摆摊状态*/
const int ERROR_IN_SELL_STATION = 2;

/*拉镖状态*/
const int ERROR_IN_YA_BIAO_STATION = 3;

/*不在同一张地图里面*/
const int ERROR_IN_ERROR_ERROR_YA_BIAO_STATION = 4;

class Map_Src;

using namespace std;
class VipBaleRoomLimit
{	
	int num;         //进副本所要求人数
	int vipRank;        //进副本所要求vip等级
	int room;         //副本房间数
	char vipMapId[SHOR_MID_VALUE_LENGTH + 1];     //vip包间类型
	char vipLimitId[SHOR_MID_VALUE_LENGTH +1];  //副本限制id
	vector<Map_Src*> initVipRom; //副本房间
	list<int> asistList;     //辅助链表，用以管理副本房间	
	
public:
	/*vip包厢构造函数*/
	VipBaleRoomLimit(char *_vipLimitId,char *_vipMapId,int _num,int _vipRank,int _room);
	
	/*初始化vip包厢*/
	void initVipMap(void);
	
	/*析构vip包厢*/
	~VipBaleRoomLimit(void);
	
	/*回收vip包间*/
	void recoverVipRom(int _room);
	
	/*单人进vip包厢检测*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*分配vip包厢房间*/
	void assignRom(vector<string> &heroId);
	
	/*进vip包厢函数*/
	bool  entVipRoom(vector<string> &heroId,int _roomNum);  
	
	/*退出vip包厢*/
	void exitVipRoomAsist(vector<string> &heroId);
	
	/*设置包厢每个房间的包厢实例指针*/
	void setMapVipRoom(void);
	
};
#endif
