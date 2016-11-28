/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    BossProt.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：BOSS相关协议
	 */
	public class BossProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：世界BOSS中复活
		 */
		public function send_WBAlive(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_WBAlive = new SOrigParam_WBAlive();
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
		 * 发送：加持
		 * @param eBuyType (枚举类型：EBossBuyType)购买类型
		 */
		public function send_WBStrength(eBuyType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_WBStrength = new SOrigParam_WBStrength();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eBuyType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：直接攻击boss
		 */
		public function send_WBAttack(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_WBAttack = new SOrigParam_WBAttack();
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
		 * 发送：获取排行榜信息
		 */
		public function send_GetTopList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家自己的排行榜信息
		 */
		public function send_GetSelfInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取boss信息
		 */
		public function send_GetBossInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：进入boss地图
		 */
		public function send_EnterMap(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_EnterMap = new SOrigParam_EnterMap();
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
		 * 发送：离开boss地图
		 */
		public function send_LeaveMap(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_LeaveMap = new SOrigParam_LeaveMap();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：世界BOSS信息通知
		private function _doRecv_BossInfoNotify(bytes:ByteArray):void
		{
			var dwBoosID:uint = bytes.readUnsignedInt(); //(无符号32位整数)bossID
			var dwCurHP:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前血量
			var dwMaxHP:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大血量
			var dwPlayerCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前地图人数
			var event_:REvt_BossInfoNotify = new REvt_BossInfoNotify(REvt_BossInfoNotify.DATA_RECEIVE);
			event_.dwBoosID = dwBoosID;
			event_.dwCurHP = dwCurHP;
			event_.dwMaxHP = dwMaxHP;
			event_.dwPlayerCnt = dwPlayerCnt;
			dispatchEvent(event_);
		}

		//接收处理：排行榜通知
		private function _doRecv_TopListNotify(bytes:ByteArray):void
		{
			var vecTopList:Vector.<SPlayerInfo> = SPlayerInfo.vectorFromByteArray(bytes); //排行榜列表
			var event_:REvt_TopListNotify = new REvt_TopListNotify(REvt_TopListNotify.DATA_RECEIVE);
			event_.vecTopList = vecTopList;
			dispatchEvent(event_);
		}

		//接收处理：个人信息通知
		private function _doRecv_SelfInfoNotify(bytes:ByteArray):void
		{
			var oSelfInfo:SPlayerInfo = SPlayerInfo.fromByteArray(bytes); //玩家信息
			var dwBeginTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var dwEndTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)结束时间
			var dwReliveTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)复活时间
			var dwSilverBufferCdTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)银币加持cd
			var dwSilverBufferCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)银币加持次数
			var dwGoldBufferCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)金币加持次数
			var dwGoldAttackCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)直接攻击次数
			var event_:REvt_SelfInfoNotify = new REvt_SelfInfoNotify(REvt_SelfInfoNotify.DATA_RECEIVE);
			event_.oSelfInfo = oSelfInfo;
			event_.dwBeginTime = dwBeginTime;
			event_.dwEndTime = dwEndTime;
			event_.dwReliveTime = dwReliveTime;
			event_.dwSilverBufferCdTime = dwSilverBufferCdTime;
			event_.dwSilverBufferCnt = dwSilverBufferCnt;
			event_.dwGoldBufferCnt = dwGoldBufferCnt;
			event_.dwGoldAttackCnt = dwGoldAttackCnt;
			dispatchEvent(event_);
		}

		//接收处理：伤害boss信息
		private function _doRecv_AtkInfoNotify(bytes:ByteArray):void
		{
			var dwDamage:uint = bytes.readUnsignedInt(); //(无符号32位整数)本次伤害
			var dwExp:uint = bytes.readUnsignedInt(); //(无符号32位整数)本次活动经验值
			var dwTotalDamage:uint = bytes.readUnsignedInt(); //(无符号32位整数)总伤害
			var dwBossMaxHp:uint = bytes.readUnsignedInt(); //(无符号32位整数)boss最大血量
			var event_:REvt_AtkInfoNotify = new REvt_AtkInfoNotify(REvt_AtkInfoNotify.DATA_RECEIVE);
			event_.dwDamage = dwDamage;
			event_.dwExp = dwExp;
			event_.dwTotalDamage = dwTotalDamage;
			event_.dwBossMaxHp = dwBossMaxHp;
			dispatchEvent(event_);
		}

		//接收处理：玩家名次变化通知
		private function _doRecv_NoChangeNotify(bytes:ByteArray):void
		{
			var dwNo:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家名次
			var event_:REvt_NoChangeNotify = new REvt_NoChangeNotify(REvt_NoChangeNotify.DATA_RECEIVE);
			event_.dwNo = dwNo;
			dispatchEvent(event_);
		}

		//接收处理：玩家奖励获取通知
		private function _doRecv_PrizeNotify(bytes:ByteArray):void
		{
			var vecPlayerPrize:Vector.<SPlayerPrize> = SPlayerPrize.vectorFromByteArray(bytes); //玩家奖励列表
			var event_:REvt_PrizeNotify = new REvt_PrizeNotify(REvt_PrizeNotify.DATA_RECEIVE);
			event_.vecPlayerPrize = vecPlayerPrize;
			dispatchEvent(event_);
		}

		//接收处理：玩家复活时间通知
		private function _doRecv_ReliveTimeNotify(bytes:ByteArray):void
		{
			var dwReliveTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)复活时间
			var event_:REvt_ReliveTimeNotify = new REvt_ReliveTimeNotify(REvt_ReliveTimeNotify.DATA_RECEIVE);
			event_.dwReliveTime = dwReliveTime;
			dispatchEvent(event_);
		}

		//接收处理：活动结束通知
		private function _doRecv_EndNotify(bytes:ByteArray):void
		{
			var dwLeaveTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)离开时间
			var event_:REvt_EndNotify = new REvt_EndNotify(REvt_EndNotify.DATA_RECEIVE);
			event_.dwLeaveTime = dwLeaveTime;
			dispatchEvent(event_);
		}

		//接收处理：玩家直接攻击次数
		private function _doRecv_AttackCountNotify(bytes:ByteArray):void
		{
			var dwAttackCount:uint = bytes.readUnsignedShort(); //(无符号16位整数)玩家直接攻击次数
			var event_:REvt_AttackCountNotify = new REvt_AttackCountNotify(REvt_AttackCountNotify.DATA_RECEIVE);
			event_.dwAttackCount = dwAttackCount;
			dispatchEvent(event_);
		}

		//接收处理：结算通知
		private function _doRecv_GainPrizeNotify(bytes:ByteArray):void
		{
			var dwNo:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家名次
			var dwExp:uint = bytes.readUnsignedInt(); //(无符号32位整数)总共获得经验
			var bKillBoss:Boolean = bytes.readBoolean(); //是否击杀boss
			var event_:REvt_GainPrizeNotify = new REvt_GainPrizeNotify(REvt_GainPrizeNotify.DATA_RECEIVE);
			event_.dwNo = dwNo;
			event_.dwExp = dwExp;
			event_.bKillBoss = bKillBoss;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：世界BOSS中复活
		private function _doReturn_WBAlive(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WBAlive = new SRetParam_WBAlive();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_WBAlive = _sessionMgr.getData(sessionID_) as SOrigParam_WBAlive;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_WBAlive = new TEvt_WBAlive(TEvt_WBAlive.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：世界BOSS中复活
		private function _onTimeOut_WBAlive(sessionID:uint):void
		{
			var retParam:SRetParam_WBAlive = new SRetParam_WBAlive();
			var event_:TEvt_WBAlive = new TEvt_WBAlive(TEvt_WBAlive.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：加持
		private function _doReturn_WBStrength(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WBStrength = new SRetParam_WBStrength();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwSilverBufferCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)银币加持次数
			var dwGoldBufferCnt:uint = bytes.readUnsignedInt(); //(无符号32位整数)金币加持次数
			var dwSilverBufferCdTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)银币加持cd
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.dwSilverBufferCnt = dwSilverBufferCnt;
			retParam_.dwGoldBufferCnt = dwGoldBufferCnt;
			retParam_.dwSilverBufferCdTime = dwSilverBufferCdTime;
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_WBStrength = _sessionMgr.getData(sessionID_) as SOrigParam_WBStrength;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_WBStrength = new TEvt_WBStrength(TEvt_WBStrength.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：加持
		private function _onTimeOut_WBStrength(sessionID:uint):void
		{
			var retParam:SRetParam_WBStrength = new SRetParam_WBStrength();
			var event_:TEvt_WBStrength = new TEvt_WBStrength(TEvt_WBStrength.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：直接攻击boss
		private function _doReturn_WBAttack(bytes:ByteArray):void
		{
			var retParam_:SRetParam_WBAttack = new SRetParam_WBAttack();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_WBAttack = _sessionMgr.getData(sessionID_) as SOrigParam_WBAttack;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_WBAttack = new TEvt_WBAttack(TEvt_WBAttack.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：直接攻击boss
		private function _onTimeOut_WBAttack(sessionID:uint):void
		{
			var retParam:SRetParam_WBAttack = new SRetParam_WBAttack();
			var event_:TEvt_WBAttack = new TEvt_WBAttack(TEvt_WBAttack.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：进入boss地图
		private function _doReturn_EnterMap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterMap = new SRetParam_EnterMap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_EnterMap = _sessionMgr.getData(sessionID_) as SOrigParam_EnterMap;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterMap = new TEvt_EnterMap(TEvt_EnterMap.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：进入boss地图
		private function _onTimeOut_EnterMap(sessionID:uint):void
		{
			var retParam:SRetParam_EnterMap = new SRetParam_EnterMap();
			var event_:TEvt_EnterMap = new TEvt_EnterMap(TEvt_EnterMap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开boss地图
		private function _doReturn_LeaveMap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveMap = new SRetParam_LeaveMap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_LeaveMap = _sessionMgr.getData(sessionID_) as SOrigParam_LeaveMap;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeaveMap = new TEvt_LeaveMap(TEvt_LeaveMap.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：离开boss地图
		private function _onTimeOut_LeaveMap(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveMap = new SRetParam_LeaveMap();
			var event_:TEvt_LeaveMap = new TEvt_LeaveMap(TEvt_LeaveMap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:BossProt;

		public static function get instance():BossProt
		{
			if(_instance == null)
				_instance = new BossProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function BossProt()
		{
			_protID = 25;
			_recvFuncList = [
				_doRecv_BossInfoNotify, //FuncID: 1
				_doRecv_TopListNotify, //FuncID: 2
				_doRecv_SelfInfoNotify, //FuncID: 3
				_doRecv_AtkInfoNotify, //FuncID: 4
				_doRecv_NoChangeNotify, //FuncID: 5
				_doRecv_PrizeNotify, //FuncID: 6
				_doRecv_ReliveTimeNotify, //FuncID: 7
				_doRecv_EndNotify, //FuncID: 8
				_doRecv_AttackCountNotify, //FuncID: 9
				_doRecv_GainPrizeNotify //FuncID: 10
			];

			_retFuncList = [
				_doReturn_WBAlive, //FuncID: 1
				_doReturn_WBStrength, //FuncID: 2
				_doReturn_WBAttack, //FuncID: 3
				_doReturn_EnterMap, //FuncID: 4
				_doReturn_LeaveMap //FuncID: 5
			];

			_timeFuncList = [
				_onTimeOut_WBAlive, //FuncID: 1
				_onTimeOut_WBStrength, //FuncID: 2
				_onTimeOut_WBAttack, //FuncID: 3
				_onTimeOut_EnterMap, //FuncID: 4
				_onTimeOut_LeaveMap //FuncID: 5
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