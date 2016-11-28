/************************************************************************
//  工具自动生成的Flash客户端协议代码
//  File Name:    MailProt.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.utils.ByteArray;
	import com.hurlant.math.BigInteger;
	import net.protocol.itemProt.SItem;
	import net.core.*;
	import net.util.*;

	/**
	 * 协议：邮件CenterServer通讯协议
	 */
	public class MailProt extends ProtocolBase
	{
		/////////////////////以下为发送函数/////////////////////
		/**
		 * 发送：邮件ID请求
		 * @param uStartIndex (无符号32位整数)请求开始序号
		 * @param uiMailNum (无符号32位整数)请求邮件数量
		 * @param eQueryType (枚举类型：EMailQueryType)邮件类型
		 */
		public function send_MailPageIDReq(uStartIndex:uint, uiMailNum:uint, eQueryType:uint):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 1;
			bytes_.writeByte(funcID_);
			bytes_.writeUnsignedInt(uStartIndex);
			bytes_.writeUnsignedInt(uiMailNum);
			bytes_.writeByte(eQueryType);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：页邮件列表信息请求
		 * @param vecMailIDList (无符号64位整数)请求ID列表
		 */
		public function send_MailSummaryListReq(vecMailIDList:Vector.<BigInteger>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 2;
			bytes_.writeByte(funcID_);
			BytesUtil.writeVecUInt64(bytes_, vecMailIDList);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：单邮件信息请求
		 * @param uiMailID (无符号64位整数)邮件ID
		 */
		public function send_MailDetailReq(uiMailID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 3;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, uiMailID);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：发送邮件
		 * @param strReceiveName 接受者姓名
		 * @param strTitle 邮件标题
		 * @param strMsg 邮件内容
		 */
		public function send_SendMail(strReceiveName:String, strTitle:String, strMsg:String):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 4;
			bytes_.writeByte(funcID_);
			BytesUtil.writeString(bytes_, strReceiveName);
			BytesUtil.writeString(bytes_, strTitle);
			BytesUtil.writeString(bytes_, strMsg);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：删除邮件
		 * @param vecMailIDList (无符号64位整数)请求ID列表
		 */
		public function send_DeleteMail(vecMailIDList:Vector.<BigInteger>):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 5;
			bytes_.writeByte(funcID_);
			BytesUtil.writeVecUInt64(bytes_, vecMailIDList);
			return serverHandler.sendPacket(bytes_);
		}

		/**
		 * 发送：收取附件
		 * @param qwMailID (无符号64位整数)邮件ID
		 */
		public function send_MailAttachmentGetReq(qwMailID:BigInteger):Boolean
		{
			var bytes_:ByteArray = BytesUtil.createByteArray();
			bytes_.writeByte(_protID);
			const funcID_:int = 6;
			bytes_.writeByte(funcID_);
			BytesUtil.writeUInt64(bytes_, qwMailID);
			return serverHandler.sendPacket(bytes_);
		}

		/////////////////////以下为接收处理函数/////////////////////
		//接收处理：页邮件ID回答
		private function _doRecv_MailPageIDAck(bytes:ByteArray):void
		{
			var vecMailIDList:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes); //(无符号64位整数)页面ID列表
			var uStartIndex:uint = bytes.readUnsignedInt(); //(无符号32位整数)当前请求索引
			var uMailTotalNum:uint = bytes.readUnsignedInt(); //(无符号32位整数)邮件总数量
			var eQueryType:uint = bytes.readUnsignedByte(); //(枚举类型：EMailQueryType)邮件类型
			var event_:REvt_MailPageIDAck = new REvt_MailPageIDAck(REvt_MailPageIDAck.DATA_RECEIVE);
			event_.vecMailIDList = vecMailIDList;
			event_.uStartIndex = uStartIndex;
			event_.uMailTotalNum = uMailTotalNum;
			event_.eQueryType = eQueryType;
			dispatchEvent(event_);
		}

		//接收处理：页邮件列表信息回答
		private function _doRecv_MailSummaryListAck(bytes:ByteArray):void
		{
			var vecMailList:Vector.<SMailSummary> = SMailSummary.vectorFromByteArray(bytes); //邮件列表
			var event_:REvt_MailSummaryListAck = new REvt_MailSummaryListAck(REvt_MailSummaryListAck.DATA_RECEIVE);
			event_.vecMailList = vecMailList;
			dispatchEvent(event_);
		}

		//接收处理：页邮件列表信息回答
		private function _doRecv_MailDetailAck(bytes:ByteArray):void
		{
			var rMailDetail:SMailDetail = SMailDetail.fromByteArray(bytes); //邮件详细信息
			var event_:REvt_MailDetailAck = new REvt_MailDetailAck(REvt_MailDetailAck.DATA_RECEIVE);
			event_.rMailDetail = rMailDetail;
			dispatchEvent(event_);
		}

		//接收处理：新邮件通知
		private function _doRecv_NewMailNotify(bytes:ByteArray):void
		{
			var byIsFrameNotify:uint = bytes.readUnsignedByte(); //(无符号8位整数)1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
			var event_:REvt_NewMailNotify = new REvt_NewMailNotify(REvt_NewMailNotify.DATA_RECEIVE);
			event_.byIsFrameNotify = byIsFrameNotify;
			dispatchEvent(event_);
		}

		//接收处理：邮件发送结果
		private function _doRecv_MailSendResult(bytes:ByteArray):void
		{
			var eErrorResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMailErrorResult)返回结果
			var event_:REvt_MailSendResult = new REvt_MailSendResult(REvt_MailSendResult.DATA_RECEIVE);
			event_.eErrorResult = eErrorResult;
			dispatchEvent(event_);
		}

		//接收处理：邮件发送结果
		private function _doRecv_MailDeleteResult(bytes:ByteArray):void
		{
			var vecMailIDList:Vector.<BigInteger> = BytesUtil.readVecUInt64(bytes); //(无符号64位整数)请求ID列表
			var eErrorResult:uint = bytes.readUnsignedByte(); //(枚举类型：EMailErrorResult)返回结果
			var event_:REvt_MailDeleteResult = new REvt_MailDeleteResult(REvt_MailDeleteResult.DATA_RECEIVE);
			event_.vecMailIDList = vecMailIDList;
			event_.eErrorResult = eErrorResult;
			dispatchEvent(event_);
		}

		//接收处理：收取附件结果
		private function _doRecv_MailAttachmentGetAck(bytes:ByteArray):void
		{
			var qwMailID:BigInteger = BytesUtil.readUInt64(bytes); //(无符号64位整数)邮件ID
			var eReSult:uint = bytes.readUnsignedByte(); //(枚举类型：EMailDRawResult)提取附件结果
			var event_:REvt_MailAttachmentGetAck = new REvt_MailAttachmentGetAck(REvt_MailAttachmentGetAck.DATA_RECEIVE);
			event_.qwMailID = qwMailID;
			event_.eReSult = eReSult;
			dispatchEvent(event_);
		}

		/////////////////////以下为单例访问接口/////////////////////
		private static var _instance:MailProt;

		public static function get instance():MailProt
		{
			if(_instance == null)
				_instance = new MailProt();
			return _instance;
		}

		/////////////////////以下为协议接口/////////////////////
		private var _recvFuncList:Array;

		public function MailProt()
		{
			_protID = 19;
			_recvFuncList = [
				_doRecv_MailPageIDAck, //FuncID: 1
				_doRecv_MailSummaryListAck, //FuncID: 2
				_doRecv_MailDetailAck, //FuncID: 3
				_doRecv_NewMailNotify, //FuncID: 4
				_doRecv_MailSendResult, //FuncID: 5
				_doRecv_MailDeleteResult, //FuncID: 6
				_doRecv_MailAttachmentGetAck //FuncID: 7
			];
		}

		public override function handleMessage(bytes:ByteArray):Boolean
		{
			var funcID:int = bytes.readByte();
			if(funcID == 0 || funcID > _recvFuncList.length)
				return false;
			var func:Function;
			if(funcID > 0)
				func = _recvFuncList[funcID - 1];
			if(func != null)
			{
				func(bytes);
				return true;
			}
			return false;
		}
	}
}