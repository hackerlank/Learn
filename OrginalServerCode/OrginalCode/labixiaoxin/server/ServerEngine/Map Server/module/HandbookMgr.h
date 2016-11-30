#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class HandbookMgr : public BaseModule
{
public:
	HandbookMgr();
	~HandbookMgr();

	void init(ACE_UINT32 unCount, BaseItemInfo *list);

	void add(ACE_UINT32 unID);//以前拥有物品只能有个列表，现在应该将它加入MaterialMgr的m_list表中，此处不再做特殊处理了	

	void del(ACE_UINT32 unID);//added jinpan for del

	bool has_handbook(ACE_UINT32 unID);

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	BaseItemInfo m_list[MAX_HANDBOOK_COUNT];


	ACE_UINT32 m_unCount;

private:
	void update_2_db();
};