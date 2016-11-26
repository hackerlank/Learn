/************************************************************
	文件名：bruType.h
	文件作用：定义BruType的属性和函数
	作者：chenzhen
	创建日期：2012.08.14
************************************************************/
#ifndef BRUSH_MONSTER_TYPE_H
#define BRUSH_MONSTER_TYPE_H
#include"groupBrush.h"		
#include<map>
#include<string>
#include"bruMonInfor.h"
class Map_Inform;
class MonsterBase;
using namespace std;

class BruType
{
	double time;      //隔多长时间刷一次
	int mapTmeCtn;    //折算成地图思考次数
	int starCtn;      //计数器
	bool apply;       //补量刷怪模式（true为是，否则不是）
	bool allFlg;      //全刷标记值（true为全刷，否则不是）
	int sum;          //每批的数量
	MonGroNum monBruNumSdu;   //刷怪各数目标准
	MonGroNum eachBru;        //每次刷怪数目
	GroupBrush *groupBrush;     //批次刷怪类指针
	map<string,MonsterBase*>monId_connect_monster;  //地图怪物信息
	map<string,BruMonInfor*>brushMonInform;          //刷怪记录表
	bool againBru;
	/*刷怪记录表迭代器，记住每次刷怪点*/
	map<string,BruMonInfor*>::iterator bruMon_it;    
	
	/*一次性全刷出*/
	void brushAllMon(void);
	
	/*通过传入参数判断和输出怪物相对应int型的类型号*/
	int typeMatchInt(MonsterBase *mon,bool _flgKind = true);
	
	/*通过传入参数判断怪物类型号*/
	bool judgebrushMonTpy(int _monTyp);
	
	/*按模式刷怪*/
	void brushMonByModle(void);
	
	/*判断刷怪时间是否到期*/
	bool judgeTme(void);   

	/*判断精英怪数量是否刷够*/
	bool judgeGenerNum(void);
	
	/*判断精英怪数量是否刷够*/
	bool judgeEliteNum(void);
	
	/*判断主动怪数量是否刷够*/
	bool judgeActiveNum(void);
	
	/*判断被动怪数量是否刷够*/
	bool judgePassNum(void);
	
	/*判断巡逻怪数量是否刷够*/
	bool judgePatNum(void);
	
	/*判断BOSS怪数量是否刷够*/
	bool judgeBossNum(void);
	
	/*判断所有怪数量是否刷够*/
	bool judgeSum(void);	
	
public:
	BruType(map<string,MonsterBase *>& _monId_connect_monster,\
			map<string,BruMonInfor*>& _brushMonInform,double _time,\
			bool _allFlg = true,bool _apply = false,GroupBrush *groupBrush = NULL);
				 
	/*刷怪外部接口,供地图调用*/
	void brushMonFun(int _Cpyflg);
	
	/*通过怪物id获得怪物实例指针*/
	MonsterBase* getMon(char *monId);
	
	/*初始化刷怪记录表的迭代器*/		
	void initBruIt(void); 
	
	/*初始化刷怪各数目标准*/
	void initMonBruStu(void);
	
	/*复制刷怪模式*/
	BruType* copyBruTpy(char *newMapId);
	
	/*重置地图刷怪记录表信息*/
	void initBrushRed(void);
	
	/*重置那些还活着的怪物*/
	void initLveMon(void);
	
	/*复制怪物实例以及和刷怪记录表*/	
	void copyMapMon(map<string,MonsterBase*> &newMonIn,\
					map<string,BruMonInfor*> &newBrushInt,\
					char *newMapId);
	
	/*还原刷怪模式*/
	void initBruTpy(void);
	
	/*析构函数*/
	~BruType(void);
	
	/*暂停此地图上所有怪的思考,后面也许会以九宫格为单位*/
	void stopMonThk(void);
	
	/*启动此地图上所有怪的思考,后面也许会以九宫格为单位*/
	void reSetMonThk(void);
	
	/*获得现存活怪的数量*/
	int getLveMonNum(void);
	
	/*获得总怪的数量*/
	int getAllMonNum(void);
	
	/*打印测试怪物信息*/
	void printMonsterInform(void);
	
	/*设置所有在此地图上的怪的地图指针*/
	void setMonMap(Map_Inform *map);
	
	/*获得此地图所有怪物类型id集合*/
	void getTypeMonOneMap(set<string> &monAllType);
	
	/*获得整个怪物信息*/
	// map<string,MonsterBase*>& getMonId_connect_monster(void);
	
	/*获得怪物记录表*/
	// map<string,BruMonInfor*>& getBrushMonInform(void);
	
	/*获得整个怪物信息*/
	void getAllMonObj(vector<MonsterBase*> &monObj);
	
	/*怪物死亡函数里调用,放进怪物死亡容器中*/
	bool monIdInputDie(char *monTypId,char *monId);
	
	/*怪物析构函数里调用，删除在地图里面的信息*/
	bool EraInMap(char *monId);
	
	/*怪物死亡函数里调用,直接删除*/
	bool monIdErase(char *monTypId,char *monId);
	
	/*普通场景怪物复活*/
	void exchageDieMon(void);

};	
#endif
	
	
	
	
	
