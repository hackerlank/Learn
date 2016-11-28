/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_WhisperFailNotify.as
//  Purpose:      协议:好友相关协议, 函数:私聊失败通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
{
	import flash.events.Event;

	/**
	 * 函数WhisperFailNotify[私聊失败通知]的接收事件
	 */
	public final class REvt_WhisperFailNotify extends Event
	{
		public static const DATA_RECEIVE:String = "FriendProt_WhisperFailNotify";
		public static const DATA_ERROR:String = "FriendProt_WhisperFailNotify_Error";

		public var eResult:uint; //(枚举类型：EFriendResult)私聊通知的结果，成功不通知

		public function REvt_WhisperFailNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_WhisperFailNotify eResult={eResult}/>;
			return topXml;
		}
	}
}
