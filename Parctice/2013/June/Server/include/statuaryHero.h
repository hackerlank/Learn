/************************************************************
	文件名：statuaryHero.h
	文件作用：定义StatuaryHero类
	作者：chenzhen
	创建日期：2013.03.01
************************************************************/

#ifndef STATUARY_HERO_H
#define STATUARY_HERO_H
#include"libev.h"
#include"wholeDefine.h"
#include"data_structure_struct.h"
#include<string>
#include<map>
using namespace std;
class Map_Src;

struct MemStatuaryHero
{
	char vocation[SHOR_MID_VALUE_LENGTH + 1];       //职业id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];        //雕像颜色id
	char heroId[SHOR_MID_VALUE_LENGTH + 1];        //关联角色id
	char mapId[SHOR_MID_VALUE_LENGTH + 1];         //所在地图id
	char titleId[SHOR_MID_VALUE_LENGTH + 1];       //称号（作为缓存的键）
	char requre[SHOR_MID_VALUE_LENGTH + 1];        //关联角色requre,对应图片id的一个键，就是那些头衔
	char heroName[SHOR_MID_VALUE_LENGTH + 1];      //关联角色昵称
	int lastSeconds;                               //还剩余秒数
	int piex_x;                                    //横坐标
	int piex_y;                                    //纵坐标
	int level;                                     //角色等级
	int lifeVal;                                   //生命值
	int lifeUpperVal;                              //生命上限值
	int magicUpperVal;                             //魔法上限值
	int magicVal;                                  //魔法值
	
	
	MemStatuaryHero(char *_heroId,char* _heroName,char *_vocation,int _level,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,\
	int _magicVal,char *_mapId,char *_photoId,char* _titleId,char* _requre,int _lastSeconds,Point _piexPt)
	{
		initMemStatuaryHero();
		strncpy(vocation,_vocation,strlen(_vocation));
		strncpy(photoId,_photoId,strlen(_photoId));
		strncpy(heroId,_heroId,strlen(_heroId));
		strncpy(mapId,_mapId,strlen(_mapId));
		strncpy(titleId,_titleId,strlen(_titleId));
		strncpy(requre,_requre,strlen(_requre));
		strncpy(heroName,_heroName,strlen(_heroName));
		lastSeconds = _lastSeconds;
		piex_x = _piexPt._x;
		piex_y = _piexPt._y;
		level = _level;
		lifeUpperVal = _lifeUpperVal;
		lifeVal = _lifeVal;
		magicUpperVal = _magicUpperVal;
		magicVal = _magicVal;		
	}
		
	void initMemStatuaryHero(void)
	{
		memset(vocation,'\0',sizeof(vocation));
		memset(photoId,'\0',sizeof(photoId));
		memset(heroId,'\0',sizeof(heroId));
		memset(mapId,'\0',sizeof(mapId));
		memset(titleId,'\0',sizeof(titleId));
		memset(requre,'\0',sizeof(requre));
		memset(heroName,'\0',sizeof(heroName));
		lastSeconds = 0;
		piex_x = 0;
		piex_y = 0;
		level = 0;
		lifeUpperVal = 0;
		lifeVal = 0;
		magicUpperVal = 0;
		magicVal = 0;		
	}
};	
	

class StatuaryHero
{
	MemStatuaryHero* memStatuaryHero;               //结构体，放缓存	
	Map_Src *map_now;                           //地图实例指针
	ev_timer last_timer;                           //持续时间计时器
	Point piexPt;								   //像素坐标
	char inSeeMsg[LONG_MID_VALUE_LENGTH + 1];      //上线消息
	char outSeeMsg[LONG_MID_VALUE_LENGTH + 1];      //下线消息
	
	
	public:
	
	StatuaryHero(MemStatuaryHero* _memStatuaryHero);
	
	/*获得关联角色id*/
	char* getHeroId(void);
	
	/*获得memStatuaryHero*/
	MemStatuaryHero* getMemStatuaryHero(void);
	
	/*析构函数*/
	~StatuaryHero(void);
	
	/*生成上线消息*/
	void formInSeeMsg(void);
	
	/*生成下线消息*/
	void formOutSeeMsg(void);
	
	/*获得上线消息*/
	char* getInSeeMsg(void);
	
	/*获得下线消息*/
	char* getOutSeeMsg(void);
	
	/*初始化地图实例指针*/
	bool initMapInform(void);
	
	/*获得像素坐标*/
	Point getPiexPt(void);
	
	/*刷出雕像*/
	void brushMsg(void);
	
	/*修改坐标*/
	void setPiex(Point _piexPt);
	
	/*摧毁雕像*/
	void destoryMsg(void);
};
#endif
