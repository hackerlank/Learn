
#pragma once
#include "InviteGSSvr.h"

using namespace NInviteGS;

class CInviteSvrS : public CInviteGSSvr
{
public:
	//接收：获取被邀请好友列表
	virtual bool OnRecv_GetInvitedFriendList(
		shared_func<SGetInvitedFriendListAck>& fnAck //返回回调函数
	);

	//接收：邀请任务列表
	virtual bool OnRecv_GetInvitedTaskList(
		shared_func<SGetInvitedTaskListAck>& fnAck //返回回调函数
	);

	//接收：每日邀请好友数量
	virtual bool OnRecv_GetDayInvitedFriends(
		shared_func<SGetDayInvitedFriendsAck>& fnAck //返回回调函数
	);

	//接收：领取奖励
	virtual bool OnRecv_TakeTaskPrize(
		UINT32 dwPrizeID, //领奖任务ID
		shared_func<STakeTaskPrizeAck>& fnAck //返回回调函数
	);

};

extern CInviteSvrS g_InviteSvrS;
