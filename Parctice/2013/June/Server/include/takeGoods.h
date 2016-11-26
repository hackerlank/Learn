#ifndef TAKE_GOODS_H
#define TAKE_GOODS_H
#include<string>
#include<set>
#include<map>
#include<time.h>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
#include"libev.h"
#include"astar.h"
const int TYPETAKEGOODS = 0;

using namespace std;
class Map_Inform;
class Hero;
class TakeGoods
{
	Point pt;                 //像素坐标
	char id[SHOR_MID_VALUE_LENGTH + 1];	              //实例id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //类型id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //图片id
	char name[SHOR_MID_VALUE_LENGTH + 1];              //名称
	char bornMsg[IN_VIEW_LENGTH + 1];           //出生信息
	char outMsg[OUT_VIEW_LENGTH + 1];		      //下线消息
	char dishOwner[SHOR_MID_VALUE_LENGTH + 1];    //宴席的宴请人
	char dishNewNme[SHOR_MID_VALUE_LENGTH + 1];   //宴席被点后，追加的新名字
	char offerWords[SHOR_MID_VALUE_LENGTH + 1];   //提示信息
	Point logicPt;            //逻辑坐标
	Map_Inform *map_now;          //地图实例指针
	char goodsId[SHOR_MID_VALUE_LENGTH + 1];               //物品Id
	static int count;
	bool bruOut;
	bool isDispear;                //采集后是否会消失
	bool trigByMsg;                //是否为消息触发
	ev_timer think_timer;    //计时器
	
	int takeModle;           //可采集物品同时可采集的类型
	int taskStyle;           //可采集物品的类型
	int brandType;			//子类型
	double takeTme;         //采集持续时间
	set<string> onwerSet;   //采集人id的集合
	bool isMove;            //宠物会动
	
	Astar *astar;             //a星
	ev_timer moveTimer;		 //移动定时器
	Point bornPiexPt;        //出生像素点
	Point bornLogPt;         //出生逻辑点
	int speed,lastSpeed;               //移动速度
	
	bool flgEndPt;           //寻路终点是否已寻到
	Point endFinPt;
	
	
	int durTme;              //宴席持续时间
	struct timeval beginTme;	//宴席开始时间
	
	int moveCtn;               //运动时间累积
	int moveRate;               //运动的频率
	
	int dishState;              //宴席状态（0表示角色点的菜，1表示系统点的菜，但是由于时间还没有到而不能吃，2表示系统点的菜，且时间到了，可以吃）
	
	bool isDished;              //是否一点菜（是表示刷出来的是有菜的桌子，否则是空桌子）
	char emptyPhotoId[SHOR_MID_VALUE_LENGTH + 1];           //空桌子的图片id
	bool chgState;              //防止多次调bursh函数（真表示可以刷，假则不刷）
	
	bool isCampSource;          //是否是阵营资源战里面的资源,真为是
	bool isUsed;                //是否已经刷出了，真为是
	
	
	char ownerNickName[SHOR_MID_VALUE_LENGTH + 1];  //新旗帜的昵称（用在帮派战里面）
	int ownerType;             //归属属性键（用在帮派战里面）
	char ownerValue[SHOR_MID_VALUE_LENGTH + 1];  //归属属性值（用在帮派战里面）
	bool isInterrupt;         //是否打断，真为可以被打断
public:
	Point currPt,endPt;
	list<Point>keyPath;
	
	
public:
	TakeGoods(char *_typeId,char *_goodsId,char *name,char *_photoId,\
	bool _isDis,bool _trigByMsg,int _takeModle,int _taskStyle,\
	int _brandType,double _takeTme,char *_offerWords,int _durTme,\
	bool _isMove,bool _isInterrupt);
	
	/*析构函数*/
	~TakeGoods(void);
	
	/*生成刷出信息*/
	void formBornMsg(void);
	
	/*生成下线信息*/
	void formOutMsg(void);	
	
	/*获得id*/
	char* getId(void);
	
	/*获得被攻击玩家实例指针*/
	Hero* getHero(char *heroId);
	
	/*设置地图以及逻辑坐标*/
	void setLogicMap(Map_Inform *_map_now);
	
	/*设置地图以及逻辑坐标*/
	TakeGoods* copyTakeGoods(Point _pt,bool _isResource = false,bool isUid = false);
	
	/*设置像素坐标*/
	void setPt(Point _pt);
	
	/*获得像素坐标*/
	Point getPt(void);
	
	/*获得摘取物品id*/
	char* getTakeId(void);
	
	/*获得逻辑坐标*/
	Point getLogicPt(void);
	
	void brushMsg(void);
	
	bool getBruOut(void);
	
	/*设置实例id*/
	void setInstId(char *_id);
	
	char* getBronMsg(void);
	
	/*摘取物品消亡*/
	void disperMsg(void);
	
	char* getGoodsId(void);
	
	char* getOutMsg(void);	
	
	/*获得触发方式*/
	bool getTrigFlg(void);
	
	/*获得采集持续时间*/
	double getTakeTme(void);
	
	/*清空采集人集合*/
	void clearOwner(char *ownerId = NULL);
	
	/*清空采集人集合*/
	void inPutOwner(char *ownerId);
	
	/*设置像素坐标和逻辑坐标*/
	void setLocation(Point _pt,int flag = 1);
	
	/*判断此采摘物是否归位*/
	bool isRec(void);
	
	/*获得是否会动的标志*/
	bool getIsMove(void);
	
	/*寻路追击函数*/
	void findAttWay(Point &end);
	
	/*暂停掐点计时器*/
	void stopMoveTimer();
	
	/*暂停移动*/
	void stopMove(void);
	
	/*路径平滑处理*/
	void smoothRoadPt(void);
	
	/*启动掐点计时器*/
	void startMoveTimer();
	
	/*把寻路寻到的逻辑点转换成像素点*/
	void exchgeWayRod(void);
	
	/*获得地图实例指针*/
	Map_Inform* getMap(void);
	
	/*获得速度*/
	int getSpeed(void);
	
	/*获得最后点速度*/
	int getLastSpeed(void);
	
	/*获得移动终点*/
	void getEndPt(void);
	
	/*获得可摘取物品类型*/
	int getTaskStyle(void);
	
	/*获取采集物品子类型*/
	int getBrandType(void);
	
	/*复制瓶罐*/
	TakeGoods* copyTakeGoods(char *_mapId);
	
	/*会动的可摘取物的回调函数*/
	void calBack(void);
	
	/*设置宴请主人*/
	void setDIshOwner(char *_ownerId);
	
	/*获得宴席持续总时间*/
	int getTolDurTme(void);
	
	/*获得宴席持续还剩多长时间*/
	int getLastTme(void);
	
	/*获得宴席的新名字*/
	void setDishNewNme(char *nickNme);
	
	/*获得可摘取物品相应的提示信息*/
	char* getOfferWords(void);
	
	/*计算获得运动频率*/
	void  ctnMoveRate(void);
	
	/*是否可以动*/
	bool isMoveTme(void);
	
	/*获得类型id*/
	char* getTypeId(void);
	
	/*获得宴席是否可吃状态值*/
	int getDishState(void);
	
	/*设置宴席是否可吃状态值*/
	void setDishState(int _newState);
	
	/*设置空宴席的图片id*/
	void setEmptyPhotoId(char *_emptyPhotoId);
	
	/*设置宴席是否已点菜*/
	void setIsDished(bool _isDished);
	
	/*获得宴席是否已点菜*/
	bool getIsDished(void);
	
	/*设置宴席图片id*/
	void setPhotoId(char *_photoId);
	
	/*设置宴席名字*/
	void setName(char *_name);
	
	/*获得宴席图片id*/
	char* getPhotoId(void);
	
	/*获得宴席名字*/
	char* getName(void);
	
	/*重置宴席的名字*/
	void initDishNewNme(void);
	
	/*重置宴席的主人名字*/
	void initDishOwner(void);
	
	/*获得是否是阵营资源战里面的资源,真为是*/
	bool getIsCampSource(void);
	
	/*获得是否是阵营资源战里面的资源,真为是*/
	void setIsCampSource(bool _isCampSource);
	
	/*阵容资源是否已经刷出了，真为是*/
	bool getIsUsed(void);
	
	/*阵容资源是否已经刷出了，真为是*/
	void setIsUsed(bool _isUsed);
	
	/*重置可摘取物品的数据*/
	void initTakeGoods(void);
	
	/*重置帮派战里面的旗帜*/
	void initFlagByHero(char *heroId);
	
	/*获得归属值*/
	char* getOwnerValue(void);
	
	/*获得归属类型*/
	int getOwnerType(void);	
	
	bool isPicking();
	
	//是否打断，真为可以打断
	bool IsInterrupt();
};
#endif
