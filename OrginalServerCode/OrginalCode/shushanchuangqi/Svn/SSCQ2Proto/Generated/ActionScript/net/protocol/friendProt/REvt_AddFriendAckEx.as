/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddFriendAckEx.as
//  Purpose:      协议:好友相关协议, 函数:增加好友/黑名单回应Ex
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;

	/**
	 * 函数AddFriendAckEx[增加好友/黑名单回应Ex]的接收事件
	 */
	public final class REvt_AddFriendAckEx extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_AddFriendAckEx";
		public static const DATA_ERROR:String = "FriendProt_AddFriendAckEx_Error";

		public var rFriendEntry:SFriendEntry; //增加的好友

		public function REvt_AddFriendAckEx(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddFriendAckEx/>;
			if(rFriendEntry != null)
				topXml.appendChild(rFriendEntry.toXML("rFriendEntry"));
			return topXml;
		}
	}
}
