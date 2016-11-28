/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SystemMsgIDNotify.as
//  Purpose:      协议:全局聊天协议, 函数:系统MsgID通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
{
	import flash.events.Event;

	/**
	 * 函数SystemMsgIDNotify[系统MsgID通知]的接收事件
	 */
	public final class REvt_SystemMsgIDNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GlobalChatProt_SystemMsgIDNotify";
		public static const DATA_ERROR:String = "GlobalChatProt_SystemMsgIDNotify_Error";

		public var wMsgID:uint; //(无符号16位整数)消息ID

		public function REvt_SystemMsgIDNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SystemMsgIDNotify wMsgID={wMsgID}/>;
			return topXml;
		}
	}
}
