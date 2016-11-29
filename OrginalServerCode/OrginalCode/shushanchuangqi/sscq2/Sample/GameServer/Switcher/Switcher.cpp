#include "stdafx.h"
#include "Switcher.h"
#include "Map.h"
#include "Protocols.h"
#include "Dungeon.h"
#include "Player.h"

void CSwitcher::GetSwitcherAppear(SSwitcherAppear& rSwitcherAppear)
{
	rSwitcherAppear.dwSwitcherID = _dwSwitcherID;
	rSwitcherAppear.eType = GetSwitcherType();
	rSwitcherAppear.bOpen = _bOpen;
}

void CSwitcher::CondCheck()
{
	if(_bOpen)
		return;

	for(auto it = _setObjCond.begin(); it != _setObjCond.end(); ++it)
	{
		SObjCondPtr pObjCond = *it;
		if(pObjCond != NULL && !pObjCond->Check(*this))
			return;
	}

	SetOpen(true);
}

void CSwitcher::TimerCheck()
{
	
}

bool CSwitcher::NotifySurround(const string& strPkg)
{
	CGameMapPtr pMap = GetMap();
	if(pMap == NULL || strPkg.empty())
		return false;
	return pMap->NotifySurround(*this, strPkg);
}

bool CSwitcher::NotifyOpenState()
{
	return NotifySurround(g_MapProtS.BuildPkg_NotifySwitcherState(_dwInstID, _bOpen));
}

void CSwitcher::SetOpen(bool bOpen, bool bNotify /*= true*/)
{
	_bOpen = bOpen;

	if(bNotify)
	{
		NotifyOpenState();
	}
}

void CSwitcher::AddCondition(SObjCond& rObjCond)
{
	if(!_setObjCond.insert(ToThisPtr(rObjCond)).second)
		LOG_CRI << "switcher AddCondition is error";
}

//////////////////////////////////////////////////////////////////////////
// CTowerJumpSwitcher

void CTowerJumpSwitcher::Exec()
{
	CGameMapPtr pMap = GetMap();
	if(!pMap)
	{
		LOG_CRI << "Map Not Exist!";
		return;
	}

	CDungeonPtr pDungeon = pMap->GetDungeon();
	if(!pDungeon)
	{
		LOG_CRI << "Is Not Dungeon!";
		return;
	}
}

void CTowerJumpSwitcher::TimerCheck()
{
	CGameMapPtr pMap = GetMap();
	if(!pMap)
	{
		LOG_CRI << "Map Not Exist!";
		return;
	}

	const TMapID2Player& mapID2Player = pMap->GetPlayerMap();
	for(auto itr = mapID2Player.begin(); itr != mapID2Player.end(); ++itr)
	{
		CPlayerPtr pPlayer = itr->second.lock();
		assert(pPlayer);
		if(_oRegion.IsInRegion(pPlayer->GetPoint()))
		{
			SetOpen(false);
			Exec();
			break;
		}
	}
}

void CTowerJumpSwitcher::PlaceTo(float fX, float fY)
{
	SetPoint(SPoint(fX, fY));
	_oRegion.fX = fX;
	_oRegion.fY = fY;
	_oRegion.fRadius = 2;
	_oRegion.Init();
}

//////////////////////////////////////////////////////////////////////////
//CCampSwitcher
