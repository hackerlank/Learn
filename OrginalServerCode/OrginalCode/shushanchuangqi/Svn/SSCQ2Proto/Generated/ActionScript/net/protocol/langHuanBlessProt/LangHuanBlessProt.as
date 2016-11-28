/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    LangHuanBlessProt.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：中午挂机活动
	 */
	public class LangHuanBlessProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：进入LangHuanBless地图
		 */
		public function send_EnterMap(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_EnterMap = new SOrigParam_EnterMap();
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
		 * 发送：选择问道
		 * @param qwPlayerID (无符号64位整数)被选择的玩家
		 * @param eLHBSkillType (枚举类型：ELHBSkillType)技能类型
		 */
		public function send_SelectSkill(qwPlayerID:BigInteger, eLHBSkillType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_SelectSkill = new SOrigParam_SelectSkill();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwPlayerID);
			bytes_.writeByte(eLHBSkillType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得的修为值
		 */
		public function send_GetScore(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetScore = new SOrigParam_GetScore();
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
		 * 发送：获得游戏中持续时间
		 */
		public function send_GetSustainTime(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GetSustainTime = new SOrigParam_GetSustainTime();
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
		 * 发送：获得玩家所有信息
		 */
		public function send_GetTotalInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetTotalInfo = new SOrigParam_GetTotalInfo();
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
		 * 发送：获得技能使用信息
		 */
		public function send_GetSkillInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetSkillInfo = new SOrigParam_GetSkillInfo();
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
		 * 发送：离开LangHuanBless地图
		 */
		public function send_LeaveMap(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_LeaveMap = new SOrigParam_LeaveMap();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：挂机活动报名开始
		private function _doRecv_EnrollNotify(bytes:ByteArray):void
		{
			var dwEnrollTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var event_:REvt_EnrollNotify = new REvt_EnrollNotify(REvt_EnrollNotify.DATA_RECEIVE);
			event_.dwEnrollTime = dwEnrollTime;
			dispatchEvent(event_);
		}

		//接收处理：挂机活动开始
		private function _doRecv_BeginNotify(bytes:ByteArray):void
		{
			var dwBeginTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)开始时间
			var event_:REvt_BeginNotify = new REvt_BeginNotify(REvt_BeginNotify.DATA_RECEIVE);
			event_.dwBeginTime = dwBeginTime;
			dispatchEvent(event_);
		}

		//接收处理：发送经验值和修为值
		private function _doRecv_PrizeNotify(bytes:ByteArray):void
		{
			var dwXiuwei:uint = bytes.readUnsignedInt(); //(无符号32位整数)修为值
			var dwExp:uint = bytes.readUnsignedInt(); //(无符号32位整数)经验值
			var event_:REvt_PrizeNotify = new REvt_PrizeNotify(REvt_PrizeNotify.DATA_RECEIVE);
			event_.dwXiuwei = dwXiuwei;
			event_.dwExp = dwExp;
			dispatchEvent(event_);
		}

		//接收处理：发送玩家在副本中的信息
		private function _doRecv_TotalInfo(bytes:ByteArray):void
		{
			var qwPlayerID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)玩家ID
			var sTotalInfo:SLHBTotalInfo = SLHBTotalInfo.fromByteArray(bytes); //玩家信息
			var event_:REvt_TotalInfo = new REvt_TotalInfo(REvt_TotalInfo.DATA_RECEIVE);
			event_.qwPlayerID = qwPlayerID;
			event_.sTotalInfo = sTotalInfo;
			dispatchEvent(event_);
		}

		//接收处理：发送技能信息
		private function _doRecv_SkillInfo(bytes:ByteArray):void
		{
			var qwAtkPlayerID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)攻击者
			var qwDfePlayerID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)被攻击者
			var eLHBSkillType:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBSkillType)使用的技能ID
			var event_:REvt_SkillInfo = new REvt_SkillInfo(REvt_SkillInfo.DATA_RECEIVE);
			event_.qwAtkPlayerID = qwAtkPlayerID;
			event_.qwDfePlayerID = qwDfePlayerID;
			event_.eLHBSkillType = eLHBSkillType;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：进入LangHuanBless地图
		private function _doReturn_EnterMap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterMap = new SRetParam_EnterMap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eLHBResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBResult)结果
			retParam_.eLHBResult = eLHBResult;
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

		//超时处理：进入LangHuanBless地图
		private function _onTimeOut_EnterMap(sessionID:uint):void
		{
			var retParam:SRetParam_EnterMap = new SRetParam_EnterMap();
			var event_:TEvt_EnterMap = new TEvt_EnterMap(TEvt_EnterMap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：选择问道
		private function _doReturn_SelectSkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SelectSkill = new SRetParam_SelectSkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRetLHBSkillType:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBSkillType)返回使用技能
			var eLHBResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBResult)结果
			retParam_.eRetLHBSkillType = eRetLHBSkillType;
			retParam_.eLHBResult = eLHBResult;
			var origParam_:SOrigParam_SelectSkill = _sessionMgr.getData(sessionID_) as SOrigParam_SelectSkill;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SelectSkill = new TEvt_SelectSkill(TEvt_SelectSkill.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：选择问道
		private function _onTimeOut_SelectSkill(sessionID:uint):void
		{
			var retParam:SRetParam_SelectSkill = new SRetParam_SelectSkill();
			var event_:TEvt_SelectSkill = new TEvt_SelectSkill(TEvt_SelectSkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得的修为值
		private function _doReturn_GetScore(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetScore = new SRetParam_GetScore();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)修为值
			retParam_.wScore = wScore;
			var origParam_:SOrigParam_GetScore = _sessionMgr.getData(sessionID_) as SOrigParam_GetScore;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetScore = new TEvt_GetScore(TEvt_GetScore.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得的修为值
		private function _onTimeOut_GetScore(sessionID:uint):void
		{
			var retParam:SRetParam_GetScore = new SRetParam_GetScore();
			var event_:TEvt_GetScore = new TEvt_GetScore(TEvt_GetScore.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得游戏中持续时间
		private function _doReturn_GetSustainTime(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSustainTime = new SRetParam_GetSustainTime();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间值
			retParam_.dwTime = dwTime;
			var origParam_:SOrigParam_GetSustainTime = _sessionMgr.getData(sessionID_) as SOrigParam_GetSustainTime;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSustainTime = new TEvt_GetSustainTime(TEvt_GetSustainTime.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得游戏中持续时间
		private function _onTimeOut_GetSustainTime(sessionID:uint):void
		{
			var retParam:SRetParam_GetSustainTime = new SRetParam_GetSustainTime();
			var event_:TEvt_GetSustainTime = new TEvt_GetSustainTime(TEvt_GetSustainTime.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得玩家所有信息
		private function _doReturn_GetTotalInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTotalInfo = new SRetParam_GetTotalInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var sTotalInfo:SLHBTotalInfo = SLHBTotalInfo.fromByteArray(bytes); //时间值
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.sTotalInfo = sTotalInfo;
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_GetTotalInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetTotalInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTotalInfo = new TEvt_GetTotalInfo(TEvt_GetTotalInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得玩家所有信息
		private function _onTimeOut_GetTotalInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetTotalInfo = new SRetParam_GetTotalInfo();
			var event_:TEvt_GetTotalInfo = new TEvt_GetTotalInfo(TEvt_GetTotalInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得技能使用信息
		private function _doReturn_GetSkillInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSkillInfo = new SRetParam_GetSkillInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecLHBSkillInfo:Vector.<SLHBSkillInfo> = SLHBSkillInfo.vectorFromByteArray(bytes); //技能使用信息
			var eLHBResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBResult)结果
			retParam_.vecLHBSkillInfo = vecLHBSkillInfo;
			retParam_.eLHBResult = eLHBResult;
			var origParam_:SOrigParam_GetSkillInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetSkillInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSkillInfo = new TEvt_GetSkillInfo(TEvt_GetSkillInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得技能使用信息
		private function _onTimeOut_GetSkillInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetSkillInfo = new SRetParam_GetSkillInfo();
			var event_:TEvt_GetSkillInfo = new TEvt_GetSkillInfo(TEvt_GetSkillInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开LangHuanBless地图
		private function _doReturn_LeaveMap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveMap = new SRetParam_LeaveMap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eLHBResult:uint = bytes.readUnsignedByte(); //(枚举类型：ELHBResult)结果
			retParam_.eLHBResult = eLHBResult;
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

		//超时处理：离开LangHuanBless地图
		private function _onTimeOut_LeaveMap(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveMap = new SRetParam_LeaveMap();
			var event_:TEvt_LeaveMap = new TEvt_LeaveMap(TEvt_LeaveMap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:LangHuanBlessProt;

		public static function get instance():LangHuanBlessProt
		{
			if(_instance == null)
				_instance = new LangHuanBlessProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function LangHuanBlessProt()
		{
			_protID = 79;
			_recvFuncList = [
				_doRecv_EnrollNotify, //FuncID: 1
				_doRecv_BeginNotify, //FuncID: 2
				_doRecv_PrizeNotify, //FuncID: 3
				_doRecv_TotalInfo, //FuncID: 4
				_doRecv_SkillInfo //FuncID: 5
			];

			_retFuncList = [
				_doReturn_EnterMap, //FuncID: 1
				_doReturn_SelectSkill, //FuncID: 2
				_doReturn_GetScore, //FuncID: 3
				_doReturn_GetSustainTime, //FuncID: 4
				_doReturn_GetTotalInfo, //FuncID: 5
				_doReturn_GetSkillInfo, //FuncID: 6
				_doReturn_LeaveMap //FuncID: 7
			];

			_timeFuncList = [
				_onTimeOut_EnterMap, //FuncID: 1
				_onTimeOut_SelectSkill, //FuncID: 2
				_onTimeOut_GetScore, //FuncID: 3
				_onTimeOut_GetSustainTime, //FuncID: 4
				_onTimeOut_GetTotalInfo, //FuncID: 5
				_onTimeOut_GetSkillInfo, //FuncID: 6
				_onTimeOut_LeaveMap //FuncID: 7
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