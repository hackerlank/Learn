/************************************************************
	文件名：map_src.h
	文件作用：类Map_Src类的属性和方法
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#ifndef MAP_SRC_H
#define MAP_SRC_H
#include<iostream>
#include"map_inform.h"

class VipBaleRoomLimit;
class PartyRoomLimit;
class PartyBaseCampLimit;
class Map_Src : public Map_Inform
{
private:	             	
	
	/*包厢实例指针*/
	VipBaleRoomLimit *vipRoom;	
	
	/*vip包间号*/
	int vipRoomNum;
	
	/*是否是vip包厢，true为vip包间*/
	bool isVipRom;
	
	/*vip包厢是否被占用，true为被占用*/
	bool isVipRomBusy;
	
	
	
	/*帮派实例指针*/
	PartyRoomLimit *partyRoom;	
	
	/*帮派房间号*/
	int partyRoomNum;
	
	/*是否是帮派包厢，true为帮派包间*/
	bool isPartyRom;
	
	/*帮派包厢是否被占用，true为被占用*/
	bool isPartyRomBusy;
	
	
	
	/*帮派大本营*/
	PartyBaseCampLimit *campRoom;	
	
	/*帮派大本营房间号*/
	int campRoomNum;
	
	/*是否是大本营包厢，true为帮派大本营包间*/
	bool isCampRom;
	
	/*帮派大本营包厢是否被占用，true为被占用*/
	bool isCampRomBusy;
	
	
	
	
	
	/*控制怪物复活用*/
	int ctnReBruDieMon;	
	
	/*把死亡怪物放入待刷容器*/
	void exchageDie(void);
	
	/*循环刷怪函数*/
	void loopBruMon(bool isFirst = false);
	
	/*控制刷怪频率*/
	bool ctlTme(int lveTme = 12);
	
	/*第一次进入场景刷怪*/
	void entMap(void);
	
	/*刷怪接口*/
	void bruMonFun(void);	
	
public:

	/*构造函数*/
	Map_Src(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int warType,int changePkType,int mapType,int campEntFlag,\
	int levelLowerLimit,int levelUpperLimit);	
	
	/*地图思考回调函数*/
	void mapThkCalBak(void);

	
	
	/*获得此地图所有怪物类型id集合*/
	set<string> getTypeMonOneMap(void);

	/*析构函数*/
	~Map_Src(void);   
	
	/*暂停此地图上已刷出怪的思考*/
	void stopAllLveMonThk(void);
	
	/*重启此地图上所有已刷出怪的思考*/	
	void reSetAllLveMonThk(void);
	
	
	/*复制地图信息，传参数是为了区分副本中的怪的id*/
	Map_Src* copyMap(int roomNum);
	
	/*重置怪物数据*/
	void initMon(void);
	
	/*重置整张地图信息*/
	void initMap(void);
	
	/*地图暂停思考函数*/
	void stopThk(void);
	
	/*生成怪物数目信息*/
	char* getSumMonMsg(void);
	
	
	/*获得是否为vip包间标志*/
	bool getIsVipRom(void);
	
	/*设置是否为vip包间标志*/
	void setIsVipRom(bool _busy);
	
	
	/*获得vip包间是否被占用标志*/
	bool getIsVipRomBusy(void);
	
	/*获得vip包间是否被占用标志*/
	void setIsVipRomBusy(bool _busy);
	
	/*设置vip包厢限制类实例指针*/
	void setVipRoom(VipBaleRoomLimit *_vipRoom);
	
	/*进入vip包厢*/
	void enterVipRoomFirst(void);
	
	/*包厢场景地图思考函数*/
	bool vipCallBack(void);
	
	/*计算得到vip包间号*/
	void ctnTheVipRoomNum(void);
	
	/*退出vip包厢*/
	void exitVipRoom(vector<string> &heroVec);
	
	/*计算得到帮派包间号*/
	void ctnThePartyRoomNum(void);
	
	/*获得vip包间是否被占用标志*/
	void setIsPartyRomBusy(bool _busy);
	
	/*获得vip包间是否被占用标志*/
	bool getIsPartyRomBusy(void);
	
	/*设置是否为帮派地图*/
	void setIsPartyRom(bool _busy);
	
	/*获得是否为帮派包间标志*/
	bool getIsPartyRom(void);
	
	/*设置帮派包厢限制类实例指针*/
	void setPartyRoom(PartyRoomLimit *_partyRoom);
	
	PartyRoomLimit* getPartyRoomLimit(void);
	
	/*进入帮派包厢*/
	void enterPartyRoomFirst(void);
	
	/*包厢场景地图思考函数*/
	bool partyCallBack(void);
	
	
	/*设置帮派大本营包厢限制类实例指针*/
	void setCampRoom(PartyBaseCampLimit *_campRoom);
	
	/*获得帮派包间是否被占用标志*/
	bool getIsCampRomBusy(void);
	
	/*获得帮派包间是否被占用标志*/
	void setIsCampRomBusy(bool _busy);
	
	/*计算得到帮派大本营包间号*/
	void ctnTheCampRoomNum(void);
	
	/*退出帮派大本营包厢*/
	void exitCampRoom(vector<string> &heroVec);
	
	/*获得是否为帮派大本营包间标志*/
	bool getIsCampRom(void);
	
	/*设置是否为帮派大本营地图*/
	void setIsCampRom(bool _busy);
	
	/*帮派大本营包厢场景地图思考函数*/
	bool campCallBack(void);
	
	/*进入帮派大本营包厢*/
	void enterCampRoomFirst(void);
	
	/*系统请客辅助函数*/
	bool systemTreat(TakeGoods *newDish);
};
#endif 
