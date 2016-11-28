/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    LingShanProt.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：灵山（改名秘境）寻宝
	 */
	public class LingShanProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：获取状态（回StatusNotify通知）
		 */
		public function send_GetStatus():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：活动报名
		 */
		public function send_Reg(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_Reg = new SOrigParam_Reg();
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
		 * 发送：当前棋盘状态
		 */
		public function send_GetMatchInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetMatchInfo = new SOrigParam_GetMatchInfo();
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
		 * 发送：获取自己的比赛信息
		 */
		public function send_GetMathSelInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_GetMathSelInfo = new SOrigParam_GetMathSelInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：更换模型信息
		 * @param dwModelID (无符号32位整数)模型id
		 */
		public function send_ChangeModel(dwModelID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_ChangeModel = new SOrigParam_ChangeModel();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeUnsignedInt(dwModelID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：移动选择
		 * @param wPos (无符号16位整数)位置
		 */
		public function send_MoveSelect(wPos:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 5);
			var origParam_:SOrigParam_MoveSelect = new SOrigParam_MoveSelect();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wPos);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取活动信息
		 */
		public function send_GetActInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 6);
			var origParam_:SOrigParam_GetActInfo = new SOrigParam_GetActInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：聊天
		 * @param strChatMsg 聊天内容
		 */
		public function send_Chat(strChatMsg:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 7);
			var origParam_:SOrigParam_Chat = new SOrigParam_Chat();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 8;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strChatMsg);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取房间信息
		 */
		public function send_GetRoomList(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 8);
			var origParam_:SOrigParam_GetRoomList = new SOrigParam_GetRoomList();
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
		 * 发送：进入参观房间
		 * @param wRoomID (无符号16位整数)房间id
		 */
		public function send_EnterVisitRoom(wRoomID:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 9);
			var origParam_:SOrigParam_EnterVisitRoom = new SOrigParam_EnterVisitRoom();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wRoomID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：离开参观房间
		 */
		public function send_LeaveVisitRoom(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 10);
			var origParam_:SOrigParam_LeaveVisitRoom = new SOrigParam_LeaveVisitRoom();
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
		 * 发送：获取动画播放信息
		 */
		public function send_GetPlayMovieInfo(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 11);
			var origParam_:SOrigParam_GetPlayMovieInfo = new SOrigParam_GetPlayMovieInfo();
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
		//接收处理：玩家个人血量通知
		private function _doRecv_SelHPRateNotify(bytes:ByteArray):void
		{
			var fHPRate:Number = bytes.readFloat(); //(Float)血量百分比
			var event_:REvt_SelHPRateNotify = new REvt_SelHPRateNotify(REvt_SelHPRateNotify.DATA_RECEIVE);
			event_.fHPRate = fHPRate;
			dispatchEvent(event_);
		}

		//接收处理：玩家自己当前状态通知
		private function _doRecv_StatusNotify(bytes:ByteArray):void
		{
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanStatus)当前状态
			var dwParam:uint = bytes.readUnsignedInt(); //(无符号32位整数)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)服务器时间戳
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_StatusNotify = new REvt_StatusNotify(REvt_StatusNotify.DATA_RECEIVE);
			event_.eRet = eRet;
			event_.dwParam = dwParam;
			event_.dwTime = dwTime;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：观看房间当前状态通知
		private function _doRecv_VisitRoomStatusNotify(bytes:ByteArray):void
		{
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanStatus)当前状态
			var dwParam:uint = bytes.readUnsignedInt(); //(无符号32位整数)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)服务器时间戳
			var event_:REvt_VisitRoomStatusNotify = new REvt_VisitRoomStatusNotify(REvt_VisitRoomStatusNotify.DATA_RECEIVE);
			event_.eRet = eRet;
			event_.dwParam = dwParam;
			event_.dwTime = dwTime;
			dispatchEvent(event_);
		}

		//接收处理：玩家移动结果通知
		private function _doRecv_PlayerMoveNotify(bytes:ByteArray):void
		{
			var vecPlayerMoveInfo:Vector.<SPlayerMoveInfo> = SPlayerMoveInfo.vectorFromByteArray(bytes); //玩家移动路径
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_PlayerMoveNotify = new REvt_PlayerMoveNotify(REvt_PlayerMoveNotify.DATA_RECEIVE);
			event_.vecPlayerMoveInfo = vecPlayerMoveInfo;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：玩家路径碰撞结果通知
		private function _doRecv_PathCollideNotify(bytes:ByteArray):void
		{
			var vecPathCollideInfo:Vector.<SPathCollideInfo> = SPathCollideInfo.vectorFromByteArray(bytes); //路径碰撞
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_PathCollideNotify = new REvt_PathCollideNotify(REvt_PathCollideNotify.DATA_RECEIVE);
			event_.vecPathCollideInfo = vecPathCollideInfo;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：玩家格子碰撞结果通知
		private function _doRecv_GridCollideNotify(bytes:ByteArray):void
		{
			var vecGridCollideInfo:Vector.<SGridCollideInfo> = SGridCollideInfo.vectorFromByteArray(bytes); //格子碰撞
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_GridCollideNotify = new REvt_GridCollideNotify(REvt_GridCollideNotify.DATA_RECEIVE);
			event_.vecGridCollideInfo = vecGridCollideInfo;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：新玩家进入
		private function _doRecv_NewPlayerEnterNotify(bytes:ByteArray):void
		{
			var vecRoomPlayInfo:Vector.<SRoomPlayInfo> = SRoomPlayInfo.vectorFromByteArray(bytes); //玩家列表
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_NewPlayerEnterNotify = new REvt_NewPlayerEnterNotify(REvt_NewPlayerEnterNotify.DATA_RECEIVE);
			event_.vecRoomPlayInfo = vecRoomPlayInfo;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：新一轮开始
		private function _doRecv_NewTurnBeginNotify(bytes:ByteArray):void
		{
			var bFreshBox:Boolean = bytes.readBoolean(); //是否刷新宝箱
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var dwFreshTurn:uint = bytes.readUnsignedInt(); //(无符号32位整数)至宝刷新剩余轮数
			var event_:REvt_NewTurnBeginNotify = new REvt_NewTurnBeginNotify(REvt_NewTurnBeginNotify.DATA_RECEIVE);
			event_.bFreshBox = bFreshBox;
			event_.wRoomID = wRoomID;
			event_.dwFreshTurn = dwFreshTurn;
			dispatchEvent(event_);
		}

		//接收处理：模型修改
		private function _doRecv_PlayerChangeModelNotify(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)玩家id
			var dwModelID:uint = bytes.readUnsignedInt(); //(无符号32位整数)模型id
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_PlayerChangeModelNotify = new REvt_PlayerChangeModelNotify(REvt_PlayerChangeModelNotify.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.dwModelID = dwModelID;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：玩家奖励log
		private function _doRecv_PlayerPrizeLogNotify(bytes:ByteArray):void
		{
			var vecTakePrizeLog:Vector.<STakePrizeLog> = STakePrizeLog.vectorFromByteArray(bytes); //玩家奖励log列表
			var event_:REvt_PlayerPrizeLogNotify = new REvt_PlayerPrizeLogNotify(REvt_PlayerPrizeLogNotify.DATA_RECEIVE);
			event_.vecTakePrizeLog = vecTakePrizeLog;
			dispatchEvent(event_);
		}

		//接收处理：聊天
		private function _doRecv_ChatNotify(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)结果
			var strChatMsg:String = BytesUtil.readString(bytes); //聊天内容
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_ChatNotify = new REvt_ChatNotify(REvt_ChatNotify.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.strChatMsg = strChatMsg;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：玩家数据更新
		private function _doRecv_PlayerUpdateNotify(bytes:ByteArray):void
		{
			var vecRoomPlayInfo:Vector.<SRoomPlayInfo> = SRoomPlayInfo.vectorFromByteArray(bytes); //玩家列表
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var event_:REvt_PlayerUpdateNotify = new REvt_PlayerUpdateNotify(REvt_PlayerUpdateNotify.DATA_RECEIVE);
			event_.vecRoomPlayInfo = vecRoomPlayInfo;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：从观察者房间踢掉
		private function _doRecv_KickViewNotify(bytes:ByteArray):void
		{
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)进入的房间id
			var event_:REvt_KickViewNotify = new REvt_KickViewNotify(REvt_KickViewNotify.DATA_RECEIVE);
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		//接收处理：从房间离开
		private function _doRecv_KickPlayerNotify(bytes:ByteArray):void
		{
			var qwRoleID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)进入的房间id
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)进入的房间id
			var event_:REvt_KickPlayerNotify = new REvt_KickPlayerNotify(REvt_KickPlayerNotify.DATA_RECEIVE);
			event_.qwRoleID = qwRoleID;
			event_.wRoomID = wRoomID;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：活动报名
		private function _doReturn_Reg(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Reg = new SRetParam_Reg();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)报名结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_Reg = _sessionMgr.getData(sessionID_) as SOrigParam_Reg;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Reg = new TEvt_Reg(TEvt_Reg.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：活动报名
		private function _onTimeOut_Reg(sessionID:uint):void
		{
			var retParam:SRetParam_Reg = new SRetParam_Reg();
			var event_:TEvt_Reg = new TEvt_Reg(TEvt_Reg.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：当前棋盘状态
		private function _doReturn_GetMatchInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMatchInfo = new SRetParam_GetMatchInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var vecBoxInfo:Vector.<SBoxInfo> = SBoxInfo.vectorFromByteArray(bytes); //地图箱子信息
			var vecRoomPlayInfo:Vector.<SRoomPlayInfo> = SRoomPlayInfo.vectorFromByteArray(bytes); //地图玩家信息
			var vecRoomMonsterInfo:Vector.<SRoomMonsterInfo> = SRoomMonsterInfo.vectorFromByteArray(bytes); //地图怪物信息
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var dwFreshTurn:uint = bytes.readUnsignedInt(); //(无符号32位整数)至宝刷新剩余轮数
			var eStatus:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanStatus)当前状态
			var dwParam:uint = bytes.readUnsignedInt(); //(无符号32位整数)排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
			var dwTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)服务器时间戳
			var oPlayMovieInfo:SPlayMovieInfo = SPlayMovieInfo.fromByteArray(bytes); //动画播放信息
			var vecTakePrizeLog:Vector.<STakePrizeLog> = STakePrizeLog.vectorFromByteArray(bytes); //玩家奖励log列表
			var dwTurn:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前轮数
			retParam_.eRet = eRet;
			retParam_.vecBoxInfo = vecBoxInfo;
			retParam_.vecRoomPlayInfo = vecRoomPlayInfo;
			retParam_.vecRoomMonsterInfo = vecRoomMonsterInfo;
			retParam_.wRoomID = wRoomID;
			retParam_.dwFreshTurn = dwFreshTurn;
			retParam_.eStatus = eStatus;
			retParam_.dwParam = dwParam;
			retParam_.dwTime = dwTime;
			retParam_.oPlayMovieInfo = oPlayMovieInfo;
			retParam_.vecTakePrizeLog = vecTakePrizeLog;
			retParam_.dwTurn = dwTurn;
			var origParam_:SOrigParam_GetMatchInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetMatchInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMatchInfo = new TEvt_GetMatchInfo(TEvt_GetMatchInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：当前棋盘状态
		private function _onTimeOut_GetMatchInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetMatchInfo = new SRetParam_GetMatchInfo();
			var event_:TEvt_GetMatchInfo = new TEvt_GetMatchInfo(TEvt_GetMatchInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取自己的比赛信息
		private function _doReturn_GetMathSelInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetMathSelInfo = new SRetParam_GetMathSelInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var eStatus:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanStatus)当前状态
			var oRoomPlayInfo:SRoomPlayInfo = SRoomPlayInfo.fromByteArray(bytes); //玩家地图信息
			var fHPRate:Number = bytes.readFloat(); //(Float)血量百分比
			var dwBoxCnt:uint = bytes.readUnsignedShort(); //(无符号16位整数)宝箱数量
			var dwSuiYuan:uint = bytes.readUnsignedInt(); //(无符号32位整数)随缘值
			var dwRoomID:uint = bytes.readUnsignedInt(); //(无符号32位整数)房间号
			var dwFreshTurn:uint = bytes.readUnsignedInt(); //(无符号32位整数)至宝刷新剩余轮数
			var dwModelID:uint = bytes.readUnsignedInt(); //(无符号32位整数)模型id
			retParam_.eRet = eRet;
			retParam_.eStatus = eStatus;
			retParam_.oRoomPlayInfo = oRoomPlayInfo;
			retParam_.fHPRate = fHPRate;
			retParam_.dwBoxCnt = dwBoxCnt;
			retParam_.dwSuiYuan = dwSuiYuan;
			retParam_.dwRoomID = dwRoomID;
			retParam_.dwFreshTurn = dwFreshTurn;
			retParam_.dwModelID = dwModelID;
			var origParam_:SOrigParam_GetMathSelInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetMathSelInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetMathSelInfo = new TEvt_GetMathSelInfo(TEvt_GetMathSelInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取自己的比赛信息
		private function _onTimeOut_GetMathSelInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetMathSelInfo = new SRetParam_GetMathSelInfo();
			var event_:TEvt_GetMathSelInfo = new TEvt_GetMathSelInfo(TEvt_GetMathSelInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：更换模型信息
		private function _doReturn_ChangeModel(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ChangeModel = new SRetParam_ChangeModel();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)
			var dwModelID:uint = bytes.readUnsignedInt(); //(无符号32位整数)模型id
			retParam_.eRet = eRet;
			retParam_.dwModelID = dwModelID;
			var origParam_:SOrigParam_ChangeModel = _sessionMgr.getData(sessionID_) as SOrigParam_ChangeModel;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ChangeModel = new TEvt_ChangeModel(TEvt_ChangeModel.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：更换模型信息
		private function _onTimeOut_ChangeModel(sessionID:uint):void
		{
			var retParam:SRetParam_ChangeModel = new SRetParam_ChangeModel();
			var event_:TEvt_ChangeModel = new TEvt_ChangeModel(TEvt_ChangeModel.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：移动选择
		private function _doReturn_MoveSelect(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MoveSelect = new SRetParam_MoveSelect();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var dwCdTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)cd
			retParam_.eRet = eRet;
			retParam_.dwCdTime = dwCdTime;
			var origParam_:SOrigParam_MoveSelect = _sessionMgr.getData(sessionID_) as SOrigParam_MoveSelect;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_MoveSelect = new TEvt_MoveSelect(TEvt_MoveSelect.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：移动选择
		private function _onTimeOut_MoveSelect(sessionID:uint):void
		{
			var retParam:SRetParam_MoveSelect = new SRetParam_MoveSelect();
			var event_:TEvt_MoveSelect = new TEvt_MoveSelect(TEvt_MoveSelect.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取活动信息
		private function _doReturn_GetActInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetActInfo = new SRetParam_GetActInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var dwBeginTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)比赛开启时间
			var dwEndTime:uint = bytes.readUnsignedInt(); //(无符号32位整数)比赛结束时间
			retParam_.eRet = eRet;
			retParam_.dwBeginTime = dwBeginTime;
			retParam_.dwEndTime = dwEndTime;
			var origParam_:SOrigParam_GetActInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetActInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetActInfo = new TEvt_GetActInfo(TEvt_GetActInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取活动信息
		private function _onTimeOut_GetActInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetActInfo = new SRetParam_GetActInfo();
			var event_:TEvt_GetActInfo = new TEvt_GetActInfo(TEvt_GetActInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：聊天
		private function _doReturn_Chat(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Chat = new SRetParam_Chat();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_Chat = _sessionMgr.getData(sessionID_) as SOrigParam_Chat;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Chat = new TEvt_Chat(TEvt_Chat.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：聊天
		private function _onTimeOut_Chat(sessionID:uint):void
		{
			var retParam:SRetParam_Chat = new SRetParam_Chat();
			var event_:TEvt_Chat = new TEvt_Chat(TEvt_Chat.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取房间信息
		private function _doReturn_GetRoomList(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetRoomList = new SRetParam_GetRoomList();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var vecRoomInfo:Vector.<SRoomInfo> = SRoomInfo.vectorFromByteArray(bytes); //房间信息
			retParam_.eRet = eRet;
			retParam_.vecRoomInfo = vecRoomInfo;
			var origParam_:SOrigParam_GetRoomList = _sessionMgr.getData(sessionID_) as SOrigParam_GetRoomList;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetRoomList = new TEvt_GetRoomList(TEvt_GetRoomList.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取房间信息
		private function _onTimeOut_GetRoomList(sessionID:uint):void
		{
			var retParam:SRetParam_GetRoomList = new SRetParam_GetRoomList();
			var event_:TEvt_GetRoomList = new TEvt_GetRoomList(TEvt_GetRoomList.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：进入参观房间
		private function _doReturn_EnterVisitRoom(bytes:ByteArray):void
		{
			var retParam_:SRetParam_EnterVisitRoom = new SRetParam_EnterVisitRoom();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_EnterVisitRoom = _sessionMgr.getData(sessionID_) as SOrigParam_EnterVisitRoom;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_EnterVisitRoom = new TEvt_EnterVisitRoom(TEvt_EnterVisitRoom.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：进入参观房间
		private function _onTimeOut_EnterVisitRoom(sessionID:uint):void
		{
			var retParam:SRetParam_EnterVisitRoom = new SRetParam_EnterVisitRoom();
			var event_:TEvt_EnterVisitRoom = new TEvt_EnterVisitRoom(TEvt_EnterVisitRoom.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：离开参观房间
		private function _doReturn_LeaveVisitRoom(bytes:ByteArray):void
		{
			var retParam_:SRetParam_LeaveVisitRoom = new SRetParam_LeaveVisitRoom();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			retParam_.eRet = eRet;
			var origParam_:SOrigParam_LeaveVisitRoom = _sessionMgr.getData(sessionID_) as SOrigParam_LeaveVisitRoom;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_LeaveVisitRoom = new TEvt_LeaveVisitRoom(TEvt_LeaveVisitRoom.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：离开参观房间
		private function _onTimeOut_LeaveVisitRoom(sessionID:uint):void
		{
			var retParam:SRetParam_LeaveVisitRoom = new SRetParam_LeaveVisitRoom();
			var event_:TEvt_LeaveVisitRoom = new TEvt_LeaveVisitRoom(TEvt_LeaveVisitRoom.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取动画播放信息
		private function _doReturn_GetPlayMovieInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetPlayMovieInfo = new SRetParam_GetPlayMovieInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eRet:uint = bytes.readUnsignedByte(); //(枚举类型：ELingShanOP)结果
			var oPlayMovieInfo:SPlayMovieInfo = SPlayMovieInfo.fromByteArray(bytes); //动画播放信息
			var vecTakePrizeLog:Vector.<STakePrizeLog> = STakePrizeLog.vectorFromByteArray(bytes); //玩家奖励log列表
			var wRoomID:uint = bytes.readUnsignedShort(); //(无符号16位整数)房间id
			var dwTurn:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前轮数
			retParam_.eRet = eRet;
			retParam_.oPlayMovieInfo = oPlayMovieInfo;
			retParam_.vecTakePrizeLog = vecTakePrizeLog;
			retParam_.wRoomID = wRoomID;
			retParam_.dwTurn = dwTurn;
			var origParam_:SOrigParam_GetPlayMovieInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetPlayMovieInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetPlayMovieInfo = new TEvt_GetPlayMovieInfo(TEvt_GetPlayMovieInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取动画播放信息
		private function _onTimeOut_GetPlayMovieInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetPlayMovieInfo = new SRetParam_GetPlayMovieInfo();
			var event_:TEvt_GetPlayMovieInfo = new TEvt_GetPlayMovieInfo(TEvt_GetPlayMovieInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:LingShanProt;

		public static function get instance():LingShanProt
		{
			if(_instance == null)
				_instance = new LingShanProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function LingShanProt()
		{
			_protID = 135;
			_recvFuncList = [
				_doRecv_SelHPRateNotify, //FuncID: 1
				_doRecv_StatusNotify, //FuncID: 2
				_doRecv_VisitRoomStatusNotify, //FuncID: 3
				_doRecv_PlayerMoveNotify, //FuncID: 4
				_doRecv_PathCollideNotify, //FuncID: 5
				_doRecv_GridCollideNotify, //FuncID: 6
				_doRecv_NewPlayerEnterNotify, //FuncID: 7
				_doRecv_NewTurnBeginNotify, //FuncID: 8
				_doRecv_PlayerChangeModelNotify, //FuncID: 9
				_doRecv_PlayerPrizeLogNotify, //FuncID: 10
				_doRecv_ChatNotify, //FuncID: 11
				_doRecv_PlayerUpdateNotify, //FuncID: 12
				_doRecv_KickViewNotify, //FuncID: 13
				_doRecv_KickPlayerNotify //FuncID: 14
			];

			_retFuncList = [
				_doReturn_Reg, //FuncID: 1
				_doReturn_GetMatchInfo, //FuncID: 2
				_doReturn_GetMathSelInfo, //FuncID: 3
				_doReturn_ChangeModel, //FuncID: 4
				_doReturn_MoveSelect, //FuncID: 5
				_doReturn_GetActInfo, //FuncID: 6
				_doReturn_Chat, //FuncID: 7
				_doReturn_GetRoomList, //FuncID: 8
				_doReturn_EnterVisitRoom, //FuncID: 9
				_doReturn_LeaveVisitRoom, //FuncID: 10
				_doReturn_GetPlayMovieInfo //FuncID: 11
			];

			_timeFuncList = [
				_onTimeOut_Reg, //FuncID: 1
				_onTimeOut_GetMatchInfo, //FuncID: 2
				_onTimeOut_GetMathSelInfo, //FuncID: 3
				_onTimeOut_ChangeModel, //FuncID: 4
				_onTimeOut_MoveSelect, //FuncID: 5
				_onTimeOut_GetActInfo, //FuncID: 6
				_onTimeOut_Chat, //FuncID: 7
				_onTimeOut_GetRoomList, //FuncID: 8
				_onTimeOut_EnterVisitRoom, //FuncID: 9
				_onTimeOut_LeaveVisitRoom, //FuncID: 10
				_onTimeOut_GetPlayMovieInfo //FuncID: 11
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