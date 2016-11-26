/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server排名数据管理类；

**************************************************/


#ifndef _RANK_INFO_ASIST_H
#define _RANK_INFO_ASIST_H

#include "hero.h"

/**************************
函数作用 获取排名信息，信息用string类型表示；
函数参数 _index 将要获取的信息类型下标；
  返回值 char*  获取信息的具体值; 
  	调用 获取排行信息是调用；
***************************/
char* getRankInfo(int index);

/**************************
函数作用 更新临时数据保存map；
  返回值 bool 获取信息成功; 
	调用 角色下线时调用；
***************************/
bool updateRankTempData(Hero* hero);

/**************************
函数作用 触发刷新排名信息,在 my_time.h 中调用；
	调用 刷新时调用；
***************************/
void setRankInfoToLocal(void);

/**************************
函数作用 开机读取排名信息；
	调用 开机时调用；
***************************/
bool rankInfoBootInit();

/**************************
函数作用 存储排名信息；
	调用 存储时调用；
***************************/
bool saveRankInfo2Mem();

/**************************
函数作用 获取战力值；
	调用 查看人物信息调用；
***************************/
unsigned long GetPowerValue(MemHero*myHeroMem);

void rankAnalysis(void);

void saveRankLog(void);

#endif
