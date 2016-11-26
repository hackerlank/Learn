#ifndef MONSTERBASE_H
#define MONSTERBASE_H
#include"game_fight_assist.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"astar.h"
#include <list>
#include<stdlib.h>
#include<map>
#include"data_structure_struct.h"
#include"library_head.h"
#include"libev.h"
#include"map_inform.h"
#include"hero.h"
#include"monster_other_action_function.h"
#include"hatValRue.h"

#include"bruMonInfor.h"
#include<time.h>
#include<unistd.h>
#include"other_define_data.h"
#include<math.h>
#include"skillBase.h"
#include"monster_base_asist.h"
#include"five_elements.h"
#include"boxAsist.h"
#include"wholeDefine.h"
#include"move_asist.h"
class SkillBase;
class Map_Inform;
extern const string DROP_BLOOD_ID; // move to cpp for safety = "X010";                  //持续掉血
	
class MonsterBase
{
protected:

	char mapId[SHOR_MID_VALUE_LENGTH + 1];        //对应地图的id   Evan add
	
	char nickName[LONG_MID_VALUE_LENGTH + 1];     //对应怪物的昵称（一种类型的怪只有一个昵称）
	
	char appendNickName[LONG_MID_VALUE_LENGTH + 1];   //任务怪改名字
	
	char typeId[SHOR_MID_VALUE_LENGTH + 1];        //怪物数值属性标识ID
	
	char identity[SHOR_MID_VALUE_LENGTH + 1];     //怪物实例id
	
	char stage[SHOR_MID_VALUE_LENGTH + 1];  
	
	int  lifeUpperVal;  //生命上限值
	
	int  lifeVal;        //当前生命值
	
	int  magicUpperVal;  //魔法上限值   Evan add
	
	int  magicVal;       //当前魔法值   Evan add
		
	Point pt;           //当前坐标点（地图像像素点）	
	
	bool isAlive;        //生死状态,true为活着，false为死	
	
	Point born_pt;         //出生点
	
	ev_timer think_timer;    //计时器
	
	int walk_ranage;      //走路范围
	
	int attack_range;     //攻击范围
		
	Map_Inform *map_now;      //所在地图指针
	
	Astar *astar;             //a星
	
	char photoId[SHOR_MID_VALUE_LENGTH + 1];	         //图片id
	
	Point logic_pt;          //当前逻辑点	
	
	
	vector<string> skill_list;   //技能列表
	
	list<HatVal>enmityValues ;   //仇恨列表
	
	char perHerId[SHOR_MID_VALUE_LENGTH + 1];           // 正在追击的目标id
	
	int hatRge;               //仇恨范围	
	
	char selfMsg[IN_VIEW_LENGTH + 1];          //刷怪时的信息	
	char outMsg[OUT_VIEW_LENGTH + 1];           //下线通知	
	char otherMsg[MONSTER_MSG_LENGTH + 1];       //寻路，战斗消息
	
	int hrtSud;      //秒伤
	
	int outHrt;     //外伤
	
	int inHrt;      //内伤
	
	/*改变前*/
	int out_AttVal;    //外功攻击值
	
	int in_AttVal;    //内功攻击值
	
	int out_DefVal;    //外功防御值
	
	int in_DefVal;    //内功防御值
	
	
	int outAttVal;    //外功攻击值
	
	int inAttVal;    //内功攻击值
	
	int outDefVal;    //外功防御值
	
	int inDefVal;    //内功防御值
	
	int defSumVal;   //防御值总和
	
	/*原来的*/
	int hitCopy;
	
	int hit;        //命中
	
	int crit;       //暴击
	
	int voids;      //闪避
	
	int tenacity;       //韧性	
	
	/*还原前*/
	int tena_city;       //韧性	
	
	int failGoodsLess;   //怪物掉落最大值
	
	int failGoodsMost;   //怪物掉落最大值
	
	int hatVal;      //仇恨值
	
	int gold;       //金币
	
	set<string> failList;  //掉落列表
	
	char kind[SHOR_MID_VALUE_LENGTH + 1];          	//（有三种，即普通，精英，Boss）
	
	char type[SHOR_MID_VALUE_LENGTH + 1];           	//怪物行为类型
	
	
	int experience;        //经验
	
	double angVal;         //boss怒气值
	
	bool flgRun;          //Boss怪逃跑标志
	
	char goodsOwner[IDL + 1]; // 物品归谁
	  
	
	double cdTime;         //普通攻击cd时间
	
	ev_timer cdTimer;    //cd计时器
	
	bool isCdCool;          //cd冷却，真表示已冷却，可以攻击人，否表示可不攻击人
	
	
	bool Rec;        	  //复归原位标志
	
	list<Point>selfWay ;        	//自己巡逻路线
	
	list<Point>::iterator pt_it;    //自己每次巡逻终点处
	
	Point perLstPt;                 //回归原点（即出生点的逻辑点）
	
	vector<SkillBase*> skiInstSet;   //技能列表
	
	vector<SkillTime> moreAtt;       //不覆盖延时性技能
	vector<SkillTime> moreAttDef;       //不覆盖延时性技能
	vector<SkillTime> oneAtt;        //定身延时性技能
	vector<SkillTime> oneAttPt;        //点穴延时性技能
	vector<SkillTime> oneAttDizz;        //点穴延时性技能
	vector<SkillTime> moreAttTen;       //不覆盖延时性技能,韧性
	vector<SkillTime> moreAttHit;       //不覆盖延时性技能,命中
	
	bool skiBody;                    //定身状态,不能移动，但可攻击
	bool attackPoint;                //点穴状态,能移动，但不能攻击
	bool dizz;                       //眩晕状态，不能移动，也不能攻击	

	bool unEnemySta;                //无敌状态，true为无敌
	int rank;                       //等级
	int speed;                      //移动速度
	LveCtnManger lveCtnMager;       //怪物存活次数 
	
	
	int fiveEleInt;      //五行属性代表值
	int fiveEleRank;     //五行等级值
	int fiveHurt;        //五行伤害值
	
	FiveElem *fiveElement;	//五行实例

	int forGo;             //寻路间隔计数点
	int goForCtn;         //怪物寻路计数点
	int expTme;            //经验倍数
	int monyTme;           //金币倍数	
	int kindInt;           //怪物类型<转化成int型>		
	
	bool repFlg;          //自卫反应标志,true 为自卫反应	
	
	Point presuitPt;      //在追击玩家时，判断玩家是否移动
	
	
	char genAttId[SHOR_MID_VALUE_LENGTH + 1];       //普通攻击id	
	
	
	int playCd;                     //动画播放时间<折算成怪物思考时间>
	int plyCdCtn;
	bool isHurt;                    //是否攻击
	bool isInPatrol;                //是否处于巡逻中
	bool isBloodTmeOpenFlg;                //回血计时器是否已开启，已开启为真
	
	ev_timer bloodTimer;    //计时器
	
	bool isPersuitHero;            //是否在追人，真为是
	
	int ownerAttriType;            //类型，帮派为1，阵营为2，3为任务怪,4为可采集任务怪，其余的暂为0
	char ownerAttri[SHOR_MID_VALUE_LENGTH + 1];     //帮派，阵营属性
	
	double attackRatio;          //击杀红名怪按比例来算
	
	bool isInnerAttack;          //偏内功为真，偏外功为假
	
	bool isUsed;                 //任务怪，为假表示此怪还没有被刷出来，否则为真
	char taskOwnerId[SHOR_MID_VALUE_LENGTH + 1];  //此怪是谁的任务怪
	
	ev_timer taskTime;        //任务怪存活时间计时器
	
	//召唤怪
	bool isCallType;             //是否为召唤怪，真为召唤怪
	bool isCalled;               //是否已被召唤
	
	MonsterBase *callBoss;         //召唤怪的boss
	
public:	
	MonsterBase(char *_mapId,char *_typeId,char *_nickName,char *_identity,char *_type,\
	char *_kind,int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
	int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt,\
	int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,int _defSumVal,\
	double _hit,double _crit,int _voids,int _tenacity,int _moveRange,int _hatRange,\
	int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,\
	set<string>& _failId,Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
	int _fiveEleRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
	vector<string> &_skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,\
	char* _ownerAttri,double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager);
	
	ev_timer moveTimer;				//移动定时器
	list<Point> keyPath;
	Point currPt, endPt;
	int lastSpeed;
	void startMoveTimer();
	void stopMoveTimer();
	int getSpeed();
	int getLastSpeed();
	void stopMove(bool _isChgePerPt = true);
	
	
	/*删除一个仇恨值*/
	void dropOneEnmityValues(HatVal &hatva);
	
	/*获得怪物当前仇恨列表*/
	list<HatVal>& getEnmityValues(void);
	
	/*获得一个仇恨值*/
	HatVal* getOneEnmityValues(void);
	
	/*获得怪物攻击距离*/
	int getAttackRange(void);
	
	/*获得怪物所在地图实例指针*/
	Map_Inform* getMap(void);
	
	/*获得怪物图片id*/
	char* getPhotoId(void);	
	
	/*设置怪物图片id*/
	void setPhotoId(char *_photoId);
	
	/*获得怪物昵称*/
	char *getNickName(void);
	
	/*设置怪物生命上限值*/
	void setLifeUpperVal(int _lifeUpperVal);
	
	/*设置怪物当前生命值*/
	virtual void setLifeVal(int _lifeVal);   
	
	/*设置怪物魔法上限值*/
	void setMagicUpperVal(int _magicUpperVal); 
	
	/*设置怪物当前魔法值*/
	void setMagicVal(int _magicVal);
	
	/*获得怪物生命上限值*/
	int getLifeUpperVal(void);
	
	/*获得怪物当前生命值*/
	int getLifeVal(void);
	
	/*获得怪物魔法上限值*/
	int getMagicUpperVal(void);   
	
	/*获得怪物当前魔法值*/
	int getMagicVal(void);
	
	/*获得怪物id*/
	char *getIdentity(void);
	
	/*获得怪物当前像素坐标点*/
   	Point getLocation(void);      //获得当前位置
	
	/*设置怪物当前像素坐标点*/
   	void setLocation(Point _pt, int flag = 0);  //修改当前位置
	
	/*获得怪物当前生命状态值*/
	bool getLifeStation(void);    //获得生死状态
	
	/*设置怪物当前生命状态值*/
	void setLifeStation(bool _life);  //修改生死状态
	
	/*获得怪物所在地图id*/
	char *getMapId(void);
	
	/*获得怪物出生像素坐标点*/
	Point getBornPoint(void);
	
	/*获得怪物当前逻辑坐标点*/
	Point getLogicPt(void);
	
	/*设置怪物当前逻辑坐标点*/
	void setLogicPt(Point _logice_pt);
	
	/*插入怪物技能id*/
	void pushSkillId(char *skillId);
	
	/*获得怪物当前技能id列表*/
	vector<string>& getSkillList(void);
	
	/*设置怪物当前“想”攻击玩家id*/
	void chageEny(char *_perHerId);
	
	/*获得怪物秒伤*/
	int getHrtSud(void) ;
	
	/*设置怪物秒伤*/
	void setHrtSud(int _hrtSud) ;
	
	/*获得怪物外伤*/
	int getOutHrt(void);
	
	/*设置怪物外伤*/
	void setOutHrt(int _outHrt) ;
	
	/*获得怪物内伤*/
	int getInHrt(void);
	
	/*获得怪物活动距离*/
	int getWalkRange(void);
	
	/*设置怪物内伤*/
	void setInHrt(int _inHrt) ;
	
	/*获得怪物外功*/
	int getOutAttVal(void) ;
	
	/*设置怪物外功*/
	void setOutAttVal(int _outAttVal) ;
	
	/*获得怪物内功*/
	int getInAttVal(void) ;
	
	/*设置怪物内功*/
	void setInAttVal(int _intAttVal) ;
	
	/*获得怪物外防*/
	int getOutDefVal(void) ;
	
	/*设置怪物外防*/
	void setOutDefVal(int _outDefVal) ;
	
	/*获得怪物内防*/
	int getInDefVal(void) ;
	
	/*设置怪物内防*/
	void setInDefVal(int _inDefVal) ;
	
	/*获得怪物总防*/
	int getDefSumVal(void) ;
	
	/*设置怪物总防*/
	void setDefSumVal(int _defSumVal) ;
	
	/*获得怪物命中*/
	int getHit(void) ;
	
	/*设置怪物命中*/
	void setHit(int _hit) ;
	
	/*获得怪物暴击*/
	int getCrit(void) ;
	
	/*设置怪物暴击*/
	void setCrit(int _crit) ;
	
	/*获得怪物闪避*/
	int getVoids(void) ;
	
	/*设置怪物闪避*/
	void setVoids(int _voids) ;
	
	/*获得怪物韧性*/
	int getTenty(void) ;
	
	/*设置怪物韧性*/
	void setTenty(int _tenacity) ;
	
	/*设置怪物仇恨范围*/
	void setHatRge(int _hatRange) ;
	
	/*获得怪物最小掉落值*/
	int getFilGdsLess(void) ;
	
	/*设置怪物最小掉落值*/
	void setFilGdsLess(int _failGoodsLess) ;
	
	/*获得怪物最大掉落值*/
	int getFilGdsMore(void) ;
	
	/*设置怪物最大掉落值*/
	void setFilGdsMore(int _failGoodsMost) ;
	
	/*获得怪物仇恨值*/
	int getHatVal(void) ;
	
	/*获得怪物金币*/
	int getGold(void) ;
	
	/*设置怪物金币*/
	void setGold(int _gold) ;
	
	/*怪物下线函数*/
	void out(void); 
	
	/*获得怪物行为属性类型*/
	char* getType(void);             //add chenzhen 5.11
	
	/*设置怪物行为属性类型*/
	void setType(char *_type);       //add chenzhen 5.11
	
	/*获得怪物数据属性id*/
	char *getTypeId(void);
		
	/*获得怪物种类*/
	void setKind(char *_kind);      //add chenzhen 5.31
	
	/*获得怪物物品所属者*/
	char* getGoodsOwner(void);//add chenzhen 6.8
		
	/* 获得Boss怪的怒气值*/
	double getAngVal(void);	
	
	/* 设置Boss怪的怒气值*/
	void setAngVal(double _angVal);	
	
	/*生成刷怪物信息函数*/
	void formBshMsg(void);
	
	/*获得刷怪物信息函数*/
	char* getBshMsg(void);
	
	/*怪物启动思考函数*/
	void initTimer(void);      //add chenzhen 6.5

	/*刷怪函数，此处为纯虚函数*/
	void brushMon(void);	
	
	/*寻路追击函数*/
	void findAttWay(Point &end,bool isPer = true);
	
	/*封装的消息发送函数,全地图发送*/
	void sendMsg(string msg_perHero,string msg_others);
	
	/*获得被攻击玩家实例指针*/
	Hero* getHero(char *_perHerId);
	
	/*获得怪物经验值*/
	int getExperience(void);    //add chenzhen 6.25
	
	/*获得怪物仇恨范围*/
	int getHatRge(void) ;
	 
	/*设置怪物仇恨值*/
	void setHatVal(int _hatVal) ;
		
	/*设置怪物掉落列表*/
	void setFailList(set<string>&  _failList) ;	
	
	/*获得怪物掉落列表*/
	set<string>& getFailList(void);
	
	/*获得怪物种类*/
	char* getKind(void);            //add chenzhen 5.31
	
	/*设置怪物物品所属者*/
	void setGoodsOwner(char *_owner);//add chenzhen 6.8 
	
	/*设置怪物所在地图实例指针，此处为纯虚函数*/
	void setMap(Map_Inform* _map);
	
	/*怪物停止思考函数*/
	void stopThk(void);         //add chenzhen 6.5
	
	/*怪物再次启动思考函数*/
	void resetTimer(void);        //add chenzhen 6.6	
	
	/*寻路*/
	void findSlfWay(Point endPt);
	
	/*仇恨范围搜索*/
	void schRge(void);
	
	/*Boss逃跑函数*/
	void escape(void);

	/*怪物死亡函数，此处为纯虚函数*/
	virtual void die(bool flgInit = false);		
	
	/*初始化技能实例指针列表*/
	void initSkiInst(vector<string> &_skiIdSet);
	
	/*获得技能id列表*/
	void getSkiIdSet(vector<string> &skiIdSet);
	
	/*获得diedNoThink的值*/
	virtual bool getDiedNoThink(void);			
	
	/*插入一个仇恨值*/
	virtual void InpushEnmityValues(HatVal &hatva);	
	
	/*怪物析构函数*/
	virtual ~MonsterBase(void);	
	
	/*获取仇恨范围内的玩家为vector*/
	void exchageHat(vector<string> &_herIdSet);
	
	/*怪物思考函数，此处为纯虚函数*/
	virtual void response(void) = 0;		
	
	/*复制怪物信息函数，此处为纯虚函数*/
	virtual MonsterBase* copyMon(char *_mapId) = 0;	
	
	/*使用技能*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*怪物死亡技能处理函数*/
	void delSki(void);
	
	/*测试打印Boss技能*/
	void testPrintSki(void);
	
	/*辅助生成技能id*/
	string asistSkiId(string &_skiId);
	
	/*攻击消息生成函数*/
	void formAttMsg(char *msg_others,int legnth,Hero *hitHero,int attack,int attFlg,int voidFlg);
	
	/*计算暴击率*/
	int coutFlgCrit(double &critTme);
	
	/*获得普通攻击值*/
	int countAttPerGen(Hero *perHero);
	
	/*计算闪避率*/
	int coutFlgVoid(Hero *perHero,double &hitPer);
	
	/*计算伤害值，技能也可以用*/
	int countAttVal(int genAtt,Hero *perHero,int &attTypFlg,int &voidFlg,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	
	/*攻击玩家函数*/
	void attPerHero(char *msg_others,int length,Hero *perHero,bool moveFlg = false,double skiHrtRatio = 0.0,double _cdTime = 1.0);
	
	/*攻击玩家是否可攻击判断函数*/
	bool judgeAtt(Hero *perHero);
	
	/*群攻攻击消息生成函数*/
	void skiAttHero(char *msg_others,int length,vector<string> &heroIds,char *skiId,double skiHrtRatio,double _cdTime);
	
	/*判断是否为Boss怪，是返回1，否则返回0*/	
	bool judgeBoss(void);
	
	/*被延时性技能攻击*/
	void inputHitTime(double _cdTimes,int _flgType = 0,int _dropBlood = 0,\
	char *_heroId = NULL,int _outAttVals = 0,int _inAttVals = 0,\
	int _outDefVals = 0,int _inDefVals = 0);
	
	/*被延时性技能攻击*/
	void inputHitTime(char *attId,int typeEffect,double lastTme,int value);
	
	/*被延时性技能攻击*/
	void hitedEffectBySki(SkillTime &_skiTme);
	
	/*调用被击覆盖类技能*/
	void callOneAtt(void);
	
	/*调用被非击覆盖类技能*/
	void callMoreAtt(SkillTime &_skiTme);
	
	/*调用所有非击覆盖类技能*/
	void dealMoreAtt(void);
	
	/*调用所有非击覆盖类技能*/
	void hitedSkiFun(void);
	
	/*调用被击覆盖类技能,点穴*/
	void callOneAttPt(void);
	
	/*调用被击覆盖类技能,眩晕*/
	void callOneAttDizz(void);
	
	/*持续掉血消息形成*/
	void formSelDropBldMsg(SkillTime &_skiTme,char *msg_other,int length);
	
	/*持续掉血消息形成*/
	void sendDropBldMsg(SkillTime &_skiTme,char *msg_other);
	
	/*持续掉血消息形成*/
	void formDropBldMsg(SkillTime &_skiTme,char *msg_other,int length);
	
	/*保存攻防总值*/
	void storeAttDef(void);
	
	/*调用攻防覆盖类技能*/
	void dealMoreAttDef(void);
	
	/*判断攻防是否达到上限,或者降到下限*/
	bool judgeAttDef(void);
	
	/*改变攻防总值*/
	void reduceAttDef(SkillTime &skiTme);
	
	/*还原攻防总值*/
	void recoverAttDef(SkillTime &skiTme);
	
	/*判断韧性是否达到上限,或者降到下限*/
	bool judgeAttTen(void);
	
	/*减韧性*/
	void reduceAttTen(SkillTime &newSkiTime);
	
	/*恢复韧性*/
	void recoverAttTen(SkillTime &newSkiTime);
	
	/*调用击覆盖类技能,降低韧性*/
	void dealMoreAttTen(void);
	
	/*减命中*/
	void reduceAttHit(SkillTime &newSkiTime);
	
	/*恢复命中*/
	void recoverAttHit(SkillTime &newSkiTime);
	
	/*判断韧性是否达到上限,或者降到下限*/
	bool judgeAttHit(void);
	
	/*调用击覆盖类技能,降低韧性*/
	void dealMoreAttHit(void);
	
	/*设置无敌状态*/
	void setUnEnemySta(bool _unEnemySta);
	
	/*设置无敌状态*/
	bool getUnEnemySta(void);
	
	/*获得等级*/
	int getRank(void);
	
	/*重置攻防值*/
	void initRecAttDef(void);
	
	/*重置怪物所受延时性技能影响*/
	void initHitedSki(void);
	
	/*重置标记值*/
	void initFlgVal(void);
	
	/*处理宠物的仇恨列表容器，如果为真，则插入，否则则删除*/
	void dealPetLst(bool _flg);
	
	/*处理宠物的仇恨列表容器，全删除*/
	void dealPerByEmy(void);
	
	/*判断次数够否*/
	bool dealLveCtn(void);
	
	/*判断时间够否*/
	bool dealDurTme(void);
	
	/*判断追击的玩家是否移动,移动则返回真*/
	bool jdgSmePt(Point heroPt);
	
	/*下线消息*/
	void formOutMsg(void);
	
	/*获得下线消息*/
	char* getOutMsg(void);
	
	/*获得怪物存活管理器*/
	LveCtnManger getLveMag(void);
	
	/*获得怪物经验倍数*/
	int getExpTme(void);
	
	/*获得怪物金钱倍数*/
	int getMonyTme(void);
	
	/*获取五行属性*/
	FiveElem *getFiveElem();
	
	/*生成移动固定头文件*/
	void getMovHeadMsg(string &moveMsg);
	
	/*怪物类型的用int型表示*/
	void kindIntInit(void);

	
	/*巡逻怪走动频率（随机和概率同时进行判断）*/
	bool judgeGoFor(void);
	
	/*把forGo全部进行对10取余数处理*/
	void dealGoFor(void);
	
	/*重置怪物属性*/
	void initMonVal(void);
	
	/*测试怪物存活属性*/
	int testLveManger(void);
	
	/*获得自卫反应标记值*/
	bool getRepFlg(void);
	
	/*修改自卫反应标记值*/
	void setRepFlg(bool _repFlg);	
	
	/*初始化追踪点坐标*/
	void initPersuitPt(void);
	
	/*刷怪函数*/
	void outScence(void);
	
	/*怪物自身复活*/
	void reLife(void);
	
	/*重置怪物部分属性*/
	void initMonsterBaseAsist(void);
	
	/*重置整个怪物数据*/
	virtual void initMonsterALL(void);
	
	/*定时发送下线消息*/
	void sendOutMsg(void);
	
	/*把寻路寻到的逻辑点转换成像素点*/
	void exchgeWayRod(void);
	
	/* 虚函数，塔防怪从客户端消失 */
	virtual void disappear();
	
	/* 虚函数，使塔防怪静止不动 */
	virtual void StandStill();
	
	
	/*根据人物初始化怪物属性*/
	virtual void initOnwer(Hero *owner);
	
	/*怪物析构时，释放技能实例*/
	void deleteSkillInst(void);
	
	/*判断动画是否播放完*/
	bool isPlayOver();
	
	/*路径平滑处理*/
	void smoothRoadPt(void);
	
	/*获得掉落阶段*/
	char *getStage(void);
	
	/*怪物回血功能*/
	void recoverBloodSelf(void);
	
	/*路径平滑处理,调用地图里面的一个函数*/
	void smoothRoadPtSelf(void);
	
	/*计算暴击率<后面更改的公式20130110*/
	int coutFlgCrit(Hero *perHero,double &critTme);
	
	/*回血条件判断*/
	bool isRecoverBlood(void);
	
	/*获得回血计时器标记值*/
	bool getIsBloodTmeOpenFlg(void);
	
	/*设置回血计时器标记值*/
	void setIsBloodTmeOpenFlg(bool _isBloodTmeOpenFlg);
	
	/*怪物自卫攻击时缩短思考时间*/
	void initResponseAgain(void);
	
	/*怪物复原位置判断*/
	bool reBack(void);
	
	/*获得帮派，阵营属性*/
	char* getOwnerAttri(void);
	
	/*修改帮派，阵营属性*/
	void setOwnerAttri(char *_ownerAttri);
	
	/*获得怪物帮派，阵营类型*/
	int getOwnerAttriType(void);
	
	/*修改怪物帮派，阵营类型*/
	void setOwnerAttriType(int _ownerType);
	
	/*阵营怪的变换*/
	void exchgeCampAttriType(int _ownerType);	
	
	/*判断是否命中*/
	int ctnHitRatio(int hitVoid);
	
	/*判断是否命中*/
	int ctnCritRatio(Hero *hitPerson);
	
	/*任务怪，追加此任务的玩家信息*/
	bool appendTaskInfo(Hero *hero);
	
	/*任务怪里面（判断此怪是否被刷出）*/
	bool getIsUsed(void);
	
	/*任务怪存活时间到*/
	void taskMonCalBack(void);
	
	/*判断任务怪的主人是否还在*/
	bool judgeTask(void);
	
	/*召唤陷阱*/
	void callTrap(const vector<string> &herId);
	
	/*设置召唤怪标志值*/
	void setIsCallType(bool _isCallType);
	
	/*获得召唤标记值*/
	bool getIsCallType(void);
	
	/*设置召唤怪召唤出来的标志值*/
	void setIsCalled(bool _isCalled);
	
	/*获得召唤怪召唤出来的标志值*/
	bool getIsCalled(void);
	
	/*设置cd冷却标记值*/
	void setIsCdCool(bool _isCdCool);
	
	/*召唤怪*/
	void callMon(void);
	
	void setCallBoss(MonsterBase* _callBoss);
	
	private:
	
	double getLength(Point heroPt);
	
	void sortByPt(void);	
	
	//判断召唤怪的boss是否已死掉，真为死掉
	bool isCallBossLife(void)  ;
};
#endif
