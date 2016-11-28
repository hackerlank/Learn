/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NewMailNotify.as
//  Purpose:      协议:邮件CenterServer通讯协议, 函数:新邮件通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
{
	import flash.events.Event;

	/**
	 * 函数NewMailNotify[新邮件通知]的接收事件
	 */
	public final class REvt_NewMailNotify extends Event
	{
		public static const DATA_RECEIVE:String = "MailProt_NewMailNotify";
		public static const DATA_ERROR:String = "MailProt_NewMailNotify_Error";

		public var byIsFrameNotify:uint; //(无符号8位整数)1:需要弹框显示 0:不需要弹框显示(邮件闪烁)

		public function REvt_NewMailNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NewMailNotify byIsFrameNotify={byIsFrameNotify}/>;
			return topXml;
		}
	}
}
