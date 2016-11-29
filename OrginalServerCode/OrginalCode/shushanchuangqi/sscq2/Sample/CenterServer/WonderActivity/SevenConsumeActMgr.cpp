// =====================================================================================
//
//       Filename:  SevenConsumeAct.cpp
//
//    Description: 七日消费活动
//
//        Version:  1.0
//        Created:  01/04/2015 11:24:57 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================

#include "SevenConsumeActMgr.h"
#include "CenterGameVar.h"
#include "Protocols.h"
#include "VarDefine.h"
#include "Tokenizer.h"
#include "SystemMail.h"
#include "CenterGameVar.h"
#include "WonderActivityProt.h"
#include "Config.h"
#include "ActivityIDProt.h"
#include "UDPLog.h"
#include "ItemProt.h"

using namespace NActivityIDProt;
using namespace NWonderActivityProt;
using namespace NItemProt;

bool CSevenConsumeActMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/SevenConsume.xml";
    CSevenConsumeLoader oSevenConsumeLoader;
    if(!oSevenConsumeLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(size_t i = 0; i < oSevenConsumeLoader._vecData.size(); ++i)
    {
        SSevenConsumeCFG* pSevenConsumeCFG = oSevenConsumeLoader._vecData[i];
        if(pSevenConsumeCFG->_ID == 0)
            continue;
        SSevenConsumeCFGEx& rSevenConsumeCFGEx = _mapID2SevenConsumeCFG[pSevenConsumeCFG->_ID];
        rSevenConsumeCFGEx.SetConfig(*pSevenConsumeCFG);

        Tokenizer tk(rSevenConsumeCFGEx._Reward, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rSevenConsumeCFGEx._vecItem.push_back(SItemCount(wItemID, dwItemCount));
            }
        }
    }

    return true;
}

bool CSevenConsumeActMgr::ReLoadConfig(const string &strFile)
{
    string strPath;
    if("SevenConsume.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/SevenConsume.xml";
        CSevenConsumeLoader oSevenConsumeLoader;
        if(!oSevenConsumeLoader.LoadData((strPath)))
        {
            LOG_CRI << "Load " << strPath << "ERR";
            return false;
        }
        _mapID2SevenConsumeCFG.clear();
        for(size_t i = 0; i < oSevenConsumeLoader._vecData.size(); ++i)
        {
            SSevenConsumeCFG* pSevenConsumeCFG = oSevenConsumeLoader._vecData[i];
            if(pSevenConsumeCFG->_ID == 0)
                continue;
            SSevenConsumeCFGEx& rSevenConsumeCFGEx = _mapID2SevenConsumeCFG[pSevenConsumeCFG->_ID];
            rSevenConsumeCFGEx.SetConfig(*pSevenConsumeCFG);

            Tokenizer tk(rSevenConsumeCFGEx._Reward, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer yatk(tk[j], ",");
                UINT16 wItemID = atoi(yatk[0].c_str());
                if (wItemID)
                {
                   UINT32 dwItemCount = 0;
                    if (yatk.size() > 1)
                        dwItemCount = atoi(yatk[1].c_str());
                    rSevenConsumeCFGEx._vecItem.push_back(SItemCount(wItemID, dwItemCount));
                }
            }
        }
    }

    return true;
}

SSevenConsumeCFGEx* CSevenConsumeActMgr::GetSevenConsumeCfg(UINT8 byIdx)
{
    auto itMap = _mapID2SevenConsumeCFG.find(byIdx);
    if (itMap != _mapID2SevenConsumeCFG.end())
        return &itMap->second;
    return NULL;
}

bool CSevenConsumeActMgr::IsOpenAct(UINT32 dwCurTime)
{
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime);
    UINT32 dwEndTime   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
    if (!dwEndTime || !dwBeginTime || dwBeginTime >= dwEndTime)
        return false;
    if (dwBeginTime > dwCurTime || dwEndTime <= dwCurTime)
        return false;
    return true;
}

void CSevenConsumeActMgr::OnSevenConsumeAct(CUserPtr pUser)
{
    if (!pUser)
        return;
    if (!IsOpenAct())
        return;
    UINT32 dwEndTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
    UINT32 dwConsume = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarSevenConsumeGold);
    //LOG_WRN << "UserID:" << pUser->GetRoleID() << " dwConsume:" << dwConsume;
    UINT8  byGetInfo = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarSevenConsumeAwardInfo);
    for (int i = 0; i < 8; ++ i)
    {
        if (byGetInfo & (1 << i))
            continue;
        SSevenConsumeCFGEx* pSevenConsumeCFG = GetSevenConsumeCfg(i+1);
        if (!pSevenConsumeCFG)
            continue;
        if (dwConsume < pSevenConsumeCFG->_Limit)
            break;
        SendAwardMail(pSevenConsumeCFG, pUser);
        byGetInfo |= (1 << i);
    }
    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerVarSevenConsumeAwardInfo, byGetInfo, 0, dwEndTime);
    UpdateSevenConsumeAct(pUser);
}

void CSevenConsumeActMgr::UpdateSevenConsumeAct(CUserPtr pUser)
{
    if (!pUser)
        return;
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime);
    UINT32 dwEndTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
    UINT32 dwConsume = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarSevenConsumeGold);
    UINT8  byGetInfo = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarSevenConsumeAwardInfo);

    SSevenConsumeAct oSevenConsumeAct;
    oSevenConsumeAct.dwBeginTime = dwBeginTime;
    oSevenConsumeAct.dwEndTime   = dwEndTime;
    oSevenConsumeAct.dwConsume   = dwConsume;
    oSevenConsumeAct.byInfo      = byGetInfo;
    //LOG_WRN << "dwBeginTime:" << dwBeginTime << " dwEndTime:" << dwEndTime << "dwConsume:" << dwConsume << " byInfo:" << byGetInfo;

    pUser->SendPkg(g_WonderActivityProtS.BuildPkg_UpdateSevenConsumeAct(oSevenConsumeAct));
}

void CSevenConsumeActMgr::SendAwardMail(SSevenConsumeCFGEx* pSevenConsumeCfg, CUserPtr pUser)
{
    if (!pSevenConsumeCfg)
        return;
    
    if (!pUser)
        return;

    //发送邮件
    string strSender, strTitle;
    CSystemMail::GetSysMailBody(SEND_SEVENCONSUME_ACT, strSender);
    CSystemMail::GetSysMailBody(TITLE_SEVENCONSUME_ACT, strTitle);
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_SEVENCONSUME_ACT;
    stBody.vecParam.push_back(NumberToString(pSevenConsumeCfg->_Limit));
    SItemAttachmentPtr pItem(new SItemAttachment());
    for (size_t i = 0; i < pSevenConsumeCfg->_vecItem.size(); ++ i)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = pSevenConsumeCfg->_vecItem[i].wItemID;
        stAttach.wCount = pSevenConsumeCfg->_vecItem[i].wCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }

    CSystemMail sysMail;
    sysMail.AddTarget(pUser->GetUserID());
    sysMail.SetSender(strSender);
    sysMail.SetBody(stBody);
    sysMail.SetSubject(strTitle);
    sysMail.AddItemInfo(pItem->vecItemInfo);
    sysMail.Send();
    
	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
    {
        string strActionCount; 
        string strCategory = "consume"; 
        switch(pSevenConsumeCfg->_ID)
        {
            case 1:
                {
                   strActionCount = "s2_150427_43";
                }
                break;
            case 2:
                {
                   strActionCount = "s2_150427_44";
                }
                break;
            case 3:
                {
                   strActionCount = "s2_150427_45";
                }
                break;
            case 4:
                {
                   strActionCount = "s2_150427_46";
                }
                break;
            case 5:
                {
                   strActionCount = "s2_150427_47";
                }
                break;
            case 6:
                {
                   strActionCount = "s2_150427_48";
                }
                break;
            case 7:
                {
                   strActionCount = "s2_150427_49";
                }
                break;
            default:
                return;
        }
        pUDPLog->UdpLog(strCategory.c_str(), strActionCount.c_str(), NumberToString(1).c_str(), "","","", "act",1);
    }
}

void CSevenConsumeActMgr::DelIcon()
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();

    //通知 Icon消失
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eSevenConsumeAct;
    oState.bOpen = false;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState, true);
    _byState = 2;
}

void CSevenConsumeActMgr::OpenIcon()
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();

    //通知 Icon出现
    SActivityState oState;
    oState.dwActID = NActivityIDProt::eSevenConsumeAct;
    oState.bOpen = true;
    g_Game2CenterCommS.SendSvr_SyncActState(&dwGameSvrIdx, 1, oState, true);
    _byState = 1;
}

void CSevenConsumeActMgr::TimerCheck()
{
    if(!Config.AllServerIsReady())
        return;
    UINT32 dwBeginTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime);
    UINT32 dwEndTime   = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
    if (!dwEndTime || !dwBeginTime || dwBeginTime >= dwEndTime)
    {
        dwBeginTime = Config._dwOpenServerTime;
        dwEndTime = dwBeginTime + 7*86400;
        g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime, dwBeginTime);
        g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime, dwEndTime);
    }
    UINT32 dwCurTime = time(NULL);
    if (_byState != 1 && dwBeginTime <= dwCurTime && dwCurTime < dwEndTime)
        OpenIcon();
    if (_byState != 2 && dwEndTime <= dwCurTime)
        DelIcon();
}

