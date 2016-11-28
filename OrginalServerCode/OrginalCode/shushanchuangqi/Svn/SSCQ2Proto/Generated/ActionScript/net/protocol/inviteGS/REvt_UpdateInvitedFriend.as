/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateInvitedFriend.as
//  Purpose:      协议:邀请好友相关协议, 函数:被邀请好友信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.events.Event;

	/**
	 * 函数UpdateInvitedFriend[被邀请好友信息更新]的接收事件
	 */
	public final class REvt_UpdateInvitedFriend extends Event
	{
		public static const DATA_RECEIVE:String = "InviteGS_UpdateInvitedFriend";
		public static const DATA_ERROR:String = "InviteGS_UpdateInvitedFriend_Error";

		public var oInvitedFriend:SInvitedFriend; //查询返回

		public function REvt_UpdateInvitedFriend(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateInvitedFriend/>;
			if(oInvitedFriend != null)
				topXml.appendChild(oInvitedFriend.toXML("oInvitedFriend"));
			return topXml;
		}
	}
}
