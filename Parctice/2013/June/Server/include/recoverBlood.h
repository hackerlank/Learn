/************************************************************
	文件名：recoverBlood.h
	文件作用：定义recoverBlood（Boss回血技能）类的属性和成员
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#ifndef RECOVER_SBLOOD_H
#define RECOVER_SBLOOD_H
#include"skillBase.h"
#include"monsterBase.h"
class RecoverBlood : public SkillBase
{
	double recoverPer;        //回血百分比
	double trigPer;          //额外触发条件（血量降到某一百分比）
	bool useSkillFlg;           //是否已用这个技能，真表示是（此技能只能用一次）
public:
	RecoverBlood(char *_name,char *_id,int _rank,double _relPer,\
	double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
	bool _lastSki,double _trigPer,double _recoverPer);
				
	/*判断生命值是否已经达到额外触发条件*/
	bool judgeLifePer(void);
	
	/*回血功能*/
	bool gainBlood(int &bloodChg);
	
	/*拷贝技能实例*/
	SkillBase* copySkillInst(MonsterBase *_owner);
	
	/*使用技能*/
	bool useSkill(vector<string> &herId,bool _station = false);
	
	/*生成消息*/
	void formMsg(char *msg_others,int lengStr,int bloodChg,char *_heroId = NULL);
	
	/*析构函数*/
	~RecoverBlood(void);
	
	/*宿主死亡时调用*/
	void ownerDie(void);
};
#endif

		