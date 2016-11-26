#ifndef TRAP_H
#define TRAP_H
#include"libev.h"
#include<set>
#include<string>
#include"data_structure_struct.h"
#include"command_return_define_data.h"
#include"other_define_data.h"
#include"boxAsist.h"
const int TYPETRAP = 3;

using namespace std;
class Hero;
class Map_Inform;
class Trap
{

	char id[SHOR_MID_VALUE_LENGTH + 1];	              //实例id
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //类型id
	char photoId[SHOR_MID_VALUE_LENGTH + 1];           //图片id
	char name[SHOR_MID_VALUE_LENGTH + 1];              //名称
	int attackRge;                  //攻击距离
	double cdTme;              //cd 时间	
	char bornMsg[IN_VIEW_LENGTH + 1];           //出生信息
	char outMsg[OUT_VIEW_LENGTH + 1];		      //下线消息
	char attMsg[TRAP_ATT_LENGTH + 1];
	Point logicPt;            //逻辑坐标
	Point pt;                 //像素坐标
	Map_Inform *map_now;         
	static int count;

	ev_timer think_timer;    //计时器
	int cdPlay;              //攻击播放时间<折算成思考时间>
	int playCtn;             //动画攻击时间
	bool isAtt;              //是否攻击
	int attStyle;            //攻击模式
	double attPercent;       //伤害百分比
	
	bool isDispear;          //是否会消失
	
	bool isWarning;          //是否有警示，真为有
	char warningMsg[IN_VIEW_LENGTH + 1];           //警示消息
	ev_timer warnTimer;    //警示计时器
	double warnTime;          //警示时间
	bool isWarned;           //只要预警过，就必须劈
	bool isCalled;       //是否是boss召唤出来的标记值，真为召唤陷阱
	bool isUsed;             //是否被用，真为已经刷出被用
	bool isMove;         //是否可以移动，真为可以
public:
	Trap(char *_typeId,double _attack,int _attackRge,int _attStyle,double _cdTme,bool _isWarning,double _waringTime,char *_name,char *_photoId);
	
	/*生成刷出信息*/
	void formBornMsg(void);
	
	/*获得id*/
	char* getId(void);
	
	/*生成下线信息*/
	void formOutMsg(void);	
	
	/*设置地图实例指针*/
	void setMap(Map_Inform *_map_now);
	
	/*获得逻辑坐标点*/
	Point getLogicPt(void);

	/*复制陷阱*/
	Trap* copyTrap(char *_mapId);
	
	
	/*设置实例id*/
	void setInstId(char *_id);
	
	/*刷出瓶罐*/
	void brushMsg(void);
	
	/*瓶罐从地图消亡*/
	void disperMsg(void);
	
	/*设置像素坐标*/
	void setPiexPt(Point _pt,bool flag = false);

	/*析构函数*/
	~Trap(void);
	
	/*获得陷阱的实例id*/
	char* getTrapId(void);
	
	/*复制陷阱<重载函数，在读取地图配置文件里面用>*/
	Trap* copyTrap(Point _pt,bool _isCalled);	
	
	/*获得陷阱的攻击距离*/
	int getAttackRge(void);
	
	/*获得陷阱的折算成地图思考次数*/
	double getCdTme(void);
	
	/*获得上线消息*/
	char* getBronMsg(void);	
	
	/*攻击人物*/
	bool AttackPerson(void);
	
	/*获得下线消息*/
	char* getOutMsg(void);
	
	/*获得像素坐标*/
	Point getPiexPt(void);
	
	/*启动计时器*/
	void initTimer(void);
	
	/*陷阱回调函数*/
	bool calBack(void);
	
	/*重置陷阱信息*/
	void initTrap(void);
	
	/*暂停计时器*/
	void stopTimer(void);		
	
	/*获得是否会消失的标记值*/
	bool getIsDispear(void);
	
	/*启动消失计时器*/
	void initTimerDispear(void);
	
	/*预警函数*/
	bool warning(void);
	
	/*设置召唤标记值*/
	void setIsCalled(bool _isCalled);
	
	/*获得召唤标记值*/
	bool getIsCalled(void);
	
	/*获得是否被刷出的标记值*/
	bool getIsUsed(void);
	
	/*判断是否可以移动*/
	bool getIsMove(void);	
	
	private:
	
	/*获得陷阱的攻击力*/
	double getAttack(void);
	
	/*计算攻击力*/
	int getAttackPow(int heroLife);
	
	/*获得玩家实例指针*/
	Hero* getHero(char *heroId);
	
	/*人物掉血处理*/
	int judgeAttackPersonDie(Hero *hitedHero,int attPow);	
	
	/*是否在cd攻击动画中*/
	bool isPlayCd(void);
	
	/*重置陷阱警示信息*/
	void initWarnDispear(void);
	
	/*判断攻击范围内是否有人*/
	bool isAttackPerson(set<string> &HeroIdSet);
	
	/*生成警示消息*/
	void formWarnMsg(void);
	
	/*移动更改坐标*/
	void move(Point piexPt);
	
};
#endif
