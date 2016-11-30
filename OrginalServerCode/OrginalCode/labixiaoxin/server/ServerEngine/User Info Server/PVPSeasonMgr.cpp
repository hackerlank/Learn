#include "PVPSeasonMgr.h"
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

//char friendMsgBuff[4096];


PVPSeasonMgr::PVPSeasonMgr()
{
	m_unCount = 0;
	m_unTotalCount = 0;
}

PVPSeasonMgr::~PVPSeasonMgr()
{
	
}

void PVPSeasonMgr::reset()
{
	m_unCount = 0;
}

void PVPSeasonMgr::load_from_db()
{

}

bool PVPSeasonMgr::check_new_season(ACE_UINT32 unTime)
{

	//ACE_UINT32 t = GameUtils::get_week_count(unTime);
	ACE_UINT32 t = GameUtils::get_pvp_season_id(unTime);

	if(t == m_unCurrentSeasonID)
	{
		return false;
	}

	m_unCurrentSeasonID = t;
	m_unRankUpdateFlag = 0;

	m_unCount = 0;

	return true;
}

void PVPSeasonMgr::add_player(PublicPlayerInfo *player)
{
	if(m_unCount >= MAX_SEASON_RANK_COUNT)
	{
		return;
	}

	m_list[m_unCount] = player;

	m_unCount ++;
	m_unTotalCount ++;
}

void PVPSeasonMgr::update_leaderboard(PublicPlayerInfo *player,int oldOrder)
{
	//int start, end;
	int t = 0;
	int i;

	bool remove_flag = false;

	int newOrder = player->pvpRankInfo.nOrder;

	if(oldOrder < 0)
	{
		t ++;
	}
	if(newOrder < 0)
	{
		t --;
	}

	int c = (int)m_unTotalCount;
	c = c + t;
	if(c < 0)
	{
		c = 0;
	}
	m_unTotalCount = c;

	if(oldOrder < 0 || oldOrder >= m_unCount)
	{
		if(newOrder < 0 || newOrder > m_unCount)
		{
			return;
		}
		else if(newOrder == m_unCount)
		{
			if(m_unCount < MAX_SEASON_RANK_COUNT)
			{
				//m_list[m_unCount] = player;
				set_player_at_index(m_unCount, player);
				m_unCount ++;
			}

			return;
		}
		else
		{
			if(m_unCount < MAX_SEASON_RANK_COUNT)
			{
				for(i = m_unCount;i > newOrder;i --)
				{
					set_player_at_index(i, m_list[i - 1]);
				}
				m_unCount ++;
			}
			else
			{
				m_list[MAX_SEASON_RANK_COUNT - 1]->pvpRankInfo.nOrder = MAX_SEASON_RANK_COUNT;

				for(i = MAX_SEASON_RANK_COUNT - 1;i > newOrder;i --)
				{
					set_player_at_index(i, m_list[i - 1]);
				}
			}

			set_player_at_index(newOrder, player);
		}
	}
	else
	{
		if(newOrder < 0 || newOrder >= m_unCount)
		{
			//move 2 last
			for(i = oldOrder;i < m_unCount - 1;i ++)
			{
				set_player_at_index(i, m_list[i + 1]);
			}
			newOrder = m_unCount - 1;
		}
		else if(newOrder == oldOrder)
		{
			return;
		}
		else if(newOrder < oldOrder)
		{
			for(i = oldOrder;i > newOrder;i --)
			{
				set_player_at_index(i, m_list[i - 1]);
			}
		}
		else
		{
			for(i = oldOrder;i < newOrder;i ++)
			{
				set_player_at_index(i, m_list[i + 1]);
			}
		}

		set_player_at_index(newOrder, player);
	}
}

void PVPSeasonMgr::set_player_at_index(int idx, PublicPlayerInfo *player)
{
	m_list[idx] = player;
	m_list[idx]->pvpRankInfo.nOrder = idx;
}

void PVPSeasonMgr::move_back_at_index(int idx)
{
}

/*
bool PVPSeasonMgr::is_season_open(ACE_UINT32 unTime)
{
	int t = GameUtils::get_week_time(unTime);

	if(t < 9 * ( 60 * 60) || t > ((6 * 24 + 20) * 60 * 60))
	{
		return false;
	}

	return true;
}
*/

/*
void TeamRankMgr::update(ACE_UINT32 unCharacterID, ACE_UINT32 unPoint, PlayerTeamInfo *teamInfo)
{
	int i;
	int pos = -1;
	int own_pos = -1;
	int addIdx = -1;
	int updateIdx = -1;
	ACE_UINT32 deleteID = 0;
	for(i = 0;i < m_unCount;i ++)
	{
		if(m_list[i].unCharacterID == unCharacterID)
		{
			if(m_list[i].unPoint >= unPoint)
			{
				return;
			}

			own_pos = i;
		}

		if(unPoint > m_list[i].unPoint)
		{
			if(pos == -1)
			{
				pos = i;
			}
		}
	}

	if(pos == -1)
	{
		if(own_pos != -1)
		{
			return;
		}

		if(m_unCount < MAX_TEAM_RANK_COUNT)
		{
			m_unCount ++;
			
			update_cell(m_unCount - 1, unCharacterID, unPoint, teamInfo);
			
			addIdx = m_unCount - 1;
		}
		else
		{
			return;
		}
	}
	else
	{
		if(own_pos != -1)
		{
			if(own_pos <= pos)
			{
				return;
			}

			for(i = own_pos;i > pos;i --)
			{
				m_list[i] = m_list[i - 1];
			}

			updateIdx = pos;

			update_cell(pos, unCharacterID, unPoint, teamInfo);
		}
		else
		{
			addIdx = pos;
			if(m_unCount < MAX_TEAM_RANK_COUNT)
			{
			}
			else
			{
				
				deleteID = m_list[m_unCount - 1].unCharacterID;
			}

			for(i = m_unCount;i > pos;i --)
			{
				if(i >= MAX_TEAM_RANK_COUNT)
				{
					continue;
				}

				m_list[i] = m_list[i - 1];
			}

			update_cell(pos, unCharacterID, unPoint, teamInfo);
		}
	}

	if(addIdx != -1)
	{
		//add 2 db
	}

	if(updateIdx != -1)
	{
		//update 2 db
	}

	if(deleteID != 0)
	{
		//delete from db
	}
}

void TeamRankMgr::update_cell(int idx, ACE_UINT32 unCharacterID, ACE_UINT32 unPoint, PlayerTeamInfo *teamInfo)
{
	m_list[idx].unCharacterID = unCharacterID;
	m_list[idx].unPoint = unPoint;
	m_list[idx].unUpdateTime = GameUtils::get_utc();
	m_list[idx].teamInfo = *teamInfo;
}

*/