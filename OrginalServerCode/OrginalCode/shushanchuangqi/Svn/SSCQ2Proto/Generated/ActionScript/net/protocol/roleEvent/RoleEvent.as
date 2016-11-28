/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    RoleEvent.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SBuffInfo;
	import net.protocol.fighterProt.SFighterInfo;
	import net.protocol.itemProt.SItem;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：玩家在GameServer的消息处理
	 */
	public class RoleEvent extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取角色面板信息
		 */
		public function send_GetRoleSpecInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetRoleSpecInfo = new SOrigParam_GetRoleSpecInfo();
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
		 * 发送：取得散仙列表
		 */
		public function send_GetFighters(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetFighters = new SOrigParam_GetFighters();
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
		 * 发送：存储新手引导信息
		 * @param strGuide 引导步骤信息
		 */
		public function send_StoreGuide(strGuide:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_StoreGuide = new SOrigParam_StoreGuide();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strGuide);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取角色Buff信息
		 */
		public function send_GetRoleBuffInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GetRoleBuffInfo = new SOrigParam_GetRoleBuffInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：散仙信息通知列表
		private function _doRecv_FighterInfoNotify(bytes:ByteArray):void
		{
			var vecFighters:Vector.<SFighterSpecInfo> = SFighterSpecInfo.vectorFromByteArray(bytes); //散仙信息
			var event_:REvt_FighterInfoNotify = new REvt_FighterInfoNotify(REvt_FighterInfoNotify.DATA_RECEIVE);
			event_.vecFighters = vecFighters;
			dispatchEvent(event_);
		}

		//接收处理：增加的AppearIcon通知
		private function _doRecv_AddAppearIconNotify(bytes:ByteArray):void
		{
			var vecAppearIcon:Vector.<uint> = BytesUtil.readVecUShort(bytes); //(无符号16位整数)增加的Icon列表
			var event_:REvt_AddAppearIconNotify = new REvt_AddAppearIconNotify(REvt_AddAppearIconNotify.DATA_RECEIVE);
			event_.vecAppearIcon = vecAppearIcon;
			dispatchEvent(event_);
		}

		//接收处理：玩家Buff变化通知
		private function _doRecv_BuffNotify(bytes:ByteArray):void
		{
			var eType:uint = bytes.readUnsignedByte(); //(枚举类型：protoCommon.EDataChange)更新类型，增加，删除，修改
			var vecBuffInfo:Vector.<SBuffInfo> = SBuffInfo.vectorFromByteArray(bytes); //玩家Buff信息
			var event_:REvt_BuffNotify = new REvt_BuffNotify(REvt_BuffNotify.DATA_RECEIVE);
			event_.eType = eType;
			event_.vecBuffInfo = vecBuffInfo;
			dispatchEvent(event_);
		}

		//接收处理：准备切地图
		private function _doRecv_ChangeMapNotify(bytes:ByteArray):void
		{
			var wMapId:uint = bytes.readUnsignedShort(); //(无符号16位整数)地图id，客户端准备资源
			var qwDgnId:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)副本实例，非单人副本为0
			var wDgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本模板，单人副本为0
			var event_:REvt_ChangeMapNotify = new REvt_ChangeMapNotify(REvt_ChangeMapNotify.DATA_RECEIVE);
			event_.wMapId = wMapId;
			event_.qwDgnId = qwDgnId;
			event_.wDgnType = wDgnType;
			dispatchEvent(event_);
		}

		//接收处理：暴击通知
		private function _doRecv_CritNotify(bytes:ByteArray):void
		{
			var eCritType:int = bytes.readByte(); //(枚举类型：ECritType)暴击类型
			var eCritMultiple:int = bytes.readByte(); //(枚举类型：ECritMultiple)暴击倍数
			var event_:REvt_CritNotify = new REvt_CritNotify(REvt_CritNotify.DATA_RECEIVE);
			event_.eCritType = eCritType;
			event_.eCritMultiple = eCritMultiple;
			dispatchEvent(event_);
		}

		//接收处理：删除AppearIcon通知
		private function _doRecv_DelAppearIconNotify(bytes:ByteArray):void
		{
			var wIconID:uint = bytes.readUnsignedShort(); //(无符号16位整数)删除的IconApear
			var event_:REvt_DelAppearIconNotify = new REvt_DelAppearIconNotify(REvt_DelAppearIconNotify.DATA_RECEIVE);
			event_.wIconID = wIconID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取角色面板信息
		private function _doReturn_GetRoleSpecInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleSpecInfo = new SRetParam_GetRoleSpecInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var stRoleStream:SRoleStream = SRoleStream.fromByteArray(bytes); //角色信息
			retParam_.stRoleStream = stRoleStream;
			var origParam_:SOrigParam_GetRoleSpecInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleSpecInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleSpecInfo = new TEvt_GetRoleSpecInfo(TEvt_GetRoleSpecInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取角色面板信息
		private function _onTimeOut_GetRoleSpecInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleSpecInfo = new SRetParam_GetRoleSpecInfo();
			var event_:TEvt_GetRoleSpecInfo = new TEvt_GetRoleSpecInfo(TEvt_GetRoleSpecInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取得散仙列表
		private function _doReturn_GetFighters(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFighters = new SRetParam_GetFighters();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecFighters:Vector.<SFighterSpecInfo> = SFighterSpecInfo.vectorFromByteArray(bytes); //散仙信息
			retParam_.vecFighters = vecFighters;
			var origParam_:SOrigParam_GetFighters = _sessionMgr.getData(sessionID_) as SOrigParam_GetFighters;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFighters = new TEvt_GetFighters(TEvt_GetFighters.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得散仙列表
		private function _onTimeOut_GetFighters(sessionID:uint):void
		{
			var retParam:SRetParam_GetFighters = new SRetParam_GetFighters();
			var event_:TEvt_GetFighters = new TEvt_GetFighters(TEvt_GetFighters.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：存储新手引导信息
		private function _doReturn_StoreGuide(bytes:ByteArray):void
		{
			var retParam_:SRetParam_StoreGuide = new SRetParam_StoreGuide();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bResult:Boolean = bytes.readBoolean(); //结果
			retParam_.bResult = bResult;
			var origParam_:SOrigParam_StoreGuide = _sessionMgr.getData(sessionID_) as SOrigParam_StoreGuide;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_StoreGuide = new TEvt_StoreGuide(TEvt_StoreGuide.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：存储新手引导信息
		private function _onTimeOut_StoreGuide(sessionID:uint):void
		{
			var retParam:SRetParam_StoreGuide = new SRetParam_StoreGuide();
			var event_:TEvt_StoreGuide = new TEvt_StoreGuide(TEvt_StoreGuide.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取角色Buff信息
		private function _doReturn_GetRoleBuffInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleBuffInfo = new SRetParam_GetRoleBuffInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBuffInfo:Vector.<SBuffInfo> = SBuffInfo.vectorFromByteArray(bytes); //玩家Buff信息
			retParam_.vecBuffInfo = vecBuffInfo;
			var origParam_:SOrigParam_GetRoleBuffInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleBuffInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleBuffInfo = new TEvt_GetRoleBuffInfo(TEvt_GetRoleBuffInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取角色Buff信息
		private function _onTimeOut_GetRoleBuffInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleBuffInfo = new SRetParam_GetRoleBuffInfo();
			var event_:TEvt_GetRoleBuffInfo = new TEvt_GetRoleBuffInfo(TEvt_GetRoleBuffInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:RoleEvent;

		public static function get instance():RoleEvent
		{
			if(_instance == null)
				_instance = new RoleEvent();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function RoleEvent()
		{
			_protID = 11;
			_recvFuncList = [
				_doRecv_FighterInfoNotify, //FuncID: 1
				_doRecv_AddAppearIconNotify, //FuncID: 2
				_doRecv_BuffNotify, //FuncID: 3
				_doRecv_ChangeMapNotify, //FuncID: 4
				_doRecv_CritNotify, //FuncID: 5
				_doRecv_DelAppearIconNotify //FuncID: 6
			];

			_retFuncList = [
				_doReturn_GetRoleSpecInfo, //FuncID: 1
				_doReturn_GetFighters, //FuncID: 2
				_doReturn_StoreGuide, //FuncID: 3
				_doReturn_GetRoleBuffInfo //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_GetRoleSpecInfo, //FuncID: 1
				_onTimeOut_GetFighters, //FuncID: 2
				_onTimeOut_StoreGuide, //FuncID: 3
				_onTimeOut_GetRoleBuffInfo //FuncID: 4
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