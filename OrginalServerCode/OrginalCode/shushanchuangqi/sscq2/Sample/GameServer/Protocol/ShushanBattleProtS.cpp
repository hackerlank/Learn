
#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "ShushanBattle.h"
#include "ShushanBattleMgr.h"
#include "ShushanBattleProtS.h"
#include "GameNetMgr.h"

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

//接收：蜀山论剑准备/开始/结束信息
void CShushanBattleProtS::OnRecv_GetBattleStartInfo(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;

    ShushanBattleMgr.SendBattleStatusInLogin(pPlayer);
}

//接收：请求蜀山论剑玩家的配对信息
void CShushanBattleProtS::OnRecv_GetPlayerPairInfo(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;
	if (!ShushanBattleMgr.IsRunning())
		return;

    ShushanBattle.SendSelfInfo(pPlayer);
}

//接收：请求连杀王、荣誉王信息
void CShushanBattleProtS::OnRecv_GetFirstPlayer(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;
	if (!ShushanBattleMgr.IsRunning())
		return;

    ShushanBattle.GetFirstPlayer(pPlayer);
}

//接收：参加蜀山论剑活动
bool CShushanBattleProtS::OnRecv_PlayerEnter(
    shared_func<SPlayerEnterAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eSSBattle_OtherErr;
        return false;
    }

    fnAck->eResult = ShushanBattle.PlayerEnter(pPlayer);
    return true;
}

//接收：退出蜀山论剑活动
bool CShushanBattleProtS::OnRecv_PlayerLeave(
    shared_func<SPlayerLeaveAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eSSBattle_OtherErr;
        return false;
    }

    fnAck->eResult = ShushanBattle.PlayerLeave(pPlayer);
    return true;
}

//接收：使用蜀山论剑技能
bool CShushanBattleProtS::OnRecv_UseSkill(
    UINT8 bySkillID, //技能ID
    shared_func<SUseSkillAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    fnAck->bySkillID = bySkillID;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eSSBattle_OtherErr;
        return false;
    }

    fnAck->eResult = ShushanBattle.UseSkill(pPlayer, bySkillID);
    return true;
}

//接收：购买蜀山论剑霸气or怒气
bool CShushanBattleProtS::OnRecv_BuySkill(
    UINT8 byFlag, //购买类型:0霸气 1怒气
    shared_func<SBuySkillAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    fnAck->byFlag = byFlag;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eSSBattle_OtherErr;
        return false;
    }

    fnAck->eResult = ShushanBattle.BuySkill(pPlayer, byFlag);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
