#include "stdafx.h"
#include "Visitor.h"
#include "Map.h"

static bool CanFight(const CBaseObjPtr& pObj1, const CBaseObjPtr& pObj2)
{
	CCreaturePtr pAttacker = dynamic_pointer_cast<CCreature>(pObj1);
	CCreaturePtr pTarget = dynamic_pointer_cast<CCreature>(pObj2);
	if(pAttacker != NULL && pTarget != NULL)
		return pAttacker->CanFight(*pTarget);
	return false;
}

static bool CanSee(const CBaseObjPtr& pObj1, const CBaseObjPtr& pObj2)
{
	CCreaturePtr pCreature1 = dynamic_pointer_cast<CCreature>(pObj1);
	CCreaturePtr pCreature2 = dynamic_pointer_cast<CCreature>(pObj2);
	if(pCreature1 != NULL && pCreature2 != NULL)
		return pCreature1->CanSee(*pCreature2);
	return false;
}

static bool HasSameUser(const CBaseObjPtr& pObj1, const CBaseObjPtr& pObj2)
{
	CPlayerPtr pPlayer1 = dynamic_pointer_cast<CPlayer>(pObj1);
	if(pPlayer1 == NULL)
		return false;
	CPlayerPtr pPlayer2 = dynamic_pointer_cast<CPlayer>(pObj2);
	if(pPlayer2 == NULL)
		return false;
	return pPlayer1->GetUserPtr() == pPlayer2->GetUserPtr();
}

bool CVisitor::Visit(CBaseObj& rObj)
{
	EObjType eObjType = rObj.GetObjType();
	CBaseObjPtr pObj = rObj.shared_from_this();
	switch(eObjType)
	{
	case eObjPlayer:
		{
			CPlayerPtr pPlayer = dynamic_pointer_cast<CPlayer>(pObj);
			if(pPlayer == NULL)
				return false;
            bool bPlayerVisitSelf = false;
            if(_eVisitType == eVisitPlayer || _eVisitType == eVisitAllMonster || _eVisitType == eVisitAllNpc)
            {
                bPlayerVisitSelf =true;
            }
			if(bPlayerVisitSelf && pPlayer->GetPlayerState() == ePlayerLeave)
			{
				LOG_CRI << "Player has left! qwRoleID: " << pPlayer->GetRoleID();
				return false;
			}
			switch(_eVisitType)
			{
			case eVisitRoundPlayer:
				if(_pObj == pObj)
					return false;
				return true;
			case eVisitPlayer:
				return true;
			case eVisitCanFight:
				if(_pObj != NULL && _pObj != pObj)
					return CanFight(_pObj, pObj);
				break;
			case eVisitAllMonster:
			case eVisitAllNpc:
				return false;
			default:
				if(_pObj == pObj)
					return false;
				if(_pObj != NULL && HasSameUser(_pObj, pObj))
					return false;
				return true;
			}
		}
		break;
	case eObjMonster:
		switch(_eVisitType)
		{
		case eVisitNotify:
		case eVisitPlayer:
		case eVisitRoundPlayer:
		case eVisitAllNpc:
			return false;
		case eVisitAllMonster:
			return true;
		case eVisitCanFight:
			if(_pObj != NULL && _pObj != pObj)
				return CanFight(_pObj, pObj);
			break;
		default:
			return CanSee(_pObj, pObj);
		}
		break;
	case eObjNpc:
		switch(_eVisitType)
		{
		case eVisitNotify:
		case eVisitPlayer:
		case eVisitRoundPlayer:
		case eVisitCanFight:
		case eVisitAllMonster:
			return false;
		default:
			return true;
		}
		break;
	case eObjSwitcher:
	case eObjBlocker:
	case eObjGather:
    case eObjArea:     
		switch(_eVisitType)
		{
		case eVisitNotify:
		case eVisitPlayer:
		case eVisitRoundPlayer:
		case eVisitAllMonster:
		case eVisitAllNpc:
			return false;
		default:
			return true;
		}
		break;
    default:
        break;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////

bool CPointPicker::Finish(INT32 dwX, INT32 dwY)
{
	SCoord oCoord(dwX, dwY);
	if(!_rMap.IsBlockPoint(oCoord, _bBaseGrid) && !_rMap.IsSafePoint(oCoord, _bBaseGrid))
	{
		SPoint oPoint;
		_rMap.GetMapInfo().ToFloatCoord(oCoord, oPoint, _bBaseGrid);
		_vecPoint.push_back(oPoint);
	}
	if(_dwCount > 0 && _vecPoint.size() >= _dwCount)
		return true;
	return false;
}
