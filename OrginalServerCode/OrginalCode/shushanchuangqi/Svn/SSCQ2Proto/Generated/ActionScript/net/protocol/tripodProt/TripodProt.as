/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    TripodProt.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.arenaGS.SArenaFighter;
	import net.protocol.itemProt.SItemCount;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：九疑鼎相关协议
	 */
	public class TripodProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：取得玩家所有九疑鼎信息
		 */
		public function send_GetAllTripods(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetAllTripods = new SOrigParam_GetAllTripods();
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
		 * 发送：取得玩家所有九疑鼎的火种信息
		 */
		public function send_GetAllFires(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetAllFires = new SOrigParam_GetAllFires();
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
		 * 发送：取得其他玩家所有九疑鼎信息
		 * @param qwRoleID (无符号64位整数)玩家ID(九疑鼎所属者)
		 */
		public function send_GetTripodData(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetTripodData = new SOrigParam_GetTripodData();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：激活九疑鼎
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 */
		public function send_ActiveTripod(byTripodID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ActiveTripod = new SOrigParam_ActiveTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：升级九疑鼎
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 * @param byOneKey (无符号8位整数)是否一键
		 */
		public function send_UpgradeTripod(byTripodID:uint, byOneKey:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_UpgradeTripod = new SOrigParam_UpgradeTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			bytes_.writeByte(byOneKey);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：九疑鼎祈火(炼丹)
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 * @param wFireID (无符号16位整数)火种ID
		 */
		public function send_MakeFireTripod(byTripodID:uint, wFireID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_MakeFireTripod = new SOrigParam_MakeFireTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			bytes_.writeShort(wFireID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：清除九疑鼎祈火记录
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 */
		public function send_ClearFireTripod(byTripodID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_ClearFireTripod = new SOrigParam_ClearFireTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取九疑鼎炼丹果实
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 */
		public function send_GetTripodAward(byTripodID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetTripodAward = new SOrigParam_GetTripodAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：加速九疑鼎炼丹(道具入鼎)
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 * @param vecItems 入鼎道具列表
		 */
		public function send_SpeedTripod(byTripodID:uint, vecItems:Vector.<SItemCount>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_SpeedTripod = new SOrigParam_SpeedTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byTripodID);
			SItemCount.vectorToByteArray(vecItems, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：扇火九疑鼎
		 * @param qwRoleID (无符号64位整数)玩家ID(九疑鼎所属者)
		 * @param byTripodID (无符号8位整数)九疑鼎ID
		 */
		public function send_AddTripodExtraSoul(qwRoleID:BigInteger, byTripodID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_AddTripodExtraSoul = new SOrigParam_AddTripodExtraSoul();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			bytes_.writeByte(byTripodID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：散仙协助九疑鼎
		 * @param wFighterID (无符号16位整数)自己的散仙ID
		 * @param byPos (无符号8位整数)协助位置
		 */
		public function send_FighterHelpTripod(wFighterID:uint, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_FighterHelpTripod = new SOrigParam_FighterHelpTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wFighterID);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家协助九疑鼎
		 * @param qwRoleID (无符号64位整数)对方玩家ID
		 * @param byPos (无符号8位整数)协助位置
		 */
		public function send_UserHelpTripod(qwRoleID:BigInteger, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_UserHelpTripod = new SOrigParam_UserHelpTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：踢出九疑鼎协助者
		 * @param byPos (无符号8位整数)协助位置(0,1,2)
		 * @param byType (无符号8位整数)0散仙 1玩家
		 */
		public function send_ShotOffHelpTripod(byPos:uint, byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_ShotOffHelpTripod = new SOrigParam_ShotOffHelpTripod();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byPos);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求玩家九疑鼎的能被扇火、协助信息
		 * @param vecRoleID (无符号64位整数)好友玩家ID列表
		 */
		public function send_GetTripodStatus(vecRoleID:Vector.<BigInteger>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_GetTripodStatus = new SOrigParam_GetTripodStatus();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeVecUInt64(bytes_, vecRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：更新玩家的九疑鼎数据
		private function _doRecv_UpdateTripod(bytes:ByteArray):void
		{
			var oTripodData:STripodData = STripodData.fromByteArray(bytes); //九疑鼎数据列表
			var byShanfeng:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今日已扇风次数
			var byHelpTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今日已协助次数(玩家协助)
			var event_:REvt_UpdateTripod = new REvt_UpdateTripod(REvt_UpdateTripod.DATA_RECEIVE);
			event_.oTripodData = oTripodData;
			event_.byShanfeng = byShanfeng;
			event_.byHelpTimes = byHelpTimes;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：取得玩家所有九疑鼎信息
		private function _doReturn_GetAllTripods(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllTripods = new SRetParam_GetAllTripods();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oTripodData:STripodData = STripodData.fromByteArray(bytes); //九疑鼎数据列表
			var byShanfeng:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今日已扇风次数
			var byHelpTimes:uint = bytes.readUnsignedByte(); //(无符号8位整数)玩家今日已协助次数(玩家协助)
			retParam_.oTripodData = oTripodData;
			retParam_.byShanfeng = byShanfeng;
			retParam_.byHelpTimes = byHelpTimes;
			var origParam_:SOrigParam_GetAllTripods = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllTripods;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllTripods = new TEvt_GetAllTripods(TEvt_GetAllTripods.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得玩家所有九疑鼎信息
		private function _onTimeOut_GetAllTripods(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllTripods = new SRetParam_GetAllTripods();
			var event_:TEvt_GetAllTripods = new TEvt_GetAllTripods(TEvt_GetAllTripods.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取得玩家所有九疑鼎的火种信息
		private function _doReturn_GetAllFires(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllFires = new SRetParam_GetAllFires();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFires:Vector.<SFireInfo> = SFireInfo.vectorFromByteArray(bytes); //九疑鼎信息列表
			retParam_.vecFires = vecFires;
			var origParam_:SOrigParam_GetAllFires = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllFires;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllFires = new TEvt_GetAllFires(TEvt_GetAllFires.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得玩家所有九疑鼎的火种信息
		private function _onTimeOut_GetAllFires(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllFires = new SRetParam_GetAllFires();
			var event_:TEvt_GetAllFires = new TEvt_GetAllFires(TEvt_GetAllFires.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取得其他玩家所有九疑鼎信息
		private function _doReturn_GetTripodData(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTripodData = new SRetParam_GetTripodData();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oTripodData:STripodData = STripodData.fromByteArray(bytes); //九疑鼎数据列表
			retParam_.oTripodData = oTripodData;
			var origParam_:SOrigParam_GetTripodData = _sessionMgr.getData(sessionID_) as SOrigParam_GetTripodData;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTripodData = new TEvt_GetTripodData(TEvt_GetTripodData.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得其他玩家所有九疑鼎信息
		private function _onTimeOut_GetTripodData(sessionID:uint):void
		{
			var retParam:SRetParam_GetTripodData = new SRetParam_GetTripodData();
			var event_:TEvt_GetTripodData = new TEvt_GetTripodData(TEvt_GetTripodData.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：激活九疑鼎
		private function _doReturn_ActiveTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ActiveTripod = new SRetParam_ActiveTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byTripodID:uint = bytes.readUnsignedByte(); //(无符号8位整数)九疑鼎ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.byTripodID = byTripodID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ActiveTripod = _sessionMgr.getData(sessionID_) as SOrigParam_ActiveTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ActiveTripod = new TEvt_ActiveTripod(TEvt_ActiveTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活九疑鼎
		private function _onTimeOut_ActiveTripod(sessionID:uint):void
		{
			var retParam:SRetParam_ActiveTripod = new SRetParam_ActiveTripod();
			var event_:TEvt_ActiveTripod = new TEvt_ActiveTripod(TEvt_ActiveTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：升级九疑鼎
		private function _doReturn_UpgradeTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeTripod = new SRetParam_UpgradeTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes); //九疑鼎信息列表
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.vecTripods = vecTripods;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UpgradeTripod = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeTripod = new TEvt_UpgradeTripod(TEvt_UpgradeTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：升级九疑鼎
		private function _onTimeOut_UpgradeTripod(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeTripod = new SRetParam_UpgradeTripod();
			var event_:TEvt_UpgradeTripod = new TEvt_UpgradeTripod(TEvt_UpgradeTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：九疑鼎祈火(炼丹)
		private function _doReturn_MakeFireTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MakeFireTripod = new SRetParam_MakeFireTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes); //九疑鼎信息列表
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.vecTripods = vecTripods;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MakeFireTripod = _sessionMgr.getData(sessionID_) as SOrigParam_MakeFireTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MakeFireTripod = new TEvt_MakeFireTripod(TEvt_MakeFireTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：九疑鼎祈火(炼丹)
		private function _onTimeOut_MakeFireTripod(sessionID:uint):void
		{
			var retParam:SRetParam_MakeFireTripod = new SRetParam_MakeFireTripod();
			var event_:TEvt_MakeFireTripod = new TEvt_MakeFireTripod(TEvt_MakeFireTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清除九疑鼎祈火记录
		private function _doReturn_ClearFireTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ClearFireTripod = new SRetParam_ClearFireTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byTripodID:uint = bytes.readUnsignedByte(); //(无符号8位整数)九疑鼎ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.byTripodID = byTripodID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ClearFireTripod = _sessionMgr.getData(sessionID_) as SOrigParam_ClearFireTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ClearFireTripod = new TEvt_ClearFireTripod(TEvt_ClearFireTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清除九疑鼎祈火记录
		private function _onTimeOut_ClearFireTripod(sessionID:uint):void
		{
			var retParam:SRetParam_ClearFireTripod = new SRetParam_ClearFireTripod();
			var event_:TEvt_ClearFireTripod = new TEvt_ClearFireTripod(TEvt_ClearFireTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取九疑鼎炼丹果实
		private function _doReturn_GetTripodAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTripodAward = new SRetParam_GetTripodAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes); //九疑鼎信息列表
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.vecTripods = vecTripods;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetTripodAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetTripodAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTripodAward = new TEvt_GetTripodAward(TEvt_GetTripodAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取九疑鼎炼丹果实
		private function _onTimeOut_GetTripodAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetTripodAward = new SRetParam_GetTripodAward();
			var event_:TEvt_GetTripodAward = new TEvt_GetTripodAward(TEvt_GetTripodAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：加速九疑鼎炼丹(道具入鼎)
		private function _doReturn_SpeedTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SpeedTripod = new SRetParam_SpeedTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes); //九疑鼎信息列表
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.vecTripods = vecTripods;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SpeedTripod = _sessionMgr.getData(sessionID_) as SOrigParam_SpeedTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SpeedTripod = new TEvt_SpeedTripod(TEvt_SpeedTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：加速九疑鼎炼丹(道具入鼎)
		private function _onTimeOut_SpeedTripod(sessionID:uint):void
		{
			var retParam:SRetParam_SpeedTripod = new SRetParam_SpeedTripod();
			var event_:TEvt_SpeedTripod = new TEvt_SpeedTripod(TEvt_SpeedTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：扇火九疑鼎
		private function _doReturn_AddTripodExtraSoul(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AddTripodExtraSoul = new SRetParam_AddTripodExtraSoul();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTripods:Vector.<STripodInfo> = STripodInfo.vectorFromByteArray(bytes); //所属者的九疑鼎信息列表
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.vecTripods = vecTripods;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_AddTripodExtraSoul = _sessionMgr.getData(sessionID_) as SOrigParam_AddTripodExtraSoul;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AddTripodExtraSoul = new TEvt_AddTripodExtraSoul(TEvt_AddTripodExtraSoul.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：扇火九疑鼎
		private function _onTimeOut_AddTripodExtraSoul(sessionID:uint):void
		{
			var retParam:SRetParam_AddTripodExtraSoul = new SRetParam_AddTripodExtraSoul();
			var event_:TEvt_AddTripodExtraSoul = new TEvt_AddTripodExtraSoul(TEvt_AddTripodExtraSoul.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：散仙协助九疑鼎
		private function _doReturn_FighterHelpTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FighterHelpTripod = new SRetParam_FighterHelpTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oFighterHelp:SFighterHelpInfo = SFighterHelpInfo.fromByteArray(bytes); //散仙协助信息
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.oFighterHelp = oFighterHelp;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FighterHelpTripod = _sessionMgr.getData(sessionID_) as SOrigParam_FighterHelpTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FighterHelpTripod = new TEvt_FighterHelpTripod(TEvt_FighterHelpTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：散仙协助九疑鼎
		private function _onTimeOut_FighterHelpTripod(sessionID:uint):void
		{
			var retParam:SRetParam_FighterHelpTripod = new SRetParam_FighterHelpTripod();
			var event_:TEvt_FighterHelpTripod = new TEvt_FighterHelpTripod(TEvt_FighterHelpTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家协助九疑鼎
		private function _doReturn_UserHelpTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UserHelpTripod = new SRetParam_UserHelpTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oPlayerHelp:SPlayerHelpInfo = SPlayerHelpInfo.fromByteArray(bytes); //玩家协助信息
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			retParam_.oPlayerHelp = oPlayerHelp;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UserHelpTripod = _sessionMgr.getData(sessionID_) as SOrigParam_UserHelpTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UserHelpTripod = new TEvt_UserHelpTripod(TEvt_UserHelpTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家协助九疑鼎
		private function _onTimeOut_UserHelpTripod(sessionID:uint):void
		{
			var retParam:SRetParam_UserHelpTripod = new SRetParam_UserHelpTripod();
			var event_:TEvt_UserHelpTripod = new TEvt_UserHelpTripod(TEvt_UserHelpTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：踢出九疑鼎协助者
		private function _doReturn_ShotOffHelpTripod(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ShotOffHelpTripod = new SRetParam_ShotOffHelpTripod();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETripodType)结果
			var byPos:uint = bytes.readUnsignedByte(); //(无符号8位整数)协助位置(0,1,2)
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)0散仙 1玩家
			retParam_.eResult = eResult;
			retParam_.byPos = byPos;
			retParam_.byType = byType;
			var origParam_:SOrigParam_ShotOffHelpTripod = _sessionMgr.getData(sessionID_) as SOrigParam_ShotOffHelpTripod;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ShotOffHelpTripod = new TEvt_ShotOffHelpTripod(TEvt_ShotOffHelpTripod.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：踢出九疑鼎协助者
		private function _onTimeOut_ShotOffHelpTripod(sessionID:uint):void
		{
			var retParam:SRetParam_ShotOffHelpTripod = new SRetParam_ShotOffHelpTripod();
			var event_:TEvt_ShotOffHelpTripod = new TEvt_ShotOffHelpTripod(TEvt_ShotOffHelpTripod.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求玩家九疑鼎的能被扇火、协助信息
		private function _doReturn_GetTripodStatus(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTripodStatus = new SRetParam_GetTripodStatus();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecStatus:Vector.<STripodStatus> = STripodStatus.vectorFromByteArray(bytes); //玩家九疑鼎的扇火、协助状态
			retParam_.vecStatus = vecStatus;
			var origParam_:SOrigParam_GetTripodStatus = _sessionMgr.getData(sessionID_) as SOrigParam_GetTripodStatus;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTripodStatus = new TEvt_GetTripodStatus(TEvt_GetTripodStatus.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求玩家九疑鼎的能被扇火、协助信息
		private function _onTimeOut_GetTripodStatus(sessionID:uint):void
		{
			var retParam:SRetParam_GetTripodStatus = new SRetParam_GetTripodStatus();
			var event_:TEvt_GetTripodStatus = new TEvt_GetTripodStatus(TEvt_GetTripodStatus.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:TripodProt;

		public static function get instance():TripodProt
		{
			if(_instance == null)
				_instance = new TripodProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function TripodProt()
		{
			_protID = 63;
			_recvFuncList = [
				_doRecv_UpdateTripod //FuncID: 1
			];

			_retFuncList = [
				_doReturn_GetAllTripods, //FuncID: 1
				_doReturn_GetAllFires, //FuncID: 2
				_doReturn_GetTripodData, //FuncID: 3
				_doReturn_ActiveTripod, //FuncID: 4
				_doReturn_UpgradeTripod, //FuncID: 5
				_doReturn_MakeFireTripod, //FuncID: 6
				_doReturn_ClearFireTripod, //FuncID: 7
				_doReturn_GetTripodAward, //FuncID: 8
				_doReturn_SpeedTripod, //FuncID: 9
				_doReturn_AddTripodExtraSoul, //FuncID: 10
				_doReturn_FighterHelpTripod, //FuncID: 11
				_doReturn_UserHelpTripod, //FuncID: 12
				_doReturn_ShotOffHelpTripod, //FuncID: 13
				_doReturn_GetTripodStatus //FuncID: 14
			];

			_timeFuncList = [
				_onTimeOut_GetAllTripods, //FuncID: 1
				_onTimeOut_GetAllFires, //FuncID: 2
				_onTimeOut_GetTripodData, //FuncID: 3
				_onTimeOut_ActiveTripod, //FuncID: 4
				_onTimeOut_UpgradeTripod, //FuncID: 5
				_onTimeOut_MakeFireTripod, //FuncID: 6
				_onTimeOut_ClearFireTripod, //FuncID: 7
				_onTimeOut_GetTripodAward, //FuncID: 8
				_onTimeOut_SpeedTripod, //FuncID: 9
				_onTimeOut_AddTripodExtraSoul, //FuncID: 10
				_onTimeOut_FighterHelpTripod, //FuncID: 11
				_onTimeOut_UserHelpTripod, //FuncID: 12
				_onTimeOut_ShotOffHelpTripod, //FuncID: 13
				_onTimeOut_GetTripodStatus //FuncID: 14
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