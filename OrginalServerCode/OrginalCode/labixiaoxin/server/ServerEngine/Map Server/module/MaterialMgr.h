#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class MaterialMgr : public BaseModule
{
public:
	MaterialMgr();
	~MaterialMgr();

	void init(ACE_UINT32 unCount, MaterialInfo *list);

	void add(ACE_UINT32 unID, ACE_UINT32 unCount);

	bool is_enough(CostInfo &cost, int times);
	void do_cost(CostInfo &cost, int times, bool write_db,ACE_UINT32 count);	

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	MaterialInfo m_list[MAX_MATERIAL_COUNT];
	ACE_UINT32 m_unCount;

	void update_2_db();
private:
	
};