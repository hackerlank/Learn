#include "stdafx.h"
#include "Protocols.h"
#include "WondActMgr.h"
#include "SysMsgDefine.h"
#include "Tokenizer.h"
#include "RTime.h"

#define  SWITCH(wID) \
    switch(wID) \
    { \

#define CASE(wID) \
        case wID: \
            { \

#define ENDCASE } \
        break; \

#define ENDSWITCH }


CWondActMgr g_WondActMgr;
UINT32 GetTimerInfo(string& strText)
{
   Tokenizer tk(strText, "."); // XXX: Year.Month.Day
    UINT32 y = 0;
    UINT32 m = 0;
    UINT32 d = 0;
    UINT32 h = 0;
    UINT32 mi = 0;

   if(tk.size()>1)
   {
       y = atoi(tk[0].c_str());
       m  = atoi(tk[1].c_str());
       d = atoi(tk[2].c_str());
       h = atoi(tk[3].c_str());
       mi  = atoi(tk[4].c_str());
   }
    struct tm  t_tm;
    t_tm.tm_year = y - 1900;
    t_tm.tm_mon = m - 1;
    t_tm.tm_mday = d;
    t_tm.tm_hour = h;
    t_tm.tm_min = mi;
    t_tm.tm_sec = 0;
    time_t t2 = mktime(&t_tm);
    return t2; 
}
static UINT32 GetTimeByDays(string strDays)
{
    UINT32 dwTmp = 0;
    dwTmp = atoi(strDays.c_str());
    dwTmp = dwTmp * 24 * 3600;
    return dwTmp;
}

CWondActMgr::CWondActMgr() :
    _bInitCheck(true),
    _bInitOpenTime(false),
    _bConfigReady(false),
    _dwOpenTime(0)
{
    _setIDs.clear();
}

bool CWondActMgr::InitActTime()
{
    for(auto & it : _mapID2Info)
    {
        SActInfoExPtr pCFGExPtr = it.second;
        if(!pCFGExPtr)
            return false;
        UINT16 wIndex = pCFGExPtr->wOpenAct;
        if(wIndex == 1)
        {
            UINT32 dwAlarm = _dwOpenTime;
            UINT32 dwBegin = dwAlarm;
            UINT32 dwTime2 = atoi(pCFGExPtr->_Time2.c_str());
            dwAlarm += dwTime2 * 24 * 60 * 60 ;
            dwBegin = dwAlarm + 60;
            pCFGExPtr->dwAdvance = dwAlarm;
            pCFGExPtr->dwBegin   = dwBegin;
            pCFGExPtr->dwEnd     = GetTimeByDays(pCFGExPtr->_Time3) + dwBegin;
            pCFGExPtr->dwRetain  = GetTimeByDays(pCFGExPtr->_Time4) + pCFGExPtr->dwEnd;
        }
        else
        {
            pCFGExPtr->dwAdvance = GetTimerInfo(pCFGExPtr->_Time1);
            pCFGExPtr->dwBegin   = GetTimerInfo(pCFGExPtr->_Time2);
            pCFGExPtr->dwEnd     = GetTimerInfo(pCFGExPtr->_Time3);
            pCFGExPtr->dwRetain  = GetTimerInfo(pCFGExPtr->_Time4);
        }
        //LOG_CRI <<"ActID[" <<pCFGExPtr->wActID <<"] InitTime Suc.";
    }
    return true;
}

bool CWondActMgr::Init()
{
    if(_bConfigReady)
    {
        LOG_INF << " Config load Suc.";
        return true;
    }

    string strPath = Config._strConfigDir + "Conf/Table/ActivityOperating.xml";
    CActivityOperatingLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oActivityOperating.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SActivityOperatingCFG* pCFG = oLoader._vecData[i];
        if(pCFG->_TotalType == 2)//GameServer服务器上的活动
        {
            if(pCFG)
            {
                SActInfoExPtr pCFGExPtr(new SActInfoEx);
                pCFGExPtr->wActID    = pCFG->_ID;
                pCFGExPtr->wConfigID = pCFG->_ConfigID;
                pCFGExPtr->wType     = pCFG->_Type;
                pCFGExPtr->wOpenAct  = pCFG->_Stye;
                /*
                pCFGExPtr->dwAdvance = GetTimerInfo(pCFG->_Time1);
                pCFGExPtr->dwBegin   = GetTimerInfo(pCFG->_Time2);
                pCFGExPtr->dwEnd     = GetTimerInfo(pCFG->_Time3);
                pCFGExPtr->dwRetain  = GetTimerInfo(pCFG->_Time4);
                */
                pCFGExPtr->CopyFrom(*pCFG);
                _mapID2Info.insert(make_pair(pCFGExPtr->wActID,pCFGExPtr));
            }
        }
    }
    _bInitCheck = true;
   // 加载具体奖励配置文件
     strPath = Config._strConfigDir + "Conf/Table/ActivityOperatingConfig.xml";
    CActivityOperatingConfigLoader  aLoader;
    if(!aLoader.LoadData(strPath))
    {
        LOG_CRI << "ActivityOperatingConfig.LoadData fails! Path: " << strPath;
        return false;
    }
        for(size_t i = 0; i < aLoader._vecData.size(); ++i)
        {
            SActivityOperatingConfigCFG *pCfg = aLoader._vecData[i];
            if(pCfg != NULL)
            {
              SActConfigExPtr pConfigPtr(new SActConfigEx);
              pConfigPtr->wConfigID = pCfg->_ID;
              pConfigPtr->wType = pCfg->_Type;
              ParseConfigInfo(pConfigPtr->vecPrizes,pCfg->_TypePara1,pCfg->_TypePara2);
              pConfigPtr->CopyFrom(*pCfg);
              _mapID2Config.insert(make_pair(pConfigPtr->wConfigID,pConfigPtr));
            }
        }
    _bConfigReady = true;
    return true;
}

bool CWondActMgr::ReLoadConfig(const string &strFile)
{
    string strPath; 
    if("ActivityOperating.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ActivityOperating.xml";
        CActivityOperatingLoader  oLoader;
        if(!oLoader.LoadData(strPath))
        {
            LOG_CRI << "oActivityOperating.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oLoader._vecData.size(); ++i)
        {
            SActivityOperatingCFG* pCFG = oLoader._vecData[i];
            if(pCFG)
            {
                if(pCFG->_TotalType == 2)//GameServer服务器上的活动
                {
                    if(IsAllowReload(pCFG->_ID,1))
                    {
                        SActInfoExPtr pCFGExPtr(new SActInfoEx);
                        pCFGExPtr->wActID    = pCFG->_ID;
                        pCFGExPtr->wConfigID = pCFG->_ConfigID;
                        pCFGExPtr->wType     = pCFG->_Type;
                        pCFGExPtr->dwAdvance = GetTimerInfo(pCFG->_Time1);
                        pCFGExPtr->dwBegin   = GetTimerInfo(pCFG->_Time2);
                        pCFGExPtr->dwEnd     = GetTimerInfo(pCFG->_Time3);
                        pCFGExPtr->dwRetain  = GetTimerInfo(pCFG->_Time4);
                        pCFGExPtr->CopyFrom(*pCFG);
                        _mapID2Info.insert(make_pair(pCFGExPtr->wActID,pCFGExPtr));
                    
                    }
                }
            }
        }
    }
    else if("ActivityOperatingConfig.xml" == strFile)
    {
        // 加载具体奖励配置文件
         strPath = Config._strConfigDir + "Conf/Table/ActivityOperatingConfig.xml";
        CActivityOperatingConfigLoader  aLoader;
        if(!aLoader.LoadData(strPath))
        {
            LOG_CRI << "ActivityOperatingConfig.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < aLoader._vecData.size(); ++i)
        {
            SActivityOperatingConfigCFG *pCfg = aLoader._vecData[i];
            if(pCfg != NULL)
            {
              if(IsAllowReload(pCfg->_ID,2))
              {
                  SActConfigExPtr pConfigPtr(new SActConfigEx);
                  pConfigPtr->wConfigID = pCfg->_ID;
                  pConfigPtr->wType = pCfg->_Type;
                  ParseConfigInfo(pConfigPtr->vecPrizes,pCfg->_TypePara1,pCfg->_TypePara2);
                  pConfigPtr->CopyFrom(*pCfg);
                  _mapID2Config.insert(make_pair(pConfigPtr->wConfigID,pConfigPtr));
              }
            }
        }
    }
    return true;
}

bool CWondActMgr::IsAllowReload(UINT16 wID,UINT8 byFlag /* 1表示判断配置表，2表示判断奖励配置表 */ )
{ 
    if(byFlag == 1)
    {
        if(GetState(wID) == eActState_OnBegin)
        {
            LOG_INF << " Activity is beginning , Config can't reload! ActID = " << wID;
            return false;
        }
   }else if(byFlag == 2)
   {
        for(auto it = _mapID2Info.begin(); it!=_mapID2Info.end(); ++it)
        {
            SActInfoExPtr pInfo = it->second;
            if(pInfo)
            {
                if(wID == pInfo->wConfigID)
                {
                    if(GetState(pInfo->wActID) == eActState_OnBegin)
                    {
                        LOG_INF << " Cofig  is used by Activity , It can't reload! ConfigID = " << wID;
                        return false;
                    }
                }
            }

         }
   }
   return true;
}
bool CWondActMgr::ParseConfigInfo(TVecID2PrizePtr &vecPrizes,string &rPrizeString,string &rItemString)
{
    Tokenizer tkPrizeStr_1(rPrizeString,"|");
    Tokenizer tkItemStr_1(rItemString, "|");
   if(tkItemStr_1.size() != tkPrizeStr_1.size())
    {
        LOG_INF << "WonderActivity Prize Config Error" ;
        return false;
    }

    for(UINT8 it=0 ; it<tkPrizeStr_1.size() ; ++it)
    {
        SID2PrizePtr pPrizeCfg(new SID2Prize);
        Tokenizer tkPrizeStr_2(tkPrizeStr_1[it],";");
        for(UINT8 i=0; i<tkPrizeStr_2.size(); ++i)
        {
            UINT32 dwCond = atoi(tkPrizeStr_2[0].c_str());
            pPrizeCfg->vecConds.push_back(dwCond);
        }
        Tokenizer tkItemStr_2(tkItemStr_1[it],";");
        for(UINT8 byIt=0; byIt<tkItemStr_2.size(); ++byIt)
        {
            Tokenizer tkItemStr_3(tkItemStr_2[byIt],",");
            SItemGenInfo stItemGen;
            stItemGen.wItemID = atoi(tkItemStr_3[0].c_str());
            //LOG_CRI << " wItemID = " << stItemGen.wItemID ;
            stItemGen.dwCount = atoi(tkItemStr_3[1].c_str());
            //LOG_CRI<<" count = " <<stItemGen.dwCount ;
            stItemGen.eBindType = eBindGet;
            pPrizeCfg->vecItems.push_back(stItemGen);
        }
       vecPrizes.push_back(pPrizeCfg); 
    }
   return true;
}

UINT8 CWondActMgr::GetPrizeState(CPlayer &rPlayer,UINT16 wID,UINT8 byIndex)
{
    UINT8 byRet = 0;
    if(GetState(wID) == eActState_Init || GetState(wID) == eActState_OnAdvance)
        return byRet;
    UINT16 wType = 0;
    wType = GetActType(wID);
    if(wType == 0)
        return byRet;
    SWITCH(wType)
    CASE(eWondActType_CONDPRIZE)
        CLevelPrizeActPtr pLevel = rPlayer.GetLevelPrizeAct();
        if(pLevel)
        {
            byRet = pLevel->GetPrizeStateByID(byIndex);
        }
    ENDCASE
    ENDSWITCH
    return byRet;
}

TVecID2PrizePtr s_vecID2PrizePtr;

TVecID2PrizePtr  CWondActMgr::GetConds(UINT16 wID)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
    if(pInfo)
    {
        SActConfigExPtr pConfig = GetActConfig(pInfo->wConfigID);
        if(pConfig)
            return pConfig->vecPrizes ;
    }
    return s_vecID2PrizePtr;
}

bool  CWondActMgr::GetConds(UINT16 wID,UINT8 byIndex,TVecUINT32& vecConds)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
    if(pInfo)
    {
        SActConfigExPtr pConfig = GetActConfig(pInfo->wConfigID);
        if(pConfig)
        {
           TVecID2PrizePtr vecPrizes = pConfig->vecPrizes ;
           SID2PrizePtr pID2Prize = vecPrizes[byIndex-1];
           TVecUINT32 vecIDs = pID2Prize->vecConds;
           vecConds.assign(vecIDs.begin(),vecIDs.end());
           return true;
        }
    }
    return false;
}

bool CWondActMgr::GetPrize(CPlayer &rPlayer,UINT16& wID,TVecPrize &vecPrizes)
{
    auto oIt = _mapID2Config.find(wID);
    if(oIt == _mapID2Config.end())
    {
        return false;
    }
    TVecID2PrizePtr vecID2Prize = oIt->second->vecPrizes;
    for(UINT8 i=0; i<vecID2Prize.size(); ++i)
    {
        SPrize sPrize;
        sPrize.byIndex = (i + 1);
        sPrize.eState = static_cast<ELevelActStatus>(GetPrizeState(rPlayer,wID,(i+1)));
        TVecItemGenInfo vecItems = vecID2Prize.at(i)->vecItems;
        sPrize.vecItem.assign(vecItems.begin(),vecItems.end());
        vecPrizes.push_back(sPrize);
    }
    return true;
}
ELevelActStatus CWondActMgr::TakePrize(CPlayer &rPlayer,const UINT16& wID,UINT8 byIndex)
{
    if(GetState(wID) == eActState_Init || GetState(wID) == eActState_OnAdvance)
    {
        return eLevleActStatus_Error;
    }
    ELevelActStatus eResult = eLevleActStatus_Error;
    UINT16 wType = 0;
    wType = GetActType(wID);
    if(wType == 0)
        return eLevleActStatus_Error;
    SWITCH(wType)
    CASE(eWondActType_CONDPRIZE)
        CLevelPrizeActPtr pLevel = rPlayer.GetLevelPrizeAct();
        if(pLevel)
        {
            eResult = pLevel->TakePrize(wID,byIndex);
        }
    ENDCASE
    ENDSWITCH
    return eResult;
}

bool CWondActMgr::GetPrizeByID(UINT16 wID,UINT8 byIndex,TVecItemGenInfo &vecItems)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        SActConfigExPtr sConfig = GetActConfig(sInfo->wConfigID);
        if(sConfig)
        {
            TVecID2PrizePtr vecID2Prize = sConfig->vecPrizes;
            SID2PrizePtr pID2Prize = vecID2Prize.at(byIndex - 1);
            if(pID2Prize)
            {
                vecItems.assign((pID2Prize->vecItems).begin(),(pID2Prize->vecItems).end());
                return true;
            }
        }
    }
    return false;
}
void CWondActMgr::GetConds(UINT16 wID,UINT8 byIndex,TSetUINT32 &setIDs)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
    if(pInfo)
    {
        SActConfigExPtr pConfig = GetActConfig(pInfo->wConfigID);
        if(pConfig)
        {
            TVecID2PrizePtr vecPrizes = pConfig->vecPrizes ;
            if(byIndex == 0)
            {
                for(auto it=vecPrizes.begin(); it!=vecPrizes.end(); ++it)
                {
                   TVecUINT32 vecIDs = (*it)->vecConds;
                   for(size_t i=0; i<vecIDs.size(); ++i)
                       setIDs.insert(vecIDs[i]);
                }
            }else
            {
               SID2PrizePtr pID2Prize = vecPrizes[byIndex-1];
               TVecUINT32 vecIDs = pID2Prize->vecConds;
               for(size_t i=0; i<vecIDs.size(); ++i)
                       setIDs.insert(vecIDs[i]);
            }
        }
    }
}

UINT8 CWondActMgr::GetIndex(UINT16 wID)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
    if(pInfo)
    {
        SActConfigExPtr pConfig = GetActConfig(pInfo->wConfigID);
        if(pConfig)
        {
           return pConfig->vecPrizes.size();
        }
    }
    return 0;
}

void CWondActMgr::ClearDB(CPlayer& rPlayer,UINT16 wID)
{
    TSetUINT32 setIDs;
    UINT8 byIndex = GetIndex(wID);
    CLevelPrizeActPtr pLevel = rPlayer.GetLevelPrizeAct();
    if(!pLevel)
        return ;
    for(UINT8 i=1; i<=byIndex; ++i)
    {
        SPrize2DB sPrize;
        sPrize.qwRoleID = rPlayer.GetRoleID();
        sPrize.wActID = wID;
        sPrize.wLevel = i;
        pLevel->Update2DB(sPrize,eOpDel);
        pLevel->ClearPrize2DB(sPrize);
    }
}
string  CWondActMgr::GetActName(const UINT16& wID)
{
    string sRet = "";
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        sRet =  sInfo->_Name;
    }
    return sRet;
}

void CWondActMgr::OnAdvance(UINT16 wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        sInfo->eState = eActState_OnAdvance;
        //LOG_CRI << "OnAdvance wID = "<<wID << "| eState = " <<sInfo->eState;
    }
}
void CWondActMgr::OnBegin(const UINT16 wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    //LOG_CRI<<"wID="<<wID;
    if(sInfo)
    {
        sInfo->eState = eActState_OnBegin;
        //LOG_CRI << "OnBegin wID = "<<wID << "| eState = " <<sInfo->eState;
       g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgActivityOperatingBegin,BuildStrVec(GetActName(wID)));
    }
      _setIDs.insert(wID);
      TMapID2Usr mapID2Usr = CUserMgr::GetUsrMap();
      for(auto it=mapID2Usr.begin(); it!=mapID2Usr.end(); ++it)
      {
         CUserPtr pUser = it->second;
         if(pUser->GetUserState() == eUserInGame)
         {
             CPlayerPtr pPlayer = pUser->GetPlayer();
             if(pPlayer)
             {
                pPlayer->AddActID(wID);
                UINT16 wType = 0;
                wType = GetActType(wID);
                if(wType == 0)
                    return;
                SWITCH(wType)
                CASE(eWondActType_CONDPRIZE)
                    CLevelPrizeActPtr pLevel = pPlayer->GetLevelPrizeAct();
                     if(pLevel)
                     {
                        pLevel->RegisterEvent(wID);
                     }
                 ENDCASE
                 ENDSWITCH
             }
          }
      }
}

void CWondActMgr::OnEnd(const UINT16 wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        sInfo->eState = eActState_OnEnd;
       g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgActivityOperatingEnd,BuildStrVec(GetActName(wID)));
    }
       _setIDs.erase(wID);
      TMapID2Usr mapID2Usr = CUserMgr::GetUsrMap();
      for(auto it=mapID2Usr.begin(); it!=mapID2Usr.end(); ++it)
      {
         CUserPtr pUser = it->second;
         if(pUser->GetUserState() == eUserInGame)
         {
             CPlayerPtr pPlayer = pUser->GetPlayer();
             if(pPlayer)
             {
                pPlayer->DelActID(wID);
                UINT16 wType = 0;
                wType = GetActType(wID);
                if(wType == 0)
                    return;
                SWITCH(wType)
                CASE(eWondActType_CONDPRIZE)
                    CLevelPrizeActPtr pLevel = pPlayer->GetLevelPrizeAct();
                     if(pLevel)
                     {
                        pLevel->RemoveAllEvent(wID);
                     //   ClearDB(*pPlayer,wID);
                     }
                 ENDCASE
                 ENDSWITCH
             }
          }
      }
}

void CWondActMgr::OnRetain(UINT16 wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        sInfo->eState = eActState_OnRetain;
    }
      TMapID2Usr mapID2Usr = CUserMgr::GetUsrMap();
      for(auto it=mapID2Usr.begin(); it!=mapID2Usr.end(); ++it)
      {
         CUserPtr pUser = it->second;
         if(pUser->GetUserState() == eUserInGame)
         {
             CPlayerPtr pPlayer = pUser->GetPlayer();
             if(pPlayer)
                ClearDB(*pPlayer,wID);
         }
      }
}

void CWondActMgr::UpdateState(UINT16& wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    EActState eState = sInfo->eState; 
    SWITCH(eState)
    CASE(eActState_Init)
         //if(time(NULL) > sInfo->dwAdvance)
          //    OnAdvance(wID); 
    ENDCASE
    CASE(eActState_OnAdvance)
        if(time(NULL) > sInfo->dwBegin)
            OnBegin(wID);
    ENDCASE
    CASE(eActState_OnBegin)
        if(time(NULL) > sInfo->dwEnd)
            OnEnd(wID);
    ENDCASE
    CASE(eActState_OnEnd)
        if(time(NULL) > sInfo->dwRetain)
            OnRetain(wID);
    ENDCASE
    CASE(eActState_OnRetain)
        //预留
    ENDCASE
    ENDSWITCH
}


EActState CWondActMgr::GetState(UINT16 wID)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        return sInfo->eState; 
    }
    return eActState_Init;
}
void CWondActMgr::OneMinCheck(time_t tNow)
{
    auto oIt = _mapID2Info.begin();
    for(; oIt!=_mapID2Info.end(); ++oIt)
    {
        SActInfoExPtr pEvent = oIt->second;
        if(pEvent != NULL)
        {
            UINT16 wID = pEvent->wActID;
            UINT32 dwTime = pEvent->dwAdvance;
            if(AdvTime(dwTime))
            {
                OnAdvance(wID);
            }
        }
    }
}

void CWondActMgr::TimerCheck(time_t tNow)
{
    if(_bInitCheck)
    {
        if(!_bConfigReady)
        {
            LOG_INF << "_bConfigReady not Ready.";
            if(!Init())
            {
                LOG_INF <<"WondActMgr Init Err.";
                return ;
            }
        }
        if(_dwOpenTime == 0)
            _dwOpenTime = Config._dwOpenServerTime;
        if(!InitActTime())
        {
            LOG_INF << " Init ActivityTime Err.";
            return;
        }
        auto It = _mapID2Info.begin();
        for(; It!=_mapID2Info.end(); ++It)
        {
            SActInfoExPtr pEvent = It->second;
            if(pEvent != NULL)
            {
                //LOG_CRI <<"Now: " << time(NULL)<<",EndTime"<<pEvent->dwEnd<<",Begin:"<<pEvent->dwBegin;
                UINT16 wID = pEvent->wActID;
                if(IsAdvTime(pEvent->dwAdvance,pEvent->dwBegin))
                    OnAdvance(wID);
                if(IsBeginTime(pEvent->dwBegin,pEvent->dwEnd))
                    OnBegin(wID);
                if(IsRetainTime(pEvent->dwEnd,pEvent->dwRetain))
                    SetState(wID,eActState_OnEnd);
            }
        }
        _bInitCheck = false;
   
    }
    auto oIt = _mapID2Info.begin();
    for(; oIt!=_mapID2Info.end(); ++oIt)
    {
        SActInfoExPtr pEvent = oIt->second;
        if(pEvent != NULL)
        {
            UINT16 wID = pEvent->wActID;
            UpdateState(wID);
        }
    }
}

void CWondActMgr::SetState(UINT16 wID,EActState eState)
{
    SActInfoExPtr sInfo = GetActInfo(wID);
    if(sInfo)
    {
        sInfo->eState = eActState_OnEnd;
    }

}

bool CWondActMgr::AdvTime(UINT32 dwTime)
{
    time_t tNow = time(NULL);
    if(tNow - dwTime >= 0 && tNow - dwTime <= 59)
        return true;
    return false;
}

bool CWondActMgr::IsRetainTime(UINT32 dwEndTime,UINT32 dwRetainTime )
{
    time_t tNow = time(NULL);
    //LOG_CRI << "------------RetainTime : " << tNow;
    if(tNow > dwEndTime && tNow < dwRetainTime)
        return true;
    return false;
}

bool CWondActMgr::IsBeginTime(UINT32 dwBeginTime,UINT32 dwEndTime )
{
    time_t tNow = time(NULL);
    if(tNow > dwBeginTime && tNow < dwEndTime)
        return true;
    return false;
}

bool CWondActMgr::IsAdvTime(UINT32 dwAdvTime,UINT32 dwBeginTime )
{
    time_t tNow = time(NULL);
    if(tNow > dwAdvTime && tNow < dwBeginTime)
        return true;
    return false;
}
SActInfoExPtr CWondActMgr::GetActInfo(const UINT16 &wID)
{
    auto oIt = _mapID2Info.find(wID);
    if(oIt != _mapID2Info.end())
    {
        return oIt->second;
    }
    return NULL;
}
SActConfigExPtr CWondActMgr::GetActConfig(UINT16 &wID)
{
    auto oIt = _mapID2Config.find(wID);
    if(oIt != _mapID2Config.end())
    {
        return oIt->second;
    }
    return NULL;
}
TSetUINT16& CWondActMgr::GetActList()
{
    return _setIDs;
}

bool CWondActMgr::OpenActivity(UINT16 wID,string &sAdv,string& sBegin,string& sEnd,string& sRetain)
{
     SActInfoExPtr pInfo = GetActInfo(wID);
     if(pInfo == NULL)
         return false;
     if(GetState(pInfo->wActID) == eActState_OnBegin)
     {
         LOG_INF << " Activity ID = " << wID << " already Begin";
         return false;
     }
     sAdv == "0" ? pInfo->dwAdvance = 0 : pInfo->dwAdvance = GetTimerInfo(sAdv);
     sRetain == "0" ?  pInfo->dwRetain = 0 : pInfo->dwRetain = GetTimerInfo(sRetain);
     pInfo->dwBegin = GetTimerInfo(sBegin);
     pInfo->dwEnd = GetTimerInfo(sEnd);
     OnBegin(pInfo->wActID);
     return true;
}
bool CWondActMgr::EndActivity(UINT16 wID)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
     if(pInfo == NULL)
         return false;
     if(GetState(pInfo->wActID) == eActState_OnEnd)
     {
         LOG_INF << " Activity ID = " << wID << " already End";
         return false;
     }
     OnEnd(pInfo->wActID);
     return true;
}

bool CWondActMgr::ModifyTime(UINT16 wID,UINT8 byType,UINT32 dwTime)
{
    //TODO
    return true; 
}

UINT16 CWondActMgr::GetActType(UINT16 wID)
{
    SActInfoExPtr pInfo = GetActInfo(wID);
    if(pInfo == NULL)
        return 0;
     return pInfo->wType; 
}

void CWondActMgr::GetRoleState(CPlayer &rPlayer,NWonderActivityProt::TVecRoleAllStatus& vecRet)
{
    auto oIt = _mapID2Info.begin();
    for(; oIt!=_mapID2Info.end(); ++oIt)
    {
        TVecPrize vecPrizes;
        SActInfoExPtr pEvent = oIt->second;
        if(pEvent != NULL)
        {
            UINT16 wID = pEvent->wActID;
            if(!GetPrize(rPlayer,wID,vecPrizes))
            {
                LOG_INF << "ActID ="<<wID <<" GetPrize Error.";
                continue;
            }
            NWonderActivityProt::SRoleAllStatus sRoleAllState;
            NWonderActivityProt::SRoleStatus sState;
            sRoleAllState.wActID = wID;
            for(auto &it : vecPrizes)
            {
                sState.wCond = static_cast<UINT32>(it.byIndex);
                switch(it.eState)
                {
                    case eLevleActStatus_Finish:
                        sState.byStatus = 1;
                        break;
                    case eLevleActStatus_GetPrize:
                        sState.byStatus = 2;
                        break;
                    default:
                        sState.byStatus = 0;
                }
                sRoleAllState.vecAllState.push_back(sState);
            }
            vecRet.push_back(sRoleAllState);
        }
    }
}

