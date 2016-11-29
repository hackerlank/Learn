
#pragma once
#include "ShushanweiweiProtSvr.h"

using namespace NShushanweiweiProt;

class CShushanweiweiProtS : public CShushanweiweiProtSvr
{
public:	
	//接收：获取礼包
	virtual bool OnRecv_TakePrize(
		EPkgType eType, //活动类型
		UINT16 wIndex, //领奖类型：0表示个人奖励，1..16 表示领取全服第几个奖励
		const std::string& strCDK, //CDK
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);
	
	//接收：收听微博
	bool OnRecv_ListenWeibo(
		shared_func<SListenWeiboAck>& fnAck //返回回调函数
	);

	//接收：获得玩家奖励信息
	virtual void OnRecv_GetPrizeInfo(
	);

private:
};

extern CShushanweiweiProtS g_ShushanweiweiProtS;
