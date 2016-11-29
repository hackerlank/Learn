
#include "stdafx.h"
#include "User.h"
#include "UserMgr.h"
#include "Archive.h"
#include "Protocols.h"
#include "ArenaManager.h"
#include "VarDefine.h"
#include "CenterGameVar.h"
#include "ItemProt.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "VIPMgr.h"
//接收：请求自己竞技场信息,同时开启竞技场
bool CArenaGSS::OnRecv_ArenaInfoReq(
        shared_func<SArenaInfoReqAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }

    if(!pUser->HasIcon(Type_Arena) && !pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        //SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        LOG_INF <<qwRoleID << " Lock by Arena";
        return false;
    }
    CArenaManager::PlayerGetInfo(qwRoleID,dwCalTimer,
            [fnAck,qwRoleID](Data2ClientPtr pClient)
            {
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            return false;
            else
            pUser->GetOpLock().UnLock(eLock_Arena);

            if(pClient != NULL)
            {
            fnAck->stReturn = *pClient;
            fnAck(true);
            }
            else
            fnAck(false);
            return true;
            });
    return true;
}

//接收：请求挑战
bool CArenaGSS::OnRecv_ArenaChallengeReq(
        UINT64 qwDefense, //被挑战者ID
        shared_func<SArenaChallengeReqAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::DoArenaChallenge(qwRoleID,qwDefense,fnAck);
    return true;
}

//接收：请求翻页
bool CArenaGSS::OnRecv_ArenaPageUpReq(
        EArenaLevel eLevel, //段位
        UINT32 dwRank, //请求排名开始名次
        UINT8 byNum, //请求数量
        shared_func<SArenaPageUpReqAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CArenaManager::GetPlayerListByRank(fnAck->vecRankData,eLevel,dwRank,byNum);
    fnAck->dwSize = CArenaManager::GetPlayerSizeByRank(eLevel);
    return true;
}

//接收：请求清除冷却
bool CArenaGSS::OnRecv_ArenaClearCDReq(
        UINT8 byType,
        shared_func<SArenaClearCDReqAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    //////////////////////////////
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(byType >0 )
    {
        if(!pUser->HasIcon(Type_Ladder))
        {
            fnAck->eResult = EArenaR_LadderNOOpen;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;
        }

    }
    else
    {
        if(!pUser->HasIcon(Type_Arena))
        {
            fnAck->eResult = EArenaR_ArenaNoOpen;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;

        }

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    const ArenaConfig& rConfig = CArenaManager::GetArenaConfig();
    //计算剩余时间
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(!pCfgVip)
    {

        fnAck->eResult = EArenaR_OtherErr;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    UINT32 dwNow = time(NULL);


    UINT32 dwNeedCost = 0;
    UINT32 OldCD = 0;
    if(byType > 0)
    {
        dwNeedCost = SParamConfig::byLadderColdTimeClearPrice;
        OldCD =  SParamConfig::wLadderColdTime;

    }
    else
    {
        OldCD = rConfig.stArenaNum.dwCDTimer;
        dwNeedCost = rConfig.stArenaNum.dwClearCDCost;
    }
    if(OldCD == 0)
    {

        fnAck->eResult = EArenaR_OtherErr;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    if(byType > 0)
    {
        if(dwNow >= rInfo.dwLadderCDTime)
        {
            fnAck->eResult = EArenaR_OtherErr;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;

        }
        dwNeedCost = ceil((rInfo.dwLadderCDTime - dwNow)*dwNeedCost/float(OldCD));  
        rInfo.dwLadderCDTime = 0;

    }
    else
    {
        if(dwNow >= rInfo.dwCDTime)
        {
            fnAck->eResult = EArenaR_OtherErr;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;

        }
        dwNeedCost = ceil((rInfo.dwCDTime - dwNow)*dwNeedCost/float(OldCD));  
        rInfo.dwCDTime  = 0 ;


    }
    if(pUser->GetGold() + pUser->GetCoupon() < dwNeedCost)
    {
        fnAck->eResult = EArenaR_LackMoney;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);

        return true;
    }

    UINT32 dwNeedGold = 0;
    UINT32 dwNeedCoupon = 0;
    if(dwNeedCost > 0 )
    {
        if(pUser->GetCoupon() >= dwNeedCost)
        {
            dwNeedCoupon = dwNeedCost;
        }
        else
        {
            dwNeedCoupon = pUser->GetCoupon();
            dwNeedGold = dwNeedCost - dwNeedCoupon;
        }
    }
    CArenaManager::UpdatePlayerDataToDB(qwRoleID);
    //TODO:扣钱
    UINT32 dwServerID = pUser->GetGameSvrID();
    if(byType == 0)
    {
        if(dwNeedGold > 0)
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_ArenaClearCD,NProtoCommon::EMONEY_GOLD,dwNeedGold);
        }
        if(dwNeedCoupon > 0)
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_ArenaClearCD,NProtoCommon::EMONEY_COUPON,dwNeedCoupon);

        }
    }
    else
    {
        if(dwNeedGold > 0)
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_ArenaClearLadderCD,NProtoCommon::EMONEY_GOLD,dwNeedGold);
        }
        if(dwNeedCoupon > 0)
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_ArenaClearLadderCD,NProtoCommon::EMONEY_COUPON,dwNeedCoupon);

        }
    }

    return true;
}

//接收：请求获取奖池奖励
bool CArenaGSS::OnRecv_ArenaGetRankingRewardReq(
        UINT32 dwLootId, //奖励包
        EArenaAwardType eType, //奖励包类型
        shared_func<SArenaGetRankingRewardReqAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    //////////////////////////////
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    /*
       if(!pUser->HasIcon(Type_Arena))
       {
       fnAck->eResult = EArenaR_ArenaNoOpen;
       SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
       return true;

       }
       */
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    bool bUpdate = CArenaManager::CheckAward(rInfo,pPlayer,dwCalTimer);
    if(bUpdate)
    {
        CArenaManager::UpdatePlayerDataToDB(qwRoleID);
        fnAck->eResult = EArenaR_AwardTimeOut;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;  
    }
    bool bFind = false;
    for(auto iter = rInfo.vecAwards.begin();iter != rInfo.vecAwards.end();iter++)
    {
        SArenaAward &rAward = *iter;
        if(rAward.dwDrawID == dwLootId && rAward.eType == eType)
        {
            bFind = true;
            if(rAward.byDraw > 0)
            {
                fnAck->eResult = EArenaR_RewardHasGet;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                return true;
            }
            break;
        }

    }
    if(!bFind)
    {
        fnAck->eResult = EArenaR_NoReward;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    /////////////////////////
    UINT32 dwServerID = pUser->GetGameSvrID();
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        return false;
    }
    g_Game2CenterCommS.SendSvr_CanPushLoot(&dwServerID, 1,qwRoleID,dwLootId,[this,eType,qwRoleID,dwLootId,fnAck](UINT8 byRet_,UINT8 byRet){
            if(byRet_ != 0 || byRet != 0)
            {
            fnAck->eResult = EArenaR_PackageFull;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            return ;
            }
            //////////////////////////////
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            fnAck(false);
            return ;
            }
            else
            {
            pUser->GetOpLock().UnLock(eLock_Arena);
            }
            UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
            if(dwCalTimer == 0)
            {
                fnAck(false);//等待结算
                return ;
            }
            SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
            if(pPlayer == NULL)
            {
                fnAck->eResult = EArenaR_NoEnter;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }

            NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
            if(rSelfInfo.empty())
            {
                LOG_CRI <<"NO SELF INFO";
                fnAck->eResult = EArenaR_NoEnter;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
            bool bUpdate = CArenaManager::CheckAward(rInfo,pPlayer,dwCalTimer);
            if(bUpdate)
            {
                CArenaManager::UpdatePlayerDataToDB(qwRoleID);
                fnAck->eResult = EArenaR_AwardTimeOut;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            bool bFind = false;
            for(auto iter = rInfo.vecAwards.begin();iter != rInfo.vecAwards.end();iter++)
            {
                SArenaAward &rAward = *iter;
                if(rAward.dwDrawID == dwLootId && rAward.eType == eType)
                {
                    bFind = true;
                    if(rAward.byDraw > 0)
                    {
                        fnAck->eResult = EArenaR_RewardHasGet;
                        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                        fnAck(true);
                        return ;
                    }
                    else
                    {
                        rAward.byDraw = 1;
                    }
                    break;
                }

            }
            if(!bFind)
            {
                fnAck->eResult = EArenaR_NoReward;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            UINT32 dwServerID = pUser->GetGameSvrID();
            CArenaManager::UpdatePlayerDataToDB(qwRoleID);
            g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID,1,qwRoleID,eOpArenaWirship,NLogDataDefine::ItemFrom_ArenaAward,dwLootId);
            TVecINT32 vecParam;
            vecParam.push_back(eType);
            if(Type_LadderRank == eType)
            {
                pUser->OnEvent(eEventType_ArenaGetPrize,vecParam);
            }
            else
            {
                pUser->OnEvent(eEventType_ExperienceGetPrize,vecParam);
            }

            fnAck(true);
    });
    return true;
}

//接收：膜拜请求
bool CArenaGSS::OnRecv_ArenaWorship(
        UINT64 qwWirshipID, //膜拜对象
        shared_func<SArenaWorshipAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    //////////////////////////////
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwCurTimes = rVar.GetVar(NVarDefine::ePlayerVarArenaWirship);
    const ArenaConfig& rConfig = CArenaManager::GetArenaConfig();
    if(dwCurTimes >= rConfig.stWorship.byMaxNum)
    {
        fnAck->eResult = EArenaR_WirShipOverTimes;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    bool bFind = false;
    const TVecArenaRank2Client& rTop= CArenaManager::GetWirship();
    for(auto it = rTop.begin();it != rTop.end();it++)
    {
        const SArenaRank2Client& rTopPlayer = *it;
        if(qwWirshipID == rTopPlayer.qwRoleID)
        {
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        fnAck->eResult = EArenaR_WirShipPlayerOverTimer;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    /////////////////////////////
    UINT32 dwServerID = pUser->GetGameSvrID();
    UINT32 dwLootId = rConfig.stWorship.dwLootId;
    if(!pUser->GetOpLock().AddLock(eLock_Arena))
    {
        return false;
    }
    g_Game2CenterCommS.SendSvr_CanPushLoot(&dwServerID, 1,qwRoleID,dwLootId,[this,qwRoleID,qwWirshipID,dwLootId,fnAck](UINT8 byRet_,UINT8 byRet){
            if(byRet_ != 0 || byRet != 0)
            {
            fnAck->eResult = EArenaR_PackageFull;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            fnAck(true);
            }
            //////////////////////////////
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL == pUser)
            {
            fnAck(false);
            return ;
            }
            else
            {
            pUser->GetOpLock().UnLock(eLock_Arena);

            }
            UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
            if(dwCalTimer == 0)
            {
                fnAck(false);//等待结算
                return ;
            }
            SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
            if(pPlayer == NULL)
            {
                fnAck->eResult = EArenaR_NoEnter;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            CCenterVar& rVar = pUser->GetCenterVar();
            UINT32 dwCurTimes = rVar.GetVar(NVarDefine::ePlayerVarArenaWirship);
            const ArenaConfig& rConfig = CArenaManager::GetArenaConfig();
            if(dwCurTimes >= rConfig.stWorship.byMaxNum)
            {
                fnAck->eResult = EArenaR_WirShipOverTimes;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;
            }
            bool bFind = false;
            const TVecArenaRank2Client& rTop= CArenaManager::GetWirship();
            for(auto it = rTop.begin();it != rTop.end();it++)
            {
                const SArenaRank2Client& rTopPlayer = *it;
                if(qwWirshipID == rTopPlayer.qwRoleID)
                {
                    bFind = true;
                    break;
                }
            }
            if(!bFind)
            {
                fnAck->eResult = EArenaR_WirShipPlayerOverTimer;
                SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
                fnAck(true);
                return ;

            }
            /////////////////////////////
            UINT32 dwServerID = pUser->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID,1,qwRoleID,eOpArenaWirship,NLogDataDefine::ItemFrom_ArenaAward,dwLootId);
            rVar.AddVar(NVarDefine::ePlayerVarArenaWirship,1, rConfig.stWorship.byReflushTimer*3600);
            fnAck(true);
    });

    return true;
}

//接收：请求刷将
bool CArenaGSS::OnRecv_FlushNewEnemy(
        shared_func<SFlushNewEnemyAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    //////////////////////////////
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    bool bUpdate = CArenaManager::CheckFlush(qwRoleID);
    if(bUpdate)
    {
        CArenaManager::UpdatePlayerDataToDB(qwRoleID);
        fnAck->eResult =  EArenaR_EnemyTimeOut;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    //获得当前刷将次数
    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwCurTimes = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFlush);
    UINT32 dwCurFreeTimes = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush);

    const ArenaConfig& rConfig = CArenaManager::GetArenaConfig();

    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(pCfgVip == NULL)
        return false;

    if(dwCurFreeTimes >= pCfgVip->_LilianFrush)
    {
        UINT32 dwNeedCost = dwCurTimes*rConfig.stFlushChallenger.dwAddFlushCost + rConfig.stFlushChallenger.dwBaseFlushCost;
        if(pUser->GetGold() < dwNeedCost)
        {
            fnAck->eResult = EArenaR_LackMoney;
            SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
            return true;
        }

        //TODO:扣钱
        UINT32 dwServerID = pUser->GetGameSvrID();
        g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwRoleID,NLogDataDefine::ItemTo_ArenaClearCD,NProtoCommon::EMONEY_GOLD,dwNeedCost);
        rVar.AddVar(NVarDefine::ePlayerVarArenaChallengeFlush,1,rConfig.stFlushChallenger.byReflushTimer*3600);
    }
    else
        rVar.AddVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush, 1, rConfig.stFlushChallenger.byReflushTimer*3600);
    TVecINT32 vecParam;
    //vecParam.push_back(rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFlush) + rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush));
    vecParam.push_back(1);
    pUser->OnEvent(eEventType_ExperienceRefresh,vecParam);
    fnAck->wSelfReflush = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFlush);
    fnAck->wSelfFreeReflush = rVar.GetVar(NVarDefine::ePlayerVarArenaChallengeFreeFlush);

    CArenaManager::DoFlush(qwRoleID);
    CArenaManager::UpdatePlayerDataToDB(qwRoleID);
    fnAck(true);

    return true;
}

//接收：请求对手信息
bool CArenaGSS::OnRecv_GetAllEnemy(
        shared_func<SGetAllEnemyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    //////////////////////////////
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        fnAck(false);//等待结算
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    bool bUpdate = CArenaManager::CheckFlush(qwRoleID);
    if(bUpdate)
    {
        CArenaManager::UpdatePlayerDataToDB(qwRoleID);
    }
    pUser->GetOpLock().AddLock(eLock_Arena);
    CArenaManager::GetFlushClient(qwRoleID,[fnAck,qwRoleID](FlushClientVecPtr vecPtr)
            {
            fnAck->vecFlushFigter = *vecPtr;
            fnAck(true);
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if(NULL != pUser)
            {
            pUser->GetOpLock().UnLock(eLock_Arena);
            }
            });
    return true;

}
//接收：请求奖励信息
bool CArenaGSS::CArenaGSS::OnRecv_GetAllAward(
        shared_func<SGetAllAwardAck>& fnAck //返回回调函数
        )
{ 
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    NRoleInfoDefine::SRoleArenaInfo &rInfo = rSelfInfo[0];
    bool bUpdate = CArenaManager::CheckAward(rInfo,pPlayer,dwCalTimer);
    if(bUpdate)
    {
        CArenaManager::UpdatePlayerDataToDB(qwRoleID);
    }
    fnAck->vecAwards = rInfo.vecAwards;
    return true;

}

//接收：请求膜拜信息
bool CArenaGSS::OnRecv_GetAllWirship(
        shared_func<SGetAllWirshipAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    fnAck->vecWirshipFigter = CArenaManager::GetWirship();
    return true;
}
//接收：请求计算:奖励信息 
bool CArenaGSS::OnRecv_GetAllAwardInfo(
        shared_func<SGetAllAwardInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::CalAwardInfo(pPlayer,fnAck->vecAwards);
    return true;
}

bool CArenaGSS::OnRecv_ArenaByChallengeTimes(
        shared_func<SArenaByChallengeTimesAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::DoBuyArenaChallengeTimes(pPlayer,fnAck);
    return true;

}
//接收：请求购买天梯挑战次数
bool CArenaGSS::OnRecv_ArenaBuyLadderTimes(
        shared_func<SArenaBuyLadderTimesAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Ladder))
    {
        fnAck->eResult = EArenaR_LadderNOOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::DoBuyLadderTimes(pPlayer,fnAck);
    return true;

}

//接收：请求对手信息
bool CArenaGSS::OnRecv_ReFluseLadderEnemy(
        UINT8 byType, //0,默认刷对手，1顺次刷对手
        shared_func<SReFluseLadderEnemyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::ReFluseLadderEnemy(pUser,pPlayer,byType,fnAck);
    return true;
}

//接收：清求领取今日天梯奖励
bool CArenaGSS::OnRecv_GetLadderAward(
        shared_func<SGetLadderAwardAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::GetLadderAward(pUser,pPlayer,fnAck);
    return true;

}
bool CArenaGSS::OnRecv_GetArenaAward(
        shared_func<SGetArenaAwardAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    if(!pUser->HasIcon(Type_Arena))
    {
        fnAck->eResult = EArenaR_ArenaNoOpen;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::GetArenaAward(pUser,pPlayer,fnAck);
    return true;

}


//接收：清求领取今日天梯奖励
bool CArenaGSS::OnRecv_GetLadderReport(
        shared_func<SGetLadderReportAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;

    }
    CArenaManager::GetLadderReport(pUser,pPlayer,fnAck);
    return true;

}

//接收：请求天梯挑战
bool CArenaGSS::OnRecv_LadderBattle(
        UINT64 qwEnemyID, //对手ID
        UINT32 dwEnemyRank, //对手天梯排名
        shared_func<SLadderBattleAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CArenaManager::LadderBattle(pUser,pPlayer,qwEnemyID,dwEnemyRank,fnAck);
    return true;
}
//接收：请求天梯排名
bool CArenaGSS::OnRecv_LadderPageUpReq(
        UINT32 dwRank, //请求排名开始名次
        UINT8 byNum, //请求数量
        shared_func<SLadderPageUpReqAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    UINT32 dwCalTimer = g_CenterGameVar.GetVar(NVarDefine::eSystemVarArena);
    if(dwCalTimer == 0)
    {
        return false;
    }
    SArenaPlayerData *pPlayer = CArenaManager::GetPlayer(qwRoleID);
    if(pPlayer == NULL)
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }

    NRoleInfoDefine::TVecRoleArenaInfo& rSelfInfo  = pUser->GetArenaInfo();
    if(rSelfInfo.empty())
    {
        fnAck->eResult = EArenaR_NoEnter;
        SendSysMsgIDNotify(fnAck->eResult,qwRoleID);
        return true;
    }
    CArenaManager::LadderPageUpReq(pUser,dwRank,byNum,fnAck);
    return true;
}

void CArenaGSS::SendSysMsgIDNotify(EArenaResult eResult,UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return ;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();

    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case EArenaR_NoEnter:
            eMsgID = eMsgArenaNoEnter;
            break;
        case EArenaR_CDTime:
            eMsgID = eMsgArenaCdTimer;
            break;
        case EArenaR_NoChanllengeTimes:
            eMsgID = eMsgArenaChallengeOverTimes;
            break;
        case EArenaR_BuyTimesChanllengeTimes:
            eMsgID = eMsgArenaChallengeBuyTimes;
            break;
        case EArenaR_LackMoney:
            eMsgID = eMsgGoldErr;
            break;
        case EArenaR_EnemyNoExist:
            eMsgID = eMsgArenaChallengeTargetErr;
            break;
        case EArenaR_EnemyTimeOut:
            eMsgID = eMsgArenaChallengeTargetOverTimer;
            break;
        case EArenaR_EnemyIsSuc:
            eMsgID = eMsgArenaChallengeTargetSuc;
            break;
        case EArenaR_NoReward:
            eMsgID = eMsgArenaAwardErr;
            break;
        case EArenaR_RewardHasGet:
            eMsgID = eMsgArenaAwardDone;
            break;
        case EArenaR_PackageFull:
            eMsgID = eMsgPackFullErr;
            break;
        case EArenaR_AwardTimeOut:
            eMsgID = eMsgArenaAwardOverTimer;
            break;
        case EArenaR_WirShipOverTimes:
            eMsgID = eMsgArenaWirshipOverTimes;
            break;
        case EArenaR_WirShipPlayerOverTimer:
            eMsgID = eMsgArenaWirshipOverTimer;
            break;
        case EArenaR_VIPLevel:
            eMsgID = eMsgVipLevelNo;
            break;
        case EArenaR_BuyTimesMax:
            eMsgID =  eMsgArenaBuyOverTimes;
            break;
        case 	EArenaR_LadderNOOpen ://天梯未开启
            eMsgID =  eMsgLadderNOOpen;
            break;
        case EArenaR_LadderTimesLimit: //天梯挑战次数不足
            eMsgID =  eMsgLadderTimesLimit;
            break;
        case EArenaR_LadderAwardHasGet: //天梯挑战奖励已领
            eMsgID = eMsgLadderAwardHasGet;
            break;
        case EArenaR_LadderRankErr: //排名验证错误
            eMsgID = eMsgLadderRankErr;
            break;
        case EArenaR_LadderRankLimit: //挑战资格验证错误
            eMsgID = eMsgLadderRankLimit;
            break;
        case EArenaR_ArenaNoOpen:
            eMsgID = eMsgSysNotOpenLvlErr;
            break;
        case EArenaR_ArenaTimesLimit:
            eMsgID = eMsgLilianTimesLimit;
            break;
        case EArenaR_ArenaAwardHasGet:
            eMsgID = eMsgLilianAwardHasGet;
            break;
        case EArenaR_LadderTimesZero:
            eMsgID = eDoujianTimesLacking;
            break;
        case EArenaR_LadderBuyTimesUp:
            eMsgID = eDoujianBuyingTimesLacking;
            break;
        default:

            break;

    }
    if(eMsgID != eMsgSuccess)
    {
        g_Game2CenterCommS.SendSvr_SendSysMsg(&dwServerID,1,qwRoleID,eMsgID);

    }
    //	g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
