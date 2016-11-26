/********************************************************************

    created:   2012/2/24  
	
	文件名：	nbox.h

    author:     cookie 

    purpose:  九宫格头文件；
			  定义Nbox类，双重vector用来管理坐标，通过坐标为键值，获得玩家ID列表（set容器管理）
	
	修改：	2012.2.27（Tory）
	重写：  2012.08.23（chenzhen）整个文档
*********************************************************************/
#ifndef _NBOX_H__
#define _NBOX_H__
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include "data_structure_struct.h"
#include <iostream>


#include"map_inform.h"
#include"monsterBase.h"
#include"boxAsist.h"
class MonsterBase;
class Wagon;
class Pet;
class TakeGoods;
using namespace std;


typedef struct PointCmp
{
  bool operator() (const Point& pt1, const Point& pt2) const
  {
	return pt1._x != pt2._x || pt1._y != pt2._y ;
  }
}PointCmp;

class Map_Inform;
class Nbox
{		
private:
	/*当前地图实例指针*/
	Map_Inform *map_now;
	
	/*此九宫格宽，高，以及大小(都是像素为单位）*/
	Point scrSizePiexPt;
	
	/*屏幕数组长度*/
	Point MapScrPtSize;
	
	/*九宫格内容，即怪物或者人物id*/
	vector <vector <OneScreen> > herOrMonIdVec;	
	
	set<Point> oldSrcPtSet;
	
	set<Point> newSrcPtSet;
	
	set<Point> sameSrcPtSet;
	
	set<Point> diffOldSrcPtSet;
	
	set<Point> diffNewSrcPtSet;
	 
	
	/*判断屏幕坐标是否合法*/
	bool judgeSCrIndex(Point &srcPt);
	
	
	
	
	
	/*计算新旧九宫格的交集的交集，发移动消息*/
	void ctnSmeValSet(void);
	
	/*计算获得新九宫格与新旧九宫格的交集的差集，先发登陆消息，再发移动消息*/
	void ctnDiffNewValSet(void);
	
	/*计算获得旧九宫格与新旧九宫格的交集的差集，发下线消息*/
	void ctnDiffOldValSet(void);
	
	
	/*判断此角色是移出当前屏幕,移出，返回false，木有则true*/
	bool judgeOutSrc(Point &oldSrcPt,Point &newSrcPt);

	/*获得坐标的九宫格（srcPt为屏幕坐标）*/
	void getStaInSrcVec(Point &srcPt,set<Point> &SrcPtSet);
	
	/*清空容器*/
	void clearSet(void);
	
	/*收集一个屏中玩家id*/
	void mapSrcPtToHerIdSet(Point &SrcPt,set<string> &heroIdSet);
	
	/*通过像素坐标获得九屏的heroid集合*/
	void mapSrcPtToHerIdSet(set<Point> &SrcPtSet,set<string> &heroIdSet);
	
	/*屏幕坐标转化成string行*/
	void ptToStr(const Point &srcPt, string& str);
	
	/*初始化屏幕数组*/
	void initScrVec(void);
	
public:

	Nbox(Map_Inform *_map_now,Point _scrSizePiexPtPiexPt);
	
	~Nbox(void);
	//获取指定地点已定距离范围内的角色容器和怪物容器
	void getObjInRange(Point &srcPt, int distSqr, set<string> &heroIdSet, set<string> &monsterSet);
	/*从旧九宫格里面删掉,重载，供内部调用*/
	bool deleteInOldSrc(Point &srcPt,StyObj &obj);
	
	/*插入九宫格里面,重载，供内部调用*/
	bool inputInOldSrc(Point &srcPt,StyObj &obj);
	
	
	/*获得九宫格内实例的像素坐标*/
	bool getObjpT(StyObj &obj,Point &piexPt);

	
	/*从旧九宫格里面删掉,下线和切地图时，才会外部调用*/
	bool deleteInOldSrc(StyObj &obj);
	
	/*插入九宫格里面,上线和切地图时，才会外部调用*/
	bool inputInOldSrc(StyObj &obj);
	
	
	/*地图像素点转换成屏幕坐标*/
	Point mapLogToSrcPtv(Point &piexPt,int flg = 0);
	
	
	/*重载获得九宫格内容函数，通过id*/
	void getStaInSrcVec(StyObj &obj);
	
	
	/*判断一个点是否合法，测试他的屏幕坐标*/
	void testInSrc(Point &piexPt);
	
	/*测试通过下标索引*/
	void testIndex(Point &srcPt);
	
	/*清空九宫格中的内容*/
	void clearBox(void);
	
	/*通过piexPt为像素坐标获得九宫格*/
	void getNineSrcByLogPt(Point &piexPt);		
	
	/*角色心跳函数*/
	void heroPollTme(Hero *hero,char *moveMsg,bool isNewRod);
	
	/*移动（心跳也可以）更改九宫格内容*/
	bool MovePt(StyObj &obj,Point &newPt);
	
	/*封装的消息发送函数，以九宫格发送*/
	void sentBoxMsg(set<Point> &SrcPtSet,char *msg,char *heroId = NULL);
	
	/*封装的消息发送函数，以九宫格发送,为相互看见的,主要用在玩家的消息发送*/
	void sentBoxViewMsg(set<Point> &SrcPtSet,char *msg,Hero *myHero,int style);
	
	/*测试附近九个格的内容*/
	void testMapSet(OneScreen &idSet);
	
	/*测试附近九个格的内容*/
	void testKindSet(set<Point> &SrcPtSet);
	
	/*测试附近九个格的内容*/
	void testAllkindScr(void);
	
	/*封装的消息发送函数，以九宫格发送*/
	void sentBoxMsg(char *msg,char *heroId = NULL);
	
	
	/*宠物移动函数*/
	void petMove(Pet *pet,char *moveMsg,bool isNewRoad, char *wonerId = NULL);
	
	/*马车移动函数*/
	void wagonMove(Wagon *wagon,char *moveMsg, bool isNewRoad, char *wonerId = NULL);
	
	/*可移动移动函数*/
	void takeGoodsMove(TakeGoods *takeGoods,char *moveMsg, bool isNewRod = false);
	
	/*角色进入或退出视野*/
	void heroEnter(Hero *hero,int style);
	
	/*获得九宫格的引用*/
	set<Point>& getNewSrcPtSet(void);
	
	
	/*通过像素坐标获得一个屏的集合*/
	OneScreen& getOneSrcMap(Point &piexPt);
	
	/*怪物移动函数*/
	void monsterMove(MonsterBase *monster,char *moveMsg, bool isNewRod = false);	
	
	
	/*通过像素坐标获得九屏的heroid集合*/
	void getNineSrcHerIdSet(Point &piexPt,set<string> &heroIdSet);
	
	/*通过像素坐标发送九宫格数据*/
	void sendMsgPiexPt(Point &piexPt,char *msg);
	
	/*从全图删掉一个obj*/
	bool deleteObj(StyObj &obj);
	
	/*从一个屏里面删掉一个obj*/
	bool deletObjHerVec(OneScreen& idSet,StyObj &obj);
	
	//获得最近相邻屏幕
	void getNeighbour(Point pixPt, set<Point> &nbSet);
	
	//通过屏幕坐标获得屏幕
	void getOneScreen(OneScreen * &screen, Point scrPt);
	
	//获取屏幕的相邻屏幕	
	void getNeighbour(Point pixPt, OneScreen **screens);
	
	/*通过像素坐标获得像素坐标附近屏的heroid集合*/
	void getCentPtSrcHerIdSet(Point &piexPt,set<string> &heroIdSet);
};

#endif
