#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class GoldenTouchMgr : public BaseModule
{
public:
	ACE_UINT32 m_buy_gold_limit;
public:
	GoldenTouchMgr();
	~GoldenTouchMgr();

	void init(ACE_UINT32 unUsedTouchCount);//格子次数，刷新次数，上次刷新时间，物品列表 

	void Reset()
	{
		m_unUsedTouchCount = 0;
		update_2_db();
	}
	ACE_UINT32 m_unUsedTouchCount;

	void update_2_db();

	void update_GoldMax(ACE_UINT32 nMax,bool is);


};