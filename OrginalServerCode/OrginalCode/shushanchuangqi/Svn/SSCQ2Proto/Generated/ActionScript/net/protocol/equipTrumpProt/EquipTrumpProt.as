/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    EquipTrumpProt.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SEquipTrump;
	import net.protocol.itemProt.SItem;
	import net.protocol.itemProt.SItemGenInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：道具相关协议
	 */
	public class EquipTrumpProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获得所有装备法宝
		 * @param qwOwnerID (无符号64位整数)散仙唯一ID（0表示获取所有散仙法宝）
		 */
		public function send_GetAllEquipTrump(qwOwnerID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetAllEquipTrump = new SOrigParam_GetAllEquipTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwOwnerID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求穿上装备法宝
		 * @param qwOwnerID (无符号64位整数)散仙唯一ID
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 */
		public function send_Wear(qwOwnerID:BigInteger, qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_Wear = new SOrigParam_Wear();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwOwnerID);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求一键穿上装备法宝
		 * @param qwOwnerID (无符号64位整数)散仙唯一ID
		 */
		public function send_WearOneKey(qwOwnerID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_WearOneKey = new SOrigParam_WearOneKey();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwOwnerID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求脱下装备法宝
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 * @param wIndex (有符号16位整数)-1：右击脱下；其他：包裹的位置
		 */
		public function send_TakeOff(qwInstID:BigInteger, wIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakeOff = new SOrigParam_TakeOff();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：交换法宝
		 * @param qwOwnerID (无符号64位整数)散仙唯一ID
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 * @param wIndex (有符号16位整数)-1：右击脱下；其他：包裹的位置
		 */
		public function send_Swap(qwOwnerID:BigInteger, qwInstID:BigInteger, wIndex:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_Swap = new SOrigParam_Swap();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwOwnerID);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeShort(wIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求合成装备法宝
		 * @param wItemID (无符号16位整数)制作装备法宝模版ID
		 * @param wCount (无符号16位整数)数量
		 */
		public function send_MergeEquipTrump(wItemID:uint, wCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_MergeEquipTrump = new SOrigParam_MergeEquipTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wItemID);
			bytes_.writeShort(wCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求分解装备法宝
		 * @param vecInstID (无符号64位整数)物品唯一ID
		 */
		public function send_BreakEquipTrump(vecInstID:Vector.<BigInteger>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_BreakEquipTrump = new SOrigParam_BreakEquipTrump();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeVecUInt64(bytes_, vecInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：装备法宝强化
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 * @param eType (枚举类型：ETIntensifyType)强化类型
		 */
		public function send_Intensify(qwInstID:BigInteger, eType:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_Intensify = new SOrigParam_Intensify();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：装备法宝一键强化
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 * @param eType (枚举类型：ETIntensifyType)强化类型
		 */
		public function send_IntensifyOneKey(qwInstID:BigInteger, eType:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_IntensifyOneKey = new SOrigParam_IntensifyOneKey();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：装备法宝洗炼
		 * @param qwInstID (无符号64位整数)装备法宝唯一ID
		 * @param dwLock (无符号32位整数)锁定属性（按位锁定 0x110 锁定2，3位）
		 */
		public function send_ShuffleResult(qwInstID:BigInteger, dwLock:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_ShuffleResult = new SOrigParam_ShuffleResult();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeUnsignedInt(dwLock);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：当前玩家角色的装备法宝通知
		private function _doRecv_EquipTrumpNotify(bytes:ByteArray):void
		{
			var qwOwnerID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)散仙唯一ID
			var eSlotType:int = bytes.readByte(); //(枚举类型：EEquipTrumpSlotType)装备法宝位类型
			var vecEquipTrump:Vector.<SEquipTrump> = SEquipTrump.vectorFromByteArray(bytes); //当前装备法宝的列表
			var event_:REvt_EquipTrumpNotify = new REvt_EquipTrumpNotify(REvt_EquipTrumpNotify.DATA_RECEIVE);
			event_.qwOwnerID = qwOwnerID;
			event_.eSlotType = eSlotType;
			event_.vecEquipTrump = vecEquipTrump;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获得所有装备法宝
		private function _doReturn_GetAllEquipTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllEquipTrump = new SRetParam_GetAllEquipTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecEquipTrump:Vector.<SEquipTrump> = SEquipTrump.vectorFromByteArray(bytes); //当前装备法宝的列表
			retParam_.vecEquipTrump = vecEquipTrump;
			var origParam_:SOrigParam_GetAllEquipTrump = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllEquipTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllEquipTrump = new TEvt_GetAllEquipTrump(TEvt_GetAllEquipTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得所有装备法宝
		private function _onTimeOut_GetAllEquipTrump(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllEquipTrump = new SRetParam_GetAllEquipTrump();
			var event_:TEvt_GetAllEquipTrump = new TEvt_GetAllEquipTrump(TEvt_GetAllEquipTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求穿上装备法宝
		private function _doReturn_Wear(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Wear = new SRetParam_Wear();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpResult)穿上装备法宝的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Wear = _sessionMgr.getData(sessionID_) as SOrigParam_Wear;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Wear = new TEvt_Wear(TEvt_Wear.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求穿上装备法宝
		private function _onTimeOut_Wear(sessionID:uint):void
		{
			var retParam:SRetParam_Wear = new SRetParam_Wear();
			var event_:TEvt_Wear = new TEvt_Wear(TEvt_Wear.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求一键穿上装备法宝
		private function _doReturn_WearOneKey(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WearOneKey = new SRetParam_WearOneKey();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpResult)穿上装备法宝的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_WearOneKey = _sessionMgr.getData(sessionID_) as SOrigParam_WearOneKey;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_WearOneKey = new TEvt_WearOneKey(TEvt_WearOneKey.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求一键穿上装备法宝
		private function _onTimeOut_WearOneKey(sessionID:uint):void
		{
			var retParam:SRetParam_WearOneKey = new SRetParam_WearOneKey();
			var event_:TEvt_WearOneKey = new TEvt_WearOneKey(TEvt_WearOneKey.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求脱下装备法宝
		private function _doReturn_TakeOff(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeOff = new SRetParam_TakeOff();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpResult)脱下装备法宝的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_TakeOff = _sessionMgr.getData(sessionID_) as SOrigParam_TakeOff;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeOff = new TEvt_TakeOff(TEvt_TakeOff.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求脱下装备法宝
		private function _onTimeOut_TakeOff(sessionID:uint):void
		{
			var retParam:SRetParam_TakeOff = new SRetParam_TakeOff();
			var event_:TEvt_TakeOff = new TEvt_TakeOff(TEvt_TakeOff.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：交换法宝
		private function _doReturn_Swap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Swap = new SRetParam_Swap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpResult)换位置的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Swap = _sessionMgr.getData(sessionID_) as SOrigParam_Swap;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Swap = new TEvt_Swap(TEvt_Swap.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：交换法宝
		private function _onTimeOut_Swap(sessionID:uint):void
		{
			var retParam:SRetParam_Swap = new SRetParam_Swap();
			var event_:TEvt_Swap = new TEvt_Swap(TEvt_Swap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求合成装备法宝
		private function _doReturn_MergeEquipTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MergeEquipTrump = new SRetParam_MergeEquipTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpMergeResult)结果
			var vecItem:Vector.<SItem> = SItem.superVectorFromByteArray(bytes); //新增的道具
			retParam_.eResult = eResult;
			retParam_.vecItem = vecItem;
			var origParam_:SOrigParam_MergeEquipTrump = _sessionMgr.getData(sessionID_) as SOrigParam_MergeEquipTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MergeEquipTrump = new TEvt_MergeEquipTrump(TEvt_MergeEquipTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求合成装备法宝
		private function _onTimeOut_MergeEquipTrump(sessionID:uint):void
		{
			var retParam:SRetParam_MergeEquipTrump = new SRetParam_MergeEquipTrump();
			var event_:TEvt_MergeEquipTrump = new TEvt_MergeEquipTrump(TEvt_MergeEquipTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求分解装备法宝
		private function _doReturn_BreakEquipTrump(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BreakEquipTrump = new SRetParam_BreakEquipTrump();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpBreakResult)结果
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //分解产生的道具
			retParam_.eResult = eResult;
			retParam_.vecItem = vecItem;
			var origParam_:SOrigParam_BreakEquipTrump = _sessionMgr.getData(sessionID_) as SOrigParam_BreakEquipTrump;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BreakEquipTrump = new TEvt_BreakEquipTrump(TEvt_BreakEquipTrump.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求分解装备法宝
		private function _onTimeOut_BreakEquipTrump(sessionID:uint):void
		{
			var retParam:SRetParam_BreakEquipTrump = new SRetParam_BreakEquipTrump();
			var event_:TEvt_BreakEquipTrump = new TEvt_BreakEquipTrump(TEvt_BreakEquipTrump.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：装备法宝强化
		private function _doReturn_Intensify(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Intensify = new SRetParam_Intensify();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bSucess:Boolean = bytes.readBoolean(); //成功/失败
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpIntensifyResult)结果
			retParam_.bSucess = bSucess;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Intensify = _sessionMgr.getData(sessionID_) as SOrigParam_Intensify;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Intensify = new TEvt_Intensify(TEvt_Intensify.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：装备法宝强化
		private function _onTimeOut_Intensify(sessionID:uint):void
		{
			var retParam:SRetParam_Intensify = new SRetParam_Intensify();
			var event_:TEvt_Intensify = new TEvt_Intensify(TEvt_Intensify.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：装备法宝一键强化
		private function _doReturn_IntensifyOneKey(bytes:ByteArray):void
		{
			var retParam_:SRetParam_IntensifyOneKey = new SRetParam_IntensifyOneKey();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bSucess:Boolean = bytes.readBoolean(); //成功/失败
			var dwIntensifyCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)强化次数（包括成功
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpIntensifyResult)结果
			retParam_.bSucess = bSucess;
			retParam_.dwIntensifyCount = dwIntensifyCount;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_IntensifyOneKey = _sessionMgr.getData(sessionID_) as SOrigParam_IntensifyOneKey;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_IntensifyOneKey = new TEvt_IntensifyOneKey(TEvt_IntensifyOneKey.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：装备法宝一键强化
		private function _onTimeOut_IntensifyOneKey(sessionID:uint):void
		{
			var retParam:SRetParam_IntensifyOneKey = new SRetParam_IntensifyOneKey();
			var event_:TEvt_IntensifyOneKey = new TEvt_IntensifyOneKey(TEvt_IntensifyOneKey.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：装备法宝洗炼
		private function _doReturn_ShuffleResult(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ShuffleResult = new SRetParam_ShuffleResult();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EEquipTrumpShuffleResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ShuffleResult = _sessionMgr.getData(sessionID_) as SOrigParam_ShuffleResult;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ShuffleResult = new TEvt_ShuffleResult(TEvt_ShuffleResult.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：装备法宝洗炼
		private function _onTimeOut_ShuffleResult(sessionID:uint):void
		{
			var retParam:SRetParam_ShuffleResult = new SRetParam_ShuffleResult();
			var event_:TEvt_ShuffleResult = new TEvt_ShuffleResult(TEvt_ShuffleResult.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:EquipTrumpProt;

		public static function get instance():EquipTrumpProt
		{
			if(_instance == null)
				_instance = new EquipTrumpProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function EquipTrumpProt()
		{
			_protID = 30;
			_recvFuncList = [
				_doRecv_EquipTrumpNotify //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GetAllEquipTrump, //FuncID: 1
				_doReturn_Wear, //FuncID: 2
				_doReturn_WearOneKey, //FuncID: 3
				_doReturn_TakeOff, //FuncID: 4
				_doReturn_Swap, //FuncID: 5
				_doReturn_MergeEquipTrump, //FuncID: 6
				_doReturn_BreakEquipTrump, //FuncID: 7
				_doReturn_Intensify, //FuncID: 8
				_doReturn_IntensifyOneKey, //FuncID: 9
				_doReturn_ShuffleResult //FuncID: 10
			];

			_timeFuncList = [
				_onTimeOut_GetAllEquipTrump, //FuncID: 1
				_onTimeOut_Wear, //FuncID: 2
				_onTimeOut_WearOneKey, //FuncID: 3
				_onTimeOut_TakeOff, //FuncID: 4
				_onTimeOut_Swap, //FuncID: 5
				_onTimeOut_MergeEquipTrump, //FuncID: 6
				_onTimeOut_BreakEquipTrump, //FuncID: 7
				_onTimeOut_Intensify, //FuncID: 8
				_onTimeOut_IntensifyOneKey, //FuncID: 9
				_onTimeOut_ShuffleResult //FuncID: 10
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