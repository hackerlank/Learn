/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SysDialogAndNoticeUpdateNotify.as
//  Purpose:      协议:全局聊天协议, 函数:系统弹窗和公告更新通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.events.Event;

	/**
	 * 函数SysDialogAndNoticeUpdateNotify[系统弹窗和公告更新通知]的接收事件
	 */
	public final class REvt_SysDialogAndNoticeUpdateNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GlobalChatProt_SysDialogAndNoticeUpdateNotify";
		public static const DATA_ERROR:String = "GlobalChatProt_SysDialogAndNoticeUpdateNotify_Error";

		public var byNotifyType:uint; //(无符号8位整数)通知类型1:系统弹窗通知；2、公告更新通知

		public function REvt_SysDialogAndNoticeUpdateNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SysDialogAndNoticeUpdateNotify byNotifyType={byNotifyType}/>;
			return topXml;
		}
	}
}
