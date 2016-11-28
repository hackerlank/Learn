/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    LoginPkgProt.as
//  Purpose:      累计登入礼包协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.loginPkgProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：累计登入礼包协议
	 */
	public class LoginPkgProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取礼包
		 * @param byIndex (无符号8位整数)累计天数
		 */
		public function send_GetLoginPkg(byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetLoginPkg = new SOrigParam_GetLoginPkg();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：登入礼包信息
		 */
		public function send_GetPkgInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetPkgInfo = new SOrigParam_GetPkgInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：登入礼包信息
		private function _doRecv_SendPkgInfo(bytes:ByteArray):void
		{
			var wDays:uint = bytes.readUnsignedShort(); //(无符号16位整数)连续登入的天数
			var wResult:uint = bytes.readUnsignedShort(); //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
			var event_:REvt_SendPkgInfo = new REvt_SendPkgInfo(REvt_SendPkgInfo.DATA_RECEIVE);
			event_.wDays = wDays;
			event_.wResult = wResult;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取礼包
		private function _doReturn_GetLoginPkg(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetLoginPkg = new SRetParam_GetLoginPkg();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wResult:uint = bytes.readUnsignedShort(); //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EResultInLoginProt)操作结果
			retParam_.wResult = wResult;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetLoginPkg = _sessionMgr.getData(sessionID_) as SOrigParam_GetLoginPkg;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetLoginPkg = new TEvt_GetLoginPkg(TEvt_GetLoginPkg.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取礼包
		private function _onTimeOut_GetLoginPkg(sessionID:uint):void
		{
			var retParam:SRetParam_GetLoginPkg = new SRetParam_GetLoginPkg();
			var event_:TEvt_GetLoginPkg = new TEvt_GetLoginPkg(TEvt_GetLoginPkg.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：登入礼包信息
		private function _doReturn_GetPkgInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPkgInfo = new SRetParam_GetPkgInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wDays:uint = bytes.readUnsignedShort(); //(无符号16位整数)连续登入的天数
			var wResult:uint = bytes.readUnsignedShort(); //(无符号16位整数)操作结果:从地位向高位，1表示领取，0表示没有领
			retParam_.wDays = wDays;
			retParam_.wResult = wResult;
			var origParam_:SOrigParam_GetPkgInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPkgInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPkgInfo = new TEvt_GetPkgInfo(TEvt_GetPkgInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：登入礼包信息
		private function _onTimeOut_GetPkgInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPkgInfo = new SRetParam_GetPkgInfo();
			var event_:TEvt_GetPkgInfo = new TEvt_GetPkgInfo(TEvt_GetPkgInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:LoginPkgProt;

		public static function get instance():LoginPkgProt
		{
			if(_instance == null)
				_instance = new LoginPkgProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function LoginPkgProt()
		{
			_protID = 92;
			_recvFuncList = [
				_doRecv_SendPkgInfo //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GetLoginPkg, //FuncID: 1
				_doReturn_GetPkgInfo //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GetLoginPkg, //FuncID: 1
				_onTimeOut_GetPkgInfo //FuncID: 2
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