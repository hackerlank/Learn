#pragma once
#include "Gate2CenterCommClt.h"

using namespace NGate2CenterComm;

class CGate2CenterCommC : public CGate2CenterCommClt
{
public:
	//接收：玩家登录通知
	virtual void OnRecv_UserWantLoginNtf(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwCryptoCode //登录验证码
		);

	//接收：踢玩家下线
	virtual void OnRecv_KickUserOffLine(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
		);

	//接收：替换帐号
	virtual bool OnRecv_ReplaceUser(
		UINT64 qwUsrID, //帐号ID
        shared_func<SReplaceUserAck>& fnAck //返回回调函数
		);

	//////////////////////////////////////////////
	void KeepAlive();
};
