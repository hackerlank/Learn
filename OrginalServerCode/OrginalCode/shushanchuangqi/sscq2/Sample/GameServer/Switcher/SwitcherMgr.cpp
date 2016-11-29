#include "stdafx.h"
#include "SwitcherMgr.h"
#include "Switcher.h"
#include "JumpSwitcher.h"
#include "BarrierCFG.h"
#include "MapInfo.h"

map<UINT32, CSwitcherPtr> CSwitcherMgr::_mapID2Switcher;
UINT32 CSwitcherMgr::_dwNextInstID = SWITCHER_ID_MIN;

bool CSwitcherMgr::Init()
{
	return true;
}

UINT32 CSwitcherMgr::GetNewInstID()
{
	UINT32 dwNewInstID = _dwNextInstID++;
	if(_dwNextInstID > SWITCHER_ID_MAX)
		_dwNextInstID = SWITCHER_ID_MIN;
	return dwNewInstID;
}
	
void CSwitcherMgr::Destroy()
{
}

CJumpSwitcherPtr CSwitcherMgr::CreateJumpSwitcher(const SDgnJumpPoint& rDgnJumpPoint)
{
	bool bOpen = rDgnJumpPoint.wConditionID == 0;
	CJumpSwitcherPtr pJumpSwitcher(new CJumpSwitcher(rDgnJumpPoint.dwJumpID,rDgnJumpPoint.byIndex,bOpen));
	if(NULL == pJumpSwitcher)
		return NULL;
	pJumpSwitcher->SetInstID(GetNewInstID());
	if(!_mapID2Switcher.insert(make_pair(pJumpSwitcher->GetInstID(), pJumpSwitcher)).second)
	{
		LOG_CRI << "Duplicate!";
		return NULL;
	}
	return pJumpSwitcher;
}

CCampSwitcherPtr CSwitcherMgr::CreateCampSwitcher(const SDgnJumpPoint& rDgnJumpPoint)
{
	bool bOpen = rDgnJumpPoint.wConditionID == 0;
	CCampSwitcherPtr pCampSwitcher(new CCampSwitcher(rDgnJumpPoint.dwJumpID, bOpen));
	if(NULL == pCampSwitcher)
		return NULL;
	pCampSwitcher->SetInstID(GetNewInstID());
	if(!_mapID2Switcher.insert(make_pair(pCampSwitcher->GetInstID(), pCampSwitcher)).second)
	{
		LOG_CRI << "Duplicate!";
		return NULL;
	}
	return pCampSwitcher;
}

CTowerJumpSwitcherPtr CSwitcherMgr::CreateTowerJumpSwitcher(UINT32 dwSwitcherID, bool bOpen)
{
	CTowerJumpSwitcherPtr pTowerJumpSwitcher(new CTowerJumpSwitcher(dwSwitcherID, bOpen));
	if(NULL == pTowerJumpSwitcher)
		return NULL;
	pTowerJumpSwitcher->SetInstID(GetNewInstID());
	if(!_mapID2Switcher.insert(make_pair(pTowerJumpSwitcher->GetInstID(), pTowerJumpSwitcher)).second)
	{
		LOG_CRI << "Duplicate!";
		return NULL;
	}
	return pTowerJumpSwitcher;
}

void CSwitcherMgr::DestroySwitcher(CSwitcher& rSwitcher)
{
	_mapID2Switcher.erase(rSwitcher.GetInstID());
}

void CSwitcherMgr::TimerCheck()
{
	for(auto it = _mapID2Switcher.begin(); it != _mapID2Switcher.end();)
	{
		CSwitcherPtr pSwitcher = it->second;
		assert(pSwitcher);
		++it;

		pSwitcher->CondCheck();
		if(pSwitcher->IsOpen())
			pSwitcher->TimerCheck();
	}
}
