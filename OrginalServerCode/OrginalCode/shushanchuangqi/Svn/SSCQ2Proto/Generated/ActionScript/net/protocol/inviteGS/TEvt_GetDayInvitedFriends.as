/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetDayInvitedFriends.as
//  Purpose:      协议:邀请好友相关协议, 函数:每日邀请好友数量
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.events.Event;

	/**
	 * 函数GetDayInvitedFriends[每日邀请好友数量]的返回事件
	 */
	public final class TEvt_GetDayInvitedFriends extends Event
	{
		public static const DATA_RETURN:String = "InviteGS_GetDayInvitedFriends";
		public static const DATA_ERROR:String = "InviteGS_GetDayInvitedFriends_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetDayInvitedFriends; //返回的参数

		public function TEvt_GetDayInvitedFriends(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetDayInvitedFriends ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
