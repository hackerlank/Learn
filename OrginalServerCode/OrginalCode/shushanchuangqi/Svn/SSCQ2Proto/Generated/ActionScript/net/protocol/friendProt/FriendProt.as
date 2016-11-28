/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    FriendProt.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：好友相关协议
	 */
	public class FriendProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：增加好友/黑名单请求
		 * @param eGroupType (枚举类型：EFriendGroupType)组别
		 * @param vecUserID (无符号64位整数)玩家ID
		 * @param byNeedRet (无符号8位整数)0-不需要返回消息 1-需要返回消息
		 */
		public function send_AddFriendReq1(eGroupType:uint, vecUserID:Vector.<BigInteger>, byNeedRet:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(eGroupType);
			BytesUtil.writeVecUInt64(bytes_, vecUserID);
			bytes_.writeByte(byNeedRet);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：增加好友/黑名单请求
		 * @param eGroupType (枚举类型：EFriendGroupType)组别
		 * @param strName 用户名
		 * @param byNeedRet (无符号8位整数)0-不需要返回消息 1-需要返回消息
		 */
		public function send_AddFriendReq2(eGroupType:uint, strName:String, byNeedRet:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(eGroupType);
			BytesUtil.writeString(bytes_, strName);
			bytes_.writeByte(byNeedRet);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：回答增加好友
		 * @param bAgree 是否同意
		 * @param qwUserID (无符号64位整数)帐号ID
		 */
		public function send_AnswerAddFriend(bAgree:Boolean, qwUserID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeBoolean(bAgree);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：删除好友/黑名单
		 * @param vecUserID (无符号64位整数)玩家ID
		 */
		public function send_RemoveFriendReq(vecUserID:Vector.<BigInteger>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			BytesUtil.writeVecUInt64(bytes_, vecUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：移动好友
		 * @param qwUserID (无符号64位整数)帐号ID
		 * @param eGroupType (枚举类型：EFriendGroupType)分组ID
		 */
		public function send_MoveFriend(qwUserID:BigInteger, eGroupType:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_MoveFriend = new SOrigParam_MoveFriend();
			origParam_.qwUserID = qwUserID;
			origParam_.eGroupType = eGroupType;
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			bytes_.writeByte(eGroupType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：私聊
		 * @param qwUserID (无符号64位整数)帐号ID
		 */
		public function send_Whisper(qwUserID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：查询玩家
		 * @param qwUserID (无符号64位整数)帐号ID
		 * @param strRoleName 主角色名
		 */
		public function send_FindUserIDNameReq(qwUserID:BigInteger, strRoleName:String):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 7;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwUserID);
			BytesUtil.writeString(bytes_, strRoleName);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取推荐好友
		 */
		public function send_FindReferFriendReq(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_FindReferFriendReq = new SOrigParam_FindReferFriendReq();
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
		 * 发送：取得所有好友信息
		 */
		public function send_GetFriendInfo():Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 9;
			bytes_.writeByte(funcID_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：修改签名
		 * @param strSign 签名文字：最多不超过255个字符
		 */
		public function send_SetSign(strSign:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_SetSign = new SOrigParam_SetSign();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 10;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strSign);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：设置心情表情
		 * @param wMood (无符号16位整数)心情表情
		 */
		public function send_SetMood(wMood:uint, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 4);
			var origParam_:SOrigParam_SetMood = new SOrigParam_SetMood();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 11;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wMood);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：询问增加好友
		private function _doRecv_AskAddFriend(bytes:ByteArray):void
		{
			var strRoleName:String = BytesUtil.readString(bytes); //角色名字
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var wFighterID:uint = bytes.readUnsignedShort(); //(无符号16位整数)主将ID
			var eSex:uint = bytes.readUnsignedByte(); //(枚举类型：protoCommon.ESexType)性别
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)等级
			var event_:REvt_AskAddFriend = new REvt_AskAddFriend(REvt_AskAddFriend.DATA_RECEIVE);
			event_.strRoleName = strRoleName;
			event_.qwUserID = qwUserID;
			event_.wFighterID = wFighterID;
			event_.eSex = eSex;
			event_.byLevel = byLevel;
			dispatchEvent(event_);
		}

		//接收处理：增加好友/黑名单回应
		private function _doRecv_AddFriendAck(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)增加好友的结果
			var strName:String = BytesUtil.readString(bytes); //名字 XXX: 如果主将改名需要修改此处
			var eSex:uint = bytes.readUnsignedByte(); //(枚举类型：protoCommon.ESexType)性别
			var event_:REvt_AddFriendAck = new REvt_AddFriendAck(REvt_AddFriendAck.DATA_RECEIVE);
			event_.eResult = eResult;
			event_.strName = strName;
			event_.eSex = eSex;
			dispatchEvent(event_);
		}

		//接收处理：增加好友/黑名单回应Ex
		private function _doRecv_AddFriendAckEx(bytes:ByteArray):void
		{
			var rFriendEntry:SFriendEntry = SFriendEntry.fromByteArray(bytes); //增加的好友
			var event_:REvt_AddFriendAckEx = new REvt_AddFriendAckEx(REvt_AddFriendAckEx.DATA_RECEIVE);
			event_.rFriendEntry = rFriendEntry;
			dispatchEvent(event_);
		}

		//接收处理：删除好友/黑名单回应
		private function _doRecv_RemoveFriendAck(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)删除好友的结果
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)删除的好友帐号ID
			var event_:REvt_RemoveFriendAck = new REvt_RemoveFriendAck(REvt_RemoveFriendAck.DATA_RECEIVE);
			event_.eResult = eResult;
			event_.qwUserID = qwUserID;
			dispatchEvent(event_);
		}

		//接收处理：私聊失败通知
		private function _doRecv_WhisperFailNotify(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)私聊通知的结果，成功不通知
			var event_:REvt_WhisperFailNotify = new REvt_WhisperFailNotify(REvt_WhisperFailNotify.DATA_RECEIVE);
			event_.eResult = eResult;
			dispatchEvent(event_);
		}

		//接收处理：私聊成功通知
		private function _doRecv_WhisperSuccessNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var strBaseInfo:String = BytesUtil.readString(bytes); //聊天基本信息
			var event_:REvt_WhisperSuccessNotify = new REvt_WhisperSuccessNotify(REvt_WhisperSuccessNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.strBaseInfo = strBaseInfo;
			dispatchEvent(event_);
		}

		//接收处理：好友信息通知
		private function _doRecv_FriendInfoNotify(bytes:ByteArray):void
		{
			var rFriend:SFriend = SFriend.fromByteArray(bytes); //好友信息
			var event_:REvt_FriendInfoNotify = new REvt_FriendInfoNotify(REvt_FriendInfoNotify.DATA_RECEIVE);
			event_.rFriend = rFriend;
			dispatchEvent(event_);
		}

		//接收处理：状态通知
		private function _doRecv_OnlineStatusNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var bOnlineStatus:Boolean = bytes.readBoolean(); //在线状态
			var event_:REvt_OnlineStatusNotify = new REvt_OnlineStatusNotify(REvt_OnlineStatusNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.bOnlineStatus = bOnlineStatus;
			dispatchEvent(event_);
		}

		//接收处理：等级变化通知
		private function _doRecv_LevelChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前等级
			var event_:REvt_LevelChangeNotify = new REvt_LevelChangeNotify(REvt_LevelChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.byLevel = byLevel;
			dispatchEvent(event_);
		}

		//接收处理：VIP变化通知
		private function _doRecv_VIPChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前等级
			var event_:REvt_VIPChangeNotify = new REvt_VIPChangeNotify(REvt_VIPChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.byLevel = byLevel;
			dispatchEvent(event_);
		}

		//接收处理：品质变化通知
		private function _doRecv_ColorChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var byColor:uint = bytes.readUnsignedByte(); //(无符号8位整数)当前品质
			var event_:REvt_ColorChangeNotify = new REvt_ColorChangeNotify(REvt_ColorChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.byColor = byColor;
			dispatchEvent(event_);
		}

		//接收处理：QQ黄钻好友通知
		private function _doRecv_YellowDiamondNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)等级
			var bYearlyPay:Boolean = bytes.readBoolean(); //是否年费黄钻
			var event_:REvt_YellowDiamondNotify = new REvt_YellowDiamondNotify(REvt_YellowDiamondNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.byLevel = byLevel;
			event_.bYearlyPay = bYearlyPay;
			dispatchEvent(event_);
		}

		//接收处理：签名改变通知
		private function _doRecv_SignChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var strSign:String = BytesUtil.readString(bytes); //签名
			var event_:REvt_SignChangeNotify = new REvt_SignChangeNotify(REvt_SignChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.strSign = strSign;
			dispatchEvent(event_);
		}

		//接收处理：签名改变通知
		private function _doRecv_MoodChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var wMood:uint = bytes.readUnsignedShort(); //(无符号16位整数)心情表情
			var event_:REvt_MoodChangeNotify = new REvt_MoodChangeNotify(REvt_MoodChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.wMood = wMood;
			dispatchEvent(event_);
		}

		//接收处理：签名改变通知
		private function _doRecv_VIPLevelChangeNotify(bytes:ByteArray):void
		{
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var byVIPLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)VIP等级
			var event_:REvt_VIPLevelChangeNotify = new REvt_VIPLevelChangeNotify(REvt_VIPLevelChangeNotify.DATA_RECEIVE);
			event_.qwUserID = qwUserID;
			event_.byVIPLevel = byVIPLevel;
			dispatchEvent(event_);
		}

		//接收处理：角色查询
		private function _doRecv_FindUserIDNameAck(bytes:ByteArray):void
		{
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)查询返回
			var qwUserID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var strRoleName:String = BytesUtil.readString(bytes); //主角色名
			var wHeroID:uint = bytes.readUnsignedShort(); //(无符号16位整数)主将ID
			var byLevel:uint = bytes.readUnsignedByte(); //(无符号8位整数)用户等级
			var bOnlineStatus:Boolean = bytes.readBoolean(); //在线状态
			var event_:REvt_FindUserIDNameAck = new REvt_FindUserIDNameAck(REvt_FindUserIDNameAck.DATA_RECEIVE);
			event_.eResult = eResult;
			event_.qwUserID = qwUserID;
			event_.strRoleName = strRoleName;
			event_.wHeroID = wHeroID;
			event_.byLevel = byLevel;
			event_.bOnlineStatus = bOnlineStatus;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：移动好友
		private function _doReturn_MoveFriend(bytes:ByteArray):void
		{
			var retParam_:SRetParam_MoveFriend = new SRetParam_MoveFriend();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)移动好友的结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_MoveFriend = _sessionMgr.getData(sessionID_) as SOrigParam_MoveFriend;
			var ret:int = 0;
			if(origParam_ == null)
				ret = 3; //确认已超时但又收到返回
			else if(!ret_)
				ret = 1;
			var event_:TEvt_MoveFriend = new TEvt_MoveFriend(TEvt_MoveFriend.DATA_RETURN);
			event_.ret = ret;
			event_.origParam = origParam_;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：移动好友
		private function _onTimeOut_MoveFriend(sessionID:uint):void
		{
			var retParam:SRetParam_MoveFriend = new SRetParam_MoveFriend();
			var origParam:SOrigParam_MoveFriend = _sessionMgr.getData(sessionID) as SOrigParam_MoveFriend;
			var event_:TEvt_MoveFriend = new TEvt_MoveFriend(TEvt_MoveFriend.DATA_RETURN);
			event_.ret = 2;
			event_.origParam = origParam;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取推荐好友
		private function _doReturn_FindReferFriendReq(bytes:ByteArray):void
		{
			var retParam_:SRetParam_FindReferFriendReq = new SRetParam_FindReferFriendReq();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecReferFriend:Vector.<SreferFriend> = SreferFriend.vectorFromByteArray(bytes); //推荐好友
			retParam_.vecReferFriend = vecReferFriend;
			var origParam_:SOrigParam_FindReferFriendReq = _sessionMgr.getData(sessionID_) as SOrigParam_FindReferFriendReq;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_FindReferFriendReq = new TEvt_FindReferFriendReq(TEvt_FindReferFriendReq.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取推荐好友
		private function _onTimeOut_FindReferFriendReq(sessionID:uint):void
		{
			var retParam:SRetParam_FindReferFriendReq = new SRetParam_FindReferFriendReq();
			var event_:TEvt_FindReferFriendReq = new TEvt_FindReferFriendReq(TEvt_FindReferFriendReq.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：修改签名
		private function _doReturn_SetSign(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetSign = new SRetParam_SetSign();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)修改签名结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SetSign = _sessionMgr.getData(sessionID_) as SOrigParam_SetSign;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetSign = new TEvt_SetSign(TEvt_SetSign.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：修改签名
		private function _onTimeOut_SetSign(sessionID:uint):void
		{
			var retParam:SRetParam_SetSign = new SRetParam_SetSign();
			var event_:TEvt_SetSign = new TEvt_SetSign(TEvt_SetSign.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：设置心情表情
		private function _doReturn_SetMood(bytes:ByteArray):void
		{
			var retParam_:SRetParam_SetMood = new SRetParam_SetMood();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EFriendResult)修改心情表情结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_SetMood = _sessionMgr.getData(sessionID_) as SOrigParam_SetMood;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_SetMood = new TEvt_SetMood(TEvt_SetMood.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：设置心情表情
		private function _onTimeOut_SetMood(sessionID:uint):void
		{
			var retParam:SRetParam_SetMood = new SRetParam_SetMood();
			var event_:TEvt_SetMood = new TEvt_SetMood(TEvt_SetMood.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:FriendProt;

		public static function get instance():FriendProt
		{
			if(_instance == null)
				_instance = new FriendProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function FriendProt()
		{
			_protID = 24;
			_recvFuncList = [
				_doRecv_AskAddFriend, //FuncID: 1
				_doRecv_AddFriendAck, //FuncID: 2
				_doRecv_AddFriendAckEx, //FuncID: 3
				_doRecv_RemoveFriendAck, //FuncID: 4
				_doRecv_WhisperFailNotify, //FuncID: 5
				_doRecv_WhisperSuccessNotify, //FuncID: 6
				_doRecv_FriendInfoNotify, //FuncID: 7
				_doRecv_OnlineStatusNotify, //FuncID: 8
				_doRecv_LevelChangeNotify, //FuncID: 9
				_doRecv_VIPChangeNotify, //FuncID: 10
				_doRecv_ColorChangeNotify, //FuncID: 11
				_doRecv_YellowDiamondNotify, //FuncID: 12
				_doRecv_SignChangeNotify, //FuncID: 13
				_doRecv_MoodChangeNotify, //FuncID: 14
				_doRecv_VIPLevelChangeNotify, //FuncID: 15
				_doRecv_FindUserIDNameAck //FuncID: 16
			];

			_retFuncList = [
				_doReturn_MoveFriend, //FuncID: 1
				_doReturn_FindReferFriendReq, //FuncID: 2
				_doReturn_SetSign, //FuncID: 3
				_doReturn_SetMood //FuncID: 4
			];

			_timeFuncList = [
				_onTimeOut_MoveFriend, //FuncID: 1
				_onTimeOut_FindReferFriendReq, //FuncID: 2
				_onTimeOut_SetSign, //FuncID: 3
				_onTimeOut_SetMood //FuncID: 4
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