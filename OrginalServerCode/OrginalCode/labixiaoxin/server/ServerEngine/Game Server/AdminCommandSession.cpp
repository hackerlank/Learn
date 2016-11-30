#include "AdminCommandSession.h"
#include "..\Base\Service\BaseAdapter.h"
#include "json\json.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\Base\Communication\ServiceEndPoint.h"
#include "ServerCommandEndPoint.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"
#include "..\Base\Service\BaseService.h"
#include "AdminCommandMgr.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\Protocol\DBProtocol.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


#define MAX_ADMIN_COMMAND_SESSION_LIVE 30

ACE_UINT32 AdminCommandSession::m_unUserInfoServerID = 0;

AdminCommandSession::AdminCommandSession(ACE_UINT32 unID, BaseAdapter *parent)
:BaseObj(unID, parent)
{
	m_bNeedCreateStep = false;
	m_unLiveCounter = 0;

	m_bDoTimeout = true;
	if(m_unUserInfoServerID == 0)
	{
		m_unUserInfoServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test User Info Server");
	}
}

AdminCommandSession::~AdminCommandSession()
{

}

//后台命令入口
int AdminCommandSession::deal_msg(MessageInfo &msgInfo)
{
	_try
	{
		if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) != 0)
		{
			//m_unDealID = msgInfo.s_head->srcAdr.unObjID;

			if(deal_client_msg(msgInfo) == 0)//开始处理分发消息
			{

			}
			else
			{
				//send_fail_msg(-1);
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

		ACE_Message_Block *msg = parse_into_internet_msg(msgInfo);


		if(msg != NULL)
		{
			if(send_msg_2_internet(msg) == -1)
			{
				msg->release();
			}

			return 0;
		}

		return BaseObj::deal_msg(msgInfo);

	}
	__except(puts("exception error"),1)
	{
		FILE *_fp;
		char file_name[64];
		char day_str[32];
		GameUtils::get_current_day_str(day_str);
		ACE_OS::sprintf(file_name, "loginfo/error-%s.txt",day_str);
		_fp = ACE_OS::fopen(file_name, "a");
		if (_fp)
		{
			GameUtils::get_current_time_str(day_str);
			ACE_OS::fprintf(_fp, "Memory crash--- %s\n", day_str);
			ACE_OS::fclose(_fp);
			_fp = NULL;
		}

		printf("gameserver memory error ------\n");
	}

	return -1;
}

ACE_Message_Block *AdminCommandSession::parse_into_internet_msg(MessageInfo &msgInfo)
{
	ACE_Message_Block *msg = NULL;
	int nRet = -1;
	//int size;

	Json::FastWriter fast_writer;
	Json::Value root;

	int i;

	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_GET_SERVICE_STATUS_RESPONSE:
			{
				MsgGetServiceStatusResponse *body = (MsgGetServiceStatusResponse *)msgInfo.body;
				root["status"] = Json::Value(body->unStatus);
				root["info"] = Json::Value(body->info);

				nRet = 0;
			}
			break;
		}
	}
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_ADMIN_OP_RESPONSE:
			{
				MsgAdminOpResponse *body = (MsgAdminOpResponse *)msgInfo.body;
				root["result"] = Json::Value(body->nResult);
				nRet = 0;
			}
			break;
		case MSG_CHARACTER_INFO_RESPONSE:
			{
				MsgCharacterInfoResponse *body = (MsgCharacterInfoResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["name"] = Json::Value(body->name);
				root["level"] = Json::Value(body->unLevel);
				root["exp"] = Json::Value(body->unExp);
				root["coin"] = Json::Value(body->unCoin);
				root["money"] = Json::Value(body->unMoney);
				root["power_point"] = Json::Value(body->unPowerPoint);
				root["frienship"] = Json::Value(body->unFriendship);
				root["DynamicEnergy"] = Json::Value(body->unDynamicEnergy);
				root["login_count"] = Json::Value(body->unLoginCount);
				root["login_bonus_count"] = Json::Value(body->unLoginBonusCount);
				root["energy"] = Json::Value(body->unEnergy);
				root["recharge_count"] = Json::Value(body->unRechargeCount);
				root["recharge_amount"] = Json::Value(body->unRechargeAmount);
				root["package_max"] = Json::Value(body->unPackageMax);

				nRet = 0;
			}
			break;
		case MSG_PACKAGE_INFO_RESPONSE:
			{
				MsgPackageInfoResponse *body = (MsgPackageInfoResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["count"] = Json::Value(body->unCount);

				Json::Value arrayObj;

				for(i = 0;i < body->unCount;i ++)
				{
					Json::Value node;

					node["idx"] = Json::Value(body->list[i].unIdx);
					node["item_id"] = Json::Value(body->list[i].item.item.unResID);
					node["level"] = Json::Value(body->list[i].item.item.info.equipment.unLevel);
					node["step"] = Json::Value(body->list[i].item.item.info.equipment.unStep);

					arrayObj.append(node);
				}

				root["list"] = arrayObj;

				nRet = 0;
			}
			break;
		case MSG_PLAYER_INFO_RESPONSE:
			{
				MsgPlayerInfoResponse *body = (MsgPlayerInfoResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["count"] = Json::Value(body->unCount);

				{
					Json::Value arrayObj;

					for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
					{
						arrayObj.append(Json::Value(body->selectedList[i]));
					}

					root["list_selected"] = arrayObj;
				}

				{
					Json::Value arrayObj;

					for(i = 0;i < body->unCount;i ++)
					{
						Json::Value node;

						node["item_id"] = Json::Value(body->playerList[i].unItemID);
						node["level"] = Json::Value(body->playerList[i].unLevel);

						arrayObj.append(node);
					}

					root["list"] = arrayObj;
				}

				nRet = 0;
			}
			break;
			/*
		case MSG_EQUIPMENT_INFO_RESPONSE:
			{
				MsgEquipmentInfoResponse *body = (MsgEquipmentInfoResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["count"] = Json::Value(body->unCount);

				Json::Value arrayObj;

				for(i = 0;i < body->unCount;i ++)
				{
					Json::Value node;

					node["item_id"] = Json::Value(body->equipmentList[i].item.item.unResID);
					node["level"] = Json::Value(body->equipmentList[i].item.item.info.equipment.unLevel);
					node["step"] = Json::Value(body->equipmentList[i].item.item.info.equipment.unStep);

					arrayObj.append(node);
				}

				root["list"] = arrayObj;

				nRet = 0;
			}
			break;
			*/
		case MSG_FUNCTION_LIST_RESPONSE:
			{
				MsgFunctionListResponse *body = (MsgFunctionListResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["count"] = Json::Value(body->unCount);

				Json::Value arrayObj;

				for(i = 0;i < body->unCount;i ++)
				{
					arrayObj.append(Json::Value(body->list[i]));
				}

				root["list"] = arrayObj;

				nRet = 0;
			}
			break;
		case MSG_SKILL_LIST_RESPONSE:
			{
				MsgSkillListResponse *body = (MsgSkillListResponse *)msgInfo.body;

				root["result"] = Json::Value(body->nResult);
				root["count"] = Json::Value(body->unCount);

				Json::Value arrayObj;

				for(i = 0;i < body->unCount;i ++)
				{
					arrayObj.append(Json::Value(body->skillList[i]));
				}

				root["list"] = arrayObj;

				nRet = 0;
			}
			break;
		}
	}

	if(nRet == 0)
	{
		std::string str = fast_writer.write(root);
		send_msg_2_internet(str.c_str());
	}

	return NULL;
}

int AdminCommandSession::deal_client_msg(MessageInfo &msgInfo)
{
	Json::Reader reader;
	Json::Value json_object;

	if(!reader.parse((char *)msgInfo.body, json_object))//转换成json
	{
		return -1;
	}

	char *msg_str = (char *)msgInfo.body;

	printf("server command msg = %s\n", msg_str);

	static char *null_str = "";

	/*
	const char *type = json_object["type"].asCString();
	const char *key = json_object["key"].asCString();
	*/
	const char *type = null_str;
	const char *key = null_str;

	if(!json_object["type"].isNull() && !json_object["key"].isNull())
	{
		type = json_object["type"].asCString();
		key = json_object["key"].asCString();
	}

	if(ACE_OS::strcmp(type, "adjust_utc") != 0)
	{
		AdminCommandMgr *adapter = (AdminCommandMgr *)this->m_ParentAdapter;

		if(!adapter->is_valid_key(key))
		{
			printf("invalid key[%s]\n", key);
			send_fail_msg(-1);
			return -1;
		}
	}

	Json::FastWriter fast_writer;
	Json::Value root;

	int nRet = -1;

	int i;

	if(ACE_OS::strcmp(type, "get_service_list") == 0)//获取服务器列表
	{
		ServiceConfigMgr *serviceConfigMgr = SERVICE_CONFIG_MGR_INSTANCE::instance();

		root["count"] = serviceConfigMgr->m_unServiceInstanceCount;

		Json::Value arrayObj;

		for(i = 0;i < serviceConfigMgr->m_unServiceInstanceCount;i ++)
		{
			ServiceInstanceInfo *info = &serviceConfigMgr->m_serviceInstanceList[i];

			Json::Value node;
			node["service_id"] = Json::Value(info->unID);

			{
				Json::Value addr_info;
				addr_info["ip"] = Json::Value(info->lanAdr.ip);
				addr_info["port"] = Json::Value(info->lanAdr.port);
				node["lan"] = addr_info;
			}

			{
				Json::Value addr_info;
				addr_info["ip"] = Json::Value(info->wlanAdr.ip);
				addr_info["port"] = Json::Value(info->wlanAdr.port);
				node["wlan"] = addr_info;
			}

			{
				Json::Value addr_info;
				addr_info["ip"] = Json::Value(info->publicAdr.ip);
				addr_info["port"] = Json::Value(info->publicAdr.port);
				node["public"] = addr_info;
			}
	
			arrayObj.append(node);
		}

		root["list"] = arrayObj;

		nRet = 0;

		//std::string str = fast_writer.write(root);
		//send_msg_2_internet(str.c_str());
		
		
	}
	else if(ACE_OS::strcmp(type, "get_service_status") == 0)//获取服务器状态
	{
		unsigned int service_id = 0;

		if(!json_object["service_id"].isNull())
		{
			service_id = json_object["service_id"].asUInt();
		}

		if(service_id != 0 && is_service_on(service_id))
		{
			MsgGetServiceStatusRequest request;
			request.unFlag = 0;

			if(sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_GET_SERVICE_STATUS_REQUEST, (char *)&request, sizeof(MsgGetServiceStatusRequest), service_id, OBJ_ID_NONE, OBJ_ID_NONE) == -1)
			{
				//send fail
				send_fail_msg(-1);
				return -1;
			}
		}
		else
		{
			root["status"] = Json::Value(0);
			root["info"] = Json::Value("");

			nRet = 0;
		}
	}
	else if(ACE_OS::strcmp(type, "is_service_on") == 0)//服务器是否在线
	{
		unsigned int service_id = 0;

		if(!json_object["service_id"].isNull())
		{
			service_id = json_object["service_id"].asUInt();
		}

		if(service_id != 0 && is_service_on(service_id))
		{
			root["status"] = Json::Value(1);
		}
		else
		{
			root["status"] = Json::Value(0);
		}

		nRet = 0;
	}
	else if(ACE_OS::strcmp(type, "close_server") == 0)//关闭服务器
	{
		unsigned int service_id = 0;

		if(!json_object["service_id"].isNull())
		{
			service_id = json_object["service_id"].asUInt();
		}
		
		if(service_id != 0)
		{
			if(sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_SERVICE_SHUTDOWN, NULL, 0, service_id, OBJ_ID_NONE, OBJ_ID_NONE) == -1)
			{
				
			}
		}

		/*
		int t = service_id & 0xffffff;
		int type = GET_SERVICE_TYPE(service_id);

		if(t == 0)
		{
			
		}
		else
		{
			
		}
		*/
		

		root["result"] = Json::Value(0);

		nRet = 0;
	}
	else if(ACE_OS::strcmp(type, "stop_service") == 0)//停止服务器
	{
		unsigned int service_id = 0;

		if(!json_object["service_id"].isNull())
		{
			service_id = json_object["service_id"].asUInt();
		}

		if(service_id != 0)
		{
			if(sendMsg(SERVICE_MESSAGE_TYPE_CTRL, MSG_SERVICE_STOP_SERVICE, NULL, 0, service_id, OBJ_ID_NONE, OBJ_ID_NONE) == -1)
			{
				
			}
		}

		root["result"] = Json::Value(0);

		nRet = 0;
	}
	else if(ACE_OS::strcmp(type, "adjust_utc") == 0)//时间校准
	{
		root["result"] = Json::Value(0);
		root["utc"] = Json::Value(GameUtils::get_utc());
		root["self"].append(Json::Value(100));
		root["self"].append(root);
		nRet = 0;
	}
	else if(ACE_OS::strcmp(type, "op_character") == 0)//操作人物相关
	{
		MsgAdminOPRequest request;

		ACE_OS::memset(&request, 0, sizeof(MsgAdminOPRequest));

		if(!json_object["op_type"].isNull() && !json_object["character_id"].isNull() )
		{
			request.unOpType = json_object["op_type"].asInt();
			request.unCharacterID = json_object["character_id"].asInt();

			request.unParamCount = 0;

			if (!json_object["param_list"].isNull())
			{
				Json::Value param_list = json_object["param_list"];
				for(i = 0;i < param_list.size();i ++)
				{
					request.paramList[i] = param_list[i].asInt();
				}
				request.unParamCount = param_list.size();
			}


			//xxj 2015/04/22  14:43:52 
			//添加缓存数据
			//内容
			if (!json_object["param_buffer"].isNull())
			{
				std::string strBuffer = json_object["param_buffer"].asString();
				int iSize = strBuffer.size() > MAIL_BODY_LEN ? MAIL_BODY_LEN : strBuffer.size();
				memcpy(request.strBuffer, strBuffer.c_str(), iSize);
				request.unBufferLen = iSize;
			}

			//标题
			if (!json_object["param_title"].isNull())
			{
				std::string strBuffer = json_object["param_title"].asString();
				int iSize = strBuffer.size() > MAIL_TITLE_LEN ? MAIL_TITLE_LEN : strBuffer.size();
				memcpy(request.strTitle, strBuffer.c_str(), iSize);
			}
			//------------------------------------------------------------------------

			switch(request.unOpType)//默认所有都发送，避免繁琐判断
			{
			default:
				sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_REQUEST, (char *)&request, sizeof(MsgAdminOPRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID);
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_REQUEST, (char *)&request, sizeof(MsgAdminOPRequest), OBJ_ID_NONE, ADAPTER_DB_HOME_MGR, request.unCharacterID);
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_REQUEST, (char *)&request, sizeof(MsgAdminOPRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, request.unCharacterID);
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_REQUEST, (char *)&request, sizeof(MsgAdminOPRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
				send_fail_msg(0);
				return 0;
			}
		}
		else
		{
			send_fail_msg(-1);
			return -1;
		}
	}
	else if (ACE_OS::strcmp(type, "admin_buffer_op") == 0)//先不考虑用base64 acu,pcu //数据统计
	{
		MsgAdminOPBufferRequest request;

		ACE_OS::memset(&request, 0, sizeof(MsgAdminOPBufferRequest));

		if(!json_object["op_type"].isNull() /*&& !json_object["character_id"].isNull()*/ && !json_object["param_buffer"].isNull()&& !json_object["param_list"].isNull())
		{
			request.unOpType = json_object["op_type"].asInt();
			std::string strBuffer = json_object["param_buffer"].asString();
			int iSize = strBuffer.size() > MAX_ADMIN_OP_BUFFER_LENGTH ? MAX_ADMIN_OP_BUFFER_LENGTH : strBuffer.size();
			memcpy(request.strBuffer, strBuffer.c_str(), iSize);
			request.unBufferLen = iSize;

			Json::Value param_list = json_object["param_list"];

			for(i = 0;i < param_list.size();i ++)
			{
				request.paramList[i] = param_list[i].asInt();
			}

			request.unParamCount = param_list.size();
			switch(request.unOpType)
			{
			default:
				//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID);
				sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_DB_HOME_MGR, m_unID);
				//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unID);
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
				send_fail_msg(0);
				return 0;
			}
		}
		else
		{
			send_fail_msg(-1);
			return -1;
		}
	}
	else if(ACE_OS::strcmp(type, "find_account") == 0)//查询用户
	{
		MsgDBGetAccountInfoRequest oGetAccountInfoRequest;
		oGetAccountInfoRequest.dwFindType = json_object["find_type"].asInt();
		strcpy(oGetAccountInfoRequest.name, json_object["name"].asCString());
		if(sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_GET_ACCOUNT_INFO, (char *)&oGetAccountInfoRequest, sizeof(MsgDBGetAccountInfoRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID) == -1)
		{
			//send fail
			send_fail_msg(-1);
			return -1;
		}
		return 0;
	}
	else if(ACE_OS::strcmp(type, "get_account_list") == 0)//获取用户列表
	{
// 		//---------------------------------------------------------
// 		//by Test
// 		MsgAdminOPBufferRequest request;
// 		ACE_OS::memset(&request, 0, sizeof(MsgAdminOPBufferRequest));
// 		request.unOpType = ADMIN_OP_TYPE_STATISTICS;
// 		std::string strBuffer = "2015-04-15";
// 		int iSize = strBuffer.size() > MAX_ADMIN_OP_BUFFER_LENGTH ? MAX_ADMIN_OP_BUFFER_LENGTH : strBuffer.size();
// 		memcpy(request.strBuffer, strBuffer.c_str(), iSize);
// 		request.unBufferLen = iSize;
// 
// 		request.paramList[0] = E_Statistics_Effect_Register;
// 		request.paramList[1] = 20;
// 		request.paramList[2] = 10;
// 
// 		request.unParamCount = 2;
// 		switch(request.unOpType)
// 		{
// 		default:
// 			//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID);
// 			sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_DB_HOME_MGR, m_unID);
// 			//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unID);
// 			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
// 			send_fail_msg(0);
// 			return 0;
// 		}
// 
// 		return 0;
// 		//-------------------------------------------------------
		MsgDBQueryAccountListRequest oQueryAccountListRequest;
		if(json_object["find_type"].isInt())
			oQueryAccountListRequest.dwFindType = json_object["find_type"].asInt();
		else
		{
			printf("get_account_list: find_type is not Int\n");
			send_fail_msg(-1);
			return -1;
		}
		oQueryAccountListRequest.name[0] = '\0';
		if(json_object["name"].isString())
			strcpy(oQueryAccountListRequest.name, json_object["name"].asCString());
		else
		{
			printf("get_account_list: name is not String\n");
			send_fail_msg(-1);
			return -1;
		}
		if(sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_QUERY_ACCOUNT_LIST, (char *)&oQueryAccountListRequest, sizeof(MsgDBQueryAccountListRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID) == -1)
		{
			//send fail
			send_fail_msg(-1);
			return -1;
		}
		return 0;
	}
	else if (ACE_OS::strcmp(type, "get_log_info") == 0)//获取日志信息
	{
		MsgDBAdminLogInfoRequest logInfoRequest;
		logInfoRequest.m_unType = json_object["m_unType"].asInt();
		logInfoRequest.m_unUserID = json_object["m_unUserID"].asInt();
		logInfoRequest.m_unLevel = json_object["m_unLevel"].asInt();
		logInfoRequest.m_goodsID = json_object["m_goodsID"].asInt();
		logInfoRequest.m_op_action = json_object["m_op_action"].asInt();
		logInfoRequest.m_pageNum = json_object["m_pageNum"].asInt();
		logInfoRequest.m_pageNum -=1;
		if (logInfoRequest.m_pageNum < 0)
			logInfoRequest.m_pageNum = 0;

		if(sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_ADMINCOMMAND_LOG_INFO_REQUEST, (char *)&logInfoRequest, 
			sizeof(MsgDBAdminLogInfoRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID) == -1)
		{
			//send fail
			send_fail_msg(-1);
			return -1;
		}
		return 0;
	}
	else if (ACE_OS::strcmp(type, "set_recharge_info") == 0)//充值请求//
	{
		if (!json_object["order_id"].isNull())
		{
			std::string str = fast_writer.write(root);
			printf("----------%s\n",str.c_str());
			MsgDBAdminRechargeRequest rechargeRequest;
			ZeroVar(rechargeRequest);
			std::string strBuffer = json_object["order_id"].asString();
			int iSize = strBuffer.size() > RECHARGE_ORDERID_LEN ? RECHARGE_ORDERID_LEN : strBuffer.size();
			memcpy(rechargeRequest.orderID, strBuffer.c_str(), iSize);

			strBuffer = json_object["product_count"].asString();//购买数量
			rechargeRequest.unProductCount = ACE_OS::atoi(strBuffer.c_str());

			strBuffer = json_object["amount"].asString();//支付金额
			rechargeRequest.unRenminbi = ACE_OS::atof(strBuffer.c_str());

			strBuffer = json_object["pay_status"].asString();//支付状态
			rechargeRequest.unPayStats = ACE_OS::atoi(strBuffer.c_str());

			strBuffer = json_object["pay_time"].asString();//处理时间
			iSize = strBuffer.size() > 32 ? 32 : strBuffer.size();
			memcpy(rechargeRequest.deal_time, strBuffer.c_str(), iSize);
			
			strBuffer = json_object["user_id"].asString();//用户系统id
			rechargeRequest.unCharacterID = ACE_OS::atoi(strBuffer.c_str());

			strBuffer = json_object["product_id"].asString();//商品id
			rechargeRequest.unProductId = ACE_OS::atoi(strBuffer.c_str());
			
			strBuffer = json_object["channel_number"].asString();//渠道号
			iSize = strBuffer.size() > RECHARGE_CHANNEL_LEN ? RECHARGE_CHANNEL_LEN : strBuffer.size();
			memcpy(rechargeRequest.strChannel, strBuffer.c_str(), iSize);

			if(sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_ADMINCOMMAND_RECHARGE_INFO_REQUEST, (char *)&rechargeRequest, 
				sizeof(MsgDBAdminRechargeRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID) == -1)
			{
				//send fail
				send_fail_msg(-1);
				return -1;
			}

			return 0;
		}
		else
			return -1;
	}
// 	else if (ACE_OS::strcmp(type,"send_announcement_info")==0)//公告模块
// 	{
// 		MsgDBAdminAnnouncementRequest request;
// 
// 		ACE_OS::memset(&request, 0, sizeof(MsgDBAdminAnnouncementRequest));
// 
// 		if(!json_object["op_type"].isNull() /*&& !json_object["character_id"].isNull()*/ && !json_object["param_buffer"].isNull()&& !json_object["param_list"].isNull())
// 		{
// 			request.m_unOpType = json_object["op_type"].asInt();
// 			std::string strBuffer = json_object["param_buffer"].asString();
// 			int iSize = strBuffer.size() > MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH ? MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH : strBuffer.size();
// 			memcpy(request.m_strBuffer, strBuffer.c_str(), iSize);
// 			request.m_unCount = iSize;
// 
// 			switch(request.m_unOpType)
// 			{
// 			default:
// 				//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_ADMINCOMMAND_Announcement_REQUEST, (char *)&request, sizeof(MsgDBAdminAnnouncementRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID);
// 				//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_ADMINCOMMAND_Announcement_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_DB_HOME_MGR, m_unID);
// 				//sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_ADMIN_OP_BUFFER_REQUEST, (char *)&request, sizeof(MsgAdminOPBufferRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unID);
// 				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_ADMINCOMMAND_Announcement_REQUEST, (char *)&request, sizeof(MsgDBAdminAnnouncementRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
// 				send_fail_msg(0);
// 				return 0;
// 			}
// 		}
// 		else
// 		{
// 			send_fail_msg(-1);
// 			return -1;
// 		}
// 	}
	else
	{
		send_fail_msg(-1);
		return -1;
	}

	if(nRet == 0)
	{
		std::string str = fast_writer.write(root);
		send_msg_2_internet(str.c_str());
	}

	return 0;
}

int AdminCommandSession::send_msg_2_internet(const char *str)
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

int AdminCommandSession::send_msg_2_internet(ACE_Message_Block *msg)
{
	return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_TCP_PHP, &m_unID, msg);
}

void AdminCommandSession::send_fail_msg(int errorCode)
{
	Json::FastWriter fast_writer;

	Json::Value root;
	root["result"] = Json::Value(errorCode);

	std::string str = fast_writer.write(root);
	
	send_msg_2_internet(str.c_str());
}

bool AdminCommandSession::is_service_on(ACE_UINT32 unServiceID)
{
	ServiceEndPoint *endPoint = (ServiceEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_SERVICE);

	if(endPoint == NULL)
	{
		return false;
	}

	if(unServiceID == BaseService::instance()->m_ownServiceInfo->unID)
	{
		return true;
	}

	return endPoint->is_service_on(unServiceID);
}

void AdminCommandSession::obj_timeout()
{
	if(m_unLiveCounter >= MAX_ADMIN_COMMAND_SESSION_LIVE)
	{
		//this->setObjStatus(SERVICE_OBJ_DESTROY);
		this->set_destroy(true);
	}
	else
	{
		m_unLiveCounter ++;
	}

	//printf("-------------AdminCommandSession time out:[%d]\n",m_unLiveCounter);
}

int AdminCommandSession::start_destroy()
{
	PhpEndPoint *endpoint = (PhpEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_PHP);

	if(endpoint != NULL)
	{
		endpoint->delete_peer(m_unID);
	}

	return BaseObj::start_destroy();
}

int AdminCommandSession::deal_db_msg( ACE_UINT32 unType, void *msg )
{
	/*printf("get db msg type = 0x%08x\n", unType);*/

	Json::FastWriter fast_writer;
	Json::Value root;

	switch(unType)
	{
	case MSG_DB_GET_ACCOUNT_INFO:
		{
			MsgDBAccountInfoResponse *body = (MsgDBAccountInfoResponse *)msg;
			if(body->nResult != 0)
			{
				send_fail_msg(body->nResult);
				return SERVICE_OBJ_DB_REQUEST_DONE;
			}

			body->m_oBasicInfos.ToJson(root["BasicInfos"]);
			body->m_oItemInfos.ToJson(root["ItemInfos"]);
			body->m_oPlayerInfos.ToJson(root["PlayerInfos"]);

			std::string str = fast_writer.write(root);
			send_msg_2_internet(str.c_str());
		}
		break;
	case MSG_DB_QUERY_ACCOUNT_LIST:
		{
			MsgDBQueryAccountListResponse *body = (MsgDBQueryAccountListResponse*)msg;
			if(body->nResult != 0)
			{
				send_fail_msg(body->nResult);
				return SERVICE_OBJ_DB_REQUEST_DONE;
			}
			body->m_oAccountList.ToJson(root);

			std::string str = fast_writer.write(root);
			send_msg_2_internet(str.c_str());
		}
		break;
// 	case MSG_DB_ADMIN_STATISTICS_REQ:
// 		{
// 			MsgDBAdminStatisticsResponse *body = (MsgDBAdminStatisticsResponse*)msg;
// 			root["Data"] = body->unData;
// 			root["Type"] = body->unStatisticsType;
// 			std::string str = fast_writer.write(root);
// 			send_msg_2_internet(str.c_str());
// 		}break;
	case MSG_DB_GET_DATA_STATISTICS://统计
		{
			MsgDBGetStatisticsResponse *body = (MsgDBGetStatisticsResponse*)msg;
			root["unType"] = body->unType;
			root["unData"] = body->unData;
			std::string str = fast_writer.write(root);
			send_msg_2_internet(str.c_str());
		}break;
	case MSG_DB_ADMINCOMMAND_LOG_INFO_RESPONSE://log信息
		{
			//ACE_UINT32  m_unCount;
			//LogItemInfo m_logInfoItem[MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT];
			MsgDBAdminLogInfoResponse *body = (MsgDBAdminLogInfoResponse*)msg;
			root["m_unCount"] = body->m_unCount;
			for(int i=0;i<body->m_unCount;i++)
			{
				GetLogInfoItemJson(body->m_logInfoItem[i],root["m_logInfoItem"][(Json::UInt)i]);
			}
			std::string str = fast_writer.write(root);
			send_msg_2_internet(str.c_str());
		}
		break;
	case MSG_DB_ADMINCOMMAND_RECHARGE_INFO_RESPONSE://充值信息返回
		{
			MsgDBAdminRechargeResponse * body = (MsgDBAdminRechargeResponse*)msg;
			root["orderID"] = body->orderID;
			root["unErrorflag"] = body->unErrorflag;
			std::string str = fast_writer.write(root);
			send_msg_2_internet(str.c_str());
		}break;
	//case MSG_DB_
	}
	return SERVICE_OBJ_DB_REQUEST_DONE;
}

void AdminCommandSession::GetLogInfoItemJson( const LogItemInfo & logInfo,Json::Value & root )
{
	root["m_unUserID"] = logInfo.m_unUserID;
	root["m_name"] = logInfo.m_name;
	root["m_unLevel"] = logInfo.m_unLevel;
	root["m_unChannel"] = logInfo.m_unChannel;
	root["m_goodsID"] = logInfo.m_goodsID;
	root["m_op_action"] = (int)logInfo.m_op_action;
	root["m_op_way"] = logInfo.m_op_way;
	root["m_unType"] = (int)logInfo.m_unType;
	root["m_op_before"] = logInfo.m_op_before;
	root["m_op_after"] = logInfo.m_op_after;
	root["m_op_involve"] = logInfo.m_op_involve;
	root["m_op_time"] = logInfo.m_op_time;
}
