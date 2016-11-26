#ifndef PICK_H
#define PICK_H
#include<iostream>
#include<string>
#include<map>
#include "map_inform.h"
#include "timerContainer.h"
#include"libev.h"
using namespace std;
class Map_Inform;
class Pick
{
private:  
	char flag[40];
	char killHeroId[40];
	int num;
	Map_Inform *dropmap;
	map<string,string> pt_to_goodsid;
	int bound;
	Point deadPoint;
	Point piexPt;
	ev_timer *three_timer;
	ev_timer *five_timer;

public:
	Pick(char *_flag,char *_killHeroId,int _num,Map_Inform *_dropmap,int _bound,Point _deadPoint);
	~Pick(void);
	char* getFlag(void);
	void saveFlag(char *_flag);
	void saveKillHeroId(char *_killHeroId);
	char* getIdentity(void);
	char* getKillHeroId(void);
	int getNum(void);
	void setNum(int _num);
	Map_Inform* getMap(void);
	map<string,string> getDropGoods(void);
	void setDropGoods(map<string,string> _pt_to_goodsid);
	int getBound(void);
	void setBound(int _bound);
	Point getDeadPoint(void);
	void msg_online(char *msg,int len);
	void msg_offline(char *msg,int len);
	void initPickTimer(void);
	void stopThreeTimer(void);
	void stopFiveTimer(void);
	void msg_threeMinutes(char *msg,int len);
	void msg_fiveMinutes(void);
	void send_nbox(char *_msg);
	
	/*获得像素坐标*/
	Point getPiexPt(void);
	
	/*逻辑转像素*/
	void exChgePiex(void);
	
	//添加掉落的物品到pt_togoodsId中
	void insertDropGoods(char *pt_flag,char *goodsId);
};
#endif