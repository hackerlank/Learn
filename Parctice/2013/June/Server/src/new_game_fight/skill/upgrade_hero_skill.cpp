#include "hero.h"
#include "money_operator.h"
#define	UPGRADE_SKILL_SUCCESS					0	//升级技能成功
#define UPGRADE_SKILL_FAILED_ERROR_SKILLID		1	//错误技能ID
#define UPGRADE_SKILL_FAILED_BORN_SKILL			2	//普攻技能不用升级
#define UPGRADE_SKILL_FAILED_CONF_MORE_SKILL	3	//配置新加技能代码未对应
#define UPGRADE_SKILL_FAILED_LEVEL_FULL			4	//玩家技能已经满级
#define UPGRADE_SKILL_FAILED_HERO_LEVEL_LIMIT	5	//玩家等级不够
#define	UPGRADE_SKILL_FAILED_EXP_NOT_ENOUGH		6	//玩家经验不够
#define	UPGRADE_SKILL_FAILED_MONEY_NOT_ENOUGH	7	//玩家金钱不够

extern map<string, HeroSkill*> skillId_2_heroSkill;

int upgrade_hero_skill(Hero *hero, char *skillId, char *msg)
{
	char *p = skillId;
	HeroSkill* skill;
	map<string, HeroSkill*>::iterator it_skill;
	it_skill = skillId_2_heroSkill.find(skillId);
	if (it_skill == skillId_2_heroSkill.end())
	{
		cout<<"Hero upgrade skill but the skillId "<<skillId<<" client sent is error"<<endl;
		return UPGRADE_SKILL_FAILED_ERROR_SKILLID;
	}
	
	p++;
	unsigned index = atoi(p);
	if (index == 0)
	{
		cout<<"The born skill needn't to learn!"<<endl;
		return UPGRADE_SKILL_FAILED_BORN_SKILL;
	}
	//(最大技能数13)
	if (index > HERO_SKILL_MAX_NUM)
	{
		cout<<"warning: there is more skills in config , please enLarge the HERO_SKILL_MAX_NUM!!"<<endl;
		return UPGRADE_SKILL_FAILED_CONF_MORE_SKILL;
	}
	
	HeroMemSkill_T *memSkill = &hero->memHero->skills[index];
	
	//该技能满级 (20级)
	if (memSkill->level >= HERO_SKILL_TOP_LEVEL)
	{
		cout<<"The hero's skill is already top level, no need to upgrade!"<<endl;
		return UPGRADE_SKILL_FAILED_LEVEL_FULL;
	}
	
	//升级需求检查
	skill = it_skill->second;
	//升级需要的玩家等级检查
	if (skill->getUpgradeNeedHeroLevel(memSkill->level) > hero->getLevel())
	{
		cout<<"The hero's level is not enough to study this skill"<<endl;
		return UPGRADE_SKILL_FAILED_HERO_LEVEL_LIMIT;
	}
	
	//升级需要的经验检查
	unsigned needExp = skill->getUpgradeNeedExp(memSkill->level);
	if (hero->getHeroSkillExp() < needExp)
	{
		cout<<"The hero doesn't have enough exp to upgrade this skill"<<endl;
		return UPGRADE_SKILL_FAILED_EXP_NOT_ENOUGH;
	}
	
	//升级需要金钱检查
	unsigned needMoney = skill->getUpgradeNeedMoney(memSkill->level);
	if (!useBoundGameMoney(hero, needMoney))
	{
		cout<<"The hero doesn't have enough bound money to upgrade this skill"<<endl;
		return UPGRADE_SKILL_FAILED_MONEY_NOT_ENOUGH;
	}
	
	//升级条件满足
	// hero->useExpNow(needExp);
	hero->useHeroSkillExp(needExp);
	hero->memHero->skills[index].level += 1;
	hero->memHero->skills[index].lastUsedTime = 0;
	int nowLevel = hero->memHero->skills[index].level;
	//如果是被动技能，hero要加上对应属性
	unsigned type = skill->getType();
	if (type >= 0 && type <= 11)
	{
		// hero->incAttr(type, skill->getValue(nowLevel));
		hero->addAttr(type, skill->getValue(nowLevel));
		hero->send_msg_att();
	}

	hero->updataSingleTarget(0,3);
	
	int k = 0;
	int skillMaxFlag=0;
	for ( k; k < HERO_SKILL_MAX_NUM; k++)
	{
		if (hero->memHero->skills[k].level == 0)
		{
			break;
		}
		else if (hero->memHero->skills[k].level == 20)
		{
			skillMaxFlag++;
		}
	}
	
	if(k >= 2)
	{
		hero->addTitle("T009");//添加头衔，学习第一个技能
	}
	
	if(k >= 6)
	{
		hero->addTitle("T010");//添加头衔，学习第5个技能,渐入佳境
	}
	
	if (k == HERO_SKILL_MAX_NUM)
	{
		hero->addTitle("T011");//添加头衔，学习所有技能,武学宗师
		hero->updataSingleTarget(6,5);
	}
	if (skillMaxFlag == HERO_SKILL_MAX_NUM)
	{
		hero->updataSingleTarget(7,5);
	}
	
	sprintf(msg, "%s,%d,%d,%d,%d,%d", skillId, nowLevel, skill->getNeedMagic(nowLevel),
		skill->getUpgradeNeedHeroLevel(nowLevel), skill->getUpgradeNeedExp(nowLevel),
		skill->getUpgradeNeedMoney(nowLevel));
	return UPGRADE_SKILL_SUCCESS;
}