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

//#include "PVPMatchMgr.h"

using namespace sql;

#define MAX_SEASON_RANK_COUNT 50


class PVPSeasonMgr
{
public:
	PVPSeasonMgr();
	~PVPSeasonMgr();

	void reset();

	void load_from_db();

	bool check_new_season(ACE_UINT32 unTime);

	void add_player(PublicPlayerInfo *player);

	void update_leaderboard(PublicPlayerInfo *player,int oldOrder);

	//bool is_season_open(ACE_UINT32 unTime);

	ACE_UINT32 m_unCurrentSeasonID;
	ACE_UINT32 m_unRankUpdateFlag;
	ACE_UINT32 m_unCount;

	ACE_UINT32 m_unTotalCount;

	PublicPlayerInfo *m_list[MAX_SEASON_RANK_COUNT];
private:

	void move_back_at_index(int idx);
	void set_player_at_index(int idx, PublicPlayerInfo *player);
	//PVPMatchMgr m_teamRankPool;
	//PVPMatchMgr m_matchPool;

	//void update_cell(int idx, ACE_UINT32 unCharacterID, ACE_UINT32 unPoint, PlayerTeamInfo *teamInfo);
};