#include "stdafx.h"
#include "DayTargetMgr.h"
#include "Tokenizer.h"
#include "Player.h"
#include "ItemMgr.h"
#include "DayTargetS.h"
#include "LogDataDefine.h"
#include "SysMsgDefine.h"

TMapDayTargetCFGExPtr CDayTargetMgr::_mapDayTargetCFGExPtr;

CDayTargetMgr::CDayTargetMgr(CPlayer& rPlayer):CRegiserterEvent(eActClass_SevenDayTarget,rPlayer),
    _rPlayer(rPlayer)
{

    _bLog = true;
    _bGetData = false;
}

bool CDayTargetMgr::DayTargetInit()
{


    string strPath = Config._strConfigDir + "Conf/Table/SevenDaysTarget.xml";
    CSevenDaysTargetLoader oSevenDaysTargetLoader;
    if(!oSevenDaysTargetLoader.LoadData(strPath))
    {
        return false;
    }

    _mapDayTargetCFGExPtr.clear();

    for(size_t i = 0; i < oSevenDaysTargetLoader._vecData.size(); ++i)
    {
        SSevenDaysTargetCFG* pCFG = oSevenDaysTargetLoader._vecData[i];
        if(pCFG)
        {
            SDayTargetCFGExPtr  pDayTarget(new SDayTargetCFGEx);
            pDayTarget->CopyFrom(*pCFG);
            
            Tokenizer tk(pCFG->_EventID, ";"); 
            for (size_t i = 0; i < tk.size(); ++i)
            {
               UINT32 dwValue = atoi(tk[i].c_str());
               pDayTarget->_vecEventInstID.push_back(dwValue);
            }

            {

                Tokenizer tkAward(pCFG->_Award, "|");
                for(size_t i = 0; i < tkAward.size(); ++i)
                {
                    Tokenizer tkItem(tkAward[i], ",");
                    if(tkItem.size() != 2)
                    {
                        break;
                    }

                    UINT16 wItemID = atoi(tkItem[0].c_str());
                    UINT32 dwItemCount = atoi(tkItem[1].c_str());
                    pDayTarget->_vecPrizeItem.emplace_back(wItemID,dwItemCount,0,eBindGet,0);

                }
            }

            if(pDayTarget->_vecPrizeItem.empty())
            {
                LOG_CRI<<"DayTarget Prize empty()!!!";
                return false;
            }

               

            _mapDayTargetCFGExPtr.insert(make_pair(pDayTarget->_ID,pDayTarget));


        }
    }

    return true;
}

bool CDayTargetMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("SevenDaysTarget.xml" == strFile)
    {
          return  DayTargetInit();
    }
    return true;

}


bool CDayTargetMgr::IsFinished(UINT16 wTaskID)
{
    auto itr = _mapDayTargetDBInfo.find(wTaskID);
    if(itr != _mapDayTargetDBInfo.end())
    {
        //是否完成
        return (itr->second.byStatus != eDayTargetTaskStatus_Init );
    }

    return false;

}


UINT32 CDayTargetMgr::GetProcess(UINT16 wTaskID)
{

    auto itr = _mapDayTargetDBInfo.find(wTaskID);
    if(itr != _mapDayTargetDBInfo.end())
    {
        return itr->second.dwProcess;
    }
    return 0;
}

void CDayTargetMgr::SetProcess(UINT16 wTaskID,UINT32 dwTotal,bool bInit)
{
    UINT32 byStatus = 0;
    auto itr = _mapDayTargetDBInfo.find(wTaskID);

    if(itr != _mapDayTargetDBInfo.end())
    {
        if(itr->second.dwProcess != dwTotal)
        {
            itr->second.dwProcess = dwTotal;
            byStatus = itr->second.byStatus;
            if(!bInit)
            {
                UpdateToDB(itr->second);
                NotifiyUpdate(itr->second);
            }
        }
    }
    else
    {
        SDayTargetDBInfo oInfo;
        oInfo.dwProcess = dwTotal;
        oInfo.qwRoleID  = _rPlayer.GetRoleID();
        oInfo.wTaskID = wTaskID;
        _mapDayTargetDBInfo.insert(make_pair(wTaskID,oInfo));
        if(!bInit)
        {
            UpdateToDB(oInfo);
            NotifiyUpdate(oInfo);
        }
    }

    if(_bLog)
    {
        LOG_INF<<"SetProcess wTaskID: "<<wTaskID<<" dwTotal: "<<dwTotal<<"|"<<byStatus;
    }

}

void CDayTargetMgr::OnFinish(UINT16 wTaskID)
{
    if(_bLog)
    {
        LOG_INF<<"CDayTargetMgr OnFinish wTaskID:"<<wTaskID;
    }
    
     SDayTargetDBInfo& rInfo = _mapDayTargetDBInfo[wTaskID];
     rInfo.byStatus = eDayTargetTaskStatus_Finish;
     UpdateToDB(rInfo);
     NotifiyUpdate(rInfo);

}

void CDayTargetMgr::LoadFromDB(const TVecDayTargetDBInfo& vecDayTargetInfo)
{
    if(_bLog)
    {
        LOG_INF<<"CDayTargetMgr::LoadFromDB "<<vecDayTargetInfo.size();
    }

    for(auto itr = vecDayTargetInfo.begin(); itr != vecDayTargetInfo.end(); ++itr)
    {
        _mapDayTargetDBInfo.insert(make_pair(itr->wTaskID,*itr));
        if(_bLog)
        {
            //LOG_INF<<"wDayTargetID: "<<itr->wDayTargetID<<"byStatus: "<<itr->byStatus <<"dwProcess: "<<itr->dwProcess;
        }
    }

    RegisterEventInit();

    //TVecUINT32 vecAchieveID;

    //查询完成状态
    for(auto itr =  CDayTargetMgr::_mapDayTargetCFGExPtr.begin(); itr != CDayTargetMgr::_mapDayTargetCFGExPtr.end(); itr++)
    {
        UINT32 wTaskID = itr->second->_ID;
        if(IsFinished(wTaskID))
        {
            //vecAchieveID.push_back(wTaskID);
            continue;
        }


        if(itr->second->_vecEventInstID.size() == 1)
        {
            UINT32 dwEventInstID = itr->second->_vecEventInstID[0];
            SEventInfoPtr pEventInfo = GetEventInfo(dwEventInstID,wTaskID);
            if(pEventInfo)
            {
                SetProcess(wTaskID,pEventInfo->dwParam1,true);
            }

            AddEvent(dwEventInstID,wTaskID);
            continue;
        }

        UINT32 dwProcess = GetProcess(wTaskID);

        for(size_t i=0; i < itr->second->_vecEventInstID.size(); i++)
        {
            if(dwProcess & (1<<i))
            {
                continue;
            }
            AddEvent(itr->second->_vecEventInstID[i],wTaskID);
        }


    }


/*
    CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
    if(pEventMgr)
    {
        TVecINT32 vecParam;
        //pEventMgr->OnEvent(eEventType_DayTargetLevelUp,vecParam,"",false);
    }

*/
}

void CDayTargetMgr::UpdateToDB(SDayTargetDBInfo& rInfo,EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeDayTarget, eDataChange, strData);

}

void CDayTargetMgr::GetTaskList(TVecDayTargetTask& vecDayTargetTask)
{
    if(_bLog)
    {
        LOG_INF<<"CDayTargetMgr::GetTaskList";
    }
    for(auto itr = _mapDayTargetDBInfo.begin(); itr != _mapDayTargetDBInfo.end(); ++itr)
    {
        vecDayTargetTask.emplace_back(itr->second.wTaskID,(EDayTargeTasktStatus)itr->second.byStatus,itr->second.dwProcess);
        if(_bLog)
            LOG_INF<<"wTaskID:"<<itr->second.wTaskID;
    }

    _bGetData = true;
}

void CDayTargetMgr::NotifiyUpdate(SDayTargetDBInfo& oInfo)
{
    if(!_bGetData) return;

    LOG_INF<<"NotifiyUpdate wTaskID:"<<oInfo.wTaskID<<"byStatus:" <<oInfo.byStatus;

    SDayTargetTask oDayTargetTask(oInfo.wTaskID,(EDayTargeTasktStatus)oInfo.byStatus,oInfo.dwProcess);

    _rPlayer.SendPkg(g_DayTargetS.BuildPkg_UpdateTaskList(oDayTargetTask));

}

SDayTargetCFGExPtr CDayTargetMgr::GetDayTargetCFGByID(UINT32 wTaskID)
{
    auto itr = CDayTargetMgr::_mapDayTargetCFGExPtr.find(wTaskID);
    if(itr != CDayTargetMgr::_mapDayTargetCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

void CDayTargetMgr::OnEvent(SEventInfoPtr pEventInfo)
{
    LOG_INF<<"CDayTargetMgr::OnEvent wTaskID:"<<pEventInfo->dwApplyID;
    if(NULL == pEventInfo)
    {
        return;
    }

    SDayTargetCFGExPtr pDayTargetCFGEx = GetDayTargetCFGByID(pEventInfo->dwApplyID); 
    if(NULL == pDayTargetCFGEx)
    {
        return;
    }

    UINT16 wTaskID = pEventInfo->dwApplyID;

    if(IsFinished(wTaskID))
    {
        return;
    }

    if(pDayTargetCFGEx->_vecEventInstID.size() == 1)
    {
        if(pEventInfo->wEventStatus == eEventStatus_Finish)
        {
            SetProcess(wTaskID,pEventInfo->dwParam1,true);
            OnFinish(wTaskID);
            RemoveEvent(pEventInfo->dwEventInstID,wTaskID);
        }
        else
        {
            SetProcess(wTaskID,pEventInfo->dwParam1);
        }
        return;
    }

    //多事件未完成不处理
    if(pEventInfo->wEventStatus != eEventStatus_Finish)
    {
        return;
    }
    
    RemoveEvent(pEventInfo->dwEventInstID,wTaskID);

    UINT32 dwProcess = GetProcess(wTaskID);

     bool bFinish=true;
     for(size_t i = 0; i < pDayTargetCFGEx->_vecEventInstID.size(); i++)
     {
            UINT32 dwEventInstID = pDayTargetCFGEx->_vecEventInstID[i];
            if(dwEventInstID == pEventInfo->dwEventInstID)
            {
                dwProcess += (1<<i);
                continue;
            }

            if( !(dwProcess& (1<<i)) )
            {
                bFinish = false;
            }
     }

     SetProcess(wTaskID,dwProcess);

     if(bFinish)
     {
         OnFinish(wTaskID);

     }
}

//领取奖励
EDayTargetRet CDayTargetMgr::TakePrize(UINT16 wTaskID)
{
    auto itr = _mapDayTargetDBInfo.find(wTaskID);
    if(itr == _mapDayTargetDBInfo.end())
    {
        LOG_INF<<"itr == _mapDayTargetDBInfo.end()";
        _rPlayer.SendSysMsg(eMsgSevenDayNotFinish);
        return eDayTargetRet_NotFinish;
    }

    SDayTargetDBInfo& rInfo = itr->second;

    if(rInfo.byStatus == eDayTargetTaskStatus_Init)
    {
        LOG_INF<<"eDayTargetTaskStatus_Init";
        _rPlayer.SendSysMsg(eMsgSevenDayNotFinish);
        return eDayTargetRet_NotFinish;
    }

    if(rInfo.byStatus == eDayTargetTaskStatus_TakePrized)
    {
        LOG_INF<<"eDayTargetTaskStatus_TakePrized";
        _rPlayer.SendSysMsg(eMsgSevenDayTakePrized);
        return eDayTargetRet_TakePrized;
    }

    SDayTargetCFGExPtr pDayTargetCFGEx = GetDayTargetCFGByID(wTaskID);
    if(NULL == pDayTargetCFGEx)
    {
        LOG_INF<<"NULL == pDayTargetCFGEx wTaskID:"<<wTaskID;
        _rPlayer.SendSysMsg(eMsgSevenDayCFGError);
        return eDayTargetRet_CFGError;
    }

    //检查领奖天数

    //天数检查去掉 2015-2-6
   /* if( pDayTargetCFGEx->_vecEventInstID.size()>1)
    {
    if(_rPlayer.GetFromCreateDays()<pDayTargetCFGEx->_Day)
    {
        LOG_INF<<"days error: day "<<_rPlayer.GetFromCreateDays()<<"|"<<pDayTargetCFGEx->_Day;
        _rPlayer.SendSysMsg(eMsgSevenDayDayLimit);
        return eDayTargetRet_DayLimit;
    }
    }
*/
    CUser& rUser = _rPlayer.GetUser();
    CStore* pStore = rUser.GetStoreByType(eStorePack);
    if(NULL == pStore)
    {
        LOG_CRI<<"NULL == pStore";
        _rPlayer.SendSysMsg(eMsgSevenDayCFGError); 
        return eDayTargetRet_CFGError;
    }

    //
    if(!pStore->CanAddItem(pDayTargetCFGEx->_vecPrizeItem))
    {
        LOG_INF<<"eDayTargetRet_PackFull";
        _rPlayer.SendSysMsg(eMsgSevenDayPackFull);
        return eDayTargetRet_PackFull;
    }


    if(!pStore->AddItem(pDayTargetCFGEx->_vecPrizeItem,NLogDataDefine::ItemFrom_SevenDayTarget))
    {
        LOG_INF<<"item cfg error";
        _rPlayer.SendSysMsg(eMsgSevenDayPackFull); 
        return eDayTargetRet_PackFull;
    }

    rInfo.byStatus = eDayTargetTaskStatus_TakePrized;
    UpdateToDB(rInfo);
    NotifiyUpdate(rInfo);

    return eDayTargetRet_Sucess;


}



