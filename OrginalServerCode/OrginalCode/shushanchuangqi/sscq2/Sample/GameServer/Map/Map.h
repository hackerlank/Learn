#pragma once
#include "Grid.h"
#include "MapInfo.h"
#include "Region.h"
#include "Visitor.h"

#include "Battle.h"

class CCreature;
class CPlayer;
class CNpc;
class CMonster;
struct SMapInfo;
class IGather;
class CSwitcher;
class CBlocker;
class CJumpSwitcher;
class CDungeon;
class CMapArea;
typedef map<UINT64, CPlayerWtr> TMapID2Player;
typedef map<UINT64, CNpcWtr> TMapID2Npc;
typedef map<UINT64, CMonsterWtr> TMapID2Monster;
typedef map<UINT32, CSwitcherWtr> TMapID2Switcher;
typedef map<UINT32, IGatherWtr> TMapID2Gather;
typedef map<UINT32, CBlockerWtr> TMapID2Blocker;
typedef map<UINT32, CMapAreaWtr> TMapID2Area;
class CGameMap : public enable_shared_from_this<CGameMap>,public CPoolObj<CGameMap>
{
    public:
        DEF_NEW_DELETE(CGameMap);
        CGameMap(SMapInfo& rMapInfo);
        ~CGameMap();

        SPoint GetRealivePoint();
        UINT16 GetMapID() const { return _rMapInfo.wMapID; }
        const SMapInfo& GetMapInfo() const { return _rMapInfo; }
        bool InitConfig();
        CGrid* GetGrid(INT32 dwX, INT32 dwY);
        CGrid* GetGrid(const SPoint& rPoint, SCoord* pCoord = NULL);
        bool DiffGrid(const SPoint& rPoint1, const SPoint& rPoint2);

        bool IsBlockPoint(INT32 dwX, INT32 dwY, bool bBaseGrid = false) const;
        bool IsBlockPoint(const SCoord& rCoord, bool bBaseGrid = false) const;
        bool IsBlockPoint(const SPoint& rPoint) const;
        bool HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, bool bLoose = false) const;
        bool HasDynamicBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2) const;
        bool IsDynamicBlockPoint(const SCoord& rCoord) const;
        bool IsSafePoint(const SCoord& rCoord, bool bBaseGrid = false) const;
        bool IsSafePoint(INT32 dwX, INT32 dwY, bool bBaseGrid = false) const;
        bool IsInSafeArea(const SPoint& rPoint);

        template<typename T>
            void VisitArea(const SCoord& rCenter, const SCoord& rRadius, T& rT);

        template<typename T>
            void VisitArea(const SPoint& rPoint, const SPoint& rRadius, T& rT);

        template<typename T>
            void VisitArea(const CBaseObj& rObj, T& rT);

        template<typename T1, typename T2>
            void VisitDiffArea(const SCoord& rCenter1, const SCoord& rCenter2, const SCoord& rRadius, T1& rT1, T2& rT2);

        template<typename T>
            void VisitRoundArea(const SPoint& rPoint, float fRadius, T& rT, bool bBaseGrid = false);

        template<typename T>
            void VisitRectArea(const SPoint (&arPoint)[4], T& rT, bool bBaseGrid = false);

        template<typename T>
            void VisitDiamondArea(const SPoint& rPoint, const SCoord& rRadius, T& rT, bool bBaseGrid = false);

        //长方形
        template<typename T>
            void GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature, const SCoord& rRadius, vector<T>& rVecObject);

        //长方形
        template<typename T>
            void GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature, const SPoint& rRadius, vector<T>& rVecObject);


        //长方形
        template<typename T>
            void GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature, vector<T>& rVecObject);

        //圆形
        template<typename T>
            void GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature, float fRadius, vector<T>& rVecObject);

        bool GridHasObject(const SCoord& rCoord, bool bBaseGrid);
        void GetGridObject(const SCoord& rCoord, bool bBaseGrid, set<CBaseObjPtr>& rSetObject);

        bool NotifySurround(CBaseObj& rBaseObj, const string& strPkg);
        bool NotifyMeAndSurround(CCreature& rCreature, const string& strPkg);

        //-qf- addd 2014/7/25
        bool NotifyAllMapPlayer(const string& strPkg); 
        UINT32 GetPlayerCount();

        void AddRegion(ERegionType eType, const SRegionPtr& rRegion);
        void ClearRegion(ERegionType eType);
        SRegionPtr GetRegion(ERegionType eType, const SPoint& rPoint);
        SRegionPtr GetRegion(ERegionType eType, const SPoint& rPoint1, const SPoint& rPoint2);
        void CheckTaskProbeRegion(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn = false);
        bool CheckRegion(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn = false);
        bool CheckJumpSwitcher(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn = false);
        bool CheckCampSwitcher(CPlayer& rPlayer);
        bool CheckMapArea(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2,bool bCheckIn = false);
        bool CheckAllPosForMove(CPlayer& rPlayer, const SPoint& rPoint1, const SPoint& rPoint2);
        bool CheckAllPosForJump(CPlayer& rPlayer);

        bool CreatureStopMove(CCreature& rCreature, const SPoint& rPoint, float fDir);
        bool CreatureMoveTo(CCreature& rCreature, const vector<SPoint>& rVecPoint, float fDir, bool bStart);
        bool CreatureMoveTo(CCreature& rCreature, const SPoint& rCurPoint, bool bNotify = true, const vector<SPoint>* pVecPoint = NULL);
        void CreatureForceMoveTo(CCreature& rCreature, const SPoint& rCurPoint, bool bNotify = true);

        //当前控制角色
        bool PlayerAppear(CPlayer& rPlayer, bool bAppear = true);
        bool PlayerDisappear(CPlayer& rPlayer);
        bool PlayerReappear(CPlayer& rPlayer);
        bool AppearToSurround(CPlayer& rPlayer);
        //玩家回到出生点
        void PlayerFlyToPos(CPlayer& rPlayer,const SPoint& rPoint);

        bool PlacePlayer(CPlayer& rPlayer);

        bool NpcAppear(CNpc& rNpc);
        bool NpcDisappear(CNpc& rNpc);

        bool AddNpc(UINT16 wNpcID, const SPoint* pPoint = NULL);
        bool DelNpc(UINT64 qwCreatureID);
        bool NpcDisappearByID(UINT64 qwCreatureID);
        void AddNpcByIndex(UINT8 byIndex);
        void NpcDestroyByIndex(UINT8 byIndex);
        void DelNpcById(UINT16 wNpc);


        bool MonsterEnter(CMonster& rMonster, const SPoint* pPoint = NULL);
        bool MonsterAppear(CMonster& rMonster);
        bool MonsterDisappear(CMonster& rMonster, bool bFade = true);
        void ClearAllMonsters();
        bool MonsterChange(CMonster& rMonster);

        UINT64 AddMonster(UINT16 wGroup, const SPoint* pPoint = NULL);
        UINT64 AddMonsterIfNotExist(UINT16 wGroup, const SPoint* pPoint = NULL);
        bool DelMonster(UINT64 qwCreatureID);
        void GetMonsterVecByGroup(UINT16 wGroup,TVecUINT64& vecMonster);
        void DelMonsterByGroup(UINT16 wGroup);

        
        bool MonsterDisappearByID(UINT64 qwCreatureID, bool bFade = true);

        bool SwitcherAppear(CSwitcher& rSwitcher);
        bool SwitcherDisappear(CSwitcher& rSwitcher);
        void AddSwitcherByIndex(UINT8 byIndex);
        void SwitcherDestroyByIndex(UINT8 byIndex);
        void ClearAllSwitchers();

        void GetOnJumpRegionPlayer(SJumpRegion& rJumpRegion, vector<CPlayerPtr>& vecPlayer);

        IGatherPtr FindGather(UINT32 dwInstID);
        bool GatherAppear(IGather& rGather);
        bool GatherDisappear(IGather& rGather);
        bool  GatherChange(IGather& rGather);
        void ClearAllGathers();
        void AddGatherByIndex(UINT8 byIndex);
        void GatherDestroyByIndex(UINT8 byIndex);
        bool AddGather(UINT16 wGather, const SPoint* pPoint = NULL);
        bool DelGather(UINT32 dwCreatureID);
        void GetGatherVecByGather(UINT16 wGather,TVecUINT32& vecGather);
        void DelGatherByGather(UINT16 wGather);


        bool CreateBlockByIndex(UINT16 wIndex);
        CBlockerPtr GetBlockById(UINT32 wID);
        bool DestroyBlock(UINT32 wID);
        void DestroyBlockByIndex(UINT16 wIndex);     
        bool BlockerAppear(CBlocker& rBlocker);
        bool BlockerDisappear(CBlocker& rBlocker);
        void ClearAllBlockers();

        bool CreateAreaByIndex(UINT16 wIndex);
        CMapAreaPtr GetAreaById(UINT32 wID);
        bool DestroyArea(UINT32 wID);
        void DestroyAreaByIndex(UINT16 wIndex);     
        bool AreaAppear(CMapArea& rArea);
        bool AreaDisappear(CMapArea& rArea);
        void ClearAllAreas();

        INT32 GetLength() const { return _dwLength; }
        INT32 GetHeight() const { return _dwHeight; }

        CCreaturePtr GetCreature(UINT64 qwCreatureID) const;
        CPlayerPtr GetPlayer(UINT64 qwRoleID) const;
        CNpcPtr GetNpc(UINT64 qwCreatureID) const;
        CNpc * GetpNpc(UINT64 qwCreatureID) const 
        {
            return GetNpc(qwCreatureID).get();
        }
        CMonsterPtr GetMonster(UINT64 qwCreatureID) const;

        const TMapID2Player& GetPlayerMap() const { return _mapRole2Player; }
        const TMapID2Npc& GetNpcMap() const { return _mapID2Npc; }
        const TMapID2Monster& GetMonsterMap() const { return _mapID2Monster; }
        const TMapID2Gather& GetGatherMap() const { return _mapID2Gather; }
        //MovablePoint：尽量靠近中心点，RandPoint：在范围内充分随机，也是可行走的
        void GetMovablePoint(const SPoint& rCenter, float fRadius, UINT32 dwCount, TVecPoint& vecPoint);
        bool GetMovablePoint(const SPoint& rCenter, SPoint& rPoint);
        bool GetMovablePoint(const SPoint& rCenter, float fRadius, SPoint& rPoint);
        bool GetRandPoint(const SPoint& rCenter, float fRadius, UINT32 dwCount, TVecPoint& vecPoint);
        void GetRandPoint(const SPoint& rCenter, float fRadius, SPoint& rPoint);
        bool GetRandPoint(SPoint& rPoint); //全地图随机

        void SetDungeon(const CDungeonPtr& pDungeon) { _pDungeon = pDungeon; }
        CDungeonPtr GetDungeon() const { return _pDungeon.lock(); }
        void AddDynBlockCoord(const SCoord& rCoord);
        void RemoveDynBlockCoord(const SCoord& rCoord);

        void AddMapIndex(UINT8 byIdx);
        void RemoveMapIndex(UINT8 byIdx);
        void BroadcastMapIdx();

#if 0
        bool CreateAbyssMonster();
        bool RemoveAllAbyssMonster();
        bool CheckAbyssMonsterState();
        UINT32 GetAbyssMonsterCount() { return static_cast<UINT32>(_mapID2AbyssMonster.size()); }
        bool IsAbyssMonster(UINT32 dwMonsterID);
#endif
        void SetAbyssCreateCount(UINT32 dwCount) { _dwAbyssCreateCount = dwCount; }
        const SMapInfo& GetMapInfo(){ return _rMapInfo; }

        EMapType GetMapType() { return _rMapInfo.eMapType; }

        bool IsNormalMap() { return eMapNormal == _rMapInfo.eMapType; }

        IBattleFighterPtr ToBattleFighter();
        bool IsWarning() const;
        bool IsFull() const;

    public:
        //-qf- 2014/05/09
        void SetParam(EMapParam eParam,UINT32 dwValue);
        UINT32 GetParam(EMapParam eParam);
    protected:

        bool AllocGrid();
        void FreeGrid();
        void FreeRegion();
        void FreeObj();

        bool PlaceMapObject(CBaseObj& rBaseObj, TVecUINT64& rVecUsrID, set<CBaseObjPtr>* pSetObj = NULL);
        bool RemoveMapObject(CBaseObj& rBaseObj, TVecUINT64& rVecUsrID);

        template<typename T>
            void VisitGrid(INT32 dwX, INT32 dwY, T& rT);

        SMapInfo& _rMapInfo;
        INT32 _dwLength;
        INT32 _dwHeight;
        CGrid** _ppGrid;

        TMapID2Player _mapRole2Player;
        TMapID2Npc _mapID2Npc;
        TMapID2Monster _mapID2Monster;
        TMapID2Switcher _mapID2Switcher;
        TMapID2Gather _mapID2Gather;
        TMapID2Blocker _mapID2Blocker;
        TMapID2Area _mapID2Area;
        vector<SRegionPtr> _arVecRegion[eRegionEnd];
        unordered_set<INT64> _setBlockCoord;
        CDungeonWtr _pDungeon;
        set<UINT8> _setMapIdx;
        //-qf- 2014/05/09
        //保存运行参数
        UINT32 _arParam[eMapParamEnd];
#if 0
        TMapID2Monster _mapID2AbyssMonster;
#endif

        UINT32 _dwAbyssCreateCount;
};

    template<typename T>
void CGameMap::VisitGrid(INT32 dwX, INT32 dwY, T& rT)
{
    CGrid* pGrid = GetGrid(dwX, dwY);
    if(pGrid != NULL)
        pGrid->Accept(rT);
}

    template<typename T>
void CGameMap::VisitArea(const SCoord& rCenter, const SCoord& rRadius, T& rT)
{
    for(INT32 i = rCenter.dwX - rRadius.dwX; i <= rCenter.dwX + rRadius.dwX; ++i)
    {
        for(INT32 j = rCenter.dwY - rRadius.dwY; j <= rCenter.dwY + rRadius.dwY; ++j)
        {
            if(rT.Finish(i, j))
                return;
            VisitGrid(i, j, rT);
        }
    }
}

    template<typename T>
void CGameMap::VisitArea(const SPoint& rPoint, const SPoint& rRadius, T& rT)
{
    SCoord oCoord, oRadius;
    _rMapInfo.ToIntCoord(rPoint, oCoord);
    PointToCoord(rRadius, oRadius);
    VisitArea(oCoord, oRadius, rT);
}

    template<typename T>
void CGameMap::VisitArea(const CBaseObj& rObj, T& rT)
{
    SCoord oCoord;
    if(!rObj.GetCoord(oCoord))
        DebugBreak();
    VisitArea(oCoord, _rMapInfo.GetBroadCastRadius(), rT);
}

    template<typename T>
void CGameMap::VisitRoundArea(const SPoint& rPoint, float fRadius, T& rT, bool bBaseGrid /*= false*/)
{
    SCoord oCenter, oRadius;
    _rMapInfo.ToIntCoord(rPoint, oCenter, bBaseGrid);
    INT32 dwCenterX = oCenter.dwX, dwCenterY = oCenter.dwY;
    PointToCoord(SPoint(fRadius, fRadius), oRadius, bBaseGrid);
    INT32 dwRadius = max(oRadius.dwX, oRadius.dwY);
    INT32 dwX = -1, dwY = 0;
    INT32 dwRadiusPower = Square(dwRadius);
    INT32 dwXPower = 0, dwYPower = 0;
    bool bNewRound = true;
    for(INT32 dwR = 1; dwR <= dwRadius; ++dwR)
    {
        dwYPower = Square(dwY);
        do {
            ++dwX;
            if(Square(dwX) + dwYPower <= dwRadiusPower)
            {
                if(rT.Finish(dwCenterX + dwX, dwCenterY + dwY))
                    return;
                if(!bBaseGrid)
                    VisitGrid(dwCenterX + dwX, dwCenterY + dwY, rT);
                bNewRound = false;
            }
            else if(!bNewRound && dwX > 0)
            {
                bNewRound = Transpose(dwX, dwY);
                break;
            }
        } while(dwX < dwR);
        dwXPower = Square(dwX);
        do {
            ++dwY;
            if(dwXPower + Square(dwY) <= dwRadiusPower)
            {
                if(rT.Finish(dwCenterX + dwX, dwCenterY + dwY))
                    return;
                if(!bBaseGrid)
                    VisitGrid(dwCenterX + dwX, dwCenterY + dwY, rT);
                bNewRound = false;
            }
            else if(!bNewRound && dwY > 0)
            {
                bNewRound = Transpose(dwX, dwY);
                break;
            }
        } while(dwY < dwR);
        dwYPower = Square(dwY);
        do {
            --dwX;
            if(Square(dwX) + dwYPower <= dwRadiusPower)
            {
                if(rT.Finish(dwCenterX + dwX, dwCenterY + dwY))
                    return;
                if(!bBaseGrid)
                    VisitGrid(dwCenterX + dwX, dwCenterY + dwY, rT);
                bNewRound = false;
            }
            else if(!bNewRound && dwX < 0)
            {
                bNewRound = Transpose(dwX, dwY);
                break;
            }
        } while(dwX > -dwR);
        dwXPower = Square(dwX);
        do {
            --dwY;
            if(dwXPower + Square(dwY) <= dwRadiusPower)
            {
                if(rT.Finish(dwCenterX + dwX, dwCenterY + dwY))
                    return;
                if(!bBaseGrid)
                    VisitGrid(dwCenterX + dwX, dwCenterY + dwY, rT);
                bNewRound = false;
            }
            else if(!bNewRound && dwY < 0)
            {
                bNewRound = Transpose(dwX, dwY);
                break;
            }
        } while(dwY > -dwR);
    }
    ++dwX;
    if(Square(dwX) + dwYPower <= dwRadiusPower)
    {
        if(rT.Finish(dwCenterX + dwX, dwCenterY + dwY))
            return;
        if(!bBaseGrid)
            VisitGrid(dwCenterX + dwX, dwCenterY + dwY, rT);
    }
}

    template<typename T>
void CGameMap::VisitRectArea(const SPoint (&arPoint)[4], T& rT, bool bBaseGrid /*= false*/)
{
    SCoord arCoord[4];
    INT32 dwLeftX = INT_MAX, dwRightX = INT_MIN;
    for(INT32 i = 0; i < 4; ++i)
    {
        _rMapInfo.ToIntCoord(arPoint[i], arCoord[i], bBaseGrid);
        if(arCoord[i].dwX < dwLeftX)
            dwLeftX = arCoord[i].dwX;
        if(arCoord[i].dwY > dwRightX)
            dwRightX = arCoord[i].dwY;
    }
    if(abs(dwRightX - dwLeftX) > _rMapInfo.GetLength(bBaseGrid))
    {
        LOG_CRI << "Error! dwLeftX: " << dwLeftX << ", dwRightX: " << dwRightX;
        return;
    }
    INT32 dwLowY = 0, dwUpY = 0;
    for(INT32 i = dwLeftX; i <= dwRightX; ++i)
    {
        GetIntersection(i, arCoord, dwLowY, dwUpY);
        if(abs(dwUpY - dwLowY) > _rMapInfo.wHeight)
        {
            LOG_CRI << "Error! dwLowY: " << dwLowY << ", dwUpY: " << dwUpY;
            return;
        }
        for(INT32 j = dwLowY; j <= dwUpY; ++j)
        {
            if(rT.Finish(i, j))
                return;
            if(!bBaseGrid)
                VisitGrid(i, j, rT);
        }
    }
}

    template<typename T>
bool VisitDiamondCoord(CGameMap& rMap, INT32 dwCenterX, INT32 dwCenterY, INT32 i, INT32 j, T& rT, bool bBaseGrid)
{
    if(rT.Finish(dwCenterX + i, dwCenterY + j))
        return false;
    if(!bBaseGrid)
        VisitGrid(dwCenterX + i, dwCenterY + j, rT);
    return true;
}

    template<typename T>
void CGameMap::VisitDiamondArea(const SPoint& rPoint, const SCoord& rRadius, T& rT, bool bBaseGrid /*= false*/)
{
    SCoord oCenter;
    if(!_rMapInfo.ToIntCoord(rPoint, oCenter, bBaseGrid))
        return;
    INT32 dwRadius = min(rRadius.dwX, rRadius.dwY);
    for(INT32 k = 1; k <= dwRadius; ++k)
    {
        for(INT32 i = 0; i <= k; ++i)
        {
            INT32 j = k - i;
            if(!VisitDiamondCoord(*this, oCenter.dwX, oCenter.dwY, i, j, rT, bBaseGrid))
                return;
            if(j > 0 && !VisitDiamondCoord(*this, oCenter.dwX, oCenter.dwY, i, -j, rT, bBaseGrid))
                return;
            if(i > 0 && !VisitDiamondCoord(*this, oCenter.dwX, oCenter.dwY, -i, j, rT, bBaseGrid))
                return;
            if(i > 0 && j > 0 && !VisitDiamondCoord(*this, oCenter.dwX, oCenter.dwY, -i, -j, rT, bBaseGrid))
                return;
        }
    }
}

    template<typename T>
void CGameMap::GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature_, const SCoord& rRadius, vector<T>& rVecObject)
{
    CCreature& rCreature = const_cast<CCreature&>(rCreature_);
    CVisitor oVisitor(eVisitType, &rCreature);
    CCollector<CVisitor> oCollector(oVisitor);
    SCoord oCoord;
    rCreature_.GetCoord(oCoord);
    VisitArea(oCoord, rRadius, oCollector);
    oCollector.GetObjectList(rVecObject);
}

    template<typename T>
void CGameMap::GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature_, const SPoint& rRadius, vector<T>& rVecObject)
{
    CCreature& rCreature = const_cast<CCreature&>(rCreature_);
    CVisitor oVisitor(eVisitType, ToThisPtr(rCreature));
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rCreature_.GetPoint(), rRadius, oCollector);
    oCollector.GetObjectList(rVecObject);
}

    template<typename T>
void CGameMap::GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature_, vector<T>& rVecObject)
{
    CCreature& rCreature = const_cast<CCreature&>(rCreature_);
    CVisitor oVisitor(eVisitType, ToThisPtr(rCreature));
    CCollector<CVisitor> oCollector(oVisitor);
    VisitArea(rCreature, oCollector);
    oCollector.GetObjectList(rVecObject);
}

    template<typename T>
void CGameMap::GetSurroundObject(EVisitType eVisitType, const CCreature& rCreature_, float fRadius, vector<T>& rVecObject)
{
    CCreature& rCreature = const_cast<CCreature&>(rCreature_);
    CVisitor oVisitor(eVisitType, ToThisPtr(rCreature));
    CCollector<CVisitor> oCollector(oVisitor);
    VisitRoundArea(rCreature.GetPoint(), fRadius, oCollector);
    oCollector.GetObjectList(rVecObject);
}
