#include "stdafx.h"
#include "Protocols.h"
#include "DBRoleMgr.h"

//接收：心跳
void CGate2DBCommS::OnRecv_KeepAlive()
{
    UINT32 dwSvrID = GetCurSvrID();
    NetMgr.GetGateHandler()->OnKeepAlive(dwSvrID);
}

void CGate2DBCommS::OnRecv_UserLogoutNtf(UINT64 qwUsrID,NServerCommon::ELeaveType eLeaveType)
{
    NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
    SDBRoleData* pUserData = CDBRoleMgr::Instance().GetRoleData(qwUsrID);
    if(pUserData == NULL)
        return;
    LOG_DBG << "UserLogout, UsrID:" << qwUsrID << " LeaveType: " << GetDescription(eLeaveType);
    pUserData->SetUserState(eUserLeaveAway);
    CDBRoleMgr::Instance().NoticeLeaveAway(qwUsrID);
    if(pUserData->nServerId != 0)
    {
        g_Game2DBCommS.SendSvr_UserLogoutNtf(&pUserData->nServerId, 1, qwUsrID, eLeaveType);
    }
}
