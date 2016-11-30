#include "PlayerPool.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "ace\OS_NS_string.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


PlayerPool::PlayerPool()
{
	m_unCount = 0;
	m_head = m_tail = NULL;
	m_nPoolID = 0;
}

PlayerPool::~PlayerPool()
{
	
}

void PlayerPool::reset()
{
	PlayerPoolBlock *block = m_head;
	PlayerPoolBlock *t;

	while(block != NULL)
	{
		t = block;
		block = block->next;
		delete t;
	}

	m_head = m_tail = NULL;
	m_unCount = 0;

}

int PlayerPool::add(PublicPlayerInfo *playerInfo)
{
	//PlayerPoolBlock *block = alloc_block();
	PlayerPoolBlock *block = NULL;

	int t = m_unCount % PLAYER_COUNT_PER_BLOCK;

	if(t == 0)
	{
		block = new PlayerPoolBlock();
		
		if(block == NULL)
		{
			return -1;
		}

		if(m_head == NULL)
		{
			m_head = m_tail = block;
			block->prev = block->next = NULL;
		}
		else
		{
			m_tail->next = block;
			block->prev = m_tail;
			block->next = NULL;
			m_tail = block;
		}
	}
	
	block = m_tail;

	//block->list[t] = playerInfo;
	set_player_info(block, t, playerInfo, m_unCount);

	m_unCount ++;

	return (m_unCount - 1);
}

PublicPlayerInfo *PlayerPool::remove(PublicPlayerInfo *playerInfo)
{
	int idx = playerInfo->poolPosition[m_unPoolType].nIndex;

	if(idx < 0 || idx >= m_unCount)
	{
		return NULL;
	}

	PublicPlayerInfo *ret = NULL;

	PlayerPoolBlock *p = get_block(idx);

	int t = idx % PLAYER_COUNT_PER_BLOCK;

	ret = p->list[t];

	int last_idx = m_unCount - 1;

	if(idx != last_idx)
	{
		set_player_info(p, t, m_tail->list[last_idx % PLAYER_COUNT_PER_BLOCK], idx);
	}

	m_unCount --;

	if((m_unCount % PLAYER_COUNT_PER_BLOCK) == 0)
	{
		if(m_head == m_tail)
		{
			delete m_head;
			m_head = m_tail = NULL;
		}
		else
		{
			p = m_tail;
			m_tail->prev->next = NULL;
			m_tail = m_tail->prev;
			delete p;
		}
	}

	playerInfo->poolPosition[m_unPoolType].nPoolID = -1;

	return ret;
}

void PlayerPool::set_player_info(PlayerPoolBlock *block, int offset, PublicPlayerInfo *playerInfo, int idx)
{
	block->list[offset] = playerInfo;
	playerInfo->poolPosition[m_unPoolType].nIndex = idx;
	playerInfo->poolPosition[m_unPoolType].nPoolID = m_nPoolID;
}

PublicPlayerInfo *PlayerPool::get_player_id_by_index(int idx)
{
	PlayerPoolBlock *p = get_block(idx);

	int t = idx % PLAYER_COUNT_PER_BLOCK;

	return p->list[t];
}

PublicPlayerInfo *PlayerPool::get_last()
{
	if(m_tail == NULL)
	{
		return NULL;
	}

	int t = (m_unCount - 1) % PLAYER_COUNT_PER_BLOCK;

	return m_tail->list[t];
}

void PlayerPool::swap_2_last(int idx)
{
	if(idx == (m_unCount - 1))
	{
		return;
	}

	int offset0,offset1;
	PlayerPoolBlock *p = get_block(idx);
	PlayerPoolBlock *last_b = m_tail;

	offset0 = idx % PLAYER_COUNT_PER_BLOCK;
	offset1 = (m_unCount - 1) % PLAYER_COUNT_PER_BLOCK;

	PublicPlayerInfo *tmp = p->list[offset0];

	set_player_info(p, offset0, last_b->list[offset1], idx);
	set_player_info(last_b, offset1, tmp, m_unCount - 1);
}

PlayerPoolBlock *PlayerPool::get_last_block()
{
	return m_tail;
}

PlayerPoolBlock *PlayerPool::get_block(int idx)
{
	int t = idx / PLAYER_COUNT_PER_BLOCK;

	PlayerPoolBlock *p = m_head;

	int i;
	for(i = 0;i < t;i ++)
	{
		p = p->next;
	}

	return p;
}

int PlayerPool::fill_2_array(PublicPlayerInfo *list[])
{
	PlayerPoolBlock *p = m_head;

	int i;
	int total = m_unCount;
	int offset = 0;
	int c;
	int ret = 0;

	while(p != NULL)
	{
		c = total > PLAYER_COUNT_PER_BLOCK ? PLAYER_COUNT_PER_BLOCK : total;
		for(i = 0;i < c;i ++)
		{
			list[offset] = p->list[i];
			ret ++;
		}

		total -= c;
		offset += c;
		p = p->next;
	}

	return ret;
}