
#pragma once
#include "CoinProtSvr.h"

using namespace NCoinProt;

class CCoinProtS : public CCoinProtSvr
{
public:	
     //接收：获取礼包
	virtual bool OnRecv_GetCoinPacket(
		NProtoCommon::EMoneyType eType, //礼包类型
		UINT32 dwMoney, //数量
		shared_func<SGetCoinPacketAck>& fnAck //返回回调函数
	);
   
private:
};

extern CCoinProtS g_CoinProtS;
