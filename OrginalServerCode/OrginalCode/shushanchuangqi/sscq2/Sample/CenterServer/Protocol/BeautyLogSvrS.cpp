#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "BeautyLogSvrS.h"
#include "CenterDataMgr.h"

CBeautyLogSvrS g_BeautyLogSvrS;
 
 //接收：获取美女log信息
bool CBeautyLogSvrS::OnRecv_GetBeautyLog(
		shared_func<SGetBeautyLogAck>& fnAck //返回回调函数
	)
{

    UINT64 qwUserID = GetCurUsrID();
    g_CenterDataMgr.OnGetBeautyLog(qwUserID,fnAck->vecBeautyLog);
    return true;
}


