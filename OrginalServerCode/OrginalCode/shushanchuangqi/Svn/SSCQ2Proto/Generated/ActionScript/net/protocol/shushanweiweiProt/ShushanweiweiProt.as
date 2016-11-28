/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ShushanweiweiProt.as
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：蜀山微微协议
	 */
	public class ShushanweiweiProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取礼包
		 * @param eType (枚举类型：EPkgType)活动类型
		 * @param wIndex (无符号16位整数)领奖类型：0表示个人奖励，1..16位 表示领取全服第几个奖励
		 * @param strCDK CDK
		 */
		public function send_TakePrize(eType:uint, wIndex:uint, strCDK:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			bytes_.writeShort(wIndex);
			BytesUtil.writeString(bytes_, strCDK);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得玩家奖励信息
		 */
		public function send_GetPrizeInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：收听微博
		 */
		public function send_ListenWeibo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_ListenWeibo = new SOrigParam_ListenWeibo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：同步玩家奖励信息
		private function _doRecv_SyncPrizeInfo(bytes:ByteArray):void
		{
			var vecResult:Vector.<SPrizeInfo> = SPrizeInfo.vectorFromByteArray(bytes); //奖励结果
			var event_:REvt_SyncPrizeInfo = new REvt_SyncPrizeInfo(REvt_SyncPrizeInfo.DATA_RECEIVE);
			event_.vecResult = vecResult;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取礼包
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRetType:uint = bytes.readUnsignedByte(); //(枚举类型：EPkgType)活动类型返回
			var wRetIndex:uint = bytes.readUnsignedShort(); //(无符号16位整数)领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EPkgResult)操作结果返回
			retParam_.eRetType = eRetType;
			retParam_.wRetIndex = wRetIndex;
			retParam_.eRet = eRet;
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

		//超时处理：获取礼包
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：收听微博
		private function _doReturn_ListenWeibo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ListenWeibo = new SRetParam_ListenWeibo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EPkgResult)操作结果返回
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_ListenWeibo = _sessionMgr.getData(sessionID_) as SOrigParam_ListenWeibo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ListenWeibo = new TEvt_ListenWeibo(TEvt_ListenWeibo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：收听微博
		private function _onTimeOut_ListenWeibo(sessionID:uint):void
		{
			var retParam:SRetParam_ListenWeibo = new SRetParam_ListenWeibo();
			var event_:TEvt_ListenWeibo = new TEvt_ListenWeibo(TEvt_ListenWeibo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ShushanweiweiProt;

		public static function get instance():ShushanweiweiProt
		{
			if(_instance == null)
				_instance = new ShushanweiweiProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ShushanweiweiProt()
		{
			_protID = 93;
			_recvFuncList = [
				_doRecv_SyncPrizeInfo //FuncID: 1
			];

			_retFuncList = [
				_doReturn_TakePrize, //FuncID: 1
				_doReturn_ListenWeibo //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_TakePrize, //FuncID: 1
				_onTimeOut_ListenWeibo //FuncID: 2
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