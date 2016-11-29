#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "VIPProtS.h"
#include "VIPMgr.h"
#include "GameServerSysMail.h"
#include "GameNetMgr.h"

static void OpenVIP(CUserPtr pUser, SVIPBaseCFGEx* pVIPBaseCfg, bool bIsOther)
{
    bool bIsFirst = false;
    CGameVar& rGameVar = pUser->GetVars();
    if (rGameVar.GetVar(NVarDefine::ePlayerVIPType) == 0)
        bIsFirst = true;
    UINT32 dwCurTime = time(NULL);
    UINT32 dwEndTime = rGameVar.GetVar(NVarDefine::ePlayerVIPEndTime);
    if(dwEndTime > dwCurTime)
        dwEndTime += pVIPBaseCfg->_Days*86400;
    else
        dwEndTime = dwCurTime + pVIPBaseCfg->_Days*86400;
    rGameVar.SetVar(NVarDefine::ePlayerVIPEndTime, dwEndTime);
    rGameVar.SetVar(NVarDefine::ePlayerVIPType, pVIPBaseCfg->_ID);
    rGameVar.SetVar(NVarDefine::ePlayerVIPDayTime, Time::TheDay(1, dwCurTime));

    //if (bIsFirst)   //第一次开通 XXX 取消
    pUser->AddVIPGrowthValue(pVIPBaseCfg->_Promotion);
    if (bIsOther)
        pUser->AddVIPGrowthValue(pVIPBaseCfg->_Give);
    pUser->SendVIPInfoToClt();
    pUser->AutoAddTitleByVIPUp();

    if (bIsFirst)
    {
        CPlayerPtr pPlayer=pUser->GetPlayer();
        if(pPlayer)
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgVIPOpen,BuildStrVec(pPlayer->GetColor(),pPlayer->GetName()));
    }
}

//接收：请求个人VIP特权信息
void CVIPProtS::OnRecv_GetVIPInfo(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;

    //pUser->CheckVIPGrowthValue();
    pUser->SendVIPInfoToClt();
}

//接收：请求开启个人VIP特权
bool CVIPProtS::OnRecv_OpenSelfVIP(
    UINT8 byType, //VIP特权类型
    shared_func<SOpenSelfVIPAck>& fnAck //返回回调函数
)
{
    return false;     //XXX 取消
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    SVIPBaseCFGEx* pVIPBaseCfg = VIPMgr.GetVIPBaseCfg(byType);
    if (!pVIPBaseCfg)
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    if (!pUser->CanSubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold))
    {
        fnAck->eResult = eVIP_LackMoney;
        return false;
    }

    OpenVIP(pUser, pVIPBaseCfg, false);
    pUser->SubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold,NLogDataDefine::ItemTo_OpenVIP);
    fnAck->eResult = eVIP_Succeed;
    return true;
}

//接收：请求开启好友VIP特权
bool CVIPProtS::OnRecv_OpenOtherVIP(
    UINT8 byType, //VIP特权类型
    UINT64 qwRoleID, //好友玩家ID
    UINT64 qwRoleID2, //好友玩家ID(匹配验证)
    shared_func<SOpenOtherVIPAck>& fnAck //返回回调函数
)
{
    return false;   //XXX 暂时取消
    fnAck->qwRoleID = qwRoleID;
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    if (!qwRoleID || qwRoleID != qwRoleID2 || pPlayer->GetRoleID() == qwRoleID)
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    SVIPBaseCFGEx* pVIPBaseCfg = VIPMgr.GetVIPBaseCfg(byType);
    if (!pVIPBaseCfg)
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    if (!pUser->CanSubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold))
    {
        fnAck->eResult = eVIP_LackMoney;
        return false;
    }

    CUserMgr::LoadUser(qwRoleID,[this, pUser, pVIPBaseCfg, fnAck](CUserPtr pOther){
            if (!pOther || !pOther->GetPlayer())
            {
                fnAck->eResult = eVIP_OtherErr;
                fnAck(true);
                return;
            }
            UINT32 dwCenterSvrID = pUser->GetCenterSvrID();
            g_Game2CenterCommC.SendSvr_IsFriend(&dwCenterSvrID,1,pUser->GetUserID(),pOther->GetUserID(),[this,dwCenterSvrID,pOther,pUser,pVIPBaseCfg,fnAck](UINT8 byRet_, UINT8 byRet){
                    if (byRet_ != 0 || byRet != 0)
                    {
                        g_Game2CenterCommC.SendSvr_IsSameGuild(&dwCenterSvrID,1,pUser->GetUserID(),pOther->GetUserID(),[this,pOther,pUser,pVIPBaseCfg,fnAck](UINT8 byRet_, UINT8 byRet){
                                if (byRet_ != 0 || byRet != 0)
                                {
                                    fnAck->eResult = eVIP_UnFriend;
                                    fnAck(true);
                                    return;
                                }
                                if (!pUser->CanSubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold))
                                {
                                    fnAck->eResult = eVIP_LackMoney;
                                    fnAck(true);
                                    return;
                                }
                                pUser->SubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold,NLogDataDefine::ItemTo_OpenFriendVIP);
                                OpenVIP(pOther, pVIPBaseCfg, true);
                                fnAck->eResult = eVIP_Succeed;
                                });
                    }
                    else
                    {
                        if (!pUser->CanSubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold))
                        {
                            fnAck->eResult = eVIP_LackMoney;
                            fnAck(true);
                            return;
                        }
                        pUser->SubMoney(EMONEY_GOLD, pVIPBaseCfg->_NeedGold,NLogDataDefine::ItemTo_OpenFriendVIP);
                        OpenVIP(pOther, pVIPBaseCfg, true);
                        fnAck->eResult = eVIP_Succeed;
                    }
                    });
            if (fnAck->eResult == eVIP_Succeed)
            {
                string strData = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgVIPPresentSuccess, BuildStrVec(pOther->GetUserName()));
                pUser->SendPkg(strData);
                //发送邮件
                NMailProt::SysMailSendTxt stBody;
                stBody.dwstrMsgID = BODY_VIPFRIEND;
                stBody.vecParam.push_back(pUser->GetUserName());
                stBody.vecParam.push_back(pVIPBaseCfg->_Desc);
                TVecUINT64 vecTargets;
                vecTargets.push_back(pOther->GetUserID());
                GameServerSysMail::SendSysMail(SEND_VIPFRIEND, TITLE_VIPFRIEND, stBody, vecTargets);
            }
            });

    return true;
}

//接收：请求开启个人月卡
bool CVIPProtS::OnRecv_OpenSelfMonthCard(
    shared_func<SOpenSelfMonthCardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy))
    {
        fnAck->eResult = eVIP_LackMoney;
        return false;
    }
    pUser->SubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy, NLogDataDefine::ItemTo_OpenVIP);

    bool bMark = false;
    UINT32 dwEndTime = pUser->GetVars().GetVar(ePlayerVarMonthCardEndTime);
    dwEndTime = dwEndTime <= time(NULL) ? time(NULL) : dwEndTime;
    UINT32 dwNow = time(NULL);
    dwEndTime = dwEndTime <= dwNow ? dwNow : dwEndTime;
    if (dwEndTime == dwNow)
    {
        bMark = true;
        pUser->GetVars().SetVar(ePlayerVarMonthCardGetTime, 0);
    }
    pUser->GetVars().SetVar(ePlayerVarMonthCardEndTime, dwEndTime+SParamConfig::dwMonthCardTime);
    pUser->GetVars().DelVar(ePlayerVarMonthCardOverNotice);
    pUser->SendVIPInfoToClt();
    pUser->SendMonthCardAward();
    
    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        pPlayer->OnEvent(eEventType_MonthCard,vecParam);
    }

    string strPkg;
    if (!bMark)
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonthCardRenew);
    else
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonthCardBuy);
    pUser->SendPkg(strPkg);
    
    fnAck->eResult = eVIP_Succeed;
    
    TVecString vecstring;
    vecstring.push_back(NumberToString(pPlayer->GetColor()));
    vecstring.push_back(pPlayer->GetName());
    g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgMonthCardBuyNotice, vecstring);
    return true;
}


//接收：请求开启好友月卡
bool CVIPProtS::OnRecv_OpenOtherMonthCard(
    UINT64 qwRoleID, //好友玩家ID
    shared_func<SOpenOtherMonthCardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy))
    {
        fnAck->eResult = eVIP_LackMoney;
        return false;
    }

    if(pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        pPlayer->OnEvent(eEventType_MonthCardSend,vecParam);
    }


    CUserMgr::LoadUser(qwRoleID,[this, pUser, fnAck](CUserPtr pOther){
            if (!pOther || !pOther->GetPlayer())
            {
                fnAck->eResult = eVIP_OtherErr;
                fnAck(true);
                return;
            }
            UINT32 dwCenterSvrID = pUser->GetCenterSvrID();
            g_Game2CenterCommC.SendSvr_IsFriend(&dwCenterSvrID,1,pUser->GetUserID(),pOther->GetUserID(),[this,dwCenterSvrID,pOther,pUser,fnAck](UINT8 byRet_, UINT8 byRet){
                    if (byRet_ != 0 || byRet != 0)
                    {
                        g_Game2CenterCommC.SendSvr_IsSameGuild(&dwCenterSvrID,1,pUser->GetUserID(),pOther->GetUserID(),[this,pOther,pUser,fnAck](UINT8 byRet_, UINT8 byRet){
                                if (byRet_ != 0 || byRet != 0)
                                {
                                    fnAck->eResult = eVIP_UnFriend;
                                    fnAck(true);
                                    return;
                                }
                                if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy))
                                {
                                    fnAck->eResult = eVIP_LackMoney;
                                    fnAck(true);
                                    return;
                                }
                                pUser->SubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy, NLogDataDefine::ItemTo_OpenFriendVIP);
                                UINT32 dwEndTime = pOther->GetVars().GetVar(ePlayerVarMonthCardEndTime);
                                UINT32 dwNow = time(NULL);
                                dwEndTime = dwEndTime <= dwNow ? dwNow : dwEndTime;
                                pOther->GetVars().SetVar(ePlayerVarMonthCardEndTime, dwEndTime+SParamConfig::dwMonthCardTime);
                                if (dwEndTime == dwNow)
                                    pOther->GetVars().SetVar(ePlayerVarMonthCardGetTime, 0);
                                pOther->GetVars().DelVar(ePlayerVarMonthCardOverNotice);
                                pOther->SendVIPInfoToClt();
                                pOther->SendMonthCardAward();
                                fnAck->eResult = eVIP_Succeed;
                                });
                    }
                    else
                    {
                        if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy))
                        {
                            fnAck->eResult = eVIP_LackMoney;
                            fnAck(true);
                            return;
                        }
                        pUser->SubMoney(EMONEY_GOLD, SParamConfig::wMonthCardBuy, NLogDataDefine::ItemTo_OpenFriendVIP);
                        UINT32 dwEndTime = pOther->GetVars().GetVar(ePlayerVarMonthCardEndTime);
                        UINT32 dwNow = time(NULL);
                        dwEndTime = dwEndTime <= dwNow ? dwNow : dwEndTime;
                        pOther->GetVars().SetVar(ePlayerVarMonthCardEndTime, dwEndTime+SParamConfig::dwMonthCardTime);
                        if (dwEndTime == dwNow)
                            pOther->GetVars().SetVar(ePlayerVarMonthCardGetTime, 0);
                        pOther->GetVars().DelVar(ePlayerVarMonthCardOverNotice);
                        pOther->SendVIPInfoToClt();
                        pOther->SendMonthCardAward();
                        fnAck->eResult = eVIP_Succeed;
                    }
                    });
            if (fnAck->eResult == eVIP_Succeed)
            {
                string strData = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgMonthCardGive, BuildStrVec(pOther->GetUserName()));
                pUser->SendPkg(strData);
                //发送邮件
                NMailProt::SysMailSendTxt stBody;
                stBody.dwstrMsgID = BODY_VIPFRIEND;
                stBody.vecParam.push_back(pUser->GetUserName());
                TVecUINT64 vecTargets;
                vecTargets.push_back(pOther->GetUserID());
                GameServerSysMail::SendSysMail(SEND_VIPFRIEND, TITLE_VIPFRIEND, stBody, vecTargets);
            }
            });

    return true;
}

//接收：领取VIP特权每日礼包
bool CVIPProtS::OnRecv_GetDayPackAward(
    shared_func<SGetDayPackAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    /*
    UINT32 dwEndTime = pUser->GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
    if (dwEndTime < time(NULL))
    {
        fnAck->eResult = eVIP_Expired;
        return false;
    }
    */
    UINT8 byVipLvl = pUser->GetVIPLevel();
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byVipLvl);
    if (!byVipLvl || !pVIPLvlCfg)
    {
        fnAck->eResult = eVIP_OtherErr;
        LOG_CRI << "OnRecv_GetDayPackAward Error!byVipLvl:" << byVipLvl << " UserID:" << pUser->GetUserID();
        return false;
    }
    UINT32 dwDayPack = pUser->GetVars().GetVar(NVarDefine::ePlayerVIPGetDayPack);
    //if (dwDayPack & (1 << (byVipLvl-1)))
    if (dwDayPack > 0)
    {
        fnAck->eResult = eVIP_HasGetAward;
        return false;
    }
    dwDayPack |= 1 << (byVipLvl-1);
    pUser->GetVars().SetVar(NVarDefine::ePlayerVIPGetDayPack, dwDayPack);
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if (!pStore || !pStore->CanAddItem(pVIPLvlCfg->_vecItemDayPack, true))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    pStore->AddItem(pVIPLvlCfg->_vecItemDayPack, NLogDataDefine::ItemFrom_VIPAward);

    fnAck->eResult = eVIP_Succeed;
    fnAck->dwDayPack = dwDayPack;

    //Event事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        pPlayer->OnEvent(eEventType_VipGetPrize, vecParam);
    }
    {
        TVecINT32 vecParam;
        vecParam.push_back(1); //类
        vecParam.push_back(byVipLvl);
        pPlayer->OnEvent(eEventType_VipGetPrizeMore, vecParam);
    }
    return true;
}

//接收：领取VIP特权等级奖励
bool CVIPProtS::OnRecv_GetVIPLevelAward(
    UINT8 byLevel, //VIP等级
    shared_func<SGetVIPLevelAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    /*
    UINT32 dwEndTime = pUser->GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
    if (dwEndTime < time(NULL))
    {
        fnAck->eResult = eVIP_Expired;
        return false;
    }
    */
    UINT8 byVipLvl = pUser->GetVIPLevel();
    if (!byVipLvl || byVipLvl < byLevel)
    {
        fnAck->eResult = eVIP_LevelErr;
        LOG_CRI << "OnRecv_GetVIPLevelAward Error!byVipLvlS:" << byVipLvl << " byVipLvlC:" << byLevel << " UserID:" << pUser->GetUserID();
        return false;
    }
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byLevel);
    if (!pVIPLvlCfg)
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    UINT32 dwLvlAward = pUser->GetVars().GetVar(NVarDefine::ePlayerVIPGetLevelAward);
    if (dwLvlAward & (1 << (byLevel-1)))
    {
        fnAck->eResult = eVIP_HasGetAward;
        return false;
    }
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if (!pStore || !pStore->CanAddItem(pVIPLvlCfg->_vecItemLevelAward, true))
    {
        fnAck->eResult = eVIP_OtherErr;
        return false;
    }
    dwLvlAward |= 1 << (byLevel-1);
    pUser->GetVars().SetVar(NVarDefine::ePlayerVIPGetLevelAward, dwLvlAward);
    for (size_t i = 0; i < pVIPLvlCfg->_vecItemLevelAward.size(); ++ i)
    {
        if (pVIPLvlCfg->_vecItemLevelAward[i].wItemID == 369)
            pPlayer->RecruitFighterByForce(109);
        else
            pStore->AddItem(pVIPLvlCfg->_vecItemLevelAward[i], NLogDataDefine::ItemFrom_VIPAward);
    }

    fnAck->eResult = eVIP_Succeed;
    fnAck->dwLvlAward = dwLvlAward;
    
    {
        TVecINT32 vecParam;
        vecParam.push_back(2); //类型
        vecParam.push_back(byLevel);
        pPlayer->OnEvent(eEventType_VipGetPrizeMore, vecParam);
    }

    return true;
}

void CVIPProtS::SendSysMsgIDNotify(EVIPResult eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eVIP_LackMoney:
            eMsgID = eMsgGoldErr;
            break;
        case eVIP_OtherErr:
            eMsgID = eMsgOtherErr;
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
