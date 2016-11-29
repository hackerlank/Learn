/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ItemProt.h
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ItemProt.h"

namespace NItemProt
{

//协议类：道具相关协议
class CItemProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：包裹或仓库道具通知
	bool Send_StoreNotify( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize, //包裹或仓库的容量
		const TVecItem& vecStoreItem //包裹或仓库中道具的列表
	);
	bool SendClt_StoreNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize, //包裹或仓库的容量
		const TVecItem& vecStoreItem //包裹或仓库中道具的列表
	);
	std::string& BuildPkg_StoreNotify( //只组包不发送
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize, //包裹或仓库的容量
		const TVecItem& vecStoreItem //包裹或仓库中道具的列表
	);

	//发送：解锁格子还需要多少时间
	bool Send_PackNextUnlockTime( //发送给当前协议处理的客户端
		UINT32 dwTime //时间，单位秒
	);
	bool SendClt_PackNextUnlockTime(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间，单位秒
	);
	std::string& BuildPkg_PackNextUnlockTime( //只组包不发送
		UINT32 dwTime //时间，单位秒
	);

	//发送：包裹或仓库容量改变通知
	bool Send_StoreSizeChangeNotify( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize //包裹或仓库的容量
	);
	bool SendClt_StoreSizeChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize //包裹或仓库的容量
	);
	std::string& BuildPkg_StoreSizeChangeNotify( //只组包不发送
		EStoreType eStoreType, //存储类型
		UINT16 wStoreSize //包裹或仓库的容量
	);

	//发送：当前玩家的包裹或仓库中道具增加通知
	bool Send_StoreItemAddNtf( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);
	bool SendClt_StoreItemAddNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);
	std::string& BuildPkg_StoreItemAddNtf( //只组包不发送
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);

	//发送：当前玩家的包裹或仓库中道具删除通知
	bool Send_StoreItemDelNtf( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		const TVecUINT64& vecInstID //道具的实例ID列表
	);
	bool SendClt_StoreItemDelNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		const TVecUINT64& vecInstID //道具的实例ID列表
	);
	std::string& BuildPkg_StoreItemDelNtf( //只组包不发送
		EStoreType eStoreType, //存储类型
		const TVecUINT64& vecInstID //道具的实例ID列表
	);

	//发送：堆叠道具数量刷新通知
	bool Send_StackItemUpdate( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwRoleID, //角色ID
		UINT64 qwInstID, //堆叠道具的实例ID
		UINT16 wStack //当前堆叠数
	);
	bool SendClt_StackItemUpdate(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwRoleID, //角色ID
		UINT64 qwInstID, //堆叠道具的实例ID
		UINT16 wStack //当前堆叠数
	);
	std::string& BuildPkg_StackItemUpdate( //只组包不发送
		EStoreType eStoreType, //存储类型
		UINT64 qwRoleID, //角色ID
		UINT64 qwInstID, //堆叠道具的实例ID
		UINT16 wStack //当前堆叠数
	);

	//发送：打开包裹或仓库
	bool Send_OpenDepot( //发送给当前协议处理的客户端
		EStoreType eStoreType //存储类型
	);
	bool SendClt_OpenDepot(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType //存储类型
	);
	std::string& BuildPkg_OpenDepot( //只组包不发送
		EStoreType eStoreType //存储类型
	);

	//发送：道具绑定改变通知
	bool Send_ItemBindChangeNtf( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		EBindType eBindType, //道具的绑定类型
		bool bBind //道具是否绑定
	);
	bool SendClt_ItemBindChangeNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		EBindType eBindType, //道具的绑定类型
		bool bBind //道具是否绑定
	);
	std::string& BuildPkg_ItemBindChangeNtf( //只组包不发送
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		EBindType eBindType, //道具的绑定类型
		bool bBind //道具是否绑定
	);

	//发送：道具CD时间通知
	bool Send_ItemCDNtf( //发送给当前协议处理的客户端
		UINT8 byType, //冷却类型0:ItemID 1:GroupID
		const SItemColdTime& rItemCD //道具CD
	);
	bool SendClt_ItemCDNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byType, //冷却类型0:ItemID 1:GroupID
		const SItemColdTime& rItemCD //道具CD
	);
	std::string& BuildPkg_ItemCDNtf( //只组包不发送
		UINT8 byType, //冷却类型0:ItemID 1:GroupID
		const SItemColdTime& rItemCD //道具CD
	);

	//发送：道具的到期时间通知
	bool Send_ItemExpireTimeNtf( //发送给当前协议处理的客户端
		UINT64 qwInstID, //道具的实例ID
		UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
	);
	bool SendClt_ItemExpireTimeNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //道具的实例ID
		UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
	);
	std::string& BuildPkg_ItemExpireTimeNtf( //只组包不发送
		UINT64 qwInstID, //道具的实例ID
		UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
	);

	//发送：道具(装备)属性变化通知
	bool Send_ItemChangeNotify( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
		const SItemPtr& rStoreItem //装备更新后信息
	);
	bool SendClt_ItemChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
		const SItemPtr& rStoreItem //装备更新后信息
	);
	std::string& BuildPkg_ItemChangeNotify( //只组包不发送
		EStoreType eStoreType, //存储类型
		UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
		const SItemPtr& rStoreItem //装备更新后信息
	);

	//发送：清除道具使用冷却CD
	bool Send_ClearAllItemCDNtf( //发送给当前协议处理的客户端
	);
	bool SendClt_ClearAllItemCDNtf(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_ClearAllItemCDNtf( //只组包不发送
	);

	//发送：角色道具冷却通知
	bool Send_SlotItemCDNotify( //发送给当前协议处理的客户端
		const TVecItemColdTime& vecItemCold, //道具使用冷却时间
		const TVecItemColdTime& vecGroupCold //道具公共冷却时间
	);
	bool SendClt_SlotItemCDNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecItemColdTime& vecItemCold, //道具使用冷却时间
		const TVecItemColdTime& vecGroupCold //道具公共冷却时间
	);
	std::string& BuildPkg_SlotItemCDNotify( //只组包不发送
		const TVecItemColdTime& vecItemCold, //道具使用冷却时间
		const TVecItemColdTime& vecGroupCold //道具公共冷却时间
	);

	//发送：角色获得道具提示
	bool Send_AddItemSystemMsg( //发送给当前协议处理的客户端
		const TVecAddItemMsg& vecAddItemMsg //道具获得提示
	);
	bool SendClt_AddItemSystemMsg(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecAddItemMsg& vecAddItemMsg //道具获得提示
	);
	std::string& BuildPkg_AddItemSystemMsg( //只组包不发送
		const TVecAddItemMsg& vecAddItemMsg //道具获得提示
	);

	//发送：错误提示
	bool Send_ItemErrNfg( //发送给当前协议处理的客户端
		EItemResult eResult //提示
	);
	bool SendClt_ItemErrNfg(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EItemResult eResult //提示
	);
	std::string& BuildPkg_ItemErrNfg( //只组包不发送
		EItemResult eResult //提示
	);

	//发送：再一次增加记录道具通知
	bool Send_AgainAddloggedItemNotify( //发送给当前协议处理的客户端
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);
	bool SendClt_AgainAddloggedItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);
	std::string& BuildPkg_AgainAddloggedItemNotify( //只组包不发送
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);

	//发送：增加记录道具通知
	bool Send_AddLoggedItemNotify( //发送给当前协议处理的客户端
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);
	bool SendClt_AddLoggedItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);
	std::string& BuildPkg_AddLoggedItemNotify( //只组包不发送
		const TVecLoggedItem& rVecLoggedItem //道具列表
	);

	//发送：更新记录的堆叠道具通知
	bool Send_UpdateLoggedStackItemNotify( //发送给当前协议处理的客户端
		UINT16 wItemID, //ID
		UINT8 byQuality, //品质
		UINT32 dwCount //数目
	);
	bool SendClt_UpdateLoggedStackItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wItemID, //ID
		UINT8 byQuality, //品质
		UINT32 dwCount //数目
	);
	std::string& BuildPkg_UpdateLoggedStackItemNotify( //只组包不发送
		UINT16 wItemID, //ID
		UINT8 byQuality, //品质
		UINT32 dwCount //数目
	);

	//发送：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
	bool Send_CittaAddNtf( //发送给当前协议处理的客户端
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);
	bool SendClt_CittaAddNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);
	std::string& BuildPkg_CittaAddNtf( //只组包不发送
		EStoreType eStoreType, //存储类型
		const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
		bool bNew //是否新获得道具
	);

	//发送：更新记录的堆叠道具通知
	bool Send_NoticeUseItemNotify( //发送给当前协议处理的客户端
		UINT16 wItemID, //ID
		UINT32 dwNum, //使用物品数量
		const TVecResource& vecRes, //资源
		const TVecItemGenInfo& vecItem //物品
	);
	bool SendClt_NoticeUseItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wItemID, //ID
		UINT32 dwNum, //使用物品数量
		const TVecResource& vecRes, //资源
		const TVecItemGenInfo& vecItem //物品
	);
	std::string& BuildPkg_NoticeUseItemNotify( //只组包不发送
		UINT16 wItemID, //ID
		UINT32 dwNum, //使用物品数量
		const TVecResource& vecRes, //资源
		const TVecItemGenInfo& vecItem //物品
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetStoreAck : public CClientFuncAck
	{
		SStoreStream stStoreStream; //背包信息
		UINT32 dwNextUnlockTime; //下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒

		SGetStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求包裹信息(整个包裹)
	virtual bool OnRecv_GetStore(
		EStoreType eStoreType, //存储类型
		shared_func<SGetStoreAck>& fnAck //返回回调函数
	) = 0;

	struct SUseItemAck : public CClientFuncAck
	{
		EItemResult eResult; //使用道具结果

		SUseItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求使用包裹中的道具
	virtual bool OnRecv_UseItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwRoleID, //针对的角色ID
		UINT64 qwMercenID, //针对的佣兵ID
		UINT64 qwInstID, //优先使用的物品实例ID
		UINT16 wStack, //使用个数(只针对堆叠道具)
		shared_func<SUseItemAck>& fnAck //返回回调函数
	) = 0;

	struct SExpandStoreAck : public CClientFuncAck
	{
		EItemResult eResult; //扩充结果

		SExpandStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扩充包裹或仓库
	virtual bool OnRecv_ExpandStore(
		EStoreType eStoreType, //存储类型
		UINT8 byCount, //扩充个数
		NProtoCommon::ECoinType eCoinType, //货币类型
		shared_func<SExpandStoreAck>& fnAck //返回回调函数
	) = 0;

	struct SRelocateStoreItemAck : public CClientFuncAck
	{
		EItemResult eResult; //换位置的结果

		SRelocateStoreItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：包裹或仓库中道具换位置
	virtual bool OnRecv_RelocateStoreItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		INT16 wNewIndex, //道具在包裹中新的位置0开始
		shared_func<SRelocateStoreItemAck>& fnAck //返回回调函数
	) = 0;

	struct STidyupStoreAck : public CClientFuncAck
	{
		EItemResult eResult; //整理的结果

		STidyupStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：整理包裹或仓库
	virtual bool OnRecv_TidyupStore(
		EStoreType eStoreType, //存储类型
		shared_func<STidyupStoreAck>& fnAck //返回回调函数
	) = 0;

	struct SSplitStackItemAck : public CClientFuncAck
	{
		EItemResult eResult; //拆分的结果

		SSplitStackItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：拆分包裹或仓库中的堆叠类道具
	virtual bool OnRecv_SplitStackItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		UINT16 wStack, //拆分出来的堆叠数量
		INT16 wIndex, //拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
		shared_func<SSplitStackItemAck>& fnAck //返回回调函数
	) = 0;

	struct SMergeStackItemAck : public CClientFuncAck
	{
		EItemResult eResult; //合并的结果

		SMergeStackItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：合并包裹或仓库中的堆叠类道具
	virtual bool OnRecv_MergeStackItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwFromInstID, //源道具的实例ID
		UINT64 qwToInstID, //目的道具的实例ID
		shared_func<SMergeStackItemAck>& fnAck //返回回调函数
	) = 0;

	struct SDestroyStoreItemAck : public CClientFuncAck
	{
		EItemResult eResult; //销毁的结果

		SDestroyStoreItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：销毁包裹或仓库中的道具
	virtual bool OnRecv_DestroyStoreItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		shared_func<SDestroyStoreItemAck>& fnAck //返回回调函数
	) = 0;

	struct STransferItemAck : public CClientFuncAck
	{
		EItemResult eResult; //移动的结果

		STransferItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：在包裹和仓库之间移动道具
	virtual bool OnRecv_TransferItem(
		EStoreType eFromStoreType, //源存储类型
		EStoreType eToStoreType, //目的存储类型
		UINT64 qwInstID, //道具的实例ID
		INT16 wIndex, //道具在目的存储中的位置(-1表示选第一个空位)
		shared_func<STransferItemAck>& fnAck //返回回调函数
	) = 0;

	struct SSellItemAck : public CClientFuncAck
	{
		EItemResult eResult; //使用道具结果

		SSellItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求出售包裹中的道具-出售给系统
	virtual bool OnRecv_SellItem(
		const TVecUINT64& vecInstID, //出售的道具实例ID集合
		shared_func<SSellItemAck>& fnAck //返回回调函数
	) = 0;

	struct SSellItemWithCountAck : public CClientFuncAck
	{
		EItemResult eResult; //卖出道具结果

		SSellItemWithCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求按个数出售包裹中的道具-出售给系统
	virtual bool OnRecv_SellItemWithCount(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //优先卖出的物品实例ID
		UINT16 wStack, //卖出个数
		shared_func<SSellItemWithCountAck>& fnAck //返回回调函数
	) = 0;

	struct SUnlockPackAck : public CClientFuncAck
	{
		EItemResult eResult; //结果

		SUnlockPackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：解锁背包格子
	virtual bool OnRecv_UnlockPack(
		shared_func<SUnlockPackAck>& fnAck //返回回调函数
	) = 0;

	//接收：打开道具日志
	virtual void OnRecv_OpenItemLogger(
		EItemLoggerType eType //
	) = 0;

	struct SRecordTransfPointAck : public CClientFuncAck
	{
		EItemResult eResult; //结果

		SRecordTransfPointAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：记录传送点
	virtual bool OnRecv_RecordTransfPoint(
		UINT64 qwInstID, //道具ID
		UINT16 wIndex, //存储序号
		shared_func<SRecordTransfPointAck>& fnAck //返回回调函数
	) = 0;

	struct STransfMapPointAck : public CClientFuncAck
	{
		EItemResult eResult; //结果

		STransfMapPointAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：传送
	virtual bool OnRecv_TransfMapPoint(
		UINT64 qwInstID, //道具ID
		UINT16 wIndex, //存储序号
		UINT16 wMapID, //地图ID
		shared_func<STransfMapPointAck>& fnAck //返回回调函数
	) = 0;

	struct SWearCittaAck : public CClientFuncAck
	{
		ECittaResult eResult; //穿上装备的结果

		SWearCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求装备心法
	virtual bool OnRecv_WearCitta(
		UINT64 qwInstID, //装备的实例ID
		ECittaSlotType eSlotType, //装备位的类型
		shared_func<SWearCittaAck>& fnAck //返回回调函数
	) = 0;

	struct STakeoffCittaAck : public CClientFuncAck
	{
		ECittaResult eResult; //脱下装备的结果

		STakeoffCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求卸下心法
	virtual bool OnRecv_TakeoffCitta(
		ECittaSlotType eSlotType, //装备位的类型
		INT16 wIndex, //放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
		shared_func<STakeoffCittaAck>& fnAck //返回回调函数
	) = 0;

	struct SMergeCittaAck : public CClientFuncAck
	{
		ECittaResult eResult; //结果
		TVecItem vecItemCitta; //新增的道具

		SMergeCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求合成心法
	virtual bool OnRecv_MergeCitta(
		EBindUseType eBindType, //绑定使用方式
		UINT16 wItemID, //制作心法模版ID
		UINT16 wCount, //制作数量
		shared_func<SMergeCittaAck>& fnAck //返回回调函数
	) = 0;

	struct SBreakCittaAck : public CClientFuncAck
	{
		ECittaResult eResult; //结果
		TVecItemGenInfo vecItemInfo; //分解产生的道具

		SBreakCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求分解心法
	virtual bool OnRecv_BreakCitta(
		const TVecUINT64& vecInstID, //物品唯一ID
		shared_func<SBreakCittaAck>& fnAck //返回回调函数
	) = 0;

	struct SActiveTrumpAck : public CClientFuncAck
	{
		ETrumpResult eResult; //结果
		TVecTrump vecTrump; //新法宝

		SActiveTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：激活法宝
	virtual bool OnRecv_ActiveTrump(
		UINT16 wItemID, //法宝道具ID
		shared_func<SActiveTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SEquipTrumpAck : public CClientFuncAck
	{
		ETrumpResult eResult; //结果
		TVecTrump vecTrump; //新法宝

		SEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：出战法宝
	virtual bool OnRecv_EquipTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SEquipTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SUnEquipTrumpAck : public CClientFuncAck
	{
		ETrumpResult eResult; //结果
		TVecTrump vecTrump; //新法宝

		SUnEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：卸下法宝
	virtual bool OnRecv_UnEquipTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SUnEquipTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeTrumpAck : public CClientFuncAck
	{
		ETrumpResult eResult; //结果
		TVecTrump vecTrump; //新法宝

		SUpgradeTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：祭炼法宝
	virtual bool OnRecv_UpgradeTrump(
		UINT64 qwInstID, //法宝的实例ID
		UINT8 byOneKey, //是否一键
		shared_func<SUpgradeTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SEvolveTrumpAck : public CClientFuncAck
	{
		ETrumpResult eResult; //结果
		TVecTrump vecTrump; //新法宝

		SEvolveTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：提升法宝品级
	virtual bool OnRecv_EvolveTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SEvolveTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SFashionActiveAck : public CClientFuncAck
	{
		EFashionResult eResult; //结果

		SFashionActiveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：激活时装
	virtual bool OnRecv_FashionActive(
		UINT16 wItemID, //时装物品ID
		shared_func<SFashionActiveAck>& fnAck //返回回调函数
	) = 0;

	struct SFashionHideAck : public CClientFuncAck
	{
		EFashionResult eResult; //结果

		SFashionHideAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：隐藏所选时装
	virtual bool OnRecv_FashionHide(
		UINT8 byType, //0-神器时装 1-神依时装
		UINT8 byHide, //0-显示 1-隐藏
		shared_func<SFashionHideAck>& fnAck //返回回调函数
	) = 0;

	struct SFashionChangeAck : public CClientFuncAck
	{
		EFashionResult eResult; //结果

		SFashionChangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：选择时装
	virtual bool OnRecv_FashionChange(
		UINT64 qwInstID, //时装唯一ID
		shared_func<SFashionChangeAck>& fnAck //返回回调函数
	) = 0;

	struct SFashionUpgradeAck : public CClientFuncAck
	{
		EFashionResult eResult; //结果

		SFashionUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：时装炼化
	virtual bool OnRecv_FashionUpgrade(
		UINT64 qwInstID, //时装物品ID
		UINT8 byOneKey, //是否一键
		shared_func<SFashionUpgradeAck>& fnAck //返回回调函数
	) = 0;

	struct SWareGemStoneAck : public CClientFuncAck
	{
		EGemstoneResult eResult; //结果
		UINT64 qwFighterID; //将ID
		UINT8 byPos; //穿戴位置
		SGemstone Item; //宝石

		SWareGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：穿戴宝石
	virtual bool OnRecv_WareGemStone(
		UINT16 wItemID, //宝石模板ID
		UINT64 qwFighterID, //将ID
		UINT8 byPos, //穿戴位置
		shared_func<SWareGemStoneAck>& fnAck //返回回调函数
	) = 0;

	struct STakeOffGemStoneAck : public CClientFuncAck
	{
		EGemstoneResult eResult; //结果
		UINT64 qwFighterID; //将ID
		UINT8 byPos; //穿戴位置

		STakeOffGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取下宝石
	virtual bool OnRecv_TakeOffGemStone(
		UINT64 qwFighterID, //将ID
		UINT8 byPos, //穿戴位置0~5,6表示全部卸下
		shared_func<STakeOffGemStoneAck>& fnAck //返回回调函数
	) = 0;

	struct SComposeGemStoneAck : public CClientFuncAck
	{
		EGemstoneResult eResult; //结果

		SComposeGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：合成宝石
	virtual bool OnRecv_ComposeGemStone(
		UINT16 wItemID, //宝石模板ID
		UINT32 dwNum, //合成数量
		shared_func<SComposeGemStoneAck>& fnAck //返回回调函数
	) = 0;

	struct SComposeGemStoneOneKeyAck : public CClientFuncAck
	{
		EGemstoneResult eResult; //结果

		SComposeGemStoneOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：一键合成宝石
	virtual bool OnRecv_ComposeGemStoneOneKey(
		const TVecGMMailItem& vecStone, //合成宝石列表
		shared_func<SComposeGemStoneOneKeyAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 18; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetStore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UseItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ExpandStore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RelocateStoreItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TidyupStore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SplitStackItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MergeStackItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DestroyStoreItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TransferItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SellItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SellItemWithCount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UnlockPack(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenItemLogger(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RecordTransfPoint(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TransfMapPoint(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WearCitta(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeoffCitta(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MergeCitta(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BreakCitta(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ActiveTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EquipTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UnEquipTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EvolveTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FashionActive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FashionHide(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FashionChange(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FashionUpgrade(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WareGemStone(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeOffGemStone(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ComposeGemStone(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ComposeGemStoneOneKey(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CItemProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NItemProt
