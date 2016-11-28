/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FriendInfoNotify.as
//  Purpose:      协议:好友相关协议, 函数:好友信息通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;

	/**
	 * 函数FriendInfoNotify[好友信息通知]的接收事件
	 */
	public final class REvt_FriendInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_FriendInfoNotify";
		public static const DATA_ERROR:String = "FriendProt_FriendInfoNotify_Error";

		public var rFriend:SFriend; //好友信息

		public function REvt_FriendInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FriendInfoNotify/>;
			if(rFriend != null)
				topXml.appendChild(rFriend.toXML("rFriend"));
			return topXml;
		}
	}
}
