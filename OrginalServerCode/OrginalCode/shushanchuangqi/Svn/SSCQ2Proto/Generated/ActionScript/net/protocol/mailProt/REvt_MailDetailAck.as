/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailDetailAck.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:页邮件列表信息回答
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;

	/**
	 * 函数MailDetailAck[页邮件列表信息回答]的接收事件
	 */
	public final class REvt_MailDetailAck extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailDetailAck";
		public static const DATA_ERROR:String = "MailProt_MailDetailAck_Error";

		public var rMailDetail:SMailDetail; //邮件详细信息

		public function REvt_MailDetailAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailDetailAck/>;
			if(rMailDetail != null)
				topXml.appendChild(rMailDetail.toXML("rMailDetail"));
			return topXml;
		}
	}
}
