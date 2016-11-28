/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ExchangeShopProt.as
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：兑换商店
	 */
	public class ExchangeShopProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：兑换物品
		 * @param dwExchangeID (无符号32位整数)兑换id
		 * @param dwCount (无符号32位整数)兑换数量
		 */
		public function send_ExchangeItem(dwExchangeID:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_ExchangeItem = new SOrigParam_ExchangeItem();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwExchangeID);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：已兑换列表
		 */
		public function send_ExchangeItemList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_ExchangeItemList = new SOrigParam_ExchangeItemList();
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
		//接收处理：已兑换信息更新
		private function _doRecv_ExchangeItemUpdate(bytes:ByteArray):void
		{
			var oExchangeInfo:ExchangeInfo = ExchangeInfo.fromByteArray(bytes); //更新已兑换信息
			var event_:REvt_ExchangeItemUpdate = new REvt_ExchangeItemUpdate(REvt_ExchangeItemUpdate.DATA_RECEIVE);
			event_.oExchangeInfo = oExchangeInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：兑换物品
		private function _doReturn_ExchangeItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ExchangeItem = new SRetParam_ExchangeItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_ExchangeItem = _sessionMgr.getData(sessionID_) as SOrigParam_ExchangeItem;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ExchangeItem = new TEvt_ExchangeItem(TEvt_ExchangeItem.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：兑换物品
		private function _onTimeOut_ExchangeItem(sessionID:uint):void
		{
			var retParam:SRetParam_ExchangeItem = new SRetParam_ExchangeItem();
			var event_:TEvt_ExchangeItem = new TEvt_ExchangeItem(TEvt_ExchangeItem.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：已兑换列表
		private function _doReturn_ExchangeItemList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ExchangeItemList = new SRetParam_ExchangeItemList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecExchangeInfo:Vector.<ExchangeInfo> = ExchangeInfo.vectorFromByteArray(bytes); //已兑换列表
			retParam_.vecExchangeInfo = vecExchangeInfo;
			var origParam_:SOrigParam_ExchangeItemList = _sessionMgr.getData(sessionID_) as SOrigParam_ExchangeItemList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ExchangeItemList = new TEvt_ExchangeItemList(TEvt_ExchangeItemList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：已兑换列表
		private function _onTimeOut_ExchangeItemList(sessionID:uint):void
		{
			var retParam:SRetParam_ExchangeItemList = new SRetParam_ExchangeItemList();
			var event_:TEvt_ExchangeItemList = new TEvt_ExchangeItemList(TEvt_ExchangeItemList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ExchangeShopProt;

		public static function get instance():ExchangeShopProt
		{
			if(_instance == null)
				_instance = new ExchangeShopProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ExchangeShopProt()
		{
			_protID = 101;
			_recvFuncList = [
				_doRecv_ExchangeItemUpdate //FuncID: 1
			];

			_retFuncList = [
				_doReturn_ExchangeItem, //FuncID: 1
				_doReturn_ExchangeItemList //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_ExchangeItem, //FuncID: 1
				_onTimeOut_ExchangeItemList //FuncID: 2
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