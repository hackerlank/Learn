/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ShushanBattleProt.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.mapProt.SPlayerAppear;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：蜀山论剑相关协议
	 */
	public class ShushanBattleProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：蜀山论剑准备/开始/结束信息
		 */
		public function send_GetBattleStartInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求蜀山论剑玩家的配对信息
		 */
		public function send_GetPlayerPairInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求连杀王、荣誉王信息
		 */
		public function send_GetFirstPlayer():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：参加蜀山论剑活动
		 */
		public function send_PlayerEnter(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_PlayerEnter = new SOrigParam_PlayerEnter();
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
		 * 发送：退出蜀山论剑活动
		 */
		public function send_PlayerLeave(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_PlayerLeave = new SOrigParam_PlayerLeave();
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
		 * 发送：使用蜀山论剑技能
		 * @param bySkillID (无符号8位整数)技能ID
		 */
		public function send_UseSkill(bySkillID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_UseSkill = new SOrigParam_UseSkill();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(bySkillID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买蜀山论剑霸气or怒气
		 * @param byFlag (无符号8位整数)购买类型:0霸气 1怒气
		 */
		public function send_BuySkill(byFlag:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_BuySkill = new SOrigParam_BuySkill();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byFlag);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：蜀山论剑准备/开始/结束信息
		private function _doRecv_BattleStartInfo(bytes:ByteArray):void
		{
			var byStatus:uint = bytes.readUnsignedByte(); //(无符号8位整数)状态=>0:准备 1:开始 2:结束
			var dwTimeLeft:uint = bytes.readUnsignedInt(); //(无符号32位整数)byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
			var event_:REvt_BattleStartInfo = new REvt_BattleStartInfo(REvt_BattleStartInfo.DATA_RECEIVE);
			event_.byStatus = byStatus;
			event_.dwTimeLeft = dwTimeLeft;
			dispatchEvent(event_);
		}

		//接收处理：蜀山论剑玩家的配对信息
		private function _doRecv_PlayerPairInfo(bytes:ByteArray):void
		{
			var stPairInfo:SSSBattlePairInfo = SSSBattlePairInfo.fromByteArray(bytes); //玩家的配对信息
			var event_:REvt_PlayerPairInfo = new REvt_PlayerPairInfo(REvt_PlayerPairInfo.DATA_RECEIVE);
			event_.stPairInfo = stPairInfo;
			dispatchEvent(event_);
		}

		//接收处理：广播连杀王玩家信息
		private function _doRecv_TopKiller(bytes:ByteArray):void
		{
			var strName:String = BytesUtil.readString(bytes); //玩家名字
			var byTopStreak:uint = bytes.readUnsignedByte(); //(无符号8位整数)最高连杀数
			var event_:REvt_TopKiller = new REvt_TopKiller(REvt_TopKiller.DATA_RECEIVE);
			event_.strName = strName;
			event_.byTopStreak = byTopStreak;
			dispatchEvent(event_);
		}

		//接收处理：广播荣誉王玩家信息
		private function _doRecv_HonorKinger(bytes:ByteArray):void
		{
			var strName:String = BytesUtil.readString(bytes); //玩家名字
			var wMaxHonor:uint = bytes.readUnsignedShort(); //(无符号16位整数)最高荣誉值
			var event_:REvt_HonorKinger = new REvt_HonorKinger(REvt_HonorKinger.DATA_RECEIVE);
			event_.strName = strName;
			event_.wMaxHonor = wMaxHonor;
			dispatchEvent(event_);
		}

		//接收处理：蜀山论剑玩家的战报信息
		private function _doRecv_BattleReportInfo(bytes:ByteArray):void
		{
			var byType:uint = bytes.readUnsignedByte(); //(无符号8位整数)0表示个人战报 1表示全部
			var vecReport:Vector.<SSSBattleReport> = SSSBattleReport.vectorFromByteArray(bytes); //玩家的战斗信息
			var event_:REvt_BattleReportInfo = new REvt_BattleReportInfo(REvt_BattleReportInfo.DATA_RECEIVE);
			event_.byType = byType;
			event_.vecReport = vecReport;
			dispatchEvent(event_);
		}

		//接收处理：蜀山论剑玩家使用技能信息
		private function _doRecv_UseSkillInfo(bytes:ByteArray):void
		{
			var stUseSkill:SSSBattleUseSkill = SSSBattleUseSkill.fromByteArray(bytes); //使用技能信息
			var event_:REvt_UseSkillInfo = new REvt_UseSkillInfo(REvt_UseSkillInfo.DATA_RECEIVE);
			event_.stUseSkill = stUseSkill;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：参加蜀山论剑活动
		private function _doReturn_PlayerEnter(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PlayerEnter = new SRetParam_PlayerEnter();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESSBattleResult)请求参加蜀山论剑返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PlayerEnter = _sessionMgr.getData(sessionID_) as SOrigParam_PlayerEnter;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PlayerEnter = new TEvt_PlayerEnter(TEvt_PlayerEnter.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：参加蜀山论剑活动
		private function _onTimeOut_PlayerEnter(sessionID:uint):void
		{
			var retParam:SRetParam_PlayerEnter = new SRetParam_PlayerEnter();
			var event_:TEvt_PlayerEnter = new TEvt_PlayerEnter(TEvt_PlayerEnter.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：退出蜀山论剑活动
		private function _doReturn_PlayerLeave(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PlayerLeave = new SRetParam_PlayerLeave();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESSBattleResult)请求退出蜀山论剑返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PlayerLeave = _sessionMgr.getData(sessionID_) as SOrigParam_PlayerLeave;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PlayerLeave = new TEvt_PlayerLeave(TEvt_PlayerLeave.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：退出蜀山论剑活动
		private function _onTimeOut_PlayerLeave(sessionID:uint):void
		{
			var retParam:SRetParam_PlayerLeave = new SRetParam_PlayerLeave();
			var event_:TEvt_PlayerLeave = new TEvt_PlayerLeave(TEvt_PlayerLeave.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：使用蜀山论剑技能
		private function _doReturn_UseSkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UseSkill = new SRetParam_UseSkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bySkillID:uint = bytes.readUnsignedByte(); //(无符号8位整数)技能ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESSBattleResult)请求使用蜀山论剑技能返回
			retParam_.bySkillID = bySkillID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_UseSkill = _sessionMgr.getData(sessionID_) as SOrigParam_UseSkill;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UseSkill = new TEvt_UseSkill(TEvt_UseSkill.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：使用蜀山论剑技能
		private function _onTimeOut_UseSkill(sessionID:uint):void
		{
			var retParam:SRetParam_UseSkill = new SRetParam_UseSkill();
			var event_:TEvt_UseSkill = new TEvt_UseSkill(TEvt_UseSkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买蜀山论剑霸气or怒气
		private function _doReturn_BuySkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuySkill = new SRetParam_BuySkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byFlag:uint = bytes.readUnsignedByte(); //(无符号8位整数)购买类型:0霸气 1怒气
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ESSBattleResult)购买蜀山论剑霸气or怒气返回
			retParam_.byFlag = byFlag;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuySkill = _sessionMgr.getData(sessionID_) as SOrigParam_BuySkill;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuySkill = new TEvt_BuySkill(TEvt_BuySkill.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买蜀山论剑霸气or怒气
		private function _onTimeOut_BuySkill(sessionID:uint):void
		{
			var retParam:SRetParam_BuySkill = new SRetParam_BuySkill();
			var event_:TEvt_BuySkill = new TEvt_BuySkill(TEvt_BuySkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ShushanBattleProt;

		public static function get instance():ShushanBattleProt
		{
			if(_instance == null)
				_instance = new ShushanBattleProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ShushanBattleProt()
		{
			_protID = 66;
			_recvFuncList = [
				_doRecv_BattleStartInfo, //FuncID: 1
				_doRecv_PlayerPairInfo, //FuncID: 2
				_doRecv_TopKiller, //FuncID: 3
				_doRecv_HonorKinger, //FuncID: 4
				_doRecv_BattleReportInfo, //FuncID: 5
				_doRecv_UseSkillInfo //FuncID: 6
			];

			_retFuncList = [
				_doReturn_PlayerEnter, //FuncID: 1
				_doReturn_PlayerLeave, //FuncID: 2
				_doReturn_UseSkill, //FuncID: 3
				_doReturn_BuySkill //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_PlayerEnter, //FuncID: 1
				_onTimeOut_PlayerLeave, //FuncID: 2
				_onTimeOut_UseSkill, //FuncID: 3
				_onTimeOut_BuySkill //FuncID: 4
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