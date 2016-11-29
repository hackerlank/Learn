#include "stdafx.h"
#include "Protocols.h"
#include "SvrInfo.h"
#include "User.h"
#include "UserMgr.h"
#include "CenterConfig.h"
#include "CenterServerLog.h"

//接收：心跳
void CGate2CenterCommS::OnRecv_KeepAlive(
	UINT32 dwUsrCnt //玩家数量
	)
{
	UINT32 dwSvrID = GetCurSvrID();
	NetMgr.GetGateHandler()->OnKeepAlive(dwSvrID);
	SSvrInfo* pSvrInfo = CSvrInfoMgr::GetSvrInfo(dwSvrID);
	if(pSvrInfo != NULL)
		pSvrInfo->dwUsrCnt = dwUsrCnt;
}

//接收：玩家上线通知
void CGate2CenterCommS::OnRecv_UserLoginNtf(
	UINT64 qwUsrID, //帐号ID
	const std::string& strIPAddr //IP地址
	)
{
	NetMgr.GetGateHandler()->OnUserLogin(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(pUser == NULL)
		return;
	pUser->SetClientIP(strIPAddr);
	pUser->SetCurLoginTime(time(NULL));

    g_Center2DBCommC.Send_UpdateLoginIP(qwUsrID, strIPAddr);

    NLogDataDefine::SLoginLogPtr ptrLog(new NLogDataDefine::SLoginLog);
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SLoginLog& rLog = *ptrLog;

    rLog.serverId = Config._wGroup;
    rLog.playerId = qwUsrID;
    rLog.loginTime = pUser->GetCurLoginTime(); 
    rLog.loginIp = strIPAddr; 
    rLog.logoutTime = 0; 
    CCenterServerLog::LogToDB(ptrLog);
}

//接收：玩家下线通知
void CGate2CenterCommS::OnRecv_UserLogoutNtf(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
	)
{
	NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(pUser == NULL)
		return;
	if(pUser->GetState() == eUserInGame)
	{
        CFriend::OnUserLogout(*pUser);
		CUserMgr::DecActiveUserCount();
        g_Game2CenterLogS.OnRecv_LogPlayerLogout((UINT32)time(NULL), qwUsrID);
	}

	switch(eLeaveType)
	{
	case eLeaveAway:
		pUser->SetState(eUserLeaveAway);
		break;
	case eLeaveKick:
	case eLeaveExcept:
    case eIndulgeKick:
    case eIndulgeTimeKick:
        LOG_INF << "qwUsrID Kick From Gate" << qwUsrID << "LeaveType" << eLeaveType;
		CUserMgr::RemoveUser(qwUsrID);
		break;
	default:
		LOG_CRI << "Invalid eLeaveType: " << GetDescription(eLeaveType);
	}

    NLogDataDefine::SLoginLogPtr ptrLog(new NLogDataDefine::SLoginLog);
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SLoginLog& rLog = *ptrLog;

    rLog.serverId = Config._wGroup;
    rLog.playerId = qwUsrID;
    rLog.loginTime = pUser->GetCurLoginTime(); 
    rLog.loginIp = pUser->GetClientIP(); 
    rLog.logoutTime = time(NULL);

    CCenterServerLog::LogToDB(ptrLog);
}
