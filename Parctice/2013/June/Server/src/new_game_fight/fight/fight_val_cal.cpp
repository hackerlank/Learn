#include "hero_fight.h"
#include "five_asist.h"
bool is_hited_judge(Hero *atker, unsigned obj_flag, void *obj, float &hitTimes, bool forbidDodge)
{
	if (forbidDodge || obj_flag == 3 || obj_flag == 4)
	{
		hitTimes = 1.0f;
		return true;
	}
	unsigned atkHit = atker->getHited();
	unsigned atkedDodge = 0;
	if (obj_flag == 1)
	{
		atkedDodge = ((Hero*)obj)->getDodge();
	} else if (obj_flag == 2) {
		atkedDodge = ((MonsterBase*)obj)->getVoids();
	}
	
	// bool isHited = false;
	bool isHited = isTouchHit(atkHit, atkedDodge);
	hitTimes = 1.0f;
	// int ret;
	
	// ret = dodge_cal(atkHit, atkedDodge, isHited, hitTimes);
	// if (ret != 0)
	// {
		// cout<<"check the hero's attr is error when the two hero are fighting"<<endl;
		// return false;
	// }
	
	return isHited;
}

#if 1
int attack_hero_cal(Hero* atker, Hero* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit)
{
	unsigned atkCrit = atker->getCrit();
	unsigned atkedTenacity = atked->getTenacity();
	
	float critTimes = 1.0f;
	isCrit = isTouchCrit(atkCrit, atkedTenacity);
	if (isCrit)
	{
		critTimes = fightConst.critTimes;
	}
	
	float hurtFactor = p_skill->getFactor(level);
	
	int attkType = p_skill->getAttkType();
	
	unsigned attk = 0, defense = 0;
	if (attkType == 0)
	{
		attk = atker->getOutAttack();
		defense = atked->getOutDefense();
	} else {
		attk = atker->getInAttack();
		defense = atked->getInDefense();
	}
	
	int heroLevel = atked->getLevel();
	float totalHurt = attk * (1 - defense / (heroLevel * fightConst.defFactor + defense)) * fightConst.attkFactor * hurtFactor;
	
	//加上五行伤害
	// FiveElem* attackFiveElem = atker->getFiveElem();
	// FiveElem* hitedFiveElem = atked->getFiveElem();
	// int fiveHurt = getFiveElemHurt(attackFiveElem, hitedFiveElem);
	
	// totalHurt = (totalHurt + fiveHurt) * critTimes;
	totalHurt = totalHurt * critTimes;
	return totalHurt;
}

#else

int attack_hero_cal(Hero* atker, Hero* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit)
{
	unsigned atkCrit = atker->getCrit();
	unsigned atkedTenacity = atked->getTenacity();
	
	float critTimes = 1.0f;
	int ret = crit_cal(atkCrit, atkedTenacity, isCrit, critTimes);
	if (ret != 0)
	{
		cout<<"check the hero's attr is error when the two hero are fighting"<<endl;
		return 0;
	}
	float hurtFactor = GET_HERO_SKILL_FACTOR(p_skill, level);
	
	unsigned outhurt = atker->getOutHurt();				//外功伤害
	unsigned inhurt = atker->getInHurt();				//内功伤害
	unsigned outattack = atker->getOutAttack();			//外功攻击
	unsigned inattack = atker->getInAttack();			//内功攻击
	
	unsigned outdefense = atked->getOutDefense();		//外功防御
	unsigned indefense  = atked->getInDefense();			//内功防御
	
	float hurtOut = BASIC_HURT_CAL(outattack, outhurt, outdefense);
	float hurtIn = BASIC_HURT_CAL(inattack, inhurt, indefense);
	float totalHurt = (hurtOut + hurtIn) * hurtFactor * hitTimes;
	
	//加上五行伤害
	FiveElem* attackFiveElem = atker->getFiveElem();
	FiveElem* hitedFiveElem = atked->getFiveElem();
	int fiveHurt = getFiveElemHurt(attackFiveElem, hitedFiveElem);
	
	totalHurt = (totalHurt + fiveHurt) * critTimes;
	return totalHurt;
}

#endif

#if 1
int attack_monster_cal(Hero* atker, MonsterBase* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit)
{
	unsigned atkCrit = atker->getCrit();
	unsigned atkedTenacity = atked->getTenty();
	
	float critTimes = 1.0f;
	isCrit = isTouchCrit(atkCrit, atkedTenacity);
	if (isCrit)
	{
		critTimes = fightConst.critTimes;
	}
	
	float hurtFactor = p_skill->getFactor(level);
	
	int attkType = p_skill->getAttkType();
	
	unsigned attk = 0, defense = 0;
	if (attkType == 0)
	{
		attk = atker->getOutAttack();
		defense = atked->getOutDefVal();
	} else {
		attk = atker->getInAttack();
		defense = atked->getInDefVal();
	}
	
	int heroLevel = atked->getRank();
	float totalHurt = attk * (1 - defense / (heroLevel * fightConst.defFactor + defense)) * fightConst.attkFactor * hurtFactor;
	
	//加上五行伤害
	// FiveElem* attackFiveElem = atker->getFiveElem();
	// FiveElem* hitedFiveElem = atked->getFiveElem();
	// int fiveHurt = getFiveElemHurt(attackFiveElem, hitedFiveElem);
	
	totalHurt = totalHurt * critTimes;
	// totalHurt = (totalHurt + fiveHurt) * critTimes;
	return totalHurt;
}
#else

int attack_monster_cal(Hero* atker, MonsterBase* atked, float hitTimes,
	HeroSkill *p_skill, unsigned level, bool &isCrit)
{
	unsigned atkCrit = atker->getCrit();
	unsigned atkedTenacity = atked->getTenty();
	if (atkedTenacity > MAX_HERO_TENACITY_VALUE)
	{
		cout<<"The monster's tenacity is "<<atked->getTenty()<<endl;
		atkedTenacity  = 0;					//临时这样使用，等真哥检查怪物韧性为什么是负值
	}
	float critTimes = 1.0f;
	int ret = crit_cal(atkCrit, atkedTenacity, isCrit, critTimes);
	if (ret != 0)
	{
		cout<<"check the hero's or the monster's attr is error when the two are fighting"<<endl;
		return 0;
	}
	
	char hurtMsg[400] = {0};
	
	float hurtFactor = GET_HERO_SKILL_FACTOR(p_skill, level);
	// sprintf(hurtMsg, "50,1,skill %s's partyFactor is %f and factor is %f hurtFactor is %f and level is %d", p_skill->getId(),  p_skill->getPartyFactor(), p_skill->getFactor(level), hurtFactor, level);
	// send_msg(atker->getFd(), hurtMsg);
	unsigned outhurt = atker->getOutHurt();				//外功伤害
	unsigned inhurt = atker->getInHurt();				//内功伤害
	unsigned outattack = atker->getOutAttack();			//外功攻击
	unsigned inattack = atker->getInAttack();			//内功攻击
	
	unsigned outdefense = atked->getOutDefVal();			//外功防御
	unsigned indefense  = atked->getInDefVal();			//内功防御
	
	float hurtOut = BASIC_HURT_CAL(outattack, outhurt, outdefense);
	float hurtIn = BASIC_HURT_CAL(inattack, inhurt, indefense);
	float totalHurt = (hurtOut + hurtIn) * hurtFactor * hitTimes;
	
	//加上五行伤害
	FiveElem* attackFiveElem = atker->getFiveElem();
	FiveElem* hitedFiveElem = atked->getFiveElem();
	int fiveHurt = getFiveElemHurt(attackFiveElem, hitedFiveElem);
	
	totalHurt = (totalHurt + fiveHurt) * critTimes;
	return totalHurt;
}

#endif

#if 0
//医疗回复值计算
unsigned cure_life_cal(Hero *hero, HeroSkill *p_skill, unsigned skillLevel)
{
	if (strcmp(hero->getParty(), "G") != 0)
	{
		return 0;
	}
	unsigned inhurt = hero->getInHurt();				//内功伤害
	float skillFactor = p_skill->getFactor(skillLevel);
	float partyFactor = p_skill->getPartyFactor();
	unsigned cure_val = 2 * inhurt * (skillFactor + partyFactor);
	return cure_val;
}

#else

//医疗回复值计算
unsigned cure_life_cal(Hero *hero, HeroSkill *p_skill, unsigned skillLevel)
{
	if (strcmp(hero->getParty(), "G") != 0)
	{
		return 0;
	}
	
	unsigned cure_val = p_skill->getValue(skillLevel);
	return cure_val;
}
#endif

void decHurtBuffDeal(Hero* atked, int &lifeHurt, int &reflectHurt)
{
	reflectHurt = 0;
	if (atked->skillBuffState & BUFF_REFLEX_STATE)
	{
		reflectHurt = REFLECT_HURT_CAL(atked, lifeHurt);
		lifeHurt -= reflectHurt;
	}
	
	if (atked->skillBuffState & BUFF_MAGIC_SHIELD_STATE)
	{
		int decHurt = atked->skillBuff[atked->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal;
		if (lifeHurt >= decHurt)
		{
			lifeHurt -= decHurt;
			atked->skillBuff[atked->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal = 0;
			int index = atked->getIndexByState(BUFF_MAGIC_SHIELD_STATE);
			atked->stop_buff_debuff_by_index(index);
		} else {
			lifeHurt = 0;
			atked->skillBuff[atked->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal -= lifeHurt;
		}
		
	}
}