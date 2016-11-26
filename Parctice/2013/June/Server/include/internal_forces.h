#ifndef _INTERNAL_FORCES_H_
#define _INTERNAL_FORCES_H_

#include "data_structure_struct.h"

#define BASE_INTERNAL_FORCES_LEVEL 10
#define MAX_INTERNAL_FORCES_LEVEL 110

typedef struct InForsLvlAdd_S
{
	int level;
	int needIF;
	int upgradeNeedExp;
	int canUseGold;
	int value[10];
	int total[10];
} InForsLvlAdd_T;

typedef struct InForsDat_S
{
	char party[10];
	int perTimeNeedInner;
	int useInnerTimeLmt;
	int useInnerGetExp;
	int useGlodGetExp;
	int luckRate;
	int luckTimes;
	int vipUseGoldTimeLmt[11];
	int thisTimeNeedGold[50];
	map<int, InForsLvlAdd_T> level_2_nomalAdd;
	map<int, InForsLvlAdd_T> level_2_extraAdd;
	
} InForsDat_T;

extern map<string, InForsDat_T> party_2_inForsDat;

#endif