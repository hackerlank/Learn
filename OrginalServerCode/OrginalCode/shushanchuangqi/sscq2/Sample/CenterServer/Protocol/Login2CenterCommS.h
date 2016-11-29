#pragma once
#include "Login2CenterCommSvr.h"

using namespace NLogin2CenterComm;

class CUser;
struct SSvrInfo;

class CLogin2CenterCommS : public CLogin2CenterCommSvr
{
public:
	//接收：心跳
	virtual void OnRecv_KeepAlive(
		);

	//接收：玩家请求进入服务器
	virtual void OnRecv_UserLoginReq(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		UINT8 byAddrType //地址类型
		);

	//////////////////////////////////////
	void NotifyUserLogin(CUser& rUser, SSvrInfo& rSvrInfo);
};
