// =====================================================================================
//
//       Filename:  NewGuildBattleProtS.cpp
//
//    Description:  新帮派战协议处理函数
//
//        Version:  1.0
//        Created:  03/18/2015 04:23:03 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleProtS.h"

#include "SysMsgDefine.h"
#include "Protocols.h"
#include "NewGuildBattleMgr.h"
#include "NewGuildBattlePlayer.h"
#include "NewGuildBattleRank.h"
#include "NewGuildBattleMountain.h"
#include "NewGuildBattleGate.h"
#include "NewGuildBattleCave.h"
#include "Player.h"
#include "GameNetMgr.h"

using namespace NNewGuildBattle;

// ===  FUNCTION  ======================================================================
//         Name:  ~CNewGuildBattleProtS
//  Description:  析构函数
// =====================================================================================
CNewGuildBattleProtS::~CNewGuildBattleProtS ()
{
}		// -----  end of function ~CNewGuildBattleProtS  ----- //

//接收：获取帮派战状态
bool CNewGuildBattleProtS::OnRecv_GetState(
        shared_func<SGetStateAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eState = CBattleMgr::Instance().GetState();
    fnAck->dwRemainTime = CBattleMgr::Instance().GetRemainTime();
    CBattleMgr::Instance().GetAllMountainsPanelInfo(fnAck->vecInfo);
    switch (fnAck->eState)
    {
        case eNGBSBattle: //帮派战进行中
            if (pPlayer)
                fnAck->eMountainType = CBattleMgr::Instance().GetPlayerMountain(pPlayer->GetRoleID());
            break;
        default:
            break;
    }
    return true;
}

//接收：获取历届占领帮会
bool CNewGuildBattleProtS::OnRecv_GetOwnerHistory(
        ENGBMountain eMountainType, //灵山类型
        shared_func<SGetOwnerHistoryAck>& fnAck //返回回调函数
        )
{
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
        return false;
    return pMountain->GetHistoryInfo(fnAck->vecInfo);
}

//接收：进入帮派战(进入准备场地)
bool CNewGuildBattleProtS::OnRecv_Enter(
        ENGBMountain eMountainType, //灵山类型
        shared_func<SEnterAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    if (pPlayer->HasBuff(22) || pPlayer->HasBuff(23))
    {
        fnAck->eResult = eNGBEREscape;
        return false;
    }

    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
                [fnAck, pPlayer, eMountainType](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
                {
                    NNewGuildBattle::CPlayerPtr pNGBPlayer;
                    if (byRet == 0)
                    {
                        if (qwGuildID)
                        {
                            if (byGuildLvl < SParamConfig::wLingMountainJoinLimit)
                            {
                                fnAck->eResult = eNGBERGuildLevel;
                                fnAck(false);
                            }
                            else
                            {
                                pNGBPlayer.reset(new NNewGuildBattle::CPlayer(pPlayer, qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName));
                                if (!pNGBPlayer)
                                {
                                    fnAck->eResult = eNGBERFailed;
                                    fnAck(false);

                                }
                                else
                                {
                                    fnAck->eResult = CBattleMgr::Instance().PlayerEnter(pNGBPlayer, eMountainType, fnAck->eState);
                                    bool bRet = fnAck->eResult == eNGBERSuccess ? true:false;
                                    fnAck(bRet);
                                    if (bRet)
                                    {
                                        pPlayer->RegenAllHP();
                                        CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
                                    }
                                }
                            }
                        }
                        else
                        {
                            fnAck->eResult = eNGBERNotInGuild;
                            fnAck(false);
                        }
                    }
                    else
                    {
                        fnAck->eResult = eNGBERFailed;
                        fnAck(false);
                    }

                    if (fnAck->eResult == eNGBERRepeat && pNGBPlayer)
                    {
                        CBattleMgr::Instance().PlayerQuit(pNGBPlayer);
                        fnAck->eResult = CBattleMgr::Instance().PlayerEnter(pNGBPlayer, eMountainType, fnAck->eState);

                    }
                    if (fnAck->eResult == eNGBERRepeat)
                    {
                        string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainInCooldownTime);
                        pPlayer->SendPkg(strPkg);
                    }
                    LOG_CRI << "fnAck->eState = " << fnAck->eState << ".";
                });
    }
    else
    {
        // 可能下线后原先保存的Player对象已经销毁
        if (!pNGBPlayer->GetPlayer())
            pNGBPlayer->SetPlayer(pPlayer);

        if (pNGBPlayer->GetMountain() != eNGBMNone)
        {
            if (pNGBPlayer->GetMountain() != eMountainType)
                fnAck->eResult = eNGBERRepeat;
            else
                fnAck->eResult = eNGBERSuccess; // 可以重复进入了
        }
        else
            fnAck->eResult = CBattleMgr::Instance().PlayerEnter(pNGBPlayer, eMountainType, fnAck->eState);

        if (fnAck->eResult == eNGBERRepeat)
        {
            CBattleMgr::Instance().PlayerQuit(pNGBPlayer);
            fnAck->eResult = CBattleMgr::Instance().PlayerEnter(pNGBPlayer, eMountainType, fnAck->eState);

        }
        if (fnAck->eResult == eNGBERRepeat)
        {
            string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainInCooldownTime);
            pPlayer->SendPkg(strPkg);
        }
        bool bRet = fnAck->eResult == eNGBERSuccess ? true:false;
        fnAck(bRet);
        if (bRet)
            CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    }
    return true;
}

//接收：城门战攻击玩家/城门
bool CNewGuildBattleProtS::OnRecv_GateAttackPlayer(
        UINT64 qwTargetRoleID, //目标唯一ID(0为城墙)
        shared_func<SGateAttackPlayerAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBGARFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBGARFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSGate) //城门战
    {
        CGatePtr pGate = pMountain->GetGate();
        if (pGate)
            fnAck->eResult = pGate->PlayerAttack(pNGBPlayer, qwTargetRoleID);
        else
            fnAck->eResult = eNGBGARFailed;
    }
    else
        fnAck->eResult = eNGBGARWrongTime;

    fnAck(fnAck->eResult == eNGBGARSuccess ? true : false);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;
}

//接收：购买傀儡
bool CNewGuildBattleProtS::OnRecv_BuyPuppet(
        shared_func<SBuyPuppetAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBBPRFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBBPRFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSGate) //城门战
    {
        CGatePtr pGate = pMountain->GetGate();
        if (pGate)
            fnAck->eResult = pGate->PlayerBuyPuppet(pNGBPlayer);
        else
            fnAck->eResult = eNGBBPRFailed;
    }
    else
        fnAck->eResult = eNGBBPRWrongTime;

    fnAck(fnAck->eResult == eNGBBPRSuccess ? true : false);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;
}

//接收：获取城门战信息
bool CNewGuildBattleProtS::OnRecv_GetGateInfo(
        shared_func<SGetGateInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSGate) //城门战
    {
        CGatePtr pGate = pMountain->GetGate();
        if (pGate && pGate->GetAllInfo(fnAck->sInfo, pPlayer->GetRoleID()))
            fnAck->eResult = eNGBRSuccess;
        else
            fnAck->eResult = eNGBRFailed;
    }
    else
        fnAck->eResult = eNGBRWrongTime;

    return fnAck->eResult == eNGBRSuccess ? true : false;
}

//接收：洞府战占领阵眼
bool CNewGuildBattleProtS::OnRecv_CaveCapture(
        ENGBCaveCore eCaveType, //阵眼类型
        shared_func<SCaveCaptureAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSCave) //洞府战
    {
        CCavePtr pCave = pMountain->GetCave();
        if (pCave)
            fnAck->eResult = pCave->PlayerCapture(pNGBPlayer, eCaveType);
        else
            fnAck->eResult = eNGBCARFailed;
    }
    else
        fnAck->eResult = eNGBCARWrongTime;
    fnAck(fnAck->eResult == eNGBCARSuccess ? true : false);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;
}

//接收：洞府战攻击他人
bool CNewGuildBattleProtS::OnRecv_CaveAttack(
        UINT64 qwTargetRoleID, //目标唯一ID
        shared_func<SCaveAttackAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSCave) //洞府战
    {
        CCavePtr pCave = pMountain->GetCave();
        if (pCave)
            fnAck->eResult = pCave->PlayerAttack(pNGBPlayer, qwTargetRoleID);
        else
            fnAck->eResult = eNGBCARFailed;
    }
    else
        fnAck->eResult = eNGBCARWrongTime;
    fnAck(fnAck->eResult == eNGBCARSuccess ? true : false);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;
}

//接收：洞府战从阵眼下阵
bool CNewGuildBattleProtS::OnRecv_CaveRest(
        shared_func<SCaveRestAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBCARFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSCave) //洞府战
    {
        CCavePtr pCave = pMountain->GetCave();
        if (pCave)
            fnAck->eResult = pCave->PlayerRest(pNGBPlayer);
        else
            fnAck->eResult = eNGBCARFailed;
    }
    else
        fnAck->eResult = eNGBCARWrongTime;
    fnAck(fnAck->eResult == eNGBCARSuccess ? true : false);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;

}

//接收：获取洞府战信息
bool CNewGuildBattleProtS::OnRecv_GetCaveInfo(
        shared_func<SGetCaveInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    ENGBMountain eMountainType = pNGBPlayer->GetMountain();
    CMountainPtr pMountain = CBattleMgr::Instance().GetMountain(eMountainType);
    if (!pMountain)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    if (pMountain->GetState() == eNGBMSCave) //洞府战
    {
        CCavePtr pCave = pMountain->GetCave();
        if (pCave && pCave->GetAllInfo(fnAck->sInfo, pPlayer->GetRoleID()))
            fnAck->eResult = eNGBRSuccess;
        else
            fnAck->eResult = eNGBRFailed;
    }
    else
        fnAck->eResult = eNGBRWrongTime;

    return fnAck->eResult == eNGBRSuccess ? true : false;
}

//接收：立即买活
bool CNewGuildBattleProtS::OnRecv_ClearDeadCD(
        shared_func<SClearDeadCDAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBCDCDRFailed;
        return false;
    }

    if (CBattleMgr::Instance().GetState() != eNGBSBattle)
    {
        fnAck->eResult = eNGBCDCDRWrongTime;
        return false;
    }

    if (!pNGBPlayer->GetDeadTime())
    {
        fnAck->eResult = eNGBCDCDRIsAlive;
        return false;
    }
    if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wLingMountainReliveGold))
    {
        fnAck->eResult = eNGBCDCDRFailed;
        return false;
    }
    pUser->SubMoney(EMONEY_GOLD, SParamConfig::wLingMountainReliveGold, NLogDataDefine::ItemTo_NewGuildBattleDead);
    pNGBPlayer->SetDeadTime(0);
    fnAck->eResult = eNGBCDCDRSuccess;
    fnAck(true);
    CBattleMgr::Instance().PlayerNotify(pPlayer->GetRoleID());
    return true;
}

//接收：帮派战退出
bool CNewGuildBattleProtS::OnRecv_Quit(
        shared_func<SQuitAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (!pNGBPlayer)
    {
        fnAck->eResult = eNGBQuitFailed;
        return false;
    }
    fnAck->eResult = CBattleMgr::Instance().PlayerQuit(pNGBPlayer);
    bool bRet = fnAck->eResult == eNGBQuitSuccess ? true : false;
    fnAck(bRet);
    return bRet;
}

//接收：获取战功榜帮派排名信息
bool CNewGuildBattleProtS::OnRecv_GetGuildRankInfo(
        UINT32 dwIndex, //排名索引
        UINT32 dwCount, //排名个数
        shared_func<SGetGuildRankInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    ENGBMountain eMountainType = eNGBMNone;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (pNGBPlayer)
        eMountainType = pNGBPlayer->GetMountain();
    ENGBState eState = CBattleMgr::Instance().GetState();
    if (eState != eNGBSBattle)
    {
        fnAck->eResult = eNGBRWrongTime;
        return false;
    }
    CGuildRankMgrPtr pRankMgr = CBattleMgr::Instance().GetGuildRankMgr();
    if (!pRankMgr)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    fnAck->eResult = pRankMgr->GetRankInfo(eMountainType, dwIndex, dwCount, 
            fnAck->dwCurIndex, fnAck->dwMaxCount, fnAck->vecInfo);
    if (fnAck->eResult != eNGBRSuccess)
        return false;
    else
        return true;
}

//接收：获取战功榜帮派成员排名信息
bool CNewGuildBattleProtS::OnRecv_GetGuildMemberRankInfo(
        UINT32 dwIndex, //排名索引
        UINT32 dwCount, //排名个数
        shared_func<SGetGuildMemberRankInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    ENGBMountain eMountainType = eNGBMNone;
    UINT64 qwGuildID = 0;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (pNGBPlayer)
    {
        eMountainType = pNGBPlayer->GetMountain();
        qwGuildID = pNGBPlayer->GetGuildID();
    }
    ENGBState eState = CBattleMgr::Instance().GetState();
    if (eState != eNGBSBattle)
    {
        fnAck->eResult = eNGBRWrongTime;
        return false;
    }

    CGuildMemberRankMgrPtr pRankMgr = CBattleMgr::Instance().GetGuildMemberRankMgr();
    if (!pRankMgr)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }

    if (qwGuildID)
    {
        fnAck->eResult = pRankMgr->GetRankInfo(eMountainType, qwGuildID, dwIndex, dwCount, 
                fnAck->dwCurIndex, fnAck->dwMaxCount, fnAck->vecInfo);

    }
    else
    {
        g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
                [fnAck, eMountainType, dwIndex, dwCount, pRankMgr](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
                {
                    if (byRet == 0 && qwGuildID)
                    {
                        fnAck->eResult = pRankMgr->GetRankInfo(eMountainType, qwGuildID, dwIndex, dwCount, 
                                fnAck->dwCurIndex, fnAck->dwMaxCount, fnAck->vecInfo);
                    }
                    else
                        fnAck->eResult = eNGBRFailed;
                    if (fnAck->eResult != eNGBRSuccess)
                        fnAck(false);
                    else
                        fnAck(true);
                });
    }
    if (fnAck->eResult != eNGBRSuccess)
        return false;
    else
        return true;
}

//接收：获取战功榜个人排名信息
bool CNewGuildBattleProtS::OnRecv_GetPlayerRankInfo(
        UINT32 dwIndex, //排名索引
        UINT32 dwCount, //排名个数
        shared_func<SGetPlayerRankInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    ::CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    ENGBMountain eMountainType = eNGBMNone;
    NNewGuildBattle::CPlayerPtr pNGBPlayer = CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
    if (pNGBPlayer)
        eMountainType = pNGBPlayer->GetMountain();
    ENGBState eState = CBattleMgr::Instance().GetState();
    if (eState != eNGBSBattle)
    {
        fnAck->eResult = eNGBRWrongTime;
        return false;
    }
    CPlayerRankMgrPtr pRankMgr = CBattleMgr::Instance().GetPlayerRankMgr();
    if (!pRankMgr)
    {
        fnAck->eResult = eNGBRFailed;
        return false;
    }
    fnAck->eResult = pRankMgr->GetRankInfo(eMountainType, dwIndex, dwCount, 
            fnAck->dwCurIndex, fnAck->dwMaxCount, fnAck->vecInfo);
    if (fnAck->eResult != eNGBRSuccess)
        return false;
    else
        return true;
}


//接收：召集帮众广播
bool CNewGuildBattleProtS::OnRecv_CallMember(
        shared_func<SCallMemberAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	::CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    UINT64 qwRoleID = pUser->GetRoleID();
    string strName = pUser->GetUserName();
    UINT8 byQuality = pPlayer->GetColor();
    switch (CBattleMgr::Instance().GetState())
    {
        case eNGBSBattle: //帮派战进行中
            g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
                    [fnAck, qwRoleID, this, strName, byQuality](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                if (byRet == 0)
                {
                    g_Game2CenterGuildBattleC.Send_GetAuthority(qwRoleID,
                            [fnAck,qwRoleID, qwGuildID, this, strName, byQuality](UINT8 byRet, bool bHasAuthority)
                            {
                                if (byRet == 0)
                                {
                                    if (bHasAuthority)
                                    {
                                        string strData = BuildPkg_CallMemberNotify(byQuality, strName);
                                        TVecUINT64 vecRoleID;
                                        CBattleMgr::Instance().GetAllGuildPlayer(qwGuildID, vecRoleID);
                                        vecRoleID.push_back(qwRoleID);
                                        g_Game2CenterCommC.Send_NotifyGuildInfo(qwGuildID, vecRoleID, strData);
                                    }
                                    else
                                        fnAck->eResult = eNGBRNoAuthority;
                                }
                                else
                                    fnAck->eResult = eNGBRFailed;
                                if (fnAck->eResult == eNGBRSuccess)
                                    fnAck(true);
                                else
                                    fnAck(false);
                            });
                }
                else
                {
                    LOG_DBG << "byRet = " << static_cast<UINT32>(byRet) << ".";
                    fnAck->eResult = eNGBRNoGuild;
                    fnAck(false);
                }
            });
            break;
        case eNGBSNone: //没有开启帮派战
        case eNGBSReady: //帮派战即将开启，倒计时通知阶段
        case eNGBSBattleEnd: //帮派战战役结束
        default:
            fnAck->eResult = eNGBRWrongTime;
            break;

    }
    return true;
}
void CNewGuildBattleProtS::SystemMsg(ENGBResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBEnterResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBGateAttackResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBBuyPuppetResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBClearDeadCDResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBCaveAttackResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBQuitResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
void CNewGuildBattleProtS::SystemMsg(ENGBBattleResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {   
        default:
            break;
    }   
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
CNewGuildBattleProtS g_NewGuildBattleProtS;

