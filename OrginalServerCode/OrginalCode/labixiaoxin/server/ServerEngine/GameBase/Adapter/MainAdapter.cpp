#include "MainAdapter.h"

#include "..\Protocol\ControlProtocol.h"

MainAdapter::MainAdapter(ACE_UINT32 unID)
:BaseAdapter(unID)
{

}

MainAdapter::~MainAdapter()
{

}

int MainAdapter::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_REGISTER_ADAPTER_REQUEST:
			if(add_sub_adapter(msgInfo.s_head->srcAdr.unServiceID, msgInfo.s_head->srcAdr.unAdapterID) == 0)
			{
				sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_REGISTER_ADAPTER_RESPONSE, NULL, 0, msgInfo.s_head->srcAdr);
			}
			//printf("get register adapter request\n");
			break;
		case MSG_UNREGISTER_ADAPTER_REQUEST:
			if(remove_sub_adapter(msgInfo.s_head->srcAdr.unServiceID, msgInfo.s_head->srcAdr.unAdapterID) == 0)
			{
				sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_UNREGISTER_ADAPTER_RESPONSE, NULL, 0, msgInfo.s_head->srcAdr);
			}
			//printf("get unregister adapter request\n");
			break;
		/*
		case MSG_CREATE_SUB_ADAPTER_OBJ_RESULT:
			{
				MsgSubAdapterObjResult *body = (MsgSubAdapterObjResult *)msgInfo.body;
				this->create_sub_adapter_obj_result(msgInfo.s_head->srcAdr.unAdapterID, body->unObjID, body->unSN);
			}
			break;
		case MSG_DESTROY_SUB_ADAPTER_OBJ_RESULT:
			{
				MsgSubAdapterObjResult *body = (MsgSubAdapterObjResult *)msgInfo.body;
				this->destroy_sub_adapter_obj_result(msgInfo.s_head->srcAdr.unAdapterID, body->unObjID, body->unSN);
			}
			break;
		case MSG_WANT_CREATE_SUB_ADAPTER_OBJ:
			{
				MsgSubAdapterObjInfo *body = (MsgSubAdapterObjInfo *)msgInfo.body;
				this->create_sub_adapter_obj(body->unAdapterID, body->unObjID);
			}
			break;
		case MSG_WANT_DESTROY_SUB_ADAPTER_OBJ:
			{
				MsgSubAdapterObjInfo *body = (MsgSubAdapterObjInfo *)msgInfo.body;
				this->destroy_sub_adapter_obj(body->unAdapterID, body->unObjID, body->unSN);
			}
			break;
		case MSG_SUB_ADAPTER_OBJ_REACTIVATE:
			
			break;
		case MSG_SUB_ADAPTER_OBJ_QUERY:
			{
				MsgSubAdapterObjQuery *body = (MsgSubAdapterObjQuery *)msgInfo.body;
				if(deal_sub_adapter_obj_query(msgInfo.s_head->srcAdr, body->unAdapterID, body->unObjID) == -1)
				{
					MsgSubAdapterObjQuery ret;
					ret = *body;
					ret.unServiceID = OBJ_ID_NONE;

					sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_SUB_ADAPTER_OBJ_QUERY_RESULT, &ret, sizeof(MsgSubAdapterObjQuery), msgInfo.s_head->srcAdr);
				}
			}
			break;*/
		}
		
	}

	return OBJ_DEAL_MSG_SUCCESS;
}

SubAdapterList *MainAdapter::get_sub_adapter(ACE_UINT32 unAdapterID)
{
	/*
	SubAdapterInfo *info = NULL;

	SUB_ADAPTER_LIST_ITERATOR iter(m_SubAdapterList);

	while(!iter.done())
	{
		info = iter.next();

		if(info->m_unAdapterID == unAdapterID)
		{
			return info;
		}

		iter.advance();
	}

	return NULL;
	*/
	return SUB_ADAPTER_STATUS_MGR::instance()->get_sub_adapter_list(unAdapterID);
}

int MainAdapter::add_sub_adapter(ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID)
{
	return SUB_ADAPTER_STATUS_MGR::instance()->add_sub_adapter(unSrcAdapterID, unSrcServiceID);
}

int MainAdapter::remove_sub_adapter(ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID)
{
	return SUB_ADAPTER_STATUS_MGR::instance()->remove_sub_adapter(unSrcAdapterID, unSrcServiceID);
}

/*
int MainAdapter::create_sub_adapter_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	SubAdapterInfo *info = get_sub_adapter(unAdapterID);

	if(info != NULL)
	{
		ACE_UINT32 unServiceID = OBJ_ID_NONE;
		ACE_UINT32 unSN = 0;
		int nRet = info->create_obj(unObjID, unServiceID, unSN);

		if(nRet == -1)
		{
			return -1;
		}
		else if(nRet == 0)
		{
			//send create obj msg
			MsgSubAdapterObjInfo body;
			body.unObjID = unObjID;
			body.unSN = unSN;

			if(sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_CREATE_SUB_ADAPTER_OBJ, &body, sizeof(MsgSubAdapterObjInfo), unServiceID, unAdapterID, OBJ_ID_NONE) == -1)
			{
				info->remove_obj(unObjID);
				return -1;
			}
		}
		else
		{
			return 1;
		}

		return 0;
	}

	return -1;
}

int MainAdapter::destroy_sub_adapter_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN)
{
	SubAdapterInfo *info = get_sub_adapter(unAdapterID);

	if(info != NULL)
	{
		ACE_UINT32 unServiceID = OBJ_ID_NONE;
		int nRet = info->create_obj(unObjID, unServiceID, unSN);

		if(nRet == -1)
		{
			return -1;
		}
		else if(nRet == 0)
		{
			//send destroy obj msg
			MsgSubAdapterObjInfo body;
			body.unObjID = unObjID;
			body.unSN = unSN;

			if(sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_DESTROY_SUB_ADAPTER_OBJ, &body, sizeof(MsgSubAdapterObjInfo), unServiceID, unAdapterID, OBJ_ID_NONE) == -1)
			{
				//do nothing
			}
		}
		else
		{
			return 1;
		}

		return 0;
	}

	return -1;
}

int MainAdapter::create_sub_adapter_obj_result(ACE_UINT32 unSrcServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN, int nResult)
{
	SubAdapterInfo *info = get_sub_adapter(unAdapterID);

	if(info == NULL)
	{
		return -1;
	}

	int nRet = info->create_obj_result(nResult, unSrcServiceID, unObjID, unSN);

	if(nRet == 0)
	{
		//on_create_sub_adapter_obj_done(unObjID, nResult);
	}
}

int MainAdapter::destroy_sub_adapter_obj_result(ACE_UINT32 unSrcServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unSN, int nResult)
{
	SubAdapterInfo *info = get_sub_adapter(unAdapterID);

	if(info == NULL)
	{
		return -1;
	}

	int nRet = info->destroy_obj_result(nResult, unSrcServiceID, unObjID, unSN);

	if(nRet == 0)
	{
		if(info->is_obj_in_idle(unObjID))
		{
			this->create_sub_adapter_obj(unAdapterID, unObjID);
		}
		//on_destroy_sub_adapter_obj_done(unObjID, nResult);
	}
}

int MainAdapter::deal_sub_adapter_obj_query(ObjAdr &addr, ACE_UINT32 unQueryAdapterID, ACE_UINT32 unQueryObjID)
{
	SubAdapterInfo *info = get_sub_adapter(unQueryAdapterID);

	if(info == NULL)
	{
		return -1;
	}

	ACE_UINT32 unServiceID = OBJ_ID_NONE;

	int status = info->get_obj_status(unQueryObjID, unServiceID);

	if(unServiceID == OBJ_ID_NONE)
	{
		if(create_sub_adapter_obj(unQueryAdapterID, unQueryObjID) != -1)
		{
			info->save_query_addr(unQueryObjID, addr);
		}
	}
	else
	{
		if(status == SubAdapterInfo::SUB_ADAPTER_OBJ_IDLE)
		{
			info->save_query_addr(unQueryObjID, addr);
			create_sub_adapter_obj(unQueryAdapterID, unQueryObjID);
		}
		else if(status == SubAdapterInfo::SUB_ADAPTER_OBJ_CREATE)
		{
			info->save_query_addr(unQueryObjID, addr);
		}
		else if(status == SubAdapterInfo::SUB_ADAPTER_OBJ_NORMAL)
		{
			answer_sub_adapter_obj_query(addr, unServiceID, unQueryAdapterID, unQueryObjID);
		}
		else
		{
			//wait destroy done
			info->save_query_addr(unQueryObjID, addr);
		}
	}

	return 0;
}

void MainAdapter::answer_sub_adapter_obj_query(ObjAdr &addr, ACE_INT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	MsgSubAdapterObjQuery body;

	body.unServiceID = unServiceID;
	body.unAdapterID = unAdapterID;
	body.unObjID = unObjID;

	sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_SUB_ADAPTER_OBJ_QUERY_RESULT, &body, sizeof(MsgSubAdapterObjQuery), addr);
}
*/