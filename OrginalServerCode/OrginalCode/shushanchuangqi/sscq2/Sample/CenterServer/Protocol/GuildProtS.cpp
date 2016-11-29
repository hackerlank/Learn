#include "GuildProtS.h"
#include "stdafx.h"
#include "Protocols.h"
#include "GuildMgr.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "UserMgr.h"
#include "GuildBuilding.h"
#include "GuildTech.h"
#include "GuildStatue.h"
#include "SysMsgDefine.h"
#include "EventCenter.h"
#include "Parameter.h"
#include "GuildXihe.h"
#include "GuildXiheManager.h"

using namespace NEventCenter;

static void NotifyResultErrorMsg(UINT64 qwRoleID, EApplyResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, ECreateResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EQuitResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, ESetAuthorityResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EEditInfoResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EMemberOperateResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EImpeachResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EGuildResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EBuildingResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, ETechResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EDonateResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EStatueResult eResult);
static void NotifyResultErrorMsg(UINT64 qwRoleID, EGuildXiheResult eResult);
//static void NotifyResultErrorMsg(UINT64 qwRoleID, EWorshipResult eResult);

//接收：获取帮派面板信息
bool CGuildProtS::OnRecv_GetGuildInfo(
        shared_func<SGetGuildInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return false;

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser || !pGuildUser->GetGuild())
    {
        SOtherGuildListInfoPtr pOtherGuildListInfo (new SOtherGuildListInfo);
        CGuildMgr::Instance().GetListInfo(0, 0, *pOtherGuildListInfo, pGuildUser);

        fnAck->sGuildInfoBase = dynamic_pointer_cast<SOtherGuildListInfo>(pOtherGuildListInfo);
    }
    else
    {
        CGuildPtr pGuild = pGuildUser->GetGuild();
        SSelfGuildInfoPtr pSelfGuildInfo(new SSelfGuildInfo);
        pGuild->GetAllInfo(pSelfGuildInfo->sAllInfo, pGuildUser);
        pGuildUser->TryGetImpeach();

        fnAck->sGuildInfoBase = dynamic_pointer_cast<SGetGuildInfoBase>(pSelfGuildInfo);
    }
    return true;
}

//接收：获得帮派列表
bool CGuildProtS::OnRecv_GetGuildList(
        UINT32 dwIndex, //帮派索引
        UINT32 dwCount, //帮派个数
        shared_func<SGetGuildListAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return false;

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    CGuildMgr::Instance().GetListInfo(dwIndex, dwCount, fnAck->sListInfo, pGuildUser);
    return true;
}

//接收：获取帮派申请列表信息
bool CGuildProtS::OnRecv_GetGuildApplyInfo(
        shared_func<SGetGuildApplyInfoAck>& fnAck //返回回调函数
        )
{
    return true;
}

//接收：创建帮派
bool CGuildProtS::OnRecv_CreateGuild(
        const std::string& strName, //帮派名称
        shared_func<SCreateGuildAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();

    UINT32 dwServerID = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser)
        dwServerID = pUser->GetGameSvrID();
    else
        return false;


    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (pGuildUser && pGuildUser->GetGuild())
    {
        fnAck->eResult = eGCreateInGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    }
    else
    {
        CGuildMgr::Instance().CreateGuild(qwRoleID, strName, fnAck->eResult,
                [fnAck, qwRoleID, dwServerID](UINT8 byRet, CGuildPtr pGuild)
                {
                if (byRet == 0)
                {
                if (pGuild)
                {
                CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
                SGuildAllInfo sGuildAllInfo;
                pGuild->GetAllInfo(sGuildAllInfo, pGuildUser);
                fnAck->vecGuildInfo.push_back(sGuildAllInfo);
                fnAck->eResult = eGCreateSuccess;
                fnAck(true);
                TVecINT32 vecParam;
                vecParam.push_back(pGuild->GetID()); // FIXME: 这里要改成64位的
                g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1,qwRoleID ,eEventType_GuildCreation ,vecParam, "", true);
                }
                else
                fnAck->eResult = eGCreateFailed;
                }
                else if (byRet == 1)
                    fnAck->eResult = eGCreateLackOfGold;
                else
                    fnAck->eResult = eGCreateFailed;
                NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
                });
    }

    return true;
}

//接收：申请加入帮派
bool CGuildProtS::OnRecv_ApplyGuild(
        UINT64 qwGuildID, //帮派ID
        shared_func<SApplyGuildAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
    {
        pGuildUser = CGuildUserMgr::Instance().CreateGuildUser(pUser);
        CGuildUser::Update2DB(pGuildUser, eOpAdd);
    }

    if (!pGuildUser)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }
    if(pGuildUser->GetGuild())
    {
        fnAck->eResult = eGApplyInGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    if (pGuildUser->GetApplyInfo(qwGuildID))
    {
        fnAck->eResult = eGApplyAlreadyApplyed;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = CGuildMgr::Instance().ApplyForGuild(qwGuildID, pGuildUser, fnAck->eResult, 
            [fnAck, qwRoleID](EApplyResult eResult)
            {
            fnAck->eResult = eResult;
            if (eResult == eGApplySuccess)
            fnAck(true);
            else
            fnAck(false);
            NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
            });
    if (!bRet)
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    return true;
}

//接收：通过加入申请
bool CGuildProtS::OnRecv_AgreeApply(
        UINT64 qwRoleID, //申请者ID
        shared_func<SAgreeApplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;
    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)     
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    if (!pUser->HasAuthority(G_INVITE_MEMBER))
    {
        fnAck->eResult = eGApplyNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = pGuild->AgreeApply(qwRoleID, pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：全部同意
bool CGuildProtS::OnRecv_AgreeApplyAll(
        shared_func<SAgreeApplyAllAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)     
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    if (!pUser->HasAuthority(G_INVITE_MEMBER))
    {
        fnAck->eResult = eGApplyNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    pGuild->AgreeApplyAll(pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：拒绝加入申请
bool CGuildProtS::OnRecv_RejectApply(
        UINT64 qwRoleID, //申请者ID
        shared_func<SRejectApplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)     
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    if (!pUser->HasAuthority(G_INVITE_MEMBER))
    {
        fnAck->eResult = eGApplyNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    pGuild->RejectApply(qwRoleID, pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：全部拒绝
bool CGuildProtS::OnRecv_RejectApplyAll(
        shared_func<SRejectApplyAllAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)     
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    if (!pUser->HasAuthority(G_INVITE_MEMBER))
    {
        fnAck->eResult = eGApplyNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    pGuild->RejectApplyAll(pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：邀请加入
bool CGuildProtS::OnRecv_InviteApply(
        const std::string& strName, //被邀请者名字
        shared_func<SInviteApplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGApplyNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    if (!pUser->HasAuthority(G_INVITE_MEMBER))
    {
        fnAck->eResult = eGApplyNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = pGuild->InviteOther(pUser, strName, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}


//接收：获得已申请帮派列表
bool CGuildProtS::OnRecv_GetGuildApplyList(
        shared_func<SGetGuildApplyListAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (pGuildUser)     
    {
        CGuildPtr pGuild = pGuildUser->GetGuild();
        if (pGuild)
            fnAck->eResult = eGApplyInGuild;
        else
        {
            TVecUINT64 vecGuildID;
            if (pGuildUser->GetApplyGuildID(vecGuildID))
            {
                for (auto& rID : vecGuildID)
                {
                    CGuildListInfoPtr pListInfo = CGuildMgr::Instance().GetListInfo(rID);
                    if (pListInfo)
                    {
                        SGuildListInfo sInfo;
                        if (pListInfo->GetAllInfo(sInfo))
                            fnAck->vecGuildListInfo.push_back(sInfo);
                    }
                }
                fnAck->eResult = eGApplySuccess;
            }
        }
    }
    else
        fnAck->eResult = eGApplySuccess;

    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：撤销帮派申请
bool CGuildProtS::OnRecv_CancelApply(
        UINT64 qwGuildID, //帮派ID
        shared_func<SCancelApplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
    if (!pGuild)
        fnAck->eResult = eGApplyNoGuild;
    else
        pGuild->CancelApply(qwOpRoleID, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    if (fnAck->eResult == eGApplySuccess)
        return true;
    else
        return false;
}


bool CGuildProtS::OnRecv_InviteReply(
        UINT64 qwGuildID, //帮派ID
        bool bAgree, //同意/拒绝
        shared_func<SInviteReplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }

    if (!bAgree) // XXX: 这里拒绝直接返回
    {
        fnAck->eResult = eGApplySuccess;
        return true;
    }

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
    {
        pGuildUser = CGuildUserMgr::Instance().CreateGuildUser(pUser);
        CGuildUser::Update2DB(pGuildUser, eOpAdd);
    }
    if (!pGuildUser)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (pGuild)
    {
        fnAck->eResult = eGApplyInGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
    if (!pGuild)
    {
        fnAck->eResult = eGApplyFailed;
        return false;
    }
    bool bRet = pGuild->InviteReply(bAgree, pGuildUser, fnAck->eResult);
    NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    return bRet;
}

//接收：退出帮派
bool CGuildProtS::OnRecv_QuitGuild(
        shared_func<SQuitGuildAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGQuitFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGQuitNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = pGuild->QuitGuild(pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：设置权限
bool CGuildProtS::OnRecv_SetAuthority(
        EMemberRank eRank, //新职位
        UINT32 dwAuthority, //可选权限
        shared_func<SSetAuthorityAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGSetAuthorityNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGSetAuthorityNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = pGuild->SetMemberAuthority(eRank, dwAuthority, pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：编辑公告
bool CGuildProtS::OnRecv_EditInfo(
        const std::string& strInfo, //公告信息
        shared_func<SEditInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGEditInfoNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGEditInfoNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    if (pUser->GetRank() <= eMemberViceOwner)
    {
        fnAck->eResult = eGEditInfoNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet = pGuild->EditInfo(strInfo, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：帮派成员操作
bool CGuildProtS::OnRecv_MemberOperate(
        UINT64 qwRoleID, //被设置者ID
        EMemberOperateType eOpType, //操作类型
        shared_func<SMemberOperateAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGMOpResultFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGMOpResultNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    switch (eOpType)
    {
        case eGMOpTypeKick:
            {
                if (!pUser->HasAuthority(G_FIRE_MEMBER))
                {
                    fnAck->eResult = eGMOpResultNoAuthority;
                    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                    return false;
                }
                bool bRet = pGuild->KickMember(qwRoleID, pUser, fnAck->eResult);
                NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                return bRet;
            }
            break;
        case eGMOpTypeGiveOwner:
            {
                if (pUser->GetRank() != eMemberOwner)
                {
                    fnAck->eResult = eGMOpResultTooLow;
                    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                    return false;
                }
                bool bRet =  pGuild->GiveOwner(qwRoleID, pUser, fnAck->eResult);
                NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                return bRet;
            }
            break;
        case eGMOpTypeUp:
            {
                if (!pUser->HasAuthority(G_IMPROVE_MEMBER))
                {
                    fnAck->eResult = eGMOpResultNoAuthority;
                    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                    return false;
                }
                bool bRet = pGuild->UpMemberRank(qwRoleID, pUser, fnAck->eResult);
                NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                return bRet;
            }
            break;
        case eGMOpTypeDown:
            {
                if (!pUser->HasAuthority(G_IMPROVE_MEMBER))
                {
                    fnAck->eResult = eGMOpResultNoAuthority;
                    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                    return false;
                }
                bool bRet = pGuild->DownMemberRank(qwRoleID, pUser, fnAck->eResult);
                NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                return bRet;
            }
            break;
        case eGMOpTypeFire:
            {
                if (!pUser->HasAuthority(G_IMPROVE_MEMBER))
                {
                    fnAck->eResult = eGMOpResultNoAuthority;
                    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                    return false;
                }
                bool bRet =  pGuild->FireMemberRank(qwRoleID, pUser, fnAck->eResult);
                NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
                return bRet;
            }
            break;
        default:
            break;
    }
    fnAck->eResult = eGMOpResultFailed;
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return false;
}
//接收：弹劾回应
bool CGuildProtS::OnRecv_ImpeachReply(
        UINT64 qwGuildID, //帮派ID
        bool bAgree, //同意/拒绝
        shared_func<SImpeachReplyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
        CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;
    ;
    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGImpeachResultFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGImpeachResultNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    if (pGuild->GetID() != qwGuildID)
    {
        fnAck->eResult = eGImpeachResultWrongGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    bool bRet =  pGuild->ImpeachReply(bAgree, pUser, fnAck->eResult);
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：发起弹劾
bool CGuildProtS::OnRecv_LaunchImpeach(
        shared_func<SLaunchImpeachAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGImpeachResultFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGImpeachResultNotInGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    return pGuild->LaunchImpeach(pUser, fnAck->eResult, 
            [fnAck, qwOpRoleID](UINT8 byRet)
            {
            if (byRet == 0)
            {
            fnAck->eResult = eGImpeachResultSuccess;
            fnAck(true);
            }
            else if (byRet == 1)
            fnAck->eResult = eGImpeachResultLackOfGold;
            else
            fnAck->eResult = eGImpeachResultFailed;
            NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
            });
}

//接收：搜索帮派
bool CGuildProtS::OnRecv_SearchGuildByName(
        const std::string& strName, //帮派名称
        shared_func<SSearchGuildByNameAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    TVecUINT64 vecGuildID;
    CGuildMgr::Instance().GetGuildIDGrep(strName, vecGuildID);
    if (vecGuildID.empty())
    {
        fnAck->eResult = eGuildNotExisted;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    for (auto it = vecGuildID.begin(); it != vecGuildID.end(); ++it)
    {
        CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(*it);
        if (!pGuildListInfo)
        {
            continue;
            //fnAck->eResult = eGuildNotExisted;
            //return false;
        }
        SGuildListInfo sGuildListInfo;
        if (!pGuildListInfo->GetAllInfo(sGuildListInfo))
        {
            continue;
            //fnAck->eResult = eGuildFailed;
            //return false;
        }
        fnAck->vecGuildListInfo.push_back(sGuildListInfo);
    }
    fnAck->eResult = eGuildSuccess;
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：搜索帮派
bool CGuildProtS::OnRecv_SearchGuildByOwnerName(
        const std::string& strOwnerName, //帮主名称
        shared_func<SSearchGuildByOwnerNameAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    TVecUINT64 vecGuildID;
    CGuildMgr::Instance().GetGuildIDByOwnerNameGrep(strOwnerName, vecGuildID);
    if (vecGuildID.empty())
    {
        fnAck->eResult = eGuildNotExisted;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    for (auto it = vecGuildID.begin(); it != vecGuildID.end(); ++it)
    {
        CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(*it);
        if (!pGuildListInfo)
        {
            continue;
            //fnAck->eResult = eGuildNotExisted;
            //return false;
        }
        SGuildListInfo sGuildListInfo;
        if (!pGuildListInfo->GetAllInfo(sGuildListInfo))
        {
            continue;
            //fnAck->eResult = eGuildFailed;
            //return false;
        }
        fnAck->vecGuildListInfo.push_back(sGuildListInfo);
    }
    fnAck->eResult = eGuildSuccess;
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：根据帮主搜索帮派
bool CGuildProtS::OnRecv_SearchGuildByBothName(
        const std::string& strName, //帮派名称
        const std::string& strOwnerName, //帮主名称
        shared_func<SSearchGuildByBothNameAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    TVecUINT64 vecGuildID;
    if (strName.empty())
        CGuildMgr::Instance().GetGuildIDByOwnerNameGrep(strOwnerName, vecGuildID);
    else if (strOwnerName.empty())
        CGuildMgr::Instance().GetGuildIDGrep(strName, vecGuildID);
    else
        CGuildMgr::Instance().GetGuildIDByBothNameGrep(strName, strOwnerName, vecGuildID);
    if (vecGuildID.empty())
    {
        fnAck->eResult = eGuildNotExisted;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    for (auto it = vecGuildID.begin(); it != vecGuildID.end(); ++it)
    {
        CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(*it);
        if (!pGuildListInfo)
            continue;
        SGuildListInfo sGuildListInfo;
        if (!pGuildListInfo->GetAllInfo(sGuildListInfo))
            continue;
        fnAck->vecGuildListInfo.push_back(sGuildListInfo);
    }
    fnAck->eResult = eGuildSuccess;
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return true;
}

//接收：提升帮派建筑等级
bool CGuildProtS::OnRecv_UpgradeBuilding(
        EBuildingType eBuildingType, //帮派建筑类型
        shared_func<SUpgradeBuildingAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pGuildUser)
    {
        fnAck->eResult = eGBuildingResultFailed;
        return false;
    }
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGBuildingResultNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    if (!pGuild->HaveAuthority(pGuildUser, G_A_BUILD))
    {
        fnAck->eResult = eGBuildingResultNoAuthority;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildBuildingOwnerPtr pBuildingOwner = pGuild->GetBuildingOwner();
    if (!pBuildingOwner)
    {
        fnAck->eResult = eGBuildingResultFailed;
        return false;
    }
    bool bRet = pBuildingOwner->UpgradeBuilding(eBuildingType, fnAck->eResult);
    if (fnAck->eResult == eGBuildingResultSuccess)
    {
        //帮派id，建筑id，建筑等级
        CUserPtr pUser = pGuildUser->GetOnlineUser();
        TVecINT32 vecParam2;
        ostringstream strInfo2;
        vecParam2.push_back(eBuildingType);
        vecParam2.push_back(pBuildingOwner->GetLevel(eBuildingType));
        strInfo2 << pGuildUser->GetGuildID();

        if (pUser && pUser->IsOnLine())
        {
            pUser->OnEvent(eEventType_GuildBuildingUpgrade,vecParam2, strInfo2.str());
        }
        else
        {
            CUser::AddOffLineEvent(qwOpRoleID, eEventType_GuildBuildingUpgrade,vecParam2, strInfo2.str());
        }

    }
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：提升帮派科技等级
bool CGuildProtS::OnRecv_UpgradeTech(
        ETechType eType, //帮派科技类型
        shared_func<SUpgradeTechAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGTResultFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGTResultNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildTechOwnerPtr pTechOwner = pUser->GetTechOwner();
    if (!pTechOwner)
    {
        fnAck->eResult = eGTResultFailed;
        return false;
    }
    bool bRet = pTechOwner->UpgradeTech(eType, fnAck->eResult);
    if (fnAck->eResult == eGTResultSuccess)
    {
        fnAck(true);
        pUser->UpdateTechAttr();
    }
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：帮派捐献
bool CGuildProtS::OnRecv_Donate(
        UINT32 dwMoney, //捐献数量
        shared_func<SDonateAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        LOG_WRN << "Donate error 1.";
        fnAck->eResult = eGDResultFailed;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        LOG_WRN << "Donate error 2.";
        fnAck->eResult = eGDResultNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    return pGuild->Donate(pUser, dwMoney, fnAck->eResult, [fnAck, pGuild, qwOpRoleID](UINT8 byRet)
            {
            if (byRet == 0)
            {
            fnAck->eResult = eGDResultSuccess;
            fnAck(true);
            pGuild->NotifyBaseInfo();
            }
            else if (byRet == 1)
            {
            LOG_WRN << "Donate error 4.";
            fnAck->eResult = eGDResultLackofSilver;
            }
            else
            {
            LOG_WRN << "Donate error 3.";
            fnAck->eResult = eGDResultFailed;
            }
            NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);

            });
}

//接收：帮派供奉
bool CGuildProtS::OnRecv_Worship(
        EWorshipType eType, //供奉类型
        shared_func<SWorshipAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
    {
        fnAck->eResult = eGSResultFailed;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGSResultNoGuild;
        NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
        return false;
    }
    CGuildStatueOwnerPtr pStatueOwner = pGuild->GetStatueOwner();
    if (!pStatueOwner)
    {
        fnAck->eResult = eGSResultFailed;
        return false;
    }
    return pStatueOwner->Worship(pUser, eType, fnAck->eResult, [fnAck, pGuild, qwOpRoleID](UINT8 byRet)
            {
            if (byRet == 0)
            {
            fnAck->eResult = eGSResultSuccess;
            fnAck(true);
            pGuild->NotifyStatueInfo();
            }
            else if (byRet == 1)
            {
            fnAck->eResult = eGSResultLackofSilver;
            }
            else
            {
            fnAck->eResult = eGSResultFailed;
            }
            NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
            });
}

//接收：募集帮众
bool CGuildProtS::OnRecv_Muster(
        shared_func<SMusterAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CUserPtr pOpUser = CUserMgr::GetUserByUserID(qwOpRoleID);
    if(!pOpUser)
        return false;

    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    bool bRet = true;
    if (!pUser)
    {
        fnAck->eResult = eGuildFailed;;
        return false;
    }
    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGuildNotExisted;
        bRet =  false;
    }
    else
    {
        g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgGuildJoinServer, BuildStrVec(pGuild->GetName(), pGuild->GetIDHexString(), pGuild->GetName()));
        bRet = true;
    }
    NotifyResultErrorMsg(qwOpRoleID, fnAck->eResult);
    return bRet;
}

//接收：获取羲和神车信息
void CGuildProtS::OnRecv_GetXiheInfo(
        UINT64 qwUserID //玩家ID(可为自己ID也可为帮派成员ID)
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return;
    CGuildXihePtr pGuildXihe = GuildXiheManager.GetGuildXihe(qwUserID);
    if (!pGuildXihe)
        return;
    if (qwRoleID != qwUserID)
    {
        if (!CGuildUserMgr::Instance().IsSameGuild(qwRoleID, qwUserID))
            return;
    }
    pGuildXihe->UpdateGuildXiheInfo(pUser);
}

//接收：玩家接受羲和神车任务
void CGuildProtS::OnRecv_AcceptXiheTask()
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return;
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
        return;
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return;
    CGuildXihePtr pGuildXihe = GuildXiheManager.GetGuildXihe(qwRoleID);
    if (!pGuildXihe || pGuildXihe->GetStage() != eXiheStageWaitAcess)
        return;
    pGuildXihe->SetStage(eXiheStageShipGoods);
    pGuildXihe->SetEndTime(time(NULL)+SParamConfig::dwTradeMissionTime);
    pGuildXihe->Update2DB(eOpUpdate);

    GuildXiheManager.AddXiheTimer(qwRoleID, pGuildXihe->GetEndTime());
    pGuildXihe->UpdateGuildXiheInfo(pUser);
}

//接收：获取自己帮派成员的羲和神车请求帮助列表
bool CGuildProtS::OnRecv_GetXiheRequestInfo(
        shared_func<SGetXiheRequestInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return false;
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
        return false;
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return false;
    TVecUINT64 vecUserID;
    pGuild->GetAllUserID(vecUserID);
    for (auto it = vecUserID.begin(); it != vecUserID.end(); ++ it)
    {
        GuildXiheManager.GetXiheRequestInfo(*it, fnAck->vecXiheRequest);
    }
    return true;
}

//接收：羲和神车装货
bool CGuildProtS::OnRecv_ShipGoods(
        UINT8 byType, //0:用道具装货 1:用仙石装货
        UINT8 byPos, //货物顺序索引(0~7)
        shared_func<SShipGoodsAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        fnAck->eResult = eXiheResultFailed;
        return false;
    }

    fnAck->eResult = GuildXiheManager.ShipGoods(pUser, byType, byPos, fnAck);
    NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    return true;
}

//接收：羲和神车发货
bool CGuildProtS::OnRecv_DeliveryGoods(
        shared_func<SDeliveryGoodsAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return false;

    CGuildXihePtr pGuildXihe = GuildXiheManager.GetGuildXihe(qwRoleID);
    if (!pGuildXihe || !pGuildXihe->IsFinishAllTask())
    {
        fnAck->eResult = eXiheResultUnfinish;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    fnAck->eResult = GuildXiheManager.DeliveryGoods(pGuildXihe);
    NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    return true;
}

//接收：羲和神车请求帮助装货
bool CGuildProtS::OnRecv_RequestForHelp(
        UINT8 byPos, //货物顺序索引(0~7)
        shared_func<SRequestForHelpAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
    {
        fnAck->eResult = eXiheResultFailed;
        return false;
    }
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
    {
        fnAck->eResult = eXiheResultFailed;
        return false;
    }
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eXiheResultNoGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    CGuildXihePtr pGuildXihe = GuildXiheManager.GetGuildXihe(qwRoleID);
    if (!pGuildXihe)
    {
        fnAck->eResult = eXiheResultFailed;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    if (pGuildXihe->GetFinishTaskCount() < 4)
    {
        fnAck->eResult = eXiheResultNotRequestLimit;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    if (pGuildXihe->GetRequest() >= SParamConfig::byTradeAskTimes)
    {
        fnAck->eResult = eXiheResultForHelpNumMax;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    STruckInfo& oTruckInfo = pGuildXihe->GetTruckInfoByPos(byPos);
    if (!oTruckInfo.byTruckID)
    {
        fnAck->eResult = eXiheResultNotTruck;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    if (oTruckInfo.byStatus == eXiheTaskFinishURe || oTruckInfo.byStatus == eXiheTaskFinishRe)
    {
        fnAck->eResult = eXiheResultFinish;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    if (oTruckInfo.byStatus == eXiheTaskRequest)
    {
        fnAck->eResult = eXiheResultHasRequest;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    pGuildXihe->SetTruckStatus(byPos, eXiheTaskRequest);
    pGuildXihe->AddRequest(1);
    pGuildXihe->Update2DB(eOpUpdate);
    pGuildXihe->UpdateGuildXiheInfo(pUser);
    
    SXiheRequest sXiheRequest(qwRoleID, pUser->GetUserName(),pUser->GetColor(), byPos, oTruckInfo.byTruckID, oTruckInfo.byStatus,oTruckInfo.strName,oTruckInfo.byColor);
   
  //  SXiheRequest sXiheRequest(qwRoleID, pUser->GetUserName(), byPos, oTruckInfo.byTruckID, oTruckInfo.byStatus,oTruckInfo.strName);
    //pUser->SendPkg(BuildPkg_GuildXiheHelpNotify(0, sXiheRequest));

    fnAck->eResult = eXiheResultSuccess;
    NotifyResultErrorMsg(qwRoleID, fnAck->eResult);

    TVecUINT64 vecUserID;
    pGuild->GetAllUserID(vecUserID);
    for (auto it = vecUserID.begin(); it != vecUserID.end(); ++ it)
    {
        CUserPtr pOther = CUserMgr::GetUserByUserID(*it);
        if (pOther && pOther->IsOnline())
            pOther->SendPkg(BuildPkg_GuildXiheHelpNotify(0, sXiheRequest));
    }
    return true;
}

//接收：羲和神车帮众成员帮助装货
bool CGuildProtS::OnRecv_HelpShipGoods(
        UINT8 byType, //0:用道具装货 1:用仙石装货
        UINT64 qwOtherID, //玩家ID
        UINT8 byPos, //货物顺序索引(0~7)
        shared_func<SHelpShipGoodsAck>& fnAck //返回回调函数
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    if (!qwOtherID || qwRoleID == qwOtherID)
    {
        fnAck->eResult = eXiheResultFailed;
        return false;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(!pUser)
        return false;

    if (!CGuildUserMgr::Instance().IsSameGuild(qwRoleID, qwOtherID))
    {
        fnAck->eResult = eXiheResultNoSameGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
    {
        fnAck->eResult = eXiheResultFailed;
        return false;
    }
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eXiheResultNoGuild;
        NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
        return false;
    }

    fnAck->eResult = GuildXiheManager.HelpShipGoods(pUser, byType, qwOtherID, byPos, fnAck);
    NotifyResultErrorMsg(qwRoleID, fnAck->eResult);
    return true;
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EApplyResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGApplyGuildFull: //帮派成员已满
            wMsgID = eMsgGuildFull;
            break;
        case eGApplyOtherGuild: //已加入其他帮派
            wMsgID = eMsgGuildApplyOtherGuild;
            break;
        case eGApplyInGuild: //已在帮派中
            wMsgID = eMsgCreatExisted;
            break;
        case eGApplyListFull: //申请列表已满
            wMsgID = eMsgGuildApplyListFull;
            break;
        case eGApplyNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGApplyNoGuild: //没有帮派
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGApplyNoUser: //不存在的用户
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGApplyNotOnline: //玩家不在线
            wMsgID = eMsgEUserOffline;
            break;
        case eGApplyAlreadyApplyed: //您已经发送过该申请
            wMsgID = eMsgGuildAlreadyApplyed;
            break;
        case eGApplyLevelLow: //等级过低
            wMsgID = eMsgRoleLevelErr;
            break;
        case eGApplyNoSelf: //不能邀请自己
            wMsgID = eMsgGuildApplyNoSelf;
            break;
        case eGApplyGuildBattle: //帮派战期间无法执行此操作
            wMsgID = eMsgGuildQuitGuildBattle;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    }

}

void NotifyResultErrorMsg(UINT64 qwRoleID, ECreateResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGCreateInGuild: //已经在帮派中
        case eGCreateExisted: //帮派存在
            wMsgID = eMsgCreatExisted;
            break;
        case eGCreateLackOfGold: //银币不足
            wMsgID = eMsgSilverErr;
            break;
        case eGCreateLackOfLevel: //等级不足
            wMsgID = eMsgGuildLackOfSilver;
            break;
        case eGCreateNameTooShort: //名称太短
            wMsgID = eMsgNameTooShort;
            break;
        case eGCreateNameTooLong: //名称太长
            wMsgID = eMsgNameTooLong;
            break;
        case eGCreateNameInvalid: //名称非法
            wMsgID = eMsgNameInvalid;
            break;
        case eGCreateNameExisted: //名称存在
            wMsgID = eMsgNameExisted;
            break;
        case eGCreateLackOfVIP:
            wMsgID = eMsgGuildBuildVipLevel;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    }
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EQuitResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGQuitNoGuild: //不在帮派中
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGQuitOwnerQuit: //帮主不能退出帮派
            wMsgID = eMsgGuildOwnerQuit;
            break;
        case eGQuitGuildBattle: //帮派战期间无法执行此操作
            wMsgID = eMsgGuildQuitGuildBattle;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    }
}

void NotifyResultErrorMsg(UINT64 qwRoleID, ESetAuthorityResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGSetAuthorityNotInGuild: //不在帮派中
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGSetAuthorityNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGSetAuthorityTooHigh: //只能提升至比自己低的职位
            wMsgID = eMsgGuildSetAuthorityTooHigh;
            break;
        case eGSetAuthorityNoSelfRank: //不能改变自身权限
            wMsgID = eMsgGuildetAuthorityNoSelfRank;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    }
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EEditInfoResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGEditInfoNotInGuild: //不在帮派中
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGEditInfoNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGEditInfoTooLong://信息过长
            wMsgID = eMsgGuildEditInfoTooLong;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    }
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EMemberOperateResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGMOpResultSelf: //不能对自己操作
            wMsgID = eMsgGuildSelf;
            break;
        case eGMOpResultNotInGuild: //不在帮派中
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGMOpResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGMOpResultTooHigh: //只能提升至比自己低的职位
            wMsgID = eMsgGuildSetAuthorityTooHigh;
            break;
        case eGMOpResultTooLow: //目标成员职位过低
            wMsgID = eMsgGuildMemberTooLow;
            break;
        case eGMOpResultTooMany: //目标职位成员数过多
            wMsgID = eMsgGuildMemberTooMany;
            break;
        case eGMOpResultHaveImpeach: //弹劾发起者无法踢出
            wMsgID = eMsgGuildHaveImpeach;
            break;
        case eGMOpResultGuildBattle: //帮派战期间无法执行此操作
            wMsgID = eMsgGuildQuitGuildBattle;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } }

void NotifyResultErrorMsg(UINT64 qwRoleID, EImpeachResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGImpeachResultSelf: //不能对自己操作
            wMsgID = eMsgGuildSelf;
            break;
        case eGImpeachResultNotInGuild: //不在帮派中
            wMsgID = eMsgGuildWarNoGuild;
            break;
        case eGImpeachResultWrongGuild: //不是该帮派
            wMsgID = eMsgGuildWrongGuild;
            break;
        case eGImpeachResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGImpeachResultHasLaunched: //已经存在弹劾
            wMsgID = eMsgGuildImpeachHasLaunched;
            break;
        case eGImpeachResultHasReplyed: //已经回应
            wMsgID = eMsgImpeachHasReplyed;
            break;
        case eGImpeachResultLackOfGold: //仙石不足
            wMsgID = eMsgGoldErr;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EGuildResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGuildNotExisted: //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGuildExisted: //存在帮派
            wMsgID = eMsgCreatExisted;
            break;
        case eGuildLoading: //加载中
        case eGuildTryAgain: //没加载到（已经开始加载了）稍等一会再试
            wMsgID = eMsgOtherErr;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EBuildingResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGBuildingResultNoGuild: //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGBuildingResultLackofSilver: //银币不足
            wMsgID = eMsgGuildSkillUpgradeNoMoney;
            break;
        case eGBuildingResultLevelMax: //已经是最大等级
            wMsgID = eMsgGuildLevelMax;
            break;
        case eGBuildingResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGBuildingResultGuildLevelTooLow: //帮派等级过低
            wMsgID = eMsgGuildLevelTooLow;
            break;
        case eGBuildingResultOracleLevelTooLow: //神谕塔等级过低
            wMsgID = eMsgGuildOracleLevelTooLow;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, ETechResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGTResultNoGuild: //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGTResultLackofSilver: //帮贡不足
            wMsgID = eMsgGuildLackOfCountribution;
            break;
        case eGTResultLevelMax: //已经是最大等级
            wMsgID = eMsgGuildLevelMax;
            break;
        case eGTResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGTResultBuildingLevelTooLow: //帮派建筑等级过低
            wMsgID = eMsgGuildBuildingLevelTooLow;
            break;
        case eGTResultUserLevelTooLow: //玩家等级过低
            wMsgID = eMsgRoleLevelErr;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EDonateResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGDResultNoGuild: //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGDResultLackofSilver: //银币不足
            wMsgID = eMsgSilverErr;
            break;
        case eGDResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGDResultFull: //每日捐献已满
            wMsgID = eMsgGuildDonateFull;
            break;
        case eGDResultDepotFull: //仓库已满
            wMsgID = eMsgGuildDepotFull;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EStatueResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eGSResultNoGuild: //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eGSResultLackofSilver: //银币不足
            wMsgID = eMsgSilverErr;
            break;
        case eGSResultNoAuthority: //权限不足
            wMsgID = eMsgGuildNoAuthority;
            break;
        case eGSResultLackofGold: //仙石不足
            wMsgID = eMsgGoldErr;
            break;
        case eGSResultLevelMax: //已经是最大等级
            wMsgID = eMsgGuildLevelMax;
            break;
        case eGSResultBuildingLevelTooLow: //帮派建筑等级过低
            wMsgID = eMsgGuildBuildingLevelTooLow;
            break;
        case eGSResultWorshiped: //本日已经供奉过
            wMsgID = eMsgGuildWorshiped;
            break;
        case eGSResultTooFast:
            wMsgID = eMsgCooldownErr;
            break;
        case eGSResultNotToday:
            wMsgID = eMsgGuildTimeLimit;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg;
        strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

void NotifyResultErrorMsg(UINT64 qwRoleID, EGuildXiheResult eResult)
{
    UINT16 wMsgID = 0;
    switch(eResult)
    {
        case eXiheResultFailed:
        case eXiheResultNotTruck:   //不存在这个货物
        case eXiheResultNoGuild:    //不存在帮派
            wMsgID = eMsgTargetNotExistErr;
            break;
        case eXiheResultUnfinish:   //货物未装满
            wMsgID = eMsgTradeNotAdd;
            break;
        case eXiheResultFinish:     //货物已装箱
            wMsgID = eMsgTradeAlreadyAdd;
            break;
        case eXiheResultHasRequest: //货物已请求帮助
            break;
        case eXiheResultNotRequest: //货物未请求帮助
            break;
        case eXiheResultNoSameGuild://不是同一帮派
            wMsgID = eMsgTradeDifferentGuild;
            break;
        case eXiheResultNotItem:    //道具不足不能装货
            wMsgID = eMsgBeautyLackItem;
            break;
        case eXiheResultNotGold:    //仙石不足不能装货
            wMsgID = eMsgGoldErr;
            break;
        case eXiheResultForHelpNumMax:  //此次任务请求帮助次数已达上限
            break;
        case eXiheResultNotRequestLimit:    //已装货物未达到4个不能请求帮助
            wMsgID = eMsgTradeCantAsk;
            break;
        default:
            break;
    }
    if (wMsgID)
    {
        string strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser)
            pUser->SendPkg(strPkg);
    } 
}

/*
   void NotifyResultErrorMsg(UINT64 qwRoleID, EWorshipResult eResult)
   {
   UINT16 wMsgID = 0;
   switch(eResult)
   {
   case eGWResultNoGuild: //不存在帮派
   wMsgID = eMsgTargetNotExistErr;
   break;
   case eGWResultLackofSilver: //银币不足
   wMsgID = eMsgSilverErr;
   break;
   case eGWResultNoAuthority: //权限不足
   wMsgID = eMsgGuildNoAuthority;
   break;
   case eGWResultLevelTooLow: //帮派等级过低
   wMsgID = eMsgGuildLevelTooLow;
   break;
   default:
   break;
   }
   if (wMsgID)
   {
   string strPkg;
   strPkg = g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID);
   CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
   if (pUser)
   pUser->SendPkg(strPkg);
   } 
   }
   */

//接收：请求帮派兑换物品信息
bool CGuildProtS::OnRecv_ReqGuildExchangedItemInfo(
        shared_func<SReqGuildExchangedItemInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CGuildUserPtr pUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pUser)
        return false;

    CGuildPtr pGuild = pUser->GetGuild();
    if (!pGuild)
        return false;

    pGuild->GetGuildExchangedItemInfo(pUser, 
            fnAck->vecLingShanType, 
            fnAck->vecGuildExchangedItem,
            fnAck->dwGUildAllMemberExchangedItemNum, 
            fnAck->dwPlayerExchangedItemNum,
            fnAck->eMemberLastRank);

    return true;
}

//接收：请求帮派兑换物品
bool CGuildProtS::OnRecv_ReqGuildExchangeItem(
        UINT32 dwExchangeID, //兑换id
        UINT32 dwCount, //兑换数量
        shared_func<SReqGuildExchangeItemAck>& fnAck //返回回调函数
        )
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pGuildUser)
    {
        fnAck->eResult = eGuildExchange_Failed;
        return false;
    }

    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
    {
        fnAck->eResult = eGuildExchange_Failed;
        return false;
    }

    pGuild->ReqGuildExchangeItem(pGuildUser, dwExchangeID, dwCount, fnAck);
    if (fnAck->eResult != eGuildExchange_Sucess)
        return false;
    else
        return true;
}

//接收：请求帮派兑换物品日志信息
bool CGuildProtS::OnRecv_ReqGuildExchangeItemLogInfo(
		shared_func<SReqGuildExchangeItemLogInfoAck>& fnAck //返回回调函数
	)
{
    UINT64 qwOpRoleID = GetCurUsrID();
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwOpRoleID);
    if (!pGuildUser)
        return false;

    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return false;

    pGuild->GetGuildExchangedItemLog(fnAck->vecGuildLogInfo);
    
    return true;
}
