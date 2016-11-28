/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    TeamGS.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.battleGS.SFeatureBase;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：竞技场协议
	 */
	public class TeamGS extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：根据模板查询可加入房间
		 * @param DgnType (无符号16位整数)房间ID
		 */
		public function send_GetTeamList(DgnType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_GetTeamList = new SOrigParam_GetTeamList();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(DgnType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：停止查询
		 */
		public function send_StopTeamList():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求创建房间
		 * @param DgnType (无符号16位整数)副本类型
		 * @param stSetting 队伍设置
		 */
		public function send_CreateTeam(DgnType:uint, stSetting:TeamSetting, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_CreateTeam = new SOrigParam_CreateTeam();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(DgnType);
			stSetting.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求加入房间
		 * @param dwTeamID (无符号32位整数)房间ID
		 * @param dwPassWord (无符号32位整数)队伍密码
		 */
		public function send_EnterTeam(dwTeamID:uint, dwPassWord:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_EnterTeam = new SOrigParam_EnterTeam();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwTeamID);
			bytes_.writeUnsignedInt(dwPassWord);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求更换将
		 * @param qwNewFighter (无符号64位整数)新将
		 * @param byPos (无符号8位整数)将位置
		 */
		public function send_ResetFigter(qwNewFighter:BigInteger, byPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ResetFigter = new SOrigParam_ResetFigter();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwNewFighter);
			bytes_.writeByte(byPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：交换自己的将位置
		 * @param byPos1 (无符号8位整数)第1个位置
		 * @param byPos2 (无符号8位整数)第2个位置
		 */
		public function send_ChangeSelfPos(byPos1:uint, byPos2:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_ChangeSelfPos = new SOrigParam_ChangeSelfPos();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byPos1);
			bytes_.writeByte(byPos2);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：交换列的位置
		 * @param byPos1 (无符号8位整数)第1个位置
		 * @param byPos2 (无符号8位整数)第2个位置
		 */
		public function send_ChangeArrayPos(byPos1:uint, byPos2:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_ChangeArrayPos = new SOrigParam_ChangeArrayPos();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeByte(byPos1);
			bytes_.writeByte(byPos2);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求离开房间
		 */
		public function send_LeaveTeam(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_LeaveTeam = new SOrigParam_LeaveTeam();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：玩家已经准备好
		 */
		public function send_DoReady(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_DoReady = new SOrigParam_DoReady();
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
		 * 发送：玩家取消准备好
		 */
		public function send_CancelDoReady(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_CancelDoReady = new SOrigParam_CancelDoReady();
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
		 * 发送：请求进入副本
		 */
		public function send_EnterDgn(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_EnterDgn = new SOrigParam_EnterDgn();
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
		 * 发送：请求踢玩家出队伍
		 * @param qwRoleID (无符号64位整数)踢的人
		 */
		public function send_KickOffPlayer(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_KickOffPlayer = new SOrigParam_KickOffPlayer();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 12;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取队伍信息
		 */
		public function send_GetTeamInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 12);
			var origParam_:SOrigParam_GetTeamInfo = new SOrigParam_GetTeamInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 13;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：换副本请求
		 * @param NewDgnType (无符号16位整数)新副本类型
		 */
		public function send_ChangDgnType(NewDgnType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 13);
			var origParam_:SOrigParam_ChangDgnType = new SOrigParam_ChangDgnType();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 14;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(NewDgnType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：换阵灵请求
		 * @param qwRoleID (无符号64位整数)阵灵的主人
		 */
		public function send_ChangPet(qwRoleID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 14);
			var origParam_:SOrigParam_ChangPet = new SOrigParam_ChangPet();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 15;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：更改设置请求
		 * @param stSetting 队伍设置
		 */
		public function send_ChangSetting(stSetting:TeamSetting, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 15);
			var origParam_:SOrigParam_ChangSetting = new SOrigParam_ChangSetting();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 16;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			stSetting.toByteArray(bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：换队长
		 * @param qwNewLeader (无符号64位整数)新队长ID
		 */
		public function send_ChangLeader(qwNewLeader:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 16);
			var origParam_:SOrigParam_ChangLeader = new SOrigParam_ChangLeader();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 17;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwNewLeader);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：房间信息更新
		private function _doRecv_TeamInfoUpdate(bytes:ByteArray):void
		{
			var stInfo:TeamInfo = TeamInfo.fromByteArray(bytes); //房间信息
			var event_:REvt_TeamInfoUpdate = new REvt_TeamInfoUpdate(REvt_TeamInfoUpdate.DATA_RECEIVE);
			event_.stInfo = stInfo;
			dispatchEvent(event_);
		}

		//接收处理：通告自己被踢
		private function _doRecv_NoticeKicked(bytes:ByteArray):void
		{
			var DgnType:uint = bytes.readUnsignedShort(); //(无符号16位整数)副本类型
			var event_:REvt_NoticeKicked = new REvt_NoticeKicked(REvt_NoticeKicked.DATA_RECEIVE);
			event_.DgnType = DgnType;
			dispatchEvent(event_);
		}

		//接收处理：房间列表更新
		private function _doRecv_UpdateTeamInfoList(bytes:ByteArray):void
		{
			var eOpType:uint = bytes.readUnsignedByte(); //(枚举类型：TeamListOP)操作类型
			var vecInfo:Vector.<TeamInfoForList> = TeamInfoForList.vectorFromByteArray(bytes); //修改的数据
			var event_:REvt_UpdateTeamInfoList = new REvt_UpdateTeamInfoList(REvt_UpdateTeamInfoList.DATA_RECEIVE);
			event_.eOpType = eOpType;
			event_.vecInfo = vecInfo;
			dispatchEvent(event_);
		}

		//接收处理：队伍解散
		private function _doRecv_TeamDelForList(bytes:ByteArray):void
		{
			var dwTeamID:uint = bytes.readUnsignedInt(); //(无符号32位整数)队伍ID
			var event_:REvt_TeamDelForList = new REvt_TeamDelForList(REvt_TeamDelForList.DATA_RECEIVE);
			event_.dwTeamID = dwTeamID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：根据模板查询可加入房间
		private function _doReturn_GetTeamList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTeamList = new SRetParam_GetTeamList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecReturn:Vector.<TeamInfoForList> = TeamInfoForList.vectorFromByteArray(bytes); //返回的房间列表
			retParam_.vecReturn = vecReturn;
			var origParam_:SOrigParam_GetTeamList = _sessionMgr.getData(sessionID_) as SOrigParam_GetTeamList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTeamList = new TEvt_GetTeamList(TEvt_GetTeamList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：根据模板查询可加入房间
		private function _onTimeOut_GetTeamList(sessionID:uint):void
		{
			var retParam:SRetParam_GetTeamList = new SRetParam_GetTeamList();
			var event_:TEvt_GetTeamList = new TEvt_GetTeamList(TEvt_GetTeamList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求创建房间
		private function _doReturn_CreateTeam(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CreateTeam = new SRetParam_CreateTeam();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTeamID:uint = bytes.readUnsignedInt(); //(无符号32位整数)房间ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)创建房间结果
			retParam_.dwTeamID = dwTeamID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CreateTeam = _sessionMgr.getData(sessionID_) as SOrigParam_CreateTeam;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CreateTeam = new TEvt_CreateTeam(TEvt_CreateTeam.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求创建房间
		private function _onTimeOut_CreateTeam(sessionID:uint):void
		{
			var retParam:SRetParam_CreateTeam = new SRetParam_CreateTeam();
			var event_:TEvt_CreateTeam = new TEvt_CreateTeam(TEvt_CreateTeam.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求加入房间
		private function _doReturn_EnterTeam(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterTeam = new SRetParam_EnterTeam();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var dwTeamID:uint = bytes.readUnsignedInt(); //(无符号32位整数)房间ID
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)请求加入房间
			retParam_.dwTeamID = dwTeamID;
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_EnterTeam = _sessionMgr.getData(sessionID_) as SOrigParam_EnterTeam;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterTeam = new TEvt_EnterTeam(TEvt_EnterTeam.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求加入房间
		private function _onTimeOut_EnterTeam(sessionID:uint):void
		{
			var retParam:SRetParam_EnterTeam = new SRetParam_EnterTeam();
			var event_:TEvt_EnterTeam = new TEvt_EnterTeam(TEvt_EnterTeam.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求更换将
		private function _doReturn_ResetFigter(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ResetFigter = new SRetParam_ResetFigter();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)请求更换将
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ResetFigter = _sessionMgr.getData(sessionID_) as SOrigParam_ResetFigter;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ResetFigter = new TEvt_ResetFigter(TEvt_ResetFigter.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求更换将
		private function _onTimeOut_ResetFigter(sessionID:uint):void
		{
			var retParam:SRetParam_ResetFigter = new SRetParam_ResetFigter();
			var event_:TEvt_ResetFigter = new TEvt_ResetFigter(TEvt_ResetFigter.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：交换自己的将位置
		private function _doReturn_ChangeSelfPos(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangeSelfPos = new SRetParam_ChangeSelfPos();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangeSelfPos = _sessionMgr.getData(sessionID_) as SOrigParam_ChangeSelfPos;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangeSelfPos = new TEvt_ChangeSelfPos(TEvt_ChangeSelfPos.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：交换自己的将位置
		private function _onTimeOut_ChangeSelfPos(sessionID:uint):void
		{
			var retParam:SRetParam_ChangeSelfPos = new SRetParam_ChangeSelfPos();
			var event_:TEvt_ChangeSelfPos = new TEvt_ChangeSelfPos(TEvt_ChangeSelfPos.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：交换列的位置
		private function _doReturn_ChangeArrayPos(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangeArrayPos = new SRetParam_ChangeArrayPos();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangeArrayPos = _sessionMgr.getData(sessionID_) as SOrigParam_ChangeArrayPos;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangeArrayPos = new TEvt_ChangeArrayPos(TEvt_ChangeArrayPos.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：交换列的位置
		private function _onTimeOut_ChangeArrayPos(sessionID:uint):void
		{
			var retParam:SRetParam_ChangeArrayPos = new SRetParam_ChangeArrayPos();
			var event_:TEvt_ChangeArrayPos = new TEvt_ChangeArrayPos(TEvt_ChangeArrayPos.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求离开房间
		private function _doReturn_LeaveTeam(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveTeam = new SRetParam_LeaveTeam();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_LeaveTeam = _sessionMgr.getData(sessionID_) as SOrigParam_LeaveTeam;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeaveTeam = new TEvt_LeaveTeam(TEvt_LeaveTeam.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求离开房间
		private function _onTimeOut_LeaveTeam(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveTeam = new SRetParam_LeaveTeam();
			var event_:TEvt_LeaveTeam = new TEvt_LeaveTeam(TEvt_LeaveTeam.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家已经准备好
		private function _doReturn_DoReady(bytes:ByteArray):void
		{
			var retParam_:SRetParam_DoReady = new SRetParam_DoReady();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_DoReady = _sessionMgr.getData(sessionID_) as SOrigParam_DoReady;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_DoReady = new TEvt_DoReady(TEvt_DoReady.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家已经准备好
		private function _onTimeOut_DoReady(sessionID:uint):void
		{
			var retParam:SRetParam_DoReady = new SRetParam_DoReady();
			var event_:TEvt_DoReady = new TEvt_DoReady(TEvt_DoReady.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：玩家取消准备好
		private function _doReturn_CancelDoReady(bytes:ByteArray):void
		{
			var retParam_:SRetParam_CancelDoReady = new SRetParam_CancelDoReady();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_CancelDoReady = _sessionMgr.getData(sessionID_) as SOrigParam_CancelDoReady;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_CancelDoReady = new TEvt_CancelDoReady(TEvt_CancelDoReady.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：玩家取消准备好
		private function _onTimeOut_CancelDoReady(sessionID:uint):void
		{
			var retParam:SRetParam_CancelDoReady = new SRetParam_CancelDoReady();
			var event_:TEvt_CancelDoReady = new TEvt_CancelDoReady(TEvt_CancelDoReady.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求进入副本
		private function _doReturn_EnterDgn(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterDgn = new SRetParam_EnterDgn();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_EnterDgn = _sessionMgr.getData(sessionID_) as SOrigParam_EnterDgn;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterDgn = new TEvt_EnterDgn(TEvt_EnterDgn.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求进入副本
		private function _onTimeOut_EnterDgn(sessionID:uint):void
		{
			var retParam:SRetParam_EnterDgn = new SRetParam_EnterDgn();
			var event_:TEvt_EnterDgn = new TEvt_EnterDgn(TEvt_EnterDgn.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求踢玩家出队伍
		private function _doReturn_KickOffPlayer(bytes:ByteArray):void
		{
			var retParam_:SRetParam_KickOffPlayer = new SRetParam_KickOffPlayer();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_KickOffPlayer = _sessionMgr.getData(sessionID_) as SOrigParam_KickOffPlayer;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_KickOffPlayer = new TEvt_KickOffPlayer(TEvt_KickOffPlayer.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求踢玩家出队伍
		private function _onTimeOut_KickOffPlayer(sessionID:uint):void
		{
			var retParam:SRetParam_KickOffPlayer = new SRetParam_KickOffPlayer();
			var event_:TEvt_KickOffPlayer = new TEvt_KickOffPlayer(TEvt_KickOffPlayer.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取队伍信息
		private function _doReturn_GetTeamInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetTeamInfo = new SRetParam_GetTeamInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_GetTeamInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetTeamInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetTeamInfo = new TEvt_GetTeamInfo(TEvt_GetTeamInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取队伍信息
		private function _onTimeOut_GetTeamInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetTeamInfo = new SRetParam_GetTeamInfo();
			var event_:TEvt_GetTeamInfo = new TEvt_GetTeamInfo(TEvt_GetTeamInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：换副本请求
		private function _doReturn_ChangDgnType(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangDgnType = new SRetParam_ChangDgnType();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangDgnType = _sessionMgr.getData(sessionID_) as SOrigParam_ChangDgnType;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangDgnType = new TEvt_ChangDgnType(TEvt_ChangDgnType.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：换副本请求
		private function _onTimeOut_ChangDgnType(sessionID:uint):void
		{
			var retParam:SRetParam_ChangDgnType = new SRetParam_ChangDgnType();
			var event_:TEvt_ChangDgnType = new TEvt_ChangDgnType(TEvt_ChangDgnType.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：换阵灵请求
		private function _doReturn_ChangPet(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangPet = new SRetParam_ChangPet();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangPet = _sessionMgr.getData(sessionID_) as SOrigParam_ChangPet;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangPet = new TEvt_ChangPet(TEvt_ChangPet.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：换阵灵请求
		private function _onTimeOut_ChangPet(sessionID:uint):void
		{
			var retParam:SRetParam_ChangPet = new SRetParam_ChangPet();
			var event_:TEvt_ChangPet = new TEvt_ChangPet(TEvt_ChangPet.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：更改设置请求
		private function _doReturn_ChangSetting(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangSetting = new SRetParam_ChangSetting();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangSetting = _sessionMgr.getData(sessionID_) as SOrigParam_ChangSetting;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangSetting = new TEvt_ChangSetting(TEvt_ChangSetting.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：更改设置请求
		private function _onTimeOut_ChangSetting(sessionID:uint):void
		{
			var retParam:SRetParam_ChangSetting = new SRetParam_ChangSetting();
			var event_:TEvt_ChangSetting = new TEvt_ChangSetting(TEvt_ChangSetting.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：换队长
		private function _doReturn_ChangLeader(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangLeader = new SRetParam_ChangLeader();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：ETEAMResult)返回
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_ChangLeader = _sessionMgr.getData(sessionID_) as SOrigParam_ChangLeader;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangLeader = new TEvt_ChangLeader(TEvt_ChangLeader.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：换队长
		private function _onTimeOut_ChangLeader(sessionID:uint):void
		{
			var retParam:SRetParam_ChangLeader = new SRetParam_ChangLeader();
			var event_:TEvt_ChangLeader = new TEvt_ChangLeader(TEvt_ChangLeader.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:TeamGS;

		public static function get instance():TeamGS
		{
			if(_instance == null)
				_instance = new TeamGS();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function TeamGS()
		{
			_protID = 56;
			_recvFuncList = [
				_doRecv_TeamInfoUpdate, //FuncID: 1
				_doRecv_NoticeKicked, //FuncID: 2
				_doRecv_UpdateTeamInfoList, //FuncID: 3
				_doRecv_TeamDelForList //FuncID: 4
			];

			_retFuncList = [
				_doReturn_GetTeamList, //FuncID: 1
				_doReturn_CreateTeam, //FuncID: 2
				_doReturn_EnterTeam, //FuncID: 3
				_doReturn_ResetFigter, //FuncID: 4
				_doReturn_ChangeSelfPos, //FuncID: 5
				_doReturn_ChangeArrayPos, //FuncID: 6
				_doReturn_LeaveTeam, //FuncID: 7
				_doReturn_DoReady, //FuncID: 8
				_doReturn_CancelDoReady, //FuncID: 9
				_doReturn_EnterDgn, //FuncID: 10
				_doReturn_KickOffPlayer, //FuncID: 11
				_doReturn_GetTeamInfo, //FuncID: 12
				_doReturn_ChangDgnType, //FuncID: 13
				_doReturn_ChangPet, //FuncID: 14
				_doReturn_ChangSetting, //FuncID: 15
				_doReturn_ChangLeader //FuncID: 16
			];

			_timeFuncList = [
				_onTimeOut_GetTeamList, //FuncID: 1
				_onTimeOut_CreateTeam, //FuncID: 2
				_onTimeOut_EnterTeam, //FuncID: 3
				_onTimeOut_ResetFigter, //FuncID: 4
				_onTimeOut_ChangeSelfPos, //FuncID: 5
				_onTimeOut_ChangeArrayPos, //FuncID: 6
				_onTimeOut_LeaveTeam, //FuncID: 7
				_onTimeOut_DoReady, //FuncID: 8
				_onTimeOut_CancelDoReady, //FuncID: 9
				_onTimeOut_EnterDgn, //FuncID: 10
				_onTimeOut_KickOffPlayer, //FuncID: 11
				_onTimeOut_GetTeamInfo, //FuncID: 12
				_onTimeOut_ChangDgnType, //FuncID: 13
				_onTimeOut_ChangPet, //FuncID: 14
				_onTimeOut_ChangSetting, //FuncID: 15
				_onTimeOut_ChangLeader //FuncID: 16
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