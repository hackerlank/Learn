#ifndef ITEM_PROT_S_H
#define ITEM_PROT_S_H

#pragma once
#include "ItemProtSvr.h"

using namespace NItemProt;

class CItemProtS : public CItemProtSvr
{
public:
	//接收：请求包裹信息(整个包裹)
	virtual bool OnRecv_GetStore(
		EStoreType eStoreType, //存储类型
		shared_func<SGetStoreAck>& fnAck //返回回调函数
	);

	//接收：请求使用包裹中的道具
	virtual bool OnRecv_UseItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwRoleID, //针对的角色ID
		UINT64 qwMercenID,	//针对的佣兵ID
		UINT64 qwInstID, //优先使用的物品实例ID
		UINT16 wStack, //使用个数(只针对堆叠道具)
		shared_func<SUseItemAck>& fnAck //返回回调函数
		);

	//接收：扩充包裹或仓库
	virtual bool OnRecv_ExpandStore(
		EStoreType eStoreType, //存储类型
		UINT8 byCount, //扩充个数
		NProtoCommon::ECoinType eCoinType, //货币类型
		shared_func<SExpandStoreAck>& fnAck //返回回调函数
		);

	//接收：包裹或仓库中道具换位置
	virtual bool OnRecv_RelocateStoreItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		INT16 wNewIndex, //道具在包裹中新的位置0开始
		shared_func<SRelocateStoreItemAck>& fnAck //返回回调函数
		);

	//接收：整理包裹或仓库
	virtual bool OnRecv_TidyupStore(
		EStoreType eStoreType, //存储类型
		shared_func<STidyupStoreAck>& fnAck //返回回调函数
		);

	//接收：拆分包裹或仓库中的堆叠类道具
	virtual bool OnRecv_SplitStackItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		UINT16 wStack, //拆分出来的堆叠数量
		INT16 wIndex, //拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
		shared_func<SSplitStackItemAck>& fnAck //返回回调函数
		);

	//接收：合并包裹或仓库中的堆叠类道具
	virtual bool OnRecv_MergeStackItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwFromInstID, //源道具的实例ID
		UINT64 qwToInstID, //目的道具的实例ID
		shared_func<SMergeStackItemAck>& fnAck //返回回调函数
		);

	//接收：销毁包裹或仓库中的道具
	virtual bool OnRecv_DestroyStoreItem(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //道具的实例ID
		shared_func<SDestroyStoreItemAck>& fnAck //返回回调函数
		);

	//接收：在包裹和仓库之间移动道具
	virtual bool OnRecv_TransferItem(
		EStoreType eFromStoreType, //源存储类型
		EStoreType eToStoreType, //目的存储类型
		UINT64 qwInstID, //道具的实例ID
		INT16 wIndex, //道具在目的存储中的位置(-1表示选第一个空位)
		shared_func<STransferItemAck>& fnAck //返回回调函数
		);

	//接收：请求出售包裹中的道具
	virtual bool OnRecv_SellItem(
		const TVecUINT64& vecInstID, //出售的道具实例ID集合
		shared_func<SSellItemAck>& fnAck //返回回调函数
		);
	//接收：请求按个数出售包裹中的道具-出售给系统
	virtual bool OnRecv_SellItemWithCount(
		EStoreType eStoreType, //存储类型
		UINT64 qwInstID, //优先卖出的物品实例ID
		UINT16 wStack, //卖出个数(只针对堆叠道具)
		shared_func<SSellItemWithCountAck>& fnAck //返回回调函数
	);
	//接收：解锁背包格子
	virtual bool OnRecv_UnlockPack(
		shared_func<SUnlockPackAck>& fnAck //返回回调函数
	);
	//接收：打开道具日志
	virtual void OnRecv_OpenItemLogger(
		EItemLoggerType eType
		);

	//接收：记录传送点
	virtual bool OnRecv_RecordTransfPoint(
		UINT64 qwInstID, //道具ID
		UINT16 wIndex, //存储序号
		shared_func<SRecordTransfPointAck>& fnAck //返回回调函数
		);

	//接收：传送
	virtual bool OnRecv_TransfMapPoint(
		UINT64 qwInstID, //道具ID
		UINT16 wIndex, //存储序号
		UINT16 wMapID, //地图ID
		shared_func<STransfMapPointAck>& fnAck //返回回调函数
		);

	//接收：请求装备心法
	virtual bool OnRecv_WearCitta(
		UINT64 qwInstID, //装备的实例ID
		ECittaSlotType eSlotType, //装备位的类型
		shared_func<SWearCittaAck>& fnAck //返回回调函数
	);
	//接收：请求卸下心法
	virtual bool OnRecv_TakeoffCitta(
		ECittaSlotType eSlotType, //装备位的类型
		INT16 wIndex, //放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
		shared_func<STakeoffCittaAck>& fnAck //返回回调函数
	);
	//接收：请求合成心法
	virtual bool OnRecv_MergeCitta(
		EBindUseType eBindUseType, //合成方式
		UINT16 wItemID, //制作心法模版ID
		UINT16 wCount, //制作数量
		shared_func<SMergeCittaAck>& fnAck //返回回调函数
	);
	//接收：请求分解心法
	virtual bool OnRecv_BreakCitta(
		const TVecUINT64& vecInstID, //物品唯一ID
		shared_func<SBreakCittaAck>& fnAck //返回回调函数
	);
	//接收：激活法宝
	virtual bool OnRecv_ActiveTrump(
		UINT16 wItemID, //法宝道具ID
		shared_func<SActiveTrumpAck>& fnAck //返回回调函数
	);
	//接收：出战法宝
	virtual bool OnRecv_EquipTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SEquipTrumpAck>& fnAck //返回回调函数
	);
	//接收：卸下法宝
	virtual bool OnRecv_UnEquipTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SUnEquipTrumpAck>& fnAck //返回回调函数
	);
	//接收：祭炼法宝
	virtual bool OnRecv_UpgradeTrump(
		UINT64 qwInstID, //法宝的实例ID
		UINT8 byOneKey, //是否一键
		shared_func<SUpgradeTrumpAck>& fnAck //返回回调函数
	);
	//接收：提升法宝品级
	virtual bool OnRecv_EvolveTrump(
		UINT64 qwInstID, //法宝的实例ID
		shared_func<SEvolveTrumpAck>& fnAck //返回回调函数
	);
	//接收：激活时装
	virtual bool OnRecv_FashionActive(
		UINT16 wItemID, //时装物品ID
		shared_func<SFashionActiveAck>& fnAck //返回回调函数
	);
	//接收：隐藏所选时装
	virtual bool OnRecv_FashionHide(
		UINT8 byType, //0-神器时装 1-神依时装
		UINT8 byHide, //0-显示 1-隐藏
		shared_func<SFashionHideAck>& fnAck //返回回调函数
	);
	//接收：选择时装
	virtual bool OnRecv_FashionChange(
		UINT64 qwInstID, //时装唯一ID
		shared_func<SFashionChangeAck>& fnAck //返回回调函数
	);
	//接收：时装炼化
	virtual bool OnRecv_FashionUpgrade(
		UINT64 qwInstID, //时装物品ID
		UINT8 byOneKey, //是否一键
		shared_func<SFashionUpgradeAck>& fnAck //返回回调函数
	);
	//接收：穿戴宝石
	virtual bool OnRecv_WareGemStone(
		UINT16 wItemID, //宝石模板ID
		UINT64 qwFighterID, //将ID
		UINT8 byPos, //穿戴位置
		shared_func<SWareGemStoneAck>& fnAck //返回回调函数
	) ;

	//接收：取下宝石
	virtual bool OnRecv_TakeOffGemStone(
		UINT64 qwFighterID, //将ID
		UINT8 byPos, //穿戴位置0~5,6表示全部卸下
		shared_func<STakeOffGemStoneAck>& fnAck //返回回调函数
	);

	//接收：合成宝石
	virtual bool OnRecv_ComposeGemStone(
		UINT16 wItemID, //宝石模板ID
		UINT32 dwNum, //合成数量
		shared_func<SComposeGemStoneAck>& fnAck //返回回调函数
	);

	//接收：一键合成宝石
	virtual bool OnRecv_ComposeGemStoneOneKey(
		const TVecGMMailItem& vecStone, //合成宝石列表
		shared_func<SComposeGemStoneOneKeyAck>& fnAck //返回回调函数
	);

	
private:
	void SendSysMsgIDNotify(EItemResult eResult);
    void SendSysMsgIDNotify(EGemstoneResult eResult);
};

#endif // #ifndef ITEM_PROT_S_H
