/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    MoneyTreeProt.as
//  Purpose:      摇钱树协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.moneyTreeProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：摇钱树协议
	 */
	public class MoneyTreeProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求摇钱树信息
		 */
		public function send_GetMoneyTreeInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetMoneyTreeInfo = new SOrigParam_GetMoneyTreeInfo();
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
		 * 发送：请求摇钱
		 */
		public function send_GetMoney(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetMoney = new SOrigParam_GetMoney();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：请求摇钱树信息
		private function _doReturn_GetMoneyTreeInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMoneyTreeInfo = new SRetParam_GetMoneyTreeInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var todayUseCount:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日使用次数
			retParam_.todayUseCount = todayUseCount;
			var origParam_:SOrigParam_GetMoneyTreeInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetMoneyTreeInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMoneyTreeInfo = new TEvt_GetMoneyTreeInfo(TEvt_GetMoneyTreeInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求摇钱树信息
		private function _onTimeOut_GetMoneyTreeInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetMoneyTreeInfo = new SRetParam_GetMoneyTreeInfo();
			var event_:TEvt_GetMoneyTreeInfo = new TEvt_GetMoneyTreeInfo(TEvt_GetMoneyTreeInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求摇钱
		private function _doReturn_GetMoney(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMoney = new SRetParam_GetMoney();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var todayUseCount:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日使用次数
			retParam_.todayUseCount = todayUseCount;
			var origParam_:SOrigParam_GetMoney = _sessionMgr.getData(sessionID_) as SOrigParam_GetMoney;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMoney = new TEvt_GetMoney(TEvt_GetMoney.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求摇钱
		private function _onTimeOut_GetMoney(sessionID:uint):void
		{
			var retParam:SRetParam_GetMoney = new SRetParam_GetMoney();
			var event_:TEvt_GetMoney = new TEvt_GetMoney(TEvt_GetMoney.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:MoneyTreeProt;

		public static function get instance():MoneyTreeProt
		{
			if(_instance == null)
				_instance = new MoneyTreeProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function MoneyTreeProt()
		{
			_protID = 88;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetMoneyTreeInfo, //FuncID: 1
				_doReturn_GetMoney //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GetMoneyTreeInfo, //FuncID: 1
				_onTimeOut_GetMoney //FuncID: 2
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