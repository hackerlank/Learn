/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    NpcProt.as
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：NPC相关协议
	 */
	public class NpcProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：打开NPC对话界面请求
		 * @param qwCreatureID (无符号64位整数)当前NPC的生物ID
		 */
		public function send_NpcTalkReq(qwCreatureID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwCreatureID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：执行NPC对话脚本函数
		 * @param qwCreatureID (无符号64位整数)当前NPC的生物ID
		 * @param strFuncName 脚本函数名称
		 */
		public function send_ExecScriptFunc(qwCreatureID:BigInteger, strFuncName:String):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwCreatureID);
			BytesUtil.writeString(bytes_, strFuncName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：地图的NPC任务状态请求
		 * @param wMapID (无符号16位整数)地图ID
		 */
		public function send_NpcTaskStateReq(wMapID:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeShort(wMapID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：完成一任务对话
		 * @param qwCreatureID (无符号64位整数)当前NPC的生物ID
		 * @param wTaskID (无符号16位整数)对话的任务
		 */
		public function send_FinishTaskTalk(qwCreatureID:BigInteger, wTaskID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_FinishTaskTalk = new SOrigParam_FinishTaskTalk();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwCreatureID);
			bytes_.writeShort(wTaskID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：NPC对话通知
		private function _doRecv_NpcTalkNtf(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)NPC的生物ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETalkResult)对话结果
			var strContent:String = BytesUtil.readString(bytes); //对话内容
			var event_:REvt_NpcTalkNtf = new REvt_NpcTalkNtf(REvt_NpcTalkNtf.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.eResult = eResult;
			event_.strContent = strContent;
			dispatchEvent(event_);
		}

		//接收处理：NPC任务状态通知
		private function _doRecv_NpcTaskStateNtf(bytes:ByteArray):void
		{
			var rVecNpcTask:Vector.<SNpcTaskState> = SNpcTaskState.vectorFromByteArray(bytes); //NPC任务状态列表
			var event_:REvt_NpcTaskStateNtf = new REvt_NpcTaskStateNtf(REvt_NpcTaskStateNtf.DATA_RECEIVE);
			event_.rVecNpcTask = rVecNpcTask;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：完成一任务对话
		private function _doReturn_FinishTaskTalk(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FinishTaskTalk = new SRetParam_FinishTaskTalk();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var strContent:String = BytesUtil.readString(bytes); //对话内容
			retParam_.strContent = strContent;
			var origParam_:SOrigParam_FinishTaskTalk = _sessionMgr.getData(sessionID_) as SOrigParam_FinishTaskTalk;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FinishTaskTalk = new TEvt_FinishTaskTalk(TEvt_FinishTaskTalk.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：完成一任务对话
		private function _onTimeOut_FinishTaskTalk(sessionID:uint):void
		{
			var retParam:SRetParam_FinishTaskTalk = new SRetParam_FinishTaskTalk();
			var event_:TEvt_FinishTaskTalk = new TEvt_FinishTaskTalk(TEvt_FinishTaskTalk.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:NpcProt;

		public static function get instance():NpcProt
		{
			if(_instance == null)
				_instance = new NpcProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function NpcProt()
		{
			_protID = 14;
			_recvFuncList = [
				_doRecv_NpcTalkNtf, //FuncID: 1
				_doRecv_NpcTaskStateNtf //FuncID: 2
			];

			_retFuncList = [
				_doReturn_FinishTaskTalk //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_FinishTaskTalk //FuncID: 1
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