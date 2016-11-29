#include "GuildBattleProtS.h"

#include "stdafx.h"

#include "User.h"
#include "Protocols.h"
#include "GuildBattleMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

using namespace NGame2CenterGuildBattle;

CGuildBattleProtS::~CGuildBattleProtS()
{
}

//接收：帮派战报名
bool CGuildBattleProtS::OnRecv_SignUp(
        EGBSpot eSpotType, //据点类型
        shared_func<SSignUpAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterGuildBattleC.Send_UserSignUp(pUser->GetUserID(), 
            [fnAck, pPlayer, eSpotType](UINT8 byRet, UINT64 qwGuildID, UINT16 wLevel, const string& strGuildName, UINT32 dwScore, EGBSignUpResult eResult)
            {
                if (byRet == 0)
                {
                    if (fnAck->eResult == eGBSignUpSuccess)
                        CGuildBattleMgr::Instance().UserSignUp(pPlayer, qwGuildID, wLevel, strGuildName, dwScore, eSpotType, fnAck->eResult);
                    else
                        fnAck->eResult = eResult;
                }
                else if (byRet == 1)
                    fnAck->eResult = eResult;
                else
                    fnAck->eResult = eGBSignUpFailed;
                fnAck(true);
            }
            );
    return true;
}

//接收：进入帮派战
bool CGuildBattleProtS::OnRecv_Enter(
        shared_func<SEnterAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    CGuildBattleMgr::Instance().UserEnter(pPlayer, fnAck->eResult);
    if (fnAck->eResult == eGBEnterSuccess)
        return true;
    else
        return false;
}

//接收：帮派战退出
bool CGuildBattleProtS::OnRecv_Quit(
        shared_func<SQuitAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    return CGuildBattleMgr::Instance().UserQuit(pPlayer, fnAck->eResult);
}

//接收：帮派成员调整
bool CGuildBattleProtS::OnRecv_AdjustMember(
        UINT64 qwRoleID, //成员角色ID
        EGBSpot eSpotType, //目标据点类型
        UINT8 byIndex, //新目标对应位置(从1开始)
        shared_func<SAdjustMemberAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterGuildBattleC.Send_GetAuthority(pUser->GetUserID(),
            [fnAck, pPlayer, qwRoleID, eSpotType, byIndex](UINT8 byRet, bool bHasAuthority)
            {
                if (byRet == 0)
                {
                    if (!bHasAuthority)
                    {
                        fnAck->eResult = eGBAdjustNoAuthority;
                        string strPkg;
                        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgGuildNotPosition);
                        pPlayer->SendPkg(strPkg);
                    }
                    else
                        CGuildBattleMgr::Instance().UserAdjust(pPlayer, qwRoleID, eSpotType, byIndex, fnAck->eResult);
                }
                else
                {
                    fnAck->eResult = eGBAdjustFailed;
                }
                if (fnAck->eResult == eGBAdjustSuccess)
                    fnAck(true);
                else
                    fnAck(false);
            });
    fnAck->eResult = eGBAdjustFailed;
    return true;
}

//接收：帮派战场信息
bool CGuildBattleProtS::OnRecv_GetFieldInfo(
        shared_func<SGetFieldInfoAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
            [fnAck, pPlayer](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                if (byRet == 0)
                {
                    bool bRet = CGuildBattleMgr::Instance().GetFieldInfo(pPlayer, qwGuildID, strGuildName, fnAck->eResult, fnAck->vecFieldInfo);
                    fnAck(bRet);
                }
                else
                {
                    LOG_DBG << "byRet = " << static_cast<UINT32>(byRet) << ".";
                    fnAck->eResult = eGBResultFailed;
                    fnAck(false);
                }
            });
    fnAck->eResult = eGBResultFailed;
    return false;
}

//接收：帮派据点信息
bool CGuildBattleProtS::OnRecv_GetSpotInfo(
        EGBSpot eType, //据点类型
        shared_func<SGetSpotInfoAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    return CGuildBattleMgr::Instance().GetSpotInfo(pPlayer, eType, fnAck->vecSpotInfo, fnAck->eResult);
}

//接收：获取帮派战状态
bool CGuildBattleProtS::OnRecv_GetState(
        shared_func<SGetStateAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
            [fnAck, pPlayer](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                if (byRet == 0)
                {
                    fnAck->eState = CGuildBattleMgr::Instance().GetState();
                    fnAck->byBattleCount = CGuildBattleMgr::Instance().GetBattleCount();
                    fnAck->dwRemainTime  = CGuildBattleMgr::Instance().GetRemainTime();
                    fnAck->bGuildJoined  = CGuildBattleMgr::Instance().IsGuildJoined(qwGuildID);
                    fnAck->eSpotType     = CGuildBattleMgr::Instance().GetSpotType(pPlayer);
                    fnAck->eSelfSide     = CGuildBattleMgr::Instance().GetSpotSide(pPlayer);
                    fnAck(true);
                }
                else
                {
                    fnAck->eState = CGuildBattleMgr::Instance().GetState();
                    fnAck->byBattleCount = CGuildBattleMgr::Instance().GetBattleCount();
                    fnAck->dwRemainTime  = CGuildBattleMgr::Instance().GetRemainTime();
                    fnAck->bGuildJoined  = CGuildBattleMgr::Instance().IsGuildJoined(qwGuildID);
                    fnAck->eSelfSide     = eGBSideInvalid;
                    fnAck(false);
                }
            });
    return true;
}

//接收：据点战报获取
bool CGuildBattleProtS::OnRecv_GetSpotBattle(
        EGBSpot eType, //据点类型
        shared_func<SGetSpotBattleAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    return CGuildBattleMgr::Instance().GetBattleInfo(pPlayer, eType, fnAck->eResult, fnAck->vecBattleData);
}

//接收：帮派战技能信息获取
bool CGuildBattleProtS::OnRecv_GetSkillInfo(
        shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
            [fnAck, pPlayer](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                if (byRet == 0)
                {
                    bool bRet = CGuildBattleMgr::Instance().GetSkillInfo(pPlayer, qwGuildID, fnAck->eResult, fnAck->vecSkillInfo);
                    fnAck(bRet);
                }
                else
                {
                    fnAck->eResult    = eGBSkillFailed;
                    fnAck(false);
                }
            });
    return true;
}

//接收：帮派购买技能结果
bool CGuildBattleProtS::OnRecv_BuySkill(
        EGBSkill eType, //购买的技能类型
        shared_func<SBuySkillAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
            [fnAck, pPlayer, eType](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                if (byRet == 0)
                {
                    bool bRet =  CGuildBattleMgr::Instance().BuySkill(pPlayer, qwGuildID, eType, fnAck->eResult);
                    fnAck(bRet);
                }
                else
                {
                    fnAck->eResult    = eGBSkillFailed;
                    fnAck(false);
                }
            });
    return true;
}

//接收：获取帮派战小面板信息
bool CGuildBattleProtS::OnRecv_GetPanelInfo(
        shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    g_Game2CenterGuildBattleC.Send_GetPanelInfo(pUser->GetUserID(),
            [fnAck, pPlayer](UINT8 byRet, UINT32 dwSelfScore, UINT32 dwGuildScore, UINT32 dwGuildRank)
            {
                //fnAck->dwSelfScore = dwSelfScore;
                fnAck->dwGuildScore = dwGuildScore;
                fnAck->dwGuildRank = dwGuildRank;
                fnAck->dwSelfScore = CGuildBattleMgr::Instance().GetPlayerScore(pPlayer->GetRoleID());
                //fnAck->dwGuildScore = CGuildBattleMgr::Instance().GetGuildScore(qwGuildID);
                //fnAck->dwGuildRank = CGuildBattleMgr::Instance().GetGuildRank(qwGuildID);
                if (byRet == 0)
                    fnAck(true);
                else
                    fnAck(false);
            });
    return true;
}

//接收：召集帮众广播
bool CGuildBattleProtS::OnRecv_CallMember(
        shared_func<SCallMemberAck>& fnAck //返回回调函数
        )
{
	CUserPtr pUser;
	CPlayerPtr pPlayer;
	if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    UINT64 qwRoleID = pUser->GetRoleID();
    string strName = pUser->GetUserName();
    UINT8 byQuality = pPlayer->GetColor();
    switch (CGuildBattleMgr::Instance().GetState())
    {
        case eGBStateReady: //帮派战即将开启，报名阶段
        case eGBStatePrepare: //帮派战准备中
        case eGBStateBattle: //帮派战进行中
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
                                        CGuildBattleMgr::Instance().GetAllMapPlayers(qwGuildID, vecRoleID);
                                        CGuildBattleMgr::Instance().GetAllOB(qwGuildID, vecRoleID);
                                        vecRoleID.push_back(qwRoleID);
                                        g_Game2CenterCommC.Send_NotifyGuildInfo(qwGuildID, vecRoleID, strData);
                                    }
                                    else
                                        fnAck->eResult = eGBResultNoAuthority;
                                }
                                else
                                    fnAck->eResult = eGBResultFailed;
                                if (fnAck->eResult == eGBResultSuccess)
                                    fnAck(true);
                                else
                                    fnAck(false);
                            });
                }
                else
                {
                    LOG_DBG << "byRet = " << static_cast<UINT32>(byRet) << ".";
                    fnAck->eResult = eGBResultNoGuild;
                    fnAck(false);
                }
            });
            break;
        case eGBStateNone: //没有开启或即将开启的帮派战
        case eGBStatePreReady: //帮派战报名即将开启
        case eGBStateBattleEnd: //帮派战战役结束
        default:
            fnAck->eResult = eGBResultWrongTime;
            break;

    }
    return true;
}
