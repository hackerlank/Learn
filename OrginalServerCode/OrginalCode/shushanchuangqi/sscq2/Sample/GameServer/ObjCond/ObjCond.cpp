#include "stdafx.h"
#include "ObjCond.h"
#include "BaseObj.h"
#include "Map.h"
#include "Monster.h"

bool SKillMonsterCond::Check(CBaseObj& rBaseObj)
{
	CGameMapPtr pMap = rBaseObj.GetMap();
	if(pMap == NULL)
	{
		LOG_CRI << "pMap is NULL";
		return false;
	}

	const TMapID2Monster& mapID2Monster = pMap->GetMonsterMap();
	for(auto it = _vecMonsterID.begin(); it != _vecMonsterID .end(); ++it)
	{
		UINT16 wMonsterID = *it;
		for(auto itM = mapID2Monster.begin(); itM != mapID2Monster.end(); ++itM)
		{
			CMonsterPtr pMonster = itM->second.lock();
			if(pMonster != NULL && pMonster->GetGroupID() == wMonsterID)
				return false;
		}
	}

	return true;
}

#if 0
bool SOpenSwitcherCond::Check(CBaseObj& rBaseObj)
{
	return true;
}
#endif
bool SPlayerPosCond::Check(CBaseObj& rBaseObj)
{
	CGameMapPtr pMap = rBaseObj.GetMap();
	if(pMap == NULL)
	{
		LOG_CRI << "pMap is NULL";
		return false;
	}

	for(auto it = _vecPoint.begin(); it != _vecPoint.end(); ++it)
	{
		CVisitor oVisitor(eVisitRoundPlayer, rBaseObj.shared_from_this());
		CCollector<CVisitor> oCollector(oVisitor);
		pMap->VisitRoundArea((*it), PLAYER_POS_RADIUS, oCollector); //test
		set<CBaseObjPtr>& rSetMeetObj = oCollector.GetObjSet();
		if(rSetMeetObj.empty())
			return false;
	}
	return true;
}

bool SAllMonsterKilled::Check(CBaseObj& rBaseObj)
{
	CGameMapPtr pMap = rBaseObj.GetMap();
	if(pMap == NULL)
	{
		LOG_CRI << "pMap is NULL";
		return false;
	}

	const TMapID2Monster& mapID2Monster = pMap->GetMonsterMap();
	if(mapID2Monster.empty())
		return true;

	return false;
}
