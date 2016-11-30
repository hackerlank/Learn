#pragma once

#include "ace\Singleton.h"
#include "..\..\Base\Utils\ConfigLoader.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"
#include "BaseRes.h"
#include "ace\SString.h"

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, BaseRes *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> ITEM_RES_MAP;
typedef ITEM_RES_MAP::ITERATOR ITEM_RES_MAP_ITERATOR;


class ItemResMgr : public ConfigLoader
{
public:
	ItemResMgr();
	~ItemResMgr();

	int load_all_config();

	virtual int deal_config(int config_id, xmlNodePtr rootNode);

	BaseRes *get_item_res(int unID);

	int get_item_id_list_by_type(ACE_UINT32 unType, ACE_UINT32 unSubInfo, int nInfoStart, int nInfoLen, ACE_UINT32 *destList, ACE_UINT32 unMask);

	void process_res_by_name();

private:
	int parse_item_res_list(xmlNodePtr node, int nResType);
	void parse_sub_type_list(xmlNodePtr node);

	ITEM_RES_MAP m_ItemResMap;

};

typedef ACE_Singleton<ItemResMgr, ACE_Thread_Mutex> ITEM_RES_MGR_INSTANCE;