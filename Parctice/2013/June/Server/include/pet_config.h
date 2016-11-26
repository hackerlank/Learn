#ifndef PET_CONFIG_H
#define PET_CONFIG_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
class Pet_Config
{
private:  
	char id[20];
	char nickName[50];
	char nextid[50];
	char nextGenid[50];
	int level;
	int limit;
	int flag;
	int outAttackVal;
	int outAttackValRate;
	int inAttackVal;
	int inAttackValRate;
	int hit;
	int hitRate;
	int crit;
	int critRate;
	int expTimes;
	int generation;
	int quality;
	int type;
	int range;
	int needNumber;
	int needCount;
	char photoId[20];
	char normal[20];

public:
	Pet_Config(char* _id,char* _nickName,int _level,int _limit,int _outAttackVal,int _outAttackValRate,int _inAttackVal,int _inAttackValRate,int _hit,int _hitRate,int _crit,int _critRate,int _generation,int _quality,int _type,int _range,char* _photoId,char* _normal,int _flag,int _expTimes,int _needNumber,int _needCount,char *_nextid,char *_nextGenid);
	char* getId(void);
	char* getNickName(void);
	int getLevel(void);
	int getLimit(void);
	int getFlag(void);
	int getOutAttackVal(void);
	int getOutAttackValRate(void);
	int getInAttackVal(void);
	int getInAttackValRate(void);
	int getHit(void);
	int getHitRate(void);
	int getCrit(void);
	int getCritRate(void);
	int getGeneration(void);
	int getQuality(void);
	int getType(void);
	int getRange(void);
	char* getPhotoId(void);
	char* getNormal(void);
	int getExpTimes(void);
	int getNeedNumber(void);
	int getNeedCount(void);
	char *getNextid(void);
	char *getNextGenid(void);
};
#endif