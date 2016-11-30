#include "ClientObj.h"
#include "..\..\Base\Communication\CommunicationMgr.h"
#include "..\Game Network\ClientEndPoint.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ClientObj::ClientObj(ACE_UINT32 unID, BaseAdapter *parent)
:SubAdapterObj(unID, parent)
{
	
}

ClientObj::~ClientObj()
{

}

int ClientObj::deal_msg(MessageInfo &msgInfo)
{
	ACE_Message_Block *msg;
	if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) != 0)
	{
		//翻译成内网的消息，传给
		MessageInfo info;
		if(parse_into_intranet_msg(info, (char *)msgInfo.body, msgInfo.nBodySize) == 0)
		{
			//处理该消息
			deal_client_msg(info);

			info.msg->release();
		}
		else
		{
			ClientEndPoint *endpoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

			if(endpoint != NULL)
			{
				ClientPeer *peer = endpoint->find_peer(m_unID);
				if(peer != NULL)
				{
					peer->remove_all_connection();
				}
			}
		}

		return 0;
	}
	else
	{
		//如果可以翻译成外网的消息，传给底层发送
		msg = parse_into_internet_msg(msgInfo);

		if(msg != NULL)
		{
			if(send_msg_2_internet(msg) == -1)
			{
				msg->release();
			}

			return 0;
		}
		else
		{
			return deal_other_msg(msgInfo);
		}
	}

	return BaseObj::deal_msg(msgInfo);
}

ACE_Message_Block *ClientObj::create_send_msg(int size)
{
	ACE_Message_Block *msg = new ACE_Message_Block(sizeof(ACE_UINT32) + size);

	return msg;
}

int ClientObj::set_send_size(ACE_Message_Block *msg, int size)
{
	if(msg == NULL)
	{
		return -1;
	}
	if(msg->size() < size)
	{
		return -1;
	}

	msg->rd_ptr(msg->base());
	msg->wr_ptr(msg->base() + size);

	return 0;
}

int ClientObj::send_msg_2_internet(ACE_Message_Block *msg)
{
	return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_TCP_INTERNET, &m_unID, msg);
}