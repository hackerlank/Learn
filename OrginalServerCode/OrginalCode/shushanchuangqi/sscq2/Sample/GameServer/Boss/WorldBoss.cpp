
#include "WorldBoss.h"
#include "WorldBossMgr.h"
#include "Battle.h"

const UINT32 WORLDBOSS_LAST  = 600;

CWorldBoss::CWorldBoss() : 
    _dwLast(WORLDBOSS_LAST), _dwLastHP(WORLDBOSS_MAX_HP),
    _dwLastAtk(WORLDBOSS_MIN_ATK), _dwLastMAtk(WORLDBOSS_MIN_ATK), _fExpFactor(1.f)
{
    ResetLevel();
}


CWorldBoss::~CWorldBoss()
{}

void CWorldBoss::ReadjustBattleFighterList(vector<TVecBattleFighterPtr>& vecvecBattleFighter)
{
    if (vecvecBattleFighter.empty() || vecvecBattleFighter[0].empty())
        return;


 

    // XXX: fix the world boss attrs
    IBattleFighterPtr& pFighter = vecvecBattleFighter[0][0]; // XXX: 第一个肯定是BOSS

    pFighter->SetMaxHP(GetLastHP());
    pFighter->SetHP(_dwHP);

    //设置等级
    pFighter->SetLevel(GetLevel());

    pFighter->SetFighterAttr(EFIGHTATTR_PHYATK,GetLastAtk());
    pFighter->SetFighterAttr(EFIGHTATTR_MGCATK,GetLastMAtk());

    LOG_INF<<"worldboss set atk:"<<GetLastMAtk()<<"HP:"<<_dwHP;
    
    return;
}

void CWorldBoss::OnDie(CCreature& rKiller)
{
    if(0 == GetHP())
    {
        _bDead = true;
        CWorldBossMgr::Instance().OnDead(*this, rKiller);
    }
}

void CWorldBoss::OnKill(CCreature& rTarget)
{
    // TODO: 
}

void CWorldBoss::OnAttacked(CCreature& rAttacker)
{
    // TODO: 
}

void CWorldBoss::OnAttacked(CCreature& rAttacker, TVecBattleFighterPtr& vecFighters)
{

    CPlayer& rPlayer = (CPlayer&)(rAttacker);

    // XXX: 因为世界BOSS只有一个上阵，所以第一个就是BOSS
    if (!vecFighters.size())
    {
        //boss 被打死
        UINT32 dwScore = _dwHP;
        _dwHP = 0;
        CWorldBossMgr::Instance().OnBossDamage(rPlayer, dwScore,_dwHP);
        return;
    }
    IBattleFighterPtr& pBoss = vecFighters[0];

    UINT32 dwScore = _dwHP - pBoss->GetHP();
    _dwHP = pBoss->GetHP();
    CWorldBossMgr::Instance().OnBossDamage(rPlayer, dwScore,_dwHP);

    //CWorldBossMgr::Instance().BossHPNotify(GetHPPercent(), _dwHP, dwScore);
    // TODO: 打世界BOSS失败后虚弱BUFF

    //LOG_CRI << "HP: " << _dwHP << " MAXHP: " << _dwMaxHP;
}

bool CWorldBoss::CanFight(CCreature& /*rCreature*/)
{
    return !_bDead;
}

bool CWorldBoss::IsAttackable()
{
    return !_bDead;
}

void CWorldBoss::ResetLevel()
{
    SetLevel(30 + GetLastHP()/5000000);
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

