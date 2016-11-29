#include "stdafx.h"
#include "Protocols.h"
#include "Tokenizer.h"
#include "ActivityMgr.h"

CActivityMgr g_ActivityMgr;

static UINT32 GetTime(std::string strTmp)
{
    struct tm  t_tm;
    if("" == strTmp)
    {
        return 0;
    }
    
    Tokenizer tk(strTmp,"."); 
    if(tk.size() > 0)
    {
        UINT32 year = atoi(tk[0].c_str());
        UINT32 mon = atoi(tk[1].c_str());
        UINT32 day = atoi(tk[2].c_str());
        UINT32 hour = atoi(tk[3].c_str());
        UINT32 min  = atoi(tk[4].c_str());
        t_tm.tm_year = year - 1900;
        t_tm.tm_mon = mon - 1;
        t_tm.tm_mday = day;
        t_tm.tm_hour = hour;
        t_tm.tm_min = min;
        t_tm.tm_sec = 0;
        time_t t2 = mktime(&t_tm);
        return t2; 
    }
    return 0;
}

bool CActivityMgr::Init()
{
    if(!LoadConfig())
    {
        LOG_CRI << "Load Config Err.";
        return false;
    }
    if(!InitActivity())
    {
        LOG_CRI<<"InitActivity Err.";
        return false;
    }
    _byProcess |= (1 << eProcessInited);
    return true;
}

bool CActivityMgr::LoadConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/ActivityCenter.xml";
    CActivityCenterLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oActivityCenter LoadData fails! Path: " << strPath;
        return false;
    }
    UINT32 dwNow = static_cast<UINT32>(time(NULL));
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SActivityCenterCFG* pEx = oLoader._vecData[i];
        if(pEx)
        {
            UINT32 dwAlarm = GetTime(pEx->_Alarm);
            UINT32 dwReady = dwAlarm + pEx->_Ready * 60; 
            UINT32 dwBegin = dwReady + pEx->_Begin * 60;
            UINT32 dwEnd = dwBegin + pEx->_End * 3600;
            if(dwNow < dwEnd)
            {
                ActivityPtr pAct(new CActivity(pEx->_ID,pEx->_Index));
                pAct->SetAlarmTime(dwAlarm);
                pAct->SetReadyTime(dwReady);
                pAct->SetBeginTime(dwBegin);
                pAct->SetEndTime(dwEnd);
                pAct->SetIsSync(pEx->_bSync);
                pAct->SetSyncTime(dwAlarm - pEx->_Sync * 60);
                
                SKey oKey(pEx->_ID,pEx->_Index);
                if(!_mapID2Activity.insert(make_pair(oKey,pAct)).second)
                {
                    LOG_INF<<"ActID="<<pEx->_ID <<" insert Err.";
                    return false;
                }
            }
        }
    }
    _byProcess |= (1 << eProcessConfigInited);
    return true;
}

void CActivityMgr::LoadFromDB()
{
    g_Center2DBCommC.Send_GetActivityCenterInfo([](UINT8 byRet_,const NProtoCommon::TVecActivityOpt& vecInfo)
            {
                 if(byRet_ == 0)
                 {
                    g_ActivityMgr.Load(vecInfo);
                 }
            });
}

void CActivityMgr::Load(const TVecActivityOpt& vecInfo)
{
    UINT32 dwNow = static_cast<UINT32>(time(NULL));
    for(auto it : vecInfo)
    {
        if(it.dwEnd > dwNow)
        {
            SKey oKey(it.dwActID,it.byIndex);
            _mapTmp.insert(make_pair(oKey,it));
        }
    }
    _byProcess |= (1 << eProcessDBInited);
}

bool CActivityMgr::InitActivity()
{
    for(auto& it : _mapID2Activity)
    {
        SKey oKey = it.first;
        ActivityPtr pAct = it.second;
        SActivityOpt* pEx = GetActByKey(oKey);
        if(!pEx || !pAct)
        {
            LOG_INF<<"pEx || pAct  null.";
            continue;
        }
        pAct->SetBeginTime(pEx->dwBegin);
        pAct->SetEndTime(pEx->dwEnd);
        DelActByKey(oKey);
    }
    for(auto& it : _mapTmp)
    {
        SKey oKey(it.first.dwActID,it.first.byIndex);
        ActivityPtr pAct(new CActivity(it.first.dwActID,it.first.byIndex));
        if(pAct)
            _mapID2Activity.insert(make_pair(oKey,pAct));
    }

    return true;
}
void CActivityMgr::DelActByKey(SKey oKey)
{
    auto it = _mapTmp.find(oKey);
    if(it != _mapTmp.end())
        _mapTmp.erase(it);
}

void CActivityMgr::DelAct(UINT32 dwActID,UINT8 byIndex)
{
    SKey oKey(dwActID,byIndex);
    auto it = _mapID2Activity.find(oKey);
    if(it != _mapID2Activity.end())
        _mapID2Activity.erase(it);
}

SActivityOpt* CActivityMgr::GetActByKey(SKey oKey)
{
    auto it = _mapTmp.find(oKey);
    if(it!=_mapTmp.end())
        return &it->second;
    return NULL;
}

ActivityPtr CActivityMgr::GetAct(UINT32 dwActID,UINT8 byIndex)
{
    SKey oKey(dwActID,byIndex);
    auto it = _mapID2Activity.find(oKey);
    if(it!=_mapID2Activity.end())
        return it->second;
    return NULL;
}

void CActivityMgr::SetTime(UINT32 dwActID,UINT32 dwBegin,UINT32 dwEnd)
{
    UINT32 dwAlarm = dwBegin - 2*60;
    UINT32 dwLonger = dwEnd - dwBegin;
    SetTime(dwActID,dwAlarm,dwLonger,true,120);
}

bool CActivityMgr::SetTime(UINT32 dwActID,UINT8 byIndex,UINT32 dwAlarm,UINT32 dwLonger,bool bSync/* = false */, UINT32 dwSync/*=120*/)
{
   if(dwAlarm < time(NULL) 
           || dwLonger == 0 
           || byIndex == 0 
           || dwActID == 0)
       return false;
   if(bSync && !dwSync)
       return false;
   ActivityPtr pAct = NULL;
   pAct = GetAct(dwActID,byIndex);
   if(!pAct)
   {
       SKey oKey(dwActID,byIndex);
       pAct = ActivityPtr(new CActivity(dwActID,byIndex));
       pAct->SetAlarmTime(dwAlarm);
       pAct->SetReadyTime(dwAlarm + 1 * 60);
       pAct->SetBeginTime(dwAlarm + 2 * 60);
       pAct->SetEndTime(dwAlarm + 2*60 + dwLonger);
       if(bSync)
           pAct->SetIsSync(bSync);
       if(!dwSync || bSync)
           pAct->SetSyncTime(dwAlarm - dwSync);
       _mapID2Activity.insert(make_pair(oKey,pAct));
   }else
   {
       if(pAct->IsRun())
       {
           LOG_INF<<"dwActID ="<<dwActID<<" is running.";
           return false;
       }
       pAct->SetAlarmTime(dwAlarm);
       pAct->SetReadyTime(dwAlarm + 1 * 60);
       pAct->SetBeginTime(dwAlarm + 2 * 60);
       pAct->SetEndTime(dwAlarm + 2*60 + dwLonger);
       if(bSync)
           pAct->SetIsSync(bSync);
       if(!dwSync || bSync)
           pAct->SetSyncTime(dwAlarm - dwSync);
   }
   pAct->Update2DB(eOpAdd);
   return true;
}

/*
bool CActivityMgr::SetTime(UINT32 dwActID,UINT32 dwBegin,UINT32 dwEnd)
{
    return SetTime(dwActID,1,dwBegin,dwEnd);
}
*/

void CActivityMgr::TimerCheck()
{
    if(!Config.AllServerIsReady())
    {
        return;
    }

    bool bRun = _byProcess & (1 << eProcessInited);
    if(!bRun)
    {
        LOG_INF<<"ActivityMap not Ready.";
        return;
    }
    if(_mapID2Activity.size() == 0)
        return;
    if(_bInit)
    {
        for(auto &it : _mapID2Activity)
        {
            ActivityPtr pAct = it.second;
            if(pAct)
                pAct->OnReBegin();
        }
        _bInit = false;
    }
    for(auto &oIt : _mapID2Activity)
    {
        ActivityPtr pAct = oIt.second;
        if(pAct)
            pAct->UpdateState();
    }
}
#if 0
bool CActivityMgr::ModifyChestParam(const NProtoCommon::SChestOpt& sChestOpt,UINT32 dwActID,UINT8 byIndex)
{
    ActivityPtr pAct = GetAct(dwActID,byIndex);
    if(!pAct)
    {
        LOG_INF<<"pAct null.";
        return false;
    }
    if(pAct->IsRun())
    {
        LOG_INF<<"Act is Runing.";
        return false;
    }
    pAct->SetIsSync(true);
    pAct->SetSyncTime(sChestOpt.dwAlarm - 2 * 60);
    pAct->SetAlarmTime(sChestOpt.dwAlarm);
    pAct->SetReadyTime(sChestOpt.dwAlarm + 1 * 60);
    pAct->SetBeginTime(sChestOpt.dwAlarm + 2 * 60);
    pAct->SetEndTime(sChestOpt.dwAlarm + sChestOpt.byLonger * 60);
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_ModifyChest(&dwGameSvrIdx, 1,sChestOpt);
    return true;
}
#endif

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

