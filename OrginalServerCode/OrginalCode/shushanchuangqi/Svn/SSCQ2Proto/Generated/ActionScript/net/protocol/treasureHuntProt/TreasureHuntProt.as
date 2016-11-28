/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    TreasureHuntProt.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：寻宝协议
	 */
	public class TreasureHuntProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求寻宝信息
		 */
		public function send_ReqTHInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_ReqTHInfo = new SOrigParam_ReqTHInfo();
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
		 * 发送：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
		 */
		public function send_ReqTHBattlePrepareInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_ReqTHBattlePrepareInfo = new SOrigParam_ReqTHBattlePrepareInfo();
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
		 * 发送：请求寻宝开始
		 * @param byCopyID (无符号8位整数)副本ID
		 */
		public function send_ReqTHStart(byCopyID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ReqTHStart = new SOrigParam_ReqTHStart();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byCopyID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求寻宝立即完成
		 */
		public function send_ReqTHQuickFinish(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ReqTHQuickFinish = new SOrigParam_ReqTHQuickFinish();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求放弃寻宝
		 */
		public function send_ReqTHGiveUp(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ReqTHGiveUp = new SOrigParam_ReqTHGiveUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求使用Buff
		 * @param byBuffID (无符号8位整数)BuffID
		 */
		public function send_ReqUseBuff(byBuffID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_ReqUseBuff = new SOrigParam_ReqUseBuff();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byBuffID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求寻宝奖励信息
		 */
		public function send_ReqTHAwardInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_ReqTHAwardInfo = new SOrigParam_ReqTHAwardInfo();
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
		 * 发送：获取寻宝奖励
		 */
		public function send_GetTHAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetTHAward = new SOrigParam_GetTHAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：寻宝开始/结束通知
		private function _doRecv_THNotify(bytes:ByteArray):void
		{
			var eTHNotify:int = bytes.readByte(); //(枚举类型：ETHNotify)开始/结束
			var byKillNum:uint = bytes.readUnsignedByte(); //(无符号8位整数)今日已击杀BOSS次数
			var vecTHBuffInfo:Vector.<STHBuffInfo> = STHBuffInfo.vectorFromByteArray(bytes); //Buff信息
			var event_:REvt_THNotify = new REvt_THNotify(REvt_THNotify.DATA_RECEIVE);
			event_.eTHNotify = eTHNotify;
			event_.byKillNum = byKillNum;
			event_.vecTHBuffInfo = vecTHBuffInfo;
			dispatchEvent(event_);
		}

		//接收处理：战斗结果通知
		private function _doRecv_THBattleResultNotify(bytes:ByteArray):void
		{
			var sBattleResult:STHBattleResult = STHBattleResult.fromByteArray(bytes); //战斗结果
			var event_:REvt_THBattleResultNotify = new REvt_THBattleResultNotify(REvt_THBattleResultNotify.DATA_RECEIVE);
			event_.sBattleResult = sBattleResult;
			dispatchEvent(event_);
		}

		//接收处理：寻宝掉落通知
		private function _doRecv_THLootNotify(bytes:ByteArray):void
		{
			var vecTHAwardInfo:Vector.<STHAwardInfo> = STHAwardInfo.vectorFromByteArray(bytes); //掉落
			var event_:REvt_THLootNotify = new REvt_THLootNotify(REvt_THLootNotify.DATA_RECEIVE);
			event_.vecTHAwardInfo = vecTHAwardInfo;
			dispatchEvent(event_);
		}

		//接收处理：日志通知
		private function _doRecv_THLogNotify(bytes:ByteArray):void
		{
			var eTHLogType:int = bytes.readByte(); //(枚举类型：ETHLogType)寻宝日志类型
			var dwParamA:uint = bytes.readUnsignedInt(); //(无符号32位整数)参数A
			var dwParamB:uint = bytes.readUnsignedInt(); //(无符号32位整数)参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
			var dwParamC:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
			var event_:REvt_THLogNotify = new REvt_THLogNotify(REvt_THLogNotify.DATA_RECEIVE);
			event_.eTHLogType = eTHLogType;
			event_.dwParamA = dwParamA;
			event_.dwParamB = dwParamB;
			event_.dwParamC = dwParamC;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求寻宝信息
		private function _doReturn_ReqTHInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHInfo = new SRetParam_ReqTHInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byCopyID:uint = bytes.readUnsignedByte(); //(无符号8位整数)0:没有副本进行中；非0:正在进行该副本
			var eTHStatus:int = bytes.readByte(); //(枚举类型：ETHStatus)寻宝状态
			var byKillNum:uint = bytes.readUnsignedByte(); //(无符号8位整数)剩余击杀次数
			var byCurrentID:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前通关到副本ID
			retParam_.byCopyID = byCopyID;
			retParam_.eTHStatus = eTHStatus;
			retParam_.byKillNum = byKillNum;
			retParam_.byCurrentID = byCurrentID;
			var origParam_:SOrigParam_ReqTHInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHInfo = new TEvt_ReqTHInfo(TEvt_ReqTHInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求寻宝信息
		private function _onTimeOut_ReqTHInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHInfo = new SRetParam_ReqTHInfo();
			var event_:TEvt_ReqTHInfo = new TEvt_ReqTHInfo(TEvt_ReqTHInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
		private function _doReturn_ReqTHBattlePrepareInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHBattlePrepareInfo = new SRetParam_ReqTHBattlePrepareInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byKillNum:uint = bytes.readUnsignedByte(); //(无符号8位整数)剩余击杀次数
			var dwCurBossHP:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前BOSS血量
			var dwTotalTimes:uint = bytes.readUnsignedInt(); //(无符号32位整数)寻宝时间
			var vecTHAwardInfo:Vector.<STHAwardInfo> = STHAwardInfo.vectorFromByteArray(bytes); //寻宝奖励信息
			var vecTHBuffInfo:Vector.<STHBuffInfo> = STHBuffInfo.vectorFromByteArray(bytes); //Buff信息
			retParam_.byKillNum = byKillNum;
			retParam_.dwCurBossHP = dwCurBossHP;
			retParam_.dwTotalTimes = dwTotalTimes;
			retParam_.vecTHAwardInfo = vecTHAwardInfo;
			retParam_.vecTHBuffInfo = vecTHBuffInfo;
			var origParam_:SOrigParam_ReqTHBattlePrepareInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHBattlePrepareInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHBattlePrepareInfo = new TEvt_ReqTHBattlePrepareInfo(TEvt_ReqTHBattlePrepareInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
		private function _onTimeOut_ReqTHBattlePrepareInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHBattlePrepareInfo = new SRetParam_ReqTHBattlePrepareInfo();
			var event_:TEvt_ReqTHBattlePrepareInfo = new TEvt_ReqTHBattlePrepareInfo(TEvt_ReqTHBattlePrepareInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求寻宝开始
		private function _doReturn_ReqTHStart(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHStart = new SRetParam_ReqTHStart();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eTHOptResult:int = bytes.readByte(); //(枚举类型：ETHOptResult)操作结果
			retParam_.eTHOptResult = eTHOptResult;
			var origParam_:SOrigParam_ReqTHStart = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHStart;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHStart = new TEvt_ReqTHStart(TEvt_ReqTHStart.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求寻宝开始
		private function _onTimeOut_ReqTHStart(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHStart = new SRetParam_ReqTHStart();
			var event_:TEvt_ReqTHStart = new TEvt_ReqTHStart(TEvt_ReqTHStart.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求寻宝立即完成
		private function _doReturn_ReqTHQuickFinish(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHQuickFinish = new SRetParam_ReqTHQuickFinish();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eTHOptResult:int = bytes.readByte(); //(枚举类型：ETHOptResult)操作结果
			retParam_.eTHOptResult = eTHOptResult;
			var origParam_:SOrigParam_ReqTHQuickFinish = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHQuickFinish;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHQuickFinish = new TEvt_ReqTHQuickFinish(TEvt_ReqTHQuickFinish.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求寻宝立即完成
		private function _onTimeOut_ReqTHQuickFinish(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHQuickFinish = new SRetParam_ReqTHQuickFinish();
			var event_:TEvt_ReqTHQuickFinish = new TEvt_ReqTHQuickFinish(TEvt_ReqTHQuickFinish.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求放弃寻宝
		private function _doReturn_ReqTHGiveUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHGiveUp = new SRetParam_ReqTHGiveUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eTHOptResult:int = bytes.readByte(); //(枚举类型：ETHOptResult)操作结果
			retParam_.eTHOptResult = eTHOptResult;
			var origParam_:SOrigParam_ReqTHGiveUp = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHGiveUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHGiveUp = new TEvt_ReqTHGiveUp(TEvt_ReqTHGiveUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求放弃寻宝
		private function _onTimeOut_ReqTHGiveUp(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHGiveUp = new SRetParam_ReqTHGiveUp();
			var event_:TEvt_ReqTHGiveUp = new TEvt_ReqTHGiveUp(TEvt_ReqTHGiveUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求使用Buff
		private function _doReturn_ReqUseBuff(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqUseBuff = new SRetParam_ReqUseBuff();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eTHOptResult:int = bytes.readByte(); //(枚举类型：ETHOptResult)操作结果
			retParam_.eTHOptResult = eTHOptResult;
			var origParam_:SOrigParam_ReqUseBuff = _sessionMgr.getData(sessionID_) as SOrigParam_ReqUseBuff;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqUseBuff = new TEvt_ReqUseBuff(TEvt_ReqUseBuff.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求使用Buff
		private function _onTimeOut_ReqUseBuff(sessionID:uint):void
		{
			var retParam:SRetParam_ReqUseBuff = new SRetParam_ReqUseBuff();
			var event_:TEvt_ReqUseBuff = new TEvt_ReqUseBuff(TEvt_ReqUseBuff.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求寻宝奖励信息
		private function _doReturn_ReqTHAwardInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqTHAwardInfo = new SRetParam_ReqTHAwardInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byCopyID:uint = bytes.readUnsignedByte(); //(无符号8位整数)副本ID
			var vecTHAwardInfo:Vector.<STHAwardInfo> = STHAwardInfo.vectorFromByteArray(bytes); //寻宝奖励信息
			retParam_.byCopyID = byCopyID;
			retParam_.vecTHAwardInfo = vecTHAwardInfo;
			var origParam_:SOrigParam_ReqTHAwardInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqTHAwardInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqTHAwardInfo = new TEvt_ReqTHAwardInfo(TEvt_ReqTHAwardInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求寻宝奖励信息
		private function _onTimeOut_ReqTHAwardInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqTHAwardInfo = new SRetParam_ReqTHAwardInfo();
			var event_:TEvt_ReqTHAwardInfo = new TEvt_ReqTHAwardInfo(TEvt_ReqTHAwardInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取寻宝奖励
		private function _doReturn_GetTHAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTHAward = new SRetParam_GetTHAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eTHOptResult:int = bytes.readByte(); //(枚举类型：ETHOptResult)操作结果
			retParam_.eTHOptResult = eTHOptResult;
			var origParam_:SOrigParam_GetTHAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetTHAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTHAward = new TEvt_GetTHAward(TEvt_GetTHAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取寻宝奖励
		private function _onTimeOut_GetTHAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetTHAward = new SRetParam_GetTHAward();
			var event_:TEvt_GetTHAward = new TEvt_GetTHAward(TEvt_GetTHAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:TreasureHuntProt;

		public static function get instance():TreasureHuntProt
		{
			if(_instance == null)
				_instance = new TreasureHuntProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function TreasureHuntProt()
		{
			_protID = 85;
			_recvFuncList = [
				_doRecv_THNotify, //FuncID: 1
				_doRecv_THBattleResultNotify, //FuncID: 2
				_doRecv_THLootNotify, //FuncID: 3
				_doRecv_THLogNotify //FuncID: 4
			];

			_retFuncList = [
				_doReturn_ReqTHInfo, //FuncID: 1
				_doReturn_ReqTHBattlePrepareInfo, //FuncID: 2
				_doReturn_ReqTHStart, //FuncID: 3
				_doReturn_ReqTHQuickFinish, //FuncID: 4
				_doReturn_ReqTHGiveUp, //FuncID: 5
				_doReturn_ReqUseBuff, //FuncID: 6
				_doReturn_ReqTHAwardInfo, //FuncID: 7
				_doReturn_GetTHAward //FuncID: 8
			];

			_timeFuncList = [
				_onTimeOut_ReqTHInfo, //FuncID: 1
				_onTimeOut_ReqTHBattlePrepareInfo, //FuncID: 2
				_onTimeOut_ReqTHStart, //FuncID: 3
				_onTimeOut_ReqTHQuickFinish, //FuncID: 4
				_onTimeOut_ReqTHGiveUp, //FuncID: 5
				_onTimeOut_ReqUseBuff, //FuncID: 6
				_onTimeOut_ReqTHAwardInfo, //FuncID: 7
				_onTimeOut_GetTHAward //FuncID: 8
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