/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    LevelPrize.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.wonderActivityProt.SRoleAllStatus;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：等级奖励
	 */
	public class LevelPrize extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取奖励
		 * @param wActID (无符号16位整数)活动Id
		 */
		public function send_GetPrizeInfo(wActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetPrizeInfo = new SOrigParam_GetPrizeInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wActID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取奖励
		 * @param wActID (无符号16位整数)活动Id
		 * @param byIndex (无符号8位整数)第几个奖励
		 */
		public function send_TakePrize(wActID:uint, byIndex:uint, callback:Function = null):Boolean
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
			bytes_.writeShort(wActID);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家在个人服活动中的状态
		 */
		public function send_GetRoleState(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetRoleState = new SOrigParam_GetRoleState();
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
		 * 发送：QQAlarm获取奖励
		 * @param wActID (无符号16位整数)活动Id
		 */
		public function send_TakePrizeForQQAlarm(wActID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakePrizeForQQAlarm = new SOrigParam_TakePrizeForQQAlarm();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wActID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：QQAlarm获取奖励状态
		 * @param wActID (无符号16位整数)活动Id
		 */
		public function send_GetStateForQQAlarm(wActID:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeShort(wActID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：等级奖励活动状态通知
		private function _doRecv_LevelPrizeNotify(bytes:ByteArray):void
		{
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动Id
			var eStatus:uint = bytes.readUnsignedByte(); //(枚举类型：EActState)活动状态
			var event_:REvt_LevelPrizeNotify = new REvt_LevelPrizeNotify(REvt_LevelPrizeNotify.DATA_RECEIVE);
			event_.wActID = wActID;
			event_.eStatus = eStatus;
			dispatchEvent(event_);
		}

		//接收处理：可领状态通知
		private function _doRecv_SendReachCondNfy(bytes:ByteArray):void
		{
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动Id
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)第几个奖励
			var event_:REvt_SendReachCondNfy = new REvt_SendReachCondNfy(REvt_SendReachCondNfy.DATA_RECEIVE);
			event_.wActID = wActID;
			event_.byIndex = byIndex;
			dispatchEvent(event_);
		}

		//接收处理：QQAlarm奖励状态通知
		private function _doRecv_SendStateForQQAlarm(bytes:ByteArray):void
		{
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELevelActStatus)结果
			var event_:REvt_SendStateForQQAlarm = new REvt_SendStateForQQAlarm(REvt_SendStateForQQAlarm.DATA_RECEIVE);
			event_.wActID = wActID;
			event_.eRet = eRet;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取奖励
		private function _doReturn_GetPrizeInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPrizeInfo = new SRetParam_GetPrizeInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动ID
			var vecPrize:Vector.<SPrize> = SPrize.vectorFromByteArray(bytes); //结果
			retParam_.wActID = wActID;
			retParam_.vecPrize = vecPrize;
			var origParam_:SOrigParam_GetPrizeInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPrizeInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPrizeInfo = new TEvt_GetPrizeInfo(TEvt_GetPrizeInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取奖励
		private function _onTimeOut_GetPrizeInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPrizeInfo = new SRetParam_GetPrizeInfo();
			var event_:TEvt_GetPrizeInfo = new TEvt_GetPrizeInfo(TEvt_GetPrizeInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取奖励
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wActID:uint = bytes.readUnsignedShort(); //(无符号16位整数)活动Id
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)活动Id
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELevelActStatus)领取结果
			retParam_.wActID = wActID;
			retParam_.byIndex = byIndex;
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

		//超时处理：获取奖励
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家在个人服活动中的状态
		private function _doReturn_GetRoleState(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleState = new SRetParam_GetRoleState();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecRet:Vector.<SRoleAllStatus> = SRoleAllStatus.vectorFromByteArray(bytes); //结果
			retParam_.vecRet = vecRet;
			var origParam_:SOrigParam_GetRoleState = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleState;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleState = new TEvt_GetRoleState(TEvt_GetRoleState.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家在个人服活动中的状态
		private function _onTimeOut_GetRoleState(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleState = new SRetParam_GetRoleState();
			var event_:TEvt_GetRoleState = new TEvt_GetRoleState(TEvt_GetRoleState.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：QQAlarm获取奖励
		private function _doReturn_TakePrizeForQQAlarm(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrizeForQQAlarm = new SRetParam_TakePrizeForQQAlarm();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELevelActStatus)领取结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_TakePrizeForQQAlarm = _sessionMgr.getData(sessionID_) as SOrigParam_TakePrizeForQQAlarm;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakePrizeForQQAlarm = new TEvt_TakePrizeForQQAlarm(TEvt_TakePrizeForQQAlarm.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：QQAlarm获取奖励
		private function _onTimeOut_TakePrizeForQQAlarm(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrizeForQQAlarm = new SRetParam_TakePrizeForQQAlarm();
			var event_:TEvt_TakePrizeForQQAlarm = new TEvt_TakePrizeForQQAlarm(TEvt_TakePrizeForQQAlarm.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:LevelPrize;

		public static function get instance():LevelPrize
		{
			if(_instance == null)
				_instance = new LevelPrize();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function LevelPrize()
		{
			_protID = 121;
			_recvFuncList = [
				_doRecv_LevelPrizeNotify, //FuncID: 1
				_doRecv_SendReachCondNfy, //FuncID: 2
				_doRecv_SendStateForQQAlarm //FuncID: 3
			];

			_retFuncList = [
				_doReturn_GetPrizeInfo, //FuncID: 1
				_doReturn_TakePrize, //FuncID: 2
				_doReturn_GetRoleState, //FuncID: 3
				_doReturn_TakePrizeForQQAlarm, //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetPrizeInfo, //FuncID: 1
				_onTimeOut_TakePrize, //FuncID: 2
				_onTimeOut_GetRoleState, //FuncID: 3
				_onTimeOut_TakePrizeForQQAlarm, //FuncID: 4
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