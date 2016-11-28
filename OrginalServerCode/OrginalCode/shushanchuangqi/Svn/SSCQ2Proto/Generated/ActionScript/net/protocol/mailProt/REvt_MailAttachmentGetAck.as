/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailAttachmentGetAck.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:收取附件结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;
	import com.hurlant.math.BigInteger;

	/**
	 * 函数MailAttachmentGetAck[收取附件结果]的接收事件
	 */
	public final class REvt_MailAttachmentGetAck extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailAttachmentGetAck";
		public static const DATA_ERROR:String = "MailProt_MailAttachmentGetAck_Error";

		public var qwMailID:BigInteger; //(无符号64位整数)邮件ID
		public var eReSult:uint; //(枚举类型：EMailDRawResult)提取附件结果

		public function REvt_MailAttachmentGetAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailAttachmentGetAck qwMailID={qwMailID} eReSult={eReSult}/>;
			return topXml;
		}
	}
}
