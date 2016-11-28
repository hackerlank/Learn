/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailSummaryListAck.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:页邮件列表信息回答
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;

	/**
	 * 函数MailSummaryListAck[页邮件列表信息回答]的接收事件
	 */
	public final class REvt_MailSummaryListAck extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailSummaryListAck";
		public static const DATA_ERROR:String = "MailProt_MailSummaryListAck_Error";

		public var vecMailList:Vector.<SMailSummary>; //邮件列表

		public function REvt_MailSummaryListAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailSummaryListAck/>;
			if(vecMailList != null)
			{
				var vecMailListXml:XML = <Vec_SMailSummary _name_="vecMailList"/>;
				for each(var s1:SMailSummary in vecMailList)
					vecMailListXml.appendChild(s1.toXML());
				topXml.appendChild(vecMailListXml);
			}
			return topXml;
		}
	}
}
