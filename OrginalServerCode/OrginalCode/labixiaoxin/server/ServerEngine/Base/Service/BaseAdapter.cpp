#include "BaseAdapter.h"

#include "BaseService.h"
#include "..\..\GameBase\Common\GameUtils.h"

BaseAdapter::BaseAdapter(ACE_UINT32 unID)
:ServiceObj(unID)
{
	
}

BaseAdapter::~BaseAdapter()
{
	
}

void BaseAdapter::setAddr(ObjAdr &addr)
{
	addr.unServiceID = BaseService::instance()->m_unID;
	addr.unAdapterID = m_unID;
	addr.unObjID = OBJ_ID_NONE;
}

BaseObj *BaseAdapter::findObj(ACE_UINT32 unObjID)
{
	BaseObj *obj = NULL;

	if(m_objMap.find(unObjID, obj) == 0)
	{
		return obj;
	}

	return NULL;
}

int BaseAdapter::addChild(BaseObj *obj, void *arg, ACE_UINT32 unArgLen)
{
	if(findObj(obj->m_unID) != NULL)
	{
		return 1;
	}

	if(m_objMap.bind(obj->m_unID, obj) != 0)
	{
		return -1;
	}

	if(obj->obj_init(arg, unArgLen) == -1)
	{
		m_objMap.unbind(obj->m_unID, obj);
		return -1;
	}

	return 0;
}

void BaseAdapter::removeChild(ACE_UINT32 unID)
{
	BaseObj *obj;

	if(m_objMap.find(unID, obj) == 0)
	{
		m_objGCList.insert_tail(obj);
	}

	/*
	int t = m_objMap.current_size();
	
	if(m_objMap.unbind(unID, obj) == 0)
	{
		t = m_objMap.current_size();
		m_objGCList.insert_tail(obj);
	}
	*/
}

void BaseAdapter::removeChild(BaseObj *obj)
{
	/*
	if(m_objMap.unbind(obj->m_unID) == 0)
	{
		m_objGCList.insert_tail(obj);
	}
	*/
	m_objGCList.insert_tail(obj);
}

void BaseAdapter::removeAllChild()
{
	ACTIVE_OBJ_MAP_ITERATOR iter(m_objMap);
	BaseObj *pObj;

	for(iter = m_objMap.begin(); iter != m_objMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		delete pObj;
	}

	m_objMap.unbind_all();
}

void BaseAdapter::obj_gc()
{
	OBJ_GC_LIST_ITERATOR iter(m_objGCList);
	BaseObj *obj;
	while(!iter.done())
	{
		obj = iter.next();

		if(obj)
		{
			m_objMap.unbind(obj->m_unID, obj);
			delete obj;
		}

		iter.remove();
		//iter.advance();
	}

	m_objGCList.reset();
}

/*
void BaseAdapter::obj_fini()
{
	removeAllChild();
	obj_gc();
}
*/


void BaseAdapter::service_obj_timer_callback()
{
	ServiceObj::service_obj_timer_callback();
	/*
	ACTIVE_OBJ_MAP_ITERATOR map_iter(m_objMap);
	BaseObj *pObj;

	for(map_iter = m_objMap.begin(); map_iter != m_objMap.end(); map_iter++)
	{
		pObj = (*map_iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		pObj->service_obj_timer_callback();
	}
	*/
	BaseObj *pObj;

	ACTIVE_OBJ_MAP_ITERATOR iter_remove(m_timeoutObjRemoveMap);
	for(iter_remove = m_timeoutObjRemoveMap.begin(); iter_remove != m_timeoutObjRemoveMap.end(); iter_remove++)
	{
		pObj = (*iter_remove).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		printf("remove timeout %d\n", pObj->m_unID);

		m_timeoutObjMap.unbind(pObj->m_unID);	
	}

	m_timeoutObjRemoveMap.unbind_all();

	
	ACTIVE_OBJ_MAP_ITERATOR iter_add(m_timeoutObjAddMap);
	for(iter_add = m_timeoutObjAddMap.begin(); iter_add != m_timeoutObjAddMap.end(); iter_add++)
	{
		pObj = (*iter_add).int_id_;
		if(pObj == NULL)
		{
			continue;
		}

		printf("add timeout adapter %d id %d\n", m_unID, pObj->m_unID);
		m_timeoutObjMap.bind(pObj->m_unID, pObj);
	}

	m_timeoutObjAddMap.unbind_all();

	ACTIVE_OBJ_MAP_ITERATOR iter(m_timeoutObjMap);
	for(iter = m_timeoutObjMap.begin(); iter != m_timeoutObjMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		pObj->service_obj_timer_callback();
		
	}


	obj_gc();
}


void BaseAdapter::closeObj(ACE_UINT32 unID)
{
	BaseObj *obj;

	if(m_objMap.find(unID, obj) == 0)
	{
		obj->set_destroy(true);
	}
}

void BaseAdapter::closeAdapter()
{
	ACTIVE_OBJ_MAP_ITERATOR iter(m_objMap);
	BaseObj *pObj;

	for(iter = m_objMap.begin(); iter != m_objMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		pObj->set_destroy(true);
	}

	this->set_destroy(true);
}

bool BaseAdapter::should_destroy()
{
	if(ServiceObj::should_destroy() && m_objMap.current_size() == 0)
	{
		return true;
	}

	return false;
}

int BaseAdapter::obj_msg_callback(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_OBJ_LOCATION)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_SERVICE_CREATE_SERVICE_OBJ:
			{
				//create service obj
				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;
				if(create_child(body->unObjID, body->unSN) == -1)
				{
					//send create fail msg

					MsgServiceObjOP retInfo;
					retInfo = *body;
					retInfo.nResult = -1;

					this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_CREATE_SERVICE_OBJ_RESULT, (char*)&retInfo, sizeof(MsgServiceObjOP), msgInfo.s_head->srcAdr);
				}

			}
			break;
		case MSG_SERVICE_DESTROY_SERVICE_OBJ:
			{
				//destroy service obj

				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;

				if(destroy_child(body->unSN) == -1)
				{
					MsgServiceObjOP retInfo;
					retInfo = *body;
					retInfo.nResult = -1;

					this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_DESTROY_SERVICE_OBJ_RESULT, (char*)&retInfo, sizeof(MsgServiceObjOP), msgInfo.s_head->srcAdr);
				}
			}
			break;
		}
		
	}
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CREATE_BASE_OBJ:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
				create_child(body->unID, 0);
			}
			break;
		case MSG_REMOVE_BASE_OBJ:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
				destroy_child(body->unID);
			}
			break;
		}
	}

	return ServiceObj::obj_msg_callback(msgInfo);
}

int BaseAdapter::create_child(ACE_UINT32 unID, ACE_UINT32 unSN, void *arg, ACE_UINT32 unArgLen)
{
	BaseObj * obj = new_child_obj(unID);

	if(obj == NULL)
	{
		return -1;
	}

	obj->m_unOPSN = unSN;

	int nRet = addChild(obj, arg, unArgLen);
	if(nRet != 0)
	{
		delete obj;
	}

	return nRet;

	/*
	if(addChild(obj, arg, unArgLen) == -1)
	{
		delete obj;
		return -1;
	}

	return 0;
	*/
}

int BaseAdapter::destroy_child(ACE_UINT32 unID)
{
	printf("destroy_child:unID[%d]\n",unID);
	BaseObj *obj = findObj(unID);

	if(obj == NULL)
	{
		return -1;
	}

	obj->set_destroy(true);
	return 0;
}

int BaseAdapter::destroy_child_direct(ACE_UINT32 unID)
{
	BaseObj *obj = NULL;

	if(m_objMap.unbind(unID, obj) == 0)
	{
		if(obj != NULL)
		{
			delete obj;
		}

		return 0;
	}
	return -1;
}

void BaseAdapter::add_child_to_timeout_map(BaseObj *obj)
{
	m_timeoutObjAddMap.bind(obj->m_unID, obj);
}

void BaseAdapter::remove_child_from_timeout_map(BaseObj *obj)
{
	m_timeoutObjRemoveMap.bind(obj->m_unID, obj);
}

void BaseAdapter::clear_timeout_map(ACE_UINT32 unID)
{
	m_timeoutObjMap.unbind(unID);
	m_timeoutObjAddMap.unbind(unID);
	m_timeoutObjRemoveMap.unbind(unID);
}