/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GatherProt.as
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
{
	import flash.utils.ByteArray;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：采集协议
	 */
	public class GatherProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：采集请求
		 * @param dwGatherId (无符号32位整数)采集ID
		 */
		public function send_GatherReq(dwGatherId:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GatherReq = new SOrigParam_GatherReq();
			origParam_.dwGatherId = dwGatherId;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwGatherId);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：取消采集
		 */
		public function send_CancelGather(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_CancelGather = new SOrigParam_CancelGather();
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
		 * 发送：客户端查询采集信息
		 */
		public function send_GetGatherInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetGatherInfo = new SOrigParam_GetGatherInfo();
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
		//接收处理：采集结束通知
		private function _doRecv_GatherEndNotify(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGatherResult)服务器返回结果
			var event_:REvt_GatherEndNotify = new REvt_GatherEndNotify(REvt_GatherEndNotify.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：采集请求
		private function _doReturn_GatherReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GatherReq = new SRetParam_GatherReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGatherResult)采集结果
			var dwGatherTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)采集剩余时间
			retParam_.eResult = eResult;
			retParam_.dwGatherTimer = dwGatherTimer;
			var origParam_:SOrigParam_GatherReq = _sessionMgr.getData(sessionID_) as SOrigParam_GatherReq;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_GatherReq = new TEvt_GatherReq(TEvt_GatherReq.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：采集请求
		private function _onTimeOut_GatherReq(sessionID:uint):void
		{
			var retParam:SRetParam_GatherReq = new SRetParam_GatherReq();
			var origParam:SOrigParam_GatherReq = _sessionMgr.getData(sessionID) as SOrigParam_GatherReq;
			var event_:TEvt_GatherReq = new TEvt_GatherReq(TEvt_GatherReq.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取消采集
		private function _doReturn_CancelGather(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CancelGather = new SRetParam_CancelGather();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGatherResult)取消采集结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CancelGather = _sessionMgr.getData(sessionID_) as SOrigParam_CancelGather;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CancelGather = new TEvt_CancelGather(TEvt_CancelGather.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取消采集
		private function _onTimeOut_CancelGather(sessionID:uint):void
		{
			var retParam:SRetParam_CancelGather = new SRetParam_CancelGather();
			var event_:TEvt_CancelGather = new TEvt_CancelGather(TEvt_CancelGather.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：客户端查询采集信息
		private function _doReturn_GetGatherInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGatherInfo = new SRetParam_GetGatherInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwGtatherId:uint = bytes.readUnsignedInt(); //(无符号32位整数)采集实例
			var dwReserverTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)剩余时间
			retParam_.dwGtatherId = dwGtatherId;
			retParam_.dwReserverTimer = dwReserverTimer;
			var origParam_:SOrigParam_GetGatherInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGatherInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGatherInfo = new TEvt_GetGatherInfo(TEvt_GetGatherInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：客户端查询采集信息
		private function _onTimeOut_GetGatherInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGatherInfo = new SRetParam_GetGatherInfo();
			var event_:TEvt_GetGatherInfo = new TEvt_GetGatherInfo(TEvt_GetGatherInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GatherProt;

		public static function get instance():GatherProt
		{
			if(_instance == null)
				_instance = new GatherProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GatherProt()
		{
			_protID = 60;
			_recvFuncList = [
				_doRecv_GatherEndNotify //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GatherReq, //FuncID: 1
				_doReturn_CancelGather, //FuncID: 2
				_doReturn_GetGatherInfo //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GatherReq, //FuncID: 1
				_onTimeOut_CancelGather, //FuncID: 2
				_onTimeOut_GetGatherInfo //FuncID: 3
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