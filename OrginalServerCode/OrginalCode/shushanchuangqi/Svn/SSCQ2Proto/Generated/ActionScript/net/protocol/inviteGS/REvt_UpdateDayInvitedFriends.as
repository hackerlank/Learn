/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateDayInvitedFriends.as
//  Purpose:      协议:邀请好友相关协议, 函数:每日邀请好友数量
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.events.Event;

	/**
	 * 函数UpdateDayInvitedFriends[每日邀请好友数量]的接收事件
	 */
	public final class REvt_UpdateDayInvitedFriends extends Event
	{
		public static const DATA_RECEIVE:String = "InviteGS_UpdateDayInvitedFriends";
		public static const DATA_ERROR:String = "InviteGS_UpdateDayInvitedFriends_Error";

		public var dwInviteCnt:uint; //(无符号32位整数)邀请数量

		public function REvt_UpdateDayInvitedFriends(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateDayInvitedFriends dwInviteCnt={dwInviteCnt}/>;
			return topXml;
		}
	}
}
