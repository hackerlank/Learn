#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "DayActProtS.h"
#include "DayActivityMgr.h"
#include "VarDefine.h"
#include "IconAppearManager.h"
#include "Loot.h"
#include "FoundationMgr.h"
#include "GameConfig.h"
#include "GameNetMgr.h"

CDayActProtS g_DayActProtS;
//接收：获取活动列表
bool CDayActProtS::OnRecv_GetActList(
	shared_func<SGetActListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_DayActivityMgr.GetActInfo(fnAck->vecActInfo);
    return true;
}

//接收：是否已领取首充礼包
bool CDayActProtS::OnRecv_GetFirstRechargeStatus(
    shared_func<SGetFirstRechargeStatusAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    UINT8 byStatus = pUser->GetVars().GetVar(NVarDefine::ePlayerVarFirstRechrgeStatus);
    if (pUser->GetTotalRecharge() > 0)
    {
        if (byStatus == 0)
            byStatus = 1;
    }

    //0未充值 1已充值但未领取 2已领取
    fnAck->byRet = byStatus;
    return true;
}

//接收：领取首充礼包
bool CDayActProtS::OnRecv_GetFirstRechargeAward(
    shared_func<SGetFirstRechargeAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    if (pUser->GetTotalRecharge() == 0)
    {
        fnAck->byRet = 2;
        return false;
    }
    UINT8 byStatus = pUser->GetVars().GetVar(NVarDefine::ePlayerVarFirstRechrgeStatus);
    if (byStatus == 2)
    {
        fnAck->byRet = 3;
        return false;
    }
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if(!pStore)
        return false;
    /*
    const static UINT32 itemAwards[5][2] = {
        //{367, 50}, {907, 1}, {2, 60000},
        {907, 1}, {2, 60000},
        {9, 5000}, {201, 20}, {202, 10}
    };
    TVecItemGenInfo oVecItemGenInfo;
    for (int i = 0; i < 6; ++ i)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID   = itemAwards[i][0];
        oItemGenInfo.dwCount   = itemAwards[i][1];
        oItemGenInfo.eBindType = eBindGet;
        oVecItemGenInfo.push_back(oItemGenInfo);
    }
    */
    TVecResource vecRes;
    TVecItemGenInfo oVecItemGenInfo;
    LOOT.Roll(SParamConfig::wFirstBuyAward, oVecItemGenInfo, vecRes);
    if (oVecItemGenInfo.empty() || !pStore->CanAddItem(oVecItemGenInfo, true))
        return false;
    pStore->AddItem(oVecItemGenInfo, NLogDataDefine::ItemFrom_VIPAward);
    if (!vecRes.empty())
        pStore->AddResource(*pUser, vecRes, NLogDataDefine::ItemFrom_VIPAward);

    //0失败 1成功 2未充值 3已领取
    fnAck->byRet = 1;
    pUser->GetVars().SetVar(NVarDefine::ePlayerVarFirstRechrgeStatus, 2);
    CIconAppearMgr::Instance().DelAction(*pUser,70);
    pPlayer->RecruitFighterByForce(107);

    {
        TVecString vecstring;
        vecstring.push_back(NumberToString(pPlayer->GetColor()));
        vecstring.push_back(pPlayer->GetName());
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgFirstPay, vecstring);
    }
    return true;
}

//接收：为自己购买蜀山基金
bool CDayActProtS::OnRecv_BuyShushanFoundSelf(
    UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
    shared_func<SBuyShushanFoundSelfAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    if (byType <= 0 || byType > 4)
        return false;
    SFoundationCFGEx* pFoundationCfg = CFoundationMgr::Instance().GetFoundationCFG(byType);
    if (!pFoundationCfg)
        return false;
    UINT64 qwValue = pUser->GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundInfo);
    UINT16 wValue = GET_BIT_16(qwValue, byType-1);
    if (GET_BIT(wValue, 0))    //已购买
        return false;
    if (!pUser->CanSubMoney(EMONEY_GOLD, pFoundationCfg->_Spend))
    {
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgGoldErr);
        return false;
    }

    pUser->SubMoney(EMONEY_GOLD, pFoundationCfg->_Spend, NLogDataDefine::ItemTo_ShushanFound);
    wValue = SET_BIT(wValue, 0);
    qwValue = SET_BIT_16(qwValue, byType-1, wValue);
    pUser->GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundInfo, qwValue);
    UINT32 dwLoginDays = pUser->GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundLoginDays);
    dwLoginDays = SET_BIT_8(dwLoginDays, byType-1, 1);
    pUser->GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundLoginDays, dwLoginDays);
    fnAck->byRet = 1;

    {
        ESystemMsgID eMsgID = eMsgFoundation;
        if (byType == 1)
            eMsgID = eMsgFoundation;
        else if (byType == 3)
            eMsgID = eMsgFoundation1;
        else if (byType == 4)
            eMsgID = eMsgFoundation2;
        TVecString vecstring;
        vecstring.push_back(NumberToString(pPlayer->GetColor()));
        vecstring.push_back(pPlayer->GetName());
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgID, vecstring);
    }
    return true;
}

//接收：为好友购买蜀山基金
bool CDayActProtS::OnRecv_BuyShushanFoundFirend(
    UINT64 qwFriendID, //好友ID
    UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
    shared_func<SBuyShushanFoundFirendAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    if (byType < 0 || byType > 4 || !qwFriendID)
        return false;
    SFoundationCFGEx* pFoundationCfg = CFoundationMgr::Instance().GetFoundationCFG(byType);
    if (!pFoundationCfg)
        return false;
    if (!pUser->CanSubMoney(EMONEY_GOLD, pFoundationCfg->_Spend))
    {
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgGoldErr);
        return false;
    }

    CUserMgr::LoadUser(qwFriendID,[this, pUser, byType, fnAck](CUserPtr pFriend){
            if (!pFriend)
            {
                fnAck(true);
                return;
            }
            UINT64 qwValue = pFriend->GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundInfo);
            UINT16 wValue = GET_BIT_16(qwValue, byType-1);
            if (GET_BIT(wValue, 0))    //已购买
            {
                fnAck(true);
                return;
            }
            UINT32 dwCenterSvrID = pUser->GetCenterSvrID();
            g_Game2CenterCommC.SendSvr_IsFriend(&dwCenterSvrID,1,pUser->GetUserID(),pFriend->GetUserID(),[this,pUser,pFriend,byType,qwValue,fnAck](UINT8 byRet_, UINT8 byRet){
                    if (byRet_ != 0 || byRet != 0 || !pUser || !pFriend)
                    {
                        fnAck(true);
                        return;
                    }
                    SFoundationCFGEx* pFoundationCfg = CFoundationMgr::Instance().GetFoundationCFG(byType);
                    if (!pFoundationCfg)
                    {
                        fnAck(true);
                        return;
                    }
                    if (!pUser->CanSubMoney(EMONEY_GOLD, pFoundationCfg->_Spend))
                    {
                        g_ChatProtS.Send_SystemMsgIDNotify(eMsgGoldErr);
                        fnAck(true);
                        return;
                    }
                    pUser->SubMoney(EMONEY_GOLD, pFoundationCfg->_Spend, NLogDataDefine::ItemTo_ShushanFound);
                    UINT16 wValue = GET_BIT_16(qwValue, byType-1);
                    wValue = SET_BIT(wValue, 0);
                    UINT64 qwNewValue = SET_BIT_16(qwValue, byType-1, wValue);
                    pFriend->GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundInfo, qwNewValue);
                    UINT32 dwLoginDays = 0;
                    dwLoginDays = SET_BIT_8(dwLoginDays, byType-1, 1);
                    pFriend->GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundLoginDays, dwLoginDays);
                    g_ChatProtS.Send_SystemMsgIDNotify(eMsgMallPresentSuccess);
                    fnAck->byRet = 1;

                    {
                        ESystemMsgID eMsgID = eMsgFoundation;
                        if (byType == 1)
                            eMsgID = eMsgFoundation;
                        else if (byType == 3)
                            eMsgID = eMsgFoundation1;
                        else if (byType == 4)
                            eMsgID = eMsgFoundation2;
                        TVecString vecstring;
                        vecstring.push_back(NumberToString(pFriend->GetPlayer()->GetColor()));
                        vecstring.push_back(pFriend->GetUserName());
                        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgID, vecstring);
                    }
                    });
            });
    return true;
}

//接收：获取玩家购买及领取蜀山基金的信息
void CDayActProtS::OnRecv_GetShushanFoundInfo(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;
    pUser->SendShushanFoundInfo();
    return;
}

//接收：领取蜀山基金奖励
bool CDayActProtS::OnRecv_GetShushanFoundAward(
    UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
    UINT8 byTimes, //领取第几个(1~7)
    shared_func<SGetShushanFoundAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    if (byType < 0 || byType > 4 || !byTimes || byTimes > 7)
        return false;
    SFoundationCFGEx* pFoundationCfg = CFoundationMgr::Instance().GetFoundationCFG(byType);
    if (!pFoundationCfg)
        return false;
    UINT64 qwValue = pUser->GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundInfo);
    UINT16 wValue = GET_BIT_16(qwValue, byType-1);
    if (GET_BIT(wValue, 0) == 0)    //未购买
        return false;
    UINT8 byGetCount = 0;
    for (size_t i = 1; i < 8; ++ i)
    {
        if ((wValue & (1 << i)) > 0)
            ++ byGetCount;
    }
    if (byGetCount >= 7)
        return false;
    if (byType == 1)    //1为成长基金
    {
        auto it = pFoundationCfg->_mapID2Level.find(byTimes);
        if (it == pFoundationCfg->_mapID2Level.end())
            return false;
        if (pUser->GetLevel() < it->second)
            return false;
        if (GET_BIT(wValue, byTimes) > 0)     //已领取
        {
            g_ChatProtS.Send_SystemMsgIDNotify(eMsgAwardHasGet);
            return false;
        }
    }
    else
    {
        UINT32 dwLoginDays = pUser->GetVars().GetVar(NVarDefine::ePlayerVarShushanFoundLoginDays);
        if (GET_BIT_8(dwLoginDays, byType-1) < byTimes)     //登陆天数不够
        {
            g_ChatProtS.Send_SystemMsgIDNotify(eMsgOtherErr);
            return false;
        }
        if (GET_BIT(wValue, byTimes) > 0)     //已领取
        {
            g_ChatProtS.Send_SystemMsgIDNotify(eMsgAwardHasGet);
            return false;
        }
    }
    auto iter = pFoundationCfg->_mapItemGen.find(byTimes);
    if (iter == pFoundationCfg->_mapItemGen.end())
        return false;
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if(!pStore)
        return false;
    TVecItemGenInfo vecItemGen;
    vecItemGen.push_back(iter->second);
    if (!pStore->CanAddItem(vecItemGen, true))
        return false;
    pStore->AddItem(vecItemGen, NLogDataDefine::ItemFrom_ShushanFound);

    wValue = SET_BIT(wValue, byTimes);
    qwValue = SET_BIT_16(qwValue, byType-1, wValue);

    pUser->GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundInfo, qwValue);
    fnAck->byRet = 1;
    return true;
}

//接收：获取二次充值礼包状态
bool CDayActProtS::OnRecv_GetSecondRechargeStatus(
    shared_func<SGetSecondRechargeStatusAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    UINT8 byStatus = pUser->GetVars().GetVar(NVarDefine::ePlayerVarSecondRechrgeStatus);
    UINT32 dwSecondRechargeValue = pUser->GetVars().GetVar(NVarDefine::ePlayerVarSecondRechargeValue);
    
    if (dwSecondRechargeValue >= SParamConfig::wSecondBuyCost && 0 == byStatus)
        byStatus = 1;

    //0未充值 1已充值但未领取 2已领取
    fnAck->byRet = byStatus;

    fnAck->dwSecondRechargeValue = dwSecondRechargeValue;

    return true;
}

//接收：领取二次充值礼包
bool CDayActProtS::OnRecv_GetSecondRechargeAward(
    shared_func<SGetSecondRechargeAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    UINT32 dwSecondRechargeValue = pUser->GetVars().GetVar(NVarDefine::ePlayerVarSecondRechargeValue);
    if (dwSecondRechargeValue < SParamConfig::wSecondBuyCost)
    {
        fnAck->byRet = 2;
        return false;
    }

    UINT8 byStatus = pUser->GetVars().GetVar(NVarDefine::ePlayerVarSecondRechrgeStatus);
    if (byStatus == 2)
    {
        fnAck->byRet = 3;
        return false;
    }

    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if(!pStore)
        return false;
    
    TVecResource vecRes;
    TVecItemGenInfo oVecItemGenInfo;
    LOOT.Roll(SParamConfig::wSecondBuyAward, oVecItemGenInfo, vecRes);
    if (oVecItemGenInfo.empty() || !pStore->CanAddItem(oVecItemGenInfo, true))
        return false;

    pStore->AddItem(oVecItemGenInfo, NLogDataDefine::ItemFrom_SecondRechargeAward);
    if (!vecRes.empty())
        pStore->AddResource(*pUser, vecRes, NLogDataDefine::ItemFrom_SecondRechargeAward);

    //0失败 1成功 2未充值 3已领取
    fnAck->byRet = 1;
    pUser->GetVars().SetVar(NVarDefine::ePlayerVarSecondRechrgeStatus, 2);
    CIconAppearMgr::Instance().DelAction(*pUser, 102);
    
    return true;
}

//接收：获取开服时间
bool CDayActProtS::OnRecv_GetOpenServerTime(
        shared_func<SGetOpenServerTimeAck>& fnAck //返回回调函数
        )
{
    fnAck->dwTime = Config._dwOpenServerTime;
    return true;
}
