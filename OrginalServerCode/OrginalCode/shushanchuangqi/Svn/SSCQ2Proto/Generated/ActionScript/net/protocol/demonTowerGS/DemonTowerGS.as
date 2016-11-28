/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    DemonTowerGS.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：锁妖塔
	 */
	public class DemonTowerGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：进入锁妖塔
		 * @param dwFloorID (无符号32位整数)层数
		 */
		public function send_EnterDemonTower(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_EnterDemonTower = new SOrigParam_EnterDemonTower();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：离开锁妖塔
		 */
		public function send_LeaveDemonTower(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_LeaveDemonTower = new SOrigParam_LeaveDemonTower();
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
		 * 发送：封印怪物(挑战?)
		 * @param dwFloorID (无符号32位整数)层数
		 */
		public function send_SealMonster(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_SealMonster = new SOrigParam_SealMonster();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：镇守锁妖塔
		 * @param dwFloorID (无符号32位整数)层数 0表示放弃镇守位置
		 * @param dwGuardPos (无符号32位整数)镇守位置
		 */
		public function send_GuardAtk(dwFloorID:uint, dwGuardPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GuardAtk = new SOrigParam_GuardAtk();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			bytes_.writeUnsignedInt(dwGuardPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：抢夺镇守位置
		 * @param dwFloorID (无符号32位整数)层数
		 * @param dwGuardPos (无符号32位整数)镇守位置
		 */
		public function send_AtkPlayer(dwFloorID:uint, dwGuardPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_AtkPlayer = new SOrigParam_AtkPlayer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			bytes_.writeUnsignedInt(dwGuardPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：领取奖励
		 * @param ePrizeType (枚举类型：EDemonTowerPrize)奖励类型
		 */
		public function send_TakePrize(ePrizeType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(ePrizeType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取镇守榜
		 * @param wPage (无符号16位整数)页码 1开始
		 * @param wPageItemCount (无符号16位整数)每页显示数目 默认5
		 */
		public function send_GetTopList(wPage:uint, wPageItemCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetTopList = new SOrigParam_GetTopList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPage);
			bytes_.writeShort(wPageItemCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取本人镇妖塔相关信息
		 */
		public function send_GetDemonTowerInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetDemonTowerInfo = new SOrigParam_GetDemonTowerInfo();
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
		 * 发送：获取镇守信息信息
		 * @param dwFloorID (无符号32位整数)镇守层
		 */
		public function send_GetGuardInfo(dwFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetGuardInfo = new SOrigParam_GetGuardInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：恢复元神
		 * @param dwCount (无符号32位整数)物品数量
		 */
		public function send_Restore(dwCount:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：增加聚魂速度
		 * @param dwCount (无符号32位整数)物品数量
		 */
		public function send_AddSpeed(dwCount:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家镇守信息
		 * @param qwUserID (无符号64位整数)账号ID
		 */
		public function send_GetPlayerInfo(qwUserID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_GetPlayerInfo = new SOrigParam_GetPlayerInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：清除pvp战斗cd
		 */
		public function send_ClearFightCd(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_ClearFightCd = new SOrigParam_ClearFightCd();
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
		 * 发送：获取过关信息
		 * @param wFloorID (无符号16位整数)通关层
		 */
		public function send_GetPassInfo(wFloorID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_GetPassInfo = new SOrigParam_GetPassInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wFloorID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：锁妖塔镇守信息
		private function _doRecv_GuardInfoNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var vecGuardInfo:Vector.<GuardInfo> = GuardInfo.vectorFromByteArray(bytes); //镇守玩家信息
			var event_:REvt_GuardInfoNotify = new REvt_GuardInfoNotify(REvt_GuardInfoNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			event_.vecGuardInfo = vecGuardInfo;
			dispatchEvent(event_);
		}

		//接收处理：锁妖塔镇守信息更新
		private function _doRecv_GuardInfoChangeNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var dwPos:uint = bytes.readUnsignedInt(); //(无符号32位整数)镇守玩家信息
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)玩家ID 0 表示该位置放弃镇守
			var oGuardInfo:GuardInfo = GuardInfo.fromByteArray(bytes); //镇守信息
			var event_:REvt_GuardInfoChangeNotify = new REvt_GuardInfoChangeNotify(REvt_GuardInfoChangeNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			event_.dwPos = dwPos;
			event_.qwUserID = qwUserID;
			event_.oGuardInfo = oGuardInfo;
			dispatchEvent(event_);
		}

		//接收处理：锁妖塔过关通知
		private function _doRecv_PassDemonTowerNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)锁妖塔过关层数
			var event_:REvt_PassDemonTowerNotify = new REvt_PassDemonTowerNotify(REvt_PassDemonTowerNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			dispatchEvent(event_);
		}

		//接收处理：锁妖塔镇守攻击cd
		private function _doRecv_DemonTowerAtkCDNotify(bytes:ByteArray):void
		{
			var dwGuardNextAttackTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)锁妖塔可攻击最早时间
			var event_:REvt_DemonTowerAtkCDNotify = new REvt_DemonTowerAtkCDNotify(REvt_DemonTowerAtkCDNotify.DATA_RECEIVE);
			event_.dwGuardNextAttackTime = dwGuardNextAttackTime;
			dispatchEvent(event_);
		}

		//接收处理：镇妖塔玩家信息
		private function _doRecv_DemonTowerPlayerNotify(bytes:ByteArray):void
		{
			var oDemonTowerPlayerInfo:SDemonTowerPlayer = SDemonTowerPlayer.fromByteArray(bytes); //镇妖塔玩家信息
			var event_:REvt_DemonTowerPlayerNotify = new REvt_DemonTowerPlayerNotify(REvt_DemonTowerPlayerNotify.DATA_RECEIVE);
			event_.oDemonTowerPlayerInfo = oDemonTowerPlayerInfo;
			dispatchEvent(event_);
		}

		//接收处理：镇妖塔错误信息
		private function _doRecv_DemonTowerErrorNotify(bytes:ByteArray):void
		{
			var dwError:uint = bytes.readUnsignedInt(); //(无符号32位整数)错误码
			var event_:REvt_DemonTowerErrorNotify = new REvt_DemonTowerErrorNotify(REvt_DemonTowerErrorNotify.DATA_RECEIVE);
			event_.dwError = dwError;
			dispatchEvent(event_);
		}

		//接收处理：镇守锁妖塔通知
		private function _doRecv_GuardSucessNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var dwGuardPos:uint = bytes.readUnsignedInt(); //(无符号32位整数)镇守位置
			var event_:REvt_GuardSucessNotify = new REvt_GuardSucessNotify(REvt_GuardSucessNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			event_.dwGuardPos = dwGuardPos;
			dispatchEvent(event_);
		}

		//接收处理：19点重置奖励通知
		private function _doRecv_DemonTowerResetNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var dwGuardPos:uint = bytes.readUnsignedInt(); //(无符号32位整数)镇守位置
			var vecSoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes); //获得的魄奖励
			var event_:REvt_DemonTowerResetNotify = new REvt_DemonTowerResetNotify(REvt_DemonTowerResetNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			event_.dwGuardPos = dwGuardPos;
			event_.vecSoulPrize = vecSoulPrize;
			dispatchEvent(event_);
		}

		//接收处理：镇妖塔被抢通知
		private function _doRecv_DemonTowerBeAttackNotify(bytes:ByteArray):void
		{
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var dwPos:uint = bytes.readUnsignedInt(); //(无符号32位整数)位置
			var qwAtkUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)抢夺人的Id
			var strRole:String = BytesUtil.readString(bytes); //抢夺人的名字
			var vecFailSoulPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes); //失败后的魄奖励
			var event_:REvt_DemonTowerBeAttackNotify = new REvt_DemonTowerBeAttackNotify(REvt_DemonTowerBeAttackNotify.DATA_RECEIVE);
			event_.dwFloorID = dwFloorID;
			event_.dwPos = dwPos;
			event_.qwAtkUserID = qwAtkUserID;
			event_.strRole = strRole;
			event_.vecFailSoulPrize = vecFailSoulPrize;
			dispatchEvent(event_);
		}

		//接收处理：玩家切层通知
		private function _doRecv_EnterDemonTowerNotify(bytes:ByteArray):void
		{
			var dwCurFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前进入的层数
			var event_:REvt_EnterDemonTowerNotify = new REvt_EnterDemonTowerNotify(REvt_EnterDemonTowerNotify.DATA_RECEIVE);
			event_.dwCurFloorID = dwCurFloorID;
			dispatchEvent(event_);
		}

		//接收处理：镇妖塔分身崩溃通知
		private function _doRecv_PrizeNotify(bytes:ByteArray):void
		{
			var eDemonTowerPrize:uint = bytes.readUnsignedByte(); //(枚举类型：EDemonTowerPrize)魄奖励类型
			var dwFloorID:uint = bytes.readUnsignedInt(); //(无符号32位整数)层数
			var dwGuardPos:uint = bytes.readUnsignedInt(); //(无符号32位整数)镇守位置
			var vecPrize:Vector.<MoneyInfo> = MoneyInfo.vectorFromByteArray(bytes); //魄奖励
			var event_:REvt_PrizeNotify = new REvt_PrizeNotify(REvt_PrizeNotify.DATA_RECEIVE);
			event_.eDemonTowerPrize = eDemonTowerPrize;
			event_.dwFloorID = dwFloorID;
			event_.dwGuardPos = dwGuardPos;
			event_.vecPrize = vecPrize;
			dispatchEvent(event_);
		}

		//接收处理：过关信息
		private function _doRecv_PassInfoNotify(bytes:ByteArray):void
		{
			var wFloorID:uint = bytes.readUnsignedShort(); //(无符号16位整数)通关层
			var vecMinRound:Vector.<SDemonTowerKillMonster> = SDemonTowerKillMonster.vectorFromByteArray(bytes); //最快通关
			var vecMinBattlePoint:Vector.<SDemonTowerKillMonster> = SDemonTowerKillMonster.vectorFromByteArray(bytes); //最小战斗力通关
			var event_:REvt_PassInfoNotify = new REvt_PassInfoNotify(REvt_PassInfoNotify.DATA_RECEIVE);
			event_.wFloorID = wFloorID;
			event_.vecMinRound = vecMinRound;
			event_.vecMinBattlePoint = vecMinBattlePoint;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：进入锁妖塔
		private function _doReturn_EnterDemonTower(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterDemonTower = new SRetParam_EnterDemonTower();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_EnterDemonTower = _sessionMgr.getData(sessionID_) as SOrigParam_EnterDemonTower;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterDemonTower = new TEvt_EnterDemonTower(TEvt_EnterDemonTower.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：进入锁妖塔
		private function _onTimeOut_EnterDemonTower(sessionID:uint):void
		{
			var retParam:SRetParam_EnterDemonTower = new SRetParam_EnterDemonTower();
			var event_:TEvt_EnterDemonTower = new TEvt_EnterDemonTower(TEvt_EnterDemonTower.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开锁妖塔
		private function _doReturn_LeaveDemonTower(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveDemonTower = new SRetParam_LeaveDemonTower();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_LeaveDemonTower = _sessionMgr.getData(sessionID_) as SOrigParam_LeaveDemonTower;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeaveDemonTower = new TEvt_LeaveDemonTower(TEvt_LeaveDemonTower.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：离开锁妖塔
		private function _onTimeOut_LeaveDemonTower(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveDemonTower = new SRetParam_LeaveDemonTower();
			var event_:TEvt_LeaveDemonTower = new TEvt_LeaveDemonTower(TEvt_LeaveDemonTower.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：封印怪物(挑战?)
		private function _doReturn_SealMonster(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SealMonster = new SRetParam_SealMonster();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_SealMonster = _sessionMgr.getData(sessionID_) as SOrigParam_SealMonster;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SealMonster = new TEvt_SealMonster(TEvt_SealMonster.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：封印怪物(挑战?)
		private function _onTimeOut_SealMonster(sessionID:uint):void
		{
			var retParam:SRetParam_SealMonster = new SRetParam_SealMonster();
			var event_:TEvt_SealMonster = new TEvt_SealMonster(TEvt_SealMonster.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：镇守锁妖塔
		private function _doReturn_GuardAtk(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GuardAtk = new SRetParam_GuardAtk();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_GuardAtk = _sessionMgr.getData(sessionID_) as SOrigParam_GuardAtk;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GuardAtk = new TEvt_GuardAtk(TEvt_GuardAtk.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：镇守锁妖塔
		private function _onTimeOut_GuardAtk(sessionID:uint):void
		{
			var retParam:SRetParam_GuardAtk = new SRetParam_GuardAtk();
			var event_:TEvt_GuardAtk = new TEvt_GuardAtk(TEvt_GuardAtk.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：抢夺镇守位置
		private function _doReturn_AtkPlayer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AtkPlayer = new SRetParam_AtkPlayer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_AtkPlayer = _sessionMgr.getData(sessionID_) as SOrigParam_AtkPlayer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AtkPlayer = new TEvt_AtkPlayer(TEvt_AtkPlayer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：抢夺镇守位置
		private function _onTimeOut_AtkPlayer(sessionID:uint):void
		{
			var retParam:SRetParam_AtkPlayer = new SRetParam_AtkPlayer();
			var event_:TEvt_AtkPlayer = new TEvt_AtkPlayer(TEvt_AtkPlayer.DATA_RETURN);
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
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
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

		//返回处理：获取镇守榜
		private function _doReturn_GetTopList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTopList = new SRetParam_GetTopList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oDemonFloorPage:SDemonFloorPage = SDemonFloorPage.fromByteArray(bytes); //分页信息
			retParam_.oDemonFloorPage = oDemonFloorPage;
			var origParam_:SOrigParam_GetTopList = _sessionMgr.getData(sessionID_) as SOrigParam_GetTopList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTopList = new TEvt_GetTopList(TEvt_GetTopList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取镇守榜
		private function _onTimeOut_GetTopList(sessionID:uint):void
		{
			var retParam:SRetParam_GetTopList = new SRetParam_GetTopList();
			var event_:TEvt_GetTopList = new TEvt_GetTopList(TEvt_GetTopList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取本人镇妖塔相关信息
		private function _doReturn_GetDemonTowerInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetDemonTowerInfo = new SRetParam_GetDemonTowerInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功 1-失败（非错误，没有进过镇妖塔）
			var oDemonTowerPlayer:SDemonTowerPlayer = SDemonTowerPlayer.fromByteArray(bytes); //玩家镇守信息
			retParam_.dwRet = dwRet;
			retParam_.oDemonTowerPlayer = oDemonTowerPlayer;
			var origParam_:SOrigParam_GetDemonTowerInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetDemonTowerInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetDemonTowerInfo = new TEvt_GetDemonTowerInfo(TEvt_GetDemonTowerInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取本人镇妖塔相关信息
		private function _onTimeOut_GetDemonTowerInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetDemonTowerInfo = new SRetParam_GetDemonTowerInfo();
			var event_:TEvt_GetDemonTowerInfo = new TEvt_GetDemonTowerInfo(TEvt_GetDemonTowerInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取镇守信息信息
		private function _doReturn_GetGuardInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuardInfo = new SRetParam_GetGuardInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecGuardInfo:Vector.<GuardInfo> = GuardInfo.vectorFromByteArray(bytes); //镇守信息信息
			retParam_.vecGuardInfo = vecGuardInfo;
			var origParam_:SOrigParam_GetGuardInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuardInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuardInfo = new TEvt_GetGuardInfo(TEvt_GetGuardInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取镇守信息信息
		private function _onTimeOut_GetGuardInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuardInfo = new SRetParam_GetGuardInfo();
			var event_:TEvt_GetGuardInfo = new TEvt_GetGuardInfo(TEvt_GetGuardInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取玩家镇守信息
		private function _doReturn_GetPlayerInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPlayerInfo = new SRetParam_GetPlayerInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0 成功 1玩家不存在
			var oDemonFloorPlayer:SDemonFloorPlayer = SDemonFloorPlayer.fromByteArray(bytes); //玩家镇守信息
			retParam_.bRet = bRet;
			retParam_.oDemonFloorPlayer = oDemonFloorPlayer;
			var origParam_:SOrigParam_GetPlayerInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPlayerInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPlayerInfo = new TEvt_GetPlayerInfo(TEvt_GetPlayerInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取玩家镇守信息
		private function _onTimeOut_GetPlayerInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPlayerInfo = new SRetParam_GetPlayerInfo();
			var event_:TEvt_GetPlayerInfo = new TEvt_GetPlayerInfo(TEvt_GetPlayerInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：清除pvp战斗cd
		private function _doReturn_ClearFightCd(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ClearFightCd = new SRetParam_ClearFightCd();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0成功 其他失败
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_ClearFightCd = _sessionMgr.getData(sessionID_) as SOrigParam_ClearFightCd;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ClearFightCd = new TEvt_ClearFightCd(TEvt_ClearFightCd.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：清除pvp战斗cd
		private function _onTimeOut_ClearFightCd(sessionID:uint):void
		{
			var retParam:SRetParam_ClearFightCd = new SRetParam_ClearFightCd();
			var event_:TEvt_ClearFightCd = new TEvt_ClearFightCd(TEvt_ClearFightCd.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取过关信息
		private function _doReturn_GetPassInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPassInfo = new SRetParam_GetPassInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecMinRound:Vector.<SDemonTowerKillMonster> = SDemonTowerKillMonster.vectorFromByteArray(bytes); //最快通关
			var vecMinBattlePoint:Vector.<SDemonTowerKillMonster> = SDemonTowerKillMonster.vectorFromByteArray(bytes); //最小战斗力通关
			retParam_.vecMinRound = vecMinRound;
			retParam_.vecMinBattlePoint = vecMinBattlePoint;
			var origParam_:SOrigParam_GetPassInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPassInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPassInfo = new TEvt_GetPassInfo(TEvt_GetPassInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取过关信息
		private function _onTimeOut_GetPassInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPassInfo = new SRetParam_GetPassInfo();
			var event_:TEvt_GetPassInfo = new TEvt_GetPassInfo(TEvt_GetPassInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:DemonTowerGS;

		public static function get instance():DemonTowerGS
		{
			if(_instance == null)
				_instance = new DemonTowerGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function DemonTowerGS()
		{
			_protID = 71;
			_recvFuncList = [
				_doRecv_GuardInfoNotify, //FuncID: 1
				_doRecv_GuardInfoChangeNotify, //FuncID: 2
				_doRecv_PassDemonTowerNotify, //FuncID: 3
				_doRecv_DemonTowerAtkCDNotify, //FuncID: 4
				_doRecv_DemonTowerPlayerNotify, //FuncID: 5
				_doRecv_DemonTowerErrorNotify, //FuncID: 6
				_doRecv_GuardSucessNotify, //FuncID: 7
				_doRecv_DemonTowerResetNotify, //FuncID: 8
				_doRecv_DemonTowerBeAttackNotify, //FuncID: 9
				_doRecv_EnterDemonTowerNotify, //FuncID: 10
				_doRecv_PrizeNotify, //FuncID: 11
				_doRecv_PassInfoNotify //FuncID: 12
			];

			_retFuncList = [
				_doReturn_EnterDemonTower, //FuncID: 1
				_doReturn_LeaveDemonTower, //FuncID: 2
				_doReturn_SealMonster, //FuncID: 3
				_doReturn_GuardAtk, //FuncID: 4
				_doReturn_AtkPlayer, //FuncID: 5
				_doReturn_TakePrize, //FuncID: 6
				_doReturn_GetTopList, //FuncID: 7
				_doReturn_GetDemonTowerInfo, //FuncID: 8
				_doReturn_GetGuardInfo, //FuncID: 9
				_doReturn_GetPlayerInfo, //FuncID: 10
				_doReturn_ClearFightCd, //FuncID: 11
				_doReturn_GetPassInfo //FuncID: 12
			];

			_timeFuncList = [
				_onTimeOut_EnterDemonTower, //FuncID: 1
				_onTimeOut_LeaveDemonTower, //FuncID: 2
				_onTimeOut_SealMonster, //FuncID: 3
				_onTimeOut_GuardAtk, //FuncID: 4
				_onTimeOut_AtkPlayer, //FuncID: 5
				_onTimeOut_TakePrize, //FuncID: 6
				_onTimeOut_GetTopList, //FuncID: 7
				_onTimeOut_GetDemonTowerInfo, //FuncID: 8
				_onTimeOut_GetGuardInfo, //FuncID: 9
				_onTimeOut_GetPlayerInfo, //FuncID: 10
				_onTimeOut_ClearFightCd, //FuncID: 11
				_onTimeOut_GetPassInfo //FuncID: 12
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