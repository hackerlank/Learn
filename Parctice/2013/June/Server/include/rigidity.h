/************************************************************
	文件名：rigidity.h
	文件作用：定义Rigidity（Boss定身技能）类的属性和成员
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#ifndef RIGIDITY_H
#define RIGIDITY_H
#include<set>
#include"data_structure_struct.h"
#include"skillBase.h"
#include"libev.h"
class Rigidity : public SkillBase
{
	ev_timer think_timer;    //计时器
	ManMonSkiTme skiTme;
	double lastTime;        //持续时间
	double trigPer;          //额外触发条件（血量降到某一百分比）
	bool flgThk;            //计时器是否暂停
public:
	Rigidity(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,\
	double _hrtRatio,bool _lastSki,double _trigPer,\
	double _lastTime);
				
	/*判断生命值是否已经达到额外触发条件*/
	bool judgeLifePer(void);
	
	/*定身功能*/
	bool standStill(vector<string> &heroId);
	
	/*拷贝技能实例*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*计时器初始化函数*/
	void initTimer(void); 
	
	/*暂停思考*/
	void stopThk(void);	
	
	/*插入那些中技能人物id*/
	void insertHerId(vector<string> &heroId);
	
	/*在思考函数里面调用*/
	bool response(void);
	
	/*获得伤害持续时间*/
	double getLastTme(void);
	
	/*使用技能*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*形成消息*/
	void formMsg(char *msg_others,int lengthStr,char *_heroId = NULL);
	
	/*技能持续时间到，则清掉玩家id*/
	bool delHerId(void);
	
	/*析构函数*/
	~Rigidity(void);
	
	/*设置被定身玩家定时标记值属性*/
	bool setHerStiFlg(string &heroId,bool _flg);
	
	/*获得定身类型*/
	int getStillType(char *_skillId);
	
	/*宿主死亡时调用*/
	void ownerDie(void);
};
#endif

		