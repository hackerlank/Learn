#pragma once
#include "Login2CenterCommClt.h"

using namespace NLogin2CenterComm;

class CLogin2CenterCommC : public CLogin2CenterCommClt
{
public:
    //接收：玩家请求进入服务器应答
    virtual void OnRecv_UserLoginAck(
        EReqResult eResult, //登陆请求的结果
        UINT64 qwUsrID, //帐号ID
        UINT32 dwSessionID, //会话ID
        const std::string& strGateAddr, //GateServer的地址
        UINT16 wGatePort, //GateServer的端口
        UINT32 dwCryptoCode //登录验证码
    );
};
