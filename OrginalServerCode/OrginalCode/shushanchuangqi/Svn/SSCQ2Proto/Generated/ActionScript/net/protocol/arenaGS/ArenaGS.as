/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ArenaGS.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.battleGS.SPlayerFeature;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：竞技场协议
	 */
	public class ArenaGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求自己竞技场信息,同时开启竞技场
		 */
		public function send_ArenaInfoReq(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_ArenaInfoReq = new SOrigParam_ArenaInfoReq();
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
		 * 发送：请求挑战
		 * @param qwDefense (无符号64位整数)被挑战者ID
		 */
		public function send_ArenaChallengeReq(qwDefense:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_ArenaChallengeReq = new SOrigParam_ArenaChallengeReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwDefense);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求购买挑战次数
		 */
		public function send_ArenaByChallengeTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ArenaByChallengeTimes = new SOrigParam_ArenaByChallengeTimes();
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
		 * 发送：请求翻页
		 * @param eLevel (枚举类型：EArenaLevel)段位
		 * @param dwRank (无符号32位整数)请求排名开始名次
		 * @param byNum (无符号8位整数)请求数量
		 */
		public function send_ArenaPageUpReq(eLevel:uint, dwRank:uint, byNum:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ArenaPageUpReq = new SOrigParam_ArenaPageUpReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eLevel);
			bytes_.writeUnsignedInt(dwRank);
			bytes_.writeByte(byNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求清除冷却
		 * @param byType (无符号8位整数)0,历练，1天梯
		 */
		public function send_ArenaClearCDReq(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ArenaClearCDReq = new SOrigParam_ArenaClearCDReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求获取奖池奖励
		 * @param dwLootId (无符号32位整数)奖励包
		 * @param eType (枚举类型：EArenaAwardType)奖励包类型
		 */
		public function send_ArenaGetRankingRewardReq(dwLootId:uint, eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_ArenaGetRankingRewardReq = new SOrigParam_ArenaGetRankingRewardReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwLootId);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：膜拜请求
		 * @param qwRoleID (无符号64位整数)膜拜对象
		 */
		public function send_ArenaWorship(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_ArenaWorship = new SOrigParam_ArenaWorship();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求刷将
		 */
		public function send_FlushNewEnemy(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_FlushNewEnemy = new SOrigParam_FlushNewEnemy();
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
		 * 发送：请求对手信息
		 */
		public function send_GetAllEnemy(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetAllEnemy = new SOrigParam_GetAllEnemy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求奖励信息
		 */
		public function send_GetAllAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_GetAllAward = new SOrigParam_GetAllAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求膜拜信息
		 */
		public function send_GetAllWirship(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_GetAllWirship = new SOrigParam_GetAllWirship();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求计算:奖励信息
		 */
		public function send_GetAllAwardInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_GetAllAwardInfo = new SOrigParam_GetAllAwardInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求对手信息
		 * @param byType (无符号8位整数)0,默认刷对手，1顺次刷对手
		 */
		public function send_ReFluseLadderEnemy(byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_ReFluseLadderEnemy = new SOrigParam_ReFluseLadderEnemy();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：清求领取今日天梯奖励
		 */
		public function send_GetLadderAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_GetLadderAward = new SOrigParam_GetLadderAward();
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
		 * 发送：清求领取今日历练奖励
		 */
		public function send_GetArenaAward(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_GetArenaAward = new SOrigParam_GetArenaAward();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：清求战报
		 */
		public function send_GetLadderReport(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_GetLadderReport = new SOrigParam_GetLadderReport();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求天梯挑战
		 * @param qwEnemyID (无符号64位整数)对手ID
		 * @param dwEnemyRank (无符号32位整数)对手天梯排名
		 */
		public function send_LadderBattle(qwEnemyID:BigInteger, dwEnemyRank:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 17);
			var origParam_:SOrigParam_LadderBattle = new SOrigParam_LadderBattle();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwEnemyID);
			bytes_.writeUnsignedInt(dwEnemyRank);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求天梯排名
		 * @param dwRank (无符号32位整数)请求排名开始名次
		 * @param byNum (无符号8位整数)请求数量
		 */
		public function send_LadderPageUpReq(dwRank:uint, byNum:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 18);
			var origParam_:SOrigParam_LadderPageUpReq = new SOrigParam_LadderPageUpReq();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 18;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwRank);
			bytes_.writeByte(byNum);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求购买天梯挑战次数
		 */
		public function send_ArenaBuyLadderTimes(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 19);
			var origParam_:SOrigParam_ArenaBuyLadderTimes = new SOrigParam_ArenaBuyLadderTimes();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 19;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：通告获得最好天梯排名
		private function _doRecv_UpdateLadderMinRank(bytes:ByteArray):void
		{
			var dwLastRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)前排名,0表示无排名
			var dwNowRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)现排名
			var event_:REvt_UpdateLadderMinRank = new REvt_UpdateLadderMinRank(REvt_UpdateLadderMinRank.DATA_RECEIVE);
			event_.dwLastRank = dwLastRank;
			event_.dwNowRank = dwNowRank;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求自己竞技场信息,同时开启竞技场
		private function _doReturn_ArenaInfoReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaInfoReq = new SRetParam_ArenaInfoReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)结果提示
			var stReturn:SArenaPlayerBaseData2Client = SArenaPlayerBaseData2Client.fromByteArray(bytes); //返回的自己信息
			retParam_.eResult = eResult;
			retParam_.stReturn = stReturn;
			var origParam_:SOrigParam_ArenaInfoReq = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaInfoReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaInfoReq = new TEvt_ArenaInfoReq(TEvt_ArenaInfoReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求自己竞技场信息,同时开启竞技场
		private function _onTimeOut_ArenaInfoReq(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaInfoReq = new SRetParam_ArenaInfoReq();
			var event_:TEvt_ArenaInfoReq = new TEvt_ArenaInfoReq(TEvt_ArenaInfoReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求挑战
		private function _doReturn_ArenaChallengeReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaChallengeReq = new SRetParam_ArenaChallengeReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求挑战返回
			var qwBattleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)战报ID
			var bySuc:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,表示挑战失败，1表示挑战成功
			var dwScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前积分
			var dwRanking:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名
			var wChallenge:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日挑战次数
			var wChallengeBuyTimes:uint = bytes.readUnsignedShort(); //(无符号16位整数)购买的挑战次数
			var dwCDTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)冷却时间戳
			retParam_.eResult = eResult;
			retParam_.qwBattleID = qwBattleID;
			retParam_.bySuc = bySuc;
			retParam_.dwScore = dwScore;
			retParam_.dwRanking = dwRanking;
			retParam_.wChallenge = wChallenge;
			retParam_.wChallengeBuyTimes = wChallengeBuyTimes;
			retParam_.dwCDTimer = dwCDTimer;
			var origParam_:SOrigParam_ArenaChallengeReq = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaChallengeReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaChallengeReq = new TEvt_ArenaChallengeReq(TEvt_ArenaChallengeReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求挑战
		private function _onTimeOut_ArenaChallengeReq(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaChallengeReq = new SRetParam_ArenaChallengeReq();
			var event_:TEvt_ArenaChallengeReq = new TEvt_ArenaChallengeReq(TEvt_ArenaChallengeReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求购买挑战次数
		private function _doReturn_ArenaByChallengeTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaByChallengeTimes = new SRetParam_ArenaByChallengeTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求挑战返回
			var wChallenge:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日挑战次数
			var wChallengeBuyTimes:uint = bytes.readUnsignedShort(); //(无符号16位整数)购买的挑战次数
			retParam_.eResult = eResult;
			retParam_.wChallenge = wChallenge;
			retParam_.wChallengeBuyTimes = wChallengeBuyTimes;
			var origParam_:SOrigParam_ArenaByChallengeTimes = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaByChallengeTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaByChallengeTimes = new TEvt_ArenaByChallengeTimes(TEvt_ArenaByChallengeTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求购买挑战次数
		private function _onTimeOut_ArenaByChallengeTimes(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaByChallengeTimes = new SRetParam_ArenaByChallengeTimes();
			var event_:TEvt_ArenaByChallengeTimes = new TEvt_ArenaByChallengeTimes(TEvt_ArenaByChallengeTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求翻页
		private function _doReturn_ArenaPageUpReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaPageUpReq = new SRetParam_ArenaPageUpReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)查询结果
			var dwSize:uint = bytes.readUnsignedInt(); //(无符号32位整数)本段位的人数总计
			var vecRankData:Vector.<SArenaRank2Client> = SArenaRank2Client.vectorFromByteArray(bytes); //排行榜数据
			retParam_.eResult = eResult;
			retParam_.dwSize = dwSize;
			retParam_.vecRankData = vecRankData;
			var origParam_:SOrigParam_ArenaPageUpReq = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaPageUpReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaPageUpReq = new TEvt_ArenaPageUpReq(TEvt_ArenaPageUpReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求翻页
		private function _onTimeOut_ArenaPageUpReq(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaPageUpReq = new SRetParam_ArenaPageUpReq();
			var event_:TEvt_ArenaPageUpReq = new TEvt_ArenaPageUpReq(TEvt_ArenaPageUpReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求清除冷却
		private function _doReturn_ArenaClearCDReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaClearCDReq = new SRetParam_ArenaClearCDReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求清除冷却返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ArenaClearCDReq = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaClearCDReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaClearCDReq = new TEvt_ArenaClearCDReq(TEvt_ArenaClearCDReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求清除冷却
		private function _onTimeOut_ArenaClearCDReq(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaClearCDReq = new SRetParam_ArenaClearCDReq();
			var event_:TEvt_ArenaClearCDReq = new TEvt_ArenaClearCDReq(TEvt_ArenaClearCDReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求获取奖池奖励
		private function _doReturn_ArenaGetRankingRewardReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaGetRankingRewardReq = new SRetParam_ArenaGetRankingRewardReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求获取奖池奖励返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ArenaGetRankingRewardReq = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaGetRankingRewardReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaGetRankingRewardReq = new TEvt_ArenaGetRankingRewardReq(TEvt_ArenaGetRankingRewardReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求获取奖池奖励
		private function _onTimeOut_ArenaGetRankingRewardReq(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaGetRankingRewardReq = new SRetParam_ArenaGetRankingRewardReq();
			var event_:TEvt_ArenaGetRankingRewardReq = new TEvt_ArenaGetRankingRewardReq(TEvt_ArenaGetRankingRewardReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：膜拜请求
		private function _doReturn_ArenaWorship(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaWorship = new SRetParam_ArenaWorship();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)膜拜请求返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ArenaWorship = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaWorship;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaWorship = new TEvt_ArenaWorship(TEvt_ArenaWorship.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：膜拜请求
		private function _onTimeOut_ArenaWorship(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaWorship = new SRetParam_ArenaWorship();
			var event_:TEvt_ArenaWorship = new TEvt_ArenaWorship(TEvt_ArenaWorship.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求刷将
		private function _doReturn_FlushNewEnemy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FlushNewEnemy = new SRetParam_FlushNewEnemy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var wSelfReflush:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前购买刷新次数
			var wSelfFreeReflush:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前VIP免费刷新次数
			retParam_.eResult = eResult;
			retParam_.wSelfReflush = wSelfReflush;
			retParam_.wSelfFreeReflush = wSelfFreeReflush;
			var origParam_:SOrigParam_FlushNewEnemy = _sessionMgr.getData(sessionID_) as SOrigParam_FlushNewEnemy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FlushNewEnemy = new TEvt_FlushNewEnemy(TEvt_FlushNewEnemy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求刷将
		private function _onTimeOut_FlushNewEnemy(sessionID:uint):void
		{
			var retParam:SRetParam_FlushNewEnemy = new SRetParam_FlushNewEnemy();
			var event_:TEvt_FlushNewEnemy = new TEvt_FlushNewEnemy(TEvt_FlushNewEnemy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求对手信息
		private function _doReturn_GetAllEnemy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllEnemy = new SRetParam_GetAllEnemy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var vecFlushFigter:Vector.<SFlushFitherForClient> = SFlushFitherForClient.vectorFromByteArray(bytes); //最近刷的对手
			retParam_.eResult = eResult;
			retParam_.vecFlushFigter = vecFlushFigter;
			var origParam_:SOrigParam_GetAllEnemy = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllEnemy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllEnemy = new TEvt_GetAllEnemy(TEvt_GetAllEnemy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求对手信息
		private function _onTimeOut_GetAllEnemy(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllEnemy = new SRetParam_GetAllEnemy();
			var event_:TEvt_GetAllEnemy = new TEvt_GetAllEnemy(TEvt_GetAllEnemy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求奖励信息
		private function _doReturn_GetAllAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllAward = new SRetParam_GetAllAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var vecAwards:Vector.<SArenaAward> = SArenaAward.vectorFromByteArray(bytes); //奖励包状态
			retParam_.eResult = eResult;
			retParam_.vecAwards = vecAwards;
			var origParam_:SOrigParam_GetAllAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllAward = new TEvt_GetAllAward(TEvt_GetAllAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求奖励信息
		private function _onTimeOut_GetAllAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllAward = new SRetParam_GetAllAward();
			var event_:TEvt_GetAllAward = new TEvt_GetAllAward(TEvt_GetAllAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求膜拜信息
		private function _doReturn_GetAllWirship(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllWirship = new SRetParam_GetAllWirship();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var vecWirshipFigter:Vector.<SArenaRank2Client> = SArenaRank2Client.vectorFromByteArray(bytes); //膜拜对象列表
			retParam_.eResult = eResult;
			retParam_.vecWirshipFigter = vecWirshipFigter;
			var origParam_:SOrigParam_GetAllWirship = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllWirship;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllWirship = new TEvt_GetAllWirship(TEvt_GetAllWirship.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求膜拜信息
		private function _onTimeOut_GetAllWirship(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllWirship = new SRetParam_GetAllWirship();
			var event_:TEvt_GetAllWirship = new TEvt_GetAllWirship(TEvt_GetAllWirship.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求计算:奖励信息
		private function _doReturn_GetAllAwardInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllAwardInfo = new SRetParam_GetAllAwardInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)返回
			var vecAwards:Vector.<SArenaAward> = SArenaAward.vectorFromByteArray(bytes); //奖励包状态
			retParam_.eResult = eResult;
			retParam_.vecAwards = vecAwards;
			var origParam_:SOrigParam_GetAllAwardInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllAwardInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllAwardInfo = new TEvt_GetAllAwardInfo(TEvt_GetAllAwardInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求计算:奖励信息
		private function _onTimeOut_GetAllAwardInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllAwardInfo = new SRetParam_GetAllAwardInfo();
			var event_:TEvt_GetAllAwardInfo = new TEvt_GetAllAwardInfo(TEvt_GetAllAwardInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求对手信息
		private function _doReturn_ReFluseLadderEnemy(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReFluseLadderEnemy = new SRetParam_ReFluseLadderEnemy();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var vecFlushFigter:Vector.<SFlushFitherForClient> = SFlushFitherForClient.vectorFromByteArray(bytes); //最近刷的对手
			retParam_.eResult = eResult;
			retParam_.vecFlushFigter = vecFlushFigter;
			var origParam_:SOrigParam_ReFluseLadderEnemy = _sessionMgr.getData(sessionID_) as SOrigParam_ReFluseLadderEnemy;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReFluseLadderEnemy = new TEvt_ReFluseLadderEnemy(TEvt_ReFluseLadderEnemy.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求对手信息
		private function _onTimeOut_ReFluseLadderEnemy(sessionID:uint):void
		{
			var retParam:SRetParam_ReFluseLadderEnemy = new SRetParam_ReFluseLadderEnemy();
			var event_:TEvt_ReFluseLadderEnemy = new TEvt_ReFluseLadderEnemy(TEvt_ReFluseLadderEnemy.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清求领取今日天梯奖励
		private function _doReturn_GetLadderAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetLadderAward = new SRetParam_GetLadderAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetLadderAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetLadderAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetLadderAward = new TEvt_GetLadderAward(TEvt_GetLadderAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清求领取今日天梯奖励
		private function _onTimeOut_GetLadderAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetLadderAward = new SRetParam_GetLadderAward();
			var event_:TEvt_GetLadderAward = new TEvt_GetLadderAward(TEvt_GetLadderAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清求领取今日历练奖励
		private function _doReturn_GetArenaAward(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetArenaAward = new SRetParam_GetArenaAward();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetArenaAward = _sessionMgr.getData(sessionID_) as SOrigParam_GetArenaAward;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetArenaAward = new TEvt_GetArenaAward(TEvt_GetArenaAward.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清求领取今日历练奖励
		private function _onTimeOut_GetArenaAward(sessionID:uint):void
		{
			var retParam:SRetParam_GetArenaAward = new SRetParam_GetArenaAward();
			var event_:TEvt_GetArenaAward = new TEvt_GetArenaAward(TEvt_GetArenaAward.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清求战报
		private function _doReturn_GetLadderReport(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetLadderReport = new SRetParam_GetLadderReport();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var vecReport:Vector.<SLadderReport> = SLadderReport.vectorFromByteArray(bytes); //请求刷将返回
			retParam_.eResult = eResult;
			retParam_.vecReport = vecReport;
			var origParam_:SOrigParam_GetLadderReport = _sessionMgr.getData(sessionID_) as SOrigParam_GetLadderReport;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetLadderReport = new TEvt_GetLadderReport(TEvt_GetLadderReport.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清求战报
		private function _onTimeOut_GetLadderReport(sessionID:uint):void
		{
			var retParam:SRetParam_GetLadderReport = new SRetParam_GetLadderReport();
			var event_:TEvt_GetLadderReport = new TEvt_GetLadderReport(TEvt_GetLadderReport.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求天梯挑战
		private function _doReturn_LadderBattle(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LadderBattle = new SRetParam_LadderBattle();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求刷将返回
			var bySuc:uint = bytes.readUnsignedByte(); //(无符号8位整数)0,失败，1成功
			var vecFlushFigter:Vector.<SFlushFitherForClient> = SFlushFitherForClient.vectorFromByteArray(bytes); //最近刷的对手
			var dwSelfRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)自己排名
			var dwLadderTimes:uint = bytes.readUnsignedShort(); //(无符号16位整数)今日挑战天梯次数
			var dwLadderCDTimer:uint = bytes.readUnsignedInt(); //(无符号32位整数)冷却时间戳
			var dwMinLadderRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)天梯最好排名,0表示无排名
			var dwLadderBuyTimes:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买的天梯挑战次数
			retParam_.eResult = eResult;
			retParam_.bySuc = bySuc;
			retParam_.vecFlushFigter = vecFlushFigter;
			retParam_.dwSelfRank = dwSelfRank;
			retParam_.dwLadderTimes = dwLadderTimes;
			retParam_.dwLadderCDTimer = dwLadderCDTimer;
			retParam_.dwMinLadderRank = dwMinLadderRank;
			retParam_.dwLadderBuyTimes = dwLadderBuyTimes;
			var origParam_:SOrigParam_LadderBattle = _sessionMgr.getData(sessionID_) as SOrigParam_LadderBattle;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LadderBattle = new TEvt_LadderBattle(TEvt_LadderBattle.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求天梯挑战
		private function _onTimeOut_LadderBattle(sessionID:uint):void
		{
			var retParam:SRetParam_LadderBattle = new SRetParam_LadderBattle();
			var event_:TEvt_LadderBattle = new TEvt_LadderBattle(TEvt_LadderBattle.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求天梯排名
		private function _doReturn_LadderPageUpReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LadderPageUpReq = new SRetParam_LadderPageUpReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)查询结果
			var vecRankData:Vector.<SArenaRank2Client> = SArenaRank2Client.vectorFromByteArray(bytes); //排行榜数据
			retParam_.eResult = eResult;
			retParam_.vecRankData = vecRankData;
			var origParam_:SOrigParam_LadderPageUpReq = _sessionMgr.getData(sessionID_) as SOrigParam_LadderPageUpReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LadderPageUpReq = new TEvt_LadderPageUpReq(TEvt_LadderPageUpReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求天梯排名
		private function _onTimeOut_LadderPageUpReq(sessionID:uint):void
		{
			var retParam:SRetParam_LadderPageUpReq = new SRetParam_LadderPageUpReq();
			var event_:TEvt_LadderPageUpReq = new TEvt_LadderPageUpReq(TEvt_LadderPageUpReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求购买天梯挑战次数
		private function _doReturn_ArenaBuyLadderTimes(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ArenaBuyLadderTimes = new SRetParam_ArenaBuyLadderTimes();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EArenaResult)请求购买返回
			var dwLadderBuyTimesToday:uint = bytes.readUnsignedInt(); //(无符号32位整数)今日购买天梯挑战次数
			var dwLadderBuyTimes:uint = bytes.readUnsignedInt(); //(无符号32位整数)购买的天梯挑战次数
			retParam_.eResult = eResult;
			retParam_.dwLadderBuyTimesToday = dwLadderBuyTimesToday;
			retParam_.dwLadderBuyTimes = dwLadderBuyTimes;
			var origParam_:SOrigParam_ArenaBuyLadderTimes = _sessionMgr.getData(sessionID_) as SOrigParam_ArenaBuyLadderTimes;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ArenaBuyLadderTimes = new TEvt_ArenaBuyLadderTimes(TEvt_ArenaBuyLadderTimes.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求购买天梯挑战次数
		private function _onTimeOut_ArenaBuyLadderTimes(sessionID:uint):void
		{
			var retParam:SRetParam_ArenaBuyLadderTimes = new SRetParam_ArenaBuyLadderTimes();
			var event_:TEvt_ArenaBuyLadderTimes = new TEvt_ArenaBuyLadderTimes(TEvt_ArenaBuyLadderTimes.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ArenaGS;

		public static function get instance():ArenaGS
		{
			if(_instance == null)
				_instance = new ArenaGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ArenaGS()
		{
			_protID = 26;
			_recvFuncList = [
				_doRecv_UpdateLadderMinRank //FuncID: 1
			];

			_retFuncList = [
				_doReturn_ArenaInfoReq, //FuncID: 1
				_doReturn_ArenaChallengeReq, //FuncID: 2
				_doReturn_ArenaByChallengeTimes, //FuncID: 3
				_doReturn_ArenaPageUpReq, //FuncID: 4
				_doReturn_ArenaClearCDReq, //FuncID: 5
				_doReturn_ArenaGetRankingRewardReq, //FuncID: 6
				_doReturn_ArenaWorship, //FuncID: 7
				_doReturn_FlushNewEnemy, //FuncID: 8
				_doReturn_GetAllEnemy, //FuncID: 9
				_doReturn_GetAllAward, //FuncID: 10
				_doReturn_GetAllWirship, //FuncID: 11
				_doReturn_GetAllAwardInfo, //FuncID: 12
				_doReturn_ReFluseLadderEnemy, //FuncID: 13
				_doReturn_GetLadderAward, //FuncID: 14
				_doReturn_GetArenaAward, //FuncID: 15
				_doReturn_GetLadderReport, //FuncID: 16
				_doReturn_LadderBattle, //FuncID: 17
				_doReturn_LadderPageUpReq, //FuncID: 18
				_doReturn_ArenaBuyLadderTimes //FuncID: 19
			];

			_timeFuncList = [
				_onTimeOut_ArenaInfoReq, //FuncID: 1
				_onTimeOut_ArenaChallengeReq, //FuncID: 2
				_onTimeOut_ArenaByChallengeTimes, //FuncID: 3
				_onTimeOut_ArenaPageUpReq, //FuncID: 4
				_onTimeOut_ArenaClearCDReq, //FuncID: 5
				_onTimeOut_ArenaGetRankingRewardReq, //FuncID: 6
				_onTimeOut_ArenaWorship, //FuncID: 7
				_onTimeOut_FlushNewEnemy, //FuncID: 8
				_onTimeOut_GetAllEnemy, //FuncID: 9
				_onTimeOut_GetAllAward, //FuncID: 10
				_onTimeOut_GetAllWirship, //FuncID: 11
				_onTimeOut_GetAllAwardInfo, //FuncID: 12
				_onTimeOut_ReFluseLadderEnemy, //FuncID: 13
				_onTimeOut_GetLadderAward, //FuncID: 14
				_onTimeOut_GetArenaAward, //FuncID: 15
				_onTimeOut_GetLadderReport, //FuncID: 16
				_onTimeOut_LadderBattle, //FuncID: 17
				_onTimeOut_LadderPageUpReq, //FuncID: 18
				_onTimeOut_ArenaBuyLadderTimes //FuncID: 19
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