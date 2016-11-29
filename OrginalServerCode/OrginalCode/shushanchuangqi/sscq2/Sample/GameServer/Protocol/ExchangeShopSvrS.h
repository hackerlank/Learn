
#pragma once
#include "ExchangeShopProtSvr.h"

using namespace NExchangeShopProt;

//协议类：锁妖塔
class CExchangeShopProtSvrS : public CExchangeShopProtSvr
{
public:
	//接收：兑换物品
	virtual bool OnRecv_ExchangeItem(
		UINT32 dwExchangeID, //兑换id
        UINT32 dwCount, //兑换数量
		shared_func<SExchangeItemAck>& fnAck //返回回调函数
	) ;

	//接收：已兑换列表
	virtual bool OnRecv_ExchangeItemList(
		shared_func<SExchangeItemListAck>& fnAck //返回回调函数
	);


};

extern CExchangeShopProtSvrS g_ExchangeShopProtSvrS;
