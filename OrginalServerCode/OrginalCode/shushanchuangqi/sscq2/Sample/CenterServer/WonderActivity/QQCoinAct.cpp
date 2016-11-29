#include "stdafx.h"
#include "Protocols.h"
#include "QQCoinAct.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "RankMgr.h"
#include "WonderActivityMgr.h"
#include "Parameter.h"
#include "ProtoCommon.h"
#include "UDPLog.h"
///////////////////////////////////
const static UINT32 RATE = 100;
const char   *pCategory = "hulingz";
const char   *pActionCount = "s2_150427_57";
const char   *pActionValue = "s2_150427_59";
/////////////////////////////////////////////
CQQCoinAct::CQQCoinAct(UINT16 wType) : CWonderActivity(wType)
{
    time_t tNow = time(NULL);
    _dwInstTime = static_cast<UINT32>(tNow);
    _bStart = true; 
    _byQQLv = 60;
    _byGoldLv = 30;
    _wLv2Coupon = 10;
    _wCoupon2Gold = 10;
    _wCoupon2QQ = 1;
    _byMinLv = 60;
    _byInterval = 5;
    _fRate = 0.1;
}

bool CQQCoinAct::OnSyncInfo(CUser& rUser)
{
    UINT32 dwTmp = 0; 
    bool bRun = false;
    bRun = IsRun(dwTmp);
    if(!bRun || !dwTmp)
    {
        LOG_INF<<"QQCoin Act End.";
        return false;
    }
    CCenterVar& rVar = rUser.GetCenterVar();
    UINT8 byPrizeLevel = static_cast<UINT8>(rVar.GetVar(NVarDefine::ePlayerQQCoinLevel));
    SQQCoinActInfo oInfo;
    oInfo.dwTime = dwTmp;
    oInfo.byLevel = byPrizeLevel;
    oInfo.dwMaxValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinMaxValue);
    oInfo.dwCurValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinConsumeValue);
    rUser.SendPkg(g_WonderActivityProtS.BuildPkg_SyncQQCoinInfo(oInfo));
    return true; 
}
bool CQQCoinAct::IsRetain()
{
    if( _dwAdvanceTime < time(NULL)  && time(NULL) < _dwRetainTime)
        return true;
    return false;
}

bool CQQCoinAct::IsRun(UINT32& dwTime)
{
    bool bRun = false;
    if(GetState() == eWActState_Begin)
        bRun = true;
    dwTime = _dwEndTime;
    return bRun;
}

void CQQCoinAct::InitParam()
{
    _byQQLv = SParamConfig::bybyMinQQLv;
    _byGoldLv = SParamConfig::bybyMinGoldLv;
    _fRate = (((float)SParamConfig::bybyRate) / RATE);
    _wLv2Coupon = SParamConfig::wLevel2QQCoupon;
    _wCoupon2QQ = SParamConfig::wQQCoupon2QQCoin;
    _wCoupon2Gold = SParamConfig::wQQCoupon2Gold;
    _byInterval = SParamConfig::byMinInterval;
    _byMinLv = SParamConfig::bybyMinLv;
}

void CQQCoinAct::ResetPoolValue(UINT32 dwCount)
{
    g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinMaxValue,dwCount);
}

void CQQCoinAct::ResetCurValue(UINT32 dwCount)
{
    g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinConsumeValue,dwCount);
}

void CQQCoinAct::SpecialProcess()
{
   bool bRun = false;
   UINT32 dwTmp = 0;
   bRun = IsRun(dwTmp);
   if(!bRun || !dwTmp)
       return;
   if(_bStart)
   {
       InitParam();
       LOG_INF<<"Server starts firstly.";
       _bStart = false;
   }

   time_t tNow = time(NULL);
   UINT32 dwNow = static_cast<UINT32>(tNow);
   dwTmp = dwNow - _dwInstTime;
   if(dwTmp > _byInterval * 60)
   {
       _dwInstTime += _byInterval * 60;
       TimerCheck();
   }
}

void CQQCoinAct::TimerCheck()
{
   bool bGet = false;
   UINT16 wMaxLevel = 0;
   wMaxLevel = CRankMgr::Instance().GetFirstLevel();
   if(wMaxLevel >= _byMinLv)
       bGet = true;
   if(bGet)
   {
       UINT32 dwMaxValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinMaxValue);
       dwMaxValue *= _fRate;
       UINT32 dwTmp = 0;
       UINT32 dwConsumeValue = static_cast<UINT32>(g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinConsumeValue));
       if(dwConsumeValue == 0)
           return;
       if(dwConsumeValue <= dwMaxValue)
           dwTmp = 0;
       else if(dwConsumeValue > dwMaxValue)
           dwTmp = dwConsumeValue - dwMaxValue;
       g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinConsumeValue,dwTmp);
   }
}

EWActResult CQQCoinAct::OnExChange(CUser &rUser,UINT8 byType)
{
    bool bRun = false;
    UINT32 dwTime = 0;
    bRun = IsRun(dwTime);
    if(!bRun || !dwTime)
    {
        LOG_INF<<"Act End.";
        return eWActResult_error;
    }
    CCenterVar& rVar = rUser.GetCenterVar();
    UINT64 qwRoleID = rUser.GetRoleID();
    UINT8 byCurLv = rUser.GetLevel(); 
    UINT8 byLv = rVar.GetVar(NVarDefine::ePlayerQQCoinLevel);
    if(byLv >= byCurLv)
    {
        LOG_INF << "No ExChange.";
        OnSyncInfo(rUser);
        return eWActResult_error;
    }
    UINT32 dwCoupon = 0;
    UINT32 dwConsumeValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinConsumeValue);
    dwCoupon = (byCurLv - byLv) * _wLv2Coupon;
    if(dwConsumeValue == 0)
    {
        LOG_INF<<"PrizePool size 0.";
        return eWActResult_error;
    }
    if(dwConsumeValue < dwCoupon)
    {
        LOG_INF<<"PrizePool size < dwCoupon";
        dwCoupon = dwConsumeValue;
    }
    TVecUserItem vecUserItem;
    UINT32 dwTmp = 0;
    UINT32 dwServerID = rUser.GetGameSvrID();
    if(byType == 1)
    {
       if(_byGoldLv > byCurLv)
       {
           LOG_INF<<"Gold exchanges for lacking lv.";
           OnSyncInfo(rUser);
           return eWActResult_error;
       }
       dwTmp = (dwCoupon * _wCoupon2Gold) / RATE;
       SUserItem oUserItem;
       oUserItem.dwTypeID = NProtoCommon::EMONEY_COUPON; //发放礼券
       oUserItem.dwCount =  dwTmp;
       vecUserItem.push_back(oUserItem);
       g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemFrom_QQCoinExChange,vecUserItem,
       [this,qwRoleID,dwCoupon,dwTmp](UINT8 byRet_, UINT8 byError)
       {
              if(byRet_ || byError)
              {
                  LOG_INF << "BagFull";
                  return;
              }
              CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
              if(pUser)
              {
                   CCenterVar& rVar = pUser->GetCenterVar();
                   UINT8 byCurLv = pUser->GetLevel();
                   UINT32 dwConsumeValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinConsumeValue);
                   rVar.SetVar(NVarDefine::ePlayerQQCoinLevel,byCurLv);
                   g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinConsumeValue,dwConsumeValue-dwCoupon);
                   OnSyncInfo(*pUser);
                   
                   //UDP 统计玩家兑换次数和额度
                   UINT32 dwCount = rVar.GetVar(NVarDefine::ePlayerQQCoinExchangeCount);
                   rVar.SetVar(NVarDefine::ePlayerQQCoinExchangeCount,dwCount + 1);

                   UINT32 dwValue = rVar.GetVar(NVarDefine::ePlayerQQCoinExchangeValue);
                   rVar.SetVar(NVarDefine::ePlayerQQCoinExchangeValue,dwValue + dwTmp);

                   SendUDPLog(qwRoleID,dwCount,dwValue);
              }
         });
    }else if (byType == 0)
    {
         if(_byQQLv > byCurLv)
         {
              LOG_INF<<"Lack Level.";
              OnSyncInfo(rUser);
              return eWActResult_error;
         }
    }
    return eWActResult_success;
}
void CQQCoinAct::OnSuc(CUser& rUser,UINT32 dwNeed,UINT8 byLevel)
{
    CCenterVar& rVar = rUser.GetCenterVar();
    UINT32 dwConsumeValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVarQQCoinConsumeValue);
    rVar.SetVar(NVarDefine::ePlayerQQCoinLevel,byLevel);
    g_CenterGameVar.SetVar(NVarDefine::eSystemVarQQCoinConsumeValue,dwConsumeValue-dwNeed);
    OnSyncInfo(rUser);
}

void CQQCoinAct::OnRetain()
{
    CWonderActivity::OnRetain();
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
   
    //通知 Icon消失
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eQQCoinActivity;
    oState.bOpen = false;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState,true);
}
void CQQCoinAct::OnBegin()
{
    CWonderActivity::OnBegin();
    OpenIcon(true);
}

void CQQCoinAct::OpenIcon(bool bNotify)
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
   
    //通知 Icon出现
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eQQCoinActivity;
    oState.bOpen = true;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState,bNotify);
}

void CQQCoinAct::SendUDPLog(UINT64 qwRoleID,UINT32 dwCount,UINT32 dwValue)
{
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
	if(NULL == pUser)
		return;
	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
    {
        pUDPLog->UdpLog(pCategory, pActionCount, NumberToString(dwCount).c_str(), "","","", "act",1);
        pUDPLog->UdpLog(pCategory, pActionValue, NumberToString(dwValue).c_str(), "","","", "act",1);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

