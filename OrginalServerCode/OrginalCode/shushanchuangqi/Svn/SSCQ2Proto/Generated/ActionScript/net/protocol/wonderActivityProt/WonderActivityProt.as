/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    WonderActivityProt.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：精彩活动
	 */
	public class WonderActivityProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获得活动时间配置
		 * @param wWActID (无符号16位整数)精彩活动ID
		 */
		public function send_GetConfigTime(wWActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetConfigTime = new SOrigParam_GetConfigTime();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wWActID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得活动所有奖励配置
		 * @param wWActID (无符号16位整数)精彩活动ID
		 */
		public function send_GetAllPrize(wWActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetAllPrize = new SOrigParam_GetAllPrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wWActID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得活动列表
		 */
		public function send_GetActList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetActList = new SOrigParam_GetActList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家领奖
		 * @param wActID (无符号16位整数)精彩活动ID
		 * @param wCond (无符号32位整数)条件
		 */
		public function send_TakePrize(wActID:uint, wCond:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wActID);
			bytes_.writeUnsignedInt(wCond);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家活动信息
		 * @param wActID (无符号16位整数)活动ID
		 */
		public function send_GetRoleActInfo(wActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetRoleActInfo = new SOrigParam_GetRoleActInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wActID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家在所有活动中的状态
		 */
		public function send_GetRoleAllState(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetRoleAllState = new SOrigParam_GetRoleAllState();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求七星龙珠活动信息
		 */
		public function send_GetDragonBallAct(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetDragonBallAct = new SOrigParam_GetDragonBallAct();
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
		 * 发送：请求七日消费活动信息
		 */
		public function send_GetSevenConsumeAct(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetSevenConsumeAct = new SOrigParam_GetSevenConsumeAct();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求Q养成活动信息
		 */
		public function send_GetQQCoinAct():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：兑换仙石或者领取Q币
		 * @param byType (无符号8位整数)0表示Q币，1表示仙石
		 */
		public function send_ExChange(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_ExChange = new SOrigParam_ExChange();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：领奖状态通知
		private function _doRecv_SendTakePrizeNtf(bytes:ByteArray):void
		{
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var wCond:uint = bytes.readUnsignedInt(); //(无符号32位整数)条件ID
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EGainResult)状态
			var event_:REvt_SendTakePrizeNtf = new REvt_SendTakePrizeNtf(REvt_SendTakePrizeNtf.DATA_RECEIVE);
			event_.wActID = wActID;
			event_.wCond = wCond;
			event_.eRet = eRet;
			dispatchEvent(event_);
		}

		//接收处理：达到条件通知
		private function _doRecv_SendReachCondNtf(bytes:ByteArray):void
		{
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var wCond:uint = bytes.readUnsignedInt(); //(无符号32位整数)条件ID
			var event_:REvt_SendReachCondNtf = new REvt_SendReachCondNtf(REvt_SendReachCondNtf.DATA_RECEIVE);
			event_.wActID = wActID;
			event_.wCond = wCond;
			dispatchEvent(event_);
		}

		//接收处理：更新七星龙珠活动信息
		private function _doRecv_UpdateDragonBallAct(bytes:ByteArray):void
		{
			var oDragonBallAct:SDragonBallAct = SDragonBallAct.fromByteArray(bytes); //七星龙珠活动信息
			var event_:REvt_UpdateDragonBallAct = new REvt_UpdateDragonBallAct(REvt_UpdateDragonBallAct.DATA_RECEIVE);
			event_.oDragonBallAct = oDragonBallAct;
			dispatchEvent(event_);
		}

		//接收处理：更新七日消费活动信息
		private function _doRecv_UpdateSevenConsumeAct(bytes:ByteArray):void
		{
			var oSevenConsumeAct:SSevenConsumeAct = SSevenConsumeAct.fromByteArray(bytes); //七日消费活动信息
			var event_:REvt_UpdateSevenConsumeAct = new REvt_UpdateSevenConsumeAct(REvt_UpdateSevenConsumeAct.DATA_RECEIVE);
			event_.oSevenConsumeAct = oSevenConsumeAct;
			dispatchEvent(event_);
		}

		//接收处理：同步QQ养成信息
		private function _doRecv_SyncQQCoinInfo(bytes:ByteArray):void
		{
			var oQQCoinInfo:SQQCoinActInfo = SQQCoinActInfo.fromByteArray(bytes); //Q养成活动信息
			var event_:REvt_SyncQQCoinInfo = new REvt_SyncQQCoinInfo(REvt_SyncQQCoinInfo.DATA_RECEIVE);
			event_.oQQCoinInfo = oQQCoinInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获得活动时间配置
		private function _doReturn_GetConfigTime(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetConfigTime = new SRetParam_GetConfigTime();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sTimes:STime = STime.fromByteArray(bytes); //时间
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EWActResult)操作结果
			retParam_.sTimes = sTimes;
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_GetConfigTime = _sessionMgr.getData(sessionID_) as SOrigParam_GetConfigTime;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetConfigTime = new TEvt_GetConfigTime(TEvt_GetConfigTime.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得活动时间配置
		private function _onTimeOut_GetConfigTime(sessionID:uint):void
		{
			var retParam:SRetParam_GetConfigTime = new SRetParam_GetConfigTime();
			var event_:TEvt_GetConfigTime = new TEvt_GetConfigTime(TEvt_GetConfigTime.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得活动所有奖励配置
		private function _doReturn_GetAllPrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllPrize = new SRetParam_GetAllPrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var sFirstPlayer:SWActPlayerInfo = SWActPlayerInfo.fromByteArray(bytes); //第一名玩家信息
			var sSelfPlayer:SWActPlayerInfo = SWActPlayerInfo.fromByteArray(bytes); //玩家自己信息
			var vecPrizeConfig:Vector.<SPrizeConfig> = SPrizeConfig.vectorFromByteArray(bytes); //奖励信息
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EWActResult)操作结果
			retParam_.wActID = wActID;
			retParam_.sFirstPlayer = sFirstPlayer;
			retParam_.sSelfPlayer = sSelfPlayer;
			retParam_.vecPrizeConfig = vecPrizeConfig;
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_GetAllPrize = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllPrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllPrize = new TEvt_GetAllPrize(TEvt_GetAllPrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得活动所有奖励配置
		private function _onTimeOut_GetAllPrize(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllPrize = new SRetParam_GetAllPrize();
			var event_:TEvt_GetAllPrize = new TEvt_GetAllPrize(TEvt_GetAllPrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得活动列表
		private function _doReturn_GetActList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetActList = new SRetParam_GetActList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTimes:Vector.<STime> = STime.vectorFromByteArray(bytes); //奖励信息
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EWActResult)操作结果
			retParam_.vecTimes = vecTimes;
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_GetActList = _sessionMgr.getData(sessionID_) as SOrigParam_GetActList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetActList = new TEvt_GetActList(TEvt_GetActList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得活动列表
		private function _onTimeOut_GetActList(sessionID:uint):void
		{
			var retParam:SRetParam_GetActList = new SRetParam_GetActList();
			var event_:TEvt_GetActList = new TEvt_GetActList(TEvt_GetActList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家领奖
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wActIDRet:uint = bytes.readUnsignedShort(); //(无符号16位整数)返回活动ID
			var wCondRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)返回条件
			retParam_.wActIDRet = wActIDRet;
			retParam_.wCondRet = wCondRet;
			var origParam_:SOrigParam_TakePrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakePrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家领奖
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家活动信息
		private function _doReturn_GetRoleActInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleActInfo = new SRetParam_GetRoleActInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wActIDRet:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var vecRet:Vector.<SRoleStatus> = SRoleStatus.vectorFromByteArray(bytes); //操作结果
			retParam_.wActIDRet = wActIDRet;
			retParam_.vecRet = vecRet;
			var origParam_:SOrigParam_GetRoleActInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleActInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleActInfo = new TEvt_GetRoleActInfo(TEvt_GetRoleActInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家活动信息
		private function _onTimeOut_GetRoleActInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleActInfo = new SRetParam_GetRoleActInfo();
			var event_:TEvt_GetRoleActInfo = new TEvt_GetRoleActInfo(TEvt_GetRoleActInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家在所有活动中的状态
		private function _doReturn_GetRoleAllState(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleAllState = new SRetParam_GetRoleAllState();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecRet:Vector.<SRoleAllStatus> = SRoleAllStatus.vectorFromByteArray(bytes); //结果
			retParam_.vecRet = vecRet;
			var origParam_:SOrigParam_GetRoleAllState = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleAllState;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleAllState = new TEvt_GetRoleAllState(TEvt_GetRoleAllState.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家在所有活动中的状态
		private function _onTimeOut_GetRoleAllState(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleAllState = new SRetParam_GetRoleAllState();
			var event_:TEvt_GetRoleAllState = new TEvt_GetRoleAllState(TEvt_GetRoleAllState.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求七星龙珠活动信息
		private function _doReturn_GetDragonBallAct(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDragonBallAct = new SRetParam_GetDragonBallAct();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0活动未开启 >0活动已开启
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetDragonBallAct = _sessionMgr.getData(sessionID_) as SOrigParam_GetDragonBallAct;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDragonBallAct = new TEvt_GetDragonBallAct(TEvt_GetDragonBallAct.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求七星龙珠活动信息
		private function _onTimeOut_GetDragonBallAct(sessionID:uint):void
		{
			var retParam:SRetParam_GetDragonBallAct = new SRetParam_GetDragonBallAct();
			var event_:TEvt_GetDragonBallAct = new TEvt_GetDragonBallAct(TEvt_GetDragonBallAct.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求七日消费活动信息
		private function _doReturn_GetSevenConsumeAct(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSevenConsumeAct = new SRetParam_GetSevenConsumeAct();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0活动未开启 >0活动已开启
			retParam_.byRet = byRet;
			var origParam_:SOrigParam_GetSevenConsumeAct = _sessionMgr.getData(sessionID_) as SOrigParam_GetSevenConsumeAct;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSevenConsumeAct = new TEvt_GetSevenConsumeAct(TEvt_GetSevenConsumeAct.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求七日消费活动信息
		private function _onTimeOut_GetSevenConsumeAct(sessionID:uint):void
		{
			var retParam:SRetParam_GetSevenConsumeAct = new SRetParam_GetSevenConsumeAct();
			var event_:TEvt_GetSevenConsumeAct = new TEvt_GetSevenConsumeAct(TEvt_GetSevenConsumeAct.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：兑换仙石或者领取Q币
		private function _doReturn_ExChange(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ExChange = new SRetParam_ExChange();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EWActResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ExChange = _sessionMgr.getData(sessionID_) as SOrigParam_ExChange;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ExChange = new TEvt_ExChange(TEvt_ExChange.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：兑换仙石或者领取Q币
		private function _onTimeOut_ExChange(sessionID:uint):void
		{
			var retParam:SRetParam_ExChange = new SRetParam_ExChange();
			var event_:TEvt_ExChange = new TEvt_ExChange(TEvt_ExChange.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:WonderActivityProt;

		public static function get instance():WonderActivityProt
		{
			if(_instance == null)
				_instance = new WonderActivityProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function WonderActivityProt()
		{
			_protID = 199;
			_recvFuncList = [
				_doRecv_SendTakePrizeNtf, //FuncID: 1
				_doRecv_SendReachCondNtf, //FuncID: 2
				_doRecv_UpdateDragonBallAct, //FuncID: 3
				_doRecv_UpdateSevenConsumeAct, //FuncID: 4
				_doRecv_SyncQQCoinInfo //FuncID: 5
			];

			_retFuncList = [
				_doReturn_GetConfigTime, //FuncID: 1
				_doReturn_GetAllPrize, //FuncID: 2
				_doReturn_GetActList, //FuncID: 3
				_doReturn_TakePrize, //FuncID: 4
				_doReturn_GetRoleActInfo, //FuncID: 5
				_doReturn_GetRoleAllState, //FuncID: 6
				_doReturn_GetDragonBallAct, //FuncID: 7
				_doReturn_GetSevenConsumeAct, //FuncID: 8
				_doReturn_ExChange //FuncID: 9
			];

			_timeFuncList = [
				_onTimeOut_GetConfigTime, //FuncID: 1
				_onTimeOut_GetAllPrize, //FuncID: 2
				_onTimeOut_GetActList, //FuncID: 3
				_onTimeOut_TakePrize, //FuncID: 4
				_onTimeOut_GetRoleActInfo, //FuncID: 5
				_onTimeOut_GetRoleAllState, //FuncID: 6
				_onTimeOut_GetDragonBallAct, //FuncID: 7
				_onTimeOut_GetSevenConsumeAct, //FuncID: 8
				_onTimeOut_ExChange //FuncID: 9
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