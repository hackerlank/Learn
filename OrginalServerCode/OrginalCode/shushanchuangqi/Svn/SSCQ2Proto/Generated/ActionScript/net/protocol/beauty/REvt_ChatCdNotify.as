/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ChatCdNotify.as
//  Purpose:      协议:美女系统, 函数:聊天cd
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数ChatCdNotify[聊天cd]的接收事件
	 */
	public final class REvt_ChatCdNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Beauty_ChatCdNotify";
		public static const DATA_ERROR:String = "Beauty_ChatCdNotify_Error";

		public var dwNextChatTime:uint; //(无符号32位整数)下次聊天冷却时间

		public function REvt_ChatCdNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ChatCdNotify dwNextChatTime={dwNextChatTime}/>;
			return topXml;
		}
	}
}
