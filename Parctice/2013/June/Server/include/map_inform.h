/************************************************************
	文件名：map_inform.h
	文件作用：类Map_Inform类的属性和方法
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
#ifndef MAP_INFORM_H
#define MAP_INFORM_H
#include"data_structure_struct.h"
#include<vector>
#include<iostream>
#include<map>
#include<set>
#include"nbox.h"
#include"libev.h"
#include"mapAction.h"
#include"command_other_function_all_over.h"	
#include"map_inform_asist.h"
#include"takeGoods.h"
#include"boxAsist.h"
using namespace std;
class MonsterBase;
class MonsterActive;
class MonsterPassivity;
class MonsterPatrol;
class MonsterBoss;
class MonsterActiveBoss;
class Nbox;
class Cpy;
class TakeGoods;
class Bottle;
class Trap;
class Pick;
class Map_Inform
{
protected:	
	char mapId[SHOR_MID_VALUE_LENGTH + 1];          	//地图id
	char mapFilePath[SHOR_MID_VALUE_LENGTH + 1];		//路径
	char mapName[SHOR_MID_VALUE_LENGTH + 1];			//名称
	int mapWidth;			//宽度（像素）
	int mapHeight;			//高度（像素）
	
	int row;				//行数（网格）
	int col;				//列数（网格）
	int baseDigst;			//地图偏移量
	
	string td_room;	
	
	map<string,MonsterBase *>monId_connect_monster;  //地图怪物信息
	
	map<string,const jumpId_infor*>jumpId_connect_jumpInfo; //跳转点信息；
	
	vector< vector<int> >map_hinder;    			//地图每个点的障碍情况
	
	Nbox *box;                                     //九宫格
	
	ev_timer timer;                            //地图计时器
	
	Point entPt;               //地图的入点
	Point outPt;               //地图的出点
	
	/****************** xhm added start***************************/
    Point tribesPt;			//阵营镇派诞生地；
	Point rangerPt;			//阵营游侠诞生地；
	Point religionPt;		//阵营邪派诞生地；

	int mapType;			//地图类型；
	int warType;			//作战类型；（1,和平模式，2,全体模式，3,阵营模式，4,帮派模式）
	int changePkType;		//pk模式更改类型；（0,不可以改变PK模式 1,可以改变PK模式）

	int	levelLowerLimit;	//跳转点等级下限制；
	int levelUpperLimit;	//地图跳转点等级上限值；
	/******************* xhm added end****************************/
	int flgThk;
	
	/* 地图思考标志，判断地图是否有人*/
	bool flgCpy;					
	
	/*地图上所有玩家的fd*/
	set<int> heroFd;  	
	
	/*可采摘的物品*/	
	map<string,TakeGoods*> takeGoodsMap;
	
	map<string,Bottle*> botInMap;	
	
	map<string,Trap*> trapInstMap;
	
	map<string,MonsterActiveBoss*> monActBoss;
	
	list<string> monAttRedList;
	
	list<string>::iterator redMon_it;
	
	int bruRedMonCtn;
	
	/*对标对应id集合*/
	map<string, set<string> > lPos_to_heroId;		//在每张地图中建立器逻辑坐标为索引，对应Hero对象指针列表的map容器对象
	
	/*所有掉落物品id*/
	map<string,Pick*> dropGoodsMap;
	
	map<string,MonsterBase *>::iterator escapePt_it;
	
	set<Point> dishPtSet;
	
	bool isActiveDishBru;                           //系统是否已点过了，是表示点过了
	
	/*中心坐标*（方便一中心点，随机生成坐标点）*/
	Point centerPt;   
	
	/*半径*/
	size_t radius;
	
	/*随机生成点累计*/
	size_t randPtCtn;
	
public:	
	
	/*静态变量，控制地图上怪物思考时间的错开*/
	int	campEntFlag;		//不加阵营是否可进图该地图标记值（0，可进入 1，不可进入）；
	static int count;                           //add chenzhen 6.1 怪物思考思考时间错开
public:
	
	/*初始化九宫格*/
	void InitBox(void);
	
	/*获得九宫格*/
	Nbox* getBox(void);
	
	/*获得地图id*/
	char* getMapId(void);
	
	/*获得地图id*/
	char* getIdentity(void);
	
	/*获得地图宽度（像素）*/
	int getHeight(void);
	
	/*获得地图高度（像素）*/
	int getWidth(void);
	
	/*获得地图偏移量*/
	int getBaseDigst(void);
	
	/*获得地图宽度（网格）*/
	int getRow(void);
	
	/*获得地图宽高（网格）*/
	int getCol(void);

	/*构造函数*/
	Map_Inform(char *_mapId,char *_mapFilePath,char *_mapName,int _mapWidth,\
	int _mapHeight,int _row,int _col,int _baseDigst,Point _entPt,\
	Point _outPt,Point _tribesPt,Point _religionPt,Point _rangerPt,\
	map<string,MonsterBase *>& _monId_connect_monster,\
	map<string,const jumpId_infor*>& _jumpId_connect_jumpInfo,\
	map<string,TakeGoods*> &_takeGoodsMap,map<string,Bottle*> &_botInMap,\
	map<string,Trap*> &_trapInstMap,set<Point> _dishPtSet,Point _centerPt,size_t _radius,bool _flgCpy,\
	int warType=1,int _changePkType=0,int _mapType=0,int _campEntFlag=0,\
	int _levelLowerLimit=0,int _levelUpperLimit=100);
	
	/*设置地图障碍点*/
	void setMapHinder(vector< vector<int> > &_map_hinder);
	
	/*获得地图障碍点信息*/
	vector< vector<int> >& getMapHinder(void);     	//返回map_hinder引用，特别小心
	
	/*获得地图怪物信息*/
	map<string,MonsterBase *>& getMonId_connect_monster(void);
	
	map<string,const jumpId_infor*>& getJumpId_connect_jumpInfo(void);//返回引用；	
	
	/*析构函数*/
	~Map_Inform(void);       						
	
	
	/*初始化计时器*/
	void initTimer(void);	
	
	/*地图思考回调函数*/
	virtual void mapThkCalBak(void) = 0;	
	
	/*获得地图入口*/
	Point getEntPt(void);
	
	/*获得地图出口*/
	Point getOutPt(void);
	
	/*获得副本标志*/
	bool getFlgCpy(void);	
	
	/*插入九宫格id*/
	bool insertID(StyObj &obj);						
	
	/*修改heroId在Map_Inform中九宫格内的位置，在command_time_poll.cpp内调用*/
	bool updateID(StyObj &obj,Point &newPt);			
	
	/*删除一个id*/
	bool deleteID(StyObj &obj);						//删除hero id
	
	/*获取玩家的当前像素坐标点*/
	bool getPtNow(StyObj &obj,Point &piexPt);
	
	/*判断逻辑点是否正确*/
	bool judgeLogPt(Point &logPt);

	/*把一个逻辑点转换成字符串*/
	void logPtToStr(string &logPtStr,Point &logPt);
	
	/*重载获得九宫格内容函数，通过id*/
	void getStaInSrcVec(StyObj &obj,map<string,StyObj> &reselt);

	/*从lPos_to_heroId中删除一个对象的id*/
	bool eraseObjId(string &logPtStr,string &objId);

	/*从lPos_to_heroId中插入一个对象的id*/
	bool insertObjId(string &logPtStr,string &objId);

	/*获取怪物的当前像素坐标点*/
	bool getPtMonNow(string monId,Point &piexPt);
	
	/*获取瓶罐的当前像素坐标点*/
	bool getPtBotNow(string botId,Point &piexPt);
	
	/*获取宠物的当前像素坐标点*/
	bool getPtPetNow(string petId,Point &piexPt);
	
	/*获取玩家的当前像素坐标点*/
	bool getPtHeroNow(string heroId,Point &piexPt);

	
	/*设置怪物信息*/
	void setMonId_connect_monster(map<string,MonsterBase *>& _monId_connect_monster); 
	
	/*地图停止思考*/
	void stopThk(void);
	
	/*插入玩家fd*/
	void inPutFd(int fd);
	
	/*删除玩家fd*/
	void delFd(int fd);
	
	/*获得在此地图人数*/
	int getFdSze(void);
	
	/*设置地图怪物所在地图实例指针*/
	
	void setMonMap(void); 
	
	/*获得此地图上所有玩家fd*/
	set<int> getHeroFd(void);
	
	/*复制地图怪物实例以及和刷怪记录表*/	
	void copyMapMon(map<string,MonsterBase*> &newMonIn,\
					char *newMapId,map<string,const jumpId_infor*>&\
					newjumpId_connect_jumpInfo);
							
	/*打印测试地图信息*/
	void printMonsterInform(void);
	
	/*获得此地图入口点的逻辑坐标*/
	Point getLogicEntPt(void);
	
	/*_index 为阵营的下标，获取对应阵营在阵营战下的像素点坐标，0支派，1宗教，2游侠 其他默认为支派*/
	Point getCampWarPt(int _index);
	
	/*重置整张地图信息*/
	virtual void initMap(void);
	
	/*设置地图思考标记值*/
	void setThkFlg(int _thkFlg);
	
	/*通过怪物id获得怪物实例指针*/
	MonsterBase* getMonsterObj(string monId);
	
	/*通过怪物id获得怪物实例指针*/
	TakeGoods* getTakeObj(string takeGoodsId);
	
	/*获得整个怪物信息*/
	void getAllMonObj(vector<MonsterBase*> &monObj);
	void getAllMonObj(vector< vector<MonsterBase *> > &);
	/*暂停此地图上已刷出怪的思考*/
	virtual void stopAllLveMonThk(void) = 0;
	
	/*重启此地图上所有已刷出怪的思考*/	
	virtual void reSetAllLveMonThk(void) = 0;
	
	/*复制可摘取物品*/
	void copyTakeGoods(map<string,TakeGoods*> &_takeGoodsMap,char *_mapId);
	
	/*设置可摘取物品地图实例指针*/
	void setTakeGoodsMap(void);
	
	/*获取摘取物品的当前像素坐标点*/
	bool getPtTakeGoodsNow(string takeGoodId,Point &piexPt);
	
	/*设置可摘取物品地图实例指针*/
	void bruTakeMsg(void);
	
	/*摘取物品消亡*/
	void disperTakeGood(string _takeGoodId);
	
	/*获取马车的当前像素坐标点*/
	bool getPtWagonNow(string heroId,Point &piexPt);
	
	/*复制可摘取物品*/
	void copyBotInMap(map<string,Bottle*>& _botInMap,char *_mapId);
	
	/*设置瓶罐物品地图信息*/
	void setBotMap(void);
	
	/*通过瓶罐实例id获得瓶罐实例*/
	Bottle* getBotInst(char *_botId);
	
	/*刷出地图瓶罐信息*/
	void brushBotMsg(void);
	
	/*复制陷阱*/
	void copyTrapVec(map<string,Trap*> &_trapInstMap,char *_mapId);
	
	/*设置陷阱地图信息*/
	void setTrapMap(void);
	
	/*刷出地图陷阱信息*/
	void brushTrapMsg(void);
	
	/*通过陷阱实例id获得陷阱实例*/
	Trap* getTrapInst(char *_trapId);
	
	/*获取陷阱的当前像素坐标点*/
	bool getPtTrapNow(string trapId,Point &piexPt);
	
	/*获取掉落物品的当前像素坐标点*/
	bool getPtPickNow(string pickid,Point &piexPt);
	
	/*获取玩家实例指针*/
	Hero* getHero(char *heroId);
	
	/*获取玩家实例指针*/
	void trapAttack(void);
	
/****************** xhm added start***************************/	
	/*
		@argument： void
		  @return： int 1 和平模式 2 全体模式 3 阵营模式 4 帮派模式
		@function： 获取当前地图作战模式
	*/
	int getWarType(void);
	
	/*
		@argument： void
		  @return： int 1 和平模式 2 全体模式 3 阵营模式 4 帮派模式
		@function： 获取当前地图作战模式
	*/
	void setWarType(int _index);	
	
	
	/*
		@argument： void
		  @return： int 0，不可切换作战模式 1，可以切换作战模式
		@function： 获取当前地图切换作战模式类型
	*/
	int getChangePkType(void);
	
	/*
		@argument： void
		  @return： int 0主城 1场景 2副本 3帮派战 4阵营战 5守卫扬州
		@function： 获取当前地图类型
	*/	
	int getMapType(void);
	
	/*
		@argument： void
		  @return： int 0主城 1场景 2副本 3帮派战 4阵营战 5守卫扬州
		@function： 获取当前地图类型
	*/	
	void setMapType(int _index);	
	

	/*
		@argument： void
		  @return： int 0不加阵营可进入 1不加阵营不可进入
		@function： 获取当前地图不加阵营是否可切换类型
	*/	
	int getCampEntFlag(void);

	/*
		@argument： void
		  @return： int 当前地图最低等级限制；
		@function： 获取当前地图最低等级限制；
	*/	
	int getLevelLowerLimit(void);

	/*
		@argument： void
		  @return： int 当前地图最低等级限制；
		@function： 获取当前地图最高等级限制；
	*/	
	int getLevelUpperLimit(void);	
/****************** xhm added end***************************/
	
	/*怪物死亡*/
	virtual void GromonDead(char *monId);
	
	string getTd_roomid(void);
	
	void setTd_roomid(string td_inst_room);

	
	/*副本回收标志*/
	virtual bool recoverCpy(void);
	
	/*清空九宫格中的内容*/
	void clearBox(void);
	
	/*测试打印副本中存活列表信息*/
	void testMonsterWait(void);
	
	/*重置怪物的存货管理器*/
	void initMonLvMager(void);
	
	/*判断逻辑点是否为障碍点<传入点为逻辑点>*/
	bool judgeLogPtHind(Point &logPt);
	
	/*更新副本怪物数目*/
	virtual void sentSumMonMsg(void);
	
	/*杀死一个怪*/
	virtual void killOneMon(void);	
	
	/*插入野外boss*/
	void insertBoss(MonsterActiveBoss* newBoss);
	
	/*设置所有在此地图上的野外BOSS的地图指针*/
	void setMonBossMap(void) ;
	
	/*刷出所有在此地图上的野外BOSS*/
	void brushMonBoss(void);
	
	/*重置所有在此地图上的野外BOSS*/
	void initMonBoss(void);
	
	/*判断像素坐标是否合法*/
	bool judgePiex(Point &piexPt);
	
	/*生成怪物数目信息<纯虚函数>*/
	virtual char* getSumMonMsg(void) = 0;
	
	/*获取掉落装备的当前像素坐标点*/
	bool getPtEquipNow(string equipId,Point &piexPt);
	
	/*重置陷阱信息*/
	void initTrap(void);
	
	/*启动陷阱计时器*/
	void reSetTrapThk(void);
	
	/*暂停陷阱计时器*/
	void stopTrapThk(void);
	
	/*重置地图的时候,清空该地图中的所有掉落物品*/
	void clearDropMap(void);
	
	/*按队列每次刷出一个击杀红名的怪*/
	void brushRedMon(void);
	
	/*队列中每只怪刷出来的间隔时间*/
	bool isNextRedMonOut(void);
	
	/*随机一个逃窜点*/
	bool randEscapePt(Point &endFinPt);
	
	/*点菜*/
	TakeGoods * olderKandy(char *dishId,char *_onwerId,char *_nickName);

	/*查找某个掉落物*/
	Pick* getDropPickInst(char *pickId);
	
	/*删掉某个掉落物*/
	void deleteDropInst(char *pickId);
	
	/*掉落时，插入掉落物*/
	void insertDropInst(Pick *dropGoods);
	
	/*动态生成宴席*/
	TakeGoods* newDishInst(char *dishId);
	
	/*清掉宴席*/
	void clearDish(void);
	
	/*通过菜单id删掉某个宴席实例*/
	void delOneDish(char *takeGoodsId);
	
	/*判断两个逻辑点之间是否存在障碍点*/		
	bool judgeLineCanPas(Point &logBeginPt,Point &logEndinPt);
	
	/*垂直于x轴的直线之间是否有障碍点*/
	bool verticlalLineX(Point &logBeginPt,Point &logEndinPt);
	
	/*垂直于y轴的直线之间是否有障碍点，有障碍点，则返回假，否则为真*/
	bool verticlalLineY(Point &logBeginPt,Point &logEndinPt);
	
	/*判断一个double是否为整形,如果是则返回真，且intValues为此整数*/
	bool isIntDigst(double y,int &intValues);
	
	/*斜线之间是否有障碍点，有障碍点，则返回假，否则为真*/
	bool slantLine(Point &logBeginPt,Point &logEndinPt);
	
	/*重置地图瓶罐信息*/
	void initBot(void);
	
	/*根据角色生成怪物属性*/
	void initMonValues(Hero *enterHero);
	
	/*动态生成宴席*/
	TakeGoods* newDishInst(TakeGoods *confDish);
	
	/*系统请客*/
	void systemTreat(void);
	
	/*系统请客辅助函数*/
	TakeGoods* systemTreatAsist(void);
	
	/*系统请客辅助函数*/
	char* getSystemTreatId(void);
	
	/*获得系统是否已点过菜，是表示点过*/
	bool getIsActiveDishBru(void);
	
	/*设置系统是否已点过菜，是表示点过*/
	void setIsActiveDishBru(bool _isActiveDishBru);
	
	/*更改系统宴席为可吃状态*/
	void setSystemDishState(int _dishState);
	
	/*获取雕像的当前像素坐标点*/
	bool getPtStatuaryNow(string statuaryId,Point &piexPt);
	
	/*初始化雕像怪*/
	void initMonStatuary(void);
	
	/*刷出四张桌子*/
	void brushTable(void);
	
	/*资源战中刷出资源数*/
	void brushTakeSource(int _num,bool isPartyWar = false,int _flagA = -1);
	
	/*重置可摘取物品的数据*/
	void initTakeGoods(void);
	
	/*点菜*/
	TakeGoods* olderKandy(char *dishId,char *deskInstId,char *_onwerId,char *_nickName);
	
	/*系统宴请活动结束*/
	void activeCloseDish(void);
	
	/*随机生成点*/
	bool randRescePt(Point &resultPt);
	
	/*初始化雕像怪*/
	void initMonStatuaryByHero(Hero *hero);
	
	/*刷出任务怪*/
	char* brushTaskMon(Hero *hero,char *npcId,int taskType = 3);
	
	/*召唤n个陷阱*/
	void callTrap(size_t n);
	
	/*召唤所有陷阱*/
	void callTrap(const vector<string> &herIdSet);
	
	/*召唤所有怪*/
	void callMon(MonsterBase *callBoss);
	
	/*召唤n个怪*/
	void callMon(size_t n);
	
	private :
	
	void getHeroInstSet(const vector<string> &herIdSet,vector<const Hero*> &herInstVec);
	
	bool randCallMonPt(const Point &bossPt,Point &resultPt,const int &bossRadius);
};
#endif 
