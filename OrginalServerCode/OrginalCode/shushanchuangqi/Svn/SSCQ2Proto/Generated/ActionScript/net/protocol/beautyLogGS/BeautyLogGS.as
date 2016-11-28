/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    BeautyLogGS.as
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beautyLogGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：美女log
	 */
	public class BeautyLogGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取美女log信息
		 */
		public function send_GetBeautyLog(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetBeautyLog = new SOrigParam_GetBeautyLog();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：美女log添加
		private function _doRecv_AddBeautyLogNotify(bytes:ByteArray):void
		{
			var oAddBeautyLog:SBeautyLog = SBeautyLog.fromByteArray(bytes); //美女log信息
			var event_:REvt_AddBeautyLogNotify = new REvt_AddBeautyLogNotify(REvt_AddBeautyLogNotify.DATA_RECEIVE);
			event_.oAddBeautyLog = oAddBeautyLog;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取美女log信息
		private function _doReturn_GetBeautyLog(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBeautyLog = new SRetParam_GetBeautyLog();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBeautyLog:Vector.<SBeautyLog> = SBeautyLog.vectorFromByteArray(bytes); //美女log信息
			retParam_.vecBeautyLog = vecBeautyLog;
			var origParam_:SOrigParam_GetBeautyLog = _sessionMgr.getData(sessionID_) as SOrigParam_GetBeautyLog;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBeautyLog = new TEvt_GetBeautyLog(TEvt_GetBeautyLog.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取美女log信息
		private function _onTimeOut_GetBeautyLog(sessionID:uint):void
		{
			var retParam:SRetParam_GetBeautyLog = new SRetParam_GetBeautyLog();
			var event_:TEvt_GetBeautyLog = new TEvt_GetBeautyLog(TEvt_GetBeautyLog.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:BeautyLogGS;

		public static function get instance():BeautyLogGS
		{
			if(_instance == null)
				_instance = new BeautyLogGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function BeautyLogGS()
		{
			_protID = 133;
			_recvFuncList = [
				_doRecv_AddBeautyLogNotify //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GetBeautyLog //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_GetBeautyLog //FuncID: 1
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