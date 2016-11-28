/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_FighterInfoNotify.as
//  Purpose:      协议:玩家在GameServer的消息处理, 函数:散仙信息通知列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
{
	import flash.events.Event;

	/**
	 * 函数FighterInfoNotify[散仙信息通知列表]的接收事件
	 */
	public final class REvt_FighterInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "RoleEvent_FighterInfoNotify";
		public static const DATA_ERROR:String = "RoleEvent_FighterInfoNotify_Error";

		public var vecFighters:Vector.<SFighterSpecInfo>; //散仙信息

		public function REvt_FighterInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_FighterInfoNotify/>;
			if(vecFighters != null)
			{
				var vecFightersXml:XML = <Vec_SFighterSpecInfo _name_="vecFighters"/>;
				for each(var s1:SFighterSpecInfo in vecFighters)
					vecFightersXml.appendChild(s1.toXML());
				topXml.appendChild(vecFightersXml);
			}
			return topXml;
		}
	}
}
