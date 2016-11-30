#pragma once

#include "ServiceObj.h"
//#include "BaseAdapter.h"

class BaseAdapter;

class BaseObj : public ServiceObj
{
public:
	/*
	enum
	{
		OBJ_TRANSFER_NONE = 0,
		OBJ_TRANSFER_SAVING,
		OBJ_TRANSFER_WAIT,
		OBJ_TRANSFER_READY
	};
	*/

	BaseObj(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~BaseObj();

	virtual void setAddr(ObjAdr &addr);

	virtual void obj_fini();

	virtual int start_create();
	virtual int start_running();
	virtual int start_destroy();

	virtual void create_done();
	virtual void destroy_done();

	virtual bool wanna_do_timeout();

	virtual void set_destroy(bool flag);
	void set_timeout_status();

	BaseAdapter *m_ParentAdapter;

	ACE_UINT32 m_unOPSN;

	

protected:

	bool m_bDoTimeout;
	//bool m_bDoDestroyMyself;

private:
	ObjAdr *get_own_query_addr();
	//ACE_UINT32 m_unObjTransferStatus;
	//ACE_UINT32 m_unTransferServiceID;
};