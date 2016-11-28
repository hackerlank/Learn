/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ActivityProt.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.utils.ByteArray;
	import net.protocol.roleInfoDefine.SActivityTaskInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：活力任务协议
	 */
	public class ActivityProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求获得奖池
		 */
		public function send_GetActivityPool(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetActivityPool = new SOrigParam_GetActivityPool();
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
		 * 发送：请求活力奖励
		 * @param stActivityGet 奖励Id
		 */
		public function send_GetActivityAward(stActivityGet:SActivityAward, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetActivityAward = new SOrigParam_GetActivityAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			stActivityGet.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取活力任务详情
		 */
		public function send_GetAllInfoActivity():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取成就分享信息
		 */
		public function send_GeShareList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GeShareList = new SOrigParam_GeShareList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取成就分享奖励
		 * @param dwActivityID (无符号32位整数)活跃度ID
		 */
		public function send_TakeSharePrize(dwActivityID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakeSharePrize = new SOrigParam_TakeSharePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwActivityID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：获取活力任务详情
		private function _doRecv_ReturnAllInfoActivity(bytes:ByteArray):void
		{
			var stActivityInfo:SActivityInfoForClient = SActivityInfoForClient.fromByteArray(bytes); //活力任务详情
			var event_:REvt_ReturnAllInfoActivity = new REvt_ReturnAllInfoActivity(REvt_ReturnAllInfoActivity.DATA_RECEIVE);
			event_.stActivityInfo = stActivityInfo;
			dispatchEvent(event_);
		}

		//接收处理：活力监测点更新
		private function _doRecv_UpdateActivityTask(bytes:ByteArray):void
		{
			var stActivityTask:SActivityTaskInfo = SActivityTaskInfo.fromByteArray(bytes); //活力监测点更新
			var dwTotolActivity:uint = bytes.readUnsignedInt(); //(无符号32位整数)活力总值
			var wActivity:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日活力值
			var event_:REvt_UpdateActivityTask = new REvt_UpdateActivityTask(REvt_UpdateActivityTask.DATA_RECEIVE);
			event_.stActivityTask = stActivityTask;
			event_.dwTotolActivity = dwTotolActivity;
			event_.wActivity = wActivity;
			dispatchEvent(event_);
		}

		//接收处理：活力总值更新
		private function _doRecv_UpdateActivityTotal(bytes:ByteArray):void
		{
			var dwTotolActivity:uint = bytes.readUnsignedInt(); //(无符号32位整数)活力总值
			var event_:REvt_UpdateActivityTotal = new REvt_UpdateActivityTotal(REvt_UpdateActivityTotal.DATA_RECEIVE);
			event_.dwTotolActivity = dwTotolActivity;
			dispatchEvent(event_);
		}

		//接收处理：成就分享通知
		private function _doRecv_ShareNotify(bytes:ByteArray):void
		{
			var oActivityShare:SActivityShare = SActivityShare.fromByteArray(bytes); //成就分享信息
			var event_:REvt_ShareNotify = new REvt_ShareNotify(REvt_ShareNotify.DATA_RECEIVE);
			event_.oActivityShare = oActivityShare;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求获得奖池
		private function _doReturn_GetActivityPool(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetActivityPool = new SRetParam_GetActivityPool();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EActivityResult)操作结果
			var dwTotolActivity:uint = bytes.readUnsignedInt(); //(无符号32位整数)活力总值
			retParam_.eResult = eResult;
			retParam_.dwTotolActivity = dwTotolActivity;
			var origParam_:SOrigParam_GetActivityPool = _sessionMgr.getData(sessionID_) as SOrigParam_GetActivityPool;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetActivityPool = new TEvt_GetActivityPool(TEvt_GetActivityPool.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求获得奖池
		private function _onTimeOut_GetActivityPool(sessionID:uint):void
		{
			var retParam:SRetParam_GetActivityPool = new SRetParam_GetActivityPool();
			var event_:TEvt_GetActivityPool = new TEvt_GetActivityPool(TEvt_GetActivityPool.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求活力奖励
		private function _doReturn_GetActivityAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetActivityAward = new SRetParam_GetActivityAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EActivityResult)操作结果
			var stActivityPost:SActivityAward = SActivityAward.fromByteArray(bytes); //奖励Id
			retParam_.eResult = eResult;
			retParam_.stActivityPost = stActivityPost;
			var origParam_:SOrigParam_GetActivityAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetActivityAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetActivityAward = new TEvt_GetActivityAward(TEvt_GetActivityAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求活力奖励
		private function _onTimeOut_GetActivityAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetActivityAward = new SRetParam_GetActivityAward();
			var event_:TEvt_GetActivityAward = new TEvt_GetActivityAward(TEvt_GetActivityAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取成就分享信息
		private function _doReturn_GeShareList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GeShareList = new SRetParam_GeShareList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecActivityShare:Vector.<SActivityShare> = SActivityShare.vectorFromByteArray(bytes); //成就分享信息
			retParam_.vecActivityShare = vecActivityShare;
			var origParam_:SOrigParam_GeShareList = _sessionMgr.getData(sessionID_) as SOrigParam_GeShareList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GeShareList = new TEvt_GeShareList(TEvt_GeShareList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取成就分享信息
		private function _onTimeOut_GeShareList(sessionID:uint):void
		{
			var retParam:SRetParam_GeShareList = new SRetParam_GeShareList();
			var event_:TEvt_GeShareList = new TEvt_GeShareList(TEvt_GeShareList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取成就分享奖励
		private function _doReturn_TakeSharePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeSharePrize = new SRetParam_TakeSharePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EActivityResult)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_TakeSharePrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeSharePrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeSharePrize = new TEvt_TakeSharePrize(TEvt_TakeSharePrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取成就分享奖励
		private function _onTimeOut_TakeSharePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeSharePrize = new SRetParam_TakeSharePrize();
			var event_:TEvt_TakeSharePrize = new TEvt_TakeSharePrize(TEvt_TakeSharePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ActivityProt;

		public static function get instance():ActivityProt
		{
			if(_instance == null)
				_instance = new ActivityProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ActivityProt()
		{
			_protID = 53;
			_recvFuncList = [
				_doRecv_ReturnAllInfoActivity, //FuncID: 1
				_doRecv_UpdateActivityTask, //FuncID: 2
				_doRecv_UpdateActivityTotal, //FuncID: 3
				_doRecv_ShareNotify //FuncID: 4
			];

			_retFuncList = [
				_doReturn_GetActivityPool, //FuncID: 1
				_doReturn_GetActivityAward, //FuncID: 2
				_doReturn_GeShareList, //FuncID: 3
				_doReturn_TakeSharePrize //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetActivityPool, //FuncID: 1
				_onTimeOut_GetActivityAward, //FuncID: 2
				_onTimeOut_GeShareList, //FuncID: 3
				_onTimeOut_TakeSharePrize //FuncID: 4
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