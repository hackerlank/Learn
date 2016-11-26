#include "hero_fight.h"

/*******************************************************
 * crit_cal -- 暴击计算
 * @atkCrit:	攻击者暴击值
 * @tenacity:	被攻击者韧性
 * @isCrit:		是否触发暴击
 * @critTimes:	暴击倍数
 * Return:	计算失败原因
 *******************************************************/
int crit_cal(unsigned &atkCrit, unsigned &tenacity, bool &isCrit, float &critTimes)
{
	//攻击者暴击值非法
	if (atkCrit > MAX_HERO_CRIT_VALUE)
	{
		cout<<"the attacker hero's crit value is error! max value is "<<MAX_HERO_CRIT_VALUE<<" and his is "<<atkCrit<<endl;
		return 1;
	}
	
	//被攻击者韧性值非法
	if (tenacity > MAX_HERO_TENACITY_VALUE)
	{
		cout<<"the attacked hero's tenacity value is error! max value is "<<MAX_HERO_TENACITY_VALUE<<" and his is "<<tenacity<<endl;
		return 2;
	}
	
	//计算暴击率及暴击倍数
	float critFactor = 0.0f;
	if (atkCrit <= tenacity)
	{
		critFactor = 0.1f;
		critTimes = 1.1f;
	} else {
		critFactor = 0.1 + 0.9 * ((atkCrit - tenacity) * 0.002 / ( 1 + (atkCrit - tenacity) * 0.002));
		critTimes = 1.1 + 0.002 * (atkCrit - tenacity);
	}
	
	//边界值
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned(critFactor * 10000);
	
	//是否暴击
	if (rank < boundary)
	{
		isCrit = true;
	} else {
		isCrit = false;
		critTimes = 1.0f;
	}
	return 0;
}

/*******************************************************
 * dodge_cal -- 暴击计算
 * @atkHit:		攻击者命中值
 * @batkdDodge:	被攻击者闪避
 * @isHited:	是否触发命中
 * @hitFactor:	命中伤害倍数
 * Return:		计算失败原因
 *******************************************************/
int dodge_cal(unsigned &atkHit, unsigned &batkdDodge, bool &isHited, float &hitTimes)
{
	//攻击者命中值非法
	if (atkHit > MAX_HERO_HIT_VALUE)
	{
		cout<<"the attacker hero's hit value is error! max value is "<<MAX_HERO_HIT_VALUE<<" and his is "<<atkHit<<endl;
		return 1;
	}
	
	//被攻击者闪避值非法
	if (batkdDodge > MAX_HERO_DODGE_VALUE)
	{
		cout<<"the attacked hero's dodge value is error! max value is "<<MAX_HERO_DODGE_VALUE<<" and his is "<<batkdDodge<<endl;
		return 2;
	}
	
	//计算闪避率及命中伤害倍数
	float dodgeFactor = 0.0f;
	if (atkHit > batkdDodge)
	{
		// dodgeFactor = 0.05f;
		// hitTimes = 1.0 + 0.0002 * (atkHit + 500 - batkdDodge);
		dodgeFactor = 0.05 * (1 - 0.02 * (atkHit - batkdDodge)) / (1 + 0.02 * (atkHit - batkdDodge));
		hitTimes = 1.0f;
	} else {
		dodgeFactor = 0.05 + 0.95 * ((batkdDodge - atkHit) * 0.002 / ( 1 + (batkdDodge - atkHit) * 0.002));
		hitTimes = 1.0f;
	}
	
	//边界值
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned((1 - dodgeFactor) * 10000);
	
	//是否命中
	if (rank < boundary)
	{
		isHited = true;
	} else {
		isHited = false;
	}
	return 0;
}

bool isTouchHit(int hitA, int dodgeB)
{
	float factor = (hitA * fightConst.hitFactor) / (hitA * fightConst.hitFactor + dodgeB);
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned (factor * 10000);
	if (rank < boundary)
	{
		return true;
	} else {
		return false;
	}
}

//暴击系数 =（15+A暴击/K）*（100-（5+B韧性/K））/10000
bool isTouchCrit(int critA, int tencB)
{
	float factor = (fightConst.critBase + critA / fightConst.critFactor) * (fightConst.tencMax - (fightConst.tencBase + tencB / fightConst.tencFactor)) / fightConst.critDivisor;
	
	unsigned rank = rand() % 10000;
	unsigned boundary = unsigned (factor * 10000);
	if (rank < boundary)
	{
		return true;
	} else {
		return false;
	}
}