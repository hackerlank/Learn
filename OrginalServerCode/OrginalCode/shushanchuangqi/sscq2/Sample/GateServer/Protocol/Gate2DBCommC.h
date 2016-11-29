#pragma once
#include "Gate2DBCommClt.h"

using namespace NGate2DBComm;

class CGate2DBCommC : public CGate2DBCommClt
{
public:
	//接收：踢玩家下线
	virtual void OnRecv_KickUserOffLine(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
		);
};
