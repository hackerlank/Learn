/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GameSvrBasic.as
//  Purpose:      GameServer的基本协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gameSvrBasic
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：GameServer的基本协议
	 */
	public class GameSvrBasic extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：心跳
		 */
		public function send_KeepAlive(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_KeepAlive = new SOrigParam_KeepAlive();
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
		//接收处理：GM指令结果返回
		private function _doRecv_GMCommandAck(bytes:ByteArray):void
		{
			var strResult:String = BytesUtil.readString(bytes); //指令结果
			var event_:REvt_GMCommandAck = new REvt_GMCommandAck(REvt_GMCommandAck.DATA_RECEIVE);
			event_.strResult = strResult;
			dispatchEvent(event_);
		}

		//接收处理：打开所有功能
		private function _doRecv_OpenAllSystem(bytes:ByteArray):void
		{
			var bOpen:Boolean = bytes.readBoolean(); //是否打开
			var event_:REvt_OpenAllSystem = new REvt_OpenAllSystem(REvt_OpenAllSystem.DATA_RECEIVE);
			event_.bOpen = bOpen;
			dispatchEvent(event_);
		}

		//接收处理：服务器断开连接通知
		private function _doRecv_ServerDisconnectNtf(bytes:ByteArray):void
		{
			var eBreakReason:uint = bytes.readUnsignedByte(); //(枚举类型：EBreakReason)断开连接原因
			var event_:REvt_ServerDisconnectNtf = new REvt_ServerDisconnectNtf(REvt_ServerDisconnectNtf.DATA_RECEIVE);
			event_.eBreakReason = eBreakReason;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：心跳
		private function _doReturn_KeepAlive(bytes:ByteArray):void
		{
			var retParam_:SRetParam_KeepAlive = new SRetParam_KeepAlive();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwServerTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)服务器的当前时间(1970年1月1日0时开始的秒数)
			retParam_.dwServerTime = dwServerTime;
			var origParam_:SOrigParam_KeepAlive = _sessionMgr.getData(sessionID_) as SOrigParam_KeepAlive;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_KeepAlive = new TEvt_KeepAlive(TEvt_KeepAlive.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：心跳
		private function _onTimeOut_KeepAlive(sessionID:uint):void
		{
			var retParam:SRetParam_KeepAlive = new SRetParam_KeepAlive();
			var event_:TEvt_KeepAlive = new TEvt_KeepAlive(TEvt_KeepAlive.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GameSvrBasic;

		public static function get instance():GameSvrBasic
		{
			if(_instance == null)
				_instance = new GameSvrBasic();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GameSvrBasic()
		{
			_protID = 13;
			_recvFuncList = [
				_doRecv_GMCommandAck, //FuncID: 1
				_doRecv_OpenAllSystem, //FuncID: 2
				_doRecv_ServerDisconnectNtf //FuncID: 3
			];

			_retFuncList = [
				_doReturn_KeepAlive //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_KeepAlive //FuncID: 1
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