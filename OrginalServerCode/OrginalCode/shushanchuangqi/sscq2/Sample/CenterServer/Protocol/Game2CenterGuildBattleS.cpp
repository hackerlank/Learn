#include "Game2CenterGuildBattleS.h"
#include "GuildBattleProt.h"

#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "Guild.h"
#include "GuildMgr.h"

using namespace NGuildBattleProt;

CGame2CenterGuildBattleS::~CGame2CenterGuildBattleS()
{
}

//接收：帮派战状态设定
void CGame2CenterGuildBattleS::OnRecv_SetState(
        NGuildBattleProt::EGBState eState //当前帮派战状态
        )
{
    switch(eState)
    {
        case eGBStateReady: //帮派战即将开启，报名阶段
        case eGBStatePrepare: //帮派战准备中
        case eGBStateBattle: //帮派战进行中
            CGuildMgr::Instance().SetGuildOpEnable(false, CGuildMgr::eOPDGuildBattle);
            break;
        case eGBStateBattleEnd: //帮派战战役结束
        case eGBStateNone: //帮派战战役结束
            CGuildMgr::Instance().SetGuildOpEnable(true, CGuildMgr::eOPDNone);
            break;
        default:
            break;
    }
}

//接收：帮派战用户报名
bool CGame2CenterGuildBattleS::OnRecv_UserSignUp(
        UINT64 qwRoleID, //玩家ID
        shared_func<SUserSignUpAck>& fnAck //返回回调函数
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
    {
        fnAck->eResult = eGBSignUpNotInGuild;
        return false;
    }
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGBSignUpNotInGuild;
        return false;
    }
    fnAck->qwGuildID = pGuild->GetID();
    fnAck->strGuildName = pGuild->GetName();
    fnAck->wLevel = pGuild->GetLevel();
    fnAck->dwScore  = pGuild->GetBattleScore();
    fnAck->eResult = eGBSignUpSuccess;
    return true;
}
//接收：帮派战相关广播
void CGame2CenterGuildBattleS::OnRecv_InfoNotify(
        UINT64 qwGuildID, //帮派对应ID
        UINT16 wMsgID, //消息ID
        const TVecString& vecStr //聊天信息参数
        )
{
    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
    if (!pGuild)
        return;
    pGuild->NotifyIDInfo(wMsgID, vecStr);
}

//接收：是否有帮派战操作权限
bool CGame2CenterGuildBattleS::OnRecv_GetAuthority(
        UINT64 qwRoleID, //玩家ID
        shared_func<SGetAuthorityAck>& fnAck //返回回调函数
        )
{
    fnAck->bHasAuthority = true;
    return true;
}

//接收：增加帮派战积分
void CGame2CenterGuildBattleS::OnRecv_AddScore(
        UINT64 qwGuildID, //帮派ID
        UINT32 dwScore, //帮派战积分
        const TVecMemberScore& vecMemberScore //玩家获得积分
        )
{
    LOG_DBG << "OnRecv_AddScore : " << qwGuildID << ".";
    CGuildMgr::Instance().AddBattleScore(qwGuildID, dwScore, vecMemberScore);
}

//接收：增加帮派战帮派积分
void CGame2CenterGuildBattleS::OnRecv_AddGuildScore(
        UINT64 qwGuildID, //帮派ID
        UINT32 dwScore //帮派战积分
        )
{
    CGuildMgr::Instance().AddGuildBattleScore(qwGuildID, dwScore);

}
//接收：增加帮派战成员积分
void CGame2CenterGuildBattleS::OnRecv_AddMemberScore(
        UINT64 qwGuildID, //帮派ID
        const TVecMemberScore& vecMemberScore //玩家获得积分
        )
{
    CGuildMgr::Instance().AddMemberBattleScore(qwGuildID, vecMemberScore);
}

//接收：获取帮派战相关面板信息
bool CGame2CenterGuildBattleS::OnRecv_GetPanelInfo(
        UINT64 qwRoleID, //玩家ID
        shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
        )
{
    return CGuildMgr::Instance().GetBattlePanelInfo(qwRoleID, fnAck->dwSelfScore, fnAck->dwGuildScore, fnAck->dwGuildRank);
}

//接收：更新帮派战积分排名
void CGame2CenterGuildBattleS::OnRecv_SyncGuildRank(
        )
{
    CGuildMgr::Instance().SyncBattleRank();
}

// =====================================================================================
// 这里是新帮派战

//接收：帮派战状态设定
void CGame2CenterGuildBattleS::OnRecv_NewSetState(
        NNewGuildBattleProt::ENGBState eState //当前帮派战状态
        )
{
    switch(eState)
    {
        case NNewGuildBattleProt::eNGBSBattle: //帮派战进行中
            CGuildMgr::Instance().SetGuildOpEnable(false, CGuildMgr::eOPDNewGuildBattle);
            break;
        case NNewGuildBattleProt::eNGBSNone: //没有开启帮派战
        case NNewGuildBattleProt::eNGBSReady: //帮派战即将开启，倒计时通知阶段
        case NNewGuildBattleProt::eNGBSBattleEnd: //帮派战战役结束
        default:
            CGuildMgr::Instance().SetGuildOpEnable(true, CGuildMgr::eOPDNone);
            break;
    }
}

//接收：获取帮派ID
bool CGame2CenterGuildBattleS::OnRecv_NewGetGuildID(
        UINT64 qwRoleID, //玩家ID
        shared_func<SNewGetGuildIDAck>& fnAck //返回回调函数
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (pGuildUser)
    {
        fnAck->qwGuildID = pGuildUser->GetGuildID();
        CGuildPtr pGuild = pGuildUser->GetGuild();
        if (pGuild)
        {
            fnAck->strGuildName = pGuild->GetName();
            fnAck->byGuildLvl = pGuild->GetLevel();
        }
    }
    else
        fnAck->qwGuildID = 0;
    return true;
}

// 这里是新帮派战
// =====================================================================================

