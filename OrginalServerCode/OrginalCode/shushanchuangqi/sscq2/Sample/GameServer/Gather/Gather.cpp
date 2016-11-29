#include "stdafx.h"
#include "Player.h"
#include "User.h"
#include "Map.h"
#include "GatherMgr.h"
#include "Task.h"
#include "UserMgr.h"
#include "Protocols.h"
    CGather::CGather(UINT16 wGatherID, UINT32 dwInstID, SGatherCFGEx& rGatherCFG,UINT64 qwVersion)
: IGather(wGatherID, dwInstID, rGatherCFG,qwVersion),
    _pVecTaskID(CTaskConfMgr::Instance().GetGatherTask(wGatherID))
{
    _wRemCount = GetGatherConfig()._wGatherNum;
    _wInGathering = 0;
}

CGather::~CGather()
{
    CancelAll();
}

bool CGather::TaskCheck(CPlayer& rPlayer)
{
    if(!GetGatherConfig().CheckHasOtherType(SGatherCFGEx::EOTHER_ISTASK))
    {
        return true;
    }
    if(NULL == _pVecTaskID)
    {
        return false;
    }
    for(size_t i = 0, size = _pVecTaskID->size(); i < size; ++i)
    {
        UINT16 wTaskID = (*_pVecTaskID)[i];
        CTaskPtr pTask = rPlayer.GetUser().GetTaskPkg().FindTask(wTaskID);
        if(NULL != pTask && eTaskAccept == pTask->GetTaskState())
            return true;
    }
    return false;
}

EGatherResult CGather::CanConsume(CPlayer& rPlayer)
{
    return IGather::CanConsume(rPlayer);
}


void CGather::Consume(CPlayer& rPlayer)
{
    IGather::Consume(rPlayer);

}



EGatherResult CGather::CanGater(CPlayer& rPlayer,bool bIsFinish)
{

    if(!CanGatherTwoPerson() &&  _wRemCount == 0 && !bIsFinish)
    {
        return eGatherNumLimit;
    }
    if(GetDistance(*this,rPlayer) > SParamConfig::wGatherDist)
    {
        return eGatherTooFar;
    }
    if(!TaskCheck(rPlayer))
    {
        return eGatherTask;
    }
    UINT8 byLua =GetGatherConfig().CanGagtherFromLua(rPlayer);
    if(byLua != 0)
    {
        return eGatherLuaErr;
    }
    return IGather::CanGater(rPlayer,bIsFinish);
}

UINT32 CGather::AddGather(CPlayer& rPlayer)
{
    if(!_mapGaterPlayer.insert(make_pair(rPlayer.GetRoleID(),time(NULL))).second)
    {
        LOG_CRI << "Insert Fal";
    }
    if(!CanGatherTwoPerson() && _wRemCount > 0 && FoverNUM != _wRemCount )
    {
        _wRemCount--;
        _wInGathering++;
        //发采集改变消息
        SendGatherChangeInfo();
    }
    //设置采集状态
    SetPlayerGather(rPlayer);
    return IGather::AddGather(rPlayer);
}

void CGather::CancelGather(CPlayer& rPlayer)
{
    _mapGaterPlayer.erase(rPlayer.GetRoleID());
    if(!CanGatherTwoPerson() && _wInGathering > 0 && FoverNUM != _wRemCount)
    {
        _wInGathering--;
        _wRemCount++;

    }
    //发送采集中断消息
    SendCancelGather(rPlayer,eGatherCancel);
    //清除采集状态
    ClearPlayerGather(rPlayer);
}

bool CGather::CanDisappear()
{
    return  _wInGathering == 0 && _wRemCount == 0;
}

void CGather::TimerCheck(time_t now)
{
    for(auto iter =  _mapGaterPlayer.begin();iter !=  _mapGaterPlayer.end();)
    {
        CPlayer* pPlayer =NULL;
        EGatherResult eResult = eGatherSuccess;
        do
        {
            CUserPtr pUser =  CUserMgr::GetUserByUserID(iter->first);
            if(NULL == pUser)
            {
                eResult = eGatherOtherErr;
                break;
            }
            CPlayer& rPlayer = *(pUser->GetPlayer());
            pPlayer = &rPlayer;
            if(rPlayer.GetMap() == NULL)
            {
                eResult = eGatherOtherErr;
                break;
            }
            if(rPlayer.GetMap() != GetMap())
            {
                eResult = eGatherTooFar;
                break;
            }
            if(GetDistance(*this,rPlayer) > SParamConfig::wGatherDist)
            {
                eResult = eGatherTooFar;
                break;
            }
            if(now - iter->second >= GetGatherConfig()._wGatherTimer)
            {
                eResult = eGatherFinish;
                break;
            }
        }while(0);
        if( eResult  != eGatherSuccess)
        {
            EGatherResult  eOpResult = eGatherSuccess;
            if(eResult == eGatherFinish)
            {
                std::vector<SItemGenInfo> vecItems;
                TVecResource vecRes;
                eOpResult = GatherFinish(*pPlayer,&vecItems,&vecRes);
                bool bNeedDisappear =false;
                if(eOpResult == eGatherSuccess)
                {
                    if(!CanGatherTwoPerson() && FoverNUM != _wRemCount)
                    {
                        if(_wInGathering > 0 )
                        {
                            _wInGathering--;
                        }
                    }
                    else if(CanGatherTwoPerson() && FoverNUM != _wRemCount)
                    {
                        if(_wRemCount > 0)
                        {
                            _wRemCount--;
                        }
                    }
                    if(CanDisappear())
                    {
                        bNeedDisappear = true;
                    }
                    //TODO:发送采集成功消息
                    SendCancelGather(*pPlayer,eGatherFinish);
                    //清除采集状态
                    ClearPlayerGather(*pPlayer);
                    iter =_mapGaterPlayer.erase(iter);
                    if(bNeedDisappear)
                    {
                        CancelAll(eGatherNotExist);
                        Disappear();
                        return;
                    }
                    else 
                    {
                        SendGatherChangeInfo();
                    }
                    continue;
                }
            }
            if(eOpResult != eGatherSuccess||eResult != eGatherFinish)
            {
                EGatherResult  eReturn;
                if(eOpResult != eGatherSuccess)
                {
                    eReturn = eOpResult;
                }
                else
                {
                    eReturn = eResult;
                }
                if( !CanGatherTwoPerson() && _wInGathering > 0 && FoverNUM != _wRemCount)
                {
                    _wInGathering--;
                    _wRemCount++;
                    //发采集改变消息
                    SendGatherChangeInfo();
                }
                //发送采集中断消息
                if(pPlayer)
                {
                    SendCancelGather(*pPlayer,eReturn);
                    //清除采集状态
                    ClearPlayerGather(*pPlayer);
                }
                iter =_mapGaterPlayer.erase(iter);
                continue;
            }

        }
        else
        {
            ++iter;
        }
    }
}

void  CGather::CancelAll(EGatherResult eResult)
{
    for(auto iter =  _mapGaterPlayer.begin();iter !=  _mapGaterPlayer.end();iter++)
    {
        CUserPtr pUser =  CUserMgr::GetUserByUserID(iter->first);
        if(NULL == pUser)
        {
            continue;
        }
        CPlayerPtr pPlayer = pUser->GetPlayer();
        //发送采集中断消息
        SendCancelGather(*pPlayer,eResult);
        //清除采集状态
        ClearPlayerGather(*pPlayer);
    }
    if(!CanGatherTwoPerson() && _wInGathering > 0 && FoverNUM != _wRemCount)
    {
        _wRemCount += _wInGathering;
    }
    _mapGaterPlayer.clear();
}

void CGather::SendGatherChangeInfo()
{ 
    CGameMapPtr pMap = GetMap();
    if(pMap != NULL)
        pMap->GatherChange(*this);

}
void CGather::SendCancelGather(CPlayer& rPlayer,EGatherResult eResult)
{
    //  LOG_CRI << "GATHER Cancel";
    rPlayer.SendPkg(g_GatherProtS.BuildPkg_GatherEndNotify(eResult));
    g_GatherProtS.SystemMsgNotify(eResult,rPlayer.GetRoleID());
}
//注册采集
void CGather::SetPlayerGather(CPlayer& rPlayer)
{
    // LOG_INF <<"Player OFF Gather!";
    rPlayer.SetGatherID(GetInstID());
}

//清除采集
void CGather::ClearPlayerGather(CPlayer& rPlayer)
{
    // LOG_INF << "Player IN Gather!";
    rPlayer.SetGatherID(0);
}

UINT32 CGather::GetReserverTimer(CPlayer& rPlayer)
{
    auto it = _mapGaterPlayer.find(rPlayer.GetRoleID());
    if(it != _mapGaterPlayer.end())
    {
        UINT32 dwPassTimer = time(NULL)- it->second;
        if(dwPassTimer > GetGatherConfig()._wGatherTimer)
        {
            return 0;
        }
        return GetGatherConfig()._wGatherTimer - dwPassTimer;
    }
    return 0;
}

void CGather::GetGatherAppear(SGatherAppear& rGatherAppear,UINT64 qwUserId)
{
    rGatherAppear.wGatheringNum = _wInGathering;
    rGatherAppear.wReserverNum = _wRemCount;
    rGatherAppear.wTotalNum = GetGatherConfig()._wGatherNum;
    IGather::GetGatherAppear(rGatherAppear);
}

