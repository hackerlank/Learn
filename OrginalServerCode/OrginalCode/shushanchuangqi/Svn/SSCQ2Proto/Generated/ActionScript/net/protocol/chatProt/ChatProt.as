/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    ChatProt.as
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.roleInfoDefine.SBubbleInfo;
	import net.protocol.globalChatProt.SSenderInfo;
	import net.protocol.globalChatProt.SShowInfo;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：聊天协议
	 */
	public class ChatProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：聊天
		 * @param eChannelType (枚举类型：globalChatProt.EChannelType)通道类型
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
		 * 发送：气泡信息获取
		 */
		public function send_BubbleGet(callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 1);
			var origParam_:SOrigParam_BubbleGet = new SOrigParam_BubbleGet();
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
		 * 发送：气泡回应
		 * @param wIndex (无符号16位整数)气泡对应位置
		 * @param vecParam (有符号64位整数)整型变量
		 * @param vecString 字符串型变量
		 */
		public function send_BubbleRespond(wIndex:uint, vecParam:Vector.<BigInteger>, vecString:Vector.<String>, callback:Function = null):Boolean
		{
			var sessionID_:uint = _sessionMgr.getNewSession(this, 2);
			var origParam_:SOrigParam_BubbleRespond = new SOrigParam_BubbleRespond();
			origParam_.callback = callback;
			_sessionMgr.storeData(sessionID_, origParam_);
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(sessionID_);
			bytes_.writeShort(wIndex);
			BytesUtil.writeVecInt64(bytes_, vecParam);
			BytesUtil.writeVecString(bytes_, vecString);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：邀请平台好友成功
		 * @param qwRoleID (无符号64位整数)被邀请人
		 */
		public function send_InviteSuc(qwRoleID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwRoleID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：聊天信息通知
		private function _doRecv_ChatInfoNotify(bytes:ByteArray):void
		{
			var eChannelType:uint = bytes.readUnsignedByte(); //(枚举类型：globalChatProt.EChannelType)通道类型
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

		//接收处理：系统信息通知
		private function _doRecv_SystemMsgNotify(bytes:ByteArray):void
		{
			var eChannelType:uint = bytes.readUnsignedByte(); //(枚举类型：globalChatProt.EChannelType)通道类型
			var strInfo:String = BytesUtil.readString(bytes); //聊天信息
			var eSubType:uint = bytes.readUnsignedByte(); //(枚举类型：globalChatProt.EChannelSubType)额外信息
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

		//接收处理：弹窗通知
		private function _doRecv_ElasticFrameNotify(bytes:ByteArray):void
		{
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)消息ID
			var event_:REvt_ElasticFrameNotify = new REvt_ElasticFrameNotify(REvt_ElasticFrameNotify.DATA_RECEIVE);
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

		//接收处理：气泡提示信息
		private function _doRecv_BubbleNotify(bytes:ByteArray):void
		{
			var vecBubbleInfo:Vector.<SBubbleInfo> = SBubbleInfo.vectorFromByteArray(bytes); //气泡列表信息
			var event_:REvt_BubbleNotify = new REvt_BubbleNotify(REvt_BubbleNotify.DATA_RECEIVE);
			event_.vecBubbleInfo = vecBubbleInfo;
			dispatchEvent(event_);
		}

		//接收处理：气泡提示信息更新
		private function _doRecv_BubbleUpdate(bytes:ByteArray):void
		{
			var eType:uint = bytes.readUnsignedByte(); //(枚举类型：protoCommon.EDataChange)更新类型，增加，删除，修改
			var sBubbleInfo:SBubbleInfo = SBubbleInfo.fromByteArray(bytes); //受影响的气泡信息
			var event_:REvt_BubbleUpdate = new REvt_BubbleUpdate(REvt_BubbleUpdate.DATA_RECEIVE);
			event_.eType = eType;
			event_.sBubbleInfo = sBubbleInfo;
			dispatchEvent(event_);
		}

		//接收处理：系统MsgID通知
		private function _doRecv_SystemFormatMsgIDNotifyWithShow(bytes:ByteArray):void
		{
			var wMsgID:uint = bytes.readUnsignedShort(); //(无符号16位整数)消息ID
			var vecStr:Vector.<String> = BytesUtil.readVecString(bytes); //聊天信息参数
			var vecShow:Vector.<SShowInfo> = SShowInfo.vectorFromByteArray(bytes); //炫耀信息
			var event_:REvt_SystemFormatMsgIDNotifyWithShow = new REvt_SystemFormatMsgIDNotifyWithShow(REvt_SystemFormatMsgIDNotifyWithShow.DATA_RECEIVE);
			event_.wMsgID = wMsgID;
			event_.vecStr = vecStr;
			event_.vecShow = vecShow;
			dispatchEvent(event_);
		}

		/////////////////////以下为返回处理函数/////////////////////
		//返回处理：气泡信息获取
		private function _doReturn_BubbleGet(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BubbleGet = new SRetParam_BubbleGet();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var vecBubbleInfo:Vector.<SBubbleInfo> = SBubbleInfo.vectorFromByteArray(bytes); //气泡列表信息
			retParam_.vecBubbleInfo = vecBubbleInfo;
			var origParam_:SOrigParam_BubbleGet = _sessionMgr.getData(sessionID_) as SOrigParam_BubbleGet;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BubbleGet = new TEvt_BubbleGet(TEvt_BubbleGet.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：气泡信息获取
		private function _onTimeOut_BubbleGet(sessionID:uint):void
		{
			var retParam:SRetParam_BubbleGet = new SRetParam_BubbleGet();
			var event_:TEvt_BubbleGet = new TEvt_BubbleGet(TEvt_BubbleGet.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		//返回处理：气泡回应
		private function _doReturn_BubbleRespond(bytes:ByteArray):void
		{
			var retParam_:SRetParam_BubbleRespond = new SRetParam_BubbleRespond();
			var sessionID_:uint = bytes.readUnsignedInt();
			var ret_:Boolean = bytes.readBoolean();
			var eResult:uint = bytes.readUnsignedByte(); //(枚举类型：EBubbleResult)气泡操作返回结果
			retParam_.eResult = eResult;
			var origParam_:SOrigParam_BubbleRespond = _sessionMgr.getData(sessionID_) as SOrigParam_BubbleRespond;
			var ret:int = 0;
			if(!ret_)
				ret = 1;
			var event_:TEvt_BubbleRespond = new TEvt_BubbleRespond(TEvt_BubbleRespond.DATA_RETURN);
			event_.ret = ret;
			event_.retParam = retParam_;
			if (origParam_.callback != null)
				origParam_.callback(event_);
			else
				dispatchEvent(event_);
			_sessionMgr.delSession(sessionID_);
		}

		//超时处理：气泡回应
		private function _onTimeOut_BubbleRespond(sessionID:uint):void
		{
			var retParam:SRetParam_BubbleRespond = new SRetParam_BubbleRespond();
			var event_:TEvt_BubbleRespond = new TEvt_BubbleRespond(TEvt_BubbleRespond.DATA_RETURN);
			event_.ret = 2;
			event_.retParam = retParam;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:ChatProt;

		public static function get instance():ChatProt
		{
			if(_instance == null)
				_instance = new ChatProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;
		private var _retFuncList:Array;
		private var _timeFuncList:Array;

		public function ChatProt()
		{
			_protID = 23;
			_recvFuncList = [
				_doRecv_ChatInfoNotify, //FuncID: 1
				_doRecv_SystemMsgNotify, //FuncID: 2
				_doRecv_SystemMsgIDNotify, //FuncID: 3
				_doRecv_ElasticFrameNotify, //FuncID: 4
				_doRecv_SystemFormatMsgIDNotify, //FuncID: 5
				_doRecv_BubbleNotify, //FuncID: 6
				_doRecv_BubbleUpdate, //FuncID: 7
				_doRecv_SystemFormatMsgIDNotifyWithShow //FuncID: 8
			];

			_retFuncList = [
				_doReturn_BubbleGet, //FuncID: 1
				_doReturn_BubbleRespond, //FuncID: 2
			];

			_timeFuncList = [
				_onTimeOut_BubbleGet, //FuncID: 1
				_onTimeOut_BubbleRespond, //FuncID: 2
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