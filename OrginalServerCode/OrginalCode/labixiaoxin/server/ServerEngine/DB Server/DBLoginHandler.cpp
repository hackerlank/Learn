#include "DBLoginHandler.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "DBUserHandler.h"

#define MAX_LOGIN_DB_HANDLER_LIVE 60

DBLoginHandler::DBLoginHandler(ACE_UINT32 unID, BaseAdapter *parent)
:DBHandler(unID, parent)
{
	ACE_OS::strcpy(m_strHandlerName, "login handler");

	m_unLiveCounter = 0;

	m_bDoTimeout = true;
}

void DBLoginHandler::do_db_load(Connection *db_conn)
{
	/*
	MessageInfo msgInfo;

	if(parseMsg(msgInfo, m_msg) == -1)
	{
		return;
	}
	*/
	m_bLoadingSuccess = true;
}

// void DBLoginHandler::obj_timeout()
// {
// 	if(m_unLiveCounter >= MAX_LOGIN_DB_HANDLER_LIVE)
// 	{
// 		//this->setObjStatus(SERVICE_OBJ_DESTROY);
// 		this->set_destroy(true);
// 	}
// 	else
// 	{
// 		m_unLiveCounter ++;
// 	}
// 
// 	printf("-------------DBLoginHandler time out:[%d]\n",m_unLiveCounter);
// }

void DBLoginHandler::do_db_request(Connection *db_conn, MessageInfo &msgInfo)
{
	//printf("%s deal db request\n", m_strHandlerName);

	//PreparedStatement *prep_stmt = NULL;
	//ResultSet *res = NULL;
	switch(msgInfo.m_head->unType)
	{
	case MSG_DB_VERIFY_ACCOUNT:
		{
			MsgVerifyAccountRequest *body = (MsgVerifyAccountRequest *)msgInfo.body;
			ACE_UINT32 unClientID = get_user_id(db_conn, body->mac, body->email, body->unUserID);

			MsgVerifyAccountResponse response;

			response.nResult = -1;
			response.unUserID = 0;

			if(unClientID != 0)
			{
				response.unUserID = unClientID;
				response.nResult = create_character(db_conn, unClientID);
			}

			/*

			if(unClientID == 0)
			{
				_prep_stmt = db_conn->prepareStatement("insert into user_tbl(mac) values(?)");
				_prep_stmt->setString(1, body->mac);
				_prep_stmt->executeUpdate();
				destroy_db_res();

				unClientID = get_user_id(db_conn, body->mac);

				for(int i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
				{
					_prep_stmt = db_conn->prepareStatement("insert into character_tbl(user_id,name,coin,money,last_login_time,login_bonus_count,login_count,create_time,buy_energy_count,buy_energy_time,level,energy,energy_restore_time) values(?,?,0,0,0,0,0,?,0,0,0,0,0)");
					_prep_stmt->setUInt(1, unClientID);
					_prep_stmt->setString(2, GAME_CONFIG_INSTANCE::instance()->m_defaultName);
					_prep_stmt->setUInt(3, GameUtils::get_utc());
					_prep_stmt->executeUpdate();
					destroy_db_res();
				}
			}
			*/

			//response.nResult = 0;
			//response.unUserID = unClientID;

			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_VERIFY_ACCOUNT, (char *)&response, sizeof(MsgVerifyAccountResponse), msgInfo.s_head->srcAdr, 0, false);

		}
		break;
	}
}

void DBLoginHandler::update_cache(MessageInfo &msgInfo)
{

}

ACE_UINT32 DBLoginHandler::get_user_id(Connection *db_conn, char *mac, char *email, ACE_UINT32 unUserID)
{
	ACE_UINT32 ret = 0;
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select user_id from user_tbl where mac=? and email=?");
	_prep_stmt->setString(1, mac);
	_prep_stmt->setString(2, email);
	//_prep_stmt->setInt(3, unUserID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res->next())
	{
		ret= _db_res->getUInt("user_id");
	}

	destroy_db_res(_prep_stmt,_db_res);

	return ret;
}

int DBLoginHandler::create_character(Connection *db_conn, ACE_UINT32 unUserID)
{
	LogItemInfo info;
	bool flag = false;
	ACE_UINT32 character_id = 0,account_flag = 0;
	
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select character_id,account_flag from character_tbl where user_id=?");
	_prep_stmt->setInt(1, unUserID);
	_db_res = _prep_stmt->executeQuery();
	
	//sql::SQLString emailStr;

	if(_db_res->next())
	{
		character_id= _db_res->getUInt("character_id");
		account_flag = _db_res->getUInt("account_flag");
		//emailStr = _db_res->getString("email");
		flag = true;
	}

	destroy_db_res(_prep_stmt,_db_res);

	if(flag)
	{
		if(account_flag > GameUtils::get_utc())//封停
			return ERROR_MSG_TING_FENG;
		else
			return 0;
	}

	flag = false;

	//sql::SQLString emailStr;
	_prep_stmt = db_conn->prepareStatement("select email from user_tbl where user_id=?");
	_prep_stmt->setInt(1, unUserID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res->next())
	{
		//ret= _db_res->getUInt("user_id");
		//emailStr = _db_res->getString("email");
		flag = true;
	}

	destroy_db_res(_prep_stmt,_db_res);

	if(!flag)
	{
		return 0;
	}

	//int money = 0;

	//if(ACE_OS::strlen(emailStr.c_str()) > 0)
	//{
	//	money = 10;
	//}
	_db_res = NULL;
	for(int i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
	{
		_prep_stmt = db_conn->prepareStatement("insert into character_tbl(user_id,create_time,level,money) values(?,?,0,0)");
		_prep_stmt->setUInt(1, unUserID);
		//_prep_stmt->setString(2, GAME_CONFIG_INSTANCE::instance()->m_defaultName);
		_prep_stmt->setUInt(2, GameUtils::get_utc());
		//_prep_stmt->setUInt(3, money);
		_prep_stmt->executeUpdate();
		destroy_db_res(_prep_stmt,_db_res);
	}

	//--------------------------------注册校验
	_prep_stmt = db_conn->prepareStatement("select character_id from character_tbl where user_id=?");
	_prep_stmt->setInt(1, unUserID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res->next())
	{
		character_id= _db_res->getUInt("character_id");

		//--------------------注册
		info.m_unUserID = unUserID;
		info.m_charactID = character_id;
		info.m_op_action = enum_LOG_ACTION::LOG_ACTION_CREATE_CHARACT;
		info.SetOp_Way(_LOG_OP_WAY_CREATE_CHARACT);
		info.m_unType = LOG_TYPE_DEFALT;
		info.m_op_after = character_id;
		info.m_op_time = GameUtils::get_utc();
		DBUserHandler::SendLogInfoItemMSG(info,character_id,this);
		//------------------------------end
	}
	destroy_db_res(_prep_stmt,_db_res);


	return 0;
}

// void DBLoginHandler::SendLogInfoItemMSG( LogItemInfo & ver,ACE_UINT32 unUserID )
// {
// 	MsgDBLogInfoRequest request;
// 	ZeroVar(request);
// 	request.unCount = 1;
// 	request.logInfoItem[0] = ver;
// 	this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_LOG_INFO_REQUEST, (char *)&request, 
// 		sizeof(MsgDBLogInfoRequest), DBUserHandler::m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
// 	//DB_LOG_MGR_INSTANCE::instance()->write_db_log(request.logInfoItem,request.unCount);
// // 	//发送日志信息
// // 	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_LOG_INFO_REQUEST, (char *)&request, sizeof(MsgDBLogInfoRequest),
// // 	OBJ_ID_NONE, ADAPTER_DB_USER_MGR, unUserID);
// }
