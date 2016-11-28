/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    MapProt.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.battleGS.SFeatureBase;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：地图相关功能的协议
	 */
	public class MapProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：角色移动请求
		 * @param wMapID (无符号16位整数)地图ID
		 * @param vecPosition 移动位置列表
		 */
		public function send_PlayerMoveReq(wMapID:uint, vecPosition:Vector.<SPosition>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeShort(wMapID);
			SPosition.vectorToByteArray(vecPosition, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：角色停止移动
		 * @param wMapID (无符号16位整数)地图ID
		 * @param StopPos 停止点
		 */
		public function send_PlayerStopReq(wMapID:uint, StopPos:SPosition):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeShort(wMapID);
			StopPos.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取玩家的外观信息
		 * @param qwUserID (无符号64位整数)目标玩家ID
		 */
		public function send_GetPlayerAppear(qwUserID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetPlayerAppear = new SOrigParam_GetPlayerAppear();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求跳地图
		 * @param wMapID (无符号16位整数)地图ID
		 * @param byIndex (无符号8位整数)地图序号,255表示任意地图
		 */
		public function send_JumpMap(wMapID:uint, byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_JumpMap = new SOrigParam_JumpMap();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMapID);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求地图负载
		 * @param wMapID (无符号16位整数)地图ID
		 */
		public function send_GetMapOverLoad(wMapID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetMapOverLoad = new SOrigParam_GetMapOverLoad();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMapID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：通知玩家进入地图
		private function _doRecv_UserEnterMapNtf(bytes:ByteArray):void
		{
			var wMapID:uint = bytes.readUnsignedShort(); //(无符号16位整数)地图ID
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)当前的角色ID
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)地图序号,非主城返回255
			var byTotal:uint = bytes.readUnsignedByte(); //(无符号8位整数)同Id地图总数,非主城返回0
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //进入位置
			var fDir:Number = bytes.readFloat(); //(Float)方向
			var event_:REvt_UserEnterMapNtf = new REvt_UserEnterMapNtf(REvt_UserEnterMapNtf.DATA_RECEIVE);
			event_.wMapID = wMapID;
			event_.qwRoleID = qwRoleID;
			event_.byIndex = byIndex;
			event_.byTotal = byTotal;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			dispatchEvent(event_);
		}

		//接收处理：新地图产生，通知同地图玩家
		private function _doRecv_NoticeNewMap(bytes:ByteArray):void
		{
			var vecLoad:Vector.<MapOverLoad> = MapOverLoad.vectorFromByteArray(bytes); //地图负载
			var event_:REvt_NoticeNewMap = new REvt_NoticeNewMap(REvt_NoticeNewMap.DATA_RECEIVE);
			event_.vecLoad = vecLoad;
			dispatchEvent(event_);
		}

		//接收处理：角色(非当前控制)地图信息通知
		private function _doRecv_RoleMapInfoNtf(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色的ID
			var wMapID:uint = bytes.readUnsignedShort(); //(无符号16位整数)地图ID
			var event_:REvt_RoleMapInfoNtf = new REvt_RoleMapInfoNtf(REvt_RoleMapInfoNtf.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.wMapID = wMapID;
			dispatchEvent(event_);
		}

		//接收处理：通知角色移动失败
		private function _doRecv_PlayerMoveFail(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色ID
			var rLastPosition:SPosition = SPosition.fromByteArray(bytes); //上一个位置
			var vecPosition:Vector.<SPosition> = SPosition.vectorFromByteArray(bytes); //移动位置列表
			var event_:REvt_PlayerMoveFail = new REvt_PlayerMoveFail(REvt_PlayerMoveFail.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.rLastPosition = rLastPosition;
			event_.vecPosition = vecPosition;
			dispatchEvent(event_);
		}

		//接收处理：通知自己的玩家角色出现
		private function _doRecv_NotifyAppear(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色ID
			var rPlayerAppear:SPlayerAppear = SPlayerAppear.fromByteArray(bytes); //玩家的外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var dwAppearState:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态(EAppearState按位或的结果)
			var event_:REvt_NotifyAppear = new REvt_NotifyAppear(REvt_NotifyAppear.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.rPlayerAppear = rPlayerAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.dwAppearState = dwAppearState;
			dispatchEvent(event_);
		}

		//接收处理：通知别的玩家角色出现
		private function _doRecv_PlayerAppear(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)角色ID
			var rPlayerAppear:SPlayerAppear = SPlayerAppear.fromByteArray(bytes); //玩家的外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var dwAppearState:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态(EAppearState按位或的结果)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_PlayerAppear = new REvt_PlayerAppear(REvt_PlayerAppear.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.rPlayerAppear = rPlayerAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.dwAppearState = dwAppearState;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知Creature移动
		private function _doRecv_NotifyCreatureMove(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var vecPosition:Vector.<SPosition> = SPosition.vectorFromByteArray(bytes); //移动位置列表
			var event_:REvt_NotifyCreatureMove = new REvt_NotifyCreatureMove(REvt_NotifyCreatureMove.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.vecPosition = vecPosition;
			dispatchEvent(event_);
		}

		//接收处理：通知Creature跳点
		private function _doRecv_NotifyCreatureJump(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)Creature ID
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //跳点目的位置
			var wJumpId:uint = bytes.readUnsignedShort(); //(无符号16位整数)跳点ID
			var event_:REvt_NotifyCreatureJump = new REvt_NotifyCreatureJump(REvt_NotifyCreatureJump.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.rPosition = rPosition;
			event_.wJumpId = wJumpId;
			dispatchEvent(event_);
		}

		//接收处理：通知Creature当前状态
		private function _doRecv_NotifyCreatureState(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)Creature ID
			var dwAppearState:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态(EAppearState按位或的结果)
			var event_:REvt_NotifyCreatureState = new REvt_NotifyCreatureState(REvt_NotifyCreatureState.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.dwAppearState = dwAppearState;
			dispatchEvent(event_);
		}

		//接收处理：通知Creature停止
		private function _doRecv_NotifyCreatureStop(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var rDestPosition:SPosition = SPosition.fromByteArray(bytes); //最终位置
			var event_:REvt_NotifyCreatureStop = new REvt_NotifyCreatureStop(REvt_NotifyCreatureStop.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.rDestPosition = rDestPosition;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上生物消失
		private function _doRecv_CreatureDisappear(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var bDieFade:Boolean = bytes.readBoolean(); //true为死亡消失，false为移出视野
			var event_:REvt_CreatureDisappear = new REvt_CreatureDisappear(REvt_CreatureDisappear.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.bDieFade = bDieFade;
			dispatchEvent(event_);
		}

		//接收处理：通知NPC出现
		private function _doRecv_NpcAppear(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var rNpcAppear:SNpcAppear = SNpcAppear.fromByteArray(bytes); //NPC外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_NpcAppear = new REvt_NpcAppear(REvt_NpcAppear.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.rNpcAppear = rNpcAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知怪物出现
		private function _doRecv_MonsterAppear(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var rMonsterAppear:SMonsterAppear = SMonsterAppear.fromByteArray(bytes); //怪物外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var dwAppearState:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态(EAppearState按位或的结果)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_MonsterAppear = new REvt_MonsterAppear(REvt_MonsterAppear.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.rMonsterAppear = rMonsterAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.dwAppearState = dwAppearState;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知开关出现
		private function _doRecv_SwitcherAppear(bytes:ByteArray):void
		{
			var dwInstID:uint = bytes.readUnsignedInt(); //(无符号32位整数)唯一实例ID
			var rSwitcherAppear:SSwitcherAppear = SSwitcherAppear.fromByteArray(bytes); //开关外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_SwitcherAppear = new REvt_SwitcherAppear(REvt_SwitcherAppear.DATA_RECEIVE);
			event_.dwInstID = dwInstID;
			event_.rSwitcherAppear = rSwitcherAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上开关消失
		private function _doRecv_SwitcherDisappear(bytes:ByteArray):void
		{
			var dwInstID:uint = bytes.readUnsignedInt(); //(无符号32位整数)开关唯一ID
			var event_:REvt_SwitcherDisappear = new REvt_SwitcherDisappear(REvt_SwitcherDisappear.DATA_RECEIVE);
			event_.dwInstID = dwInstID;
			dispatchEvent(event_);
		}

		//接收处理：通知开关当前状态
		private function _doRecv_NotifySwitcherState(bytes:ByteArray):void
		{
			var dwInstID:uint = bytes.readUnsignedInt(); //(无符号32位整数)开关唯一实例ID
			var bOpen:Boolean = bytes.readBoolean(); //当前开关是否开启
			var event_:REvt_NotifySwitcherState = new REvt_NotifySwitcherState(REvt_NotifySwitcherState.DATA_RECEIVE);
			event_.dwInstID = dwInstID;
			event_.bOpen = bOpen;
			dispatchEvent(event_);
		}

		//接收处理：通知采集物出现
		private function _doRecv_GatherAppear(bytes:ByteArray):void
		{
			var dwGatherID:uint = bytes.readUnsignedInt(); //(无符号32位整数)生物ID
			var rGatherAppear:SGatherAppear = SGatherAppear.fromByteArray(bytes); //采集物外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_GatherAppear = new REvt_GatherAppear(REvt_GatherAppear.DATA_RECEIVE);
			event_.dwGatherID = dwGatherID;
			event_.rGatherAppear = rGatherAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上采集物消失
		private function _doRecv_GatherDisappear(bytes:ByteArray):void
		{
			var dwGatherID:uint = bytes.readUnsignedInt(); //(无符号32位整数)采集物ID
			var bDieFade:Boolean = bytes.readBoolean(); //true为采集后消失，false为移出视野
			var event_:REvt_GatherDisappear = new REvt_GatherDisappear(REvt_GatherDisappear.DATA_RECEIVE);
			event_.dwGatherID = dwGatherID;
			event_.bDieFade = bDieFade;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上采集物改变
		private function _doRecv_GatherChange(bytes:ByteArray):void
		{
			var dwGatherID:uint = bytes.readUnsignedInt(); //(无符号32位整数)采集物ID
			var rGatherAppear:SGatherAppear = SGatherAppear.fromByteArray(bytes); //采集物外观
			var event_:REvt_GatherChange = new REvt_GatherChange(REvt_GatherChange.DATA_RECEIVE);
			event_.dwGatherID = dwGatherID;
			event_.rGatherAppear = rGatherAppear;
			dispatchEvent(event_);
		}

		//接收处理：阻挡物出现
		private function _doRecv_BlockerAppear(bytes:ByteArray):void
		{
			var dwInstID:uint = bytes.readUnsignedInt(); //(无符号32位整数)唯一ID
			var rBlockerAppear:SBlockerAppear = SBlockerAppear.fromByteArray(bytes); //阻挡物开关
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var fDir:Number = bytes.readFloat(); //(Float)方向(弧度)
			var bBorn:Boolean = bytes.readBoolean(); //true为出生，false为进入视野
			var event_:REvt_BlockerAppear = new REvt_BlockerAppear(REvt_BlockerAppear.DATA_RECEIVE);
			event_.dwInstID = dwInstID;
			event_.rBlockerAppear = rBlockerAppear;
			event_.rPosition = rPosition;
			event_.fDir = fDir;
			event_.bBorn = bBorn;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上阻挡物消失
		private function _doRecv_BlockerDisappear(bytes:ByteArray):void
		{
			var dwInstID:uint = bytes.readUnsignedInt(); //(无符号32位整数)阻挡物唯一ID
			var event_:REvt_BlockerDisappear = new REvt_BlockerDisappear(REvt_BlockerDisappear.DATA_RECEIVE);
			event_.dwInstID = dwInstID;
			dispatchEvent(event_);
		}

		//接收处理：通知怪物改变
		private function _doRecv_MonsterChange(bytes:ByteArray):void
		{
			var qwCreatureID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)生物ID
			var rMonsterAppear:SMonsterAppear = SMonsterAppear.fromByteArray(bytes); //怪物外观
			var event_:REvt_MonsterChange = new REvt_MonsterChange(REvt_MonsterChange.DATA_RECEIVE);
			event_.qwCreatureID = qwCreatureID;
			event_.rMonsterAppear = rMonsterAppear;
			dispatchEvent(event_);
		}

		//接收处理：通知区域出现
		private function _doRecv_AreaAppear(bytes:ByteArray):void
		{
			var dwAreaID:uint = bytes.readUnsignedInt(); //(无符号32位整数)区域实例ID
			var rAreaAppear:SAreaAppear = SAreaAppear.fromByteArray(bytes); //区域外观
			var rPosition:SPosition = SPosition.fromByteArray(bytes); //出现位置
			var event_:REvt_AreaAppear = new REvt_AreaAppear(REvt_AreaAppear.DATA_RECEIVE);
			event_.dwAreaID = dwAreaID;
			event_.rAreaAppear = rAreaAppear;
			event_.rPosition = rPosition;
			dispatchEvent(event_);
		}

		//接收处理：通知地图上区域消失
		private function _doRecv_AreaDisappear(bytes:ByteArray):void
		{
			var dwAreaID:uint = bytes.readUnsignedInt(); //(无符号32位整数)区域实例ID
			var event_:REvt_AreaDisappear = new REvt_AreaDisappear(REvt_AreaDisappear.DATA_RECEIVE);
			event_.dwAreaID = dwAreaID;
			dispatchEvent(event_);
		}

		//接收处理：怪物发现敌人
		private function _doRecv_MonsterTargetChange(bytes:ByteArray):void
		{
			var qwMonsterID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)怪物ID
			var qwTargetID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)目标ID
			var event_:REvt_MonsterTargetChange = new REvt_MonsterTargetChange(REvt_MonsterTargetChange.DATA_RECEIVE);
			event_.qwMonsterID = qwMonsterID;
			event_.qwTargetID = qwTargetID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取玩家的外观信息
		private function _doReturn_GetPlayerAppear(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPlayerAppear = new SRetParam_GetPlayerAppear();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0 成功 1失败
			var rPlayerAppear:SPlayerAppear = SPlayerAppear.fromByteArray(bytes); //玩家的外观
			retParam_.byRet = byRet;
			retParam_.rPlayerAppear = rPlayerAppear;
			var origParam_:SOrigParam_GetPlayerAppear = _sessionMgr.getData(sessionID_) as SOrigParam_GetPlayerAppear;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPlayerAppear = new TEvt_GetPlayerAppear(TEvt_GetPlayerAppear.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取玩家的外观信息
		private function _onTimeOut_GetPlayerAppear(sessionID:uint):void
		{
			var retParam:SRetParam_GetPlayerAppear = new SRetParam_GetPlayerAppear();
			var event_:TEvt_GetPlayerAppear = new TEvt_GetPlayerAppear(TEvt_GetPlayerAppear.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求跳地图
		private function _doReturn_JumpMap(bytes:ByteArray):void
		{
			var retParam_:SRetParam_JumpMap = new SRetParam_JumpMap();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var byRet:uint = bytes.readUnsignedByte(); //(无符号8位整数)0成功
			var wMapID:uint = bytes.readUnsignedShort(); //(无符号16位整数)地图ID
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)地图序号,255表示任意地图
			retParam_.byRet = byRet;
			retParam_.wMapID = wMapID;
			retParam_.byIndex = byIndex;
			var origParam_:SOrigParam_JumpMap = _sessionMgr.getData(sessionID_) as SOrigParam_JumpMap;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_JumpMap = new TEvt_JumpMap(TEvt_JumpMap.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求跳地图
		private function _onTimeOut_JumpMap(sessionID:uint):void
		{
			var retParam:SRetParam_JumpMap = new SRetParam_JumpMap();
			var event_:TEvt_JumpMap = new TEvt_JumpMap(TEvt_JumpMap.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求地图负载
		private function _doReturn_GetMapOverLoad(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMapOverLoad = new SRetParam_GetMapOverLoad();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wMapID:uint = bytes.readUnsignedShort(); //(无符号16位整数)地图ID
			var vecLoad:Vector.<MapOverLoad> = MapOverLoad.vectorFromByteArray(bytes); //地图ID
			retParam_.wMapID = wMapID;
			retParam_.vecLoad = vecLoad;
			var origParam_:SOrigParam_GetMapOverLoad = _sessionMgr.getData(sessionID_) as SOrigParam_GetMapOverLoad;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMapOverLoad = new TEvt_GetMapOverLoad(TEvt_GetMapOverLoad.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求地图负载
		private function _onTimeOut_GetMapOverLoad(sessionID:uint):void
		{
			var retParam:SRetParam_GetMapOverLoad = new SRetParam_GetMapOverLoad();
			var event_:TEvt_GetMapOverLoad = new TEvt_GetMapOverLoad(TEvt_GetMapOverLoad.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:MapProt;

		public static function get instance():MapProt
		{
			if(_instance == null)
				_instance = new MapProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function MapProt()
		{
			_protID = 5;
			_recvFuncList = [
				_doRecv_UserEnterMapNtf, //FuncID: 1
				_doRecv_NoticeNewMap, //FuncID: 2
				_doRecv_RoleMapInfoNtf, //FuncID: 3
				_doRecv_PlayerMoveFail, //FuncID: 4
				_doRecv_NotifyAppear, //FuncID: 5
				_doRecv_PlayerAppear, //FuncID: 6
				_doRecv_NotifyCreatureMove, //FuncID: 7
				_doRecv_NotifyCreatureJump, //FuncID: 8
				_doRecv_NotifyCreatureState, //FuncID: 9
				_doRecv_NotifyCreatureStop, //FuncID: 10
				_doRecv_CreatureDisappear, //FuncID: 11
				_doRecv_NpcAppear, //FuncID: 12
				_doRecv_MonsterAppear, //FuncID: 13
				_doRecv_SwitcherAppear, //FuncID: 14
				_doRecv_SwitcherDisappear, //FuncID: 15
				_doRecv_NotifySwitcherState, //FuncID: 16
				_doRecv_GatherAppear, //FuncID: 17
				_doRecv_GatherDisappear, //FuncID: 18
				_doRecv_GatherChange, //FuncID: 19
				_doRecv_BlockerAppear, //FuncID: 20
				_doRecv_BlockerDisappear, //FuncID: 21
				_doRecv_MonsterChange, //FuncID: 22
				_doRecv_AreaAppear, //FuncID: 23
				_doRecv_AreaDisappear, //FuncID: 24
				_doRecv_MonsterTargetChange //FuncID: 25
			];

			_retFuncList = [
				_doReturn_GetPlayerAppear, //FuncID: 1
				_doReturn_JumpMap, //FuncID: 2
				_doReturn_GetMapOverLoad //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_GetPlayerAppear, //FuncID: 1
				_onTimeOut_JumpMap, //FuncID: 2
				_onTimeOut_GetMapOverLoad //FuncID: 3
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