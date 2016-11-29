#include "stdafx.h"
#include "Blocker.h"
#include "Map.h"
#include "BlockerMgr.h"

void CBlocker::AssginBlockPt(UINT16 wIndex,const TVecPoint& rVecPoint, SMapInfo& rMapInfo)
{
	CGameMapPtr pMap = GetMap();
	if(pMap == NULL)
	{
		LOG_CRI << "_pMap is NULL!";
		return;
	}
	SCoord oCoord;
	_vecBlockPt.reserve(rVecPoint.size());
    _wIndex = wIndex;
	for(auto it = rVecPoint.begin(); it != rVecPoint.end(); ++it)
	{
		rMapInfo.ToIntCoord(*it, oCoord, true);
		_vecBlockCoord.push_back(oCoord);
		pMap->AddDynBlockCoord(oCoord);
		_vecBlockPt.push_back(*it);
	}
}

void CBlocker::AddCondition(SObjCond& rObjCond)
{
	if(!_setObjCond.insert(ToThisPtr(rObjCond)).second)
		LOG_CRI << "blocker AddCondition is error";
}

void CBlocker::GetBlockerAppear(SBlockerAppear& rBlockerAppear)
{
	rBlockerAppear.dwBlockerID = _dwBlockerID;
	rBlockerAppear.vecPos.assign(_vecBlockPt.begin(), _vecBlockPt.end());
}

bool CBlocker::IsDisappeared()
{
	if(_setObjCond.empty())
		return false;

	for(auto it = _setObjCond.begin(); it != _setObjCond.end(); ++it)
	{
		SObjCondPtr pObjCond = *it;
		if(pObjCond != NULL && !pObjCond->Check(*this))
			return false;
	}

	return true;
}

void CBlocker::Disappear()
{
	CGameMapPtr pMap = GetMap();
	if(pMap != NULL)
	{
		for(auto it = _vecBlockCoord.begin(); it != _vecBlockCoord.end(); ++it)
			pMap->RemoveDynBlockCoord(*it);
		pMap->BlockerDisappear(*this);
	}
	else
    {
		LOG_CRI << "_pMap is NULL! _dwInstID: " << _dwInstID;
	    CBlockerMgr::DestroyBlocker(*this);
    }
}
