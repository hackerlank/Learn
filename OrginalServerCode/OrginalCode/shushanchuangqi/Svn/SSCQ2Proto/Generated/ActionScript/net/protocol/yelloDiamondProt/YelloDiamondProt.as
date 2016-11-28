/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    YelloDiamondProt.as
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：QQ黄钻协议
	 */
	public class YelloDiamondProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取黄钻礼包
		 * @param eBagType (枚举类型：EBagType)礼包类型
		 * @param dLevel (无符号16位整数)玩家等级成长礼包
		 */
		public function send_GainYDBag(eBagType:uint, dLevel:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GainYDBag = new SOrigParam_GainYDBag();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eBagType);
			bytes_.writeShort(dLevel);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取黄钻礼包领取信息
		 */
		public function send_GetYDBagInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetYDBagInfo = new SOrigParam_GetYDBagInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：获取黄钻礼包
		private function _doReturn_GainYDBag(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GainYDBag = new SRetParam_GainYDBag();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eOpResult:uint = bytes.readUnsignedByte(); //(枚举类型：EOpResult)操作结果
			retParam_.eOpResult = eOpResult;
			var origParam_:SOrigParam_GainYDBag = _sessionMgr.getData(sessionID_) as SOrigParam_GainYDBag;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GainYDBag = new TEvt_GainYDBag(TEvt_GainYDBag.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取黄钻礼包
		private function _onTimeOut_GainYDBag(sessionID:uint):void
		{
			var retParam:SRetParam_GainYDBag = new SRetParam_GainYDBag();
			var event_:TEvt_GainYDBag = new TEvt_GainYDBag(TEvt_GainYDBag.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取黄钻礼包领取信息
		private function _doReturn_GetYDBagInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetYDBagInfo = new SRetParam_GetYDBagInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var ydInfo:SYDInfo = SYDInfo.fromByteArray(bytes); //黄钻信息
			retParam_.ydInfo = ydInfo;
			var origParam_:SOrigParam_GetYDBagInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetYDBagInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetYDBagInfo = new TEvt_GetYDBagInfo(TEvt_GetYDBagInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取黄钻礼包领取信息
		private function _onTimeOut_GetYDBagInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetYDBagInfo = new SRetParam_GetYDBagInfo();
			var event_:TEvt_GetYDBagInfo = new TEvt_GetYDBagInfo(TEvt_GetYDBagInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:YelloDiamondProt;

		public static function get instance():YelloDiamondProt
		{
			if(_instance == null)
				_instance = new YelloDiamondProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function YelloDiamondProt()
		{
			_protID = 200;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GainYDBag, //FuncID: 1
				_doReturn_GetYDBagInfo //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GainYDBag, //FuncID: 1
				_onTimeOut_GetYDBagInfo //FuncID: 2
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