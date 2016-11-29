#include "stdafx.h"
#include "Protocols.h"
#include "Version.h"
#include "Tokenizer.h"
#include "WonderActivityMgr.h"
#include "SysMsgDefine.h"
#include "VarDefine.h"
#include "CenterGameVar.h"
#include "Parameter.h"

//注册活动头文件
#include "RankMgr.h"
#include "LevelAct.h"
#include "TotalActMgr.h"
#include "PointActMgr.h"
#include "LevelRank.h"
#include "FighterRank.h"
#include "PetRank.h"
#include "GuildRank.h"
#include "ArenaRank.h"
#include "TrumpRank.h"
#include "TrumpAct.h"
#include "PointRank.h"
#include "QQCoinAct.h"
#include "BeautyAct.h"
#include "HorseAct.h"
#include "OpenAct.h"

////////////////////////////////
//QQ养成中Var值设置
const static UINT32 dwPoolMax = 10000;
//按期活动，中间间隔2分钟开启 下一场
const static UINT32 dwInterval = 2 * 60;
////////////////////////////////
CWonderActivityMgr g_WonderActivityMgr;
/////////////////////////
bool GetTimerInfo(SWActTime& oTimerInfo,string& strText)
{
   
   if("" == strText)
   {
       return true;

   }
   Tokenizer tk(strText, "."); // XXX: Year.Month.Day
   
   if(tk.size()>1)
   {
      oTimerInfo.wYear = atoi(tk[0].c_str());
      oTimerInfo.byMonth = atoi(tk[1].c_str());
      oTimerInfo.byDay = atoi(tk[2].c_str());
      oTimerInfo.byHour = atoi(tk[3].c_str());
      oTimerInfo.byMin  = atoi(tk[4].c_str());
   }

   return true;
}
static void GetTimeByDay(SWActTime &oTimerInfo,UINT32 dwDays, bool bAddInterval)
{
    UINT32 dwTmp = 0;
    dwTmp = dwDays * 24 * 3600; //s
    if(bAddInterval)
        dwTmp += dwInterval;
    dwTmp += g_WonderActivityMgr.GetOpenTime();
    time_t tTime = static_cast<time_t>(dwTmp);
    struct tm *pTm = localtime(&tTime);
    
    oTimerInfo.wYear = pTm->tm_year + 1900;
    oTimerInfo.byMonth = pTm->tm_mon + 1;
    oTimerInfo.byDay = pTm->tm_mday;
    oTimerInfo.byHour = pTm->tm_hour;
    oTimerInfo.byMin  = pTm->tm_min;
}
bool CWonderActivityMgr::Init()
{
    if(_bConfigReady) //配置已经被加载
        return true;
    return LoadConfig();
}

bool CWonderActivityMgr::CheckActivityVar()
{
    bool bRet = false;
    if(g_CenterGameVar.IsLoad())
    {
        UINT32 dwValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinMaxValue);
        if(!dwValue)
        {
            dwValue = SParamConfig::dwMaxPoolValue;
            g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinMaxValue,dwValue);
            g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinConsumeValue,dwValue);
        }
        bRet = true;
        _dwOpenTime = Config._dwOpenServerTime;
    }
    return bRet;
}
bool CWonderActivityMgr::InitTimeForAct()
{
   UINT16 byIndex = 0;
   for(auto &it : _mapID2WActInfo)
   {
       SWActCFGExPtr pCFGExPtr = it.second;
       if(pCFGExPtr)
       {
           byIndex = pCFGExPtr->wOpenAct;
           if(byIndex == 1) /* 开服活动 */
           {
               bool bAdd = false;
               UINT32 dwBase = atoi((pCFGExPtr->_Time2).c_str());
               if(dwBase)
                   bAdd = true;
               GetTimeByDay(pCFGExPtr->sAdvanceTime,dwBase,bAdd);
               GetTimeByDay(pCFGExPtr->sBeginTime,dwBase,bAdd);

               UINT32 dwTime = atoi((pCFGExPtr->_Time3).c_str());
               dwTime += dwBase;
               GetTimeByDay(pCFGExPtr->sEndTime,dwTime,false);
               dwTime += atoi((pCFGExPtr->_Time4).c_str());
               GetTimeByDay(pCFGExPtr->sRetainTime,dwTime,false); 
           }
           else 
           {
               GetTimerInfo(pCFGExPtr->sAdvanceTime,pCFGExPtr->_Time1);
               GetTimerInfo(pCFGExPtr->sBeginTime,pCFGExPtr->_Time2);
               GetTimerInfo(pCFGExPtr->sEndTime,pCFGExPtr->_Time3);
               GetTimerInfo(pCFGExPtr->sRetainTime,pCFGExPtr->_Time4);
           }
       }
       else 
       {
           LOG_INF <<"pCFGExPtr null.";
           return false;
       }
       //LOG_CRI << "ActID["<<pCFGExPtr->wID <<"] InitTime Suc"; 
   }
   return true;
}

bool CWonderActivityMgr::LoadConfig(bool bReload)
{
    string strPath = Config._strConfigDir + "Conf/Table/ActivityOperating.xml";
    CActivityOperatingLoader  oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oActivityOperating.LoadData fails! Path: " << strPath;
        return false;
    }

    _mapID2WActEvent.clear();
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SActivityOperatingCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
           SWActCFGExPtr pCFGExPtr(new SWActCFGEx);
           pCFGExPtr->wID = pCFG->_ID;
           pCFGExPtr->wCfgID = pCFG->_ConfigID;
           pCFGExPtr->wType  = pCFG->_Type;
           pCFGExPtr->wOpenAct  = pCFG->_Stye;
           pCFGExPtr->CopyFrom(*pCFG);
           
           _mapID2WActInfo.insert(make_pair(pCFGExPtr->wID,pCFGExPtr));
           _mapID2ActivityOperatingCFG.insert(make_pair(pCFG->_ID, *pCFG)); 
           
           CWonderActivityEventPtr pWActEventPtr(new CWonderActivityEvent(pCFGExPtr->wID,pCFGExPtr->wType));
           _mapID2WActEvent.insert(make_pair(pCFGExPtr->wID,pWActEventPtr));
           //不需要在精彩活动面板中显示的活动  请自己注册
           AddActIDToNotSend(pCFGExPtr->wID,pCFGExPtr->wType);
        }
    }
    RegisterAct();
    
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
          SWActConfigCFGPtr pConfigPtr(new SWActConfigCFG);
          pConfigPtr->wConfigID = pCfg->_ID;
          pConfigPtr->wType = pCfg->_Type;
          pConfigPtr->wMailID = pCfg->_MailTitle;
          pConfigPtr->wMailContentID = pCfg->_MailContent;
          ParseConfigInfo(pConfigPtr->wConfigID,pConfigPtr->vecWActPrizePtr,pCfg->_TypePara1,pCfg->_TypePara2);
          pConfigPtr->CopyFrom(*pCfg);
          _mapID2WActCfg.insert(make_pair(pConfigPtr->wConfigID,pConfigPtr));
        }
    }
    //加载配置成功
    _bConfigReady = true; 
    return true;
}

bool CWonderActivityMgr::ReLoadConfig(const string &strFile)
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

        //_mapID2WActEvent.clear();
        for(size_t i = 0; i < oLoader._vecData.size(); ++i)
        {
            SActivityOperatingCFG* pCFG = oLoader._vecData[i];
            if(pCFG)
            {
                if(IsAllowReload(pCFG->_ID,1))
                {
                    SWActCFGExPtr pCFGExPtr(new SWActCFGEx);
                    pCFGExPtr->wID = pCFG->_ID;
                    pCFGExPtr->wCfgID = pCFG->_ConfigID;
                    pCFGExPtr->wType  = pCFG->_Type;
                    GetTimerInfo(pCFGExPtr->sAdvanceTime,pCFG->_Time1);
                    GetTimerInfo(pCFGExPtr->sBeginTime,pCFG->_Time2);
                    GetTimerInfo(pCFGExPtr->sEndTime,pCFG->_Time3);
                    GetTimerInfo(pCFGExPtr->sRetainTime,pCFG->_Time4);
                    pCFGExPtr->CopyFrom(*pCFG);
                
                    _mapID2WActInfo.insert(make_pair(pCFGExPtr->wID,pCFGExPtr));
                    CWonderActivityEventPtr pWActEventPtr(new CWonderActivityEvent(pCFGExPtr->wID,pCFGExPtr->wType));
                    _mapID2WActEvent.insert(make_pair(pCFGExPtr->wID,pWActEventPtr));

                    _mapID2ActivityOperatingCFG.insert(make_pair(pCFG->_ID, *pCFG)); 
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
                  SWActConfigCFGPtr pConfigPtr(new SWActConfigCFG);
                  pConfigPtr->wConfigID = pCfg->_ID;
                  pConfigPtr->wType = pCfg->_Type;
                  pConfigPtr->wMailID = pCfg->_MailTitle;
                  pConfigPtr->wMailContentID = pCfg->_MailContent;

                  ParseConfigInfo(pConfigPtr->wConfigID,pConfigPtr->vecWActPrizePtr,pCfg->_TypePara1,pCfg->_TypePara2);
                  pConfigPtr->CopyFrom(*pCfg);
                  _mapID2WActCfg.insert(make_pair(pConfigPtr->wConfigID,pConfigPtr));
              }
            }
        }
    }

    return true;
}

bool CWonderActivityMgr::IsAllowReload(UINT16 wID,UINT8 byFlag /* 1表示判断配置表，2表示判断奖励配置表 */ )
{ 
    if(byFlag == 1)
    {
        auto oIt = _mapID2WActInfo.find(wID);
        if(oIt == _mapID2WActInfo.end())
            return true;
        UINT16 wType = GetTypeByActID(wID);
        if(wType == 0)
            return true;
        auto it = _mapID2WAct.find(wType);
        if(it == _mapID2WAct.end())
        {
            LOG_CRI << " Not Find Instance for ActivityID = " << wID;
            return false;
        }
        if(it->second->GetState() == eWActState_Begin)
        {
            LOG_INF << " Activity is beginning , Config can't reload! ActID = " << wID;
            return false;
        }
        //return true;
   }else if(byFlag == 2)
   {
        auto oIt = _mapID2WActCfg.find(wID);
        if(oIt == _mapID2WActCfg.end())
            return true;
        for(auto it = _mapID2WActInfo.begin(); it!=_mapID2WActInfo.end(); ++it)
        {
            if(wID == it->second->wCfgID)
            {
                auto rIt = _mapID2WAct.find(it->second->wType);
                if(rIt == _mapID2WAct.end())
                {
                    LOG_CRI << " Not Find Instance for ActivityID = " << wID;
                    return true;
                }
                if(rIt->second->GetState() == eWActState_Begin)
                {
                    LOG_INF << " Cofig  is used by Activity , It can't reload! ConfigID = " << wID;
                    return false;
                }
            }
        }

   }
   return true;
}

#if 0
//prizeString: 1|2,10|11,50|51,200
//ItemString : 200,50;201,100|200,50;201,100;202,30
bool CWonderActivityMgr::ParseConfigInfo(UINT16 wConfigID,TVecPrizeCFGPtr &rVecPrizePtr,string &rPrizeString,string &rItemString)
{
    UINT32 dwIndex = 1;
    Tokenizer tkPrizeStr_1(rPrizeString,"|");
    Tokenizer tkItemStr_1(rItemString, "|");
    if(tkItemStr_1.size() != tkPrizeStr_1.size())
    {
        LOG_INF << "WonderActivity Config Error,ConfigID = "<< wConfigID<<",PrizeString="<<rPrizeString<<",ItemString="<<rItemString;
        return false;
    }

    for(UINT8 it=0 ; it<tkPrizeStr_1.size() ; ++it)
    {
        SWActPrizeCFGPtr pPrizeCfg(new SWActPrizeCFG);
        Tokenizer tkPrizeStr_2(tkPrizeStr_1[it],",");
        if(tkPrizeStr_2.size() == 1)
        {
           if(tkPrizeStr_3.size() > 1)
           {
               LOG_INF <<" ConfigError ,Check Tokenize[.]";
               return false;
           }
           pPrizeCfg->wLow =  pPrizeCfg->wHigh = atoi(tkPrizeStr_2[0].c_str());
        }else
        {
            Tokenizer tkPrizeStr_3(tkPrizeStr_2[0],".");
            if(tkPrizeStr_3.size() > 1)
            {
                pPrizeCfg->wHigh = dwIndex;
                for(UINT8 i=0; i<tkPrizeStr_3.size(); ++i)
                {
                     pPrizeCfg->vecTrumpID.push_back(atoi(tkPrizeStr_3[i].c_str()));
                }
                ++dwIndex;
            }else
                pPrizeCfg->wHigh = atoi(tkPrizeStr_2[0].c_str());
            pPrizeCfg->wLow  = atoi(tkPrizeStr_2[1].c_str());
        }
        Tokenizer tkItemStr_2(tkItemStr_1[it],";");
        for(UINT8 byIt=0; byIt<tkItemStr_2.size(); ++byIt)
        {
            Tokenizer tkItemStr_3(tkItemStr_2[byIt],",");
            SItemConfigPtr sItem(new SItemConfig);
            sItem->dwItemID = atoi(tkItemStr_3[0].c_str());
            sItem->dwCount = atoi(tkItemStr_3[1].c_str());
            pPrizeCfg->vecItem.push_back(sItem);
        }
       rVecPrizePtr.push_back(pPrizeCfg); 
    }
    return true;
}

#endif

bool CWonderActivityMgr::ParseConfigInfo(UINT16 wConfigID,TVecPrizeCFGPtr &rVecPrizePtr,string &rPrizeString,string &rItemString)
{
    Tokenizer tkPrizeStr_1(rPrizeString,"|");
    Tokenizer tkItemStr_1(rItemString, "|");
    if(tkItemStr_1.size() != tkPrizeStr_1.size())
    {
        LOG_INF << "WonderActivity Config Error,ConfigID = "<< wConfigID<<",PrizeString="<<rPrizeString<<",ItemString="<<rItemString;
        return false;
    }

    for(UINT8 it=0 ; it<tkPrizeStr_1.size() ; ++it)
    {
        SWActPrizeCFGPtr pPrizeCfg(new SWActPrizeCFG);
        Tokenizer tkPrizeStr_2(tkPrizeStr_1[it],",");
        if(tkPrizeStr_2.size() == 1)
        {
            pPrizeCfg->wLow =  pPrizeCfg->wHigh = atoi(tkPrizeStr_2[0].c_str());

        }else
        {
            pPrizeCfg->wHigh = atoi(tkPrizeStr_2[0].c_str());
            pPrizeCfg->wLow  = atoi(tkPrizeStr_2[1].c_str());
        }
        Tokenizer tkItemStr_2(tkItemStr_1[it],";");
        for(UINT8 byIt=0; byIt<tkItemStr_2.size(); ++byIt)
        {
            Tokenizer tkItemStr_3(tkItemStr_2[byIt],",");
            SItemConfigPtr sItem(new SItemConfig);
            sItem->dwItemID = atoi(tkItemStr_3[0].c_str());
            sItem->dwCount = atoi(tkItemStr_3[1].c_str());
            pPrizeCfg->vecItem.push_back(sItem);
        }
       rVecPrizePtr.push_back(pPrizeCfg); 
    }
    return true;
}
void  CWonderActivityMgr::RegisterAct()
{
#define REGISTERACTIVITY(eActType,eClassType,name) { \
    static eClassType name(eActType); \
    _mapID2WAct[eActType] = &name; }

#define REGISTERACTIVITYBYTYPE(eActType,eClassType,name,byType) { \
    static eClassType name(eActType,byType); \
    _mapID2WAct[eActType] = &name; }
    
    REGISTERACTIVITY(eWActType_RANKPOINT,CPointRank,g_PointRank);
    REGISTERACTIVITY(eWActType_LEVELACT,CLevelActMgr,g_LevelActMgr);
    REGISTERACTIVITY(eWActType_POINT,CPointActMgr,g_PointActMgr);
    REGISTERACTIVITY(eWActType_OpenBuy,COpenAct,g_OpenAct);
    
    REGISTERACTIVITY(eWActType_RANKLEVEL,CLevelRank,g_LevelRankAct);
    REGISTERACTIVITY(eWActType_RANKFIGHTER,CFighterRank,g_FighterRankAct);
    REGISTERACTIVITY(eWActType_RANKPET,CPetRank,g_PetRankAct);
    REGISTERACTIVITY(eWActType_RANKARENA,CArenaRank,g_ArenaRankAct);
    REGISTERACTIVITY(eWActType_RANKGUILD,CGuildRank,g_GuildRankAct);
    REGISTERACTIVITY(eWActType_RANKTRUMP,CTrumpRank,g_TrumpRankAct);
    REGISTERACTIVITY(eWActType_TRUMP,CTrumpAct,g_TrumpAct);
    REGISTERACTIVITY(eWActType_QQCOIN,CQQCoinAct,g_QQCoinAct);
    REGISTERACTIVITY(eWActType_BEAUTYACT,CBeautyActMgr,g_BeautyActMgr);
    REGISTERACTIVITY(eWActType_HORSEACT,CHorseActMgr,g_HorseActMgr);
     
    //根据类型定义活动 
    REGISTERACTIVITYBYTYPE(eWActType_DUNGON,CTotalActMgr,g_DungonActMgr,NGame2CenterComm::eActDungon);
    REGISTERACTIVITYBYTYPE(eWActType_FIGHTER,CTotalActMgr,g_FighterActMgr,NGame2CenterComm::eActFighter);
    REGISTERACTIVITYBYTYPE(eWActType_FORMATION,CTotalActMgr,g_FormationActMgr,NGame2CenterComm::eActFormation);
}

void CWonderActivityMgr::OpenActivity(UINT16 &wActID,string sAdv,string sBegin,string sEnd,string sRetain)
{
    UINT16 wType = GetTypeByActID(wActID);
    if(wType == 0)
        return;
    auto it = _mapID2WAct.find(wType);
    SWActTime sAdvTime;
    SWActTime sBeginTime;
    SWActTime sEndTime;
    SWActTime sRetainTime;
    if(it != _mapID2WAct.end())
    {
        GetTimerInfo(sAdvTime,sAdv);
        GetTimerInfo(sBeginTime,sBegin);
        GetTimerInfo(sEndTime,sEnd);
        GetTimerInfo(sRetainTime,sRetain);
        it->second->GMOpen(sAdvTime,sBeginTime,sEndTime,sRetainTime);
    }

}
EWActResult CWonderActivityMgr::GetPlayerInfo(UINT64& qwUserID,bool bType,UINT16 &wActID,SWActPlayerInfo& sPlayer)
{
    EWActResult eResult;
    UINT16 wType = GetTypeByActID(wActID);
    if(wType == 0)
        return eWActResult_none;
    auto oIt = _mapID2WActInfo.find(wActID);
    if(oIt == _mapID2WActInfo.end())
    {
        return eWActResult_none;
    }
    auto rIt = _mapID2WAct.find(wType);
    if(rIt == _mapID2WAct.end())
    {
        return eWActResult_none;
    }
    bool bRet = rIt->second->GetPlayerInfo(bType,qwUserID,wType,sPlayer);
    if(!bRet)
    {
       LOG_INF <<" Get PlayerInfo Error! bType = " << bType << " | qwRoleID = " << qwUserID ;
       eResult = eWActResult_error;
    }
    return eResult;
}
EWActResult CWonderActivityMgr::GetPrizeInfo(UINT16& wActID, EWActPrizeType eType, TVecItemConfig &vecItem)
{
    EWActResult eResult = eWActResult_error;
    UINT8 byIndex = 0;
    auto oIt = _mapID2WActInfo.find(wActID);
    if(oIt == _mapID2WActInfo.end())
    {
        return eWActResult_none;
    }
    switch(eType)
    {
        case eWActPrizeType_first:
            {
                byIndex = 0;
                eResult = GetPrize(wActID,byIndex,vecItem);
            }
            break;
        case eWActPrizeType_one:
            {
                byIndex = 1;
                eResult = GetPrize(wActID,byIndex,vecItem);

            }
            break;
        case eWActPrizeType_two:
            {
                byIndex = 2;
                eResult = GetPrize(wActID,byIndex,vecItem);

            }
            break;
        case eWActPrizeType_three:
            {
                byIndex = 3;
                eResult = GetPrize(wActID,byIndex,vecItem);
            }
            break;
        default:
            break;
    }
    return eResult;
}

EWActResult CWonderActivityMgr::GetPrize(UINT16& wActID, UINT8& byIndex, TVecItemConfig &vecItems)
{
   auto oIt = _mapID2WActInfo.find(wActID);
   if(oIt == _mapID2WActInfo.end())
   {
       return eWActResult_none;
   }
  
   auto cIt = _mapID2WActCfg.find(oIt->second->wCfgID);
   if(cIt == _mapID2WActCfg.end())
   {
       return eWActResult_none;
   }
   if(byIndex >=  cIt->second->vecWActPrizePtr.size())
   {
       return eWActResult_error;
   }
   SWActPrizeCFGPtr pPrize = cIt->second->vecWActPrizePtr.at(byIndex);
   TVecItemConfigPtr pItems = pPrize->vecItem;
   for(auto it=pItems.begin(); it!=pItems.end(); ++it)
   {
      SItemConfig sItem;
      sItem.dwItemID = (*it)->dwItemID;
      sItem.dwCount = (*it)->dwCount;
      vecItems.push_back(sItem);
   }
  return eWActResult_success; 
}

EWActResult CWonderActivityMgr::GetAllPrize(UINT16& wActID, TVecPrizeConfig &vecItemConfig)
{
    auto oIt = _mapID2WActInfo.find(wActID);
    if(oIt == _mapID2WActInfo.end())
    {
       return eWActResult_none;
    }
    for(UINT8 it=0; it!=static_cast<UINT8>(eWActPrizeType_MAX) - 1; ++it)
    {
        SPrizeConfig sConfig;
        sConfig.ePrizeType = static_cast<EWActPrizeType>(it + 1);
        EWActResult eResult =  GetPrize(wActID,it,sConfig.vecItems);
        if(eResult != eWActResult_success)
        {
             LOG_INF << "wActID = " << wActID<<" |  PrizeID = [ " << it + 1  << " ] Error";
             continue;
        }
        vecItemConfig.push_back(sConfig);
    }

    return eWActResult_success;
}
EWActResult CWonderActivityMgr::GetAllTime(UINT16& wActID, STime &st)
{
    auto oIt = _mapID2WActInfo.find(wActID);
    if(oIt == _mapID2WActInfo.end())
    {
       return eWActResult_none;
    }
    st.wWActID = oIt->second->wID;
    st.dwAdvTime = GetDayTime(oIt->second->sAdvanceTime);
    st.dwBeginTime = GetDayTime(oIt->second->sBeginTime);
    st.dwEndTime = GetDayTime(oIt->second->sEndTime);
    st.dwRetainTime = GetDayTime(oIt->second->sRetainTime);

    return eWActResult_success;
}

EWActResult CWonderActivityMgr::GetActList(TVecTime& vecTimes) 
{
    time_t tNow = time(NULL);
    auto oIt = _mapID2WActInfo.begin();
    for(; oIt!=_mapID2WActInfo.end(); ++oIt)
    {
        STime st;
        st.wWActID = oIt->second->wID;
        st.dwAdvTime = GetDayTime(oIt->second->sAdvanceTime);
        st.dwBeginTime = GetDayTime(oIt->second->sBeginTime);
        st.dwEndTime = GetDayTime(oIt->second->sEndTime);
        st.dwRetainTime = GetDayTime(oIt->second->sRetainTime);
        if(tNow >= st.dwAdvTime && tNow <= st.dwRetainTime)
        {
            if(CheckActID(st.wWActID))
            {
                vecTimes.push_back(st);
            }
        }
    }

    return eWActResult_success;
}

bool CWonderActivityMgr::CheckActID(UINT16 wActID)
{
    auto it = _setActID.find(wActID);
    if(it != _setActID.end())
        return false;
    return true;
}

void CWonderActivityMgr::TakePrize(UINT64 &qwRoleID, UINT16& wActID,UINT32 &wCond) 
{
    UINT16 wType = GetTypeByActID(wActID);
    if(wType == 0)
        return ;
    CWonderActivity *pAct = GetWAct(wType);
    if(pAct)
        pAct->TakePrize(qwRoleID,wCond);
}

EWActResult CWonderActivityMgr::ExChange(CUser& rUser,UINT8 byType)
{
    EWActResult eResult = eWActResult_error;
    UINT16 wType = eWActType_QQCOIN;
    CWonderActivity *pAct = GetWAct(wType);
    CQQCoinAct *pTmp = dynamic_cast<CQQCoinAct*>(pAct);
    if(pTmp)
       eResult = pTmp->OnExChange(rUser,byType);
    return eResult;
}

void CWonderActivityMgr::SetPoolValue(UINT8 byType,UINT32 dwValue)
{
    UINT16 wType = eWActType_QQCOIN;
    CWonderActivity *pAct = GetWAct(wType);
    CQQCoinAct *pTmp = dynamic_cast<CQQCoinAct*>(pAct);
    if(pTmp)
    {
        if(byType == 0)
           pTmp->ResetPoolValue(dwValue);
        else if(byType == 1)
           pTmp->ResetCurValue(dwValue);
    }
}

bool CWonderActivityMgr::IsRun(UINT16 wActID)
{
    bool bRun = false;
    UINT16 wType = GetTypeByActID(wActID);
    CWonderActivity *pAct = GetWAct(wType);
    CQQCoinAct *pTmp = dynamic_cast<CQQCoinAct*>(pAct);
    if(pTmp)
    {
        bRun = pTmp->IsRetain(); 
    }
    return bRun;
}

void CWonderActivityMgr::SyncCoinInfo(CUser& rUser)
{
    UINT16 wType = eWActType_QQCOIN;
    CWonderActivity *pAct = GetWAct(wType);
    CQQCoinAct *pTmp = dynamic_cast<CQQCoinAct*>(pAct);
    if(pTmp)
        pTmp->OnSyncInfo(rUser);
}

void CWonderActivityMgr::GetRoleActInfo(UINT64 &qwRoleID, UINT16& wActID,TVecRoleStatus &vecRet)
{
    UINT16 wType = GetTypeByActID(wActID);
    if(wType == 0)
        return ;
    CWonderActivity *pAct = GetWAct(wType);
    if(pAct)
        pAct->GetRoleStateByActID(qwRoleID,wActID,vecRet);
}

void CWonderActivityMgr::OneMinCheck(time_t tNow)
{
    for(auto oIt=_mapID2WActEvent.begin(); oIt!=_mapID2WActEvent.end(); ++oIt)
    {
        if(oIt->second->IsInitTime(tNow))
        {
            oIt->second->OnInit();
        }
    }
    InitReachActID();
    CheckReachActID();
}

void CWonderActivityMgr::TimerCheck(time_t tNow)
{
    if(_bInitCheck)
    {
        if(!CheckActivityVar())
        {
            LOG_INF <<"SystemVar not Ready.";
            return;
        }
        if(!_bConfigReady)
        {
            if(!LoadConfig())
            {
                LOG_INF <<" Load Config Err.";
                return;
            }
        }
        if(!InitTimeForAct())
        {
            LOG_INF <<"InitTime for WonderActivity Err.";
            return;
        }
        if(!Config.AllServerIsReady()) 
        {
            return;
        }
        for(auto oIt=_mapID2WActEvent.begin(); oIt!=_mapID2WActEvent.end(); ++oIt)
        {
            oIt->second->CheckStatus();
        }
        InitReachActID(); 
        _bInitCheck = false;
        return;
    }
    for(auto it=_mapID2WAct.begin(); it!=_mapID2WAct.end(); ++it)
    {
        if(NULL != it->second)
        {
            it->second->UpdateState();
        }
    }
}

void CWonderActivityMgr::CheckReachActID()
{
    for(size_t i = 0; i < _vecActID2Cond.size();)
    {
        SActID2Cond& rInfo = _vecActID2Cond[i];
        if(rInfo.wActID == 0 || rInfo.dwCond == 0)
            continue;
        UINT16 wType = GetTypeByActID(rInfo.wActID);
        if(wType == 0)
            continue;
        CWonderActivity *pAct = GetWAct(wType);
        if(pAct)
        {
           if(pAct->CheckConds(rInfo.dwCond))
           {
              g_WonderActivityProtS.SendClt_SendReachCondNtf(NULL,0,rInfo.wActID, rInfo.dwCond);
              _vecActID2Cond.erase(_vecActID2Cond.begin() + i);
              continue;
           }
        }
        ++i;
    }
}

SWActCFGExPtr CWonderActivityMgr::GetConfigEx(UINT16 wWActID)
{
    auto oIt = _mapID2WActInfo.find(wWActID);
    if(oIt != _mapID2WActInfo.end())
    {
        return oIt->second;
    }
    return NULL;
}

CWonderActivity* CWonderActivityMgr::GetWAct(UINT16 wWActID)
{
    auto oIt = _mapID2WAct.find(wWActID);
    if(oIt != _mapID2WAct.end())
    {
        return oIt->second;
    }
    return NULL;
}
CWonderActivityEventPtr CWonderActivityMgr::GetWActEvent(UINT16 wWActID)
{
    auto oIt = _mapID2WActEvent.find(wWActID);
    if(oIt != _mapID2WActEvent.end())
    {
        return oIt->second;
    }
    return NULL;

}
SWActConfigCFGPtr CWonderActivityMgr::GetPrizeConfig(UINT16 wPrizeConfigID) 
{
    auto oIt = _mapID2WActCfg.find(wPrizeConfigID);
    if(oIt != _mapID2WActCfg.end())
    {
        return oIt->second;
    }
    return NULL;

}

UINT16 CWonderActivityMgr::GetTypeByActID(UINT16& wActID)
{
    SWActCFGExPtr pInfo = GetConfigEx(wActID);
    if(pInfo == NULL)
        return 0;
    return pInfo->wType;
}

void  CWonderActivityMgr::LoadFromDB()
{
    g_Center2DBCommC.Send_GetPrizeStatus([this](UINT8 byRet_, const NWonderActivityProt::TVecWonderPrize2DB& vecRet)
            {
                if(0 == byRet_)
                {
                       g_WonderActivityMgr.OnLoad(vecRet);
                }
            });
}

void CWonderActivityMgr::OnLoad(const TVecWonderPrize2DB& vecData)
{
      for(auto &oIt : vecData)
      {
          SWonderPrizeKey oKey(oIt.qwRoleID,oIt.wActID,oIt.wCond);
          _mapID2PrizeState.insert(make_pair(oKey,oIt));
      }
}

void CWonderActivityMgr::LoadRoleLevelData()
{
   for(UINT8 byType=1; byType!=NGame2CenterComm::eActEnd; ++byType)
   {
       g_Center2DBCommC.Send_GetAllRoleLevel(byType,[](UINT8 byRet_, UINT8 byTypeRet,const TVecRoleLevel& vecRoleLevel)
       {
            if(0 == byRet_)
            {
                   CUserMgr::SetRoleInfos(byTypeRet,vecRoleLevel);                
            }
       });
   
   }
}

void CWonderActivityMgr::OnSuccess(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL)
        return;
    NWonderActivityProt::SWonderPrize2DB sPrize2DB;
    sPrize2DB.qwRoleID = qwRoleID;
    sPrize2DB.wActID = wActID;
    sPrize2DB.wCond = wCond;
    sPrize2DB.byStatus = 2;
    g_Center2DBCommC.Send_UpdatePrizeStatus(sPrize2DB,eOpAdd);
    pUser->SendPkg(g_WonderActivityProtS.BuildPkg_SendTakePrizeNtf(wActID,wCond,eGainResult_alreadyGain));

    SWonderPrizeKey oKey(qwRoleID,wActID,wCond);
    auto oIt = _mapID2PrizeState.find(oKey);
    if(oIt == _mapID2PrizeState.end())
    {
         _mapID2PrizeState.insert(make_pair(oKey,sPrize2DB));
    }else
    {
        oIt->second.byStatus = 2;
    }
}

TMapID2PrizeState& CWonderActivityMgr::GetMapID2PrizeState()
{
    return _mapID2PrizeState;
}

UINT8 CWonderActivityMgr::GetPrizeStateByRoleID(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
{
    SWonderPrizeKey oKey(qwRoleID,wActID,wCond);
    auto oIt = _mapID2PrizeState.find(oKey);
    if(oIt == _mapID2PrizeState.end())
        return 0;
    else 
        return 2;
}

void  CWonderActivityMgr::InitReachActID() //初始化需要通知的活动和条件
{
   UINT16 wType = 0;
   UINT16 wActID = 0;
   if(!_mapID2WActInfo.size())
   {
       LOG_INF << " _mapID2WActInfo size is 0.";
       return;
   }
   for(auto &oIt : _mapID2WActInfo)
   {
        SWActCFGExPtr pInfo = oIt.second;
        if(!pInfo)
        {
            LOG_INF <<" pInfo Null.";
            continue;
        }
        wActID = pInfo->wID;
        wType = pInfo->wType;
        if(!wActID || !wType)
        {
            LOG_INF << " wActID || wType Error.";
            continue;
        }
        UINT16 wServerType = GetServerType(wActID);
        if(wServerType == 0)
            continue;
        if(wServerType != 1)
            continue;
        CWonderActivity *pAct = GetWAct(wType);
        if(!pAct)
        {
            //LOG_INF << "pAct Null.";
            continue;
        }
        TVecUINT32 vecConds;
        pAct->GetConds(vecConds);
        if(vecConds.size() == 0)
        {
           // LOG_INF <<"wActID("<<wActID<<") vecConds size 0.";
            continue;
        }
        for(auto &it : vecConds)
        {
            SActID2Cond sActID2Cond;
            sActID2Cond.wActID = wActID;
            sActID2Cond.dwCond = it;
            if(IsFined(sActID2Cond))
                continue;
            if(!pAct->CheckConds(it))
            {
                _vecActID2Cond.push_back(sActID2Cond); 
            } 
        }
   }
}

bool CWonderActivityMgr::IsFined(SActID2Cond &sTmp)
{
    for(auto &it : _vecActID2Cond)
    {
        if(it.wActID == sTmp.wActID 
           && it.dwCond == sTmp.dwCond)
            return true;
    }
    return false;
}

void CWonderActivityMgr::GetRoleAllState(UINT64& qwRoleID,TVecRoleAllStatus& vecRet)
{
     TVecTime vecTimes;
     if(eWActResult_success != GetActList(vecTimes))
     {
         LOG_INF << " GetActList error";
         return;
     }
     UINT16 wActID = 0;
     for(auto &oIt : vecTimes)
     {
        SRoleAllStatus  oTmp;
        wActID = oIt.wWActID;
        if(!wActID)
        {
            LOG_INF<< " wActID is 0.";
            continue;
        }
        UINT16 wServerType = GetServerType(wActID);
        if(wServerType == 0)
            continue;
        if(wServerType != 1)
            continue;
        oTmp.wActID = wActID;
        UINT16 wType = GetTypeByActID(wActID);
        if(!wType)
        {
            LOG_INF << " wType 0.";
            continue;
        }
        GetRoleActInfo(qwRoleID,wActID,oTmp.vecAllState);
        vecRet.push_back(oTmp);
     }
}

UINT16 CWonderActivityMgr::GetServerType(UINT16 wActID)
{
    SWActCFGExPtr pInfo = GetConfigEx(wActID);
    if(!pInfo)
        return 0;
    else
        return pInfo->_TotalType;
}

void  CWonderActivityMgr::GetOpenServerTime(UINT32& dwTime,bool& bOpen)
{
    dwTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVarOpenServerActivity);
    if(!dwTime)
    {
        LOG_INF <<" SystemVar Not Ready.";
        bOpen = false;
    }
    else 
        bOpen = true;
}


SActivityOperatingCFG* CWonderActivityMgr::GetActivityOperatingCFG(UINT16 wActID)
{
    auto it = _mapID2ActivityOperatingCFG.find(wActID);
    if(it != _mapID2ActivityOperatingCFG.end())
        return &it->second;

    return NULL;
}

//不需要在精彩活动面板中显示的活动  请自己注册
void CWonderActivityMgr::AddActIDToNotSend(UINT16 wActID,UINT16 wType)
{
    if(wType == eWActType_QQCOIN 
        || wType == eWActType_OpenBuy
       )
        _setActID.insert(wActID);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

