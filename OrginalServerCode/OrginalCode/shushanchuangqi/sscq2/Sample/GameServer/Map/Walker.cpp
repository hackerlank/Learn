#include "stdafx.h"
#include <boost/math/special_functions/fpclassify.hpp>
#include "Walker.h"
#include "Creature.h"
#include "Map.h"
bool CWalker::TrySetCurPoint(const SPoint & rPoint)
{
    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
        return false;
    if(pMap->IsBlockPoint(rPoint))
    {
        LOG_CRI << "Try To Block Point";
        return false;
    }
    _oCurPoint = rPoint;
    return true;
}


void CWalker::SetPath(const vector<SPoint>& rVecPoint)
{
    _vecPoint = rVecPoint;
    _vecDistance.clear();
          
}

bool CWalker::CheckPath(vector<SPoint>& rVecPoint)
{
    if(rVecPoint.size() == 1)
    {
        if(_rCreature.GetPoint() == rVecPoint[0])
        {
            return false;
        }
        else
        {
          rVecPoint.insert(rVecPoint.begin(),_rCreature.GetPoint());

        }

    }
    if(rVecPoint.size() < 2 || rVecPoint.size() > 100)
    {
        LOG_CRI << "Point size  < 2 or Point size > 100 size: " << rVecPoint.size();
        return false;
    }

    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
        return false;
    size_t start = 0;
    if(_rCreature.GetPoint() == rVecPoint[0])
        start = 1;
    for(size_t i = start; i < rVecPoint.size(); ++i)
    {
        if(!pMap->GetMapInfo().IsInMapArea(rVecPoint[i]))
        {
            LOG_CRI << "Point is not in map area: " << rVecPoint[i];
            return false;
        }
        /*
        if(pMap->IsBlockPoint(rVecPoint[i]))
        {
            LOG_CRI << "Point is  in Block: " << rVecPoint[i];
            return false;
        }
        */

    }
    return true;
}

bool CWalker::StartPath(vector<SPoint>& rVecPoint, UINT32 dwTimeIntervel, bool bCheckBlock /*= true*/)
{
    if(rVecPoint.size() < 2)
    {
        LOG_CRI << "Path point size < 2! CreatureID: " << _rCreature.GetCreatureID();
        return false;
    }
    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
    {
        LOG_CRI << "pMap is NULL!";
        return false;
    }
    SPoint& rPoint = _rCreature.GetPoint();
    _fMoveSpeed = _rCreature.GetSpeedForWalker();
    if(_fMoveSpeed < 0.1f)
    {
        LOG_CRI << "_fMoveSpeed is too low: " << _fMoveSpeed;
        return false;
    }
    if(dwTimeIntervel < 100)
        dwTimeIntervel = 100;
    UINT32 dwTickCount = GetTickCount();
    if(_eWalkState == eWalkMove)
    {
#ifdef _WIN32
        if(IsDebuggerPresent())
        {
            UINT32 dwTickInterval = dwTickCount - _dwLastMoveTick;
            if(dwTickInterval > _dwTimeIntervel + 50)
                dwTickInterval = _dwTimeIntervel + 50;
            _dwTotalMoveTick += dwTickInterval;
        }
#endif
        bool bInWalk = GetCurPoint(dwTickCount);
        if((!bInWalk && _dwCurIndex != (UINT32)_vecDistance.size() - 1) ||pMap->HasBlockPoint(rPoint, GetCurPoint(), true))
        {
            LOG_INF << "New and current point has block! fDistance: " << _fMoveSpeed
                << ", MapID: " << pMap->GetMapID() << ", Curr Point: " << rPoint << ", First Point: " << rVecPoint[0];
            ClearPath();
            return false;
        }
        if(_rCreature.GetObjType() == eObjPlayer)
        {
        }
        else
        {
            TVecPoint vecNewPoint;
            vecNewPoint.push_back(GetCurPoint());
            LOG_DBG << "New Point => " << _rCreature.GetLocaleName() << GetCurPoint();
            if(_dwLastMoveTick != 0 && dwTickCount > _dwLastMoveTick)
            {
                float fMovedLength = _fMoveSpeed * (dwTickCount - _dwLastMoveTick) / 1000;
                for(size_t i = 1; i < rVecPoint.size(); ++i)
                {
                    float fLength = GetDistance(rVecPoint[i], rVecPoint[i - 1]);
                    if(fMovedLength > fLength)
                    {
                        fMovedLength -= fLength;
                    }
                    else
                    {
                        //LOG_WRN << "i: " << i;
                        vecNewPoint.insert(vecNewPoint.begin() + 1, rVecPoint.begin() + i, rVecPoint.end());
                        rVecPoint = move(vecNewPoint);
                        break;
                    }
                }
            }
        }
    }
    else if(_rCreature.GetObjType() == eObjPlayer)
    {
#if 0
        float fDistance = GetDistance(rVecPoint[0], _rCreature.GetPoint());
        if(fDistance > _fMoveSpeed)
        {
            CPlayer& rPlayer = (CPlayer&)_rCreature;
            LOG_INF << "Distance exceeds max! fDistance: " << fDistance << ", UsrID: " << rPlayer.GetUserID() << ", RoleID: " << rPlayer.GetRoleID()
                << ", Speed: " << _fMoveSpeed << ", MapID: " << pMap->GetMapID() << ", Curr Point: " << rPoint << ", First Point: " << rVecPoint[0];
            ClearPath();
            return false;
        }
        _fDiffDistance = 0;
        _dwLastDiffTick = dwTickCount;
#endif

    }
    _vecPoint = move(rVecPoint);
    _dwTimeIntervel = dwTimeIntervel;
    _vecDistance.clear();
    _eWalkState = eWalkMove;
    _dwCurIndex = 0;
    _dwPreIndex = 1;
#ifdef _WIN32
    if(IsDebuggerPresent())
        _dwTotalMoveTick = 0;
#endif
    _dwStartMoveTick = dwTickCount;
    _dwLastMoveTick = 0;
    _bCheckBlock = bCheckBlock;
    return OnStep(dwTickCount);
}

void CWalker::ClearPath()
{
    _eWalkState = eWalkStop;
    _vecPoint.clear();
    _dwLastMoveTick = 0;
}

void CWalker::Abort(UINT32 dwTickCount)
{
    if(_eWalkState == eWalkStop)
        return;
    OnStep(dwTickCount, true);
    _eWalkState = eWalkStop;
}

bool CWalker::Continue(UINT32 dwTickCount)
{
    if(_vecPoint.size() < 2)
        return false;
    _vecPoint[0] = GetCurPoint();
    for(size_t i = _dwCurIndex + 1, j = 1; i < _vecPoint.size(); ++i, ++j)
        _vecPoint[j] = _vecPoint[i];
    _vecDistance.clear();
    _eWalkState = eWalkMove;
    _dwCurIndex = 0;
#ifdef _WIN32
    if(IsDebuggerPresent())
        _dwTotalMoveTick = 0;
#endif
    _dwStartMoveTick = dwTickCount;
    _dwLastMoveTick = 0;
    return OnStep(dwTickCount);
}

UINT32 CWalker::GetTotalMoveTick(UINT32 dwTickCount) const
{
    return dwTickCount - _dwStartMoveTick;
}

bool CWalker::GetCurPoint(UINT32 dwTickCount)
{
    assert(_vecPoint.size() >= 2);
    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
        return false;
    if(_vecDistance.empty())
    {
        for(int i = 0; i < (int)_vecPoint.size() - 1; ++i)
            _vecDistance.push_back(GetDistance(_vecPoint[i], _vecPoint[i + 1]));
    }
    float fLength = 0;
#ifdef _WIN32
    if(IsDebuggerPresent())
        fLength = _fMoveSpeed * _dwTotalMoveTick / 1000;
    else
#endif
        fLength = _fMoveSpeed * GetTotalMoveTick(dwTickCount) / 1000;
    _oPrePoint = GetCurPoint();
    _dwPreIndex = _dwCurIndex;
    SPoint oWillPoint;
    for(UINT32 i = 0; i < (UINT32)_vecDistance.size(); ++i)
    {
        float fDistance = _vecDistance[i];
        if(fLength > fDistance)
        {
            fLength -= fDistance;
        }
        else
        {
            SPoint& rPoint1 = _vecPoint[i];
            SPoint& rPoint2 = _vecPoint[i + 1];
            if(fLength == fDistance || fDistance < FLT_EPSILON)
            {
                 oWillPoint  = rPoint2;
            }
            else
            {
                float fPercent = fLength / fDistance;
                if(!boost::math::isfinite(fPercent))
                {
                    fPercent = 1;
                }
                else if(fPercent > 1)
                {
                    fPercent = 1;
                    LOG_CRI << "fPercent invalid: " << fPercent << ", Path: " << _vecPoint;
                }
                float fDeltaX = rPoint2.fX - rPoint1.fX;
                float fDeltaY = rPoint2.fY - rPoint1.fY;
                _fDir = atan2f(fDeltaY, fDeltaX);
                 oWillPoint.fX = rPoint1.fX + fDeltaX * fPercent;
                 oWillPoint.fY = rPoint1.fY + fDeltaY * fPercent;
                if(!pMap->GetMapInfo().IsInMapArea(oWillPoint))
                {
                    LOG_CRI << "Point is not in map area: " << GetCurPoint() << ", Point1: " << rPoint1 << ", Point2: " << rPoint2 << ", fPercent: " << fPercent;
                    TrySetCurPoint(rPoint2);
                    return false;
                }
            }
            if(!TrySetCurPoint(oWillPoint))
            {
                return false;
            }
            _dwCurIndex = i;
            return true;
        }
    }
    SPoint& rPoint = _vecPoint.back();
    TrySetCurPoint(rPoint);
    _dwCurIndex = (UINT32)_vecDistance.size() - 1;
    //到达寻路终点
    return false;
}

void CWalker::GetCurPath(vector<SPoint>& rVecPathPoint)
{
    for(size_t i = _dwCurIndex + 1; i < _vecPoint.size(); ++i)
        rVecPathPoint.push_back(_vecPoint[i]);
}

bool CWalker::GetDestPoint(SPoint& rDestPoint)
{
    if(_vecPoint.empty())
        return false;
    rDestPoint = _vecPoint.back();
    return true;
}

SPoint* CWalker::GetCurDestPoint()
{
    if(_eWalkState == eWalkStop || _vecPoint.empty())
        return NULL;
    if(_dwCurIndex >= _vecPoint.size() - 1)
        return &_vecPoint.back();
    return &_vecPoint[_dwCurIndex + 1];
}

bool CWalker::IsStepBlocked()
{
    bool bLoose =true;
    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
        return true;
    if(_vecPoint.empty())
        return true;
    bool bBlock =false;
    if(_dwPreIndex > _dwCurIndex)
    {
        bBlock = pMap->HasBlockPoint(_rCreature.GetPoint(), _vecPoint[0],bLoose);
        if(bBlock)
        {
            LOG_CRI <<"BLock 1";
        }
        return pMap->HasBlockPoint(_rCreature.GetPoint(), _vecPoint[0], bLoose);
    }
    TVecPoint vecPoint;
    for(UINT32 i = _dwPreIndex + 1; i <= _dwCurIndex; ++i)
        vecPoint.push_back(_vecPoint[i]);
    if(vecPoint.empty())
    {
        if(pMap->HasBlockPoint(_oPrePoint, GetCurPoint(), bLoose))
        {
            LOG_CRI <<"BLOCK 2";
            return true;
        }
    }
    else
    {
        if(pMap->HasBlockPoint(_oPrePoint, vecPoint.front(), bLoose))
        {
            LOG_CRI<<"BLOCK 3";
            return true;
        }
        for(size_t i = 1; i < vecPoint.size(); ++i)
        {
            if(pMap->HasBlockPoint(vecPoint[i - 1], vecPoint[i], bLoose))
            {
                LOG_CRI <<"BLOCK 4";
                return true;
            }
        }
        if(pMap->HasBlockPoint(vecPoint.back(), GetCurPoint(), bLoose))
        {
            LOG_CRI <<"BLOCK 5";
            return true;
        }
    }
    return false;
}

bool CWalker::OnStep(UINT32 dwTickCount, bool bAbort /*= false*/)
{
    CGameMapPtr pMap = _rCreature.GetMap();
    if(pMap == NULL)
    {
        LOG_CRI << "pMap is NULL!";
        _eWalkState = eWalkStop;
        return false;
    }
    vector<SPoint> vecPathPoint;
    if(_dwLastMoveTick == 0)
    {
        for(size_t i = 0; i < _vecPoint.size(); ++i)
            vecPathPoint.push_back(_vecPoint[i]);
        assert(_vecPoint.size() >= 2);
        SPoint& rPoint1 = _vecPoint[0];
        SPoint& rPoint2 = _vecPoint[1];
        float fDeltaX = rPoint2.fX - rPoint1.fX;
        float fDeltaY = rPoint2.fY - rPoint1.fY;
        _fDir = atan2f(fDeltaY, fDeltaX);
        _dwLastMoveTick = dwTickCount;
        if(!_rCreature.MoveTo(vecPathPoint, _fDir, true))
        {
            _eWalkState = eWalkStop;
            return false;
        }
        TrySetCurPoint(rPoint1);
        return true;
    }
#ifdef _WIN32
    if(IsDebuggerPresent())
    {
        UINT32 dwTickInterval = dwTickCount - _dwLastMoveTick;
        if(dwTickInterval > _dwTimeIntervel + 50)
            dwTickInterval = _dwTimeIntervel + 50;
        _dwTotalMoveTick += dwTickInterval;
    }
#endif
    _dwLastMoveTick = dwTickCount;
    bool bInWalk = GetCurPoint(dwTickCount);
    if(bAbort)
    {
        _rCreature.StopMove(GetCurPoint(), _fDir);
        _eWalkState = eWalkStop;
    }
    else if(bInWalk)
    {
        vecPathPoint.push_back(GetCurPoint());
        for(size_t i = _dwCurIndex + 1; i < _vecPoint.size(); ++i)
            vecPathPoint.push_back(_vecPoint[i]);
        if(!_rCreature.MoveTo(vecPathPoint, _fDir, false))
        {
            _eWalkState = eWalkStop;
            return false;
        }
    }
    else
    {
        vecPathPoint.push_back(GetCurPoint());
        _rCreature.MoveTo(vecPathPoint, _fDir, false);
        _eWalkState = eWalkStop;
    }
    return true;
}
bool CWalker::CheckAndSetLastMoveTime()
{
    if(GetTickCount() - _dwLastMoveTime < PLAYER_WALK_TIME_INTERVAL)
    {
        LOG_DBG<<"too small time:"<<GetTickCount() - _dwLastMoveTime<<"qwCreatureID:"<<_rCreature.GetCreatureID();
        return false;
    }

    _dwLastMoveTime = GetTickCount();

    return true;
}
bool CWalker::TimerCheck(UINT32 dwTickCount)
{
    if(_eWalkState != eWalkMove || _vecPoint.empty())
        return false;
#ifdef _DEBUG
    if(_rCreature.GetObjType() == eObjPlayer)
    {
        /*
           CPlayer& rPlayer = (CPlayer&)_rCreature;
           if(rPlayer.GetRoleState() != eRoleLive && rPlayer.GetRoleState() != eRoleGhost)
           LOG_CRI << "Player is dead! " << _rCreature;
           */
    }
    else
    {
        if(_rCreature.IsDead())
            LOG_CRI << "Creature is dead! " << _rCreature;
    }
#endif
    if(_rCreature.IsDead())
    {
        Abort();
        return false;
    }
    /* TODO
       if(_rCreature.GetFightInfo().HasFight())
       {
       Abort(dwTickCount);
       return false;
       }
       */
    if(dwTickCount - _dwLastMoveTick >= _dwTimeIntervel)
        OnStep(dwTickCount);
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

map<UINT64, CWalker*> CWalkerMgr::_arWalkerMap[PLAYER_WALK_MAP_COUNT];

UINT32 CWalkerMgr::SelectMapIndex()
{
    UINT32 dwMinCount = UINT_MAX;
    UINT32 dwIndex = 0;
    for(UINT32 i = 0; i < SLOW_MONSTER_MAP_COUNT; ++i)
    {
        if(_arWalkerMap[i].size() < dwMinCount)
        {
            dwMinCount = (UINT32)_arWalkerMap[i].size();
            dwIndex = i;
        }
    }
    return dwIndex;
}

void CWalkerMgr::AddWalker(CWalker& rWalker)
{
    CCreaturePtr pCreature = ToThisPtr(CONTAINING_RECORD(&rWalker, CCreature, GetWalker()));
    UINT64 qwCreatureID = pCreature->GetCreatureID();
    UINT32 dwIndex = SelectMapIndex();
    rWalker._dwWalkerMapIndex = dwIndex;
    _arWalkerMap[dwIndex].insert(make_pair(qwCreatureID, &rWalker));
}

void CWalkerMgr::DelWalker(CWalker& rWalker)
{
    CCreaturePtr pCreature = ToThisPtr(CONTAINING_RECORD(&rWalker, CCreature, GetWalker()));
    UINT64 qwCreatureID = pCreature->GetCreatureID();
    UINT32 dwIndex = rWalker._dwWalkerMapIndex;
    _arWalkerMap[dwIndex].erase(qwCreatureID);
}

void CWalkerMgr::TimerCheck(UINT32 dwIndex)
{
    UINT32 dwTickCount = GetTickCount();
    for(auto it = _arWalkerMap[dwIndex].begin(); it != _arWalkerMap[dwIndex].end(); ++it)
        it->second->TimerCheck(dwTickCount);
}


