#pragma once
#include "stdafx.h"
#include "Dungeon.h"

class CDemonTowerDgn : public CDungeon,public CPoolObj<CDemonTowerDgn>
{
    friend class CDungeonMgr;
    public:
    DEF_NEW_DELETE(CDemonTowerDgn);

    CDemonTowerDgn(const SDgnInfo& rDgnInfo, UINT64 qwInstID, const CPlayerPtr& pPlayer);
    virtual ~CDemonTowerDgn();

    virtual void FailOver();//因为结束关闭，可能超时，或别的条件
    virtual void ClearDungeon();
    virtual EDgnType GetDgnType() { return eDemonTowerDgn; }
    virtual void TimerCheck(UINT64 qwTick);
    virtual bool PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint);
    virtual bool PlayerEnter(CPlayer& rPlayer, SPoint* pPoint = NULL);
    virtual bool PlayerLeave(CPlayer& rPlayer);
    virtual bool CanEnter(CPlayer& rPlayer);
    virtual void SetDgnState(EDgnState eState);
    virtual bool CanAttackMonster(UINT16 wMonsterGroup);
    virtual	void OnMonsterDie(CMonster& rMonste, UINT64 qwKillRoleID ,UINT64 qwBattleID);
    virtual void OnPlayerDie(CCreature& rKiller,CPlayer& rPlayer);
    virtual bool OnBegin();
    virtual void OnEnd();
    virtual bool LoadMap();
    virtual bool IsCanRelogin() { return false; };

    //采集一个物品
    virtual	void OnGather(UINT16 wGatherID, CPlayer& rPlayer);
    
    //是否可以跳转地图
    virtual bool IsCanJumpMap( CPlayer* pPlayer,CGameMapPtr& pCurMap,CGameMapPtr& pDestMap);
    
    //玩家离开副本事件
    virtual void OnBeforeLeaveDgn( CPlayer* pPlayer);
   
    //进入副本
    virtual void OnEnterDgn(CPlayer* pPlayer);

    //进入地图之后事件（在进入副本函数之后调用）
    virtual void OnEnterMap(CPlayer* pPlayer,CGameMapPtr& pCurMap);


    bool PlayerEnterFloor(CPlayer& rPlayer,UINT32 dwFloorID);

    void AddAttackTurns(UINT16 wTurns);
    CPlayerPtr GetPlayer() { return _pPlayer.lock(); }

    CGameMapPtr GetFloorMapByID(UINT32 dwFloorID);

    UINT32 GetCurFloorID() { return _dwCurFloorID; }

    protected:
    CPlayerWtr _pPlayer;
    vector<UINT16> _vecAttackOrder;
    UINT16 _wTotalTurns;
    private:
    std::vector<CGameMapPtr> _vecFloorMap;
    UINT32 _dwGatherID;
    UINT32 _dwCurFloorID;
};

