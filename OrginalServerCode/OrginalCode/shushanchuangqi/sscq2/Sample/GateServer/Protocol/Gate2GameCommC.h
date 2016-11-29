#pragma once
#include "Gate2GameCommClt.h"

using namespace NGate2GameComm;

class CGate2GameCommC : public CGate2GameCommClt
{
public:
	//接收：帐号进入GameServer通知
	virtual void OnRecv_UserEnterNtf(
		UINT64 qwUsrID //帐号ID
		);

	//接收：踢玩家下线
	virtual void OnRecv_KickUserOffLine(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
		);
};
