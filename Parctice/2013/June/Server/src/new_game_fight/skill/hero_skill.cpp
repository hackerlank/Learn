#include "hero_skill.h"

HeroSkill::HeroSkill(HeroSkill_T &skillData)
{
	strncpy(skillId, skillData.skillId, sizeof(skillId));
	type = skillData.type;
	buffType = skillData.buffType;
	attackRange = skillData.attackRange;
	hurtRange = skillData.hurtRange;
	animationTime = skillData.animationTime;
	partyFactor = skillData.partyFactor;
	memcpy(upgradeNeedHeroLevel, skillData.upgradeNeedHeroLevel, sizeof(upgradeNeedHeroLevel));
	memcpy(upgradeNeedMoney, skillData.upgradeNeedMoney, sizeof(upgradeNeedMoney));
	memcpy(upgradeNeedExp, skillData.upgradeNeedExp, sizeof(upgradeNeedExp));
	memcpy(cdTime, skillData.cdTime, sizeof(cdTime));
	memcpy(needMagic, skillData.needMagic, sizeof(needMagic));
	memcpy(value, skillData.value, sizeof(value));
	memcpy(totalVal, skillData.totalVal, sizeof(totalVal));
	memcpy(factor, skillData.factor, sizeof(factor));
	memcpy(attkNum, skillData.attkNum, sizeof (attkNum));
	attkType = skillData.attkType;
}


//技能基本属性
char* HeroSkill::getId()
{
	return skillId;
}
unsigned HeroSkill::getType()
{
	return type;
}
unsigned HeroSkill::getBuffType()
{
	return buffType;
}

unsigned HeroSkill::getAttkType()
{
	return attkType;
}

//技能效果属性
unsigned HeroSkill::getAttackRange()
{
	return attackRange;
}
unsigned HeroSkill::getHurtRange()
{
	return hurtRange;
}
float HeroSkill::getAnimationTime()
{
	return animationTime;
}
float HeroSkill::getPartyFactor()
{
	return partyFactor;
}
unsigned HeroSkill::getCdTime(unsigned level)
{
	//当前等级对应的，传入的level参数要不小于1
	return cdTime[level - 1];
}
unsigned HeroSkill::getNeedMagic(unsigned level)
{
	return needMagic[level - 1];
}
unsigned HeroSkill::getValue(unsigned level)
{
	return value[level - 1];
}
unsigned HeroSkill::getTotalVal(unsigned level)
{
	return totalVal[level - 1];
}
float HeroSkill::getFactor(unsigned level)
{
	return factor[level - 1];
}

unsigned HeroSkill::getAttkNum(unsigned level)
{
	return attkNum[level - 1];
}
	
//技能升级属性
unsigned HeroSkill::getUpgradeNeedHeroLevel(unsigned level)
{
	//升到下一级所需，level不能大于19
	return upgradeNeedHeroLevel[level];
}
unsigned HeroSkill::getUpgradeNeedMoney(unsigned level)
{
	return upgradeNeedMoney[level];
}
unsigned HeroSkill::getUpgradeNeedExp(unsigned level)
{
	return upgradeNeedExp[level];
}