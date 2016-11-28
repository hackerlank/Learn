/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    DayTarget.as
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：七日目标活动
	 */
	public class DayTarget extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取任务列表
		 */
		public function send_GetTaskList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetTaskList = new SOrigParam_GetTaskList();
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
		 * 发送：领取奖励
		 * @param wTaskID (无符号16位整数)任务ID
		 */
		public function send_TakePrize(wTaskID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
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

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：任务信息更新
		private function _doRecv_UpdateTaskList(bytes:ByteArray):void
		{
			var oDayTargetTask:SDayTargetTask = SDayTargetTask.fromByteArray(bytes); //任务信息
			var event_:REvt_UpdateTaskList = new REvt_UpdateTaskList(REvt_UpdateTaskList.DATA_RECEIVE);
			event_.oDayTargetTask = oDayTargetTask;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取任务列表
		private function _doReturn_GetTaskList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTaskList = new SRetParam_GetTaskList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecDayTargetTask:Vector.<SDayTargetTask> = SDayTargetTask.vectorFromByteArray(bytes); //任务列表
			retParam_.vecDayTargetTask = vecDayTargetTask;
			var origParam_:SOrigParam_GetTaskList = _sessionMgr.getData(sessionID_) as SOrigParam_GetTaskList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTaskList = new TEvt_GetTaskList(TEvt_GetTaskList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取任务列表
		private function _onTimeOut_GetTaskList(sessionID:uint):void
		{
			var retParam:SRetParam_GetTaskList = new SRetParam_GetTaskList();
			var event_:TEvt_GetTaskList = new TEvt_GetTaskList(TEvt_GetTaskList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取奖励
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EDayTargetRet)领奖结果
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

		//超时处理：领取奖励
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:DayTarget;

		public static function get instance():DayTarget
		{
			if(_instance == null)
				_instance = new DayTarget();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function DayTarget()
		{
			_protID = 125;
			_recvFuncList = [
				_doRecv_UpdateTaskList //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GetTaskList, //FuncID: 1
				_doReturn_TakePrize //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GetTaskList, //FuncID: 1
				_onTimeOut_TakePrize //FuncID: 2
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