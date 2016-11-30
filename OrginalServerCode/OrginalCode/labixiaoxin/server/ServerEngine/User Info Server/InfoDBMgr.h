#pragma once

//#include "PhpProxySession.h"
#include "..\Base\Service\BaseAdapter.h"
#include "..\GameBase\Common\GameDefine.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
//#include "ace\Containers.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"   
#include "cppconn/prepared_statement.h"   
#include "cppconn/metadata.h"   
#include "cppconn/exception.h" 

#include "ace\ACE.h"
#include "ace\Singleton.h"
#include "ace\Message_Queue.h"
#include "ace\Condition_Thread_Mutex.h"

using namespace sql;

enum
{
	INFO_DB_COMMAND_NONE = 0,
	INFO_DB_COMMAND_CLEAR_SEASON_TBL,
	INFO_DB_COMMAND_UPDATE_SCORE,
	INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ORDER,
	INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ID,
	INFO_DB_COMMAND_UPDATE_CONFIG_TBL,
	//INFO_DB_COMMAND_UPDATE_TEAM_RANK,
	INFO_DB_COMMAND_GET_RANK,
};

typedef struct tagInfoDBCommand
{
	ACE_UINT32 unType;
	tagInfoDBCommand()
	{
		unType = INFO_DB_COMMAND_NONE;
	};
}InfoDBCommand;

typedef struct tagInfoDBClearSeasonTable : public InfoDBCommand
{
	ACE_UINT32 unSeasonID;
	tagInfoDBClearSeasonTable()
	{
		unType = INFO_DB_COMMAND_CLEAR_SEASON_TBL;
	}
}InfoDBClearSeasonTable;

typedef struct tagInfoDBUpdateScore : public InfoDBCommand
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unScore;
	ACE_UINT32 unAll;
	ACE_UINT32 unWin;
	tagInfoDBUpdateScore()
	{
		unType = INFO_DB_COMMAND_UPDATE_SCORE;
	}
}InfoDBUpdateScore;

typedef struct tagInfoDBGetPlayerInfoByOrder : public InfoDBCommand
{
	ACE_UINT32 unOrder;
	tagInfoDBGetPlayerInfoByOrder()
	{
		unType = INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ORDER;
	}
}InfoDBGetPlayerInfoByOrder;

typedef struct tagInfoDBGetPlayerInfoByID : public InfoDBCommand
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unSeasonID;
	tagInfoDBGetPlayerInfoByID()
	{
		unType = INFO_DB_COMMAND_GET_PLAYER_INFO_BY_ID;
	}
}InfoDBGetPlayerInfoByID;

typedef struct tagInfoDBUpdateConfigTable : public InfoDBCommand
{
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unRankUpdateFlag;
	tagInfoDBUpdateConfigTable()
	{
		unType = INFO_DB_COMMAND_UPDATE_CONFIG_TBL;
	}
}InfoDBUpdateConfigTable;

/*
typedef struct tagInfoDBUpdateTeamRank : public InfoDBCommand
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unPoint;
	PlayerTeamInfo teamInfo;
	tagInfoDBUpdateTeamRank()
	{
		unType = INFO_DB_COMMAND_UPDATE_TEAM_RANK;
	}
}InfoDBUpdateTeamRank;
*/

typedef struct tagInfoDBGetRank : public InfoDBCommand
{
	ACE_UINT32 unCurrentCharacterID;
	ACE_UINT32 unSeasonID;
	tagInfoDBGetRank()
	{
		unType = INFO_DB_COMMAND_GET_RANK;
	}
}InfoDBGetRank;

class InfoDBMgr
{
public:
	InfoDBMgr();
	~InfoDBMgr();

	int init();
	void fini();

	void add_command(void *data, int size);
	void commit();

	bool has_request();

	void send_notify_msg(ACE_UINT32 unType, void *data, int size);
public:
	static Connection *create_db_connection();
private:
	ACE_Message_Queue<ACE_MT_SYNCH> m_dealQueue;

	static ACE_THR_FUNC_RETURN do_db_query(void *opParam);
	int m_nThreadGroupID;

	void clear_season_tbl(ACE_UINT32 unSeasonID);
	void update_score(ACE_UINT32 unCharacterID, ACE_UINT32 unSeasonID, ACE_UINT32 unScore, ACE_UINT32 unAll, ACE_UINT32 unWin);
	void get_player_info_by_order(ACE_UINT32 unOrder);
	void get_player_info_by_id(ACE_UINT32 unCharacterID, ACE_UINT32 unSeasonID);
	void update_config_tbl(ACE_UINT32 unSeasonID, ACE_UINT32 unRankUpdateFlag);
	//void update_team_rank(ACE_UINT32 unCharacterID, ACE_UINT32 unPoint, PlayerTeamInfo *teamInfo);
	void get_rank(ACE_UINT32 unCurrentCharacterID, ACE_UINT32 unSeasonID);

	Connection *m_dbConn;//不能长期持有

	PreparedStatement *m_prep_stmt;
	ResultSet *m_db_res;

	void destroy_db_res();
	int update_db_connection();
	void destroy_db_connection();
};

typedef ACE_Singleton<InfoDBMgr, ACE_Thread_Mutex> INFO_DB_MGR_INSTANCE;