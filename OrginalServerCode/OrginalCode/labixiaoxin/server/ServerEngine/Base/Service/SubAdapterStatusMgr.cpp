#include "SubAdapterStatusMgr.h"
#include "ServiceObj.h"

#define GENERATE_SERVICE_OBJ_LOCATION_ID(a, b) ((((ACE_UINT64)a) << 32) | (((ACE_UINT64)b)))

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


SubAdapterStatusMgr::SubAdapterStatusMgr()
{
	m_SNCounter = 0;
}

SubAdapterStatusMgr::~SubAdapterStatusMgr()
{

}

bool SubAdapterStatusMgr::is_obj_in_idle(ACE_UINT32 unAdapter, ACE_UINT32 unObjID)
{
	return false;
}

ServiceObjStatusInfo * SubAdapterStatusMgr::find_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	ACE_UINT64 t = GENERATE_SERVICE_OBJ_LOCATION_ID(unAdapterID, unObjID);

	ServiceObjStatusInfo *info = NULL;
	if(m_service_obj_status_map.find(t, info) == 0)
	{
		return info;
	}

	return NULL;
}

int SubAdapterStatusMgr::create_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN)
{
	ServiceObjStatusInfo *pInfo = NULL;

	pInfo = new ServiceObjStatusInfo();

	if(pInfo == NULL)
	{
		return -1;
	}

	pInfo->unAdapterID = unAdapterID;
	pInfo->unObjID = unObjID;

	int nRet = create_obj(pInfo, unServiceID, unSN);

	if(nRet != 0)
	{
		delete pInfo; 
	}

	return nRet;
}

int SubAdapterStatusMgr::create_obj(ServiceObjStatusInfo *pInfo, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN)
{
	ACE_UINT64 t = GENERATE_SERVICE_OBJ_LOCATION_ID(pInfo->unAdapterID, pInfo->unObjID);

	if(m_service_obj_status_map.find(t) == 0)
	{
		return 1;
	}

	pInfo->unStatus = SUB_ADAPTER_OBJ_CREATE;
	pInfo->unSN = m_SNCounter;
	pInfo->bRecreate = true;
	pInfo->unServiceID = get_service_lowest_loading(pInfo->unAdapterID);

	if(m_service_obj_status_map.bind(t, pInfo) != 0)
	{
		return -1;
	}

	unServiceID = pInfo->unServiceID;
	unSN = pInfo->unSN;

	m_SNCounter ++;

	return 0;
}

ServiceObjStatusInfo *SubAdapterStatusMgr::create_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN)
{
	ServiceObjStatusInfo *pInfo = NULL;
	ACE_UINT64 t = GENERATE_SERVICE_OBJ_LOCATION_ID(unAdapterID, unObjID);

	if(m_service_obj_status_map.find(t, pInfo) != 0)
	{
		return NULL;
	}

	if(pInfo->unSN != unSN || pInfo->unServiceID != unServiceID)
	{
		return NULL;
	}

	if(pInfo->unStatus == SUB_ADAPTER_OBJ_CREATE)
	{
		if(nResult == 0)
		{
			pInfo->unStatus = SUB_ADAPTER_OBJ_NORMAL;
			increase_service_loading(unAdapterID, unObjID, pInfo->unServiceID);
		}
		else
		{
			m_service_obj_status_map.unbind(t, pInfo);
		}

		return pInfo;
	}

	return NULL;
}

int SubAdapterStatusMgr::destroy_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN, bool bRecreate)
{
	ServiceObjStatusInfo *pInfo = NULL;
	ACE_UINT64 t = GENERATE_SERVICE_OBJ_LOCATION_ID(unAdapterID, unObjID);

	if(m_service_obj_status_map.find(t, pInfo) != 0)
	{
		return -1;
	}

	pInfo->bRecreate = bRecreate;

	if(pInfo->unStatus == SUB_ADAPTER_OBJ_DESTROY)
	{
		return -1;
	}

	unSN = pInfo->unSN;
	unServiceID = pInfo->unServiceID;
	pInfo->unStatus = SUB_ADAPTER_OBJ_DESTROY;

	return 0;
}

ServiceObjStatusInfo *SubAdapterStatusMgr::destroy_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN)
{
	ServiceObjStatusInfo *pInfo = NULL;
	ACE_UINT64 t = GENERATE_SERVICE_OBJ_LOCATION_ID(unAdapterID, unObjID);

	if(m_service_obj_status_map.find(t, pInfo) != 0)
	{
		return NULL;
	}

	if(pInfo->unSN != unSN || pInfo->unServiceID != unServiceID)
	{
		return NULL;
	}

	m_service_obj_status_map.unbind(t, pInfo);
	decrease_service_loading(unAdapterID, unObjID, pInfo->unServiceID);
	return pInfo;

	/*
	if(pInfo->unStatus == SUB_ADAPTER_OBJ_DESTROY)
	{
		m_service_obj_status_map.unbind(t);

		decrease_service_loading(unAdapterID, unObjID, pInfo->unServiceID);

		return pInfo;
	}

	return NULL;
	*/
}

int SubAdapterStatusMgr::set_recreate_flag(bool flag, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	return 0;
}

void SubAdapterStatusMgr::add_queue(ACE_UINT32 unAdapter, ACE_UINT32 unObjID, ObjAdr &adr)
{
	ServiceObjStatusInfo *info = find_obj(unAdapter, unObjID);
	if(info == NULL)
	{
		return;
	}

	add_queue(info, adr);
}

void SubAdapterStatusMgr::add_queue(ServiceObjStatusInfo *info, ObjAdr &adr)
{
	ObjAdr *new_adr = new ObjAdr();
	if(new_adr == NULL)
	{
		return;
	}
	*new_adr = adr;

	info->query_list.insert_tail(new_adr);
}

SubAdapterLoadingInfo *SubAdapterStatusMgr::find_sub_adapter_loading_info(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID)
{
	SUB_ADAPTER_LIST_ITERATOR iter(m_service_loading_list);

	SubAdapterList *info = NULL;

	while(!iter.done())
	{
		info = iter.next();

		if(info->unAdapterID == unAdapter)
		{
			SUB_ADAPTER_LOADING_LIST_ITERATOR sub_iter(info->service_list);
			SubAdapterLoadingInfo *sub_info = NULL;
			while(!sub_iter.done())
			{
				sub_info = sub_iter.next();

				if(sub_info->unServiceID == unServiceID)
				{
					return sub_info;
				}
				
				sub_iter.advance();
			}

			return NULL;
		}

		iter.advance();
	}

	return NULL;
}

SubAdapterList *SubAdapterStatusMgr::get_sub_adapter_list(ACE_UINT32 unAdapter)
{
	SUB_ADAPTER_LIST_ITERATOR iter(m_service_loading_list);

	SubAdapterList *info = NULL;

	while(!iter.done())
	{
		info = iter.next();

		if(info->unAdapterID == unAdapter)
		{
			return info;
		}

		iter.advance();
	}

	return NULL;
}

int SubAdapterStatusMgr::add_sub_adapter(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID)
{
	SUB_ADAPTER_LIST_ITERATOR iter(m_service_loading_list);

	SubAdapterList *info = NULL;
	bool flag = false;

	while(!iter.done())
	{
		info = iter.next();

		if(info->unAdapterID == unAdapter)
		{
			flag = true;
			break;
		}

		iter.advance();
	}

	if(!flag)
	{
		info = new SubAdapterList();
		if(info == NULL)
		{
			return -1;
		}

		info->unAdapterID = unAdapter;

		m_service_loading_list.insert_tail(info);
	}

	SUB_ADAPTER_LOADING_LIST_ITERATOR sub_iter(info->service_list);
	SubAdapterLoadingInfo *sub_info = NULL;
	while(!sub_iter.done())
	{
		sub_info = sub_iter.next();

		if(sub_info->unServiceID == unServiceID)
		{
			return 1;
		}

		sub_iter.advance();
	}

	sub_info = new SubAdapterLoadingInfo();

	if(sub_info == NULL)
	{
		return -1;
	}

	sub_info->unServiceID = unServiceID;
	sub_info->m_unObjCount = 0;

	info->service_list.insert_tail(sub_info);

	return 0;
}

int SubAdapterStatusMgr::remove_sub_adapter(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID)
{
	SUB_ADAPTER_LIST_ITERATOR iter(m_service_loading_list);

	SubAdapterList *info = NULL;
	bool flag = false;

	while(!iter.done())
	{
		info = iter.next();

		if(info->unAdapterID == unAdapter)
		{
			flag = true;
			break;
		}

		iter.advance();
	}

	if(!flag)
	{
		return -1;
	}

	SUB_ADAPTER_LOADING_LIST_ITERATOR sub_iter(info->service_list);
	SubAdapterLoadingInfo *sub_info = NULL;
	while(!sub_iter.done())
	{
		sub_info = sub_iter.next();

		if(sub_info->unServiceID == unServiceID)
		{
			iter.remove();
			delete sub_info;
			return 0;
		}

		sub_iter.advance();
	}

	return -1;
}

ACE_UINT32 SubAdapterStatusMgr::get_service_lowest_loading(ACE_UINT32 unAdapter)
{
	SUB_ADAPTER_LIST_ITERATOR iter(m_service_loading_list);

	ACE_UINT32 unID = OBJ_ID_NONE;
	SubAdapterList *info = NULL;
	
	while(!iter.done())
	{
		info = iter.next();

		if(info->unAdapterID == unAdapter)
		{
			SUB_ADAPTER_LOADING_LIST_ITERATOR sub_iter(info->service_list);
			SubAdapterLoadingInfo *sub_info = NULL;
			ACE_UINT32 c = 0x7fffffff;
			while(!sub_iter.done())
			{
				sub_info = sub_iter.next();

				if(sub_info->m_unObjCount < c)
				{
					c = sub_info->m_unObjCount;
					unID = sub_info->unServiceID;
				}

				sub_iter.advance();
			}

			break;
		}

		iter.advance();
	}

	return unID;
}

void SubAdapterStatusMgr::increase_service_loading(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID, int c)
{
	SubAdapterLoadingInfo *info = find_sub_adapter_loading_info(unAdapter, unServiceID);

	if(info == NULL)
	{
		return;
	}

	increase_service_loading(info, c);
}

void SubAdapterStatusMgr::decrease_service_loading(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID, int c)
{
	SubAdapterLoadingInfo *info = find_sub_adapter_loading_info(unAdapter, unServiceID);

	if(info == NULL)
	{
		return;
	}

	decrease_service_loading(info, c);
}

void SubAdapterStatusMgr::increase_service_loading(SubAdapterLoadingInfo *info, int c)
{
	info->m_unObjCount += c;
}

void SubAdapterStatusMgr::decrease_service_loading(SubAdapterLoadingInfo *info, int c)
{
	if(info->m_unObjCount < c)
	{
		info->m_unObjCount = 0;
	}
	else
	{
		info->m_unObjCount -= c;
	}
}