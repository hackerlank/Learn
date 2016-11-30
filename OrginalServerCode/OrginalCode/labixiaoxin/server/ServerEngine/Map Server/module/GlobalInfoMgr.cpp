#include "GlobalInfoMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\..\GameBase\res\MapGroupRes.h"
#include "..\Map.h"

GlobalInfoMgr::GlobalInfoMgr()
{
	m_unMapGroupCount = 0;
	ZeroVar(m_mapGroupList);
	m_unMapCount = 0;
	ZeroVar(m_mapList);
}

GlobalInfoMgr::~GlobalInfoMgr()
{
	
}

void GlobalInfoMgr::init()
{
	ACE_UINT32 tmp[MAX_MAP_COUNT];

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_MAP_GROUP, 0, 0, 0, tmp, 0);

	if(c > MAX_MAP_COUNT)
	{
		return;
	}

	m_unMapGroupCount = 0;
	m_unMapCount = 0;

	int i, j;
	int idx;
	MapGroupRes *res;

	for(i = 0;i < c;i ++)
	{
		idx = -1;
		for(j = 0;j < m_unMapGroupCount;j ++)
		{
			if(tmp[i] < m_mapGroupList[j])
			{
				idx = j;
				break;
			}
		}
		if(idx == -1)
		{
			idx = m_unMapGroupCount;
		}
		for(j = m_unMapGroupCount;j > idx;j --)
		{
			m_mapGroupList[j] = m_mapGroupList[j - 1];
		}
		m_mapGroupList[idx] = tmp[i];
		m_unMapGroupCount ++;

		res = (MapGroupRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tmp[i]);

		for(j = 0;j < res->m_unMapCount;j ++)
		{
			add_map_id(res->m_mapList[j]);
		}
	}

	/*
	ACE_UINT32 tmp[MAX_MAP_COUNT];

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_MAP, 0, 0, 0, tmp, 1);

	int i;
	char tmp_name[64];
	int m,n;

	for(i = 0;i < c;i ++)
	{
		//m = (tmp[i] / 1000000) % 100;
		//n = (tmp[i] / 10000) % 100;
		m = GET_ITEM_ID_INFO(tmp[i], 4, 2);
		n = GET_ITEM_ID_INFO(tmp[i], 2, 1);

		ACE_OS::sprintf(tmp_name, "config/ser/sermap%X_%X.xml", m, n);

		this->load_config(tmp[i], tmp_name);
	}
	*/
}

void GlobalInfoMgr::add_map_id(ACE_UINT32 unMapID)
{
	if(m_unMapCount >= MAX_MAP_COUNT * MAX_MAP_DIFFRENCE)
	{
		return;
	}
	int i;
	int idx = -1;
	for(i = 0;i < m_unMapCount;i ++)
	{
		if(unMapID < m_mapList[i])
		{
			idx = i;
			break;
		}
	}

	if(idx == -1)
	{
		idx = m_unMapCount;
	}

	for(i = m_unMapCount;i > idx;i --)
	{
		m_mapList[i] = m_mapList[i - 1];
	}
	m_mapList[idx] = unMapID;

	m_unMapCount ++;
}