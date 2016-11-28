/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    SittingProt.as
//  Purpose:      打坐协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.sittingProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.mapProt.SPlayerAppear;
	import net.protocol.itemProt.SResource;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：打坐协议
	 */
	public class SittingProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求双修
		 * @param qwOtherID (无符号64位整数)对方ID,0表示单修，非0表示双修
		 */
		public function send_DoSittingTogether(qwOtherID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_DoSittingTogether = new SOrigParam_DoSittingTogether();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwOtherID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求取消修炼
		 */
		public function send_CancelSitting():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：玩家打坐结算
		private function _doRecv_CancelSittingOffLine(bytes:ByteArray):void
		{
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,表示单修，1表示双修
			var vecRes:Vector.<SResource> = SResource.vectorFromByteArray(bytes); //获得的资源
			var dwSittingTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var event_:REvt_CancelSittingOffLine = new REvt_CancelSittingOffLine(REvt_CancelSittingOffLine.DATA_RECEIVE);
			event_.byType = byType;
			event_.vecRes = vecRes;
			event_.dwSittingTimer = dwSittingTimer;
			dispatchEvent(event_);
		}

		//接收处理：打坐状态变化
		private function _doRecv_UpdateSitting(bytes:ByteArray):void
		{
			var byState:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,表示结束打坐，1 ，开始打坐
			var vecOtherApear:Vector.<SPlayerAppear> = SPlayerAppear.vectorFromByteArray(bytes); //空表示单修，非空表示双修
			var dwSittingTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var event_:REvt_UpdateSitting = new REvt_UpdateSitting(REvt_UpdateSitting.DATA_RECEIVE);
			event_.byState = byState;
			event_.vecOtherApear = vecOtherApear;
			event_.dwSittingTimer = dwSittingTimer;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求双修
		private function _doReturn_DoSittingTogether(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoSittingTogether = new SRetParam_DoSittingTogether();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESittingResult)请求结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_DoSittingTogether = _sessionMgr.getData(sessionID_) as SOrigParam_DoSittingTogether;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoSittingTogether = new TEvt_DoSittingTogether(TEvt_DoSittingTogether.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求双修
		private function _onTimeOut_DoSittingTogether(sessionID:uint):void
		{
			var retParam:SRetParam_DoSittingTogether = new SRetParam_DoSittingTogether();
			var event_:TEvt_DoSittingTogether = new TEvt_DoSittingTogether(TEvt_DoSittingTogether.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:SittingProt;

		public static function get instance():SittingProt
		{
			if(_instance == null)
				_instance = new SittingProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function SittingProt()
		{
			_protID = 55;
			_recvFuncList = [
				_doRecv_CancelSittingOffLine, //FuncID: 1
				_doRecv_UpdateSitting //FuncID: 2
			];

			_retFuncList = [
				_doReturn_DoSittingTogether, //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_DoSittingTogether, //FuncID: 1
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