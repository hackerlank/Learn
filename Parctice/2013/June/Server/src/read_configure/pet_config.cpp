#include "pet_config.h"
#include <string.h>
Pet_Config::Pet_Config(char* _id,char* _nickName,int _level,int _limit,int _outAttackVal,int _outAttackValRate,int _inAttackVal,int _inAttackValRate,int _hit,int _hitRate,int 						_crit,int _critRate,int _generation,int _quality,int _type,int _range,char* _photoId,char* _normal,int _flag,int _expTimes,int _needNumber,int _needCount,
						char *_nextid,char*_nextGenid)
{	
	strncpy(id,_id,sizeof(id));
	
	strncpy(nickName,_nickName,sizeof(nickName));
	
	strncpy(nextid,_nextid,sizeof(nextid));
	
	strncpy(nextGenid,_nextGenid,sizeof(nextGenid));
	
	level=_level;
	limit=_limit;
	outAttackVal=_outAttackVal;
	outAttackValRate=_outAttackValRate;
	inAttackVal=_inAttackVal;
	inAttackValRate=_inAttackValRate;
	hit=_hit;
	hitRate=_hitRate;
	crit=_crit;
	critRate=_critRate;
	generation=_generation;
	quality=_quality;
	type=_type;
	range=_range;
	flag=_flag;
	
	strncpy(photoId,_photoId,sizeof(photoId));
	
	strncpy(normal,_normal,sizeof(normal));
	
	expTimes=_expTimes;
	needCount=_needCount;
	needNumber=_needNumber;
}
char*  Pet_Config::getId(void)
{
	return id;
}
char*  Pet_Config::getNickName(void)
{
	return nickName;
}
int Pet_Config::getLevel(void)
{
	return level;
}
int Pet_Config::getLimit(void)
{
	return limit;
}
int Pet_Config::getFlag(void)
{
	return flag;
}
int Pet_Config::getOutAttackVal(void)
{
	return outAttackVal;
}
int Pet_Config::getOutAttackValRate(void)
{
	return outAttackValRate;
}
int Pet_Config::getInAttackVal(void)
{
	return inAttackVal;
}
int Pet_Config::getInAttackValRate(void)
{
	return inAttackValRate;
}
int Pet_Config::getHit(void)
{
	return hit;
}
int Pet_Config::getHitRate(void)
{
	return hitRate;
}
int Pet_Config::getCrit(void)
{
	return crit;
}
int Pet_Config::getCritRate(void)
{
	return critRate;
}
int Pet_Config::getGeneration(void)
{
	return generation;
}
int Pet_Config::getQuality(void)
{
	return quality;
}
int Pet_Config::getType(void)
{
	return type;
}
int Pet_Config::getRange(void)
{
	return range;
}
char*  Pet_Config::getPhotoId(void)
{
	return photoId;
}
char* Pet_Config::getNormal(void)
{
	return normal;
}
int Pet_Config::getExpTimes(void)
{
	return expTimes;
}
int Pet_Config::getNeedNumber(void)
{
	return needNumber;
}
int Pet_Config::getNeedCount(void)
{
	return needCount;
}
char *Pet_Config::getNextid(void)
{
	return nextid;
}
char *Pet_Config::getNextGenid(void)
{
	return nextGenid;
}