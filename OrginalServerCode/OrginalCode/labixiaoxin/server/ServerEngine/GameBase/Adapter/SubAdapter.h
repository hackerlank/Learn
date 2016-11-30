#pragma once

/*
1.向main adapter注册和注销
2.向main adapter请求增加和删除obj
*/

#include "..\..\Base\Service\BaseAdapter.h"
#include "SubAdapterObj.h"

typedef struct tagMainAdapterInfo
{
	enum
	{
		MAIN_ADAPTER_REGISER = 0,
		MAIN_ADAPTER_REGISTER_DONE,
		MAIN_ADAPTER_UNREGISTER
	};
	
	ACE_UINT32 unStatus;
	ACE_UINT32 unServiceID;
	ACE_UINT32 unAdapterID;
	tagMainAdapterInfo()
	{
		unStatus = MAIN_ADAPTER_REGISER;
		unServiceID = OBJ_ID_NONE;
		unAdapterID = OBJ_ID_NONE;
	}
}MainAdapterInfo;

class SubAdapter : public BaseAdapter
{
public:
	SubAdapter(ACE_UINT32 unID);
	virtual ~SubAdapter();

	//向目标adapter注册
	int register_adapter(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID);
	//向目标adapte注销
	int unregister_adapter();

	virtual ACE_UINT32 get_register_service_id() = 0;
	virtual ACE_UINT32 get_register_adapter_id() = 0;

	virtual int start_create();
	virtual int start_destroy();

	virtual int deal_msg(MessageInfo &msgInfo);
	virtual void obj_timeout();

	virtual bool hasCreated();
	virtual bool hasDestoryed();

	void lru_add(SubAdapterObj *obj);
	void lru_remove(SubAdapterObj *obj);
	void lru_update(SubAdapterObj *obj);
	void lru_full_notify();
protected:
	ACE_UINT32 m_unMaxChild;
	
private:
	bool isAdapterRegisterDone();
	bool isAdapterUnregisterDone();
	void set_register_done(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID);
	void set_unregister_done(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID);

	void remove_lru_obj();

	MainAdapterInfo m_MainAdapterInfo;

	SubAdapterObj *m_ChildHead;
	SubAdapterObj *m_ChildTail;

};