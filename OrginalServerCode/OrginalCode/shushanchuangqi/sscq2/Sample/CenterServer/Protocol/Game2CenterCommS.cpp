#include "Game2CenterCommS.h"
#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "UserInfoMgr.h"
#include "SystemMail.h"
#include "TeamMananger.h"
#include "ChatShow.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "GuildMgr.h"
#include "ArenaManager.h"
#include "TripodManager.h"
#include "FireSlots.h"
#include "DemonTowerMgr.h"
#include "VarDefine.h"
#include "CenterDataMgr.h"
#include "PrepaidManager.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "InvitedFriendMgr.h"
#include "WonderActivityMgr.h"
#include "ShipManager.h"

//接收：心跳
void CGame2CenterCommS::OnRecv_KeepAlive(
        )
{
    UINT32 dwSvrID = GetCurSvrID();
    NetMgr.GetSvrHandler(eHostGame)->OnKeepAlive(dwSvrID);
}

//接收：CenterServer状态请求
bool CGame2CenterCommS::OnRecv_GetCenterState(
        shared_func<SGetCenterStateAck>& fnAck //返回回调函数
        )
{
    return Config._bInited;
}
//接收：GameServer初始化完成通知
void CGame2CenterCommS::OnRecv_GameSvrInitNft(
        )
{
    //LOG_CRI << "OnRecv_GameSvrInitNft";
    UINT32 dwSvrID = GetCurSvrID();
    static map<UINT32, bool> mapSvr2Init;
    if(mapSvr2Init.empty())
    {
        auto itSvr = Config._oConfigInfo.mapSvr2Conf.find(eHostGame);
        if(itSvr != Config._oConfigInfo.mapSvr2Conf.end())
        {
            auto& rMapConf = itSvr->second;
            for(auto itConf = rMapConf.begin(); itConf != rMapConf.end(); ++itConf)
            {
                UINT8 bySvrIdx = itConf->first;
                UINT32 dwGameSvrID = GetServerID(Config._wGroup, eHostGame, bySvrIdx);
                mapSvr2Init[dwGameSvrID] = false;
            }
        }
    }
    mapSvr2Init[dwSvrID] = true;
    bool bInited = true;
    for(auto it = mapSvr2Init.begin(); it != mapSvr2Init.end(); ++it)
    {
        if(!it->second)
        {
            bInited = false;
            break;
        }
    }
    Config._bAllGameSvrInited = bInited;
    Config.CheckServerIsReady();
}

//接收：GameServer数据同步请求
void CGame2CenterCommS::OnRecv_GameSvrDataSyncReq(
        ESyncKey eSyncKey, //同步Key
        UINT16 wDestGroup, //目的服务器组号
        UINT8 byDestIndex, //目的GameServer(0为全部)
        const TVecINT32& vecParam, //同步参数
        const std::string& strSyncData //同步数据
        )
{
}

bool VarsFromDB(CUser& rUser, const SUserEnterInfo& Info)
{

    size_t szVars = Info.vecGameVars.size();
    for (size_t i = 0; i < szVars; ++i)
    {
        const NRoleInfoDefine::SVarsDBInfo& rVarDBInfo = Info.vecGameVars[i];
        rUser.GetCenterVar().SetVarFromDB(rVarDBInfo.wVar, rVarDBInfo.qwValue, rVarDBInfo.dwExpired);
    }

    return true;
}
//接收：账号进入游戏通知
void CGame2CenterCommS::OnRecv_UserLoginNtf(
        UINT64 qwUsrID, //账号ID
        const SUserEnterInfo& rUserInfo //帐号进入信息
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {

        LOG_CRI << "Can't find User: " << qwUsrID;
        return;
    }
    LOG_DBG << "User Login, UsrID: " << qwUsrID << " UserName: " << rUserInfo.strName;
    EUserState OldState = pUser->GetState();
    pUser->SetPlatformParam(rUserInfo.vecPlatform, rUserInfo.vecPlatform.size() - 1);

    pUser->SetState(eUserInGame);
    if(eUserReplace ==  OldState)
    {
        return ;
    }
    pUser->SetUserName(rUserInfo.strName);
    pUser->SetFighterID(rUserInfo.wHeroID);
    pUser->SetSex(rUserInfo.eSex);
    CUserMgr::MapUserName2ID(rUserInfo.strName, qwUsrID);
    pUser->SetGameSvrID(GetCurSvrID());
    pUser->SetCareer(rUserInfo.eCareer);
    pUser->SetLevel(rUserInfo.byLevel);
    pUser->SetGMLvl(rUserInfo.byGMLvl);
    pUser->SetNation(rUserInfo.byNation);
    pUser->SetTotalRecharge(rUserInfo.dwTotalRecharge);
    pUser->SetCreateTime(rUserInfo.dwCreateTime);
    pUser->SetLoginTime(rUserInfo.dwLoginTime);
    pUser->SetOfflineTime(rUserInfo.dwOfflineTime);
    pUser->SetLockExpireTime(rUserInfo.dwLockExpireTime);
    pUser->SetForbExpireTime(rUserInfo.dwForbExpireTime);
    pUser->SetGold(rUserInfo.dwGold);
    pUser->SetSilver(rUserInfo.dwSilver);
    pUser->SetCoupon(rUserInfo.dwCoupon);
    pUser->SetOwnTitle(rUserInfo.vecOwnTitle);
    pUser->SetEquipTitle(rUserInfo.vecEquipTitle);
#ifdef QQ_VERSION
    pUser->SetDomain(rUserInfo.byDomain);
    pUser->SetDomainLvl(rUserInfo.byDomainLvl);
    pUser->SetDisplayLvl(rUserInfo.byDisplayLvl);
    pUser->SetDomainYear(rUserInfo.byDomainYear);
    if (rUserInfo.szOpenId.size() > 255)
    {
        LOG_CRI << "szOpenId Too Large :User :" <<qwUsrID;
    }
    else
    {
        pUser->SetOpenId(const_cast<char*>(rUserInfo.szOpenId.c_str()));
    }
    if (rUserInfo.szOpenKey.size() >255)
    {
        LOG_CRI << "szOpenKey Too Large :User :" <<qwUsrID;
    }
    else
    {
        pUser->SetOpenKey(const_cast<char*>(rUserInfo.szOpenKey.c_str()));
    }
#endif
    pUser->SetInvited(rUserInfo.qwInvitedID);
    pUser->SetWallow(rUserInfo.byWallow);
    pUser->SetVIPLevel(rUserInfo.byVIPLvl);
    pUser->SetSign(rUserInfo.strSign);
    pUser->SetMood(rUserInfo.wMood);
    pUser->GetFriend().Init(rUserInfo.vecFriendsInfo);

    CUserMgr::UpdateUserLevel(*pUser);
    CFriend::OnUserLogin(*pUser);
    CGuildUserMgr::Instance().OnUserLogin(pUser);

    pUser->GetMailBox().LoadMailList(); // 读取邮件
    CUserMgr::IncActiveUserCount();
    //设置玩家变量
    VarsFromDB(*pUser,rUserInfo);
    //设置斗剑数据
    pUser->SetArenaInfo(rUserInfo.vecArenaInfo);
    pUser->SetFighterPower(rUserInfo.dwFighterPower);
    pUser->SetPlayerFighterID(rUserInfo.wPlayerFighterID);
    pUser->SetQuality(rUserInfo.byQuality);
    SArenaPlayerData * pArenaPlayer =  CArenaManager::GetPlayer(qwUsrID);
    if(pArenaPlayer && pArenaPlayer->stBaseData.dwFighterPower != rUserInfo.dwFighterPower)
    {
        pArenaPlayer->stBaseData.dwFighterPower = rUserInfo.dwFighterPower;
        pArenaPlayer->stBaseData.byQuality = rUserInfo.byQuality;
        CArenaManager::UpadateBaseToDB(qwUsrID);
    }
    pUser->SetIcon(rUserInfo.szIconAppear);
    pUser->GetFireSlots().LoadFireFromDB(rUserInfo.vecFireInfo);
    TripodManager.OnUserLogin(pUser);
    g_DemonTowerMgr.OnLogin(*pUser);
    {
        //XXX 处理玩家未创角预先充值的仙石 仙石ID为1
        UINT32 dwPreGold = CPrepaidManager::Instance().PopRecharge(qwUsrID);
        if (dwPreGold > 0)
        {
            UINT32 dwServerID = pUser->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_AddTotalPrepaid(&dwServerID,1,qwUsrID, dwPreGold);
        }
    }
    if (pUser->GetOfflineTime() > 0)
    {
        if(!pUser->GetCenterVar().GetVar(NVarDefine::ePlayerNoticeUpdateMark))
        {
            pUser->GetCenterVar().SetVar(NVarDefine::ePlayerNoticeUpdateMark, 1);
            pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SysDialogAndNoticeUpdateNotify(eUpdateNoticeDialog));
        }

        if(!pUser->GetCenterVar().GetVar(NVarDefine::ePlayerSysDialogMark))
        {
            pUser->GetCenterVar().SetVar(NVarDefine::ePlayerSysDialogMark, 1);
            pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SysDialogAndNoticeUpdateNotify(eSysDialog));
        }
    }


    pUser->GetShipPkg().SetSelfData(rUserInfo.sShipData);
    pUser->GetShipPkg().SetShipReportList(rUserInfo.vecShipReport);

    if(rUserInfo.qwInvitedID)
        g_InvitedFriendMgr.OnUserLogin(*pUser);
}

void CGame2CenterCommS::OnRecv_SynIconAppear(
        UINT64 qwRoleID, //角色ID
        const std::string& szIcon //功能
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL)
    {

        LOG_CRI << "Can't find User: " << qwRoleID;
        return;
    }
    pUser->SetIcon(szIcon);

}

//接收：账号退出游戏通知
void CGame2CenterCommS::OnRecv_UserLogoutNtf(
        UINT64 qwUsrID //账号ID
        )
{	
    NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }
    EUserState eUserState = pUser->GetState();
    if(eUserState == eUserInGame)
    {
        CFriend::OnUserLogout(*pUser);
        CUserMgr::DecActiveUserCount();
        g_DemonTowerMgr.OnOffLine(qwUsrID);
    }
    if(eUserState != eUserReplace)
    {
        pUser->SetState(eUserLeaveAway);
    }

}

//接收：账号替换通知
void CGame2CenterCommS::OnRecv_UserReplaceNtf(
        UINT64 qwUsrID //账号ID
        )
{	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User: " << qwUsrID;
        return;
    }
    LOG_DBG << "User Replace, UsrID: " << qwUsrID;
    pUser->SetState(eUserInGame);

}

void CGame2CenterCommS::OnRecv_UserJumpSvrNtf(
        UINT64 qwUsrID //账号ID
        )
{	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't Find User, UserID: " << qwUsrID;
        return;
    }
    UINT32 dwSvrID = GetCurSvrID();
    pUser->SetGameSvrID(dwSvrID);
    g_TeamManager.SynPlayerTeamForJump(qwUsrID);

}

//接收：角色同步属性通知
void CGame2CenterCommS::OnRecv_UserSyncPropNtf(
        UINT64 qwUsrID, //帐号ID
        EUserSyncPropField eField, //同步属性类型
        const std::string& strVal //值
        )
{
    NetMgr.SetCurUsrID(qwUsrID);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't Find User, UserID: " << GetUserDesc(qwUsrID);
        return;
    }

    if(!strVal.empty())
        CUserMgr::OnUserPropChanged(*pUser, eField, strVal);
}

//接收：是否为好友
bool CGame2CenterCommS::OnRecv_IsFriend(
        UINT64 qwUsrID, //账号ID
        UINT64 qwFriID, //好友账号ID
        shared_func<SIsFriendAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        fnAck->byRet = 1;
        LOG_CRI << "Can't Find User, UserID: " << qwUsrID;
        return false;
    }
    bool bRet = pUser->GetFriend().IsFriend(qwFriID);
    if (bRet)
        fnAck->byRet = 0;
    else
        fnAck->byRet = 1;
    return true;
}

//接收：是否为帮派成员
bool CGame2CenterCommS::OnRecv_IsSameGuild(
        UINT64 qwUsrID, //账号ID
        UINT64 qwOtherID, //帮派成员ID
        shared_func<SIsSameGuildAck>& fnAck //返回回调函数
        )
{
    if (CGuildUserMgr::Instance().IsSameGuild(qwUsrID, qwOtherID))
        fnAck->byRet = 0;
    else
        fnAck->byRet = 1;
    return true;
}

//接收：获取帮派ID
bool CGame2CenterCommS::OnRecv_GetGuildID(
        UINT64 qwRoleID, //玩家ID
        shared_func<SGetGuildIDAck>& fnAck //返回回调函数
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (pGuildUser)
    {
        fnAck->qwGuildID = pGuildUser->GetGuildID();
        CGuildPtr pGuild = pGuildUser->GetGuild();
        if (pGuild)
        {
            fnAck->strGuildName         = pGuild->GetName();
            fnAck->byGuildLvl           = pGuild->GetLevel();
            fnAck->strGuildOwnerName    = pGuild->GetOwnerName();
        }
        return true;
    }
    else
    {
        fnAck->qwGuildID = 0;
        return false;
    }
}
//接收：获取帮派ID
bool CGame2CenterCommS::OnRecv_GetGuildName(
        UINT64 qwGuildID, //帮派ID
        shared_func<SGetGuildNameAck>& fnAck //返回回调函数
        )
{
    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
    fnAck->qwGuildID = qwGuildID;
    if (pGuild)
    {
        fnAck->bValid = true;
        fnAck->strGuildName         = pGuild->GetName();
        fnAck->byGuildLvl           = pGuild->GetLevel();
        fnAck->strGuildOwnerName    = pGuild->GetOwnerName();
        return true;
    }
    else
    {
        fnAck->bValid = false;
        return false;
    }
}


//接收：帮派广播
void CGame2CenterCommS::OnRecv_NotifyGuildInfo(
        UINT64 qwGuildID, //帮派ID
        const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
        const std::string& strData //具体信息
        )
{
    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
    if (pGuild)
        pGuild->Broadcast(strData, vecExcpRoleID);
}


//接收：发送系统邮件
void CGame2CenterCommS::OnRecv_SendMail(
        const std::string& strSender, //发送者
        const std::string& strTitle, //标题
        const NMailProt::SysMailSendTxt& strMsgInfo, //内容
        const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
        const TVecUINT64& vecTargetIDs //接受者IDs
        ) 
{
    CSystemMail sysMail;
    for(auto iter = vecTargetIDs.begin();iter != vecTargetIDs.end();iter++)
    {
        sysMail.AddTarget(*iter);
    }
    sysMail.SetSender(strSender);
    sysMail.SetBody(strMsgInfo);
    sysMail.SetSubject(strTitle);
    for (auto iter = vecItemInfo.begin();iter != vecItemInfo.end();iter++)
    {
        SMailBaseAttachmentPtr itemPtr = *(iter);
        switch (itemPtr->GetClassType())
        {
            case eType_SItemAttachment:
                {
                    SItemAttachmentPtr pAttach = dynamic_pointer_cast<SItemAttachment>(itemPtr);
                    if(pAttach == NULL)
                    {
                        break;
                    }
                    sysMail.AddItemInfo(pAttach->vecItemInfo);

                }
                break;
            case eType_SItemBaseCT:
                {
                    SItemBaseCTPtr pAttach = dynamic_pointer_cast<SItemBaseCT>(itemPtr);
                    if(pAttach == NULL)
                    {
                        break;
                    }
                    sysMail.AddBaseItems(pAttach->vecItems);
                }
                break;
            default:
                break;
        }

    }
    sysMail.Send();
}

//接收：增加帮派贡献
void CGame2CenterCommS::OnRecv_AddGuildContribution(
        UINT64 qwRoleID, //玩家ID
        UINT32 dwContribution //帮派贡献
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser)
        return;
    pGuildUser->AddContribution(dwContribution);
}

//接收：增加玩家九疑鼎火种
void CGame2CenterCommS::OnRecv_ActiveTripodFire(
        UINT64 qwRoleID, //玩家ID
        UINT16 wFireID //火种ID
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    pUser->GetFireSlots().ActiveFire(wFireID);
}

//接收：更新登录参数
void CGame2CenterCommS::OnRecv_UpdatePlatformParam(
        UINT64 qwRoleID, //玩家ID
        const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
        UINT32 dwIndex //当前平台索引
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser)
        pUser->SetPlatformParam(vecPlatform, dwIndex);
    else
        CUserMgr::UpdatePlatformParam(qwRoleID, vecPlatform);
}

//接收：更新登录其他参数
void CGame2CenterCommS::OnRecv_UpdateEnterString(
        UINT64 qwRoleID, //玩家ID
        const TVecString& vecEnterString //平台参数列表
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser)
        pUser->SetEnterString(vecEnterString);
}

//接收：发送全服活动信息
void CGame2CenterCommS::OnRecv_SendWonderType(
        EWonderActType eActType, //活动类型
        UINT64 qwRoleID, //玩家ID
        UINT32 dwCond //条件ID
        ) 
{
    CUserMgr::ChangeRoleInfo(eActType, dwCond, qwRoleID);
}

//接收：扣除帮贡
bool CGame2CenterCommS::OnRecv_SubGuildContribution(
        UINT64 qwRoleID, //玩家ID
        UINT32 dwContribution, //帮贡数量
        shared_func<SSubGuildContributionAck>& fnAck //返回回调函数
        )
{
    CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
    if (!pGuildUser || !pGuildUser->GetGuild())
    {
        fnAck->eResult = eGuildNotExisted;
        return true;
    }
    bool bRet = pGuildUser->SubContribution(dwContribution);
    if (bRet)
        fnAck->eResult = eGuildSuccess;
    else
        fnAck->eResult = eGuildLackOfMoney;
    return true;
}

//接收：美女抽奖log
void CGame2CenterCommS::OnRecv_BeautyLotteryLog(
        const NBeautyLogGS::SBeautyLog& oBeautyLog//抽奖log
        )
{
    g_CenterDataMgr.OnAddBeautyLog(oBeautyLog);
    return;
}

//接收：邀请好友成功
void CGame2CenterCommS::OnRecv_InviteFriend(
        UINT64 qwUserID, //邀请人
        UINT64 qwInvitedUserID //被邀请人
        )
{
    g_InvitedFriendMgr.OnInviteFriend(qwUserID,qwInvitedUserID);
}

//接收：通知帮派兑换物品开始
void CGame2CenterCommS::OnRecv_NotifyGuildExchangedItemBegin(
        const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
        )
{
    CGuildMgr::Instance().GuildExchangedBegin(vecLingShanShopData);
}

//接收：同步在Center使用的buff结束时间
void CGame2CenterCommS::OnRecv_SyncGameBuffUseInCenter(
        UINT64 qwRoleID, //玩家ID
        UINT16 wBuffID, //buffID
        UINT32 dwEndTime //结束时间
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser == NULL)
        return;
    pUser->AddGameBuff(wBuffID, dwEndTime);
}
//接收：同步活动参数
void CGame2CenterCommS::OnRecv_SyncGameActiveParam(
        ActiveParam eParam, //参数类型
        const TVecUINT32& vecParam //参数
        ) 
{
    switch(eParam)
    {
        case eShip:
            if(!vecParam.empty())
                g_ShipManager.SetAwardRate(vecParam[0]);
            break;
        default:
            break;
    }
}

//接收：获取全局Var值
bool CGame2CenterCommS::OnRecv_GetSystemVar(
        const TVecUINT16& vecVarID, //varID列表
        shared_func<SGetSystemVarAck>& fnAck //返回回调函数
        )
{
    for (auto & rID : vecVarID)
    {
        if (rID <= NVarDefine::eSystemVarNone || rID >= NVarDefine::eSystemVarMax)
        {
            LOG_CRI << "Invalid VarID: " << rID << ".";
            continue;
        }
        fnAck->vecVars.push_back(rID);
        fnAck->vecValues.push_back(g_CenterGameVar.GetVar(rID));
    }
    return true;
}

//接收：设置全局Var值
bool CGame2CenterCommS::OnRecv_SetSystemVar(
        const TVecUINT16& vecVars, //varID列表
        const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
        shared_func<SSetSystemVarAck>& fnAck //返回回调函数
        )
{
    if (vecVars.size() != vecValues.size())
    {
        LOG_CRI << "vecVars.size() = " << vecVars.size() << ", vecValues.size() = " << vecValues.size() << ".";
        return false;
    }

    for (size_t szIndex = 0; szIndex < vecVars.size(); ++szIndex)
    {
        if (vecVars[szIndex] <= NVarDefine::eSystemVarNone || vecVars[szIndex] >= NVarDefine::eSystemVarMax)
        {
            LOG_CRI << "Invalid VarID: " << vecVars[szIndex] << ".";
            continue;
        }
        g_CenterGameVar.SetVar(vecVars[szIndex], vecValues[szIndex]);
        fnAck->vecVarID.push_back(vecVars[szIndex]);
    }
    return true;
}

