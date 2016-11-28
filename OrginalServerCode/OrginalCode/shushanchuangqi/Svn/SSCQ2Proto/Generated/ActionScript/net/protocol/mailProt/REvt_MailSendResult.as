/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_MailSendResult.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:邮件发送结果
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;

	/**
	 * 函数MailSendResult[邮件发送结果]的接收事件
	 */
	public final class REvt_MailSendResult extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_MailSendResult";
		public static const DATA_ERROR:String = "MailProt_MailSendResult_Error";

		public var eErrorResult:uint; //(枚举类型：EMailErrorResult)返回结果

		public function REvt_MailSendResult(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_MailSendResult eErrorResult={eErrorResult}/>;
			return topXml;
		}
	}
}
