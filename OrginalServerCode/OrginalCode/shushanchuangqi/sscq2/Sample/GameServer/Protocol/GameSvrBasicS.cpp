#include "stdafx.h"
#include "Protocols.h"
//接收：心跳
bool CGameSvrBasicS::OnRecv_KeepAlive(
		shared_func<SKeepAliveAck>& fnAck //返回回调函数
	)
{
    //LOG_CRI << "OnRecv_KeepAlive";
	//assert(false);
    fnAck->dwServerTime = time(NULL);
    return true;
}

