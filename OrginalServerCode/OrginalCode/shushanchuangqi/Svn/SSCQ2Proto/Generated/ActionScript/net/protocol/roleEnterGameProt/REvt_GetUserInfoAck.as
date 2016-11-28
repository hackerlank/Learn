/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GetUserInfoAck.as
//  Purpose:      协议:角色信息相关操作协议, 函数:角色查询返回
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEnterGameProt
{
	import flash.events.Event;

	/**
	 * 函数GetUserInfoAck[角色查询返回]的接收事件
	 */
	public final class REvt_GetUserInfoAck extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEnterGameProt_GetUserInfoAck";
		public static const DATA_ERROR:String = "RoleEnterGameProt_GetUserInfoAck_Error";

		public var stRoleEnterInfo:RoleEnterGameData; //进入信息

		public function REvt_GetUserInfoAck(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GetUserInfoAck/>;
			if(stRoleEnterInfo != null)
				topXml.appendChild(stRoleEnterInfo.toXML("stRoleEnterInfo"));
			return topXml;
		}
	}
}
