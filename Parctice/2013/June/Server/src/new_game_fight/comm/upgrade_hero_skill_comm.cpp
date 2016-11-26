#include "wholeDefine.h"
#include "hero_skill_asist.h"

extern map<string, HeroSkill*> skillId_2_heroSkill;

void upgrade_hero_skill_comm(char *buffer)
{
	char *skillId;
	char msg[200] = {0};
	char temp[200] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(skillId);
	int ret = upgrade_hero_skill(pg_hero, skillId, temp);
	if (ret != 0)
	{
		sprintf(msg, "26,0,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	} else {
		sprintf(msg, "26,0,1,%s,%d", temp, pg_hero->getHeroSkillExp());
		send_msg(pg_hero->getFd(), msg);
	}
}

void view_hero_skills_comm(char *buffer)
{
	view_hero_skills_info_comm(pg_hero);
}

void view_hero_skills_info_comm(Hero *hero)
{
	char msg[400] = {0}, temp[400] = {0};
	HeroSkill* skill;
	map<string, HeroSkill*>::iterator it_skill;
	int skillNum = 0;
	int nowLevel = 0;
	for (int index = 1; index < HERO_SKILL_MAX_NUM; index++)
	{
		HeroMemSkill_T *memSkill = &hero->memHero->skills[index];
		nowLevel = memSkill->level;
		// cout<<"Come in and skillId is "<<memSkill->skillId<<" and skillLevel is "<<nowLevel<<endl;
		if (nowLevel > 0)
		{
			// cout<<"this skill is more than 1 level "<<memSkill->skillId<<endl;
			it_skill = skillId_2_heroSkill.find(memSkill->skillId);
			if (it_skill == skillId_2_heroSkill.end())
			{
				// cout<<"Hero memSkill have saveed an errorId "<<memSkill->skillId<<endl;
				continue;
			}
			
			skillNum++;
			skill = it_skill->second;
			hero->memHero->skills[index].lastUsedTime = 0;				//把技能的CD清掉
			sprintf(temp + strlen(temp), ",%s,%d,%d,%d,%d,%d", memSkill->skillId, nowLevel,
			skill->getNeedMagic(nowLevel), skill->getUpgradeNeedHeroLevel(nowLevel),
			skill->getUpgradeNeedExp(nowLevel), skill->getUpgradeNeedMoney(nowLevel));
		}
	}
	sprintf(msg, "26,1,%d%s,%d", skillNum, temp, hero->getHeroSkillExp());
	send_msg(hero->getFd(), msg);
}