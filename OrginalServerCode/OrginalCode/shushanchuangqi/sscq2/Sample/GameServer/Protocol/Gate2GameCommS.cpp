#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "GameNetMgr.h"

//接收：心跳
void CGate2GameCommS::OnRecv_KeepAlive(
	)
{
	UINT32 dwSvrID = GetCurSvrID();
	NetMgr.GetGateHandler()->OnKeepAlive(dwSvrID);
}

void CGate2GameCommS::OnRecv_UserLogoutNtf(UINT64 qwUserId, ELeaveType eLeaveType)
{
    // XXX: 网关下线
    LOG_DBG << "UserLogout, UsrID:" << qwUserId << " LeaveType: " << GetDescription(eLeaveType);
    CUserMgr::OnUserLeave(qwUserId, eLeaveType);


}

