#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "CompareBattlePointS.h"
#include "HeroFighter.h"
#include "FighterManager.h"
#include "GameNetMgr.h"

//接收：战斗力对比
bool CCompareBattlePointS::OnRecv_CompareOtherBPByID(
    UINT64 qwRoleID, //对方的玩家ID
    shared_func<SCompareOtherBPByIDAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer) || !qwRoleID)
        return false;

    CUserMgr::LoadUser(qwRoleID,[this,fnAck](CUserPtr pOthUser){
            if (!pOthUser || !pOthUser->GetPlayer())
                return;
            CPlayerPtr pOthPlayer = pOthUser->GetPlayer();
            SCompareData stCD;
            stCD.qwRoleID = pOthUser->GetUserID();
            stCD.strName  = pOthUser->GetUserName();
            stCD.byLevel  = pOthUser->GetLevel();
            stCD.eCareer  = static_cast<NProtoCommon::ECareerType>(pOthPlayer->GetJob());
            stCD.eSex     = pOthPlayer->GetSex();
            stCD.dwBattlePoint = pOthPlayer->GetBattlePoint();
            CFighterManagerPtr pFighterManager = pOthPlayer->GetFighterManager();
            if (pFighterManager)
            {
                stCD.dwHeroBP   = pFighterManager->CalcHeroFighterBattlePoint();
                stCD.dwBeautyBP = pFighterManager->GetBeautyBattlePoint();
                stCD.dwTrumpBP  = pFighterManager->GetTrumpBattlePoint();
                stCD.dwHorseBP  = pFighterManager->GetHorseBattlePoint();
                stCD.dwDujieBP  = pFighterManager->GetDujieBattlePoint();
                stCD.dwXinfaBP  = pFighterManager->GetXinfaBattlePoint();
                stCD.dwClanBP   = pFighterManager->GetGuildBattlePoint();
            }
            fnAck->vecCompareData.push_back(stCD);
            fnAck(true);
            return;
            });
    return true;
}

//接收：战斗力对比
bool CCompareBattlePointS::OnRecv_CompareOtherBPByName(
    const std::string& strName, //对方的玩家名字
    shared_func<SCompareOtherBPByNameAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer) || strName.empty())
        return false;

    g_Game2DBCommC.Send_GetUserIDFromName(strName, [fnAck](UINT8 byRet, UINT64 qwReceiveID){
            if(byRet != 0 || qwReceiveID == 0)
            {
                fnAck(true);
                return;
            }
            CUserMgr::LoadUser(qwReceiveID,[fnAck](CUserPtr pOthUser){
                    if (!pOthUser || !pOthUser->GetPlayer())
                    {
                        fnAck(true);
                        return;
                    }
                    CPlayerPtr pOthPlayer = pOthUser->GetPlayer();
                    SCompareData stCD;
                    stCD.qwRoleID = pOthUser->GetUserID();
                    stCD.strName  = pOthUser->GetUserName();
                    stCD.byLevel  = pOthUser->GetLevel();
                    stCD.eCareer  = static_cast<NProtoCommon::ECareerType>(pOthPlayer->GetJob());
                    stCD.eSex     = pOthPlayer->GetSex();
                    stCD.dwBattlePoint = pOthPlayer->GetBattlePoint();
                    CFighterManagerPtr pFighterManager = pOthPlayer->GetFighterManager();
                    if (pFighterManager)
                    {
                        stCD.dwHeroBP   = pFighterManager->CalcHeroFighterBattlePoint();
                        stCD.dwBeautyBP = pFighterManager->GetBeautyBattlePoint();
                        stCD.dwTrumpBP  = pFighterManager->GetTrumpBattlePoint();
                        stCD.dwHorseBP  = pFighterManager->GetHorseBattlePoint();
                        stCD.dwDujieBP  = pFighterManager->GetDujieBattlePoint();
                        stCD.dwXinfaBP  = pFighterManager->GetXinfaBattlePoint();
                        stCD.dwClanBP   = pFighterManager->GetGuildBattlePoint();
                    }
                    fnAck->vecCompareData.push_back(stCD);
                    fnAck(true);
                    return;
                    });
            });

    return true;
}

