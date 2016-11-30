#pragma once

#include "ServiceObj.h"
#include "BaseObj.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Containers.h"

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, BaseObj *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> ACTIVE_OBJ_MAP;
typedef ACTIVE_OBJ_MAP::ITERATOR ACTIVE_OBJ_MAP_ITERATOR;

typedef ACE_DLList<BaseObj> OBJ_GC_LIST;
typedef ACE_DLList_Iterator<BaseObj> OBJ_GC_LIST_ITERATOR;

class BaseAdapter : public ServiceObj
{
public:
	BaseAdapter(ACE_UINT32 unID);
	virtual ~BaseAdapter();

	virtual void service_obj_timer_callback();

	virtual void setAddr(ObjAdr &addr);

	int addChild(BaseObj *obj, void *arg = NULL, ACE_UINT32 unArgLen = 0);
	void removeChild(ACE_UINT32 unID);
	void removeChild(BaseObj *obj);

	int get_obj_count(){return m_objMap.current_size();};

	virtual BaseObj *new_child_obj(ACE_UINT32 unID){return NULL;};

	int create_child(ACE_UINT32 unID, ACE_UINT32 unSN = 0, void *arg = NULL, ACE_UINT32 unArgLen = 0);
	int destroy_child(ACE_UINT32 unID);

	int destroy_child_direct(ACE_UINT32 unID);
	
	BaseObj *findObj(ACE_UINT32 unObjID);

	void closeObj(ACE_UINT32 unID);

	void add_child_to_timeout_map(BaseObj *obj);
	void remove_child_from_timeout_map(BaseObj *obj);
	void clear_timeout_map(ACE_UINT32 unID);

	void closeAdapter();
	virtual bool should_destroy();

	//virtual bool hasDestoryed();

	virtual int obj_msg_callback(MessageInfo &msgInfo);

	ACE_Recursive_Thread_Mutex m_mutex;
protected:
	ACTIVE_OBJ_MAP m_objMap;
	ACTIVE_OBJ_MAP m_timeoutObjMap;
	ACTIVE_OBJ_MAP m_timeoutObjAddMap;
	ACTIVE_OBJ_MAP m_timeoutObjRemoveMap;

private:
	void removeAllChild();
	void obj_gc();

	OBJ_GC_LIST m_objGCList;
	//ACE_UINT32 m_unAdapterStatus;
};