#include "stdafx.h"
#include "UserMgr.h"
#include "InviteGSSvrS.h"
#include "InvitedFriendMgr.h"

CInviteSvrS g_InviteSvrS;
 
//接收：获取被邀请好友列表
bool CInviteSvrS::OnRecv_GetInvitedFriendList(
	shared_func<SGetInvitedFriendListAck>& fnAck //返回回调函数
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_InvitedFriendMgr.OnGetInvitedFriendList(qwUserID,fnAck->vecInvitedFriend);

    return true;
}

//接收：邀请任务列表
bool CInviteSvrS::OnRecv_GetInvitedTaskList(
	shared_func<SGetInvitedTaskListAck>& fnAck //返回回调函数
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_InvitedFriendMgr.OnGetInvitedTaskList(qwUserID,fnAck->vecInvitedTask);

    return true;
}

//接收：每日邀请好友数量
bool CInviteSvrS::OnRecv_GetDayInvitedFriends(
	shared_func<SGetDayInvitedFriendsAck>& fnAck //返回回调函数
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_InvitedFriendMgr.OnGetDayInvitedFriends(qwUserID,fnAck->dwInviteCnt);

    return true;
}


//接收：领取奖励
bool CInviteSvrS::OnRecv_TakeTaskPrize(
	UINT32 dwPrizeID, //领奖任务ID
	shared_func<STakeTaskPrizeAck>& fnAck //返回回调函数
)
{
    UINT64 qwUserID = GetCurUsrID();
    fnAck->eRet = g_InvitedFriendMgr.OnTakeTaskPrize(qwUserID,dwPrizeID);
    return true;
}
