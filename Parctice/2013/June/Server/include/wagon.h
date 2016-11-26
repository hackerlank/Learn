#ifndef WAGON_H
#define WAGON_H
#include<set>
#include<string>
#include"libev.h"
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
const int TYPEWAGON = 1;

using namespace std;

//马车颜色刷新概率
typedef struct wagonColorRank_S
{
	int upRate;						//上升率
	int downRate;					//下降率
	int stillRate;					//不变率
	char worseWagonId[51];				//低一品级马车Id
	char betterWagonId[51];				//高一品级马车ID
	wagonColorRank_S(int _upRate, int _downRate, int _stillRate, char *prev, char *next)
	{
		upRate = _upRate;
		downRate = _downRate;
		stillRate = _stillRate;
		strncpy(worseWagonId, prev, sizeof(worseWagonId));
		strncpy(betterWagonId, next, sizeof(betterWagonId));
	}
}wagonColorRank_T;

class Hero;
class Wagon
{
	Point pt;                 //像素坐标
	char id[SHOR_MID_VALUE_LENGTH + 1];	              //实例id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //类型id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //图片id
	char name[SHOR_MID_VALUE_LENGTH + 1];              //名称
	char color[SHOR_MID_VALUE_LENGTH + 1];             //马车的颜色
	char ownerId[51];									//马车主人ID
	int lifeVal;              //马车生命值
	int lifeUperVal;          //血量上限值
	int hurt;                 //每次击打马车伤害值
	float rewardTimes;			//马车奖励系数
	
	char bornMsg[IN_VIEW_LENGTH + 1];           //出生信息
	char outMsg[IN_VIEW_LENGTH + 1];		      //下线消息
	Map_Inform *mapNow;			//马车所在地图
	Point logicPt;            //逻辑坐标
	ev_timer think_timer;    //计时器
	// static int count;
	bool bruOut;
	ev_timer moveTimer;
	ev_timer speedGameCtlTimer;
	ev_timer incSpeedTimer;
	
	bool haveSpeedGame;
	int blackSpeed;
	int yellowSpeed;
	int redSpeed;
	double gameLastTime;
	double gameCdTime;
	double incSpeedTime;
	int gameCtlState;
	bool SpeedUpOnce;
	
	int routeIndex;
	int routeSize;
	int routeArrUsedIndex;
	int routeArr[1024];
public:
	char noUseMem[1024];
	list<Point> keyPath;				//路径点
	Point currPt, endPt, speedPt;		//本次路径搜寻起点与终点
	int speed;						//移动速度
	int lastSpeed;
	Wagon(char *_typeId,int _lifeVal,int _hurt,char *_color,char *_name,char *_photoId, float rewardTimes, bool _haveSpeedGame,
		int _blackSpeed, int _yellowSpeed, int _redSpeed, double _gameLastTime, double _gameCdTime, double _incSpeedTime);
	~Wagon(void);
	/*生成刷出信息*/
	void formBornMsg(void);
	
	/*获得id*/
	char *getId(void);
	
	/*生成下线信息*/
	void formOutMsg(void);
	
	/*获得玩家实例指针*/
	Hero* getHero(char *heroId);
	
	/*设置马车主人实例指针*/
	bool setOwnerId(char *ownerId, Hero* owner);
	
	/*领出马车*/
	void dirveWagon(char *ownerId);
	
	/*修改逻辑坐标时，也对应的修改了其像素坐标,匹配客户端的心跳*/
	void setLogicPt(Point _logPt);
	
	/*修改像素坐标时，也对应的修改了其逻辑坐标,匹配客户端的心跳*/
	void setLocation(Point _pt, int flag = 0);
	
	/*获得像素坐标点*/
	Point getPt(void);
	
	/*获得逻辑坐标点*/
	Point getLogicPt(void);
	
	/*当主人切换地图时*/
	void ownerChageMap(void);
	
	/*复制马车*/
	Wagon* copyWagon(void);
	
	/*获得马车id*/
	char* getWagonId(void);
	
	/*设置实例id*/
	void setInstId(char *_id);
	
	/*刷出马车*/
	void brushMsg(void);
	
	/*马车从地图消亡*/
	void disperMsg(void);
	
	/*设置马车的生命值*/
	void setLifeVal(int _lifeVal);

	//马车被攻击
	bool beAttacked(void);
	//获取马车当前血量
	int getLifeVal(void);
	//获取每次攻击伤害
	int getHurt(void);
	//获取马车主人
	Hero *getOwner(void);
	//马车主人ID
	char *getOwnerId(void);
	//获取上线消息
	char* getOnlineMsg(void);
	//获取下线消息
	char* getOfflineMsg(void);
	
	/*马车场景跳转*/
	bool enter_scene();
	
	/*马车退出场景*/
	bool quit_scene();
	
	/*实例计时器函数*/
	void initTimer(void);
	
	/*暂停思考*/
	void deleteTimer(void);   

	char* getIdentity(void);
	
	//和主人离婚
	void divorceWithOwner(void);
	//获取马车地图
	Map_Inform *getMap();
	void stopMoveTimer();
	void startMoveTimer();
	Point getLocation();
	float getRewardTimes();
	//获取血上限
	int getLifeUpperVal();
	
	void setSpeed(int newSpeed);
	void changeSpeed(int chgSpeed = 0);
	void stopSpeedGameCtlTimer();
	void startSpeedGameCtlTimer(int flag = 0);
	void stopIncSpeedTimer();
	void startIncSpeedTimer(int speedColor = 0);
	int getSpeed();
	int getLastSpeed();
	
	void pushOneRoutePt(int x, int y);
	void popOneRoutePt(Point &pt);
	void routeClear(); 
	int getRouteIndex();
	int getRouteSize();
	void viewRouteMsg(char* routeMsg);
	
};
#endif
