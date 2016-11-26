/************************************************************
	文件名：map_cpy.h
	文件作用：类Map_Cpy类的属性和方法
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#ifndef MAP_CPY_H
#define MAP_CPY_H
#include<iostream>	
#include"map_inform.h"
#include"map_inform_asist.h"
using namespace std;

class Map_Cpy : public Map_Inform
{
private:	 
	
	/*此地图所属副本实例指针*/
	Cpy *cpy;
	
	/*控制怪物复活用*/
	int ctnReBruDieMon;
	
	/*刷怪容器下标*/
	int index;
	
	/*刷怪批次*/	
	vector<BruGro>bruGropVec;
	
	/*每批怪刷出的时间,折算成地图思考时间*/
	vector<int>bruEachTme;
	
	/*计时器（折算成怪物思考时间）*/
	int ctnBru;
	
	/*以存活怪物id*/
	// list<string> lveMonCtnId;	
	
	bool pasFlg,goNext;
	
	int sumMon;
	
	int lveSumMon;
	
	char sumMonMsg[SHOR_MID_VALUE_LENGTH + 1];
	
	
	set<string>::iterator bruMonId_it;
	
	/*进入副本下一层以及回收副本*/
	void getNextStage(void);
	
	/*重置批次刷怪容器*/
	bool initGroBru(void);
	
	/*下一批怪刷出条件判断*/
	bool judgeGroDieOut(void);
	
	/*批次时间是否到*/
	bool judgeBruGroTmeOut(void);
	
	/*按批次模式刷怪接口*/
	void bruMonByGroMod(void);	
	
	
	/*副本具体刷怪函数*/
	void bruMonByGroFun(int _index);
	
	/*复制刷怪批次*/
	void copyBruGropVec(vector<BruGro> &_bruGropVec,char *newMap);
	
	/*怪物死亡*/
	void GromonDead(char *monId);
	
	/*重置按批刷怪模式*/
	void initGroMon(void);
	
	/*怪物存活次数刷怪函数*/
	void bruMonByCtnFun();
	
	/*刷新地图信息函数*/
	void bruMapFun(void);

	/*所有批次是否刷完*/
	bool judgeBruGroIndex(void);	
	
	/*把怪物从地图上删掉*/
	void  monLveOutView(void);
	
public:
	/*构造函数*/
	Map_Cpy(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	vector<BruGro> _bruGropVec,	vector<int>_bruEachTme,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int _sumMon,int warType,int _changePkType,int _mapType=0,\
	int _campEntFlag=0,int _levelLowerLimit=0,int _levelUpperLimit=100);
	
	
	/*第一次进入副本*/
	void fristEntMap(void);
	
	/*设置副本值*/
	void SetCpy(Cpy *_cpy);
	
	/*复制地图信息，传参数是为了区分副本中的怪的id*/
	Map_Cpy* copyMap(int roomNum,char *cpyId = NULL);
	
	/*地图思考回调函数*/
	void mapThkCalBak(void);
	
	/*析构函数*/
	~Map_Cpy(void);
	
	/*暂停此地图上已刷出怪的思考*/
	void stopAllLveMonThk(void);
	
	/*重启此地图上所有已刷出怪的思考*/	
	void reSetAllLveMonThk(void);
	
	/*重置整张地图信息*/
	void initMap(void);
	
	
	/*测试各刷怪批次怪物id*/	
	void testGroMonId(void);
	
	/*测试各刷怪批次时间*/	
	void testGroCtn(void);
	
	/*测试打印刷怪时间容器*/
	void testBruEachTme(void);
	
	/*副本回收标志*/
	bool recoverCpy(void);
	
	/*测试打印副本中存活列表信息*/
	void testLveCtn(void);
	
	/*测试打印副本重置信息*/
	void testMapInfor(void);
	
	/*生成怪物数目信息*/
	void formSumMonMsg(void);
	
	/*生成怪物数目信息*/
	char* getSumMonMsg(void);	
	
	/*更新副本怪物数目*/
	void sentSumMonMsg(void);
	
	/*杀死一个怪*/
	void killOneMon(void);
	
	/*测试怪物存活次数*/
	void testLveMager(set<string> &monId);
	
	/*地图暂停思考函数*/
	void stopThk(void);
	
	void getMonObj(vector< vector<string> > &mon_vec);	//tory add
	
	/*下一波怪刷出前的提示*/
	void formNextMonMsg(void);
	
	/*返回副本势力指针*/
	Cpy* getCpy(void);
};
#endif 
