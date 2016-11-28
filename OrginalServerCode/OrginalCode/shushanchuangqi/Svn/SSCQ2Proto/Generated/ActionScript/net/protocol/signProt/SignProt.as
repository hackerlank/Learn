/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    SignProt.as
//  Purpose:      签到协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：签到协议
	 */
	public class SignProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求签到信息
		 */
		public function send_GetSignInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetSignInfo = new SOrigParam_GetSignInfo();
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
		 * 发送：请求签到
		 */
		public function send_DoSign(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_DoSign = new SOrigParam_DoSign();
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
		 * 发送：请求补签
		 * @param byDay (无符号8位整数)补签日期
		 */
		public function send_DoReSign(byDay:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_DoReSign = new SOrigParam_DoReSign();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byDay);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求领取奖励
		 * @param byId (无符号8位整数)奖励ID
		 */
		public function send_DoGetAward(byId:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_DoGetAward = new SOrigParam_DoGetAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byId);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：请求签到信息
		private function _doReturn_GetSignInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSignInfo = new SRetParam_GetSignInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwSignData:uint = bytes.readUnsignedInt(); //(无符号32位整数)按位计数，从右到左，一位表示1天，1表示该日已签到
			var byReSignTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)该月补签天数
			var dwAward:uint = bytes.readUnsignedInt(); //(无符号32位整数)签到奖励包获取状态
			retParam_.dwSignData = dwSignData;
			retParam_.byReSignTimes = byReSignTimes;
			retParam_.dwAward = dwAward;
			var origParam_:SOrigParam_GetSignInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetSignInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSignInfo = new TEvt_GetSignInfo(TEvt_GetSignInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求签到信息
		private function _onTimeOut_GetSignInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetSignInfo = new SRetParam_GetSignInfo();
			var event_:TEvt_GetSignInfo = new TEvt_GetSignInfo(TEvt_GetSignInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求签到
		private function _doReturn_DoSign(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoSign = new SRetParam_DoSign();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESignResult)处理结果
			var dwSignData:uint = bytes.readUnsignedInt(); //(无符号32位整数)按位计数，从右到左，一位表示1天，1表示该日已签到
			retParam_.eResult = eResult;
			retParam_.dwSignData = dwSignData;
			var origParam_:SOrigParam_DoSign = _sessionMgr.getData(sessionID_) as SOrigParam_DoSign;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoSign = new TEvt_DoSign(TEvt_DoSign.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求签到
		private function _onTimeOut_DoSign(sessionID:uint):void
		{
			var retParam:SRetParam_DoSign = new SRetParam_DoSign();
			var event_:TEvt_DoSign = new TEvt_DoSign(TEvt_DoSign.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求补签
		private function _doReturn_DoReSign(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoReSign = new SRetParam_DoReSign();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESignResult)处理结果
			var dwSignData:uint = bytes.readUnsignedInt(); //(无符号32位整数)按位计数，从右到左，一位表示1天，1表示该日已签到
			var byReSignTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)该月补签天数
			retParam_.eResult = eResult;
			retParam_.dwSignData = dwSignData;
			retParam_.byReSignTimes = byReSignTimes;
			var origParam_:SOrigParam_DoReSign = _sessionMgr.getData(sessionID_) as SOrigParam_DoReSign;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoReSign = new TEvt_DoReSign(TEvt_DoReSign.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求补签
		private function _onTimeOut_DoReSign(sessionID:uint):void
		{
			var retParam:SRetParam_DoReSign = new SRetParam_DoReSign();
			var event_:TEvt_DoReSign = new TEvt_DoReSign(TEvt_DoReSign.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求领取奖励
		private function _doReturn_DoGetAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoGetAward = new SRetParam_DoGetAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESignResult)处理结果
			var dwAward:uint = bytes.readUnsignedInt(); //(无符号32位整数)签到奖励包获取状态
			retParam_.eResult = eResult;
			retParam_.dwAward = dwAward;
			var origParam_:SOrigParam_DoGetAward = _sessionMgr.getData(sessionID_) as SOrigParam_DoGetAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoGetAward = new TEvt_DoGetAward(TEvt_DoGetAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求领取奖励
		private function _onTimeOut_DoGetAward(sessionID:uint):void
		{
			var retParam:SRetParam_DoGetAward = new SRetParam_DoGetAward();
			var event_:TEvt_DoGetAward = new TEvt_DoGetAward(TEvt_DoGetAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:SignProt;

		public static function get instance():SignProt
		{
			if(_instance == null)
				_instance = new SignProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function SignProt()
		{
			_protID = 83;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetSignInfo, //FuncID: 1
				_doReturn_DoSign, //FuncID: 2
				_doReturn_DoReSign, //FuncID: 3
				_doReturn_DoGetAward //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetSignInfo, //FuncID: 1
				_onTimeOut_DoSign, //FuncID: 2
				_onTimeOut_DoReSign, //FuncID: 3
				_onTimeOut_DoGetAward //FuncID: 4
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