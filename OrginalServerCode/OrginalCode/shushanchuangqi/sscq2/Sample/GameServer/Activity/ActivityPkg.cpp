#include  "ActivityPkg.h"
#include  "Protocols.h"
#include  "Player.h"
#include "User.h"
#include "VarDefine.h"
#include "Parameter.h"
#include "GameServerSysMail.h"
#include "SysMsgDefine.h"
#include "Loot.h"
#include "VIPMgr.h"
#include "AutoStoreMgr.h"
using namespace NVarDefine;
CActivityPkg::CActivityPkg(CPlayer &rPlayer):CRegiserterEvent(eActClass_Activity,rPlayer),_wLastLevel(0),_byLastVIp(0)
{
}

void CActivityPkg::Init(const TVecActivityTaskInfo &rvecInfo)
{
    for(auto it = rvecInfo.begin();it != rvecInfo.end();it++)
    {
        const SActivityTaskInfo & rInfo = *it;
        const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(rInfo.wId);
        if(!pCfg)
        {
            Update2DB(rInfo,eOpDel);
            continue;
        }
        UINT16 wEventId = static_cast<UINT16>(rInfo.wId);
        _mapActivityTaskInfo[wEventId] = rInfo;

    }
    if(!CheckActivityTask())
    {
        if(HasIcon())
        {
            RegiserterEvent();
        }
    }
}

void CActivityPkg::Update2DB(const SActivityTaskInfo & rInfo,EDataChange eUpdatwEventId)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rRegisterPlayer.GetUserID(), eTypeActivityTask, eUpdatwEventId, strData);
}

bool CActivityPkg::CheckActivityTask()
{
    if(!HasIcon())
    {
        return false;
    }
    bool bNeedFlush = _rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivityTask) == 0;
    if(!bNeedFlush)
    {
        return false;
    }
    for(auto it = _mapActivityTaskInfo.begin();it != _mapActivityTaskInfo.end();it++)
    {
        const SActivityTaskInfo & rInfo = it->second;
        Update2DB(rInfo,eOpDel);
    }
    _rRegisterPlayer.GetUser().GetTaskPkg().OnAction(_rRegisterPlayer,eProcessAction_TodayActivity);
    ClearEvent();
    _mapActivityTaskInfo.clear();
    //刷特别任务
  #if 0
    vector<UINT16> vecRandom;
    g_CActivityManager.GetRandomActivityPoint(SParamConfig::byActivitySpecialTask,vecRandom);
    for(auto it = vecRandom.begin();it != vecRandom.end();it++)
    {
        const SActivityPointCFGEx * pCfg = g_CActivityManager.GetActivityPoint(*it);
        if(pCfg == NULL)
        {
            continue;
        }
        SActivityTaskInfo sInfo;
        sInfo.wId = *it;
        sInfo.byTimes = 0;
        sInfo.byIsSpecial = 1;
        _mapActivityTaskInfo[*it] = sInfo;
    }
#endif
    for(auto it = _mapActivityTaskInfo.begin();it != _mapActivityTaskInfo.end();it++)
    {
        const SActivityTaskInfo & rInfo = it->second;
        Update2DB(rInfo,eOpAdd);
    }
    _rRegisterPlayer.GetUser().GetVars().SetVar(ePlayerActivityTask,1);
    RegiserterEvent();
    return true;
}

void CActivityPkg::SendAllInfoActivity()
{
    if(!HasIcon())
    {
        return ;
    }
    CheckActivityTask();
    SActivityInfoForClient stActivityInfo;
    //stActivityInfo.dwTotolActivity = _rRegisterPlayer.GetTotalActivity();策划要求，不要奖池
    stActivityInfo.wActivity =  _rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivity);
    for(auto it = _mapActivityTaskInfo.begin();it != _mapActivityTaskInfo.end();it++)
    {
        stActivityInfo.vecActivityTask.push_back(it->second);
    }
    g_CActivityManager.GetActivityAward(stActivityInfo.vecActivityAward,_rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivityAward));  
    _rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_ReturnAllInfoActivity(stActivityInfo));
    //LOG_CRI << "Send Activity";
}

EActivityResult CActivityPkg::GetActivityAward(const SActivityAward& stActivityGet)
{
    //如果领取，不可再领
    UINT64 qwKey = 0;
    if(!g_CActivityManager.MakeAwardKey(stActivityGet,qwKey))
    {
        return eActivityErrOther;
    }
    UINT64 qwAwardGet = _rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivityAward);
    if((qwAwardGet & qwKey) >0)
    {
        return eActivityHasGet;
    }
    //活力不足，不可领取
    const ActivityAward* pAward = g_CActivityManager.GetAward(qwKey);
    if(pAward == NULL)
    {
        return eActivityErrOther;
    }
    if(_rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivity) < pAward->wActivity)
    {
        return eActivityMin;
    }
    /*if(_rRegisterPlayer.GetUser().GetVIPLevel() < pAward->byVIPLevel)
      {
      return eActivityVip;
      }*/

    if(stActivityGet.byVIP > 0 )
    {
        const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rRegisterPlayer.GetUser().GetVIPLevel());
        if(pCfgVip == NULL)
            return eActivityErrOther;

        bool mark = false;
        Tokenizer tk(pCfgVip->_HuoyueAward, "|");
        for (size_t i=0; i<tk.size(); ++i)
        {
            UINT8 byAwardId = atoi(tk[i].c_str());
            if (stActivityGet.byId == byAwardId)
            {
                mark = true;
                break;
            }
        }

        if (!mark)
            return eActivityVip;
    }

    if(!DoLoot(pAward->dwLootId))
    {
        return eActivityPackNoSpace;
    }
    qwAwardGet |= qwKey;
    _rRegisterPlayer.GetUser().GetVars().SetVar(ePlayerActivityAward,qwAwardGet);
    return  eActivitySucceed;
}

EActivityResult CActivityPkg::GetActivityPool(UINT32 &dwTotalActivity)
{
    UINT32 dwTotal = _rRegisterPlayer.GetTotalActivity();
    dwTotalActivity = dwTotal;
    if(dwTotal < SParamConfig::dwActivityPool)
    {
        return eActivityTotalMin;
    }
    UINT32 dwLootId = g_CActivityManager.GetLootIdByVip(_rRegisterPlayer.GetUser().GetVIPLevel());
    if(!DoLoot(dwLootId))
    {
        return eActivityPackNoSpace;
    }
    dwTotalActivity -= SParamConfig::dwActivityPool;
    _rRegisterPlayer.SetTotalActivity(dwTotalActivity);
    return  eActivitySucceed;
}

bool CActivityPkg::DoLoot(UINT32 dwLootId)
{
    std::vector<SItemGenInfo> vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwLootId, vecItems,vecRes);
    CPack& oPack = _rRegisterPlayer.GetUser().GetPack();
    if(!vecItems.empty())
    {
        if(!oPack.CanAddItem(vecItems))
        {
            return false;
        }
        else
        {
            oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_Activity);
        }
    }

    if(!vecRes.empty())
    {
        CStore::AddResource(_rRegisterPlayer.GetUser(),vecRes,NLogDataDefine::ItemFrom_Activity);
    }

    for(auto itr = vecItems.begin(); itr != vecItems.end(); itr++)
    {
        TVecINT32 vecParam;
        vecParam.push_back(itr->wItemID);
        _rRegisterPlayer.OnEvent(eEventType_ActiveValueGetPrize,vecParam);
    }

    return true;
}

void CActivityPkg::OnVipUp()
{
    if(!HasIcon())
    {
        return ;
    }
    RegiserterEvent(2);

}

void CActivityPkg::OnLevelUp()
{
    if(!HasIcon())
    {
        return ;
    }
    RegiserterEvent(1);
}

void CActivityPkg::RegiserterEvent(UINT8 bySource)
{
    switch (bySource)
    {
        case 0:
            {
                TVecUINT16 vecAllEvent;
                g_CActivityManager.GetAllActivityPoint(vecAllEvent);
                for(auto it = vecAllEvent.begin(); it != vecAllEvent.end();it++)
                {
                    //LOG_CRI<<"RegiserterEvent :"<<*it;
                    //等级不足，不计
                    const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(*it);
                    if(pCfg == NULL)
                    {
                        continue ;
                    }
                    if(_rRegisterPlayer.GetLevel() < pCfg->wMinLevel)
                    {
                        //LOG_CRI<<"low Level:"<<pCfg->wMinLevel;
                        continue;
                    }
                    auto iter = _mapActivityTaskInfo.find(*it);
                    if(iter != _mapActivityTaskInfo.end())
                    {
                        if(iter->second.byTimes >= pCfg->GetMaxTimesByVip(_rRegisterPlayer.GetUser().GetVIPLevel()))
                        {
                            //LOG_CRI<<"byTimes: "<<iter->second.byTimes<<"MaxTimesByVip:"<<pCfg->GetMaxTimesByVip(_rRegisterPlayer.GetUser().GetVIPLevel());
                            continue ;
                        }
                    }

                    AddEvent(*it,*it,ThisDayZero());
                }

            }

            break;
        case 1:
            {
                TVecUINT16 vecAllEvent;
                g_CActivityManager.GetAllActivityPoint(vecAllEvent);
                for(auto it = vecAllEvent.begin(); it != vecAllEvent.end();it++)
                {
                    //等级不足，不计
                    const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(*it);
                    if(pCfg == NULL)
                    {
                        continue ;
                    }
                    bool bNeedAdd = pCfg->wMinLevel > _wLastLevel && pCfg->wMinLevel <= _rRegisterPlayer.GetLevel();
                    if(!bNeedAdd)
                    {
                        continue;
                    }
                    AddEvent(*it,*it,ThisDayZero());

                }
            }

            break;
        case 2:
            {
                TVecUINT16 vecAllEvent;
                g_CActivityManager.GetAllActivityPoint(vecAllEvent);
                for(auto it = vecAllEvent.begin(); it != vecAllEvent.end();it++)
                {
                    //等级不足，不计
                    const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(*it);
                    if(pCfg == NULL)
                    {
                        continue ;
                    }
                    UINT8 byNowVip = _rRegisterPlayer.GetUser().GetVIPLevel();
                    auto iter = _mapActivityTaskInfo.find(*it);
                    if(iter != _mapActivityTaskInfo.end())
                    {
                        bool bNeedAdd =  pCfg->GetMaxTimesByVip(_byLastVIp) < pCfg->GetMaxTimesByVip(byNowVip) && iter->second.byTimes < pCfg->GetMaxTimesByVip(byNowVip);
                        if(!bNeedAdd)
                        {
                            continue;
                        }

                    }
                    else
                    {
                        continue;
                    }
                    AddEvent(*it,*it,ThisDayZero());
                }

            }
            break;
    }

    _wLastLevel = _rRegisterPlayer.GetLevel();
    _byLastVIp = _rRegisterPlayer.GetUser().GetVIPLevel();
}

/*
   void CActivityPkg::CheckActivityPoint(UINT16 wEventId)
   {
//等级不足，不计
const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(wEventId);
if(pCfg == NULL)
{
return ;
}
if(_rRegisterPlayer.GetLevel() < pCfg->wMinLevel)
{
return ;
}

//超过今日次数，不计
bool bAdd = true;
bool bIsSpecial = false;
auto it = _mapActivityTaskInfo.find(wEventId);
if(it != _mapActivityTaskInfo.end())
{
if(it->second.byTimes >= pCfg->byMaxTimes)
{
return ;
}
bAdd = false;
if(it->second.byIsSpecial > 0)
{
bIsSpecial = true;
}
}
//加近日次数
if(bAdd)
{
_mapActivityTaskInfo[wEventId].byTimes = 1;
_mapActivityTaskInfo[wEventId].wId = wEventId;
}
else
{
_mapActivityTaskInfo[wEventId].byTimes++;
}
//加活跃度
const SActivityTaskInfo &rInfo = _mapActivityTaskInfo[wEventId];
UINT16 wActivity = pCfg->wActivity;
if(bIsSpecial)
{
wActivity *= SParamConfig::byActivitySpecialAward;
}
_rRegisterPlayer.GetUser().GetVars().AddVar(ePlayerActivity,wActivity);
Update2DB(rInfo,bAdd ? eOpAdd : eOpUpdate);
//活跃总值
UINT32 dwTotal = _rRegisterPlayer.GetTotalActivity();
dwTotal += wActivity; 
_rRegisterPlayer.SetTotalActivity(dwTotal);
//通知客户端
_rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_UpdateActivityTask(rInfo,dwTotal,_rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivity)));
}
*/
void CActivityPkg::OnEvent(SEventInfoPtr pEventInfo)
{
    if(!pEventInfo)
    {
        LOG_CRI << "empty point";
        return ;
    }
    UINT32 wEventId  =  pEventInfo->dwEventInstID ;
    const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(wEventId);
    if(pCfg == NULL)
    {
        RemoveEvent(wEventId,wEventId);
        auto it = _mapActivityTaskInfo.find(wEventId);
        if(it != _mapActivityTaskInfo.end())
        {
            Update2DB(it->second,eOpDel);
        }
        return ;
    }
    //如果是进度
    /*
    if (pEventInfo->wEventStatus != eEventStatus_Finish)
    {
        UINT32 dwParam1 = pEventInfo->dwParam1; //统计参数1
        INT32 dwParam2 = pEventInfo->dwParam2; //统计参数2
        //TODO:
        //发给客户端
        return ;

    }
    */
    //如果已完成
    bool bAdd = true;
    bool bIsSpecial = false;
    auto it = _mapActivityTaskInfo.find(wEventId);
    if(it != _mapActivityTaskInfo.end())
    {
        bAdd = false;
        if(it->second.byIsSpecial > 0)
        {
            bIsSpecial = true;
        }
    }
    //加近日次数
    if(bAdd)
    {
        _mapActivityTaskInfo[wEventId].byTimes = 1;
        _mapActivityTaskInfo[wEventId].wId = wEventId;
    }
    else
    {
        _mapActivityTaskInfo[wEventId].byTimes++;
    }
    //加活跃度
    const SActivityTaskInfo &rInfo = _mapActivityTaskInfo[wEventId];
    RemoveEvent(wEventId,wEventId);  
    if(rInfo.byTimes < pCfg->GetMaxTimesByVip(_rRegisterPlayer.GetUser().GetVIPLevel()))
    {
        AddEvent(wEventId,wEventId,ThisDayZero());
    }
    UINT16 wActivity = pCfg->wActivity;
    if(bIsSpecial)
    {
        wActivity *= SParamConfig::byActivitySpecialAward;
    }
    Update2DB(rInfo,bAdd ? eOpAdd : eOpUpdate);
    AddActivity(wActivity);
    //通知客户端
    _rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_UpdateActivityTask(rInfo,_rRegisterPlayer.GetTotalActivity(),_rRegisterPlayer.GetUser().GetVars().GetVar(ePlayerActivity)));

    //event
    {
        TVecINT32 vecParam;
        vecParam.push_back(wActivity);
        _rRegisterPlayer.OnEvent(eEventType_ActivePointGet,vecParam);
    }

    if( 0 != pCfg->_Share)
    {
        if(eShareStatus_Init == GetShareStatus(wEventId))
        {
            SetShareStatus(wEventId,eShareStatus_Finish);


            SActivityShare oShareNotify;
            oShareNotify.dwActivityID = wEventId;
            oShareNotify.eStatus = eShareStatus_Finish;
            //notify
            _rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_ShareNotify(oShareNotify));
        }
    }

}

void CActivityPkg::AddActivity(UINT16 wActivity)
{
    _rRegisterPlayer.GetUser().GetVars().AddVar(ePlayerActivity,wActivity);
#if 0 
    UINT32 dwTotal = _rRegisterPlayer.GetTotalActivity();
    dwTotal += wActivity;
    _rRegisterPlayer.SetTotalActivity(dwTotal);
#endif
    _rRegisterPlayer.GetUser().GetTaskPkg().OnAction(_rRegisterPlayer,eProcessAction_TodayActivity);
}

UINT32 CActivityPkg::ThisDayZero()
{
    time_t now = Time::Now();
    return Time::TheDay(0,now);
}

void CActivityPkg::AddActivityPool(UINT16 wActivity)
{
    return ;
    if(!HasIcon())
        return ;
    UINT32 dwTotal = _rRegisterPlayer.GetTotalActivity();
    dwTotal += wActivity;
    _rRegisterPlayer.SetTotalActivity(dwTotal);
    //通知客户端，活力池增加
    _rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_UpdateActivityTotal(_rRegisterPlayer.GetTotalActivity()));


}

bool CActivityPkg::HasIcon()
{
    return true;
    return _rRegisterPlayer.CheckIconIsOpen(ActivityIcon);
}

void CActivityPkg::OpenIcon()
{
    if(!HasIcon())
        return ;
    RegiserterEvent();

}

//分享好友状态
void CActivityPkg::SetShareStatus(UINT32 dwActivityID,EShareStatus eStatus)
{
    if(_rRegisterPlayer.GetAutoStoreMgr())
    {
        _rRegisterPlayer.GetAutoStoreMgr()->SetValue(eAutoStore_Activity_ShareFriend,dwActivityID,eStatus);
    }

}

EShareStatus CActivityPkg::GetShareStatus(UINT32 dwActivityID)
{
    if(_rRegisterPlayer.GetAutoStoreMgr())
    {
        return (EShareStatus)_rRegisterPlayer.GetAutoStoreMgr()->GetValue(eAutoStore_Activity_ShareFriend,dwActivityID);
    }

    return eShareStatus_Init;

}

//获取分享列表
void CActivityPkg::OnGeShareList(TVecActivityShare& vecActivityShare)
{
    if(NULL == _rRegisterPlayer.GetAutoStoreMgr())
    {
        return;
    }

    TVecAutoStoreDBInfo vecAutoStoreDBInfo;
    _rRegisterPlayer.GetAutoStoreMgr()->GetListByType(eAutoStore_Activity_ShareFriend,vecAutoStoreDBInfo);

    for(size_t i = 0; i < vecAutoStoreDBInfo.size(); i++)
    {
        SActivityShare oActivityShare;
        oActivityShare.dwActivityID = vecAutoStoreDBInfo[i].dwClassID;
        oActivityShare.eStatus = (EShareStatus)vecAutoStoreDBInfo[i].dwValue;
        vecActivityShare.push_back(oActivityShare);
    }
}

EActivityResult CActivityPkg::OnTakeSharePrize(UINT32 dwActivityID)
{
    EShareStatus eStatus = GetShareStatus(dwActivityID);
    if(eStatus == eShareStatus_Init)
    {
        LOG_INF<<"not finish dwActivityID:"<<dwActivityID;
        return eActivityNotFinish;
    }

    if(eStatus == eShareStatus_TakePrize)
    {
        LOG_INF<<"Has take prize dwActivityID:"<<dwActivityID;
        return eActivityHasGet;
    }

    if(eStatus != eShareStatus_Finish)
    {
        LOG_CRI<<"Unkown Error eStatus:"<<eStatus;
        return eActivityErrOther;
    }


    const SActivityPointCFGEx * pCfg =   g_CActivityManager.GetActivityPoint(dwActivityID);
    if(NULL == pCfg)
    {
        return eActivityErrOther;
    }

    //if(0 == pCfg->_Share)
    //{
    //    return;
    //}
    CUser& rUser = _rRegisterPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if (!rPack.CanAddItem(pCfg->_vecSharePrize))
    {
        rUser.SendSysMsg(eMsgPackFullErr);
        return eActivityPackNoSpace;
    }
    
    if (!rPack.AddItem(pCfg->_vecSharePrize, NLogDataDefine::ItemFrom_Activity))
    {
        _rRegisterPlayer.SendSysMsg(eMsgPackFullErr);
        return eActivityPackNoSpace;
    }

    SetShareStatus(dwActivityID,eShareStatus_TakePrize);

    SActivityShare oShareNotify;
    oShareNotify.dwActivityID = dwActivityID;
    oShareNotify.eStatus = eShareStatus_TakePrize;
 
    _rRegisterPlayer.SendPkg(g_ActivityProtS.BuildPkg_ShareNotify(oShareNotify));
    
    return eActivitySucceed;
}


