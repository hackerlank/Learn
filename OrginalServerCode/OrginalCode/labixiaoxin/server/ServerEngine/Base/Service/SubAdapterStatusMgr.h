#pragma once

/*
管理所有obj的状态，obj的key是64位的

*/

#include "ace\Singleton.h"
#include "ace\Containers.h"
#include "..\Protocol\Protocol.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"

typedef ACE_DLList<ObjAdr> OBJ_QUERY_ADDR_LIST;
typedef ACE_DLList_Iterator<ObjAdr> OBJ_QUERY_ADDR_LIST_ITERATOR;

typedef struct tagServiceObjStatusInfo
{
	ACE_UINT32 unServiceID;
	ACE_UINT32 unAdapterID;
	ACE_UINT32 unObjID;
	ACE_UINT32 unStatus;
	ACE_UINT32 unSN;
	bool bRecreate;
	OBJ_QUERY_ADDR_LIST query_list;
}ServiceObjStatusInfo;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT64, ServiceObjStatusInfo *, ACE_Hash<ACE_UINT64>, 
ACE_Equal_To<ACE_UINT64>, ACE_Null_Mutex> SERVICE_OBJ_STATUS_INFO_MAP;
typedef SERVICE_OBJ_STATUS_INFO_MAP::ITERATOR SERVICE_OBJ_STATUS_INFO_MAP_ITERATOR;

typedef struct tagSubAdapterLoadingInfo
{
	ACE_UINT32 unServiceID;
	ACE_UINT32 m_unObjCount;
}SubAdapterLoadingInfo;

typedef ACE_DLList<SubAdapterLoadingInfo> SUB_ADAPTER_LOADING_LIST;
typedef ACE_DLList_Iterator<SubAdapterLoadingInfo> SUB_ADAPTER_LOADING_LIST_ITERATOR;

typedef struct tagSubAdapterList
{
	ACE_UINT32 unAdapterID;
	SUB_ADAPTER_LOADING_LIST service_list;
}SubAdapterList;

typedef ACE_DLList<SubAdapterList> SUB_ADAPTER_LIST;
typedef ACE_DLList_Iterator<SubAdapterList> SUB_ADAPTER_LIST_ITERATOR;

class SubAdapterStatusMgr
{
public:
	enum
	{
		SUB_ADAPTER_OBJ_CREATE = 0,
		SUB_ADAPTER_OBJ_NORMAL,
		SUB_ADAPTER_OBJ_DESTROY
	};

	SubAdapterStatusMgr();
	~SubAdapterStatusMgr();

	//service obj mgr
	bool is_obj_in_idle(ACE_UINT32 unAdapter, ACE_UINT32 unObjID);
	ServiceObjStatusInfo *find_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	int create_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN);
	int create_obj(ServiceObjStatusInfo *pInfo, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN);
	ServiceObjStatusInfo *create_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN);
	int destroy_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 &unServiceID, ACE_UINT32 &unSN, bool bRecreate);
	ServiceObjStatusInfo *destroy_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN);
	int set_recreate_flag(bool flag, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	int reactivate_obj(ACE_UINT32 unObjID, ACE_UINT32 unSN);

	//cache query adr
	void add_queue(ACE_UINT32 unAdapter, ACE_UINT32 unObjID, ObjAdr &adr);
	void add_queue(ServiceObjStatusInfo *info, ObjAdr &adr);

	//sub adapter mgr
	SubAdapterLoadingInfo *find_sub_adapter_loading_info(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID);
	SubAdapterList *get_sub_adapter_list(ACE_UINT32 unAdapter);
	int add_sub_adapter(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID);
	int remove_sub_adapter(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID);
	ACE_UINT32 get_service_lowest_loading(ACE_UINT32 unAdapter);
	void increase_service_loading(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID, int c = 1);
	void decrease_service_loading(ACE_UINT32 unAdapter, ACE_UINT32 unServiceID, int c = 1);
	void increase_service_loading(SubAdapterLoadingInfo *info, int c = 1);
	void decrease_service_loading(SubAdapterLoadingInfo *info, int c = 1);
private:
	SERVICE_OBJ_STATUS_INFO_MAP m_service_obj_status_map;
	SUB_ADAPTER_LIST m_service_loading_list;

	ACE_UINT32 m_SNCounter;
};

typedef ACE_Singleton<SubAdapterStatusMgr, ACE_Thread_Mutex> SUB_ADAPTER_STATUS_MGR;