#include "stdafx.h"
#include "Chat.h"
#include "MapMgr.h"
#include "UserMgr.h"
#include "Protocols.h"

void CChat::Chat( CUser& rUser, EChannelType eChannelType, const std::string& strInfo, const TVecShowInfo& vecShowInfo)
{
	static TVecUINT64 vecUserID;
	vecUserID.reserve(1024);
	vecUserID.clear();

	switch(eChannelType)
	{
        default:
            {
                LOG_CRI << "Invalid ChannelType=" << (UINT8)eChannelType;
                return;
            }
    }

    if(!vecUserID.empty())
    {
        SSenderInfo oSenderInfo;
        oSenderInfo.qwUsrID = rUser.GetUserID();
        oSenderInfo.byVIPType = rUser.GetVIPLevel();
        oSenderInfo.strName = rUser.GetUserName(); //发送者名
        oSenderInfo.strGuildName = rUser.GetPlayer()->GetGuildName();
        oSenderInfo.vecPlatforms = rUser.GetPlatformParam();
        oSenderInfo.byQuality = rUser.GetPlayer()->GetColor();
        // TODO:
        g_ChatProtS.SendClt_ChatInfoNotify(vecUserID.data(), (UINT16)vecUserID.size(), eChannelType, oSenderInfo, strInfo, vecShowInfo);
	}
}

void CChat::SystemChat(
	UINT64 qwID,
	EChannelType eChannelType,
	const std::string& strInfo,
	EChannelSubType eSubType)
{
	TVecUINT64 vecUserID;
	switch(eChannelType)
	{
	case eChannelSys:
		{
			//vecUserID.push_back(pPlayer->GetUserID());
		}
		break;
	default:
		{
			LOG_CRI << "Invalid ChannelType=" << (UINT8)eChannelType;
			return;
		}
	}

	if(!vecUserID.empty())
		g_ChatProtS.SendClt_SystemMsgNotify(vecUserID.data(), (UINT16)vecUserID.size(), eChannelType, strInfo, eSubType);
}

void CChat::DebugInfo(
	UINT64 qwID,
	const std::string& strInfo
    )
{
	TVecUINT64 vecUserID;
    vecUserID.push_back(qwID);

    string strData = g_ChatProtS.BuildPkg_SystemMsgNotify(eChannelSys, strInfo, eSubNone);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwID);
    if (pUser)
        pUser->SendPkg(strData);
	if(!vecUserID.empty())
		g_ChatProtS.SendClt_SystemMsgNotify(vecUserID.data(), (UINT16)vecUserID.size(), eChannelWorld, strInfo, eSubNone);
}

