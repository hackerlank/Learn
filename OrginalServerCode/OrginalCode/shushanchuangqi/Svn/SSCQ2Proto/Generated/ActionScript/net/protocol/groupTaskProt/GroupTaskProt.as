/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GroupTaskProt.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：师门任务协议
	 */
	public class GroupTaskProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求操作
		 */
		public function send_GroupTaskOp(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GroupTaskOp = new SOrigParam_GroupTaskOp();
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
		 * 发送：刷新师门任务列表
		 */
		public function send_FlushTask(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_FlushTask = new SOrigParam_FlushTask();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取师门任务详情
		 */
		public function send_GetAllInfoTask():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买师门任务
		 */
		public function send_BuyTaskTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_BuyTaskTimes = new SOrigParam_BuyTaskTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：获取师门任务详情
		private function _doRecv_ReturnAllInfoTask(bytes:ByteArray):void
		{
			var stGroupTaskInfo:SGroupTaskInfoForClient = SGroupTaskInfoForClient.fromByteArray(bytes); //师门任务详情
			var event_:REvt_ReturnAllInfoTask = new REvt_ReturnAllInfoTask(REvt_ReturnAllInfoTask.DATA_RECEIVE);
			event_.stGroupTaskInfo = stGroupTaskInfo;
			dispatchEvent(event_);
		}

		//接收处理：任务列表更新
		private function _doRecv_UpdateGroupTask(bytes:ByteArray):void
		{
			var stTask:SGroupTask = SGroupTask.fromByteArray(bytes); //师门任务详情
			var event_:REvt_UpdateGroupTask = new REvt_UpdateGroupTask(REvt_UpdateGroupTask.DATA_RECEIVE);
			event_.stTask = stTask;
			dispatchEvent(event_);
		}

		//接收处理：完成任务数更新
		private function _doRecv_UpdateFinishTask(bytes:ByteArray):void
		{
			var byFinishTask:uint = bytes.readUnsignedByte(); //(无符号8位整数)今日完成的师门任务数
			var byAcceptTaskTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)剩余可接任务数
			var byVIPTaskTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)购买的可接任务数
			var byBuyTimesToday:uint = bytes.readUnsignedByte(); //(无符号8位整数)今日购买的任务数
			var event_:REvt_UpdateFinishTask = new REvt_UpdateFinishTask(REvt_UpdateFinishTask.DATA_RECEIVE);
			event_.byFinishTask = byFinishTask;
			event_.byAcceptTaskTimes = byAcceptTaskTimes;
			event_.byVIPTaskTimes = byVIPTaskTimes;
			event_.byBuyTimesToday = byBuyTimesToday;
			dispatchEvent(event_);
		}

		//接收处理：更新清修状态
		private function _doRecv_UpdateStudyState(bytes:ByteArray):void
		{
			var eStudyState:uint = bytes.readUnsignedByte(); //(枚举类型：EGroupStudyState)清修状态
			var event_:REvt_UpdateStudyState = new REvt_UpdateStudyState(REvt_UpdateStudyState.DATA_RECEIVE);
			event_.eStudyState = eStudyState;
			dispatchEvent(event_);
		}

		//接收处理：更新声望等级
		private function _doRecv_UpdateGroupReputeLevel(bytes:ByteArray):void
		{
			var dwGroupLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)声望等级
			var event_:REvt_UpdateGroupReputeLevel = new REvt_UpdateGroupReputeLevel(REvt_UpdateGroupReputeLevel.DATA_RECEIVE);
			event_.dwGroupLevel = dwGroupLevel;
			dispatchEvent(event_);
		}

		//接收处理：更新声望
		private function _doRecv_UpdateGroupRepute(bytes:ByteArray):void
		{
			var dwGroupRepute:uint = bytes.readUnsignedInt(); //(无符号32位整数)声望
			var event_:REvt_UpdateGroupRepute = new REvt_UpdateGroupRepute(REvt_UpdateGroupRepute.DATA_RECEIVE);
			event_.dwGroupRepute = dwGroupRepute;
			dispatchEvent(event_);
		}

		//接收处理：更新今日清修领奖次数
		private function _doRecv_UpdateStudyAward(bytes:ByteArray):void
		{
			var byStudyAward:uint = bytes.readUnsignedByte(); //(无符号8位整数)今日领取的清修次数
			var event_:REvt_UpdateStudyAward = new REvt_UpdateStudyAward(REvt_UpdateStudyAward.DATA_RECEIVE);
			event_.byStudyAward = byStudyAward;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求操作
		private function _doReturn_GroupTaskOp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GroupTaskOp = new SRetParam_GroupTaskOp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGroupTaskResult)操作结果
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：EGroupStudyState)当前清修状态
			retParam_.eResult = eResult;
			retParam_.eState = eState;
			var origParam_:SOrigParam_GroupTaskOp = _sessionMgr.getData(sessionID_) as SOrigParam_GroupTaskOp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GroupTaskOp = new TEvt_GroupTaskOp(TEvt_GroupTaskOp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求操作
		private function _onTimeOut_GroupTaskOp(sessionID:uint):void
		{
			var retParam:SRetParam_GroupTaskOp = new SRetParam_GroupTaskOp();
			var event_:TEvt_GroupTaskOp = new TEvt_GroupTaskOp(TEvt_GroupTaskOp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：刷新师门任务列表
		private function _doReturn_FlushTask(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FlushTask = new SRetParam_FlushTask();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGroupTaskResult)操作结果
			var vecTask:Vector.<SGroupTask> = SGroupTask.vectorFromByteArray(bytes); //推的任务列表
			var byFlushTask:uint = bytes.readUnsignedByte(); //(无符号8位整数)今日刷新任务列表次数
			retParam_.eResult = eResult;
			retParam_.vecTask = vecTask;
			retParam_.byFlushTask = byFlushTask;
			var origParam_:SOrigParam_FlushTask = _sessionMgr.getData(sessionID_) as SOrigParam_FlushTask;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FlushTask = new TEvt_FlushTask(TEvt_FlushTask.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：刷新师门任务列表
		private function _onTimeOut_FlushTask(sessionID:uint):void
		{
			var retParam:SRetParam_FlushTask = new SRetParam_FlushTask();
			var event_:TEvt_FlushTask = new TEvt_FlushTask(TEvt_FlushTask.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买师门任务
		private function _doReturn_BuyTaskTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyTaskTimes = new SRetParam_BuyTaskTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGroupTaskResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyTaskTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyTaskTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyTaskTimes = new TEvt_BuyTaskTimes(TEvt_BuyTaskTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买师门任务
		private function _onTimeOut_BuyTaskTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyTaskTimes = new SRetParam_BuyTaskTimes();
			var event_:TEvt_BuyTaskTimes = new TEvt_BuyTaskTimes(TEvt_BuyTaskTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GroupTaskProt;

		public static function get instance():GroupTaskProt
		{
			if(_instance == null)
				_instance = new GroupTaskProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GroupTaskProt()
		{
			_protID = 51;
			_recvFuncList = [
				_doRecv_ReturnAllInfoTask, //FuncID: 1
				_doRecv_UpdateGroupTask, //FuncID: 2
				_doRecv_UpdateFinishTask, //FuncID: 3
				_doRecv_UpdateStudyState, //FuncID: 4
				_doRecv_UpdateGroupReputeLevel, //FuncID: 5
				_doRecv_UpdateGroupRepute, //FuncID: 6
				_doRecv_UpdateStudyAward //FuncID: 7
			];

			_retFuncList = [
				_doReturn_GroupTaskOp, //FuncID: 1
				_doReturn_FlushTask, //FuncID: 2
				_doReturn_BuyTaskTimes //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GroupTaskOp, //FuncID: 1
				_onTimeOut_FlushTask, //FuncID: 2
				_onTimeOut_BuyTaskTimes //FuncID: 3
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