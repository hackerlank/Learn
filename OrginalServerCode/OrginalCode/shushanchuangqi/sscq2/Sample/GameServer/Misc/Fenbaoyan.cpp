#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "Fenbaoyan.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "IconAppearManager.h"

extern CFenbaoyanMgr g_FenbaoyanMgr;
const static UINT32 DAYTIME = 86400;
CFenbaoyanMgr::CFenbaoyanMgr(CPlayer &rPlayer) : 
    _rPlayer(rPlayer)
{
    _bRun = false;
}

static UINT32 CreateTime(UINT32 dwTime)
{
    time_t tNow = static_cast<time_t>(dwTime);
    struct tm *pTm = localtime(&tNow);
    tm oTm = *pTm;
    oTm.tm_hour = 23;
    oTm.tm_min = 59;
    oTm.tm_sec = 58;
    return mktime(&oTm);
}

void CFenbaoyanMgr::OnUserLogin()
{
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    CGameVar &rVar = pUser->GetVars();
    UINT32 dwNote = rVar.GetVar(NVarDefine::ePlayerVarFenbaoyan);
    if(dwNote == 0)
    {
        rVar.SetVar(NVarDefine::ePlayerVarFenbaoyan,static_cast<UINT32>(time(NULL)));
        _bRun = true;
    }
    CheckTime();
}

EMiscOptRes CFenbaoyanMgr::OnBuyFenbaoyan(UINT16 wNum)
{
    EMiscOptRes eRet = eMiscOptRes_Error;
    if(!IsRun() || !wNum) 
    {
        LOG_INF << "Time(" << time(NULL)<<") Fenbaoyan over.";
        return eRet;
    }
    UINT16 wOnePrice = SParamConfig::wTrumpBuyPrice;
    if(wOnePrice == 0)
    {
        LOG_INF<<"wOnePrice is 0.";
        return eRet;
    }
    UINT32 wTotal = wOnePrice * wNum;
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return eRet;
    
    TVecItemGenInfo vecItems;
    SItemGenInfo oInfo;
    oInfo.wItemID = SParamConfig::wTrumpBuyItem;
    oInfo.dwCount = wNum;
	oInfo.eBindType = eBindGet; //绑定类型
    vecItems.push_back(oInfo);
    CPack& oPack = pUser->GetPack();
    if(!oPack.CanAddItem(vecItems))
    {
        LOG_INF<<"PkgFull";
        _rPlayer.SendSysMsg(eMsgPackFullErr);
        return eRet;
    }

    if(!pUser->CanSubMoney(EMONEY_GOLD,wTotal))
    {
        _rPlayer.SendSysMsg(eMsgGoldErr);
        return eRet;
    }
    else
    {
        pUser->SubMoney(EMONEY_GOLD,wTotal,NLogDataDefine::ItemTo_Fenbaoyan);
        oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_Fenbaoyan);
        eRet = eMiscOptRes_Sucess;
    }
   return eRet; 
}

void CFenbaoyanMgr::CheckTime()
{
    UINT16 wDays = SParamConfig::wTrumpBuyTime;
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    UINT32 dwBegin = pUser->GetVars().GetVar(NVarDefine::ePlayerVarFenbaoyan);
    UINT32 dwEnd = dwBegin + wDays * DAYTIME;
    UINT32 dwTmp = CreateTime(dwEnd);
    if(dwTmp <= time(NULL))
    {
        //活动结束
        _bRun = false;
        //看看是否需要
        CloseIcon();
    }else
    {
        _bRun = true;
    }
}

void CFenbaoyanMgr::GetTime(UINT32 &dwBegin,UINT32 &dwEnd)
{
    UINT16 wDays = SParamConfig::wTrumpBuyTime;
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return;
    dwBegin = pUser->GetVars().GetVar(NVarDefine::ePlayerVarFenbaoyan);
    UINT32 dwTmp = dwBegin + wDays * DAYTIME;
    dwEnd = CreateTime(dwTmp);
    LOG_INF<<"Fenbaoyan dwEnd:"<<dwEnd;
}

void CFenbaoyanMgr::CloseIcon()
{
    //关闭图标
    CUserPtr pUser = _rPlayer.GetUserPtr();
    if(!pUser)
        return ;
    CIconAppearMgr::Instance().DelAction(*pUser,111);
    LOG_CRI << " Fenbaoyan over.";
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

