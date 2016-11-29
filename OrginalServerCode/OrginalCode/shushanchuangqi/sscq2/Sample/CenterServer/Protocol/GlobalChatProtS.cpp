#include "stdafx.h"
#include "SysMsgDefine.h"
#include "GlobalChatProtS.h"
#include "User.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "ChatShow.h"
#include "Parameter.h"
#include "UserForbidMgr.h"
#include "GM.h"
#include "TeamMananger.h"
#include "Guild.h"
#include "GuildUser.h"
#include "ProtoCommon.h"
#include "Friend.h"
#include "GuildUserMgr.h"
#define MAX_CHAT_LENGTH 256


static void GMParser(CUser& rUser, const char* gmcmd)
{
    if (!gmcmd)
        return;
#ifdef _DEBUG
    GM::GM(gmcmd, 0xFFFFFFFF);
#else
   GM::GM(gmcmd, rUser.GetGMLvl());
#endif
}

static void Chat(CUser& rUser, EChannelType eChannelType, const std::string& strInfo, const TVecShowInfo& vecShowInfo)
{
    static TVecUINT64 vecUserID;
    vecUserID.reserve(1024);
    vecUserID.clear();

    if((strInfo.size() == 0 || strInfo.size() > MAX_CHAT_LENGTH) && vecShowInfo.empty())
        return;

    UINT64 qwUsrID =  rUser.GetUserID();

    if (strInfo.length() > 2 && strInfo[0] == '/' && strInfo[1] == '/')
    {
        GMParser(rUser, &strInfo.c_str()[2]);
        return;
    }

    if (rUser.GetForbExpireTime() && rUser.GetForbExpireTime() >= time(NULL))
    {
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID, 1, eMsgSysChatForbid);
        return;
    }

    SSenderInfo oSenderInfo;
    oSenderInfo.qwUsrID = rUser.GetUserID();
    oSenderInfo.strName = rUser.GetFixdUserName();
    CGuildUserMgr::Instance().GetGuildName(rUser.GetUserID(), oSenderInfo.strGuildName);
    oSenderInfo.byNation = rUser.GetNation();
    oSenderInfo.byVIPType = rUser.GetVIPLevel();
    oSenderInfo.vecPlatforms = rUser.GetPlatformParam();
    oSenderInfo.byQuality = rUser.GetQuality();

    switch(eChannelType)
    {
        case eChannelWorld:
            {
#if !defined _DEBUG
                if(rUser.GetLevel() < SParamConfig::byWorldChnnelLvl)
                {
                    rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgSysChatWorldLvErr));
                    return;
                }
#endif

                time_t tNow = time(NULL);
                time_t tLastChatTime = rUser.GetLastWorldTime();
                if(tLastChatTime != 0)
                {
                    double tDiff = difftime(tNow, tLastChatTime);
                    if(tDiff < (double)SParamConfig::wChatWorld)
                    {
                        rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgSysChatTooFast));
                        return;
                    }
                }
                rUser.SetLastWorldTime(tNow);

                g_GlobalChatProtS.SendClt_ChatInfoNotify(NULL, 0, eChannelType, oSenderInfo, strInfo, vecShowInfo);

            }
            break;
        case eChannelGuild:
            {
                CGuildUserPtr pGuildUser = rUser.GetGuildUser();
                if (pGuildUser)
                {
                    CGuildPtr pGuild = pGuildUser->GetGuild();
                    if (pGuild)
                        pGuild->GetAllUserID(vecUserID);
                }
            }
            break;
        case eChannelTeam:
            {
                CMemInfo* pInfo = g_TeamManager.GetRoleInfoByID(rUser.GetRoleID());
                if (!pInfo)
                    return;
                CTeamInfo* pTeamInfo = g_TeamManager.GetTeamInfoByID(pInfo->GetTeamID());
                if (!pTeamInfo)
                    return;
                vecUserID = pTeamInfo->GetMemBers();
            }
            break;
        default:
            LOG_CRI << "Invalid ChannelType=" << (UINT8)eChannelType;
            return;
    }

    if(!vecUserID.empty())
        g_GlobalChatProtS.SendClt_ChatInfoNotify(vecUserID.data(), (UINT16)vecUserID.size(), eChannelType, oSenderInfo, strInfo, vecShowInfo);
}

static void Whisper(CUser& rUser, UINT64 qwUsrID, const std::string& strInfo, const TVecShowInfo& vecShowInfo, UINT16& wMsgID)
{
	CUserPtr pTarget = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pTarget || !pTarget->IsOnline())
	{
		rUser.SendPkg(g_GlobalChatProtS.BuildPkg_WhisperErrorNotify(eWhisperOfflineErr, qwUsrID));
        wMsgID = eWhisperOfflineErr;
		return;
	}

    if((strInfo.size() == 0 || strInfo.size() > MAX_CHAT_LENGTH) && vecShowInfo.empty())
	{
		rUser.SendPkg(g_GlobalChatProtS.BuildPkg_WhisperErrorNotify(eWhisperLengthErr, qwUsrID));
        wMsgID = eWhisperLengthErr;
		return;
	}

	time_t tNow = time(NULL);
	time_t tLastChatTime = rUser.GetLastWhisperTime();
	if(tLastChatTime != 0)
	{
		double tDiff = difftime(tNow, tLastChatTime);
		if(tDiff < (double)SParamConfig::wChatWhisper)
		{
			rUser.SendPkg(g_GlobalChatProtS.BuildPkg_WhisperErrorNotify(eWhisperTooFastErr, qwUsrID));
            wMsgID = eWhisperTooFastErr;
			return;
		}
	}
	rUser.SetLastWhisperTime(tNow);

	SSenderInfo oSendInfo;
	oSendInfo.qwUsrID = rUser.GetUserID();
	oSendInfo.strName = rUser.GetFixdUserName();
    CGuildUserMgr::Instance().GetGuildName(rUser.GetUserID(), oSendInfo.strGuildName);
	oSendInfo.byNation = rUser.GetNation();
    oSendInfo.byVIPType = rUser.GetVIPLevel();
    oSendInfo.vecPlatforms = rUser.GetPlatformParam();
    oSendInfo.byQuality = rUser.GetQuality();

    TVecINT64 vecParam;
    TVecString vecString;
    vecString.push_back(rUser.GetFixdUserName());
    UINT32 dwSeverID = pTarget->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID,1,qwUsrID, eOpAdd, 3, vecParam, vecString);
	pTarget->SendPkg(g_GlobalChatProtS.BuildPkg_WhisperInfoNotify(oSendInfo, strInfo, vecShowInfo));
    wMsgID = 0;
}

//接收：聊天
void CGlobalChatProtS::OnRecv_Chat(
	EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
    const TVecShowInfo& vecShowInfo //炫耀物品信息
	)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return;

	Chat(*pUser, eChannelType, strInfo, vecShowInfo);
}

//接收：私聊
bool CGlobalChatProtS::OnRecv_Whisper(
	UINT64 qwUsrID, //帐号ID
	const std::string& strInfo, //聊天信息
    const TVecShowInfo& vecShowInfo, //炫耀物品信息
    shared_func<SWhisperAck>& fnAck //返回回调函数
	)
{
	UINT64 qwCurUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUsrID);
	if(!pUser)
		return false;
    if(pUser->GetForbExpireTime() && pUser->GetForbExpireTime() >= time(NULL))
	{
		g_GlobalChatProtS.SendClt_SystemMsgIDNotify(&qwCurUsrID, 1, eMsgSysChatForbid);
		return false;
	}
	if(qwCurUsrID != qwUsrID)
    {
        CUserPtr pReceive = CUserMgr::GetUserByUserID(qwUsrID);
        if(!pReceive)
            return false;

        CFriend& rFriend = pReceive->GetFriend();
        if(rFriend.IsBlackFriend(qwCurUsrID))
            return false;

		Whisper(*pUser, qwUsrID, strInfo, vecShowInfo, fnAck->wMsgID);
    }

    if(fnAck->wMsgID)
        return false;
    else
        return true;
}

/*
//接收：请求展示信息
bool CGlobalChatProtS::OnRecv_ShowItemReq(
	UINT32 dwShowID, //展示ID
	EChatShowType eShowType, //类型
    shared_func<SShowItemReqAck>& fnAck //返回回调函数
	)
{
    if(CChatShow::GetChatShowInfo(dwShowID, fnAck->strShowItem, eShowType))
        fnAck->eResult = eChatShowSucceed;
    else
        fnAck->eResult = eChatShowNotExist;

    return eChatShowSucceed == fnAck->eResult;
}
*/

// TODO: 接收：获取炫耀信息
bool CGlobalChatProtS::OnRecv_GetShowInfo(
        UINT64 qwInstID, //唯一ID
        shared_func<SGetShowInfoAck>& fnAck //返回回调函数
        )
{
    return true;
}

//接收：请求私聊信
bool CGlobalChatProtS::OnRecv_ReqWhisperInfo(
		const std::string& strReceiveName, //玩家名字
		shared_func<SReqWhisperInfoAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
	CUserPtr pCurUser = CUserMgr::GetUserByUserID(qwRoleID);
	if (NULL == pCurUser)
		return false;

    g_Center2DBCommC.Send_GetUserIDFromName(strReceiveName, [qwRoleID, fnAck](UINT8 byRet, UINT64 qwReceiveID){
    if (byRet != 0 || qwReceiveID == 0)
    {
        fnAck(true);
        return;
    }

    CUserPtr pCurUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (NULL == pCurUser)
    {
        fnAck(true);
        return;
    }

    if (qwReceiveID == qwRoleID)
    {
        fnAck(true);
        return;
    }

    CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
	if (NULL != pReceive)
    {
        fnAck->whisperInfo.qwUserID = qwReceiveID;
        fnAck->whisperInfo.strName = pReceive->GetUserName();
        fnAck->whisperInfo.wFighterID = pReceive->GetFighterID();
        fnAck->whisperInfo.eSex = (ESexType)pReceive->GetSex();
        fnAck->whisperInfo.byLevel = pReceive->GetLevel();
        CGuildUserMgr::Instance().GetGuildName(qwReceiveID, fnAck->whisperInfo.strGuildName);
        fnAck->whisperInfo.wMood = pReceive->GetMood();
        fnAck->whisperInfo.strSign = pReceive->GetSign();
        fnAck->whisperInfo.byVIPType = pReceive->GetVIPLevel();
        fnAck->whisperInfo.byQuality = pReceive->GetQuality();
        fnAck->whisperInfo.vecPlatforms = pReceive->GetPlatformParam();
        fnAck(true);
        return;
    }
    else
    {
        g_Center2DBCommC.Send_GetWhisperInfo(qwReceiveID, [qwRoleID, fnAck](UINT8 byRet, const NGlobalChatProt::SWhisperInfo& whisperInfo){
        if (byRet != 0 || whisperInfo.wFighterID == 0)
        {
            fnAck(true);
            return;
        }

        CUserPtr pCurUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (NULL == pCurUser)
        {
            fnAck(true);
            return;
        }
        fnAck->whisperInfo = whisperInfo;
        fnAck(true);
        return;
        });
    }
    });

    return true;
}
