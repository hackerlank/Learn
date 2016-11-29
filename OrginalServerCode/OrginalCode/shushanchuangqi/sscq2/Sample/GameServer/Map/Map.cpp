#include "stdafx.h"
#include "Map.h"
#include "MapMgr.h"
#include "Protocols.h"
#include "BaseObj.h"
#include "Visitor.h"
#include "User.h"
#include "Player.h"
#include "NPCMgr.h"
#include "MonsterMgr.h"
#include "Switcher.h"
#include "JumpSwitcher.h"
#include "SwitcherMgr.h"
#include "Dungeon.h"
#include "DungeonMgr.h"
#include "Blocker.h"
#include "Gather.h"
#include "BlockerMgr.h"
#include "GatherMgr.h"
#include "DemonTowerMgr.h"
#include "MapAreaManager.h"
#include "PlayerDgn.h"
#include "GUIDMgr.h"
#include "Random.h"
#include "GameNetMgr.h"

using namespace NRoleInfoDefine;

    template<typename T1, typename T2>
void CGameMap::VisitDiffArea(const SCoord& rCenter1, const SCoord& rCenter2, const SCoord& rRadius, T1& rT1, T2& rT2)
{
    INT32 dwLeftX1 = rCenter1.dwX - rRadius.dwX, dwRightX1 = rCenter1.dwX + rRadius.dwX;
    INT32 dwLowY1 = rCenter1.dwY - rRadius.dwY, dwUpY1 = rCenter1.dwY + rRadius.dwY;
    INT32 dwLeftX2 = rCenter2.dwX - rRadius.dwX, dwRightX2 = rCenter2.dwX + rRadius.dwX;
    INT32 dwLowY2 = rCenter2.dwY - rRadius.dwY, dwUpY2 = rCenter2.dwY + rRadius.dwY;

    if(dwRightX1 < dwLeftX2 || dwRightX2 < dwLeftX1 || dwUpY1 < dwLowY2 || dwUpY2 < dwLowY1)
    {
        for(INT32 i = dwLeftX1; i <= dwRightX1; ++i)
        {
            for(INT32 j = dwLowY1; j <= dwUpY1; ++j)
                VisitGrid(i, j, rT1);
        }
        for(INT32 i = dwLeftX2; i <= dwRightX2; ++i)
        {
            for(INT32 j = dwLowY2; j <= dwUpY2; ++j)
                VisitGrid(i, j, rT2);
        }
        return;
    }
    INT32 dwLowY = dwLowY1, dwUpY = dwUpY1;
    if(rCenter1.dwY < rCenter2.dwY)
    {
        for(INT32 j = dwLowY1; j < dwLowY2; ++j)
        {
            for(INT32 i = dwLeftX1; i <= dwRightX1; ++i)
                VisitGrid(i, j, rT1);
        }
        for(INT32 j = dwUpY2; j > dwUpY1; --j)
        {
            for(INT32 i = dwLeftX2; i <= dwRightX2; ++i)
                VisitGrid(i, j, rT2);
        }
        dwLowY = dwLowY2;
        dwUpY = dwUpY1;
    }
    else if(rCenter1.dwY > rCenter2.dwY)
    {
        for(INT32 j = dwUpY1; j > dwUpY2; --j)
        {
            for(INT32 i = dwLeftX1; i <= dwRightX1; ++i)
                VisitGrid(i, j, rT1);
        }
        for(INT32 j = dwLowY2; j < dwLowY1; ++j)
        {
            for(INT32 i = dwLeftX2; i <= dwRightX2; ++i)
                VisitGrid(i, j, rT2);
        }
        dwLowY = dwLowY1;
        dwUpY = dwUpY2;
    }
    for(INT32 j = dwLowY; j <= dwUpY; ++j)
    {
        if(rCenter1.dwX < rCenter2.dwX)
        {
            for(INT32 i = dwLeftX1; i < dwLeftX2; ++i)
                VisitGrid(i, j, rT1);
            for(INT32 i = dwRightX2; i > dwRightX1; --i)
                VisitGrid(i, j, rT2);
        }
        else if(rCenter1.dwX > rCenter2.dwX)
        {
            for(INT32 i = dwLeftX2; i < dwLeftX1; ++i)
                VisitGrid(i, j, rT2);
            for(INT32 i = dwRightX1; i > dwRightX2; --i)
                VisitGrid(i, j, rT1);
        }
    }
}

CGameMap::CGameMap(SMapInfo& rMapInfo) : 
    _rMapInfo(rMapInfo), _dwLength(rMapInfo.GetLength()), _dwHeight(rMapInfo.GetHeight()), _ppGrid(NULL), _dwAbyssCreateCount(0)
{
    memset(_arParam, 0, sizeof(_arParam));
}

CGameMap::~CGameMap()
{
    FreeObj();
    FreeRegion();
    FreeGrid();
}

bool CGameMap::InitConfig()
{
    if(!AllocGrid())
        return false;
    if(!_rMapInfo.InitMap(shared_from_this()))
        return false;
    return true;
}

bool CGameMap::AllocGrid()
{
    _ppGrid = new CGrid*[_dwLength];
    if(_ppGrid == NULL)
        return false;
    CGrid* pGrid = new CGrid[_dwLength * _dwHeight];
    if(pGrid == NULL)
    {
        delete[] _ppGrid;
        return false;
    }
    for(INT32 i = 0; i < _dwLength; ++i)
        _ppGrid[i] = &pGrid[i * _dwHeight];
    return true;
}

void CGameMap::FreeGrid()
{
    if(_ppGrid != NULL)
        delete[] _ppGrid[0];
    delete[] _ppGrid;
}

CGrid* CGameMap::GetGrid(INT32 dwX, INT32 dwY)
{
    if(dwX >= _dwLength || dwX < 0 || dwY >= _dwHeight || dwY < 0)
        return NULL;
    return &_ppGrid[dwX][dwY];
}

CGrid* CGameMap::GetGrid(const SPoint& rPoint, SCoord* pCoord /*= NULL*/)
{
    SCoord oCoord;
    _rMapInfo.ToIntCoord(rPoint, oCoord);
    if(pCoord != NULL)
        *pCoord = oCoord;
    return GetGrid(oCoord.dwX, oCoord.dwY);
}

bool CGameMap::DiffGrid(const SPoint& rPoint1, const SPoint& rPoint2)
{
    SCoord oCoord1, oCoord2;
    _rMapInfo.ToIntCoord(rPoint1, oCoord1);
    _rMapInfo.ToIntCoord(rPoint2, oCoord2);
    return oCoord1 != oCoord2;
}

bool CGameMap::GridHasObject(const SCoord& rCoord, bool bBaseGrid)
{
    if(bBaseGrid)
    {
        CGrid* pGrid = GetGrid(rCoord.dwX, rCoord.dwY);
        if(pGrid != NULL)
            return pGrid->HasObj();
    }
    else
    {
        for(INT32 dwBaseX = rCoord.dwX * GRID_RATIO_X; dwBaseX < (rCoord.dwX + 1) * GRID_RATIO_X; ++dwBaseX)
        {
            for(INT32 dwBaseY = rCoord.dwY * GRID_RATIO_Y; dwBaseY < (rCoord.dwY + 1) * GRID_RATIO_Y; ++dwBaseY)
            {
                CGrid* pGrid = GetGrid(dwBaseX, dwBaseY);
                if(pGrid != NULL)
                    return pGrid->HasObj();
            }
        }
    }
    return false;
}

void CGameMap::GetGridObject(const SCoord& rCoord, bool bBaseGrid, set<CBaseObjPtr>& rSetObject)
{
    if(bBaseGrid)
    {
        CGrid* pGrid = GetGrid(rCoord.dwX, rCoord.dwY);
        if(pGrid != NULL)
            pGrid->GetAllObj(rSetObject);
    }
    else
    {
        for(INT32 dwBaseX = rCoord.dwX * GRID_RATIO_X; dwBaseX < (rCoord.dwX + 1) * GRID_RATIO_X; ++dwBaseX)
        {
            for(INT32 dwBaseY = rCoord.dwY * GRID_RATIO_Y; dwBaseY < (rCoord.dwY + 1) * GRID_RATIO_Y; ++dwBaseY)
            {
                CGrid* pGrid = GetGrid(dwBaseX, dwBaseY);
                if(pGrid != NULL)
                    pGrid->GetAllObj(rSetObject);
            }
        }
    }
}

bool CGameMap::IsBlockPoint(INT32 dwX, INT32 dwY, bool bBaseGrid /*= false*/) const
{
    if(bBaseGrid)
    {
        if(/*_rMapInfo.IsDungeon() && */IsDynamicBlockPoint(SCoord(dwX, dwY)))
            return true;
        return _rMapInfo.IsBlock(dwX, dwY);
    }
    else
    {
        for(INT32 dwBaseX = dwX * GRID_RATIO_X; dwBaseX < (dwX + 1) * GRID_RATIO_X; ++dwBaseX)
        {
            for(INT32 dwBaseY = dwY * GRID_RATIO_Y; dwBaseY < (dwY + 1) * GRID_RATIO_Y; ++dwBaseY)
            {
                if(_rMapInfo.IsBlock(dwBaseX, dwBaseY))
                    return true;
            }
        }
        return false;
    }
}

bool CGameMap::IsBlockPoint(const SCoord& rCoord, bool bBaseGrid /*= false*/) const
{
    return IsBlockPoint(rCoord.dwX, rCoord.dwY, bBaseGrid);
}

bool CGameMap::IsBlockPoint(const SPoint& rPoint) const
{
    return _rMapInfo.IsBlock(rPoint);
}

bool CGameMap::HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, bool bLoose /*= false*/) const
{
    if(_rMapInfo.IsDungeon() && HasDynamicBlockPoint(rPoint1, rPoint2))
        return true;
    return _rMapInfo.HasBlockPoint(rPoint1, rPoint2, bLoose);
}

bool CGameMap::HasDynamicBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2) const
{
    SCoord oCoord1, oCoord2;
    _rMapInfo.ToIntCoord(rPoint1, oCoord1, true);
    _rMapInfo.ToIntCoord(rPoint2, oCoord2, true);
    return ::HasBlockPoint(oCoord1, oCoord2, [this](INT32 dwX, INT32 dwY)->bool{ return IsDynamicBlockPoint(SCoord(dwX, dwY)); });
    //return ::HasBlockPoint(rPoint1, rPoint2, [this](INT32 dwX, INT32 dwY)->bool{ return IsDynamicBlockPoint(SCoord(dwX, dwY)); });
}

bool CGameMap::IsDynamicBlockPoint(const SCoord& rCoord) const
{
    if(_setBlockCoord.empty())
    {
        return false;
    }
    return _setBlockCoord.find(rCoord) != _setBlockCoord.end();
}

bool CGameMap::IsSafePoint(const SCoord& rCoord, bool bBaseGrid /*= false*/) const
{
    return IsSafePoint(rCoord.dwX, rCoord.dwY, bBaseGrid);
}

bool CGameMap::IsSafePoint(INT32 dwX, INT32 dwY, bool bBaseGrid /*= false*/) const
{
    if(bBaseGrid)
    {
        return _rMapInfo.IsSafe(dwX, dwY);
    }
    else
    {
        for(INT32 dwBaseX = dwX * GRID_RATIO_X; dwBaseX < (dwX + 1) * GRID_RATIO_X; ++dwBaseX)
        {
            for(INT32 dwBaseY = dwY * GRID_RATIO_Y; dwBaseY < (dwY + 1) * GRID_RATIO_Y; ++dwBaseY)
            {
                if(_rMapInfo.IsSafe(dwBaseX, dwBaseY))
                    return true;
            }
        }
        return false;
    }
}

bool CGameMap::NotifySurround(CBaseObj& rBaseObj, const string& strPkg)
{
    CVisitor oVisitor(eVisitRoundPlayer, rBaseObj.shared_from_this());
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rBaseObj, oCollector);
    TVecUINT64 vecUsrID;
    oCollector.GetUserList(vecUsrID);
    if(!vecUsrID.empty())
        return NetMgr.GetGateHandler()->SendClt(&vecUsrID[0], (UINT16)vecUsrID.size(), strPkg.c_str(), (UINT32)strPkg.size());
    return true;
}

bool CGameMap::NotifyMeAndSurround(CCreature& rCreature, const string& strPkg)
{
    CVisitor oVisitor(eVisitPlayer, rCreature.shared_from_this());
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rCreature, oCollector);
    TVecUINT64 vecUsrID;
    oCollector.GetUserList(vecUsrID);
    if(!vecUsrID.empty())
        return NetMgr.GetGateHandler()->SendClt(&vecUsrID[0], (UINT16)vecUsrID.size(), strPkg.c_str(), (UINT32)strPkg.size());
    return true;
}

bool CGameMap::NotifyAllMapPlayer(const string& strPkg)
{
    TVecUINT64 vecUsrID;
    vecUsrID.reserve(_mapRole2Player.size());
    for(auto it = _mapRole2Player.begin(); it != _mapRole2Player.end(); ++it)
    {
        CPlayerPtr pPlayer = it->second.lock();
        if(pPlayer)
            vecUsrID.push_back(pPlayer->GetUserID());
    }

    if(!vecUsrID.empty())
        return NetMgr.GetGateHandler()->SendClt(&vecUsrID[0], (UINT16)vecUsrID.size(), strPkg.c_str(), (UINT32)strPkg.size());
    return true;
}

UINT32 CGameMap::GetPlayerCount()
{
    return _mapRole2Player.size();
}

void CGameMap::AddRegion(ERegionType eType, const SRegionPtr& rRegion)
{
    if(eType < eRegionEnd)
        _arVecRegion[eType].push_back(rRegion);
}

void CGameMap::ClearRegion(ERegionType eType)
{
    if(eType < eRegionEnd)
        _arVecRegion[eType].clear();
}

SRegionPtr CGameMap::GetRegion(ERegionType eType, const SPoint& rPoint)
{
    if(eType >= eRegionEnd)
        return NULL;
    for(size_t i = 0, size = _arVecRegion[eType].size(); i < size; ++i)
    {
        if(_arVecRegion[eType][i]->IsInRegion(rPoint))
            return _arVecRegion[eType][i];
    }
    return NULL;
}

SRegionPtr CGameMap::GetRegion(ERegionType eType, const SPoint& rPoint1, const SPoint& rPoint2)
{
    if(eType >= eRegionEnd)
        return NULL;
    for(size_t i = 0, size = _arVecRegion[eType].size(); i < size; ++i)
    {
        if(_arVecRegion[eType][i]->IntersectRegion(rPoint1, rPoint2))
            return _arVecRegion[eType][i];
    }
    return NULL;
}

void CGameMap::CheckTaskProbeRegion(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn)
{
    for(size_t i = 0, size = _arVecRegion[eRegionProbe].size(); i < size; ++i)
    {
        bool bIn = false;
        if(bCheckIn)
        {
            bIn = _arVecRegion[eRegionProbe][i]->IsInRegion(rPlayer.GetPoint());
        }
        else
        {
            bIn = _arVecRegion[eRegionProbe][i]->IntersectRegion(rPoint1, rPoint2);
        }
        if(bIn)
        {
            SRegionPtr& pRegion = _arVecRegion[eRegionProbe][i];
            if(pRegion != NULL)
            {
                SProbeRegionPtr pProbeRegion = dynamic_pointer_cast<SProbeRegion>(pRegion);
                if(pProbeRegion != NULL)
                    rPlayer.GetUser().GetTaskPkg().OnProbe(pProbeRegion->wTaskID, pProbeRegion->oMapArea);
            }
        }
    }
}

bool CGameMap::CheckRegion(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn)
{
    // TODO:
    //LOG_DBG << "CheckRegion Point, X: " << rPoint.fX << ", Y: " << rPoint.fY;
    SRegionPtr pRegion;
    if(bCheckIn)
    {
        pRegion = GetRegion(eRegionJump,rPlayer.GetPoint());
    }
    else
    { 
        pRegion = GetRegion(eRegionJump, rPoint1, rPoint2);
    }

    if(pRegion != NULL)
    {
        //LOG_DBG << "In Jump Region, X: " << rPoint.fX << ", Y: " << rPoint.fY;
        SJumpRegionPtr pJumpRegion = dynamic_pointer_cast<SJumpRegion>(pRegion);
        if(pJumpRegion != NULL)
        {
            SMapInfoPtr pMapInfo = CMapMgr::GetMapInfo(pJumpRegion->wToMapID);
            if(pMapInfo == NULL)
            {
                LOG_CRI << "Can't find JumpToMap! MapID: " << pJumpRegion->wToMapID;
                return true;
            }
            CGameMapPtr pMap = CMapMgr::GetMap(pJumpRegion->wToMapID);
            if(pMap == NULL)
            {
                LOG_CRI << "Map doesn't exist! ToMapID: " << pJumpRegion->wToMapID;
            }
            else
            {
                const SMapInfo& rMapInfo = pMap->GetMapInfo();
                //bool bCurJumpRegion = GetRegion(eRegionJump, rPlayer.GetPoint()) != NULL;
                do
                {
                    if(rPlayer.GetLevel() < rMapInfo.wLeastlevel)
                    {
                        break;
                    }

                    if(rPlayer.JumpMap(pJumpRegion->wToMapID, pJumpRegion->oToPoint,pJumpRegion->wID))
                        return false;
                    else
                        LOG_CRI << "Jump Map Fails! MapID: " << GetMapID() << ", Point: " << rPoint2 << ", ToMapID: " << pJumpRegion->wToMapID << ", ToPoint: " << pJumpRegion->oToPoint;

                }while(false);
            }
        }
    }
    CheckTaskProbeRegion(rPlayer, rPoint1, rPoint2,bCheckIn);
    if(bCheckIn)
    {
        pRegion = GetRegion(eRegionTaskTrigger,rPlayer.GetPoint());
    }
    else
    { 
        pRegion = GetRegion(eRegionTaskTrigger, rPoint1, rPoint2);
    }
    if(NULL != pRegion)
    {
        SProbeRegionPtr pProbeRegion = dynamic_pointer_cast<SProbeRegion>(pRegion);
        if(pProbeRegion != NULL)
        {
            if(rPlayer.GetUser().GetTaskPkg().CheckAcceptTask(pProbeRegion->wTaskID) == eTaskSucceed)
                rPlayer.GetUser().GetTaskPkg().AcceptTask(pProbeRegion->wTaskID,0);
        }
    }
    return true;
}

void CGameMap::FreeRegion()
{
    for(UINT32 i = 0; i < eRegionEnd; ++i)
        _arVecRegion[i].clear();
}

void CGameMap::FreeObj()
{
    if(!_mapRole2Player.empty())
    {
        LOG_CRI << "Map has player!";
        for(auto it = _mapRole2Player.begin(); it != _mapRole2Player.end();)
        {
            CPlayerPtr pPlayer = it->second.lock();
            ++it;
            if(pPlayer != NULL)
                PlayerDisappear(*pPlayer);
        }
    }
    for(auto it = _mapID2Npc.begin(); it != _mapID2Npc.end(); )
    {
        CNpcPtr pNpc = it->second.lock();
        it++;
        if(pNpc != NULL)
        {
            pNpc->SetMap(NULL);
            pNpc->SetGrid(NULL);
            CNpcMgr::DestroyNpc(*pNpc);
        }
    }

    for(auto it = _mapID2Monster.begin(); it != _mapID2Monster.end(); )
    {
        CMonsterPtr pMonster = it->second.lock();
        it++;
        if(pMonster != NULL)
        {
            pMonster->SetMap(NULL);
            pMonster->SetGrid(NULL);
            CMonsterMgr::DestroyMonster(pMonster);
        }
    }
    for(auto it = _mapID2Switcher.begin(); it != _mapID2Switcher.end(); )
    {
        CSwitcherPtr pSwitcher = it->second.lock();
        it++;
        if(pSwitcher != NULL)
        {
            pSwitcher->SetMap(NULL);
            pSwitcher->SetGrid(NULL);
            CSwitcherMgr::DestroySwitcher(*pSwitcher);
        }
    }
    for(auto it = _mapID2Gather.begin(); it != _mapID2Gather.end(); )
    {
        IGatherPtr pGather = it->second.lock();
        it++;
        if(pGather != NULL)
        {
            pGather->SetMap(NULL);
            pGather->SetGrid(NULL);
            CGatherMgr::DestroyGather(*pGather);
        }
    }
    for(auto it = _mapID2Blocker.begin(); it != _mapID2Blocker.end();)
    {
        CBlockerPtr pBlocker = it->second.lock();
        it++;
        if(pBlocker != NULL)
        {
            pBlocker->SetMap(NULL);
            pBlocker->SetGrid(NULL);
            CBlockerMgr::DestroyBlocker(*pBlocker);
        }
    }
    for(auto it = _mapID2Area.begin(); it != _mapID2Area.end(); )
    {
        CMapAreaPtr pArea = it->second.lock();
        it++;
        if(pArea != NULL)
        {
            pArea->SetMap(NULL);
            pArea->SetGrid(NULL);
            g_AreaManager.Destroy(*pArea);
        }
    }
}
bool CGameMap::IsInSafeArea(const SPoint& rPoint)
{ 
    for(auto it = _mapID2Area.begin(); it != _mapID2Area.end(); ++it)
    {
        CMapAreaPtr pArea = it->second.lock();
        if(pArea != NULL)
        {
            if(pArea->IsSafe() && pArea->IsInRegion(rPoint))
            {
                return true;
            }
        }
    }
    return false;
}

bool CGameMap::PlaceMapObject(CBaseObj& rBaseObj, TVecUINT64& rVecUsrID, set<CBaseObjPtr>* pSetObj /*= NULL*/)
{
    SPoint& rPoint = rBaseObj.GetPoint();
    SCoord oCoord;
    CGrid* pGrid = GetGrid(rPoint, &oCoord);
    if(pGrid == NULL)
    {
        LOG_CRI << "GetGrid Fails! Object: " << rBaseObj;
        return false;
    }
    rBaseObj.SetMap(shared_from_this());
    rBaseObj.SetCoord(oCoord);
    CBaseObjPtr pBaseObj = rBaseObj.shared_from_this();
    if(!pGrid->AddObj(pBaseObj))
        LOG_CRI << "Add Fails! Object: " << rBaseObj;

    CVisitor oVisitor(eVisitMeet, pBaseObj);
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(oCoord, _rMapInfo.GetBroadCastRadius(), oCollector);
    oCollector.GetUserList(rVecUsrID);
    if(pSetObj != NULL)
        *pSetObj = move(oCollector.GetObjSet());
    return true;
}

bool CGameMap::RemoveMapObject(CBaseObj& rBaseObj, TVecUINT64& rVecUsrID)
{
    CGameMapPtr pMap = rBaseObj.GetMap();
    if(pMap == NULL)
        return true;
    if(pMap != shared_from_this())
    {
        LOG_CRI << "pMap is not match!";
        return false;
    }
    SCoord oCoord;
    if(!rBaseObj.GetCoord(oCoord))
        DebugBreak();
    CGrid* pGrid = rBaseObj.GetGrid();
    if(pGrid == NULL)
    {
        LOG_CRI << "Grid is NULL! " << rBaseObj;
        return true;
    }
#if COORDINATE_CHECK
    CGrid* pNewGrid = GetGrid(oCoord.dwX, oCoord.dwY);
    if(pGrid != pNewGrid)
    {
        LOG_CRI << "Grid not match! Object: " << rBaseObj;
        PRINT_CALL_STACK;
    }
#endif
    CBaseObjPtr pBaseObj = rBaseObj.shared_from_this();
    if(!pGrid->DelObj(pBaseObj))
        LOG_CRI << "Delete Fails! Object: " << rBaseObj;
    CVisitor oVisitor(eVisitMiss, pBaseObj);
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(oCoord, _rMapInfo.GetBroadCastRadius(), oCollector);
    oCollector.GetUserList(rVecUsrID);
    rBaseObj.SetMap(CGameMapPtr(NULL));
    rBaseObj.SetCoord(SCoord());
    return true;
}

bool CGameMap::CreatureStopMove(CCreature& rCreature, const SPoint& rPoint, float fDir)
{
    const SPoint* pPoint = &rCreature.GetPoint();
    if(!HasBlockPoint(rCreature.GetPoint(), rPoint))
    {
        rCreature.SetDir(fDir);
        if(CreatureMoveTo(rCreature, rPoint, true))
            pPoint = &rPoint;
    }
    CVisitor oVisitor(eVisitMeet, rCreature.shared_from_this());
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rCreature, oCollector);
    TVecUINT64 vecUsrID;
    oCollector.GetUserList(vecUsrID);
    if(!vecUsrID.empty())
        return g_MapProtS.SendClt_NotifyCreatureStop(&vecUsrID[0], (UINT16)vecUsrID.size(), rCreature.GetCreatureID(), *pPoint);
    return true;
}

bool CGameMap::CreatureMoveTo(CCreature& rCreature, const vector<SPoint>& rVecPoint, float fDir, bool bStart)
{
    if(rVecPoint.empty())
    {
        LOG_CRI << "rVecPoint is empty!";
        return false;
    }
    SPoint& rOrigPoint = rCreature.GetPoint();
    const SPoint& rCurPoint = rVecPoint[0];
    rCreature.SetDir(fDir);

    if(!_rMapInfo.IsInMapArea(rCurPoint))
    {
        CPlayerPtr pPlayer = ToPtr<CPlayer>(rCreature);
        if(pPlayer != NULL)
        {
            TVecPosition vecPosition;
            for(size_t i = 0;i < rVecPoint.size();i++)
            {
                SPosition sPosition;
                sPosition.fX = rVecPoint[0].fX;
                sPosition.fX = rVecPoint[0].fY;
                vecPosition.push_back(sPosition);
            }
            pPlayer->NotifyMeAndSurround(g_MapProtS.BuildPkg_PlayerMoveFail(pPlayer->GetRoleID(), rOrigPoint,vecPosition));
            rCreature.GetWalker().ClearPath();
        }
        if(pPlayer == NULL || !pPlayer->IsRobot())
            LOG_CRI << "Point is not in map area: " << rCurPoint;
        return false;
    }

    bool bBlocked = false;
    if(rCreature.GetWalker().CheckBlock() && rCreature.GetWalker().IsStepBlocked())
        bBlocked = true;
    switch(rCreature.GetObjType())
    {
        case eObjPlayer:
            {
                CPlayerPtr pPlayer = ToPtr<CPlayer>(rCreature);
                if(pPlayer != NULL)
                {
                    if(bBlocked && !pPlayer->IsRobot())
                    {
                        LOG_CRI << "Point is blocked, from " << rOrigPoint << ", to " << rCurPoint << ", MapID: " << GetMapID() << ", RoleID:" << pPlayer->GetRoleID();
                        TVecPosition vecPosition;
                        for(size_t i = 0;i < rVecPoint.size();i++)
                        {
                            SPosition sPosition;
                            sPosition.fX = rVecPoint[0].fX;
                            sPosition.fX = rVecPoint[0].fY;
                            vecPosition.push_back(sPosition);
                        }
                        pPlayer->NotifyMeAndSurround(g_MapProtS.BuildPkg_PlayerMoveFail(pPlayer->GetRoleID(), rOrigPoint,vecPosition));

                        rCreature.GetWalker().ClearPath();
                        return false;
                    }
                    if(!CheckAllPosForMove(*pPlayer, rOrigPoint, rCurPoint))
                        return false;

                }
            }
            break;
        case eObjMonster:
            if(bBlocked)
            {
                LOG_DBG << "Point is blocked, from " << rOrigPoint << ", to " << rCurPoint << ", Monster Creature:" << rCreature;
                CreatureStopMove(rCreature, rOrigPoint, fDir);
                return false;
            }
            break;
        default:
            break;
    }

    if(bStart)
    {
        CVisitor oVisitor(eVisitNotify, rCreature.shared_from_this());
        CCollector<CVisitor> oCollector(oVisitor);
        VisitArea(rCreature, oCollector);
        TVecUINT64 vecUsrID;
        oCollector.GetUserList(vecUsrID);
        if(!vecUsrID.empty())
        {
            size_t stStart = rVecPoint.size() > 1 ? 1 : 0;

            //世界boss丢弃移动包处理
            if(10 == GetMapID() && vecUsrID.size()>20)
            {
                vecUsrID.resize(20);
            }
            g_MapProtS.SendClt_NotifyCreatureMove(&vecUsrID[0], (UINT16)vecUsrID.size(), rCreature.GetCreatureID(), SPoint::ToProtVecPoint(rVecPoint, stStart));
            //LOG_DBG << "Start NotifyCreatureMove: " << rVecPoint;
        }
    }
    return CreatureMoveTo(rCreature, rCurPoint, true, &rVecPoint);
}

bool CGameMap::CreatureMoveTo(CCreature& rCreature, const SPoint& rCurPoint, bool bNotify /*= true*/, const vector<SPoint>* pVecPoint /*= NULL*/)
{
    SPoint oOrigPoint = rCreature.GetPoint();
    if(oOrigPoint == rCurPoint)
        return true;

    CGrid* pOrigGrid = rCreature.GetGrid();
    if(pOrigGrid == NULL)
    {
        LOG_CRI << "Creature is not on Map! " << rCreature.GetDescription();
        return false;
    }
    SCoord oOrigCoord;
    if(!rCreature.GetCoord(oOrigCoord))
        DebugBreak();

#if COORDINATE_CHECK
    if(pOrigGrid != GetGrid(oOrigCoord.dwX, oOrigCoord.dwY))
        LOG_CRI << "Grid not match! dwOriX:" << oOrigCoord.dwX << ", dwOriY:" << oOrigCoord.dwY << rCreature.GetDescription();
#endif

    SCoord oCurCoord;
    CGrid* pCurGrid = GetGrid(rCurPoint, &oCurCoord);
    if(pCurGrid == NULL)
    {
        LOG_CRI << "Grid doesn't exist! X: " << oCurCoord.dwX << ", Y: " << oCurCoord.dwY << rCreature.GetDescription();
        return false;
    }

    rCreature.SetPoint(rCurPoint);
    /*
       if(rCreature.GetObjType() == eObjPlayer)
       LOG_INF << rCreature.GetLocaleName() << ", Move From: " << oOrigPoint << " To: " << rCurPoint << ", Tick: " << GetTickCount();
       */

    if(pOrigGrid == pCurGrid)
        return true;

    if(!pOrigGrid->DelObj(rCreature.shared_from_this()))
        LOG_CRI << "DelObj Fails:" << rCreature.GetDescription();
    if(!pCurGrid->AddObj(rCreature.shared_from_this()))
        LOG_CRI << "AddObj Fails:" << rCreature.GetDescription();
    rCreature.SetCoord(oCurCoord);

    if(bNotify)
    {
        CVisitor oMeetVisitor(eVisitMeet, rCreature.shared_from_this());
        CCollector<CVisitor> oMeetCollector(oMeetVisitor);
        CVisitor oLeaveVisitor(eVisitMeet, rCreature.shared_from_this());
        CCollector<CVisitor> oLeaveCollector(oLeaveVisitor);
        VisitDiffArea(oOrigCoord, oCurCoord, _rMapInfo.GetBroadCastRadius(), oLeaveCollector, oMeetCollector);

        TVecUINT64 vecMeetUsrID, vecLeaveUsrID;
        oMeetCollector.GetUserList(vecMeetUsrID);
        oLeaveCollector.GetUserList(vecLeaveUsrID);
        set<CBaseObjPtr> setMeetObj = move(oMeetCollector.GetObjSet());
        set<CBaseObjPtr> setLeaveObj = move(oLeaveCollector.GetObjSet());
        g_MapProtS.NotifyCreatureDisappear(vecLeaveUsrID, rCreature, false);
        switch(rCreature.GetObjType())
        {
            case eObjPlayer:
                {
                    CPlayer& rPlayer = (CPlayer&)rCreature;
                    g_MapProtS.NotifyPlayerAppear(vecMeetUsrID, rPlayer, false);
                    g_MapProtS.NotifySurroundAppear(rPlayer, setMeetObj);
                    g_MapProtS.NotifySurroundDisappear(rPlayer, setLeaveObj);
                    rPlayer.UpdateBaseInfo2DB();
                }
                break;
            case eObjMonster:
                {
                    CMonster& rMonster = (CMonster&)rCreature;
                    g_MapProtS.NotifyMonsterAppear(vecMeetUsrID, rMonster, false);
                }
                break;
            case eObjNpc:
                {
                    CNpc& rNpc = (CNpc&)rCreature;
                    g_MapProtS.NotifyNpcAppear(vecMeetUsrID, rNpc, false);
                }
                break;
            default:
                break;
        }
        if(pVecPoint != NULL && !vecMeetUsrID.empty())
        {
            //for(int i = 0; i<100;i++)
            {
            g_MapProtS.SendClt_NotifyCreatureMove(&vecMeetUsrID[0], (UINT16)vecMeetUsrID.size(), rCreature.GetCreatureID(), SPoint::ToProtVecPoint(*pVecPoint));
            }
            //LOG_DBG << "Meet NotifyCreatureMove: " << *pVecPoint;
        }
    }
    return true;
}

void CGameMap::CreatureForceMoveTo(CCreature& rCreature, const SPoint& rCurPoint, bool bNotify /*= true*/)
{
    rCreature.GetWalker().ClearPath();
    CreatureMoveTo(rCreature, rCurPoint, bNotify);
}

bool CGameMap::PlayerAppear(CPlayer& rPlayer, bool bAppear /* = true */)
{
    TVecUINT64 vecUsrID;
    set<CBaseObjPtr> setObj;
    //

    SPoint rPoint = rPlayer.GetPoint();
    if(rPoint.fX == 0 && rPoint.fY == 0)
    {
        SPoint oRealivePoint =  _rMapInfo.GetRealivePoint();
        rPlayer.SetPoint(oRealivePoint);
        rPoint = rPlayer.GetPoint();
    }
 
    if(IsBlockPoint(rPoint))
    {
        bool bRet = GetRandPoint(rPoint);
        if(!bRet)
        {
            LOG_CRI << "Place Player fails! UserID:" << GetUserDesc(rPlayer.GetUserID())<<" fx:"<<rPoint.fX<<" fy:"<<rPoint.fY<<"Map:"<<_rMapInfo.GetName();

        }
        else
        {
            rPlayer.SetPoint(rPoint);
        }
    }

    if(!PlaceMapObject(rPlayer, vecUsrID, &setObj))
    {
        LOG_CRI << "Place Player fails! UserID: " << GetUserDesc(rPlayer.GetUserID());
        return false;
    }
    if(!_mapRole2Player.insert(make_pair(rPlayer.GetRoleID(), ToThisPtr(rPlayer))).second)
        LOG_CRI << "Player already exists! UserID: " << GetUserDesc(rPlayer.GetUserID());
    rPlayer.SetPlayerState(ePlayerInGame);
    SPlayerAppear appear;
    rPlayer.GetPlayerAppear(appear);
    rPlayer.SendPkg(g_MapProtS.BuildPkg_NotifyAppear(rPlayer.GetRoleID(), appear, rPlayer.GetPoint(), rPlayer.GetDir(), rPlayer.GetAppearState()));
    if(rPlayer.HasAppearState(eAppearGhost))
        rPlayer.OnEnterGhost();
    if (bAppear)
        g_MapProtS.NotifyPlayerAppear(vecUsrID, rPlayer, true);
    g_MapProtS.NotifySurroundAppear(rPlayer, setObj);
    BroadcastMapIdx();
    return true;
}

bool CGameMap::PlayerDisappear(CPlayer& rPlayer)
{
    if(!rPlayer.IsOnMap())
        return true;
    bool bRet = true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rPlayer, vecUsrID))
    {
        LOG_CRI << "Remove Player fails! UserID: " << GetUserDesc(rPlayer.GetUserID());
        bRet = false;
    }
    if(Config._bInited) //关闭时不广播
        g_MapProtS.NotifyCreatureDisappear(vecUsrID, rPlayer, false);
    if(_mapRole2Player.erase(rPlayer.GetRoleID()) == 0)
    {
        LOG_CRI << "Player not exists! UserID: " << GetUserDesc(rPlayer.GetUserID());
        bRet = false;
    }
    return bRet;
}

bool CGameMap::PlayerReappear(CPlayer& rPlayer)
{
    if (_mapRole2Player.find(rPlayer.GetRoleID()) == _mapRole2Player.end())
    {
        return PlayerAppear(rPlayer);
    }
    TVecUINT64 vecUsrID;
    CVisitor oVisitor(eVisitMeet, ToThisPtr(rPlayer));
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rPlayer, oCollector);
    oCollector.GetUserList(vecUsrID);
    rPlayer.SetPlayerState(ePlayerInGame);
    UINT32 dwAppearState = rPlayer.GetAppearState();
    SPlayerAppear appear;
    rPlayer.GetPlayerAppear(appear);
    rPlayer.SendPkg(g_MapProtS.BuildPkg_NotifyAppear(rPlayer.GetRoleID(), appear, rPlayer.GetPoint(), rPlayer.GetDir(), dwAppearState));
    if(rPlayer.HasAppearState(eAppearGhost))
        rPlayer.OnEnterGhost();
    g_MapProtS.NotifySurroundAppear(rPlayer, oCollector.GetObjSet());
    return true;
}

bool CGameMap::AppearToSurround(CPlayer& rPlayer)
{
    UINT32 dwAppearState = rPlayer.GetAppearState();
    SPlayerAppear appear;
    rPlayer.GetPlayerAppear(appear);
    rPlayer.SendPkg(g_MapProtS.BuildPkg_NotifyAppear(rPlayer.GetRoleID(), appear, rPlayer.GetPoint(), rPlayer.GetDir(), dwAppearState));
    NotifySurround(rPlayer, g_MapProtS.BuildPkg_NotifyAppear(rPlayer.GetRoleID(), appear, rPlayer.GetPoint(), rPlayer.GetDir(), dwAppearState));
    return true;
}

bool CGameMap::PlacePlayer(CPlayer& rPlayer)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rPlayer, vecUsrID))
    {
        LOG_CRI << "Place Player fails! qwRoleID: " << rPlayer.GetRoleID();
        return false;
    }
    rPlayer.SetPlayerState(ePlayerInGame);
    rPlayer.SetMap(shared_from_this());
    g_MapProtS.NotifyPlayerAppear(vecUsrID, rPlayer, true);
    if(!_mapRole2Player.insert(make_pair(rPlayer.GetRoleID(), ToThisPtr(rPlayer))).second)
        LOG_CRI << "Player already exists! qwRoleID: " << rPlayer.GetRoleID();

    return true;
}

bool CGameMap::MonsterEnter(CMonster& rMonster, const SPoint* pPoint /*= NULL*/)
{
    rMonster.SetMap(shared_from_this());
    rMonster.SetBornMap(shared_from_this());
    if(pPoint != NULL)
    {
        rMonster.SetPoint(*pPoint);
    }
    return MonsterAppear(rMonster);
}

bool CGameMap::MonsterAppear(CMonster& rMonster)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rMonster, vecUsrID))
    {
        LOG_CRI << "Place Monster fails! qwCreatureID: " << rMonster.GetCreatureID();
        return false;
    }
    rMonster.CreateAI();
    g_MapProtS.NotifyMonsterAppear(vecUsrID, rMonster, true);
    if(!_mapID2Monster.insert(make_pair(rMonster.GetCreatureID(), ToThisPtr(rMonster))).second)
        LOG_CRI << "Monster already exists!";
    AddMapIndex(rMonster.GetMapIdx());
    return true;
}

bool CGameMap::MonsterDisappear(CMonster& rMonster, bool bFade)
{
    if(!rMonster.IsOnMap())
        return true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rMonster, vecUsrID))
    {
        LOG_CRI << "Remove Monster fails! qwCreatureID: " << rMonster.GetCreatureID();
        return false;
    }
    g_MapProtS.NotifyCreatureDisappear(vecUsrID, rMonster, bFade);
    if(_mapID2Monster.erase(rMonster.GetCreatureID()) == 0)
        LOG_CRI << "Monster not exists!";
    RemoveMapIndex(rMonster.GetMapIdx());
    BroadcastMapIdx();
    CMonsterPtr pMonster = dynamic_pointer_cast<CMonster>(rMonster.shared_from_this());
    if(pMonster)
    {
        CMonsterMgr::DestroyMonster(pMonster);
    }
    else
    {
        LOG_CRI <<"Get Monster self ptr err";
    }
    return true;
}

void CGameMap::ClearAllMonsters()
{
    auto it = _mapID2Monster.begin();
    while(it != _mapID2Monster.end())
    {
        CMonsterPtr pMonster = it->second.lock();
        ++it;
        if(pMonster != NULL)
            MonsterDisappear(*pMonster, false);
    }
}

UINT64 CGameMap::AddMonster(UINT16 wCroup, const SPoint* sPoint)
{
    if(sPoint != NULL)
    {
        return  _rMapInfo.CreateMonster(shared_from_this(),wCroup,sPoint->fX,sPoint->fY,NULL);
    }
    return 0;
}

UINT64 CGameMap::AddMonsterIfNotExist(UINT16 wCroup, const SPoint* sPoint)
{
    TVecUINT64 vecID;
    GetMonsterVecByGroup(wCroup,vecID);
    if(!vecID.empty())
    {
        return 0;
    }
    if(sPoint != NULL)
    {
        return  _rMapInfo.CreateMonster(shared_from_this(),wCroup,sPoint->fX,sPoint->fY,NULL);
    }
    return 0;
}



bool CGameMap::DelMonster(UINT64 qwCreatureID)
{
    CMonsterPtr pMonster = GetMonster(qwCreatureID);
    if(pMonster != NULL)
    {
        pMonster->OnDie(*pMonster);
        return true;
    }
    // TODO:
    return false;
}

void CGameMap::GetMonsterVecByGroup(UINT16 wGroup,TVecUINT64& vecMonster)
{
    for (auto it = _mapID2Monster.begin() ;it != _mapID2Monster.end();it++)
    {
        CMonsterPtr pMonster = (it->second).lock();
        if(pMonster == NULL)
        {
            continue;
        }
        if(pMonster->GetGroupID() == wGroup)
        {
            vecMonster.push_back(it->first);
        }
    }

}

void CGameMap::DelNpcById(UINT16 wNpc)
{
    TVecUINT64 vecDel;
    for(auto it = _mapID2Npc.begin(); it != _mapID2Npc.end();it++)
    {
        CNpcPtr pNpc = it->second.lock();
        if(pNpc && pNpc->GetNpcID() == wNpc)
        {
            vecDel.push_back(it->first);
        }
    }
    for(auto it = vecDel.begin(); it != vecDel.end() ;it++)
    {
        DelNpc(*it);
    }

}
void CGameMap::DelMonsterByGroup(UINT16 wGroup)
{
    TVecUINT64 vecMonster;
    GetMonsterVecByGroup(wGroup,vecMonster);
    for(auto it = vecMonster.begin();it != vecMonster.end();it++)
    {
        DelMonster(*it);
    }
}
bool CGameMap::AddGather(UINT16 wGather, const SPoint* pPoint)
{
    if(pPoint != NULL)
    {
        return  _rMapInfo.CreateGather(shared_from_this(),wGather,0,pPoint->fX,pPoint->fY);
    }
    return false;
}

bool CGameMap::DelGather(UINT32 dwCreatureID)
{
    IGatherPtr pGather = FindGather(dwCreatureID);
    if(NULL != pGather)
    {
        pGather->Disappear();
    }
    return true;
}

void CGameMap::GetGatherVecByGather(UINT16 wGather,TVecUINT32& vecGather)
{
    for (auto it = _mapID2Gather.begin() ;it != _mapID2Gather.end();it++)
    {
        IGatherPtr pGather = (it->second).lock();
        if(pGather == NULL)
        {
            continue;
        }
        if(pGather->GetGatherID() == wGather)
        {
            vecGather.push_back(it->first);
        }
    }
}

void CGameMap::DelGatherByGather(UINT16 wGather)
{
    TVecUINT32 vecGather;
    GetGatherVecByGather(wGather,vecGather);
    for(auto it = vecGather.begin();it != vecGather.end();it++)
    {
        DelGather(*it);
    }
}


bool CGameMap::MonsterDisappearByID(UINT64 qwCreatureID, bool bFade)
{
    CMonsterPtr pMonster = GetMonster(qwCreatureID);
    if (!pMonster)
        return false;
    return MonsterDisappear(*pMonster, bFade);
}
bool CGameMap::SwitcherAppear(CSwitcher& rSwitcher)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rSwitcher, vecUsrID))
    {
        LOG_CRI << "Place Switcher fails! dwInstID: " << rSwitcher.GetInstID();
        return false;
    }
    g_MapProtS.NotifySwitcherAppear(vecUsrID, rSwitcher, true);
    if(!_mapID2Switcher.insert(make_pair(rSwitcher.GetInstID(), ToThisPtr<CSwitcher>(rSwitcher))).second)
        LOG_CRI << "Switcher already exists!";
    return true;
}

void CGameMap::AddSwitcherByIndex(UINT8 byIndex)
{
    const TVecDgnJumpPoint &rvec =  _rMapInfo.vecDgnJumpPoint;
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        const SDgnJumpPoint& rPoint = *it;
        if( byIndex == rPoint.byIndex)
        {
            _rMapInfo.CreateSwitcher(shared_from_this(),rPoint);
        }
    }


}
void CGameMap::SwitcherDestroyByIndex(UINT8 byIndex)
{
    TVecUINT64 vecDel;
    for(auto it = _mapID2Switcher.begin();it !=  _mapID2Switcher.end();it++)
    {
        CSwitcherPtr pSwitcher = it->second.lock();
        if( pSwitcher &&  pSwitcher->GetIndex() == byIndex)
        {
            vecDel.push_back(it->first);
        }
    }
    for(auto it = vecDel.begin(); it != vecDel.end(); it++)
    {
        auto iter = _mapID2Switcher.find(*it);
        if(iter != _mapID2Switcher.end())
        {
            CSwitcherPtr pSwitcher = iter->second.lock();
            if(pSwitcher)
            {
                SwitcherDisappear(*pSwitcher);
            }

        }

    }

}


bool CGameMap::SwitcherDisappear(CSwitcher& rSwitcher)
{
    if(!rSwitcher.IsOnMap())
        return true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rSwitcher, vecUsrID))
    {
        LOG_CRI << "Remove Switcher fails! dwInstID: " << rSwitcher.GetInstID();
        return false;
    }
    g_MapProtS.NotifySwitcherDisappear(vecUsrID, rSwitcher, true);
    if(_mapID2Switcher.erase(rSwitcher.GetInstID()) == 0)
        LOG_CRI << "Switcher not exists!";
    CSwitcherMgr::DestroySwitcher(rSwitcher);
    return true;
}

void CGameMap::ClearAllSwitchers()
{
    while(!_mapID2Switcher.empty())
    {
        auto itr = _mapID2Switcher.begin();
        CSwitcherPtr pSwitcher = itr->second.lock();
        assert(pSwitcher);
        SwitcherDisappear(*pSwitcher);
    }
}

IGatherPtr CGameMap::FindGather(UINT32 dwInstID)
{
    auto it = _mapID2Gather.find(dwInstID);
    if(it != _mapID2Gather.end())
        return it->second.lock();
    return NULL;
}

bool CGameMap::GatherAppear(IGather& rGather)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rGather, vecUsrID))
    {
        LOG_CRI << "Place Gather fails!"<<" Map :" << GetMapID() <<" dwInstID: " << rGather.GetInstID() << "Gather ID:" << rGather.GetGatherID();
        return false;
    }
    g_MapProtS.NotifyGatherAppear(vecUsrID, rGather, true);
    if(!_mapID2Gather.insert(make_pair(rGather.GetInstID(), ToThisPtr(rGather))).second)
        LOG_CRI << "Gather already exists!";
    return true;
}
bool CGameMap::GatherChange(IGather& rGather)
{
    CVisitor oVisitor(eVisitNotify, rGather.shared_from_this());
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rGather,oCollector);
    TVecUINT64 vecUsrID;
    oCollector.GetUserList(vecUsrID);
    g_MapProtS.NotifyGatherChange(vecUsrID, rGather);
    return true;
}
bool CGameMap::MonsterChange(CMonster& rMonster)
{
    CVisitor oVisitor(eVisitNotify, rMonster.shared_from_this());
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rMonster,oCollector);
    TVecUINT64 vecUsrID;
    oCollector.GetUserList(vecUsrID);
    g_MapProtS.NotifyMonsterChange(vecUsrID, rMonster);
    return true;
}
bool CGameMap::GatherDisappear(IGather& rGather)
{
    if(!rGather.IsOnMap())
        return true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rGather, vecUsrID))
        return false;
    g_MapProtS.NotifyGatherDisappear(vecUsrID, rGather, true);
    if(_mapID2Gather.erase(rGather.GetInstID()) == 0)
        LOG_CRI << "Gather not exists!";
    rGather.CancelAll();
    CGatherMgr::DestroyGather(rGather);
    return true;
}

void CGameMap::AddGatherByIndex(UINT8 byIndex)
{
    const TVecGatherPoint &rvec =  _rMapInfo.vecGatherPoint;
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        const SGatherPoint& rGatherPoint = *it;
        if(rGatherPoint.byIndex == byIndex)
        {
            _rMapInfo.CreateGather(shared_from_this(),rGatherPoint.wGatherID,byIndex,rGatherPoint.fX,rGatherPoint.fY);
        }
    }
}

void CGameMap::GatherDestroyByIndex(UINT8 byIndex)
{
    TVecUINT32 vecDel;
    for(auto it = _mapID2Gather.begin();it != _mapID2Gather.end();it++)
    {
        IGatherPtr pGather = it->second.lock();
        if(NULL != pGather)
        {
            if(pGather->byIndex() == byIndex)
            {
                vecDel.push_back(it->first);
            }
        }
    }
    for(auto it = vecDel.begin();it != vecDel.end();it++)
    {
        auto iter = _mapID2Gather.find(*it);
        if(iter == _mapID2Gather.end())
            continue;
        IGatherPtr pGather = iter->second.lock();
        GatherDisappear(*pGather);  


    }
}

void CGameMap::ClearAllGathers()
{
    while(!_mapID2Gather.empty())
    {
        auto itr = _mapID2Gather.begin();
        IGatherPtr pGather = itr->second.lock();
        assert(pGather);
        GatherDisappear(*pGather);
    }
}

bool CGameMap::BlockerAppear(CBlocker& rBlocker)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rBlocker, vecUsrID))
    {
        LOG_CRI << "Place Blocker fails! dwInstID: " << rBlocker.GetInstID() <<" map ID :" << GetMapID();
        return false;
    }
    //LOG_CRI << "Place Blocker ! dwInstID: " << rBlocker.GetInstID();
    g_MapProtS.NotifyBlockerAppear(vecUsrID, rBlocker, true);
    if(!_mapID2Blocker.insert(make_pair(rBlocker.GetInstID(), ToThisPtr(rBlocker))).second)
        LOG_CRI << "Blocker already exists!";
    return true;
}
bool CGameMap::CreateBlockByIndex(UINT16 wIndex)
{
    const TVecBlockerPoint &rvec =  _rMapInfo.vecBlockerPoint;
    const SBlockerPoint* pPoint = NULL;
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        const SBlockerPoint* pCheckPoint = &(*it);
        if(pCheckPoint->wIndex == wIndex)
        {
            pPoint = pCheckPoint;
            break;
        }
    }
    if(pPoint == NULL)
    {
        return false;
    }
    return _rMapInfo.CreateBlock(shared_from_this(),*pPoint);  
}

CBlockerPtr CGameMap::GetBlockById(UINT32 wID)
{
    auto it = _mapID2Blocker.find(wID);
    if(it == _mapID2Blocker.end())
    {
        return NULL;
    }
    return it->second.lock();
}

bool CGameMap::DestroyBlock(UINT32 wID)
{
    CBlockerPtr pBlock = GetBlockById(wID);
    if(pBlock == NULL)
        return false;
    pBlock->Disappear();
    return true;
}
void CGameMap::DestroyBlockByIndex(UINT16 wIndex)
{
    TVecUINT32 vecDestroy;
    for(auto it = _mapID2Blocker.begin();it != _mapID2Blocker.end(); it++)
    {
        CBlockerPtr pBlock = (it->second).lock();
        if(pBlock != NULL  && pBlock->GetIndex() == wIndex)
        {
            vecDestroy.push_back(it->first);
        }

    }
    for(auto pos = vecDestroy.begin();pos != vecDestroy.end();pos ++)
    {
        DestroyBlock(*pos);
    };
}

bool CGameMap::BlockerDisappear(CBlocker& rBlocker)
{
    if(!rBlocker.IsOnMap())
    {
        LOG_CRI << "Blocker  not IsOnMap()";
        return true;
    }
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rBlocker, vecUsrID))
    {
        LOG_CRI << "Remove Blocker fails! dwInstID: " << rBlocker.GetInstID();
        return false;
    }
    g_MapProtS.NotifyBlockerDisappear(vecUsrID, rBlocker, true);
    if(_mapID2Blocker.erase(rBlocker.GetInstID()) == 0)
        LOG_CRI << "Blocker not exists!";
    CBlockerMgr::DestroyBlocker(rBlocker);
    return true;
}

void CGameMap::ClearAllBlockers()
{
    auto it = _mapID2Blocker.begin();
    while(it != _mapID2Blocker.end())
    {
        CBlockerPtr pBlocker = it->second.lock();
        ++it;
        if(pBlocker != NULL)
        {
            //BlockerDisappear(*pBlocker);
            pBlocker->Disappear();
        }
    }
}
/////
bool CGameMap::AreaAppear(CMapArea& rArea)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rArea, vecUsrID))
    {
        LOG_CRI << "Place Area fails! dwInstID: " << rArea.GetInstID();
        return false;
    }
    g_MapProtS.NotifyAreaAppear(vecUsrID, rArea);
    if(!_mapID2Area.insert(make_pair(rArea.GetInstID(), ToThisPtr(rArea))).second)
        LOG_CRI << "Area already exists!";
    return true;
}
bool CGameMap::CreateAreaByIndex(UINT16 wIndex)
{
    const TVecAreaPoint &rvec =  _rMapInfo.vecAreaPoint;
    const SAreaPoint* pPoint = NULL;
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        const SAreaPoint* pCheckPoint = &(*it);
        if(pCheckPoint->wIndex == wIndex)
        {
            pPoint = pCheckPoint;
            break;
        }
    }
    if(pPoint == NULL)
    {
        return false;
    }
    return _rMapInfo.CreateArea(shared_from_this(),*pPoint);  
}

CMapAreaPtr CGameMap::GetAreaById(UINT32 wID)
{
    auto it = _mapID2Area.find(wID);
    if(it == _mapID2Area.end())
    {
        return NULL;
    }
    return it->second.lock();
}

bool CGameMap::DestroyArea(UINT32 wID)
{
    CMapAreaPtr pArea = GetAreaById(wID);
    if(pArea == NULL)
        return false;
    pArea->Disappear();
    return true;
}
void CGameMap::DestroyAreaByIndex(UINT16 wIndex)
{
    TVecUINT32 vecDestroy;
    for(auto it = _mapID2Area.begin();it != _mapID2Area.end(); it++)
    {
        CMapAreaPtr pArea = (it->second).lock();
        if(pArea != NULL  && pArea->GetIndex() == wIndex)
        {
            vecDestroy.push_back(it->first);
        }

    }
    for(auto pos = vecDestroy.begin();pos != vecDestroy.end();pos ++)
    {
        DestroyArea(*pos);
    };
}

bool CGameMap::AreaDisappear(CMapArea& rArea)
{
    if(!rArea.IsOnMap())
        return true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rArea, vecUsrID))
    {
        LOG_CRI << "Remove Area fails! dwInstID: " << rArea.GetInstID();
        return false;
    }
    g_MapProtS.NotifyAreaDisappear(vecUsrID, rArea);
    if(_mapID2Area.erase(rArea.GetInstID()) == 0)
        LOG_CRI << "Area not exists!";
    g_AreaManager.Destroy(rArea);
    return true;
}

void CGameMap::ClearAllAreas()
{
    auto it = _mapID2Area.begin();
    while(it != _mapID2Area.end())
    {
        CMapAreaPtr pArea = it->second.lock();
        ++it;
        if(pArea != NULL)
            AreaDisappear(*pArea);
    }
}
/////
CCreaturePtr CGameMap::GetCreature(UINT64 qwCreatureID) const
{
    EGUIDType eType = CGUIDMgr::GetType(qwCreatureID);
    switch(eType)
    {
        case GUID_NPC:
            {
                auto it = _mapID2Npc.find(qwCreatureID);
                if(it != _mapID2Npc.end())
                    return static_pointer_cast<CCreature>(it->second.lock());
            }
            break;
        case GUID_MONSTER:
            {
                auto it = _mapID2Monster.find(qwCreatureID);
                if(it != _mapID2Monster.end())
                    return static_pointer_cast<CCreature>(it->second.lock());
            }
            break;
        default: //todo 删档后改为 case GUID_ROLE:
            {
                auto it = _mapRole2Player.find(qwCreatureID);
                if(it != _mapRole2Player.end())
                    return static_pointer_cast<CCreature>(it->second.lock());
            }
            break;
    }
    return NULL;
}

CPlayerPtr CGameMap::GetPlayer(UINT64 qwRoleID) const
{
    auto it = _mapRole2Player.find(qwRoleID);
    if(it != _mapRole2Player.end())
        return it->second.lock();
    return NULL;
}


CNpcPtr CGameMap::GetNpc(UINT64 qwCreatureID) const
{
    auto it = _mapID2Npc.find(qwCreatureID);
    if(it != _mapID2Npc.end())
        return it->second.lock();
    return NULL;
}



CMonsterPtr CGameMap::GetMonster(UINT64 qwCreatureID) const
{
    auto it = _mapID2Monster.find(qwCreatureID);
    if(it != _mapID2Monster.end())
        return it->second.lock();
    return NULL;
}


void CGameMap::GetMovablePoint(const SPoint& rCenter, float fRadius, UINT32 dwCount, TVecPoint& vecPoint)
{
    CPointPicker oPicker(*this, dwCount, true);
    VisitRoundArea(rCenter, fRadius, oPicker, true);
    vecPoint = oPicker.GetPointList();
}

bool CGameMap::GetMovablePoint(const SPoint& rCenter, SPoint& rPoint)
{
    TVecPoint vecPoint;
#define POINT_MAX_DISTANCE 10.0f
    GetMovablePoint(rCenter, POINT_MAX_DISTANCE, 3, vecPoint);
    if(vecPoint.empty())
        return false;
    for(int i = (int)vecPoint.size() - 1; i >= 0; --i)
    {
        if(vecPoint[i] != rCenter)
        {
            rPoint = vecPoint[i];
            return true;
        }
    }
    return false;
}

bool CGameMap::GetMovablePoint(const SPoint& rCenter, float fRadius, SPoint& rPoint)
{
    TVecPoint& rVecPoint = _rMapInfo.vecRandMovePoint;
    if(rVecPoint.empty())
        return false;
    TVecPoint vecCandt;
    INT32 dwSize = (INT32)rVecPoint.size();
    INT32 dwStart = CRandom::RandInt(0, dwSize - 1);
    for(INT32 i = 0; i < dwSize; ++i)
    {
        INT32 dwIndex = (dwStart + i) % dwSize;
        if(GetDistance(rCenter, rVecPoint[dwIndex]) < fRadius)
        {
            vecCandt.push_back(rVecPoint[dwIndex]);
            if(vecCandt.size() >= 5)
                break;
        }
    }
    if(vecCandt.empty())
        return false;
    rPoint = CRandom::RandVecElem(vecCandt);
    return true;
}

bool CGameMap::GetRandPoint(const SPoint& rCenter, float fRadius, UINT32 dwCount, TVecPoint& vecPoint)
{
    if(fRadius < 0)
        return false;
    CPointPicker oPicker(*this, 0, true);
    VisitRoundArea(rCenter, fRadius, oPicker, true);
    TVecPoint& vecPointList = oPicker.GetPointList();
    random_shuffle(vecPointList.begin(), vecPointList.end());
    if(vecPointList.empty())
        return false;
#ifdef _DEBUG
    for(size_t i = 0; i < vecPointList.size(); ++i)
    {
        if(IsBlockPoint(vecPointList[i]))
            DebugBreak();
    }
#endif
    if(vecPointList.size() < dwCount)
    {
        vecPoint = vecPointList;
        return false;
    }
    vecPoint.assign(vecPointList.begin(), vecPointList.begin() + dwCount);
    return true;
}

void CGameMap::GetRandPoint(const SPoint& rCenter, float fRadius, SPoint& rPoint)
{
    TVecPoint vecPoint;
    GetRandPoint(rCenter, fRadius, 1, vecPoint);
    if(vecPoint.empty())
        rPoint = rCenter;
    else
        rPoint = vecPoint[0];
}

bool CGameMap::GetRandPoint(SPoint& rPoint)
{
    TVecPoint& rVecPoint = _rMapInfo.vecRandMovePoint;
    if(rVecPoint.empty())
        return false;
    rPoint = CRandom::RandVecElem(rVecPoint);
    return true;
}

void CGameMap::GetOnJumpRegionPlayer(SJumpRegion& rJumpRegion, vector<CPlayerPtr>& vecPlayer)
{
    if(!_rMapInfo.IsDungeon())
    {
        LOG_CRI << "the map is not dungeon map, warning!!!!!!!!!!";
        return;
    }
    for(auto it = _mapRole2Player.begin(); it != _mapRole2Player.end(); ++it)
    {
        CPlayerPtr pPlayer = it->second.lock();
        if(pPlayer != NULL && rJumpRegion.IsInRegion(pPlayer->GetPoint()))
            vecPlayer.push_back(pPlayer);
    }
}

bool CGameMap::CheckJumpSwitcher(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn)
{
    if(!_rMapInfo.IsDungeon())
        return true;
    CDungeonPtr pDungeon = _pDungeon.lock();
    if(pDungeon == NULL)
    {
        //LOG_CRI << "_pDungeon is NULL";
        return true;
    }

    //if(pDungeon->GetDgnType() != ePlayerDgn && pDungeon->GetDgnType() != eTeamDgn)
    //    return true;

    for(auto it = _mapID2Switcher.begin(); it != _mapID2Switcher.end(); ++it)
    {
        CSwitcherPtr pSwitcher = it->second.lock();
        if(pSwitcher == NULL || pSwitcher->GetSwitcherType() != eSwitcherJump)
            continue;

        CJumpSwitcher& rJumpSwitcher = (CJumpSwitcher&)*pSwitcher;
        SJumpRegion& rJumpRegion = (SJumpRegion&)rJumpSwitcher;
        if(!rJumpSwitcher.IsOpen())
            continue;
        bool bIn =false;
        if(bCheckIn)
        {
            bIn = rJumpRegion.IsInRegion(rPlayer.GetPoint()); 
        }
        else
        {
            bIn = rJumpRegion.IntersectRegion(rPoint1, rPoint2);
        }
        if(bIn)
        {
            if(_mapRole2Player.size() > 0/*1*/)
            {
                std::vector<CPlayerPtr> vecPlayer;
                GetOnJumpRegionPlayer(rJumpSwitcher, vecPlayer);
                if(rJumpRegion.IsInRegion(rPlayer.GetPoint()))
                {
                    /*
                       if(vecPlayer.size() < DGN_MULTI_PLAYER_JUMP)
                       return true;
                       */
                }
                else
                {
                    if(vecPlayer.empty())
                    {
                        CDungeonMgr::NotifyPlayerWait(rPlayer);
                        return true;
                    }
                }
            }
            //bug  note: yhs 
            /*
               for(auto itPlayer = _mapRole2Player.begin(); itPlayer != _mapRole2Player.end(); ++itPlayer)
               {
               CPlayerPtr pPlayer = itPlayer->second.lock();
               if(pPlayer != NULL && pPlayer->GetFightInfo().HasFight())
               {
               if(!rJumpRegion.IsInRegion(rPlayer.GetPoint()))
               CDungeonMgr::NotifyPlayerWait(rPlayer);
               return true;
               }
               }
               */

            if(pDungeon->GetDgnType() == eDemonTowerDgn)
            {
                //only one
                if(rJumpRegion.wID == 1)
                {
                    g_DemonTowerMgr.PlayerEnterLowFloor(rPlayer);
                }
                else
                {
                    g_DemonTowerMgr.PlayerEnterNextFloor(rPlayer);

                }

                /*
                   for(auto itPlayer = _mapRole2Player.begin(); itPlayer != _mapRole2Player.end();)
                   {
                   CPlayerPtr pPlayer = itPlayer->second.lock();
                   ++itPlayer;
                   if(pPlayer)

                   g_DemonTowerMgr.PlayerEnterNextFloor(*pPlayer);
                //g_DemonTowerMgr.PlayerEnterLowFloor(*pPlayer);

                }
                */


                return true;
            }

            CGameMapPtr pMap = pDungeon->GetMap(rJumpRegion.wToMapID);
            if(pMap == NULL)
            {
                LOG_CRI << "goto dungeon next map is error!!! curMapID: " << GetMapID() << ", ToMapID: " << rJumpRegion.wToMapID;
                return true;
            }
            pDungeon->SetCurMap(pMap);
            for(auto itPlayer = _mapRole2Player.begin(); itPlayer != _mapRole2Player.end();)
            {
                CPlayerPtr pPlayer = itPlayer->second.lock();
                ++itPlayer;
                CGameMapPtr pMap = pDungeon->GetCurMap();
                if(pPlayer != NULL && !pPlayer->JumpMap(pMap,rJumpRegion.oToPoint,rJumpRegion.wID) )
                    LOG_CRI << "Player enter dungeon error";
            }
            return false;
        }
    }
    return true;
}

bool CGameMap::CheckMapArea(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn)
{
    if(!_rMapInfo.IsDungeon())
        return true;
    CDungeonPtr pDungeon = _pDungeon.lock();
    if(pDungeon == NULL)
    {
        //LOG_CRI << "_pDungeon is NULL";
        return true;
    }
    TVecUINT32 vecDestroy;
    for(auto it = _mapID2Area.begin(); it != _mapID2Area.end(); ++it)
    {
        CMapAreaPtr pArea = it->second.lock();
        if(pArea == NULL)
            continue;
        bool bIn =false;
        if(bCheckIn)
        {
            bIn = pArea->IsInRegion(rPlayer.GetPoint());
        }
        else 
        {
            bIn = pArea->IntersectRegion(rPoint1, rPoint2);
        }
        if(bIn)
        {
            const SAreaCFGEx* pCfg =  g_AreaManager.GetConfigById(pArea->GetAreaID());
            if(pCfg != NULL && pCfg->HasLua())
            {
                Config.GetScript().InArea(pArea->GetAreaID(),rPlayer.GetUser());
            }
            if(pArea->CanDel())
            {
                vecDestroy.push_back(it->first);  
            }
            if(pDungeon->GetDgnType() == ePlayerDgn || pDungeon->GetDgnType() ==  eGatherDgn)
            {
                CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDungeon);
                if(NULL != pPlayerDgn)
                {
                    pPlayerDgn->ArriveArea(pArea->GetAreaID());
                }
            }

        }
    }
    for(auto pos = vecDestroy.begin();pos != vecDestroy.end();pos ++)
    {
        DestroyArea(*pos);
    };
    return true;
}

#if 0
bool CGameMap::CheckCampSwitcher(CPlayer& rPlayer)
{
    if(!_rMapInfo.IsDungeon())
        return true;

    for(auto it = _mapID2Switcher.begin(); it != _mapID2Switcher.end(); ++it)
    {
        CSwitcherPtr pSwitcher = it->second.lock();
        if(pSwitcher != NULL && pSwitcher->GetSwitcherType() == eSwitcherCamp)
        {
            CCampSwitcher& rCampSwitcher = (CCampSwitcher&)*pSwitcher;
            if(rCampSwitcher.GetRegion().IsInRegion(rPlayer.GetPoint()))
                return true;
        }

        return false;
    }
}
#endif
void CGameMap::AddDynBlockCoord(const SCoord& rCoord)
{
    if(!_setBlockCoord.insert(rCoord).second)
        LOG_CRI << "AddBlockCoord Error! Coord: " << rCoord;
}

void CGameMap::RemoveDynBlockCoord(const SCoord& rCoord)
{
    if(1 != _setBlockCoord.erase(rCoord))
        LOG_CRI << "RemoveBlockCoord Error! Coord: " << rCoord;
}

void CGameMap::AddMapIndex(UINT8 byIdx)
{
    if(_rMapInfo.eMapType != eMapSingleDgn && _rMapInfo.eMapType != eMapMultipleDgn)
        return;
    if(byIdx != 0)
        _setMapIdx.insert(byIdx);
}

void CGameMap::RemoveMapIndex(UINT8 byIdx)
{
    if(_rMapInfo.eMapType != eMapSingleDgn && _rMapInfo.eMapType != eMapMultipleDgn)
        return;
    if(byIdx != 0)
        _setMapIdx.erase(byIdx);
}
void CGameMap::SetParam(EMapParam eParam,UINT32 dwValue)
{
    if(eParam < eMapParamEnd)
    {
        _arParam[eParam] = dwValue;
    }
    else
    {
        LOG_CRI<<"error EMapParam: "<< eParam;
    }
}  
UINT32 CGameMap::GetParam(EMapParam eParam)
{
    if(eParam < eMapParamEnd)       
    {                               
        return _arParam[eParam]; 
    }                               
    return 0;                            
}

void CGameMap::BroadcastMapIdx()
{
    if(_rMapInfo.eMapType != eMapSingleDgn && _rMapInfo.eMapType != eMapMultipleDgn)
        return;
    TVecUINT8 vecIdx(_setMapIdx.begin(), _setMapIdx.end());
    TVecUINT64 vecUsrID;
    vecUsrID.reserve(_mapRole2Player.size());
    for(auto it = _mapRole2Player.begin(); it != _mapRole2Player.end(); ++it)
    {
        CPlayerPtr pPlayer = it->second.lock();
        if(pPlayer)
            vecUsrID.push_back(pPlayer->GetUserID());
    }
    // TODO:
#if 0
    if(!vecUsrID.empty())
        g_DungeonProtS.SendClt_DungeonMapIdxNotify(&vecUsrID[0], (UINT16)vecUsrID.size(), vecIdx);
#endif
}

#if 0
bool CGameMap::CreateAbyssMonster()
{
    if (GetMapInfo().IsCity() == true)
        return false;

    if (CheckAbyssMonsterState() == false)
        return false;

    UINT32 dwCurCount = static_cast<int>(_mapID2AbyssMonster.size());
    UINT32 dwNeedMonsterCount = CMapMgr::GetCurOnlineUserCount() / SParamConfig::dwAbyssMonsterServerOffset;
    if (dwNeedMonsterCount < SParamConfig::dwAbyssMonsterMinCount)
        dwNeedMonsterCount = SParamConfig::dwAbyssMonsterMinCount;
    if (dwNeedMonsterCount < dwCurCount)
        return false;
    dwNeedMonsterCount -= dwCurCount;
    if (dwNeedMonsterCount == 0)
        return false;
    UINT32 dwLogCount = dwNeedMonsterCount;

    const SAbyssAtkCFGEx* pCFG = CMonsterMgr::GetAbyssAtkCFGByMapID(GetMapID());
    if (pCFG == NULL)
        return false;

    for (auto v = pCFG->vecRareMonster.begin(); v != pCFG->vecRareMonster.end(); ++v)
    {
        UINT16 wRand = static_cast<UINT16>(CRandom::RandInt(0, 100));
        if (wRand > v->wRate)
            continue;

        SMonsterGroup* pMstGroup = CMonsterMgr::GetMonsterGroup(v->wGroupID);
        if(NULL == pMstGroup)
            continue;

        CMonsterPtr pMonster = CMonsterMgr::CreateMonster(v->wMonsterID);
        if(pMonster == NULL)
            continue;

        SPoint oBornPoint;
        if (GetRandPoint(oBornPoint) == false)
            continue;

        pMonster->SetDir(arDirect[CRandom::RandInt(1, ARRAYSIZE(arDirect) - 1)]);
        pMonster->SetGroupID(v->wGroupID);
        pMonster->SetDropID(pMstGroup->wDropID);
        pMonster->SetRefreshTime(0);
        pMonster->SetReLivable(false);
        MonsterEnter(*pMonster, &oBornPoint);
        if(pMonster->CanMove())
            pMonster->GenWalkPoint();

        _mapID2AbyssMonster[pMonster->GetCreatureID()] = pMonster;
        --dwNeedMonsterCount;

        // log to count
        AbyssLog.AddAbyssMonster(eAbyssMonsterType_Refresh, pMonster->Level());

        g_Game2CenterCommC.Send_SendSysMsgNotify((EChannelType)56, v->strShout, eSubBroadcast);

        break;
    }

    while (dwNeedMonsterCount != 0)
    {
        for (auto v = pCFG->vecNormalMonster.begin(); v != pCFG->vecNormalMonster.end(); ++v)
        {
            SMonsterGroup* pMstGroup = CMonsterMgr::GetMonsterGroup(v->wGroupID);
            if(NULL == pMstGroup)
                continue;

            CMonsterPtr pMonster = CMonsterMgr::CreateMonster(v->wMonsterID);
            if(pMonster == NULL)
                continue;

            SPoint oBornPoint;
            if (GetRandPoint(oBornPoint) == false)
                continue;
#ifdef _DEBUG
            oBornPoint.fX = 20.0f;
            oBornPoint.fY = 72.0f;
#endif

            pMonster->SetDir(arDirect[CRandom::RandInt(1, ARRAYSIZE(arDirect) - 1)]);
            pMonster->SetGroupID(v->wGroupID);	
            pMonster->SetRefreshTime(0);
            pMonster->SetReLivable(false);
            MonsterEnter(*pMonster, &oBornPoint);
            if(pMonster->CanMove())
                pMonster->GenWalkPoint();

            _mapID2AbyssMonster[pMonster->GetCreatureID()] = pMonster;

            // log to count
            AbyssLog.AddAbyssMonster(eAbyssMonsterType_Refresh, pMonster->Level());

            if (--dwNeedMonsterCount == 0)
                break;
        }
    }

    ++_dwAbyssCreateCount;

    return true;
}

bool CGameMap::RemoveAllAbyssMonster()
{
    for (auto m = _mapID2AbyssMonster.begin(); m != _mapID2AbyssMonster.end(); ++m)
        m->second.lock()->SetMonsterState(eMonsterDead);
    _mapID2AbyssMonster.clear();

    SetAbyssCreateCount(0);

    return false;
}

bool CGameMap::CheckAbyssMonsterState()
{
    if (_dwAbyssCreateCount > SParamConfig::dwAbyssMonsterRefreshMaxCount)
        return false;

    UINT32 dwMonsterNum = static_cast<UINT32>(_mapID2AbyssMonster.size());
    if (dwMonsterNum < SParamConfig::dwAbyssMonsterMinNum)
        return true;

    return false;
}

bool CGameMap::IsAbyssMonster(UINT32 dwMonsterID)
{
    auto m = _mapID2AbyssMonster.find(dwMonsterID);
    if (m == _mapID2AbyssMonster.end())
        return false;

    return true;
}

#endif


IBattleFighterPtr CGameMap::ToBattleFighter()
{
    return CMapMgr::ToBattleFighter(_rMapInfo.wMapID);
}

SPoint CGameMap::GetRealivePoint()
{
    return move(_rMapInfo.GetRealivePoint());
}

bool CGameMap::NpcAppear(CNpc& rNpc)
{
    TVecUINT64 vecUsrID;
    if(!PlaceMapObject(rNpc, vecUsrID))
    {
        LOG_CRI << "Place NPC fails! qwCreatureID: " << rNpc.GetCreatureID();
        return false;
    }
    g_MapProtS.NotifyNpcAppear(vecUsrID, rNpc, true);
    if(!_mapID2Npc.insert(make_pair(rNpc.GetCreatureID(), ToThisPtr(rNpc))).second)
        LOG_CRI << "NPC already exists!";
    return true;
}

bool CGameMap::NpcDisappear(CNpc& rNpc)
{
    if(!rNpc.IsOnMap())
        return true;
    TVecUINT64 vecUsrID;
    if(!RemoveMapObject(rNpc, vecUsrID))
    {
        LOG_CRI << "Remove NPC fails! qwCreatureID: " << rNpc.GetCreatureID();
        return false;
    }
    g_MapProtS.NotifyCreatureDisappear(vecUsrID, rNpc, true);
    if(_mapID2Npc.erase(rNpc.GetCreatureID()) == 0)
        LOG_CRI << "NPC not exists!";
    CNpcMgr::DestroyNpc(rNpc);
    return true;
}

bool CGameMap::AddNpc(UINT16 wNpcID, const SPoint* pPoint)
{
    CNpcPtr pNpc = CNpcMgr::CreateNpc(wNpcID,0);
    if (!pNpc)
        return false;

    if (pPoint)
        pNpc->SetPoint(*pPoint);

    return NpcAppear(*pNpc);
}
void  CGameMap::AddNpcByIndex(UINT8 byIndex)
{
    const TVecNpcPoint& rvec = _rMapInfo.vecNpcPoint;
    for(auto it = rvec.begin(); it != rvec.end();it++)
    {
        const SNpcPoint &rNpc = *it;
        if(byIndex == rNpc.byIndex)
        {
            _rMapInfo.CreateNpc(shared_from_this(),rNpc);
        }
    }


}
void  CGameMap::NpcDestroyByIndex(UINT8 byIndex)
{
    TVecUINT64 vecDel;
    for(auto it = _mapID2Npc.begin(); it != _mapID2Npc.end();it++)
    {
        CNpcPtr pNpc = it->second.lock();
        if(pNpc && pNpc->GetIndex() == byIndex)
        {
            vecDel.push_back(it->first);
        }
    }
    for(auto it = vecDel.begin(); it != vecDel.end() ;it++)
    {
        DelNpc(*it);
    }
}

bool CGameMap::DelNpc(UINT64 qwCreatureID)
{
    NpcDisappearByID(qwCreatureID);
    return true;
}

bool CGameMap::NpcDisappearByID(UINT64 qwCreatureID)
{
    CNpcPtr pNpc = GetNpc(qwCreatureID);
    if(pNpc)
        NpcDisappear(*pNpc);
    return true;
}

bool CGameMap::CheckAllPosForMove(CPlayer& rPlayer, const SPoint& rPoint1,const SPoint& rPoint2)
{
    if(!CheckRegion(rPlayer, rPoint1, rPoint2))
        return false;
    // TODO:
    if(!CheckJumpSwitcher(rPlayer, rPoint1, rPoint2))
        return false;
    if(!CheckMapArea(rPlayer, rPoint1, rPoint2))
        return false;
    return true;
}
bool CGameMap::CheckAllPosForJump(CPlayer& rPlayer)
{
    SPoint rPoint1;
    SPoint rPoint2;
    if(!CheckRegion(rPlayer, rPoint1, rPoint2,true))
        return false;
    if(!CheckJumpSwitcher(rPlayer, rPoint1, rPoint2,true))
        return false;
    if(!CheckMapArea(rPlayer, rPoint1, rPoint2,true))
        return false;
    return true;
}

bool CGameMap::IsWarning() const
{
    if(_rMapInfo.eMapType != eMapNormal)
    {
        return false;
    }
    return  _mapRole2Player.size() >= _rMapInfo.wSMaxPlayer;

}

bool CGameMap::IsFull() const
{
    if(_rMapInfo.eMapType != eMapNormal)
    {
        return false;
    }
    return  _mapRole2Player.size() >= _rMapInfo.wMaxPlayer;

}


