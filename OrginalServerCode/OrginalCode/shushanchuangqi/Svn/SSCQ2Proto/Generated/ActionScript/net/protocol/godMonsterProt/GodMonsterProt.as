/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GodMonsterProt.as
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：天元神兽协议
	 */
	public class GodMonsterProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：打开活动面板
		 */
		public function send_OnEnter(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_OnEnter = new SOrigParam_OnEnter();
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
		 * 发送：喂养
		 * @param byType (无符号8位整数)0: 表示喂养一次，1: 表示一键喂养
		 */
		public function send_OnFeed(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_OnFeed = new SOrigParam_OnFeed();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领奖
		 * @param ePrizeType (枚举类型：EMonsterPrizeType)奖励类型
		 */
		public function send_TakePrize(ePrizeType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(ePrizeType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买限购礼包
		 * @param wIndex (无符号16位整数)礼包ID
		 * @param byCount (无符号8位整数)礼包数量
		 */
		public function send_BuyPkg(wIndex:uint, byCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BuyPkg = new SOrigParam_BuyPkg();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wIndex);
			bytes_.writeByte(byCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：表扬
		 * @param qwRoleID (无符号64位整数)玩家
		 */
		public function send_OnPraise(qwRoleID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：督促
		 * @param qwRoleID (无符号64位整数)玩家
		 */
		public function send_OnUrge(qwRoleID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：同步数据
		private function _doRecv_SyncClientInfo(bytes:ByteArray):void
		{
			var sInfo:SyncInfoToClient = SyncInfoToClient.fromByteArray(bytes); //客户端数据
			var event_:REvt_SyncClientInfo = new REvt_SyncClientInfo(REvt_SyncClientInfo.DATA_RECEIVE);
			event_.sInfo = sInfo;
			dispatchEvent(event_);
		}

		//接收处理：活动开始
		private function _doRecv_OnBegin(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_OnBegin = new REvt_OnBegin(REvt_OnBegin.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：活动结束
		private function _doRecv_OnEnd(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_OnEnd = new REvt_OnEnd(REvt_OnEnd.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：打开活动面板
		private function _doReturn_OnEnter(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OnEnter = new SRetParam_OnEnter();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sInfo:SyncInfoToClient = SyncInfoToClient.fromByteArray(bytes); //客户端数据
			retParam_.sInfo = sInfo;
			var origParam_:SOrigParam_OnEnter = _sessionMgr.getData(sessionID_) as SOrigParam_OnEnter;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OnEnter = new TEvt_OnEnter(TEvt_OnEnter.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：打开活动面板
		private function _onTimeOut_OnEnter(sessionID:uint):void
		{
			var retParam:SRetParam_OnEnter = new SRetParam_OnEnter();
			var event_:TEvt_OnEnter = new TEvt_OnEnter(TEvt_OnEnter.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：喂养
		private function _doReturn_OnFeed(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OnFeed = new SRetParam_OnFeed();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMonsterResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_OnFeed = _sessionMgr.getData(sessionID_) as SOrigParam_OnFeed;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OnFeed = new TEvt_OnFeed(TEvt_OnFeed.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：喂养
		private function _onTimeOut_OnFeed(sessionID:uint):void
		{
			var retParam:SRetParam_OnFeed = new SRetParam_OnFeed();
			var event_:TEvt_OnFeed = new TEvt_OnFeed(TEvt_OnFeed.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领奖
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMonsterResult)操作结果
			retParam_.eResult = eResult;
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

		//超时处理：领奖
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买限购礼包
		private function _doReturn_BuyPkg(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyPkg = new SRetParam_BuyPkg();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMonsterResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyPkg = _sessionMgr.getData(sessionID_) as SOrigParam_BuyPkg;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyPkg = new TEvt_BuyPkg(TEvt_BuyPkg.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买限购礼包
		private function _onTimeOut_BuyPkg(sessionID:uint):void
		{
			var retParam:SRetParam_BuyPkg = new SRetParam_BuyPkg();
			var event_:TEvt_BuyPkg = new TEvt_BuyPkg(TEvt_BuyPkg.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GodMonsterProt;

		public static function get instance():GodMonsterProt
		{
			if(_instance == null)
				_instance = new GodMonsterProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GodMonsterProt()
		{
			_protID = 96;
			_recvFuncList = [
				_doRecv_SyncClientInfo, //FuncID: 1
				_doRecv_OnBegin, //FuncID: 2
				_doRecv_OnEnd //FuncID: 3
			];

			_retFuncList = [
				_doReturn_OnEnter, //FuncID: 1
				_doReturn_OnFeed, //FuncID: 2
				_doReturn_TakePrize, //FuncID: 3
				_doReturn_BuyPkg, //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_OnEnter, //FuncID: 1
				_onTimeOut_OnFeed, //FuncID: 2
				_onTimeOut_TakePrize, //FuncID: 3
				_onTimeOut_BuyPkg, //FuncID: 4
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