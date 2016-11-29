#include "stdafx.h"
#include "Protocols.h"
#include "SvrInfo.h"
#include "User.h"
#include "UserMgr.h"
#include "ArenaManager.h"
#include "CenterGameVar.h"
//接收：心跳
void CLogin2CenterCommS::OnRecv_KeepAlive(
	)
{
	UINT32 dwSvrID = GetCurSvrID();
	NetMgr.GetSvrHandler(eHostLogin)->OnKeepAlive(dwSvrID);
}

//接收：玩家请求进入服务器
void CLogin2CenterCommS::OnRecv_UserLoginReq(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwSessionID, //会话ID
	UINT8 byAddrType //地址类型
	)
{
	EReqResult eReqResult = eReqOtherErr;
	SSvrInfo* pSvrInfo = NULL;
	CUserPtr pUser;
    //TODO:forbit Player :except Ower people!
	if(CUserMgr::HasException(qwUsrID))
		goto FAIL;
	//if(!Config._bInited || !Config._bAllGameSvrInited || !CGUIDMgr::Instance().IsLoaded()||!CArenaManager::IsDoInitCase()||!g_CenterGameVar.IsLoad())
	if(!Config.AllServerIsReady())
	{
		eReqResult = eReqNotInited;
		goto FAIL;
	}
	pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser != NULL)
	{
		pUser->SetSessionID(dwSessionID);
		pUser->SetAddrType(byAddrType);
	    switch(pUser->GetState())
		{
		case eUserNone:
			goto FAIL;
		case eUserWantLogin:
            /*
			eReqResult = eReqTooFreqent;
			goto FAIL;
            */
            if(!pUser->CheckStateTime(ROLE_REQ_WAIT))//2s 连续登陆，踢！！！
			{
				eReqResult = eReqTooFreqent;
				goto FAIL;
			}
            break;
		case eUserReplace:
			eReqResult = eReqKickWait;
			goto FAIL;
		case eUserLeaveAway:
			break;
		case eUserInGame:
			if(!pUser->CheckStateTime(ROLE_REQ_WAIT))
			{
				eReqResult = eReqTooFreqent;
				goto FAIL;
			}
			if(!pUser->ReplaceUser())
			{
				LOG_CRI << "ReplaceUser fails! UsrID: " << qwUsrID;
				CUserMgr::KickUserOffLine(qwUsrID);
			}
			return;
		}
	}
	else
	{
		pUser = CUserMgr::CreateUser(qwUsrID);
		if(pUser == NULL)
		{
			LOG_CRI << "Can't create user: " << qwUsrID;
			goto FAIL;
		}
	}
    pSvrInfo = CSvrInfoMgr::GetMinUsrSvrInfo(eHostGate);
    if (NULL == pSvrInfo)
    {
        LOG_CRI<< "Can't Find GateServer MinUsrSvr";
        eReqResult = eReqFull; 
         goto FAIL;
    }
    //pUser->SetGateId(pSvrInfo->dwSvrID);
	pUser->SetSessionID(dwSessionID);
	pUser->SetAddrType(byAddrType);
	NotifyUserLogin(*pUser, *pSvrInfo);
	return;
FAIL:
	static string strGateIP;
	static UINT16 wGatePort;
	static UINT32 dwCryptoKey;
	Send_UserLoginAck(eReqResult, qwUsrID, dwSessionID, strGateIP, wGatePort, dwCryptoKey);
}

void CLogin2CenterCommS::NotifyUserLogin(CUser& rUser, SSvrInfo& rSvrInfo)
{
	UINT64 qwUsrID = rUser.GetUserID();
	UINT32 dwSvrID = rSvrInfo.dwSvrID;
	UINT16 wGatePort = rSvrInfo.wPort;
	UINT32 dwSessionID = rUser.GetSessionID();
	UINT8 byAddrType = rUser.GetAddrType();
	string strGateAddr;
	UINT32 dwSessionKey = 0;
	auto it = rSvrInfo.mapType2Addr.find(byAddrType);
	if(it == rSvrInfo.mapType2Addr.end())
	{
		LOG_CRI << "Can't find address on GateServer: " << GetServerIndex(dwSvrID) << " for type: " << byAddrType;
		Send_UserLoginAck(eReqOtherErr, qwUsrID, dwSessionID, strGateAddr, wGatePort, dwSessionKey);
		return;
	}
	strGateAddr = it->second;
	rUser.SetState(eUserWantLogin);
	dwSessionKey = CUserMgr::GenSessionKey();
	Send_UserLoginAck(eReqSucceed, qwUsrID, dwSessionID, strGateAddr, wGatePort, dwSessionKey);
	g_Gate2CenterCommS.SendSvr_UserWantLoginNtf(&dwSvrID, 1, qwUsrID, dwSessionKey);
}
