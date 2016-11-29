
#ifndef CREATURE_H_
#define CREATURE_H_

#include "BaseObj.h"
#include "Walker.h"
#include "GameBuffManager.h"
class CCreature : public CBaseObj, public CGameBuffManager
{
public:
    CCreature();
    virtual ~CCreature();

    virtual UINT64 GetCreatureID() const = 0;
    virtual bool IsDead() const = 0;
    virtual void OnKill(CCreature& rTarget) {}
    virtual void OnDie(CCreature& rKiller) {}
    virtual bool CanUseItem();
    virtual bool CanSee(CCreature& /*rCreature*/) { return true; }
    virtual bool CanFight(CCreature& /*rCreature*/); 
    virtual bool IsAttackable() const { return false; }
    virtual void OnAttacked(CCreature& rAttacker) {}
    UINT32 GetAppearState() const { return _dwAppearState; }
    bool HasAppearState(EAppearState eAppearState) const { return (_dwAppearState & eAppearState) != 0; }
    void SetAppearState(EAppearState eAppearState, bool bNotify = true);
    void ClearAppearState(EAppearState eAppearState, bool bNotify = true);
    CWalker& GetWalker() { return _oWalker; }
    virtual float GetSpeedForWalker() const { return 4.f; }
    bool MoveTo(const vector<SPoint>& vecPoint, float fDir, bool bStart);
    virtual bool StopMove(const SPoint& rPoint, float fDir);
    void ResetNextBattleTime(UINT16 wNextBattleTime = 3);

    virtual bool SendPkg(const string& strPkg) { return false; }
    bool NotifyMeAndSurround(const string& strPkg);
    bool NotifySurround(const string& strPkg);

    UINT8 GetJob() const {return  _byJob; }
    void SetJob(UINT8 byJob) { _byJob = byJob; }

    virtual UINT8 GetLevel() const { return _byLevel; }
    virtual void SetLevel(UINT8 byLevel) { _byLevel = byLevel; }

    //Buffer
    virtual void BufferRebuildAttr();

    //获取战斗类型相关的buffer属性
    TVecFloat GetBattleAttrVec(UINT8 byBattleType);

private:
    UINT32 _dwAppearState; //外观状态
    UINT32 _dwTimerMapIndex;
    UINT8 _byJob;       //职业
    UINT32 _dwNextBattleTime;
    UINT8 _byLevel;
    bool _bDead;
    
protected:
    CWalker _oWalker;
};

inline CLogObj& operator<<(CLogObj& src, const CCreature& rCreature)
{
    src << " [" << rCreature.GetDescription() << "]";
    return src;
}

inline CLogObj& operator<<(CLogObj& src, const vector<CCreaturePtr>& vecCreature)
{
    for(CCreaturePtr pCreature : vecCreature)
        src << "[" << pCreature->GetDescription() << "]";
    return src;
}

#endif // CREATURE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

