#include "stdafx.h"
#include "Protocols.h"
#include "ClientMgr.h"

//接收：玩家登录通知
void CGate2CenterCommC::OnRecv_UserWantLoginNtf(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwCryptoCode //登录验证码
	)
{
	NetMgr.GetClientMgr().NotifyUserLogin(qwUsrID, dwCryptoCode);
    LOG_INF << "Rev dwCryptoCode From Login ,User:" <<qwUsrID;
}

//接收：踢玩家下线
void CGate2CenterCommC::OnRecv_KickUserOffLine(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
	)
{
	NetMgr.GetClientMgr().KickClientOffLine(qwUsrID, eLeaveType);
    LOG_INF <<"Center Kickoff User:" << qwUsrID << ", LeaveType: " << GetDescription(eLeaveType);
}

//接收：替换帐号
bool CGate2CenterCommC::OnRecv_ReplaceUser(
	UINT64 qwUsrID, //帐号ID
    shared_func<SReplaceUserAck>& fnAck //返回回调函数
	)
{
	LOG_DBG << "Replace User, UserID: " << qwUsrID;
	return NetMgr.GetClientMgr().RemoveClient(qwUsrID, eLeaveReplace);
}

///////////////////////////////////////////////////////////////////

void CGate2CenterCommC::KeepAlive()
{
	Send_KeepAlive(NetMgr.GetClientMgr().GetAuthedClientCount());
}
