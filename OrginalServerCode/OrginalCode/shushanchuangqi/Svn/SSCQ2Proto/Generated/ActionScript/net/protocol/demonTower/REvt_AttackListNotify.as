/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AttackListNotify.as
//  Purpose:      协议:锁妖塔, 函数:被攻击列表通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTower
{
	import flash.events.Event;

	/**
	 * 函数AttackListNotify[被攻击列表通知]的接收事件
	 */
	public final class REvt_AttackListNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DemonTower_AttackListNotify";
		public static const DATA_ERROR:String = "DemonTower_AttackListNotify_Error";

		public var oDemonToweAttackedInfo:Vector.<SDemonToweAttackedInfo>; //被攻击列表

		public function REvt_AttackListNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AttackListNotify/>;
			if(oDemonToweAttackedInfo != null)
			{
				var oDemonToweAttackedInfoXml:XML = <Vec_SDemonToweAttackedInfo _name_="oDemonToweAttackedInfo"/>;
				for each(var s1:SDemonToweAttackedInfo in oDemonToweAttackedInfo)
					oDemonToweAttackedInfoXml.appendChild(s1.toXML());
				topXml.appendChild(oDemonToweAttackedInfoXml);
			}
			return topXml;
		}
	}
}
