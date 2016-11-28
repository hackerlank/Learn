/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    InviteGS.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：邀请好友相关协议
	 */
	public class InviteGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取被邀请好友列表
		 */
		public function send_GetInvitedFriendList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetInvitedFriendList = new SOrigParam_GetInvitedFriendList();
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
		 * 发送：邀请任务列表
		 */
		public function send_GetInvitedTaskList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetInvitedTaskList = new SOrigParam_GetInvitedTaskList();
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
		 * 发送：每日邀请好友数量
		 */
		public function send_GetDayInvitedFriends(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetDayInvitedFriends = new SOrigParam_GetDayInvitedFriends();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取奖励
		 * @param dwPrizeID (无符号32位整数)领奖任务ID
		 */
		public function send_TakeTaskPrize(dwPrizeID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakeTaskPrize = new SOrigParam_TakeTaskPrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwPrizeID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：被邀请好友信息更新
		private function _doRecv_UpdateInvitedFriend(bytes:ByteArray):void
		{
			var oInvitedFriend:SInvitedFriend = SInvitedFriend.fromByteArray(bytes); //查询返回
			var event_:REvt_UpdateInvitedFriend = new REvt_UpdateInvitedFriend(REvt_UpdateInvitedFriend.DATA_RECEIVE);
			event_.oInvitedFriend = oInvitedFriend;
			dispatchEvent(event_);
		}

		//接收处理：被邀请任务信息更新
		private function _doRecv_UpdateInvitedTask(bytes:ByteArray):void
		{
			var oInvitedTask:SInvitedTask = SInvitedTask.fromByteArray(bytes); //被邀请任务信息
			var event_:REvt_UpdateInvitedTask = new REvt_UpdateInvitedTask(REvt_UpdateInvitedTask.DATA_RECEIVE);
			event_.oInvitedTask = oInvitedTask;
			dispatchEvent(event_);
		}

		//接收处理：每日邀请好友数量
		private function _doRecv_UpdateDayInvitedFriends(bytes:ByteArray):void
		{
			var dwInviteCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)邀请数量
			var event_:REvt_UpdateDayInvitedFriends = new REvt_UpdateDayInvitedFriends(REvt_UpdateDayInvitedFriends.DATA_RECEIVE);
			event_.dwInviteCnt = dwInviteCnt;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取被邀请好友列表
		private function _doReturn_GetInvitedFriendList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetInvitedFriendList = new SRetParam_GetInvitedFriendList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecInvitedFriend:Vector.<SInvitedFriend> = SInvitedFriend.vectorFromByteArray(bytes); //被邀请好友列表
			retParam_.vecInvitedFriend = vecInvitedFriend;
			var origParam_:SOrigParam_GetInvitedFriendList = _sessionMgr.getData(sessionID_) as SOrigParam_GetInvitedFriendList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetInvitedFriendList = new TEvt_GetInvitedFriendList(TEvt_GetInvitedFriendList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取被邀请好友列表
		private function _onTimeOut_GetInvitedFriendList(sessionID:uint):void
		{
			var retParam:SRetParam_GetInvitedFriendList = new SRetParam_GetInvitedFriendList();
			var event_:TEvt_GetInvitedFriendList = new TEvt_GetInvitedFriendList(TEvt_GetInvitedFriendList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：邀请任务列表
		private function _doReturn_GetInvitedTaskList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetInvitedTaskList = new SRetParam_GetInvitedTaskList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecInvitedTask:Vector.<SInvitedTask> = SInvitedTask.vectorFromByteArray(bytes); //邀请任务状态信息
			retParam_.vecInvitedTask = vecInvitedTask;
			var origParam_:SOrigParam_GetInvitedTaskList = _sessionMgr.getData(sessionID_) as SOrigParam_GetInvitedTaskList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetInvitedTaskList = new TEvt_GetInvitedTaskList(TEvt_GetInvitedTaskList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：邀请任务列表
		private function _onTimeOut_GetInvitedTaskList(sessionID:uint):void
		{
			var retParam:SRetParam_GetInvitedTaskList = new SRetParam_GetInvitedTaskList();
			var event_:TEvt_GetInvitedTaskList = new TEvt_GetInvitedTaskList(TEvt_GetInvitedTaskList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：每日邀请好友数量
		private function _doReturn_GetDayInvitedFriends(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDayInvitedFriends = new SRetParam_GetDayInvitedFriends();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwInviteCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)邀请数量
			retParam_.dwInviteCnt = dwInviteCnt;
			var origParam_:SOrigParam_GetDayInvitedFriends = _sessionMgr.getData(sessionID_) as SOrigParam_GetDayInvitedFriends;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDayInvitedFriends = new TEvt_GetDayInvitedFriends(TEvt_GetDayInvitedFriends.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：每日邀请好友数量
		private function _onTimeOut_GetDayInvitedFriends(sessionID:uint):void
		{
			var retParam:SRetParam_GetDayInvitedFriends = new SRetParam_GetDayInvitedFriends();
			var event_:TEvt_GetDayInvitedFriends = new TEvt_GetDayInvitedFriends(TEvt_GetDayInvitedFriends.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取奖励
		private function _doReturn_TakeTaskPrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeTaskPrize = new SRetParam_TakeTaskPrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EInviteResult)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_TakeTaskPrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeTaskPrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeTaskPrize = new TEvt_TakeTaskPrize(TEvt_TakeTaskPrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取奖励
		private function _onTimeOut_TakeTaskPrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeTaskPrize = new SRetParam_TakeTaskPrize();
			var event_:TEvt_TakeTaskPrize = new TEvt_TakeTaskPrize(TEvt_TakeTaskPrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:InviteGS;

		public static function get instance():InviteGS
		{
			if(_instance == null)
				_instance = new InviteGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function InviteGS()
		{
			_protID = 134;
			_recvFuncList = [
				_doRecv_UpdateInvitedFriend, //FuncID: 1
				_doRecv_UpdateInvitedTask, //FuncID: 2
				_doRecv_UpdateDayInvitedFriends //FuncID: 3
			];

			_retFuncList = [
				_doReturn_GetInvitedFriendList, //FuncID: 1
				_doReturn_GetInvitedTaskList, //FuncID: 2
				_doReturn_GetDayInvitedFriends, //FuncID: 3
				_doReturn_TakeTaskPrize //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetInvitedFriendList, //FuncID: 1
				_onTimeOut_GetInvitedTaskList, //FuncID: 2
				_onTimeOut_GetDayInvitedFriends, //FuncID: 3
				_onTimeOut_TakeTaskPrize //FuncID: 4
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