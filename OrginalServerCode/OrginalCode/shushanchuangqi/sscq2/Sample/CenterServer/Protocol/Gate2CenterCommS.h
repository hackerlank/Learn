#pragma once
#include "Gate2CenterCommSvr.h"

using namespace NGate2CenterComm;

class CGate2CenterCommS : public CGate2CenterCommSvr
{
public:
	//接收：心跳
	virtual void OnRecv_KeepAlive(
		UINT32 dwUsrCnt //玩家数量
		);

	//接收：玩家上线通知
	virtual void OnRecv_UserLoginNtf(
		UINT64 qwUsrID, //帐号ID
		const std::string& strIPAddr //IP地址
		);

	//接收：玩家下线通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
		);
};
