#include "LoginSession.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include "..\GameBase\Game Network\ClientEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#include "..\GameBase\Res\GameConfig.h"

#define MAX_LOGIN_SESSION_LIVE 30

//#define CURRENT_GAME_VERSION 10002

ACE_UINT32 LoginSession::m_unGameServerID = 0;

LoginSession::LoginSession(ACE_UINT32 unID, BaseAdapter *parent)
:ClientObj(unID, parent)
{
	m_unLiveCounter = 0;
	m_bNeedCreateStep = false;

	m_bDoTimeout = true;

	if(m_unGameServerID == 0)
	{
		m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
	}
}

LoginSession::~LoginSession()
{

}

int LoginSession::deal_client_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_LOGIN_REQUEST:
			//验证合法性
			{
				bool flag = true;

				MsgVerifyAccountRequest new_body;
				ZeroVar(new_body);

				MsgLoginRequest *body = (MsgLoginRequest *)msgInfo.body;

				int error_code = 0;

				ACE_UINT32 dwCurrentVersion = GAME_CONFIG_INSTANCE::instance()->m_unCurrentVersion;
				if(body->unVersion >= 100 && body->unVersion != dwCurrentVersion)
				{
					flag = false;
					error_code = ERROR_CODE_VERSION_NOT_MATCH;
				}
				else
				{
					printf("login mac = %s, email = %s, user_id = %d\n", body->mac, body->email, body->unUserID);
					ACE_OS::memcpy(new_body.mac, body->mac, MAX_MAC_LENGTH);
					ACE_OS::memcpy(new_body.email, body->email, MAX_EMAIL_LENGTH);
					new_body.unUserID = body->unUserID;

					if(this->add_db_request(ADAPTER_DB_LOGIN_MGR, MSG_DB_VERIFY_ACCOUNT, (char *)&new_body, sizeof(MsgVerifyAccountRequest)) == -1)
					{
						flag = false;
					}
				}

				if(!flag)
				{
					ACE_Message_Block *msg = create_login_response(error_code, 0, 0, 0, 0);
					if(msg != NULL)
					{
						if(send_msg_2_internet(msg) == -1)
						{
							msg->release();
						}
					}
				}
			}
			break;
		}
	}

	return 0;
}

int LoginSession::deal_db_msg(ACE_UINT32 unType, void *msg)
{
	
	switch(unType)
	{
	case MSG_DB_VERIFY_ACCOUNT:
		{
			MsgVerifyAccountResponse *body = (MsgVerifyAccountResponse *)msg;
			bool flag = false;
			if(body->nResult == 0)
			{
				MsgQueryLoginInfoRequest info;
				info.unLoginID = m_unID;
				info.unUserID = body->unUserID;

				/*printf("login db response = %d\n", body->unUserID);*/

				/*
				if(sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_QUERY_LOGIN_INFO_REQUEST, (char *)&info, sizeof(MsgQueryLoginInfoRequest), m_unGameServerID, ADAPTER_GAME_SERVER_MGR, OBJ_ID_NONE) == 0)
				{
					flag = true;
				}
				*/
				if(sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_QUERY_LOGIN_INFO_REQUEST, (char *)&info, sizeof(MsgQueryLoginInfoRequest), OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, body->unUserID) == 0)
				{
					flag = true;
				}
			}

			if(!flag)
			{
				ACE_Message_Block *msg = create_login_response(body->nResult, 0, 0, 0, 0);
				if(msg != NULL)
				{
					if(send_msg_2_internet(msg) == -1)
					{
						msg->release();
					}
				}
			}
		}
		break;
	}

	return SERVICE_OBJ_DB_REQUEST_DONE;
}


void LoginSession::obj_timeout()
{
	if(m_unLiveCounter >= MAX_LOGIN_SESSION_LIVE)
	{
		//this->setObjStatus(SERVICE_OBJ_DESTROY);
		this->set_destroy(true);
	}
	else
	{
		m_unLiveCounter ++;
	}
	//printf("-------------LoginSession time out:[%d]\n",m_unLiveCounter);
}

int LoginSession::start_destroy()
{
	ClientEndPoint *endpoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

	if(endpoint != NULL)
	{
		endpoint->delete_peer(m_unID);
	}

	return ClientObj::start_destroy();
}

int LoginSession::parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size)
{
	m_stream.reset(buff, size);

	ACE_UINT32 unType;

	if(m_stream.readInt(unType) == -1)
	{
		return -1;
	}

	switch(unType)
	{
	case MSG_LOGIN_REQUEST:
		{
			if(allocMessageWithInfo(msgInfo, sizeof(MsgLoginRequest), SERVICE_MESSAGE_TYPE_USER, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, MSG_LOGIN_REQUEST) == -1)
			{
				return -1;
			}

			MsgLoginRequest *body = (MsgLoginRequest *)msgInfo.body;

			if(m_stream.readInt(body->unVersion) == -1)
			{
				msgInfo.msg->release();
				return -1;
			}

			if(m_stream.readString(body->mac, MAX_MAC_LENGTH) == -1 || m_stream.readString(body->email, MAX_EMAIL_LENGTH) == -1 || m_stream.readInt(body->unUserID) == -1)
			{
				msgInfo.msg->release();
				return -1;
			}

			return 0;
		}
		break;
	}

	return -1;
}

ACE_Message_Block *LoginSession::parse_into_internet_msg(MessageInfo &msgInfo)
{
	ACE_Message_Block *msg = NULL;
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_QUERY_LOGIN_INFO_RESPONSE:
			{
				MsgQueryLoginInfoResponse *body = (MsgQueryLoginInfoResponse *)msgInfo.body;
				printf("login response ip = %d, port = %d, user_id = %d\n", body->unIP, body->unPort, body->unUserID);
				msg = create_login_response(0, body->unIP, body->unPort, body->unUserID, body->strSession);
			}
			break;
		}
	}

	return msg;
}

ACE_Message_Block *LoginSession::create_login_response(int nResult, ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unClientID, char *strSession)
{
	ACE_Message_Block *msg = create_send_msg(sizeof(MsgLoginResponse));
	if(msg == NULL)
	{
		return NULL;
	}

	m_stream.reset(msg->base(), msg->size());

	if(m_stream.writeInt(MSG_LOGIN_RESPONSE) == -1)
	{
		msg->release();
		return NULL;
	}

	if(m_stream.writeInt(nResult) == -1 || m_stream.writeInt(unIP) == -1 || m_stream.writeInt(unPort) == -1 
		|| m_stream.writeInt(unClientID) == -1 || m_stream.writeString(strSession, CLIENT_SESSION_LEN) == -1)
	{
		msg->release();
		return NULL;
	}

	if(set_send_size(msg, m_stream.getCursor()) == -1)
	{
		msg->release();
		return NULL;
	}

	return msg;
}