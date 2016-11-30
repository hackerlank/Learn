#include "PlayerPoolMgr.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "ace\OS_NS_string.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


PlayerPoolMgr::PlayerPoolMgr()
{
	m_poolList = NULL;
	//m_unSize = 0;
	m_unCapcity = 0;
	m_unPoolType = 0;
}

PlayerPoolMgr::~PlayerPoolMgr()
{

}

void PlayerPoolMgr::init(ACE_UINT32 unSize)
{
	resize(unSize);
}

void PlayerPoolMgr::resize(ACE_UINT32 unSize)
{
	ACE_UINT32 capcity = cal_capcity(unSize);

	if(m_unCapcity >= capcity)
	{
		return;
	}

	PPlayerPool *oldlist = m_poolList;

	m_poolList = new PPlayerPool[capcity];

	if(m_poolList == NULL)
	{
		return;
	}

	int i;

	for(i = 0;i < capcity;i ++)
	{
		if(i < m_unCapcity)
		{
			m_poolList[i] = oldlist[i];
		}
		else
		{
			m_poolList[i] = new PlayerPool();
			m_poolList[i]->m_nPoolID = i;
			m_poolList[i]->m_unPoolType = m_unPoolType;
		}
	}

	m_unCapcity = capcity;
}

void PlayerPoolMgr::reset()
{
	int i;

	for(i = 0;i < m_unCapcity;i ++)
	{
		m_poolList[i]->reset();
	}
}

ACE_UINT32 PlayerPoolMgr::cal_capcity(ACE_UINT32 unSize)
{
	if(unSize <= 0)
	{
		return MIN_PLAYER_POOL_COUNT;
	}

	return (1 + (unSize - 1) / MIN_PLAYER_POOL_COUNT) * MIN_PLAYER_POOL_COUNT;
}

void PlayerPoolMgr::add(int nPoolID, PublicPlayerInfo *playerInfo)
{
	if(nPoolID < 0)
	{
		return;
	}

	resize(nPoolID + 1);

	m_poolList[nPoolID]->add(playerInfo);
}

void PlayerPoolMgr::move(int nPoolID, PublicPlayerInfo *playerInfo)
{
	int oldID = playerInfo->poolPosition[m_unPoolType].nPoolID;

	if(nPoolID == oldID)
	{
		return;
	}

	if(oldID >= 0)
	{
		m_poolList[oldID]->remove(playerInfo);
	}
	if(nPoolID >= 0)
	{
		m_poolList[nPoolID]->add(playerInfo);
	}

}

int PlayerPoolMgr::pool_size(int nPoolID)
{
	if(nPoolID < 0)
	{
		return 0;
	}

	resize(nPoolID + 1);

	return m_poolList[nPoolID]->m_unCount;
}

int PlayerPoolMgr::get_random_player(int nPoolID, int minCount, PublicPlayerInfo *list[], int nCount)
{
	if(nPoolID < 0)
	{
		return 0;
	}

	int ret = 0;

	int t_start, t_end;

	int i, j;

	t_start = t_end = nPoolID;

	int current_c = m_poolList[nPoolID]->m_unCount;

	m_randomCountList[t_start] = current_c;

	if(current_c < minCount)
	{
		int step = t_start;

		if((m_unCapcity - nPoolID) > step)
		{
			step = m_unCapcity - nPoolID;
		}

		for(i = 0;i < step;i ++)
		{
			if(t_start > 0)
			{
				t_start --;

				m_randomCountList[t_start] = m_poolList[t_start]->m_unCount;
				current_c += m_randomCountList[t_start];
			}
			if(t_end < (m_unCapcity - 1))
			{
				t_end ++;

				m_randomCountList[t_end] = m_poolList[t_end]->m_unCount;
				current_c += m_randomCountList[t_end];
			}

			if(current_c >= minCount)
			{
				break;
			}
		}
	}

	int offset = 0;

	if(current_c <= nCount)
	{
		for(i = t_start;i <= t_end;i ++)
		{
			offset += m_poolList[i]->fill_2_array(&list[offset]);
		}
		ret = current_c;
	}
	else
	{
		ret = nCount;
		int idx;
		int tmp;

		for(i = 0;i < nCount;i ++)
		{
			idx = ACE_OS::rand() % current_c;
			tmp = -1;

			for(j = t_start;j <= t_end;j ++)
			{
				if(idx < m_randomCountList[j])
				{
					tmp = j;

					break;
				}

				idx -= m_randomCountList[j];
			}

			if(tmp == -1)
			{
				ret = i;
				break;
			}

			m_poolList[j]->swap_2_last(idx);
			m_randomCountList[j] --;
			current_c --;

			list[i] = m_poolList[j]->get_last();
		}
	}

	for (i=0;i<ret;++i)
	{
		if (list[i] == NULL)
		{
			break;
		}
	}

	ret = i;
	return ret;
}