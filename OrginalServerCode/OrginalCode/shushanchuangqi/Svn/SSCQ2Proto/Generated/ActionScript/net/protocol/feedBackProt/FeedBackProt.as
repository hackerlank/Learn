/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    FeedBackProt.as
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：消费回馈
	 */
	public class FeedBackProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取回馈列表
		 */
		public function send_GetFeedBackList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetFeedBackList = new SOrigParam_GetFeedBackList();
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
		 * 发送：购买折扣物品
		 * @param dwBuyID (无符号32位整数)购买id
		 * @param dwCount (无符号32位整数)购买id数量
		 */
		public function send_BuyDisCountItem(dwBuyID:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_BuyDisCountItem = new SOrigParam_BuyDisCountItem();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwBuyID);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取奖励
		 * @param dwActID (无符号32位整数)活动id
		 */
		public function send_TakeFeedBackPrize(dwActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_TakeFeedBackPrize = new SOrigParam_TakeFeedBackPrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwActID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：回馈信息更新
		private function _doRecv_FeedBackInfoNotify(bytes:ByteArray):void
		{
			var oFeedBackInfo:SFeedBackInfo = SFeedBackInfo.fromByteArray(bytes); //回馈信息
			var event_:REvt_FeedBackInfoNotify = new REvt_FeedBackInfoNotify(REvt_FeedBackInfoNotify.DATA_RECEIVE);
			event_.oFeedBackInfo = oFeedBackInfo;
			dispatchEvent(event_);
		}

		//接收处理：回馈活动过期
		private function _doRecv_FeedBackExpireNotify(bytes:ByteArray):void
		{
			var dwActID:uint = bytes.readUnsignedInt(); //(无符号32位整数)活动id
			var event_:REvt_FeedBackExpireNotify = new REvt_FeedBackExpireNotify(REvt_FeedBackExpireNotify.DATA_RECEIVE);
			event_.dwActID = dwActID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取回馈列表
		private function _doReturn_GetFeedBackList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFeedBackList = new SRetParam_GetFeedBackList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFeedBackInfo:Vector.<SFeedBackInfo> = SFeedBackInfo.vectorFromByteArray(bytes); //回馈信息列表
			var vecSBuyDiscountInfo:Vector.<SBuyDiscountInfo> = SBuyDiscountInfo.vectorFromByteArray(bytes); //折扣限购信息
			retParam_.vecFeedBackInfo = vecFeedBackInfo;
			retParam_.vecSBuyDiscountInfo = vecSBuyDiscountInfo;
			var origParam_:SOrigParam_GetFeedBackList = _sessionMgr.getData(sessionID_) as SOrigParam_GetFeedBackList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFeedBackList = new TEvt_GetFeedBackList(TEvt_GetFeedBackList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取回馈列表
		private function _onTimeOut_GetFeedBackList(sessionID:uint):void
		{
			var retParam:SRetParam_GetFeedBackList = new SRetParam_GetFeedBackList();
			var event_:TEvt_GetFeedBackList = new TEvt_GetFeedBackList(TEvt_GetFeedBackList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买折扣物品
		private function _doReturn_BuyDisCountItem(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyDisCountItem = new SRetParam_BuyDisCountItem();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EFeedBackRet)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_BuyDisCountItem = _sessionMgr.getData(sessionID_) as SOrigParam_BuyDisCountItem;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyDisCountItem = new TEvt_BuyDisCountItem(TEvt_BuyDisCountItem.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买折扣物品
		private function _onTimeOut_BuyDisCountItem(sessionID:uint):void
		{
			var retParam:SRetParam_BuyDisCountItem = new SRetParam_BuyDisCountItem();
			var event_:TEvt_BuyDisCountItem = new TEvt_BuyDisCountItem(TEvt_BuyDisCountItem.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取奖励
		private function _doReturn_TakeFeedBackPrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeFeedBackPrize = new SRetParam_TakeFeedBackPrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EFeedBackRet)结果
			var dwBuyCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)已购买次数（购买成功后返回次数）
			retParam_.eRet = eRet;
			retParam_.dwBuyCount = dwBuyCount;
			var origParam_:SOrigParam_TakeFeedBackPrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeFeedBackPrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeFeedBackPrize = new TEvt_TakeFeedBackPrize(TEvt_TakeFeedBackPrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取奖励
		private function _onTimeOut_TakeFeedBackPrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeFeedBackPrize = new SRetParam_TakeFeedBackPrize();
			var event_:TEvt_TakeFeedBackPrize = new TEvt_TakeFeedBackPrize(TEvt_TakeFeedBackPrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:FeedBackProt;

		public static function get instance():FeedBackProt
		{
			if(_instance == null)
				_instance = new FeedBackProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function FeedBackProt()
		{
			_protID = 144;
			_recvFuncList = [
				_doRecv_FeedBackInfoNotify, //FuncID: 1
				_doRecv_FeedBackExpireNotify //FuncID: 2
			];

			_retFuncList = [
				_doReturn_GetFeedBackList, //FuncID: 1
				_doReturn_BuyDisCountItem, //FuncID: 2
				_doReturn_TakeFeedBackPrize //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GetFeedBackList, //FuncID: 1
				_onTimeOut_BuyDisCountItem, //FuncID: 2
				_onTimeOut_TakeFeedBackPrize //FuncID: 3
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