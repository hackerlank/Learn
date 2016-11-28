/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_DelAppearIconNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:删除AppearIcon通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;

	/**
	 * 函数DelAppearIconNotify[删除AppearIcon通知]的接收事件
	 */
	public final class REvt_DelAppearIconNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_DelAppearIconNotify";
		public static const DATA_ERROR:String = "RoleEvent_DelAppearIconNotify_Error";

		public var wIconID:uint; //(无符号16位整数)删除的IconApear

		public function REvt_DelAppearIconNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_DelAppearIconNotify wIconID={wIconID}/>;
			return topXml;
		}
	}
}
