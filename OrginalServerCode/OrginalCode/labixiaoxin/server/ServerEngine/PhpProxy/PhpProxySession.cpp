#include "PhpProxySession.h"
#include "json\json.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"
#include "..\Base\Service\ServiceConfigMgr.h"

ACE_UINT32 PhpProxySession::m_unGameServerID = 0;
ACE_UINT32 PhpProxySession::m_unUserInfoServerID = 0;

#define MAX_PHP_SESSION_LIVE 60

PhpProxySession::PhpProxySession(ACE_UINT32 unID, BaseAdapter *parent)
:SubAdapterObj(unID, parent)
{
	m_unLiveCounter = 0;
	m_bNeedCreateStep = false;

	m_bDoTimeout = true;

	if(m_unGameServerID == 0)
	{
		m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
		m_unUserInfoServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test User Info Server");
	}
}

PhpProxySession::~PhpProxySession()
{

}

int PhpProxySession::deal_msg(MessageInfo &msgInfo)
{
	ACE_Message_Block *msg;
	if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) != 0)
	{
		if(deal_client_msg(msgInfo) == 0)
		{
			
		}
		else
		{
			send_fail_msg(-1);
			/*
			PhpEndPoint *endpoint = (PhpEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

			if(endpoint != NULL)
			{
				//close connection
			}
			*/
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

int PhpProxySession::deal_client_msg(MessageInfo &msgInfo)
{
	//login
	//uid:123456
	//return ip,port,uid,session

	//get basic info list
	//uid:123456,uid:123456
	//return name:dsf,c_id,lv

	Json::Reader reader;
	Json::Value json_object;

	if(!reader.parse((char *)msgInfo.body, json_object))
	{
		return -1;
	}

	char *msg_str = (char *)msgInfo.body;

	/*printf("login msg = %s\n", msg_str);*/

	static char *null_str = "";

	const char *type = null_str;

	if(!json_object["type"].isNull())
	{
		type = json_object["type"].asCString();
	}

	//const char *type = json_object["type"].asCString();

	if(ACE_OS::strcmp(type, "purchase") == 0)
	{
		if(!json_object["purchase_id"].isNull() && !json_object["character_id"].isNull())
		{
			unsigned int purchase_id = json_object["purchase_id"].asUInt();
			unsigned int character_id = json_object["character_id"].asUInt();

			MsgPurchaseRequest request;
			request.unPurchaseID = purchase_id;

			if(sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PURCHASE_GOLD_REQUEST, (char *)&request, sizeof(MsgPurchaseRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, character_id) == -1)
			{
				//send fail
				send_fail_msg(-1);
				return -1;
			}
		}
		else
		{
			send_fail_msg(-1);
			return -1;
		}
	}
	else if(ACE_OS::strcmp(type, "bind_success") == 0)
	{
		if(!json_object["user_id"].isNull() && !json_object["character_id"].isNull())
		{
			unsigned int user_id = json_object["user_id"].asUInt();
			unsigned int character_id = json_object["character_id"].asUInt();

			MsgBindSuccessRequest request;
			request.unUserID = user_id;

			if(sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_BIND_SUCCESS_REQUEST, (char *)&request, sizeof(MsgBindSuccessRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, character_id) == -1)
			{
				//send fail
				send_fail_msg(-1);
				return -1;
			}
		}
		else
		{
			send_fail_msg(-1);
			return -1;
		}
	}

	return 0;
}

ACE_Message_Block *PhpProxySession::parse_into_internet_msg(MessageInfo &msgInfo)
{
	ACE_Message_Block *msg = NULL;
	int nRet = -1;
	//int size;

	Json::FastWriter fast_writer;
	Json::Value root;

	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_PURCHASE_GOLD_RESPONSE:
			{
				MsgMsgPurchaseResponse *body = (MsgMsgPurchaseResponse *)msgInfo.body;
				root["result"] = Json::Value(body->nResult);
				nRet = 0;
			}
			break;
		case MSG_BIND_SUCCESS_RESPONSE:
			{
				send_fail_msg(0);
			}
			break;
			/*
		case MSG_DELIVER_GOODS_RESPONSE:
			{
				MsgDeliverGoodsResponse *body = (MsgDeliverGoodsResponse *)msgInfo.body;
				root["result"] = body->nResult;
				root["amount"] = body->nAmount;
				nRet = 0;
			}
			break;
			*/
		}
	}

	if(nRet == 0)
	{
		std::string str = fast_writer.write(root);
		send_msg_2_internet(str.c_str());
	}

	return NULL;
}

int PhpProxySession::deal_other_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		/*
		switch(msgInfo.m_head->unType)
		{
		case MSG_GET_CHARACTER_INFO_RESPONSE:
			{
				MsgGetCharacterInfoResponse *info = (MsgGetCharacterInfoResponse *)msgInfo.body;

				if(info->unCharacterID != 0)
				{
					MsgInviteFriendDone msg;
					msg.unFriendID = 0;

					this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_INVITE_FRIEND_DONE,(char *)&msg, sizeof(MsgInviteFriendDone), OBJ_ID_NONE, ADAPTER_MAP_MGR, info->unCharacterID);
				}
			}
			break;
		}
		*/
	}

	return 0;
}

void PhpProxySession::obj_timeout()
{
	if(m_unLiveCounter >= MAX_PHP_SESSION_LIVE)
	{
		//this->setObjStatus(SERVICE_OBJ_DESTROY);
		this->set_destroy(true);
	}
	else
	{
		m_unLiveCounter ++;
	}
}

int PhpProxySession::start_destroy()
{
	PhpEndPoint *endpoint = (PhpEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_PHP);

	if(endpoint != NULL)
	{
		endpoint->delete_peer(m_unID);
	}

	return SubAdapterObj::start_destroy();
}

int PhpProxySession::send_msg_2_internet(const char *str)
{
	int len = strlen(str) + 1;
	ACE_Message_Block *msg = new ACE_Message_Block(len);

	if(msg == NULL)
	{
		return -1;
	}

	ACE_OS::memcpy(msg->base(), str, len);

	msg->rd_ptr(msg->base());
	msg->wr_ptr(msg->base() + len);

	return send_msg_2_internet(msg);
}

int PhpProxySession::send_msg_2_internet(ACE_Message_Block *msg)
{
	return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_TCP_PHP, &m_unID, msg);
}

void PhpProxySession::send_fail_msg(int errorCode)
{
	Json::FastWriter fast_writer;

	Json::Value root;
	root["result"] = Json::Value(errorCode);

	std::string str = fast_writer.write(root);
	
	send_msg_2_internet(str.c_str());
}