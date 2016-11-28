/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    AnswerProt.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：答题协议
	 */
	public class AnswerProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：玩家报名
		 */
		public function send_Join():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家离开
		 */
		public function send_Leave():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取活动开始倒计时
		 */
		public function send_GetCoutdown(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetCoutdown = new SOrigParam_GetCoutdown();
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
		 * 发送：玩家答题
		 * @param byAnswerID (无符号8位整数)玩家选择答案
		 */
		public function send_Answer(byAnswerID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_Answer = new SOrigParam_Answer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byAnswerID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家使用技能
		 * @param eSkillType (枚举类型：EAnswerSkill)技能ID
		 */
		public function send_UseSkill(eSkillType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_UseSkill = new SOrigParam_UseSkill();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eSkillType);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：答题预告
		private function _doRecv_AnswerAlarm(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_AnswerAlarm = new REvt_AnswerAlarm(REvt_AnswerAlarm.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：答题开始倒计时30秒通知
		private function _doRecv_AnswerCountdown(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_AnswerCountdown = new REvt_AnswerCountdown(REvt_AnswerCountdown.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：答题开始
		private function _doRecv_AnswerBegin(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_AnswerBegin = new REvt_AnswerBegin(REvt_AnswerBegin.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：答题结束
		private function _doRecv_AnswerEnd(bytes:ByteArray):void
		{
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)时间
			var event_:REvt_AnswerEnd = new REvt_AnswerEnd(REvt_AnswerEnd.DATA_RECEIVE);
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：发送题目
		private function _doRecv_SendTopic(bytes:ByteArray):void
		{
			var sTopic:SAnswerTopic = SAnswerTopic.fromByteArray(bytes); //题目信息
			var event_:REvt_SendTopic = new REvt_SendTopic(REvt_SendTopic.DATA_RECEIVE);
			event_.sTopic = sTopic;
			dispatchEvent(event_);
		}

		//接收处理：答完一题信息发送
		private function _doRecv_SendAnswerInfo(bytes:ByteArray):void
		{
			var sPlayerInfo:SAnswerPlayer = SAnswerPlayer.fromByteArray(bytes); //玩家信息
			var vecRankInfo:Vector.<SAnswerRank> = SAnswerRank.vectorFromByteArray(bytes); //排名列表
			var event_:REvt_SendAnswerInfo = new REvt_SendAnswerInfo(REvt_SendAnswerInfo.DATA_RECEIVE);
			event_.sPlayerInfo = sPlayerInfo;
			event_.vecRankInfo = vecRankInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取活动开始倒计时
		private function _doReturn_GetCoutdown(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetCoutdown = new SRetParam_GetCoutdown();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)倒计时时间
			var sPlayerInfo:SAnswerPlayer = SAnswerPlayer.fromByteArray(bytes); //玩家信息
			var bRet:Boolean = bytes.readBoolean(); //是否开启面板
			retParam_.dwTime = dwTime;
			retParam_.sPlayerInfo = sPlayerInfo;
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_GetCoutdown = _sessionMgr.getData(sessionID_) as SOrigParam_GetCoutdown;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetCoutdown = new TEvt_GetCoutdown(TEvt_GetCoutdown.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取活动开始倒计时
		private function _onTimeOut_GetCoutdown(sessionID:uint):void
		{
			var retParam:SRetParam_GetCoutdown = new SRetParam_GetCoutdown();
			var event_:TEvt_GetCoutdown = new TEvt_GetCoutdown(TEvt_GetCoutdown.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家答题
		private function _doReturn_Answer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Answer = new SRetParam_Answer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)题目
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EAnswerResult)答题结果返回
			retParam_.dwIndex = dwIndex;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Answer = _sessionMgr.getData(sessionID_) as SOrigParam_Answer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Answer = new TEvt_Answer(TEvt_Answer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家答题
		private function _onTimeOut_Answer(sessionID:uint):void
		{
			var retParam:SRetParam_Answer = new SRetParam_Answer();
			var event_:TEvt_Answer = new TEvt_Answer(TEvt_Answer.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家使用技能
		private function _doReturn_UseSkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UseSkill = new SRetParam_UseSkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eSkillTypeRet:uint = bytes.readUnsignedByte(); //(枚举类型：EAnswerSkill)技能ID
			var byAnswer1:uint = bytes.readUnsignedByte(); //(无符号8位整数)答案1
			var byAnswer2:uint = bytes.readUnsignedByte(); //(无符号8位整数)答案2
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EAnswerResult)结果
			retParam_.eSkillTypeRet = eSkillTypeRet;
			retParam_.byAnswer1 = byAnswer1;
			retParam_.byAnswer2 = byAnswer2;
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

		//超时处理：玩家使用技能
		private function _onTimeOut_UseSkill(sessionID:uint):void
		{
			var retParam:SRetParam_UseSkill = new SRetParam_UseSkill();
			var event_:TEvt_UseSkill = new TEvt_UseSkill(TEvt_UseSkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:AnswerProt;

		public static function get instance():AnswerProt
		{
			if(_instance == null)
				_instance = new AnswerProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function AnswerProt()
		{
			_protID = 95;
			_recvFuncList = [
				_doRecv_AnswerAlarm, //FuncID: 1
				_doRecv_AnswerCountdown, //FuncID: 2
				_doRecv_AnswerBegin, //FuncID: 3
				_doRecv_AnswerEnd, //FuncID: 4
				_doRecv_SendTopic, //FuncID: 5
				_doRecv_SendAnswerInfo //FuncID: 6
			];

			_retFuncList = [
				_doReturn_GetCoutdown, //FuncID: 1
				_doReturn_Answer, //FuncID: 2
				_doReturn_UseSkill //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GetCoutdown, //FuncID: 1
				_onTimeOut_Answer, //FuncID: 2
				_onTimeOut_UseSkill //FuncID: 3
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