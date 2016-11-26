/************************************************************
	文件名：skillBase.h
	文件作用：定义SkillBase（Boss技能基类）类的属性和成员
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#ifndef SKILL_BASE_H
#define SKILL_BASE_H
#include<string>
#include<vector>
#include<time.h>
#include"wholeDefine.h"
#include"libev.h"
#include"bossSkiThk.h"
/*蛊惑之术的类型*/
#define DELUDE 1    
   
/*天罗地网的类型*/
#define TIGHT_ENCIRCLE 2   
 
/*神拳铁臂的类型*/
#define FIST 3          


/*此处是回发给客户端的消息宏，后面经整合后，会删掉*/
const int MONSTER_SKILL_HEAD  = 2;   //怪物技能头命令
const int MONSTER_SKILL_TYPE = 14;  //群攻命令
const int MONSTER_SKILL_SINGLE = 13;  //单体命令（只是定身）
const int MONSTER_SKILL_CHANGE_PRO = 15;  //单体瞬发改变属性
const int HIT_TYPE_HERO = 1;
const int HIT_TYPE_MONSTER = 0;
const int STAND_STILL_ID = 1;           //技能id（为了配合人物技能）类型
const int STAND_STILL_FUNCTION = 1;           //技能id（为了配合人物技能）类型

const int MONSTER_SKILL_RECOVER_BLOOD_ID  = 14; //回血命令
const int RECOVER_BLOOD_FUNCTION = 2;                  //回血类型

const int STAND_UNENEMY_FUNCTION = 13;          //无敌技能


class MonsterBase;
using namespace std;
class SkillBase
{
protected:	
	char name[SHOR_MID_VALUE_LENGTH + 1];              //技能名称
	char id[SHOR_MID_VALUE_LENGTH + 1];                //技能实例id 
	char typeId[SHOR_MID_VALUE_LENGTH + 1];            //技能类型id<发给客户端的技能id>
	int rank;                 //技能等级
	double relPer;        	 //释放频率
	double angVal;			 //触发技能怒气值
	double cdTime;           //cd时间
	MonsterBase *owner;      //此技能使用者的怪物
	double hrtRatio;         //技能伤害系数
	bool lastSki;     //技能是否为持续技能（true为持续时间技能，false为瞬发技能）	
	

	double playCd;           //技能播放时间

	ev_timer think_timer;    //计时器,控制播放时间，以及冷却时间
	
	bool isOverTme;          //播放，以及冷却时间都过聊,ture 表示，此技能已冷却且播放完
	
	
public:
	SkillBase(char *_name,char *_id,int _rank,double _relPer,double _angVal,\
	double _cdTime,double _playCd,double _hrtRatio,bool _lastSki);
	
	/*获得技能名称*/
	char* getName(void);
	
	/*获得技能id*/
	char* getId(void);
	
	/*获得技能id，调用getId方法*/
	char* getIdentity(void);
	
	/*获得技能使用等级*/
	int getRank(void);
	
	/*获得技能触发频率*/
	double getRelPer(void);
	
	/*获得技能触发所需怒气值*/
	double getAngVal(void);
	
	/*获得技能cd时间*/
	double getCdTme(void);
	
	/*判断技能触发频率是否满足*/
	bool judgeRelPer(void);
	
	/*判断技能触发怒气值是否满足*/
	bool judgeAngVal(void);
	
	/*初始化此技能宿主*/
	void initOwner(MonsterBase *monster);
	
	/*获得此技能宿主*/
	MonsterBase* getOwner(void);
	
	/*判断此技能是否为可持续*/
	bool getLastSki(void);
	
	/*宿主死亡时调用*/
	virtual void ownerDie(void);
	
	/*拷贝技能实例*/
	virtual SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*使用技能*/
	virtual bool useSkill(vector<string> &herId,bool _station = false);
	
	/*发送技能使用后消息（单发）*/
	void sendOneMsg(char *_heroId,char *msg_others);
	
	/*发送技能使用后消息（群发）*/
	void sendMsgNineBox(char *msg_others);
	
	/*析构函数，必须为虚函数*/
	virtual ~SkillBase(void);
	
	/*获得技能伤害系数*/
	double getHrtRatio(void);
	
	/*初始化技能类型id*/
	void initTypeId(void);
	
	/*获得技能冷却时间和cd时间是否已过*/
	bool getIsOverTme(void);
	
	/*设置技能冷却时间和cd时间是否已过*/
	void setIsOverTme(bool _isOver);	
	
	/*启动技能cd和播放cd计时器*/
	void initCdAndPlayTmer(void);
	
	/*暂停计时器*/
	void stopTme(void);
};
#endif
	
	