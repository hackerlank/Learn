/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ItemProt.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：道具相关协议
	 */
	public class ItemProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求包裹信息(整个包裹)
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 */
		public function send_GetStore(eStoreType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetStore = new SOrigParam_GetStore();
			origParam_.eStoreType = eStoreType;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求使用包裹中的道具
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwRoleID (无符号64位整数)针对的角色ID
		 * @param qwMercenID (无符号64位整数)针对的佣兵ID
		 * @param qwInstID (无符号64位整数)优先使用的物品实例ID
		 * @param wStack (无符号16位整数)使用个数(只针对堆叠道具)
		 */
		public function send_UseItem(eStoreType:uint, qwRoleID:BigInteger, qwMercenID:BigInteger, qwInstID:BigInteger, wStack:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_UseItem = new SOrigParam_UseItem();
			origParam_.eStoreType = eStoreType;
			origParam_.qwRoleID = qwRoleID;
			origParam_.qwMercenID = qwMercenID;
			origParam_.qwInstID = qwInstID;
			origParam_.wStack = wStack;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			BytesUtil.writeUInt64(bytes_, qwMercenID);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wStack);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：扩充包裹或仓库
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param byCount (无符号8位整数)扩充个数
		 * @param eCoinType (枚举类型：protoCommon.ECoinType)货币类型
		 */
		public function send_ExpandStore(eStoreType:uint, byCount:uint, eCoinType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ExpandStore = new SOrigParam_ExpandStore();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			bytes_.writeByte(byCount);
			bytes_.writeByte(eCoinType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：包裹或仓库中道具换位置
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwInstID (无符号64位整数)道具的实例ID
		 * @param wNewIndex (有符号16位整数)道具在包裹中新的位置0开始
		 */
		public function send_RelocateStoreItem(eStoreType:uint, qwInstID:BigInteger, wNewIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_RelocateStoreItem = new SOrigParam_RelocateStoreItem();
			origParam_.eStoreType = eStoreType;
			origParam_.qwInstID = qwInstID;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wNewIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：整理包裹或仓库
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 */
		public function send_TidyupStore(eStoreType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_TidyupStore = new SOrigParam_TidyupStore();
			origParam_.eStoreType = eStoreType;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：拆分包裹或仓库中的堆叠类道具
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwInstID (无符号64位整数)道具的实例ID
		 * @param wStack (无符号16位整数)拆分出来的堆叠数量
		 * @param wIndex (有符号16位整数)拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
		 */
		public function send_SplitStackItem(eStoreType:uint, qwInstID:BigInteger, wStack:uint, wIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_SplitStackItem = new SOrigParam_SplitStackItem();
			origParam_.eStoreType = eStoreType;
			origParam_.qwInstID = qwInstID;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wStack);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：合并包裹或仓库中的堆叠类道具
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwFromInstID (无符号64位整数)源道具的实例ID
		 * @param qwToInstID (无符号64位整数)目的道具的实例ID
		 */
		public function send_MergeStackItem(eStoreType:uint, qwFromInstID:BigInteger, qwToInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_MergeStackItem = new SOrigParam_MergeStackItem();
			origParam_.eStoreType = eStoreType;
			origParam_.qwFromInstID = qwFromInstID;
			origParam_.qwToInstID = qwToInstID;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwFromInstID);
			BytesUtil.writeUInt64(bytes_, qwToInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：销毁包裹或仓库中的道具
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwInstID (无符号64位整数)道具的实例ID
		 */
		public function send_DestroyStoreItem(eStoreType:uint, qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_DestroyStoreItem = new SOrigParam_DestroyStoreItem();
			origParam_.eStoreType = eStoreType;
			origParam_.qwInstID = qwInstID;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：在包裹和仓库之间移动道具
		 * @param eFromStoreType (枚举类型：EStoreType)源存储类型
		 * @param eToStoreType (枚举类型：EStoreType)目的存储类型
		 * @param qwInstID (无符号64位整数)道具的实例ID
		 * @param wIndex (有符号16位整数)道具在目的存储中的位置(-1表示选第一个空位)
		 */
		public function send_TransferItem(eFromStoreType:uint, eToStoreType:uint, qwInstID:BigInteger, wIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_TransferItem = new SOrigParam_TransferItem();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eFromStoreType);
			bytes_.writeByte(eToStoreType);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求出售包裹中的道具-出售给系统
		 * @param vecInstID (无符号64位整数)出售的道具实例ID集合
		 */
		public function send_SellItem(vecInstID:Vector.<BigInteger>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_SellItem = new SOrigParam_SellItem();
			origParam_.vecInstID = vecInstID;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeVecUInt64(bytes_, vecInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求按个数出售包裹中的道具-出售给系统
		 * @param eStoreType (枚举类型：EStoreType)存储类型
		 * @param qwInstID (无符号64位整数)优先卖出的物品实例ID
		 * @param wStack (无符号16位整数)卖出个数
		 */
		public function send_SellItemWithCount(eStoreType:uint, qwInstID:BigInteger, wStack:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_SellItemWithCount = new SOrigParam_SellItemWithCount();
			origParam_.eStoreType = eStoreType;
			origParam_.qwInstID = qwInstID;
			origParam_.wStack = wStack;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eStoreType);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wStack);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：解锁背包格子
		 */
		public function send_UnlockPack(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_UnlockPack = new SOrigParam_UnlockPack();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：打开道具日志
		 * @param eType (枚举类型：EItemLoggerType)
		 */
		public function send_OpenItemLogger(eType:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：记录传送点
		 * @param qwInstID (无符号64位整数)道具ID
		 * @param wIndex (无符号16位整数)存储序号
		 */
		public function send_RecordTransfPoint(qwInstID:BigInteger, wIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_RecordTransfPoint = new SOrigParam_RecordTransfPoint();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：传送
		 * @param qwInstID (无符号64位整数)道具ID
		 * @param wIndex (无符号16位整数)存储序号
		 * @param wMapID (无符号16位整数)地图ID
		 */
		public function send_TransfMapPoint(qwInstID:BigInteger, wIndex:uint, wMapID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_TransfMapPoint = new SOrigParam_TransfMapPoint();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wIndex);
			bytes_.writeShort(wMapID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求装备心法
		 * @param qwInstID (无符号64位整数)装备的实例ID
		 * @param eSlotType (枚举类型：ECittaSlotType)装备位的类型
		 */
		public function send_WearCitta(qwInstID:BigInteger, eSlotType:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_WearCitta = new SOrigParam_WearCitta();
			origParam_.qwInstID = qwInstID;
			origParam_.eSlotType = eSlotType;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(eSlotType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求卸下心法
		 * @param eSlotType (枚举类型：ECittaSlotType)装备位的类型
		 * @param wIndex (有符号16位整数)放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
		 */
		public function send_TakeoffCitta(eSlotType:int, wIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_TakeoffCitta = new SOrigParam_TakeoffCitta();
			origParam_.eSlotType = eSlotType;
			origParam_.wIndex = wIndex;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eSlotType);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求合成心法
		 * @param eBindType (枚举类型：EBindUseType)绑定使用方式
		 * @param wItemID (无符号16位整数)制作心法模版ID
		 * @param wCount (无符号16位整数)制作数量
		 */
		public function send_MergeCitta(eBindType:uint, wItemID:uint, wCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 17);
			var origParam_:SOrigParam_MergeCitta = new SOrigParam_MergeCitta();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 18;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eBindType);
			bytes_.writeShort(wItemID);
			bytes_.writeShort(wCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求分解心法
		 * @param vecInstID (无符号64位整数)物品唯一ID
		 */
		public function send_BreakCitta(vecInstID:Vector.<BigInteger>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 18);
			var origParam_:SOrigParam_BreakCitta = new SOrigParam_BreakCitta();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 19;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeVecUInt64(bytes_, vecInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：激活法宝
		 * @param wItemID (无符号16位整数)法宝道具ID
		 */
		public function send_ActiveTrump(wItemID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 19);
			var origParam_:SOrigParam_ActiveTrump = new SOrigParam_ActiveTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 20;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wItemID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：出战法宝
		 * @param qwInstID (无符号64位整数)法宝的实例ID
		 */
		public function send_EquipTrump(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 20);
			var origParam_:SOrigParam_EquipTrump = new SOrigParam_EquipTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 21;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：卸下法宝
		 * @param qwInstID (无符号64位整数)法宝的实例ID
		 */
		public function send_UnEquipTrump(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 21);
			var origParam_:SOrigParam_UnEquipTrump = new SOrigParam_UnEquipTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 22;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：祭炼法宝
		 * @param qwInstID (无符号64位整数)法宝的实例ID
		 * @param byOneKey (无符号8位整数)是否一键
		 */
		public function send_UpgradeTrump(qwInstID:BigInteger, byOneKey:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 22);
			var origParam_:SOrigParam_UpgradeTrump = new SOrigParam_UpgradeTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 23;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(byOneKey);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：提升法宝品级
		 * @param qwInstID (无符号64位整数)法宝的实例ID
		 */
		public function send_EvolveTrump(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 23);
			var origParam_:SOrigParam_EvolveTrump = new SOrigParam_EvolveTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 24;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：激活时装
		 * @param wItemID (无符号16位整数)时装物品ID
		 */
		public function send_FashionActive(wItemID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 24);
			var origParam_:SOrigParam_FashionActive = new SOrigParam_FashionActive();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 25;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wItemID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：隐藏所选时装
		 * @param byType (无符号8位整数)0-神器时装 1-神依时装
		 * @param byHide (无符号8位整数)0-显示 1-隐藏
		 */
		public function send_FashionHide(byType:uint, byHide:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 25);
			var origParam_:SOrigParam_FashionHide = new SOrigParam_FashionHide();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 26;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			bytes_.writeByte(byHide);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：选择时装
		 * @param qwInstID (无符号64位整数)时装唯一ID
		 */
		public function send_FashionChange(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 26);
			var origParam_:SOrigParam_FashionChange = new SOrigParam_FashionChange();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 27;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：时装炼化
		 * @param qwInstID (无符号64位整数)时装物品ID
		 * @param byOneKey (无符号8位整数)是否一键
		 */
		public function send_FashionUpgrade(qwInstID:BigInteger, byOneKey:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 27);
			var origParam_:SOrigParam_FashionUpgrade = new SOrigParam_FashionUpgrade();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 28;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(byOneKey);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：穿戴宝石
		 * @param wItemID (无符号16位整数)宝石模板ID
		 * @param qwFighterID (无符号64位整数)将ID
		 * @param byPos (无符号8位整数)穿戴位置
		 */
		public function send_WareGemStone(wItemID:uint, qwFighterID:BigInteger, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 28);
			var origParam_:SOrigParam_WareGemStone = new SOrigParam_WareGemStone();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 29;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wItemID);
			BytesUtil.writeUInt64(bytes_, qwFighterID);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：取下宝石
		 * @param qwFighterID (无符号64位整数)将ID
		 * @param byPos (无符号8位整数)穿戴位置0~5,6表示全部卸下
		 */
		public function send_TakeOffGemStone(qwFighterID:BigInteger, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 29);
			var origParam_:SOrigParam_TakeOffGemStone = new SOrigParam_TakeOffGemStone();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 30;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwFighterID);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：合成宝石
		 * @param wItemID (无符号16位整数)宝石模板ID
		 * @param dwNum (无符号32位整数)合成数量
		 */
		public function send_ComposeGemStone(wItemID:uint, dwNum:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 30);
			var origParam_:SOrigParam_ComposeGemStone = new SOrigParam_ComposeGemStone();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 31;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wItemID);
			bytes_.writeUnsignedInt(dwNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：一键合成宝石
		 * @param vecStone 合成宝石列表
		 */
		public function send_ComposeGemStoneOneKey(vecStone:Vector.<SGMMailItem>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 31);
			var origParam_:SOrigParam_ComposeGemStoneOneKey = new SOrigParam_ComposeGemStoneOneKey();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 32;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			SGMMailItem.vectorToByteArray(vecStone, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：包裹或仓库道具通知
		private function _doRecv_StoreNotify(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var wStoreSize:uint = bytes.readUnsignedShort(); //(无符号16位整数)包裹或仓库的容量
			var vecStoreItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes); //包裹或仓库中道具的列表
			var event_:REvt_StoreNotify = new REvt_StoreNotify(REvt_StoreNotify.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.wStoreSize = wStoreSize;
			event_.vecStoreItem = vecStoreItem;
			dispatchEvent(event_);
		}

		//接收处理：解锁格子还需要多少时间
		private function _doRecv_PackNextUnlockTime(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间，单位秒
			var event_:REvt_PackNextUnlockTime = new REvt_PackNextUnlockTime(REvt_PackNextUnlockTime.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：包裹或仓库容量改变通知
		private function _doRecv_StoreSizeChangeNotify(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var wStoreSize:uint = bytes.readUnsignedShort(); //(无符号16位整数)包裹或仓库的容量
			var event_:REvt_StoreSizeChangeNotify = new REvt_StoreSizeChangeNotify(REvt_StoreSizeChangeNotify.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.wStoreSize = wStoreSize;
			dispatchEvent(event_);
		}

		//接收处理：当前玩家的包裹或仓库中道具增加通知
		private function _doRecv_StoreItemAddNtf(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var vecStoreItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes); //包裹或仓库中道具的列表
			var bNew:Boolean = bytes.readBoolean(); //是否新获得道具
			var event_:REvt_StoreItemAddNtf = new REvt_StoreItemAddNtf(REvt_StoreItemAddNtf.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.vecStoreItem = vecStoreItem;
			event_.bNew = bNew;
			dispatchEvent(event_);
		}

		//接收处理：当前玩家的包裹或仓库中道具删除通知
		private function _doRecv_StoreItemDelNtf(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var vecInstID:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes); //(无符号64位整数)道具的实例ID列表
			var event_:REvt_StoreItemDelNtf = new REvt_StoreItemDelNtf(REvt_StoreItemDelNtf.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.vecInstID = vecInstID;
			dispatchEvent(event_);
		}

		//接收处理：堆叠道具数量刷新通知
		private function _doRecv_StackItemUpdate(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色ID
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)堆叠道具的实例ID
			var wStack:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前堆叠数
			var event_:REvt_StackItemUpdate = new REvt_StackItemUpdate(REvt_StackItemUpdate.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.qwRoleID = qwRoleID;
			event_.qwInstID = qwInstID;
			event_.wStack = wStack;
			dispatchEvent(event_);
		}

		//接收处理：打开包裹或仓库
		private function _doRecv_OpenDepot(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var event_:REvt_OpenDepot = new REvt_OpenDepot(REvt_OpenDepot.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			dispatchEvent(event_);
		}

		//接收处理：道具绑定改变通知
		private function _doRecv_ItemBindChangeNtf(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)道具的实例ID
			var eBindType:uint = bytes.readUnsignedByte(); //(枚举类型：EBindType)道具的绑定类型
			var bBind:Boolean = bytes.readBoolean(); //道具是否绑定
			var event_:REvt_ItemBindChangeNtf = new REvt_ItemBindChangeNtf(REvt_ItemBindChangeNtf.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.qwInstID = qwInstID;
			event_.eBindType = eBindType;
			event_.bBind = bBind;
			dispatchEvent(event_);
		}

		//接收处理：道具CD时间通知
		private function _doRecv_ItemCDNtf(bytes:ByteArray):void
		{
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)冷却类型0:ItemID 1:GroupID
			var rItemCD:SItemColdTime = SItemColdTime.fromByteArray(bytes); //道具CD
			var event_:REvt_ItemCDNtf = new REvt_ItemCDNtf(REvt_ItemCDNtf.DATA_RECEIVE);
			event_.byType = byType;
			event_.rItemCD = rItemCD;
			dispatchEvent(event_);
		}

		//接收处理：道具的到期时间通知
		private function _doRecv_ItemExpireTimeNtf(bytes:ByteArray):void
		{
			var qwInstID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)道具的实例ID
			var dwExpireTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)到期时间(1970年1月1日0时开始的秒数)
			var event_:REvt_ItemExpireTimeNtf = new REvt_ItemExpireTimeNtf(REvt_ItemExpireTimeNtf.DATA_RECEIVE);
			event_.qwInstID = qwInstID;
			event_.dwExpireTime = dwExpireTime;
			dispatchEvent(event_);
		}

		//接收处理：道具(装备)属性变化通知
		private function _doRecv_ItemChangeNotify(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)所有者ID(可能是主将，副将，宠物...)
			var rStoreItem:SItem = SItem.superFromByteArray(bytes); //装备更新后信息
			var event_:REvt_ItemChangeNotify = new REvt_ItemChangeNotify(REvt_ItemChangeNotify.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.qwOwnerID = qwOwnerID;
			event_.rStoreItem = rStoreItem;
			dispatchEvent(event_);
		}

		//接收处理：清除道具使用冷却CD
		private function _doRecv_ClearAllItemCDNtf(bytes:ByteArray):void
		{
			var event_:REvt_ClearAllItemCDNtf = new REvt_ClearAllItemCDNtf(REvt_ClearAllItemCDNtf.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：角色道具冷却通知
		private function _doRecv_SlotItemCDNotify(bytes:ByteArray):void
		{
			var vecItemCold:Vector.<SItemColdTime> = SItemColdTime.vectorFromByteArray(bytes); //道具使用冷却时间
			var vecGroupCold:Vector.<SItemColdTime> = SItemColdTime.vectorFromByteArray(bytes); //道具公共冷却时间
			var event_:REvt_SlotItemCDNotify = new REvt_SlotItemCDNotify(REvt_SlotItemCDNotify.DATA_RECEIVE);
			event_.vecItemCold = vecItemCold;
			event_.vecGroupCold = vecGroupCold;
			dispatchEvent(event_);
		}

		//接收处理：角色获得道具提示
		private function _doRecv_AddItemSystemMsg(bytes:ByteArray):void
		{
			var vecAddItemMsg:Vector.<SAddItemMsg> = SAddItemMsg.vectorFromByteArray(bytes); //道具获得提示
			var event_:REvt_AddItemSystemMsg = new REvt_AddItemSystemMsg(REvt_AddItemSystemMsg.DATA_RECEIVE);
			event_.vecAddItemMsg = vecAddItemMsg;
			dispatchEvent(event_);
		}

		//接收处理：错误提示
		private function _doRecv_ItemErrNfg(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)提示
			var event_:REvt_ItemErrNfg = new REvt_ItemErrNfg(REvt_ItemErrNfg.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		//接收处理：再一次增加记录道具通知
		private function _doRecv_AgainAddloggedItemNotify(bytes:ByteArray):void
		{
			var rVecLoggedItem:Vector.<SLoggedItem> = SLoggedItem.vectorFromByteArray(bytes); //道具列表
			var event_:REvt_AgainAddloggedItemNotify = new REvt_AgainAddloggedItemNotify(REvt_AgainAddloggedItemNotify.DATA_RECEIVE);
			event_.rVecLoggedItem = rVecLoggedItem;
			dispatchEvent(event_);
		}

		//接收处理：增加记录道具通知
		private function _doRecv_AddLoggedItemNotify(bytes:ByteArray):void
		{
			var rVecLoggedItem:Vector.<SLoggedItem> = SLoggedItem.vectorFromByteArray(bytes); //道具列表
			var event_:REvt_AddLoggedItemNotify = new REvt_AddLoggedItemNotify(REvt_AddLoggedItemNotify.DATA_RECEIVE);
			event_.rVecLoggedItem = rVecLoggedItem;
			dispatchEvent(event_);
		}

		//接收处理：更新记录的堆叠道具通知
		private function _doRecv_UpdateLoggedStackItemNotify(bytes:ByteArray):void
		{
			var wItemID:uint = bytes.readUnsignedShort(); //(无符号16位整数)ID
			var byQuality:uint = bytes.readUnsignedByte(); //(无符号8位整数)品质
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)数目
			var event_:REvt_UpdateLoggedStackItemNotify = new REvt_UpdateLoggedStackItemNotify(REvt_UpdateLoggedStackItemNotify.DATA_RECEIVE);
			event_.wItemID = wItemID;
			event_.byQuality = byQuality;
			event_.dwCount = dwCount;
			dispatchEvent(event_);
		}

		//接收处理：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
		private function _doRecv_CittaAddNtf(bytes:ByteArray):void
		{
			var eStoreType:uint = bytes.readUnsignedByte(); //(枚举类型：EStoreType)存储类型
			var vecStoreItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes); //包裹或仓库中道具的列表
			var bNew:Boolean = bytes.readBoolean(); //是否新获得道具
			var event_:REvt_CittaAddNtf = new REvt_CittaAddNtf(REvt_CittaAddNtf.DATA_RECEIVE);
			event_.eStoreType = eStoreType;
			event_.vecStoreItem = vecStoreItem;
			event_.bNew = bNew;
			dispatchEvent(event_);
		}

		//接收处理：更新记录的堆叠道具通知
		private function _doRecv_NoticeUseItemNotify(bytes:ByteArray):void
		{
			var wItemID:uint = bytes.readUnsignedShort(); //(无符号16位整数)ID
			var dwNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)使用物品数量
			var vecRes:Vector.<SResource> = SResource.vectorFromByteArray(bytes); //资源
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //物品
			var event_:REvt_NoticeUseItemNotify = new REvt_NoticeUseItemNotify(REvt_NoticeUseItemNotify.DATA_RECEIVE);
			event_.wItemID = wItemID;
			event_.dwNum = dwNum;
			event_.vecRes = vecRes;
			event_.vecItem = vecItem;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求包裹信息(整个包裹)
		private function _doReturn_GetStore(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetStore = new SRetParam_GetStore();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var stStoreStream:SStoreStream = SStoreStream.fromByteArray(bytes); //背包信息
			var dwNextUnlockTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)下一个解锁背包空间的时间 0-表示可解锁 0xFFFFFFFF-表示没有可解锁的了 其他为秒
			retParam_.stStoreStream = stStoreStream;
			retParam_.dwNextUnlockTime = dwNextUnlockTime;
			var origParam_:SOrigParam_GetStore = _sessionMgr.getData(sessionID_) as SOrigParam_GetStore;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_GetStore = new TEvt_GetStore(TEvt_GetStore.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求包裹信息(整个包裹)
		private function _onTimeOut_GetStore(sessionID:uint):void
		{
			var retParam:SRetParam_GetStore = new SRetParam_GetStore();
			var origParam:SOrigParam_GetStore = _sessionMgr.getData(sessionID) as SOrigParam_GetStore;
			var event_:TEvt_GetStore = new TEvt_GetStore(TEvt_GetStore.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求使用包裹中的道具
		private function _doReturn_UseItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UseItem = new SRetParam_UseItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)使用道具结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UseItem = _sessionMgr.getData(sessionID_) as SOrigParam_UseItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_UseItem = new TEvt_UseItem(TEvt_UseItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求使用包裹中的道具
		private function _onTimeOut_UseItem(sessionID:uint):void
		{
			var retParam:SRetParam_UseItem = new SRetParam_UseItem();
			var origParam:SOrigParam_UseItem = _sessionMgr.getData(sessionID) as SOrigParam_UseItem;
			var event_:TEvt_UseItem = new TEvt_UseItem(TEvt_UseItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：扩充包裹或仓库
		private function _doReturn_ExpandStore(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ExpandStore = new SRetParam_ExpandStore();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)扩充结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ExpandStore = _sessionMgr.getData(sessionID_) as SOrigParam_ExpandStore;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ExpandStore = new TEvt_ExpandStore(TEvt_ExpandStore.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：扩充包裹或仓库
		private function _onTimeOut_ExpandStore(sessionID:uint):void
		{
			var retParam:SRetParam_ExpandStore = new SRetParam_ExpandStore();
			var event_:TEvt_ExpandStore = new TEvt_ExpandStore(TEvt_ExpandStore.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：包裹或仓库中道具换位置
		private function _doReturn_RelocateStoreItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_RelocateStoreItem = new SRetParam_RelocateStoreItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)换位置的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_RelocateStoreItem = _sessionMgr.getData(sessionID_) as SOrigParam_RelocateStoreItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_RelocateStoreItem = new TEvt_RelocateStoreItem(TEvt_RelocateStoreItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：包裹或仓库中道具换位置
		private function _onTimeOut_RelocateStoreItem(sessionID:uint):void
		{
			var retParam:SRetParam_RelocateStoreItem = new SRetParam_RelocateStoreItem();
			var origParam:SOrigParam_RelocateStoreItem = _sessionMgr.getData(sessionID) as SOrigParam_RelocateStoreItem;
			var event_:TEvt_RelocateStoreItem = new TEvt_RelocateStoreItem(TEvt_RelocateStoreItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：整理包裹或仓库
		private function _doReturn_TidyupStore(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TidyupStore = new SRetParam_TidyupStore();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)整理的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TidyupStore = _sessionMgr.getData(sessionID_) as SOrigParam_TidyupStore;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_TidyupStore = new TEvt_TidyupStore(TEvt_TidyupStore.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：整理包裹或仓库
		private function _onTimeOut_TidyupStore(sessionID:uint):void
		{
			var retParam:SRetParam_TidyupStore = new SRetParam_TidyupStore();
			var origParam:SOrigParam_TidyupStore = _sessionMgr.getData(sessionID) as SOrigParam_TidyupStore;
			var event_:TEvt_TidyupStore = new TEvt_TidyupStore(TEvt_TidyupStore.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：拆分包裹或仓库中的堆叠类道具
		private function _doReturn_SplitStackItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SplitStackItem = new SRetParam_SplitStackItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)拆分的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SplitStackItem = _sessionMgr.getData(sessionID_) as SOrigParam_SplitStackItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_SplitStackItem = new TEvt_SplitStackItem(TEvt_SplitStackItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：拆分包裹或仓库中的堆叠类道具
		private function _onTimeOut_SplitStackItem(sessionID:uint):void
		{
			var retParam:SRetParam_SplitStackItem = new SRetParam_SplitStackItem();
			var origParam:SOrigParam_SplitStackItem = _sessionMgr.getData(sessionID) as SOrigParam_SplitStackItem;
			var event_:TEvt_SplitStackItem = new TEvt_SplitStackItem(TEvt_SplitStackItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：合并包裹或仓库中的堆叠类道具
		private function _doReturn_MergeStackItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MergeStackItem = new SRetParam_MergeStackItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)合并的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MergeStackItem = _sessionMgr.getData(sessionID_) as SOrigParam_MergeStackItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_MergeStackItem = new TEvt_MergeStackItem(TEvt_MergeStackItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：合并包裹或仓库中的堆叠类道具
		private function _onTimeOut_MergeStackItem(sessionID:uint):void
		{
			var retParam:SRetParam_MergeStackItem = new SRetParam_MergeStackItem();
			var origParam:SOrigParam_MergeStackItem = _sessionMgr.getData(sessionID) as SOrigParam_MergeStackItem;
			var event_:TEvt_MergeStackItem = new TEvt_MergeStackItem(TEvt_MergeStackItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：销毁包裹或仓库中的道具
		private function _doReturn_DestroyStoreItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DestroyStoreItem = new SRetParam_DestroyStoreItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)销毁的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_DestroyStoreItem = _sessionMgr.getData(sessionID_) as SOrigParam_DestroyStoreItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_DestroyStoreItem = new TEvt_DestroyStoreItem(TEvt_DestroyStoreItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：销毁包裹或仓库中的道具
		private function _onTimeOut_DestroyStoreItem(sessionID:uint):void
		{
			var retParam:SRetParam_DestroyStoreItem = new SRetParam_DestroyStoreItem();
			var origParam:SOrigParam_DestroyStoreItem = _sessionMgr.getData(sessionID) as SOrigParam_DestroyStoreItem;
			var event_:TEvt_DestroyStoreItem = new TEvt_DestroyStoreItem(TEvt_DestroyStoreItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：在包裹和仓库之间移动道具
		private function _doReturn_TransferItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TransferItem = new SRetParam_TransferItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)移动的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TransferItem = _sessionMgr.getData(sessionID_) as SOrigParam_TransferItem;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TransferItem = new TEvt_TransferItem(TEvt_TransferItem.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：在包裹和仓库之间移动道具
		private function _onTimeOut_TransferItem(sessionID:uint):void
		{
			var retParam:SRetParam_TransferItem = new SRetParam_TransferItem();
			var event_:TEvt_TransferItem = new TEvt_TransferItem(TEvt_TransferItem.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求出售包裹中的道具-出售给系统
		private function _doReturn_SellItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SellItem = new SRetParam_SellItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)使用道具结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SellItem = _sessionMgr.getData(sessionID_) as SOrigParam_SellItem;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_SellItem = new TEvt_SellItem(TEvt_SellItem.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求出售包裹中的道具-出售给系统
		private function _onTimeOut_SellItem(sessionID:uint):void
		{
			var retParam:SRetParam_SellItem = new SRetParam_SellItem();
			var origParam:SOrigParam_SellItem = _sessionMgr.getData(sessionID) as SOrigParam_SellItem;
			var event_:TEvt_SellItem = new TEvt_SellItem(TEvt_SellItem.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求按个数出售包裹中的道具-出售给系统
		private function _doReturn_SellItemWithCount(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SellItemWithCount = new SRetParam_SellItemWithCount();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)卖出道具结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SellItemWithCount = _sessionMgr.getData(sessionID_) as SOrigParam_SellItemWithCount;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_SellItemWithCount = new TEvt_SellItemWithCount(TEvt_SellItemWithCount.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求按个数出售包裹中的道具-出售给系统
		private function _onTimeOut_SellItemWithCount(sessionID:uint):void
		{
			var retParam:SRetParam_SellItemWithCount = new SRetParam_SellItemWithCount();
			var origParam:SOrigParam_SellItemWithCount = _sessionMgr.getData(sessionID) as SOrigParam_SellItemWithCount;
			var event_:TEvt_SellItemWithCount = new TEvt_SellItemWithCount(TEvt_SellItemWithCount.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：解锁背包格子
		private function _doReturn_UnlockPack(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UnlockPack = new SRetParam_UnlockPack();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UnlockPack = _sessionMgr.getData(sessionID_) as SOrigParam_UnlockPack;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UnlockPack = new TEvt_UnlockPack(TEvt_UnlockPack.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：解锁背包格子
		private function _onTimeOut_UnlockPack(sessionID:uint):void
		{
			var retParam:SRetParam_UnlockPack = new SRetParam_UnlockPack();
			var event_:TEvt_UnlockPack = new TEvt_UnlockPack(TEvt_UnlockPack.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：记录传送点
		private function _doReturn_RecordTransfPoint(bytes:ByteArray):void
		{
			var retParam_:SRetParam_RecordTransfPoint = new SRetParam_RecordTransfPoint();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_RecordTransfPoint = _sessionMgr.getData(sessionID_) as SOrigParam_RecordTransfPoint;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_RecordTransfPoint = new TEvt_RecordTransfPoint(TEvt_RecordTransfPoint.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：记录传送点
		private function _onTimeOut_RecordTransfPoint(sessionID:uint):void
		{
			var retParam:SRetParam_RecordTransfPoint = new SRetParam_RecordTransfPoint();
			var event_:TEvt_RecordTransfPoint = new TEvt_RecordTransfPoint(TEvt_RecordTransfPoint.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：传送
		private function _doReturn_TransfMapPoint(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TransfMapPoint = new SRetParam_TransfMapPoint();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EItemResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TransfMapPoint = _sessionMgr.getData(sessionID_) as SOrigParam_TransfMapPoint;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TransfMapPoint = new TEvt_TransfMapPoint(TEvt_TransfMapPoint.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：传送
		private function _onTimeOut_TransfMapPoint(sessionID:uint):void
		{
			var retParam:SRetParam_TransfMapPoint = new SRetParam_TransfMapPoint();
			var event_:TEvt_TransfMapPoint = new TEvt_TransfMapPoint(TEvt_TransfMapPoint.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求装备心法
		private function _doReturn_WearCitta(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WearCitta = new SRetParam_WearCitta();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECittaResult)穿上装备的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_WearCitta = _sessionMgr.getData(sessionID_) as SOrigParam_WearCitta;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_WearCitta = new TEvt_WearCitta(TEvt_WearCitta.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求装备心法
		private function _onTimeOut_WearCitta(sessionID:uint):void
		{
			var retParam:SRetParam_WearCitta = new SRetParam_WearCitta();
			var origParam:SOrigParam_WearCitta = _sessionMgr.getData(sessionID) as SOrigParam_WearCitta;
			var event_:TEvt_WearCitta = new TEvt_WearCitta(TEvt_WearCitta.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求卸下心法
		private function _doReturn_TakeoffCitta(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeoffCitta = new SRetParam_TakeoffCitta();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECittaResult)脱下装备的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TakeoffCitta = _sessionMgr.getData(sessionID_) as SOrigParam_TakeoffCitta;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_TakeoffCitta = new TEvt_TakeoffCitta(TEvt_TakeoffCitta.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求卸下心法
		private function _onTimeOut_TakeoffCitta(sessionID:uint):void
		{
			var retParam:SRetParam_TakeoffCitta = new SRetParam_TakeoffCitta();
			var origParam:SOrigParam_TakeoffCitta = _sessionMgr.getData(sessionID) as SOrigParam_TakeoffCitta;
			var event_:TEvt_TakeoffCitta = new TEvt_TakeoffCitta(TEvt_TakeoffCitta.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求合成心法
		private function _doReturn_MergeCitta(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MergeCitta = new SRetParam_MergeCitta();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECittaResult)结果
			var vecItemCitta:Vector.<SItem> = SItem.superVectorFromByteArray(bytes); //新增的道具
			retParam_.eResult = eResult;
			retParam_.vecItemCitta = vecItemCitta;
			var origParam_:SOrigParam_MergeCitta = _sessionMgr.getData(sessionID_) as SOrigParam_MergeCitta;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MergeCitta = new TEvt_MergeCitta(TEvt_MergeCitta.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求合成心法
		private function _onTimeOut_MergeCitta(sessionID:uint):void
		{
			var retParam:SRetParam_MergeCitta = new SRetParam_MergeCitta();
			var event_:TEvt_MergeCitta = new TEvt_MergeCitta(TEvt_MergeCitta.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求分解心法
		private function _doReturn_BreakCitta(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BreakCitta = new SRetParam_BreakCitta();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ECittaResult)结果
			var vecItemInfo:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //分解产生的道具
			retParam_.eResult = eResult;
			retParam_.vecItemInfo = vecItemInfo;
			var origParam_:SOrigParam_BreakCitta = _sessionMgr.getData(sessionID_) as SOrigParam_BreakCitta;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BreakCitta = new TEvt_BreakCitta(TEvt_BreakCitta.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求分解心法
		private function _onTimeOut_BreakCitta(sessionID:uint):void
		{
			var retParam:SRetParam_BreakCitta = new SRetParam_BreakCitta();
			var event_:TEvt_BreakCitta = new TEvt_BreakCitta(TEvt_BreakCitta.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：激活法宝
		private function _doReturn_ActiveTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ActiveTrump = new SRetParam_ActiveTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETrumpResult)结果
			var vecTrump:Vector.<STrump> = STrump.vectorFromByteArray(bytes); //新法宝
			retParam_.eResult = eResult;
			retParam_.vecTrump = vecTrump;
			var origParam_:SOrigParam_ActiveTrump = _sessionMgr.getData(sessionID_) as SOrigParam_ActiveTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ActiveTrump = new TEvt_ActiveTrump(TEvt_ActiveTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活法宝
		private function _onTimeOut_ActiveTrump(sessionID:uint):void
		{
			var retParam:SRetParam_ActiveTrump = new SRetParam_ActiveTrump();
			var event_:TEvt_ActiveTrump = new TEvt_ActiveTrump(TEvt_ActiveTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：出战法宝
		private function _doReturn_EquipTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EquipTrump = new SRetParam_EquipTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETrumpResult)结果
			var vecTrump:Vector.<STrump> = STrump.vectorFromByteArray(bytes); //新法宝
			retParam_.eResult = eResult;
			retParam_.vecTrump = vecTrump;
			var origParam_:SOrigParam_EquipTrump = _sessionMgr.getData(sessionID_) as SOrigParam_EquipTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EquipTrump = new TEvt_EquipTrump(TEvt_EquipTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：出战法宝
		private function _onTimeOut_EquipTrump(sessionID:uint):void
		{
			var retParam:SRetParam_EquipTrump = new SRetParam_EquipTrump();
			var event_:TEvt_EquipTrump = new TEvt_EquipTrump(TEvt_EquipTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：卸下法宝
		private function _doReturn_UnEquipTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UnEquipTrump = new SRetParam_UnEquipTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETrumpResult)结果
			var vecTrump:Vector.<STrump> = STrump.vectorFromByteArray(bytes); //新法宝
			retParam_.eResult = eResult;
			retParam_.vecTrump = vecTrump;
			var origParam_:SOrigParam_UnEquipTrump = _sessionMgr.getData(sessionID_) as SOrigParam_UnEquipTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UnEquipTrump = new TEvt_UnEquipTrump(TEvt_UnEquipTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：卸下法宝
		private function _onTimeOut_UnEquipTrump(sessionID:uint):void
		{
			var retParam:SRetParam_UnEquipTrump = new SRetParam_UnEquipTrump();
			var event_:TEvt_UnEquipTrump = new TEvt_UnEquipTrump(TEvt_UnEquipTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：祭炼法宝
		private function _doReturn_UpgradeTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeTrump = new SRetParam_UpgradeTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETrumpResult)结果
			var vecTrump:Vector.<STrump> = STrump.vectorFromByteArray(bytes); //新法宝
			retParam_.eResult = eResult;
			retParam_.vecTrump = vecTrump;
			var origParam_:SOrigParam_UpgradeTrump = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeTrump = new TEvt_UpgradeTrump(TEvt_UpgradeTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：祭炼法宝
		private function _onTimeOut_UpgradeTrump(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeTrump = new SRetParam_UpgradeTrump();
			var event_:TEvt_UpgradeTrump = new TEvt_UpgradeTrump(TEvt_UpgradeTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：提升法宝品级
		private function _doReturn_EvolveTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EvolveTrump = new SRetParam_EvolveTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETrumpResult)结果
			var vecTrump:Vector.<STrump> = STrump.vectorFromByteArray(bytes); //新法宝
			retParam_.eResult = eResult;
			retParam_.vecTrump = vecTrump;
			var origParam_:SOrigParam_EvolveTrump = _sessionMgr.getData(sessionID_) as SOrigParam_EvolveTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EvolveTrump = new TEvt_EvolveTrump(TEvt_EvolveTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：提升法宝品级
		private function _onTimeOut_EvolveTrump(sessionID:uint):void
		{
			var retParam:SRetParam_EvolveTrump = new SRetParam_EvolveTrump();
			var event_:TEvt_EvolveTrump = new TEvt_EvolveTrump(TEvt_EvolveTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：激活时装
		private function _doReturn_FashionActive(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FashionActive = new SRetParam_FashionActive();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFashionResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FashionActive = _sessionMgr.getData(sessionID_) as SOrigParam_FashionActive;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FashionActive = new TEvt_FashionActive(TEvt_FashionActive.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活时装
		private function _onTimeOut_FashionActive(sessionID:uint):void
		{
			var retParam:SRetParam_FashionActive = new SRetParam_FashionActive();
			var event_:TEvt_FashionActive = new TEvt_FashionActive(TEvt_FashionActive.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：隐藏所选时装
		private function _doReturn_FashionHide(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FashionHide = new SRetParam_FashionHide();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFashionResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FashionHide = _sessionMgr.getData(sessionID_) as SOrigParam_FashionHide;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FashionHide = new TEvt_FashionHide(TEvt_FashionHide.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：隐藏所选时装
		private function _onTimeOut_FashionHide(sessionID:uint):void
		{
			var retParam:SRetParam_FashionHide = new SRetParam_FashionHide();
			var event_:TEvt_FashionHide = new TEvt_FashionHide(TEvt_FashionHide.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：选择时装
		private function _doReturn_FashionChange(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FashionChange = new SRetParam_FashionChange();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFashionResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FashionChange = _sessionMgr.getData(sessionID_) as SOrigParam_FashionChange;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FashionChange = new TEvt_FashionChange(TEvt_FashionChange.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：选择时装
		private function _onTimeOut_FashionChange(sessionID:uint):void
		{
			var retParam:SRetParam_FashionChange = new SRetParam_FashionChange();
			var event_:TEvt_FashionChange = new TEvt_FashionChange(TEvt_FashionChange.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：时装炼化
		private function _doReturn_FashionUpgrade(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FashionUpgrade = new SRetParam_FashionUpgrade();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFashionResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FashionUpgrade = _sessionMgr.getData(sessionID_) as SOrigParam_FashionUpgrade;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FashionUpgrade = new TEvt_FashionUpgrade(TEvt_FashionUpgrade.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：时装炼化
		private function _onTimeOut_FashionUpgrade(sessionID:uint):void
		{
			var retParam:SRetParam_FashionUpgrade = new SRetParam_FashionUpgrade();
			var event_:TEvt_FashionUpgrade = new TEvt_FashionUpgrade(TEvt_FashionUpgrade.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：穿戴宝石
		private function _doReturn_WareGemStone(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WareGemStone = new SRetParam_WareGemStone();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGemstoneResult)结果
			var qwFighterID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将ID
			var byPos:uint = bytes.readUnsignedByte(); //(无符号8位整数)穿戴位置
			var Item:SGemstone = SGemstone.fromByteArray(bytes); //宝石
			retParam_.eResult = eResult;
			retParam_.qwFighterID = qwFighterID;
			retParam_.byPos = byPos;
			retParam_.Item = Item;
			var origParam_:SOrigParam_WareGemStone = _sessionMgr.getData(sessionID_) as SOrigParam_WareGemStone;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_WareGemStone = new TEvt_WareGemStone(TEvt_WareGemStone.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：穿戴宝石
		private function _onTimeOut_WareGemStone(sessionID:uint):void
		{
			var retParam:SRetParam_WareGemStone = new SRetParam_WareGemStone();
			var event_:TEvt_WareGemStone = new TEvt_WareGemStone(TEvt_WareGemStone.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取下宝石
		private function _doReturn_TakeOffGemStone(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeOffGemStone = new SRetParam_TakeOffGemStone();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGemstoneResult)结果
			var qwFighterID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)将ID
			var byPos:uint = bytes.readUnsignedByte(); //(无符号8位整数)穿戴位置
			retParam_.eResult = eResult;
			retParam_.qwFighterID = qwFighterID;
			retParam_.byPos = byPos;
			var origParam_:SOrigParam_TakeOffGemStone = _sessionMgr.getData(sessionID_) as SOrigParam_TakeOffGemStone;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeOffGemStone = new TEvt_TakeOffGemStone(TEvt_TakeOffGemStone.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取下宝石
		private function _onTimeOut_TakeOffGemStone(sessionID:uint):void
		{
			var retParam:SRetParam_TakeOffGemStone = new SRetParam_TakeOffGemStone();
			var event_:TEvt_TakeOffGemStone = new TEvt_TakeOffGemStone(TEvt_TakeOffGemStone.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：合成宝石
		private function _doReturn_ComposeGemStone(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ComposeGemStone = new SRetParam_ComposeGemStone();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGemstoneResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ComposeGemStone = _sessionMgr.getData(sessionID_) as SOrigParam_ComposeGemStone;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ComposeGemStone = new TEvt_ComposeGemStone(TEvt_ComposeGemStone.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：合成宝石
		private function _onTimeOut_ComposeGemStone(sessionID:uint):void
		{
			var retParam:SRetParam_ComposeGemStone = new SRetParam_ComposeGemStone();
			var event_:TEvt_ComposeGemStone = new TEvt_ComposeGemStone(TEvt_ComposeGemStone.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：一键合成宝石
		private function _doReturn_ComposeGemStoneOneKey(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ComposeGemStoneOneKey = new SRetParam_ComposeGemStoneOneKey();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGemstoneResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ComposeGemStoneOneKey = _sessionMgr.getData(sessionID_) as SOrigParam_ComposeGemStoneOneKey;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ComposeGemStoneOneKey = new TEvt_ComposeGemStoneOneKey(TEvt_ComposeGemStoneOneKey.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：一键合成宝石
		private function _onTimeOut_ComposeGemStoneOneKey(sessionID:uint):void
		{
			var retParam:SRetParam_ComposeGemStoneOneKey = new SRetParam_ComposeGemStoneOneKey();
			var event_:TEvt_ComposeGemStoneOneKey = new TEvt_ComposeGemStoneOneKey(TEvt_ComposeGemStoneOneKey.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ItemProt;

		public static function get instance():ItemProt
		{
			if(_instance == null)
				_instance = new ItemProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ItemProt()
		{
			_protID = 18;
			_recvFuncList = [
				_doRecv_StoreNotify, //FuncID: 1
				_doRecv_PackNextUnlockTime, //FuncID: 2
				_doRecv_StoreSizeChangeNotify, //FuncID: 3
				_doRecv_StoreItemAddNtf, //FuncID: 4
				_doRecv_StoreItemDelNtf, //FuncID: 5
				_doRecv_StackItemUpdate, //FuncID: 6
				_doRecv_OpenDepot, //FuncID: 7
				_doRecv_ItemBindChangeNtf, //FuncID: 8
				_doRecv_ItemCDNtf, //FuncID: 9
				_doRecv_ItemExpireTimeNtf, //FuncID: 10
				_doRecv_ItemChangeNotify, //FuncID: 11
				_doRecv_ClearAllItemCDNtf, //FuncID: 12
				_doRecv_SlotItemCDNotify, //FuncID: 13
				_doRecv_AddItemSystemMsg, //FuncID: 14
				_doRecv_ItemErrNfg, //FuncID: 15
				_doRecv_AgainAddloggedItemNotify, //FuncID: 16
				_doRecv_AddLoggedItemNotify, //FuncID: 17
				_doRecv_UpdateLoggedStackItemNotify, //FuncID: 18
				_doRecv_CittaAddNtf, //FuncID: 19
				_doRecv_NoticeUseItemNotify //FuncID: 20
			];

			_retFuncList = [
				_doReturn_GetStore, //FuncID: 1
				_doReturn_UseItem, //FuncID: 2
				_doReturn_ExpandStore, //FuncID: 3
				_doReturn_RelocateStoreItem, //FuncID: 4
				_doReturn_TidyupStore, //FuncID: 5
				_doReturn_SplitStackItem, //FuncID: 6
				_doReturn_MergeStackItem, //FuncID: 7
				_doReturn_DestroyStoreItem, //FuncID: 8
				_doReturn_TransferItem, //FuncID: 9
				_doReturn_SellItem, //FuncID: 10
				_doReturn_SellItemWithCount, //FuncID: 11
				_doReturn_UnlockPack, //FuncID: 12
				_doReturn_RecordTransfPoint, //FuncID: 13
				_doReturn_TransfMapPoint, //FuncID: 14
				_doReturn_WearCitta, //FuncID: 15
				_doReturn_TakeoffCitta, //FuncID: 16
				_doReturn_MergeCitta, //FuncID: 17
				_doReturn_BreakCitta, //FuncID: 18
				_doReturn_ActiveTrump, //FuncID: 19
				_doReturn_EquipTrump, //FuncID: 20
				_doReturn_UnEquipTrump, //FuncID: 21
				_doReturn_UpgradeTrump, //FuncID: 22
				_doReturn_EvolveTrump, //FuncID: 23
				_doReturn_FashionActive, //FuncID: 24
				_doReturn_FashionHide, //FuncID: 25
				_doReturn_FashionChange, //FuncID: 26
				_doReturn_FashionUpgrade, //FuncID: 27
				_doReturn_WareGemStone, //FuncID: 28
				_doReturn_TakeOffGemStone, //FuncID: 29
				_doReturn_ComposeGemStone, //FuncID: 30
				_doReturn_ComposeGemStoneOneKey //FuncID: 31
			];

			_timeFuncList = [
				_onTimeOut_GetStore, //FuncID: 1
				_onTimeOut_UseItem, //FuncID: 2
				_onTimeOut_ExpandStore, //FuncID: 3
				_onTimeOut_RelocateStoreItem, //FuncID: 4
				_onTimeOut_TidyupStore, //FuncID: 5
				_onTimeOut_SplitStackItem, //FuncID: 6
				_onTimeOut_MergeStackItem, //FuncID: 7
				_onTimeOut_DestroyStoreItem, //FuncID: 8
				_onTimeOut_TransferItem, //FuncID: 9
				_onTimeOut_SellItem, //FuncID: 10
				_onTimeOut_SellItemWithCount, //FuncID: 11
				_onTimeOut_UnlockPack, //FuncID: 12
				_onTimeOut_RecordTransfPoint, //FuncID: 13
				_onTimeOut_TransfMapPoint, //FuncID: 14
				_onTimeOut_WearCitta, //FuncID: 15
				_onTimeOut_TakeoffCitta, //FuncID: 16
				_onTimeOut_MergeCitta, //FuncID: 17
				_onTimeOut_BreakCitta, //FuncID: 18
				_onTimeOut_ActiveTrump, //FuncID: 19
				_onTimeOut_EquipTrump, //FuncID: 20
				_onTimeOut_UnEquipTrump, //FuncID: 21
				_onTimeOut_UpgradeTrump, //FuncID: 22
				_onTimeOut_EvolveTrump, //FuncID: 23
				_onTimeOut_FashionActive, //FuncID: 24
				_onTimeOut_FashionHide, //FuncID: 25
				_onTimeOut_FashionChange, //FuncID: 26
				_onTimeOut_FashionUpgrade, //FuncID: 27
				_onTimeOut_WareGemStone, //FuncID: 28
				_onTimeOut_TakeOffGemStone, //FuncID: 29
				_onTimeOut_ComposeGemStone, //FuncID: 30
				_onTimeOut_ComposeGemStoneOneKey //FuncID: 31
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0 || funcID > _recvFuncList.length
				 || funcID < -_retFuncList.length)
				return false;
			var func:Function;
			if(funcID > 0)
				func = _recvFuncList[funcID - 1];
			else
				func = _retFuncList[-funcID - 1];
			if(func != null)
			{
				func(bytes);
				return true;
			}
			return false;
		}

		public override function onTimeOut(funcID:uint, sessionID:uint):void
		{
			if(funcID == 0 || funcID > _timeFuncList.length)
				return;
			_timeFuncList[funcID - 1](sessionID);
		}
	}
}