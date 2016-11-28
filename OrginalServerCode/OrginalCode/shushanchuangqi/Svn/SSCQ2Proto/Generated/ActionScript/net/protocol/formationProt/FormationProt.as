/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    FormationProt.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.roleInfoDefine.SBeastSoulInfo;
	import net.protocol.roleInfoDefine.SPetDataInfo;
	import net.protocol.roleInfoDefine.SRolePetInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：阵灵相关协议
	 */
	public class FormationProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：上阵/下阵
		 * @param qwInstID (无符号64位整数)散仙唯一ID
		 * @param iPos (有符号32位整数)目标位置: [0-8]为上阵 <-1时为下阵
		 */
		public function send_FormationUp(qwInstID:BigInteger, iPos:int, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_FormationUp = new SOrigParam_FormationUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			bytes_.writeInt(iPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置阵形
		 * @param vecSLineup 阵形列表
		 */
		public function send_SetFormation(vecSLineup:Vector.<SLineup>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_SetFormation = new SOrigParam_SetFormation();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			SLineup.vectorToByteArray(vecSLineup, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：取得所有阵灵信息
		 */
		public function send_PetsGet(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_PetsGet = new SOrigParam_PetsGet();
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
		 * 发送：激活阵灵
		 * @param wPetID (无符号16位整数)阵灵ID
		 */
		public function send_PetsActive(wPetID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_PetsActive = new SOrigParam_PetsActive();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPetID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置阵灵状态
		 * @param wPetID (无符号16位整数)阵灵ID
		 * @param byType (无符号8位整数)状态: 1-出战且显示 2-出战隐藏
		 */
		public function send_PetsStatus(wPetID:uint, byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_PetsStatus = new SOrigParam_PetsStatus();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPetID);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：阵灵幻化
		 * @param wPetID (无符号16位整数)阵灵ID
		 */
		public function send_PetsUpgrade(wPetID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_PetsUpgrade = new SOrigParam_PetsUpgrade();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPetID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：阵灵升级
		 * @param wPetID (无符号16位整数)阵灵ID
		 * @param byType (无符号8位整数)升级消耗类型 0-朱果 1-蟠桃
		 */
		public function send_PetsLevelUp(wPetID:uint, byType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_PetsLevelUp = new SOrigParam_PetsLevelUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPetID);
			bytes_.writeByte(byType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：阵灵一键升级
		 * @param wPetID (无符号16位整数)阵灵ID
		 */
		public function send_QuickPetsLevelUp(wPetID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_QuickPetsLevelUp = new SOrigParam_QuickPetsLevelUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPetID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取兽魂信息
		 */
		public function send_GetBeastSoul(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetBeastSoul = new SOrigParam_GetBeastSoul();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：升级兽魂
		 * @param eType (枚举类型：roleInfoDefine.EBeastSoulType)兽魂种类
		 */
		public function send_UpgradeBeastSoul(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_UpgradeBeastSoul = new SOrigParam_UpgradeBeastSoul();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：阵形信息
		private function _doRecv_FormationNotify(bytes:ByteArray):void
		{
			var wFormationID:uint = bytes.readUnsignedShort(); //(无符号16位整数)阵形ID
			var bySelected:uint = bytes.readUnsignedByte(); //(无符号8位整数)状态: 0-未启用 1-未启用
			var event_:REvt_FormationNotify = new REvt_FormationNotify(REvt_FormationNotify.DATA_RECEIVE);
			event_.wFormationID = wFormationID;
			event_.bySelected = bySelected;
			dispatchEvent(event_);
		}

		//接收处理：阵灵信息
		private function _doRecv_PetDataNotify(bytes:ByteArray):void
		{
			var wPetID:uint = bytes.readUnsignedShort(); //(无符号16位整数)阵灵ID
			var bySelected:uint = bytes.readUnsignedByte(); //(无符号8位整数)状态: 0-未启用 1-出战且显示 2-出战隐藏
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)阵灵等级
			var dwExp:uint = bytes.readUnsignedInt(); //(无符号32位整数)经验
			var event_:REvt_PetDataNotify = new REvt_PetDataNotify(REvt_PetDataNotify.DATA_RECEIVE);
			event_.wPetID = wPetID;
			event_.bySelected = bySelected;
			event_.byLevel = byLevel;
			event_.dwExp = dwExp;
			dispatchEvent(event_);
		}

		//接收处理：全局阵灵信息
		private function _doRecv_RolePetNotify(bytes:ByteArray):void
		{
			var sRolePetInfo:SRolePetInfo = SRolePetInfo.fromByteArray(bytes); //阵灵全局信息
			var event_:REvt_RolePetNotify = new REvt_RolePetNotify(REvt_RolePetNotify.DATA_RECEIVE);
			event_.sRolePetInfo = sRolePetInfo;
			dispatchEvent(event_);
		}

		//接收处理：兽魂信息
		private function _doRecv_BeastNotify(bytes:ByteArray):void
		{
			var wBeastID:uint = bytes.readUnsignedShort(); //(无符号16位整数)兽魂ID
			var event_:REvt_BeastNotify = new REvt_BeastNotify(REvt_BeastNotify.DATA_RECEIVE);
			event_.wBeastID = wBeastID;
			dispatchEvent(event_);
		}

		//接收处理：兽魂信息
		private function _doRecv_BeastSoulNotify(bytes:ByteArray):void
		{
			var vecBeastSoul:Vector.<SBeastSoulInfo> = SBeastSoulInfo.vectorFromByteArray(bytes); //兽魂信息
			var event_:REvt_BeastSoulNotify = new REvt_BeastSoulNotify(REvt_BeastSoulNotify.DATA_RECEIVE);
			event_.vecBeastSoul = vecBeastSoul;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：上阵/下阵
		private function _doReturn_FormationUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FormationUp = new SRetParam_FormationUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_FormationUp = _sessionMgr.getData(sessionID_) as SOrigParam_FormationUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FormationUp = new TEvt_FormationUp(TEvt_FormationUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：上阵/下阵
		private function _onTimeOut_FormationUp(sessionID:uint):void
		{
			var retParam:SRetParam_FormationUp = new SRetParam_FormationUp();
			var event_:TEvt_FormationUp = new TEvt_FormationUp(TEvt_FormationUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：设置阵形
		private function _doReturn_SetFormation(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetFormation = new SRetParam_SetFormation();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var bRet:Boolean = bytes.readBoolean(); //结果
			retParam_.bRet = bRet;
			var origParam_:SOrigParam_SetFormation = _sessionMgr.getData(sessionID_) as SOrigParam_SetFormation;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetFormation = new TEvt_SetFormation(TEvt_SetFormation.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：设置阵形
		private function _onTimeOut_SetFormation(sessionID:uint):void
		{
			var retParam:SRetParam_SetFormation = new SRetParam_SetFormation();
			var event_:TEvt_SetFormation = new TEvt_SetFormation(TEvt_SetFormation.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：取得所有阵灵信息
		private function _doReturn_PetsGet(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PetsGet = new SRetParam_PetsGet();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecPets:Vector.<SPetDataInfo> = SPetDataInfo.vectorFromByteArray(bytes); //阵灵信息列表
			retParam_.vecPets = vecPets;
			var origParam_:SOrigParam_PetsGet = _sessionMgr.getData(sessionID_) as SOrigParam_PetsGet;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PetsGet = new TEvt_PetsGet(TEvt_PetsGet.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：取得所有阵灵信息
		private function _onTimeOut_PetsGet(sessionID:uint):void
		{
			var retParam:SRetParam_PetsGet = new SRetParam_PetsGet();
			var event_:TEvt_PetsGet = new TEvt_PetsGet(TEvt_PetsGet.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：激活阵灵
		private function _doReturn_PetsActive(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PetsActive = new SRetParam_PetsActive();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PetsActive = _sessionMgr.getData(sessionID_) as SOrigParam_PetsActive;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PetsActive = new TEvt_PetsActive(TEvt_PetsActive.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：激活阵灵
		private function _onTimeOut_PetsActive(sessionID:uint):void
		{
			var retParam:SRetParam_PetsActive = new SRetParam_PetsActive();
			var event_:TEvt_PetsActive = new TEvt_PetsActive(TEvt_PetsActive.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：设置阵灵状态
		private function _doReturn_PetsStatus(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PetsStatus = new SRetParam_PetsStatus();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PetsStatus = _sessionMgr.getData(sessionID_) as SOrigParam_PetsStatus;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PetsStatus = new TEvt_PetsStatus(TEvt_PetsStatus.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：设置阵灵状态
		private function _onTimeOut_PetsStatus(sessionID:uint):void
		{
			var retParam:SRetParam_PetsStatus = new SRetParam_PetsStatus();
			var event_:TEvt_PetsStatus = new TEvt_PetsStatus(TEvt_PetsStatus.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：阵灵幻化
		private function _doReturn_PetsUpgrade(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PetsUpgrade = new SRetParam_PetsUpgrade();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PetsUpgrade = _sessionMgr.getData(sessionID_) as SOrigParam_PetsUpgrade;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PetsUpgrade = new TEvt_PetsUpgrade(TEvt_PetsUpgrade.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：阵灵幻化
		private function _onTimeOut_PetsUpgrade(sessionID:uint):void
		{
			var retParam:SRetParam_PetsUpgrade = new SRetParam_PetsUpgrade();
			var event_:TEvt_PetsUpgrade = new TEvt_PetsUpgrade(TEvt_PetsUpgrade.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：阵灵升级
		private function _doReturn_PetsLevelUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_PetsLevelUp = new SRetParam_PetsLevelUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_PetsLevelUp = _sessionMgr.getData(sessionID_) as SOrigParam_PetsLevelUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_PetsLevelUp = new TEvt_PetsLevelUp(TEvt_PetsLevelUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：阵灵升级
		private function _onTimeOut_PetsLevelUp(sessionID:uint):void
		{
			var retParam:SRetParam_PetsLevelUp = new SRetParam_PetsLevelUp();
			var event_:TEvt_PetsLevelUp = new TEvt_PetsLevelUp(TEvt_PetsLevelUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：阵灵一键升级
		private function _doReturn_QuickPetsLevelUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_QuickPetsLevelUp = new SRetParam_QuickPetsLevelUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFormPetType)结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_QuickPetsLevelUp = _sessionMgr.getData(sessionID_) as SOrigParam_QuickPetsLevelUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_QuickPetsLevelUp = new TEvt_QuickPetsLevelUp(TEvt_QuickPetsLevelUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：阵灵一键升级
		private function _onTimeOut_QuickPetsLevelUp(sessionID:uint):void
		{
			var retParam:SRetParam_QuickPetsLevelUp = new SRetParam_QuickPetsLevelUp();
			var event_:TEvt_QuickPetsLevelUp = new TEvt_QuickPetsLevelUp(TEvt_QuickPetsLevelUp.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取兽魂信息
		private function _doReturn_GetBeastSoul(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetBeastSoul = new SRetParam_GetBeastSoul();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EBeastSoulResult)获取结果
			var vecBeastSoul:Vector.<SBeastSoulInfo> = SBeastSoulInfo.vectorFromByteArray(bytes); //兽魂信息
			retParam_.eResult = eResult;
			retParam_.vecBeastSoul = vecBeastSoul;
			var origParam_:SOrigParam_GetBeastSoul = _sessionMgr.getData(sessionID_) as SOrigParam_GetBeastSoul;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetBeastSoul = new TEvt_GetBeastSoul(TEvt_GetBeastSoul.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取兽魂信息
		private function _onTimeOut_GetBeastSoul(sessionID:uint):void
		{
			var retParam:SRetParam_GetBeastSoul = new SRetParam_GetBeastSoul();
			var event_:TEvt_GetBeastSoul = new TEvt_GetBeastSoul(TEvt_GetBeastSoul.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：升级兽魂
		private function _doReturn_UpgradeBeastSoul(bytes:ByteArray):void
		{
			var retParam_:SRetParam_UpgradeBeastSoul = new SRetParam_UpgradeBeastSoul();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EBeastSoulResult)获取结果
			var vecBeastSoul:Vector.<SBeastSoulInfo> = SBeastSoulInfo.vectorFromByteArray(bytes); //兽魂信息
			var vecItem:Vector.<SBeastSoulItem> = SBeastSoulItem.vectorFromByteArray(bytes); //包裹或仓库中道具的列表
			retParam_.eResult = eResult;
			retParam_.vecBeastSoul = vecBeastSoul;
			retParam_.vecItem = vecItem;
			var origParam_:SOrigParam_UpgradeBeastSoul = _sessionMgr.getData(sessionID_) as SOrigParam_UpgradeBeastSoul;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_UpgradeBeastSoul = new TEvt_UpgradeBeastSoul(TEvt_UpgradeBeastSoul.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：升级兽魂
		private function _onTimeOut_UpgradeBeastSoul(sessionID:uint):void
		{
			var retParam:SRetParam_UpgradeBeastSoul = new SRetParam_UpgradeBeastSoul();
			var event_:TEvt_UpgradeBeastSoul = new TEvt_UpgradeBeastSoul(TEvt_UpgradeBeastSoul.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:FormationProt;

		public static function get instance():FormationProt
		{
			if(_instance == null)
				_instance = new FormationProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function FormationProt()
		{
			_protID = 22;
			_recvFuncList = [
				_doRecv_FormationNotify, //FuncID: 1
				_doRecv_PetDataNotify, //FuncID: 2
				_doRecv_RolePetNotify, //FuncID: 3
				_doRecv_BeastNotify, //FuncID: 4
				_doRecv_BeastSoulNotify //FuncID: 5
			];

			_retFuncList = [
				_doReturn_FormationUp, //FuncID: 1
				_doReturn_SetFormation, //FuncID: 2
				_doReturn_PetsGet, //FuncID: 3
				_doReturn_PetsActive, //FuncID: 4
				_doReturn_PetsStatus, //FuncID: 5
				_doReturn_PetsUpgrade, //FuncID: 6
				_doReturn_PetsLevelUp, //FuncID: 7
				_doReturn_QuickPetsLevelUp, //FuncID: 8
				_doReturn_GetBeastSoul, //FuncID: 9
				_doReturn_UpgradeBeastSoul //FuncID: 10
			];

			_timeFuncList = [
				_onTimeOut_FormationUp, //FuncID: 1
				_onTimeOut_SetFormation, //FuncID: 2
				_onTimeOut_PetsGet, //FuncID: 3
				_onTimeOut_PetsActive, //FuncID: 4
				_onTimeOut_PetsStatus, //FuncID: 5
				_onTimeOut_PetsUpgrade, //FuncID: 6
				_onTimeOut_PetsLevelUp, //FuncID: 7
				_onTimeOut_QuickPetsLevelUp, //FuncID: 8
				_onTimeOut_GetBeastSoul, //FuncID: 9
				_onTimeOut_UpgradeBeastSoul //FuncID: 10
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