/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    BattleArray.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
{
	import flash.utils.ByteArray;
	import net.protocol.itemProt.SItemGenInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：破阵
	 */
	public class BattleArray extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取阵信息
		 */
		public function send_GetBattleArray(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetBattleArray = new SOrigParam_GetBattleArray();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：攻击阵图
		 * @param dwBattleArrayLevelID (无符号32位整数)阵图id
		 */
		public function send_AttackBattleArray(dwBattleArrayLevelID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_AttackBattleArray = new SOrigParam_AttackBattleArray();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwBattleArrayLevelID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：扫荡阵图
		 * @param dwBattleArrayLevelID (无符号32位整数)阵图id
		 */
		public function send_SweepBattleArray(dwBattleArrayLevelID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_SweepBattleArray = new SOrigParam_SweepBattleArray();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwBattleArrayLevelID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取通关奖励
		 * @param wBattleArrayID (无符号16位整数)阵id
		 */
		public function send_BattleArrayTakePrize(wBattleArrayID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BattleArrayTakePrize = new SOrigParam_BattleArrayTakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBattleArrayID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取当前购买价格
		 * @param dwCount (无符号32位整数)购买次数
		 */
		public function send_GetBuyAtkCountPrice(dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetBuyAtkCountPrice = new SOrigParam_GetBuyAtkCountPrice();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买攻击阵图次数
		 * @param dwCount (无符号32位整数)购买次数
		 */
		public function send_BuyAtkCount(dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_BuyAtkCount = new SOrigParam_BuyAtkCount();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：阵信息更新
		private function _doRecv_BattleArrayNotify(bytes:ByteArray):void
		{
			var oBattleArray:SBattleArray = SBattleArray.fromByteArray(bytes); //阵信息
			var event_:REvt_BattleArrayNotify = new REvt_BattleArrayNotify(REvt_BattleArrayNotify.DATA_RECEIVE);
			event_.oBattleArray = oBattleArray;
			dispatchEvent(event_);
		}

		//接收处理：攻击阵图信息
		private function _doRecv_SBattleArrayAttackCntNotify(bytes:ByteArray):void
		{
			var oBattleArrayAttackCnt:SBattleArrayAttackCnt = SBattleArrayAttackCnt.fromByteArray(bytes); //攻击阵图信息
			var event_:REvt_SBattleArrayAttackCntNotify = new REvt_SBattleArrayAttackCntNotify(REvt_SBattleArrayAttackCntNotify.DATA_RECEIVE);
			event_.oBattleArrayAttackCnt = oBattleArrayAttackCnt;
			dispatchEvent(event_);
		}

		//接收处理：总攻击次数
		private function _doRecv_TotleAttackCntNotify(bytes:ByteArray):void
		{
			var dwAttackCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)总攻击次数
			var dwBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)剩余购买数
			var event_:REvt_TotleAttackCntNotify = new REvt_TotleAttackCntNotify(REvt_TotleAttackCntNotify.DATA_RECEIVE);
			event_.dwAttackCnt = dwAttackCnt;
			event_.dwBuyCnt = dwBuyCnt;
			dispatchEvent(event_);
		}

		//接收处理：获得物品通知
		private function _doRecv_GainNotify(bytes:ByteArray):void
		{
			var eBattleArrayGain:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleArrayGain)类型
			var vecItemGenInfo:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //物品
			var event_:REvt_GainNotify = new REvt_GainNotify(REvt_GainNotify.DATA_RECEIVE);
			event_.eBattleArrayGain = eBattleArrayGain;
			event_.vecItemGenInfo = vecItemGenInfo;
			dispatchEvent(event_);
		}

		//接收处理：全部阵信息
		private function _doRecv_GetBattleArrayNotify(bytes:ByteArray):void
		{
			var vecBattleArray:Vector.<SBattleArray> = SBattleArray.vectorFromByteArray(bytes); //阵信息列表
			var vecBattleArrayAttackCnt:Vector.<SBattleArrayAttackCnt> = SBattleArrayAttackCnt.vectorFromByteArray(bytes); //攻击阵图信息
			var dwBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)可用的次数
			var dwDayBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)当天购买次数
			var event_:REvt_GetBattleArrayNotify = new REvt_GetBattleArrayNotify(REvt_GetBattleArrayNotify.DATA_RECEIVE);
			event_.vecBattleArray = vecBattleArray;
			event_.vecBattleArrayAttackCnt = vecBattleArrayAttackCnt;
			event_.dwBuyCnt = dwBuyCnt;
			event_.dwDayBuyCnt = dwDayBuyCnt;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取阵信息
		private function _doReturn_GetBattleArray(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBattleArray = new SRetParam_GetBattleArray();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBattleArray:Vector.<SBattleArray> = SBattleArray.vectorFromByteArray(bytes); //阵信息列表
			var vecBattleArrayAttackCnt:Vector.<SBattleArrayAttackCnt> = SBattleArrayAttackCnt.vectorFromByteArray(bytes); //攻击阵图信息
			var dwBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)可用的次数
			var dwDayBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)当天购买次数
			var dwFailCd:uint = bytes.readUnsignedInt(); //(无符号32位整数)战败cd
			retParam_.vecBattleArray = vecBattleArray;
			retParam_.vecBattleArrayAttackCnt = vecBattleArrayAttackCnt;
			retParam_.dwBuyCnt = dwBuyCnt;
			retParam_.dwDayBuyCnt = dwDayBuyCnt;
			retParam_.dwFailCd = dwFailCd;
			var origParam_:SOrigParam_GetBattleArray = _sessionMgr.getData(sessionID_) as SOrigParam_GetBattleArray;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBattleArray = new TEvt_GetBattleArray(TEvt_GetBattleArray.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取阵信息
		private function _onTimeOut_GetBattleArray(sessionID:uint):void
		{
			var retParam:SRetParam_GetBattleArray = new SRetParam_GetBattleArray();
			var event_:TEvt_GetBattleArray = new TEvt_GetBattleArray(TEvt_GetBattleArray.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：攻击阵图
		private function _doReturn_AttackBattleArray(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AttackBattleArray = new SRetParam_AttackBattleArray();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eBattleArrayRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleArrayRet)操作结果
			var dwFailCd:uint = bytes.readUnsignedInt(); //(无符号32位整数)战败cd
			retParam_.eBattleArrayRet = eBattleArrayRet;
			retParam_.dwFailCd = dwFailCd;
			var origParam_:SOrigParam_AttackBattleArray = _sessionMgr.getData(sessionID_) as SOrigParam_AttackBattleArray;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AttackBattleArray = new TEvt_AttackBattleArray(TEvt_AttackBattleArray.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：攻击阵图
		private function _onTimeOut_AttackBattleArray(sessionID:uint):void
		{
			var retParam:SRetParam_AttackBattleArray = new SRetParam_AttackBattleArray();
			var event_:TEvt_AttackBattleArray = new TEvt_AttackBattleArray(TEvt_AttackBattleArray.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：扫荡阵图
		private function _doReturn_SweepBattleArray(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SweepBattleArray = new SRetParam_SweepBattleArray();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eBattleArrayRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleArrayRet)操作结果
			retParam_.eBattleArrayRet = eBattleArrayRet;
			var origParam_:SOrigParam_SweepBattleArray = _sessionMgr.getData(sessionID_) as SOrigParam_SweepBattleArray;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SweepBattleArray = new TEvt_SweepBattleArray(TEvt_SweepBattleArray.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：扫荡阵图
		private function _onTimeOut_SweepBattleArray(sessionID:uint):void
		{
			var retParam:SRetParam_SweepBattleArray = new SRetParam_SweepBattleArray();
			var event_:TEvt_SweepBattleArray = new TEvt_SweepBattleArray(TEvt_SweepBattleArray.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取通关奖励
		private function _doReturn_BattleArrayTakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BattleArrayTakePrize = new SRetParam_BattleArrayTakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eBattleArrayRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleArrayRet)操作结果
			retParam_.eBattleArrayRet = eBattleArrayRet;
			var origParam_:SOrigParam_BattleArrayTakePrize = _sessionMgr.getData(sessionID_) as SOrigParam_BattleArrayTakePrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BattleArrayTakePrize = new TEvt_BattleArrayTakePrize(TEvt_BattleArrayTakePrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取通关奖励
		private function _onTimeOut_BattleArrayTakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_BattleArrayTakePrize = new SRetParam_BattleArrayTakePrize();
			var event_:TEvt_BattleArrayTakePrize = new TEvt_BattleArrayTakePrize(TEvt_BattleArrayTakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取当前购买价格
		private function _doReturn_GetBuyAtkCountPrice(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBuyAtkCountPrice = new SRetParam_GetBuyAtkCountPrice();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwPrice:uint = bytes.readUnsignedInt(); //(无符号32位整数)价格
			var dwBuyCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)当天已购买次数
			retParam_.dwPrice = dwPrice;
			retParam_.dwBuyCount = dwBuyCount;
			var origParam_:SOrigParam_GetBuyAtkCountPrice = _sessionMgr.getData(sessionID_) as SOrigParam_GetBuyAtkCountPrice;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBuyAtkCountPrice = new TEvt_GetBuyAtkCountPrice(TEvt_GetBuyAtkCountPrice.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取当前购买价格
		private function _onTimeOut_GetBuyAtkCountPrice(sessionID:uint):void
		{
			var retParam:SRetParam_GetBuyAtkCountPrice = new SRetParam_GetBuyAtkCountPrice();
			var event_:TEvt_GetBuyAtkCountPrice = new TEvt_GetBuyAtkCountPrice(TEvt_GetBuyAtkCountPrice.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买攻击阵图次数
		private function _doReturn_BuyAtkCount(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyAtkCount = new SRetParam_BuyAtkCount();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EBattleArrayRet)结果
			var dwBuyCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)已购买次数
			var dwDayBuyCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)当天购买次数
			retParam_.eRet = eRet;
			retParam_.dwBuyCount = dwBuyCount;
			retParam_.dwDayBuyCnt = dwDayBuyCnt;
			var origParam_:SOrigParam_BuyAtkCount = _sessionMgr.getData(sessionID_) as SOrigParam_BuyAtkCount;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyAtkCount = new TEvt_BuyAtkCount(TEvt_BuyAtkCount.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买攻击阵图次数
		private function _onTimeOut_BuyAtkCount(sessionID:uint):void
		{
			var retParam:SRetParam_BuyAtkCount = new SRetParam_BuyAtkCount();
			var event_:TEvt_BuyAtkCount = new TEvt_BuyAtkCount(TEvt_BuyAtkCount.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:BattleArray;

		public static function get instance():BattleArray
		{
			if(_instance == null)
				_instance = new BattleArray();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function BattleArray()
		{
			_protID = 130;
			_recvFuncList = [
				_doRecv_BattleArrayNotify, //FuncID: 1
				_doRecv_SBattleArrayAttackCntNotify, //FuncID: 2
				_doRecv_TotleAttackCntNotify, //FuncID: 3
				_doRecv_GainNotify, //FuncID: 4
				_doRecv_GetBattleArrayNotify //FuncID: 5
			];

			_retFuncList = [
				_doReturn_GetBattleArray, //FuncID: 1
				_doReturn_AttackBattleArray, //FuncID: 2
				_doReturn_SweepBattleArray, //FuncID: 3
				_doReturn_BattleArrayTakePrize, //FuncID: 4
				_doReturn_GetBuyAtkCountPrice, //FuncID: 5
				_doReturn_BuyAtkCount //FuncID: 6
			];

			_timeFuncList = [
				_onTimeOut_GetBattleArray, //FuncID: 1
				_onTimeOut_AttackBattleArray, //FuncID: 2
				_onTimeOut_SweepBattleArray, //FuncID: 3
				_onTimeOut_BattleArrayTakePrize, //FuncID: 4
				_onTimeOut_GetBuyAtkCountPrice, //FuncID: 5
				_onTimeOut_BuyAtkCount //FuncID: 6
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