/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    CollectionProt.as
//  Purpose:      收藏协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：收藏协议
	 */
	public class CollectionProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取收藏信息
		 */
		public function send_GeCollectionInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GeCollectionInfo = new SOrigParam_GeCollectionInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：收藏点通知
		private function _doRecv_APNotify(bytes:ByteArray):void
		{
			var dwAP:uint = bytes.readUnsignedInt(); //(无符号32位整数)收藏点
			var event_:REvt_APNotify = new REvt_APNotify(REvt_APNotify.DATA_RECEIVE);
			event_.dwAP = dwAP;
			dispatchEvent(event_);
		}

		//接收处理：收藏等级通知
		private function _doRecv_CollectionLevelNotify(bytes:ByteArray):void
		{
			var wLevel:uint = bytes.readUnsignedShort(); //(无符号16位整数)收藏等级
			var event_:REvt_CollectionLevelNotify = new REvt_CollectionLevelNotify(REvt_CollectionLevelNotify.DATA_RECEIVE);
			event_.wLevel = wLevel;
			dispatchEvent(event_);
		}

		//接收处理：收藏等级通知
		private function _doRecv_CollectionInfoNotify(bytes:ByteArray):void
		{
			var oCollectionInfo:SCollectionInfo = SCollectionInfo.fromByteArray(bytes); //收藏信息
			var event_:REvt_CollectionInfoNotify = new REvt_CollectionInfoNotify(REvt_CollectionInfoNotify.DATA_RECEIVE);
			event_.oCollectionInfo = oCollectionInfo;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取收藏信息
		private function _doReturn_GeCollectionInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GeCollectionInfo = new SRetParam_GeCollectionInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecCollectionInfo:Vector.<SCollectionInfo> = SCollectionInfo.vectorFromByteArray(bytes); //收藏榜信息
			var wLevel:uint = bytes.readUnsignedShort(); //(无符号16位整数)收藏等级
			var dwAP:uint = bytes.readUnsignedInt(); //(无符号32位整数)收藏点
			retParam_.vecCollectionInfo = vecCollectionInfo;
			retParam_.wLevel = wLevel;
			retParam_.dwAP = dwAP;
			var origParam_:SOrigParam_GeCollectionInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GeCollectionInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GeCollectionInfo = new TEvt_GeCollectionInfo(TEvt_GeCollectionInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取收藏信息
		private function _onTimeOut_GeCollectionInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GeCollectionInfo = new SRetParam_GeCollectionInfo();
			var event_:TEvt_GeCollectionInfo = new TEvt_GeCollectionInfo(TEvt_GeCollectionInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:CollectionProt;

		public static function get instance():CollectionProt
		{
			if(_instance == null)
				_instance = new CollectionProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function CollectionProt()
		{
			_protID = 78;
			_recvFuncList = [
				_doRecv_APNotify, //FuncID: 1
				_doRecv_CollectionLevelNotify, //FuncID: 2
				_doRecv_CollectionInfoNotify //FuncID: 3
			];

			_retFuncList = [
				_doReturn_GeCollectionInfo //FuncID: 1
			];

			_timeFuncList = [
				_onTimeOut_GeCollectionInfo //FuncID: 1
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