/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MallProt.h
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "MallProt.h"

namespace NMallProt
{

//协议类：商城相关协议
class CMallProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：通知玩家商城限购信息
	bool Send_UpdateMallDiscountInfo( //发送给当前协议处理的客户端
		const TVecDiscount& vecDiscount, //限购信息列表
		UINT32 wCountPos1, //限购位置1购买道具数
		UINT32 wCountPos2, //限购位置2购买道具数
		UINT32 wCountPos3, //限购位置3购买道具数
		UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
		UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
		UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
		UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
		UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
		UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
	);
	bool SendClt_UpdateMallDiscountInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecDiscount& vecDiscount, //限购信息列表
		UINT32 wCountPos1, //限购位置1购买道具数
		UINT32 wCountPos2, //限购位置2购买道具数
		UINT32 wCountPos3, //限购位置3购买道具数
		UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
		UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
		UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
		UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
		UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
		UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
	);
	std::string& BuildPkg_UpdateMallDiscountInfo( //只组包不发送
		const TVecDiscount& vecDiscount, //限购信息列表
		UINT32 wCountPos1, //限购位置1购买道具数
		UINT32 wCountPos2, //限购位置2购买道具数
		UINT32 wCountPos3, //限购位置3购买道具数
		UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
		UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
		UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
		UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
		UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
		UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
	);

	//发送：通过栏位通知玩家商城限购信息
	bool Send_UpdateMallDiscountInfoByPos( //发送给当前协议处理的客户端
		const SDiscount& oDiscount //限购信息列表
	);
	bool SendClt_UpdateMallDiscountInfoByPos(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SDiscount& oDiscount //限购信息列表
	);
	std::string& BuildPkg_UpdateMallDiscountInfoByPos( //只组包不发送
		const SDiscount& oDiscount //限购信息列表
	);

	//发送：物品购买数量更新
	bool Send_BuyItemNotify( //发送给当前协议处理的客户端
		const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
	);
	bool SendClt_BuyItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
	);
	std::string& BuildPkg_BuyItemNotify( //只组包不发送
		const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
	);

	//发送：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
	bool Send_UpdateChongZhiActInfo( //发送给当前协议处理的客户端
		UINT8 byIdx, //当前充值完成的第几个
		UINT32 dwCount, //当前充值了几个仙石包
		UINT8 byInfo //按位取(低6位,每位为1表明已完成)
	);
	bool SendClt_UpdateChongZhiActInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byIdx, //当前充值完成的第几个
		UINT32 dwCount, //当前充值了几个仙石包
		UINT8 byInfo //按位取(低6位,每位为1表明已完成)
	);
	std::string& BuildPkg_UpdateChongZhiActInfo( //只组包不发送
		UINT8 byIdx, //当前充值完成的第几个
		UINT32 dwCount, //当前充值了几个仙石包
		UINT8 byInfo //按位取(低6位,每位为1表明已完成)
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SMalGetAck : public CClientFuncAck
	{
		TVecMallInfo vecMallInfo; //商场信息列表

		SMalGetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：预览商城信息
	virtual bool OnRecv_MalGet(
		EMallType eType, //商城类型
		shared_func<SMalGetAck>& fnAck //返回回调函数
	) = 0;

	struct SMalBuyAck : public CClientFuncAck
	{
		EMallResult eResult; //购买结果返回

		SMalBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：商场购买
	virtual bool OnRecv_MalBuy(
		EUseMoneyMark eMark, //使用钱币标志
		EMallType eType, //商城类型
		UINT32 wInstID, //实例ID
		UINT16 wCount, //物品个数
		shared_func<SMalBuyAck>& fnAck //返回回调函数
	) = 0;

	struct SMallPresentAck : public CClientFuncAck
	{
		EMallResult eResult; //赠送结果返回

		SMallPresentAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：商场赠送
	virtual bool OnRecv_MallPresent(
		EUseMoneyMark eMark, //使用钱币标志
		EMallType eType, //商城类型
		UINT32 wInstID, //物品ID
		UINT16 wCount, //物品个数
		const std::string& strReceiveName, //接受者姓名
		const std::string& strTitle, //邮件标题
		const std::string& strMsg, //邮件内容
		shared_func<SMallPresentAck>& fnAck //返回回调函数
	) = 0;

	//接收：预览商城限购信息
	virtual void OnRecv_GetMallDiscountInfo(
	) = 0;

	struct SBuyDiscountItemAck : public CClientFuncAck
	{
		EMallResult eResult; //购买结果返回
		UINT8 byPos; //限购位置(0,1,2)
		UINT16 wCount; //购买个数

		SBuyDiscountItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买商场限购道具
	virtual bool OnRecv_BuyDiscountItem(
		UINT8 byPos, //限购位置(0,1,2)
		UINT16 wCount, //购买个数
		shared_func<SBuyDiscountItemAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBuyItemListAck : public CClientFuncAck
	{
		TVecBuyItemInfo vecBuyItemInfo; //购买数量列表

		SGetBuyItemListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取物品购买数量列表
	virtual bool OnRecv_GetBuyItemList(
		shared_func<SGetBuyItemListAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取玩家首次充值活动完成信息(在商城界面的奖励)
	virtual void OnRecv_GetChongZhiActInfo(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 27; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_MalGet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MalBuy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MallPresent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMallDiscountInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyDiscountItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBuyItemList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetChongZhiActInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CMallProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NMallProt
