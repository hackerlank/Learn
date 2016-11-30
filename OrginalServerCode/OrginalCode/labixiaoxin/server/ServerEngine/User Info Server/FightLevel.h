/********************************************************************
    创建时间：    2015/09/08  15:02:25 
    文件名：      PlayerLevel.h
    作者：        xxj
    
    功能:		1.闯关最高伤害排行榜
				2.
                
    说明:		1. 
                2. 
*********************************************************************/

#pragma once
#include "..\ace\Basic_Types.h"
#include "..\GameBase\Common\GameDefine.h"

class CFightLevel
{
public:
	CFightLevel();
	~CFightLevel();
public:
	void Update(const FightPlayerInfoBase & info);

	ACE_UINT32 m_unCount;
	FightPlayerInfoBase m_list[MAX_HONOUR_LEVEL_COUNT + 1];//多预留一个做缓存区//
private:
	void InsertionSort(const FightPlayerInfoBase & info);
};