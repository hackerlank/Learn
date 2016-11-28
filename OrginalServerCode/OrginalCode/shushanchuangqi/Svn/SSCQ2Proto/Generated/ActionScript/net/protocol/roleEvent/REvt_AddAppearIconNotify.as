/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddAppearIconNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:增加的AppearIcon通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;

	/**
	 * 函数AddAppearIconNotify[增加的AppearIcon通知]的接收事件
	 */
	public final class REvt_AddAppearIconNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_AddAppearIconNotify";
		public static const DATA_ERROR:String = "RoleEvent_AddAppearIconNotify_Error";

		public var vecAppearIcon:Vector.<uint>; //(无符号16位整数)增加的Icon列表

		public function REvt_AddAppearIconNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddAppearIconNotify/>;
			if(vecAppearIcon != null)
			{
				var vecAppearIconXml:XML = <Vec_UINT16 _name_="vecAppearIcon"/>;
				var text1:String = "";
				for each(var value1:uint in vecAppearIcon)
					text1 += "[" + value1 + "]";
				vecAppearIconXml.appendChild(text1);
				topXml.appendChild(vecAppearIconXml);
			}
			return topXml;
		}
	}
}
