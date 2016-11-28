/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateInvitedTask.as
//  Purpose:      协议:邀请好友相关协议, 函数:被邀请任务信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.events.Event;

	/**
	 * 函数UpdateInvitedTask[被邀请任务信息更新]的接收事件
	 */
	public final class REvt_UpdateInvitedTask extends Event
	{
		public static const DATA_RECEIVE:String = "InviteGS_UpdateInvitedTask";
		public static const DATA_ERROR:String = "InviteGS_UpdateInvitedTask_Error";

		public var oInvitedTask:SInvitedTask; //被邀请任务信息

		public function REvt_UpdateInvitedTask(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateInvitedTask/>;
			if(oInvitedTask != null)
				topXml.appendChild(oInvitedTask.toXML("oInvitedTask"));
			return topXml;
		}
	}
}
