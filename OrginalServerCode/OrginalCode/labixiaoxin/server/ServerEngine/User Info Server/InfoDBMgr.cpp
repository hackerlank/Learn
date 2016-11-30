#include "InfoDBMgr.h"
#include "json\json.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"
#include "..\GameBase\Common\GameDefine.h"
#include "..\Base\Service\ServiceConfigMgr.h"
//#include "..\GameBase\res\ArenaConfig.h"m_characterPool
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\DB Server\DBHandler.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

InfoDBMgr::InfoDBMgr()
{
	//m_unCount = 0;
	m_nThreadGroupID = -1;
	m_dealQueue.high_water_mark(0xA00000);
	m_dealQueue.low_water_mark(0xA00000);
	m_dbConn = NULL;
	m_prep_stmt = NULL;
	m_db_res = NULL;
}

InfoDBMgr::~InfoDBMgr()
{

}

int InfoDBMgr::init()
{
	m_nThreadGroupID = ACE_Thread_Manager::instance()->spawn_n(1, do_db_query, this);//创建一个线程

	if(m_nThreadGroupID == -1)
	{
		return -1;
	}

	return 0;
}

void InfoDBMgr::fini()
{
	m_dealQueue.close();

	if(m_nThreadGroupID != -1)
	{
		ACE_Thread_Manager::instance()->wait_grp(m_nThreadGroupID);
		m_nThreadGroupID = -1;
	}

	destroy_db_connection();
}

bool InfoDBMgr::has_request()
{
	return (!m_dealQueue.is_empty());
}

void InfoDBMgr::add_command(void *data, int size)
{
	ACE_Message_Block *msg = new ACE_Message_Block(size);

	if(msg == NULL)
	{
		return;
	}
	msg->wr_ptr(msg->base() + msg->size());
	msg->rd_ptr(msg->base());

	ACE_OS::memcpy(msg->base(), data, size);

	m_dealQueue.enqueue_tail(msg);
}

void InfoDBMgr::destroy_db_res()
{
	if(m_db_res != NULL)
	{
		try
		{
			m_db_res->close();
		}
		catch(SQLException& e) 
		{
		}

		delete m_db_res;
		m_db_res = NULL;
	}

	if(m_prep_stmt != NULL)
	{
		try
		{
			m_prep_stmt->close();
		}
		catch(SQLException& e) 
		{
		}

		delete m_prep_stmt;
		m_prep_stmt = NULL;
	}
}

int InfoDBMgr::update_db_connection()
{
	if(m_dbConn != NULL)
	{
		if(m_dbConn->isClosed())
		{
			delete m_dbConn;

			m_dbConn = NULL;
		}
		else
		{
			return 0;
		}
	}

	m_dbConn = create_db_connection();

	if(m_dbConn == NULL)
	{
		return -1;
	}

	return 0;
}

void InfoDBMgr::destroy_db_connection()
{
	if(m_dbConn == NULL)
	{
		return;
	}
	try
	{
		m_dbConn->close();
	}
	catch (SQLException &e)
	{

	}

	delete m_dbConn;
	m_dbConn = NULL;
}

void InfoDBMgr::commit()
{
	if(m_dbConn == NULL)
	{
		return;
	}

	m_dbConn->commit();
}

ACE_THR_FUNC_RETURN InfoDBMgr::do_db_query(void *opParam)
{
		ACE_Message_Block *msg;

		InfoDBMgr *mgr = (InfoDBMgr *)opParam;

		while(1)
		{
			if(mgr->m_dealQueue.dequeue(msg) == -1)
			{
				break;
			}

			if(mgr->update_db_connection() == -1)
			{
				mgr->m_dealQueue.enqueue_head(msg);
				ACE_OS::sleep(1);
				continue;
			}

			char *msg_p = msg->base();

			InfoDBCommand *pCommand = (InfoDBCommand *)msg_p;

			switch(pCommand->unType)
			{
			case INFO_DB_COMMAND_CLEAR_SEASON_TBL:
				{
					InfoDBClearSeasonTable *c = (InfoDBClearSeasonTable *)pCommand;
					mgr->clear_season_tbl(c->unSeasonID);
				}
				break;
			case INFO_DB_COMMAND_UPDATE_SCORE:
				{
					InfoDBUpdateScore *c = (InfoDBUpdateScore *)pCommand;
					mgr->update_score(c->unCharacterID, c->unSeasonID, c->unScore, c->unAll, c->unWin);
				}
				break;
			case INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ORDER:
				{
					InfoDBGetPlayerInfoByOrder *c = (InfoDBGetPlayerInfoByOrder *)pCommand;
					mgr->get_player_info_by_order(c->unOrder);
				}
				break;
			case INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ID:
				{
					InfoDBGetPlayerInfoByID *c = (InfoDBGetPlayerInfoByID *)pCommand;
					mgr->get_player_info_by_id(c->unCharacterID, c->unSeasonID);
				}
				break;
			case INFO_DB_COMMAND_UPDATE_CONFIG_TBL:
				{
					InfoDBUpdateConfigTable *c = (InfoDBUpdateConfigTable *)pCommand;
					mgr->update_config_tbl(c->unSeasonID, c->unRankUpdateFlag);
				}
				break;
				/*
				case INFO_DB_COMMAND_UPDATE_TEAM_RANK:
				{
				InfoDBUpdateTeamRank *c = (InfoDBUpdateTeamRank *)pCommand;
				mgr->update_team_rank(c->unCharacterID, c->unPoint, &c->teamInfo);
				}
				break;
				*/
			case INFO_DB_COMMAND_GET_RANK:
				{
					InfoDBGetRank *c = (InfoDBGetRank *)pCommand;
					mgr->get_rank(c->unCurrentCharacterID, c->unSeasonID);
				}
				break;
			}

			msg->release();

			mgr->commit();
			mgr->destroy_db_connection();//及时删除
		}

		return static_cast<ACE_THR_FUNC_RETURN>(0);
}

void InfoDBMgr::clear_season_tbl(ACE_UINT32 unSeasonID)
{
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "delete from %s", GameUtils::get_pvp_season_tbl_name(unSeasonID));

	m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
	if(m_prep_stmt == NULL)
	{
		return;
	}
	m_db_res = m_prep_stmt->executeQuery();
	destroy_db_res();
}

void InfoDBMgr::update_score(ACE_UINT32 unCharacterID, ACE_UINT32 unSeasonID, ACE_UINT32 unScore, ACE_UINT32 unAll, ACE_UINT32 unWin)
{
	////pvp_season_tbl0 [character_id,score,all,win,season_id,update_time]
	char *tblName = GameUtils::get_pvp_season_tbl_name(unSeasonID);
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "select score from %s where character_id=?", tblName);
	m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);

	if(m_prep_stmt == NULL)
	{
		return;
	}
	m_prep_stmt->setInt(1, unCharacterID);

	m_db_res = m_prep_stmt->executeQuery();

	bool insertFlag = true;

	if(m_db_res->next())
	{
		insertFlag = false;
	}
	destroy_db_res();

	if(insertFlag)
	{
		ACE_OS::sprintf(tmp_sql, "insert into %s(score,total,win,season_id,update_time,character_id) values(?,?,?,?,?,?)", tblName);
		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
	}
	else
	{
		ACE_OS::sprintf(tmp_sql, "update %s set score=?,total=?,win=?,season_id=?,update_time=? where character_id=?", tblName);
		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
	}

	if(m_prep_stmt == NULL)
	{
		return;
	}

	m_prep_stmt->setInt(1, unScore);
	m_prep_stmt->setInt(2, unAll);
	m_prep_stmt->setInt(3, unWin);
	m_prep_stmt->setInt(4, unSeasonID);
	m_prep_stmt->setInt(5, GameUtils::get_utc());
	m_prep_stmt->setInt(6, unCharacterID);

	m_db_res = m_prep_stmt->executeQuery();
	destroy_db_res();
}

void InfoDBMgr::get_player_info_by_order(ACE_UINT32 unOrder)
{

}

void InfoDBMgr::get_player_info_by_id(ACE_UINT32 unCharacterID, ACE_UINT32 unSeasonID)
{
	int nOrder = -1;

	char *tblName = GameUtils::get_pvp_season_tbl_name(unSeasonID);
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "select score,update_time from %s where character_id=%d", tblName, unCharacterID);
	m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
	if(m_prep_stmt == NULL)
	{
		return;
	}

	ACE_UINT32 unScore;
	ACE_UINT32 unUpdateTime;
	bool flag = false;
	m_db_res = m_prep_stmt->executeQuery();

	if(m_db_res->next())
	{
		flag = true;
		unScore = m_db_res->getInt("score");
		unUpdateTime = m_db_res->getInt("update_time");
	}
	destroy_db_res();

	if(flag)
	{
		ACE_OS::sprintf(tmp_sql, "select count(*) from %s where score>%d or (score=%d and update_time<%d)", tblName, unScore, unScore, unUpdateTime);

		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
		if(m_prep_stmt == NULL)
		{
			return;
		}
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			nOrder = m_db_res->getInt(1);
		}
		destroy_db_res();
	}

	MsgPlayerPVPOrderResponse response;
	response.unCharacterID = unCharacterID;
	response.unSeasonID = unSeasonID;
	response.nOrder = nOrder;
	send_notify_msg(MSG_PLAYER_PVP_ORDER_RESPONSE, &response, sizeof(MsgPlayerPVPOrderResponse));
}

void InfoDBMgr::update_config_tbl(ACE_UINT32 unSeasonID, ACE_UINT32 unRankUpdateFlag)
{
	return;//change by xxj 2015/07/07  20: 29:39 
	m_prep_stmt = m_dbConn->prepareStatement("update config_tbl set current_pvp_season=?,rank_update_flag=?");
	if(m_prep_stmt == NULL)
	{
		return;
	}
	m_prep_stmt->setInt(1, unSeasonID);
	m_prep_stmt->setInt(2, unRankUpdateFlag);
	m_db_res = m_prep_stmt->executeQuery();
	destroy_db_res();
}


void InfoDBMgr::get_rank(ACE_UINT32 unCurrentCharacterID, ACE_UINT32 unSeasonID)
{
	ACE_UINT32 unCharacterID = 0;
	ACE_UINT32 unScore;
	ACE_UINT32 unUpdateTime;

	char *tblName = GameUtils::get_pvp_season_tbl_name(unSeasonID - 1);
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "select character_id,score,update_time from %s where character_id > ? order by character_id limit 1", tblName);
	m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
	if(m_prep_stmt == NULL)
	{
		return;
	}

	//m_prep_stmt->setString(1, tblName);
	m_prep_stmt->setInt(1, unCurrentCharacterID);
	m_db_res = m_prep_stmt->executeQuery();

	if(m_db_res->next())
	{
		unCharacterID = m_db_res->getInt("character_id");
		unScore = m_db_res->getInt("score");
		unUpdateTime = m_db_res->getInt("update_time");
	}

	destroy_db_res();

	ACE_UINT32 unCount = 0;
	ACE_UINT32 unOrder = 0;
	ACE_UINT32 unRankID = 0;
	if(unCharacterID != 0)
	{
		ACE_OS::sprintf(tmp_sql, "select count(character_id) from %s", tblName);
		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			unCount = m_db_res->getInt(1);
		}

		ACE_OS::sprintf(tmp_sql, "select count(character_id) from %s where score>? or (score=? and update_time<?)", tblName);
		m_prep_stmt = m_dbConn->prepareStatement(tmp_sql);
		m_prep_stmt->setInt(1, unScore);
		m_prep_stmt->setInt(2, unScore);
		m_prep_stmt->setInt(3, unUpdateTime);
		m_db_res = m_prep_stmt->executeQuery();

		if(m_db_res->next())
		{
			unOrder = m_db_res->getInt(1);
		}

		destroy_db_res();

		unRankID = GameUtils::get_rank(unOrder, unCount);

		m_prep_stmt = m_dbConn->prepareStatement("update character_tmp_tbl set rank=?,pvp_season=? where character_id=?");
		if(m_prep_stmt == NULL)
		{
			return;
		}

		m_prep_stmt->setInt(1, unRankID);
		m_prep_stmt->setInt(2, unSeasonID);
		m_prep_stmt->setInt(3, unCharacterID);

		m_prep_stmt->executeUpdate();
		destroy_db_res();
	}


	MsgPlayerPVPRankResponse response;
	response.unCharacterID = unCharacterID;
	response.unSeasonID = unSeasonID;
	response.unRank = unRankID;
	send_notify_msg(MSG_PLAYER_PVP_RANK_RESPONSE, &response, sizeof(MsgPlayerPVPRankResponse));
}

void InfoDBMgr::send_notify_msg(ACE_UINT32 unType, void *data, int size)
{
	MessageInfo msg;

	if(allocMessageWithInfo(msg, size, SERVICE_MESSAGE_TYPE_USER, OBJ_ID_NONE, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType) == -1)
	{
		return;
	}

	//setAddr(msg.s_head->srcAdr);
	//msg.i_head->unSig = m_unCurrentSig;
	if(size > 0)
	{
		memcpy(msg.body, data, size);
	}

	if(COMMUNICATION_MGR_INSTANCE::instance()->send_local_msg(msg.msg) == -1)
	{
		msg.msg->release();
		return;
	}

	return;
}

ACE_Recursive_Thread_Mutex __mutex;
Connection *InfoDBMgr::create_db_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(__mutex);
	Connection *ret = NULL;
	Driver *driver;
	try
	{
		driver = get_driver_instance();

		if(driver == NULL)
		{
			return ret;
		}

		DatabaseInfo *dbInfo = &SERVICE_CONFIG_MGR_INSTANCE::instance()->m_dbInfo;

		/* create a database connection using the Driver */  
		ret = driver->connect(dbInfo->host, dbInfo->user, dbInfo->password);

		if(ret == NULL)
		{
			return ret;
		}

		/* turn off the autocommit */
		ret -> setAutoCommit(0);
		ret -> setSchema(dbInfo->name);
	}
	catch (SQLException &e)
	{
		if(ret != NULL)
		{
			try
			{
				ret->close();
			}
			catch (SQLException &e)
			{

			}

			delete ret;
		}

		ret = NULL;
	}

	return ret;
}