/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    CoinProt.as
//  Purpose:      888礼券协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.coinProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：888礼券协议
	 */
	public class CoinProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取礼包
		 * @param eType (枚举类型：protoCommon.EMoneyType)礼包类型
		 * @param dwMoney (无符号32位整数)数量
		 */
		public function send_GetCoinPacket(eType:uint, dwMoney:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetCoinPacket = new SOrigParam_GetCoinPacket();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			bytes_.writeUnsignedInt(dwMoney);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：获取礼包
		private function _doReturn_GetCoinPacket(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetCoinPacket = new SRetParam_GetCoinPacket();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EResultInCoinProt)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetCoinPacket = _sessionMgr.getData(sessionID_) as SOrigParam_GetCoinPacket;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetCoinPacket = new TEvt_GetCoinPacket(TEvt_GetCoinPacket.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取礼包
		private function _onTimeOut_GetCoinPacket(sessionID:uint):void
		{
			var retParam:SRetParam_GetCoinPacket = new SRetParam_GetCoinPacket();
			var event_:TEvt_GetCoinPacket = new TEvt_GetCoinPacket(TEvt_GetCoinPacket.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:CoinProt;

		public static function get instance():CoinProt
		{
			if(_instance == null)
				_instance = new CoinProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function CoinProt()
		{
			_protID = 91;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetCoinPacket //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_GetCoinPacket //FuncID: 1
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