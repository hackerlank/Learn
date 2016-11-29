#include "ManagerMonsterAI.h"
#include "MonsterMgr.h"
#include "Monster.h"
CMonsterAIManager g_MonsterAIManager;
CMonsterAIPtr CMonsterAIManager::CreateMonsterAI(CMonster &rMonster,UINT16 wAI,const SPoint& rPoint)
{
    CMonsterAIPtr pAI(new CMonsterAI(rMonster,wAI,rPoint));
    if(pAI == NULL)
    {
        return NULL;
    }
    AddSlowMonster(pAI);
    //出生动画,需要配出生时间
    if(0)
    {
        pAI->SetMonsterState(eMonsterBorn);
        //发送客户端

    }
    else
    {
        pAI->SetIdle();
    }
    return pAI;
}
void   CMonsterAIManager::DestroyMonsterAI(CMonsterAIPtr pAI)
{
    if(pAI == NULL)
    {
        return ;
    }
    pAI->SetMonsterState(eMonsterDead);

}

void  CMonsterAIManager::AddSlowMonster(CMonsterAIPtr pAI)
{
    if(pAI == NULL || SLOW_MONSTER_MAP_COUNT <= 0)
    {
        return ;
    }
    UINT32 dwSize = _arraySlowTimer[0].size();
    int iMin = 0;
    for (auto i = 1; i != SLOW_MONSTER_MAP_COUNT;i++)
    {
        if(_arraySlowTimer[i].size() < dwSize)
        {
            dwSize = _arraySlowTimer[i].size();
            iMin = i;
        }

    }
    pAI->SetTimerSign(iMin,eTimerSlow);
    _arraySlowTimer[iMin].insert(pAI);
}

void  CMonsterAIManager::AddFastMonster(CMonsterAIPtr pAI)
{
    if(pAI == NULL || FAST_MONSTER_MAP_COUNT <= 0)
    {
        return ;
    }
    UINT32 dwSize = _arrayFastTimer[0].size();
    int iMin = 0;
    for (auto i = 1; i != FAST_MONSTER_MAP_COUNT;i++)
    {
        if(_arrayFastTimer[i].size() < dwSize)
        {
            dwSize = _arrayFastTimer[i].size();
            iMin = i;
        }

    }
    pAI->SetTimerSign(iMin,eTimerFast);
    _arrayFastTimer[iMin].insert(pAI);
}

void CMonsterAIManager::TimerCheckSlow(UINT32 dwIndex, time_t tNow)
{
    if(dwIndex >= SLOW_MONSTER_MAP_COUNT)
    {
        return ;
    }
    UINT32 dwTickCount = GetTickCount();
    auto& rSetSlowMonster = _arraySlowTimer[dwIndex];
    for(auto pos = rSetSlowMonster.begin();pos != rSetSlowMonster.end();)
    {
        CMonsterAIPtr pAI = *pos;
        if(pAI->GetTimerType() != eTimerSlow||pAI ->GetMonsterState() == eMonsterDead)
        {
            pos = rSetSlowMonster.erase(pos);
        }
        else 
        {
            pAI->TimerCheckSlow(tNow, dwTickCount);
            pos++;
        }
    }
}

void CMonsterAIManager::TimerCheckFast(UINT32 dwIndex, time_t tNow)
{
    if(dwIndex >= FAST_MONSTER_MAP_COUNT)
    {
        return ;
    }
    UINT32 dwTickCount = GetTickCount();
    auto& rSetFastMonster = _arrayFastTimer[dwIndex];
    for(auto pos = rSetFastMonster.begin();pos != rSetFastMonster.end();)
    {
        CMonsterAIPtr pAI = *pos;
        if(pAI->GetTimerType() != eTimerFast||pAI ->GetMonsterState() == eMonsterDead)
        {
            pos = rSetFastMonster.erase(pos);
        }
        else
        {   pAI->TimerCheckFast(tNow, dwTickCount);
            pos++;
        }
    }
}

void  CMonsterAIManager::Destroy()
{
    for(size_t pos =0 ;pos != FAST_MONSTER_MAP_COUNT;pos++)
    {
        _arrayFastTimer[pos].clear();
    }
    for(size_t pos =0 ;pos != SLOW_MONSTER_MAP_COUNT;pos++)
    {
        _arraySlowTimer[pos].clear();
    }

}
