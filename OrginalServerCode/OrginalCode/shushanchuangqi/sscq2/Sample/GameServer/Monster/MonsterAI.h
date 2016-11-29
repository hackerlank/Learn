#ifndef MONSTERAI_H__
#define MONSTERAI_H__
#include "stdafx.h"
#include "Point.h"
class CMonster;
struct SAICFGEx;
enum EMonsterState
{
    eMonsterNone,
    eMonsterBorn,//出生,无敌
    eMonsterLive,//	空闲
    eMonsterDead,//	死亡
    eMonsterWander,//	漫游
    eMonsterChase,//	追击
    eMonsterFight,//	战斗
    eMonsterLeave,//	离开
    eMonsterFade,//	消失
};

enum ETimerType
{
    eTimerNone,
    eTimerFast,
    eTimerSlow
};
const float fInValidDir = -1*2*PI;
class CMonsterAI: public enable_shared_from_this<CMonsterAI>, public CPoolObj<CMonsterAI>
{
    public:
        CMonsterAI(CMonster &rMonster,UINT16 wAIID,const SPoint& rPoint );
         ~CMonsterAI();
    public:
        EMonsterState GetMonsterState() const
        { return _eMonsterState; }

        void SetMonsterState(EMonsterState eMonsterState);
        bool SetAIID(UINT16 wAIID);
        const SAICFGEx& GetAICfg() const;
        bool IsActiveFight() const;
        UINT32 GetWanderSpeed() const;
        UINT32 GetChaseSpeed() const;
        float GetAttackDistance() const;
        float GetMoveRadius() const;
        float GetSightRadius() const;
        float GetChaseRadius() const;
        CCreaturePtr FindTarget();
        CCreaturePtr GetFightTarget();
        virtual bool IsDead() const
        { return _eMonsterState == eMonsterDead; }

        bool SetTarget(CCreature& rTarget);
        bool CanMove();
        void SetIdle();
        void StartRandPath();
        void StartPathNext();
        void BackToBornPoint();
        bool FindPath(SPoint& rDestPoint);
        void OnPathFound(TVecPoint& rVecPath);
        bool GenWalkPoint();
        bool GenPathPoint();
        bool GetRandWalkPoint(SPoint& rPoint);
        bool IsInPathFind() const
        { return _bInPathFind; }

        void SetInPathFind(bool bInPathFind)
        { _bInPathFind = bInPathFind; }

        bool TryLockTarget(UINT32 dwCurTick);
        bool TryFightTarget(CCreature& rTarget, UINT32 dwCurTick, bool& bBlocked);
        bool TryTraceTarget(CCreature& rTarget, UINT32 dwCurTick, bool bBlocked);
        const SPoint& GetBornPoint() const
        { return _oBornPoint; }

        void SetBornPoint(const SPoint& rBornPoint)
        { _oBornPoint = rBornPoint; }
        void TimerCheckSlow(time_t tNow, UINT32 dwCurTick);
        void TimerCheckFast(time_t tNow,UINT32 dwCurTick);
        void OnAttacked(CCreature& rAttacker);
        void SetTimerSign(UINT8 byTimerIndex,ETimerType eTimerType)
        {
            _byTimerIndex = byTimerIndex;
            _eTimerType = eTimerType;
        }
        void GetTimerSign(UINT8& byTimerIndex,ETimerType& eTimerType)
        {
            byTimerIndex = _byTimerIndex;
            eTimerType = _eTimerType;
        }
        ETimerType GetTimerType(){return _eTimerType;}
        CMonsterPtr GetMonster();
        bool IsInSightAngle(CCreature& rTarget);
        void SetPreDir(float fDir);
    protected:
        void OnPathFoundFail();
        bool ReverseWalk();
        void OnIdle(UINT32 dwCurTick);
        void OnFinishFast(UINT32 dwCurTick);
        bool CanFight(CCreature& rCreature);
        float CheckAngle(float fDir);
    private:
        CMonster& _rMonster;
        EMonsterState _eMonsterState;//怪物状态
        time_t _tLastStateChangeTime; //状态最后一次改变的时间
        UINT32 _dwIdleTick;
        UINT64 _qwTargetID;
        //SPoint _oTargetPoint;
        SPoint _oBornPoint;
        bool _bInPathFind;
        TVecPoint _vecWalkPoint;
        ETimerType _eTimerType;
        const SAICFGEx* _pAICFG;
        UINT8 _byTimerIndex;
        UINT8 _byPointIndex;
        float _fDirBefore;


};
#endif// MONSTERAI_H__
