// =====================================================================================
//
//       Filename:  GuildXiheManager.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  01/27/2015 02:55:07 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================

#include "Center2DBGuildC.h"
#include "GuildXihe.h"
#include "GuildXiheManager.h"
#include "User.h"
#include "Parameter.h"
#include "SystemMail.h"
#include "SysMsgDefine.h"
#include "VarDefine.h"
#include "GuildMgr.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "Game2CenterComm.h"
#include "Protocols.h"
#include "UserMgr.h"

using namespace NGame2CenterComm;

bool CGuildXiheManager::_bLoadFromDB = false;

CGuildXihePtr CGuildXiheManager::GetGuildXihe(UINT64 qwRoleID)
{
    if (!qwRoleID)
        return NULL;
    auto iter = _mapAllXiheShenche.find(qwRoleID);
    if (iter == _mapAllXiheShenche.end())
    {
        if (CGuildUserMgr::Instance().GetGuildID(qwRoleID) == 0)
            return NULL;
        CGuildXihePtr pGuildXihe(new CGuildXihe(qwRoleID));
        pGuildXihe->SetStage(eXiheStageWaitAcess);
        pGuildXihe->AssignTask();
        pGuildXihe->Update2DB(eOpAdd);
        auto pairRet = _mapAllXiheShenche.insert(make_pair(qwRoleID, pGuildXihe));
        if (!pairRet.second)
            LOG_CRI  << "CGuildXihePtr insert Error!qwRoleID: " << qwRoleID;
        iter = pairRet.first;
        AddXiheTimer(qwRoleID, pGuildXihe->GetEndTime());
    }
    return iter->second;
}

void CGuildXiheManager::AddXiheTimer(UINT64 qwRoleID, UINT32 dwTime)
{
    if (!qwRoleID || !dwTime)
        return;
    _mapTimerXihe.insert(make_pair(dwTime, qwRoleID));
}

void CGuildXiheManager::TimerCheck(time_t tNow)
{
    if(!Config.AllServerIsReady())
        return;
    TVecUINT64 vecAriveXihe;
    auto itLast = _mapTimerXihe.end();
    for(auto it = _mapTimerXihe.begin(); it != _mapTimerXihe.end(); ++ it)
    {
        if(it->first <= tNow)
        {
            vecAriveXihe.push_back(it->second);
        }
        else
        {
            itLast = it;
            break;
        }
    }
    if(vecAriveXihe.empty())
        return;
    //XXX delete time
    _mapTimerXihe.erase(_mapTimerXihe.begin(), itLast);

    for(auto iter = vecAriveXihe.begin(); iter != vecAriveXihe.end(); ++ iter)
    {
        auto itXihe = _mapAllXiheShenche.find(*iter);
        if (itXihe != _mapAllXiheShenche.end())
        {
            UINT32 dwEndTime = itXihe->second->GetEndTime();
            if (tNow >= dwEndTime)
            {
                UINT8 byStage = itXihe->second->GetStage();
                if (byStage == eXiheStageShipGoods)
                {
                    DeliveryGoods(itXihe->second);
                }
                else if (byStage == eXiheStageTaskCool)
                {
                    itXihe->second->SetStage(eXiheStageWaitAcess);
                    itXihe->second->Update2DB(eOpUpdate);
                    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(itXihe->first);
                    if (pGuildUser)
                        itXihe->second->UpdateGuildXiheInfo(pGuildUser->GetOnlineUser());
                }
            }
        }
    }
}

bool CGuildXiheManager::LoadXiheFromDB()
{
    if (_bLoadFromDB)
        return false;

    UINT32 dwsize = TAKE_ARRAY_LENGTH(SGuildXihe);
    g_Center2DBGuildC.Send_GetAllGuildXihe(dwsize);
    _bLoadFromDB = true;
    return true;
}

void CGuildXiheManager::RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NGuildProt::TVecGuildXihe& vecSendData)
{
    for (size_t i = 0; i < vecSendData.size(); ++ i)
    {
        UINT64 qwRoleID = vecSendData[i].qwRoleID;
        if (!qwRoleID)
            continue;
        CGuildXihePtr pGuildXihe(new CGuildXihe(qwRoleID));
        if (!pGuildXihe)
            continue;
        pGuildXihe->SetStage(EXiheStage(vecSendData[i].byStage));
        pGuildXihe->SetEndTime(vecSendData[i].dwEndTime);
        pGuildXihe->SetRequest(vecSendData[i].byRequest);
        pGuildXihe->SetTruckInfo(vecSendData[i].vecTruckInfo);

        _mapAllXiheShenche.insert(make_pair(qwRoleID, pGuildXihe));
        if (pGuildXihe->GetStage() != eXiheStageWaitAcess)
            AddXiheTimer(qwRoleID, pGuildXihe->GetEndTime());
    }
    if (dwCurPage == dwTotalPage)
    {
        //XXX
    }
}

void CGuildXiheManager::GetXiheRequestInfo(UINT64 qwRoleID, TVecXiheRequest& vecRequest)
{
    if (!qwRoleID)
        return;
    auto iter = _mapAllXiheShenche.find(qwRoleID);
    if (iter == _mapAllXiheShenche.end())
        return;
    CGuildXihePtr pGuildXihe = iter->second;
    if (!pGuildXihe)
        return;
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
        return;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        LOG_INF << "pUser Null.";
        return;
    }
    TVecTruckInfo& vecTruck = pGuildXihe->GetTruckInfo();
    for (size_t i = 0; i < vecTruck.size(); ++ i)
    {
        if (vecTruck[i].byStatus == eXiheTaskRequest || (vecTruck[i].byStatus == eXiheTaskFinishRe && !vecTruck[i].strName.empty()))
        {
            
            SXiheRequest oRequest(qwRoleID, pGuildUser->GetName(),pGuildUser->GetQuality(),vecTruck[i].byPos, vecTruck[i].byTruckID, vecTruck[i].byStatus,vecTruck[i].strName,vecTruck[i].byColor);
            
           // SXiheRequest oRequest(qwRoleID, pGuildUser->GetName(), vecTruck[i].byPos, vecTruck[i].byTruckID, vecTruck[i].byStatus,vecTruck[i].strName);
            vecRequest.push_back(oRequest);
        }
    }
}

//接收：羲和神车装货
EGuildXiheResult CGuildXiheManager::ShipGoods(CUserPtr pUser, UINT8 byType, UINT8 byPos, shared_func<CGuildProtSvr::SShipGoodsAck> fnAck)
{
    if (!pUser || !fnAck)
        return eXiheResultFailed;
    CGuildXihePtr pGuildXihe = GetGuildXihe(pUser->GetRoleID());
    if (!pGuildXihe)
        return eXiheResultFailed;
     STruckInfo& oTruckInfo = pGuildXihe->GetTruckInfoByPos(byPos);
    if (!oTruckInfo.byTruckID)
        return eXiheResultNotTruck;
    if (oTruckInfo.byStatus == eXiheTaskFinishURe || oTruckInfo.byStatus == eXiheTaskFinishRe)
        return eXiheResultFinish;
    SXiHeTruckCFGEx* pXiheTruckCfg = CGuildMgr::Instance().GetXiHeTruckCfg(oTruckInfo.byTruckID);
    if (!pXiheTruckCfg)
        return eXiheResultFailed;
    TVecUserItem vecItemCost;
    TVecUserItem vecItemAward;
    if (byType == 0)
    {
        for (size_t i = 0; i < pXiheTruckCfg->_vecItemCost.size(); ++ i)
        {
            UINT32 dwCount = pXiheTruckCfg->_vecItemCost[i].wCount;
            SUserItem oItem(pXiheTruckCfg->_vecItemCost[i].wItemID, dwCount);
            vecItemCost.push_back(oItem);
        }
    }
    else
    {
        SUserItem oItem(1, pXiheTruckCfg->_Value);
        vecItemCost.push_back(oItem);
    }
    for (size_t i = 0; i < pXiheTruckCfg->_vecItemAward.size(); ++ i)
    {
        UINT32 dwCount = pXiheTruckCfg->_vecItemAward[i].wCount;
        SUserItem oItem(pXiheTruckCfg->_vecItemAward[i].wItemID, dwCount);
        vecItemAward.push_back(oItem);
    }
    UINT32 dwGuildMoney = pXiheTruckCfg->_GuildMoney;

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_UserSubItem(&dwServerID,1,pUser->GetUserID(),NLogDataDefine::ItemTo_GuildXihe,vecItemCost,
            [fnAck,pUser,oTruckInfo,pGuildXihe,dwGuildMoney,dwServerID,vecItemAward,byType](UINT8 byRet_, UINT8 byError) mutable
            {
                if (!fnAck || !pUser || !pGuildXihe || byRet_ || byError)
                {
                    LOG_CRI << "Sub item Error!!";
                    if (byType == 0)
                        fnAck->eResult = eXiheResultNotItem;
                    else
                        fnAck->eResult = eXiheResultNotGold;
                    fnAck(true);
                    return;
                }
                if (oTruckInfo.byStatus == eXiheTaskUnfinish)
                    pGuildXihe->SetTruckStatus(oTruckInfo.byPos, eXiheTaskFinishURe);
                else
                    pGuildXihe->SetTruckStatus(oTruckInfo.byPos, eXiheTaskFinishRe);
                pGuildXihe->Update2DB(eOpUpdate);

                pGuildXihe->UpdateGuildXiheInfo(pUser);
                if (oTruckInfo.byStatus == eXiheTaskRequest)
                {
                    
                    SXiheRequest sXiheRequest(pGuildXihe->GetOwnerID(), pUser->GetUserName(),pUser->GetColor(),oTruckInfo.byPos, oTruckInfo.byTruckID, oTruckInfo.byStatus, oTruckInfo.strName,oTruckInfo.byColor);
                    
                   // SXiheRequest sXiheRequest(pGuildXihe->GetOwnerID(), pUser->GetUserName(), oTruckInfo.byPos, oTruckInfo.byTruckID, oTruckInfo.byStatus, oTruckInfo.strName);
                    pUser->SendPkg(g_GuildProtS.BuildPkg_GuildXiheHelpNotify(1, sXiheRequest));
                }
                //XXX 增加帮派资金及帮贡
                CGuildUserPtr pGuildUser = pUser->GetGuildUser();
                if (pGuildUser)
                {
                    CGuildPtr pGuild = pGuildUser->GetGuild();
                    if (pGuild && dwGuildMoney > 0)
                        pGuild->AddMoney(dwGuildMoney);
                    if (vecItemAward.size() > 0)
                        pGuildUser->AddContribution(vecItemAward[0].dwCount);
                }
                fnAck->eResult = eXiheResultSuccess;
                fnAck(true);
            });
    return eXiheResultSuccess;
}

//接收：羲和神车帮众成员帮助装货
EGuildXiheResult CGuildXiheManager::HelpShipGoods(CUserPtr pUser, UINT8 byType, UINT64 qwOtherID, UINT8 byPos, shared_func<CGuildProtSvr::SHelpShipGoodsAck> fnAck)
{
    if (!pUser || !fnAck)
        return eXiheResultFailed;
    CGuildXihePtr pOtherXihe = GetGuildXihe(qwOtherID);
    if (!pOtherXihe)
        return eXiheResultFailed;
     STruckInfo& oTruckInfo = pOtherXihe->GetTruckInfoByPos(byPos);
    if (!oTruckInfo.byTruckID)
        return eXiheResultNotTruck;
    if (oTruckInfo.byStatus != eXiheTaskRequest)
        return eXiheResultNotRequest;
    SXiHeTruckCFGEx* pXiheTruckCfg = CGuildMgr::Instance().GetXiHeTruckCfg(oTruckInfo.byTruckID);
    if (!pXiheTruckCfg)
        return eXiheResultFailed;
    TVecUserItem vecItemCost;
    TVecUserItem vecItemAward;
    if (byType == 0)
    {
        for (size_t i = 0; i < pXiheTruckCfg->_vecItemCost.size(); ++ i)
        {
            UINT32 dwCount = pXiheTruckCfg->_vecItemCost[i].wCount;
            SUserItem oItem(pXiheTruckCfg->_vecItemCost[i].wItemID, dwCount);
            vecItemCost.push_back(oItem);
        }
    }
    else
    {
        SUserItem oItem(1, pXiheTruckCfg->_Value);
        vecItemCost.push_back(oItem);
    }
    UINT32 dwHelpCnt = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarXiheHelpCount);
    for (size_t i = 0; i < pXiheTruckCfg->_vecItemAward.size(); ++ i)
    {
        UINT32 dwCount = pXiheTruckCfg->_vecItemAward[i].wCount;
        if (dwHelpCnt < SParamConfig::wTradeHelpAwardTimes)
            dwCount *= 1.0f + float(SParamConfig::wTradeHelpAwardRatio) / 10000;
        SUserItem oItem(pXiheTruckCfg->_vecItemAward[i].wItemID, dwCount);
        vecItemAward.push_back(oItem);
    }
    UINT32 dwGuildMoney = pXiheTruckCfg->_GuildMoney;

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_UserSubItem(&dwServerID,1,pUser->GetUserID(),NLogDataDefine::ItemTo_GuildXihe,vecItemCost,
            [fnAck,pUser,oTruckInfo,pOtherXihe,dwGuildMoney,dwServerID,vecItemAward,byType](UINT8 byRet_, UINT8 byError) mutable
            {
                if (!fnAck || !pUser || !pOtherXihe || byRet_ || byError)
                {
                    LOG_CRI << "Sub item Error!!";
                    if (byType == 0)
                        fnAck->eResult = eXiheResultNotItem;
                    else
                        fnAck->eResult = eXiheResultNotGold;
                    fnAck(true);
                    return;
                }
                CGuildUserPtr pGuildOther = CGuildUserMgr::Instance().GetUserByUserID(pOtherXihe->GetOwnerID());
                if (!pGuildOther)
                {
                    fnAck->eResult = eXiheResultFailed;
                    fnAck(true);
                    return;
                }

                CGuildUserPtr pGuildUser = pUser->GetGuildUser();
                if (!pGuildUser)
                {
                    fnAck->eResult = eXiheResultFailed;
                    fnAck(true);
                    return;
                }

                CGuildPtr pGuild = pGuildUser->GetGuild();
                if (!pGuild)
                {
                    fnAck->eResult = eXiheResultFailed;
                    fnAck(true);
                    return;
                }

                pOtherXihe->SetTruckHelpName(oTruckInfo.byPos, pUser->GetUserName(),pUser->GetColor());
                if (oTruckInfo.byStatus == eXiheTaskUnfinish)
                    pOtherXihe->SetTruckStatus(oTruckInfo.byPos, eXiheTaskFinishURe);
                else
                    pOtherXihe->SetTruckStatus(oTruckInfo.byPos, eXiheTaskFinishRe);
                pOtherXihe->Update2DB(eOpUpdate);
                pUser->GetCenterVar().AddVar(NVarDefine::ePlayerVarXiheHelpCount, 1);

                pOtherXihe->UpdateGuildXiheInfo(pUser);
                CUserPtr pOther = pGuildOther->GetOnlineUser();
                if (pOther)
                    pOtherXihe->UpdateGuildXiheInfo(pOther);

                if (dwGuildMoney > 0)
                    pGuild->AddMoney(dwGuildMoney);

                if (vecItemAward.size() > 0)
                    pGuildUser->AddContribution(vecItemAward[0].dwCount);

                SXiheRequest sXiheRequest(pOtherXihe->GetOwnerID(), pGuildOther->GetName(), pGuildOther->GetQuality(),oTruckInfo.byPos, oTruckInfo.byTruckID, eXiheTaskFinishRe, pUser->GetUserName(),pUser->GetColor());
                
                //SXiheRequest sXiheRequest(pOtherXihe->GetOwnerID(), pGuildOther->GetName(), oTruckInfo.byPos, oTruckInfo.byTruckID, eXiheTaskFinishRe,pUser->GetUserName());
                string strPkg = g_GuildProtS.BuildPkg_GuildXiheHelpNotify(2, sXiheRequest);
                TVecUINT64 vecUserID;
                pGuild->GetAllUserID(vecUserID);
                for (auto it=vecUserID.begin(); it!=vecUserID.end(); ++it)
                {
                    CGuildUserPtr pGuildMember = CGuildUserMgr::Instance().GetUserByUserID(*it);
                    if (pGuildMember)
                    {
                        CUserPtr pMember = pGuildMember->GetOnlineUser();
                        if (pMember)
                            pMember->SendPkg(strPkg);
                    }
                }
                
                /*CGuildUserPtr pGuildOther = CGuildUserMgr::Instance().GetUserByUserID(pOtherXihe->GetOwnerID());
                if (pGuildOther)
                {
                    SXiheRequest sXiheRequest(pOtherXihe->GetOwnerID(), pGuildOther->GetName(), oTruckInfo.byPos, oTruckInfo.byTruckID);
                    string strPkg = g_GuildProtS.BuildPkg_GuildXiheHelpNotify(1, sXiheRequest);
                    pUser->SendPkg(strPkg);

                    CUserPtr pOther = pGuildOther->GetOnlineUser();
                    if (pOther)
                    {
                        pOtherXihe->UpdateGuildXiheInfo(pOther);
                        pOther->SendPkg(strPkg);
                    }
                }
                //XXX 增加帮派资金及帮贡
                CGuildUserPtr pGuildUser = pUser->GetGuildUser();
                if (pGuildUser)
                {
                    CGuildPtr pGuild = pGuildUser->GetGuild();
                    if (pGuild && dwGuildMoney > 0)
                        pGuild->AddMoney(dwGuildMoney);
                    if (vecItemAward.size() > 0)
                        pGuildUser->AddContribution(vecItemAward[0].dwCount);
                }*/
                fnAck->eResult = eXiheResultSuccess;
                fnAck(true);
            });
    return eXiheResultSuccess;
}

//接收：羲和神车发货
EGuildXiheResult CGuildXiheManager::DeliveryGoods(CGuildXihePtr pGuildXihe)
{
    if (!pGuildXihe)
        return eXiheResultFailed;
    UINT64 qwRoleID  = pGuildXihe->GetOwnerID();
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    //发送邮件
    CSystemMail sysMail;
    string strSender, strTitle;
    NMailProt::SysMailSendTxt stBody;
    if (pGuildXihe->IsFinishAllTask())
    {
        SXiHeTruckCFGEx* pXiheTruckCfg = CGuildMgr::Instance().GetXiHeTruckCfg(0);  //XXX id为0 装满奖励
        if (pXiheTruckCfg)
        {
            SItemAttachmentPtr pItem(new SItemAttachment());
            for (size_t i = 0; i < pXiheTruckCfg->_vecItemAward.size(); ++ i)
            {
                SMailItemInfo stAttach;
                stAttach.wItemID = pXiheTruckCfg->_vecItemAward[i].wItemID;
                stAttach.wCount = pXiheTruckCfg->_vecItemAward[i].wCount;
                stAttach.eBindType = NItemProt::eBindGet;
                pItem->vecItemInfo.push_back(stAttach);
            }
            sysMail.AddItemInfo(pItem->vecItemInfo);
        }
        CSystemMail::GetSysMailBody(SEND_XIHESHENCHEALL_ACT, strSender);
        CSystemMail::GetSysMailBody(TITLE_XIHESHENCHEALL_ACT, strTitle);
        stBody.dwstrMsgID = BODY_XIHESHENCHEALL_ACT;

        //XXX 增加帮派资金
        if(pGuildUser && pXiheTruckCfg->_GuildMoney > 0)
        {
            CGuildPtr pGuild = pGuildUser->GetGuild();
            if (pGuild)
                pGuild->AddMoney(pXiheTruckCfg->_GuildMoney);
        }
    }
    else
    {
        CSystemMail::GetSysMailBody(SEND_XIHESHENCHENOT_ACT, strSender);
        CSystemMail::GetSysMailBody(TITLE_XIHESHENCHENOT_ACT, strTitle);
        stBody.dwstrMsgID = BODY_XIHESHENCHENOT_ACT;
    }
    sysMail.AddTarget(qwRoleID);
    sysMail.SetSender(strSender);
    sysMail.SetBody(stBody);
    sysMail.SetSubject(strTitle);
    sysMail.Send();

    CUserPtr pUser = pGuildUser ? pGuildUser->GetOnlineUser() : NULL;
    TVecTruckInfo& vecTruck = pGuildXihe->GetTruckInfo();
    for (auto it = vecTruck.begin(); it != vecTruck.end(); ++ it)
    {
        if (it->byStatus == eXiheTaskRequest && pGuildUser && pUser)
        {
            
            SXiheRequest sXiheRequest(qwRoleID, pGuildUser->GetName(),pGuildUser->GetQuality(), it->byPos, it->byTruckID, it->byStatus,it->strName,it->byColor);
           
            //SXiheRequest sXiheRequest(qwRoleID, pGuildUser->GetName(), it->byPos, it->byTruckID, it->byStatus,it->strName);
            string strPkg = g_GuildProtS.BuildPkg_GuildXiheHelpNotify(1, sXiheRequest);
            pUser->SendPkg(strPkg);
        }
    }
    UINT32 dwLastEnd = pGuildXihe->GetEndTime();
    auto range = _mapTimerXihe.equal_range(dwLastEnd);
    for (auto iter = range.first; iter != range.second; ++ iter)
    {
        if(iter->second == qwRoleID)
        {
            _mapTimerXihe.erase(iter);
            break;
        }
    }
    pGuildXihe->SetEndTime(time(NULL)+SParamConfig::dwTradeCoolDownTime);
    pGuildXihe->SetStage(eXiheStageTaskCool);
    pGuildXihe->AssignTask();
    pGuildXihe->SetRequest(0);
    pGuildXihe->Update2DB(eOpUpdate);
    AddXiheTimer(qwRoleID, pGuildXihe->GetEndTime());

    if (pUser)
    {
        pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgTradeAlreadySend));
        pGuildXihe->UpdateGuildXiheInfo(pUser);
    }
    return eXiheResultSuccess;
}

