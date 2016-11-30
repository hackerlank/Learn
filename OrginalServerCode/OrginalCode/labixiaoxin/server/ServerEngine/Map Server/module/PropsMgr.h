#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include <vector>

class PropsMgr : public BaseModule
{
public:
	PropsMgr();
	~PropsMgr();

	void init(ACE_UINT32 unCount, PropsInfo *list);

	void add(ACE_UINT32 unID, ACE_UINT32 unCount);

	bool is_enough(CostInfo &cost, int times);
	void do_cost(CostInfo &cost, int times, bool write_db,ACE_UINT32 count);	

	const PropsInfo* GetPropsInfo(int idx);
	const PropsInfo* GetPropsInfoByID(int id);

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	std::vector<PropsInfo> m_list;

	void update_2_db();
private:
	
};