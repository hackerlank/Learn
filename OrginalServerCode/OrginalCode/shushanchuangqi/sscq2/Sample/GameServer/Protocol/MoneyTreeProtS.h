
#pragma once
#include "MoneyTreeProtSvr.h"

using namespace NMoneyTreeProt;

class CMoneyTreeProtS : public CMoneyTreeProtSvr 
{
public:
    
    //接收：请求摇钱树信息
	virtual bool OnRecv_GetMoneyTreeInfo(
		shared_func<SGetMoneyTreeInfoAck>& fnAck //返回回调函数
	);

	//接收：请求摇钱
	virtual bool OnRecv_GetMoney(
		shared_func<SGetMoneyAck>& fnAck //返回回调函数
	);
};

extern CMoneyTreeProtS g_MoneyTreeProtS;



