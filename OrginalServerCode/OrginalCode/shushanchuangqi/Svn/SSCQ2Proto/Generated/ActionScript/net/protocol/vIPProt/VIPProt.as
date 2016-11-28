/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    VIPProt.as
//  Purpose:      VIP特权相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：VIP特权相关协议
	 */
	public class VIPProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求个人VIP特权信息
		 */
		public function send_GetVIPInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求个人VIP特权
		 * @param byType (无符号8位整数)VIP特权类型
		 */
		public function send_OpenSelfVIP(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_OpenSelfVIP = new SOrigParam_OpenSelfVIP();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求开启好友VIP特权
		 * @param byType (无符号8位整数)VIP特权类型
		 * @param qwRoleID (无符号64位整数)好友玩家ID
		 * @param qwRoleID2 (无符号64位整数)好友玩家ID(匹配验证)
		 */
		public function send_OpenOtherVIP(byType:uint, qwRoleID:BigInteger, qwRoleID2:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_OpenOtherVIP = new SOrigParam_OpenOtherVIP();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			BytesUtil.writeUInt64(bytes_, qwRoleID2);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求开启个人月卡
		 */
		public function send_OpenSelfMonthCard(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_OpenSelfMonthCard = new SOrigParam_OpenSelfMonthCard();
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
		 * 发送：请求开启好友月卡
		 * @param qwRoleID (无符号64位整数)好友玩家ID
		 */
		public function send_OpenOtherMonthCard(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_OpenOtherMonthCard = new SOrigParam_OpenOtherMonthCard();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取VIP特权每日礼包
		 */
		public function send_GetDayPackAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetDayPackAward = new SOrigParam_GetDayPackAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取VIP特权等级奖励
		 * @param byLevel (无符号8位整数)VIP等级
		 */
		public function send_GetVIPLevelAward(byLevel:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetVIPLevelAward = new SOrigParam_GetVIPLevelAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byLevel);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：个人VIP特权信息
		private function _doRecv_SelfVIPInfo(bytes:ByteArray):void
		{
			var stVIPData:SVIPData = SVIPData.fromByteArray(bytes); //VIP特权信息
			var event_:REvt_SelfVIPInfo = new REvt_SelfVIPInfo(REvt_SelfVIPInfo.DATA_RECEIVE);
			event_.stVIPData = stVIPData;
			dispatchEvent(event_);
		}

		//接收处理：月卡过期通知消息
		private function _doRecv_UpdateMonthCardOverdue(bytes:ByteArray):void
		{
			var byVal:uint = bytes.readUnsignedByte(); //(无符号8位整数)0未过期 >0已过期
			var event_:REvt_UpdateMonthCardOverdue = new REvt_UpdateMonthCardOverdue(REvt_UpdateMonthCardOverdue.DATA_RECEIVE);
			event_.byVal = byVal;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求个人VIP特权
		private function _doReturn_OpenSelfVIP(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OpenSelfVIP = new SRetParam_OpenSelfVIP();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_OpenSelfVIP = _sessionMgr.getData(sessionID_) as SOrigParam_OpenSelfVIP;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OpenSelfVIP = new TEvt_OpenSelfVIP(TEvt_OpenSelfVIP.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求个人VIP特权
		private function _onTimeOut_OpenSelfVIP(sessionID:uint):void
		{
			var retParam:SRetParam_OpenSelfVIP = new SRetParam_OpenSelfVIP();
			var event_:TEvt_OpenSelfVIP = new TEvt_OpenSelfVIP(TEvt_OpenSelfVIP.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求开启好友VIP特权
		private function _doReturn_OpenOtherVIP(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OpenOtherVIP = new SRetParam_OpenOtherVIP();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)好友玩家ID
			retParam_.eResult = eResult;
			retParam_.qwRoleID = qwRoleID;
			var origParam_:SOrigParam_OpenOtherVIP = _sessionMgr.getData(sessionID_) as SOrigParam_OpenOtherVIP;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OpenOtherVIP = new TEvt_OpenOtherVIP(TEvt_OpenOtherVIP.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求开启好友VIP特权
		private function _onTimeOut_OpenOtherVIP(sessionID:uint):void
		{
			var retParam:SRetParam_OpenOtherVIP = new SRetParam_OpenOtherVIP();
			var event_:TEvt_OpenOtherVIP = new TEvt_OpenOtherVIP(TEvt_OpenOtherVIP.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求开启个人月卡
		private function _doReturn_OpenSelfMonthCard(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OpenSelfMonthCard = new SRetParam_OpenSelfMonthCard();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_OpenSelfMonthCard = _sessionMgr.getData(sessionID_) as SOrigParam_OpenSelfMonthCard;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OpenSelfMonthCard = new TEvt_OpenSelfMonthCard(TEvt_OpenSelfMonthCard.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求开启个人月卡
		private function _onTimeOut_OpenSelfMonthCard(sessionID:uint):void
		{
			var retParam:SRetParam_OpenSelfMonthCard = new SRetParam_OpenSelfMonthCard();
			var event_:TEvt_OpenSelfMonthCard = new TEvt_OpenSelfMonthCard(TEvt_OpenSelfMonthCard.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求开启好友月卡
		private function _doReturn_OpenOtherMonthCard(bytes:ByteArray):void
		{
			var retParam_:SRetParam_OpenOtherMonthCard = new SRetParam_OpenOtherMonthCard();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)好友玩家ID
			retParam_.eResult = eResult;
			retParam_.qwRoleID = qwRoleID;
			var origParam_:SOrigParam_OpenOtherMonthCard = _sessionMgr.getData(sessionID_) as SOrigParam_OpenOtherMonthCard;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_OpenOtherMonthCard = new TEvt_OpenOtherMonthCard(TEvt_OpenOtherMonthCard.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求开启好友月卡
		private function _onTimeOut_OpenOtherMonthCard(sessionID:uint):void
		{
			var retParam:SRetParam_OpenOtherMonthCard = new SRetParam_OpenOtherMonthCard();
			var event_:TEvt_OpenOtherMonthCard = new TEvt_OpenOtherMonthCard(TEvt_OpenOtherMonthCard.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取VIP特权每日礼包
		private function _doReturn_GetDayPackAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDayPackAward = new SRetParam_GetDayPackAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			var dwDayPack:uint = bytes.readUnsignedInt(); //(无符号32位整数)VIP特权每日礼包领取状态(低15位,按位取)
			retParam_.eResult = eResult;
			retParam_.dwDayPack = dwDayPack;
			var origParam_:SOrigParam_GetDayPackAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetDayPackAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDayPackAward = new TEvt_GetDayPackAward(TEvt_GetDayPackAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取VIP特权每日礼包
		private function _onTimeOut_GetDayPackAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetDayPackAward = new SRetParam_GetDayPackAward();
			var event_:TEvt_GetDayPackAward = new TEvt_GetDayPackAward(TEvt_GetDayPackAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取VIP特权等级奖励
		private function _doReturn_GetVIPLevelAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetVIPLevelAward = new SRetParam_GetVIPLevelAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EVIPResult)操作结果
			var dwLvlAward:uint = bytes.readUnsignedInt(); //(无符号32位整数)VIP等级奖励领取状态(低15位,按位取)
			retParam_.eResult = eResult;
			retParam_.dwLvlAward = dwLvlAward;
			var origParam_:SOrigParam_GetVIPLevelAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetVIPLevelAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetVIPLevelAward = new TEvt_GetVIPLevelAward(TEvt_GetVIPLevelAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取VIP特权等级奖励
		private function _onTimeOut_GetVIPLevelAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetVIPLevelAward = new SRetParam_GetVIPLevelAward();
			var event_:TEvt_GetVIPLevelAward = new TEvt_GetVIPLevelAward(TEvt_GetVIPLevelAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:VIPProt;

		public static function get instance():VIPProt
		{
			if(_instance == null)
				_instance = new VIPProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function VIPProt()
		{
			_protID = 65;
			_recvFuncList = [
				_doRecv_SelfVIPInfo, //FuncID: 1
				_doRecv_UpdateMonthCardOverdue //FuncID: 2
			];

			_retFuncList = [
				_doReturn_OpenSelfVIP, //FuncID: 1
				_doReturn_OpenOtherVIP, //FuncID: 2
				_doReturn_OpenSelfMonthCard, //FuncID: 3
				_doReturn_OpenOtherMonthCard, //FuncID: 4
				_doReturn_GetDayPackAward, //FuncID: 5
				_doReturn_GetVIPLevelAward //FuncID: 6
			];

			_timeFuncList = [
				_onTimeOut_OpenSelfVIP, //FuncID: 1
				_onTimeOut_OpenOtherVIP, //FuncID: 2
				_onTimeOut_OpenSelfMonthCard, //FuncID: 3
				_onTimeOut_OpenOtherMonthCard, //FuncID: 4
				_onTimeOut_GetDayPackAward, //FuncID: 5
				_onTimeOut_GetVIPLevelAward //FuncID: 6
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