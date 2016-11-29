#include "stdafx.h"
#include "Protocols.h"

//接收：帐号进入GameServer通知
void CGate2GameCommC::OnRecv_UserEnterNtf(
	UINT64 qwUsrID //帐号ID
	)
{
	UINT32 dwSvrID = GetCurSvrID();
	CClientObjPtr pClientObj = NetMgr.GetClientMgr().GetAuthedClient(qwUsrID);
	if(pClientObj == NULL)
	{
		LOG_CRI << "Can't find ClientObj, dwUsrID: " << qwUsrID;
		return;
	}
	pClientObj->SetGameSvrID(dwSvrID);
}

//接收：踢玩家下线
void CGate2GameCommC::OnRecv_KickUserOffLine(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
	)
{
	LOG_INF << "Kick offline from GameServer, UserID: " << qwUsrID << ", LeaveType: " << GetDescription(eLeaveType);
	NetMgr.GetClientMgr().KickClientOffLine(qwUsrID, eLeaveType);
}
