/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    Horse.as
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.horse
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：坐骑
	 */
	public class Horse extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取坐骑信息
		 */
		public function send_GetHorseList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：激活坐骑
		 * @param dwHorseID (无符号32位整数)坐骑ID
		 */
		public function send_ActiveHorse(dwHorseID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_ActiveHorse = new SOrigParam_ActiveHorse();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwHorseID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：坐骑进阶
		 * @param dwHorseID (无符号32位整数)坐骑ID
		 * @param bAll 是否一键进阶
		 */
		public function send_UpgradeHorse(dwHorseID:uint, bAll:Boolean, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_UpgradeHorse = new SOrigParam_UpgradeHorse();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwHorseID);
			bytes_.writeBoolean(bAll);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：骑乘状态修改
		 * @param dwHorseID (无符号32位整数)坐骑ID
		 * @param eHorseStatus (无符号32位整数)骑乘状态
		 */
		public function send_SetHorseStatus(dwHorseID:uint, eHorseStatus:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_SetHorseStatus = new SOrigParam_SetHorseStatus();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwHorseID);
			bytes_.writeUnsignedInt(eHorseStatus);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取坐骑属性
		 * @param dwHorseID (无符号32位整数)坐骑ID id=0为所有坐骑属性
		 */
		public function send_GetHorseAttr(dwHorseID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GetHorseAttr = new SOrigParam_GetHorseAttr();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwHorseID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：解锁技能属性（暂时不用）
		 * @param dwHorseID (无符号32位整数)坐骑ID
		 * @param dwPos (无符号32位整数)第几个技能属性 1开始
		 */
		public function send_UnLockHorseSkillAttr(dwHorseID:uint, dwPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_UnLockHorseSkillAttr = new SOrigParam_UnLockHorseSkillAttr();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwHorseID);
			bytes_.writeUnsignedInt(dwPos);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：坐骑信息
		private function _doRecv_HorseNotifyList(bytes:ByteArray):void
		{
			var vecHorseInfo:Vector.<SHorseInfo> = SHorseInfo.vectorFromByteArray(bytes); //坐骑信息
			var event_:REvt_HorseNotifyList = new REvt_HorseNotifyList(REvt_HorseNotifyList.DATA_RECEIVE);
			event_.vecHorseInfo = vecHorseInfo;
			dispatchEvent(event_);
		}

		//接收处理：坐骑信息更新
		private function _doRecv_HorseInfoChangeNotifyList(bytes:ByteArray):void
		{
			var dwHorseOpType:uint = bytes.readUnsignedInt(); //(无符号32位整数)更新类型
			var oHorseInfo:SHorseInfo = SHorseInfo.fromByteArray(bytes); //坐骑信息更新
			var event_:REvt_HorseInfoChangeNotifyList = new REvt_HorseInfoChangeNotifyList(REvt_HorseInfoChangeNotifyList.DATA_RECEIVE);
			event_.dwHorseOpType = dwHorseOpType;
			event_.oHorseInfo = oHorseInfo;
			dispatchEvent(event_);
		}

		//接收处理：坐骑属性信息
		private function _doRecv_HorseAttrNotify(bytes:ByteArray):void
		{
			var dwHorseID:uint = bytes.readUnsignedInt(); //(无符号32位整数)坐骑ID
			var vecAttrInfo:Vector.<SFtAttrMod> = SFtAttrMod.vectorFromByteArray(bytes); //坐骑属性信息表
			var event_:REvt_HorseAttrNotify = new REvt_HorseAttrNotify(REvt_HorseAttrNotify.DATA_RECEIVE);
			event_.dwHorseID = dwHorseID;
			event_.vecAttrInfo = vecAttrInfo;
			dispatchEvent(event_);
		}

		//接收处理：玩家速度通知
		private function _doRecv_SpeedChangeNotify(bytes:ByteArray):void
		{
			var dwSpeed:uint = bytes.readUnsignedInt(); //(无符号32位整数)玩家速度
			var event_:REvt_SpeedChangeNotify = new REvt_SpeedChangeNotify(REvt_SpeedChangeNotify.DATA_RECEIVE);
			event_.dwSpeed = dwSpeed;
			dispatchEvent(event_);
		}

		//接收处理：坐骑外观改变
		private function _doRecv_HorseLookChangeNotify(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色Id
			var dwHorseID:uint = bytes.readUnsignedInt(); //(无符号32位整数)坐骑模型
			var dwHorseLevel:uint = bytes.readUnsignedInt(); //(无符号32位整数)坐骑等级
			var event_:REvt_HorseLookChangeNotify = new REvt_HorseLookChangeNotify(REvt_HorseLookChangeNotify.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.dwHorseID = dwHorseID;
			event_.dwHorseLevel = dwHorseLevel;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：激活坐骑
		private function _doReturn_ActiveHorse(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ActiveHorse = new SRetParam_ActiveHorse();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_ActiveHorse = _sessionMgr.getData(sessionID_) as SOrigParam_ActiveHorse;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ActiveHorse = new TEvt_ActiveHorse(TEvt_ActiveHorse.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活坐骑
		private function _onTimeOut_ActiveHorse(sessionID:uint):void
		{
			var retParam:SRetParam_ActiveHorse = new SRetParam_ActiveHorse();
			var event_:TEvt_ActiveHorse = new TEvt_ActiveHorse(TEvt_ActiveHorse.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：坐骑进阶
		private function _doReturn_UpgradeHorse(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeHorse = new SRetParam_UpgradeHorse();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_UpgradeHorse = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeHorse;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeHorse = new TEvt_UpgradeHorse(TEvt_UpgradeHorse.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：坐骑进阶
		private function _onTimeOut_UpgradeHorse(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeHorse = new SRetParam_UpgradeHorse();
			var event_:TEvt_UpgradeHorse = new TEvt_UpgradeHorse(TEvt_UpgradeHorse.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：骑乘状态修改
		private function _doReturn_SetHorseStatus(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetHorseStatus = new SRetParam_SetHorseStatus();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_SetHorseStatus = _sessionMgr.getData(sessionID_) as SOrigParam_SetHorseStatus;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetHorseStatus = new TEvt_SetHorseStatus(TEvt_SetHorseStatus.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：骑乘状态修改
		private function _onTimeOut_SetHorseStatus(sessionID:uint):void
		{
			var retParam:SRetParam_SetHorseStatus = new SRetParam_SetHorseStatus();
			var event_:TEvt_SetHorseStatus = new TEvt_SetHorseStatus(TEvt_SetHorseStatus.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取坐骑属性
		private function _doReturn_GetHorseAttr(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetHorseAttr = new SRetParam_GetHorseAttr();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwRet:uint = bytes.readUnsignedInt(); //(无符号32位整数)结果 0成功其他错误码
			retParam_.dwRet = dwRet;
			var origParam_:SOrigParam_GetHorseAttr = _sessionMgr.getData(sessionID_) as SOrigParam_GetHorseAttr;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetHorseAttr = new TEvt_GetHorseAttr(TEvt_GetHorseAttr.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取坐骑属性
		private function _onTimeOut_GetHorseAttr(sessionID:uint):void
		{
			var retParam:SRetParam_GetHorseAttr = new SRetParam_GetHorseAttr();
			var event_:TEvt_GetHorseAttr = new TEvt_GetHorseAttr(TEvt_GetHorseAttr.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：解锁技能属性（暂时不用）
		private function _doReturn_UnLockHorseSkillAttr(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UnLockHorseSkillAttr = new SRetParam_UnLockHorseSkillAttr();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_UnLockHorseSkillAttr = _sessionMgr.getData(sessionID_) as SOrigParam_UnLockHorseSkillAttr;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UnLockHorseSkillAttr = new TEvt_UnLockHorseSkillAttr(TEvt_UnLockHorseSkillAttr.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：解锁技能属性（暂时不用）
		private function _onTimeOut_UnLockHorseSkillAttr(sessionID:uint):void
		{
			var retParam:SRetParam_UnLockHorseSkillAttr = new SRetParam_UnLockHorseSkillAttr();
			var event_:TEvt_UnLockHorseSkillAttr = new TEvt_UnLockHorseSkillAttr(TEvt_UnLockHorseSkillAttr.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:Horse;

		public static function get instance():Horse
		{
			if(_instance == null)
				_instance = new Horse();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function Horse()
		{
			_protID = 74;
			_recvFuncList = [
				_doRecv_HorseNotifyList, //FuncID: 1
				_doRecv_HorseInfoChangeNotifyList, //FuncID: 2
				_doRecv_HorseAttrNotify, //FuncID: 3
				_doRecv_SpeedChangeNotify, //FuncID: 4
				_doRecv_HorseLookChangeNotify //FuncID: 5
			];

			_retFuncList = [
				_doReturn_ActiveHorse, //FuncID: 1
				_doReturn_UpgradeHorse, //FuncID: 2
				_doReturn_SetHorseStatus, //FuncID: 3
				_doReturn_GetHorseAttr, //FuncID: 4
				_doReturn_UnLockHorseSkillAttr //FuncID: 5
			];

			_timeFuncList = [
				_onTimeOut_ActiveHorse, //FuncID: 1
				_onTimeOut_UpgradeHorse, //FuncID: 2
				_onTimeOut_SetHorseStatus, //FuncID: 3
				_onTimeOut_GetHorseAttr, //FuncID: 4
				_onTimeOut_UnLockHorseSkillAttr //FuncID: 5
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