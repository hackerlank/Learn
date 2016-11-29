#pragma once
#include "Gate2DBCommSvr.h"

using namespace NGate2DBComm;

class CGate2DBCommS : public CGate2DBCommSvr
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
