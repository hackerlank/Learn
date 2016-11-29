
#pragma once
#include "YelloDiamondProtSvr.h"

using namespace NYelloDiamondProt;

class CYelloDiamondProtS : public CYelloDiamondProtSvr
{
public:	
    //接收：获取黄钻礼包
	virtual bool OnRecv_GainYDBag(
		EBagType eBagType, //礼包类型
		UINT16 dLevel, //玩家等级成长礼包
		shared_func<SGainYDBagAck>& fnAck //返回回调函数
	);
    //接收：获取黄钻礼包领取信息
	virtual bool OnRecv_GetYDBagInfo(
		shared_func<SGetYDBagInfoAck>& fnAck //返回回调函数
	);

private:
};

extern CYelloDiamondProtS g_YelloDiamondProtS;
