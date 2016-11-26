#ifndef UNENMITY_H
#define UNENMITY_H
#include"skillBase.h"
#include"libev.h"
class UnEnemy : public SkillBase 
{
	double lastTime;          //持续时间
	
	ev_timer think_timer;    //计时器
	
public:
	UnEnemy(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _lastTime);
	
	
	/*生成技能使用后所发消息*/
	void formMsg(char *msg_others,int lengStr,char *_heroId = NULL);
	
	/*使用技能*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*无敌持续时间处理*/
	void recoverUnEnemySki(void);
	
	/*拷贝技能实例*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*计时器初始化函数*/
	void initTimer(void);
	
	/*计时器暂停函数*/
	void stopThk(void);
	
	/*宿主死亡时调用*/
	void ownerDie(void);

	/*析构函数*/
	~UnEnemy(void);
};
#endif