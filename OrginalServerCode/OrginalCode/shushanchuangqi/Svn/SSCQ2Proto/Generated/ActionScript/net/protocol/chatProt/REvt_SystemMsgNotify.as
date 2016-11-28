/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SystemMsgNotify.as
//  Purpose:      协议:聊天协议, 函数:系统信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
{
	import flash.events.Event;

	/**
	 * 函数SystemMsgNotify[系统信息通知]的接收事件
	 */
	public final class REvt_SystemMsgNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ChatProt_SystemMsgNotify";
		public static const DATA_ERROR:String = "ChatProt_SystemMsgNotify_Error";

		public var eChannelType:uint; //(枚举类型：globalChatProt.EChannelType)通道类型
		public var strInfo:String; //聊天信息
		public var eSubType:uint; //(枚举类型：globalChatProt.EChannelSubType)额外信息

		public function REvt_SystemMsgNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SystemMsgNotify eChannelType={eChannelType} strInfo={strInfo} eSubType={eSubType}/>;
			return topXml;
		}
	}
}
