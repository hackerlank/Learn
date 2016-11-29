#include "stdafx.h"
#include "Protocols.h"

//接收：踢玩家下线
void CGate2DBCommC::OnRecv_KickUserOffLine(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
	)
{
	LOG_INF << "Kick offline from DBServer, UserID: " << qwUsrID << ", LeaveType: " << GetDescription(eLeaveType);
	NetMgr.GetClientMgr().KickClientOffLine(qwUsrID, eLeaveType);
}
