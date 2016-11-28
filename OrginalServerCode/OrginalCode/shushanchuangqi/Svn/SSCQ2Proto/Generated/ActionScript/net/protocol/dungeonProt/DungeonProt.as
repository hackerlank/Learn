/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    DungeonProt.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItemGenInfo;
	import net.protocol.itemProt.SResource;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：副本相关协议
	 */
	public class DungeonProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：扫荡
		 * @param wDgnID (无符号16位整数)副本ID
		 * @param wCount (无符号16位整数)次数
		 * @param byOptions (无符号8位整数)选项, 1位为gold，2位为key,采集相关
		 */
		public function send_Sweeping(wDgnID:uint, wCount:uint, byOptions:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_Sweeping = new SOrigParam_Sweeping();
			origParam_.wDgnID = wDgnID;
			origParam_.wCount = wCount;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wDgnID);
			bytes_.writeShort(wCount);
			bytes_.writeByte(byOptions);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：加速扫荡
		 * @param byOptions (无符号8位整数)0为使用仙石
		 */
		public function send_SweepingSpeedUp(byOptions:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_SweepingSpeedUp = new SOrigParam_SweepingSpeedUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byOptions);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：取消扫荡
		 */
		public function send_CancelSweeping(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_CancelSweeping = new SOrigParam_CancelSweeping();
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
		 * 发送：
		 * @param wDgnID (无符号16位整数)副本ID
		 */
		public function send_EnterPlayerDungeon(wDgnID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_EnterPlayerDungeon = new SOrigParam_EnterPlayerDungeon();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wDgnID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：离开单人副本
		 */
		public function send_LeavePlayerDungeon(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_LeavePlayerDungeon = new SOrigParam_LeavePlayerDungeon();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：客户端确认领奖
		 * @param qwDgnID (无符号64位整数)副本唯一实例ID
		 */
		public function send_NotifyAcceptDgnAward(qwDgnID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_NotifyAcceptDgnAward = new SOrigParam_NotifyAcceptDgnAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwDgnID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：查询副本星级
		 */
		public function send_GetAllDgnInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetAllDgnInfo = new SOrigParam_GetAllDgnInfo();
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
		 * 发送：客户端查询扫荡信息
		 */
		public function send_GetDgnSweepingInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetDgnSweepingInfo = new SOrigParam_GetDgnSweepingInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：查询副本进度和星级
		 */
		public function send_GetDgnProcessAndStar():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：副本中玩家复活
		 */
		public function send_ReliveInDgn():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取组队副本信息
		 */
		public function send_GetTeamInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买英雄副本次数
		 * @param wDgnID (无符号16位整数)副本ID
		 */
		public function send_BuyHeroDgnTimes(wDgnID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_BuyHeroDgnTimes = new SOrigParam_BuyHeroDgnTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wDgnID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买历险副本次数
		 */
		public function send_BuyLiXianDgnTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_BuyLiXianDgnTimes = new SOrigParam_BuyLiXianDgnTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：查询副本星级领奖状态
		 */
		public function send_GetDgnStarAwardInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_GetDgnStarAwardInfo = new SOrigParam_GetDgnStarAwardInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取副本星级奖励
		 * @param wStarID (无符号16位整数)领奖ID
		 */
		public function send_GetDgnStarAward(wStarID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_GetDgnStarAward = new SOrigParam_GetDgnStarAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wStarID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：扫荡更新通知
		private function _doRecv_SweepingUpdateNotify(bytes:ByteArray):void
		{
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //获得物品
			var vecResSource:Vector.<SResource> = SResource.vectorFromByteArray(bytes); //获得资源
			var wCurrCount:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前次数
			var dwSweepEndTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)扫荡结束时间
			var event_:REvt_SweepingUpdateNotify = new REvt_SweepingUpdateNotify(REvt_SweepingUpdateNotify.DATA_RECEIVE);
			event_.vecItem = vecItem;
			event_.vecResSource = vecResSource;
			event_.wCurrCount = wCurrCount;
			event_.dwSweepEndTime = dwSweepEndTime;
			dispatchEvent(event_);
		}

		//接收处理：扫荡结束通知
		private function _doRecv_SweepingEndNotify(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			var event_:REvt_SweepingEndNotify = new REvt_SweepingEndNotify(REvt_SweepingEndNotify.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		//接收处理：副本地图怪物采集物索引通知
		private function _doRecv_DungeonMapIdxNotify(bytes:ByteArray):void
		{
			var vecIdx:Vector.<uint> = BytesUtil.readVecUByte(bytes); //(无符号8位整数)索引ID
			var event_:REvt_DungeonMapIdxNotify = new REvt_DungeonMapIdxNotify(REvt_DungeonMapIdxNotify.DATA_RECEIVE);
			event_.vecIdx = vecIdx;
			dispatchEvent(event_);
		}

		//接收处理：通知通关副本领奖
		private function _doRecv_NotifyDgnAward(bytes:ByteArray):void
		{
			var qwDgnId:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)副本唯一实例
			var wDgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本类型
			var qwLastBattleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)最后战报
			var byStar:uint = bytes.readUnsignedByte(); //(无符号8位整数)战斗评级
			var vecItem:Vector.<SItemGenInfo> = SItemGenInfo.vectorFromByteArray(bytes); //获得物品
			var vecResSource:Vector.<SResource> = SResource.vectorFromByteArray(bytes); //获得资源
			var event_:REvt_NotifyDgnAward = new REvt_NotifyDgnAward(REvt_NotifyDgnAward.DATA_RECEIVE);
			event_.qwDgnId = qwDgnId;
			event_.wDgnType = wDgnType;
			event_.qwLastBattleID = qwLastBattleID;
			event_.byStar = byStar;
			event_.vecItem = vecItem;
			event_.vecResSource = vecResSource;
			dispatchEvent(event_);
		}

		//接收处理：通告副本进程
		private function _doRecv_NotifyDgnProcess(bytes:ByteArray):void
		{
			var wDgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本类型
			var vecProcess:Vector.<MulCond> = MulCond.vectorFromByteArray(bytes); //副本进度
			var event_:REvt_NotifyDgnProcess = new REvt_NotifyDgnProcess(REvt_NotifyDgnProcess.DATA_RECEIVE);
			event_.wDgnType = wDgnType;
			event_.vecProcess = vecProcess;
			dispatchEvent(event_);
		}

		//接收处理：通告副本星级
		private function _doRecv_NotifyDgnStar(bytes:ByteArray):void
		{
			var wDgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本类型
			var vecStar:Vector.<MulCond> = MulCond.vectorFromByteArray(bytes); //副本星级
			var event_:REvt_NotifyDgnStar = new REvt_NotifyDgnStar(REvt_NotifyDgnStar.DATA_RECEIVE);
			event_.wDgnType = wDgnType;
			event_.vecStar = vecStar;
			dispatchEvent(event_);
		}

		//接收处理：同步领奖记录
		private function _doRecv_SynTeamAwardRecord(bytes:ByteArray):void
		{
			var stAward:TeamAwardAllRecord = TeamAwardAllRecord.fromByteArray(bytes); //同步数据
			var event_:REvt_SynTeamAwardRecord = new REvt_SynTeamAwardRecord(REvt_SynTeamAwardRecord.DATA_RECEIVE);
			event_.stAward = stAward;
			dispatchEvent(event_);
		}

		//接收处理：队伍战斗结果
		private function _doRecv_TeamBattleResult(bytes:ByteArray):void
		{
			var DgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本类型
			var bySuc:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,失败，1成功
			var event_:REvt_TeamBattleResult = new REvt_TeamBattleResult(REvt_TeamBattleResult.DATA_RECEIVE);
			event_.DgnType = DgnType;
			event_.bySuc = bySuc;
			dispatchEvent(event_);
		}

		//接收处理：更新历险副本信息
		private function _doRecv_UpdateLiXian(bytes:ByteArray):void
		{
			var sLiXian:DgnLiXian = DgnLiXian.fromByteArray(bytes); //历险副本信息
			var event_:REvt_UpdateLiXian = new REvt_UpdateLiXian(REvt_UpdateLiXian.DATA_RECEIVE);
			event_.sLiXian = sLiXian;
			dispatchEvent(event_);
		}

		//接收处理：更新单个副本信息
		private function _doRecv_UpdateDgnInfo(bytes:ByteArray):void
		{
			var sDgnStar:DgnStar = DgnStar.fromByteArray(bytes); //副本信息
			var event_:REvt_UpdateDgnInfo = new REvt_UpdateDgnInfo(REvt_UpdateDgnInfo.DATA_RECEIVE);
			event_.sDgnStar = sDgnStar;
			dispatchEvent(event_);
		}

		//接收处理：更新所有副本信息
		private function _doRecv_UpdateDgnInfoForAll(bytes:ByteArray):void
		{
			var sLiXian:DgnLiXian = DgnLiXian.fromByteArray(bytes); //历险副本信息
			var vecStar:Vector.<DgnStar> = DgnStar.vectorFromByteArray(bytes); //副本星级
			var event_:REvt_UpdateDgnInfoForAll = new REvt_UpdateDgnInfoForAll(REvt_UpdateDgnInfoForAll.DATA_RECEIVE);
			event_.sLiXian = sLiXian;
			event_.vecStar = vecStar;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：扫荡
		private function _doReturn_Sweeping(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Sweeping = new SRetParam_Sweeping();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)扫荡结果
			var dwSweepEndTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)扫荡结束时间
			retParam_.eResult = eResult;
			retParam_.dwSweepEndTime = dwSweepEndTime;
			var origParam_:SOrigParam_Sweeping = _sessionMgr.getData(sessionID_) as SOrigParam_Sweeping;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_Sweeping = new TEvt_Sweeping(TEvt_Sweeping.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：扫荡
		private function _onTimeOut_Sweeping(sessionID:uint):void
		{
			var retParam:SRetParam_Sweeping = new SRetParam_Sweeping();
			var origParam:SOrigParam_Sweeping = _sessionMgr.getData(sessionID) as SOrigParam_Sweeping;
			var event_:TEvt_Sweeping = new TEvt_Sweeping(TEvt_Sweeping.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：加速扫荡
		private function _doReturn_SweepingSpeedUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SweepingSpeedUp = new SRetParam_SweepingSpeedUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)加速扫荡结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SweepingSpeedUp = _sessionMgr.getData(sessionID_) as SOrigParam_SweepingSpeedUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SweepingSpeedUp = new TEvt_SweepingSpeedUp(TEvt_SweepingSpeedUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：加速扫荡
		private function _onTimeOut_SweepingSpeedUp(sessionID:uint):void
		{
			var retParam:SRetParam_SweepingSpeedUp = new SRetParam_SweepingSpeedUp();
			var event_:TEvt_SweepingSpeedUp = new TEvt_SweepingSpeedUp(TEvt_SweepingSpeedUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取消扫荡
		private function _doReturn_CancelSweeping(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CancelSweeping = new SRetParam_CancelSweeping();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)取消扫荡结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CancelSweeping = _sessionMgr.getData(sessionID_) as SOrigParam_CancelSweeping;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CancelSweeping = new TEvt_CancelSweeping(TEvt_CancelSweeping.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取消扫荡
		private function _onTimeOut_CancelSweeping(sessionID:uint):void
		{
			var retParam:SRetParam_CancelSweeping = new SRetParam_CancelSweeping();
			var event_:TEvt_CancelSweeping = new TEvt_CancelSweeping(TEvt_CancelSweeping.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：
		private function _doReturn_EnterPlayerDungeon(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterPlayerDungeon = new SRetParam_EnterPlayerDungeon();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_EnterPlayerDungeon = _sessionMgr.getData(sessionID_) as SOrigParam_EnterPlayerDungeon;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterPlayerDungeon = new TEvt_EnterPlayerDungeon(TEvt_EnterPlayerDungeon.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：
		private function _onTimeOut_EnterPlayerDungeon(sessionID:uint):void
		{
			var retParam:SRetParam_EnterPlayerDungeon = new SRetParam_EnterPlayerDungeon();
			var event_:TEvt_EnterPlayerDungeon = new TEvt_EnterPlayerDungeon(TEvt_EnterPlayerDungeon.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开单人副本
		private function _doReturn_LeavePlayerDungeon(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeavePlayerDungeon = new SRetParam_LeavePlayerDungeon();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_LeavePlayerDungeon = _sessionMgr.getData(sessionID_) as SOrigParam_LeavePlayerDungeon;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeavePlayerDungeon = new TEvt_LeavePlayerDungeon(TEvt_LeavePlayerDungeon.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：离开单人副本
		private function _onTimeOut_LeavePlayerDungeon(sessionID:uint):void
		{
			var retParam:SRetParam_LeavePlayerDungeon = new SRetParam_LeavePlayerDungeon();
			var event_:TEvt_LeavePlayerDungeon = new TEvt_LeavePlayerDungeon(TEvt_LeavePlayerDungeon.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：客户端确认领奖
		private function _doReturn_NotifyAcceptDgnAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_NotifyAcceptDgnAward = new SRetParam_NotifyAcceptDgnAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_NotifyAcceptDgnAward = _sessionMgr.getData(sessionID_) as SOrigParam_NotifyAcceptDgnAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_NotifyAcceptDgnAward = new TEvt_NotifyAcceptDgnAward(TEvt_NotifyAcceptDgnAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：客户端确认领奖
		private function _onTimeOut_NotifyAcceptDgnAward(sessionID:uint):void
		{
			var retParam:SRetParam_NotifyAcceptDgnAward = new SRetParam_NotifyAcceptDgnAward();
			var event_:TEvt_NotifyAcceptDgnAward = new TEvt_NotifyAcceptDgnAward(TEvt_NotifyAcceptDgnAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：查询副本星级
		private function _doReturn_GetAllDgnInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllDgnInfo = new SRetParam_GetAllDgnInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sLiXian:DgnLiXian = DgnLiXian.fromByteArray(bytes); //历险副本信息
			var vecStar:Vector.<DgnStar> = DgnStar.vectorFromByteArray(bytes); //副本星级
			retParam_.sLiXian = sLiXian;
			retParam_.vecStar = vecStar;
			var origParam_:SOrigParam_GetAllDgnInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllDgnInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllDgnInfo = new TEvt_GetAllDgnInfo(TEvt_GetAllDgnInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：查询副本星级
		private function _onTimeOut_GetAllDgnInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllDgnInfo = new SRetParam_GetAllDgnInfo();
			var event_:TEvt_GetAllDgnInfo = new TEvt_GetAllDgnInfo(TEvt_GetAllDgnInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：客户端查询扫荡信息
		private function _doReturn_GetDgnSweepingInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDgnSweepingInfo = new SRetParam_GetDgnSweepingInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oGetSweepInfo:SGetSweepInfo = SGetSweepInfo.fromByteArray(bytes); //扫荡信息
			retParam_.oGetSweepInfo = oGetSweepInfo;
			var origParam_:SOrigParam_GetDgnSweepingInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetDgnSweepingInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDgnSweepingInfo = new TEvt_GetDgnSweepingInfo(TEvt_GetDgnSweepingInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：客户端查询扫荡信息
		private function _onTimeOut_GetDgnSweepingInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetDgnSweepingInfo = new SRetParam_GetDgnSweepingInfo();
			var event_:TEvt_GetDgnSweepingInfo = new TEvt_GetDgnSweepingInfo(TEvt_GetDgnSweepingInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买英雄副本次数
		private function _doReturn_BuyHeroDgnTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyHeroDgnTimes = new SRetParam_BuyHeroDgnTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyHeroDgnTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyHeroDgnTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyHeroDgnTimes = new TEvt_BuyHeroDgnTimes(TEvt_BuyHeroDgnTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买英雄副本次数
		private function _onTimeOut_BuyHeroDgnTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyHeroDgnTimes = new SRetParam_BuyHeroDgnTimes();
			var event_:TEvt_BuyHeroDgnTimes = new TEvt_BuyHeroDgnTimes(TEvt_BuyHeroDgnTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买历险副本次数
		private function _doReturn_BuyLiXianDgnTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyLiXianDgnTimes = new SRetParam_BuyLiXianDgnTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyLiXianDgnTimes = _sessionMgr.getData(sessionID_) as SOrigParam_BuyLiXianDgnTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyLiXianDgnTimes = new TEvt_BuyLiXianDgnTimes(TEvt_BuyLiXianDgnTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买历险副本次数
		private function _onTimeOut_BuyLiXianDgnTimes(sessionID:uint):void
		{
			var retParam:SRetParam_BuyLiXianDgnTimes = new SRetParam_BuyLiXianDgnTimes();
			var event_:TEvt_BuyLiXianDgnTimes = new TEvt_BuyLiXianDgnTimes(TEvt_BuyLiXianDgnTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：查询副本星级领奖状态
		private function _doReturn_GetDgnStarAwardInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDgnStarAwardInfo = new SRetParam_GetDgnStarAwardInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecAward:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)副本星级已领奖ID
			retParam_.vecAward = vecAward;
			var origParam_:SOrigParam_GetDgnStarAwardInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetDgnStarAwardInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDgnStarAwardInfo = new TEvt_GetDgnStarAwardInfo(TEvt_GetDgnStarAwardInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：查询副本星级领奖状态
		private function _onTimeOut_GetDgnStarAwardInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetDgnStarAwardInfo = new SRetParam_GetDgnStarAwardInfo();
			var event_:TEvt_GetDgnStarAwardInfo = new TEvt_GetDgnStarAwardInfo(TEvt_GetDgnStarAwardInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：领取副本星级奖励
		private function _doReturn_GetDgnStarAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDgnStarAward = new SRetParam_GetDgnStarAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EDungeonResult)服务器返回结果
			var vecAward:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)副本星级已领奖ID
			retParam_.eResult = eResult;
			retParam_.vecAward = vecAward;
			var origParam_:SOrigParam_GetDgnStarAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetDgnStarAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDgnStarAward = new TEvt_GetDgnStarAward(TEvt_GetDgnStarAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：领取副本星级奖励
		private function _onTimeOut_GetDgnStarAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetDgnStarAward = new SRetParam_GetDgnStarAward();
			var event_:TEvt_GetDgnStarAward = new TEvt_GetDgnStarAward(TEvt_GetDgnStarAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:DungeonProt;

		public static function get instance():DungeonProt
		{
			if(_instance == null)
				_instance = new DungeonProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function DungeonProt()
		{
			_protID = 59;
			_recvFuncList = [
				_doRecv_SweepingUpdateNotify, //FuncID: 1
				_doRecv_SweepingEndNotify, //FuncID: 2
				_doRecv_DungeonMapIdxNotify, //FuncID: 3
				_doRecv_NotifyDgnAward, //FuncID: 4
				_doRecv_NotifyDgnProcess, //FuncID: 5
				_doRecv_NotifyDgnStar, //FuncID: 6
				_doRecv_SynTeamAwardRecord, //FuncID: 7
				_doRecv_TeamBattleResult, //FuncID: 8
				_doRecv_UpdateLiXian, //FuncID: 9
				_doRecv_UpdateDgnInfo, //FuncID: 10
				_doRecv_UpdateDgnInfoForAll //FuncID: 11
			];

			_retFuncList = [
				_doReturn_Sweeping, //FuncID: 1
				_doReturn_SweepingSpeedUp, //FuncID: 2
				_doReturn_CancelSweeping, //FuncID: 3
				_doReturn_EnterPlayerDungeon, //FuncID: 4
				_doReturn_LeavePlayerDungeon, //FuncID: 5
				_doReturn_NotifyAcceptDgnAward, //FuncID: 6
				_doReturn_GetAllDgnInfo, //FuncID: 7
				_doReturn_GetDgnSweepingInfo, //FuncID: 8
				_doReturn_BuyHeroDgnTimes, //FuncID: 9
				_doReturn_BuyLiXianDgnTimes, //FuncID: 10
				_doReturn_GetDgnStarAwardInfo, //FuncID: 11
				_doReturn_GetDgnStarAward //FuncID: 12
			];

			_timeFuncList = [
				_onTimeOut_Sweeping, //FuncID: 1
				_onTimeOut_SweepingSpeedUp, //FuncID: 2
				_onTimeOut_CancelSweeping, //FuncID: 3
				_onTimeOut_EnterPlayerDungeon, //FuncID: 4
				_onTimeOut_LeavePlayerDungeon, //FuncID: 5
				_onTimeOut_NotifyAcceptDgnAward, //FuncID: 6
				_onTimeOut_GetAllDgnInfo, //FuncID: 7
				_onTimeOut_GetDgnSweepingInfo, //FuncID: 8
				_onTimeOut_BuyHeroDgnTimes, //FuncID: 9
				_onTimeOut_BuyLiXianDgnTimes, //FuncID: 10
				_onTimeOut_GetDgnStarAwardInfo, //FuncID: 11
				_onTimeOut_GetDgnStarAward //FuncID: 12
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