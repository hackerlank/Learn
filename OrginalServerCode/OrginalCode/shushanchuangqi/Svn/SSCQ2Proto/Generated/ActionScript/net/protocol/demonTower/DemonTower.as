/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    DemonTower.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：锁妖塔
	 */
	public class DemonTower extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：进入锁妖塔 (暂时不用)
		 * @param dwFloorID (无符号32位整数)层数
		 */
		public function send_EnterDemonTower(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_EnterDemonTower = new SOrigParam_EnterDemonTower();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：离开锁妖塔 (暂时不用)
		 */
		public function send_LeaveDemonTower(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_LeaveDemonTower = new SOrigParam_LeaveDemonTower();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：封印怪物(暂时不用)
		 * @param dwFloorID (无符号32位整数)层数
		 */
		public function send_SealMonster(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_SealMonster = new SOrigParam_SealMonster();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：升级魄空间
		 * @param dwSoulSpaceID (无符号32位整数)魄空间类型ID
		 */
		public function send_UpgradeSoulSpace(dwSoulSpaceID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_UpgradeSoulSpace = new SOrigParam_UpgradeSoulSpace();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwSoulSpaceID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取魄空间列表
		 */
		public function send_GetSoulSpace():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取被攻击列表
		 */
		public function send_GetAttackedList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取每日奖励
		 */
		public function send_TakeDayPrize(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_TakeDayPrize = new SOrigParam_TakeDayPrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取每层奖励
		 * @param dwFloorID (无符号32位整数)层数
		 */
		public function send_TakeLayerPrize(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_TakeLayerPrize = new SOrigParam_TakeLayerPrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取最高已领奖层
		 */
		public function send_GetTopPrizeLayer(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetTopPrizeLayer = new SOrigParam_GetTopPrizeLayer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：清除pve战斗cd
		 */
		public function send_ClearFightMonsterCd(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_ClearFightMonsterCd = new SOrigParam_ClearFightMonsterCd();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取已领奖励层数
		 */
		public function send_GetLayerPrized(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetLayerPrized = new SOrigParam_GetLayerPrized();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：升级魄空间通知
		private function _doRecv_UpgradeSoulSpaceNotify(bytes:ByteArray):void
		{
			var dwSoulSpaceID:uint = bytes.readUnsignedInt(); //(无符号32位整数)魄空间类型ID(升级结果)
			var dwSoulSpaceLevel:uint = bytes.readUnsignedInt(); //(无符号32位整数)魄空间等级(升级结果)
			var event_:REvt_UpgradeSoulSpaceNotify = new REvt_UpgradeSoulSpaceNotify(REvt_UpgradeSoulSpaceNotify.DATA_RECEIVE);
			event_.dwSoulSpaceID = dwSoulSpaceID;
			event_.dwSoulSpaceLevel = dwSoulSpaceLevel;
			dispatchEvent(event_);
		}

		//接收处理：魄空间列表
		private function _doRecv_SoulSpaceListNotify(bytes:ByteArray):void
		{
			var vecSpaceInfo:Vector.<SSpaceInfo> = SSpaceInfo.vectorFromByteArray(bytes); //魄空间列表
			var event_:REvt_SoulSpaceListNotify = new REvt_SoulSpaceListNotify(REvt_SoulSpaceListNotify.DATA_RECEIVE);
			event_.vecSpaceInfo = vecSpaceInfo;
			dispatchEvent(event_);
		}

		//接收处理：每日重置奖励通知
		private function _doRecv_DayPrizeResetNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var event_:REvt_DayPrizeResetNotify = new REvt_DayPrizeResetNotify(REvt_DayPrizeResetNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			dispatchEvent(event_);
		}

		//接收处理：被攻击列表通知
		private function _doRecv_AttackListNotify(bytes:ByteArray):void
		{
			var oDemonToweAttackedInfo:Vector.<SDemonToweAttackedInfo> = SDemonToweAttackedInfo.vectorFromByteArray(bytes); //被攻击列表
			var event_:REvt_AttackListNotify = new REvt_AttackListNotify(REvt_AttackListNotify.DATA_RECEIVE);
			event_.oDemonToweAttackedInfo = oDemonToweAttackedInfo;
			dispatchEvent(event_);
		}

		//接收处理：被攻击通知(收到通知后拉取被攻击列表)
		private function _doRecv_AttackChangedNotify(bytes:ByteArray):void
		{
			var event_:REvt_AttackChangedNotify = new REvt_AttackChangedNotify(REvt_AttackChangedNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：通关协议
		private function _doRecv_FloorPassNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)通关层数
			var event_:REvt_FloorPassNotify = new REvt_FloorPassNotify(REvt_FloorPassNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：进入锁妖塔 (暂时不用)
		private function _doReturn_EnterDemonTower(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterDemonTower = new SRetParam_EnterDemonTower();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_EnterDemonTower = _sessionMgr.getData(sessionID_) as SOrigParam_EnterDemonTower;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterDemonTower = new TEvt_EnterDemonTower(TEvt_EnterDemonTower.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：进入锁妖塔 (暂时不用)
		private function _onTimeOut_EnterDemonTower(sessionID:uint):void
		{
			var retParam:SRetParam_EnterDemonTower = new SRetParam_EnterDemonTower();
			var event_:TEvt_EnterDemonTower = new TEvt_EnterDemonTower(TEvt_EnterDemonTower.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开锁妖塔 (暂时不用)
		private function _doReturn_LeaveDemonTower(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveDemonTower = new SRetParam_LeaveDemonTower();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_LeaveDemonTower = _sessionMgr.getData(sessionID_) as SOrigParam_LeaveDemonTower;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeaveDemonTower = new TEvt_LeaveDemonTower(TEvt_LeaveDemonTower.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：离开锁妖塔 (暂时不用)
		private function _onTimeOut_LeaveDemonTower(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveDemonTower = new SRetParam_LeaveDemonTower();
			var event_:TEvt_LeaveDemonTower = new TEvt_LeaveDemonTower(TEvt_LeaveDemonTower.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：封印怪物(暂时不用)
		private function _doReturn_SealMonster(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SealMonster = new SRetParam_SealMonster();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_SealMonster = _sessionMgr.getData(sessionID_) as SOrigParam_SealMonster;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SealMonster = new TEvt_SealMonster(TEvt_SealMonster.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：封印怪物(暂时不用)
		private function _onTimeOut_SealMonster(sessionID:uint):void
		{
			var retParam:SRetParam_SealMonster = new SRetParam_SealMonster();
			var event_:TEvt_SealMonster = new TEvt_SealMonster(TEvt_SealMonster.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：升级魄空间
		private function _doReturn_UpgradeSoulSpace(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeSoulSpace = new SRetParam_UpgradeSoulSpace();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_UpgradeSoulSpace = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeSoulSpace;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeSoulSpace = new TEvt_UpgradeSoulSpace(TEvt_UpgradeSoulSpace.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：升级魄空间
		private function _onTimeOut_UpgradeSoulSpace(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeSoulSpace = new SRetParam_UpgradeSoulSpace();
			var event_:TEvt_UpgradeSoulSpace = new TEvt_UpgradeSoulSpace(TEvt_UpgradeSoulSpace.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取每日奖励
		private function _doReturn_TakeDayPrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeDayPrize = new SRetParam_TakeDayPrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_TakeDayPrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeDayPrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeDayPrize = new TEvt_TakeDayPrize(TEvt_TakeDayPrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取每日奖励
		private function _onTimeOut_TakeDayPrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeDayPrize = new SRetParam_TakeDayPrize();
			var event_:TEvt_TakeDayPrize = new TEvt_TakeDayPrize(TEvt_TakeDayPrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取每层奖励
		private function _doReturn_TakeLayerPrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeLayerPrize = new SRetParam_TakeLayerPrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)最高已领奖层
			retParam_.dwRet = dwRet;
			retParam_.dwFloorID = dwFloorID;
			var origParam_:SOrigParam_TakeLayerPrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeLayerPrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeLayerPrize = new TEvt_TakeLayerPrize(TEvt_TakeLayerPrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取每层奖励
		private function _onTimeOut_TakeLayerPrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeLayerPrize = new SRetParam_TakeLayerPrize();
			var event_:TEvt_TakeLayerPrize = new TEvt_TakeLayerPrize(TEvt_TakeLayerPrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取最高已领奖层
		private function _doReturn_GetTopPrizeLayer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTopPrizeLayer = new SRetParam_GetTopPrizeLayer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			retParam_.dwFloorID = dwFloorID;
			var origParam_:SOrigParam_GetTopPrizeLayer = _sessionMgr.getData(sessionID_) as SOrigParam_GetTopPrizeLayer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTopPrizeLayer = new TEvt_GetTopPrizeLayer(TEvt_GetTopPrizeLayer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取最高已领奖层
		private function _onTimeOut_GetTopPrizeLayer(sessionID:uint):void
		{
			var retParam:SRetParam_GetTopPrizeLayer = new SRetParam_GetTopPrizeLayer();
			var event_:TEvt_GetTopPrizeLayer = new TEvt_GetTopPrizeLayer(TEvt_GetTopPrizeLayer.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清除pve战斗cd
		private function _doReturn_ClearFightMonsterCd(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ClearFightMonsterCd = new SRetParam_ClearFightMonsterCd();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0成功 其他失败
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_ClearFightMonsterCd = _sessionMgr.getData(sessionID_) as SOrigParam_ClearFightMonsterCd;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ClearFightMonsterCd = new TEvt_ClearFightMonsterCd(TEvt_ClearFightMonsterCd.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清除pve战斗cd
		private function _onTimeOut_ClearFightMonsterCd(sessionID:uint):void
		{
			var retParam:SRetParam_ClearFightMonsterCd = new SRetParam_ClearFightMonsterCd();
			var event_:TEvt_ClearFightMonsterCd = new TEvt_ClearFightMonsterCd(TEvt_ClearFightMonsterCd.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取已领奖励层数
		private function _doReturn_GetLayerPrized(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetLayerPrized = new SRetParam_GetLayerPrized();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFloorID:Vector.<uint> = BytesUtil.readVecUInt(bytes); //(无符号32位整数)已领奖励层数
			retParam_.vecFloorID = vecFloorID;
			var origParam_:SOrigParam_GetLayerPrized = _sessionMgr.getData(sessionID_) as SOrigParam_GetLayerPrized;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetLayerPrized = new TEvt_GetLayerPrized(TEvt_GetLayerPrized.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取已领奖励层数
		private function _onTimeOut_GetLayerPrized(sessionID:uint):void
		{
			var retParam:SRetParam_GetLayerPrized = new SRetParam_GetLayerPrized();
			var event_:TEvt_GetLayerPrized = new TEvt_GetLayerPrized(TEvt_GetLayerPrized.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:DemonTower;

		public static function get instance():DemonTower
		{
			if(_instance == null)
				_instance = new DemonTower();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function DemonTower()
		{
			_protID = 70;
			_recvFuncList = [
				_doRecv_UpgradeSoulSpaceNotify, //FuncID: 1
				_doRecv_SoulSpaceListNotify, //FuncID: 2
				_doRecv_DayPrizeResetNotify, //FuncID: 3
				_doRecv_AttackListNotify, //FuncID: 4
				_doRecv_AttackChangedNotify, //FuncID: 5
				_doRecv_FloorPassNotify //FuncID: 6
			];

			_retFuncList = [
				_doReturn_EnterDemonTower, //FuncID: 1
				_doReturn_LeaveDemonTower, //FuncID: 2
				_doReturn_SealMonster, //FuncID: 3
				_doReturn_UpgradeSoulSpace, //FuncID: 4
				_doReturn_TakeDayPrize, //FuncID: 5
				_doReturn_TakeLayerPrize, //FuncID: 6
				_doReturn_GetTopPrizeLayer, //FuncID: 7
				_doReturn_ClearFightMonsterCd, //FuncID: 8
				_doReturn_GetLayerPrized //FuncID: 9
			];

			_timeFuncList = [
				_onTimeOut_EnterDemonTower, //FuncID: 1
				_onTimeOut_LeaveDemonTower, //FuncID: 2
				_onTimeOut_SealMonster, //FuncID: 3
				_onTimeOut_UpgradeSoulSpace, //FuncID: 4
				_onTimeOut_TakeDayPrize, //FuncID: 5
				_onTimeOut_TakeLayerPrize, //FuncID: 6
				_onTimeOut_GetTopPrizeLayer, //FuncID: 7
				_onTimeOut_ClearFightMonsterCd, //FuncID: 8
				_onTimeOut_GetLayerPrized //FuncID: 9
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