
#pragma once
#include "MallProtSvr.h"

using namespace NMallProt;

class CMallProtS : public CMallProtSvr
{
public:
	//接收：预览商城信息
	virtual bool OnRecv_MalGet(
		EMallType eType, //商城类型
		shared_func<SMalGetAck>& fnAck //返回回调函数
	);
	//接收：商场购买
	virtual bool OnRecv_MalBuy(
		EUseMoneyMark eMark, //使用钱币标志
		EMallType eType, //商城类型
        UINT32 wInstID, //实例ID
		UINT16 wCount, //物品个数
		shared_func<SMalBuyAck>& fnAck //返回回调函数
	);
    //接收：商场赠送
	virtual bool OnRecv_MallPresent(
		EUseMoneyMark eMark, //使用钱币标志
		EMallType eType, //商城类型
        UINT32 wInstID, //实例ID
		UINT16 wCount, //物品个数
		const std::string& strReceiveName, //接受者姓名
		const std::string& strTitle, //邮件标题
		const std::string& strMsg, //邮件内容
		shared_func<SMallPresentAck>& fnAck //返回回调函数
	); 
    
    //接收：获取物品购买数量列表
	virtual bool OnRecv_GetBuyItemList(
		shared_func<SGetBuyItemListAck>& fnAck //返回回调函数
	);

	//接收：预览商城限购信息
	virtual void OnRecv_GetMallDiscountInfo(
	);
	//接收：购买商场限购道具
	virtual bool OnRecv_BuyDiscountItem(
        UINT8 byPos, //限购位置(0,1,2)
		UINT16 wCount, //购买个数
		shared_func<SBuyDiscountItemAck>& fnAck //返回回调函数
	);

	//接收：获取玩家首次充值活动完成信息(在商城界面的奖励)
	virtual void OnRecv_GetChongZhiActInfo(
	);

private:
};
