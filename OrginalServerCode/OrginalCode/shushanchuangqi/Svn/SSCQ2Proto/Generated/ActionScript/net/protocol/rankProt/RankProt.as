/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    RankProt.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.battleGS.SFeatureBase;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：排行榜相关协议
	 */
	public class RankProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取排行榜数据
		 * @param eType (枚举类型：ERankType)排行榜类型
		 * @param dwIndex (无符号32位整数)排名索引
		 * @param dwCount (无符号32位整数)排名个数
		 */
		public function send_GetRankInfo(eType:uint, dwIndex:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetRankInfo = new SOrigParam_GetRankInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			bytes_.writeUnsignedInt(dwIndex);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得玩家外观信息
		 * @param qwRoleID (无符号64位整数)玩家ID
		 */
		public function send_GetPlayerFeature(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetPlayerFeature = new SOrigParam_GetPlayerFeature();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获得崇拜数量
		 * @param qwRoleID (无符号64位整数)玩家ID
		 */
		public function send_GetAdoreCount(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetAdoreCount = new SOrigParam_GetAdoreCount();
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
		 * 发送：崇拜玩家
		 * @param qwRoleID (无符号64位整数)玩家ID
		 */
		public function send_AdorePlayer(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_AdorePlayer = new SOrigParam_AdorePlayer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：获取排行榜数据
		private function _doReturn_GetRankInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRankInfo = new SRetParam_GetRankInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eType:uint = bytes.readUnsignedByte(); //(枚举类型：ERankType)排行榜类型
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var dwSelfRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)自己所在排名
			var vecRankInfo:Vector.<SRankInfo> = SRankInfo.superVectorFromByteArray(bytes); //排行榜数据
			var vecSelfRankInfo:Vector.<SRankInfo> = SRankInfo.superVectorFromByteArray(bytes); //自己所在排名
			retParam_.eType = eType;
			retParam_.dwMaxCount = dwMaxCount;
			retParam_.dwCurIndex = dwCurIndex;
			retParam_.dwSelfRank = dwSelfRank;
			retParam_.vecRankInfo = vecRankInfo;
			retParam_.vecSelfRankInfo = vecSelfRankInfo;
			var origParam_:SOrigParam_GetRankInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetRankInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRankInfo = new TEvt_GetRankInfo(TEvt_GetRankInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取排行榜数据
		private function _onTimeOut_GetRankInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetRankInfo = new SRetParam_GetRankInfo();
			var event_:TEvt_GetRankInfo = new TEvt_GetRankInfo(TEvt_GetRankInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得玩家外观信息
		private function _doReturn_GetPlayerFeature(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPlayerFeature = new SRetParam_GetPlayerFeature();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ERankResult)崇拜结果
			var pFeature:SFeatureBase = SFeatureBase.superFromByteArray(bytes); //外观信息
			retParam_.eResult = eResult;
			retParam_.pFeature = pFeature;
			var origParam_:SOrigParam_GetPlayerFeature = _sessionMgr.getData(sessionID_) as SOrigParam_GetPlayerFeature;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPlayerFeature = new TEvt_GetPlayerFeature(TEvt_GetPlayerFeature.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得玩家外观信息
		private function _onTimeOut_GetPlayerFeature(sessionID:uint):void
		{
			var retParam:SRetParam_GetPlayerFeature = new SRetParam_GetPlayerFeature();
			var event_:TEvt_GetPlayerFeature = new TEvt_GetPlayerFeature(TEvt_GetPlayerFeature.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获得崇拜数量
		private function _doReturn_GetAdoreCount(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAdoreCount = new SRetParam_GetAdoreCount();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)崇拜数量
			var dwSelfCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)自己剩余崇拜数量
			retParam_.dwCount = dwCount;
			retParam_.dwSelfCount = dwSelfCount;
			var origParam_:SOrigParam_GetAdoreCount = _sessionMgr.getData(sessionID_) as SOrigParam_GetAdoreCount;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAdoreCount = new TEvt_GetAdoreCount(TEvt_GetAdoreCount.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获得崇拜数量
		private function _onTimeOut_GetAdoreCount(sessionID:uint):void
		{
			var retParam:SRetParam_GetAdoreCount = new SRetParam_GetAdoreCount();
			var event_:TEvt_GetAdoreCount = new TEvt_GetAdoreCount(TEvt_GetAdoreCount.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：崇拜玩家
		private function _doReturn_AdorePlayer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AdorePlayer = new SRetParam_AdorePlayer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ERankResult)崇拜结果
			var dwCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)崇拜数量
			var dwSelfCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)自己剩余崇拜数量
			retParam_.eResult = eResult;
			retParam_.dwCount = dwCount;
			retParam_.dwSelfCount = dwSelfCount;
			var origParam_:SOrigParam_AdorePlayer = _sessionMgr.getData(sessionID_) as SOrigParam_AdorePlayer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AdorePlayer = new TEvt_AdorePlayer(TEvt_AdorePlayer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：崇拜玩家
		private function _onTimeOut_AdorePlayer(sessionID:uint):void
		{
			var retParam:SRetParam_AdorePlayer = new SRetParam_AdorePlayer();
			var event_:TEvt_AdorePlayer = new TEvt_AdorePlayer(TEvt_AdorePlayer.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:RankProt;

		public static function get instance():RankProt
		{
			if(_instance == null)
				_instance = new RankProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function RankProt()
		{
			_protID = 80;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetRankInfo, //FuncID: 1
				_doReturn_GetPlayerFeature, //FuncID: 2
				_doReturn_GetAdoreCount, //FuncID: 3
				_doReturn_AdorePlayer //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetRankInfo, //FuncID: 1
				_onTimeOut_GetPlayerFeature, //FuncID: 2
				_onTimeOut_GetAdoreCount, //FuncID: 3
				_onTimeOut_AdorePlayer //FuncID: 4
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