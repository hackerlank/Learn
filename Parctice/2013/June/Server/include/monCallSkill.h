/************************************************************
	文件名：monCallSkill.h
	文件作用：定义MonCallSkill（召唤技能）类的属性和成员
	作者：chenzhen
	创建日期：2013.05.09
************************************************************/
#ifndef MON_CALL_SKILL_H
#define MON_CALL_SKILL_H
#include"skillBase.h"
#include"monsterBase.h"
class MonCallSkill : public SkillBase
{
	double trigPer;          //额外触发条件（血量降到某一百分比）
	int typeFlg;             //召唤类型，1：只召唤陷阱 2：只召唤怪 3：召唤陷阱和怪
public:
	MonCallSkill(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _trigPer);
				
	/*判断生命值是否已经达到额外触发条件*/
	bool judgeLifePer(void);
	
	/*拷贝技能实例*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*使用技能*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*析构函数*/
	~MonCallSkill(void);
	
	/*宿主死亡时调用*/
	void ownerDie(void);
	
	//解析召唤类型
	void getCallType(void);
	
	private:
	
	//召唤
	void UseSkillAsist(const vector<string> &herId);
	
	
};
#endif

		