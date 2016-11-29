
#pragma once
#include "RegisterSevenDaysProtSvr.h"

using namespace NRegisterSevenDaysProt;

class CRegisterSevenDaysProtS : public CRegisterSevenDaysProtSvr 
{
public:
    
    //接收：请求当天目标信息
	virtual bool OnRecv_GetCurTargetInfo(
		shared_func<SGetCurTargetInfoAck>& fnAck //返回回调函数
	);

    //接收：通过dwDayID获取目标信息
	virtual bool OnRecv_GetTargetInfoByDayID(
		UINT32 dwDayID, //第几天
		shared_func<SGetTargetInfoByDayIDAck>& fnAck //返回回调函数
	);

    //接收：获取奖励
	virtual bool OnRecv_GetAward(
		UINT32 dwDayID, //第几天
		UINT8 byTargetID, //目标ID
		shared_func<SGetAwardAck>& fnAck //返回回调函数
	);

    //接收：请求当天购买信息
	virtual bool OnRecv_GetCurBuyInfo(
		shared_func<SGetCurBuyInfoAck>& fnAck //返回回调函数
	);

	//接收：请求购买
	virtual bool OnRecv_ReqBuy(
		shared_func<SReqBuyAck>& fnAck //返回回调函数
	);
};

extern CRegisterSevenDaysProtS g_RegisterSevenDaysProtS;



