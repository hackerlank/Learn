#ifndef PETSKILL_CONFIG_H
#define PETSKILL_CONFIG_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
class PetSkill_Config
{
private:  
	char id[20];
	int flag;
	int initEffect;
	int increaseRatio;
	int range;
	int limit;
	int addLimit;
	int maxLimit;
	int needNumber;
	int needCount;	
	int addNeedCount;	

public:
	PetSkill_Config(char* _id,int _flag,int _initEffect,int _increaseRatio,int _range,int _limit,int _addLimit,int _maxLimit,int _needNumber,int _needCount,int _addNeedCount);
	char* getId(void);
	int getFlag(void);
	int getInitEffect(void);
	int getIncreaseRatio(void);
	int getRange(void);
	int getLimit(void);
	int getAddLimit(void);
	int getMaxLimit(void);
	int getNeedNumber(void);
	int getNeedCount(void);
	int getAddNeedCount(void);

};
#endif