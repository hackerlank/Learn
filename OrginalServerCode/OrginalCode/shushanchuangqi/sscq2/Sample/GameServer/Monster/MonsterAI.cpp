#include "MonsterAI.h"
#include "PathFinder.h"
#include "FighterMgr.h"
#include "Protocols.h" 
#include "MonsterMgr.h"
#include "Monster.h"
#include "Map.h"
#include "Player.h"
#include "ManagerMonsterAI.h"
#include "Random.h"
CMonsterAI::CMonsterAI(CMonster &rMonster,UINT16 wAIID,const SPoint& rPoint ):_rMonster(rMonster),_eMonsterState(eMonsterNone),_tLastStateChangeTime(0),_dwIdleTick(0),_qwTargetID(0),_bInPathFind(false),_eTimerType(eTimerNone),_pAICFG(NULL),_byTimerIndex(0),_byPointIndex(0),_fDirBefore(fInValidDir)
{
    SetAIID(wAIID);
    SetBornPoint(rPoint);
}

CMonsterAI::~CMonsterAI()
{
    LOG_INF << "AI Destroy";
}
void CMonsterAI::SetMonsterState(EMonsterState eMonsterState) 
{ 
    if(eMonsterState == _eMonsterState)
        return;
    if(_eMonsterState == eMonsterDead)
    {
        return ;
    }
    bool bNewAppear = false;
    if((_eMonsterState == eMonsterNone || _eMonsterState == eMonsterBorn) && eMonsterState == eMonsterLive)//设置初速
    {
        _rMonster.Speed() = GetWanderSpeed();
    }
    if(eMonsterState == eMonsterChase)//变速
    {
        _rMonster.Speed() = GetChaseSpeed();
        bNewAppear  =true;
    }
    else if(_eMonsterState == eMonsterChase)
    {
        _rMonster.Speed() = GetWanderSpeed();
        bNewAppear  =true;
    }
    else if(_eMonsterState == eMonsterLive)
    {
        if(_qwTargetID != 0)
        {
            bNewAppear  =true;
        }
        _qwTargetID = 0;
    }
    _eMonsterState = eMonsterState; 
    _tLastStateChangeTime = time(NULL);
    //LOG_INF << "设置状态 :" << _eMonsterState;
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap && bNewAppear)
    {
        pMap->MonsterChange(_rMonster);
        string strMsg = g_MapProtS.BuildPkg_MonsterTargetChange(_rMonster.GetCreatureID(),_qwTargetID);
        pMap->NotifyAllMapPlayer(strMsg);
    }
}

bool CMonsterAI::SetAIID(UINT16 wAIID)
{
    _pAICFG = CMonsterMgr::GetAIConfig(wAIID);
    if(_pAICFG == NULL)
    {
        LOG_CRI << "Can't find AICFG! AIID: " << wAIID;
        return false;
    }
    return true;
}

const SAICFGEx& CMonsterAI::GetAICfg() const
{
    if(_pAICFG == NULL)
    {
        LOG_CRI << "_pAICFG is NULL!";
        static SAICFGEx oAICFG;
        return oAICFG;
    }
    return *_pAICFG;
}

CCreaturePtr CMonsterAI::FindTarget()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap == NULL || !IsActiveFight())
        return NULL;

    CCreaturePtr pTarget = NULL;
    CVisitor oVisitor(eVisitCanFight, _rMonster.GetThisPtr());
    CCollector<CVisitor> oCollector(oVisitor);
    pMap->VisitRoundArea(_rMonster.GetPoint(), GetSightRadius(), oCollector);

    vector<CCreaturePtr> vecCreature;
    oCollector.GetObjectList(vecCreature);
    for(auto it = vecCreature.begin();it != vecCreature.end();)
    {
        if(!CanFight(*(*it))||!IsInSightAngle(*(*it)))
        {
            it = vecCreature.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if(!vecCreature.empty())
        pTarget = CRandom::RandVecElem(vecCreature);
    return pTarget;
}

CCreaturePtr CMonsterAI::GetFightTarget()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(_qwTargetID != 0 && pMap != NULL)
        return pMap->GetCreature(_qwTargetID);
    return NULL;
}

bool CMonsterAI::SetTarget(CCreature& rTarget)
{
    if(_qwTargetID == rTarget.GetCreatureID())
        return true;
    _qwTargetID = rTarget.GetCreatureID();
    //_oTargetPoint = _rMonster.GetPoint();
    if(GetAICfg()._eMoveType == SAICFGEx::eMovePath)
    {
        _oBornPoint = _rMonster.GetPoint();
    }
    SetMonsterState(eMonsterChase);
    g_MonsterAIManager.AddFastMonster(shared_from_this());
    //LOG_DBG << "eMonsterChase";
    //LOG_DBG << "Init Target Distance: " << GetDistance(rTarget.GetPoint(), _rMonster.GetPoint());
    return true;
}
bool CMonsterAI::CanMove()
{
    switch (GetAICfg()._eMoveType)
    {
        case SAICFGEx::eMoveNone:
            {
                return false;
            }
            break;
        case SAICFGEx::eMoveRand:
            {
                if(GetMoveRadius() == 0 )
                {
                    return false;
                }
            }
            break;
        case SAICFGEx::eMovePath:
            {
                if(_rMonster.GetPath() == NULL)
                {
                    return false;
                }
            }
            break;
    }
    return true;
}
bool CMonsterAI::CanFight(CCreature& rCreature)
{
    if(!IsActiveFight())
        return false;
    if(!_rMonster.CanFight(rCreature))
        return false;
    if(!CanMove() && GetDistance(rCreature.GetPoint(),_rMonster.GetPoint()) > GetAttackDistance())
    {
        LOG_DBG << "Target is out of range";
        return false;
    }
    return true;
}
void CMonsterAI::SetIdle()
{
    SetMonsterState(eMonsterLive);
    _dwIdleTick = 1000 * (UINT32)CRandom::RandInt(0, 0);
    switch (GetAICfg()._eMoveType)
    {
        case SAICFGEx::eMoveNone:
            {
                return ;
            }
            break;
        case SAICFGEx::eMoveRand:
            {
                if(GetMoveRadius() != 0 && _vecWalkPoint.empty())
                {
                    GenWalkPoint();
                }
            }
            break;
        case SAICFGEx::eMovePath:
            {
                if(_vecWalkPoint.empty())
                {
                    GenPathPoint();
                }
            }
            break;
    }

}

void CMonsterAI::OnIdle(UINT32 dwCurTick)
{
    if(!CanMove())
        return;
    UINT32 dwLastMoveTick = _rMonster.GetWalk().GetLastMoveTick();
    if(dwCurTick - dwLastMoveTick >= _dwIdleTick)
    {
        switch (GetAICfg()._eMoveType)
        {
            case SAICFGEx::eMoveRand:
                {
                    if(IsActiveFight() && GetDistance(_rMonster.GetPoint(), _oBornPoint) > GetChaseRadius())
                        BackToBornPoint();
                    else
                        StartRandPath();

                }
                break;
            case SAICFGEx::eMovePath:
                {
                    StartPathNext();//到达下个寻路点
                }
                break;
            default:
                break;
        }
    }
}
void CMonsterAI::StartRandPath()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap == NULL)
        return;

    //LOG_INF << "查找下个寻路点";
    SPoint oDestPoint;
    if(!GetRandWalkPoint(oDestPoint))
        return;
    if(_rMonster.GetPoint() == oDestPoint)
        return;
    TVecPoint vecPoint;
    vecPoint.push_back(_rMonster.GetPoint());
    vecPoint.push_back(oDestPoint);
    if(pMap->HasBlockPoint(vecPoint[0], vecPoint[1]))
    {
        if(GetDistance(_rMonster.GetPoint(), _oBornPoint) < GetMoveRadius())
        {
            if(!ReverseWalk())
            {
                _rMonster.GetWalk().ClearPath();
                SetIdle();
                return;
            }
        }
        else
        {
            FindPath(_oBornPoint);
        }
        SetMonsterState(eMonsterWander);
        //LOG_DBG << "eMonsterWander";
        return;
    }
    //LOG_DBG << "Start Path: " << vecPoint;
    if(_rMonster.GetWalk().StartPath(vecPoint, SLOW_MONSTER_TIMER_INTERVAL, false))
    {
        SetMonsterState(eMonsterWander);
        //LOG_DBG << "eMonsterWander";
    }
}
void CMonsterAI::StartPathNext()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap == NULL)
        return;
    if(_byPointIndex >= _vecWalkPoint.size())
    {
        return ;
    }
    if( _vecWalkPoint[_byPointIndex] == _rMonster.GetPoint())//需要找下一个点
    {
        _byPointIndex = (_byPointIndex + 1) %( _vecWalkPoint.size());
    }
    SPoint oDestPoint = _vecWalkPoint[_byPointIndex];
    if(_rMonster.GetPoint() == oDestPoint)
        return;
    TVecPoint vecPoint;
    vecPoint.push_back(_rMonster.GetPoint());
    vecPoint.push_back(oDestPoint);
    if(pMap->HasBlockPoint(vecPoint[0], vecPoint[1]))
    {
        /*
        if(GetDistance(_rMonster.GetPoint(), _oBornPoint) < GetMoveRadius())
        {
            if(!ReverseWalk())
            {
                _rMonster.GetWalk().ClearPath();
                SetIdle();
                return;
            }
        }
        else
        {
            FindPath(_oBornPoint);
        }
        */
        FindPath(oDestPoint);
        SetMonsterState(eMonsterWander);
        //LOG_DBG << "eMonsterWander";
        return;
    }
    //LOG_DBG << "Start Path: " << vecPoint;
    if(_rMonster.GetWalk().StartPath(vecPoint, SLOW_MONSTER_TIMER_INTERVAL, false))
    {
        SetMonsterState(eMonsterWander);
        //LOG_DBG << "eMonsterWander";
    }
    else
    {
        LOG_CRI << "CAN NOT TO NEXT Point";

    }

}


void CMonsterAI::BackToBornPoint()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap == NULL)
        return;
    if(GetDistance(_rMonster.GetPoint(), _oBornPoint) < GetMoveRadius())
    {
        _rMonster.GetWalk().ClearPath();
        SetIdle();
        return;
    }
    switch(_eMonsterState)
    {
        case eMonsterWander:
            break;
        case eMonsterLive:
        case eMonsterChase:
        case eMonsterFight:
            SetMonsterState(eMonsterWander);
            //LOG_DBG << "eMonsterWander";
            break;
        default:
            LOG_CRI << "State error! CurState:" << _eMonsterState;
    }
    SPoint oDestPoint;
    if(!GetRandWalkPoint(oDestPoint))
        return;
    TVecPoint vecPoint;
    vecPoint.push_back(_rMonster.GetPoint());
    vecPoint.push_back(oDestPoint);
    if(pMap->HasBlockPoint(vecPoint[0], vecPoint[1]))
    {
        FindPath(oDestPoint);
    }
    else
    {
        //LOG_DBG << "Start Path: " << vecPoint;
        _rMonster.GetWalk().StartPath(vecPoint, SLOW_MONSTER_TIMER_INTERVAL, false);
    }
}

bool CMonsterAI::FindPath(SPoint& rDestPoint)
{
    if(_bInPathFind)
    {
        LOG_CRI << "Already in PathFind";
        return false;
    }
    //LOG_DBG << "FindPath, CurPoint: " << _rMonster.GetPoint() << ", DestPoint: " << rDestPoint;
    return CPathFindMgr::Instance().FindPath(_rMonster, rDestPoint);
}

void CMonsterAI::OnPathFound(TVecPoint& rVecPath)
{
    if(!_bInPathFind)
        return;
    if(rVecPath.empty())
    {
        LOG_DBG << "A* path is empty!";
        OnPathFoundFail();
    }
    else
    {
        if(rVecPath.size() < 2)
        {
            TVecPoint& rVecNewPath = const_cast<TVecPoint&>(rVecPath);
            rVecNewPath.insert(rVecNewPath.begin(), _rMonster.GetPoint());
        }
        UINT32 dwTimeInterval = 0;//AI时间100毫秒
        if(_eTimerType == eTimerSlow)
            dwTimeInterval = SLOW_MONSTER_TIMER_INTERVAL;
        else if(_eTimerType == eTimerFast)
            dwTimeInterval = FAST_MONSTER_TIMER_INTERVAL;
        else
            DebugBreak();
        _rMonster.GetWalk().StartPath(rVecPath, dwTimeInterval, false);
    }
}

void CMonsterAI::OnPathFoundFail()
{
    time_t tNow = time(NULL);
    if(tNow > _tLastStateChangeTime && tNow - _tLastStateChangeTime > 5)
    {
        SetIdle();
        //LOG_DBG << "eMonsterLive";
        return;
    }
    if(!ReverseWalk())
    {
        LOG_DBG << "ReverseWalk fails! CreatureID: " <<_rMonster.GetCreatureID() << ", ObjType: " << _rMonster.GetObjType();
        SetIdle();
    }
}

bool CMonsterAI::ReverseWalk()
{
    const TVecPoint& rVecPoint = _rMonster.GetWalk().GetPath();
    if(rVecPoint.empty())
        return false;
    TVecPoint vecPoint;
    size_t size = rVecPoint.size();
    vecPoint.resize(size);
    reverse_copy(rVecPoint.begin(), rVecPoint.end(), vecPoint.begin());
    SetMonsterState(eMonsterWander);
    _rMonster.GetWalk().StartPath(vecPoint, SLOW_MONSTER_TIMER_INTERVAL, false);
    return true;
}

bool CMonsterAI::GenWalkPoint()
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap == NULL)
        return false;
    bool bRet = pMap->GetRandPoint(_oBornPoint, GetMoveRadius(), 20, _vecWalkPoint);
    if(_vecWalkPoint.empty())
        LOG_CRI << "GetRandPoint fails for Monster: " << _rMonster.GetMonsterID() << _oBornPoint;
    return bRet;
}

bool CMonsterAI::GenPathPoint()
{
    //TODO: for Test :UseRandPoint
    const SPath *pPath = _rMonster.GetPath();
    if(pPath == NULL)
    {
        return false;
    }
    _vecWalkPoint = pPath->vecPoint;
    _byPointIndex = 0;
    _vecWalkPoint.insert(_vecWalkPoint.begin(),_oBornPoint);
    return true;
}
bool CMonsterAI::GetRandWalkPoint(SPoint& rPoint)
{
    if(_vecWalkPoint.empty())
        return false;
    rPoint = CRandom::RandVecElem(_vecWalkPoint);
    return true;
}

bool CMonsterAI::TryLockTarget(UINT32 dwCurTick)
{
    //LOG_INF <<"TryLockTarget";
    if(IsActiveFight())
    {

        CCreaturePtr pTarget = FindTarget();
        if(pTarget != NULL && SetTarget(*pTarget))
        {
            LOG_INF << "LockTarget";
            return true;
        }
    }
    return false;
}

bool CMonsterAI::TryFightTarget(CCreature& rTarget, UINT32 dwCurTick, bool& bBlocked)
{
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap->HasBlockPoint(_rMonster.GetPoint(), rTarget.GetPoint()))
    {
        bBlocked = true;
        return false;
    }
    float fDistance = GetDistance(_rMonster, rTarget);
    float fAttackRange = GetAttackDistance();
    if(fDistance * 0.9 < fAttackRange)
    {
        SetMonsterState(eMonsterFight);
        _rMonster.FighterToOther(rTarget);
        //TODO:Fighter
#if 0
        if(_bDummy)
        {
            if(StartDummyFight(rTarget))
                SetMonsterState(eMonsterFight);
        }
        else
        {
            EFightType eFightType = CFightTypeUtil::GetFightType(rTarget, _rMonster);
            if(eFightType != eFightInvalid && CFightMgr::StartFight(rTarget, _rMonster, eFightType))
                SetMonsterState(eMonsterFight);
            else
                LOG_CRI << "TryFightTarget error, FightType is " << eFightType << ", MonsterID: " << _wMonsterID << ", MapID: " << pMap->GetMapID();
        }
        _rMonster.GetWalk().ClearPath();
        //LOG_DBG << "eMonsterFight";
#endif
        return true;
    }
    //LOG_DBG << "Try Fight Distance: " << fDistance;

    return false;
}

bool CMonsterAI::TryTraceTarget(CCreature& rTarget, UINT32 dwCurTick, bool bBlocked)
{
    if(!CanMove())
        return false;
    SPoint& rTargetPoint = rTarget.GetPoint();
    UINT32 dwLastMoveTick = _rMonster.GetWalk().GetLastMoveTick();
    if(_rMonster.GetWalk().GetState() == eWalkMove && dwLastMoveTick != 0 &&
            dwCurTick > dwLastMoveTick && dwCurTick - dwLastMoveTick < FAST_MONSTER_TIMER_INTERVAL)
        return true;
    if(GetDistance(_rMonster.GetPoint(), rTargetPoint) < 0.2f)
        return true;
    float fAttackRange = GetAttackDistance();
    //LOG_DBG << "StartPath[" << _rMonster.GetPoint()._fX << "," << _rMonster.GetPoint()._fZ << "][" << rDest._fX << "," << rDest._fZ << "]";
    TVecPoint vecPoint;
    vecPoint.push_back(_rMonster.GetPoint());
    SPoint oSkillPoint = GetMidPoint(rTargetPoint, _rMonster.GetPoint(), fAttackRange);
    CGameMapPtr pMap = _rMonster.GetMap();
    if(pMap->IsBlockPoint(oSkillPoint))
        vecPoint.push_back(rTargetPoint);
    else
        vecPoint.push_back(oSkillPoint);
    //_oTargetPoint = rTargetPoint;
    //LOG_DBG << "New Target Distance: " << GetDistance(rTargetPoint, _rMonster.GetPoint());
    //LOG_DBG << "Set Target Point: " << rTargetPoint;
    if(bBlocked)
        {
            //LOG_CRI << _qwCreatureID << " Find Path: " << _rMonster.GetPoint() << " To " << rTargetPoint;
            return FindPath(rTargetPoint);
        }
        else
        {
            //LOG_DBG << _qwCreatureID << " Start Path: " << vecPoint;
            return _rMonster.GetWalk().StartPath(vecPoint, FAST_MONSTER_TIMER_INTERVAL, false);
        }
    }

    void CMonsterAI::TimerCheckSlow(time_t tNow, UINT32 dwCurTick)
    {
        switch(_eMonsterState)
        {
            case eMonsterLive:
                {
                    if(_rMonster.GetWalk().GetState() == eWalkMove)
                        LOG_CRI << "Move State invalid!";
                    if(TryLockTarget(dwCurTick))
                        break;
                    if(CanMove())
                        OnIdle(dwCurTick);
                }
                break;
            case eMonsterWander:
                {
                    if(TryLockTarget(dwCurTick))
                        break;
                    if(!_rMonster.GetWalk().TimerCheck(dwCurTick) && !_bInPathFind)
                    {
                        SetIdle();

                    }
                }
                break;
            case eMonsterDead:
                break;
            case eMonsterFade:
                break;
            case eMonsterFight:
                {
                    SetIdle();
                }
                break;
            default:
                LOG_CRI << "Invalid Monster State:" << _eMonsterState << _rMonster.GetMonsterID();
        }
    }

    void CMonsterAI::TimerCheckFast(time_t tNow,UINT32 dwCurTick)
    {
        switch(_eMonsterState)
        {
            case eMonsterChase:
                break;
            case eMonsterFight:
                break;
            default:
                LOG_CRI << "Invalid MonsterState: " << _eMonsterState << "MonsterID:" << _rMonster.GetMonsterID();
                return;
        }
        if(CanMove())
            _rMonster.GetWalk().TimerCheck(dwCurTick);
        else
            _rMonster.GetWalk().Abort(dwCurTick);
        if(_bInPathFind)
            return;
        bool bFinishFast = false;
        bool bBlocked = false;
        CCreaturePtr pTarget = GetFightTarget();
        if(pTarget == NULL)
        {
            bFinishFast = true;
            goto EXIT;
        }
        if(!CanFight(*pTarget))
        {
            bFinishFast = true;
            goto EXIT;
        }
        if(TryFightTarget(*pTarget, dwCurTick, bBlocked))
        {
            bFinishFast = true;
            goto EXIT;
        }
        if(!TryTraceTarget(*pTarget, dwCurTick, bBlocked))
        bFinishFast = true;

EXIT:
    if(bFinishFast && _eMonsterState != eMonsterDead )
    {
        _qwTargetID = 0;
        OnFinishFast(dwCurTick);
        g_MonsterAIManager.AddSlowMonster(shared_from_this());
    }
}

void CMonsterAI::OnAttacked(CCreature& rAttacker)
{
    _rMonster.GetWalk().Abort();
    _eMonsterState = eMonsterFight;
}

bool CMonsterAI::IsActiveFight() const
{
    return GetAICfg()._Attack == 1;
}

UINT32 CMonsterAI::GetWanderSpeed() const
{
    return GetAICfg()._StandbySpeed;
}

UINT32 CMonsterAI::GetChaseSpeed() const
{
    return GetAICfg()._ChaseSpeed;
}


void CMonsterAI::OnFinishFast(UINT32 dwCurTick)
{
    if(_eMonsterState != eMonsterFight)
        SetIdle();
    _rMonster.GetWalk().Abort(dwCurTick);
    _rMonster.GetWalk().ClearPath();
}
float CMonsterAI::GetAttackDistance() const
{
    return GetAICfg()._AtkDistance;
}// 攻击距离

float CMonsterAI::GetMoveRadius() const
{
    return GetAICfg()._MoveRadius;
}// 	移动范围

float CMonsterAI::GetSightRadius() const
{
    return GetAICfg().SightRadius;
}//	视野范围

float CMonsterAI::GetChaseRadius() const
{
    return GetAICfg()._FightRadius;
}//	追击范围
CMonsterPtr CMonsterAI::GetMonster()
{
    return _rMonster.GetThisPtr();
}

bool CMonsterAI::IsInSightAngle(CCreature& rTarget)
{
    //得到怪物视野
    if(GetAICfg().SightAngle == 0 || GetAICfg().SightAngle >=360 )
    {
        return true;
    }
    float fAngle = (float)(GetAICfg().SightAngle)/2;//夹角除2

    fAngle = fAngle/180*PI;
    if(fInValidDir != _fDirBefore)
    {
        fAngle += CheckAngle(_fDirBefore -_rMonster.GetDir())/2;
        _fDirBefore = fInValidDir;
    }
    float fDeltaX = rTarget.GetPoint().fX - _rMonster.GetPoint().fX;
    float fDeltaY = rTarget.GetPoint().fY - _rMonster.GetPoint().fY;
    float fDir = _rMonster.GetDir() -  atan2f(fDeltaY, fDeltaX);//夹角
    LOG_INF << "self Angle is:"<<fAngle;
    fDir = CheckAngle(fDir);
    LOG_INF<<"夹角是:" << fDir;
    return fAngle >= fDir;
}

float CMonsterAI::CheckAngle(float fDir) 
{
    if(fDir < (-1)*PI)
    {
        fDir += 2*PI;
    }
    else if( fDir > PI)
    {
        fDir = 2*PI - fDir;
    }
    return abs(fDir);

}

void CMonsterAI::SetPreDir(float fDir)
{
    _fDirBefore = fDir;
}
