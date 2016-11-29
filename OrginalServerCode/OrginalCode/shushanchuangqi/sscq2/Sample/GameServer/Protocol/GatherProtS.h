#pragma once
#include "GatherProtSvr.h"

using namespace NGatherProt;

class CGatherProtS : public CGatherProtSvr
{
public:
    //接收：采集请求
	virtual bool OnRecv_GatherReq(
		UINT32 dwGatherId, //采集ID
		shared_func<SGatherReqAck>& fnAck //返回回调函数
	);
   //接收：取消采集
	virtual bool OnRecv_CancelGather(
		shared_func<SCancelGatherAck>& fnAck //返回回调函数
	);
   //接收：客户端查询采集信息
	virtual bool OnRecv_GetGatherInfo(
		shared_func<SGetGatherInfoAck>& fnAck //返回回调函数
	);



    void  SystemMsgNotify(EGatherResult result,UINT64 qwUserId  );
    

};
