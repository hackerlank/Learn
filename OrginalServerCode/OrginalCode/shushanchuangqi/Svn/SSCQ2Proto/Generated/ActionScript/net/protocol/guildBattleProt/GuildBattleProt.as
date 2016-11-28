/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GuildBattleProt.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.mapProt.SPlayerAppear;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：帮派相关协议
	 */
	public class GuildBattleProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：帮派战报名
		 * @param eSpotType (枚举类型：EGBSpot)据点类型
		 */
		public function send_SignUp(eSpotType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_SignUp = new SOrigParam_SignUp();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eSpotType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：进入帮派战(进入准备场地)
		 */
		public function send_Enter(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_Enter = new SOrigParam_Enter();
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
		 * 发送：帮派战退出
		 */
		public function send_Quit(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_Quit = new SOrigParam_Quit();
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
		 * 发送：帮派成员调整
		 * @param qwRoleID (无符号64位整数)成员角色ID
		 * @param eSpotType (枚举类型：EGBSpot)目标据点类型
		 * @param byIndex (无符号8位整数)新目标对应位置(从1开始)
		 */
		public function send_AdjustMember(qwRoleID:BigInteger, eSpotType:uint, byIndex:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_AdjustMember = new SOrigParam_AdjustMember();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			bytes_.writeByte(eSpotType);
			bytes_.writeByte(byIndex);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取帮派战状态
		 */
		public function send_GetState(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_GetState = new SOrigParam_GetState();
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
		 * 发送：帮派战场信息
		 */
		public function send_GetFieldInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetFieldInfo = new SOrigParam_GetFieldInfo();
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
		 * 发送：帮派据点信息
		 * @param eType (枚举类型：EGBSpot)据点类型
		 */
		public function send_GetSpotInfo(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_GetSpotInfo = new SOrigParam_GetSpotInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：据点战报获取
		 * @param eType (枚举类型：EGBSpot)据点类型
		 */
		public function send_GetSpotBattle(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetSpotBattle = new SOrigParam_GetSpotBattle();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(eType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：帮派战技能信息获取
		 */
		public function send_GetSkillInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_GetSkillInfo = new SOrigParam_GetSkillInfo();
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
		 * 发送：帮派购买技能结果
		 * @param eType (枚举类型：EGBSkill)购买的技能类型
		 */
		public function send_BuySkill(eType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_BuySkill = new SOrigParam_BuySkill();
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

		/**
		 * 发送：获取帮派战小面板信息
		 */
		public function send_GetPanelInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_GetPanelInfo = new SOrigParam_GetPanelInfo();
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
		 * 发送：召集帮众广播
		 */
		public function send_CallMember(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_CallMember = new SOrigParam_CallMember();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：帮派战状态通知
		private function _doRecv_StateNotify(bytes:ByteArray):void
		{
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：EGBState)当前帮派战状态
			var byBattleCount:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前已经战斗的数量
			var dwRemainTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态剩余时间
			var eSpotType:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSpot)自己所在据点(报名的据点或者目前被调整到的据点)
			var eSelfSide:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSide)自己所在帮派方向
			var event_:REvt_StateNotify = new REvt_StateNotify(REvt_StateNotify.DATA_RECEIVE);
			event_.eState = eState;
			event_.byBattleCount = byBattleCount;
			event_.dwRemainTime = dwRemainTime;
			event_.eSpotType = eSpotType;
			event_.eSelfSide = eSelfSide;
			dispatchEvent(event_);
		}

		//接收处理：帮派战信息通知
		private function _doRecv_FieldInfoNotify(bytes:ByteArray):void
		{
			var sFieldInfo:SFieldInfo = SFieldInfo.fromByteArray(bytes); //战场信息
			var event_:REvt_FieldInfoNotify = new REvt_FieldInfoNotify(REvt_FieldInfoNotify.DATA_RECEIVE);
			event_.sFieldInfo = sFieldInfo;
			dispatchEvent(event_);
		}

		//接收处理：帮派战据点信息通知
		private function _doRecv_SpotInfoNotify(bytes:ByteArray):void
		{
			var vecSpotInfo:Vector.<SSpotInfo> = SSpotInfo.superVectorFromByteArray(bytes); //据点详细信息
			var event_:REvt_SpotInfoNotify = new REvt_SpotInfoNotify(REvt_SpotInfoNotify.DATA_RECEIVE);
			event_.vecSpotInfo = vecSpotInfo;
			dispatchEvent(event_);
		}

		//接收处理：据点战斗通知
		private function _doRecv_SpotBattleNotify(bytes:ByteArray):void
		{
			var eType:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSpot)据点类型
			var vecBattleData:Vector.<SBattleData> = SBattleData.vectorFromByteArray(bytes); //战报信息
			var event_:REvt_SpotBattleNotify = new REvt_SpotBattleNotify(REvt_SpotBattleNotify.DATA_RECEIVE);
			event_.eType = eType;
			event_.vecBattleData = vecBattleData;
			dispatchEvent(event_);
		}

		//接收处理：帮派战技能信息通知
		private function _doRecv_SkillInfoNotify(bytes:ByteArray):void
		{
			var vecSkillInfo:Vector.<SSkillInfo> = SSkillInfo.vectorFromByteArray(bytes); //具体已购买技能
			var event_:REvt_SkillInfoNotify = new REvt_SkillInfoNotify(REvt_SkillInfoNotify.DATA_RECEIVE);
			event_.vecSkillInfo = vecSkillInfo;
			dispatchEvent(event_);
		}

		//接收处理：更新帮派战小面板信息
		private function _doRecv_PanelInfoNotify(bytes:ByteArray):void
		{
			var dwSelfScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)我的积分
			var dwGuildScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派积分
			var dwGuildRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派排名
			var event_:REvt_PanelInfoNotify = new REvt_PanelInfoNotify(REvt_PanelInfoNotify.DATA_RECEIVE);
			event_.dwSelfScore = dwSelfScore;
			event_.dwGuildScore = dwGuildScore;
			event_.dwGuildRank = dwGuildRank;
			dispatchEvent(event_);
		}

		//接收处理：报名还没进入的通知进入
		private function _doRecv_SignupEnterNotify(bytes:ByteArray):void
		{
			var event_:REvt_SignupEnterNotify = new REvt_SignupEnterNotify(REvt_SignupEnterNotify.DATA_RECEIVE);
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
		//返回处理：帮派战报名
		private function _doReturn_SignUp(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SignUp = new SRetParam_SignUp();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSignUpResult)报名返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SignUp = _sessionMgr.getData(sessionID_) as SOrigParam_SignUp;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SignUp = new TEvt_SignUp(TEvt_SignUp.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派战报名
		private function _onTimeOut_SignUp(sessionID:uint):void
		{
			var retParam:SRetParam_SignUp = new SRetParam_SignUp();
			var event_:TEvt_SignUp = new TEvt_SignUp(TEvt_SignUp.DATA_RETURN);
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
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBEnterResult)报名返回结果
			retParam_.eResult = eResult;
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

		//返回处理：帮派战退出
		private function _doReturn_Quit(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Quit = new SRetParam_Quit();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBQuitResult)退出返回结果
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

		//返回处理：帮派成员调整
		private function _doReturn_AdjustMember(bytes:ByteArray):void
		{
			var retParam_:SRetParam_AdjustMember = new SRetParam_AdjustMember();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBAdjustResult)调整返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_AdjustMember = _sessionMgr.getData(sessionID_) as SOrigParam_AdjustMember;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_AdjustMember = new TEvt_AdjustMember(TEvt_AdjustMember.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派成员调整
		private function _onTimeOut_AdjustMember(sessionID:uint):void
		{
			var retParam:SRetParam_AdjustMember = new SRetParam_AdjustMember();
			var event_:TEvt_AdjustMember = new TEvt_AdjustMember(TEvt_AdjustMember.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取帮派战状态
		private function _doReturn_GetState(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetState = new SRetParam_GetState();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eState:uint = bytes.readUnsignedByte(); //(枚举类型：EGBState)当前帮派战状态
			var byBattleCount:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前已经战斗的数量
			var dwRemainTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前状态剩余时间
			var eSpotType:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSpot)自己所在据点(不为None也可能在准备地图中)
			var bGuildJoined:Boolean = bytes.readBoolean(); //自己所在帮派是否已经参加
			var eSelfSide:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSide)自己所在帮派方向
			retParam_.eState = eState;
			retParam_.byBattleCount = byBattleCount;
			retParam_.dwRemainTime = dwRemainTime;
			retParam_.eSpotType = eSpotType;
			retParam_.bGuildJoined = bGuildJoined;
			retParam_.eSelfSide = eSelfSide;
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

		//返回处理：帮派战场信息
		private function _doReturn_GetFieldInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetFieldInfo = new SRetParam_GetFieldInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBResult)返回结果
			var vecFieldInfo:Vector.<SFieldInfo> = SFieldInfo.vectorFromByteArray(bytes); //帮派战场信息
			retParam_.eResult = eResult;
			retParam_.vecFieldInfo = vecFieldInfo;
			var origParam_:SOrigParam_GetFieldInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetFieldInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetFieldInfo = new TEvt_GetFieldInfo(TEvt_GetFieldInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派战场信息
		private function _onTimeOut_GetFieldInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetFieldInfo = new SRetParam_GetFieldInfo();
			var event_:TEvt_GetFieldInfo = new TEvt_GetFieldInfo(TEvt_GetFieldInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派据点信息
		private function _doReturn_GetSpotInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSpotInfo = new SRetParam_GetSpotInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBResult)返回结果
			var vecSpotInfo:Vector.<SSpotInfo> = SSpotInfo.superVectorFromByteArray(bytes); //据点详细信息（数量为0/1）
			retParam_.eResult = eResult;
			retParam_.vecSpotInfo = vecSpotInfo;
			var origParam_:SOrigParam_GetSpotInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetSpotInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSpotInfo = new TEvt_GetSpotInfo(TEvt_GetSpotInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派据点信息
		private function _onTimeOut_GetSpotInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetSpotInfo = new SRetParam_GetSpotInfo();
			var event_:TEvt_GetSpotInfo = new TEvt_GetSpotInfo(TEvt_GetSpotInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：据点战报获取
		private function _doReturn_GetSpotBattle(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSpotBattle = new SRetParam_GetSpotBattle();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBBattleResult)战报获取结果
			var vecBattleData:Vector.<SBattleData> = SBattleData.vectorFromByteArray(bytes); //战报信息
			retParam_.eResult = eResult;
			retParam_.vecBattleData = vecBattleData;
			var origParam_:SOrigParam_GetSpotBattle = _sessionMgr.getData(sessionID_) as SOrigParam_GetSpotBattle;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSpotBattle = new TEvt_GetSpotBattle(TEvt_GetSpotBattle.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：据点战报获取
		private function _onTimeOut_GetSpotBattle(sessionID:uint):void
		{
			var retParam:SRetParam_GetSpotBattle = new SRetParam_GetSpotBattle();
			var event_:TEvt_GetSpotBattle = new TEvt_GetSpotBattle(TEvt_GetSpotBattle.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派战技能信息获取
		private function _doReturn_GetSkillInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetSkillInfo = new SRetParam_GetSkillInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSkillResult)购买结果
			var vecSkillInfo:Vector.<SSkillInfo> = SSkillInfo.vectorFromByteArray(bytes); //具体已购买技能
			retParam_.eResult = eResult;
			retParam_.vecSkillInfo = vecSkillInfo;
			var origParam_:SOrigParam_GetSkillInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetSkillInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetSkillInfo = new TEvt_GetSkillInfo(TEvt_GetSkillInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派战技能信息获取
		private function _onTimeOut_GetSkillInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetSkillInfo = new SRetParam_GetSkillInfo();
			var event_:TEvt_GetSkillInfo = new TEvt_GetSkillInfo(TEvt_GetSkillInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：帮派购买技能结果
		private function _doReturn_BuySkill(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BuySkill = new SRetParam_BuySkill();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBSkillResult)购买结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BuySkill = _sessionMgr.getData(sessionID_) as SOrigParam_BuySkill;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BuySkill = new TEvt_BuySkill(TEvt_BuySkill.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：帮派购买技能结果
		private function _onTimeOut_BuySkill(sessionID:uint):void
		{
			var retParam:SRetParam_BuySkill = new SRetParam_BuySkill();
			var event_:TEvt_BuySkill = new TEvt_BuySkill(TEvt_BuySkill.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取帮派战小面板信息
		private function _doReturn_GetPanelInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPanelInfo = new SRetParam_GetPanelInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwSelfScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)我的积分
			var dwGuildScore:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派积分
			var dwGuildRank:uint = bytes.readUnsignedInt(); //(无符号32位整数)帮派排名
			retParam_.dwSelfScore = dwSelfScore;
			retParam_.dwGuildScore = dwGuildScore;
			retParam_.dwGuildRank = dwGuildRank;
			var origParam_:SOrigParam_GetPanelInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPanelInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPanelInfo = new TEvt_GetPanelInfo(TEvt_GetPanelInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取帮派战小面板信息
		private function _onTimeOut_GetPanelInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPanelInfo = new SRetParam_GetPanelInfo();
			var event_:TEvt_GetPanelInfo = new TEvt_GetPanelInfo(TEvt_GetPanelInfo.DATA_RETURN);
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
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EGBResult)召集结果
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
		private static var _instance:GuildBattleProt;

		public static function get instance():GuildBattleProt
		{
			if(_instance == null)
				_instance = new GuildBattleProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GuildBattleProt()
		{
			_protID = 76;
			_recvFuncList = [
				_doRecv_StateNotify, //FuncID: 1
				_doRecv_FieldInfoNotify, //FuncID: 2
				_doRecv_SpotInfoNotify, //FuncID: 3
				_doRecv_SpotBattleNotify, //FuncID: 4
				_doRecv_SkillInfoNotify, //FuncID: 5
				_doRecv_PanelInfoNotify, //FuncID: 6
				_doRecv_SignupEnterNotify, //FuncID: 7
				_doRecv_CallMemberNotify //FuncID: 8
			];

			_retFuncList = [
				_doReturn_SignUp, //FuncID: 1
				_doReturn_Enter, //FuncID: 2
				_doReturn_Quit, //FuncID: 3
				_doReturn_AdjustMember, //FuncID: 4
				_doReturn_GetState, //FuncID: 5
				_doReturn_GetFieldInfo, //FuncID: 6
				_doReturn_GetSpotInfo, //FuncID: 7
				_doReturn_GetSpotBattle, //FuncID: 8
				_doReturn_GetSkillInfo, //FuncID: 9
				_doReturn_BuySkill, //FuncID: 10
				_doReturn_GetPanelInfo, //FuncID: 11
				_doReturn_CallMember //FuncID: 12
			];

			_timeFuncList = [
				_onTimeOut_SignUp, //FuncID: 1
				_onTimeOut_Enter, //FuncID: 2
				_onTimeOut_Quit, //FuncID: 3
				_onTimeOut_AdjustMember, //FuncID: 4
				_onTimeOut_GetState, //FuncID: 5
				_onTimeOut_GetFieldInfo, //FuncID: 6
				_onTimeOut_GetSpotInfo, //FuncID: 7
				_onTimeOut_GetSpotBattle, //FuncID: 8
				_onTimeOut_GetSkillInfo, //FuncID: 9
				_onTimeOut_BuySkill, //FuncID: 10
				_onTimeOut_GetPanelInfo, //FuncID: 11
				_onTimeOut_CallMember //FuncID: 12
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