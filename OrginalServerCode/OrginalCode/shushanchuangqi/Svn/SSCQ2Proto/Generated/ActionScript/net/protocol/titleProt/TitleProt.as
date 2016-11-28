/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    TitleProt.as
//  Purpose:      称号协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
{
	import flash.utils.ByteArray;
	import net.protocol.roleInfoDefine.STitle;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：称号协议
	 */
	public class TitleProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：得到当前所有称号
		 */
		public function send_GetAllTitle(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetAllTitle = new SOrigParam_GetAllTitle();
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
		 * 发送：刷新称号列表
		 * @param wId (无符号16位整数)称号ID
		 * @param byPos (无符号8位整数)装备位置,0表示任意位置
		 */
		public function send_EquipTitle(wId:uint, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_EquipTitle = new SOrigParam_EquipTitle();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wId);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：获得称号
		private function _doRecv_AddTitle(bytes:ByteArray):void
		{
			var stTitleInfo:STitle = STitle.fromByteArray(bytes); //称号详情
			var event_:REvt_AddTitle = new REvt_AddTitle(REvt_AddTitle.DATA_RECEIVE);
			event_.stTitleInfo = stTitleInfo;
			dispatchEvent(event_);
		}

		//接收处理：删除称号
		private function _doRecv_DelTitle(bytes:ByteArray):void
		{
			var wId:uint = bytes.readUnsignedShort(); //(无符号16位整数)称号ID
			var event_:REvt_DelTitle = new REvt_DelTitle(REvt_DelTitle.DATA_RECEIVE);
			event_.wId = wId;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：得到当前所有称号
		private function _doReturn_GetAllTitle(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetAllTitle = new SRetParam_GetAllTitle();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecTitle:Vector.<STitle> = STitle.vectorFromByteArray(bytes); //当前所有称号
			retParam_.vecTitle = vecTitle;
			var origParam_:SOrigParam_GetAllTitle = _sessionMgr.getData(sessionID_) as SOrigParam_GetAllTitle;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetAllTitle = new TEvt_GetAllTitle(TEvt_GetAllTitle.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：得到当前所有称号
		private function _onTimeOut_GetAllTitle(sessionID:uint):void
		{
			var retParam:SRetParam_GetAllTitle = new SRetParam_GetAllTitle();
			var event_:TEvt_GetAllTitle = new TEvt_GetAllTitle(TEvt_GetAllTitle.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：刷新称号列表
		private function _doReturn_EquipTitle(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EquipTitle = new SRetParam_EquipTitle();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETitleResult)操作结果
			var wId:uint = bytes.readUnsignedShort(); //(无符号16位整数)称号ID
			var byPos:uint = bytes.readUnsignedByte(); //(无符号8位整数)装备位置
			retParam_.eResult = eResult;
			retParam_.wId = wId;
			retParam_.byPos = byPos;
			var origParam_:SOrigParam_EquipTitle = _sessionMgr.getData(sessionID_) as SOrigParam_EquipTitle;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EquipTitle = new TEvt_EquipTitle(TEvt_EquipTitle.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：刷新称号列表
		private function _onTimeOut_EquipTitle(sessionID:uint):void
		{
			var retParam:SRetParam_EquipTitle = new SRetParam_EquipTitle();
			var event_:TEvt_EquipTitle = new TEvt_EquipTitle(TEvt_EquipTitle.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:TitleProt;

		public static function get instance():TitleProt
		{
			if(_instance == null)
				_instance = new TitleProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function TitleProt()
		{
			_protID = 54;
			_recvFuncList = [
				_doRecv_AddTitle, //FuncID: 1
				_doRecv_DelTitle //FuncID: 2
			];

			_retFuncList = [
				_doReturn_GetAllTitle, //FuncID: 1
				_doReturn_EquipTitle //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GetAllTitle, //FuncID: 1
				_onTimeOut_EquipTitle //FuncID: 2
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