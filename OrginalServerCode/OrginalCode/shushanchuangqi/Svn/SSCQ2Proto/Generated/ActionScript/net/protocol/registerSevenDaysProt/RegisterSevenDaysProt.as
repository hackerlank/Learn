/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    RegisterSevenDaysProt.as
//  Purpose:      注册七天目标协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：注册七天目标协议
	 */
	public class RegisterSevenDaysProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求当天目标信息
		 */
		public function send_GetCurTargetInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetCurTargetInfo = new SOrigParam_GetCurTargetInfo();
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
		 * 发送：通过dwDayID获取目标信息
		 * @param dwDayID (无符号32位整数)第几天
		 */
		public function send_GetTargetInfoByDayID(dwDayID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetTargetInfoByDayID = new SOrigParam_GetTargetInfoByDayID();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwDayID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取奖励
		 * @param dwDayID (无符号32位整数)第几天
		 * @param byTargetID (无符号8位整数)目标ID
		 */
		public function send_GetAward(dwDayID:uint, byTargetID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetAward = new SOrigParam_GetAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwDayID);
			bytes_.writeByte(byTargetID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求当天购买信息
		 */
		public function send_GetCurBuyInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GetCurBuyInfo = new SOrigParam_GetCurBuyInfo();
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
		 * 发送：请求购买
		 */
		public function send_ReqBuy(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ReqBuy = new SOrigParam_ReqBuy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：请求当天目标信息
		private function _doReturn_GetCurTargetInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetCurTargetInfo = new SRetParam_GetCurTargetInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwDayID:uint = bytes.readUnsignedInt(); //(无符号32位整数)第几天
			var qwTargetInfo:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)
			retParam_.dwDayID = dwDayID;
			retParam_.qwTargetInfo = qwTargetInfo;
			var origParam_:SOrigParam_GetCurTargetInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetCurTargetInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetCurTargetInfo = new TEvt_GetCurTargetInfo(TEvt_GetCurTargetInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求当天目标信息
		private function _onTimeOut_GetCurTargetInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetCurTargetInfo = new SRetParam_GetCurTargetInfo();
			var event_:TEvt_GetCurTargetInfo = new TEvt_GetCurTargetInfo(TEvt_GetCurTargetInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：通过dwDayID获取目标信息
		private function _doReturn_GetTargetInfoByDayID(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTargetInfoByDayID = new SRetParam_GetTargetInfoByDayID();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var qwTargetInfo:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)
			retParam_.qwTargetInfo = qwTargetInfo;
			var origParam_:SOrigParam_GetTargetInfoByDayID = _sessionMgr.getData(sessionID_) as SOrigParam_GetTargetInfoByDayID;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTargetInfoByDayID = new TEvt_GetTargetInfoByDayID(TEvt_GetTargetInfoByDayID.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：通过dwDayID获取目标信息
		private function _onTimeOut_GetTargetInfoByDayID(sessionID:uint):void
		{
			var retParam:SRetParam_GetTargetInfoByDayID = new SRetParam_GetTargetInfoByDayID();
			var event_:TEvt_GetTargetInfoByDayID = new TEvt_GetTargetInfoByDayID(TEvt_GetTargetInfoByDayID.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取奖励
		private function _doReturn_GetAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAward = new SRetParam_GetAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ERegisterSevenDaysResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAward = new TEvt_GetAward(TEvt_GetAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取奖励
		private function _onTimeOut_GetAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetAward = new SRetParam_GetAward();
			var event_:TEvt_GetAward = new TEvt_GetAward(TEvt_GetAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求当天购买信息
		private function _doReturn_GetCurBuyInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetCurBuyInfo = new SRetParam_GetCurBuyInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwDayID:uint = bytes.readUnsignedInt(); //(无符号32位整数)第几天
			var eBuyStatus:uint = bytes.readUnsignedByte(); //(枚举类型：EBuyStatus)购买状态
			retParam_.dwDayID = dwDayID;
			retParam_.eBuyStatus = eBuyStatus;
			var origParam_:SOrigParam_GetCurBuyInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetCurBuyInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetCurBuyInfo = new TEvt_GetCurBuyInfo(TEvt_GetCurBuyInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求当天购买信息
		private function _onTimeOut_GetCurBuyInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetCurBuyInfo = new SRetParam_GetCurBuyInfo();
			var event_:TEvt_GetCurBuyInfo = new TEvt_GetCurBuyInfo(TEvt_GetCurBuyInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求购买
		private function _doReturn_ReqBuy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqBuy = new SRetParam_ReqBuy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ERegisterSevenDaysResult)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ReqBuy = _sessionMgr.getData(sessionID_) as SOrigParam_ReqBuy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqBuy = new TEvt_ReqBuy(TEvt_ReqBuy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求购买
		private function _onTimeOut_ReqBuy(sessionID:uint):void
		{
			var retParam:SRetParam_ReqBuy = new SRetParam_ReqBuy();
			var event_:TEvt_ReqBuy = new TEvt_ReqBuy(TEvt_ReqBuy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:RegisterSevenDaysProt;

		public static function get instance():RegisterSevenDaysProt
		{
			if(_instance == null)
				_instance = new RegisterSevenDaysProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function RegisterSevenDaysProt()
		{
			_protID = 89;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetCurTargetInfo, //FuncID: 1
				_doReturn_GetTargetInfoByDayID, //FuncID: 2
				_doReturn_GetAward, //FuncID: 3
				_doReturn_GetCurBuyInfo, //FuncID: 4
				_doReturn_ReqBuy //FuncID: 5
			];

			_timeFuncList = [
				_onTimeOut_GetCurTargetInfo, //FuncID: 1
				_onTimeOut_GetTargetInfoByDayID, //FuncID: 2
				_onTimeOut_GetAward, //FuncID: 3
				_onTimeOut_GetCurBuyInfo, //FuncID: 4
				_onTimeOut_ReqBuy //FuncID: 5
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0
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