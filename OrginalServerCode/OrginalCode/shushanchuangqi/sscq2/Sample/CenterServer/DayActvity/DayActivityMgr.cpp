#include "DayActivityMgr.h"
#include "Tokenizer.h"
#include "DayActProt.h"
#include "DayActCFG.h"

using namespace NDayActProt;

CDayActivityMgr  g_DayActivityMgr;

bool LoadTimerInfo(STimerInfo& oTimerInfo,string& strText)
{
   
   if("" == strText)
   {
       return true;

   }


   Tokenizer tk(strText, ":"); // XXX: Hour:Minute
   
   if(tk.size()>1)
   {
      oTimerInfo.byHour = atoi(tk[0].c_str());
      oTimerInfo.byMinute = atoi(tk[1].c_str());
   }

   return true;
}

bool CDayActivityMgr::Init()
{
    CDayActLoader oDayActLoader;
    string strPath = Config._strConfigDir + "Conf/Table/DayAct.xml";
    if(!oDayActLoader.LoadData(strPath))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    _mapDayActEventPtr.clear();

    for(auto iter = oDayActLoader._vecData.begin(); iter != oDayActLoader._vecData.end();iter++)
    {
        SDayActCFG* pDayActCFG = *iter;
        if(pDayActCFG)
        {
            SDayActExPtr pCFG = SDayActExPtr(new SDayActEx);
            LoadTimerInfo(pCFG->oAlarmTime,pDayActCFG->_AlarmTime);
            LoadTimerInfo(pCFG->oReadyTime,pDayActCFG->_ReadyTime);
            LoadTimerInfo(pCFG->oBeginTime,pDayActCFG->_BeginTime);
            LoadTimerInfo(pCFG->oEndTime,pDayActCFG->_EndTime);
 
            pCFG->CopyFrom(*pDayActCFG);

            _mapDayActExPtr[pCFG->_ID]=pCFG;

            CDayActEventPtr pDayActEvent(new CDayActEvent(pCFG->_ID,pCFG->_ActType));

            _mapDayActEventPtr[pCFG->_ID]=pDayActEvent;

         }
    }

    //register 
    //_mapDayActivity[eActTypeWorldBoss]= &CWorldBossMgr::Instance();
    //_mapDayActivity[eActTypeLangHuanBless] = &CLangHuanBlessMgr::Instance();
    //_mapDayActivity[eActTypeShushanBattle]= &CShushanBattleMgr::Instance();
    //_mapDayActivity[eActTypeGuildBattle] = &CGuildBattleMgr::Instance();
    //_mapDayActivity[eActTypeEnergy] = &CEnergyActivity::Instance();
    //_mapDayActivity[eActTypeTeamReward] = &CTeamRewardActivity::Instance();
    
    //_mapDayActivity[eActTypeAnswer] = &CAnswerMgr::Instance();
    _bInitCheck = true;
  
    /*
    strPath = Config._strConfigDir + "Conf/Table/Foundation.xml";
    CFoundationLoader oFoundationLoader;
    if(!oFoundationLoader.LoadData(strPath))
    {
        LOG_CRI << "oFoundationLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFoundationLoader._vecData.size(); ++i)
    {
        SFoundationCFG* pFoundationCFG = oFoundationLoader._vecData[i];
        SFoundationCFGEx& rFoundationCFGEx = _mapID2FoundationCFG[pFoundationCFG->_Uid];
        rFoundationCFGEx.SetConfig(*pFoundationCFG);

        if (rFoundationCFGEx._Level.length() > 0)
        {
            Tokenizer yatk(rFoundationCFGEx._Level, ",");
            for (size_t j = 0; j < yatk.size(); ++ j)
            {
                rFoundationCFGEx._mapID2Level.insert(make_pair(j, atoi(yatk[j].c_str())));
            }
        }
        Tokenizer tk(rFoundationCFGEx._Reward, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (!dwItemID)
                continue;
            SItemGenInfo stItemGen;
            if (yatk.size() > 1)
                stItemGen.dwCount = atoi(yatk[1].c_str());
            else
                stItemGen.dwCount = 1;
            stItemGen.wItemID = dwItemID;
            stItemGen.eBindType = eBindGet;
            rFoundationCFGEx._mapItemGen.insert(make_pair(j+1, stItemGen));
        }
    }

    */
    return true;
}

void CDayActivityMgr::OnMinuteCheck(time_t tNow)
{
    if(_bInitCheck)
    {
        for(auto itr = _mapDayActEventPtr.begin(); itr != _mapDayActEventPtr.end(); ++itr)
        {
            itr->second->CheckStatus();
        }
        _bInitCheck = false;
        return;
    }


    for(auto itr = _mapDayActEventPtr.begin(); itr != _mapDayActEventPtr.end(); ++itr)
    {
        if(itr->second->IsAlarmTime(tNow))
        {
            itr->second->OnAlarm();
        }
    }
}

void CDayActivityMgr::TimerCheck(time_t tNow)
{
    for(auto itr = _mapDayActivity.begin(); itr != _mapDayActivity.end(); ++itr)
    {
        itr->second->UpdateState(tNow);
        itr->second->UpdateEvent(tNow);
        if(itr->second->GetStatus() == eDayActivityStatusEnd)
        {
            itr->second->ResetState();
        }
    }

}

void CDayActivityMgr::OpenActivity(UINT32 dwActID)
{
    LOG_INF<<"CDayActivityMgr::OpenActivity: "<<dwActID;

    auto itr = _mapDayActEventPtr.find(dwActID);
    if(itr != _mapDayActEventPtr.end())
    {
        itr->second->GMOpen();
    }
    else
    {
        LOG_INF << "Error dwActID: " << dwActID;
    }
}

CDayActEventPtr CDayActivityMgr::GetDayActEvent(UINT32 dwActID)
{
    auto itr = _mapDayActEventPtr.find(dwActID);
    if(itr != _mapDayActEventPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

CDayActivity*  CDayActivityMgr::GetDayActivity(UINT32 dwActType)
{
     auto itr = _mapDayActivity.find(dwActType);
    if(itr != _mapDayActivity.end())
    {
        return itr->second;
    }

    return NULL;
}

SDayActExPtr CDayActivityMgr::GetDayActEx(UINT32 dwActID)
{
    auto itr = _mapDayActExPtr.find(dwActID);
    if(itr != _mapDayActExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

void CDayActivityMgr::GetActInfo(TVecActInfo& vecActInfo)
{
    for(auto itr = _mapDayActivity.begin(); itr != _mapDayActivity.end(); ++itr)
    {
        SActInfo oInfo;
        oInfo.dwActType = itr->second->GetActID();
        oInfo.dwActStatus = itr->second->GetStatus();
        vecActInfo.push_back(oInfo);

    }
}

/*
SFoundationCFGEx* CDayActivityMgr::GetFoundationCFG(UINT8 byType)
{
    auto itr = _mapID2FoundationCFG.find(byType);
    if(itr != _mapID2FoundationCFG.end())
        return &itr->second;
    return NULL;
}
*/
void CDayActivityMgr::Destroy()
{
    _mapDayActExPtr.clear();
    _mapDayActEventPtr.clear();
    _mapDayActivity.clear();
}
