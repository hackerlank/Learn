#include "GameServerMgr.h"
#include "OnlineClient.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "json\json.h"
#include "..\Base\Communication\ServiceEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "ace\INET_Addr.h"

GameServerMgr::GameServerMgr(ACE_UINT32 unID)
:MainAdapter(unID)
{
	//m_unLiveCounter = 0;
}

GameServerMgr::~GameServerMgr()
{

}

// void GameServerMgr::obj_timeout()
// {
// 	if(m_unLiveCounter >= MAX_GameServer_SESSION_LIVE)
// 	{
// 		//  			this->set_destroy(true);
// 		//this->setObjStatus(SERVICE_OBJ_DESTROY);
// 		m_unLiveCounter = 0;
// 	}
// 	else
// 	{
// 		m_unLiveCounter ++;
// 	}
// 
// 	printf("GameServer timeout status = %d[%d] [%d]\n", this->m_unObjStatus, m_unID,m_unLiveCounter);
// }

/*
BaseObj *GameServerMgr::new_child_obj(ACE_UINT32 unID)
{
	return (new OnlineClient(unID, this));
}
*/

/*
int GameServerMgr::deal_msg(MessageInfo &msgInfo)
{
	
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_QUERY_LOGIN_INFO_REQUEST:
			{
				MsgQueryLoginInfoRequest *body = (MsgQueryLoginInfoRequest *)msgInfo.body;
				//ACE_UINT32 unSessionID = (ACE_UINT32)ACE_OS::rand();

				OnlineClient *pClient = (OnlineClient *)this->findObj(body->unUserID);
				if(pClient == NULL)
				{
					if(this->create_child(body->unUserID, 0, &msgInfo.s_head->srcAdr, sizeof(ObjAdr)) == -1)
					{
						//send login failed
						MsgQueryLoginInfoResponse info;

						info.unIP = 0;
						info.unPort = 0;
						info.unUserID = 0;
						info.strSession[0]= '\0';

						sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_QUERY_LOGIN_INFO_RESPONSE, (char*)&info, sizeof(MsgQueryLoginInfoResponse), msgInfo.s_head->srcAdr);
					}
				}
				else
				{
					pClient->set_login_response_adr(msgInfo.s_head->srcAdr);
				}
			}
			break;
		case MSG_GATEWAY_PROXY_DESTROY_REQUEST:
			{
				MsgDestroyGatewayProxyRequest *body = (MsgDestroyGatewayProxyRequest *)msgInfo.body;

				OnlineClient *pClient = (OnlineClient *)this->findObj(body->unID);

				if(pClient != NULL)
				{
					if(pClient->is_same_login(body->unLoginID))
					{
						this->destroy_child_direct(body->unID);
					}
				}

			}
			break;
		}
	}

	return MainAdapter::deal_msg(msgInfo);
}
*/
