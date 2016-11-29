#include "DayActivityMgr.h"

#include "Tokenizer.h"
#include "WorldBossMgr.h"
#include "DayActProt.h"
#include "DayActCFG.h"
#include "LangHuanBlessMgr.h"
#include "ShushanBattleMgr.h"
#include "GuildBattleMgr.h"
#include "NewGuildBattleMgr.h"
#include "EnergyMgr.h"
#include "DayTeamRewardActivity.h"
#include "DayShipRewardActivity.h"
#include "AnswerMgr.h"
#include "ZhanQiMgr.h"
#include "GodChest.h"

using namespace NDayActProt;


CDayActivityMgr  g_DayActivityMgr;

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

    for(auto& pDayActCFG : oDayActLoader._vecData)
    {
        if(pDayActCFG)
        {
            SDayActExPtr pCFG = SDayActExPtr(new SDayActEx);
            LoadTimerInfo(pCFG->oAlarmTime, pDayActCFG->_AlarmTime);
            LoadTimerInfo(pCFG->oReadyTime, pDayActCFG->_ReadyTime);
            LoadTimerInfo(pCFG->oBeginTime, pDayActCFG->_BeginTime);
            LoadTimerInfo(pCFG->oEndTime,   pDayActCFG->_EndTime);
 
            pCFG->CopyFrom(*pDayActCFG);

            _mapDayActExPtr[pCFG->_ID] = pCFG;

            CDayActEventPtr pDayActEvent(new CDayActEvent(pCFG->_ID, pCFG->_ActType, pCFG->_SpecialType));
            _mapDayActEventPtr[pCFG->_ID] = pDayActEvent;

            if(eActTypeLingShan == pCFG->_ActType)
            {
                if(0 == pCFG->_dwParam)
                {
                    LOG_CRI<<" eActTypeLingShan Error Param";
                    return false;
                }
            }
         }
    }

    //register 
    _mapDayActivity[eActTypeWorldBoss]          = &CWorldBossMgr::Instance();
    _mapDayActivity[eActTypeLangHuanBless]      = &CLangHuanBlessMgr::Instance();
    _mapDayActivity[eActTypeShushanBattle]      = &CShushanBattleMgr::Instance();
    _mapDayActivity[eActTypeGuildBattle]        = &CGuildBattleMgr::Instance();
    _mapDayActivity[eActTypeEnergy]             = &CEnergyActivity::Instance();
    _mapDayActivity[eActTypeTeamReward]         = &CTeamRewardActivity::Instance();
    _mapDayActivity[eActTypeAnswer]             = &CAnswerMgr::Instance();
    _mapDayActivity[eActTypeLingShan]           = &g_ZhanQiMgr;
    _mapDayActivity[eActTypeNewGuildBattle]     = &NNewGuildBattle::CBattleMgr::Instance();
    _mapDayActivity[eActTypeChest]              = &g_GodChest;
    _mapDayActivity[eActTypeShipReward]         = &CShipRewardActivity::Instance();
    _bInitCheck = true;
  
    return true;
}

void CDayActivityMgr::OnMinuteCheck(time_t tNow)
{
    if(_bInitCheck)
    {
        for(auto & rPair : _mapDayActEventPtr)
        {
            rPair.second->CheckStatus();
        }
        _bInitCheck = false;
        return;
    }

    for(auto & rPair : _mapDayActEventPtr)
    {
        if(CheckConflictType(rPair.second->_dwActType) && rPair.second->IsAlarmTime(tNow))
            rPair.second->OnAlarm();
    }
}

void CDayActivityMgr::TimerCheck(time_t tNow)
{
    for(auto itr = _mapDayActivity.begin(); itr != _mapDayActivity.end(); ++itr)
    {
        itr->second->UpdateState(tNow);
        itr->second->UpdateEvent(tNow);
        if(itr->second->GetStatus() == eDayActivityStatusEnd)
            itr->second->ResetState();
    }
}

void CDayActivityMgr::OpenActivity(UINT32 dwActID)
{
    LOG_INF << "CDayActivityMgr::OpenActivity: " << dwActID;

    auto itr = _mapDayActEventPtr.find(dwActID);
    if(itr != _mapDayActEventPtr.end())
        itr->second->GMOpen();
    else
        LOG_INF << "Error dwActID: " << dwActID;
}

CDayActEventPtr CDayActivityMgr::GetDayActEvent(UINT32 dwActID)
{
    auto itr = _mapDayActEventPtr.find(dwActID);
    if(itr != _mapDayActEventPtr.end())
        return itr->second;

    return NULL;
}

CDayActivity*  CDayActivityMgr::GetDayActivity(UINT32 dwActType)
{
    auto itr = _mapDayActivity.find(dwActType);
    if(itr != _mapDayActivity.end())
        return itr->second;

    return NULL;
}

SDayActExPtr CDayActivityMgr::GetDayActEx(UINT32 dwActID)
{
    auto itr = _mapDayActExPtr.find(dwActID);
    if(itr != _mapDayActExPtr.end())
        return itr->second;

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

void CDayActivityMgr::Destroy()
{
    _mapDayActExPtr.clear();
    _mapDayActEventPtr.clear();
    _mapDayActivity.clear();
}

// ===  FUNCTION  ======================================================================
//         Name:  GetTypeTime
//  Description:  获取某一类活动的时间
// =====================================================================================
bool CDayActivityMgr::GetTypeTime(NDayActProt::EActType eType, TSetUINT32& rsetDayTime)
{
    for (auto& rPair : _mapDayActExPtr)
    {
        if (!rPair.second)
            continue;
        if (rPair.second->_ActType == eType)
        {
            switch(eType)
            {
                case eActTypeNewGuildBattle: // 新帮派战
                    {
                        UINT8 byWeek = rPair.second->_WeekDay;
                        if (byWeek)
                        {
                            if (byWeek == 1)
                                byWeek = 8;
                            --byWeek;
                        }
                        rsetDayTime.insert((byWeek - 1) * 24 *3600 + rPair.second->oBeginTime.byHour * 3600 + rPair.second->oBeginTime.byMinute * 60);
                    }
                    break;
                default:
                    rsetDayTime.insert(rPair.second->oBeginTime.byHour * 3600 + rPair.second->oBeginTime.byMinute * 60);
                    break;
            }
        }
    }
    return true;
}		// -----  end of function GetTypeTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetForceOpenDay
//  Description:  获取强开的活动天数
// =====================================================================================
UINT8 CDayActivityMgr::GetForceOpenDay (NDayActProt::EActType eType)
{
    for (auto & rPair : _mapDayActExPtr)
    {
        if (!rPair.second)
            continue;
        if (rPair.second->_ActType == static_cast<UINT8>(eType) && rPair.second->_OpenDay)
            return rPair.second->_OpenDay;
    }
    return 0;
}		// -----  end of function GetForceOpenDay  ----- //

bool CDayActivityMgr::CheckConflictType(UINT32 dwActType)
{
    for (auto& rPair : _mapDayActEventPtr)
    {
        if (!rPair.second)
            continue;
        const set<NDayActProt::EActType>& rsetInfo = rPair.second->GetConflictType();
        auto it = rsetInfo.find(static_cast<NDayActProt::EActType>(dwActType));
        if (it != rsetInfo.end())
        {
            auto it = _mapDayActivity.find(static_cast<NDayActProt::EActType>(rPair.second->_dwActType));
            {
                if (it != _mapDayActivity.end())
                {
                    switch (it->second->GetStatus())
                    {
                        case eDayActivityStatusAlarm: //活动警戒状态
                        case eDayActivityStatusReady: //活动准备状态
                        case eDayActivityStatusProcess: //活动进行状态
                            return false;
                        case eDayActivityStatusInit: //活动初始化状态
                        case eDayActivityStatusEnd: //活动结束状态
                        default:
                            break;
                    }
                }
            }
        }
    }
    return true;
}

bool CDayActivityMgr::LoadTimerInfo(STimerInfo& oTimerInfo,string& strText)
{
   if("" == strText)
       return true;
   Tokenizer tk(strText, ":"); // XXX: Hour:Minute
   if(tk.size() > 1)
   {
      oTimerInfo.byHour     = atoi(tk[0].c_str());
      oTimerInfo.byMinute   = atoi(tk[1].c_str());
   }
   return true;
}

