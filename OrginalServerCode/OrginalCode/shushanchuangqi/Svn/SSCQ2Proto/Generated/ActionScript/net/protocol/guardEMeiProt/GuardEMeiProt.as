/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GuardEMeiProt.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：守卫峨眉协议
	 */
	public class GuardEMeiProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：请求守卫峨眉信息
		 */
		public function send_ReqGEMInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_ReqGEMInfo = new SOrigParam_ReqGEMInfo();
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
		 * 发送：请求购买守卫峨眉进入次数
		 */
		public function send_BuyGEMEntryNum(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_BuyGEMEntryNum = new SOrigParam_BuyGEMEntryNum();
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
		 * 发送：请求使用Buff
		 * @param dwBuffID (无符号32位整数)BuffID
		 */
		public function send_ReqUseBuff(dwBuffID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ReqUseBuff = new SOrigParam_ReqUseBuff();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwBuffID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求重置关卡
		 * @param wMissionID (无符号16位整数)关卡ID
		 */
		public function send_ReqResetGEM(wMissionID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ReqResetGEM = new SOrigParam_ReqResetGEM();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMissionID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求守卫峨眉准备战斗信息
		 * @param wMissionID (无符号16位整数)关卡ID
		 */
		public function send_ReqGEMPrepareBattleInfo(wMissionID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ReqGEMPrepareBattleInfo = new SOrigParam_ReqGEMPrepareBattleInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMissionID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求守卫峨眉战斗
		 * @param wMissionID (无符号16位整数)关卡ID
		 * @param dwBuffID (无符号32位整数)BuffID
		 * @param eGEMBattleType (枚举类型：EGEMBattleType)战斗类型
		 */
		public function send_ReqGEMBattle(wMissionID:uint, dwBuffID:uint, eGEMBattleType:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_ReqGEMBattle = new SOrigParam_ReqGEMBattle();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMissionID);
			bytes_.writeUnsignedInt(dwBuffID);
			bytes_.writeByte(eGEMBattleType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求获取守卫峨眉扫荡开始
		 * @param wMissionID (无符号16位整数)关卡ID
		 */
		public function send_ReqSweepBegin(wMissionID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_ReqSweepBegin = new SOrigParam_ReqSweepBegin();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMissionID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求获取守卫峨眉扫荡结束(放弃扫荡)
		 * @param wMissionID (无符号16位整数)关卡ID
		 */
		public function send_ReqSweepEnd(wMissionID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_ReqSweepEnd = new SOrigParam_ReqSweepEnd();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMissionID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：扫荡信息通知
		private function _doRecv_SweepInfoNotify(bytes:ByteArray):void
		{
			var wCurProgress:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前进度
			var vecGEMSAwardInfo:Vector.<SGEMAwardInfo> = SGEMAwardInfo.vectorFromByteArray(bytes); //守卫峨眉扫荡奖励信息
			var event_:REvt_SweepInfoNotify = new REvt_SweepInfoNotify(REvt_SweepInfoNotify.DATA_RECEIVE);
			event_.wCurProgress = wCurProgress;
			event_.vecGEMSAwardInfo = vecGEMSAwardInfo;
			dispatchEvent(event_);
		}

		//接收处理：关卡通关成功通知
		private function _doRecv_MissionPassSuccNotify(bytes:ByteArray):void
		{
			var event_:REvt_MissionPassSuccNotify = new REvt_MissionPassSuccNotify(REvt_MissionPassSuccNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		//接收处理：关卡通关失败通知
		private function _doRecv_MissionPassFailedtify(bytes:ByteArray):void
		{
			var event_:REvt_MissionPassFailedtify = new REvt_MissionPassFailedtify(REvt_MissionPassFailedtify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：请求守卫峨眉信息
		private function _doReturn_ReqGEMInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGEMInfo = new SRetParam_ReqGEMInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecGEMMissionInfo:Vector.<SGEMMissionInfo> = SGEMMissionInfo.vectorFromByteArray(bytes); //守卫峨眉关卡信息
			retParam_.vecGEMMissionInfo = vecGEMMissionInfo;
			var origParam_:SOrigParam_ReqGEMInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGEMInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGEMInfo = new TEvt_ReqGEMInfo(TEvt_ReqGEMInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求守卫峨眉信息
		private function _onTimeOut_ReqGEMInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGEMInfo = new SRetParam_ReqGEMInfo();
			var event_:TEvt_ReqGEMInfo = new TEvt_ReqGEMInfo(TEvt_ReqGEMInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求购买守卫峨眉进入次数
		private function _doReturn_BuyGEMEntryNum(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyGEMEntryNum = new SRetParam_BuyGEMEntryNum();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eGEMOptResult:int = bytes.readByte(); //(枚举类型：EGEMOptResult)操作结果
			retParam_.eGEMOptResult = eGEMOptResult;
			var origParam_:SOrigParam_BuyGEMEntryNum = _sessionMgr.getData(sessionID_) as SOrigParam_BuyGEMEntryNum;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyGEMEntryNum = new TEvt_BuyGEMEntryNum(TEvt_BuyGEMEntryNum.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求购买守卫峨眉进入次数
		private function _onTimeOut_BuyGEMEntryNum(sessionID:uint):void
		{
			var retParam:SRetParam_BuyGEMEntryNum = new SRetParam_BuyGEMEntryNum();
			var event_:TEvt_BuyGEMEntryNum = new TEvt_BuyGEMEntryNum(TEvt_BuyGEMEntryNum.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求使用Buff
		private function _doReturn_ReqUseBuff(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqUseBuff = new SRetParam_ReqUseBuff();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecGEMBattleFighterInfo:Vector.<SGEMBattleFighterInfo> = SGEMBattleFighterInfo.vectorFromByteArray(bytes); //守卫峨眉参战散仙信息
			var vecGEMBuffInfo:Vector.<SGEMBuffInfo> = SGEMBuffInfo.vectorFromByteArray(bytes); //守卫峨眉Buff信息
			retParam_.vecGEMBattleFighterInfo = vecGEMBattleFighterInfo;
			retParam_.vecGEMBuffInfo = vecGEMBuffInfo;
			var origParam_:SOrigParam_ReqUseBuff = _sessionMgr.getData(sessionID_) as SOrigParam_ReqUseBuff;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqUseBuff = new TEvt_ReqUseBuff(TEvt_ReqUseBuff.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求使用Buff
		private function _onTimeOut_ReqUseBuff(sessionID:uint):void
		{
			var retParam:SRetParam_ReqUseBuff = new SRetParam_ReqUseBuff();
			var event_:TEvt_ReqUseBuff = new TEvt_ReqUseBuff(TEvt_ReqUseBuff.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求重置关卡
		private function _doReturn_ReqResetGEM(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqResetGEM = new SRetParam_ReqResetGEM();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eGEMOptResult:int = bytes.readByte(); //(枚举类型：EGEMOptResult)操作结果
			retParam_.eGEMOptResult = eGEMOptResult;
			var origParam_:SOrigParam_ReqResetGEM = _sessionMgr.getData(sessionID_) as SOrigParam_ReqResetGEM;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqResetGEM = new TEvt_ReqResetGEM(TEvt_ReqResetGEM.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求重置关卡
		private function _onTimeOut_ReqResetGEM(sessionID:uint):void
		{
			var retParam:SRetParam_ReqResetGEM = new SRetParam_ReqResetGEM();
			var event_:TEvt_ReqResetGEM = new TEvt_ReqResetGEM(TEvt_ReqResetGEM.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求守卫峨眉准备战斗信息
		private function _doReturn_ReqGEMPrepareBattleInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGEMPrepareBattleInfo = new SRetParam_ReqGEMPrepareBattleInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sGEMPrepareBattleInfo:SGEMPrepareBattleInfo = SGEMPrepareBattleInfo.fromByteArray(bytes); //守卫峨眉准备战斗信息
			retParam_.sGEMPrepareBattleInfo = sGEMPrepareBattleInfo;
			var origParam_:SOrigParam_ReqGEMPrepareBattleInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGEMPrepareBattleInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGEMPrepareBattleInfo = new TEvt_ReqGEMPrepareBattleInfo(TEvt_ReqGEMPrepareBattleInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求守卫峨眉准备战斗信息
		private function _onTimeOut_ReqGEMPrepareBattleInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGEMPrepareBattleInfo = new SRetParam_ReqGEMPrepareBattleInfo();
			var event_:TEvt_ReqGEMPrepareBattleInfo = new TEvt_ReqGEMPrepareBattleInfo(TEvt_ReqGEMPrepareBattleInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求守卫峨眉战斗
		private function _doReturn_ReqGEMBattle(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqGEMBattle = new SRetParam_ReqGEMBattle();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eGEMBattleRet:int = bytes.readByte(); //(枚举类型：EGEMBattleRet)战斗结果
			var sGEMPrepareBattleInfo:SGEMPrepareBattleInfo = SGEMPrepareBattleInfo.fromByteArray(bytes); //守卫峨眉下一波准备战斗信息
			retParam_.eGEMBattleRet = eGEMBattleRet;
			retParam_.sGEMPrepareBattleInfo = sGEMPrepareBattleInfo;
			var origParam_:SOrigParam_ReqGEMBattle = _sessionMgr.getData(sessionID_) as SOrigParam_ReqGEMBattle;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqGEMBattle = new TEvt_ReqGEMBattle(TEvt_ReqGEMBattle.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求守卫峨眉战斗
		private function _onTimeOut_ReqGEMBattle(sessionID:uint):void
		{
			var retParam:SRetParam_ReqGEMBattle = new SRetParam_ReqGEMBattle();
			var event_:TEvt_ReqGEMBattle = new TEvt_ReqGEMBattle(TEvt_ReqGEMBattle.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求获取守卫峨眉扫荡开始
		private function _doReturn_ReqSweepBegin(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqSweepBegin = new SRetParam_ReqSweepBegin();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eGEMOptResult:int = bytes.readByte(); //(枚举类型：EGEMOptResult)操作结果
			retParam_.eGEMOptResult = eGEMOptResult;
			var origParam_:SOrigParam_ReqSweepBegin = _sessionMgr.getData(sessionID_) as SOrigParam_ReqSweepBegin;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqSweepBegin = new TEvt_ReqSweepBegin(TEvt_ReqSweepBegin.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求获取守卫峨眉扫荡开始
		private function _onTimeOut_ReqSweepBegin(sessionID:uint):void
		{
			var retParam:SRetParam_ReqSweepBegin = new SRetParam_ReqSweepBegin();
			var event_:TEvt_ReqSweepBegin = new TEvt_ReqSweepBegin(TEvt_ReqSweepBegin.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求获取守卫峨眉扫荡结束(放弃扫荡)
		private function _doReturn_ReqSweepEnd(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqSweepEnd = new SRetParam_ReqSweepEnd();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wCurProgress:uint = bytes.readUnsignedShort(); //(无符号16位整数)当前进度
			retParam_.wCurProgress = wCurProgress;
			var origParam_:SOrigParam_ReqSweepEnd = _sessionMgr.getData(sessionID_) as SOrigParam_ReqSweepEnd;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqSweepEnd = new TEvt_ReqSweepEnd(TEvt_ReqSweepEnd.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求获取守卫峨眉扫荡结束(放弃扫荡)
		private function _onTimeOut_ReqSweepEnd(sessionID:uint):void
		{
			var retParam:SRetParam_ReqSweepEnd = new SRetParam_ReqSweepEnd();
			var event_:TEvt_ReqSweepEnd = new TEvt_ReqSweepEnd(TEvt_ReqSweepEnd.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GuardEMeiProt;

		public static function get instance():GuardEMeiProt
		{
			if(_instance == null)
				_instance = new GuardEMeiProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GuardEMeiProt()
		{
			_protID = 86;
			_recvFuncList = [
				_doRecv_SweepInfoNotify, //FuncID: 1
				_doRecv_MissionPassSuccNotify, //FuncID: 2
				_doRecv_MissionPassFailedtify //FuncID: 3
			];

			_retFuncList = [
				_doReturn_ReqGEMInfo, //FuncID: 1
				_doReturn_BuyGEMEntryNum, //FuncID: 2
				_doReturn_ReqUseBuff, //FuncID: 3
				_doReturn_ReqResetGEM, //FuncID: 4
				_doReturn_ReqGEMPrepareBattleInfo, //FuncID: 5
				_doReturn_ReqGEMBattle, //FuncID: 6
				_doReturn_ReqSweepBegin, //FuncID: 7
				_doReturn_ReqSweepEnd //FuncID: 8
			];

			_timeFuncList = [
				_onTimeOut_ReqGEMInfo, //FuncID: 1
				_onTimeOut_BuyGEMEntryNum, //FuncID: 2
				_onTimeOut_ReqUseBuff, //FuncID: 3
				_onTimeOut_ReqResetGEM, //FuncID: 4
				_onTimeOut_ReqGEMPrepareBattleInfo, //FuncID: 5
				_onTimeOut_ReqGEMBattle, //FuncID: 6
				_onTimeOut_ReqSweepBegin, //FuncID: 7
				_onTimeOut_ReqSweepEnd //FuncID: 8
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