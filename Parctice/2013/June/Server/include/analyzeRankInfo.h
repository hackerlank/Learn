#ifndef _ANALYZE_RANK_INFO_H
#define _ANALYZE_RANK_INFO_H
#include "hero.h"
#include "rankInfo.h"

/*获取排名信息 消息的格式
11，11，heroId,type    
			1财富排名
			2等级排名
			3战力排名
			4杀戮排名
			5杀敌数排名
			6击杀红名排名
			7声望排名
			*/
void getRankInfo(char* buffers);

#endif