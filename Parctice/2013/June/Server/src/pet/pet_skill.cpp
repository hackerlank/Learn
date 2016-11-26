// #include "hero.h"
#include "pet.h"
#include "petSkill_config.h"
#include "money_operator.h"
extern map<string,PetSkill_Config*> id_to_petSkill;

void Pet::initSkill(int _index)
{
	char skillId[20]={0};
	snprintf(skillId,sizeof(skillId),"%s%d","f_dj_115_10",_index+1);
	map<string,PetSkill_Config*>::iterator it;
	it=id_to_petSkill.find(skillId);
	if (it==id_to_petSkill.end())
	{
		cout<<"skillId:"<<skillId<<endl;
		return;
	}

	PetSkill_Config *petSkill_config=it->second;
		
	char* uuid = cid();
	strncpy(petdata->petskilldata[_index].identity,uuid,sizeof(petdata->petskilldata[_index].identity));					//宠物技能实例id
	free(uuid);
	snprintf(petdata->petskilldata[_index].id,sizeof(petdata->petskilldata[_index].id),"%s%d",skillId,petdata->type);		//宠物技能id
	petdata->petskilldata[_index].flag=petSkill_config->getFlag();														//宠物技能类型
	petdata->petskilldata[_index].effect=petSkill_config->getInitEffect();												//宠物技能效果
	petdata->petskilldata[_index].increaseRatio=petSkill_config->getIncreaseRatio();										//宠物技能效果的增量
	petdata->petskilldata[_index].limit=petSkill_config->getLimit();														//学习技能宠物需要的等级
	petdata->petskilldata[_index].addLimit=petSkill_config->getAddLimit();												//宠物技能升级所需金币
	petdata->petskilldata[_index].maxLimit=petSkill_config->getMaxLimit();
	petdata->petskilldata[_index].needNumber=petSkill_config->getNeedNumber();
	petdata->petskilldata[_index].needCount=petSkill_config->getNeedCount();
	petdata->petskilldata[_index].addNeedCount=petSkill_config->getAddNeedCount();
	petdata->petskilldata[_index].range=petSkill_config->getRange();
	petdata->petskilldata[_index].level=0;
}

void Pet::learnSkill(int _index)
{
	petdata->petskilldata[_index].level=1;
}

bool Pet::skillLevelUp(Hero *hero,int _index)
{
	petdata->petskilldata[_index].limit=petdata->petskilldata[_index].limit+petdata->petskilldata[_index].addLimit;
	petdata->petskilldata[_index].level++;
	petdata->petskilldata[_index].effect+=petdata->petskilldata[_index].increaseRatio;
	petdata->petskilldata[_index].needCount+=petdata->petskilldata[_index].addNeedCount;
	return true;
}

int Pet::judgeSkillLearn(int _index)
{
	if (petdata->petskilldata[_index].level==0)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
int Pet::getAttRatio(int _index)										//获得攻击比率
{
	return petdata->petskilldata[_index].effect;
}

char* Pet::getSkillId(int _index)
{
	return petdata->petskilldata[_index].id;
}

char* Pet::getSkillIdentity(int _index)
{
	return petdata->petskilldata[_index].identity;
}

PetSkillData Pet::getStruct(int _index)
{
	return petdata->petskilldata[_index];
}

int Pet::getSkillLevel(int _index)
{
	return petdata->petskilldata[_index].level;
}

int Pet::getSkillLimit(int _index)
{
	return petdata->petskilldata[_index].limit;
}

int Pet::getMaxLimit(int _index)
{
	return petdata->petskilldata[_index].maxLimit;
}

int Pet::getSkillFlag(int _index)
{
	return petdata->petskilldata[_index].flag;
}

int Pet::getSkillNeedNumber(int _index)
{
	return petdata->petskilldata[_index].needNumber;
}

int Pet::getSkillNeedCount(int _index)
{
	return petdata->petskilldata[_index].needCount;
}
