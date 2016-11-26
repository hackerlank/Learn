#include "petSkill_config.h"
#include <string.h>
PetSkill_Config::PetSkill_Config(char* _id,int _flag,int _initEffect,int _increaseRatio,int _range,int _limit,int _addLimit,int _maxLimit,int _needNumber,int _needCount,int _addNeedCount)
{
	strncpy(id,_id,sizeof(id));
	flag=_flag;
	initEffect=_initEffect;
	increaseRatio=_increaseRatio;
	range=_range;
	limit=_limit;
	addLimit=_addLimit;
	maxLimit=_maxLimit;
	needNumber=_needNumber;
	needCount=_needCount;
	addNeedCount=_addNeedCount;
}
char* PetSkill_Config::getId(void)
{
	return id;
}
int PetSkill_Config::getFlag(void)
{
	return flag;
}
int PetSkill_Config::getInitEffect(void)
{
	return initEffect;
}
int PetSkill_Config::getIncreaseRatio(void)
{
	return increaseRatio;
}
int PetSkill_Config::getRange(void)
{
	return range;
}
int PetSkill_Config::getLimit(void)
{
	return limit;
}
int PetSkill_Config::getAddLimit(void)
{
	return addLimit;
}
int PetSkill_Config::getMaxLimit(void)
{
	return maxLimit;
}
int PetSkill_Config::getNeedNumber(void)
{
	return needNumber;
}
int PetSkill_Config::getNeedCount(void)
{
	return needCount;
}
int PetSkill_Config::getAddNeedCount(void)
{
	return addNeedCount;
}