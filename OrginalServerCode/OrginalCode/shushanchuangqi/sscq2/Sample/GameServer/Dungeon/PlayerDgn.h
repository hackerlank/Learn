#ifndef PLAYERDGN_H__
#define PLAYERDGN_H__
#include "Dungeon.h"
#include "DgnCondManager.h"
class CPlayerDgn : public CDungeon,public CPoolObj<CPlayerDgn>
{
    friend class CDungeonMgr;
    public:
    DEF_NEW_DELETE(CPlayerDgn);
    CPlayerDgn(const SDgnInfo& rDgnInfo, UINT64 qwInstID, const CPlayerPtr& pPlayer);
    virtual ~CPlayerDgn();
    virtual void FailOver();//因为结束关闭，可能超时，或别的条件
    virtual void ClearDungeon();
    virtual EDgnType GetDgnType() { return _rDgnInfo.oDgnCfg.eType; }
    virtual void OnTimer(time_t tNow);
    virtual bool PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint);
    virtual bool PlayerEnter(CPlayer& rPlayer,const SPoint* pPoint = NULL);
    virtual bool PlayerLeave(CPlayer& rPlayer);
    virtual bool CanEnter(CPlayer& rPlayer);
    virtual void SetDgnState(EDgnState eState);
    virtual bool CanAttackMonster(UINT16 wMonsterGroup);
    virtual void PlayerKillAll(CPlayer& rPlayer); 
    virtual	void OnMonsterDie(CMonster& rMonster, UINT64 qwKillRoleID ,UINT64 qwBattleID);
    virtual void OnGather(UINT16 wGatherID, CPlayer& rPlayer);
    virtual EDungeonResult AcceptDgnAward(CPlayer& rPlayer);
    virtual bool OnBegin();
    virtual void OnEnd();
    virtual void FinishDgn(CPlayer& rPlayer);
    virtual void OnPlayerDie(CCreature& rKiller,CPlayer& rPlayer);
    virtual void GetLogString(string &strMsg);
    void AddAttackTurns(UINT16 wTurns);
    void ArriveArea(UINT16 wAreaId); 
    void FightWithMonster(UINT16 wGroupId);
    CPlayerPtr GetPlayer() { return _pPlayer.lock(); }
    CPlayer* GetpPlayer() { return GetPlayer().get(); }
    void DoFinish(UINT64 qwBattleID = 0) ;
    void UpdateDgnProcess(bool bUpdateProcess = true,bool bUpdateStar = true);
    void PlayerRelive();
    void GetDgnProcessFromClient(CPlayer& rPlayer);

    protected:
    CPlayerWtr _pPlayer;
    vector<UINT16> _vecAttackOrder;
    DgnCondInstance _InsProcess;
    DgnCondInstance _InsStar;
};
#endif //PLAYER_DGN__
