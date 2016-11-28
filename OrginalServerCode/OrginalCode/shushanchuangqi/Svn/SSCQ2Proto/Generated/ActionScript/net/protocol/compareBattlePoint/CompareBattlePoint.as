/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    CompareBattlePoint.as
//  Purpose:      变强(战力对比)相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.compareBattlePoint
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：变强(战力对比)相关协议
	 */
	public class CompareBattlePoint extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：战斗力对比
		 * @param qwRoleID (无符号64位整数)对方的玩家ID
		 */
		public function send_CompareOtherBPByID(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_CompareOtherBPByID = new SOrigParam_CompareOtherBPByID();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：战斗力对比
		 * @param strName 对方的玩家名字
		 */
		public function send_CompareOtherBPByName(strName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_CompareOtherBPByName = new SOrigParam_CompareOtherBPByName();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strName);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：战斗力对比
		private function _doReturn_CompareOtherBPByID(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CompareOtherBPByID = new SRetParam_CompareOtherBPByID();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecCompareData:Vector.<SCompareData> = SCompareData.vectorFromByteArray(bytes); //玩家的对比数据信息
			retParam_.vecCompareData = vecCompareData;
			var origParam_:SOrigParam_CompareOtherBPByID = _sessionMgr.getData(sessionID_) as SOrigParam_CompareOtherBPByID;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CompareOtherBPByID = new TEvt_CompareOtherBPByID(TEvt_CompareOtherBPByID.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：战斗力对比
		private function _onTimeOut_CompareOtherBPByID(sessionID:uint):void
		{
			var retParam:SRetParam_CompareOtherBPByID = new SRetParam_CompareOtherBPByID();
			var event_:TEvt_CompareOtherBPByID = new TEvt_CompareOtherBPByID(TEvt_CompareOtherBPByID.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：战斗力对比
		private function _doReturn_CompareOtherBPByName(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CompareOtherBPByName = new SRetParam_CompareOtherBPByName();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecCompareData:Vector.<SCompareData> = SCompareData.vectorFromByteArray(bytes); //玩家的对比数据信息
			retParam_.vecCompareData = vecCompareData;
			var origParam_:SOrigParam_CompareOtherBPByName = _sessionMgr.getData(sessionID_) as SOrigParam_CompareOtherBPByName;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CompareOtherBPByName = new TEvt_CompareOtherBPByName(TEvt_CompareOtherBPByName.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：战斗力对比
		private function _onTimeOut_CompareOtherBPByName(sessionID:uint):void
		{
			var retParam:SRetParam_CompareOtherBPByName = new SRetParam_CompareOtherBPByName();
			var event_:TEvt_CompareOtherBPByName = new TEvt_CompareOtherBPByName(TEvt_CompareOtherBPByName.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:CompareBattlePoint;

		public static function get instance():CompareBattlePoint
		{
			if(_instance == null)
				_instance = new CompareBattlePoint();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function CompareBattlePoint()
		{
			_protID = 58;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_CompareOtherBPByID, //FuncID: 1
				_doReturn_CompareOtherBPByName //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_CompareOtherBPByID, //FuncID: 1
				_onTimeOut_CompareOtherBPByName //FuncID: 2
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