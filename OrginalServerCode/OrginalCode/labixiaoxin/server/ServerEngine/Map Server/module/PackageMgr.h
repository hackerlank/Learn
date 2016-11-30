#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

class PackageMgr : public BaseModule, public EventListener
{
public:
	PackageMgr();
	~PackageMgr();
	
	void Init_list(ACE_UINT32 unCount, PackageCell *list);
	PackageCell *get_cell(int idx);
	int replace(int idx, PackageCell *cell);
	int add_item(const ItemInfo &info);

	void update_cell(int idx);

	int delete_item(int idx, PackageCell &cell);
	int delete_item_list(int *idxList, int nCount);

	void delete_last_item();

	int expand_max_package();

	virtual void handle_event(BaseEvent *e);



	ACE_UINT32 m_unPackageMax;

	ACE_UINT32 m_unExtraLimit;

	bool is_full();

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	int send_info_i(ObjAdr &targetAdr, ACE_UINT32 unSN, int start_pos);

	void update_2_db(int idx);

	void update_PackageMax(ACE_UINT32 packageMax,bool is);

private:
	void DeleteOldRes();
	ACE_UINT32 m_lockList[MAX_ITEMS_COUNT];

	ACE_UINT32 m_unCount;
	PackageCell m_list[MAX_ITEMS_COUNT];
};