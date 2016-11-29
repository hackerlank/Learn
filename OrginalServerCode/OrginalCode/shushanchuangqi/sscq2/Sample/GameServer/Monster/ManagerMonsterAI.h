#ifndef MANAGERMONSTERAI_H__
#define MANAGERMONSTERAI_H__
#include "MonsterAI.h"
class CMonsterAIManager
{
    public:
        CMonsterAIPtr CreateMonsterAI(CMonster &rMonster,UINT16 wAI,const SPoint& rPoint);
        void DestroyMonsterAI(CMonsterAIPtr pAIPtr);
        void AddSlowMonster(CMonsterAIPtr pAIPtr);
        void AddFastMonster(CMonsterAIPtr pAIPtr);
        void TimerCheckSlow(UINT32 dwIndex, time_t tNow); 
        void TimerCheckFast(UINT32 dwIndex, time_t tNow);
        void Destroy();
    private:
        
        set<CMonsterAIPtr> _arrayFastTimer[FAST_MONSTER_MAP_COUNT];
        set<CMonsterAIPtr> _arraySlowTimer[SLOW_MONSTER_MAP_COUNT];
};
extern CMonsterAIManager g_MonsterAIManager;
#endif// MONSTERAI_H__
