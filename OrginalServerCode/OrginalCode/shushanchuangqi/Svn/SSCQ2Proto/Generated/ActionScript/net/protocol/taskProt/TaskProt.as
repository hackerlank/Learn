/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    TaskProt.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：任务协议
	 */
	public class TaskProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：接受任务请求
		 * @param byCost (无符号8位整数)0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		 * @param wTaskID (无符号16位整数)任务ID
		 */
		public function send_AcceptTaskReq(byCost:uint, wTaskID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_AcceptTaskReq = new SOrigParam_AcceptTaskReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byCost);
			bytes_.writeShort(wTaskID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：放弃任务请求
		 * @param wTaskID (无符号16位整数)任务ID
		 */
		public function send_GiveUpTask(wTaskID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GiveUpTask = new SOrigParam_GiveUpTask();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wTaskID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：完成任务请求(领取奖励)
		 * @param byCost (无符号8位整数)0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		 * @param wTaskID (无符号16位整数)任务ID
		 * @param byIndex (无符号8位整数)可选择的奖励索引
		 */
		public function send_FinishTask(byCost:uint, wTaskID:uint, byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_FinishTask = new SOrigParam_FinishTask();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byCost);
			bytes_.writeShort(wTaskID);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：完成特殊任务请求
		 * @param wTaskID (无符号16位整数)任务ID
		 */
		public function send_FinishSpeTask(wTaskID:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeShort(wTaskID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得任务列表
		 */
		public function send_GetTaskList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得环任务信息
		 */
		public function send_GetCircleTaskInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：完成所有的环任务
		 */
		public function send_FinishCircleTaskOneKey(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_FinishCircleTaskOneKey = new SOrigParam_FinishCircleTaskOneKey();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：提升环任务星级
		 */
		public function send_UpdateCircleTaskStar(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_UpdateCircleTaskStar = new SOrigParam_UpdateCircleTaskStar();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：任务列表通知
		private function _doRecv_TaskListNtf(bytes:ByteArray):void
		{
			var vecTask:Vector.<STask> = STask.vectorFromByteArray(bytes); //任务列表
			var event_:REvt_TaskListNtf = new REvt_TaskListNtf(REvt_TaskListNtf.DATA_RECEIVE);
			event_.vecTask = vecTask;
			dispatchEvent(event_);
		}

		//接收处理：任务更新通知
		private function _doRecv_TaskUpdateNtf(bytes:ByteArray):void
		{
			var rTask:STask = STask.fromByteArray(bytes); //任务
			var event_:REvt_TaskUpdateNtf = new REvt_TaskUpdateNtf(REvt_TaskUpdateNtf.DATA_RECEIVE);
			event_.rTask = rTask;
			dispatchEvent(event_);
		}

		//接收处理：删除任务
		private function _doRecv_DelTaskAck(bytes:ByteArray):void
		{
			var wTaskID:uint = bytes.readUnsignedShort(); //(无符号16位整数)任务ID
			var event_:REvt_DelTaskAck = new REvt_DelTaskAck(REvt_DelTaskAck.DATA_RECEIVE);
			event_.wTaskID = wTaskID;
			dispatchEvent(event_);
		}

		//接收处理：添加任务
		private function _doRecv_AddTaskAck(bytes:ByteArray):void
		{
			var byCost:uint = bytes.readUnsignedByte(); //(无符号8位整数)立即完成
			var rTask:STask = STask.fromByteArray(bytes); //任务
			var event_:REvt_AddTaskAck = new REvt_AddTaskAck(REvt_AddTaskAck.DATA_RECEIVE);
			event_.byCost = byCost;
			event_.rTask = rTask;
			dispatchEvent(event_);
		}

		//接收处理：任务记录
		private function _doRecv_NotifyTaskRecordAck(bytes:ByteArray):void
		{
			var vecTaskID:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)任务完成记录
			var event_:REvt_NotifyTaskRecordAck = new REvt_NotifyTaskRecordAck(REvt_NotifyTaskRecordAck.DATA_RECEIVE);
			event_.vecTaskID = vecTaskID;
			dispatchEvent(event_);
		}

		//接收处理：通知播放剧情
		private function _doRecv_NotifyStory(bytes:ByteArray):void
		{
			var wStoryID:uint = bytes.readUnsignedShort(); //(无符号16位整数)剧情ID
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)参数类型
			var dwParam:uint = bytes.readUnsignedInt(); //(无符号32位整数)参数
			var event_:REvt_NotifyStory = new REvt_NotifyStory(REvt_NotifyStory.DATA_RECEIVE);
			event_.wStoryID = wStoryID;
			event_.byType = byType;
			event_.dwParam = dwParam;
			dispatchEvent(event_);
		}

		//接收处理：通知环任务信息
		private function _doRecv_SendCircleTaskInfo(bytes:ByteArray):void
		{
			var byStar:uint = bytes.readUnsignedByte(); //(无符号8位整数)环任务星级
			var byNum:uint = bytes.readUnsignedByte(); //(无符号8位整数)环任务环数
			var event_:REvt_SendCircleTaskInfo = new REvt_SendCircleTaskInfo(REvt_SendCircleTaskInfo.DATA_RECEIVE);
			event_.byStar = byStar;
			event_.byNum = byNum;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：接受任务请求
		private function _doReturn_AcceptTaskReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AcceptTaskReq = new SRetParam_AcceptTaskReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETaskResult)接受任务的结果
			var byCost:uint = bytes.readUnsignedByte(); //(无符号8位整数)参数回传
			var wTaskID:uint = bytes.readUnsignedShort(); //(无符号16位整数)任务ID
			retParam_.eResult = eResult;
			retParam_.byCost = byCost;
			retParam_.wTaskID = wTaskID;
			var origParam_:SOrigParam_AcceptTaskReq = _sessionMgr.getData(sessionID_) as SOrigParam_AcceptTaskReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AcceptTaskReq = new TEvt_AcceptTaskReq(TEvt_AcceptTaskReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：接受任务请求
		private function _onTimeOut_AcceptTaskReq(sessionID:uint):void
		{
			var retParam:SRetParam_AcceptTaskReq = new SRetParam_AcceptTaskReq();
			var event_:TEvt_AcceptTaskReq = new TEvt_AcceptTaskReq(TEvt_AcceptTaskReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：放弃任务请求
		private function _doReturn_GiveUpTask(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GiveUpTask = new SRetParam_GiveUpTask();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETaskResult)放弃任务的结果
			var wTaskID:uint = bytes.readUnsignedShort(); //(无符号16位整数)任务ID
			retParam_.eResult = eResult;
			retParam_.wTaskID = wTaskID;
			var origParam_:SOrigParam_GiveUpTask = _sessionMgr.getData(sessionID_) as SOrigParam_GiveUpTask;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GiveUpTask = new TEvt_GiveUpTask(TEvt_GiveUpTask.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：放弃任务请求
		private function _onTimeOut_GiveUpTask(sessionID:uint):void
		{
			var retParam:SRetParam_GiveUpTask = new SRetParam_GiveUpTask();
			var event_:TEvt_GiveUpTask = new TEvt_GiveUpTask(TEvt_GiveUpTask.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：完成任务请求(领取奖励)
		private function _doReturn_FinishTask(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FinishTask = new SRetParam_FinishTask();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETaskResult)完成任务的结果
			var byCost:uint = bytes.readUnsignedByte(); //(无符号8位整数)参数回传
			var wTaskID:uint = bytes.readUnsignedShort(); //(无符号16位整数)任务ID
			retParam_.eResult = eResult;
			retParam_.byCost = byCost;
			retParam_.wTaskID = wTaskID;
			var origParam_:SOrigParam_FinishTask = _sessionMgr.getData(sessionID_) as SOrigParam_FinishTask;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FinishTask = new TEvt_FinishTask(TEvt_FinishTask.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：完成任务请求(领取奖励)
		private function _onTimeOut_FinishTask(sessionID:uint):void
		{
			var retParam:SRetParam_FinishTask = new SRetParam_FinishTask();
			var event_:TEvt_FinishTask = new TEvt_FinishTask(TEvt_FinishTask.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：完成所有的环任务
		private function _doReturn_FinishCircleTaskOneKey(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FinishCircleTaskOneKey = new SRetParam_FinishCircleTaskOneKey();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETaskResult)完成任务的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FinishCircleTaskOneKey = _sessionMgr.getData(sessionID_) as SOrigParam_FinishCircleTaskOneKey;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FinishCircleTaskOneKey = new TEvt_FinishCircleTaskOneKey(TEvt_FinishCircleTaskOneKey.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：完成所有的环任务
		private function _onTimeOut_FinishCircleTaskOneKey(sessionID:uint):void
		{
			var retParam:SRetParam_FinishCircleTaskOneKey = new SRetParam_FinishCircleTaskOneKey();
			var event_:TEvt_FinishCircleTaskOneKey = new TEvt_FinishCircleTaskOneKey(TEvt_FinishCircleTaskOneKey.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：提升环任务星级
		private function _doReturn_UpdateCircleTaskStar(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpdateCircleTaskStar = new SRetParam_UpdateCircleTaskStar();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETaskResult)完成任务的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UpdateCircleTaskStar = _sessionMgr.getData(sessionID_) as SOrigParam_UpdateCircleTaskStar;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpdateCircleTaskStar = new TEvt_UpdateCircleTaskStar(TEvt_UpdateCircleTaskStar.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：提升环任务星级
		private function _onTimeOut_UpdateCircleTaskStar(sessionID:uint):void
		{
			var retParam:SRetParam_UpdateCircleTaskStar = new SRetParam_UpdateCircleTaskStar();
			var event_:TEvt_UpdateCircleTaskStar = new TEvt_UpdateCircleTaskStar(TEvt_UpdateCircleTaskStar.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:TaskProt;

		public static function get instance():TaskProt
		{
			if(_instance == null)
				_instance = new TaskProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function TaskProt()
		{
			_protID = 15;
			_recvFuncList = [
				_doRecv_TaskListNtf, //FuncID: 1
				_doRecv_TaskUpdateNtf, //FuncID: 2
				_doRecv_DelTaskAck, //FuncID: 3
				_doRecv_AddTaskAck, //FuncID: 4
				_doRecv_NotifyTaskRecordAck, //FuncID: 5
				_doRecv_NotifyStory, //FuncID: 6
				_doRecv_SendCircleTaskInfo //FuncID: 7
			];

			_retFuncList = [
				_doReturn_AcceptTaskReq, //FuncID: 1
				_doReturn_GiveUpTask, //FuncID: 2
				_doReturn_FinishTask, //FuncID: 3
				_doReturn_FinishCircleTaskOneKey, //FuncID: 4
				_doReturn_UpdateCircleTaskStar //FuncID: 5
			];

			_timeFuncList = [
				_onTimeOut_AcceptTaskReq, //FuncID: 1
				_onTimeOut_GiveUpTask, //FuncID: 2
				_onTimeOut_FinishTask, //FuncID: 3
				_onTimeOut_FinishCircleTaskOneKey, //FuncID: 4
				_onTimeOut_UpdateCircleTaskStar //FuncID: 5
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