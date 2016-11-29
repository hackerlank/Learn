// =====================================================================================
//
//       Filename:  DragonBallAct.cpp
//
//    Description: 七龙珠活动(连续充值)
//
//        Version:  1.0
//        Created:  01/05/2015 04:24:57 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================

#include "DragonBallActMgr.h"
#include "CenterGameVar.h"
#include "Protocols.h"
#include "VarDefine.h"
#include "Tokenizer.h"
#include "SystemMail.h"
#include "CenterGameVar.h"
#include "WonderActivityProt.h"
#include "Config.h"
#include "ActivityIDProt.h"
#include "ItemProt.h"

using namespace NActivityIDProt;
using namespace NWonderActivityProt;
using namespace NItemProt;

bool CDragonBallActMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/DragonBall.xml";
    CDragonBallLoader oDragonBallLoader;
    if(!oDragonBallLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(size_t i = 0; i < oDragonBallLoader._vecData.size(); ++i)
    {
        SDragonBallCFG* pDragonBallCFG = oDragonBallLoader._vecData[i];
        if(pDragonBallCFG->_cid == 0)
            continue;
        map<UINT8, SDragonBallCFGEx>& rMapDragonBallCFGEx = _mapID2DragonBallCFG[pDragonBallCFG->_cid];
        SDragonBallCFGEx rDragonBallCFGEx;
        rDragonBallCFGEx.SetConfig(*pDragonBallCFG);

        Tokenizer tk(rDragonBallCFGEx._Award, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rDragonBallCFGEx._vecItem.push_back(SItemCount(wItemID, dwItemCount));
            }
        }
        rMapDragonBallCFGEx.insert(make_pair(pDragonBallCFG->_Daytime, rDragonBallCFGEx));
    }

    return true;
}

bool CDragonBallActMgr::ReLoadConfig(const string &strFile)
{
    string strPath;
    if("DragonBall.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/DragonBall.xml";
        CDragonBallLoader oDragonBallLoader;
        if(!oDragonBallLoader.LoadData((strPath)))
        {
            LOG_CRI << "Load " << strPath << "ERR";
            return false;
        }
        for(size_t i = 0; i < oDragonBallLoader._vecData.size(); ++i)
        {
            SDragonBallCFG* pDragonBallCFG = oDragonBallLoader._vecData[i];
            if(pDragonBallCFG->_cid == 0)
                continue;
            map<UINT8, SDragonBallCFGEx>& rMapDragonBallCFGEx = _mapID2DragonBallCFG[pDragonBallCFG->_cid];
            SDragonBallCFGEx rDragonBallCFGEx;
            rDragonBallCFGEx.SetConfig(*pDragonBallCFG);

            Tokenizer tk(rDragonBallCFGEx._Award, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer yatk(tk[j], ",");
                UINT16 wItemID = atoi(yatk[0].c_str());
                if (wItemID)
                {
                   UINT32 dwItemCount = 0;
                    if (yatk.size() > 1)
                        dwItemCount = atoi(yatk[1].c_str());
                    rDragonBallCFGEx._vecItem.push_back(SItemCount(wItemID, dwItemCount));
                }
            }
            rMapDragonBallCFGEx.insert(make_pair(pDragonBallCFG->_Daytime, rDragonBallCFGEx));
        }
    }

    return true;
}

SDragonBallCFGEx* CDragonBallActMgr::GetDragonBallCfg(UINT8 byIdx, UINT8 byDay)
{
    auto itMap = _mapID2DragonBallCFG.find(byIdx);
    if (itMap == _mapID2DragonBallCFG.end())
        return NULL;
    auto it = itMap->second.find(byDay);
    if (it != itMap->second.end())
        return &it->second;
    return NULL;
}

void CDragonBallActMgr::TimeCheck(time_t tNow)
{
    if(!Config.AllServerIsReady())
        return;
    UINT32 dwEndTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
    if (tNow < dwEndTime)
    {
        if (_byState != 1)
        {
            if (IsOpenAct(tNow))
                OpenIcon();
        }
        if (_byState != 2)
        {
            if (!IsOpenAct(tNow))
                DelIcon();
        }
        return;
    }
    if (dwEndTime == 0)
        dwEndTime = Config._dwOpenServerTime;
    g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActBeginTime, dwEndTime);
    g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActEndTime, dwEndTime+86400*DRAGONBALL_PERIOD);
    UINT8 byPeriod = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActPeriod);
    if (byPeriod == 0)
        ++ byPeriod;
    if (GetDragonBallCfg(byPeriod, 1))
    {
        g_CenterGameVar.AddVar(NVarDefine::eSystemVar_DragonBallActPeriod, 1);
    }
    if (IsOpenAct(tNow))
        OpenIcon();
    else
        DelIcon();
}

void CDragonBallActMgr::DelIcon()
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();

    //通知 Icon消失
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eDragonBallAct;
    oState.bOpen = false;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState, true);
    _byState = 2;
}

void CDragonBallActMgr::OpenIcon()
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();

    //通知 Icon出现
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eDragonBallAct;
    oState.bOpen = true;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState, true);
    _byState = 1;
}

bool CDragonBallActMgr::IsOpenAct(UINT32 dwCurTime)
{
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActBeginTime);
    UINT32 dwEndTime   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
    if (!dwEndTime || !dwBeginTime || dwBeginTime >= dwEndTime)
        return false;
    if (dwBeginTime > dwCurTime || dwEndTime <= dwCurTime)
        return false;
    UINT8 byPeriod = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActPeriod);
    if (!GetDragonBallCfg(byPeriod, 1))
        return false;
    return true;
}

UINT8 CDragonBallActMgr::GetUserExtraCount(CUserPtr pUser)
{
    if (!pUser)
        return 0;
    if (!IsOpenAct(time(NULL)))
        return 0;
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActBeginTime);
    UINT32 dwEndTime   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
    UINT32 dwCreateTime = pUser->GetCreateTime();
    if (!dwCreateTime || dwCreateTime < dwBeginTime || dwCreateTime >= dwEndTime)
        return 0;
    return (Time::TheDay(0, dwCreateTime) - dwBeginTime) / 86400;
}

void CDragonBallActMgr::OnDragonBallAct(CUserPtr pUser)
{
    //XXX　逻辑很复杂，坑，勿怨！！！
    if (!pUser)
        return;
    UINT32 dwNow = time(NULL);
    if (!IsOpenAct(dwNow))
        return;
    UINT32 dwAllCount = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDragonBall_AllCount);
    UINT8 byAllCount = GET_BIT_8(dwAllCount, 0);
    UINT8 byCurExtra = GET_BIT_8(dwAllCount, 1);
    if (byAllCount >= DRAGONBALL_PERIOD)
        return;
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActBeginTime);
    UINT32 dwEndTime   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
    UINT8 byPeriod     = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActPeriod);
    UINT8 byDayCount   = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDragonBall_TodayCount);
    UINT32 dwDayRecharge = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDayRechargeCenter);
    UINT8 byExtraCount = GetUserExtraCount(pUser);
    UINT8 byIdx = (Time::TheDay(1, dwNow) - dwBeginTime) / 86400;
    if (byAllCount >= byIdx || byDayCount >= byExtraCount+1)
        return;
    byExtraCount = byExtraCount<=byCurExtra ? 0 : byExtraCount-byCurExtra;
    if (byDayCount > 0 && byExtraCount == 0)
        return;
    SDragonBallCFGEx* pDragonBallCfg = GetDragonBallCfg(byPeriod, byAllCount+1);
    if (!pDragonBallCfg || dwDayRecharge < pDragonBallCfg->_Cost)
        return;
    UINT64 qwUserID = pUser->GetRoleID();
    int iMax = byExtraCount + (byDayCount > 0 ? 0 : 1);   //XXX 新创角玩家当天可以补错过的龙珠
    UINT32 dwNeedRecharge = 0;
    for (int i = 0; i < byDayCount; ++ i)
    {
        pDragonBallCfg = GetDragonBallCfg(byPeriod, byAllCount-i);
        if (pDragonBallCfg)
            dwNeedRecharge += pDragonBallCfg->_Cost;
    }
    for (int i = 0; i < iMax; ++ i)
    {
        pDragonBallCfg = GetDragonBallCfg(byPeriod, byAllCount+1);
        if (!pDragonBallCfg)
            break;
        dwNeedRecharge += pDragonBallCfg->_Cost;
        if (dwDayRecharge < dwNeedRecharge)
            break;
        ++ byAllCount;
        ++ byDayCount;
        if (byDayCount > 1)
            ++ byCurExtra;
        SendAwardMailDay(pDragonBallCfg, qwUserID);
    }
    dwAllCount = SET_BIT_8(dwAllCount, 0, byAllCount);
    dwAllCount = SET_BIT_8(dwAllCount, 1, byCurExtra);
    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerVarDragonBall_AllCount, dwAllCount, 0, dwEndTime);
    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerVarDragonBall_TodayCount, byDayCount);
    if (byAllCount == DRAGONBALL_PERIOD && dwNow >= dwEndTime - 1*86400 && dwNow < dwEndTime)    //第7天
    {
        pUser->GetCenterVar().SetVar(NVarDefine::ePlayerVarDragonBall_AllCount, ++ dwAllCount, 0, dwEndTime);
        pUser->GetCenterVar().SetVar(NVarDefine::ePlayerVarDragonBall_TodayCount, ++ byDayCount);
        SDragonBallCFGEx* pDragonBallCfgNext = GetDragonBallCfg(byPeriod, byAllCount+1);
        //发送邮件
        if (pDragonBallCfgNext)
            SendAwardMailFinal(pDragonBallCfgNext, qwUserID);
    }
    UpdateDragonBallAct(pUser);
}

void CDragonBallActMgr::UpdateDragonBallAct(CUserPtr pUser)
{
    if (!pUser)
        return;
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActBeginTime);
    UINT32 dwEndTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
    UINT32 dwAllCount = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDragonBall_AllCount);
    UINT8 byAllCount = GET_BIT_8(dwAllCount, 0);
    UINT8 byCurExtra = GET_BIT_8(dwAllCount, 1);
    UINT8 byDayCount = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDragonBall_TodayCount);
    UINT8 byPeriod   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActPeriod);
    UINT32 dwDayRecharge = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarDayRechargeCenter);
    UINT8 byExtraCount = GetUserExtraCount(pUser);
    UINT8 byRemain = byExtraCount > byCurExtra ? byExtraCount-byCurExtra : 0;

    SDragonBallAct oDragonBallAct;
    oDragonBallAct.dwBeginTime = dwBeginTime;
    oDragonBallAct.dwEndTime   = dwEndTime;
    oDragonBallAct.dwRecharge  = dwDayRecharge;
    oDragonBallAct.byRemain    = byRemain;
    oDragonBallAct.byAll = byAllCount;
    oDragonBallAct.byDay = byDayCount;
    oDragonBallAct.byIdx = byPeriod;
    //LOG_WRN << "dwBeginTime:" << dwBeginTime << " dwEndTime:" << dwEndTime  << " byIdx:" << byPeriod << " byAllCount:" << byAllCount << " byDayCount:" << byDayCount << "dwDayRecharge:" << dwDayRecharge << " byRemain:" << byRemain;

    pUser->SendPkg(g_WonderActivityProtS.BuildPkg_UpdateDragonBallAct(oDragonBallAct));
}

void CDragonBallActMgr::SendAwardMailDay(SDragonBallCFGEx* pDragonBallCfg, UINT64 qwUserID)
{
    if (!pDragonBallCfg)
        return;
    //发送邮件
    string strSender, strTitle;
    CSystemMail::GetSysMailBody(SEND_DRAGONBALL_ACT, strSender);
    CSystemMail::GetSysMailBody(TITLE_DRAGONBALL_ACT, strTitle);
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_DRAGONBALL_ACT;
    SItemAttachmentPtr pItem(new SItemAttachment());
    for (size_t i = 0; i < pDragonBallCfg->_vecItem.size(); ++ i)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = pDragonBallCfg->_vecItem[i].wItemID;
        stAttach.wCount = pDragonBallCfg->_vecItem[i].wCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }

    CSystemMail sysMail;
    sysMail.AddTarget(qwUserID);
    sysMail.SetSender(strSender);
    sysMail.SetBody(stBody);
    sysMail.SetSubject(strTitle);
    sysMail.AddItemInfo(pItem->vecItemInfo);
    sysMail.Send();
}

void CDragonBallActMgr::SendAwardMailFinal(SDragonBallCFGEx* pDragonBallCfg, UINT64 qwUserID)
{
    if (!pDragonBallCfg)
        return;
    //发送邮件
    string strSender, strTitle;
    CSystemMail::GetSysMailBody(SEND_DRAGONBALL_ENDACT, strSender);
    CSystemMail::GetSysMailBody(TITLE_DRAGONBALL_ENDACT, strTitle);
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_DRAGONBALL_ENDACT;
    SItemAttachmentPtr pItem(new SItemAttachment());
    for (size_t i = 0; i < pDragonBallCfg->_vecItem.size(); ++ i)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = pDragonBallCfg->_vecItem[i].wItemID;
        stAttach.wCount = pDragonBallCfg->_vecItem[i].wCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }

    CSystemMail sysMail;
    sysMail.AddTarget(qwUserID);
    sysMail.SetSender(strSender);
    sysMail.SetBody(stBody);
    sysMail.SetSubject(strTitle);
    sysMail.AddItemInfo(pItem->vecItemInfo);
    sysMail.Send();
}

