/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SlotItemCDNotify.as
//  Purpose:      协议:道具相关协议, 函数:角色道具冷却通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数SlotItemCDNotify[角色道具冷却通知]的接收事件
	 */
	public final class REvt_SlotItemCDNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_SlotItemCDNotify";
		public static const DATA_ERROR:String = "ItemProt_SlotItemCDNotify_Error";

		public var vecItemCold:Vector.<SItemColdTime>; //道具使用冷却时间
		public var vecGroupCold:Vector.<SItemColdTime>; //道具公共冷却时间

		public function REvt_SlotItemCDNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SlotItemCDNotify/>;
			if(vecItemCold != null)
			{
				var vecItemColdXml:XML = <Vec_SItemColdTime _name_="vecItemCold"/>;
				for each(var s1:SItemColdTime in vecItemCold)
					vecItemColdXml.appendChild(s1.toXML());
				topXml.appendChild(vecItemColdXml);
			}
			if(vecGroupCold != null)
			{
				var vecGroupColdXml:XML = <Vec_SItemColdTime _name_="vecGroupCold"/>;
				for each(var s2:SItemColdTime in vecGroupCold)
					vecGroupColdXml.appendChild(s2.toXML());
				topXml.appendChild(vecGroupColdXml);
			}
			return topXml;
		}
	}
}
