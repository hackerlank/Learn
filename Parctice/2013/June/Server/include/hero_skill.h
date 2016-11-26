/****************************************************************
 * Filename: hero_skill.h
 * 
 * Description: 人物技能
 *
 * Original Author : bison, 2012-11-14
 *
 ****************************************************************/
#ifndef _HERO_SKILL_H_
#define _HERO_SKILL_H_

#include<iostream>
#include"my_timer.h"
using namespace std;

#define HERO_SKILL_MAX_NUM					14		//人物最大技能数
#define HERO_SKILL_TOP_LEVEL				20		//角色技能最大等级

//被动技能Type 	0:被动加生命；1:被动加魔法上限；2:被动加外功防御；3:被动加内功防御
//				4:被动加外功攻击；5:被动加内功攻击；6:被动加命中；7：被动加闪避；
//				8:被动加韧性；9:被动加暴击；10:被动加外功伤害；11:被动加内功伤害
#define HERO_SKILL_MIN_STATIC_TYPE			0		//角色被动技能类型值范围下限
#define HERO_SKILL_MAX_STATIC_TYPE			11		//角色被动技能类型值范围上限
#define HERO_SKILL_NORMAL_TYPE				100		//普通攻击
#define HERO_SKILL_SINGLE_HURT_TYPE			101		//单体主动攻击技能
#define	HERO_SKILL_RUSH_TYPE				102		//冲锋技能
#define HERO_SKILL_BUFF_TYPE				103		//英雄buff类技能
#define HERO_SKILL_SINGLE_TREAT_TYPE		104		//单体医疗
#define HERO_SKILL_MANY_HURT_NO_AIM_TYPE 	105		//群攻非指向
#define	HERO_SKILL_MANY_HURT_WITH_AIM_TYPE	106		//群攻有指向
#define HERO_SKILL_MANY_TREAT_TYPE			107		//群体医疗
#define HERO_SKILL_MIN_DYNAMIC_TYPE			100		//主动技能类型值范围下限
#define HERO_SKILL_MAX_DYNAMIC_TYPE			107		//主动技能类型值范围上限

typedef struct HeroMemSkill_S
{
	char skillId[10];
	unsigned level;
	unsigned lastUsedTime;
} HeroMemSkill_T;
extern HeroMemSkill_T M_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T H_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T G_SkillBase[HERO_SKILL_MAX_NUM];
extern HeroMemSkill_T X_SkillBase[HERO_SKILL_MAX_NUM];

typedef struct HeroSkill_S
{
	char skillId[10];					//技能ID
	unsigned type;						//技能类型
	unsigned buffType;					//技能附带buff类型
	unsigned attackRange;				//攻击范围
	unsigned hurtRange;					//伤害范围
	float	 animationTime;				//动画时间
	float	 partyFactor;				//门派伤害系数
	unsigned upgradeNeedHeroLevel[20];	//升级需要的角色等级
	unsigned upgradeNeedMoney[20];		//升级需要金钱
	unsigned upgradeNeedExp[20];		//升级需要经验
	unsigned cdTime[20];				//CD时间
	unsigned needMagic[20];				//释放技能消耗魔法
	unsigned value[20];					//技能数值
	unsigned totalVal[20];				//技能所加总值
	unsigned attkNum[20];				//技能攻击目标数
	float 	 factor[20];				//技能伤害/医疗系数
	unsigned attkType;					//攻击类型
} HeroSkill_T;

class HeroSkill
{
private:
	char skillId[10];					//技能ID
	unsigned type;						//技能类型
	unsigned buffType;					//技能附带buff类型
	unsigned attackRange;				//攻击范围
	unsigned hurtRange;					//伤害范围
	float	 animationTime;				//动画时间
	float	 partyFactor;				//门派伤害系数
	unsigned upgradeNeedHeroLevel[20];	//升级需要的角色等级
	unsigned upgradeNeedMoney[20];		//升级需要金钱
	unsigned upgradeNeedExp[20];		//升级需要经验
	unsigned cdTime[20];				//CD时间
	unsigned needMagic[20];				//释放技能消耗魔法
	unsigned value[20];					//技能数值
	unsigned totalVal[20];				//技能所加总值
	unsigned attkNum[20];				//技能攻击目标数
	float 	 factor[20];				//技能伤害/医疗系数
	unsigned attkType;					//攻击类型
public:
	HeroSkill(HeroSkill_T &skillData);
	
	//技能基本属性
	char *getId();
	unsigned getType();
	unsigned getBuffType();
	//技能效果属性
	unsigned getAttackRange();
	unsigned getHurtRange();
	float getAnimationTime();
	float getPartyFactor();
	unsigned getAttkType();
	
	unsigned getCdTime(unsigned level);
	unsigned getNeedMagic(unsigned level);
	unsigned getValue(unsigned level);
	unsigned getTotalVal(unsigned level);
	float getFactor(unsigned level);
	unsigned getAttkNum(unsigned level);
	//技能升级属性
	unsigned getUpgradeNeedHeroLevel(unsigned level);
	unsigned getUpgradeNeedMoney(unsigned level);
	unsigned getUpgradeNeedExp(unsigned level);
};
#endif