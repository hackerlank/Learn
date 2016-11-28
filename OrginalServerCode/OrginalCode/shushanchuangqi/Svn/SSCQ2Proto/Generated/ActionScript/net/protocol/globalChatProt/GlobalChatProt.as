/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    GlobalChatProt.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.protoCommon.SFtAttrMod;
	import net.protocol.protoCommon.SPlatformParam;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：全局聊天协议
	 */
	public class GlobalChatProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：聊天
		 * @param eChannelType (枚举类型：EChannelType)通道类型
		 * @param strInfo 聊天信息
		 * @param vecShowInfo 炫耀物品信息
		 */
		public function send_Chat(eChannelType:uint, strInfo:String, vecShowInfo:Vector.<SShowInfo>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeByte(eChannelType);
			BytesUtil.writeString(bytes_, strInfo);
			SShowInfo.vectorToByteArray(vecShowInfo, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：私聊
		 * @param qwUsrID (无符号64位整数)帐号ID
		 * @param strInfo 聊天信息
		 * @param vecShowInfo 炫耀物品信息
		 */
		public function send_Whisper(qwUsrID:BigInteger, strInfo:String, vecShowInfo:Vector.<SShowInfo>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_Whisper = new SOrigParam_Whisper();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwUsrID);
			BytesUtil.writeString(bytes_, strInfo);
			SShowInfo.vectorToByteArray(vecShowInfo, bytes_);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：获取炫耀信息
		 * @param qwInstID (无符号64位整数)唯一ID
		 */
		public function send_GetShowInfo(qwInstID:BigInteger, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_GetShowInfo = new SOrigParam_GetShowInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeUInt64(bytes_, qwInstID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：请求私聊信息
		 * @param strReceiveName 玩家名字
		 */
		public function send_ReqWhisperInfo(strReceiveName:String, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 3);
			var origParam_:SOrigParam_ReqWhisperInfo = new SOrigParam_ReqWhisperInfo();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			BytesUtil.writeString(bytes_, strReceiveName);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：聊天信息通知
		private function _doRecv_ChatInfoNotify(bytes:ByteArray):void
		{
			var eChannelType:uint = bytes.readUnsignedByte(); //(枚举类型：EChannelType)通道类型
			var rSenderInfo:SSenderInfo = SSenderInfo.fromByteArray(bytes); //发送者信息
			var strInfo:String = BytesUtil.readString(bytes); //聊天信息
			var vecShowInfo:Vector.<SShowInfo> = SShowInfo.vectorFromByteArray(bytes); //炫耀物品信息
			var event_:REvt_ChatInfoNotify = new REvt_ChatInfoNotify(REvt_ChatInfoNotify.DATA_RECEIVE);
			event_.eChannelType = eChannelType;
			event_.rSenderInfo = rSenderInfo;
			event_.strInfo = strInfo;
			event_.vecShowInfo = vecShowInfo;
			dispatchEvent(event_);
		}

		//接收处理：私聊错误通知
		private function _doRecv_WhisperErrorNotify(bytes:ByteArray):void
		{
			var eErrType:uint = bytes.readUnsignedByte(); //(枚举类型：EWhisperErrorType)错误类型
			var qwUsrID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)帐号ID
			var event_:REvt_WhisperErrorNotify = new REvt_WhisperErrorNotify(REvt_WhisperErrorNotify.DATA_RECEIVE);
			event_.eErrType = eErrType;
			event_.qwUsrID = qwUsrID;
			dispatchEvent(event_);
		}

		//接收处理：私聊信息通知
		private function _doRecv_WhisperInfoNotify(bytes:ByteArray):void
		{
			var rSenderInfo:SSenderInfo = SSenderInfo.fromByteArray(bytes); //发送者信息
			var strInfo:String = BytesUtil.readString(bytes); //私聊信息
			var vecShowInfo:Vector.<SShowInfo> = SShowInfo.vectorFromByteArray(bytes); //炫耀物品信息
			var event_:REvt_WhisperInfoNotify = new REvt_WhisperInfoNotify(REvt_WhisperInfoNotify.DATA_RECEIVE);
			event_.rSenderInfo = rSenderInfo;
			event_.strInfo = strInfo;
			event_.vecShowInfo = vecShowInfo;
			dispatchEvent(event_);
		}

		//接收处理：系统信息通知
		private function _doRecv_SystemMsgNotify(bytes:ByteArray):void
		{
			var eChannelType:uint = bytes.readUnsignedByte(); //(枚举类型：EChannelType)通道类型
			var strInfo:String = BytesUtil.readString(bytes); //聊天信息
			var eSubType:uint = bytes.readUnsignedByte(); //(枚举类型：EChannelSubType)额外信息
			var event_:REvt_SystemMsgNotify = new REvt_SystemMsgNotify(REvt_SystemMsgNotify.DATA_RECEIVE);
			event_.eChannelType = eChannelType;
			event_.strInfo = strInfo;
			event_.eSubType = eSubType;
			dispatchEvent(event_);
		}

		//接收处理：系统MsgID通知
		private function _doRecv_SystemMsgIDNotify(bytes:ByteArray):void
		{
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)消息ID
			var event_:REvt_SystemMsgIDNotify = new REvt_SystemMsgIDNotify(REvt_SystemMsgIDNotify.DATA_RECEIVE);
			event_.wMsgID = wMsgID;
			dispatchEvent(event_);
		}

		//接收处理：系统MsgID通知
		private function _doRecv_SystemFormatMsgIDNotify(bytes:ByteArray):void
		{
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)消息ID
			var vecStr:Vector.<String> = BytesUtil.readVecString(bytes); //聊天信息参数
			var event_:REvt_SystemFormatMsgIDNotify = new REvt_SystemFormatMsgIDNotify(REvt_SystemFormatMsgIDNotify.DATA_RECEIVE);
			event_.wMsgID = wMsgID;
			event_.vecStr = vecStr;
			dispatchEvent(event_);
		}

		//接收处理：系统弹窗和公告更新通知
		private function _doRecv_SysDialogAndNoticeUpdateNotify(bytes:ByteArray):void
		{
			var byNotifyType:uint = bytes.readUnsignedByte(); //(无符号8位整数)通知类型1:系统弹窗通知；2、公告更新通知
			var event_:REvt_SysDialogAndNoticeUpdateNotify = new REvt_SysDialogAndNoticeUpdateNotify(REvt_SysDialogAndNoticeUpdateNotify.DATA_RECEIVE);
			event_.byNotifyType = byNotifyType;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：私聊
		private function _doReturn_Whisper(bytes:ByteArray):void
		{
			var retParam_:SRetParam_Whisper = new SRetParam_Whisper();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)返回错误码（0为没有错误）
			retParam_.wMsgID = wMsgID;
			var origParam_:SOrigParam_Whisper = _sessionMgr.getData(sessionID_) as SOrigParam_Whisper;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_Whisper = new TEvt_Whisper(TEvt_Whisper.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：私聊
		private function _onTimeOut_Whisper(sessionID:uint):void
		{
			var retParam:SRetParam_Whisper = new SRetParam_Whisper();
			var event_:TEvt_Whisper = new TEvt_Whisper(TEvt_Whisper.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：获取炫耀信息
		private function _doReturn_GetShowInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_GetShowInfo = new SRetParam_GetShowInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var rSenderInfo:SSenderInfo = SSenderInfo.fromByteArray(bytes); //发送者信息
			var strShowInfo:ByteArray = BytesUtil.readBytes(bytes); //展示信息序列化
			retParam_.rSenderInfo = rSenderInfo;
			retParam_.strShowInfo = strShowInfo;
			var origParam_:SOrigParam_GetShowInfo = _sessionMgr.getData(sessionID_) as SOrigParam_GetShowInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_GetShowInfo = new TEvt_GetShowInfo(TEvt_GetShowInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：获取炫耀信息
		private function _onTimeOut_GetShowInfo(sessionID:uint):void
		{
			var retParam:SRetParam_GetShowInfo = new SRetParam_GetShowInfo();
			var event_:TEvt_GetShowInfo = new TEvt_GetShowInfo(TEvt_GetShowInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：请求私聊信息
		private function _doReturn_ReqWhisperInfo(bytes:ByteArray):void
		{
			var retParam_:SRetParam_ReqWhisperInfo = new SRetParam_ReqWhisperInfo();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var whisperInfo:SWhisperInfo = SWhisperInfo.fromByteArray(bytes); //获取私聊对方信息返回
			retParam_.whisperInfo = whisperInfo;
			var origParam_:SOrigParam_ReqWhisperInfo = _sessionMgr.getData(sessionID_) as SOrigParam_ReqWhisperInfo;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_ReqWhisperInfo = new TEvt_ReqWhisperInfo(TEvt_ReqWhisperInfo.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：请求私聊信息
		private function _onTimeOut_ReqWhisperInfo(sessionID:uint):void
		{
			var retParam:SRetParam_ReqWhisperInfo = new SRetParam_ReqWhisperInfo();
			var event_:TEvt_ReqWhisperInfo = new TEvt_ReqWhisperInfo(TEvt_ReqWhisperInfo.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:GlobalChatProt;

		public static function get instance():GlobalChatProt
		{
			if(_instance == null)
				_instance = new GlobalChatProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function GlobalChatProt()
		{
			_protID = 28;
			_recvFuncList = [
				_doRecv_ChatInfoNotify, //FuncID: 1
				_doRecv_WhisperErrorNotify, //FuncID: 2
				_doRecv_WhisperInfoNotify, //FuncID: 3
				_doRecv_SystemMsgNotify, //FuncID: 4
				_doRecv_SystemMsgIDNotify, //FuncID: 5
				_doRecv_SystemFormatMsgIDNotify, //FuncID: 6
				_doRecv_SysDialogAndNoticeUpdateNotify //FuncID: 7
			];

			_retFuncList = [
				_doReturn_Whisper, //FuncID: 1
				_doReturn_GetShowInfo, //FuncID: 2
				_doReturn_ReqWhisperInfo //FuncID: 3
			];

			_timeFuncList = [
				_onTimeOut_Whisper, //FuncID: 1
				_onTimeOut_GetShowInfo, //FuncID: 2
				_onTimeOut_ReqWhisperInfo //FuncID: 3
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