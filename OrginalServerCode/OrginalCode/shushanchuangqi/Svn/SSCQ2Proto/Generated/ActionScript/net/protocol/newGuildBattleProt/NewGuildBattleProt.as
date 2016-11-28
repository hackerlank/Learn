/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    NewGuildBattleProt.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：新帮派战相关协议
	 */
	public class NewGuildBattleProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取帮派战状态
		 */
		public function send_GetState(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetState = new SOrigParam_GetState();
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
		 * 发送：获取历届占领帮会
		 * @param eMountainType (枚举类型：ENGBMountain)灵山类型
		 */
		public function send_GetOwnerHistory(eMountainType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetOwnerHistory = new SOrigParam_GetOwnerHistory();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eMountainType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：进入帮派战(进入准备场地)
		 * @param eMountainType (枚举类型：ENGBMountain)灵山类型
		 */
		public function send_Enter(eMountainType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_Enter = new SOrigParam_Enter();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eMountainType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：城门战攻击玩家/城门
		 * @param qwTargetRoleID (无符号64位整数)目标唯一ID(0为城墙)
		 */
		public function send_GateAttackPlayer(qwTargetRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_GateAttackPlayer = new SOrigParam_GateAttackPlayer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwTargetRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：购买傀儡
		 */
		public function send_BuyPuppet(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_BuyPuppet = new SOrigParam_BuyPuppet();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取城门战信息
		 */
		public function send_GetGateInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetGateInfo = new SOrigParam_GetGateInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：洞府战占领阵眼
		 * @param eCaveType (枚举类型：ENGBCaveCore)阵眼类型
		 */
		public function send_CaveCapture(eCaveType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_CaveCapture = new SOrigParam_CaveCapture();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eCaveType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：洞府战攻击他人
		 * @param qwTargetRoleID (无符号64位整数)目标唯一ID
		 */
		public function send_CaveAttack(qwTargetRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_CaveAttack = new SOrigParam_CaveAttack();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwTargetRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：洞府战从阵眼下阵
		 */
		public function send_CaveRest(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_CaveRest = new SOrigParam_CaveRest();
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
		 * 发送：获取洞府战信息
		 */
		public function send_GetCaveInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_GetCaveInfo = new SOrigParam_GetCaveInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：立即买活
		 */
		public function send_ClearDeadCD(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_ClearDeadCD = new SOrigParam_ClearDeadCD();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：帮派战退出
		 */
		public function send_Quit(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_Quit = new SOrigParam_Quit();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取战功榜帮派排名信息
		 * @param dwIndex (无符号32位整数)排名索引
		 * @param dwCount (无符号32位整数)排名个数
		 */
		public function send_GetGuildRankInfo(dwIndex:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_GetGuildRankInfo = new SOrigParam_GetGuildRankInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwIndex);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取战功榜帮派成员排名信息
		 * @param dwIndex (无符号32位整数)排名索引
		 * @param dwCount (无符号32位整数)排名个数
		 */
		public function send_GetGuildMemberRankInfo(dwIndex:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_GetGuildMemberRankInfo = new SOrigParam_GetGuildMemberRankInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwIndex);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取战功榜个人排名信息
		 * @param dwIndex (无符号32位整数)排名索引
		 * @param dwCount (无符号32位整数)排名个数
		 */
		public function send_GetPlayerRankInfo(dwIndex:uint, dwCount:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_GetPlayerRankInfo = new SOrigParam_GetPlayerRankInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwIndex);
			bytes_.writeUnsignedInt(dwCount);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：召集帮众广播
		 */
		public function send_CallMember(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_CallMember = new SOrigParam_CallMember();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：状态变更广播
		private function _doRecv_StateNotify(bytes:ByteArray):void
		{
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBState)当前帮派战状态
			var dwRemainTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)新帮派战剩余时间
			var vecInfo:Vector.<SMountainPanelInfo> = SMountainPanelInfo.vectorFromByteArray(bytes); //各个灵山信息
			var event_:REvt_StateNotify = new REvt_StateNotify(REvt_StateNotify.DATA_RECEIVE);
			event_.eState = eState;
			event_.dwRemainTime = dwRemainTime;
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：城门战广播
		private function _doRecv_GateInfoNotify(bytes:ByteArray):void
		{
			var sInfo:SMountainGateInfo = SMountainGateInfo.fromByteArray(bytes); //城门信息
			var event_:REvt_GateInfoNotify = new REvt_GateInfoNotify(REvt_GateInfoNotify.DATA_RECEIVE);
			event_.sInfo = sInfo;
			dispatchEvent(event_);
		}

		//接收处理：城门战列表通知
		private function _doRecv_GateListNotify(bytes:ByteArray):void
		{
			var vecInfo:Vector.<SPlayerPanelInfo> = SPlayerPanelInfo.vectorFromByteArray(bytes); //城门玩家列表信息通知
			var event_:REvt_GateListNotify = new REvt_GateListNotify(REvt_GateListNotify.DATA_RECEIVE);
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：城门被攻破广播
		private function _doRecv_GateBrokenNotify(bytes:ByteArray):void
		{
			var eMountainType:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBMountain)灵山类型
			var vecAttackGuildID:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes); //(无符号64位整数)（洞府战）攻击帮派ID
			var event_:REvt_GateBrokenNotify = new REvt_GateBrokenNotify(REvt_GateBrokenNotify.DATA_RECEIVE);
			event_.eMountainType = eMountainType;
			event_.vecAttackGuildID = vecAttackGuildID;
			dispatchEvent(event_);
		}

		//接收处理：洞府战广播
		private function _doRecv_CaveInfoNotify(bytes:ByteArray):void
		{
			var sInfo:SCaveInfo = SCaveInfo.fromByteArray(bytes); //洞府具体信息
			var event_:REvt_CaveInfoNotify = new REvt_CaveInfoNotify(REvt_CaveInfoNotify.DATA_RECEIVE);
			event_.sInfo = sInfo;
			dispatchEvent(event_);
		}

		//接收处理：洞府战列表通知
		private function _doRecv_CaveListNotify(bytes:ByteArray):void
		{
			var vecInfo:Vector.<SPlayerPanelInfo> = SPlayerPanelInfo.vectorFromByteArray(bytes); //洞府玩家列表信息通知
			var event_:REvt_CaveListNotify = new REvt_CaveListNotify(REvt_CaveListNotify.DATA_RECEIVE);
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：洞府战阵眼信息通知
		private function _doRecv_CaveCoreNotify(bytes:ByteArray):void
		{
			var vecCaveCoreInfo:Vector.<SCaveCoreInfo> = SCaveCoreInfo.vectorFromByteArray(bytes); //阵眼信息
			var event_:REvt_CaveCoreNotify = new REvt_CaveCoreNotify(REvt_CaveCoreNotify.DATA_RECEIVE);
			event_.vecCaveCoreInfo = vecCaveCoreInfo;
			dispatchEvent(event_);
		}

		//接收处理：洞府战被占领通知
		private function _doRecv_CaveCapture(bytes:ByteArray):void
		{
			var eMountainType:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBMountain)灵山类型
			var strGuildName:String = BytesUtil.readString(bytes); //当前占领帮派名称
			var event_:REvt_CaveCapture = new REvt_CaveCapture(REvt_CaveCapture.DATA_RECEIVE);
			event_.eMountainType = eMountainType;
			event_.strGuildName = strGuildName;
			dispatchEvent(event_);
		}

		//接收处理：战斗日志通知
		private function _doRecv_BattleLogNotify(bytes:ByteArray):void
		{
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)消息ID
			var vecStr:Vector.<String> = BytesUtil.readVecString(bytes); //聊天信息参数
			var event_:REvt_BattleLogNotify = new REvt_BattleLogNotify(REvt_BattleLogNotify.DATA_RECEIVE);
			event_.wMsgID = wMsgID;
			event_.vecStr = vecStr;
			dispatchEvent(event_);
		}

		//接收处理：战斗日志通知
		private function _doRecv_PuppetAttackNotify(bytes:ByteArray):void
		{
			var byIndex:uint = bytes.readUnsignedByte(); //(无符号8位整数)所属站位(0,1,2; 0为系统战争傀儡)
			var event_:REvt_PuppetAttackNotify = new REvt_PuppetAttackNotify(REvt_PuppetAttackNotify.DATA_RECEIVE);
			event_.byIndex = byIndex;
			dispatchEvent(event_);
		}

		//接收处理：战功榜帮派排名信息广播
		private function _doRecv_GuildRankInfoNotify(bytes:ByteArray):void
		{
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SGuildRankInfo> = SGuildRankInfo.vectorFromByteArray(bytes); //排名信息
			var event_:REvt_GuildRankInfoNotify = new REvt_GuildRankInfoNotify(REvt_GuildRankInfoNotify.DATA_RECEIVE);
			event_.dwMaxCount = dwMaxCount;
			event_.dwCurIndex = dwCurIndex;
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：战功榜帮派成员排名信息广播
		private function _doRecv_GuildMemberRankInfoNotify(bytes:ByteArray):void
		{
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SGuildMemberRankInfo> = SGuildMemberRankInfo.vectorFromByteArray(bytes); //排名信息
			var event_:REvt_GuildMemberRankInfoNotify = new REvt_GuildMemberRankInfoNotify(REvt_GuildMemberRankInfoNotify.DATA_RECEIVE);
			event_.dwMaxCount = dwMaxCount;
			event_.dwCurIndex = dwCurIndex;
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：战功榜个人排名信息广播
		private function _doRecv_PlayerRankInfoNotify(bytes:ByteArray):void
		{
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SPlayerRankInfo> = SPlayerRankInfo.vectorFromByteArray(bytes); //排名信息
			var event_:REvt_PlayerRankInfoNotify = new REvt_PlayerRankInfoNotify(REvt_PlayerRankInfoNotify.DATA_RECEIVE);
			event_.dwMaxCount = dwMaxCount;
			event_.dwCurIndex = dwCurIndex;
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：召集帮众广播
		private function _doRecv_CallMemberNotify(bytes:ByteArray):void
		{
			var byQuality:uint = bytes.readUnsignedByte(); //(无符号8位整数)品质
			var strName:String = BytesUtil.readString(bytes); //名字
			var event_:REvt_CallMemberNotify = new REvt_CallMemberNotify(REvt_CallMemberNotify.DATA_RECEIVE);
			event_.byQuality = byQuality;
			event_.strName = strName;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：获取帮派战状态
		private function _doReturn_GetState(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetState = new SRetParam_GetState();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBState)当前帮派战状态
			var dwRemainTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)新帮派战剩余时间
			var vecInfo:Vector.<SMountainPanelInfo> = SMountainPanelInfo.vectorFromByteArray(bytes); //各个灵山信息
			var eMountainType:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBMountain)自己所在战斗信息
			retParam_.eState = eState;
			retParam_.dwRemainTime = dwRemainTime;
			retParam_.vecInfo = vecInfo;
			retParam_.eMountainType = eMountainType;
			var origParam_:SOrigParam_GetState = _sessionMgr.getData(sessionID_) as SOrigParam_GetState;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetState = new TEvt_GetState(TEvt_GetState.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取帮派战状态
		private function _onTimeOut_GetState(sessionID:uint):void
		{
			var retParam:SRetParam_GetState = new SRetParam_GetState();
			var event_:TEvt_GetState = new TEvt_GetState(TEvt_GetState.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取历届占领帮会
		private function _doReturn_GetOwnerHistory(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetOwnerHistory = new SRetParam_GetOwnerHistory();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecInfo:Vector.<SOwnerHistoryInfo> = SOwnerHistoryInfo.vectorFromByteArray(bytes); //理解帮派信息
			retParam_.vecInfo = vecInfo;
			var origParam_:SOrigParam_GetOwnerHistory = _sessionMgr.getData(sessionID_) as SOrigParam_GetOwnerHistory;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetOwnerHistory = new TEvt_GetOwnerHistory(TEvt_GetOwnerHistory.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取历届占领帮会
		private function _onTimeOut_GetOwnerHistory(sessionID:uint):void
		{
			var retParam:SRetParam_GetOwnerHistory = new SRetParam_GetOwnerHistory();
			var event_:TEvt_GetOwnerHistory = new TEvt_GetOwnerHistory(TEvt_GetOwnerHistory.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：进入帮派战(进入准备场地)
		private function _doReturn_Enter(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Enter = new SRetParam_Enter();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBEnterResult)进入结果
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBMountainState)灵山状态
			retParam_.eResult = eResult;
			retParam_.eState = eState;
			var origParam_:SOrigParam_Enter = _sessionMgr.getData(sessionID_) as SOrigParam_Enter;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Enter = new TEvt_Enter(TEvt_Enter.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：进入帮派战(进入准备场地)
		private function _onTimeOut_Enter(sessionID:uint):void
		{
			var retParam:SRetParam_Enter = new SRetParam_Enter();
			var event_:TEvt_Enter = new TEvt_Enter(TEvt_Enter.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：城门战攻击玩家/城门
		private function _doReturn_GateAttackPlayer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GateAttackPlayer = new SRetParam_GateAttackPlayer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBGateAttackResult)攻击返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GateAttackPlayer = _sessionMgr.getData(sessionID_) as SOrigParam_GateAttackPlayer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GateAttackPlayer = new TEvt_GateAttackPlayer(TEvt_GateAttackPlayer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：城门战攻击玩家/城门
		private function _onTimeOut_GateAttackPlayer(sessionID:uint):void
		{
			var retParam:SRetParam_GateAttackPlayer = new SRetParam_GateAttackPlayer();
			var event_:TEvt_GateAttackPlayer = new TEvt_GateAttackPlayer(TEvt_GateAttackPlayer.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：购买傀儡
		private function _doReturn_BuyPuppet(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuyPuppet = new SRetParam_BuyPuppet();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBBuyPuppetResult)购买结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuyPuppet = _sessionMgr.getData(sessionID_) as SOrigParam_BuyPuppet;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuyPuppet = new TEvt_BuyPuppet(TEvt_BuyPuppet.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：购买傀儡
		private function _onTimeOut_BuyPuppet(sessionID:uint):void
		{
			var retParam:SRetParam_BuyPuppet = new SRetParam_BuyPuppet();
			var event_:TEvt_BuyPuppet = new TEvt_BuyPuppet(TEvt_BuyPuppet.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取城门战信息
		private function _doReturn_GetGateInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGateInfo = new SRetParam_GetGateInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)返回结果
			var sInfo:SMountainGateInfo = SMountainGateInfo.fromByteArray(bytes); //城门信息
			retParam_.eResult = eResult;
			retParam_.sInfo = sInfo;
			var origParam_:SOrigParam_GetGateInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGateInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGateInfo = new TEvt_GetGateInfo(TEvt_GetGateInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取城门战信息
		private function _onTimeOut_GetGateInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGateInfo = new SRetParam_GetGateInfo();
			var event_:TEvt_GetGateInfo = new TEvt_GetGateInfo(TEvt_GetGateInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：洞府战占领阵眼
		private function _doReturn_CaveCapture(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CaveCapture = new SRetParam_CaveCapture();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBCaveAttackResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CaveCapture = _sessionMgr.getData(sessionID_) as SOrigParam_CaveCapture;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CaveCapture = new TEvt_CaveCapture(TEvt_CaveCapture.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：洞府战占领阵眼
		private function _onTimeOut_CaveCapture(sessionID:uint):void
		{
			var retParam:SRetParam_CaveCapture = new SRetParam_CaveCapture();
			var event_:TEvt_CaveCapture = new TEvt_CaveCapture(TEvt_CaveCapture.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：洞府战攻击他人
		private function _doReturn_CaveAttack(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CaveAttack = new SRetParam_CaveAttack();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBCaveAttackResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CaveAttack = _sessionMgr.getData(sessionID_) as SOrigParam_CaveAttack;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CaveAttack = new TEvt_CaveAttack(TEvt_CaveAttack.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：洞府战攻击他人
		private function _onTimeOut_CaveAttack(sessionID:uint):void
		{
			var retParam:SRetParam_CaveAttack = new SRetParam_CaveAttack();
			var event_:TEvt_CaveAttack = new TEvt_CaveAttack(TEvt_CaveAttack.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：洞府战从阵眼下阵
		private function _doReturn_CaveRest(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CaveRest = new SRetParam_CaveRest();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBCaveAttackResult)返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CaveRest = _sessionMgr.getData(sessionID_) as SOrigParam_CaveRest;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CaveRest = new TEvt_CaveRest(TEvt_CaveRest.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：洞府战从阵眼下阵
		private function _onTimeOut_CaveRest(sessionID:uint):void
		{
			var retParam:SRetParam_CaveRest = new SRetParam_CaveRest();
			var event_:TEvt_CaveRest = new TEvt_CaveRest(TEvt_CaveRest.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取洞府战信息
		private function _doReturn_GetCaveInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetCaveInfo = new SRetParam_GetCaveInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)返回结果
			var sInfo:SCaveInfo = SCaveInfo.fromByteArray(bytes); //洞府信息
			retParam_.eResult = eResult;
			retParam_.sInfo = sInfo;
			var origParam_:SOrigParam_GetCaveInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetCaveInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetCaveInfo = new TEvt_GetCaveInfo(TEvt_GetCaveInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取洞府战信息
		private function _onTimeOut_GetCaveInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetCaveInfo = new SRetParam_GetCaveInfo();
			var event_:TEvt_GetCaveInfo = new TEvt_GetCaveInfo(TEvt_GetCaveInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：立即买活
		private function _doReturn_ClearDeadCD(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ClearDeadCD = new SRetParam_ClearDeadCD();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBClearDeadCDResult)返回类型
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ClearDeadCD = _sessionMgr.getData(sessionID_) as SOrigParam_ClearDeadCD;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ClearDeadCD = new TEvt_ClearDeadCD(TEvt_ClearDeadCD.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：立即买活
		private function _onTimeOut_ClearDeadCD(sessionID:uint):void
		{
			var retParam:SRetParam_ClearDeadCD = new SRetParam_ClearDeadCD();
			var event_:TEvt_ClearDeadCD = new TEvt_ClearDeadCD(TEvt_ClearDeadCD.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派战退出
		private function _doReturn_Quit(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Quit = new SRetParam_Quit();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBQuitResult)退出返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_Quit = _sessionMgr.getData(sessionID_) as SOrigParam_Quit;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Quit = new TEvt_Quit(TEvt_Quit.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派战退出
		private function _onTimeOut_Quit(sessionID:uint):void
		{
			var retParam:SRetParam_Quit = new SRetParam_Quit();
			var event_:TEvt_Quit = new TEvt_Quit(TEvt_Quit.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取战功榜帮派排名信息
		private function _doReturn_GetGuildRankInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildRankInfo = new SRetParam_GetGuildRankInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)返回结果
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SGuildRankInfo> = SGuildRankInfo.vectorFromByteArray(bytes); //排名信息
			retParam_.eResult = eResult;
			retParam_.dwMaxCount = dwMaxCount;
			retParam_.dwCurIndex = dwCurIndex;
			retParam_.vecInfo = vecInfo;
			var origParam_:SOrigParam_GetGuildRankInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildRankInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildRankInfo = new TEvt_GetGuildRankInfo(TEvt_GetGuildRankInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取战功榜帮派排名信息
		private function _onTimeOut_GetGuildRankInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildRankInfo = new SRetParam_GetGuildRankInfo();
			var event_:TEvt_GetGuildRankInfo = new TEvt_GetGuildRankInfo(TEvt_GetGuildRankInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取战功榜帮派成员排名信息
		private function _doReturn_GetGuildMemberRankInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetGuildMemberRankInfo = new SRetParam_GetGuildMemberRankInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)返回结果
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SGuildMemberRankInfo> = SGuildMemberRankInfo.vectorFromByteArray(bytes); //排名信息
			retParam_.eResult = eResult;
			retParam_.dwMaxCount = dwMaxCount;
			retParam_.dwCurIndex = dwCurIndex;
			retParam_.vecInfo = vecInfo;
			var origParam_:SOrigParam_GetGuildMemberRankInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetGuildMemberRankInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetGuildMemberRankInfo = new TEvt_GetGuildMemberRankInfo(TEvt_GetGuildMemberRankInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取战功榜帮派成员排名信息
		private function _onTimeOut_GetGuildMemberRankInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetGuildMemberRankInfo = new SRetParam_GetGuildMemberRankInfo();
			var event_:TEvt_GetGuildMemberRankInfo = new TEvt_GetGuildMemberRankInfo(TEvt_GetGuildMemberRankInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取战功榜个人排名信息
		private function _doReturn_GetPlayerRankInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPlayerRankInfo = new SRetParam_GetPlayerRankInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)返回结果
			var dwMaxCount:uint = bytes.readUnsignedInt(); //(无符号32位整数)最大排名数量
			var dwCurIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前排名索引
			var vecInfo:Vector.<SPlayerRankInfo> = SPlayerRankInfo.vectorFromByteArray(bytes); //排名信息
			retParam_.eResult = eResult;
			retParam_.dwMaxCount = dwMaxCount;
			retParam_.dwCurIndex = dwCurIndex;
			retParam_.vecInfo = vecInfo;
			var origParam_:SOrigParam_GetPlayerRankInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPlayerRankInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPlayerRankInfo = new TEvt_GetPlayerRankInfo(TEvt_GetPlayerRankInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取战功榜个人排名信息
		private function _onTimeOut_GetPlayerRankInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPlayerRankInfo = new SRetParam_GetPlayerRankInfo();
			var event_:TEvt_GetPlayerRankInfo = new TEvt_GetPlayerRankInfo(TEvt_GetPlayerRankInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：召集帮众广播
		private function _doReturn_CallMember(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CallMember = new SRetParam_CallMember();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ENGBResult)召集结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CallMember = _sessionMgr.getData(sessionID_) as SOrigParam_CallMember;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CallMember = new TEvt_CallMember(TEvt_CallMember.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：召集帮众广播
		private function _onTimeOut_CallMember(sessionID:uint):void
		{
			var retParam:SRetParam_CallMember = new SRetParam_CallMember();
			var event_:TEvt_CallMember = new TEvt_CallMember(TEvt_CallMember.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:NewGuildBattleProt;

		public static function get instance():NewGuildBattleProt
		{
			if(_instance == null)
				_instance = new NewGuildBattleProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function NewGuildBattleProt()
		{
			_protID = 68;
			_recvFuncList = [
				_doRecv_StateNotify, //FuncID: 1
				_doRecv_GateInfoNotify, //FuncID: 2
				_doRecv_GateListNotify, //FuncID: 3
				_doRecv_GateBrokenNotify, //FuncID: 4
				_doRecv_CaveInfoNotify, //FuncID: 5
				_doRecv_CaveListNotify, //FuncID: 6
				_doRecv_CaveCoreNotify, //FuncID: 7
				_doRecv_CaveCapture, //FuncID: 8
				_doRecv_BattleLogNotify, //FuncID: 9
				_doRecv_PuppetAttackNotify, //FuncID: 10
				_doRecv_GuildRankInfoNotify, //FuncID: 11
				_doRecv_GuildMemberRankInfoNotify, //FuncID: 12
				_doRecv_PlayerRankInfoNotify, //FuncID: 13
				_doRecv_CallMemberNotify //FuncID: 14
			];

			_retFuncList = [
				_doReturn_GetState, //FuncID: 1
				_doReturn_GetOwnerHistory, //FuncID: 2
				_doReturn_Enter, //FuncID: 3
				_doReturn_GateAttackPlayer, //FuncID: 4
				_doReturn_BuyPuppet, //FuncID: 5
				_doReturn_GetGateInfo, //FuncID: 6
				_doReturn_CaveCapture, //FuncID: 7
				_doReturn_CaveAttack, //FuncID: 8
				_doReturn_CaveRest, //FuncID: 9
				_doReturn_GetCaveInfo, //FuncID: 10
				_doReturn_ClearDeadCD, //FuncID: 11
				_doReturn_Quit, //FuncID: 12
				_doReturn_GetGuildRankInfo, //FuncID: 13
				_doReturn_GetGuildMemberRankInfo, //FuncID: 14
				_doReturn_GetPlayerRankInfo, //FuncID: 15
				_doReturn_CallMember //FuncID: 16
			];

			_timeFuncList = [
				_onTimeOut_GetState, //FuncID: 1
				_onTimeOut_GetOwnerHistory, //FuncID: 2
				_onTimeOut_Enter, //FuncID: 3
				_onTimeOut_GateAttackPlayer, //FuncID: 4
				_onTimeOut_BuyPuppet, //FuncID: 5
				_onTimeOut_GetGateInfo, //FuncID: 6
				_onTimeOut_CaveCapture, //FuncID: 7
				_onTimeOut_CaveAttack, //FuncID: 8
				_onTimeOut_CaveRest, //FuncID: 9
				_onTimeOut_GetCaveInfo, //FuncID: 10
				_onTimeOut_ClearDeadCD, //FuncID: 11
				_onTimeOut_Quit, //FuncID: 12
				_onTimeOut_GetGuildRankInfo, //FuncID: 13
				_onTimeOut_GetGuildMemberRankInfo, //FuncID: 14
				_onTimeOut_GetPlayerRankInfo, //FuncID: 15
				_onTimeOut_CallMember //FuncID: 16
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