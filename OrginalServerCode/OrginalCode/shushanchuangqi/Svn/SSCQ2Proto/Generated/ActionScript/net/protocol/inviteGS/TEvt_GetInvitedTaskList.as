/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetInvitedTaskList.as
//  Purpose:      协议:邀请好友相关协议, 函数:邀请任务列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
{
	import flash.events.Event;

	/**
	 * 函数GetInvitedTaskList[邀请任务列表]的返回事件
	 */
	public final class TEvt_GetInvitedTaskList extends Event
	{
		public static const DATA_RETURN:String = "InviteGS_GetInvitedTaskList";
		public static const DATA_ERROR:String = "InviteGS_GetInvitedTaskList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetInvitedTaskList; //返回的参数

		public function TEvt_GetInvitedTaskList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetInvitedTaskList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
