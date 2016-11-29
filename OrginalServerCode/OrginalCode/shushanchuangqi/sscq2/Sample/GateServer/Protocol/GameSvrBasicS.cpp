#include "stdafx.h"
#include "Protocols.h"

//接收：心跳
bool CGameSvrBasicS::OnRecv_KeepAlive(shared_func<SKeepAliveAck>& fnAck
	)
{
	CClientObjPtr pClientObj = NetMgr.GetClientMgr().GetCurClient();
	if(pClientObj != NULL)
	{
		//LOG_INF << "OnKeepAlive UsrID: " << pClientObj->GetUsrID();
		pClientObj->OnKeepAlive();
	}
	/*NetMgr.GetClientMgr().SetPeekPass(false);
    fnAck->dwServerTime = time(NULL);*/
    return true;
}
