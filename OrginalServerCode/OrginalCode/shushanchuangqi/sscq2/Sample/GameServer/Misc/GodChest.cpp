#include "stdafx.h"
#include "Protocols.h"
#include "GodChest.h"
#include "UserMgr.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "MapMgr.h"
#include "Random.h"

CGodChest g_GodChest;

CGodChest::CGodChest() : 
    CDayActivity(eActTypeChest)
{
    _wMapID = 2;
    _byBig = 15;
    _byMid = 85;
    _bySmall = 20;
    _byInterval = 60;
    _byLonger = 0;
    _byRount = 15;
    _byRemain = 15;
    _byCountDown = 5;
    _byNotice = 2;
}

void CGodChest::OnEnter(CPlayer &rPlayer)
{
    CGameMapPtr pMap = CMapMgr::GetMap(_wMapID);
    if(!pMap)
    {
        LOG_INF<<"pMap null.";
        return ;
    }
    
    SPoint rDestPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
    rPlayer.JumpMap(pMap,rDestPoint);
    GetRount(rPlayer);
}

void CGodChest::GetRount(CPlayer &rPlayer)
{
    SGodChestInfo sInfo;
    sInfo.byState = 0;
    if(IsRun())
    {
        sInfo.byState = 1;
    }
    sInfo.byRount = _byRemain;
    sInfo.dwEnd = _dwEndTime;
    rPlayer.SendPkg(g_MiscProtS.BuildPkg_SyncChestInfo(sInfo));
}

bool CGodChest::RandChest(SMapInfoPtr pMapInfo,TVecChestInfo& vecInfo)
{
    bool bExsit;
    UINT16 wIndex,wCnt,byBig,byMid,bySmall;
    wIndex = wCnt = byBig = byMid = bySmall = 1;
    UINT16 wMaxPoint = pMapInfo->vecChestPoint.size();
    UINT16 wMaxChest = _byBig + _bySmall + _byMid;
    while(wCnt <= wMaxChest)
    {
       bExsit = false;
       wIndex = CRandom::RandInt(1,wMaxPoint);
       for(auto& it : vecInfo)
       {
           if(it.wIndex == wIndex)
           {
               bExsit = true;
               break;
           }
       }
       if(!bExsit)
       {
           SChestInfo oInfo;
           oInfo.wIndex = wIndex;
           if(byBig <= _byBig)
           {
              oInfo.eType = eChestType_Big;
              byBig ++;
              goto Add;
           }
           if(byMid <= _byMid)
           {
               oInfo.eType = eChestType_Mid;
               byMid ++;
               goto Add;
           }
           if(bySmall <= _bySmall)
           {
               oInfo.eType = eChestType_Small;
               bySmall ++;
           }
Add:
           if(!GetPoint(pMapInfo,wIndex,oInfo.fX,oInfo.fY))
           {
               LOG_INF<<" GetPoint Err.";
               return false;
           }
           vecInfo.push_back(oInfo);
           wCnt ++;
       }
    }
    return true;
}

bool CGodChest::GetPoint(SMapInfoPtr pMapInfo,UINT32 dwID,float& rX,float &rY)
{
    if(!pMapInfo) 
    {
        LOG_INF<<"pMapInfo Err.";
        return false;
    }
    for(auto it : pMapInfo->vecChestPoint)
    {
        if(it.dwID == dwID)
        {
            rX = it.fX;
            rY = it.fY;
            break;
        }
    }
    return true;
}

void CGodChest::OnBegin()
{
    LOG_WRN << "CGodChest::OnBegin()";
    CDayActivity::OnBegin();
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgTreasureOpenAlready);
    
    OnSync(_byInterval - _byNotice - _byCountDown); 
}

bool CGodChest::OnAlarm()
{
    LOG_WRN << "CGodChest::OnAlarm()";

    CDayActivity::OnAlarm();
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgTreasureOpenReady);
    return true;
}

void CGodChest::OnReady()
{
    LOG_WRN << "CGodChest::OnReady()";
    _wMapID = SParamConfig::wTreasureMap;
    if(_wMapID == 0)
    {
        LOG_WRN<<"MapID 0";
        return;
    }
    CDayActivity::OnReady();
    //初始化参数
    InitParam();
    //初始化宝箱事件
    InitEvent();
}

void CGodChest::InitParam()
{
    _byBig = SParamConfig::wTreasureBigNum;
    _byMid = SParamConfig::wTreasureMidNum;
    _bySmall = SParamConfig::wTreasureSmallNum;
}

void CGodChest::OnEnd()
{
    LOG_WRN << "CGodChest::OnEnd()";
    CDayActivity::OnEnd();
    ClearChest();
    ClearEvent();
    g_MiscProtS.SendClt_OnEnd(NULL,0);
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgTreasureAlreadyEnd);

    //重新初始化成  初始数据。运营有可能添加活动，修改数据
    {
        _wMapID = 2;
        _byBig = 15;
        _byMid = 85;
        _bySmall = 20;
        _byInterval = 60;
        _byLonger = 0;
        _byRount = 15;
        _byRemain = 15;
        _byCountDown = 5;
    } 
}

bool CGodChest::GMOpen()
{
    LOG_INF<<"CGodChest::GMOpen";
    if(GetStatus()==eDayActivityStatusReady || GetStatus() == eDayActivityStatusProcess)
    {
        return false;
    }

    ClearEvent();

    //测试用
    UINT32 dwNow = (UINT32)(time(NULL));
    _dwAlarmTime = dwNow + 10;
    _dwReadyTime = dwNow + 15;
    _dwBeginTime = dwNow + 30;
    _dwEndTime = dwNow + 10 * 60;
    SetStatus(eDayActivityStatusAlarm);
    //InitParam();
    //InitEvent();
    return true;
}

void CGodChest::OnEvent(SActEventData& oSActEventData)
{
    switch(oSActEventData.dwEventID)
    {
        case eEventType_PreNotice:
        case eEventType_Notice:
            SendNotice();
            break;
        case eEventType_PreCountDown:
        case eEventType_CountDown:
            SendCountDown();
            break;
        case eEventType_Reflush:
            Reflush();
            break;
        case eEventType_ClearChest:
            ClearChest();
            break;
        default:
            break;
    }
}

void CGodChest::SendNotice()
{
    g_MiscProtS.SendClt_SendNotice(NULL,0,_byRemain,_byRount);
}

void CGodChest::Reflush()
{
    SMapInfoPtr pMapInfo = CMapMgr::GetMapInfo(_wMapID);
    if(!pMapInfo)
    {
        LOG_INF<<"pmapInfo err.";
        return;
    }
    vector<CGameMapPtr> vecMapInst;
    CMapMgr::GetAllMapInstByMapID(_wMapID,vecMapInst);
    if(vecMapInst.size() == 0)
    {
        LOG_INF<<"vecMapInst.size == 0";
        return;
    }
    for(auto &oIt : vecMapInst)
    {
        CGameMapPtr pMap = oIt;
        TVecChestInfo vecChest;
        if(!RandChest(pMapInfo,vecChest))
        {
            LOG_INF<<"RandChest Err.";
            continue;
        }
        UINT8 byIndex = 0;
        for(auto& it : vecChest)
        {
           SPoint oPoint(it.fX,it.fY);
           pMap->AddGather(it.eType,&oPoint); 
           ++byIndex;
        }
    }
    _byRemain -= 1;
    OnSync(_byInterval - _byNotice - _byCountDown); 
}

void CGodChest::OnSync(UINT32 dwTime)
{
    SGodChestInfo sInfo;
    sInfo.byState = 0;
    if(IsRun())
        sInfo.byState = 1;
    sInfo.byRount = _byRemain;
    sInfo.dwEnd = _dwEndTime;
    sInfo.dwTime = dwTime;
    g_MiscProtS.SendClt_SyncChestInfo(NULL,0,sInfo);
}

void CGodChest::SendCountDown()
{
    g_MiscProtS.SendClt_OnCountDown(NULL,0,_byCountDown);
}

void CGodChest::ClearChest()
{
    vector<CGameMapPtr> vecMapInst;
    CMapMgr::GetAllMapInstByMapID(_wMapID,vecMapInst);
    if(vecMapInst.size() == 0)
    {
        LOG_INF<<"vecMapInst.size == 0 ,clearChest Err";
        return;
    }
    for(auto &oIt : vecMapInst)
    {
        CGameMapPtr pMap = oIt;
        pMap->ClearAllGathers();
    }
}

void CGodChest::UpdateState(time_t tNow)
{
    CDayActivity::UpdateState(tNow);
}

void CGodChest::ResetState()
{
}

void CGodChest::OnReBegin()
{ 
    LOG_WRN <<" GodChest Server ReBegin!";
    OnEnd();
}

bool CGodChest::InitEvent()
{
    UINT16 dwRount = 0;
    UINT32 dwNow = (UINT32)(time(NULL));
    UINT16 wFlag = 0;
    if(dwNow > _dwEndTime || _dwBeginTime > _dwEndTime)
        return false;
    wFlag = (_dwEndTime - _dwBeginTime) % _byInterval;
    if(wFlag)
        dwRount = ((_dwEndTime - _dwBeginTime)/_byInterval) + 1;
    else  
        dwRount = ((_dwEndTime - _dwBeginTime)/_byInterval);
    _byRount = (UINT8)dwRount;
    _byRemain = _byRount;
    UINT32 dwTmp = _dwBeginTime;
    AddEvent(eEventType_PreNotice, dwTmp - _byCountDown - _byNotice, _byInterval);
    AddEvent(eEventType_PreCountDown, dwTmp - _byCountDown, _byInterval);
    AddPeriodEvent(eEventType_Reflush,dwTmp,dwRount,_byInterval);
    AddPeriodEvent(eEventType_Notice,dwTmp + _byInterval - _byCountDown - _byNotice,dwRount - 1 ,_byInterval);
    AddPeriodEvent(eEventType_ClearChest,dwTmp + _byInterval - _byCountDown - _byNotice,dwRount - 1,_byInterval);
    AddPeriodEvent(eEventType_CountDown,dwTmp + _byInterval - _byCountDown,dwRount - 1 ,_byInterval);
    LOG_CRI <<" Rount = "<<_byRount; 
    return true;
}

bool CGodChest::IsRun()
{
    return _eState == eDayActivityStatusProcess;
}

bool CGodChest::SetInterval(UINT8 byTmp)
{
   if(IsRun())
   {
        LOG_CRI<<"ChestBox is running.";
        return false;
   }
   _byInterval = byTmp; 
   return true;
}

void CGodChest::SetTime(const NProtoCommon::SActivityTime& sActTime)
{
    if(IsRun())
    {
        LOG_INF <<"dwActID = "<<_dwActID<<",is runing.";
        return;
    }
    _dwAlarmTime = sActTime.dwAlarm;
    _dwReadyTime = sActTime.dwReady;
    _dwBeginTime = sActTime.dwBegin;
    _dwEndTime = sActTime.dwEnd;
}

bool CGodChest::SetLonger(UINT8 byTmp)
{
    if(IsRun())
    {
        LOG_CRI<<"ChestBox is running.";
        return false;
    }
    _dwEndTime += byTmp * 60;
    return true;
}

bool CGodChest::SetBig(UINT8 byTmp)
{
    if(IsRun())
    {
        LOG_CRI<<"ChestBox is running.";
        return false;
    }
    _byBig = byTmp;
    return true;
}

bool CGodChest::SetMid(UINT8 byTmp)
{
    if(IsRun())
    {
        LOG_CRI<<"ChestBox is running.";
        return false;
    }
    _byMid = byTmp;
    return true;
}

bool CGodChest::SetSmall(UINT8 byTmp)
{
    if(IsRun())
    {
        LOG_CRI<<"ChestBox is running.";
        return false;
    }
    _bySmall = byTmp;
    return true;
}

bool CGodChest::SetMap(UINT16 wMapID)
{
    if(IsRun())
    {
        LOG_CRI<<"ChestBox is running.";
        return false;
    }
    _wMapID = wMapID;
    return true;
}

void CGodChest::ModifyParam(const NPHPProt::SChestInfo& sInfo)
{
    if(IsRun())
    {
        LOG_INF <<"ChestBox is running.";
        return;
    }
    time_t tNow = time(NULL);
    if(tNow < sInfo.dwTime)
    {
        LOG_INF<<" TimeSet Err.(tNow > sInfo.Time)";
        return;
    }

    if(!sInfo.byPeroid)
    {
        LOG_INF<<"PeroidTime is 0.";
        return;
    }

    if(!sInfo.wMapID)
    {
        CGameMapPtr pMap = CMapMgr::GetMap(sInfo.wMapID);
        if(!pMap)
        {
            LOG_INF<<"NotFind MapID = " <<sInfo.wMapID;
            return;
        }

        SetMap(sInfo.wMapID);
        LOG_INF<<"SetMapID:"<<sInfo.wMapID;
    }
    if(!sInfo.byBig)
    {
        SetBig(sInfo.byBig);
        LOG_INF<<"SetBigBox:"<<sInfo.byBig;
    }
    if(!sInfo.byMid)
    {
        SetMid(sInfo.byMid);
        LOG_INF<<"SetMidBox:"<<sInfo.byMid;
    }
    if(!sInfo.bySmall)
    {
        SetSmall(sInfo.bySmall);
        LOG_INF<<"SetSmallBox:"<<sInfo.bySmall;
    }

    UINT32 dwTime = sInfo.dwTime; 
    UINT32 dwEnd  = dwTime + sInfo.byPeroid * 60;
    _dwAlarmTime = dwTime + 1;
    _dwReadyTime = dwTime + 2;
    _dwBeginTime = dwTime + 3;
    _dwEndTime = dwEnd;
    SetStatus(eDayActivityStatusAlarm);
    //InitParam();
    //InitEvent();
}

void CGodChest::CheckChest(CPlayer &rPlayer)
{
    if(!IsRun())
        return;
    if(rPlayer.GetCurMapID() != _wMapID)
        return;
    
    SGodChestInfo sInfo;
    sInfo.byState = 1;
    sInfo.byRount = _byRemain;
    sInfo.dwEnd = _dwEndTime;
    sInfo.dwTime = 0;
    rPlayer.SendPkg(g_MiscProtS.BuildPkg_SyncChestInfo(sInfo));
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

