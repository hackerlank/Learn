
#ifndef WORLDBOSS_H_
#define WORLDBOSS_H_

#include "Boss.h"

class CWorldBoss : public CBoss
{
public:
    CWorldBoss();
    virtual ~CWorldBoss();

    virtual EMonsterType GetMonsterType() const { return eWorldBossMonster; }
    virtual void OnDie(CCreature& rKiller);
    virtual void OnKill(CCreature& rTarget);
    virtual void OnAttacked(CCreature& rAttacker);
    virtual bool CanFight(CCreature& /*rCreature*/);
    virtual bool IsAttackable();
    virtual bool IsWorldBoss() const { return true; }
    virtual void ReadjustBattleFighterList(vector<TVecBattleFighterPtr>& vecvecBattleFighter);
    void OnAttacked(CCreature& rAttacker, TVecBattleFighterPtr& vecFighters);


    void SetLast(UINT32 dwLast) { _dwLast = dwLast; }
    UINT32 GetLast() const { return _dwLast; }
    void SetLastHP(UINT32 dwHP) { _dwLastHP = dwHP; ResetLevel();}
    UINT32 GetLastHP() const { return _dwLastHP; }
    void SetLastAtk(UINT32 dwLastAtk) { _dwLastAtk = dwLastAtk; }
    UINT32 GetLastAtk() const { return _dwLastAtk; }
    void SetLastMAtk(UINT32 dwLastMAtk) { _dwLastMAtk = dwLastMAtk; }
    UINT32 GetLastMAtk() const { return _dwLastMAtk; }

    float GetExpFactor() const { return _fExpFactor; }
    void SetExpFactor(float fFactor) { _fExpFactor = fFactor; }

    void ResetLevel();

private:
    UINT32 _dwLast; // 上次持续时长
    UINT32 _dwLastHP; // 上次最大血量
    INT32 _dwLastAtk; // 上次物理攻击
    INT32 _dwLastMAtk; // 上次魔法攻击
    float _fExpFactor; // 经验位数
};

#endif // WORLDBOSS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

