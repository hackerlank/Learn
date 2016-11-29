#pragma once
#include "SignProtSvr.h"
using namespace NSignProt;

class CSignProtS : public CSignProtSvr
{
    public:
        //接收：请求签到信息
        virtual bool OnRecv_GetSignInfo(
                shared_func<SGetSignInfoAck>& fnAck //返回回调函数
                );
        //接收：请求签到
        virtual bool OnRecv_DoSign(
                shared_func<SDoSignAck>& fnAck //返回回调函数
                );
        //接收：请求补签
        virtual bool OnRecv_DoReSign(
                UINT8 byDay, //补签日期
                shared_func<SDoReSignAck>& fnAck //返回回调函数
                );
        //接收：请求领取奖励
        virtual bool OnRecv_DoGetAward(
                UINT8 byId, //奖励ID
                shared_func<SDoGetAwardAck>& fnAck //返回回调函数
                );

    public:
        void SendSysMsgIDNotify(ESignResult eResult);
};
