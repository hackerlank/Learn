#pragma once
#include "Gate2GameCommSvr.h"

using namespace NGate2GameComm;

class CGate2GameCommS : public CGate2GameCommSvr
{
public:
    //接收：心跳
    virtual void OnRecv_KeepAlive(
    );
    //接收：玩家下线通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	) ;
};
