#pragma once
#include "CompareBattlePointSvr.h"

using namespace NCompareBattlePoint;

class CCompareBattlePointS : public CCompareBattlePointSvr
{
public:
	//接收：战斗力对比
	virtual bool OnRecv_CompareOtherBPByID(
		UINT64 qwRoleID, //对方的玩家ID
		shared_func<SCompareOtherBPByIDAck>& fnAck //返回回调函数
	);

    //接收：战斗力对比
    virtual bool OnRecv_CompareOtherBPByName(
        const std::string& strName, //对方的玩家名字
        shared_func<SCompareOtherBPByNameAck>& fnAck //返回回调函数
    );

};
