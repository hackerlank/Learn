#include "stdafx.h"
#include "FriendProtS.h"
#include "User.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "Parameter.h"
#include "SysMsgDefine.h"
#include "CommonDef.h" // XXX: for LEVEL_MAX
#include "TaskConf.h"
#include "EventCenter.h"

#define REFERFRIEND_COUNT 15
//接收：增加好友/黑名单请求
void CFriendProtS::OnRecv_AddFriendReq1(
	EFriendGroupType eGroupType, //组别
	const TVecUINT64& vecUserID, //玩家ID
    UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
	)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

    UINT32 dwSeverID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ActionNotify(&dwSeverID, 1, qwUsrID, eProcessAction_Refer);

	CFriend& rFriend = pUser->GetFriend();
	switch(eGroupType)
	{
	case NFriendProt::eCommonFriend:
		for(size_t i = 0;i < vecUserID.size();i++)
		{
			if(qwUsrID == vecUserID[i])//屏蔽掉自己
				continue;

			rFriend.AddFriend(vecUserID[i], byNeedRet);
		}
		break;
	case NFriendProt::eBlackFriend:
		for(size_t i = 0;i < vecUserID.size();i++)
		{
			if(qwUsrID == vecUserID[i])//屏蔽掉自己
				continue;

			rFriend.AddBlackList(vecUserID[i]);
		}
		break;
	default:
		break;
	}
}

//接收：增加好友/黑名单请求
void CFriendProtS::OnRecv_AddFriendReq2(
	EFriendGroupType eGroupType, //组别
	const std::string& strName, //用户名
    UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
	)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

	if(pUser->GetRoleName() == strName)
		return;

	CFriend& rFriend = pUser->GetFriend();
	switch(eGroupType)
	{
	case NFriendProt::eCommonFriend:
		rFriend.AddFriend(strName, byNeedRet);
		break;
	case NFriendProt::eBlackFriend:
		rFriend.AddBlackList(strName);
		break;
	default:
		break;
	}
}

//接收：回答增加好友
void CFriendProtS::OnRecv_AnswerAddFriend(
	bool bAgree, //是否同意
	UINT64 qwUsrID //帐号ID
	)
{
	UINT64 qwCurUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUsrID);
	if(!pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

	CFriend& rFriend = pUser->GetFriend();
	rFriend.AnswerAddFriend(bAgree, qwUsrID);
}

//接收：删除好友
void CFriendProtS::OnRecv_RemoveFriendReq(
	const TVecUINT64& vecUserID //玩家ID
	)
{
	UINT64 qwCurUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUsrID);
	if(!pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

	CFriend& rFriend = pUser->GetFriend();
	for(size_t i = 0;i < vecUserID.size();i++)
		rFriend.RemoveFriend(vecUserID[i]);
}

//接收：移动好友
bool CFriendProtS::OnRecv_MoveFriend(
	UINT64 qwUsrID, //帐号ID
	EFriendGroupType eGroupType, //分组ID
	shared_func<SMoveFriendAck>& fnAck //返回回调函数
	)
{
	UINT64 qwCurUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUsrID);
	if(!pUser)
		return false;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return false;
	}

	if(eGroupNone == eGroupType || 
	   eBlackFriend == eGroupType || 
	   eGroupEnd <= eGroupType)
	{
		fnAck->eResult = eFriendGroupIDErr;
		return false;
	}

	CFriend& rFriend = pUser->GetFriend();
	fnAck->eResult = rFriend.MoveFriend(qwUsrID, eGroupType);

	return eFriendSuccess == fnAck->eResult;
}

//接收：私聊
void CFriendProtS::OnRecv_Whisper(
	UINT64 qwUsrID //帐号ID
	)
{

}

//接收：查询玩家
void CFriendProtS::OnRecv_FindUserIDNameReq(
	UINT64 qwUsrID, //帐号ID
	const std::string& strRoleName //主角色名
	)
{
	UINT64 qwCurUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUsrID);
	if(NULL == pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

	if(0 == qwUsrID && strRoleName.empty())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr));
		return;
	}

	g_Center2DBCommC.Send_UserIDNameReq(eUserReqFriend, qwUsrID, strRoleName, qwCurUsrID);
}

//接收：获取推荐好友
bool CFriendProtS::OnRecv_FindReferFriendReq(
	shared_func<SFindReferFriendReqAck>& fnAck //返回回调函数
	)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return false;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return false;
	}

	CFriend& rFriend = pUser->GetFriend();
	TMapLevel2User* pMap = CUserMgr::GetUserLevelRange(pUser->GetNation());
	if(NULL == pMap)
		return false;

	UINT8 byLevel = pUser->GetLevel();
	auto func_find = [&](UINT8 byLevel){
		auto it = pMap->find(byLevel);
		if(it != pMap->end())
		{
			for(auto it_set = it->second.begin();it_set != it->second.end();it_set++)
			{
				if((*it_set) != qwUsrID &&!rFriend.IsFriendEntry(*it_set))
				{
					CUserPtr pDestUser = CUserMgr::GetUserByUserID(*it_set);
					if(!pDestUser)
						continue;
                    if(pDestUser->GetLevel() < 10)
                        continue;
					fnAck->vecReferFriend.emplace_back(pDestUser->GetUserID(), byLevel, pDestUser->GetFighterID(), pDestUser->GetRoleName());
					if(fnAck->vecReferFriend.size() >= REFERFRIEND_COUNT)
						break;
				}
			}
		}
	};

	int i = 0;
	while(i < LEVEL_MAX && fnAck->vecReferFriend.size() < REFERFRIEND_COUNT)
	{
		if(byLevel + i < LEVEL_MAX)
			func_find(byLevel + i);

		if(i > 0 && byLevel > i)
			func_find(byLevel - i);
		i++;
	}

    //使用好友推荐事件
    TVecINT32 vecParam;
    vecParam.push_back(1);
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1, qwUsrID, NEventCenter::eEventType_FriendRecommendUsing, vecParam, "", true);
                    
	return true;
}

//接收：取得所有好友信息
void CFriendProtS::OnRecv_GetFriendInfo(
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return;
	}

	CFriend& rFriend = pUser->GetFriend();
    rFriend.FriendInfoNotify();
}

//接收：修改签名
bool CFriendProtS::OnRecv_SetSign(
    const std::string& strSign, //签名文字：最多不超过255个字符
    shared_func<SSetSignAck>& fnAck //返回回调函数
)
{
    fnAck->eResult = eFriendFailed;

	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return false;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return false;
	}

    if (strSign.length() > SParamConfig::wSignLenMax)
    {
        fnAck->eResult = eFriendSignLenErr;
        return false;
    }

    pUser->SetSign(strSign);
    CFriend& rFriend = pUser->GetFriend();
    rFriend.ChangeSign(strSign);

    fnAck->eResult = eFriendSign;
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_SetSign(&dwServerID, 1, pUser->GetUserID(), strSign);
    
    //修改个性签名事件
    TVecINT32 vecParam;
    vecParam.push_back(1);
    g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1, pUser->GetUserID(), NEventCenter::eEventType_FriendSignatureChangings, vecParam, "", true);
    
    return true;
}

//接收：设置心情表情
bool CFriendProtS::OnRecv_SetMood(
    UINT16 wMood, //心情表情
    shared_func<SSetMoodAck>& fnAck //返回回调函数
)
{
    fnAck->eResult = eFriendFailed;

	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return false;

	if (pUser->IsInCrossServer())
	{
		pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgEventInMineBattleErr));
		return false;
	}

    pUser->SetMood(wMood);
    CFriend& rFriend = pUser->GetFriend();
    rFriend.ChangeMood(wMood);

    fnAck->eResult = eFriendMood;
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_SetMood(&dwServerID, 1, pUser->GetUserID(), wMood);
    return true;
}

