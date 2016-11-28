/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    AchievementProt.as
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：成就相关协议
	 */
	public class AchievementProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取成就信息
		 */
		public function send_GeAchievementInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GeAchievementInfo = new SOrigParam_GeAchievementInfo();
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
		 * 发送：获取成就奖励
		 * @param wAchievementID (无符号16位整数)成就ID
		 */
		public function send_TakePrize(wAchievementID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_TakePrize = new SOrigParam_TakePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wAchievementID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取成就分享信息
		 */
		public function send_GeAchievementShareList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GeAchievementShareList = new SOrigParam_GeAchievementShareList();
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
		 * 发送：获取成就分享奖励
		 * @param wAchievementID (无符号16位整数)成就ID
		 */
		public function send_TakeSharePrize(wAchievementID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_TakeSharePrize = new SOrigParam_TakeSharePrize();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wAchievementID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：成就点通知
		private function _doRecv_APNotify(bytes:ByteArray):void
		{
			var dwAP:uint = bytes.readUnsignedInt(); //(无符号32位整数)成就点
			var event_:REvt_APNotify = new REvt_APNotify(REvt_APNotify.DATA_RECEIVE);
			event_.dwAP = dwAP;
			dispatchEvent(event_);
		}

		//接收处理：成就等级通知
		private function _doRecv_AchievementLevelNotify(bytes:ByteArray):void
		{
			var wLevel:uint = bytes.readUnsignedShort(); //(无符号16位整数)成就等级
			var event_:REvt_AchievementLevelNotify = new REvt_AchievementLevelNotify(REvt_AchievementLevelNotify.DATA_RECEIVE);
			event_.wLevel = wLevel;
			dispatchEvent(event_);
		}

		//接收处理：成就等级通知
		private function _doRecv_AchievementInfoNotify(bytes:ByteArray):void
		{
			var oAchievementInfo:SAchievementInfo = SAchievementInfo.fromByteArray(bytes); //成就信息
			var event_:REvt_AchievementInfoNotify = new REvt_AchievementInfoNotify(REvt_AchievementInfoNotify.DATA_RECEIVE);
			event_.oAchievementInfo = oAchievementInfo;
			dispatchEvent(event_);
		}

		//接收处理：成就分享通知
		private function _doRecv_AchievementShareNotify(bytes:ByteArray):void
		{
			var oAchievementShare:SAchievementShare = SAchievementShare.fromByteArray(bytes); //成就分享信息
			var event_:REvt_AchievementShareNotify = new REvt_AchievementShareNotify(REvt_AchievementShareNotify.DATA_RECEIVE);
			event_.oAchievementShare = oAchievementShare;
			dispatchEvent(event_);
		}

		//接收处理：零点通知
		private function _doRecv_MidnightNotify(bytes:ByteArray):void
		{
			var event_:REvt_MidnightNotify = new REvt_MidnightNotify(REvt_MidnightNotify.DATA_RECEIVE);
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取成就信息
		private function _doReturn_GeAchievementInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GeAchievementInfo = new SRetParam_GeAchievementInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecAchievementInfo:Vector.<SAchievementInfo> = SAchievementInfo.vectorFromByteArray(bytes); //成就榜信息
			var wLevel:uint = bytes.readUnsignedShort(); //(无符号16位整数)成就等级
			var dwAP:uint = bytes.readUnsignedInt(); //(无符号32位整数)成就点
			retParam_.vecAchievementInfo = vecAchievementInfo;
			retParam_.wLevel = wLevel;
			retParam_.dwAP = dwAP;
			var origParam_:SOrigParam_GeAchievementInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GeAchievementInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GeAchievementInfo = new TEvt_GeAchievementInfo(TEvt_GeAchievementInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取成就信息
		private function _onTimeOut_GeAchievementInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GeAchievementInfo = new SRetParam_GeAchievementInfo();
			var event_:TEvt_GeAchievementInfo = new TEvt_GeAchievementInfo(TEvt_GeAchievementInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取成就奖励
		private function _doReturn_TakePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakePrize = new SRetParam_TakePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EAchievementRet)结果
			retParam_.eRet = eRet;
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

		//超时处理：获取成就奖励
		private function _onTimeOut_TakePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakePrize = new SRetParam_TakePrize();
			var event_:TEvt_TakePrize = new TEvt_TakePrize(TEvt_TakePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取成就分享信息
		private function _doReturn_GeAchievementShareList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GeAchievementShareList = new SRetParam_GeAchievementShareList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecAchievementShare:Vector.<SAchievementShare> = SAchievementShare.vectorFromByteArray(bytes); //成就分享信息
			retParam_.vecAchievementShare = vecAchievementShare;
			var origParam_:SOrigParam_GeAchievementShareList = _sessionMgr.getData(sessionID_) as SOrigParam_GeAchievementShareList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GeAchievementShareList = new TEvt_GeAchievementShareList(TEvt_GeAchievementShareList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取成就分享信息
		private function _onTimeOut_GeAchievementShareList(sessionID:uint):void
		{
			var retParam:SRetParam_GeAchievementShareList = new SRetParam_GeAchievementShareList();
			var event_:TEvt_GeAchievementShareList = new TEvt_GeAchievementShareList(TEvt_GeAchievementShareList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取成就分享奖励
		private function _doReturn_TakeSharePrize(bytes:ByteArray):void
		{
			var retParam_:SRetParam_TakeSharePrize = new SRetParam_TakeSharePrize();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：EAchievementRet)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_TakeSharePrize = _sessionMgr.getData(sessionID_) as SOrigParam_TakeSharePrize;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_TakeSharePrize = new TEvt_TakeSharePrize(TEvt_TakeSharePrize.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取成就分享奖励
		private function _onTimeOut_TakeSharePrize(sessionID:uint):void
		{
			var retParam:SRetParam_TakeSharePrize = new SRetParam_TakeSharePrize();
			var event_:TEvt_TakeSharePrize = new TEvt_TakeSharePrize(TEvt_TakeSharePrize.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:AchievementProt;

		public static function get instance():AchievementProt
		{
			if(_instance == null)
				_instance = new AchievementProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function AchievementProt()
		{
			_protID = 75;
			_recvFuncList = [
				_doRecv_APNotify, //FuncID: 1
				_doRecv_AchievementLevelNotify, //FuncID: 2
				_doRecv_AchievementInfoNotify, //FuncID: 3
				_doRecv_AchievementShareNotify, //FuncID: 4
				_doRecv_MidnightNotify //FuncID: 5
			];

			_retFuncList = [
				_doReturn_GeAchievementInfo, //FuncID: 1
				_doReturn_TakePrize, //FuncID: 2
				_doReturn_GeAchievementShareList, //FuncID: 3
				_doReturn_TakeSharePrize //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GeAchievementInfo, //FuncID: 1
				_onTimeOut_TakePrize, //FuncID: 2
				_onTimeOut_GeAchievementShareList, //FuncID: 3
				_onTimeOut_TakeSharePrize //FuncID: 4
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