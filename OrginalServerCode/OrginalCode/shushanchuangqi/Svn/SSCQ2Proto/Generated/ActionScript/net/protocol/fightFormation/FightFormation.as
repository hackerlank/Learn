/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    FightFormation.as
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fightFormation
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：新阵型相关协议
	 */
	public class FightFormation extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：取得阵形信息
		 * @param wBattleType (无符号16位整数)战斗类型 EBattleType
		 */
		public function send_GetFightFormation(wBattleType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetFightFormation = new SOrigParam_GetFightFormation();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBattleType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置阵形信息
		 * @param wBattleType (无符号16位整数)战斗类型
		 * @param oFightFormation 阵形ID
		 */
		public function send_SetFightFormation(wBattleType:uint, oFightFormation:FightFormationInfo, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_SetFightFormation = new SOrigParam_SetFightFormation();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBattleType);
			oFightFormation.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：战斗散仙信息
		 * @param wBattleType (无符号16位整数)战斗类型 EBattleType
		 */
		public function send_GetFightHeroInfo(wBattleType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetFightHeroInfo = new SOrigParam_GetFightHeroInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wBattleType);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：取得阵形信息
		private function _doReturn_GetFightFormation(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFightFormation = new SRetParam_GetFightFormation();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var oFightFormation:FightFormationInfo = FightFormationInfo.fromByteArray(bytes); //战斗阵形信息
			retParam_.oFightFormation = oFightFormation;
			var origParam_:SOrigParam_GetFightFormation = _sessionMgr.getData(sessionID_) as SOrigParam_GetFightFormation;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFightFormation = new TEvt_GetFightFormation(TEvt_GetFightFormation.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得阵形信息
		private function _onTimeOut_GetFightFormation(sessionID:uint):void
		{
			var retParam:SRetParam_GetFightFormation = new SRetParam_GetFightFormation();
			var event_:TEvt_GetFightFormation = new TEvt_GetFightFormation(TEvt_GetFightFormation.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：设置阵形信息
		private function _doReturn_SetFightFormation(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetFightFormation = new SRetParam_SetFightFormation();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EFightFormationResult)操作结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_SetFightFormation = _sessionMgr.getData(sessionID_) as SOrigParam_SetFightFormation;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetFightFormation = new TEvt_SetFightFormation(TEvt_SetFightFormation.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：设置阵形信息
		private function _onTimeOut_SetFightFormation(sessionID:uint):void
		{
			var retParam:SRetParam_SetFightFormation = new SRetParam_SetFightFormation();
			var event_:TEvt_SetFightFormation = new TEvt_SetFightFormation(TEvt_SetFightFormation.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：战斗散仙信息
		private function _doReturn_GetFightHeroInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFightHeroInfo = new SRetParam_GetFightHeroInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFightHeroInfo:Vector.<FightHeroInfo> = FightHeroInfo.vectorFromByteArray(bytes); //战斗阵形信息
			retParam_.vecFightHeroInfo = vecFightHeroInfo;
			var origParam_:SOrigParam_GetFightHeroInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetFightHeroInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFightHeroInfo = new TEvt_GetFightHeroInfo(TEvt_GetFightHeroInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：战斗散仙信息
		private function _onTimeOut_GetFightHeroInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetFightHeroInfo = new SRetParam_GetFightHeroInfo();
			var event_:TEvt_GetFightHeroInfo = new TEvt_GetFightHeroInfo(TEvt_GetFightHeroInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:FightFormation;

		public static function get instance():FightFormation
		{
			if(_instance == null)
				_instance = new FightFormation();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function FightFormation()
		{
			_protID = 132;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetFightFormation, //FuncID: 1
				_doReturn_SetFightFormation, //FuncID: 2
				_doReturn_GetFightHeroInfo //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GetFightFormation, //FuncID: 1
				_onTimeOut_SetFightFormation, //FuncID: 2
				_onTimeOut_GetFightHeroInfo //FuncID: 3
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0
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