#ifndef _HERO_FIGHT_H_
#define _HERO_FIGHT_H_

#include"hero.h"
#include"math.h"
#include"bottle.h"
#include"wagon.h"

#define MAX_HERO_CRIT_VALUE		20000000	//玩家最大暴击值
#define MAX_HERO_TENACITY_VALUE	20000000	//玩家最大韧性值
#define MAX_HERO_HIT_VALUE		20000000	//玩家最大命中值
#define MAX_HERO_DODGE_VALUE	20000000	//玩家最大闪避值

#define PEACE_MODE				1
#define ALL_WAR_MODE			2
#define CAMP_WAR_MODE			3
#define GUILD_WAR_MODE			4

//基本攻击计算
#define BASIC_HURT_CAL(atkA, hurtA, defB)	(2 * (atkA) * (hurtA) / ((hurtA) + (defB)))
#define REFLECT_HURT_CAL(hero, hurt) ((hurt) *	\
((hero)->skillBuff[hero->getIndexByState(BUFF_REFLEX_STATE)].totalVal) / 1000)

#define GET_HERO_SKILL_FACTOR(p_skill, level) (p_skill->getPartyFactor() * p_skill->getAnimationTime()\
	+ p_skill->getFactor(level))

#define GET_DISTANCE_SQR(ptA, ptB)	(((ptA)._x - (ptB)._x) * ((ptA)._x - (ptB)._x)\
									+ ((ptA)._y - (ptB)._y) * ((ptA)._y - (ptB)._y))
#define GET_DISTANCE(ptA, ptB)	sqrt(GET_DISTANCE_SQR(ptA, ptB))
		
#define IS_OUT_RANGE(ptA, ptB, dist)	((dist) < (GET_DISTANCE(ptA, ptB)))

#define JUDGE_WILL_LIFE(obj, hurt)	((obj->getLifeVal() <= hurt) ? 0 : (obj->getLifeVal() - hurt))

typedef struct FightConst_S
{
	float attkFactor;
	float defFactor;
	float hitFactor;
	float critFactor;
	float tencFactor;
	float critBase;
	float tencBase;
	float tencMax;
	float critDivisor;
	float critTimes;
}FightConst_T;

extern FightConst_T fightConst;

//basic_cal
//暴击计算
int crit_cal(unsigned &atkCrit, unsigned &tenacity, bool &isCrit, float &critTimes);
//闪避计算
int dodge_cal(unsigned &atkHit, unsigned &batkdDodge, bool &isHited, float &hitTimes);
//是否暴击
bool isTouchCrit(int critA, int tencB);
//是否命中
bool isTouchHit(int hitA, int dodgeB);

//fight_val_cal
//是否闪避
bool is_hited_judge(Hero *atker, unsigned obj_flag, void *obj, float &hitTimes, bool forbidDodge);
//角色受击计算
int attack_hero_cal(Hero* atker, Hero* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit);
//怪物受击计算
int attack_monster_cal(Hero* atker, MonsterBase* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit);
//医疗回复值计算
unsigned cure_life_cal(Hero *hero, HeroSkill *p_skill, unsigned skillLevel);
//减伤处理
void decHurtBuffDeal(Hero* atked, int &lifeHurt, int &reflectHurt);

//proc_lose_life
//玩家扣血统一处理
void proc_hero_lose_life(Hero* atker, Hero* hero, unsigned lifeHurt);
//怪物扣血统一处理
void proc_mon_lose_life(Hero *atker, MonsterBase* mon, unsigned lifeHurt);
//马车扣血统一处理
void proc_wagon_lose_life(Hero* atker, Wagon* wagon, int lifeHurt);
//瓶子扣血统一处理
void proc_bottle_lose_life(Hero* atker, Bottle* bottInst, int lifeHurt);

//hero_skill_deal
//普通单体指向性技能
void single_aimed_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void* obj, char *objId, float animationTime);
//单体指向技能之冲锋
void single_aimed_rush_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, char *objId, float animationTime);
//群体技能 flag = true:群体指向性技能；flag = false:无指向性
void many_hurt_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, bool flag, float animationTime);
//单体医疗技能
void single_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime);
//群体医疗技能
void many_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime);

//proc_use_skill
//敌友判断
int relationCheck(Hero *heroA, Hero* heroB, Map_Inform* map);
//使用技能处理
int proc_use_skill(Hero* owner, char *skillId, char *objId, int &remainCD);
//以人物为中心，发送九宫格消息
void send_nine_msg(Hero *hero, char* msg);

//use_skill_comm
//使用技能通信
void use_skill_comm(char *buffer);
#endif