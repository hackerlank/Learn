
#include "stdafx.h"
#include "BaseObj.h"
#include "Map.h"

const char* CBaseObj::GetObjTypeName(EObjType eObjType)
{
    switch(eObjType)
    {
        case eObjNone:
            return "None";
        case eObjPlayer:
            return "Player";
        case eObjMonster:
            return "Monster";
        case eObjNpc:
            return "NPC";
        case eObjGather:
            return "Gather";
        case eObjSwitcher:
            return "Switcher";
        case eObjBlocker:
            return "Blocker";
        case eObjArea:
            return "MapArea";
        default:
            return "Unknown";
    }
}

bool CBaseObj::GetCoord(SCoord& rCoord) const
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL)
        return false;
    rCoord = _oCoord;
    return true;
}

void CBaseObj::SetPoint(const SPoint& rPoint)
{
    if(GetObjType() == eObjPlayer)
    {
    CGameMapPtr pMap = GetMap();
    if(pMap)
    {
        if(pMap->IsBlockPoint(rPoint))
        {
             LOG_CRI << "Try To Block Point";
             _oPoint = SPoint();
             return;
        }
        
    }
    }
    _oPoint = rPoint;

}
CBaseObj::~CBaseObj()
{

#if 0
     LOG_DBG<< "Delll :" << GetObjTypeName(GetObjType());
    if(GetMap() || _pGrid != NULL)
    {
	    DebugBreak();
    }
#endif


}
