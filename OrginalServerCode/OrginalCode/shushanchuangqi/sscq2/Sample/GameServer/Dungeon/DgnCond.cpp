#include "DgnCond.h"
EDgnCondStatus DungeonCondBase::GetStatus()
{
    DgnSucCond *pBase = dynamic_cast<DgnSucCond*>(this);
    if(pBase != NULL)
    {
        return pBase->eStatus;
    }
    return eCondFal;
}

DungeonCondSucMonster::DungeonCondSucMonster(UINT16 wId,UINT16 wMonster,UINT8 byNum)
{  
    wCondId = wId;
    wMonsterGroup = wMonster;
    byTotalNum = byNum;
    byCurNum = 0;
}

bool DungeonCondSucMonster::KillMonster(UINT16 wGroup)
{
    if(eStatus != eCondRun)
    {
        return false;
    }
    if(wMonsterGroup != wGroup)
    {
        return false;
    }
    byCurNum++;
    if(byCurNum == byTotalNum)
    {
        eStatus = eCondSuc;
    }
    return true;
}

DgnSucCondPtr DungeonCondSucMonster::GetStream()
{
    SucMonsterPtr pMonster(new SucMonster(static_cast<SucMonster &>(*this)));
                return pMonster;
}

DungeonCondSucGather::DungeonCondSucGather(UINT16 wId,UINT16 wGatherId,UINT8 byNum)
{  
    wCondId = wId;
    wGather = wGatherId;
    byTotalNum = byNum;
    byCurNum = 0;
}

bool DungeonCondSucGather::GatherFinish(UINT16 wGatherId)
{
    if(eStatus != eCondRun)
    {
        return false;
    }
    if(wGather != wGatherId)
    {
        return false;
    }
    byCurNum++;
    if(byCurNum == byTotalNum)
    {
        eStatus = eCondSuc;
    }
    return true;
}

DgnSucCondPtr DungeonCondSucGather::GetStream()
{
    SucGatherPtr pGather(new SucGather(static_cast<SucGather &>(*this)));
            return pGather;
}

DungeonCondSucTurns::DungeonCondSucTurns(UINT16 wId,UINT8 byTurns)
{
    wCondId = wId;
    byTotalTurns = byTurns;
    byCurTurns = 0;
    eStatus = eCondSuc;
}

bool DungeonCondSucTurns::AddTurns(UINT8 byTurns)
{
    if(byCurTurns + byTurns > 255)
    {
        byCurTurns = 255;
        return true;
    }
    byCurTurns += byTurns;
    if(byCurTurns  > byTotalTurns)
    {
        eStatus = eCondFal;
    }
    return true;
}

DgnSucCondPtr DungeonCondSucTurns::GetStream()
{
    SucTurnsPtr pTurns(new SucTurns(static_cast<SucTurns &>(*this)));
    return pTurns;
}

DungeonCondSucInTimer::DungeonCondSucInTimer(UINT16 wId,UINT32 dwTimer)
{
    wCondId = wId;
    dwTotalTimer = dwTimer;
    dwBeginTimer = time(NULL);
    eStatus = eCondSuc;
}

bool DungeonCondSucInTimer::TimerCheck(UINT32 tNow)
{
    if(eStatus == eCondFal)
    {
        return false;
    }
    if(tNow > dwTotalTimer + dwBeginTimer)
    {
        eStatus = eCondFal;
        return true;
    }
    return false;
}

DgnSucCondPtr DungeonCondSucInTimer::GetStream()
{
    SucInTimerPtr pSucInTimer(new SucInTimer(static_cast<SucInTimer &>(*this)));
    return pSucInTimer;
}

DungeonCondSucMonsterInTimer::DungeonCondSucMonsterInTimer(UINT16 wId,UINT16 wMonster,UINT8 byNum,UINT32 dwTimer)
{
    wCondId = wId;
    dwTotalTimer = dwTimer;
    dwBeginTimer = time(NULL);
    wMonsterGroup = wMonster;
    byTotalNum = byNum;
    byCurNum = 0;
}

bool DungeonCondSucMonsterInTimer::KillMonster(UINT16 wGroup)
{
    if(eStatus != eCondRun)
    {
        return false;
    }
    if(wMonsterGroup != wGroup)
    {
        return false;
    }
    byCurNum++;
    if(byCurNum == byTotalNum)
    {
        eStatus = eCondSuc;
    }
    return true;
}

bool DungeonCondSucMonsterInTimer::TimerCheck(UINT32 tNow)
{
    if(eStatus == eCondFal)
    {
        return false;
    }
    if(tNow > dwTotalTimer + dwBeginTimer)
    {
        eStatus = eCondFal;
        return true;
    }
    return false;
}

DgnSucCondPtr DungeonCondSucMonsterInTimer::GetStream()
{
    SucMonsterInTimerPtr pSucMonsterInTimer(new SucMonsterInTimer(static_cast<SucMonsterInTimer &>(*this)));
    return pSucMonsterInTimer;
}

DungeonCondSucGatherInTimer::DungeonCondSucGatherInTimer(UINT16 wId,UINT16 wGatherId,UINT8 byNum,UINT32 dwTimer)
{
    wCondId = wId;
    dwTotalTimer = dwTimer;
    dwBeginTimer = time(NULL);
    wGather = wGatherId;
    byTotalNum = byNum;
    byCurNum = 0;
}

bool DungeonCondSucGatherInTimer::GatherFinish(UINT16 wGatherId)
{
    if(eStatus != eCondRun)
    {
        return false;
    }
    if(wGather != wGatherId)
    {
        return false;
    }
    byCurNum++;
    if(byCurNum == byTotalNum)
    {
        eStatus = eCondSuc;
    }
    return true;
}

bool DungeonCondSucGatherInTimer::TimerCheck(UINT32 tNow)
{
    if(eStatus == eCondFal)
    {
        return false;
    }
    if(tNow > dwTotalTimer + dwBeginTimer)
    {
        eStatus = eCondFal;
        return true;
    }
    return false;
}

DgnSucCondPtr DungeonCondSucGatherInTimer::GetStream()
{
    SucGatherInTimerPtr pSucGatherInTimer(new SucGatherInTimer(static_cast<SucGatherInTimer &>(*this)));
    return pSucGatherInTimer;
}

DungeonCondSucFightWithMonsterMinTimes::DungeonCondSucFightWithMonsterMinTimes(UINT16 wId,UINT16 wGroupId,UINT8 byNum)
{
    wCondId = wId;
    wGroup = wGroupId;
    byTotalTimes = byNum;
    eStatus = eCondSuc;
}

bool DungeonCondSucFightWithMonsterMinTimes::FightWithMonster(UINT16 wGroupId)
{
    if(eStatus == eCondFal)
    {
        return false;
    }
    if(wGroupId != wGroup)
    {
        return false;
    }
    byCurTimes++;
    if(byCurTimes >= byTotalTimes)
    {
        eStatus = eCondFal;
    }
    return true;

}
#define GetBaseStream(T) \
        T##Ptr pSuc##T(new T(static_cast<T &>(*this)));\
        return pSuc##T;
DgnSucCondPtr DungeonCondSucFightWithMonsterMinTimes::GetStream()
{
    GetBaseStream(SucFightWithMonsterMinTimes);

}

DungeonCondSucArriveArea::DungeonCondSucArriveArea(UINT16 wId,UINT16 wAreaId)
{
    wCondId = wId;
    wAreaID = wAreaId;
}

bool DungeonCondSucArriveArea::ArriveArea(UINT16 wAreaId)
{
    if(eStatus != eCondRun)
    {
        return false;
    }
    if(wAreaId != wAreaID)
    {
        return false;
    }
    eStatus = eCondSuc;
    return true;
}

DgnSucCondPtr DungeonCondSucArriveArea::GetStream()
{
    GetBaseStream(SucArriveArea);
}
