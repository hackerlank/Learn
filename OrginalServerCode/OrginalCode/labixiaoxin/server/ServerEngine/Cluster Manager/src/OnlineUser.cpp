#include "OnlineUser.h"

OnlineUser::OnlineUser(ACE_UINT32 unID, BaseAdapter *parent)
:BaseObj(unID, parent)
{
	m_unCurrentWorldID = OBJ_ID_NONE;
	m_unCurrentEntityID = OBJ_ID_NONE;
}

OnlineUser::~OnlineUser()
{

}

int OnlineUser::dealMsg(MessageInfo &msgInfo)
{
	if(msgInfo.m_head->unType == MSG_LOGIN_RESPONSE)
	{

	}
	else if(msgInfo.m_head->unType == MSG_GET_WORLD_LIST_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_ENTER_WORLD_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_LEAVE_WORLD_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_GET_CHARACTER_LIST_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_CREATE_CHARACTER_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_DELETE_CHARACTER_REQUEST)
	{

	}
	else if(msgInfo.m_head->unType == MSG_GATEWAY_CREATE_SESSION_RESPONSE)
	{

	}
	else if(msgInfo.m_head->unType == MSG_GATEWAY_REMOVE_SESSION_RESPONSE)
	{

	}

	return 0;
}