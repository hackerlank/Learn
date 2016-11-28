/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ViewInfoProt.as
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.viewInfoProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.roleInfoDefine.SBeastSoulInfo;
	import net.protocol.itemProt.SEquipTrump;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：查看信息协议
	 */
	public class ViewInfoProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取对方主角信息
		 * @param strReceiveName 对方玩家名字
		 */
		public function send_GetRoleInfo(strReceiveName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetRoleInfo = new SOrigParam_GetRoleInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strReceiveName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取散仙信息
		 * @param strReceiveName 对方玩家名字
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 */
		public function send_GetFighterInfo(strReceiveName:String, qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetFighterInfo = new SOrigParam_GetFighterInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strReceiveName);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		//返回处理：获取对方主角信息
		private function _doReturn_GetRoleInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoleInfo = new SRetParam_GetRoleInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var RoleData:SRoleData = SRoleData.fromByteArray(bytes); //对方主角信息
			retParam_.RoleData = RoleData;
			var origParam_:SOrigParam_GetRoleInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoleInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoleInfo = new TEvt_GetRoleInfo(TEvt_GetRoleInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取对方主角信息
		private function _onTimeOut_GetRoleInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoleInfo = new SRetParam_GetRoleInfo();
			var event_:TEvt_GetRoleInfo = new TEvt_GetRoleInfo(TEvt_GetRoleInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取散仙信息
		private function _doReturn_GetFighterInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFighterInfo = new SRetParam_GetFighterInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var FighterData:SFighterData = SFighterData.fromByteArray(bytes); //对方散仙信息
			retParam_.FighterData = FighterData;
			var origParam_:SOrigParam_GetFighterInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetFighterInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFighterInfo = new TEvt_GetFighterInfo(TEvt_GetFighterInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取散仙信息
		private function _onTimeOut_GetFighterInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetFighterInfo = new SRetParam_GetFighterInfo();
			var event_:TEvt_GetFighterInfo = new TEvt_GetFighterInfo(TEvt_GetFighterInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ViewInfoProt;

		public static function get instance():ViewInfoProt
		{
			if(_instance == null)
				_instance = new ViewInfoProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ViewInfoProt()
		{
			_protID = 82;
			_recvFuncList = [
			];

			_retFuncList = [
				_doReturn_GetRoleInfo, //FuncID: 1
				_doReturn_GetFighterInfo //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_GetRoleInfo, //FuncID: 1
				_onTimeOut_GetFighterInfo //FuncID: 2
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