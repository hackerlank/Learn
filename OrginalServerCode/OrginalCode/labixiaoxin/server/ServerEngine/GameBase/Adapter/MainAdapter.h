#pragma once

/*
1.管理所有的sub adapter(注册，注销)
2.处理sub adater下的obj添加和删除消息
*/

#include "..\..\Base\Service\BaseAdapter.h"
#include "..\..\Base\Service\SubAdapterStatusMgr.h"

class MainAdapter : public BaseAdapter
{
public:
	MainAdapter(ACE_UINT32 unID);
	virtual ~MainAdapter();

	virtual int deal_msg(MessageInfo &msgInfo);

	//virtual void on_create_sub_adapter_obj_done(ACE_UINT32 unObjID, int result) = 0;
	//virtual void on_destroy_sub_adapter_obj_done(ACE_UINT32 unObjID, int result) = 0;

private:
	SubAdapterList *get_sub_adapter(ACE_UINT32 unAdapterID);
	int add_sub_adapter(ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID);
	int remove_sub_adapter(ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID);
	//int create_sub_adapter_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	//int destroy_sub_adapter_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN);
	//int create_sub_adapter_obj_result(ACE_UINT32 unSrcServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN, int nResult);
	//int destroy_sub_adapter_obj_result(ACE_UINT32 unSrcServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN, int nResult);
	//int deal_sub_adapter_obj_query(ObjAdr &addr, ACE_UINT32 unQueryAdapterID, ACE_UINT32 unQueryObjID);

	//void answer_sub_adapter_obj_query(ObjAdr &addr, ACE_INT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
};